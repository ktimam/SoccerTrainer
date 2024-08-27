#include "PitchManager.h"

PitchManager::PitchManager()
{
    //Init AI and Physics
    fl::init();
    PhysicsManager::Instance()->init();

    g_SoccerPitch = new SoccerPitch(PitchLength, PitchWidth, mGameMode);
    g_MatchReplay = new Snapshot();
}

PitchManager::~PitchManager()
{
	delete g_MatchReplay;
	delete g_SoccerPitch;
}

void PitchManager::Reset()
{
	mTickCount = 1;
	mMatchFinished = false;

	g_FinalScore1 = 0;
	g_FinalScore2 = 0;

	EntityManager::Instance()->Reset();
	delete g_MatchReplay;
	delete g_SoccerPitch;

    g_SoccerPitch = new SoccerPitch(PitchLength, PitchWidth, mGameMode);
    g_MatchReplay = new Snapshot();
	g_LastSnapshot = g_MatchReplay->AddSnapshot(g_SoccerPitch);
}

void PitchManager::Step()
{
	g_SoccerPitch->Update();
	PhysicsManager::Instance()->Update();
	bool goal_scored = g_SoccerPitch->CheckGoal();

	if (LOG_MATCH_OUTPUT)
	{
		//Don't take snapshot for every move
		if (SNAPSHOT_RATE == 1 || mTickCount % SNAPSHOT_RATE == 1 || mTickCount == 1)
		{
			g_LastSnapshot = g_MatchReplay->AddSnapshot(g_SoccerPitch);
		}
	}
	if (g_SoccerPitch->GameOn())
	{
		IncrementTime(1);
	}
	if ((goal_scored && RESET_ON_GOAL) ||
		(mMatchFinished && RESET_ON_FINISH)) {
		Reset();
	}

}
