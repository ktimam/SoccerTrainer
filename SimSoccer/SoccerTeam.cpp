#include "SoccerTeam.h"
#include "SoccerPitch.h"
#include "FieldGoal.h"
#include "PlayerBase.h"
#include "GoalKeeper.h"
#include "FieldPlayer.h"
#include "../Common/misc/utils.h"
#include "SteeringBehaviors.h"
#include "GoalKeeperStates.h"
#include "ParamLoader.h"
#include "../Common/2D/geometry.h"
#include "../Common/Game/EntityManager.h"
#include "../Common/Messaging/MessageDispatcher.h"
#include "SoccerMessages.h"
#include "TeamStates.h"
#include "PitchManager.h"
//#include "Debug/DebugConsole.h"
//#include <windows.h>

#include <Jolt/Physics/Character/Character.h>
#include <Jolt/Physics/Collision/Shape/CapsuleShape.h>
#include <Jolt/Physics/Collision/Shape/CylinderShape.h>
#include <Jolt/Physics/Collision/Shape/RotatedTranslatedShape.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Collision/Shape/MeshShape.h>

using std::vector;

//these define the home regions for this state of each of the players
std::vector<int> SoccerTeam::BlueAttackingRegions = { 1,12,14,6,4 };
std::vector<int> SoccerTeam::RedAttackingRegions  = { 16,3,5,9,13 };
std::vector<int> SoccerTeam::BlueDefendingRegions = { 1,6,8,3,5 };
std::vector<int> SoccerTeam::RedDefendingRegions  = { 16,9,11,12,14 };

//----------------------------- ctor -------------------------------------
//
//------------------------------------------------------------------------
SoccerTeam::SoccerTeam(FieldGoal*        home_goal,
                       FieldGoal*        opponents_goal,
                       SoccerPitch* pitch,
                       team_color   color):m_pOpponentsGoal(opponents_goal),
                                           m_pHomeGoal(home_goal),
                                           m_pOpponents(NULL),
                                           m_pPitch(pitch),
                                           m_Color(color),
                                           m_dDistSqToBallOfClosestPlayer(0.0),
                                           m_pSupportingPlayer(NULL),
                                           m_pReceivingPlayer(NULL),
                                           m_pControllingPlayer(NULL),
                                           m_pPlayerClosestToBall(NULL)
{
  //setup the state machine
  m_pStateMachine = new StateMachine<SoccerTeam>(this);

  m_pStateMachine->SetCurrentState(PrepareForKickOff::Instance());
  m_pStateMachine->SetPreviousState(Defending::Instance());
  m_pStateMachine->SetGlobalState(NULL);

}

//----------------------- Init -------------------------------------------
//
//------------------------------------------------------------------------
void SoccerTeam::Init()
{

    //create the players and goalkeeper
    CreatePlayers();

    //set default steering behaviors
    std::vector<PlayerBase*>::iterator it = m_Players.begin();

    for (it; it != m_Players.end(); ++it)
    {
        (*it)->Steering()->SeparationOn();
    }

    //create the sweet spot calculator
    m_pSupportSpotCalc = new SupportSpotCalculator(Prm.NumSupportSpotsX,
        Prm.NumSupportSpotsY,
        this);
}

//----------------------- dtor -------------------------------------------
//
//------------------------------------------------------------------------
SoccerTeam::~SoccerTeam()
{
  delete m_pStateMachine;

  std::vector<PlayerBase*>::iterator it = m_Players.begin();
  for (it; it != m_Players.end(); ++it)
  {
    delete *it;
  }

  delete m_pSupportSpotCalc;
}

//-------------------------- update --------------------------------------
//
//  iterates through each player's update function and calculates 
//  frequently accessed info
//------------------------------------------------------------------------
void SoccerTeam::Update()
{
  //this information is used frequently so it's more efficient to 
  //calculate it just once each frame
  CalculateClosestPlayerToBall();

  //the team state machine switches between attack/defense behavior. It
  //also handles the 'kick off' state where a team must return to their
  //kick off positions before the whistle is blown
  m_pStateMachine->Update();
  
  //now update each player
  std::vector<PlayerBase*>::iterator it = m_Players.begin();

  for (it; it != m_Players.end(); ++it)
  {
    (*it)->Update();
  }

}


//------------------------ CalculateClosestPlayerToBall ------------------
//
//  sets m_iClosestPlayerToBall to the player closest to the ball
//------------------------------------------------------------------------
void SoccerTeam::CalculateClosestPlayerToBall()
{
  double ClosestSoFar = MaxFloat;

  std::vector<PlayerBase*>::iterator it = m_Players.begin();

  for (it; it != m_Players.end(); ++it)
  {
    //calculate the dist. Use the squared value to avoid sqrt
    double dist = ((*it)->Pos()- Pitch()->Ball()->Pos()).LengthSq();

    //keep a record of this value for each player
    (*it)->SetDistSqToBall(dist);
    
    if (dist < ClosestSoFar)
    {
      ClosestSoFar = dist;

      m_pPlayerClosestToBall = *it;
    }
  }

  m_dDistSqToBallOfClosestPlayer = ClosestSoFar;
}


//------------- DetermineBestSupportingAttacker ------------------------
//
// calculate the closest player to the SupportSpot
//------------------------------------------------------------------------
PlayerBase* SoccerTeam::DetermineBestSupportingAttacker()
{
  double ClosestSoFar = MaxFloat;

  PlayerBase* BestPlayer = NULL;

  std::vector<PlayerBase*>::iterator it = m_Players.begin();

  for (it; it != m_Players.end(); ++it)
  {
    //only attackers utilize the BestSupportingSpot
    if ( ((*it)->Role() == PlayerBase::attacker) && ((*it) != m_pControllingPlayer) )
    {
      //calculate the dist. Use the squared value to avoid sqrt
      double dist = ((*it)->Pos()- m_pSupportSpotCalc->GetBestSupportingSpot()).LengthSq();
    
      //if the distance is the closest so far and the player is not a
      //goalkeeper and the player is not the one currently controlling
      //the ball, keep a record of this player
      if ((dist < ClosestSoFar) )
      {
        ClosestSoFar = dist;

        BestPlayer = (*it);
      }
    }
  }

  return BestPlayer;
}

//-------------------------- FindPass ------------------------------
//
//  The best pass is considered to be the pass that cannot be intercepted 
//  by an opponent and that is as far forward of the receiver as possible
//------------------------------------------------------------------------
bool SoccerTeam::FindPass(const PlayerBase*const passer,
                         PlayerBase*&           receiver,
                         Vec3&              PassTarget,
                         double                  power,
                         double                  MinPassingDistance)const
{  
  
  std::vector<PlayerBase*>::const_iterator curPlyr = Members().begin();

  double    ClosestToGoalSoFar = MaxFloat;
  Vec3 Target;

  //iterate through all this player's team members and calculate which
  //one is in a position to be passed the ball 
  for (curPlyr; curPlyr != Members().end(); ++curPlyr)
  {   
    //make sure the potential receiver being examined is not this player
    //and that it is further away than the minimum pass distance
    if ( (*curPlyr != passer) &&            
        ((passer->Pos()- (*curPlyr)->Pos()).LengthSq() >
         MinPassingDistance*MinPassingDistance))                  
    {           
      if (GetBestPassToReceiver(passer, *curPlyr, Target, power))
      {
        //if the pass target is the closest to the opponent's goal line found
        // so far, keep a record of it
        double Dist2Goal = fabs(Target.GetX() - OpponentsGoal()->Center().GetX());

        if (Dist2Goal < ClosestToGoalSoFar)
        {
          ClosestToGoalSoFar = Dist2Goal;
          
          //keep a record of this player
          receiver = *curPlyr;

          //and the target
          PassTarget = Target;
        }     
      }
    }
  }//next team member

  if (receiver) return true;
 
  else return false;
}


//---------------------- GetBestPassToReceiver ---------------------------
//
//  Three potential passes are calculated. One directly toward the receiver's
//  current position and two that are the tangents from the ball position
//  to the circle of radius 'range' from the receiver.
//  These passes are then tested to see if they can be intercepted by an
//  opponent and to make sure they terminate within the playing area. If
//  all the passes are invalidated the function returns false. Otherwise
//  the function returns the pass that takes the ball closest to the 
//  opponent's goal area.
//------------------------------------------------------------------------
bool SoccerTeam::GetBestPassToReceiver(const PlayerBase* const passer,
                                       const PlayerBase* const receiver,
                                       Vec3&               PassTarget,
                                       double                   power)const
{  
  //first, calculate how much time it will take for the ball to reach 
  //this receiver, if the receiver was to remain motionless 
  double time = Pitch()->Ball()->TimeToCoverDistance(Pitch()->Ball()->Pos(),
                                                    receiver->Pos(),
                                                    power);

  //return false if ball cannot reach the receiver after having been
  //kicked with the given power
  if (time < 0) return false;

  //the maximum distance the receiver can cover in this time
  double InterceptRange = time * receiver->MaxSpeed();
  
  //Scale the intercept range
  const double ScalingFactor = 0.01;
  InterceptRange *= ScalingFactor;

  //now calculate the pass targets which are positioned at the intercepts
  //of the tangents from the ball to the receiver's range circle.
  Vector2D ip1, ip2;

  GetTangentPoints(Vector2D(receiver->Pos().GetX(), receiver->Pos().GetZ()),
                   InterceptRange,
                   Vector2D(Pitch()->Ball()->Pos().GetX(), Pitch()->Ball()->Pos().GetZ()),
                   ip1,
                   ip2);
 
  const int NumPassesToTry = 3;
  Vector2D Passes[NumPassesToTry] = {ip1, Vector2D(receiver->Pos().GetX(),receiver->Pos().GetZ()), ip2};
  
  
  // this pass is the best found so far if it is:
  //
  //  1. Further upfield than the closest valid pass for this receiver
  //     found so far
  //  2. Within the playing area
  //  3. Cannot be intercepted by any opponents

  double ClosestSoFar = MaxFloat;
  bool  bResult      = false;

  for (int pass=0; pass<NumPassesToTry; ++pass)
  {    
    double dist = fabs(Passes[pass].x - OpponentsGoal()->Center().GetX());

    if (( dist < ClosestSoFar) &&
        Pitch()->PlayingArea()->Inside(Vec3(Passes[pass].x,0, Passes[pass].y)) &&
        isPassSafeFromAllOpponents(Vector2D(Pitch()->Ball()->Pos().GetX(), Pitch()->Ball()->Pos().GetZ()),
                                   Passes[pass],
                                   receiver,
                                   power))
        
    {
      ClosestSoFar = dist;
      PassTarget   = Vec3(Passes[pass].x, 0, Passes[pass].y);
      bResult      = true;
    }
  }

  return bResult;
}

//----------------------- isPassSafeFromOpponent -------------------------
//
//  test if a pass from 'from' to 'to' can be intercepted by an opposing
//  player
//------------------------------------------------------------------------
bool SoccerTeam::isPassSafeFromOpponent(Vector2D    from,
                                        Vector2D    target,
                                        const PlayerBase* const receiver,
                                        const PlayerBase* const opp,
                                        double       PassingForce)const
{
  //move the opponent into local space.
    Vector2D ToTarget = target - from;
    Vector2D ToTargetNormalized = Vec2DNormalize(ToTarget);

    Vector2D LocalPosOpp = PointToLocalSpace(Vector2D(opp->Pos().GetX(), opp->Pos().GetZ()),
                                         ToTargetNormalized,
                                         ToTargetNormalized.Perp(),
                                         from);

  //if opponent is behind the kicker then pass is considered okay(this is 
  //based on the assumption that the ball is going to be kicked with a 
  //velocity greater than the opponent's max velocity)
  if ( LocalPosOpp.x < 0 )
  {     
    return true;
  }
  
  //if the opponent is further away than the target we need to consider if
  //the opponent can reach the position before the receiver.
  if (Vec2DDistanceSq(from, target) < Vec2DDistanceSq(Vector2D(opp->Pos().GetX(), opp->Pos().GetZ()), from))
  {
    if (receiver)
    {
      if ( Vec2DDistanceSq(target, Vector2D(opp->Pos().GetX(), opp->Pos().GetZ()))  >
           Vec2DDistanceSq(target, Vector2D(receiver->Pos().GetX(), receiver->Pos().GetZ())) )
      {
        return true;
      }

      else
      {
        return false;
      }

    }

    else
    {
      return true;
    } 
  }
  
  //calculate how long it takes the ball to cover the distance to the 
  //position orthogonal to the opponents position
  double TimeForBall = 
  Pitch()->Ball()->TimeToCoverDistance(Vec3(0,0,0),
                                       Vec3(LocalPosOpp.x, 0, 0),
                                       PassingForce);

  //now calculate how far the opponent can run in this time
  double reach = opp->MaxSpeed() * TimeForBall;

  //if the distance to the opponent's y position is less than his running
  //range plus the radius of the ball and the opponents radius then the
  //ball can be intercepted
  if ( fabs(LocalPosOpp.y) < reach )
  {
    return false;
  }

  return true;
}

//---------------------- isPassSafeFromAllOpponents ----------------------
//
//  tests a pass from position 'from' to position 'target' against each member
//  of the opposing team. Returns true if the pass can be made without
//  getting intercepted
//------------------------------------------------------------------------
bool SoccerTeam::isPassSafeFromAllOpponents(Vector2D                from,
                                            Vector2D                target,
                                            const PlayerBase* const receiver,
                                            double     PassingForce)const
{
  std::vector<PlayerBase*>::const_iterator opp = Opponents()->Members().begin();

  for (opp; opp != Opponents()->Members().end(); ++opp)
  {
    if (!isPassSafeFromOpponent(from, target, receiver, *opp, PassingForce))
    {
      //debug_on
        
      return false;
    }
  }

  return true;
}

//------------------------ CanShoot --------------------------------------
//
//  Given a ball position, a kicking power and a reference to a Vec3
//  this function will sample random positions along the opponent's goal-
//  mouth and check to see if a goal can be scored if the ball was to be
//  kicked in that direction with the given power. If a possible shot is 
//  found, the function will immediately return true, with the target 
//  position stored in the vector ShotTarget.
//------------------------------------------------------------------------
bool SoccerTeam::CanShoot(Vec3  BallPos,
                          double     power, 
                          Vec3& ShotTarget)const
{
  //the number of randomly created shot targets this method will test 
  int NumAttempts = Prm.NumAttemptsToFindValidStrike;

  while (NumAttempts--)
  {
    //choose a random position along the opponent's goal mouth. (making
    //sure the ball's radius is taken into account)
    ShotTarget = Vec3(OpponentsGoal()->Center());

    //the y value of the shot position should lay somewhere between two
    //goalposts (taking into consideration the ball diameter)
    int MinYVal = OpponentsGoal()->LeftPost().GetX();// +Pitch()->Ball()->BRadius();
    int MaxYVal = OpponentsGoal()->RightPost().GetX();// -Pitch()->Ball()->BRadius();

    ShotTarget.SetX((double)RandInt(MinYVal, MaxYVal));

    //make sure striking the ball with the given power is enough to drive
    //the ball over the goal line.
    double time = Pitch()->Ball()->TimeToCoverDistance(BallPos,
                                                      ShotTarget,
                                                      power);
    
    //if it is, this shot is then tested to see if any of the opponents
    //can intercept it.
    if (time >= 0)
    {
      if (isPassSafeFromAllOpponents(Vector2D(BallPos.GetX(), BallPos.GetZ()), Vector2D(ShotTarget.GetX(), ShotTarget.GetZ()), NULL, power))
      {
        return true;
      }
    }
  }
  
  return false;
}

 
//--------------------- ReturnAllFieldPlayersToHome ---------------------------
//
//  sends a message to all players to return to their home areas forthwith
//------------------------------------------------------------------------
void SoccerTeam::ReturnAllFieldPlayersToHome()const
{
  std::vector<PlayerBase*>::const_iterator it = m_Players.begin();

  for (it; it != m_Players.end(); ++it)
  {
    if ((*it)->Role() != PlayerBase::goal_keeper)
    {
      Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
                            1,
                            (*it)->ID(),
                            Msg_GoHome,
                            NULL);
    }
  }
}

//------------------------- CreatePlayers --------------------------------
//
//  creates the players
//------------------------------------------------------------------------
void SoccerTeam::CreatePlayers()
{
    float player_elevation = 0.2f;
    // Character size
    float	cCharacterHeightStanding = 1.5f;
    float	cCharacterRadiusStanding = 0.2f;

    // Create 'player' character
    Ref<CharacterSettings> settings = new CharacterSettings();
    settings->mMaxSlopeAngle = DegreesToRadians(45.0f);
    settings->mLayer = Layers::MOVING;
    settings->mShape = RotatedTranslatedShapeSettings(Vec3(0, 0.5f * cCharacterHeightStanding + cCharacterRadiusStanding, 0), Quat::sIdentity(), new CapsuleShape(0.5f * cCharacterHeightStanding, cCharacterRadiusStanding)).Create().Get();
    settings->mFriction = 0.005f;
    settings->mSupportingVolume = Plane(Vec3::sAxisY(), -cCharacterRadiusStanding); // Accept contacts that touch the lower sphere of the capsule
    settings->mMass = Prm.PlayerMass;
    Character* character;

    FieldPlayerMLP *playerMLP_Red = new FieldPlayerMLP();
    //playerMLP_Red->Load("Models/Match_FiveVsFive_7LayersNN/model6_Epoch558001");
    //playerMLP_Red->Load("Models/latest_model");
    playerMLP_Red->meter = PitchManager::meter;

    FieldPlayerMLP* playerMLP_Blue = playerMLP_Red;// new FieldPlayerMLP();
    //playerMLP_Blue->Load("Models/Match_FiveVsFive_2LayersNN/model6_Epoch2231001");
    playerMLP_Blue->meter = PitchManager::meter;

  if (Color() == blue)
  {
    //goalkeeper
    character = new Character(settings, Vec3(6, player_elevation,5), Quat::sIdentity(), 0, &m_pPitch->m_PhysicsManager->GetPhysicsSystem());
    character->AddToPhysicsSystem(EActivation::Activate);
    m_Players.push_back(new GoalKeeper(this,
                               1,
                               TendGoal::Instance(),
                               m_pPitch->m_PhysicsManager->GetBodyInterface(), character->GetBodyID(),
                               Prm.PlayerMaxForce,
                               Prm.PlayerMaxSpeedWithoutBall,
                               Prm.PlayerMaxTurnRate,
                               playerMLP_Blue));
 
    //create the players
    character = new Character(settings, Vec3(8, player_elevation,5), Quat::sIdentity(), 0, &m_pPitch->m_PhysicsManager->GetPhysicsSystem());
    character->AddToPhysicsSystem(EActivation::Activate);
    m_Players.push_back(new FieldPlayer(this,
                               6,
                               Wait::Instance(),
                               m_pPitch->m_PhysicsManager->GetBodyInterface(), character->GetBodyID(),
                               Prm.PlayerMaxForce,
                               Prm.PlayerMaxSpeedWithoutBall,
                               Prm.PlayerMaxTurnRate,
                               PlayerBase::attacker,
                               playerMLP_Blue));



    character = new Character(settings, Vec3(10, player_elevation,5), Quat::sIdentity(), 0, &m_pPitch->m_PhysicsManager->GetPhysicsSystem());
    character->AddToPhysicsSystem(EActivation::Activate);
        m_Players.push_back(new FieldPlayer(this,
                               8,
                               Wait::Instance(),
                               m_pPitch->m_PhysicsManager->GetBodyInterface(), character->GetBodyID(),
                               Prm.PlayerMaxForce,
                               Prm.PlayerMaxSpeedWithoutBall,
                               Prm.PlayerMaxTurnRate,
                               PlayerBase::attacker,
                               NULL));


 

        
    character = new Character(settings, Vec3(12, player_elevation,5), Quat::sIdentity(), 0, &m_pPitch->m_PhysicsManager->GetPhysicsSystem());
    character->AddToPhysicsSystem(EActivation::Activate);
        m_Players.push_back(new FieldPlayer(this,
                               3,
                               Wait::Instance(),
                               m_pPitch->m_PhysicsManager->GetBodyInterface(), character->GetBodyID(),
                               Prm.PlayerMaxForce,
                               Prm.PlayerMaxSpeedWithoutBall,
                               Prm.PlayerMaxTurnRate,
                               PlayerBase::defender,
                               NULL));


    character = new Character(settings, Vec3(14, player_elevation,5), Quat::sIdentity(), 0, &m_pPitch->m_PhysicsManager->GetPhysicsSystem());
    character->AddToPhysicsSystem(EActivation::Activate);
        m_Players.push_back(new FieldPlayer(this,
                               5,
                               Wait::Instance(),
                               m_pPitch->m_PhysicsManager->GetBodyInterface(), character->GetBodyID(),
                               Prm.PlayerMaxForce,
                               Prm.PlayerMaxSpeedWithoutBall,
                               Prm.PlayerMaxTurnRate,
                               PlayerBase::defender,
                               NULL));

  }

  else
  {
     //goalkeeper
    character = new Character(settings, Vec3(20, player_elevation,5), Quat::sIdentity(), 0, &m_pPitch->m_PhysicsManager->GetPhysicsSystem());
    character->AddToPhysicsSystem(EActivation::Activate); 
    m_Players.push_back(new GoalKeeper(this,
                               16,
                               TendGoal::Instance(),
                               m_pPitch->m_PhysicsManager->GetBodyInterface(), character->GetBodyID(),
                               Prm.PlayerMaxForce,
                               Prm.PlayerMaxSpeedWithoutBall,
                               Prm.PlayerMaxTurnRate,
                               NULL));


    //create the players
    character = new Character(settings, Vec3(22, player_elevation,5), Quat::sIdentity(), 0, &m_pPitch->m_PhysicsManager->GetPhysicsSystem());
    character->AddToPhysicsSystem(EActivation::Activate);
    m_Players.push_back(new FieldPlayer(this,
                               9,
                               Wait::Instance(),
                               m_pPitch->m_PhysicsManager->GetBodyInterface(), character->GetBodyID(),
                               Prm.PlayerMaxForce,
                               Prm.PlayerMaxSpeedWithoutBall,
                               Prm.PlayerMaxTurnRate,
                               PlayerBase::attacker,
                               NULL));

    character = new Character(settings, Vec3(24, player_elevation,5), Quat::sIdentity(), 0, &m_pPitch->m_PhysicsManager->GetPhysicsSystem());
    character->AddToPhysicsSystem(EActivation::Activate);
    m_Players.push_back(new FieldPlayer(this,
                               11,
                               Wait::Instance(),
                               m_pPitch->m_PhysicsManager->GetBodyInterface(), character->GetBodyID(),
                               Prm.PlayerMaxForce,
                               Prm.PlayerMaxSpeedWithoutBall,
                               Prm.PlayerMaxTurnRate,
                               PlayerBase::attacker,
                               NULL));



    character = new Character(settings, Vec3(26, player_elevation,5), Quat::sIdentity(), 0, &m_pPitch->m_PhysicsManager->GetPhysicsSystem());
    character->AddToPhysicsSystem(EActivation::Activate);
    m_Players.push_back(new FieldPlayer(this,
                               12,
                               Wait::Instance(),
                               m_pPitch->m_PhysicsManager->GetBodyInterface(), character->GetBodyID(),
                               Prm.PlayerMaxForce,
                               Prm.PlayerMaxSpeedWithoutBall,
                               Prm.PlayerMaxTurnRate,
                               PlayerBase::defender,
                               NULL));


    character = new Character(settings, Vec3(28, player_elevation,5), Quat::sIdentity(), 0, &m_pPitch->m_PhysicsManager->GetPhysicsSystem());
    character->AddToPhysicsSystem(EActivation::Activate);
    m_Players.push_back(new FieldPlayer(this,
                               14,
                               Wait::Instance(),
                               m_pPitch->m_PhysicsManager->GetBodyInterface(), character->GetBodyID(),
                               Prm.PlayerMaxForce,
                               Prm.PlayerMaxSpeedWithoutBall,
                               Prm.PlayerMaxTurnRate,
                               PlayerBase::defender,
                               NULL));
                      
  }
  playerMLP_Red->Load("Models/latest_model");
  //playerMLP->Load("Models/AbsoluteObservations/latest_model");
  //playerMLP->Load("Models/RelativeObservations/latest_model");
  playerMLP_Red->setTrainingOn(false);
  //SetAIType(PlayerBase::nn);

  //register the players with the entity manager
  std::vector<PlayerBase*>::iterator it = m_Players.begin();

  for (it; it != m_Players.end(); ++it)
  {
    EntityMgr->RegisterEntity(*it);
  }
}


PlayerBase* SoccerTeam::GetPlayerFromID(int id)const
{
  std::vector<PlayerBase*>::const_iterator it = m_Players.begin();

  for (it; it != m_Players.end(); ++it)
  {
    if ((*it)->ID() == id) return *it;
  }

  return NULL;
}


void SoccerTeam::SetPlayerHomeRegion(int plyr, int region)const
{
  assert ( (plyr>=0) && (plyr<m_Players.size()) );

  m_Players[plyr]->SetHomeRegion(region);
}


//---------------------- UpdateTargetsOfWaitingPlayers ------------------------
//
//  
void SoccerTeam::UpdateTargetsOfWaitingPlayers()const
{
  std::vector<PlayerBase*>::const_iterator it = m_Players.begin();

  for (it; it != m_Players.end(); ++it)
  {  
    if ( (*it)->Role() != PlayerBase::goal_keeper )
    {
      //cast to a field player
      FieldPlayer* plyr = static_cast<FieldPlayer*>(*it);
      
      if ( plyr->GetFSM()->isInState(*Wait::Instance()) ||
           plyr->GetFSM()->isInState(*ReturnToHomeRegion::Instance()) )
      {
        plyr->Steering()->SetTarget(plyr->HomeRegion()->Center());
      }
    }
  }
}


//--------------------------- AllPlayersAtHome --------------------------------
//
//  returns false if any of the team are not located within their home region
//-----------------------------------------------------------------------------
bool SoccerTeam::AllPlayersAtHome()const
{
  std::vector<PlayerBase*>::const_iterator it = m_Players.begin();

  for (it; it != m_Players.end(); ++it)
  {
    if ((*it)->InHomeRegion() == false)
    {
      return false;
    }
  }

  return true;
}

//------------------------- RequestPass ---------------------------------------
//
//  this tests to see if a pass is possible between the requester and
//  the controlling player. If it is possible a message is sent to the
//  controlling player to pass the ball asap.
//-----------------------------------------------------------------------------
void SoccerTeam::RequestPass(FieldPlayer* requester)const
{
  //maybe put a restriction here
  if (RandFloat() > 0.1) return;
  
  if (isPassSafeFromAllOpponents(Vector2D(ControllingPlayer()->Pos().GetX(), ControllingPlayer()->Pos().GetZ()),
                                 Vector2D(requester->Pos().GetX(), requester->Pos().GetZ()),
                                 requester,
                                 Prm.MaxPassingForce))
  {

    //tell the player to make the pass
    //let the receiver know a pass is coming 
    Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
                          requester->ID(),
                          ControllingPlayer()->ID(),
                          Msg_PassToMe,
                          requester); 

  }
}


//----------------------------- isOpponentWithinRadius ------------------------
//
//  returns true if an opposing player is within the radius of the position
//  given as a parameter
//-----------------------------------------------------------------------------
bool SoccerTeam::isOpponentWithinRadius(Vec3 pos, double rad)
{
  std::vector<PlayerBase*>::const_iterator end = Opponents()->Members().end();
  std::vector<PlayerBase*>::const_iterator it;

  for (it=Opponents()->Members().begin(); it !=end; ++it)
  {
    if ((pos- (*it)->Pos()).LengthSq() < rad*rad)
    {
      return true;
    }
  }

  return false;
}
