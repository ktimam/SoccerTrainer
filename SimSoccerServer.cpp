// SimSoccerServer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#ifndef WINDOWS
#include "SimSoccerServer.h"

#include "ic_api.h"

#include <filesystem>
#include <stdio.h>
#include <iostream>

#include "Common/misc/Snapshot.h"

#include "SimSoccer/PitchManager.h"

//#include "3rdparty/cpp-httplib/httplib.h"
//#include "3rdparty/picojson/picojson.h"

using json = nlohmann::json;

#define ENTRY vector<float>

PitchManager* g_PitchManager;

void PrintVectorLine(ostream& output_stream, vector<float>& vec) {
    vector<float>::iterator vec_itr = vec.begin();
    for (; vec_itr != vec.end(); vec_itr++) {
        output_stream << fixed << setprecision(4) << setw(7) << setfill(' ') << (float)*vec_itr << " ";
    }
    output_stream << std::endl;
}

void start_match() {
   IC_API ic_api(CanisterUpdate{std::string(__func__)}, false);
   g_PitchManager = new PitchManager(SoccerPitch::one_vs_one);

   // Create a msg, to be passed back as Candid over the wire
  std::string msg;
  msg.append("Success");
  ic_api.to_wire(CandidTypeText{msg});
}
/* ---------------------------------------------------------
  Extract a 'std::string" from an incoming CandidTypeText
  Respond with an 'std::string' wrapped in a CandidTypeText
*/
void play_match() {
  IC_API ic_api(CanisterUpdate{std::string(__func__)}, false);

  // Get the principal of the caller, as cryptographically verified by the IC
  CandidTypePrincipal caller = ic_api.get_caller();

  // Get the name, passed as a Candid parameter to this method
  uint64_t seed{0};
  uint64_t time{ 0 };
  CandidArgs args_in;
  args_in.append(CandidTypeNat64{&seed});
  args_in.append(CandidTypeNat64{&time});
  ic_api.from_wire(args_in);
  //ic_api.from_wire(CandidTypeNat64{&seed});

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //std::cout << "Time : " << time << std::endl;
  //std::cout << "Seed Generated : " << seed << std::endl;
    //seed random number generator
    srand(seed);

   //g_PitchManager = new PitchManager(SoccerPitch::one_vs_one);

    //std::cout << "Starting Match..." << std::endl;
    g_PitchManager->Run(time);

   std::string msg = "Resume";
   if(g_PitchManager->Finished()){
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
      msg = "";
      msg.append(result.dump());
      
   }
  //msg.append("Your principal is: " + caller.get_text());

  //std::cout << "score1 : " << score1 << std::endl;
  //std::cout << "score2 : " << score2 << std::endl;
  //std::cout << "Match : "  << msg << std::endl;

  // Send the response back
  ic_api.to_wire(CandidTypeText{msg});
}


void delete_file() {
   IC_API ic_api(CanisterUpdate{std::string(__func__)}, false);
   
  std::string filename{""};
  CandidArgs args_in;
  args_in.append(CandidTypeText{&filename});
  ic_api.from_wire(args_in);

  filesystem::remove(filename);

   // Create a msg, to be passed back as Candid over the wire
  std::string msg;
  msg.append("Success");
  ic_api.to_wire(CandidTypeText{msg});
}

void train() {
   IC_API ic_api(CanisterUpdate{std::string(__func__)}, false);

  std::string model_filename{""};
  std::string obsrv_filename{""};
  std::string action_filename{""};
  uint64_t epochs{ 0 };
  float target_score{ 0 };
  CandidArgs args_in;
  args_in.append(CandidTypeText{&model_filename});
  args_in.append(CandidTypeText{&obsrv_filename});
  args_in.append(CandidTypeText{&action_filename});
  args_in.append(CandidTypeNat64{&epochs});
  args_in.append(CandidTypeFloat32{&target_score});
  ic_api.from_wire(args_in);


  int current_epoch = 0;
  float best_ml_score = 10000;
  float start_ml_score = 0;

  FieldPlayerMLP* mlp = new FieldPlayerMLP();
  mlp->Load(model_filename);
  AverageValueMeter* meter = new AverageValueMeter();
  mlp->meter = meter;

  //vector<ObservationAction> observation_action_entries;
  vector<ENTRY> observations_vec;
  vector<ENTRY> actions_vec;

  ifstream obs_ifs(obsrv_filename);
  ifstream act_ifs(action_filename);

  string obs_line;
  string act_line;

while (std::getline(obs_ifs, obs_line), std::getline(act_ifs, act_line)) {

      if(obs_line == "") break;

      vector<float> obs_data;
      vector<float> act_data;

      istringstream obs_iss(obs_line);
      float word;
      while (obs_iss >> word) {
          obs_data.push_back(word);
      }

      istringstream act_iss(act_line);
      while (act_iss >> word) {
          act_data.push_back(word);
      }
      observations_vec.push_back(obs_data);
      actions_vec.push_back(act_data);
  }

  std::string msg;
  time_t start_time = time(NULL);
  time_t last_time  = time(NULL);
  float last_score = 0;
  float current_ml_score = -1;
  while (++current_epoch < epochs) {

      for (uint obsv_i = 0; obsv_i < observations_vec.size(); obsv_i++) {
          Action action = mlp->Process(observations_vec[obsv_i], actions_vec[obsv_i]);
      }

      current_ml_score = meter->value()[0];
      if (start_ml_score == 0) {
          start_ml_score = current_ml_score;
      }
      std::cout << "Epoch: " << current_epoch << " Mean Squared Error: " << current_ml_score
          << std::endl;

      float target_score_difference = current_ml_score - target_score;
      float last_score_difference = last_score - current_ml_score;
      if (last_score == 0) last_score_difference = current_ml_score;
      float score_jumps_needed = 0;
      if(last_score_difference != 0) target_score_difference / last_score_difference;
      time_t current_time = time(NULL);
      double seconds = difftime(current_time, last_time);
      seconds = seconds * score_jumps_needed;
      int hour = seconds / 3600;
      int min = (seconds - hour * 3600) / 60;
      int sec = seconds - hour * 3600 - min * 60;
      std::cout << "Time Remaining: " << hour << ":" << min << ":" << sec
          << std::endl << std::endl;

      float total_difference = start_ml_score - current_ml_score;
      score_jumps_needed = 0;
      if(total_difference != 0) score_jumps_needed = target_score_difference / total_difference;
      seconds = difftime(current_time, start_time);
      seconds = seconds * score_jumps_needed;
      hour = seconds / 3600;
      min = (seconds - hour * 3600) / 60;
      sec = seconds - hour * 3600 - min * 60;
      std::cout << "Average Time Remaining: " << hour << ":" << min << ":" << sec
          << std::endl << std::endl;

      last_time = time(NULL);
      last_score = current_ml_score;

      if (current_epoch == 1) {
          best_ml_score = current_ml_score;
      }
      if (current_ml_score < best_ml_score )
      {
          best_ml_score = current_ml_score;
          mlp->Save(model_filename);
      }
      if (current_ml_score < target_score) {
          mlp->Save(model_filename);
          break;
      }
      meter->reset();

  }
  // Create a msg, to be passed back as Candid over the wire
  stringstream ss;
  ss << "Epoch: " << current_epoch << " Mean Squared Error: " << current_ml_score;
  msg = ss.str();  
  ic_api.to_wire(CandidTypeText{msg});
}
#endif