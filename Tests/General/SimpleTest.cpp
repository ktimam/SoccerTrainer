// Jolt Physics Library (https://github.com/jrouwe/JoltPhysics)
// SPDX-FileCopyrightText: 2021 Jorrit Rouwe
// SPDX-License-Identifier: MIT

#include <TestFramework.h>

#include <Tests/General/SimpleTest.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>
#include <Common/Game/PhysicsManager.h>

JPH_IMPLEMENT_RTTI_VIRTUAL(SimpleTest)
{
	JPH_ADD_BASE_CLASS(SimpleTest, Test)
}

SimpleTest::~SimpleTest()
{
	// Unregister activation listener
	mPhysicsSystem->SetBodyActivationListener(nullptr);
}

void SimpleTest::Initialize()
{
	// Register activation listener
	mPhysicsSystem->SetBodyActivationListener(&mBodyActivationListener);

	// Floor
	CreateFloor();

	RefConst<Shape> box_shape = new BoxShape(Vec3(0.5f, 1.0f, 2.0f));

	// Dynamic body 1
	Body &body1 = *mBodyInterface->CreateBody(BodyCreationSettings(box_shape, RVec3(0, 10, 0), Quat::sIdentity(), EMotionType::Dynamic, Layers::MOVING));
	mBodyInterface->AddBody(body1.GetID(), EActivation::Activate);

	// Dynamic body 2
	Body &body2 = *mBodyInterface->CreateBody(BodyCreationSettings(box_shape, RVec3(5, 10, 0), Quat::sRotation(Vec3::sAxisX(), 0.25f * JPH_PI), EMotionType::Dynamic, Layers::MOVING));
	mBodyInterface->AddBody(body2.GetID(), EActivation::Activate);

	// Dynamic body 3
	Body &body3 = *mBodyInterface->CreateBody(BodyCreationSettings(new SphereShape(2.0f), RVec3(10, 10, 0), Quat::sRotation(Vec3::sAxisX(), 0.25f * JPH_PI), EMotionType::Dynamic, Layers::MOVING));
	mBodyInterface->AddBody(body3.GetID(), EActivation::Activate);


	BodyCreationSettings settings;
	settings.SetShape(new SphereShape(1.0f));
	settings.mPosition = RVec3(20, 20, 0);// RVec3(0, 0.5f, 0);
	settings.mMotionType = EMotionType::Dynamic;
	//settings.mMotionQuality = EMotionQuality::LinearCast;
	//settings.mLinearVelocity = Vec3(-24, 0, -12);
	settings.mFriction = 0.0f;
	settings.mRestitution = 0.6f;
	settings.mObjectLayer = Layers::MOVING;
	Body*  mBody = mBodyInterface->CreateBody(settings);
	mBodyInterface->AddBody(mBody->GetID(), EActivation::Activate);
}
