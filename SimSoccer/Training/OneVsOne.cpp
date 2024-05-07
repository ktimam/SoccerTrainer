#include "OneVsOne.h"

#include "../SoccerPitch.h"
#include "../GoalKeeper.h"
#include "../FieldPlayer.h"
#include "../../Common/Game/PhysicsManager.h"
#include "../ParamLoader.h"
#include "../GoalKeeperStates.h"
#include "../../Common/Game/EntityManager.h"

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
    float player_elevation = 2;
    // Character size
    float	cCharacterHeightStanding = 13.5f;
    float	cCharacterRadiusStanding = 3.0f;

    if (Color() == blue)
    {
        // Create 'player' character
        Ref<CharacterSettings> settings = new CharacterSettings();
        settings->mMaxSlopeAngle = DegreesToRadians(45.0f);
        settings->mLayer = Layers::MOVING;
        settings->mShape = RotatedTranslatedShapeSettings(Vec3(0, 0.5f * cCharacterHeightStanding + cCharacterRadiusStanding, 0), Quat::sIdentity(), new CapsuleShape(0.5f * cCharacterHeightStanding, cCharacterRadiusStanding)).Create().Get();
        settings->mFriction = 0.5f;
        settings->mSupportingVolume = Plane(Vec3::sAxisY(), -cCharacterRadiusStanding); // Accept contacts that touch the lower sphere of the capsule
        settings->mMass = Prm.PlayerMass;
        Character* character;

        //create the players
        character = new Character(settings, Vec3(120, player_elevation, 100), Quat::sIdentity(), 0, &m_pPitch->m_PhysicsManager->GetPhysicsSystem());
        character->AddToPhysicsSystem(EActivation::Activate);
        m_Players.push_back(new FieldPlayer(this,
            4,
            Wait::Instance(),
            m_pPitch->m_PhysicsManager->GetBodyInterface(), character->GetBodyID(),
            Prm.PlayerMaxForce,
            Prm.PlayerMaxSpeedWithoutBall,
            Prm.PlayerMaxTurnRate,
            PlayerBase::defender));

    }

    else
    {
        // Create 'player' character
        Ref<CharacterSettings> settings = new CharacterSettings();
        settings->mMaxSlopeAngle = DegreesToRadians(45.0f);
        settings->mLayer = Layers::MOVING;
        settings->mShape = RotatedTranslatedShapeSettings(Vec3(0, 0.5f * cCharacterHeightStanding + cCharacterRadiusStanding, 0), Quat::sIdentity(), new CapsuleShape(0.5f * cCharacterHeightStanding, cCharacterRadiusStanding)).Create().Get();
        settings->mFriction = 0.5f;
        settings->mSupportingVolume = Plane(Vec3::sAxisY(), -cCharacterRadiusStanding); // Accept contacts that touch the lower sphere of the capsule
        settings->mMass = Prm.PlayerMass;
        Character* character;

        //create the players
        character = new Character(settings, Vec3(220, player_elevation, 100), Quat::sIdentity(), 0, &m_pPitch->m_PhysicsManager->GetPhysicsSystem());
        character->AddToPhysicsSystem(EActivation::Activate);
        m_Players.push_back(new FieldPlayer(this,
            10,
            Wait::Instance(),
            m_pPitch->m_PhysicsManager->GetBodyInterface(), character->GetBodyID(),
            Prm.PlayerMaxForce,
            Prm.PlayerMaxSpeedWithoutBall,
            Prm.PlayerMaxTurnRate,
            PlayerBase::attacker));

    }

    //register the players with the entity manager
    std::vector<PlayerBase*>::iterator it = m_Players.begin();

    for (it; it != m_Players.end(); ++it)
    {
        EntityMgr->RegisterEntity(*it);
    }
}