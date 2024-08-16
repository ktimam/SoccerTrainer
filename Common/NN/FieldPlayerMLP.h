#pragma once


#include "flashlight/fl/tensor/Init.h"
#include "flashlight/fl/dataset/datasets.h"
#include "flashlight/fl/meter/meters.h"
#include "flashlight/fl/nn/nn.h"
//#include "flashlight/fl/optim/optim.h"
#include "flashlight/fl/optim/SGDOptimizer.h"
#include "flashlight/fl/tensor/Random.h"
#include "flashlight/fl/tensor/TensorBase.h"

#include <Common/Game/PhysicsManager.h>

using namespace fl;

struct Observation {

	Vec3 BallPosition;
	Vec3 AgentPosition;

	vector<Vec3> TeamPositions;
	vector<Vec3> OpponentPositions;

	vector<float> toVector() {
		vector<float> observation_vec;

		observation_vec.push_back(AgentPosition.GetX());
		observation_vec.push_back(AgentPosition.GetY());
		observation_vec.push_back(AgentPosition.GetZ());


		std::vector<Vec3>::const_iterator vec3_itr = TeamPositions.begin();
		for (vec3_itr; vec3_itr != TeamPositions.end(); ++vec3_itr)
		{
			observation_vec.push_back(vec3_itr->GetX());
			observation_vec.push_back(vec3_itr->GetY());
			observation_vec.push_back(vec3_itr->GetZ());
		}
		vec3_itr = OpponentPositions.begin();
		for (vec3_itr; vec3_itr != OpponentPositions.end(); ++vec3_itr)
		{
			observation_vec.push_back(vec3_itr->GetX());
			observation_vec.push_back(vec3_itr->GetY());
			observation_vec.push_back(vec3_itr->GetZ());
		}

		observation_vec.push_back(BallPosition.GetX());
		observation_vec.push_back(BallPosition.GetY());
		observation_vec.push_back(BallPosition.GetZ());

		return observation_vec;
	}
};

struct Action {
	double ForwardForce;
	double TurningForce;

	bool KickBall;
	Vec3 KickDirection;
	double KickForce;

	bool TrackBall;

	vector<float> toVector() {
		vector<float> action_vec;
		action_vec.push_back(ForwardForce);
		action_vec.push_back(TurningForce);

		action_vec.push_back(KickBall ? 1 : 0);
		action_vec.push_back(KickForce);
		action_vec.push_back(KickDirection.GetX());
		action_vec.push_back(KickDirection.GetY());
		action_vec.push_back(KickDirection.GetZ());

		action_vec.push_back(TrackBall ? 1 : 0);

		return action_vec;
	}

	static inline Action toAction(Tensor actionTensor) {
		vector<float> tensorVec = actionTensor.toHostVector<float>();
		Action action;

		action.ForwardForce = tensorVec[0];
		action.TurningForce = tensorVec[1];

		action.KickBall      = tensorVec[2];
		action.KickForce     = tensorVec[3];
		action.KickDirection = Vec3(tensorVec[4], tensorVec[5], tensorVec[6]);

		action.TrackBall = tensorVec[7];

		return action;
	}
};

class FieldPlayerMLP
{
private:
	//const int nSamples = 500;// 10000;
	const int nInputCount  = 10;
	const int nOutputCount = 8;

	const float learningRate = 0.0001;
	const float momentum = 0.9;

	Sequential model;
	MeanSquaredError loss;
	SGDOptimizer *sgd;

public:
	FieldPlayerMLP();

	// Meter definition
	static AverageValueMeter *meter;

	/// <summary>
	/// Process the observation, return action and train model
	/// </summary>
	/// <param name="observation">World Observation from Agent Perspective</param>
	/// <param name="backpropagate">Handle backpropagation</param>
	/// <param name="target">The correct target to train agent against. backpropagate needs to be set to true.</param>
	/// <returns>Action that the agent should take</returns>
	Action Process(Observation observation, bool backpropagate, Action target);
};

