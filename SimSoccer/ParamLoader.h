#ifndef PARAMLOADER
#define PARAMLOADER
#pragma warning(disable:4800)
//------------------------------------------------------------------------
//
//Name:  ParamLoader.h
//
//Desc:  singleton class to handle the loading of default parameter
//       values from an initialization file: 'params.ini'
//
//Author: Mat Buckland 2003 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
//#include <fstream>
//#include <string>
//#include <cassert>


#include "constants.h"
//#include "iniFileLoaderBase.h"


#define Prm (*ParamLoader::Instance())

class ParamLoader //: public iniFileLoaderBase
{
private:

    ParamLoader()//:iniFileLoaderBase("Params.ini")
    {

        GoalWidth = 4;// 7.3;// 100;// GetNextParameterDouble();

        NumSupportSpotsX = 13;// GetNextParameterInt();
        NumSupportSpotsY = 6;// GetNextParameterInt();

        Spot_PassSafeScore = 2;//GetNextParameterDouble();
        Spot_CanScoreFromPositionScore = 1;//GetNextParameterDouble();
        Spot_DistFromControllingPlayerScore = 2;//GetNextParameterDouble();
        Spot_ClosenessToSupportingPlayerScore = 0;//GetNextParameterDouble();
        Spot_AheadOfAttackerScore = 0;//GetNextParameterDouble();

        SupportSpotUpdateFreq = 1;//GetNextParameterDouble(); 

        ChancePlayerAttemptsPotShot = 0.005;//GetNextParameterDouble();
        ChanceOfUsingArriveTypeReceiveBehavior = 0.5;//GetNextParameterDouble();

        BallSize = 0.22;// 5;//GetNextParameterDouble();    
        BallMass = 0.5;//GetNextParameterDouble();    
        Friction = -0.015;//GetNextParameterDouble(); 

        KeeperInBallRange = 1;// 10;//GetNextParameterDouble();    
        PlayerInTargetRange = 0.2;// 10;//GetNextParameterDouble(); 
        PlayerKickingDistance = 0.85;// 1;// 6;//GetNextParameterDouble(); 
        PlayerKickFrequency = 8;//GetNextParameterDouble();


        PlayerMass = 50;// 15;// 3;//GetNextParameterDouble(); 
        PlayerMaxForce = 5;// 450;// 1;//GetNextParameterDouble();    
        PlayerMaxSpeedWithBall = 7;// 70;// 1.2;// 3700;//GetNextParameterDouble();   
        PlayerMaxSpeedWithoutBall = 10;// 100;// 1.6;// 4000;//GetNextParameterDouble();   
        PlayerMaxTurnRate = 0.1;//GetNextParameterDouble(); 
        PlayerScale = 1;//GetNextParameterDouble();      
        PlayerComfortZone = 3;// 60;//GetNextParameterDouble();  
        PlayerKickingAccuracy = 0.99;//GetNextParameterDouble();

        NumAttemptsToFindValidStrike = 5;//GetNextParameterInt();



        MaxDribbleForce = 0.2;// 0.5;// 1.5;// 75;// 1.5;//GetNextParameterDouble(); 
        MaxShootingForce = 6;// 6;// 300;// 6;//GetNextParameterDouble();    
        MaxPassingForce = 3;// 3;// 150;// 3;//GetNextParameterDouble();  

        WithinRangeOfHome = 0.5;// 15;//GetNextParameterDouble();    
        WithinRangeOfSupportSpot = 0.5;// 15;//GetNextParameterDouble();    

        MinPassDist = 4;// 120;//GetNextParameterDouble();
        GoalkeeperMinPassDist = 5;// 50;//GetNextParameterDouble();

        GoalKeeperTendingDistance = 2;// 20;//GetNextParameterDouble();    
        GoalKeeperInterceptRange = 5;// 100;//GetNextParameterDouble();
        BallWithinReceivingRange = 1;// 10;//GetNextParameterDouble();

        bStates = 1;//GetNextParameterBool();    
        bIDs = 1;//GetNextParameterBool(); 
        bSupportSpots = 0;//GetNextParameterBool();     
        bRegions = 0;//GetNextParameterBool();
        bShowControllingTeam = 0;//GetNextParameterBool();
        bViewTargets = 1;//GetNextParameterBool();
        bHighlightIfThreatened = 0;//GetNextParameterBool();

        FrameRate = 240;//GetNextParameterInt();

        SeparationCoefficient = 3;//erDouble(); 
        ViewDistance = 3;// 30;//GetNextParameterDouble(); 
        bNonPenetrationConstraint = 0;//GetNextParameterBool(); 


        BallWithinReceivingRangeSq = BallWithinReceivingRange * BallWithinReceivingRange;
        KeeperInBallRangeSq = KeeperInBallRange * KeeperInBallRange;
        PlayerInTargetRangeSq = PlayerInTargetRange * PlayerInTargetRange;
        PlayerKickingDistance += BallSize;
        PlayerKickingDistanceSq = PlayerKickingDistance * PlayerKickingDistance;
        PlayerComfortZoneSq = PlayerComfortZone * PlayerComfortZone;
        GoalKeeperInterceptRangeSq = GoalKeeperInterceptRange * GoalKeeperInterceptRange;
        WithinRangeOfSupportSpotSq = WithinRangeOfSupportSpot * WithinRangeOfSupportSpot;
    }

public:

    static ParamLoader* Instance();

    double GoalWidth;

    int   NumSupportSpotsX;
    int   NumSupportSpotsY;

    //these values tweak the various rules used to calculate the support spots
    double Spot_PassSafeScore;
    double Spot_CanScoreFromPositionScore;
    double Spot_DistFromControllingPlayerScore;
    double Spot_ClosenessToSupportingPlayerScore;
    double Spot_AheadOfAttackerScore;

    double SupportSpotUpdateFreq;

    double ChancePlayerAttemptsPotShot;
    double ChanceOfUsingArriveTypeReceiveBehavior;

    double BallSize;
    double BallMass;
    double Friction;

    double KeeperInBallRange;
    double KeeperInBallRangeSq;

    double PlayerInTargetRange;
    double PlayerInTargetRangeSq;

    double PlayerMass;

    //max steering force
    double PlayerMaxForce;
    double PlayerMaxSpeedWithBall;
    double PlayerMaxSpeedWithoutBall;
    double PlayerMaxTurnRate;
    double PlayerMaxForwardForce;
    double PlayerForwardForceMultiplier;
    double PlayerSteeringForceMultiplier;
    double PlayerScale;
    double PlayerComfortZone;

    double PlayerKickingDistance;
    double PlayerKickingDistanceSq;

    double PlayerKickFrequency;

    double  MaxDribbleForce;
    double  MaxDribbleRotation;
    double  MaxShootingForce;
    double  MaxPassingForce;

    double  PlayerComfortZoneSq;

    //in the range zero to 1.0. adjusts the amount of noise added to a kick,
    //the lower the value the worse the players get
    double  PlayerKickingAccuracy;

    //the number of times the SoccerTeam::CanShoot method attempts to find
    //a valid shot
    int    NumAttemptsToFindValidStrike;

    //the distance away from the center of its home region a player
    //must be to be considered at home
    double WithinRangeOfHome;

    //how close a player must get to a sweet spot before he can change state
    double WithinRangeOfSupportSpot;
    double WithinRangeOfSupportSpotSq;


    //the minimum distance a receiving player must be from the passing player
    double   MinPassDist;
    double   GoalkeeperMinPassDist;

    //this is the distance the keeper puts between the back of the net
    //and the ball when using the interpose steering behavior
    double  GoalKeeperTendingDistance;

    //when the ball becomes within this distance of the goalkeeper he
    //changes state to intercept the ball
    double  GoalKeeperInterceptRange;
    double  GoalKeeperInterceptRangeSq;

    //how close the ball must be to a receiver before he starts chasing it
    double  BallWithinReceivingRange;
    double  BallWithinReceivingRangeSq;


    //these values control what debug info you can see
    bool  bStates;
    bool  bIDs;
    bool  bSupportSpots;
    bool  bRegions;
    bool  bShowControllingTeam;
    bool  bViewTargets;
    bool  bHighlightIfThreatened;

    int FrameRate;


    double SeparationCoefficient;

    //how close a neighbour must be before an agent perceives it
    double ViewDistance;

    //zero this to turn the constraint off
    bool bNonPenetrationConstraint;

};

#endif