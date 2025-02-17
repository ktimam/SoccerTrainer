#pragma once

#include <iostream>

#include "SimSoccer/constants.h"
#include "Common/misc/utils.h"
#include "Common/Time/PrecisionTimer.h"
#include "Common/Game/EntityManager.h"
#include "SimSoccer/SoccerPitch.h"
#include "SimSoccer/SoccerTeam.h"
#include "SimSoccer/PlayerBase.h"
#include "SimSoccer/Goalkeeper.h"
#include "SimSoccer/FieldPlayer.h"
#include "SimSoccer/FieldGoal.h"
#include "SimSoccer/SteeringBehaviors.h"
#include "Common/misc/Snapshot.h"
#include "Common/json/json.hpp"
#include "Common/misc/Cgdi.h"
#include "SimSoccer/ParamLoader.h"
#include "Resource.h"
#include "Common/misc/WindowUtils.h"
#include "Common/Debug/DebugConsole.h"
#include "Common/misc/WinHttpWrapper.h"
#include <Common/Game/PhysicsManager.h>

#include "flashlight/fl/tensor/Init.h"
#include "flashlight/fl/dataset/datasets.h"
#include "flashlight/fl/meter/meters.h"
#include "flashlight/fl/nn/nn.h"
//#include "flashlight/fl/optim/optim.h"
#include "flashlight/fl/optim/SGDOptimizer.h"
#include "flashlight/fl/tensor/Random.h"
#include "flashlight/fl/tensor/TensorBase.h"

using namespace fl;

//#include <flashlight/fl/flashlight.h>

using namespace std;
using json = nlohmann::json;

class PitchManager
{
	//--------------------------------- Globals ------------------------------
//
//------------------------------------------------------------------------

	int mMatchDurationSeconds = 60;// 20000;// 45;
	const int MATCH_RATE = 1;

	const int MILLI_IN_SECOND = 20;
	const int MILLI_IN_MINUTE = 60 * 20;
	const int SECOND_MAX_VALUE = 60;

	bool mResetOnFinish = false;
	bool mResetOnGoal = false;

	bool mLogMatchOutput = true;

	int mSnapshotRate = 1 * MATCH_RATE;

	SoccerPitch* g_SoccerPitch;
	Snapshot* g_MatchReplay;
	json         g_LastSnapshot;

	SoccerPitch::game_mode mGameMode;

	int mTickCount = 1;
	bool mMatchFinished = false;

	int g_FinalScore1 = 0;
	int g_FinalScore2 = 0;

	float mBestMLScore = 10000;
	int mEpochNumber = 1;

	int IncrementTime(int rate)
	{
		mTickCount += MATCH_RATE * rate;

		int seconds = mTickCount / MILLI_IN_SECOND;

		if (seconds >= mMatchDurationSeconds)
		{
			mMatchFinished = true;
		}
		return seconds;
	}
public:
	// Meter definition
	static AverageValueMeter* meter;

	PitchManager(SoccerPitch::game_mode aGameMode);
	~PitchManager();

	void TogglePause(){
		g_SoccerPitch->TogglePause();
	}

	SoccerPitch* GetSoccerPitch() { return g_SoccerPitch; }

	bool Finished() {
		return mMatchFinished;
	}

	json         LastSnapshot() { return g_LastSnapshot; }

	Snapshot* MatchReplay(){return g_MatchReplay;}

	std::string GetCurrentTimeString()
	{
		int seconds = (mTickCount / MILLI_IN_SECOND) % SECOND_MAX_VALUE;
		int minutes = mTickCount / MILLI_IN_MINUTE;
		std::ostringstream stringStream;
		stringStream << minutes << " : " << seconds;
		std::string time = stringStream.str();
		return time;
	}
	void SetMatchDurationSeconds(int seconds) { mMatchDurationSeconds = seconds; }
	void Step();
	void Reset();
	void Run(int seconds);
};

