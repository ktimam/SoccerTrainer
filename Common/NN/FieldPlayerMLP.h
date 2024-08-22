#pragma once


#include "flashlight/fl/tensor/Init.h"
#include "flashlight/fl/dataset/datasets.h"
#include "flashlight/fl/meter/meters.h"
#include "flashlight/fl/nn/nn.h"
#include "flashlight/fl/optim/optim.h"
#include "flashlight/fl/tensor/Random.h"
#include "flashlight/fl/tensor/TensorBase.h"

#include <SimSoccer/constants.h>
#include <Common/Game/PhysicsManager.h>

using namespace fl;

//const int nSamples = 500;// 10000;
const int nInputCount = 32;
const int nOutputCount = 8;

const float learningRate = 0.001;// 0.0001;
const float momentum = 0;// 0.9;

constexpr static float FEAT_MIN = -1;
constexpr static float FEAT_MAX = 1;

static float normalize(float val, float min_val, float max_val) {
	if (val < min_val || val > max_val) {
		std::cout << "Feature Violated Feature Bounds: " << val
			<< " Expected min/max: [" << min_val << ", "
			<< max_val << "]" << std::endl;
		val = std::min(std::max(val, min_val), max_val);
	}
	return ((val - min_val) / (max_val - min_val))
		* (FEAT_MAX - FEAT_MIN) + FEAT_MIN;
}

static float normalizedXPos(float absolute_x_pos, bool team_in_control) {
	float tolerance_x = .1 * PitchLength;
	//if (team_in_control) 
	{
		return normalize(absolute_x_pos, -tolerance_x, PitchLength + tolerance_x);
	}
	/*else {
		return normalize(absolute_x_pos, -PitchLength - tolerance_x, tolerance_x);
	}*/
}

static float normalizedYPos(float absolute_y_pos) {
	float tolerance_y = .1 * PitchWidth;
	return normalize(absolute_y_pos, -PitchWidth - tolerance_y,
		PitchWidth + tolerance_y);
}

struct Observation {

	Vec3 BallPosition;
	Vec3 BallVelocity;
	bool BallKickable;
	Vec3 AgentPosition;
	Vec3 AgentVelocity;
	Vec3 AgentHeading;
	Vec3 AgentTarget;
	bool ClosestToBall;
	bool TeamInControl;

	vector<Vec3> TeamPositions;
	vector<Vec3> OpponentPositions;

	vector<float> toVector() {
		vector<float> observation_vec;

		observation_vec.push_back(normalizedXPos(BallPosition.GetX(), TeamInControl));
		//observation_vec.push_back(BallPosition.GetY());
		observation_vec.push_back(normalizedYPos(BallPosition.GetZ()));

		observation_vec.push_back(BallVelocity.GetX());
		//observation_vec.push_back(BallVelocity.GetY());
		observation_vec.push_back(BallVelocity.GetZ());

		observation_vec.push_back(BallKickable ? 1 : -1);

		observation_vec.push_back(normalizedXPos(AgentPosition.GetX(), TeamInControl));
		observation_vec.push_back(normalizedYPos(AgentPosition.GetZ()));

		observation_vec.push_back(AgentVelocity.GetX());
		observation_vec.push_back(AgentVelocity.GetZ());

		observation_vec.push_back(AgentHeading.GetX());
		observation_vec.push_back(AgentHeading.GetZ());

		observation_vec.push_back(normalizedXPos(AgentTarget.GetX(), TeamInControl));
		observation_vec.push_back(normalizedYPos(AgentTarget.GetZ()));

		observation_vec.push_back(ClosestToBall ? 1 : -1);

		std::vector<Vec3>::const_iterator vec3_itr = TeamPositions.begin();
		for (vec3_itr; vec3_itr != TeamPositions.end(); ++vec3_itr)
		{
			observation_vec.push_back(normalizedXPos(vec3_itr->GetX(), TeamInControl));
			observation_vec.push_back(normalizedYPos(vec3_itr->GetZ()));
		}
		vec3_itr = OpponentPositions.begin();
		for (vec3_itr; vec3_itr != OpponentPositions.end(); ++vec3_itr)
		{
			observation_vec.push_back(normalizedXPos(vec3_itr->GetX(), TeamInControl));
			observation_vec.push_back(normalizedYPos(vec3_itr->GetZ()));
		}

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

		action_vec.push_back(KickBall ? 1 : -1);
		action_vec.push_back(KickForce);
		action_vec.push_back(KickDirection.GetX());
		action_vec.push_back(KickDirection.GetY());
		action_vec.push_back(KickDirection.GetZ());

		action_vec.push_back(TrackBall ? 1 : -1);

		return action_vec;
	}

	static inline Action toAction(Tensor actionTensor) {
		vector<float> tensorVec = actionTensor.toHostVector<float>();
		Action action;

		action.ForwardForce = tensorVec[0];
		action.TurningForce = tensorVec[1];

		action.KickBall      = tensorVec[2] > 0.1;
		action.KickForce     = tensorVec[3];
		action.KickDirection = Vec3(tensorVec[4], tensorVec[5], tensorVec[6]);

		action.TrackBall = tensorVec[7] > 0.1;

		return action;
	}
};

class FieldPlayerMLP
{
private:
	Sequential model;
	MeanSquaredError loss;
	FirstOrderOptimizer* optimizer;

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

