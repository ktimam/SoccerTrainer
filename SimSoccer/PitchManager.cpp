#include "PitchManager.h"

AverageValueMeter* PitchManager::meter;

PitchManager::PitchManager()
{
    //Init AI and Physics
    fl::init();
    PhysicsManager::Instance()->init();

	meter = new AverageValueMeter();

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
	float current_ml_score = meter->value()[0];
	mEpochNumber++;
	std::cout << "Epoch: " << mEpochNumber << " Mean Squared Error: " << current_ml_score
		<< std::endl << std::endl;

	if (mEpochNumber == 1) {
		mBestMLScore = current_ml_score;
	}
	if (current_ml_score < mBestMLScore && g_SoccerPitch->m_pRedTeam->Members()[0]->Brain()->isTrainingOn())
	{
		mBestMLScore = current_ml_score;
		g_SoccerPitch->m_pBlueTeam->Members()[0]->Brain()->Save("Models/latest_model");
		/*g_SoccerPitch->m_pBlueTeam->Members()[0]->Brain()->Save("Models/model" + 
			to_string(g_SoccerPitch->m_pBlueTeam->Members()[0]->ID())
			+ "_Epoch" + to_string(mEpochNumber));*/
	}
	meter->reset();

	mTickCount = 1;
	mMatchFinished = false;

	g_FinalScore1 = 0;
	g_FinalScore2 = 0;

	PhysicsManager::Instance()->init();
	EntityManager::Instance()->Reset();
	delete g_MatchReplay;
	delete g_SoccerPitch;

    g_SoccerPitch = new SoccerPitch(PitchLength, PitchWidth, mGameMode);

	if (current_ml_score < 0.01) {
		//g_SoccerPitch->m_pBlueTeam->SetAIType(PlayerBase::nn);
	}

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
		//Reset();
		IncrementTime(1);
	}
	if ((goal_scored && RESET_ON_GOAL) ||
		(mMatchFinished && RESET_ON_FINISH)) {
		Reset();
	}

}
