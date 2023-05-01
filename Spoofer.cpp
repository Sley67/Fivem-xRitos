#include "Common.hpp"

#include <vector>
#include <algorithm>
#include <iostream>
#include <locale>
#include <codecvt>
#include <stdio.h>
#include <windows.h>
#include <Mmsystem.h>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <Psapi.h>
#include <timeapi.h>
#include <time.h>
#include "UI/UIManager.hpp"

std::string sp1 = "previousBomuldho";

std::string Playername = "Bomulddddddddddd"; //Bomulddddddddddd


namespace Big
{
	std::string pdPath = "C:\\Viper\\Configs\\Detection.ini";
	std::string logPoint = "Players";
	std::string logPointt = "Players";
	
	std::string p1 = ReadStringFromIni(pdPath, logPoint, "Player1");
	std::string p2 = ReadStringFromIni(pdPath, logPoint, "Player2");
	std::string p3 = ReadStringFromIni(pdPath, logPoint, "Player3");
	std::string p4 = ReadStringFromIni(pdPath, logPoint, "Player4");
	std::string p5 = ReadStringFromIni(pdPath, logPoint, "Player5");

	std::string v1 = ReadStringFromIni(pdPath, logPointt, "Vehicle1");
	std::string v2 = ReadStringFromIni(pdPath, logPointt, "Vehicle2");
	std::string v3 = ReadStringFromIni(pdPath, logPointt, "Vehicle3");
	std::string v4 = ReadStringFromIni(pdPath, logPointt, "Vehicle4");
	std::string v5 = ReadStringFromIni(pdPath, logPointt, "Vehicle5");

	bool Crash = false;
	bool antiAFK;
	bool chatBypass;
	bool restricted;
	bool sessionInfo;
	bool PlayerInfo = true;
	bool serverScanner = false;
	bool NightClubMoney = false;
	
	bool notify = false;
	bool kick;
	bool crash;
	bool joinNotify = false;
	bool lockLobby;
	bool Remembertoputthisboolinaninifiletocheckifweshouldnotifythisvalue = false;
	bool blacklistopmk2;

	bool InfiniteLoading;
	bool antiKick;
	bool antitransaction_error;
	bool antiCeoKick;
	bool antiCEOban;
	bool antiSsend_player_to_job;
	bool antiPassive;
	bool antiAntismth;
	NativeVector3 coordsOf(Entity entity)
	{
		return ENTITY::GET_ENTITY_COORDS(entity, 1);
	}


	bool exMe;
	bool exFriends;
	bool exIniPlayers;
	
	enum RemoteEvents
	{

		SoundSpam1andtext = 1097312011,
		SpundSpam2 = -1162153263,


		FORCE_TO_NEW_SESSION = 150902083,

		Kick_Host_1 = -1462751325,
		Kick_Host_2 = 900146065,

		CEO_Kick = -1648921703,
		CEO_BAN = -738295409,

		lll1 = -125325620,
		lll2 = 2017074594,

		SEND_NOTIFICATION_MESSAGES = 564131320,

		TRANSACTION_FAIL = 3413717565,

		GTA_BANNER_EFFECT = 2422236493,

		REMOVE_WANTED_LEVEL = 301606138,

		Kick_FROM_CAR = 4164637196,

		RESET_CAM = 589125870,

		SET_BOUNTY = 544453591,

		REMOTE_OFF_RADAR = 2931916346,
		REMOTE_COPS_BLIND_EYE = -336686044,
		CEO_10K_MONEY = 3693313620,
		DESTROY_PERSONAL_VEHICLE = 150902083,

		TP_TO_APARTMENTS = 3041711092,

		SEND_TO_JOB = -545396442,
		SEND_TO_JOB2_TEXT = 2017074594,


	};

	bool exclude(int pl)
	{
		bool frnd;
		if (exMe && PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(pl) == PLAYER::PLAYER_PED_ID())
		{
			return false;
		}
		if (exFriends && isPlayerFriend(pl, frnd) && frnd)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	void SendToJob()
	{

		DWORD64 args[10] = { SEND_TO_JOB, g_SelectedPlayer,  0, 0, 0, 4, 1, 1, 0 };
		SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, 10, 1 << g_SelectedPlayer);

	}
	void CEOKick()
	{

		DWORD64 args[4] = { CEO_Kick, g_SelectedPlayer, 0, 5 };
		SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, 4, 1 << g_SelectedPlayer);

	}
	void CEOBan()
	{

		DWORD64 args[3] = { CEO_BAN, g_SelectedPlayer, 1 };
		SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, 3, 1 << g_SelectedPlayer);
	}
	void DoSoundSpam()
	{
		DWORD64 args[3] = { SoundSpam1andtext, g_SelectedPlayer, 7 };
		SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, 3, 1 << g_SelectedPlayer);

		DWORD64 argsd[3] = { SpundSpam2, g_SelectedPlayer, 7 };
		SCRIPT::TRIGGER_SCRIPT_EVENT(1, argsd, 3, 1 << g_SelectedPlayer);
	}
	void sendFaceCameraForward()
	{
		DWORD64 args[4] = { RESET_CAM, g_SelectedPlayer, -1859848501, 0 };
		SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, 4, 1 << g_SelectedPlayer);
	}
	void VehKick()
	{

		DWORD64 args[2] = { Kick_FROM_CAR, 0 };
		SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, 2, 1 << g_SelectedPlayer);
	}
	void cagePlayer(Ped ped)
	{
		NativeVector3 remotePos = ENTITY::GET_ENTITY_COORDS(ped, 0);
		OBJECT::CREATE_OBJECT(959275690, remotePos.x, remotePos.y, remotePos.z - 1.f, true, false, false);
	}

	void airStrikePlayer(Ped player) {
		NativeVector3 StrikeCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), 1);
		StrikeCoords.z += 15;
		g_CallbackScript->AddCallback<AssetCallback>((MISC::GET_HASH_KEY("VEHICLE_WEAPON_SPACE_ROCKET")), [=] {
			MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(StrikeCoords.x, StrikeCoords.y, StrikeCoords.z + 35, StrikeCoords.x, StrikeCoords.y, StrikeCoords.z, 250, 1, MISC::GET_HASH_KEY("VEHICLE_WEAPON_SPACE_ROCKET"), PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), 1, 1, 500);
			MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(StrikeCoords.x, StrikeCoords.y, StrikeCoords.z + 30, StrikeCoords.x, StrikeCoords.y, StrikeCoords.z, 250, 0, MISC::GET_HASH_KEY("VEHICLE_WEAPON_SPACE_ROCKET"), 0, 1, 1, 500);
			MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(StrikeCoords.x, StrikeCoords.y, StrikeCoords.z + 55, StrikeCoords.x, StrikeCoords.y, StrikeCoords.z, 100, false, 0xF8A3939F, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), true, true, 600);
		});
	}

	void ceo_kek()
	{
		uint64_t re[4] = { -738295409, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 0, 0 };
		SCRIPT::TRIGGER_SCRIPT_EVENT(1, re, 4, 1 << g_SelectedPlayer);
	}

	void kick_to_new_lobby(int player)
	{
		Hash kickHashes[] = { -1169499038,
2068861029, 1770262894, 2102749046, -452918768, 1979460190, -1766754442, 121406262, -1256990787, -1233539946, 1302710489, -1715498868, 997710829, -203021367, -290471766, 1310884765, -394638198,
-1881241035, 938997823, -744392447, -560772508, -1775205375, -1185346884, -92797437, 1673605511, 470431182, 150164177, -601653676, -1294585740, 1421531240, 1776174799, 472658729, 424346598,
-726819886, 236292243, -1758138102, 1199507682, 969472089, -1970545882, -1334698325, 1331611678, 1706248285, 992790930, 142887261, 285918879, -1712801863, -1595454678, -1014227710, -25668159,

		};
		for (int i = 0; i < 49; i++) {
			uint64_t kick[4] = { -1252906024,  player, 0, 0 };
			SCRIPT::TRIGGER_SCRIPT_EVENT(1, kick, 4, 1 << player);
		}
	}

	void netwUpdateLoop()
	{
		if (NightClubMoney)
		{
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLUB_PAY_TIME_LEFT"), -1, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLUB_POPULARITY"), 1000, true);
		}
		if (antiAFK)
		{
			globalHandle(262145).At(90).As<int>() = INT_MAX;
			globalHandle(262145).At(87).As<int>() = INT_MAX;
			globalHandle(262145).At(88).As<int>() = INT_MAX;
			globalHandle(262145).At(89).As<int>() = INT_MAX;
		}

		if (otr)
		{
			globalHandle(2425662).At(PLAYER::PLAYER_ID(), 421).At(200).As<int>() = 1;
			globalHandle(2439138).At(70).As<int>() = NETWORK::GET_NETWORK_TIME();
		}

		if (chatBypass)
		{
			NETWORK::NETWORK_OVERRIDE_RECEIVE_RESTRICTIONS(PLAYER::PLAYER_PED_ID(), true);
			NETWORK::NETWORK_OVERRIDE_CHAT_RESTRICTIONS(PLAYER::PLAYER_PED_ID(), true);
		}

		if (restricted)
		{
			PLAYER::_EXPAND_WORLD_LIMITS(50000.0, 50000.0, 50.0);
			PLAYER::_EXPAND_WORLD_LIMITS(-50000.0, -50000.0, 50.0);

			MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("am_armybase");
			MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("restrictedareas");
			MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("re_armybase");
			MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("re_lossantosintl");
			MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("re_prison");
			MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("re_prisonvanbreak");
			MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("am_doors");
		}
		if (serverScanner)
		{
			for (std::uint32_t i = 0; i < 32; ++i)
			{
				if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))) 
				{
					Ped playerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
					Vehicle selectedlPlayerveh = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);
					Hash hashvehmodel = ENTITY::GET_ENTITY_MODEL(selectedlPlayerveh);
					auto Plyername = PLAYER::GET_PLAYER_NAME(i);

					if (p1 == PLAYER::GET_PLAYER_NAME(i))
					{
						if (notify)
						{
							std::string one = p1;
							std::string two = " has been detected in your session";
							std::string niggaDetect = one + two;

							const char* a = StringToChar(niggaDetect);
                 
							IconNotification((char*)a, (char*)"Viper Protections", (char*)"Player Detection");
						}
						if (kick)
						{
							if (PLAYER::GET_PLAYER_NAME(g_SelectedPlayer) == p1)
							{
								kick_to_new_lobby(g_SelectedPlayer);
							}
						}
						if (crash)
						{
							if (PLAYER::GET_PLAYER_NAME(g_SelectedPlayer) == p1)
							{
								Player nigga = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
								STREAMING::REQUEST_MODEL(0x856cfb02);
								while (!STREAMING::HAS_MODEL_LOADED(0x856cfb02)) SYSTEM::WAIT(0);
								NativeVector3 fposition = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(nigga, 0.0, 5.0, 0.0);
								PED::CREATE_PED(1, 0x856cfb02, fposition.x, fposition.y, fposition.z, ENTITY::GET_ENTITY_HEADING(nigga), TRUE, TRUE);
							}	
						}
					}
					if (p2 == PLAYER::GET_PLAYER_NAME(i))
					{
						if (notify)
						{
							std::string one = p2;
							std::string two = " has been detected in your session";
							std::string niggaDetect = one + two;

							const char* a = StringToChar(niggaDetect);

							IconNotification((char*)a, (char*)"Viper Protections", (char*)"Player Detection");
						}
						if (kick)
						{
							if (PLAYER::GET_PLAYER_NAME(g_SelectedPlayer) == p2)
							{
								kick_to_new_lobby(g_SelectedPlayer);
							}
						}
						if (crash)
						{
							if (PLAYER::GET_PLAYER_NAME(g_SelectedPlayer) == p2)
							{
								Player nigga = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
								STREAMING::REQUEST_MODEL(0x856cfb02);
								while (!STREAMING::HAS_MODEL_LOADED(0x856cfb02)) SYSTEM::WAIT(0);
								NativeVector3 fposition = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(nigga, 0.0, 5.0, 0.0);
								PED::CREATE_PED(1, 0x856cfb02, fposition.x, fposition.y, fposition.z, ENTITY::GET_ENTITY_HEADING(nigga), TRUE, TRUE);
							}
						}
					}
					if (p3 == PLAYER::GET_PLAYER_NAME(i))
					{
						if (notify)
						{
							std::string one = p3;
							std::string two = " has been detected in your session";
							std::string niggaDetect = one + two;

							const char* a = StringToChar(niggaDetect);

							IconNotification((char*)a, (char*)"Viper Protections", (char*)"Player Detection");
						}
						if (kick)
						{
							if (PLAYER::GET_PLAYER_NAME(g_SelectedPlayer) == p3)
							{
								kick_to_new_lobby(g_SelectedPlayer);
							}
						}
						if (crash)
						{
							if (PLAYER::GET_PLAYER_NAME(g_SelectedPlayer) == p3)
							{
								Player nigga = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
								STREAMING::REQUEST_MODEL(0x856cfb02);
								while (!STREAMING::HAS_MODEL_LOADED(0x856cfb02)) SYSTEM::WAIT(0);
								NativeVector3 fposition = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(nigga, 0.0, 5.0, 0.0);
								PED::CREATE_PED(1, 0x856cfb02, fposition.x, fposition.y, fposition.z, ENTITY::GET_ENTITY_HEADING(nigga), TRUE, TRUE);
							}
						}
					}
					if (p4 == PLAYER::GET_PLAYER_NAME(i))
					{
						if (notify)
						{
							std::string one = p4;
							std::string two = " has been detected in your session";
							std::string niggaDetect = one + two;

							const char* a = StringToChar(niggaDetect);

							IconNotification((char*)a, (char*)"Viper Protections", (char*)"Player Detection");
						}
						if (kick)
						{
							if (PLAYER::GET_PLAYER_NAME(g_SelectedPlayer) == p4)
							{
								kick_to_new_lobby(g_SelectedPlayer);
							}
						}
						if (crash)
						{
							if (PLAYER::GET_PLAYER_NAME(g_SelectedPlayer) == p4)
							{
								Player nigga = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
								STREAMING::REQUEST_MODEL(0x856cfb02);
								while (!STREAMING::HAS_MODEL_LOADED(0x856cfb02)) SYSTEM::WAIT(0);
								NativeVector3 fposition = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(nigga, 0.0, 5.0, 0.0);
								PED::CREATE_PED(1, 0x856cfb02, fposition.x, fposition.y, fposition.z, ENTITY::GET_ENTITY_HEADING(nigga), TRUE, TRUE);
							}
						}
					}
					if (p5 == PLAYER::GET_PLAYER_NAME(i))
					{
						if (notify)
						{
							std::string one = p5;
							std::string two = " has been detected in your session";
							std::string niggaDetect = one + two;

							const char* a = StringToChar(niggaDetect);

							IconNotification((char*)a, (char*)"Viper Protections", (char*)"Player Detection");
						}
						if (kick)
						{
							if (PLAYER::GET_PLAYER_NAME(g_SelectedPlayer) == p5)
							{
								kick_to_new_lobby(g_SelectedPlayer);
							}
						}
						if (crash)
						{
							if (PLAYER::GET_PLAYER_NAME(g_SelectedPlayer) == p5)
							{
								Player nigga = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
								STREAMING::REQUEST_MODEL(0x856cfb02);
								while (!STREAMING::HAS_MODEL_LOADED(0x856cfb02)) SYSTEM::WAIT(0);
								NativeVector3 fposition = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(nigga, 0.0, 5.0, 0.0);
								PED::CREATE_PED(1, 0x856cfb02, fposition.x, fposition.y, fposition.z, ENTITY::GET_ENTITY_HEADING(nigga), TRUE, TRUE);
							}
						}
					}

					if (joinNotify)
					{


						if (!NETWORK::NETWORK_IS_PLAYER_CONNECTED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i)) && ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i)))
						{
							std::string iName = PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID());
							std::string pName = PLAYER::GET_PLAYER_NAME(i);
							if (pName == ("**Invalid**"))
							{

							}
							else if (pName == iName)
							{

							}
							else
							{
								std::string msg = " is joining your session";
								std::string niggaDetecc = pName + msg;
								const char* uwu = StringToChar(niggaDetecc);
								IconNotification((char*)uwu, (char*)"Viper Protections", (char*)"Player Joining"), PLAYER::GET_PLAYER_NAME(i);
							}
						}

						if (auto gay = NETWORK::NETWORK_JOIN_TRANSITION(i))
						{
							std::string pName = PLAYER::GET_PLAYER_NAME(gay);
							std::string msg = " is joining your session";
							std::string niggaDetecc = pName + msg;
							const char* uwu = StringToChar(niggaDetecc);
							IconNotification((char*)uwu, (char*)"Viper Protections", (char*)"Player Joining");
						}
					}
					
					if (blacklistopmk2)
					{
						if (exclude(i))
						{
							if (hashvehmodel == $("Adder"))
							{
								const char* vehname = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(hashvehmodel);
								std::string name_veh = HUD::_GET_LABEL_TEXT(vehname);
								std::string pName = PLAYER::GET_PLAYER_NAME(i);
								BRAIN::CLEAR_PED_TASKS_IMMEDIATELY(playerPed);
								BRAIN::CLEAR_PED_TASKS(playerPed);
								BRAIN::CLEAR_PED_SECONDARY_TASK(playerPed);

								std::string re = "Vehicle: ";
								std::string ree = "\nStatus: Blocked\nPlayer: ";
								std::string bmsg = re + vehname + ree + pName;

								char* omglollmao = StringToChar(bmsg);

								IconNotification((char*)omglollmao, (char*)"Viper Protections", (char*)"Vehicle Detection");
							}

							if (hashvehmodel == $(v2))
							{
								const char* vehname = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(hashvehmodel);
								std::string name_veh = HUD::_GET_LABEL_TEXT(vehname);
								std::string pName = PLAYER::GET_PLAYER_NAME(i);
								BRAIN::CLEAR_PED_TASKS_IMMEDIATELY(playerPed);
								BRAIN::CLEAR_PED_TASKS(playerPed);
								BRAIN::CLEAR_PED_SECONDARY_TASK(playerPed);

								std::string re = "Vehicle: ";
								std::string ree = "\nStatus: Blocked\nPlayer: ";
								std::string bmsg = re + vehname + ree + pName;

								char* omglollmao = StringToChar(bmsg);

								IconNotification((char*)omglollmao, (char*)"Viper Protections", (char*)"Vehicle Detection");
							}

							if (hashvehmodel == $(v3))
							{
								const char* vehname = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(hashvehmodel);
								std::string name_veh = HUD::_GET_LABEL_TEXT(vehname);
								std::string pName = PLAYER::GET_PLAYER_NAME(i);
								BRAIN::CLEAR_PED_TASKS_IMMEDIATELY(playerPed);
								BRAIN::CLEAR_PED_TASKS(playerPed);
								BRAIN::CLEAR_PED_SECONDARY_TASK(playerPed);

								std::string re = "Vehicle: ";
								std::string ree = "\nStatus: Blocked\nPlayer: ";
								std::string bmsg = re + vehname + ree + pName;

								char* omglollmao = StringToChar(bmsg);

								IconNotification((char*)omglollmao, (char*)"Viper Protections", (char*)"Vehicle Detection");
							}

							if (hashvehmodel == $(v4))
							{
								const char* vehname = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(hashvehmodel);
								std::string name_veh = HUD::_GET_LABEL_TEXT(vehname);
								std::string pName = PLAYER::GET_PLAYER_NAME(i);
								BRAIN::CLEAR_PED_TASKS_IMMEDIATELY(playerPed);
								BRAIN::CLEAR_PED_TASKS(playerPed);
								BRAIN::CLEAR_PED_SECONDARY_TASK(playerPed);

								std::string re = "Vehicle: ";
								std::string ree = "\nStatus: Blocked\nPlayer: ";
								std::string bmsg = re + vehname + ree + pName;

								char* omglollmao = StringToChar(bmsg);

								IconNotification((char*)omglollmao, (char*)"Viper Protections", (char*)"Vehicle Detection");
							}

							if (hashvehmodel == $(v5))
							{
								const char* vehname = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(hashvehmodel);
								std::string name_veh = HUD::_GET_LABEL_TEXT(vehname);
								std::string pName = PLAYER::GET_PLAYER_NAME(i);
								BRAIN::CLEAR_PED_TASKS_IMMEDIATELY(playerPed);
								BRAIN::CLEAR_PED_TASKS(playerPed);
								BRAIN::CLEAR_PED_SECONDARY_TASK(playerPed);

								std::string re = "Vehicle: ";
								std::string ree = "\nStatus: Blocked\nPlayer: ";
								std::string bmsg = re + vehname + ree + pName;

								char* omglollmao = StringToChar(bmsg);

								IconNotification((char*)omglollmao, (char*)"Viper Protections", (char*)"Vehicle Detection");
							}
						}
					}
				}
			}
		}



		if (lockLobby)
		{
			NETWORK::NETWORK_SESSION_BLOCK_JOIN_REQUESTS(true);
			NETWORK::NETWORK_SESSION_CANCEL_INVITE();
		}

		if (Crash == true)
		{
			

			auto LocalPlayer = PLAYER::GET_PLAYER_INDEX();
			auto LocalPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(LocalPlayer);

			auto PlayerNetId = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(LocalPed);


			while (NETWORK::NETWORK_HAS_CONTROL_OF_NETWORK_ID(PlayerNetId))
			{
				NETWORK::NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(PlayerNetId);
			}

			NETWORK::_SET_NETWORK_ID_SYNC_TO_PLAYER(PlayerNetId, LocalPlayer, true);

		}

		
	
	}


	Object* Crashobjects;
	void instantCrash()
	{
		Player nigga = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
		STREAMING::REQUEST_MODEL(0x856cfb02);
		while (!STREAMING::HAS_MODEL_LOADED(0x856cfb02)) SYSTEM::WAIT(0);
		NativeVector3 fposition = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(nigga, 0.0, 5.0, 0.0);
		PED::CREATE_PED(1, 0x856cfb02, fposition.x, fposition.y, fposition.z, ENTITY::GET_ENTITY_HEADING(nigga), TRUE, TRUE);
	}

	void dupeCar(int player)
	{
		Vehicle pedVeh = NULL;
		Ped playerPed = PLAYER::PLAYER_PED_ID();
		if (PED::IS_PED_IN_ANY_VEHICLE(player, 0))
		{
			pedVeh = PED::GET_VEHICLE_PED_IS_IN(player, 0);
			if (ENTITY::DOES_ENTITY_EXIST(pedVeh))
			{
				Hash vehicleModelHash = ENTITY::GET_ENTITY_MODEL(pedVeh);
				g_CallbackScript->AddCallback<ModelCallback>(vehicleModelHash, [vehicleModelHash, playerPed, pedVeh]
					{
						NativeVector3 playerPosition = ENTITY::GET_ENTITY_COORDS(playerPed, FALSE);
						Vehicle playerVeh = VEHICLE::CREATE_VEHICLE(vehicleModelHash, playerPosition.x, playerPosition.y, playerPosition.z, ENTITY::GET_ENTITY_HEADING(playerPed), true, false, 0);
						PED::SET_PED_INTO_VEHICLE(playerPed, playerVeh, -1);
						int primaryColor, secondaryColor;
						VEHICLE::GET_VEHICLE_COLOURS(pedVeh, &primaryColor, &secondaryColor);
						VEHICLE::SET_VEHICLE_COLOURS(playerVeh, primaryColor, secondaryColor);
						if (VEHICLE::GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(pedVeh))
						{
							int r, g, b;
							VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(pedVeh, &r, &g, &b);
							VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(playerVeh, r, g, b);
						}
						if (VEHICLE::GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(pedVeh))
						{
							int r, g, b;
							VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(pedVeh, &r, &g, &b);
							VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(playerVeh, r, g, b);
						}
						if (VEHICLE::IS_THIS_MODEL_A_CAR(vehicleModelHash) || VEHICLE::IS_THIS_MODEL_A_BIKE(vehicleModelHash))
						{
							VEHICLE::SET_VEHICLE_MOD_KIT(playerVeh, 0);
							VEHICLE::SET_VEHICLE_WHEEL_TYPE(playerVeh, VEHICLE::GET_VEHICLE_WHEEL_TYPE(pedVeh));
							for (int i = 0; i <= 24; i++)
							{
								if (i > 16 && i < 23)
									VEHICLE::TOGGLE_VEHICLE_MOD(playerVeh, i, VEHICLE::IS_TOGGLE_MOD_ON(pedVeh, i));
								else
									VEHICLE::SET_VEHICLE_MOD(playerVeh, i, VEHICLE::GET_VEHICLE_MOD(pedVeh, i), VEHICLE::GET_VEHICLE_MOD_VARIATION(pedVeh, i));
							}
							int tireSmokeColor[3], pearlescentColor, wheelColor;
							VEHICLE::GET_VEHICLE_TYRE_SMOKE_COLOR(pedVeh, &tireSmokeColor[0], &tireSmokeColor[1], &tireSmokeColor[2]);
							VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(playerVeh, tireSmokeColor[0], tireSmokeColor[1], tireSmokeColor[2]);
							VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(playerVeh, VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(pedVeh));
							VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(playerVeh, TEST::GET_VEHICLE_NUMBER_PLATE_TEXT(pedVeh));
							VEHICLE::GET_VEHICLE_EXTRA_COLOURS(pedVeh, &pearlescentColor, &wheelColor);
							VEHICLE::SET_VEHICLE_EXTRA_COLOURS(playerVeh, pearlescentColor, wheelColor);
							if (VEHICLE::IS_VEHICLE_A_CONVERTIBLE(pedVeh, 0))
							{
								int convertableState = VEHICLE::GET_CONVERTIBLE_ROOF_STATE(pedVeh);
								if (convertableState == 0 || convertableState == 3 || convertableState == 5)
									VEHICLE::RAISE_CONVERTIBLE_ROOF(playerVeh, 1);
								else
									VEHICLE::LOWER_CONVERTIBLE_ROOF(playerVeh, 1);
							}
							for (int i = 0; i <= 3; i++)
							{
								VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(playerVeh, i, VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(pedVeh, i));
							}
							for (int i = 0; i <= 11; i++)
							{
								if (VEHICLE::DOES_EXTRA_EXIST(pedVeh, i))
									VEHICLE::SET_VEHICLE_EXTRA(playerVeh, i, !VEHICLE::IS_VEHICLE_EXTRA_TURNED_ON(pedVeh, i));
							}
							if ((VEHICLE::GET_VEHICLE_LIVERY_COUNT(pedVeh) > 1) && VEHICLE::GET_VEHICLE_LIVERY(pedVeh) >= 0)
							{
								VEHICLE::SET_VEHICLE_LIVERY(playerVeh, VEHICLE::GET_VEHICLE_LIVERY(pedVeh));
							}
							int neonColor[3];
							VEHICLE::_GET_VEHICLE_NEON_LIGHTS_COLOUR(pedVeh, &neonColor[0], &neonColor[1], &neonColor[2]);
							VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(playerVeh, neonColor[0], neonColor[1], neonColor[2]);
							VEHICLE::SET_VEHICLE_WINDOW_TINT(playerVeh, VEHICLE::GET_VEHICLE_WINDOW_TINT(pedVeh));
							VEHICLE::SET_VEHICLE_DIRT_LEVEL(playerVeh, VEHICLE::GET_VEHICLE_DIRT_LEVEL(pedVeh));
						}
						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(vehicleModelHash);
				});
			}
		}
		else
		{
			
		}

	}
	int dAmount = 2500;
	int dDelay = 100;
	bool dEnable;

	Hash emodel4 = 0xF9AFB48F;

	Hash modelDrop(int id)
	{
		switch (id)
		{
		case 0: return -1666779307; break;
		case 1: return MISC::GET_HASH_KEY("prop_xmas_tree_int"); break;
		case 2: return MISC::GET_HASH_KEY("prop_alien_egg_01"); break;
		case 3: return MISC::GET_HASH_KEY("prop_cs_dildo_01"); break;
		case 4: return MISC::GET_HASH_KEY("prop_ld_int_safe_01"); break;
		case 5: return MISC::GET_HASH_KEY("prop_med_bag_01"); break;
		case 6: return MISC::GET_HASH_KEY("prop_gun_case_01"); break;
		case 7: return MISC::GET_HASH_KEY("prop_acc_guitar_01"); break;
		case 8: return MISC::GET_HASH_KEY("prop_golf_bag_01");; break;
		case 9: return MISC::GET_HASH_KEY("vw_prop_vw_colle_alien");; break;
		case 10: return 0x113FD533; break;
		}
	}

	int t = 0;
	int dHeight = 0;
	int dx, dy, dz = 0;


	Hash modelDropG(int id)
	{
		switch (id)
		{
		case 0: return 0xCE6FDD6B; break;
		case 1: return 0x2C014CA6; break;
		}
	}

	void moneyDrop(bool enable, int amount, int droptype, int delay, int xPlus, int yPlus, int zPlus, int Height, Hash model)
	{
		if (enable)
		{
			Ped playerped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
			if (!ENTITY::DOES_ENTITY_EXIST(playerped)) return;
			if ((timeGetTime() - t) > delay)
			{
				g_CallbackScript->AddCallback<ModelCallback>(modelDrop(droptype), [=] {
					NativeVector3 playerPosition = wc.GetPos(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer));
					OBJECT::CREATE_AMBIENT_PICKUP(modelDropG(typePos), playerPosition.x + xPlus, playerPosition.y + yPlus, playerPosition.z + zPlus, Height, amount, modelDrop(droptype), FALSE, TRUE);
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(modelDrop(droptype));
				});
				t = timeGetTime();
			}

		}
	}
}









