#ifndef SUPPORTSPOTCALCULATOR
#define SUPPORTSPOTCALCULATOR
#pragma warning (disable:4786)
//------------------------------------------------------------------------
//
//  Name:   SupportSpotCalculator.h
//
//  Desc:   Class to determine the best spots for a suppoting soccer
//          player to move to.
//
//  Author: Mat Buckland 2003 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------

#include <vector>

#include "../Common/Game/Region.h"
//#include "Common/misc/Cgdi.h"


class PlayerBase;
class Goal;
class SoccerBall;
class SoccerTeam;
class Regulator;



//------------------------------------------------------------------------

class SupportSpotCalculator
{
public:
  
  //a data structure to hold the values and positions of each spot
  struct SupportSpot
  {
    
    Vec3  m_vPos;

    double    m_dScore;

    SupportSpot(Vec3 pos, double value):m_vPos(pos),
                                            m_dScore(value)
    {}
  };

private:


  SoccerTeam*               m_pTeam;

  std::vector<SupportSpot>  m_Spots;

  //a pointer to the highest valued spot from the last update
  SupportSpot*              m_pBestSupportingSpot;

  //this will regulate how often the spots are calculated (default is
  //one update per second)
  //Regulator*                m_pRegulator;

public:
  
  SupportSpotCalculator(int numX,
                        int numY,
                        SoccerTeam* team);

  ~SupportSpotCalculator();

  //draws the spots to the screen as a hollow circles. The higher the 
  //score, the bigger the circle. The best supporting spot is drawn in
  //bright green.
  //void       Render()const;

  const std::vector<SupportSpot>& SupportSpots()const { return m_Spots; }
  const SupportSpot* BestSupportingSpot()const { return m_pBestSupportingSpot; }

  //this method iterates through each possible spot and calculates its
  //score.
  Vec3  DetermineBestSupportingPosition();

  //returns the best supporting spot if there is one. If one hasn't been
  //calculated yet, this method calls DetermineBestSupportingPosition and
  //returns the result.
  Vec3  GetBestSupportingSpot();
};


#endif