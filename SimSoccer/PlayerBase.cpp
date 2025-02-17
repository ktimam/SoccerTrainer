#include "PlayerBase.h"
#include "SteeringBehaviors.h"
#include "../Common/2D/Transformations.h"
#include "../Common/2D/Geometry.h"
#include "../Common/misc/Cgdi.h"
#include "../Common/2D/C2DMatrix.h"
#include "../Common/Game/Region.h"
#include "ParamLoader.h"
#include "../Common/Messaging/MessageDispatcher.h"
#include "SoccerMessages.h"
#include "SoccerTeam.h"
#include "ParamLoader.h"
#include "FieldGoal.h"
#include "SoccerBall.h"
#include "SoccerPitch.h"
#include "../Common/Debug/DebugConsole.h"


using std::vector;


//----------------------------- dtor -------------------------------------
//------------------------------------------------------------------------
PlayerBase::~PlayerBase()
{
  delete m_pSteering;
  if (m_Brain != NULL) {
    delete m_Brain;
    m_Brain = NULL;
  }
}

//----------------------------- ctor -------------------------------------
//------------------------------------------------------------------------
PlayerBase::PlayerBase(SoccerTeam* home_team,
                       int   home_region,
                       BodyInterface& bodyInterface, BodyID body_id,
                       double    max_force,
                       double    max_speed,
                       double    max_turn_rate,
                       player_role role,
                       FieldPlayerMLP* brain):

    MovingEntity(bodyInterface, body_id, 
                 max_speed,
                 max_turn_rate,
                 max_force),
   m_pTeam(home_team),
   m_dDistSqToBall(MaxFloat),
   m_iHomeRegion(home_region),
   m_iDefaultRegion(home_region),
   m_PlayerRole(role),
   m_Brain(brain)
{
  //set up the steering behavior class
  m_pSteering = new SteeringBehaviors(this,
                                      m_pTeam->Pitch(),
                                      Ball());  
  
  //a player's start target is its start position (because it's just waiting)
  m_pSteering->SetTarget(home_team->Pitch()->GetRegionFromIndex(home_region)->Center());
}




//----------------------------- TrackBall --------------------------------
//
//  sets the player's heading to point at the ball
//------------------------------------------------------------------------
void PlayerBase::TrackBall()
{
  RotateHeadingToFacePosition(Ball()->Pos());  
}


//------------------------------------------------------------------------
//
//binary predicates for std::sort (see CanPassForward/Backward)
//------------------------------------------------------------------------
bool  SortByDistanceToOpponentsGoal(const PlayerBase*const p1,
                                    const PlayerBase*const p2)
{
  return (p1->DistToOppGoal() < p2->DistToOppGoal());
}

bool  SortByReversedDistanceToOpponentsGoal(const PlayerBase*const p1,
                                            const PlayerBase*const p2)
{
  return (p1->DistToOppGoal() > p2->DistToOppGoal());
}


//------------------------- WithinFieldOfView ---------------------------
//
//  returns true if subject is within field of view of this player
//-----------------------------------------------------------------------
bool PlayerBase::PositionInFrontOfPlayer(Vec3 position)const
{
    Vec3 ToSubject = position - Pos();

  if (ToSubject.Dot(Heading()) > 0) 
    
    return true;

  else

    return false;
}

//------------------------- IsThreatened ---------------------------------
//
//  returns true if there is an opponent within this player's 
//  comfort zone
//------------------------------------------------------------------------
bool PlayerBase::isThreatened()const
{
  //check against all opponents to make sure non are within this
  //player's comfort zone
  std::vector<PlayerBase*>::const_iterator curOpp;  
  curOpp = Team()->Opponents()->Members().begin();
 
  for (curOpp; curOpp != Team()->Opponents()->Members().end(); ++curOpp)
  {
    //calculate distance to the player. if dist is less than our
    //comfort zone, and the opponent is infront of the player, return true
    if (PositionInFrontOfPlayer((*curOpp)->Pos()) &&
       ((Pos() - (*curOpp)->Pos()).LengthSq() < Prm.PlayerComfortZoneSq))
    {        
      return true;
    }
   
  }// next opp

  return false;
}

//----------------------------- FindSupport -----------------------------------
//
//  determines the player who is closest to the SupportSpot and messages him
//  to tell him to change state to SupportAttacker
//-----------------------------------------------------------------------------
void PlayerBase::FindSupport()const
{    
  //if there is no support we need to find a suitable player.
  if (Team()->SupportingPlayer() == NULL)
  {
    PlayerBase* BestSupportPly = Team()->DetermineBestSupportingAttacker();

    Team()->SetSupportingPlayer(BestSupportPly);

    if (BestSupportPly == NULL) {
        return;
    }
    Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
                            ID(),
                            Team()->SupportingPlayer()->ID(),
                            Msg_SupportAttacker,
                            NULL);
  }
    
  PlayerBase* BestSupportPly = Team()->DetermineBestSupportingAttacker();
    
  //if the best player available to support the attacker changes, update
  //the pointers and send messages to the relevant players to update their
  //states
  if (BestSupportPly && (BestSupportPly != Team()->SupportingPlayer()))
  {
    
    if (Team()->SupportingPlayer())
    {
      Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
                              ID(),
                              Team()->SupportingPlayer()->ID(),
                              Msg_GoHome,
                              NULL);
    }
    
    
    
    Team()->SetSupportingPlayer(BestSupportPly);

    Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
                            ID(),
                            Team()->SupportingPlayer()->ID(),
                            Msg_SupportAttacker,
                            NULL);
  }
}


  //calculate distance to opponent's goal. Used frequently by the passing//methods
double PlayerBase::DistToOppGoal()const
{
  return fabs(Pos().GetX() - Team()->OpponentsGoal()->Center().GetX());
}

double PlayerBase::DistToHomeGoal()const
{
  return fabs(Pos().GetX() - Team()->HomeGoal()->Center().GetX());
}

bool PlayerBase::isControllingPlayer()const
{return Team()->ControllingPlayer()==this;}

bool PlayerBase::BallWithinKeeperRange()const
{
  return ((Pos() - Ball()->Pos()).LengthSq() < Prm.KeeperInBallRangeSq);
}

bool PlayerBase::BallWithinReceivingRange()const
{
  return ((Pos() - Ball()->Pos()).LengthSq() < Prm.BallWithinReceivingRangeSq);
}

bool PlayerBase::BallWithinKickingRange()const
{
    if (!PositionInFrontOfPlayer(Ball()->Pos())) return false;
    double ball_distance_sq = (Ball()->Pos() - Pos()).LengthSq();
  return (ball_distance_sq < Prm.PlayerKickingDistanceSq);
}


bool PlayerBase::InHomeRegion()const
{
  if (m_PlayerRole == goal_keeper)
  {
    return Pitch()->GetRegionFromIndex(m_iHomeRegion)->Inside(Pos(), Region::normal);
  }
  else
  {
    return Pitch()->GetRegionFromIndex(m_iHomeRegion)->Inside(Pos(), Region::halfsize);
  }
}

bool PlayerBase::AtTarget()const
{
  Vec3 distance = Pos() - Steering()->Target();
  return (Vec3(distance.GetX(), 0, distance.GetZ()).LengthSq() < Prm.PlayerInTargetRangeSq);
}

bool PlayerBase::isClosestTeamMemberToBall()const
{
  return Team()->PlayerClosestToBall() == this;
}

bool PlayerBase::isClosestPlayerOnPitchToBall()const
{
  return isClosestTeamMemberToBall() && 
         (DistSqToBall() < Team()->Opponents()->ClosestDistToBallSq());
}

bool PlayerBase::InHotRegion()const
{
  return fabs(Pos().GetZ() - Team()->OpponentsGoal()->Center().GetZ()) <
         Pitch()->PlayingArea()->Length()/3.0;
}

bool PlayerBase::isAheadOfAttacker()const
{
  return fabs(Pos().GetX() - Team()->OpponentsGoal()->Center().GetX()) <
         fabs(Team()->ControllingPlayer()->Pos().GetX() - Team()->OpponentsGoal()->Center().GetX());
}

SoccerBall* const PlayerBase::Ball()const
{
  return Team()->Pitch()->Ball();
}

SoccerPitch* const PlayerBase::Pitch()const
{
  return Team()->Pitch();
}

const Region* const PlayerBase::HomeRegion()const
{
  return Pitch()->GetRegionFromIndex(m_iHomeRegion);
}

Observation PlayerBase::GetObservation()
{
    Observation observation;
    observation.BallPosition  = Team()->Pitch()->Ball()->Pos();
    observation.BallVelocity = Team()->Pitch()->Ball()->Velocity();
    observation.BallKickable = BallWithinKickingRange();
    observation.AgentPosition = Pos();
    observation.AgentHeading = Heading();
    observation.AgentVelocity = Velocity();
    observation.AgentTarget   = Steering()->Target();
    observation.ClosestToBall = isClosestPlayerOnPitchToBall() && Team()->Pitch()->GameOn();
    observation.TeamInControl = Team()->InControl();
    observation.OpponentGoalCenter = Team()->OpponentsGoal()->Center();

    std::vector<PlayerBase*>::const_iterator plrs_itr = Team()->Members().begin();
    int count = 0;
    for (plrs_itr; plrs_itr != Team()->Members().end(); ++plrs_itr, count++)
    {
        if (*plrs_itr != this) {
            observation.TeamPositions[count] = (*plrs_itr)->Pos();
        }
    }
    plrs_itr = Team()->Opponents()->Members().begin();
    count = 0;
    for (plrs_itr; plrs_itr != Team()->Opponents()->Members().end(); ++plrs_itr, count++)
    {
        observation.OpponentPositions[count] = (*plrs_itr)->Pos();
    }

    return observation;
}


