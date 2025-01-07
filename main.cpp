#ifndef LINUX
#ifndef WIN3D

#pragma warning (disable:4786)
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
//#include <time.h>

#define WIN32_LEAN_AND_MEAN      // Exclude rarely-used stuff from Windows headers

#include <iostream>

#include "SimSoccer/PitchManager.h"

using namespace WinHttpWrapper;
using namespace std;
using json = nlohmann::json;

//#define PLAYER_STATE_INFO_ON

//#define SERVER_MODE
//#define CLIENT_MODE
#define LIVE_MODE
//#define REMOTE_MODE

//#define TRAIN_FROM_OBSERVATION_FILE
//#define DUMP_FROM_BINARY_TO_TEXT

////--------------------------------- Globals ------------------------------
////
////------------------------------------------------------------------------

int RENDERING_RATE = 1;

const char* g_szApplicationName = "Simple Soccer";
const char*	g_szWindowClassName = "MyWindowClass";

const wstring REMOTE_API_SERVER_URL = L"localhost";
int REMOTE_API_SERVER_PORT = 3010;
bool REMOTE_API_SERVER_HTTPS = false;
const wstring requestHeader = L"Content-Type: application/json";

PitchManager* g_PitchManager;
SoccerPitch::game_mode gGameMode = SoccerPitch::one_vs_one;
TeamData gHomeTeam;
TeamData gAwayTeam;

//the vertex buffer
std::vector<Vector2D>   g_vecPlayerVB;
//the buffer for the transformed vertices
std::vector<Vector2D>   g_vecPlayerVBTrans;

//create a timer
PrecisionTimer timer(Prm.FrameRate);

bool g_singleStepEnabled = false;
enum StepType{STEP, NO_STEP, STEP_SAVE_OBSERVATION, STEP_NO_SAVE_OBSERVATION};
StepType g_stepType = NO_STEP;
bool g_updateConsole = true;

Observation g_LastObservation[11];
Action g_LastTargetAction[11];

void PrintVectorLine(ostream& output_stream, vector<float>& vec) {
    vector<float>::iterator vec_itr = vec.begin();
    for (; vec_itr != vec.end(); vec_itr++) {
        output_stream << fixed << setprecision(4) << setw(7) << setfill(' ') << (float)*vec_itr << " ";
    }
    output_stream << std::endl;
}
//used when a user clicks on a menu item to ensure the option is 'checked'
//correctly
void CheckAllMenuItemsAppropriately(HWND hwnd)
{
   CheckMenuItemAppropriately(hwnd, IDM_SHOW_REGIONS, Prm.bRegions);
   CheckMenuItemAppropriately(hwnd, IDM_SHOW_STATES, Prm.bStates);
   CheckMenuItemAppropriately(hwnd, IDM_SHOW_IDS, Prm.bIDs);
   CheckMenuItemAppropriately(hwnd, IDM_AIDS_SUPPORTSPOTS, Prm.bSupportSpots);
   CheckMenuItemAppropriately(hwnd, ID_AIDS_SHOWTARGETS, Prm.bViewTargets);
   CheckMenuItemAppropriately(hwnd, IDM_AIDS_HIGHLITE, Prm.bHighlightIfThreatened);
}

bool RenderSoccerPitch()
{
    SoccerPitch* g_SoccerPitch = g_PitchManager->GetSoccerPitch();
    //draw the grass
    gdi->DarkGreenPen();
    gdi->DarkGreenBrush();
    gdi->Rect(0.0f, 0.0f, g_SoccerPitch->cxClient() * PitchWindowRate, g_SoccerPitch->cyClient() * PitchWindowRate);

    //render regions
    if (Prm.bRegions)
    {
        for (unsigned int r = 0; r < g_SoccerPitch->Regions().size(); ++r)
        {
            //g_SoccerPitch->Regions()[r]->Render(true);

            gdi->HollowBrush();
            gdi->GreenPen();
            gdi->Rect(g_SoccerPitch->Regions()[r]->Left() * PitchWindowRate, g_SoccerPitch->Regions()[r]->Top() * PitchWindowRate, g_SoccerPitch->Regions()[r]->Right() * PitchWindowRate, g_SoccerPitch->Regions()[r]->Bottom() * PitchWindowRate);
            
            gdi->TextColor(Cgdi::green);
            gdi->TextAtPos(Vector2D(g_SoccerPitch->Regions()[r]->Center().GetX() * PitchWindowRate, g_SoccerPitch->Regions()[r]->Center().GetZ() * PitchWindowRate), ttos(g_SoccerPitch->Regions()[r]->ID()));
        }
    }

    //render the goals
    gdi->HollowBrush();
    gdi->RedPen();
    gdi->Rect(g_SoccerPitch->PlayingArea()->Left() * PitchWindowRate, (g_SoccerPitch->cyClient() - Prm.GoalWidth) * PitchWindowRate / 2, g_SoccerPitch->PlayingArea()->Left() * PitchWindowRate + 4, g_SoccerPitch->cyClient() * PitchWindowRate - (g_SoccerPitch->cyClient() - Prm.GoalWidth) * PitchWindowRate / 2);

    gdi->BluePen();
    gdi->Rect(g_SoccerPitch->PlayingArea()->Right() * PitchWindowRate, (g_SoccerPitch->cyClient() - Prm.GoalWidth) * PitchWindowRate / 2, g_SoccerPitch->PlayingArea()->Right() * PitchWindowRate - 4, g_SoccerPitch->cyClient() * PitchWindowRate - (g_SoccerPitch->cyClient() - Prm.GoalWidth) * PitchWindowRate / 2);

    //render the pitch markings
    gdi->WhitePen();
    gdi->Circle(Vector2D(g_SoccerPitch->PlayingArea()->Center().GetX() * PitchWindowRate, g_SoccerPitch->PlayingArea()->Center().GetZ() * PitchWindowRate), g_SoccerPitch->PlayingArea()->Width() * PitchWindowRate * 0.125);
    gdi->Line(g_SoccerPitch->PlayingArea()->Center().GetX() * PitchWindowRate, g_SoccerPitch->PlayingArea()->Top() * PitchWindowRate, g_SoccerPitch->PlayingArea()->Center().GetX() * PitchWindowRate, g_SoccerPitch->PlayingArea()->Bottom() * PitchWindowRate);
    gdi->WhiteBrush();
    gdi->Circle(Vector2D(g_SoccerPitch->PlayingArea()->Center().GetX() * PitchWindowRate, g_SoccerPitch->PlayingArea()->Center().GetZ() * PitchWindowRate), 2.0);


    gdi->WhitePen();
    gdi->WhiteBrush();

    json g_LastSnapshot = g_PitchManager->LastSnapshot();
    bool empty = g_LastSnapshot.empty();
    if ( !empty)
    {
        gdi->BlackBrush();
        json::iterator it = g_LastSnapshot["scrn"].begin();
        //Render the ball
        json::iterator entity_position_json = it.value()["p"].begin();
        double entity_position_x = entity_position_json.value();
        double entity_position_y = (++entity_position_json).value();
        Vector2D entity_position = Vector2D( entity_position_x * PitchWindowRate, entity_position_y * PitchWindowRate);
        gdi->Circle(entity_position, Prm.BallSize * PitchWindowRate);

        //Render the teams
        for (++it; it != g_LastSnapshot["scrn"].end(); ++it) {

            int id = it.value()["id"];// .begin().value();
            PlayerBase* player = (PlayerBase*)EntityMgr->GetEntityFromID(id);

            //Persist Observation
            if (g_singleStepEnabled && g_stepType == STEP_SAVE_OBSERVATION && player->Brain()) {
                //static int count = 0;
                std::ofstream o("Models/observations", ios::app | ios::binary);
                o.write((char*)&g_LastObservation[id], sizeof(g_LastObservation[id]));
                o.write((char*)&g_LastTargetAction[id], sizeof(g_LastTargetAction[id]));
                o.close();


                std::ofstream obs_ofs("Models/observations.txt", ios::app);
                vector<float> observation_vec = g_LastObservation[id].toVector();
                PrintVectorLine(obs_ofs, observation_vec);
                obs_ofs.close();

                std::ofstream act_ofs("Models/actions.txt", ios::app);
                vector<float> decision_vec = g_LastTargetAction[id].toVector();
                PrintVectorLine(act_ofs, decision_vec);
                act_ofs.close();

                g_stepType = STEP;
            }
            if (g_singleStepEnabled && player->Brain() && g_updateConsole) {

                g_updateConsole = false;

                cout << "Player ID : " << id << endl;

                g_LastObservation[id] = player->GetLastObservation();
                vector<float> observation_vec = g_LastObservation[id].toVector();
                PrintVectorLine(cout, observation_vec);

                g_LastTargetAction[id] = player->GetLastTargetAction();
                vector<float> decision_vec = g_LastTargetAction[id].toVector();
                PrintVectorLine(cout, decision_vec);

                vector<float> action_vec = player->Brain()->Process(g_LastObservation[id], g_LastTargetAction[id]).toVector();
                PrintVectorLine(cout, action_vec);
            }
            /*Tensor observation_tensor = Tensor::fromVector(last_observation.toVector());
            Tensor decision = Tensor::fromVector(last_target_action.toVector());
            std::cout << "observation_tensor : " << observation_tensor << std::endl;
            std::cout << "decision : " << decision << std::endl;
            std::cout << "count : " << count++ << std::endl;*/

            //End Persist Observation

            entity_position_json = it.value()["p"].begin();
            entity_position_x = entity_position_json.value();
            entity_position_y = (++entity_position_json).value();
            Vector2D entity_position = Vector2D(entity_position_x * PitchWindowRate, entity_position_y * PitchWindowRate);

            json::iterator entity_heading_json = it.value()["h"].begin();
            json entity_heading_x = entity_heading_json.value();
            json entity_heading_y = (++entity_heading_json).value();
            Vector2D entity_heading = Vector2D(entity_heading_x, entity_heading_y);

            gdi->TransparentText();
            gdi->TextColor(Cgdi::grey);

            //set appropriate team color
            if (player->Team()->Color() == SoccerTeam::blue) { gdi->BluePen(); }
            else { gdi->RedPen(); }



            //render the player's body
            g_vecPlayerVBTrans = WorldTransform(g_vecPlayerVB,
                entity_position,
                entity_heading,
                entity_heading.Perp(),
                Vector2D(Prm.PlayerScale, Prm.PlayerScale));
            gdi->ClosedShape(g_vecPlayerVBTrans);

            //and 'is 'ead
            gdi->BrownBrush();
            gdi->Circle(entity_position, 6);


            //and 'is 'ead
            gdi->BrownBrush();
#ifdef LIVE_MODE
            if (Prm.bHighlightIfThreatened && (player->Team()->ControllingPlayer() == player) && player->isThreatened()) gdi->YellowBrush();
            if (player->AIType() == ai_type::nn) gdi->LightPinkPen();
#endif
            gdi->Circle(entity_position, 6);

#ifdef LIVE_MODE
            //render the state
            if (Prm.bStates)
            {
                gdi->TextColor(0, 170, 0);
                gdi->TextAtPos(entity_position.x, entity_position.y - 20, player->GetCurrentStateName());
            }

            //show IDs
            if (Prm.bIDs)
            {
                gdi->TextColor(0, 170, 0);
                gdi->TextAtPos(entity_position.x - 20, entity_position.y - 20, ttos(player->ID()));
            }


            if (Prm.bViewTargets)
            {
                gdi->RedBrush();
                gdi->Circle(Vector2D(player->Steering()->Target().GetX()* PitchWindowRate, player->Steering()->Target().GetZ()* PitchWindowRate), 3);
                gdi->TextAtPos(Vector2D(player->Steering()->Target().GetX() * PitchWindowRate, player->Steering()->Target().GetZ() * PitchWindowRate), ttos(player->ID()));
            }
            //gdi->WhitePen();
            //gdi->Line(entity_position.x, entity_position.y, player->Steering()->Target().GetX(), player->Steering()->Target().GetZ());


            gdi->ThickBluePen();
            double forwardforce = player->Steering()->ForwardComponent();// *10;
            Vec3 force = player->Heading() * forwardforce;
            force = force + Vec3(player->Pos().GetX() * PitchWindowRate,0, player->Pos().GetZ() * PitchWindowRate);
            gdi->Line(entity_position.x, entity_position.y, force.GetX(), force.GetZ());

            /*gdi->ThickGreenPen();
            Vec3 velocity_target = player->Pos() + player->Velocity();
            gdi->Line(entity_position.x, entity_position.y, velocity_target.GetX(), velocity_target.GetZ());*/
#endif
        }
    }

    //render the walls
    gdi->WhitePen();
    bool RenderNormals = false;
    for (unsigned int w = 0; w < g_SoccerPitch->Walls().size(); ++w)
    {
        gdi->Line(g_SoccerPitch->Walls()[w].From().x * PitchWindowRate, g_SoccerPitch->Walls()[w].From().y * PitchWindowRate, 
            g_SoccerPitch->Walls()[w].To().x * PitchWindowRate, g_SoccerPitch->Walls()[w].To().y* PitchWindowRate);

        //render the normals if rqd
        if (RenderNormals)
        {
            int MidX = (int)((g_SoccerPitch->Walls()[w].From().x+ g_SoccerPitch->Walls()[w].To().x)/2) * PitchWindowRate;
            int MidY = (int)((g_SoccerPitch->Walls()[w].From().y+ g_SoccerPitch->Walls()[w].To().y)/2) * PitchWindowRate;

            gdi->Line(MidX, MidY, (int)(MidX+(g_SoccerPitch->Walls()[w].Normal().x * PitchWindowRate * 5)), (int)(MidY+(g_SoccerPitch->Walls()[w].Normal().y * PitchWindowRate * 5)));
        }
    }
    gdi->TextColor(Cgdi::black);
    gdi->TextAtPos((int)(g_SoccerPitch->cxClient() * PitchWindowRate / 2) - 10, 2, g_PitchManager->GetCurrentTimeString());

#ifdef LIVE_MODE
    //render the sweet spots
    if (Prm.bSupportSpots)
    {
        SoccerTeam* controllingteam = g_SoccerPitch->HomeTeam();
        if (g_SoccerPitch->AwayTeam()->InControl())
        {
            controllingteam = g_SoccerPitch->AwayTeam();
        }

        gdi->HollowBrush();
        gdi->GreyPen();

        SupportSpotCalculator* ssc = controllingteam->GetSupportSpotCalculator();
        const std::vector<SupportSpotCalculator::SupportSpot>& SupportSpots = ssc->SupportSpots();
        for (unsigned int spt = 0; spt < SupportSpots.size(); ++spt)
        {
            gdi->Circle(Vector2D(SupportSpots[spt].m_vPos.GetX()* PitchWindowRate, SupportSpots[spt].m_vPos.GetZ()* PitchWindowRate), SupportSpots[spt].m_dScore);
        }

        if (ssc->BestSupportingSpot())
        {
            gdi->GreenPen();
            gdi->Circle(Vector2D(ssc->BestSupportingSpot()->m_vPos.GetX()* PitchWindowRate, ssc->BestSupportingSpot()->m_vPos.GetZ()* PitchWindowRate), ssc->BestSupportingSpot()->m_dScore);
        }
    }
#endif
// 
    //show the score
    gdi->TextColor(Cgdi::red);
    gdi->TextAtPos((WindowWidth /2)-50, WindowHeight -18, "Red: " + ttos(g_SoccerPitch->HomeTeam()->OpponentsGoal()->NumGoalsScored()));

    gdi->TextColor(Cgdi::blue);
    gdi->TextAtPos((WindowWidth /2)+10, WindowHeight -18, "Blue: " + ttos(g_SoccerPitch->AwayTeam()->OpponentsGoal()->NumGoalsScored()));

    return true;
}

//---------------------------- WindowProc ---------------------------------
//	
//	This is the callback function which handles all the windows messages
//-------------------------------------------------------------------------

LRESULT CALLBACK WindowProc (HWND   hwnd,
                             UINT   msg,
                             WPARAM wParam,
                             LPARAM lParam)
{
 
   //these hold the dimensions of the client window area
	 static int cxClient, cyClient; 

	 //used to create the back buffer
   static HDC		hdcBackBuffer;
   static HBITMAP	hBitmap;
   static HBITMAP	hOldBitmap;

    switch (msg)
    {
	
		//A WM_CREATE msg is sent when your application window is first
		//created
    case WM_CREATE:
      {
         //to get get the size of the client window first we need  to create
         //a RECT and then ask Windows to fill in our RECT structure with
         //the client window size. Then we assign to cxClient and cyClient 
         //accordingly
			   RECT rect;

			   GetClientRect(hwnd, &rect);

			   cxClient = rect.right;
			   cyClient = rect.bottom;

#ifdef REMOTE_MODE
               HttpRequest req(REMOTE_API_SERVER_URL, REMOTE_API_SERVER_PORT, REMOTE_API_SERVER_HTTPS);
               HttpResponse response;

               cout << "Action: REMOTE api server - input" << endl;
               req.Post(L"/api/input",
                   requestHeader,
                   R"({"payload":"hello"})",
                   response);
               json response_json = json::parse(response.text);
               int epoch = response_json["epoch_index"];
               int input = response_json["input_index"];
               json query_json;
               query_json["epoch"] = epoch;
               query_json["input"] = input;
               string query_text = query_json.dump();
               cout << "Returned Status:" << response.statusCode << endl;
               cout << "Content Length:" << response.contentLength << endl << endl;
               //PrintDictionary(response.GetHeaderDictionary());
               //wcout << endl << response.header << endl;
               response.Reset();

               cout << "Action: REMOTE api server - notice" << endl;
               req.Post(L"/api/notice_list",
                   requestHeader,
                   query_text,
                   response);
               while (response.text == "[]")
               {
                   //Match result not retrieved yet, try again
                   cout << "Match result not retrieved yet, trying again..." << endl;
                   response.Reset(); 
                   Sleep(100);
                   req.Post(L"/api/notice_list",
                       requestHeader,
                       query_text,
                       response);
               }
               json match_json = json::parse(response.text);
               json::iterator it = match_json.begin();
               string payload = it.value()["payload"];
               json payloadjson = json::parse(payload);
               unsigned seed = payloadjson["seed"];
               g_FinalScore1 = payloadjson["score1"];
               g_FinalScore2 = payloadjson["score2"];
               cout << "Returned Status:" << response.statusCode << endl;
               cout << "Content Length:" << response.contentLength << endl << endl;
               //PrintDictionary(response.GetHeaderDictionary());
               //wcout << endl << response.header << endl;
               response.Reset();

               std::cout << "Using Seed : " << seed << std::endl;
               std::cout << "FinalScore1 : " << g_FinalScore1 << std::endl;
               std::cout << "FinalScore2 : " << g_FinalScore2 << std::endl;
               srand(1674374940);// seed);
#else
         //seed random number generator
         srand((unsigned)time(0));
#endif

         
         //---------------create a surface to render to(backbuffer)

         //create a memory device context
         hdcBackBuffer = CreateCompatibleDC(NULL);

         //get the DC for the front buffer
         HDC hdc = GetDC(hwnd);

         hBitmap = CreateCompatibleBitmap(hdc,
                                          cxClient,
                                          cyClient);

			  
         //select the bitmap into the memory device context
			   hOldBitmap = (HBITMAP)SelectObject(hdcBackBuffer, hBitmap);

         //don't forget to release the DC
         ReleaseDC(hwnd, hdc); 
         
         {
             PlayerData player_data;
             player_data.ID = 55;
             player_data.PlayerMaxForce = Prm.PlayerMaxForce;
             player_data.PlayerMaxSpeedWithoutBall = Prm.PlayerMaxSpeedWithoutBall;
             player_data.PlayerMaxTurnRate = Prm.PlayerMaxTurnRate;
             MatchPlayerData match_player_data;
             match_player_data.Data = player_data;
             match_player_data.AIType = ai_type::nn;
             match_player_data.HomeRegion = 10;
             match_player_data.Number = 10;
             match_player_data.PlayerRole = player_role::attacker;
             gHomeTeam.MatchPlayersData.push_back(match_player_data);
         }
         {
             PlayerData player_data;
             player_data.ID = 66;
             player_data.PlayerMaxForce = Prm.PlayerMaxForce;
             player_data.PlayerMaxSpeedWithoutBall = Prm.PlayerMaxSpeedWithoutBall;
             player_data.PlayerMaxTurnRate = Prm.PlayerMaxTurnRate;
             MatchPlayerData match_player_data;
             match_player_data.Data = player_data;
             match_player_data.AIType = ai_type::script;
             match_player_data.HomeRegion = 4;
             match_player_data.Number = 5;
             match_player_data.PlayerRole = player_role::defender;
             gAwayTeam.MatchPlayersData.push_back(match_player_data);
         }
         g_PitchManager = new PitchManager(gHomeTeam, gAwayTeam, gGameMode);

         //setup the vertex buffers and calculate the bounding radius
         const int NumPlayerVerts = 4;
         const Vector2D player[NumPlayerVerts] = { Vector2D(-3, 8),
                                                   Vector2D(3,10),
                                                   Vector2D(3,-10),
                                                   Vector2D(-3,-8) };

         for (int vtx = 0; vtx < NumPlayerVerts; ++vtx)
         {
             g_vecPlayerVB.push_back(player[vtx]);
         }

         CheckAllMenuItemsAppropriately(hwnd);

      }

      break;

    case WM_COMMAND:
      {
        switch(wParam)
        {
          case ID_AIDS_NOAIDS:

            Prm.bStates        = 0;
            Prm.bRegions       = 0;
            Prm.bIDs           = 0;
            Prm.bSupportSpots  = 0;
            Prm.bViewTargets   = 0;

            CheckAllMenuItemsAppropriately(hwnd);

            break;
            
          case IDM_SHOW_REGIONS:

            Prm.bRegions = !Prm.bRegions;

            CheckAllMenuItemsAppropriately(hwnd);

            break;

          case IDM_SHOW_STATES:

            Prm.bStates = !Prm.bStates;

            CheckAllMenuItemsAppropriately(hwnd);

            break;

          case IDM_SHOW_IDS:

            Prm.bIDs = !Prm.bIDs;

            CheckAllMenuItemsAppropriately(hwnd);

            break;


          case IDM_AIDS_SUPPORTSPOTS:

            Prm.bSupportSpots = !Prm.bSupportSpots;

            CheckAllMenuItemsAppropriately(hwnd);

             break;

           case ID_AIDS_SHOWTARGETS:

            Prm.bViewTargets = !Prm.bViewTargets;

            CheckAllMenuItemsAppropriately(hwnd);

             break;
              
           case IDM_AIDS_HIGHLITE:

            Prm.bHighlightIfThreatened = !Prm.bHighlightIfThreatened; 

            CheckAllMenuItemsAppropriately(hwnd);

            break;
            
        }//end switch
      }

      break;


    case WM_KEYUP:
      {
        switch(wParam)
        {
           case VK_ESCAPE:
            {             
              SendMessage(hwnd, WM_DESTROY, NULL, NULL);
            }
          
            break;

          case 'R':
            {
              delete g_PitchManager;
              g_PitchManager = new PitchManager(gHomeTeam, gAwayTeam, gGameMode);
            }

            break;

          case 'P':
            {
              g_PitchManager->TogglePause();
            }

            break;

          case 'F':
          {
              RENDERING_RATE = 100;
          }

          break;

          case 'N':
          {
              RENDERING_RATE = 1;
          }

          break;

          case 'S':
          {
              g_stepType = STEP_SAVE_OBSERVATION;
          }

          break;

        }//end switch
        
      }//end WM_KEYUP

      break;

    case WM_KEYDOWN:
    {
        switch (wParam)
        {

        case 'D':
        {
            g_stepType = STEP_NO_SAVE_OBSERVATION;
        }

        break;

        }//end switch

    }//end WM_KEYDOWN

    break;

    
    case WM_PAINT:
      {
 		       
         PAINTSTRUCT ps;
          
         BeginPaint (hwnd, &ps);
         
         gdi->StartDrawing(hdcBackBuffer);
         
         //g_SoccerPitch->Render();
         RenderSoccerPitch();

         gdi->StopDrawing(hdcBackBuffer);

        

         //now blit backbuffer to front
			   BitBlt(ps.hdc, 0, 0, cxClient, cyClient, hdcBackBuffer, 0, 0, SRCCOPY); 
          
         EndPaint (hwnd, &ps);

      }

      break;

    //has the user resized the client area?
		case WM_SIZE:
		  {
        //if so we need to update our variables so that any drawing
        //we do using cxClient and cyClient is scaled accordingly
			  cxClient = LOWORD(lParam);
			  cyClient = HIWORD(lParam);

      //now to resize the backbuffer accordingly. First select
      //the old bitmap back into the DC
			SelectObject(hdcBackBuffer, hOldBitmap);

      //don't forget to do this or you will get resource leaks
      DeleteObject(hBitmap); 

			//get the DC for the application
      HDC hdc = GetDC(hwnd);

			//create another bitmap of the same size and mode
      //as the application
      hBitmap = CreateCompatibleBitmap(hdc,
											cxClient,
											cyClient);

			ReleaseDC(hwnd, hdc);
			
			//select the new bitmap into the DC
      SelectObject(hdcBackBuffer, hBitmap);

      }

      break;
          
		 case WM_DESTROY:
			 {

         //clean up our backbuffer objects
         SelectObject(hdcBackBuffer, hOldBitmap);

         DeleteDC(hdcBackBuffer);
         DeleteObject(hBitmap); 
         
         // kill the application, this sends a WM_QUIT message  
				 PostQuitMessage (0);
			 }

       break;

     }//end switch

     //this is where all the messages not specifically handled by our 
		 //winproc are sent to be processed
		 return DefWindowProc (hwnd, msg, wParam, lParam);
}

//-------------------------------- WinMain -------------------------------
//
//	The entry point of the windows program
//------------------------------------------------------------------------
int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR     szCmdLine, 
                    int       iCmdShow)
{
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);

  //handle to our window
  HWND						hWnd;
    
  //our window class structure
  WNDCLASSEX     winclass;
		 
  // first fill in the window class stucture
  winclass.cbSize        = sizeof(WNDCLASSEX);
  winclass.style         = CS_HREDRAW | CS_VREDRAW;
  winclass.lpfnWndProc   = WindowProc;
  winclass.cbClsExtra    = 0;
  winclass.cbWndExtra    = 0;
  winclass.hInstance     = hInstance;
  winclass.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
  winclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
  winclass.hbrBackground = NULL;
  winclass.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU1);
  winclass.lpszClassName = g_szWindowClassName;
  winclass.hIconSm       = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));

  //register the window class
  if (!RegisterClassEx(&winclass))
  {
    MessageBox(NULL, "Registration Failed!", "Error", 0);

    //exit the application
    return 0;
  }

  //create the window and assign its ID to hwnd    
  hWnd = CreateWindowEx (NULL,                 // extended style
                         g_szWindowClassName,  // window class name
                         g_szApplicationName,  // window caption
                         WS_OVERLAPPED | WS_VISIBLE | WS_CAPTION | WS_SYSMENU,
                         GetSystemMetrics(SM_CXSCREEN)/2 - WindowWidth/2,
                         GetSystemMetrics(SM_CYSCREEN)/2 - WindowHeight/2,                    
                         WindowWidth + 10,     // initial x size
                         WindowHeight + 70,    // initial y size
                         NULL,                 // parent window handle
                         NULL,                 // window menu handle
                         hInstance,            // program instance handle
                         NULL);                // creation parameters

  //make sure the window creation has gone OK
  if(!hWnd)
  {
    MessageBox(NULL, "CreateWindowEx Failed!", "Error!", 0);
  }

  //start the timer
  timer.Start();

  MSG msg;

#ifdef SERVER_MODE
  while(!g_PitchManager->Finished())
  {
      g_PitchManager->Step();
  }//end while
  // write prettified JSON to another file// , std::ios::out | std::ios::binary | std::ios::ate);
  json raw_data = g_MatchReplay->Snapshots();
  // create a JSON value
  //std::vector<std::uint8_t> v_bson = json::to_msgpack(raw_data);
  //std::ofstream obson("match.msgpack.json", std::ios::out | std::ios::binary | std::ios::ate);
  //// print the vector content
  //for (auto& byte : v_bson)
  //{
  //    obson << "0x" << std::hex << std::setw(2) << std::setfill('0') << (int)byte << " ";
  //}
  //obson << std::endl;

  std::ofstream o("match.json");
  o << std::setw(4) << raw_data << std::endl;
#endif


#ifdef TRAIN_FROM_OBSERVATION_FILE
  const int EPOCHS_COUNT = 1000000;
  int current_epoch = 0;
  float best_ml_score = 10000;
  float start_ml_score = 0;
  float target_score = 0.005;// 0.012;

  FieldPlayerMLP* mlp = new FieldPlayerMLP();
  mlp->Load("Models/latest_model");
  AverageValueMeter* meter = new AverageValueMeter();
  mlp->meter = meter;

  vector<ObservationAction> observation_action_entries;

#ifdef DUMP_FROM_BINARY_TO_TEXT
  Observation observation;
  Action target;

  std::ofstream obs_ofs("Models/observations.txt");
  std::ofstream act_ofs("Models/actions.txt");

  std::ifstream ifs("Models/observations", ios::binary);
  ifs.read((char*)&observation, sizeof(observation));
  ifs.read((char*)&target, sizeof(target));

  while (!ifs.eof()) {
      ifs.read((char*)&observation, sizeof(observation));
      ifs.read((char*)&target, sizeof(target));

      //Tensor observation_tensor = Tensor::fromVector(observation_vec);
      //Tensor decision = Tensor::fromVector(decision_vec);
      //Tensor action_tensor = Tensor::fromVector(action.toVector());
      //ofs << "observation_tensor : " << observation_tensor << std::endl;
      //ofs << "decision : " << decision << std::endl << std::endl;
      //std::cout << "result : " << action_tensor << std::endl;
      //std::cout << "count : " << count++ << std::endl;

      vector<float> observation_vec = observation.toVector();
      vector<float> decision_vec = target.toVector();

      vector<float>::iterator observation_itr = observation_vec.begin();
      for (; observation_itr != observation_vec.end(); observation_itr++) {
          obs_ofs << fixed << setprecision(4) << setw(7) << setfill(' ') << (float)*observation_itr << " ";
      }
      obs_ofs << std::endl ;

      vector<float>::iterator decision_itr = decision_vec.begin();
      for (; decision_itr != decision_vec.end(); decision_itr++) {
          act_ofs << fixed << setprecision(4) << setw(7) << setfill(' ') << (float)*decision_itr << " ";
      }
      act_ofs << std::endl ;
  }
  ifs.close();
  obs_ofs.close();
  act_ofs.close();
#endif

  ifstream obs_ifs("Models/observations.txt");
  ifstream act_ifs("Models/actions.txt");

  string obs_line;
  string act_line;

while (std::getline(obs_ifs, obs_line), std::getline(act_ifs, act_line)) {

      if (obs_line == "") break;

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

      ObservationAction observation_action;
      observation_action.ObservationEntry = obs_data;
      observation_action.ActionEntry = act_data;

      observation_action_entries.push_back(observation_action);
  }

  time_t start_time = time(NULL);
  time_t last_time  = time(NULL);
  float last_score = 0;
  while (++current_epoch < EPOCHS_COUNT) {

      vector<ObservationAction>::iterator observation_action_itr = observation_action_entries.begin();
      for (; observation_action_itr != observation_action_entries.end(); observation_action_itr++) {
          ObservationAction observation_action = (ObservationAction)*observation_action_itr;
          Action action = mlp->Process(observation_action.ObservationEntry, observation_action.ActionEntry);
      }

      float current_ml_score = meter->value()[0];
      if (start_ml_score == 0) {
          start_ml_score = current_ml_score;
      }
      std::cout << "Epoch: " << current_epoch << " Mean Squared Error: " << current_ml_score
          << std::endl;

      float target_score_difference = current_ml_score - target_score;
      float last_score_difference = last_score - current_ml_score;
      if (last_score == 0) last_score_difference = current_ml_score;
      float score_jumps_needed = target_score_difference / last_score_difference;
      time_t current_time = time(NULL);
      double seconds = difftime(current_time, last_time);
      seconds = seconds * score_jumps_needed;
      int hour = seconds / 3600;
      int min = (seconds - hour * 3600) / 60;
      int sec = seconds - hour * 3600 - min * 60;
      std::cout << "Time Remaining: " << hour << ":" << min << ":" << sec
          << std::endl << std::endl;

      float total_difference = start_ml_score - current_ml_score;
      score_jumps_needed = target_score_difference / total_difference;
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
      if (current_ml_score < best_ml_score && current_epoch % 1000 == 0)
      {
          best_ml_score = current_ml_score;
          mlp->Save("Models/latest_model");
      }
      if (current_ml_score < target_score) {
          mlp->Save("Models/latest_model");
          break;
      }
      meter->reset();

  }
#endif

  //enter the message loop
  bool bDone = false; 

  //mTickCount = 0;

#ifdef CLIENT_MODE
  std::ifstream ifs("match.json");// , std::ios::in | std::ios::binary | std::ios::ate);
  std::string content;// ((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
  ifs >> content;
  json data = json::parse(content);
  //std::vector<json>::const_iterator it = g_MatchReplay->Snapshots().begin();
  json::const_iterator it = data["scrnsnaps"].begin();
  for (it; it != data["scrnsnaps"].end(); ++it)
#else
  while(!bDone)
#endif // LIVE_MODE
  {
      while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
      {
          if (msg.message == WM_QUIT)
          {
              // Stop loop if it's a quit message
              bDone = true;
          }

          else
          {
              TranslateMessage(&msg);
              DispatchMessage(&msg);
          }
      }

      while (Prm.FrameRate != 0 && !timer.ReadyForNextFrame() && msg.message != WM_QUIT)
      {
          Sleep(1);
      }
      //update game states
#ifdef CLIENT_MODE
      IncrementTime(SNAPSHOT_RATE);
      g_LastSnapshot = (*it);
#else
      //Don't render every step.
      int steps = 0;
      while (!g_PitchManager->Finished() && steps++ < RENDERING_RATE)
      {
          if (!g_singleStepEnabled || g_stepType == STEP || g_stepType == STEP_NO_SAVE_OBSERVATION) {
            g_PitchManager->Step();
            g_stepType = NO_STEP;
            g_updateConsole = true;
          }
      }
#endif // LIVE_MODE

      //render 
      RedrawWindow(hWnd, true);

  }//end while

  json raw_data = g_PitchManager->MatchReplay()->Snapshots();
  std::ofstream o("match_client.json");
  o << std::setw(4) << raw_data.dump() << std::endl;

  delete g_PitchManager;

  UnregisterClass( g_szWindowClassName, winclass.hInstance );

  return msg.wParam;
}

#endif
#endif
