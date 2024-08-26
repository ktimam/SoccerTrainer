#include "FieldPlayer.h"
#include "PlayerBase.h"
#include "SteeringBehaviors.h"
#include "../Common/2D/Transformations.h"
#include "../Common/2D/Geometry.h"
//#include "Common/misc/Cgdi.h"
#include "../Common/2D/C2DMatrix.h"
#include "FieldGoal.h"
#include "../Common/Game/Region.h"
#include "../Common/Game/EntityFunctionTemplates.h"
#include "ParamLoader.h"
#include "SoccerTeam.h"
//#include "time/Regulator.h"
#include "../Common/Debug/DebugConsole.h"


#include <limits>

using std::vector;

//------------------------------- dtor ---------------------------------------
//----------------------------------------------------------------------------
FieldPlayer::~FieldPlayer()
{
    m_Brain->Save("Models/model" + to_string(ID()));

  //delete m_pKickLimiter;
  delete m_pStateMachine;
}

//----------------------------- ctor -------------------------------------
//------------------------------------------------------------------------
FieldPlayer::FieldPlayer(SoccerTeam* home_team,
                      int   home_region,
                      State<FieldPlayer>* start_state,
                      BodyInterface& bodyInterface, BodyID body_id,
                      double    max_force,
                      double    max_speed,
                      double    max_turn_rate,
                      player_role role,
                      FieldPlayerMLP* brain): PlayerBase(home_team,
                                                    home_region,
                                                    bodyInterface, body_id,
                                                    max_force,
                                                    max_speed,
                                                    max_turn_rate,
                                                    role,
                                                    brain)                                    
{
  //set up the state machine
  m_pStateMachine =  new StateMachine<FieldPlayer>(this);

  if (start_state)
  {    
    m_pStateMachine->SetCurrentState(start_state);
    m_pStateMachine->SetPreviousState(start_state);
    m_pStateMachine->SetGlobalState(GlobalPlayerState::Instance());

    m_pStateMachine->CurrentState()->Enter(this);
  }    

  m_pSteering->SeparationOn();

  //set up the kick regulator
  //m_pKickLimiter = new Regulator(Prm.PlayerKickFrequency);
}

//------------------------------ Update ----------------------------------
//
//  
//------------------------------------------------------------------------
void FieldPlayer::Update()
{ 
  //run the logic for the current state
  m_pStateMachine->Update();

  Action target_action;

  target_action.KickBall = m_ActionKickBall;
  target_action.KickForce = 0;
  target_action.KickDirection = Vec3();
  if (m_ActionKickBall) {
      target_action.KickForce = m_ActionKickBallForce;
      target_action.KickDirection = m_ActionKickBallDirection;
  }

  target_action.TrackBall = m_ActionTrackBall;

  //calculate the combined steering force
  m_pSteering->Calculate();
  double ForwardForce = m_pSteering->ForwardComponent();
  double TurningForce = m_pSteering->SideComponent();
  target_action.ForwardForce = ForwardForce;
  target_action.TurningForce = TurningForce;

  //Deep Learning Logic
  Action action = m_Brain->Process(GetObservation(), true, target_action);
  if (action.ForwardForce == INFINITY) {
      std::cout << "NAN : " << INFINITY << std::endl;
  }
  if (m_AIType == nn) {
      ForwardForce = action.ForwardForce;
      TurningForce = action.TurningForce;

      m_ActionKickBall = action.KickBall;
      m_ActionKickBallForce = action.KickForce;
      m_ActionKickBallDirection = action.KickDirection;

      m_ActionTrackBall = action.TrackBall;
  }
  //End Deep Learning
  
  //Perform Actions
  if (m_ActionKickBall && BallWithinKickingRange()) {
      Ball()->Kick(m_ActionKickBallDirection, m_ActionKickBallForce);
  }
  m_ActionKickBall = false;
  if (m_ActionTrackBall) {
      TrackBall();
  }
  m_ActionTrackBall = false;
  //if no steering force is produced decelerate the player by applying a
  //braking force
  if (m_pSteering->Force().IsNearZero())
  {
      const double BrakingRate = 0.8;

      SetVelocity(Velocity() * BrakingRate);
  }

  ForwardForce = Clamp(ForwardForce, -m_dMaxForce, m_dMaxForce);

  //the steering force's side component is a force that rotates the 
  //player about its axis. We must limit the rotation so that a player
  //can only turn by PlayerMaxTurnRate rads per update.
  TurningForce = Clamp(TurningForce, -m_dMaxTurnRate, m_dMaxTurnRate);

  //rotate the heading vector
  //Vec2DRotateAroundOrigin(m_vHeading, TurningForce);
  //m_BodyInterface.SetAngularVelocity(m_EntityPhysicsID, Vec3(0, TurningForce, 0));
  Rotate(TurningForce);

  //make sure the velocity vector points in the same direction as
  //the heading vector
  SetVelocity(Heading() * Velocity().Length());

  //now to calculate the acceleration due to the force exerted by
  //the forward component of the steering force in the direction
  //of the player's heading
  Vec3 Acceleration = Heading() * ForwardForce / Mass();

  m_BodyInterface.AddLinearVelocity(m_EntityPhysicsID, Acceleration);

  //make sure player does not exceed maximum velocity
  SetVelocity(Vec3::sClamp(Velocity(), Vec3(-m_dMaxSpeed, -m_dMaxSpeed, -m_dMaxSpeed), Vec3(m_dMaxSpeed, m_dMaxSpeed, m_dMaxSpeed)));
}

//-------------------- HandleMessage -------------------------------------
//
//  routes any messages appropriately
//------------------------------------------------------------------------
bool FieldPlayer::HandleMessage(const Telegram& msg)
{
  return m_pStateMachine->HandleMessage(msg);
}


