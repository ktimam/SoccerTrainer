#pragma once

//#define ABSOLUTE_OBSERVATIONS

#include "flashlight/fl/tensor/Init.h"
#include "flashlight/fl/dataset/datasets.h"
#include "flashlight/fl/meter/meters.h"
#include "flashlight/fl/nn/nn.h"
#include "flashlight/fl/optim/optim.h"
#include "flashlight/fl/tensor/Random.h"
#include "flashlight/fl/tensor/TensorBase.h"

#include <SimSoccer/constants.h>
#include <SimSoccer/ParamLoader.h>
#include <Common/Game/PhysicsManager.h>
#include <Common/misc/utils.h>

using namespace fl;

const int nInputCount =  3;// 19;// 43;//32
const int nOutputCount = 2;// 8;

const float learningRate = 0.0000001;// 0.0001;
const float momentum = 0.9;

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

static float unnormalize(float val, float min_val, float max_val) {
	if (val < FEAT_MIN || val > FEAT_MAX) {
		/*std::cout << "Unnormalized value Violated Feature Bounds: " << val
			<< " Expected min/max: [" << FEAT_MIN << ", "
			<< FEAT_MAX << "]" << std::endl;*/
		float ft_max = FEAT_MAX; // Linker error on OSX otherwise...?
		float ft_min = FEAT_MIN;
		val = std::min(std::max(val, ft_min), ft_max);
	}
	return ((val - FEAT_MIN) / (FEAT_MAX - FEAT_MIN))
		* (max_val - min_val) + min_val;
}

static float normalizedXPos(float absolute_x_pos, bool team_in_control) {
	float tolerance_x = .2 * PitchLength;
	//if (team_in_control) 
	{
		return normalize(absolute_x_pos, -tolerance_x, PitchLength + tolerance_x);
	}
	/*else {
		return normalize(absolute_x_pos, -PitchLength - tolerance_x, tolerance_x);
	}*/
}

static float normalizedYPos(float absolute_y_pos) {
	float tolerance_y = .2 * PitchWidth;
	return normalize(absolute_y_pos, -PitchWidth - tolerance_y,
		PitchWidth + tolerance_y);
}

struct Observation {
	vector<float> ObservationVector;

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

	//Angle between two vectors
	void addAngleFeature(const Vec3& heading, const Vec3& target, vector<float>& ObservationVector) {
		Vec3 heading_normalized = heading.Normalized();
		double dot = heading_normalized.Dot(target);
		//some compilers lose acurracy so the value is clamped to ensure it
		//remains valid for the acos
		Clamp(dot, -1, 1);
		//determine the angle between the heading vector and the target
		double angle = acos(dot);
		//angle = RadiansToDegrees(angle);
		ObservationVector.push_back(sin(angle));
		ObservationVector.push_back(cos(angle));
	}

	//Angle for heading vector
	void addAngleFeature(const Vec3& heading, vector<float>& ObservationVector) {
		//determine the angle for the heading vector
		double angle = atan2f(heading.GetZ(), heading.GetX());
		//angle = RadiansToDegrees(angle);
		ObservationVector.push_back(sin(angle));
		ObservationVector.push_back(cos(angle));
	}

	//Proximity between two positions
	void addDistanceFeature(const Vec3& position, const Vec3& target_position, float maxDist, vector<float>& ObservationVector) {
		Vec3 agent_vec(position.GetX(), 0, position.GetZ());
		Vec3 target_vec(target_position.GetX(), 0, target_position.GetZ());
		Vec3 proximty_vec = target_vec - agent_vec;
		float proximity = 1.f - std::max(0.f, std::min(1.f, proximty_vec.Length() / maxDist));
		ObservationVector.push_back(normalize(proximity, 0., 1.));
	}

	//Proximity and angle between the Agent and another entity (3 features added)
	void AddAgentObservation(const Vec3& target, vector<float>& ObservationVector) {

		//Proximity from agent
		addDistanceFeature(AgentPosition, target, Prm.MaxFieldDistance, ObservationVector);
		//Angle from agent 
		addAngleFeature(AgentHeading, target, ObservationVector);
	}

#ifdef ABSOLUTE_OBSERVATIONS
	vector<float> toVector() {
		ObservationVector.clear();

		ObservationVector.push_back(normalizedXPos(BallPosition.GetX(), TeamInControl));
		//ObservationVector.push_back(BallPosition.GetY());
		ObservationVector.push_back(normalizedYPos(BallPosition.GetZ()));

		ObservationVector.push_back(BallVelocity.GetX());
		//ObservationVector.push_back(BallVelocity.GetY());
		ObservationVector.push_back(BallVelocity.GetZ());

		ObservationVector.push_back(BallKickable ? 1 : -1);

		ObservationVector.push_back(normalizedXPos(AgentPosition.GetX(), TeamInControl));
		ObservationVector.push_back(normalizedYPos(AgentPosition.GetZ()));

		ObservationVector.push_back(AgentVelocity.GetX());
		ObservationVector.push_back(AgentVelocity.GetZ());

		ObservationVector.push_back(AgentHeading.GetX());
		ObservationVector.push_back(AgentHeading.GetZ());

		ObservationVector.push_back(normalizedXPos(AgentTarget.GetX(), TeamInControl));
		ObservationVector.push_back(normalizedYPos(AgentTarget.GetZ()));

		ObservationVector.push_back(ClosestToBall ? 1 : -1);

		std::vector<Vec3>::const_iterator vec3_itr = TeamPositions.begin();
		for (vec3_itr; vec3_itr != TeamPositions.end(); ++vec3_itr)
		{
			ObservationVector.push_back(normalizedXPos(vec3_itr->GetX(), TeamInControl));
			ObservationVector.push_back(normalizedYPos(vec3_itr->GetZ()));
		}
		vec3_itr = OpponentPositions.begin();
		for (vec3_itr; vec3_itr != OpponentPositions.end(); ++vec3_itr)
		{
			ObservationVector.push_back(normalizedXPos(vec3_itr->GetX(), TeamInControl));
			ObservationVector.push_back(normalizedYPos(vec3_itr->GetZ()));
		}

		return ObservationVector;
	}
#else

	vector<float>& toVector() {
		ObservationVector.clear();

		////Ball Proximity/Angle
		//AddAgentObservation(BallPosition, ObservationVector);
		////Ball Velocity Angle
		//addAngleFeature(BallVelocity, ObservationVector);
		////Ball Velocity Magnitude
		//addDistanceFeature(Vec3(), BallVelocity, Prm.MaxShootingForce, ObservationVector);
		////Can kick ball
		//ObservationVector.push_back(BallKickable ? 1 : -1);

		////Agent Velocity Angle
		//addAngleFeature(AgentVelocity, ObservationVector);
		////Agent Velocity Magnitude
		//addDistanceFeature(Vec3(), AgentVelocity, Prm.PlayerMaxSpeedWithoutBall, ObservationVector);

		////Agent Heading Angle
		//addAngleFeature(AgentHeading, ObservationVector);

		//Agent Target Proximity/Angle
		AddAgentObservation(AgentTarget, ObservationVector);

		////Closest player to ball
		//ObservationVector.push_back(ClosestToBall ? 1 : -1);

		//vector<Vec3>::const_iterator vec3_itr = TeamPositions.begin();
		//for (vec3_itr; vec3_itr != TeamPositions.end(); ++vec3_itr)
		//{
		//	AddAgentObservation(*vec3_itr, ObservationVector);
		//}
		//vec3_itr = OpponentPositions.begin();
		//for (vec3_itr; vec3_itr != OpponentPositions.end(); ++vec3_itr)
		//{
		//	AddAgentObservation(*vec3_itr, ObservationVector);
		//}

		return ObservationVector;
	}
#endif
};

struct Action {
	double ForwardForce = 0;
	double TurningForce = 0;

	bool KickBall = false;
	Vec3 KickDirection;
	double KickForce = 0;

	bool TrackBall = false;

	vector<float> toVector() {
		vector<float> action_vec;
		action_vec.push_back(normalize(ForwardForce,-Prm.PlayerMaxForce,Prm.PlayerMaxForce));
		action_vec.push_back(normalize(TurningForce, -Prm.PlayerMaxTurnRate, Prm.PlayerMaxTurnRate));
		//float angle = RadiansToDegrees(TurningForce);
		//action_vec.push_back(sin(TurningForce));
		//action_vec.push_back(cos(TurningForce));

		/*action_vec.push_back(KickBall ? 1 : -1);
		action_vec.push_back(normalize(KickForce, 0., Prm.MaxShootingForce));
		action_vec.push_back(KickDirection.GetX());
		action_vec.push_back(KickDirection.GetY());
		action_vec.push_back(KickDirection.GetZ());

		action_vec.push_back(TrackBall ? 1 : -1);*/

		return action_vec;
	}

	static inline Action toAction(Tensor actionTensor) {
		vector<float> tensorVec = actionTensor.toHostVector<float>();
		Action action;

		action.ForwardForce = unnormalize(tensorVec[0], -Prm.PlayerMaxForce, Prm.PlayerMaxForce);
		action.TurningForce = unnormalize(tensorVec[1], -Prm.PlayerMaxTurnRate, Prm.PlayerMaxTurnRate);
		/*float ball_ang_sin_rad = tensorVec[1];
		float ball_ang_cos_rad = tensorVec[2];
		float ball_ang_rad = acos(ball_ang_cos_rad);
		if (ball_ang_sin_rad < 0)
			ball_ang_rad *= -1.;
		action.TurningForce = ball_ang_rad;*/

		/*action.KickBall      = tensorVec[2] > 0.1;
		if (action.KickBall) {
			action.KickForce = unnormalize(tensorVec[3], 0., Prm.MaxShootingForce);
		}
		action.KickDirection = Vec3(tensorVec[4], tensorVec[5], tensorVec[6]);

		action.TrackBall = tensorVec[7] > 0.1;*/

		return action;
	}
};

class FieldPlayerMLP
{
private:
	std::shared_ptr<Sequential>  model;
	std::shared_ptr < FirstOrderOptimizer> optimizer;
	MeanSquaredError loss;

	bool trainingOn = true;

public:
	FieldPlayerMLP();

	// Meter definition
	static AverageValueMeter *meter;

	/// <summary>
	/// Process the observation, return action and train model
	/// </summary>
	/// <param name="observation">World Observation from Agent Perspective</param>
	/// <param name="target">The correct target to train agent against. trainingOn needs to be set to true.</param>
	/// <returns>Action that the agent should take</returns>
	Action Process(Observation observation, Action target);

	bool Save(string aFileName);
	bool Load(string aFileName);

	bool isTrainingOn() { return trainingOn; }
	void setTrainingOn(bool training_on) { trainingOn = training_on; }
};

