#pragma once
#include <vector>

enum player_role { goal_keeper, attacker, defender };

enum ai_type { script, nn };

class PlayerData
{
public:
	int ID;
	double PlayerMaxForce;
	double PlayerMaxSpeedWithoutBall;
	double PlayerMaxTurnRate;
};

class MatchPlayerData
{
public:
	PlayerData Data;

	int Number;
	player_role PlayerRole;
	ai_type AIType;
	int HomeRegion;
};

class TeamData
{
public:
	std::vector<MatchPlayerData> MatchPlayersData;
};

