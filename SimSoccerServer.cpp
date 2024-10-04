// SimSoccerServer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#ifndef WINDOWS
#include "SimSoccerServer.h"

#include "ic_api.h"

#include <stdio.h>
#include <iostream>

#include "Common/misc/Snapshot.h"

#include "SimSoccer/PitchManager.h"

//#include "3rdparty/cpp-httplib/httplib.h"
//#include "3rdparty/picojson/picojson.h"

using json = nlohmann::json;

PitchManager* g_PitchManager;

/* ---------------------------------------------------------
  Extract a 'std::string" from an incoming CandidTypeText
  Respond with an 'std::string' wrapped in a CandidTypeText
*/
void play_match() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);

  // Get the principal of the caller, as cryptographically verified by the IC
  CandidTypePrincipal caller = ic_api.get_caller();

  // Get the name, passed as a Candid parameter to this method
  uint64_t seed{0};
  ic_api.from_wire(CandidTypeNat64{&seed});

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //std::cout << "Seed Generated : " << seed << std::endl;
    //seed random number generator
    srand(seed);

   g_PitchManager = new PitchManager();

    //std::cout << "Starting Match..." << std::endl;
    while (!g_PitchManager->Finished())
    {
       g_PitchManager->Step();
    }

    json result;
    json raw_data = g_PitchManager->MatchReplay()->Snapshots();
    result["snapshot"] = raw_data.dump();
    //std::ofstream o("match_server.json");
    //o << std::setw(4) << raw_data.dump() << std::endl;

    auto score1 = g_PitchManager->GetSoccerPitch()->HomeTeam()->OpponentsGoal()->NumGoalsScored();
    auto score2 = g_PitchManager->GetSoccerPitch()->AwayTeam()->OpponentsGoal()->NumGoalsScored();

    //result["seed"]   = seed;
    result["score1"] = score1;
    result["score2"] = score2;

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Create a msg, to be passed back as Candid over the wire
  std::string msg;
  msg.append(result.dump());
  //msg.append("Your principal is: " + caller.get_text());

  std::cout << "score1 : " << score1 << std::endl;
  std::cout << "score2 : " << score2 << std::endl;
  std::cout << "Match : "  << msg << std::endl;

  // Send the response back
  ic_api.to_wire(CandidTypeText{msg});
}

#endif