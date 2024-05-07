#pragma once
#include "../SoccerTeam.h"
class OneVsOne :
    public SoccerTeam
{
protected:
    //creates all the players for this team
    virtual void CreatePlayers() override;

public:

    OneVsOne(FieldGoal* home_goal,
        FieldGoal* opponents_goal,
        SoccerPitch* pitch,
        team_color   color);

    ~OneVsOne();


};

