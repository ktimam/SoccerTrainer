#include "OneVsOne.h"

#include "../SoccerTeam.h"
#include "../SoccerPitch.h"
#include "../GoalKeeper.h"
#include "../FieldPlayer.h"
#include <Common/Game/PhysicsManager.h>
#include "../ParamLoader.h"
#include "../GoalKeeperStates.h"
#include "../../Common/Game/EntityManager.h"
#include "../PitchManager.h"

#include <Jolt/Physics/Character/Character.h>
#include <Jolt/Physics/Collision/Shape/CapsuleShape.h>
#include <Jolt/Physics/Collision/Shape/CylinderShape.h>
#include <Jolt/Physics/Collision/Shape/RotatedTranslatedShape.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Collision/Shape/MeshShape.h>


//----------------------------- ctor -------------------------------------
//
//------------------------------------------------------------------------
OneVsOne::OneVsOne(FieldGoal* home_goal,
    FieldGoal* opponents_goal,
    SoccerPitch* pitch,
    team_color   color) : SoccerTeam(home_goal, opponents_goal, pitch, color)
{
    SoccerTeam::BlueAttackingRegions = { 4 };
    SoccerTeam::RedAttackingRegions = { 10 };
    SoccerTeam::BlueDefendingRegions = { 4 };
    SoccerTeam::RedDefendingRegions = { 10 };
}

//----------------------- dtor -------------------------------------------
//
//------------------------------------------------------------------------
OneVsOne::~OneVsOne()
{
}

//------------------------- CreatePlayers --------------------------------
//
//  creates the players
//------------------------------------------------------------------------
void OneVsOne::CreatePlayers()
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

    FieldPlayerMLP* playerMLP = new FieldPlayerMLP();
    playerMLP->meter = PitchManager::meter;

    if (Color() == blue)
    {
        //playerMLP_Blue->Load("Models/Match_FiveVsFive_2LayersNN/model6_Epoch2231001");
        //playerMLP->Load("Models/AbsoluteObservations/latest_model");
        
        //create the players
        character = new Character(settings, 
            //Vec3(12, player_elevation, 5), 
            Pitch()->GetRegionFromIndex(4)->Center(), 
            Quat::sIdentity(), 0, &m_pPitch->m_PhysicsManager->GetPhysicsSystem());
        character->AddToPhysicsSystem(EActivation::Activate);
        m_Players.push_back(new FieldPlayer(this,
            4,
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
        //playerMLP_Red->Load("Models/Match_FiveVsFive_7LayersNN/model6_Epoch558001");
        //playerMLP->Load("Models/RelativeObservations/latest_model");
        
        //create the players
        character = new Character(settings, 
            //Vec3(22, player_elevation, 5), 
            Pitch()->GetRegionFromIndex(10)->Center(),
            Quat::sIdentity(), 0, &m_pPitch->m_PhysicsManager->GetPhysicsSystem());
        character->AddToPhysicsSystem(EActivation::Activate);
        m_Players.push_back(new FieldPlayer(this,
            10,
            Wait::Instance(),
            m_pPitch->m_PhysicsManager->GetBodyInterface(), character->GetBodyID(),
            Prm.PlayerMaxForce,
            Prm.PlayerMaxSpeedWithoutBall,
            Prm.PlayerMaxTurnRate,
            PlayerBase::attacker,
            playerMLP));

    }
    playerMLP->Load("Models/latest_model");
    //playerMLP->Load("Models/AbsoluteObservations/latest_model");
    //playerMLP->Load("Models/RelativeObservations/latest_model");
    playerMLP->setTrainingOn(false);
    SetAIType(PlayerBase::nn);

    //register the players with the entity manager
    std::vector<PlayerBase*>::iterator it = m_Players.begin();

    for (it; it != m_Players.end(); ++it)
    {
        EntityMgr->RegisterEntity(*it);
    }
}