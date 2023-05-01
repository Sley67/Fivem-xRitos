#include "MainScript.hpp"
#include "ScriptCallback.hpp"
#include "Lists.hpp"
#include "Natives.hpp"
#include "Timer.hpp"
#include "Translation.hpp"
#include "CustomText.hpp"
#include "UI/UIManager.hpp"
#include "UI/BoolOption.hpp"
#include "UI/ChooseOption.hpp"
#include "UI/NumberOption.hpp"
#include "UI/RegularOption.hpp"
#include "UI/SubOption.hpp"
#include "UI/RegularSubmenu.hpp"
#include "UI/PlayerSubmenu.hpp"
#include "Enum.h"
#include "TIck.h"
#include "Loader.h"
#include "Network.h"
#include "network stuff.h"	
#include "Fibers.hpp"


bool bUnkerMoney;



namespace Big
{
	bool god = true;
	void SendToJob();
	void CEOKick();
	void CEOBan();
	void CEOBan();
	void DoSoundSpam();
	void sendFaceCameraForward();
	void VehKick();
	int vehicleNumber;

	enum Submenu : std::uint32_t
	{
		SubmenuHome,
		SubmenuSettings,
		SubmenuSettingsHeader,
		SubmenuSettingsHeaderStaticBackground,
		SubmenuSettingsHeaderGradientBackground,
		SubmenuSettingsHeaderText,
		SubmenuSettingsSubmenuBar,
		SubmenuSettingsOption,
		SubmenuSettingsFooter,
		SubmenuSettingsDescription,
		SubmenuSettingsInput,
		SubmenuSettingsLanguage,
		SubmenuSelectedPlayer,
		SubmenuPlayerList,
		SubmenuTest,
		Local,
		Playerr,
		Onlinee,
		protections,
		Rec,
		PM,
		selectedPed,
		allPlayers,
		database,
		PD,
		PB,
		exxxx,
		OC,
		VH,
		tpl,
		cf,
		LO,
		Weaponn,
		Vehiclee,
		spawner,
		Bodyguardss,
		Teleportt,
		Worldd,
		Miscellaneouss,
		Super,
		fv,
		Sports,
		SportClassic,
		Offroad,
		Sedans,
		Coupes,
		Muscle,
		Utility,
		Commercial,
		Compacts,
		SUV,
		Cycles,
		Motorcycles,
		Helicopters,
		Planes,
		Emergency,
		Industrial,
		Trailer,
		Trains,
		Service,
		Boats,
		Military,
		Loaderr,
		TPMenu,
		TPLSC,
		TPOVehicle,
		TPSports,
		TPStores,
		TPAir,
		TPFun,
		TPServices,
		TPAparts,
		tp,
		AmbientFemale,
		AmbientMale,
		Cutscene,
		GangFemale,
		GangMale,
		Story,
		Multiplayer,
		ScenarioFemale,
		ScenarioMale,
		StoryScenarioFemale,
		StoryScenarioMale_,
		Models,
		Timeee,
		WorldSpeed_,
		Weather,
		keysHot,
		CasinoH,
		VehicleOptions,
		RIDOptions,
		RIDManager,
		VehicleManagerSub,
		VehicleManagerDelete,
		pDrop,
		scriptNigga
	};

	bool IsKeyboardActive;

	bool MainScript::IsInitialized()
	{
		return m_Initialized;
	}

	ScriptType MainScript::GetType()
	{
		return ScriptType::Game;
	}


	int Time_h, Time_m, Time_s;
	void TIMEBACK(int TIME, int MAX)
	{
		if (TIME == MAX)
			TIME = 1;
	}

	void MainScript::Initialize()
	{
		m_Initialized = true;
		using namespace UserInterface;

		g_CustomText->AddText(CONSTEXPR_JOAAT("HUD_JOINING"), "Isn't " BIGBASE_NAME " the fucking best?");
		g_CustomText->AddText(CONSTEXPR_JOAAT("HUD_TRANSP"), "Isn't " BIGBASE_NAME " the fucking best?");

		Setup();

		if (FileExists("C:\\Viper\\Configs\\MenuConfig.ini"))
		{
			CurrentConfig();
		}
		else
		{
			FirstConfig();
		}

		
	    _mkdir("C:\\Viper\\Manager");
		_mkdir("C:\\Viper\\Manager\\RIDManager");

		g_UiManager->AddSubmenu<RegularSubmenu>("Home", SubmenuHome, [](RegularSubmenu* sub)
		{
			sub->AddOption<SubOption>("Player", nullptr, Playerr);
			sub->AddOption<SubOption>("Online", nullptr, Onlinee);	
			sub->AddOption<SubOption>("Weapon", nullptr, Weaponn);
			sub->AddOption<SubOption>("Vehicle", nullptr, Vehiclee);
			sub->AddOption<SubOption>("Teleport", nullptr, Teleportt);
			sub->AddOption<SubOption>("World", nullptr, Worldd);
			sub->AddOption<SubOption>("Settings", nullptr, SubmenuSettings);
			sub->AddOption<SubOption>("Loader", nullptr, Loaderr);
		});

		/* MAIN MENU */

		g_UiManager->AddSubmenu<RegularSubmenu>("Player", Playerr, [](RegularSubmenu* sub)
		{
			sub->AddOption<BoolOption<bool>>("Invincible", nullptr, &godmodee, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Never Wanted", nullptr, &NeverWanted, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("No Ragdoll", nullptr, &NoRagdoll, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Forcefield", nullptr, &ForceField, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Fly", nullptr, &Fly, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Freecam", nullptr, &Freecam, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Super Jump", nullptr, &SuperJump, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("No Clip", nullptr, &yesclip, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Walking No Clip", nullptr, &walkingnoclip, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<RegularOption>("Clean", nullptr, [] { PED::CLEAR_PED_BLOOD_DAMAGE(PLAYER::PLAYER_PED_ID()); });
			sub->AddOption<RegularOption>("Dry", nullptr, [] { PED::CLEAR_PED_WETNESS(PLAYER::PLAYER_PED_ID()); });
			sub->AddOption<RegularOption>("Max Health", nullptr, [] { ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), ENTITY::GET_ENTITY_MAX_HEALTH(PLAYER::PLAYER_PED_ID())); });
			sub->AddOption<RegularOption>("Max Armour", nullptr, [] { PED::SET_PED_ARMOUR(PLAYER::PLAYER_PED_ID(), PLAYER::GET_PLAYER_MAX_ARMOUR(PLAYER::PLAYER_ID())); });
			sub->AddOption<NumberOption<float>>("Walk Speed", nullptr, &fastboi, 0.f, 20.f, 0.1f, 1, true, "", "", [] {});
			sub->AddOption<NumberOption<float>>("Swim Speed", nullptr, &fastboi2, 0.f, 20.f, 0.1f, 1, true, "", "", [] {});
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Protections", protections, [](RegularSubmenu* sub)
		{
			sub->AddOption<BoolOption<bool>>("Kick", nullptr, &antiKick, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Infinite Loading", nullptr, &InfiniteLoading, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Transaction Error", nullptr, &antitransaction_error, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("CEO Kick", nullptr, &antiCeoKick, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Send To Job", nullptr, &antiSsend_player_to_job, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Passivemode", nullptr, &antiPassive, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Remove Weapons", nullptr, &m_RemoveWeapons, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Clear Ped Tasks", nullptr, &m_ClearPedTasks, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Give Weapons", nullptr, &m_Give_Weapons, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Sound Spam", nullptr, &m_SoundEvent, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Wanted Level", nullptr, &m_WantedLevel, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Explosions", nullptr, &m_Explosions, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Weather", nullptr, &m_Weather, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Time", nullptr, &m_Clock, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Fire", nullptr, &m_Fire, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("PTFX", nullptr, &m_PTFX, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Request Pickup", nullptr, &m_RequestPickup, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Report Myself", nullptr, &m_ReportMyself, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Report Cash Spawn", nullptr, &m_ReportCashSpawn, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Request Control", nullptr, &m_RequestControl, BoolDisplay::OnOff, false, [] {});
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Casino Heist Options", CasinoH, [](RegularSubmenu* sub)
		{
			sub->AddOption<RegularOption>("Continue To Next Board", nullptr, [] { STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_BITSET1"), -1, 1); });
			sub->AddOption<RegularOption>("Skips and helpers", "Info section", [] {});
			sub->AddOption<RegularOption>("Remove Heavy Armoured Gaurds", nullptr, [] { STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_DISRUPTSHIP"), 3, 1); });
			sub->AddOption<RegularOption>("Increase Keycard Level", nullptr, [] { STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_KEYLEVELS"), 2, 1); });
			sub->AddOption<RegularOption>("Best Weapons", nullptr, [] { STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_CREWWEAP"), 5, 1); });
			sub->AddOption<RegularOption>("Best Driver", nullptr, [] { STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_CREWDRIVER"), 5, 1); });
			sub->AddOption<RegularOption>("Best Hacker", nullptr, [] { STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_CREWHACKER"), 5, 1);; });
			sub->AddOption<RegularOption>("Best Heist Vehicles", nullptr, [] { STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_VEHS"), 3, 1); });
			sub->AddOption<RegularOption>("More Heist Weapons", nullptr, [] { STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_WEAPS"), 1, 1); });
			sub->AddOption<RegularOption>("Increase Keycard Level", nullptr, [] { STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_KEYLEVELS"), 2, 1); });
			sub->AddOption<RegularOption>("Continue", nullptr, [] { STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_BITSET0"), -1, 1); });
			sub->AddOption<RegularOption>("Resets", "Info section", [] {});
			sub->AddOption<RegularOption>("~r~Reset Second Board", nullptr, [] { STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_BITSET0"), 0, 1); });
			sub->AddOption<RegularOption>("~r~Reset First Board", nullptr, [] { STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_BITSET1"), -1, 1); });
			sub->AddOption<RegularOption>("Reset Lesters Cooldown", "Info section", [] {});
			sub->AddOption<RegularOption>("ontinue To Next Board", nullptr, [] { STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3_COMPLETEDPOSIX"), -1, 1); });
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("R*ID Options", RIDOptions, [](RegularSubmenu* sub)
		{
			sub->AddOption<RegularOption>("R*ID Join", "", [] {
				g_FiberScript->addTask([] {
					MISC::DISPLAY_ONSCREEN_KEYBOARD(true, (char*)"Input", (char*)"", (char*)"", (char*)"", (char*)"", (char*)"", 20);
					while (MISC::UPDATE_ONSCREEN_KEYBOARD() == 0)
					{
						IsKeyboardActive = true;
						g_UiManager->ResetInput();
						g_FiberScript->Wait(0);
					}
					IsKeyboardActive = false;
					if (!MISC::GET_ONSCREEN_KEYBOARD_RESULT())
						return 0;
					if (MISC::GET_ONSCREEN_KEYBOARD_RESULT() != NULL || MISC::GET_ONSCREEN_KEYBOARD_RESULT() != 0)
					{
						Join = atoi(MISC::GET_ONSCREEN_KEYBOARD_RESULT());
						Joiner = true;
						notifyMap(0, "~w~R*ID attached!");
						notifyMap(0, "~g~Now join anyone from your crew members, and you will be redirected to the R*ID player.");
					}
				});
			});
			sub->AddOption<SubOption>("R*ID Manager", nullptr, RIDManager); //Not done yet
			sub->AddOption<BoolOption<bool>>("Block R* ID Join", nullptr, &lockLobby, BoolDisplay::OnOff, false, [] {});
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Drop Options", pDrop, [](RegularSubmenu* sub)
		{
			sub->AddOption<ChooseOption<const char*, std::size_t>>("Type:", nullptr, &TypeText, &typePos, true);
			sub->AddOption<ChooseOption<const char*, std::size_t>>("Model", nullptr, &money_drop, &money_drop_pos, true);
			sub->AddOption<NumberOption<int>>("Value", nullptr, &dAmount, 0, 2500, 100, 1, false);
			sub->AddOption<NumberOption<int>>("Delay", nullptr, &dDelay, 0, 1000, 10, 1, false);
			sub->AddOption<NumberOption<int>>("Height", nullptr, &dz, 0, 10, 1, 1, false);
			sub->AddOption<BoolOption<bool>>("Drop", nullptr, &dEnable, BoolDisplay::OnOff, false);
			sub->AddOption<NumberOption<int>>("X", nullptr, &dx, 0, 10, 1, 1, false);
			sub->AddOption<NumberOption<int>>("Y", nullptr, &dy, 0, 10, 1, 1, false);
			sub->AddOption<NumberOption<int>>("Z", nullptr, &dHeight, 0, 10, 1, 1, false);
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Online", Onlinee, [](RegularSubmenu* sub)
		{
			sub->AddOption<SubOption>("Protections", nullptr, protections);
			sub->AddOption<SubOption>("Recovery", nullptr, Rec);
			sub->AddOption<SubOption>("Player Moderation", nullptr, PM);
			sub->AddOption<SubOption>("All Players", nullptr, allPlayers);
			sub->AddOption<SubOption>("Playerlist", nullptr, SubmenuPlayerList);
			sub->AddOption<SubOption>("R*ID Options", nullptr, RIDOptions);
			sub->AddOption<SubOption>("Casino Heist Options", nullptr, CasinoH);
			sub->AddOption<ChooseOption<const char*, std::size_t>>("Session Weather", nullptr, &Lists::session_weather, &Lists::session_weather_pos, true);
			sub->AddOption<RegularOption>("Set Weather", nullptr, [=] {g_GameFunctions->m_SessionWeather(1, Lists::session_weather_pos, 76, 0); });
			sub->AddOption<BoolOption<bool>>("Off Radar", nullptr, &otr, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Infinite AFK", "You won't be kicked for being afk", &antiAFK, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Bypass Chat Restrictions", nullptr, &chatBypass, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Bypass World Restrictions", nullptr, &restricted, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<RegularOption>("Skip Cutscene", nullptr, []
			{
				CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();
			});

		});
		g_UiManager->AddSubmenu<RegularSubmenu>("All Players", allPlayers, [](RegularSubmenu* sub)
		{
			sub->AddOption<RegularOption>("Cage", nullptr, []
			{
				for (std::uint32_t i = 0; i < 32; ++i)
				{
					g_SelectedPlayer = i;
					if (exclude(i))
					{
						cagePlayer(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i));
					}
				}
			});
			sub->AddOption<RegularOption>("Kick", nullptr, []
			{
				for (std::uint32_t i = 0; i < 32; ++i)
				{
					g_SelectedPlayer = i;
					if (exclude(i))
					{
						kick_to_new_lobby(i);
					}
				}
			});
			sub->AddOption<RegularOption>("Airstrike", nullptr, []
			{
				for (std::uint32_t i = 0; i < 32; ++i)
				{
					g_SelectedPlayer = i;
					if (exclude(i))
					{
						airStrikePlayer(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i));
					}
				}
			});
			sub->AddOption<RegularOption>("Explode", nullptr, []
			{
				for (std::uint32_t i = 0; i < 32; ++i)
				{
					g_SelectedPlayer = i;
					if (exclude(i))
					{
						NativeVector3 GetPlayerCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(i), true);
						//FIRE::ADD_EXPLOSION(GetPlayerCoords.x, GetPlayerCoords.y, GetPlayerCoords.z, 29, 20, false, false, 0.f, false);
						PED::EXPLODE_PED_HEAD(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), 0x145F1012);


					}
				}
			});
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Player Moderation", PM, [](RegularSubmenu* sub)
		{
			sub->AddOption<SubOption>("Excludes", nullptr, exxxx);
			sub->AddOption<SubOption>("Player Detection", nullptr, PD);
			sub->AddOption<SubOption>("Vehicle Blacklisting", nullptr, PB);
			sub->AddOption<BoolOption<bool>>("Enable", "Player & Vehicle Settings", &serverScanner, BoolDisplay::OnOff, false, [] {});


		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Excludes", exxxx, [](RegularSubmenu* sub)
		{
			sub->AddOption<BoolOption<bool>>("Me", "You won't be affected", &exMe, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Friends", "Your friends won't be affected", &exFriends, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<RegularOption>("INFO", "This won't apply to all features", [] {});
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Player Detection", PD, [](RegularSubmenu* sub)
		{
			sub->AddOption<BoolOption<bool>>("Joining", "Notifies you when players are joining your session ", &joinNotify, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Notify", "When saved players are in your session", &notify, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Kick", "Saved Players when they are in your session ", &kick, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Crash", "Saved Players when they are in your session ", &crash, BoolDisplay::OnOff, false, [] {});
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Vehicle Blacklisting", PB, [](RegularSubmenu* sub)
		{
			sub->AddOption<RegularOption>("Add vehicles in Detection.ini", nullptr, [] {});
			sub->AddOption<BoolOption<bool>>("Adder", "Will work within a mile around you", &blacklistopmk2, BoolDisplay::OnOff, false, [] {});
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Recovery", Rec, [](RegularSubmenu* sub)
		{
			sub->AddOption<BoolOption<bool>>("Bunker Stock Multiplier", "Go to your bunker and sell your stock", &bUnkerMoney, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<RegularOption>("Unlock All", nullptr, [] { UnlockAll(); });
			sub->AddOption<RegularOption>("Max Snacks", nullptr, [] { UnlockSnacks(); });
			sub->AddOption<RegularOption>("Max Stats", nullptr, [] { UnlockStats(); });
			sub->AddOption<RegularOption>("Unlock Tattoos", nullptr, [] { UnlockTattoos(); });
			sub->AddOption<RegularOption>("Unlock Rims", nullptr, [] { UnlockRims(); });
			sub->AddOption<RegularOption>("Unlock Vehicles", nullptr, [] { UnlockVehicles(); });
			sub->AddOption<RegularOption>("Unlock Achievements", nullptr, [] { UnlockAchievements(); });
			sub->AddOption<RegularOption>("Unlock Hairstyles", nullptr, [] { UnlockHairstyles(); });
			sub->AddOption<RegularOption>("Unlock Weapons", nullptr, [] { UnlockWeapons(); });
			sub->AddOption<RegularOption>("Unlock Clothes", nullptr, [] { UnlockClothes(); });
			sub->AddOption<RegularOption>("SecuroServ Office Cash", nullptr, [] { OfficeMoney(); });
			sub->AddOption<RegularOption>("SecuroServ Office Statue", nullptr, [] { OfficeStatue(); });
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Loader", Loaderr, [](RegularSubmenu* sub)
		{
			sub->AddOption<SubOption>("Outfit Loader", nullptr, OC);
			sub->AddOption<SubOption>("Vehicle Loader", nullptr, VH);
			sub->AddOption<SubOption>("Config", nullptr, cf);
			sub->AddOption<SubOption>("Hotkeys", nullptr, keysHot);
			sub->AddOption<RegularOption>("Remove Input Window", nullptr, [] { KeyWindow = false; CreateOutfitWindow = false; });
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Hotkeys", keysHot, [](RegularSubmenu* sub)
		{
			sub->AddOption<BoolOption<bool>>("Teleport To Waypoint", "F7", &f7, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Freecam", "F5", &f5, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Vehicle Fly", "F4", &f4, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<RegularOption>("Change Controls", nullptr, [] { KeyWindow = true; notifyMap(HUD_COLOUR_BLUEDARK, ("Press X to enable your mouse"));	});
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Config", cf, [](RegularSubmenu* sub)
		{
			sub->AddOption<RegularOption>("Change Controls", nullptr, [] { KeyWindow = true; notifyMap(HUD_COLOUR_BLUEDARK, ("Press X to enable your mouse"));	});
			sub->AddOption<RegularOption>("Save Config", nullptr, [] { SaveConfig(); });
			sub->AddOption<RegularOption>("Save:", nullptr, [] {});
			sub->AddOption<BoolOption<bool>>("Local", "Save Local Settings", &LocalFiles, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Online", "Save Online Settings", &NetworkFiles, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Vehicle", "Save Vehicle Settings", &VehicleFiles, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Weapon", "Save Weapon Settings", &WeaponFiles, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("World", "Save World Settings", &WorldFiles, BoolDisplay::OnOff, false, [] {});
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Outfit Loader", OC, [](RegularSubmenu* sub)
		{
			sub->AddOption<SubOption>("Load Outfits", nullptr, LO);
			sub->AddOption<RegularOption>("Save Outfit", nullptr, []
			{
				CreateOutfitFile();
			});
			sub->AddOption<NumberOption<std::int32_t>>("Face:", nullptr, &o1, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 0), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 0, o1, 0, 0); });
			sub->AddOption<NumberOption<std::int32_t>>("Head:", nullptr, &o2, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 1), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 1, o2, 0, 0); });
			sub->AddOption<NumberOption<std::int32_t>>("Hair:", nullptr, &o3, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 2), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 2, o3, 0, 0); });
			sub->AddOption<NumberOption<std::int32_t>>("Torso:", nullptr, &o4, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 3), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 3, o4, 0, 0); });
			sub->AddOption<NumberOption<std::int32_t>>("Legs:", nullptr, &o5, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 4), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 4, o5, 0, 0); });
			sub->AddOption<NumberOption<std::int32_t>>("Hands:", nullptr, &o6, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 5), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 5, o6, 0, 0); });
			sub->AddOption<NumberOption<std::int32_t>>("Feet:", nullptr, &o7, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 6), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 6, o7, 0, 0); });
			sub->AddOption<NumberOption<std::int32_t>>("Eyes:", nullptr, &o8, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 7), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 7, o8, 0, 0); });
			sub->AddOption<NumberOption<std::int32_t>>("Accessories:", nullptr, &o9, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 8), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 8, o9, 0, 0); });
			sub->AddOption<NumberOption<std::int32_t>>("Tasks:", nullptr, &o10, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 9), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 9, o10, 0, 0); });
			sub->AddOption<NumberOption<std::int32_t>>("Textures:", nullptr, &o11, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 10), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 10, o11, 0, 0); });
			sub->AddOption<NumberOption<std::int32_t>>("Torso2:", nullptr, &o12, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 11), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 11, o12, 0, 0); });
			sub->AddOption<NumberOption<std::int32_t>>("Head Props:", nullptr, &o13, 0, 255, 1, 3, true, "", "", [] { PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 1, o13, 0, 0); });
			sub->AddOption<NumberOption<std::int32_t>>("Eye Props:", nullptr, &o14, 0, 255, 1, 3, true, "", "", [] { PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 2, o14, 0, 0); });

		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Load R*IDs", RIDManager, [](RegularSubmenu* sub)
		{
			namespace fs = std::filesystem;
			fs::directory_iterator dirIt{ "C:\\Viper\\Manager\\RIDManager\\" };
			for (auto&& dirEntry : dirIt)
			{
				if (dirEntry.is_regular_file())
				{
					auto path = dirEntry.path();
					if (path.has_filename())
					{
						if (path.extension() == ".ini")
						{
							RIDList();
							sub->AddOption<RegularOption>(path.stem().u8string().c_str(), nullptr, [=]
							{
								JoinRID(path.stem().u8string().c_str());
							});

						}

					}
				}

			}
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Load Outfits", LO, [](RegularSubmenu* sub)
		{
			namespace fs = std::filesystem;
			fs::directory_iterator dirIt{ "C:\\Viper\\Outfits\\" };
			for (auto&& dirEntry : dirIt)
			{
				if (dirEntry.is_regular_file())
				{
					auto path = dirEntry.path();
					if (path.has_filename())
					{
						if (path.extension() == ".ini")
						{
							OutfitList();
							sub->AddOption<RegularOption>(path.stem().u8string().c_str(), nullptr, [=]
							{
								LoadOutfit(path.stem().u8string().c_str());
							});

						}

					}
				}

			}
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Vehicle Loader", VH, [](RegularSubmenu* sub)
		{
			namespace fs = std::filesystem;
			fs::directory_iterator dirIt{ "C:\\Viper\\Vehicles\\" };
			for (auto&& dirEntry : dirIt)
			{
				if (dirEntry.is_regular_file())
				{
					auto path = dirEntry.path();
					if (path.has_filename())
					{
						if (path.extension() == ".ini")
						{
							OutfitList();
							sub->AddOption<RegularOption>(path.stem().u8string().c_str(), nullptr, [=]
							{
								LoadPreset(path.stem().u8string().c_str());
							});

						}

					}
				}
			}
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Teleport Locations", tpl, [](RegularSubmenu* sub)
		{
			namespace fs = std::filesystem;
			fs::directory_iterator dirIt{ "C:\\Viper\\Teleports\\" };
			for (auto&& dirEntry : dirIt)
			{
				if (dirEntry.is_regular_file())
				{
					auto path = dirEntry.path();
					if (path.has_filename() && !fs::is_empty(path))
					{
						sub->AddOption<RegularOption>(path.stem().u8string().c_str(), nullptr, [=]
						{
							fs::path m_FilePath;
							char prefix[64] = {};
							std::snprintf(prefix, sizeof(prefix) - 1, "%s%s", path.stem().u8string(), ".ini");

							m_FilePath.append(prefix);

							std::ifstream ifs(m_FilePath);

							std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
							std::stringstream ss(content);
							std::vector<float> result;

							while (ss.good())
							{
								std::string substr;
								std::getline(ss, substr, ',');
								result.push_back(::atof(substr.c_str()));
							}
							if (PED::IS_PED_IN_VEHICLE(PLAYER::PLAYER_PED_ID(), PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), true))
							{
								Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
								ENTITY::SET_ENTITY_COORDS_NO_OFFSET(veh, result[0], result[1], result[2], false, false, false);
							}
							else
							{
								ENTITY::SET_ENTITY_COORDS_NO_OFFSET(PLAYER::PLAYER_PED_ID(), result[0], result[1], result[2], false, false, false);
							}
						});
					}
				}
			}

		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Weapon", Weaponn, [](RegularSubmenu* sub)
		{
			sub->AddOption<BoolOption<bool>>("Gravity Gun", nullptr, &gravityGun, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Infinite Ammo", nullptr, &InfiniteAmmo, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Airstrike Gun", nullptr, &AirstrikeGun, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("One shot Gun", nullptr, &Oneshot, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Rope Gun", nullptr, &ROPEGUN, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Firework Gun", nullptr, &fireworkgun, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Force Gun", nullptr, &forcegun, BoolDisplay::OnOff, false, [] {}); //pedAimbot
			sub->AddOption<BoolOption<bool>>("Aimbot", nullptr, &pedAimbot, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Triggerbot", nullptr, &pedAimbot, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("TP Gun", nullptr, &tpgun, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<RegularOption>("Give Weapons", nullptr, []
			{
				uint Weapons[] = { 0x92A27487, 0x958A4A8F, 0xF9E6AA4B, 0x84BD7BFD, 0xA2719263, 0x8BB05FD7, 0x440E4788, 0x4E875F73, 0xF9DCBF2D, 0xD8DF3C3C, 0x99B507EA, 0xDD5DF8D9, 0xDFE37640, 0x678B81B1, 0x19044EE0, 0xCD274149, 0x94117305, 0x3813FC08, /* Melee  */   0x1B06D571, 0xBFE256D4, 0x5EF9FEC4, 0x22D8FE39, 0x3656C8C1, 0x99AEEB3B, 0xBFD21232, 0x88374054, 0xD205520E, 0x83839C4, 0x47757124, 0xDC4DB296, 0xC1B3C3D1, 0xCB96392F, 0x97EA20B8, /* Handguns */  0x13532244, 0x2BE6766B, 0x2BE6766B, 0xEFE7E2DF, 0x0A3D4D34, 0xDB1AA450, 0xBD248B55, /* Submachine Guns */  0x1D073A89, 0x555AF99A, 0x7846A318, 0xE284C527, 0x9D61E50F, 0xA89CB99E, 0x3AABBBAA, 0xEF951FBB, 0x12E82D3D,   /* Shotguns */ 0xBFEFFF6D, 0x394F415C, 0x83BF0278, 0xFAD1F1C9, 0xAF113F99, 0xC0A3098D, 0x969C3D67, 0x7F229F94, 0x84D6FAFD, 0x624FE830,  /* Assault Rifles */ 0x9D07F764, 0x7FD62962, 0xDBBD7280, 0x61012683,   /* Light Machine Guns */ 0x05FC3C11, 0x0C472FE2, 0xA914799, 0xC734385A, 0x6A6C02E0, /* Sniper Rifles  */ 0xB1CA77B1, 0xA284510B, 0x4DD2DC56, 0x42BF8A85, 0x7F7497E5, 0x6D544C99, 0x63AB0442, 0x0781FE4A, /* Heavy Weapons  */ 0x93E220BD, 0xA0973D5E, 0x24B17070, 0x2C3731D9, 0xAB564B93, 0x787F0BB, 0xBA45E8B8, 0x23C9F95C, 0xFDBC8A50, 0x497FACC3,  /*Throwables  */ 0x34A67B97, 0xFBAB5776, 0x060EC506,  /*Miscellaneous  */ 0xAF3696A1, 0x476BF155, 0xB62D1F67,	  /* 1.46  */ 0x2B5EF5EC, 0x2CE227AC, 0x832A1A76, 0x917F6C8C  /* Casino  */
				};
				for (int i = 0; i < (sizeof(Weapons) / 4); i++) {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()), Weapons[i], 9999, 1);
				}
			});
		});


		g_UiManager->AddSubmenu<RegularSubmenu>("Vehicle", Vehiclee, [](RegularSubmenu* sub)
		{	//VehicleManagerSubOption	
			sub->AddOption<SubOption>("Vehicle Spawner", nullptr, spawner);
			sub->AddOption<BoolOption<bool>>("Vehicle Fly", nullptr, &VehFly, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Invincible", nullptr, &vehicleInvincible, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Collision", nullptr, &flyCollision_veh, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Visible", nullptr, &vehInvisible, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Rainbow", nullptr, &Rainbow, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Seatbelt", "You won't be able to fall off", &Seatbelt, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Reduce Grip", nullptr, &reducegrip, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Auto Fix", "Vehicle fly may glitch", &autoFix, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Auto Flip", nullptr, &autoFlip, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Instant Break", "Press R to execute", &autoFlip, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Bypass Speedlimit", nullptr, &nolimit, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Hornboost", nullptr, &Hornboost, BoolDisplay::OnOff, false, [] {});
		});	

		g_UiManager->AddSubmenu<RegularSubmenu>("Vehicle Spawn Options", VehicleOptions, [](RegularSubmenu* sub)
		{
			sub->AddOption<BoolOption<bool>>("Spawn In Vehicle", nullptr, &SpawnInVeh, BoolDisplay::OnOff, false, [] {}); //Make can save option
			sub->AddOption<BoolOption<bool>>("Max Vehicle On Spawn", nullptr, &MaxVeh, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Delete Current Vehicle", nullptr, &DeleteVeh, BoolDisplay::OnOff, false, [] {});
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Delete", VehicleManagerDelete, [](RegularSubmenu* sub)
		{
			for (auto VehicleList : _VehicleList)
			{
				const char* Vehiclename = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(ENTITY::GET_ENTITY_MODEL(VehicleList));

				if (Vehiclename != NULL)
				{
					sub->AddOption<RegularOption>(Vehiclename, nullptr, [=]
					{
						for (auto VehicleList : _VehicleList)
						{
							Vehicle car = VehicleList;
							VEHICLE::DELETE_VEHICLE(&car);

							const char* name = "C:\\Viper\\Manager\\VehicleManager\\";

							string namepp = name + (string)Vehiclename + std::to_string(vehicleNumber);

					//		ostringstream name;

							const char* vehicleppname = StringToChar(namepp);

							remove(vehicleppname);

						//	DeleteFileA(name);
						}
					});
				}
				if (Vehiclename == "CARNOTFOUND")
				{
				
				}
			}
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Delete", VehicleManagerDelete, [](RegularSubmenu* sub)
		{
			namespace fs = std::filesystem;
			fs::directory_iterator dirIt{ "C:\\Viper\\Pedestrian Manager\\Current\\" };
			for (auto&& dirEntry : dirIt)
			{
				if (dirEntry.is_regular_file())
				{
					auto path = dirEntry.path();
					if (path.has_filename())
					{
						if (path.extension() == ".ini")
						{
							alivepedlist();
							sub->AddOption<SubOption>(path.stem().u8string().c_str(), nullptr, SubmenuSelectedPlayer, [=]
							{
								
							});
						}

					}
				}

			}
			
		});
		
		
		
		
		g_UiManager->AddSubmenu<RegularSubmenu>("Vehicle Loader", VH, [](RegularSubmenu* sub)
		{
			namespace fs = std::filesystem;
			fs::directory_iterator dirIt{ "C:\\Viper\\Vehicles\\" };
			for (auto&& dirEntry : dirIt)
			{
				if (dirEntry.is_regular_file())
				{
					auto path = dirEntry.path();
					if (path.has_filename())
					{
						if (path.extension() == ".ini")
						{
							OutfitList();
							sub->AddOption<RegularOption>(path.stem().u8string().c_str(), nullptr, [=]
							{
								LoadPreset(path.stem().u8string().c_str());
							});

						}

					}
				}
			}
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Vehicle Manager", VehicleManagerSub, [](RegularSubmenu* sub)
		{
			sub->AddOption<SubOption>("Delete Vehicles", nullptr, VehicleManagerDelete);
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Vehicle Spawner", spawner, [](RegularSubmenu* sub)
		{
			sub->AddOption<SubOption>("Favorite Vehicles", nullptr, fv);
			sub->AddOption<SubOption>("Vehicle Spawn Options", nullptr, VehicleOptions);
			sub->AddOption<SubOption>("Super", nullptr, Super);
			sub->AddOption<SubOption>("Sports", nullptr, Sports);
			sub->AddOption<SubOption>("SportClassic", nullptr, SportClassic);
			sub->AddOption<SubOption>("Offroad", nullptr, Offroad);
			sub->AddOption<SubOption>("Sedans", nullptr, Sedans);
			sub->AddOption<SubOption>("Coupes", nullptr, Coupes);
			sub->AddOption<SubOption>("Muscle", nullptr, Muscle);
			sub->AddOption<SubOption>("Utility", nullptr, Utility);
			sub->AddOption<SubOption>("Commercial", nullptr, Commercial);
			sub->AddOption<SubOption>("Compacts", nullptr, Compacts);
			sub->AddOption<SubOption>("SUV", nullptr, SUV);
			sub->AddOption<SubOption>("Cycles", nullptr, Cycles);
			sub->AddOption<SubOption>("Motorcycles", nullptr, Motorcycles);
			sub->AddOption<SubOption>("Helicopters", nullptr, Helicopters);
			sub->AddOption<SubOption>("Planes", nullptr, Planes);
			sub->AddOption<SubOption>("Emergency", nullptr, Emergency);
			sub->AddOption<SubOption>("Industrial", nullptr, Industrial);
			sub->AddOption<SubOption>("Trailer", nullptr, Trailer);
			sub->AddOption<SubOption>("Trains", nullptr, Trains);
			sub->AddOption<SubOption>("Boats", nullptr, Boats);
			sub->AddOption<SubOption>("Military", nullptr, Military);
		});


		g_UiManager->AddSubmenu<RegularSubmenu>("Favorite Vehicles", fv, [](RegularSubmenu* sub)
		{
			namespace fs = std::filesystem;
			fs::directory_iterator dirIt{ "C:\\Viper\\Favorite Vehicles\\" };
			for (auto&& dirEntry : dirIt)
			{
				if (dirEntry.is_regular_file())
				{
					auto path = dirEntry.path();
					if (path.has_filename())
					{
						if (path.extension() == ".ini")
						{
							sub->AddOption<RegularOption>(path.stem().u8string().c_str(), nullptr, [=]
							{
								SpawnOption(path.stem().u8string().c_str());
							});

						}

					}
				}
			}
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Pedestrian Manager", Bodyguardss, [](RegularSubmenu* sub)
		{
			sub->AddOption<SubOption>("Spawn Peds", nullptr, Models);
			sub->AddOption<SubOption>("Database", nullptr, database);
			sub->AddOption<RegularOption>("Current Spawned:", nullptr, [=] {});
			sub->AddOption<SubOption>("mp_m_securoguard_01", nullptr, database);
			sub->AddOption<SubOption>("g_f_y_families_01", nullptr, database);
			sub->AddOption<SubOption>("g_m_importexport_01", nullptr, database);
			sub->AddOption<SubOption>("g_m_m_armboss_01", nullptr, database);
			sub->AddOption<SubOption>("g_m_m_armgoon_01", nullptr, database);
			sub->AddOption<SubOption>("g_m_m_armlieut_01", nullptr, database);
			sub->AddOption<SubOption>("g_m_y_armgoon_02", nullptr, database);
			sub->AddOption<SubOption>("mp_m_securoguard_01", nullptr, database);
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Pedestrian Manager", database, [](RegularSubmenu* sub)
		{
			namespace fs = std::filesystem;
			fs::directory_iterator dirIt{ "C:\\Viper\\Pedestrian Manager\\" };
			for (auto&& dirEntry : dirIt)
			{
				if (dirEntry.is_regular_file())
				{
					auto path = dirEntry.path();
					if (path.has_filename())
					{
						if (path.extension() == "")
						{
							sub->AddOption<RegularOption>(path.stem().u8string().c_str(), nullptr, [=]
							{
								load_peds(path.stem().u8string().c_str());
							});

						}

					}
				}
			}
		});

		

		g_UiManager->AddSubmenu<RegularSubmenu>("Teleport", Teleportt, [](RegularSubmenu* sub)
		{
			sub->AddOption<SubOption>("Vehicle", nullptr, TPOVehicle);
			sub->AddOption<SubOption>("Sports", nullptr, TPSports);
			sub->AddOption<SubOption>("Stores", nullptr, TPStores);
			sub->AddOption<SubOption>("Airports", nullptr, TPAir);
			sub->AddOption<SubOption>("Fun", nullptr, TPFun);
			sub->AddOption<SubOption>("Services", nullptr, TPServices);
			sub->AddOption<SubOption>("Apartments", nullptr, TPAparts);
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("World", Worldd, [](RegularSubmenu* sub)
		{

			sub->AddOption<SubOption>("Weather", nullptr, Weather);
			sub->AddOption<SubOption>("WorldSpeed", nullptr, WorldSpeed_);
			sub->AddOption<SubOption>("Time", nullptr, Timeee);
			sub->AddOption<RegularOption>("Clear All", nullptr, []
			{
				World_Clear();

			});
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Miscellaneous", Miscellaneouss, [](RegularSubmenu* sub)
		{

		});

		/* PLAYER */


		/* ONLINE */
		g_UiManager->AddSubmenu<RegularSubmenu>("Players", SubmenuPlayerList, [](RegularSubmenu* sub)
		{
			for (std::uint32_t i = 0; i < 32; ++i)
			{
				if (sub->GetSelectedOption() == sub->GetNumOptions()) {
					LoadPlayerInfo(i);
				}
				if (auto ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))
				{
					sub->AddOption<SubOption>(PlayerName(i).c_str(), nullptr, SubmenuSelectedPlayer, [=]
					{
						g_SelectedPlayer = i;
					});
				}
			}
		});

		g_UiManager->AddSubmenu<PlayerSubmenu>(&g_SelectedPlayer, SubmenuSelectedPlayer, [](PlayerSubmenu* sub)
		{	
			LoadPlayerInfo(g_SelectedPlayer);//CreateRIDConfig
			sub->AddOption<BoolOption<bool>>("Spectate", nullptr, &_Spectate, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<SubOption>("Vehicle Spawner", nullptr, spawner);
			sub->AddOption<SubOption>("Drop", nullptr, pDrop);
			sub->AddOption<SubOption>("Script Events", nullptr, scriptNigga);
			sub->AddOption<RegularOption>("Save RID", nullptr, []
			{
				//RID
				int netHandle[13];
				NETWORK::NETWORK_HANDLE_FROM_PLAYER(g_SelectedPlayer, netHandle, 13);
				const char* RID = NETWORK::NETWORK_MEMBER_ID_FROM_GAMER_HANDLE(&netHandle[0]);
				CreateRIDConfig(PLAYER::GET_PLAYER_NAME(g_SelectedPlayer), RID);
			});
			sub->AddOption<RegularOption>("Duplicate Car", nullptr, []
			{
				dupeCar(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer));
			});
		
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Events", scriptNigga, [](RegularSubmenu* sub)
		{
			LoadPlayerInfo(g_SelectedPlayer);
			sub->AddOption<RegularOption>("Send To Job", nullptr, [] { SendToJob(); });
			sub->AddOption<RegularOption>("CEO Kick", nullptr, [] { CEOKick(); });
			sub->AddOption<RegularOption>("CEO Ban", nullptr, [] { CEOBan(); });
			sub->AddOption<RegularOption>("Sound Spam", nullptr, [] { DoSoundSpam(); });
			sub->AddOption<RegularOption>("Send Face Camera Forward", nullptr, [] { sendFaceCameraForward(); });
			sub->AddOption<RegularOption>("Vehicle Kick", nullptr, [] { VehKick(); });
			sub->AddOption<RegularOption>("Kick", nullptr, [] { kick_to_new_lobby(g_SelectedPlayer); });
			

		});

		/* SETTINGS */

		g_UiManager->AddSubmenu<RegularSubmenu>("Settings", SubmenuSettings, [](RegularSubmenu* sub)
		{
			//		LoadPlayerInfo(g_SelectedPlayer);
			sub->AddOption<SubOption>("Header", nullptr, SubmenuSettingsHeader);
			sub->AddOption<SubOption>("Infobar", nullptr, SubmenuSettingsSubmenuBar);
			sub->AddOption<SubOption>("Options", nullptr, SubmenuSettingsOption);
			sub->AddOption<SubOption>("Footer", nullptr, SubmenuSettingsFooter);
			sub->AddOption<SubOption>("Description", nullptr, SubmenuSettingsDescription);
			sub->AddOption<SubOption>("Input", nullptr, SubmenuSettingsInput);
			sub->AddOption<SubOption>("Language", nullptr, SubmenuSettingsLanguage); //m_Width	
			sub->AddOption<NumberOption<float>>("X Position", nullptr, &g_UiManager->m_PosX, 0.f, 1.f, 0.01f, 2);
			sub->AddOption<NumberOption<float>>("Y Position", nullptr, &g_UiManager->m_PosY, 0.f, 1.f, 0.01f, 2);
			sub->AddOption<NumberOption<float>>("Width", nullptr, &g_UiManager->m_Width, 0.01f, 1.f, 0.01f, 2); //Scale m_OptionHeight2
			sub->AddOption<NumberOption<float>>(" m_PosXx", nullptr, &g_UiManager->m_PosXx, 0.f, 1.f, 0.01f, 2);
			sub->AddOption<NumberOption<float>>(" m_PosYy", nullptr, &g_UiManager->m_PosYy, 0.f, 1.f, 0.01f, 2);
			sub->AddOption<NumberOption<float>>(" m_PosXScrol", nullptr, &g_UiManager->m_PosXScrol, 0.f, 1.f, 0.01f, 2);
			sub->AddOption<NumberOption<float>>(" m_PosWidthScrol", nullptr, &g_UiManager->m_PosWidthScrol, 0.f, 1.f, 0.01f, 2);
			sub->AddOption<NumberOption<float>>(" m_PosXScrol2", nullptr, &g_UiManager->m_PosXScrol2, 0.f, 1.f, 0.01f, 2);
			sub->AddOption<NumberOption<float>>(" m_PosWidthScrol2", nullptr, &g_UiManager->m_PosWidthScrol2, 0.f, 1.f, 0.01f, 2);
			sub->AddOption<NumberOption<float>>(" m_OptionHeight2", nullptr, &g_UiManager->m_OptionHeight2, 0.f, 1.f, 0.01f, 2);
			sub->AddOption<NumberOption<float>>("Scale Test", nullptr, &g_UiManager->Scale, 0.01f, 1.f, 0.01f, 2);
			sub->AddOption<NumberOption<float>>("Scale Test 2", nullptr, &g_UiManager->Scale2, 0.01f, 1.f, 0.01f, 2);
			sub->AddOption<NumberOption<float>>("Width Test", nullptr, &g_UiManager->m_withh, 0.01f, 1.f, 0.01f, 2); //
		//	sub->AddOption<NumberOption<float>>("X Pos Test", nullptr, &g_UiManager->x_poss, 0.01f, 1.f, 0.01f, 2);	
		//	sub->AddOption<NumberOption<float>>("X Pos 2 Test", nullptr, &g_UiManager->x_poss2, 0.01f, 1.f, 0.01f, 2);

			sub->AddOption<NumberOption<float>>(" m_Number1", nullptr, &g_UiManager->m_Number1, 0.f, 1.f, 0.01f, 2);
			sub->AddOption<NumberOption<float>>(" m_Number2", nullptr, &g_UiManager->m_Number2, 0.f, 1.f, 0.01f, 2);;
			//sub->AddOption<NumberOption<float>>(" m_Number3", nullptr, &g_UiManager->m_Number3, 0.f, 1.f, 0.01f, 2);

			sub->AddOption<BoolOption<bool>>("Sounds", nullptr, &g_UiManager->m_Sounds, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<std::atomic_bool>>("Log Window", nullptr, &g_Settings.m_LogWindow, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Log Script Events", nullptr, &g_LogScriptEvents, BoolDisplay::OnOff);
			sub->AddOption<RegularOption>("Unload", "Unload the menu.", []
			{
				g_Running = false;
			});
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Language", SubmenuSettingsLanguage, [](RegularSubmenu* sub)
		{
			namespace fs = std::filesystem;
			fs::directory_iterator dirIt{ g_TranslationManager->GetTranslationDirectory() };
			for (auto&& dirEntry : dirIt)
			{
				if (dirEntry.is_regular_file())
				{
					auto path = dirEntry.path();
					if (path.has_filename())
					{
						sub->AddOption<RegularOption>(path.stem().u8string().c_str(), nullptr, [=]
						{
							g_TranslationManager->LoadTranslations(path.stem().u8string().c_str());
						});
					}
				}
			}
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Infobar", SubmenuSettingsSubmenuBar, [](RegularSubmenu* sub)
		{
			sub->AddOption<NumberOption<float>>("Height", nullptr, &g_UiManager->m_SubmenuBarHeight, 0.01f, 0.1f, 0.001f, 3);
			sub->AddOption<NumberOption<float>>("Text Size", nullptr, &g_UiManager->m_SubmenuBarTextSize, 0.01f, 1.f, 0.01f, 2);

			sub->AddOption<NumberOption<std::uint8_t>>("Background R", nullptr, &g_UiManager->m_SubmenuBarBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Background G", nullptr, &g_UiManager->m_SubmenuBarBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Background B", nullptr, &g_UiManager->m_SubmenuBarBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Background A", nullptr, &g_UiManager->m_SubmenuBarBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Text R", nullptr, &g_UiManager->m_SubmenuBarTextColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Text G", nullptr, &g_UiManager->m_SubmenuBarTextColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Text B", nullptr, &g_UiManager->m_SubmenuBarTextColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Text A", nullptr, &g_UiManager->m_SubmenuBarTextColor.a, '\0', static_cast<std::uint8_t>(255));
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Options", SubmenuSettingsOption, [](RegularSubmenu* sub)
		{
			sub->AddOption<NumberOption<float>>("Height", nullptr, &g_UiManager->m_OptionHeight, 0.01f, 0.1f, 0.001f, 3);
			sub->AddOption<NumberOption<float>>("Text Size", nullptr, &g_UiManager->m_OptionTextSize, 0.01f, 1.f, 0.01f, 2);

			sub->AddOption<NumberOption<std::uint8_t>>("Selected Background R", nullptr, &g_UiManager->m_OptionSelectedBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Selected Background G", nullptr, &g_UiManager->m_OptionSelectedBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Selected Background B", nullptr, &g_UiManager->m_OptionSelectedBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Selected Background A", nullptr, &g_UiManager->m_OptionSelectedBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Unselected Background R", nullptr, &g_UiManager->m_OptionUnselectedBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Unselected Background G", nullptr, &g_UiManager->m_OptionUnselectedBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Unselected Background B", nullptr, &g_UiManager->m_OptionUnselectedBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Unselected Background A", nullptr, &g_UiManager->m_OptionUnselectedBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));

			sub->AddOption<NumberOption<std::uint8_t>>("Selected Text R", nullptr, &g_UiManager->m_OptionSelectedTextColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Selected Text G", nullptr, &g_UiManager->m_OptionSelectedTextColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Selected Text B", nullptr, &g_UiManager->m_OptionSelectedTextColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Selected Text A", nullptr, &g_UiManager->m_OptionSelectedTextColor.a, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Unselected Text R", nullptr, &g_UiManager->m_OptionUnselectedTextColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Unselected Text G", nullptr, &g_UiManager->m_OptionUnselectedTextColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Unselected Text B", nullptr, &g_UiManager->m_OptionUnselectedTextColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Unselected Text A", nullptr, &g_UiManager->m_OptionUnselectedTextColor.a, '\0', static_cast<std::uint8_t>(255));
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Footer", SubmenuSettingsFooter, [](RegularSubmenu* sub)
		{
			sub->AddOption<NumberOption<float>>("Height", nullptr, &g_UiManager->m_FooterHeight, 0.01f, 0.1f, 0.001f, 3);
			sub->AddOption<NumberOption<float>>("Sprite Size", nullptr, &g_UiManager->m_FooterSpriteSize, 0.01f, 1.f, 0.001f, 3);

			sub->AddOption<NumberOption<std::uint8_t>>("Background R", nullptr, &g_UiManager->m_FooterBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Background G", nullptr, &g_UiManager->m_FooterBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Background B", nullptr, &g_UiManager->m_FooterBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Background A", nullptr, &g_UiManager->m_FooterBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Sprite R", nullptr, &g_UiManager->m_FooterSpriteColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Sprite G", nullptr, &g_UiManager->m_FooterSpriteColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Sprite B", nullptr, &g_UiManager->m_FooterSpriteColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Sprite A", nullptr, &g_UiManager->m_FooterSpriteColor.a, '\0', static_cast<std::uint8_t>(255));
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Header", SubmenuSettingsHeader, [](RegularSubmenu* sub)
		{
			sub->AddOption<ChooseOption<const char*, std::size_t>>("Type", nullptr, &Lists::HeaderTypesFrontend, &Lists::HeaderTypesPosition, true, []
			{
				g_UiManager->m_HeaderType = Lists::HeaderTypesBackend[Lists::HeaderTypesPosition];
			});

			switch (g_UiManager->m_HeaderType)
			{
			case HeaderType::Static:
				sub->AddOption<SubOption>("Background", nullptr, SubmenuSettingsHeaderStaticBackground);
				break;
			case HeaderType::Gradient:
				sub->AddOption<SubOption>("Gradient", nullptr, SubmenuSettingsHeaderGradientBackground);
				break;
			case HeaderType::YTD:
				break;
			case HeaderType::GIF:
				break;
			}

			sub->AddOption<SubOption>("Text", nullptr, SubmenuSettingsHeaderText);
			sub->AddOption<NumberOption<float>>("Height", nullptr, &g_UiManager->m_HeaderHeight, 0.01f, 0.2f, 0.001f, 3);
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Header Background", SubmenuSettingsHeaderStaticBackground, [](RegularSubmenu* sub)
		{
			sub->AddOption<NumberOption<std::uint8_t>>("R", nullptr, &g_UiManager->m_HeaderBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("G", nullptr, &g_UiManager->m_HeaderBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("B", nullptr, &g_UiManager->m_HeaderBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("A", nullptr, &g_UiManager->m_HeaderBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));
		});


		g_UiManager->AddSubmenu<RegularSubmenu>("Header Gradient", SubmenuSettingsHeaderGradientBackground, [](RegularSubmenu* sub)
		{
			sub->AddOption<BoolOption<bool>>("Transparent", nullptr, &g_UiManager->m_HeaderGradientTransparent, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Flip", nullptr, &g_UiManager->m_HeaderGradientFlip, BoolDisplay::OnOff);

			sub->AddOption<NumberOption<std::uint8_t>>("R1", nullptr, &g_UiManager->m_HeaderGradientColorLeft.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("G1", nullptr, &g_UiManager->m_HeaderGradientColorLeft.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("B1", nullptr, &g_UiManager->m_HeaderGradientColorLeft.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("A1", nullptr, &g_UiManager->m_HeaderGradientColorLeft.a, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("R2", nullptr, &g_UiManager->m_HeaderGradientColorRight.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("G2", nullptr, &g_UiManager->m_HeaderGradientColorRight.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("B2", nullptr, &g_UiManager->m_HeaderGradientColorRight.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("A2", nullptr, &g_UiManager->m_HeaderGradientColorRight.a, '\0', static_cast<std::uint8_t>(255));
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Header Text", SubmenuSettingsHeaderText, [](RegularSubmenu* sub)
		{
			sub->AddOption<BoolOption<bool>>("Enable", nullptr, &g_UiManager->m_HeaderText, BoolDisplay::OnOff);
			sub->AddOption<NumberOption<float>>("Size", nullptr, &g_UiManager->m_HeaderTextSize, 0.1f, 2.f, 0.01f, 2);
			sub->AddOption<NumberOption<std::uint8_t>>("R", nullptr, &g_UiManager->m_HeaderTextColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("G", nullptr, &g_UiManager->m_HeaderTextColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("B", nullptr, &g_UiManager->m_HeaderTextColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("A", nullptr, &g_UiManager->m_HeaderTextColor.a, '\0', static_cast<std::uint8_t>(255));
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Description", SubmenuSettingsDescription, [](RegularSubmenu* sub)
		{
			sub->AddOption<NumberOption<float>>("Padding", "Padding before the description rect.", &g_UiManager->m_DescriptionHeightPadding, 0.01f, 1.f, 0.001f,
				3);
			sub->AddOption<NumberOption<float>>("Height", "Size of the description rect.", &g_UiManager->m_DescriptionHeight, 0.01f, 1.f, 0.001f, 3);
			sub->AddOption<NumberOption<float>>("Text Size", "Size of the description text.", &g_UiManager->m_DescriptionTextSize, 0.1f, 2.f, 0.01f, 2);
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Input", SubmenuSettingsInput, [](RegularSubmenu* sub)
		{
			sub->AddOption<NumberOption<std::int32_t>>("Open Delay", nullptr, &g_UiManager->m_OpenDelay, 10, 1000, 10, 0);
			sub->AddOption<NumberOption<std::int32_t>>("Back Delay", nullptr, &g_UiManager->m_BackDelay, 10, 1000, 10, 0);
			sub->AddOption<NumberOption<std::int32_t>>("Enter Delay", nullptr, &g_UiManager->m_EnterDelay, 10, 1000, 10, 0);
			sub->AddOption<NumberOption<std::int32_t>>("Vertical Delay", nullptr, &g_UiManager->m_VerticalDelay, 10, 1000, 10, 0);
			sub->AddOption<NumberOption<std::int32_t>>("Horizontal Delay", nullptr, &g_UiManager->m_HorizontalDelay, 10, 1000, 10, 0);
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Super", Super, [](RegularSubmenu* sub)
		{

			for (auto car : Super1) {

				Hash model = MISC::GET_HASH_KEY(car);
				const char* vehname = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(model);
				const char* name_veh = HUD::_GET_LABEL_TEXT(vehname);

				sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnOption(car); });
			}

		});


		g_UiManager->AddSubmenu<RegularSubmenu>("Sports", Sports, [](RegularSubmenu* sub)
		{

			for (auto car : Sports1) {

				Hash model = MISC::GET_HASH_KEY(car);
				const char* vehname = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(model);
				const char* name_veh = HUD::_GET_LABEL_TEXT(vehname);

				sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnOption(car); });
			}

		});


		g_UiManager->AddSubmenu<RegularSubmenu>("SportClassic", SportClassic, [](RegularSubmenu* sub)
		{

			for (auto car : SportsClassics1) {

				Hash model = MISC::GET_HASH_KEY(car);
				const char* vehname = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(model);
				const char* name_veh = HUD::_GET_LABEL_TEXT(vehname);

				sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnOption(car); });
			}

		});


		g_UiManager->AddSubmenu<RegularSubmenu>("Offroad", Offroad, [](RegularSubmenu* sub)
		{

			for (auto car : OffRoad1) {

				Hash model = MISC::GET_HASH_KEY(car);
				const char* vehname = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(model);
				const char* name_veh = HUD::_GET_LABEL_TEXT(vehname);

				sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnOption(car); });
			}

		});


		g_UiManager->AddSubmenu<RegularSubmenu>("Sedans", Sedans, [](RegularSubmenu* sub)
		{

			for (auto car : Sedans1) {

				Hash model = MISC::GET_HASH_KEY(car);
				const char* vehname = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(model);
				const char* name_veh = HUD::_GET_LABEL_TEXT(vehname);

				sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnOption(car); });
			}

		});


		g_UiManager->AddSubmenu<RegularSubmenu>("Coupes", Coupes, [](RegularSubmenu* sub)
		{


			for (auto car : Coupes1) {

				Hash model = MISC::GET_HASH_KEY(car);
				const char* vehname = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(model);
				const char* name_veh = HUD::_GET_LABEL_TEXT(vehname);

				sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnOption(car); });
			}
		});


		g_UiManager->AddSubmenu<RegularSubmenu>("Muscle", Muscle, [](RegularSubmenu* sub)
		{

			for (auto car : Muscle1) {

				Hash model = MISC::GET_HASH_KEY(car);
				const char* vehname = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(model);
				const char* name_veh = HUD::_GET_LABEL_TEXT(vehname);

				sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnOption(car); });
			}

		});


		g_UiManager->AddSubmenu<RegularSubmenu>("Utility", Utility, [](RegularSubmenu* sub)
		{

			for (auto car : Utility1) {

				Hash model = MISC::GET_HASH_KEY(car);
				const char* vehname = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(model);
				const char* name_veh = HUD::_GET_LABEL_TEXT(vehname);

				sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnOption(car); });
			}

		});


		g_UiManager->AddSubmenu<RegularSubmenu>("Commercial", Commercial, [](RegularSubmenu* sub)
		{

			for (auto car : Commercial1) {

				Hash model = MISC::GET_HASH_KEY(car);
				const char* vehname = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(model);
				const char* name_veh = HUD::_GET_LABEL_TEXT(vehname);

				sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnOption(car); });
			}

		});


		g_UiManager->AddSubmenu<RegularSubmenu>("Compacts", Compacts, [](RegularSubmenu* sub)
		{


			for (auto car : Compacts1) {

				Hash model = MISC::GET_HASH_KEY(car);
				const char* vehname = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(model);
				const char* name_veh = HUD::_GET_LABEL_TEXT(vehname);

				sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnOption(car); });
			}
		});


		g_UiManager->AddSubmenu<RegularSubmenu>("SUV", SUV, [](RegularSubmenu* sub)
		{


			for (auto car : SUVs1) {

				Hash model = MISC::GET_HASH_KEY(car);
				const char* vehname = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(model);
				const char* name_veh = HUD::_GET_LABEL_TEXT(vehname);

				sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnOption(car); });
			}
		});


		g_UiManager->AddSubmenu<RegularSubmenu>("Motorcycles", Motorcycles, [](RegularSubmenu* sub)
		{

			for (auto car : Motorcycles1) {

				Hash model = MISC::GET_HASH_KEY(car);
				const char* vehname = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(model);
				const char* name_veh = HUD::_GET_LABEL_TEXT(vehname);

				sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnOption(car); });
			}

		});


		g_UiManager->AddSubmenu<RegularSubmenu>("Helicopters", Helicopters, [](RegularSubmenu* sub)
		{

			for (auto car : Helicopters1) {

				Hash model = MISC::GET_HASH_KEY(car);
				const char* vehname = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(model);
				const char* name_veh = HUD::_GET_LABEL_TEXT(vehname);

				sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnOption(car); });
			}

		});


		g_UiManager->AddSubmenu<RegularSubmenu>("Planes", Planes, [](RegularSubmenu* sub)
		{

			for (auto car : Planes1) {

				Hash model = MISC::GET_HASH_KEY(car);
				const char* vehname = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(model);
				const char* name_veh = HUD::_GET_LABEL_TEXT(vehname);

				sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnOption(car); });
			}

		});


		g_UiManager->AddSubmenu<RegularSubmenu>("Emergency", Emergency, [](RegularSubmenu* sub)
		{

			for (auto car : Emergency1) {

				Hash model = MISC::GET_HASH_KEY(car);
				const char* vehname = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(model);
				const char* name_veh = HUD::_GET_LABEL_TEXT(vehname);

				sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnOption(car); });
			}

		});


		g_UiManager->AddSubmenu<RegularSubmenu>("Industrial", Industrial, [](RegularSubmenu* sub)
		{

			for (auto car : Industrial1) {

				Hash model = MISC::GET_HASH_KEY(car);
				const char* vehname = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(model);
				const char* name_veh = HUD::_GET_LABEL_TEXT(vehname);

				sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnOption(car); });
			}

		});


		g_UiManager->AddSubmenu<RegularSubmenu>("Trailer", Trailer, [](RegularSubmenu* sub)
		{

			for (auto car : Trailer1) {

				Hash model = MISC::GET_HASH_KEY(car);
				const char* vehname = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(model);
				const char* name_veh = HUD::_GET_LABEL_TEXT(vehname);

				sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnOption(car); });
			}

		});


		g_UiManager->AddSubmenu<RegularSubmenu>("Trains", Trains, [](RegularSubmenu* sub)
		{

			for (auto car : Trains1) {

				Hash model = MISC::GET_HASH_KEY(car);
				const char* vehname = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(model);
				const char* name_veh = HUD::_GET_LABEL_TEXT(vehname);

				sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnOption(car); });
			}

		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Service", Service, [](RegularSubmenu* sub)
		{

			for (auto car : Service1) {

				Hash model = MISC::GET_HASH_KEY(car);
				const char* vehname = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(model);
				const char* name_veh = HUD::_GET_LABEL_TEXT(vehname);

				sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnOption(car); });
			}

		});


		g_UiManager->AddSubmenu<RegularSubmenu>("Military", Military, [](RegularSubmenu* sub)
		{

			for (auto car : Military1) {

				Hash model = MISC::GET_HASH_KEY(car);
				const char* vehname = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(model);
				const char* name_veh = HUD::_GET_LABEL_TEXT(vehname);

				sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnOption(car); });
			}

		});


		g_UiManager->AddSubmenu<RegularSubmenu>("Vehicle", TPOVehicle, [](RegularSubmenu* sub)
		{

			sub->AddOption<RegularOption>("Bennys Garage", nullptr, [] {  Teleport(-196.349442, -1303.103271, 30.650515); });
			sub->AddOption<RegularOption>("Burton", nullptr, [] {  Teleport(-370.533752f, -130.402649f, 38.197617f); });
			sub->AddOption<RegularOption>("Beekers Garage", nullptr, [] {  Teleport(116.223175f, 6606.201660f, 31.462461f); });
			sub->AddOption<RegularOption>("Los Santos Airport", nullptr, [] {  Teleport(-1135.707275f, -1987.154175f, 12.976217f); });
			sub->AddOption<RegularOption>("La Mesa", nullptr, [] {  Teleport(709.295471f, -1081.996216f, 21.975765f); });
			sub->AddOption<RegularOption>("Sandy Shores", nullptr, [] {  Teleport(1176.822632f, 2657.973145, 37.370682); });



		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Sports", TPSports, [](RegularSubmenu* sub)
		{

			sub->AddOption<RegularOption>("Davis", nullptr, [] {  Teleport(1198.025757f, -471.814178f, 68.659100f); });
			sub->AddOption<RegularOption>("Havick", nullptr, [] {  Teleport(-27.791309f, -136.863708f, 56.515392f); });
			sub->AddOption<RegularOption>("Mirror Park", nullptr, [] {  Teleport(1678.057495f, 4819.882324f, 41.299820f); });
			sub->AddOption<RegularOption>("Polito Bay", nullptr, [] {  Teleport(-286.639038f, 6239.389648f, 30.567659f); });
			sub->AddOption<RegularOption>("Rockford Hills", nullptr, [] {  Teleport(-829.426392f, -191.582718f, 36.921909f); });
			sub->AddOption<RegularOption>("Sandy Shores", nullptr, [] {  Teleport(1938.357910f, 3717.808350f, 31.607185f); });
			sub->AddOption<RegularOption>("Vespucci", nullptr, [] {  Teleport(-1294.995239f, -1117.641724f, 6.157444f); });



		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Stores", TPStores, [](RegularSubmenu* sub)
		{


			sub->AddOption<RegularOption>("Binco - Vespucci", nullptr, [] {  Teleport(-814.432800f, -1085.986938f, 10.567306f); });
			sub->AddOption<RegularOption>("Binco - Strawberry", nullptr, [] {  Teleport(411.403564f, -806.654907f, 28.742212f); });
			sub->AddOption<RegularOption>("Discount Store - Grand Senora", nullptr, [] {  Teleport(1179.679688f, 2691.378662f, 37.124043f); });
			sub->AddOption<RegularOption>("Discount Store - Grapeseed", nullptr, [] {  Teleport(1678.057495f, 4819.882324f, 41.299820f); });
			sub->AddOption<RegularOption>("Discount Store - Great Chaparral", nullptr, [] {  Teleport(-1089.404785f, 2697.033447f, 19.442095f); });
			sub->AddOption<RegularOption>("Discount Store - Polito Bay", nullptr, [] {  Teleport(-4.509100f, 6521.252930f, 30.571024f); });
			sub->AddOption<RegularOption>("Discount Store - Strawberry", nullptr, [] {  Teleport(89.320786f, -1392.317627f, 28.800083f); });
			sub->AddOption<RegularOption>("Masks - Vespucci Beach", nullptr, [] {  Teleport(-1342.185913f, -1280.013428f, 4.443256f); });
			sub->AddOption<RegularOption>("Ponsonbys - Burton", nullptr, [] {  Teleport(-148.234741f, -308.074463f, 38.104240f); });
			sub->AddOption<RegularOption>("Ponsonbys - Rockford Hills", nullptr, [] {  Teleport(-725.551453f, -162.833710f, 36.570301f); });
			sub->AddOption<RegularOption>("Ponsonbys - Morningwood", nullptr, [] {  Teleport(-1460.654419f, -227.550964f, 48.728519f); });
			sub->AddOption<RegularOption>("Suburban - Havick", nullptr, [] {  Teleport(134.122055f, -200.211334f, 53.864090f); });
			sub->AddOption<RegularOption>("Suburban - Del Perro", nullptr, [] {  Teleport(-1210.620361f, -784.160217f, 16.549015f); });
			sub->AddOption<RegularOption>("Suburban - Chumash", nullptr, [] {  Teleport(-3166.560547f, 1059.929688f, 20.65988f); });
			sub->AddOption<RegularOption>("Suburban - Harmony", nullptr, [] {  Teleport(618.081604f, 2745.795410f, 42.276966f); });
			sub->AddOption<RegularOption>("24/7 - Banham Canyon", nullptr, [] {  Teleport(-3037.177246f, 590.165283f, 7.78449f); });
			sub->AddOption<RegularOption>("24/7 - Chumash", nullptr, [] {  Teleport(-3237.171387f, 1004.163879f, 12.354364f); });
			sub->AddOption<RegularOption>("24/7 - Grand Senora Desert", nullptr, [] {  Teleport(2683.951172f, 3281.507324f, 55.347145f); });
			sub->AddOption<RegularOption>("24/7 - Harmony", nullptr, [] {  Teleport(543.490784f, 2675.008301f, 42.162228f); });
			sub->AddOption<RegularOption>("24/7 - Mount Chiliad", nullptr, [] {  Teleport(1730.461914f, 6410.027344f, 35.384476f); });
			sub->AddOption<RegularOption>("24/7 - Sandy Shores - Niland Ave", nullptr, [] {  Teleport(1966.198853f, 3738.300537f, 32.251864f); });
			sub->AddOption<RegularOption>("24/7 - Strawberry", nullptr, [] {  Teleport(28.123456f, -1351.123456f, 29.123456f); });
			sub->AddOption<RegularOption>("24/7 - Tataviam Mountains", nullptr, [] {  Teleport(2561.452881f, 384.998932f, 108.532890f); });
			sub->AddOption<RegularOption>("24/7 - Vinewood", nullptr, [] {  Teleport(376.287079f, 322.833252f, 103.418564f); });
			sub->AddOption<RegularOption>("Limited LTD Gasoline - Grapeseed", nullptr, [] {  Teleport(1695.349267f, 4932.165039f, 41.826122f); });
			sub->AddOption<RegularOption>("Limited LTD Gasoline - Grove St", nullptr, [] {  Teleport(-54.6644520f, -1758.542847f, 29.432362f); });
			sub->AddOption<RegularOption>("Limited LTD Gasoline - Little Seoul", nullptr, [] {  Teleport(-712.059570f, -919.167175f, 18.835764f); });
			sub->AddOption<RegularOption>("Limited LTD Gasoline - Mirror Park", nullptr, [] {  Teleport(1159.879761f, -329.307495f, 68.822609f); });
			sub->AddOption<RegularOption>("Limited LTD Gasoline - Richman Glen", nullptr, [] {  Teleport(-1821.082275f, 787.085510f, 137.868439f); });
			sub->AddOption<RegularOption>("Rob's Liqour - Banham Canyon", nullptr, [] {  Teleport(-2976.010742f, 391.081024f, 15.013429f); });
			sub->AddOption<RegularOption>("Rob's Liqour - Morningwood", nullptr, [] {  Teleport(-1493.295166f, -385.783142f, 39.841709f); });
			sub->AddOption<RegularOption>("Rob's Liqour - Murrieta Heights", nullptr, [] {  Teleport(1142.654053f, -980.857788f, 45.945202f); });
			sub->AddOption<RegularOption>("Rob's Liqour - Vespucci Canals", nullptr, [] {  Teleport(-1227.629639f, -900.404236f, 12.366796f); });
			sub->AddOption<RegularOption>("Scoops - Grand Senora Desert", nullptr, [] {  Teleport(1166.794556f, 2700.728027f, 38.224377f); });
			sub->AddOption<RegularOption>("N/A - Algonquin Blvd", nullptr, [] {  Teleport(1394.642578f, 3598.434082f, 34.892509f); });


		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Airports", TPAir, [](RegularSubmenu* sub)
		{

			sub->AddOption<RegularOption>("Fort Zancudo ATC entrance", nullptr, [] {  Teleport(-2344.373f, 3267.498f, 32.811f); });
			sub->AddOption<RegularOption>("Fort Zancudo ATC top floor", nullptr, [] {  Teleport(-2358.132f, 3249.754f, 101.451f); });

		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Fun", TPFun, [](RegularSubmenu* sub)
		{


			sub->AddOption<RegularOption>("Burnt FIB Building", nullptr, [] {  Teleport(153.344131f, -734.524353f, 253.848343f); });
			sub->AddOption<RegularOption>("FIB Roof", nullptr, [] {  Teleport(150.126f, -754.591f, 262.865f); });
			sub->AddOption<RegularOption>("FIB Top Floor", nullptr, [] {  Teleport(135.733f, -749.216f, 258.152f); });
			sub->AddOption<RegularOption>("IAA Roof", nullptr, [] {  Teleport(134.085f, -637.859f, 262.851f); });
			sub->AddOption<RegularOption>("IAA Office", nullptr, [] {  Teleport(117.220f, -620.938f, 206.047f); });
			sub->AddOption<RegularOption>("Mile High Club", nullptr, [] {  Teleport(-144.274f, -946.813f, 269.135f); });
			sub->AddOption<RegularOption>("Play Boy Mansion", nullptr, [] {  Teleport(-1475.234f, 167.088f, 55.841f); });
			sub->AddOption<RegularOption>("Strip Club", nullptr, [] {  Teleport(135.548096f, -1308.388306f, 28.344141f); });
			sub->AddOption<RegularOption>("Strip Club - DJ Booth", nullptr, [] {  Teleport(122.416924f, -1281.09976f, 29.480480f); });
			sub->AddOption<RegularOption>("Torture Room X", nullptr, [] {  Teleport(147.170f, -2201.804f, 4.688f); });
			sub->AddOption<RegularOption>("Weed Farm", nullptr, [] {  Teleport(2208.777f, 5578.235f, 53.735f); });




			sub->AddOption<RegularOption>("Abandon Mine", nullptr, [] {  Teleport(-595.342f, 2086.008f, 131.412f); });
			sub->AddOption<RegularOption>("Airplane Graveyard Airplane Tail", nullptr, [] {  Teleport(2395.096f, 3049.616f, 60.053f); });
			sub->AddOption<RegularOption>("Altruist Cult Camp", nullptr, [] {  Teleport(-1170.841f, 4926.646f, 224.295f); });
			sub->AddOption<RegularOption>("Beach Skatepark", nullptr, [] {  Teleport(-1374.881f, -1398.835f, 6.141f); });
			sub->AddOption<RegularOption>("Calafia Train Bridge", nullptr, [] {  Teleport(-517.869f, 4425.284f, 89.795897f); });
			sub->AddOption<RegularOption>("Cargo Ship", nullptr, [] {  Teleport(899.678f, -2882.191f, 19.013f); });
			sub->AddOption<RegularOption>("Casino", nullptr, [] {  Teleport(925.329f, 46.152f, 80.908f); });
			sub->AddOption<RegularOption>("Chicken", nullptr, [] {  Teleport(-31.010f, 6316.830f, 40.083f); });
			sub->AddOption<RegularOption>("Chumash Historic Family Pier", nullptr, [] {  Teleport(-3426.683f, 967.738f, 8.347f); });
			sub->AddOption<RegularOption>("Del Perro Pier", nullptr, [] {  Teleport(-1850.127f, -1231.751f, 13.017f); });
			sub->AddOption<RegularOption>("Devin Weston's House", nullptr, [] {  Teleport(-2639.872f, 1866.812f, 160.135f); });
			sub->AddOption<RegularOption>("El Gordo Lighthouse - Floor", nullptr, [] {  Teleport(3422.703125f, 5174.532715f, 7.382134f); });
			sub->AddOption<RegularOption>("El Gordo Lighthouse - Top", nullptr, [] {  Teleport(3431.182617f, 5173.422852f, 41.371891f); });
			sub->AddOption<RegularOption>("Epsilon Building", nullptr, [] {  Teleport(-695.025f, 82.955f, 55.855f); });
			sub->AddOption<RegularOption>("Floyd's Apartment", nullptr, [] {  Teleport(-1150.703f, -1520.713f, 10.633f); });
			sub->AddOption<RegularOption>("Galileo Observatory Roof", nullptr, [] {  Teleport(-438.804f, 1076.097f, 352.411f); });
			sub->AddOption<RegularOption>("God's thumb", nullptr, [] {  Teleport(-1006.402f, 6272.383f, 1.503f); });
			sub->AddOption<RegularOption>("Hippy Camp", nullptr, [] {  Teleport(2476.712f, 3789.645f, 41.226f); });
			sub->AddOption<RegularOption>("Humane Labs Entrance", nullptr, [] {  Teleport(3613.750000f, 3747.294180f, 28.59690090f); });
			sub->AddOption<RegularOption>("Humane Labs Tunnel", nullptr, [] {  Teleport(3525.495f, 3705.301f, 20.992f); });
			sub->AddOption<RegularOption>("Jolene Ghost - Time 23:00/24:00", nullptr, [] {  Teleport(3059.620f, 5564.246f, 197.091f); });
			sub->AddOption<RegularOption>("Kortz Center", nullptr, [] {  Teleport(-2243.810f, 264.048f, 174.615f); });
			sub->AddOption<RegularOption>("La Puerta Freeway Bridge", nullptr, [] {  Teleport(-543.932f, -2225.543f, 122.366f); });
			sub->AddOption<RegularOption>("Land Act Dam", nullptr, [] {  Teleport(1660.369f, -12.013f, 170.020f); });
			sub->AddOption<RegularOption>("Lester's House", nullptr, [] {  Teleport(1273.898f, -1719.304f, 54.771f); });
			sub->AddOption<RegularOption>("Little Portola", nullptr, [] {  Teleport(-635.463f, -242.402f, 38.175f); });
			sub->AddOption<RegularOption>("Little Seoul", nullptr, [] {  Teleport(-889.655f, -853.499f, 20.566f); });
			sub->AddOption<RegularOption>("Marlowe Vineyards", nullptr, [] {  Teleport(-1868.971f, 2095.674f, 139.115f); });
			sub->AddOption<RegularOption>("Merryweather Dock", nullptr, [] {  Teleport(486.417f, -3339.692f, 6.070f); });
			sub->AddOption<RegularOption>("Mirror Park", nullptr, [] {  Teleport(1070.206f, -711.958f, 58.483f); });
			sub->AddOption<RegularOption>("Mount Gordo", nullptr, [] {  Teleport(2877.633f, 5911.078f, 369.624f); });
			sub->AddOption<RegularOption>("NOOSE Headquarters", nullptr, [] {  Teleport(2535.243f, -383.799f, 92.993f); });
			sub->AddOption<RegularOption>("Pacific Bluffs Country Club", nullptr, [] {  Teleport(-3022.222f, 39.968f, 13.611f); });
			sub->AddOption<RegularOption>("Paleto Bay Pier", nullptr, [] {  Teleport(-275.522f, 6635.835f, 7.425f); });
			sub->AddOption<RegularOption>("Paleto Forest Sawmill Chimney", nullptr, [] {  Teleport(-549.467f, 5308.221f, 114.146f); });
			sub->AddOption<RegularOption>("Palmer-Taylor Power Station", nullptr, [] {  Teleport(2732.931f, 1577.540f, 83.671f); });
			sub->AddOption<RegularOption>("Police Station", nullptr, [] {  Teleport(436.491f, -982.172f, 30.699f); });
			sub->AddOption<RegularOption>("Quarry", nullptr, [] {  Teleport(2954.196f, 2783.410f, 41.004f); });
			sub->AddOption<RegularOption>("Rebel Radio", nullptr, [] {  Teleport(736.153f, 2583.143f, 79.634f); });
			sub->AddOption<RegularOption>("Rocket", nullptr, [] {  Teleport(1608.698f, 6438.096f, 37.637f); });
			sub->AddOption<RegularOption>("Sandy Shores Crane", nullptr, [] {  Teleport(1051.209f, 2280.452f, 89.727f); });
			sub->AddOption<RegularOption>("Satellite Dish Antenna", nullptr, [] {  Teleport(2034.988f, 2953.105f, 74.602f); });
			sub->AddOption<RegularOption>("Satellite Dishes", nullptr, [] {  Teleport(2062.123f, 2942.055f, 47.431f); });
			sub->AddOption<RegularOption>("Sisyphus Theater Stage", nullptr, [] {  Teleport(205.316f, 1167.378f, 227.005f); });
			sub->AddOption<RegularOption>("Snowman", nullptr, [] {  Teleport(971.245f, -1620.993f, 30.111f); });
			sub->AddOption<RegularOption>("Stab City", nullptr, [] {  Teleport(126.975f, 3714.419f, 46.827f); });
			sub->AddOption<RegularOption>("The Richman Hotel", nullptr, [] {  Teleport(-1330.911f, 340.871f, 64.078f); });
			sub->AddOption<RegularOption>("Top of Mt Chilad", nullptr, [] {  Teleport(450.718f, 5566.614f, 806.183f); });
			sub->AddOption<RegularOption>("Trevor's Meth Lab", nullptr, [] {  Teleport(1391.773f, 3608.716f, 38.942f); });
			sub->AddOption<RegularOption>("Underpass Skatepark", nullptr, [] {  Teleport(718.341f, -1218.714f, 26.014f); });
			sub->AddOption<RegularOption>("University of San Andreas", nullptr, [] {  Teleport(-1696.866f, 142.747f, 64.372f); });
			sub->AddOption<RegularOption>("Vinewood Bowl Stage", nullptr, [] {  Teleport(686.245f, 577.950f, 130.461f); });
			sub->AddOption<RegularOption>("Vinewood sign", nullptr, [] {  Teleport(711.362f, 1198.134f, 348.526f); });
			sub->AddOption<RegularOption>("Windmill Top", nullptr, [] {  Teleport(2026.677f, 1842.684f, 133.313f); });





			sub->AddOption<RegularOption>("Blaine County Bank", nullptr, [] {  Teleport(-109.299f, 6464.035f, 31.627f); });
			sub->AddOption<RegularOption>("Pacific Standard Bank", nullptr, [] {  Teleport(235.046f, 216.434f, 106.287f); });
			sub->AddOption<RegularOption>("Pacific Standard Bank Vault", nullptr, [] {  Teleport(255.851f, 217.030f, 101.683f); });
			sub->AddOption<RegularOption>("Maze Bank Arena Roof", nullptr, [] {  Teleport(-324.300f, -1968.545f, 67.002f); });
			sub->AddOption<RegularOption>("Maze Bank Roof", nullptr, [] {  Teleport(-75.015f, -818.215f, 326.176f); });


		});




		g_UiManager->AddSubmenu<RegularSubmenu>("Service", TPServices, [](RegularSubmenu* sub)
		{



			sub->AddOption<RegularOption>("Fire Station - Davis, Macdonald", nullptr, [] {  Teleport(213.927261f, -1639.267090f, 29.692514f); });
			sub->AddOption<RegularOption>("Fire Station - Fort Zancudo", nullptr, [] {  Teleport(-2113.866699f, 2847.312988f, 32.558411f); });
			sub->AddOption<RegularOption>("Fire Station - LS HQ", nullptr, [] {  Teleport(-639.470703f, -122.451233f, 38.112556f); });
			sub->AddOption<RegularOption>("Fire Station - LS Station 7", nullptr, [] {  Teleport(1200.554443f, -1457.295044f, 35.248623f); });
			sub->AddOption<RegularOption>("Fire Station - Paleto Bay", nullptr, [] {  Teleport(-387.178131f, 6125.819336f, 31.586800f); });
			sub->AddOption<RegularOption>("Fire Station - Sandy Shores", nullptr, [] {  Teleport(1691.670166f, 3579.191895f, 35.636360f); });
			sub->AddOption<RegularOption>("Hospital - Lifeguard 1", nullptr, [] {  Teleport(-1290.980835f, -1757.102905f, 3.058975f); });
			sub->AddOption<RegularOption>("Hospital - Lifeguard 2", nullptr, [] {  Teleport(-1373.146851f, -1627.157837f, 3.364384f); });
			sub->AddOption<RegularOption>("Hospital - Lifeguard 3", nullptr, [] {  Teleport(-1432.086426f, -1512.424316f, 3.214696f); });
			sub->AddOption<RegularOption>("Hospital - Lifeguard 4", nullptr, [] {  Teleport(-1468.421753f, -1391.712158f, 3.525731f); });
			sub->AddOption<RegularOption>("Hospital - Lifeguard 5", nullptr, [] {  Teleport(-1520.238281f, -1275.765625f, 2.950766f); });
			sub->AddOption<RegularOption>("Hospital - Lifeguard 6", nullptr, [] {  Teleport(-1560.793945f, -1158.407593f, 3.295668f); });
			sub->AddOption<RegularOption>("Hospital - Lifeguard 7", nullptr, [] {  Teleport(-1798.075684f, -858.578857f, 8.840805f); });
			sub->AddOption<RegularOption>("Hospital - Lifeguard 8", nullptr, [] {  Teleport(-1904.379150f, -713.960449f, 8.344188f); });
			sub->AddOption<RegularOption>("Hospital - Lifeguard 9", nullptr, [] {  Teleport(-2006.548340f, -560.289368f, 12.898447f); });
			sub->AddOption<RegularOption>("Hospital - Paleto Bay", nullptr, [] {  Teleport(-440.541779f, 6019.399902f, 31.262650f); });
			sub->AddOption<RegularOption>("Hospital - Rockford Hills", nullptr, [] {  Teleport(-475.191345f, -353.762787f, 34.002174f); });
			sub->AddOption<RegularOption>("Hospital - Sandy Shores", nullptr, [] {  Teleport(1850.026367f, 3679.041748f, 33.983913f); });
			sub->AddOption<RegularOption>("Hospital - Strawberry Ave", nullptr, [] {  Teleport(337.111145f, -1393.440063f, 32.257248f); });
			sub->AddOption<RegularOption>("Hospital - textile City", nullptr, [] {  Teleport(376.534027f, -581.015381f, 28.707024f); });
			sub->AddOption<RegularOption>("Police - La Mesa", nullptr, [] {  Teleport(817.000000f, -1290.000000f, 26.146124f); });
			sub->AddOption<RegularOption>("Police - Mission Row", nullptr, [] {  Teleport(429.601593f, -982.458923f, 30.463333f); });
			sub->AddOption<RegularOption>("Police - Paleto Bay", nullptr, [] {  Teleport(-440.541779f, 6019.399902f, 31.262650f); });
			sub->AddOption<RegularOption>("Police - Rancho", nullptr, [] {  Teleport(360.000000f, -1583.000000f, 29.105696f); });
			sub->AddOption<RegularOption>("Police - Rockford Hills", nullptr, [] {  Teleport(-557.245789f, -142.276871f, 38.247066f); });
			sub->AddOption<RegularOption>("Police - Sandy Shores", nullptr, [] {  Teleport(1858.026367f, 3679.041748f, 33.983913f); });
			sub->AddOption<RegularOption>("Police - Vespucci Beach", nullptr, [] {  Teleport(-1312.137085f, -1528.899658f, 4.159692f); });
			sub->AddOption<RegularOption>("Police - Vespucci HQ", nullptr, [] {  Teleport(-1110.682617f, -846.652466f, 19.361103f); });
			sub->AddOption<RegularOption>("Police - Vinewood", nullptr, [] {  Teleport(642.722046f, 0.252486f, 82.890823f); });
			sub->AddOption<RegularOption>("Police - Vinewood Hills Ranger", nullptr, [] {  Teleport(388.549255f, 791.305176f, 190.476166f); });



		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Apartments", TPAparts, [](RegularSubmenu* sub)
		{


			sub->AddOption<RegularOption>("3 Alta St", nullptr, [] {  Teleport(-261.747620f, -976.950623f, 30.971106f); });
			sub->AddOption<RegularOption>("4 Integrit Way", nullptr, [] {  Teleport(-54.668861f, -588.563904f, 36.193024f); });
			sub->AddOption<RegularOption>("Bay City Ave Apt 45", nullptr, [] {  Teleport(-986.981323f, -1445.468018f, 5.942831f); });
			sub->AddOption<RegularOption>("Blvd Del Perro Apt 18", nullptr, [] {  Teleport(-1611.278442f, -424.959167f, 40.691673f); });
			sub->AddOption<RegularOption>("Cougar Ave Apt 19", nullptr, [] {  Teleport(-1538.185791f, -328.037628f, 47.265511f); });
			sub->AddOption<RegularOption>("Dream Tower Apt 15", nullptr, [] {  Teleport(-755.427124f, -749.572021f, 26.665794f); });
			sub->AddOption<RegularOption>("Eclipse Towers", nullptr, [] {  Teleport(-773.505920f, 296.763641f, 85.830109f); });
			sub->AddOption<RegularOption>("Milton Dr 0504", nullptr, [] {  Teleport(-635.008545f, 161.922287f, 59.699619f); });
			sub->AddOption<RegularOption>("Milton Dr Apt 13", nullptr, [] {  Teleport(-508.407379f, 112.594910f, 63.480057f); });
			sub->AddOption<RegularOption>("Power St 1162", nullptr, [] {  Teleport(269.939819f, -150.483261f, 64.293060f); });
			sub->AddOption<RegularOption>("Prosperity St Apt 21", nullptr, [] {  Teleport(-1556.567627f, -415.096069f, 42.539715f); });
			sub->AddOption<RegularOption>("Richard Majestic", nullptr, [] {  Teleport(-956.922424f, -403.93678f, 38.278751f); });
			sub->AddOption<RegularOption>("South Rockford Dr", nullptr, [] {  Teleport(-837.304504f, -849.619080f, 19.522774f); });
			sub->AddOption<RegularOption>("South Rockford Dr Apt 13", nullptr, [] {  Teleport(-818.702759f, -989.048035f, 13.501397f); });
			sub->AddOption<RegularOption>("The Royal Apt 19", nullptr, [] {  Teleport(-201.004333f, 91.132614f, 69.530350f); });
			sub->AddOption<RegularOption>("Vespucci Blvd Apt 1", nullptr, [] {  Teleport(-671.988403f, -854.607910f, 23.965218f); });
			sub->AddOption<RegularOption>("Weazel Plaza", nullptr, [] {  Teleport(-924.684082f, -465.046417f, 36.882763f); });

		});


		g_UiManager->AddSubmenu<RegularSubmenu>("Time", Timeee, [](RegularSubmenu* sub)
		{

			sub->AddOption<RegularOption>("Add Hour", nullptr, [] { Time_h + 1;  TIMEBACK(Time_h, 23); });
			sub->AddOption<RegularOption>("Add Minute", nullptr, [] { Time_m + 1;  TIMEBACK(Time_m, 59); });
			sub->AddOption<RegularOption>("Add Second", nullptr, [] { Time_s + 1; TIMEBACK(Time_s, 23); });
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Weather", Weather, [](RegularSubmenu* sub)
		{

			sub->AddOption<RegularOption>("Clear", nullptr, []
			{
				WorldWeather((char*)"CLEAR");

			});

			sub->AddOption<RegularOption>("Extra Sunny", nullptr, []
			{
				WorldWeather((char*)"EXTRASUNNY");

			});

			sub->AddOption<RegularOption>("Clouds", nullptr, []
			{
				WorldWeather((char*)"CLOUDS");

			});
			sub->AddOption<RegularOption>("Over Cast", nullptr, []
			{
				WorldWeather((char*)"OVERCAST");

			});
			sub->AddOption<RegularOption>("Rain", nullptr, []
			{
				WorldWeather((char*)"RAIN");

			});
			sub->AddOption<RegularOption>("Clearing", nullptr, []
			{
				WorldWeather((char*)"CLEARING");

			});
			sub->AddOption<RegularOption>("Thunder", nullptr, []
			{
				WorldWeather((char*)"THUNDER");

			});
			sub->AddOption<RegularOption>("Smog", nullptr, []
			{
				WorldWeather((char*)"SMOG");

			});
			sub->AddOption<RegularOption>("Foggy", nullptr, []
			{
				WorldWeather((char*)"FOGGY");

			});
			sub->AddOption<RegularOption>("Xmas", nullptr, []
			{
				WorldWeather((char*)"XMAS");

			});
			sub->AddOption<RegularOption>("Light Snow", nullptr, []
			{
				WorldWeather((char*)"SNOWLIGHT");

			});
			sub->AddOption<RegularOption>("Blizzard", nullptr, []
			{
				WorldWeather((char*)"BLIZZARD");

			});
			sub->AddOption<RegularOption>("Random", nullptr, []
			{
				MISC::SET_RANDOM_WEATHER_TYPE();
			});

		});

		g_UiManager->AddSubmenu<RegularSubmenu>("World Speed", WorldSpeed_, [](RegularSubmenu* sub)
		{

			sub->AddOption<RegularOption>("Normal", nullptr, []
			{
				WorldSpeed(1.0f);
			});

			sub->AddOption<RegularOption>("Slow", nullptr, []
			{
				WorldSpeed(0.8f);
			});

			sub->AddOption<RegularOption>("More SLow", nullptr, []
			{
				WorldSpeed(0.5f);
			});

			sub->AddOption<RegularOption>("Ultra Slow", nullptr, []
			{
				WorldSpeed(0.1f);
			});
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Models", Models, [](RegularSubmenu* sub)
		{
			sub->AddOption<BoolOption<bool>>("Add To Database", nullptr, &add_to_folder, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<SubOption>("AmbientFemale", nullptr, AmbientFemale);
			sub->AddOption<SubOption>("AmbientMale", nullptr, AmbientMale);
			sub->AddOption<SubOption>("Cutscene", nullptr, Cutscene);
			sub->AddOption<SubOption>("GangFemale", nullptr, GangFemale);
			sub->AddOption<SubOption>("GangMale", nullptr, GangMale);
			sub->AddOption<SubOption>("Story", nullptr, Story);
			sub->AddOption<SubOption>("Multiplayer", nullptr, Multiplayer);
			sub->AddOption<SubOption>("ScenarioFemale", nullptr, ScenarioFemale);
			sub->AddOption<SubOption>("ScenarioMale", nullptr, ScenarioMale);
			sub->AddOption<SubOption>("StoryScenarioFemale", nullptr, StoryScenarioFemale);
			sub->AddOption<SubOption>("StoryScenarioMale", nullptr, StoryScenarioMale_);
		});
		g_UiManager->AddSubmenu<RegularSubmenu>("AmbientFemale", AmbientFemale, [](RegularSubmenu* sub)
		{
			sub->AddOption<RegularOption>("Beach Female", nullptr, [] {load_peds("a_f_m_beach_01"); });
			sub->AddOption<RegularOption>("Beach Tramp Female", nullptr, [] {load_peds("a_f_m_trampbeac_01"); });
			sub->AddOption<RegularOption>("Beach Young Female", nullptr, [] {load_peds("a_f_y_beach_01"); });
			sub->AddOption<RegularOption>("Beverly Hills Female", nullptr, [] {load_peds("a_f_m_bevhills_01"); });
			sub->AddOption<RegularOption>("Beverly Hills Female 2", nullptr, [] {load_peds("a_f_m_bevhills_02"); });
			sub->AddOption<RegularOption>("Beverly Hills Young Female", nullptr, [] {load_peds("a_f_y_bevhills_01"); });
			sub->AddOption<RegularOption>("Beverly Hills Young Female 2", nullptr, [] {load_peds("a_f_y_bevhills_02"); });
			sub->AddOption<RegularOption>("Beverly Hills Young Female 3", nullptr, [] {load_peds("a_f_y_bevhills_03"); });
			sub->AddOption<RegularOption>("Beverly Hills Young Female 4", nullptr, [] {load_peds("a_f_y_bevhills_04"); });
			sub->AddOption<RegularOption>("Bodybuilder Female", nullptr, [] {load_peds("a_f_m_bodybuild_01"); });
			sub->AddOption<RegularOption>("Business Female 2", nullptr, [] {load_peds("a_f_m_business_02"); });
			sub->AddOption<RegularOption>("Business Young Female", nullptr, [] {load_peds("a_f_y_business_01"); });
			sub->AddOption<RegularOption>("Business Young Female 2", nullptr, [] {load_peds("a_f_y_business_02"); });
			sub->AddOption<RegularOption>("Business Young Female 3", nullptr, [] {load_peds("a_f_y_business_03"); });
			sub->AddOption<RegularOption>("Business Young Female 4", nullptr, [] {load_peds("a_f_y_business_04"); });
			sub->AddOption<RegularOption>("Downtown Female", nullptr, [] {load_peds("a_f_m_downtown_01"); });
			sub->AddOption<RegularOption>("Dressy Female", nullptr, [] {load_peds("a_f_y_scdressy_01"); });
			sub->AddOption<RegularOption>("East SA Female", nullptr, [] {load_peds("a_f_m_eastsa_01"); });
			sub->AddOption<RegularOption>("East SA Female 2", nullptr, [] {load_peds("a_f_m_eastsa_02"); });
			sub->AddOption<RegularOption>("East SA Young Female", nullptr, [] {load_peds("a_f_y_eastsa_01"); });
			sub->AddOption<RegularOption>("East SA Young Female 2", nullptr, [] {load_peds("a_f_y_eastsa_02"); });
			sub->AddOption<RegularOption>("East SA Young Female 3", nullptr, [] {load_peds("a_f_y_eastsa_03"); });
			sub->AddOption<RegularOption>("Epsilon Female", nullptr, [] {load_peds("a_f_y_epsilon_01"); });
			sub->AddOption<RegularOption>("Fat Black Female", nullptr, [] {load_peds("a_f_m_fatbla_01"); });
			sub->AddOption<RegularOption>("Fat Cult Female", nullptr, [] {load_peds("a_f_m_fatcult_01"); });
			sub->AddOption<RegularOption>("Fat White Female", nullptr, [] {load_peds("a_f_m_fatwhite_01"); });
			sub->AddOption<RegularOption>("Female Agent", nullptr, [] {load_peds("a_f_y_femaleagent"); });
			sub->AddOption<RegularOption>("Fitness Female", nullptr, [] {load_peds("a_f_y_fitness_01"); });
			sub->AddOption<RegularOption>("Fitness Female 2", nullptr, [] {load_peds("a_f_y_fitness_02"); });
			sub->AddOption<RegularOption>("General Hot Young Female", nullptr, [] {load_peds("a_f_y_genhot_01"); });
			sub->AddOption<RegularOption>("General Street Old Female", nullptr, [] {load_peds("a_f_o_genstreet_01"); });
			sub->AddOption<RegularOption>("Casual Casino Guest", nullptr, [] {load_peds("a_f_y_gencaspat_01"); });
			sub->AddOption<RegularOption>("Formel Casino Guest", nullptr, [] {load_peds("a_f_y_smartcaspat_01"); });
			sub->AddOption<RegularOption>("Golfer Young Female", nullptr, [] {load_peds("a_f_y_golfer_01"); });
			sub->AddOption<RegularOption>("Hiker Female", nullptr, [] {load_peds("a_f_y_hiker_01"); });
			sub->AddOption<RegularOption>("Hippie Female", nullptr, [] {load_peds("a_f_y_hippie_01"); });
			sub->AddOption<RegularOption>("Hipster Female", nullptr, [] {load_peds("a_f_y_hipster_01"); });
			sub->AddOption<RegularOption>("Hipster Female 2", nullptr, [] {load_peds("a_f_y_hipster_02"); });
			sub->AddOption<RegularOption>("Hipster Female 3", nullptr, [] {load_peds("a_f_y_hipster_03"); });
			sub->AddOption<RegularOption>("Hipster Female 4", nullptr, [] {load_peds("a_f_y_hipster_04"); });
			sub->AddOption<RegularOption>("Indian Old Female", nullptr, [] {load_peds("a_f_o_indian_01"); });
			sub->AddOption<RegularOption>("Indian Young Female", nullptr, [] {load_peds("a_f_y_indian_01"); });
			sub->AddOption<RegularOption>("Jogger Female", nullptr, [] {load_peds("a_f_y_runner_01"); });
			sub->AddOption<RegularOption>("Juggalo Female", nullptr, [] {load_peds("a_f_y_juggalo_01"); });
			sub->AddOption<RegularOption>("Korean Female", nullptr, [] {load_peds("a_f_m_ktown_01"); });
			sub->AddOption<RegularOption>("Korean Female 2", nullptr, [] {load_peds("a_f_m_ktown_02"); });
			sub->AddOption<RegularOption>("Korean Old Female", nullptr, [] {load_peds("a_f_o_ktown_01"); });
			sub->AddOption<RegularOption>("Prologue Host Female", nullptr, [] {load_peds("a_f_m_prolhost_01"); });
			sub->AddOption<RegularOption>("Rural Meth Addict Female", nullptr, [] {load_peds("a_f_y_rurmeth_01"); });
			sub->AddOption<RegularOption>("Salton Female", nullptr, [] {load_peds("a_f_m_salton_01"); });
			sub->AddOption<RegularOption>("Salton Old Female", nullptr, [] {load_peds("a_f_o_salton_01"); });
			sub->AddOption<RegularOption>("Skater Female", nullptr, [] {load_peds("a_f_y_skater_01"); });
			sub->AddOption<RegularOption>("Skid Row Female", nullptr, [] {load_peds("a_f_m_skidrow_01"); });
			sub->AddOption<RegularOption>("South Central Female", nullptr, [] {load_peds("a_f_m_soucent_01"); });
			sub->AddOption<RegularOption>("South Central Female 2", nullptr, [] {load_peds("a_f_m_soucent_02"); });
			sub->AddOption<RegularOption>("South Central MC Female", nullptr, [] {load_peds("a_f_m_soucentmc_01"); });
			sub->AddOption<RegularOption>("South Central Old Female", nullptr, [] {load_peds("a_f_o_soucent_01"); });
			sub->AddOption<RegularOption>("South Central Old Female 2", nullptr, [] {load_peds("a_f_o_soucent_02"); });
			sub->AddOption<RegularOption>("South Central Young Female", nullptr, [] {load_peds("a_f_y_soucent_01"); });
			sub->AddOption<RegularOption>("South Central Young Female 2", nullptr, [] {load_peds("a_f_y_soucent_02"); });
			sub->AddOption<RegularOption>("South Central Young Female 3", nullptr, [] {load_peds("a_f_y_soucent_03"); });
			sub->AddOption<RegularOption>("Tennis Player Female", nullptr, [] {load_peds("a_f_y_tennis_01"); });
			sub->AddOption<RegularOption>("Topless", nullptr, [] {load_peds("a_f_y_topless_01"); });
			sub->AddOption<RegularOption>("Tourist Female", nullptr, [] {load_peds("a_f_m_tourist_01"); });
			sub->AddOption<RegularOption>("Tourist Young Female", nullptr, [] {load_peds("a_f_y_tourist_01"); });
			sub->AddOption<RegularOption>("Tourist Young Female 2", nullptr, [] {load_peds("a_f_y_tourist_02"); });
			sub->AddOption<RegularOption>("Tramp Female", nullptr, [] {load_peds("a_f_m_tramp_01"); });
			sub->AddOption<RegularOption>("Vinewood Female", nullptr, [] {load_peds("a_f_y_vinewood_01"); });
			sub->AddOption<RegularOption>("Vinewood Female 2", nullptr, [] {load_peds("a_f_y_vinewood_02"); });
			sub->AddOption<RegularOption>("Vinewood Female 3", nullptr, [] {load_peds("a_f_y_vinewood_03"); });
			sub->AddOption<RegularOption>("Vinewood Female 4", nullptr, [] {load_peds("a_f_y_vinewood_04"); });
			sub->AddOption<RegularOption>("Yoga Female", nullptr, [] {load_peds("a_f_y_yoga_01"); });
			sub->AddOption<RegularOption>("Club Customer Female 1", nullptr, [] {load_peds("a_f_y_clubcust_01"); });
			sub->AddOption<RegularOption>("Club Customer Female 2", nullptr, [] {load_peds("a_f_y_clubcust_02"); });
			sub->AddOption<RegularOption>("Club Customer Female 3", nullptr, [] {load_peds("a_f_y_clubcust_03"); });

		});

		g_UiManager->AddSubmenu<RegularSubmenu>("AmbientMale", AmbientMale, [](RegularSubmenu* sub)
		{
			sub->AddOption<RegularOption>("African American Male", nullptr, [] {load_peds("a_m_m_afriamer_01"); });
			sub->AddOption<RegularOption>("Altruist Cult Mid-Age Male", nullptr, [] {load_peds("a_m_m_acult_01"); });
			sub->AddOption<RegularOption>("Altruist Cult Old Male", nullptr, [] {load_peds("a_m_o_acult_01"); });
			sub->AddOption<RegularOption>("Altruist Cult Old Male 2", nullptr, [] {load_peds("a_m_o_acult_02"); });
			sub->AddOption<RegularOption>("Altruist Cult Young Male", nullptr, [] {load_peds("a_m_y_acult_01"); });
			sub->AddOption<RegularOption>("Altruist Cult Young Male 2", nullptr, [] {load_peds("a_m_y_acult_02"); });
			sub->AddOption<RegularOption>("Beach Male", nullptr, [] {load_peds("a_m_m_beach_01"); });
			sub->AddOption<RegularOption>("Beach Male 2", nullptr, [] {load_peds("a_m_m_beach_02"); });
			sub->AddOption<RegularOption>("Beach Muscle Male", nullptr, [] {load_peds("a_m_y_musclbeac_01"); });
			sub->AddOption<RegularOption>("Beach Muscle Male 2", nullptr, [] {load_peds("a_m_y_musclbeac_02"); });
			sub->AddOption<RegularOption>("Midlife Crisis Casino Bikers", nullptr, [] {load_peds("a_m_m_mlcrisis_01"); });
			sub->AddOption<RegularOption>("Casual Casino Guests", nullptr, [] {load_peds("a_m_y_gencaspat_01"); });
			sub->AddOption<RegularOption>("Formel Casino Guests", nullptr, [] {load_peds("a_m_y_smartcaspat_01"); });
			sub->AddOption<RegularOption>("Beach Old Male", nullptr, [] {load_peds("a_m_o_beach_01"); });
			sub->AddOption<RegularOption>("Beach Tramp Male", nullptr, [] {load_peds("a_m_m_trampbeac_01"); });
			sub->AddOption<RegularOption>("Beach Young Male", nullptr, [] {load_peds("a_m_y_beach_01"); });
			sub->AddOption<RegularOption>("Beach Young Male 2", nullptr, [] {load_peds("a_m_y_beach_02"); });
			sub->AddOption<RegularOption>("Beach Young Male 3", nullptr, [] {load_peds("a_m_y_beach_03"); });
			sub->AddOption<RegularOption>("Beverly Hills Male", nullptr, [] {load_peds("a_m_m_bevhills_01"); });
			sub->AddOption<RegularOption>("Beverly Hills Male 2", nullptr, [] {load_peds("a_m_m_bevhills_02"); });
			sub->AddOption<RegularOption>("Beverly Hills Young Male", nullptr, [] {load_peds("a_m_y_bevhills_01"); });
			sub->AddOption<RegularOption>("Beverly Hills Young Male 2", nullptr, [] {load_peds("a_m_y_bevhills_02"); });
			sub->AddOption<RegularOption>("Black Street Male", nullptr, [] {load_peds("a_m_y_stbla_01"); });
			sub->AddOption<RegularOption>("Black Street Male 2", nullptr, [] {load_peds("a_m_y_stbla_02"); });
			sub->AddOption<RegularOption>("Breakdancer Male", nullptr, [] {load_peds("a_m_y_breakdance_01"); });
			sub->AddOption<RegularOption>("Business Casual", nullptr, [] {load_peds("a_m_y_busicas_01"); });
			sub->AddOption<RegularOption>("Business Male", nullptr, [] {load_peds("a_m_m_business_01"); });
			sub->AddOption<RegularOption>("Business Young Male", nullptr, [] {load_peds("a_m_y_business_01"); });
			sub->AddOption<RegularOption>("Business Young Male 2", nullptr, [] {load_peds("a_m_y_business_02"); });
			sub->AddOption<RegularOption>("Business Young Male 3", nullptr, [] {load_peds("a_m_y_business_03"); });
			sub->AddOption<RegularOption>("Cyclist Male", nullptr, [] {load_peds("a_m_y_cyclist_01"); });
			sub->AddOption<RegularOption>("Downhill Cyclist", nullptr, [] {load_peds("a_m_y_dhill_01"); });
			sub->AddOption<RegularOption>("Downtown Male", nullptr, [] {load_peds("a_m_y_downtown_01"); });
			sub->AddOption<RegularOption>("East SA Male", nullptr, [] {load_peds("a_m_m_eastsa_01"); });
			sub->AddOption<RegularOption>("East SA Male 2", nullptr, [] {load_peds("a_m_m_eastsa_02"); });
			sub->AddOption<RegularOption>("East SA Young Male", nullptr, [] {load_peds("a_m_y_eastsa_01"); });
			sub->AddOption<RegularOption>("East SA Young Male 2", nullptr, [] {load_peds("a_m_y_eastsa_02"); });
			sub->AddOption<RegularOption>("Epsilon Male", nullptr, [] {load_peds("a_m_y_epsilon_01"); });
			sub->AddOption<RegularOption>("Epsilon Male 2", nullptr, [] {load_peds("a_m_y_epsilon_02"); });
			sub->AddOption<RegularOption>("Farmer", nullptr, [] {load_peds("a_m_m_farmer_01"); });
			sub->AddOption<RegularOption>("Fat Latino Male", nullptr, [] {load_peds("a_m_m_fatlatin_01"); });
			sub->AddOption<RegularOption>("Gay Male", nullptr, [] {load_peds("a_m_y_gay_01"); });
			sub->AddOption<RegularOption>("Gay Male 2", nullptr, [] {load_peds("a_m_y_gay_02"); });
			sub->AddOption<RegularOption>("General Fat Male", nullptr, [] {load_peds("a_m_m_genfat_01"); });
			sub->AddOption<RegularOption>("General Fat Male 2", nullptr, [] {load_peds("a_m_m_genfat_02"); });
			sub->AddOption<RegularOption>("General Street Old Male", nullptr, [] {load_peds("a_m_o_genstreet_01"); });
			sub->AddOption<RegularOption>("General Street Young Male", nullptr, [] {load_peds("a_m_y_genstreet_01"); });
			sub->AddOption<RegularOption>("General Street Young Male 2", nullptr, [] {load_peds("a_m_y_genstreet_02"); });
			sub->AddOption<RegularOption>("Golfer Male", nullptr, [] {load_peds("a_m_m_golfer_01"); });
			sub->AddOption<RegularOption>("Golfer Young Male", nullptr, [] {load_peds("a_m_y_golfer_01"); });
			sub->AddOption<RegularOption>("Hasidic Jew Male", nullptr, [] {load_peds("a_m_m_hasjew_01"); });
			sub->AddOption<RegularOption>("Hasidic Jew Young Male", nullptr, [] {load_peds("a_m_y_hasjew_01"); });
			sub->AddOption<RegularOption>("Hiker Male", nullptr, [] {load_peds("a_m_y_hiker_01"); });
			sub->AddOption<RegularOption>("Hillbilly Male", nullptr, [] {load_peds("a_m_m_hillbilly_01"); });
			sub->AddOption<RegularOption>("Hillbilly Male 2", nullptr, [] {load_peds("a_m_m_hillbilly_02"); });
			sub->AddOption<RegularOption>("Hippie Male", nullptr, [] {load_peds("a_m_y_hippy_01"); });
			sub->AddOption<RegularOption>("Hipster Male", nullptr, [] {load_peds("a_m_y_hipster_01"); });
			sub->AddOption<RegularOption>("Hipster Male 2", nullptr, [] {load_peds("a_m_y_hipster_02"); });
			sub->AddOption<RegularOption>("Hipster Male 3", nullptr, [] {load_peds("a_m_y_hipster_03"); });
			sub->AddOption<RegularOption>("Indian Male", nullptr, [] {load_peds("a_m_m_indian_01"); });
			sub->AddOption<RegularOption>("Indian Young Male", nullptr, [] {load_peds("a_m_y_indian_01"); });
			sub->AddOption<RegularOption>("Jetskier", nullptr, [] {load_peds("a_m_y_jetski_01"); });
			sub->AddOption<RegularOption>("Jogger Male", nullptr, [] {load_peds("a_m_y_runner_01"); });
			sub->AddOption<RegularOption>("Jogger Male 2", nullptr, [] {load_peds("a_m_y_runner_02"); });
			sub->AddOption<RegularOption>("Juggalo Male", nullptr, [] {load_peds("a_m_y_juggalo_01"); });
			sub->AddOption<RegularOption>("Korean Male", nullptr, [] {load_peds("a_m_m_ktown_01"); });
			sub->AddOption<RegularOption>("Korean Old Male", nullptr, [] {load_peds("a_m_o_ktown_01"); });
			sub->AddOption<RegularOption>("Korean Young Male", nullptr, [] {load_peds("a_m_y_ktown_01"); });
			sub->AddOption<RegularOption>("Korean Young Male 2", nullptr, [] {load_peds("a_m_y_ktown_02"); });
			sub->AddOption<RegularOption>("Latino Street Male 2", nullptr, [] {load_peds("a_m_m_stlat_02"); });
			sub->AddOption<RegularOption>("Latino Street Young Male", nullptr, [] {load_peds("a_m_y_stlat_01"); });
			sub->AddOption<RegularOption>("Latino Young Male", nullptr, [] {load_peds("a_m_y_latino_01"); });
			sub->AddOption<RegularOption>("Malibu Male", nullptr, [] {load_peds("a_m_m_malibu_01"); });
			sub->AddOption<RegularOption>("Meth Addict", nullptr, [] {load_peds("a_m_y_methhead_01"); });
			sub->AddOption<RegularOption>("Mexican Labourer", nullptr, [] {load_peds("a_m_m_mexlabor_01"); });
			sub->AddOption<RegularOption>("Mexican Rural", nullptr, [] {load_peds("a_m_m_mexcntry_01"); });
			sub->AddOption<RegularOption>("Mexican Thug", nullptr, [] {load_peds("a_m_y_mexthug_01"); });
			sub->AddOption<RegularOption>("Motocross Biker", nullptr, [] {load_peds("a_m_y_motox_01"); });
			sub->AddOption<RegularOption>("Motocross Biker 2", nullptr, [] {load_peds("a_m_y_motox_02"); });
			sub->AddOption<RegularOption>("OG Boss", nullptr, [] {load_peds("a_m_m_og_boss_01"); });
			sub->AddOption<RegularOption>("Paparazzi Male", nullptr, [] {load_peds("a_m_m_paparazzi_01"); });
			sub->AddOption<RegularOption>("Polynesian", nullptr, [] {load_peds("a_m_m_polynesian_01"); });
			sub->AddOption<RegularOption>("Polynesian Young", nullptr, [] {load_peds("a_m_y_polynesian_01"); });
			sub->AddOption<RegularOption>("Prologue Host Male", nullptr, [] {load_peds("a_m_m_prolhost_01"); });
			sub->AddOption<RegularOption>("Road Cyclist", nullptr, [] {load_peds("a_m_y_roadcyc_01"); });
			sub->AddOption<RegularOption>("Rural Meth Addict Male", nullptr, [] {load_peds("a_m_m_rurmeth_01"); });
			sub->AddOption<RegularOption>("Salton Male", nullptr, [] {load_peds("a_m_m_salton_01"); });
			sub->AddOption<RegularOption>("Salton Male 2", nullptr, [] {load_peds("a_m_m_salton_02"); });
			sub->AddOption<RegularOption>("Salton Male 3", nullptr, [] {load_peds("a_m_m_salton_03"); });
			sub->AddOption<RegularOption>("Salton Male 4", nullptr, [] {load_peds("a_m_m_salton_04"); });
			sub->AddOption<RegularOption>("Salton Old Male", nullptr, [] {load_peds("a_m_o_salton_01"); });
			sub->AddOption<RegularOption>("Salton Young Male", nullptr, [] {load_peds("a_m_y_salton_01"); });
			sub->AddOption<RegularOption>("Skater Male", nullptr, [] {load_peds("a_m_m_skater_01"); });
			sub->AddOption<RegularOption>("Skater Young Male", nullptr, [] {load_peds("a_m_y_skater_01"); });
			sub->AddOption<RegularOption>("Skater Young Male 2", nullptr, [] {load_peds("a_m_y_skater_02"); });
			sub->AddOption<RegularOption>("Skid Row Male", nullptr, [] {load_peds("a_m_m_skidrow_01"); });
			sub->AddOption<RegularOption>("South Central Latino Male", nullptr, [] {load_peds("a_m_m_socenlat_01"); });
			sub->AddOption<RegularOption>("South Central Male", nullptr, [] {load_peds("a_m_m_soucent_01"); });
			sub->AddOption<RegularOption>("South Central Male 2", nullptr, [] {load_peds("a_m_m_soucent_02"); });
			sub->AddOption<RegularOption>("South Central Male 3", nullptr, [] {load_peds("a_m_m_soucent_03"); });
			sub->AddOption<RegularOption>("South Central Male 4", nullptr, [] {load_peds("a_m_m_soucent_04"); });
			sub->AddOption<RegularOption>("South Central Old Male", nullptr, [] {load_peds("a_m_o_soucent_01"); });
			sub->AddOption<RegularOption>("South Central Old Male 2", nullptr, [] {load_peds("a_m_o_soucent_02"); });
			sub->AddOption<RegularOption>("South Central Old Male 3", nullptr, [] {load_peds("a_m_o_soucent_03"); });
			sub->AddOption<RegularOption>("South Central Young Male", nullptr, [] {load_peds("a_m_y_soucent_01"); });
			sub->AddOption<RegularOption>("South Central Young Male 2", nullptr, [] {load_peds("a_m_y_soucent_02"); });
			sub->AddOption<RegularOption>("South Central Young Male 3", nullptr, [] {load_peds("a_m_y_soucent_03"); });
			sub->AddOption<RegularOption>("South Central Young Male 4", nullptr, [] {load_peds("a_m_y_soucent_04"); });
			sub->AddOption<RegularOption>("Sunbather Male", nullptr, [] {load_peds("a_m_y_sunbathe_01"); });
			sub->AddOption<RegularOption>("Surfer", nullptr, [] {load_peds("a_m_y_surfer_01"); });
			sub->AddOption<RegularOption>("Tennis Player Male", nullptr, [] {load_peds("a_m_m_tennis_01"); });
			sub->AddOption<RegularOption>("Tourist Male", nullptr, [] {load_peds("a_m_m_tourist_01"); });
			sub->AddOption<RegularOption>("Tramp Male", nullptr, [] {load_peds("a_m_m_tramp_01"); });
			sub->AddOption<RegularOption>("Tramp Old Male", nullptr, [] {load_peds("a_m_o_tramp_01"); });
			sub->AddOption<RegularOption>("Transvestite Male", nullptr, [] {load_peds("a_m_m_tranvest_01"); });
			sub->AddOption<RegularOption>("Transvestite Male 2", nullptr, [] {load_peds("a_m_m_tranvest_02"); });
			sub->AddOption<RegularOption>("Vespucci Beach Male", nullptr, [] {load_peds("a_m_y_beachvesp_01"); });
			sub->AddOption<RegularOption>("Vespucci Beach Male 2", nullptr, [] {load_peds("a_m_y_beachvesp_02"); });
			sub->AddOption<RegularOption>("Vinewood Douche", nullptr, [] {load_peds("a_m_y_vindouche_01"); });
			sub->AddOption<RegularOption>("Vinewood Male", nullptr, [] {load_peds("a_m_y_vinewood_01"); });
			sub->AddOption<RegularOption>("Vinewood Male 2", nullptr, [] {load_peds("a_m_y_vinewood_02"); });
			sub->AddOption<RegularOption>("Vinewood Male 3", nullptr, [] {load_peds("a_m_y_vinewood_03"); });
			sub->AddOption<RegularOption>("Vinewood Male 4", nullptr, [] {load_peds("a_m_y_vinewood_04"); });
			sub->AddOption<RegularOption>("White Street Male", nullptr, [] {load_peds("a_m_y_stwhi_01"); });
			sub->AddOption<RegularOption>("White Street Male 2", nullptr, [] {load_peds("a_m_y_stwhi_02"); });
			sub->AddOption<RegularOption>("Yoga Male", nullptr, [] {load_peds("a_m_y_yoga_01"); });
			sub->AddOption<RegularOption>("Club Customer Male 1", nullptr, [] {load_peds("a_m_y_clubcust_01"); });
			sub->AddOption<RegularOption>("Club Customer Male 2", nullptr, [] {load_peds("a_m_y_clubcust_02"); });
			sub->AddOption<RegularOption>("Club Customer Male 3", nullptr, [] {load_peds("a_m_y_clubcust_03"); });

		});
		g_UiManager->AddSubmenu<RegularSubmenu>("Cutscene", Cutscene, [](RegularSubmenu* sub)
		{

			sub->AddOption<RegularOption>("Abigail Mathers", nullptr, [] {load_peds("csb_abigail"); });
			sub->AddOption<RegularOption>("Agent", nullptr, [] {load_peds("csb_agent"); });
			sub->AddOption<RegularOption>("Agatha Baker", nullptr, [] {load_peds("csb_agatha"); });
			sub->AddOption<RegularOption>("Avery Duggan", nullptr, [] {load_peds("csb_avery"); });
			sub->AddOption<RegularOption>("Agent 14", nullptr, [] {load_peds("csb_mp_agent14"); });
			sub->AddOption<RegularOption>("Amanda De Santa", nullptr, [] {load_peds("cs_amandatownley"); });
			sub->AddOption<RegularOption>("Andreas Sanchez", nullptr, [] {load_peds("cs_andreas"); });
			sub->AddOption<RegularOption>("Anita Mendoza", nullptr, [] {load_peds("csb_anita"); });
			sub->AddOption<RegularOption>("Anton Beaudelaire", nullptr, [] {load_peds("csb_anton"); });
			sub->AddOption<RegularOption>("Ashley Butler", nullptr, [] {load_peds("cs_ashley"); });
			sub->AddOption<RegularOption>("Avon Hertz", nullptr, [] {load_peds("csb_avon"); });
			sub->AddOption<RegularOption>("Ballas OG", nullptr, [] {load_peds("csb_ballasog"); });
			sub->AddOption<RegularOption>("Bank Manager", nullptr, [] {load_peds("cs_bankman"); });
			sub->AddOption<RegularOption>("Barry", nullptr, [] {load_peds("cs_barry"); });
			sub->AddOption<RegularOption>("Beverly Felton", nullptr, [] {load_peds("cs_beverly"); });
			sub->AddOption<RegularOption>("Brucie Kibbutz", nullptr, [] {load_peds("csb_brucie2"); });
			sub->AddOption<RegularOption>("Bigfoot", nullptr, [] {load_peds("cs_orleans"); });
			sub->AddOption<RegularOption>("Bogdan", nullptr, [] {load_peds("csb_bogdan"); });
			sub->AddOption<RegularOption>("Brad", nullptr, [] {load_peds("cs_brad"); });
			sub->AddOption<RegularOption>("Brad's Cadaver", nullptr, [] {load_peds("cs_bradcadaver"); });
			sub->AddOption<RegularOption>("Bride", nullptr, [] {load_peds("csb_bride"); });
			sub->AddOption<RegularOption>("Burger Drug Worker", nullptr, [] {load_peds("csb_burgerdrug"); });
			sub->AddOption<RegularOption>(" 3 Guy 1", nullptr, [] {load_peds("csb_3guy1"); });
			sub->AddOption<RegularOption>(" 3 Guy 2", nullptr, [] {load_peds("csb_3guy2"); });
			sub->AddOption<RegularOption>(" Buyer", nullptr, [] {load_peds("cs_buyer"); });
			sub->AddOption<RegularOption>("Casey", nullptr, [] {load_peds("cs_casey"); });
			sub->AddOption<RegularOption>("Chef", nullptr, [] {load_peds("csb_chef"); });
			sub->AddOption<RegularOption>("Chef", nullptr, [] {load_peds("csb_chef2"); });
			sub->AddOption<RegularOption>("Chinese Goon", nullptr, [] {load_peds("csb_chin_goon"); });
			sub->AddOption<RegularOption>("Clay Simons (The Lost)", nullptr, [] {load_peds("cs_clay"); });
			sub->AddOption<RegularOption>("Cletus", nullptr, [] {load_peds("csb_cletus"); });
			sub->AddOption<RegularOption>("Cop", nullptr, [] {load_peds("csb_cop"); });
			sub->AddOption<RegularOption>("Cris Formage", nullptr, [] {load_peds("cs_chrisformage"); });
			sub->AddOption<RegularOption>("Customer", nullptr, [] {load_peds("csb_customer"); });
			sub->AddOption<RegularOption>("Dale", nullptr, [] {load_peds("cs_dale"); });
			sub->AddOption<RegularOption>("Dave Norton", nullptr, [] {load_peds("cs_davenorton"); });
			sub->AddOption<RegularOption>("Debra", nullptr, [] {load_peds("cs_debra"); });
			sub->AddOption<RegularOption>("Denise", nullptr, [] {load_peds("cs_denise"); });
			sub->AddOption<RegularOption>("Denise's Friend", nullptr, [] {load_peds("csb_denise_friend"); });
			sub->AddOption<RegularOption>("Devin", nullptr, [] {load_peds("cs_devin"); });
			sub->AddOption<RegularOption>("Dima Popov", nullptr, [] {load_peds("csb_popov"); });
			sub->AddOption<RegularOption>("Dom Beasley", nullptr, [] {load_peds("cs_dom"); });
			sub->AddOption<RegularOption>("Dr. Friedlander", nullptr, [] {load_peds("cs_drfriedlander"); });
			sub->AddOption<RegularOption>("Epsilon Tom", nullptr, [] {load_peds("cs_tomepsilon"); });
			sub->AddOption<RegularOption>("Fabien", nullptr, [] {load_peds("cs_fabien"); });
			sub->AddOption<RegularOption>("Families Gang Member?", nullptr, [] {load_peds("csb_ramp_gang"); });
			sub->AddOption<RegularOption>("Ferdinand Kerimov (Mr. K)", nullptr, [] {load_peds("cs_mrk"); });
			sub->AddOption<RegularOption>("FIB Suit", nullptr, [] {load_peds("cs_fbisuit_01"); });
			sub->AddOption<RegularOption>("Floyd Hebert", nullptr, [] {load_peds("cs_floyd"); });
			sub->AddOption<RegularOption>("FOS Rep?", nullptr, [] {load_peds("csb_fos_rep"); });
			sub->AddOption<RegularOption>("Gerald", nullptr, [] {load_peds("csb_g"); });
			sub->AddOption<RegularOption>("Groom", nullptr, [] {load_peds("csb_groom"); });
			sub->AddOption<RegularOption>("Grove Street Dealer", nullptr, [] {load_peds("csb_grove_str_dlr"); });
			sub->AddOption<RegularOption>("Guadalope", nullptr, [] {load_peds("cs_guadalope"); });
			sub->AddOption<RegularOption>("GURK?", nullptr, [] {load_peds("cs_gurk"); });
			sub->AddOption<RegularOption>("Hao", nullptr, [] {load_peds("csb_hao"); });
			sub->AddOption<RegularOption>("Hick", nullptr, [] {load_peds("csb_ramp_hic"); });
			sub->AddOption<RegularOption>("Hipster", nullptr, [] {load_peds("csb_ramp_hipster"); });
			sub->AddOption<RegularOption>("Hugh Welsh", nullptr, [] {load_peds("csb_hugh"); });
			sub->AddOption<RegularOption>("Hunter", nullptr, [] {load_peds("cs_hunter"); });
			sub->AddOption<RegularOption>("Imran Shinowa", nullptr, [] {load_peds("csb_imran"); });
			sub->AddOption<RegularOption>("Jack Howitzer", nullptr, [] {load_peds("csb_jackhowitzer"); });
			sub->AddOption<RegularOption>("Janet", nullptr, [] {load_peds("cs_janet"); });
			sub->AddOption<RegularOption>("Janitor", nullptr, [] {load_peds("csb_janitor"); });
			sub->AddOption<RegularOption>("Jeweller Assistant", nullptr, [] {load_peds("cs_jewelass"); });
			sub->AddOption<RegularOption>("Jimmy Boston", nullptr, [] {load_peds("cs_jimmyboston"); });
			sub->AddOption<RegularOption>("Jimmy De Santa", nullptr, [] {load_peds("cs_jimmydisanto"); });
			sub->AddOption<RegularOption>("Johnny Klebitz", nullptr, [] {load_peds("cs_johnnyklebitz"); });
			sub->AddOption<RegularOption>("Josef", nullptr, [] {load_peds("cs_josef"); });
			sub->AddOption<RegularOption>("Josh", nullptr, [] {load_peds("cs_josh"); });
			sub->AddOption<RegularOption>("Karen Daniels", nullptr, [] {load_peds("cs_karen_daniels"); });
			sub->AddOption<RegularOption>("Lamar Davis", nullptr, [] {load_peds("cs_lamardavis"); });
			sub->AddOption<RegularOption>("Lazlow", nullptr, [] {load_peds("cs_lazlow"); });
			sub->AddOption<RegularOption>("Lester Crest", nullptr, [] {load_peds("cs_lestercrest"); });
			sub->AddOption<RegularOption>("Life Invader", nullptr, [] {load_peds("cs_lifeinvad_01"); });
			sub->AddOption<RegularOption>("Magenta", nullptr, [] {load_peds("cs_magenta"); });
			sub->AddOption<RegularOption>("Manuel", nullptr, [] {load_peds("cs_manuel"); });
			sub->AddOption<RegularOption>("Marine", nullptr, [] {load_peds("csb_ramp_marine"); });
			sub->AddOption<RegularOption>("Marnie Allen", nullptr, [] {load_peds("cs_marnie"); });
			sub->AddOption<RegularOption>("Martin Madrazo", nullptr, [] {load_peds("cs_martinmadrazo"); });
			sub->AddOption<RegularOption>("Mary-Ann Quinn", nullptr, [] {load_peds("cs_maryann"); });
			sub->AddOption<RegularOption>("Maude", nullptr, [] {load_peds("csb_maude"); });
			sub->AddOption<RegularOption>("Maxim Rashkovsky", nullptr, [] {load_peds("csb_rashcosvki"); });
			sub->AddOption<RegularOption>("Merryweather Merc", nullptr, [] {load_peds("csb_mweather"); });
			sub->AddOption<RegularOption>("Mexican", nullptr, [] {load_peds("csb_ramp_mex"); });
			sub->AddOption<RegularOption>("Michelle", nullptr, [] {load_peds("cs_michelle"); });
			sub->AddOption<RegularOption>("Milton McIlroy", nullptr, [] {load_peds("cs_milton"); });
			sub->AddOption<RegularOption>("Minuteman Joe", nullptr, [] {load_peds("cs_joeminuteman"); });
			sub->AddOption<RegularOption>("Molly", nullptr, [] {load_peds("cs_molly"); });
			sub->AddOption<RegularOption>("Money Man", nullptr, [] {load_peds("csb_money"); });
			sub->AddOption<RegularOption>("Movie Premiere Female", nullptr, [] {load_peds("cs_movpremf_01"); });
			sub->AddOption<RegularOption>("Movie Premiere Male", nullptr, [] {load_peds("cs_movpremmale"); });
			sub->AddOption<RegularOption>("Mrs. Phillips", nullptr, [] {load_peds("cs_mrsphillips"); });
			sub->AddOption<RegularOption>("Mrs. Rackman", nullptr, [] {load_peds("csb_mrs_r"); });
			sub->AddOption<RegularOption>("Mrs. Thornhill", nullptr, [] {load_peds("cs_mrs_thornhill"); });
			sub->AddOption<RegularOption>("Natalia", nullptr, [] {load_peds("cs_natalia"); });
			sub->AddOption<RegularOption>("Nervous Ron", nullptr, [] {load_peds("cs_nervousron"); });
			sub->AddOption<RegularOption>("Nigel", nullptr, [] {load_peds("cs_nigel"); });
			sub->AddOption<RegularOption>("Old Man 1", nullptr, [] {load_peds("cs_old_man1a"); });
			sub->AddOption<RegularOption>("Old Man 2", nullptr, [] {load_peds("cs_old_man2"); });
			sub->AddOption<RegularOption>("Omega", nullptr, [] {load_peds("cs_omega"); });
			sub->AddOption<RegularOption>("Ortega", nullptr, [] {load_peds("csb_ortega"); });
			sub->AddOption<RegularOption>("Os", nullptr, [] {load_peds("csb_os"); });
			sub->AddOption<RegularOption>("Paige Harris", nullptr, [] {load_peds("csb_paige"); });
			sub->AddOption<RegularOption>("Patricia", nullptr, [] {load_peds("cs_patricia"); });
			sub->AddOption<RegularOption>("Peter Dreyfuss", nullptr, [] {load_peds("cs_dreyfuss"); });
			sub->AddOption<RegularOption>("Porn Dude", nullptr, [] {load_peds("csb_porndudes"); });
			sub->AddOption<RegularOption>("Priest", nullptr, [] {load_peds("cs_priest"); });
			sub->AddOption<RegularOption>("Prologue Driver", nullptr, [] {load_peds("csb_prologuedriver"); });
			sub->AddOption<RegularOption>("Prologue Security", nullptr, [] {load_peds("csb_prolsec"); });
			sub->AddOption<RegularOption>("Prologue Security 2", nullptr, [] {load_peds("cs_prolsec_02"); });
			sub->AddOption<RegularOption>("Reporter", nullptr, [] {load_peds("csb_reporter"); });
			sub->AddOption<RegularOption>("Rocco Pelosi", nullptr, [] {load_peds("csb_roccopelosi"); });
			sub->AddOption<RegularOption>("Russian Drunk", nullptr, [] {load_peds("cs_russiandrunk"); });
			sub->AddOption<RegularOption>("Screenwriter", nullptr, [] {load_peds("csb_screen_writer"); });
			sub->AddOption<RegularOption>("Simeon Yetarian", nullptr, [] {load_peds("cs_siemonyetarian"); });
			sub->AddOption<RegularOption>("Solomon Richards", nullptr, [] {load_peds("cs_solomon"); });
			sub->AddOption<RegularOption>("Steve Haines", nullptr, [] {load_peds("cs_stevehains"); });
			sub->AddOption<RegularOption>("Stretch", nullptr, [] {load_peds("cs_stretch"); });
			sub->AddOption<RegularOption>("Stripper", nullptr, [] {load_peds("csb_stripper_01"); });
			sub->AddOption<RegularOption>("Stripper 2", nullptr, [] {load_peds("csb_stripper_02"); });
			sub->AddOption<RegularOption>("Tanisha", nullptr, [] {load_peds("cs_tanisha"); });
			sub->AddOption<RegularOption>("Tao Cheng", nullptr, [] {load_peds("cs_taocheng"); });
			sub->AddOption<RegularOption>("Tao Cheng (Casino)", nullptr, [] {load_peds("cs_taocheng2"); });
			sub->AddOption<RegularOption>("Tao's Translator", nullptr, [] {load_peds("cs_taostranslator"); });
			sub->AddOption<RegularOption>("Tao's Translator (Casino)", nullptr, [] {load_peds("cs_taostranslator2"); });
			sub->AddOption<RegularOption>("Tennis Coach", nullptr, [] {load_peds("cs_tenniscoach"); });
			sub->AddOption<RegularOption>("Terry", nullptr, [] {load_peds("cs_terry"); });
			sub->AddOption<RegularOption>("Tom", nullptr, [] {load_peds("cs_tom"); });
			sub->AddOption<RegularOption>("Tom Connors", nullptr, [] {load_peds("csb_tomcasino"); });
			sub->AddOption<RegularOption>("Tonya", nullptr, [] {load_peds("csb_tonya"); });
			sub->AddOption<RegularOption>("Thornton Duggan", nullptr, [] {load_peds("csb_thornton"); });
			sub->AddOption<RegularOption>("Tracey De Santa", nullptr, [] {load_peds("cs_tracydisanto"); });
			sub->AddOption<RegularOption>("Traffic Warden", nullptr, [] {load_peds("csb_trafficwarden"); });
			sub->AddOption<RegularOption>("Undercover Cop", nullptr, [] {load_peds("csb_undercover"); });
			sub->AddOption<RegularOption>("United Paper Man", nullptr, [] {load_peds("cs_paper"); });
			sub->AddOption<RegularOption>("Vagos Speak", nullptr, [] {load_peds("csb_vagspeak"); });
			sub->AddOption<RegularOption>("Vincent (Casino)", nullptr, [] {load_peds("csb_vincent"); });
			sub->AddOption<RegularOption>("Wade", nullptr, [] {load_peds("cs_wade"); });
			sub->AddOption<RegularOption>("Wei Cheng", nullptr, [] {load_peds("cs_chengsr"); });
			sub->AddOption<RegularOption>("Zimbor", nullptr, [] {load_peds("cs_zimbor"); });
			sub->AddOption<RegularOption>("DJ Black Madonna", nullptr, [] {load_peds("csb_djblamadon"); });
			sub->AddOption<RegularOption>("Dixon", nullptr, [] {load_peds("csb_dix"); });
			sub->AddOption<RegularOption>("English Dave", nullptr, [] {load_peds("csb_englishdave"); });
			sub->AddOption<RegularOption>("Lazlow 2", nullptr, [] {load_peds("cs_lazlow_2"); });
			sub->AddOption<RegularOption>("Soloman", nullptr, [] {load_peds("csb_sol"); });
			sub->AddOption<RegularOption>("Tale of Us 1", nullptr, [] {load_peds("csb_talcc"); });
			sub->AddOption<RegularOption>("Tale of Us 2", nullptr, [] {load_peds("csb_talmm"); });
			sub->AddOption<RegularOption>("Tony Prince", nullptr, [] {load_peds("csb_tonyprince"); });
			sub->AddOption<RegularOption>("Alan Jerome", nullptr, [] {load_peds("csb_alan"); });
			sub->AddOption<RegularOption>("Bryony", nullptr, [] {load_peds("csb_bryony"); });
		});
		g_UiManager->AddSubmenu<RegularSubmenu>("GangFemale", GangFemale, [](RegularSubmenu* sub)
		{
			sub->AddOption<RegularOption>("Ballas Female", nullptr, [] {load_peds("g_f_y_ballas_01"); });
			sub->AddOption<RegularOption>("Families Female", nullptr, [] {load_peds("g_f_y_families_01"); });
			sub->AddOption<RegularOption>("Import Export Female", nullptr, [] {load_peds("g_f_importexport_01"); });
			sub->AddOption<RegularOption>("The Lost MC Female", nullptr, [] {load_peds("g_f_y_lost_01"); });
			sub->AddOption<RegularOption>("Vagos Female", nullptr, [] {load_peds("g_f_y_vagos_01"); });
			sub->AddOption<RegularOption>("Gang Female (Import-Export)", nullptr, [] {load_peds("g_f_importexport_01"); });


		});
		g_UiManager->AddSubmenu<RegularSubmenu>("GangMale", GangMale, [](RegularSubmenu* sub)
		{
			sub->AddOption<RegularOption>("Gang Male (Import-Export)", nullptr, [] {load_peds("g_m_importexport_01"); });
			sub->AddOption<RegularOption>("Armenian Boss", nullptr, [] {load_peds("g_m_m_armboss_01"); });
			sub->AddOption<RegularOption>("Armenian Goon", nullptr, [] {load_peds("g_m_m_armgoon_01"); });
			sub->AddOption<RegularOption>("Armenian Goon 2", nullptr, [] {load_peds("g_m_y_armgoon_02"); });
			sub->AddOption<RegularOption>("Armenian Lieutenant", nullptr, [] {load_peds("g_m_m_armlieut_01"); });
			sub->AddOption<RegularOption>("Azteca", nullptr, [] {load_peds("g_m_y_azteca_01"); });
			sub->AddOption<RegularOption>("Ballas East Male", nullptr, [] {load_peds("g_m_y_ballaeast_01"); });
			sub->AddOption<RegularOption>("Ballas Original Male", nullptr, [] {load_peds("g_m_y_ballaorig_01"); });
			sub->AddOption<RegularOption>("Ballas South Male", nullptr, [] {load_peds("g_m_y_ballasout_01"); });
			sub->AddOption<RegularOption>("Casino Guests?", nullptr, [] {load_peds("g_m_m_casrn_01"); });
			sub->AddOption<RegularOption>("Chemical Plant Worker", nullptr, [] {load_peds("g_m_m_chemwork_01"); });
			sub->AddOption<RegularOption>("Chinese Boss", nullptr, [] {load_peds("g_m_m_chiboss_01"); });
			sub->AddOption<RegularOption>("Chinese Goon", nullptr, [] {load_peds("g_m_m_chigoon_01"); });
			sub->AddOption<RegularOption>("Chinese Goon 2", nullptr, [] {load_peds("g_m_m_chigoon_02"); });
			sub->AddOption<RegularOption>("Chinese Goon Older", nullptr, [] {load_peds("g_m_m_chicold_01"); });
			sub->AddOption<RegularOption>("Families CA Male", nullptr, [] {load_peds("g_m_y_famca_01"); });
			sub->AddOption<RegularOption>("Families DNF Male", nullptr, [] {load_peds("g_m_y_famdnf_01"); });
			sub->AddOption<RegularOption>("Families FOR Male", nullptr, [] {load_peds("g_m_y_famfor_01"); });
			sub->AddOption<RegularOption>("Korean Boss", nullptr, [] {load_peds("g_m_m_korboss_01"); });
			sub->AddOption<RegularOption>("Korean Lieutenant", nullptr, [] {load_peds("g_m_y_korlieut_01"); });
			sub->AddOption<RegularOption>("Korean Young Male", nullptr, [] {load_peds("g_m_y_korean_01"); });
			sub->AddOption<RegularOption>("Korean Young Male 2", nullptr, [] {load_peds("g_m_y_korean_02"); });
			sub->AddOption<RegularOption>("Mexican Boss", nullptr, [] {load_peds("g_m_m_mexboss_01"); });
			sub->AddOption<RegularOption>("Mexican Boss 2", nullptr, [] {load_peds("g_m_m_mexboss_02"); });
			sub->AddOption<RegularOption>("Mexican Gang Member", nullptr, [] {load_peds("g_m_y_mexgang_01"); });
			sub->AddOption<RegularOption>("Mexican Goon", nullptr, [] {load_peds("g_m_y_mexgoon_01"); });
			sub->AddOption<RegularOption>("Mexican Goon 2", nullptr, [] {load_peds("g_m_y_mexgoon_02"); });
			sub->AddOption<RegularOption>("Mexican Goon 3", nullptr, [] {load_peds("g_m_y_mexgoon_03"); });
			sub->AddOption<RegularOption>("Polynesian Goon", nullptr, [] {load_peds("g_m_y_pologoon_01"); });
			sub->AddOption<RegularOption>("Polynesian Goon 2", nullptr, [] {load_peds("g_m_y_pologoon_02"); });
			sub->AddOption<RegularOption>("Salvadoran Boss", nullptr, [] {load_peds("g_m_y_salvaboss_01"); });
			sub->AddOption<RegularOption>("Salvadoran Goon", nullptr, [] {load_peds("g_m_y_salvagoon_01"); });
			sub->AddOption<RegularOption>("Salvadoran Goon 2", nullptr, [] {load_peds("g_m_y_salvagoon_02"); });
			sub->AddOption<RegularOption>("Salvadoran Goon 3", nullptr, [] {load_peds("g_m_y_salvagoon_03"); });
			sub->AddOption<RegularOption>("Street Punk", nullptr, [] {load_peds("g_m_y_strpunk_01"); });
			sub->AddOption<RegularOption>("Street Punk 2", nullptr, [] {load_peds("g_m_y_strpunk_02"); });
			sub->AddOption<RegularOption>("The Lost MC Male", nullptr, [] {load_peds("g_m_y_lost_01"); });
			sub->AddOption<RegularOption>("The Lost MC Male 2", nullptr, [] {load_peds("g_m_y_lost_02"); });
			sub->AddOption<RegularOption>("The Lost MC Male 3", nullptr, [] {load_peds("g_m_y_lost_03"); });

		});
		g_UiManager->AddSubmenu<RegularSubmenu>("Story", Story, [](RegularSubmenu* sub)
		{

			sub->AddOption<RegularOption>("Michael", nullptr, [] { load_peds("player_zero"); });
			sub->AddOption<RegularOption>("Franklin", nullptr, [] {load_peds("player_one"); });
			sub->AddOption<RegularOption>("Trevor", nullptr, [] {load_peds("player_two"); });
			sub->AddOption<RegularOption>("Abigail Mathers", nullptr, [] {load_peds("ig_abigail"); });
			sub->AddOption<RegularOption>("Agent", nullptr, [] {load_peds("ig_agent"); });
			sub->AddOption<RegularOption>("Agatha Baker", nullptr, [] {load_peds("ig_agatha"); });
			sub->AddOption<RegularOption>("Avery Duggan", nullptr, [] {load_peds("ig_avery"); });
			sub->AddOption<RegularOption>("Agent 14", nullptr, [] {load_peds("ig_mp_agent14"); });
			sub->AddOption<RegularOption>("Amanda De Santa", nullptr, [] {load_peds("ig_amandatownley"); });
			sub->AddOption<RegularOption>("Andreas Sanchez", nullptr, [] {load_peds("ig_andreas"); });
			sub->AddOption<RegularOption>("Ashley Butler", nullptr, [] {load_peds("ig_ashley"); });
			sub->AddOption<RegularOption>("Avon Hertz", nullptr, [] {load_peds("ig_avon"); });
			sub->AddOption<RegularOption>("Ballas OG", nullptr, [] {load_peds("ig_ballasog"); });
			sub->AddOption<RegularOption>("Benny", nullptr, [] {load_peds("ig_benny"); });
			sub->AddOption<RegularOption>("Bank Manager", nullptr, [] {load_peds("ig_bankman"); });
			sub->AddOption<RegularOption>("Barry", nullptr, [] {load_peds("ig_barry"); });
			sub->AddOption<RegularOption>("Best Man", nullptr, [] {load_peds("ig_bestmen"); });
			sub->AddOption<RegularOption>("Beverly Felton", nullptr, [] {load_peds("ig_beverly"); });
			sub->AddOption<RegularOption>("Brucie Kibbutz", nullptr, [] {load_peds("ig_brucie2"); });
			sub->AddOption<RegularOption>("Bigfoot", nullptr, [] {load_peds("ig_orleans"); });
			sub->AddOption<RegularOption>("Brad", nullptr, [] {load_peds("ig_brad"); });
			sub->AddOption<RegularOption>("Bride", nullptr, [] {load_peds("ig_bride"); });
			sub->AddOption<RegularOption>(" 3 Guy 1", nullptr, [] {load_peds("ig_3guy1"); });
			sub->AddOption<RegularOption>(" 3 Guy 2", nullptr, [] {load_peds("ig_3guy2"); });
			sub->AddOption<RegularOption>("Casey", nullptr, [] {load_peds("ig_casey"); });
			sub->AddOption<RegularOption>("Chef", nullptr, [] {load_peds("ig_chef"); });
			sub->AddOption<RegularOption>("Chef", nullptr, [] {load_peds("ig_chef2"); });
			sub->AddOption<RegularOption>("Clay Jackson (The Pain Giver)", nullptr, [] {load_peds("ig_claypain"); });
			sub->AddOption<RegularOption>("Clay Simons (The Lost)", nullptr, [] {load_peds("ig_clay"); });
			sub->AddOption<RegularOption>("Cletus", nullptr, [] {load_peds("ig_cletus"); });
			sub->AddOption<RegularOption>("Cris Formage", nullptr, [] {load_peds("ig_chrisformage"); });
			sub->AddOption<RegularOption>("Dale", nullptr, [] {load_peds("ig_dale"); });
			sub->AddOption<RegularOption>("Dave Norton", nullptr, [] {load_peds("ig_davenorton"); });
			sub->AddOption<RegularOption>("Denise", nullptr, [] {load_peds("ig_denise"); });
			sub->AddOption<RegularOption>("Devin", nullptr, [] {load_peds("ig_devin"); });
			sub->AddOption<RegularOption>("Dima Popov", nullptr, [] {load_peds("ig_popov"); });
			sub->AddOption<RegularOption>("Dom Beasley", nullptr, [] {load_peds("ig_dom"); });
			sub->AddOption<RegularOption>("Dr. Friedlander", nullptr, [] {load_peds("ig_drfriedlander"); });
			sub->AddOption<RegularOption>("Epsilon Tom", nullptr, [] {load_peds("ig_tomepsilon"); });
			sub->AddOption<RegularOption>("Fabien", nullptr, [] {load_peds("ig_fabien"); });
			sub->AddOption<RegularOption>("Families Gang Member?", nullptr, [] {load_peds("ig_ramp_gang"); });
			sub->AddOption<RegularOption>("Ferdinand Kerimov (Mr. K)", nullptr, [] {load_peds("ig_mrk"); });
			sub->AddOption<RegularOption>("FIB Suit", nullptr, [] {load_peds("ig_fbisuit_01"); });
			sub->AddOption<RegularOption>("Floyd Hebert", nullptr, [] {load_peds("ig_floyd"); });
			sub->AddOption<RegularOption>("Gerald", nullptr, [] {load_peds("ig_g"); });
			sub->AddOption<RegularOption>("Groom", nullptr, [] {load_peds("ig_groom"); });
			sub->AddOption<RegularOption>("Hao", nullptr, [] {load_peds("ig_hao"); });
			sub->AddOption<RegularOption>("Hick", nullptr, [] {load_peds("ig_ramp_hic"); });
			sub->AddOption<RegularOption>("Hipster", nullptr, [] {load_peds("ig_ramp_hipster"); });
			sub->AddOption<RegularOption>("Hunter", nullptr, [] {load_peds("ig_hunter"); });
			sub->AddOption<RegularOption>("Janet", nullptr, [] {load_peds("ig_janet"); });
			sub->AddOption<RegularOption>("Jay Norris", nullptr, [] {load_peds("ig_jay_norris"); });
			sub->AddOption<RegularOption>("Jeweller Assistant", nullptr, [] {load_peds("ig_jewelass"); });
			sub->AddOption<RegularOption>("Jimmy Boston", nullptr, [] {load_peds("ig_jimmyboston"); });
			sub->AddOption<RegularOption>("Jimmy De Santa", nullptr, [] {load_peds("ig_jimmydisanto"); });
			sub->AddOption<RegularOption>("Johnny Klebitz", nullptr, [] {load_peds("ig_johnnyklebitz"); });
			sub->AddOption<RegularOption>("Josef", nullptr, [] {load_peds("ig_josef"); });
			sub->AddOption<RegularOption>("Josh", nullptr, [] {load_peds("ig_josh"); });
			sub->AddOption<RegularOption>("Karen Daniels", nullptr, [] {load_peds("ig_karen_daniels"); });
			sub->AddOption<RegularOption>("Kerry McIntosh", nullptr, [] {load_peds("ig_kerrymcintosh"); });
			sub->AddOption<RegularOption>("Lamar Davis", nullptr, [] {load_peds("ig_lamardavis"); });
			sub->AddOption<RegularOption>("Lazlow", nullptr, [] {load_peds("ig_lazlow"); });
			sub->AddOption<RegularOption>("Lester Crest", nullptr, [] {load_peds("ig_lestercrest"); });
			sub->AddOption<RegularOption>("Lester Crest (Doomsday Heist)", nullptr, [] {load_peds("ig_lestercrest_2"); });
			sub->AddOption<RegularOption>("Life Invader", nullptr, [] {load_peds("ig_lifeinvad_01"); });
			sub->AddOption<RegularOption>("Life Invader 2", nullptr, [] {load_peds("ig_lifeinvad_02"); });
			sub->AddOption<RegularOption>("Magenta", nullptr, [] {load_peds("ig_magenta"); });
			sub->AddOption<RegularOption>("Manuel", nullptr, [] {load_peds("ig_manuel"); });
			sub->AddOption<RegularOption>("Marnie Allen", nullptr, [] {load_peds("ig_marnie"); });
			sub->AddOption<RegularOption>("Mary-Ann Quinn", nullptr, [] {load_peds("ig_maryann"); });
			sub->AddOption<RegularOption>("Maude", nullptr, [] {load_peds("ig_maude"); });
			sub->AddOption<RegularOption>("Maxim Rashkovsky", nullptr, [] {load_peds("ig_rashcosvki"); });
			sub->AddOption<RegularOption>("Mexican", nullptr, [] {load_peds("ig_ramp_mex"); });
			sub->AddOption<RegularOption>("Michelle", nullptr, [] {load_peds("ig_michelle"); });
			sub->AddOption<RegularOption>("Milton McIlroy", nullptr, [] {load_peds("ig_milton"); });
			sub->AddOption<RegularOption>("Minuteman Joe", nullptr, [] {load_peds("ig_joeminuteman"); });
			sub->AddOption<RegularOption>("Malc", nullptr, [] {load_peds("ig_malc"); });
			sub->AddOption<RegularOption>("Molly", nullptr, [] {load_peds("ig_molly"); });
			sub->AddOption<RegularOption>("Money Man", nullptr, [] {load_peds("ig_money"); });
			sub->AddOption<RegularOption>("Mrs. Phillips", nullptr, [] {load_peds("ig_mrsphillips"); });
			sub->AddOption<RegularOption>("Mrs. Thornhill", nullptr, [] {load_peds("ig_mrs_thornhill"); });
			sub->AddOption<RegularOption>("Natalia", nullptr, [] {load_peds("ig_natalia"); });
			sub->AddOption<RegularOption>("Nervous Ron", nullptr, [] {load_peds("ig_nervousron"); });
			sub->AddOption<RegularOption>("Nigel", nullptr, [] {load_peds("ig_nigel"); });
			sub->AddOption<RegularOption>("Old Man 1", nullptr, [] {load_peds("ig_old_man1a"); });
			sub->AddOption<RegularOption>("Old Man 2", nullptr, [] {load_peds("ig_old_man2"); });
			sub->AddOption<RegularOption>("Omega", nullptr, [] {load_peds("ig_omega"); });
			sub->AddOption<RegularOption>("O'Neil Brothers", nullptr, [] {load_peds("ig_oneil"); });
			sub->AddOption<RegularOption>("Ortega", nullptr, [] {load_peds("ig_ortega"); });
			sub->AddOption<RegularOption>("Paige Harris", nullptr, [] {load_peds("ig_paige"); });
			sub->AddOption<RegularOption>("Patricia", nullptr, [] {load_peds("ig_patricia"); });
			sub->AddOption<RegularOption>("Peter Dreyfuss", nullptr, [] {load_peds("ig_dreyfuss"); });
			sub->AddOption<RegularOption>("Priest", nullptr, [] {load_peds("ig_priest"); });
			sub->AddOption<RegularOption>("Prologue Security 2", nullptr, [] {load_peds("ig_prolsec_02"); });
			sub->AddOption<RegularOption>("Rocco Pelosi", nullptr, [] {load_peds("ig_roccopelosi"); });
			sub->AddOption<RegularOption>("Russian Drunk", nullptr, [] {load_peds("ig_russiandrunk"); });
			sub->AddOption<RegularOption>("Screenwriter", nullptr, [] {load_peds("ig_screen_writer"); });
			sub->AddOption<RegularOption>("Simeon Yetarian", nullptr, [] {load_peds("ig_siemonyetarian"); });
			sub->AddOption<RegularOption>("Solomon Richards", nullptr, [] {load_peds("ig_solomon"); });
			sub->AddOption<RegularOption>("Steve Haines", nullptr, [] {load_peds("ig_stevehains"); });
			sub->AddOption<RegularOption>("Stretch", nullptr, [] {load_peds("ig_stretch"); });
			sub->AddOption<RegularOption>("Talina", nullptr, [] {load_peds("ig_talina"); });
			sub->AddOption<RegularOption>("Tanisha", nullptr, [] {load_peds("ig_tanisha"); });
			sub->AddOption<RegularOption>("Tao Cheng", nullptr, [] {load_peds("ig_taocheng"); });
			sub->AddOption<RegularOption>("Tao Cheng (Casino)", nullptr, [] {load_peds("ig_taocheng2"); });
			sub->AddOption<RegularOption>("Tao's Translator", nullptr, [] {load_peds("ig_taostranslator"); });
			sub->AddOption<RegularOption>("Tao's Translator (Casino)", nullptr, [] {load_peds("ig_taostranslator2"); });
			sub->AddOption<RegularOption>("Tennis Coach", nullptr, [] {load_peds("ig_tenniscoach"); });
			sub->AddOption<RegularOption>("Terry", nullptr, [] {load_peds("ig_terry"); });
			sub->AddOption<RegularOption>("Tonya", nullptr, [] {load_peds("ig_tonya"); });
			sub->AddOption<RegularOption>("Tracey De Santa", nullptr, [] {load_peds("ig_tracydisanto"); });
			sub->AddOption<RegularOption>("Traffic Warden", nullptr, [] {load_peds("ig_trafficwarden"); });
			sub->AddOption<RegularOption>("Tyler Dixon", nullptr, [] {load_peds("ig_tylerdix"); });
			sub->AddOption<RegularOption>("United Paper Man", nullptr, [] {load_peds("ig_paper"); });
			sub->AddOption<RegularOption>("Vagos Funeral Speaker", nullptr, [] {load_peds("ig_vagspeak"); });
			sub->AddOption<RegularOption>("Wade", nullptr, [] {load_peds("ig_wade"); });
			sub->AddOption<RegularOption>("Wei Cheng", nullptr, [] {load_peds("ig_chengsr"); });
			sub->AddOption<RegularOption>("Zimbor", nullptr, [] {load_peds("ig_zimbor"); });
			sub->AddOption<RegularOption>("DJ Black Madonna", nullptr, [] {load_peds("ig_djblamadon"); });
			sub->AddOption<RegularOption>("DJ Ryan S", nullptr, [] {load_peds("ig_djblamryans"); });
			sub->AddOption<RegularOption>("DJ Rupert", nullptr, [] {load_peds("ig_djblamrupert"); });
			sub->AddOption<RegularOption>("DJ Dixon Manager", nullptr, [] {load_peds("ig_djdixmanager"); });
			sub->AddOption<RegularOption>("DJ Fotios", nullptr, [] {load_peds("ig_djsolfotios"); });
			sub->AddOption<RegularOption>("DJ Jakob", nullptr, [] {load_peds("ig_djsoljakob"); });
			sub->AddOption<RegularOption>("DJ Mike T", nullptr, [] {load_peds("ig_djsolmike"); });
			sub->AddOption<RegularOption>("DJ Rob T", nullptr, [] {load_peds("ig_djsolrobt"); });
			sub->AddOption<RegularOption>("DJ Aurelia", nullptr, [] {load_peds("ig_djtalaurelia"); });
			sub->AddOption<RegularOption>("DJ Ignazio", nullptr, [] {load_peds("ig_djtalignazio"); });
			sub->AddOption<RegularOption>("Dixon", nullptr, [] {load_peds("ig_dix"); });
			sub->AddOption<RegularOption>("English Dave", nullptr, [] {load_peds("ig_englishdave"); });
			sub->AddOption<RegularOption>("Generic DJ", nullptr, [] {load_peds("ig_djgeneric_01"); });
			sub->AddOption<RegularOption>("Jimmy Boston 2", nullptr, [] {load_peds("ig_jimmyboston_02"); });
			sub->AddOption<RegularOption>("Kerry McIntosh 2", nullptr, [] {load_peds("ig_kerrymcintosh_02"); });
			sub->AddOption<RegularOption>("Lacy Jones 2", nullptr, [] {load_peds("ig_lacey_jones_02"); });
			sub->AddOption<RegularOption>("Lazlow 2", nullptr, [] {load_peds("ig_lazlow_2"); });
			sub->AddOption<RegularOption>("Soloman", nullptr, [] {load_peds("ig_sol"); });
			sub->AddOption<RegularOption>("Soloman Manager", nullptr, [] {load_peds("ig_djsolmanager"); });
			sub->AddOption<RegularOption>("Tale of Us 1", nullptr, [] {load_peds("ig_talcc"); });
			sub->AddOption<RegularOption>("Tale of Us 2", nullptr, [] {load_peds("ig_talmm"); });
			sub->AddOption<RegularOption>("Tyler Dixon 2", nullptr, [] {load_peds("ig_tylerdix_02"); });
			sub->AddOption<RegularOption>("Tony Prince", nullptr, [] {load_peds("ig_tonyprince"); });
			sub->AddOption<RegularOption>("Sacha Yetarian", nullptr, [] {load_peds("ig_sacha"); });
			sub->AddOption<RegularOption>("Thornton Duggan", nullptr, [] {load_peds("ig_thornton"); });
			sub->AddOption<RegularOption>("Tom Connors", nullptr, [] {load_peds("ig_tomcasino"); });
			sub->AddOption<RegularOption>("Vincent (Casino)", nullptr, [] {load_peds("ig_vincent"); });
		});
		g_UiManager->AddSubmenu<RegularSubmenu>("Multiplayer", Multiplayer, [](RegularSubmenu* sub)
		{
			sub->AddOption<RegularOption>("Armoured Van Security Male", nullptr, [] {load_peds("mp_s_m_armoured_01"); });
			sub->AddOption<RegularOption>("Avon Goon", nullptr, [] {load_peds("mp_m_avongoon"); });
			sub->AddOption<RegularOption>("Biker Cocaine Female", nullptr, [] {load_peds("mp_f_cocaine_01"); });
			sub->AddOption<RegularOption>("Biker Cocaine Male", nullptr, [] {load_peds("mp_m_cocaine_01"); });
			sub->AddOption<RegularOption>("Biker Counterfeit Female", nullptr, [] {load_peds("mp_f_counterfeit_01"); });
			sub->AddOption<RegularOption>("Biker Counterfeit Male", nullptr, [] {load_peds("mp_m_counterfeit_01"); });
			sub->AddOption<RegularOption>("Biker Forgery Female", nullptr, [] {load_peds("mp_f_forgery_01"); });
			sub->AddOption<RegularOption>("Biker Forgery Male", nullptr, [] {load_peds("mp_m_forgery_01"); });
			sub->AddOption<RegularOption>("Biker Meth Female", nullptr, [] {load_peds("mp_f_meth_01"); });
			sub->AddOption<RegularOption>("Biker Meth Male", nullptr, [] {load_peds("mp_m_meth_01"); });
			sub->AddOption<RegularOption>("Biker Weed Female", nullptr, [] {load_peds("mp_f_weed_01"); });
			sub->AddOption<RegularOption>("Biker Weed Male", nullptr, [] {load_peds("mp_m_weed_01"); });
			sub->AddOption<RegularOption>("Boat-Staff Female", nullptr, [] {load_peds("mp_f_boatstaff_01"); });
			sub->AddOption<RegularOption>("Boat-Staff Male", nullptr, [] {load_peds("mp_m_boatstaff_01"); });
			sub->AddOption<RegularOption>("Bogdan Goon", nullptr, [] {load_peds("mp_m_bogdangoon"); });
			sub->AddOption<RegularOption>("Clubhouse Bar Female", nullptr, [] {load_peds("mp_f_chbar_01"); });
			sub->AddOption<RegularOption>("Claude Speed", nullptr, [] {load_peds("mp_m_claude_01"); });
			sub->AddOption<RegularOption>("Dead Hooker", nullptr, [] {load_peds("mp_f_deadhooker"); });
			sub->AddOption<RegularOption>("Ex-Army Male", nullptr, [] {load_peds("mp_m_exarmy_01"); });
			sub->AddOption<RegularOption>("Executive PA Female", nullptr, [] {load_peds("mp_f_execpa_01"); });
			sub->AddOption<RegularOption>("Executive PA Female 2", nullptr, [] {load_peds("mp_f_execpa_02"); });
			sub->AddOption<RegularOption>("Executive PA Male", nullptr, [] {load_peds("mp_m_execpa_01"); });
			sub->AddOption<RegularOption>("Families DD Male", nullptr, [] {load_peds("mp_m_famdd_01"); });
			sub->AddOption<RegularOption>("FIB Security", nullptr, [] {load_peds("mp_m_fibsec_01"); });
			sub->AddOption<RegularOption>("Freemode Female", nullptr, [] {load_peds("mp_f_freemode_01"); });
			sub->AddOption<RegularOption>("Freemode Male", nullptr, [] {load_peds("mp_m_freemode_01"); });
			sub->AddOption<RegularOption>("Heli-Staff Female", nullptr, [] {load_peds("mp_f_helistaff_01"); });
			sub->AddOption<RegularOption>("John Marston", nullptr, [] {load_peds("mp_m_marston_01"); });
			sub->AddOption<RegularOption>("Misty", nullptr, [] {load_peds("mp_f_misty_01"); });
			sub->AddOption<RegularOption>("Niko Bellic", nullptr, [] {load_peds("mp_m_niko_01"); });
			sub->AddOption<RegularOption>("Office Garage Mechanic (Female)", nullptr, [] {load_peds("mp_f_design_01"); });
			sub->AddOption<RegularOption>("Pros", nullptr, [] {load_peds("mp_g_m_pros_01"); });
			sub->AddOption<RegularOption>("Securoserve Guard (Male)", nullptr, [] {load_peds("mp_m_securoguard_01"); });
			sub->AddOption<RegularOption>("Shopkeeper (Male)", nullptr, [] {load_peds("mp_m_shopkeep_01"); });
			sub->AddOption<RegularOption>("Stripper Lite (Female)", nullptr, [] {load_peds("mp_f_stripperlite"); });
			sub->AddOption<RegularOption>("Vagos Funeral", nullptr, [] {load_peds("mp_m_g_vagfun_01"); });
			sub->AddOption<RegularOption>("Warehouse Mechanic (Male)", nullptr, [] {load_peds("mp_m_waremech_01"); });
			sub->AddOption<RegularOption>("Weapon Exp (Male)", nullptr, [] {load_peds("mp_m_weapexp_01"); });
			sub->AddOption<RegularOption>("Weapon Work (Male)", nullptr, [] {load_peds("mp_m_weapwork_01"); });
			sub->AddOption<RegularOption>("Benny Mechanic (Female)", nullptr, [] {load_peds("mp_f_bennymech_01"); });

		});
		g_UiManager->AddSubmenu<RegularSubmenu>("ScenarioFemale", ScenarioFemale, [](RegularSubmenu* sub)
		{
			sub->AddOption<RegularOption>("Air Hostess", nullptr, [] {load_peds("s_f_y_airhostess_01"); });
			sub->AddOption<RegularOption>("Barber Female", nullptr, [] {load_peds("s_f_m_fembarber"); });
			sub->AddOption<RegularOption>("Bartender", nullptr, [] {load_peds("s_f_y_bartender_01"); });
			sub->AddOption<RegularOption>("Baywatch Female", nullptr, [] {load_peds("s_f_y_baywatch_01"); });
			sub->AddOption<RegularOption>("Casino Staff", nullptr, [] {load_peds("s_f_y_casino_01"); });
			sub->AddOption<RegularOption>("Cop Female", nullptr, [] {load_peds("s_f_y_cop_01"); });
			sub->AddOption<RegularOption>("Factory Worker Female", nullptr, [] {load_peds("s_f_y_factory_01"); });
			sub->AddOption<RegularOption>("Hooker", nullptr, [] {load_peds("s_f_y_hooker_01"); });
			sub->AddOption<RegularOption>("Hooker 2", nullptr, [] {load_peds("s_f_y_hooker_02"); });
			sub->AddOption<RegularOption>("Hooker 3", nullptr, [] {load_peds("s_f_y_hooker_03"); });
			sub->AddOption<RegularOption>("Hospital Scrubs Female", nullptr, [] {load_peds("s_f_y_scrubs_01"); });
			sub->AddOption<RegularOption>("Maid", nullptr, [] {load_peds("s_f_m_maid_01"); });
			sub->AddOption<RegularOption>("Migrant Female", nullptr, [] {load_peds("s_f_y_migrant_01"); });
			sub->AddOption<RegularOption>("Movie Premiere Female", nullptr, [] {load_peds("s_f_y_movprem_01"); });
			sub->AddOption<RegularOption>("Ranger Female", nullptr, [] {load_peds("s_f_y_ranger_01"); });
			sub->AddOption<RegularOption>("Sales Assistant (High-End)", nullptr, [] {load_peds("s_f_m_shop_high"); });
			sub->AddOption<RegularOption>("Sales Assistant (Low-End)", nullptr, [] {load_peds("s_f_y_shop_low"); });
			sub->AddOption<RegularOption>("Sales Assistant (Mid-Price)", nullptr, [] {load_peds("s_f_y_shop_mid"); });
			sub->AddOption<RegularOption>("Sheriff Female", nullptr, [] {load_peds("s_f_y_sheriff_01"); });
			sub->AddOption<RegularOption>("Stripper", nullptr, [] {load_peds("s_f_y_stripper_01"); });
			sub->AddOption<RegularOption>("Stripper 2", nullptr, [] {load_peds("s_f_y_stripper_02"); });
			sub->AddOption<RegularOption>("Stripper Lite", nullptr, [] {load_peds("s_f_y_stripperlite"); });
			sub->AddOption<RegularOption>("Sweatshop Worker", nullptr, [] {load_peds("s_f_m_sweatshop_01"); });
			sub->AddOption<RegularOption>("Sweatshop Worker Young", nullptr, [] {load_peds("s_f_y_sweatshop_01"); });
			sub->AddOption<RegularOption>("Club Bartender Female", nullptr, [] {load_peds("s_f_y_clubbar_01"); });

		});
		g_UiManager->AddSubmenu<RegularSubmenu>("ScenarioMale", ScenarioMale, [](RegularSubmenu* sub)
		{
			sub->AddOption<RegularOption>("Air Worker Male", nullptr, [] {load_peds("s_m_y_airworker"); });
			sub->AddOption<RegularOption>("Alien", nullptr, [] {load_peds("s_m_m_movalien_01"); });
			sub->AddOption<RegularOption>("Ammu-Nation City Clerk", nullptr, [] {load_peds("s_m_y_ammucity_01"); });
			sub->AddOption<RegularOption>("Ammu-Nation Rural Clerk", nullptr, [] {load_peds("s_m_m_ammucountry"); });
			sub->AddOption<RegularOption>("Armoured Van Security", nullptr, [] {load_peds("s_m_m_armoured_01"); });
			sub->AddOption<RegularOption>("Armoured Van Security 2", nullptr, [] {load_peds("s_m_m_armoured_02"); });
			sub->AddOption<RegularOption>("Army Mechanic", nullptr, [] {load_peds("s_m_y_armymech_01"); });
			sub->AddOption<RegularOption>("Autopsy Tech", nullptr, [] {load_peds("s_m_y_autopsy_01"); });
			sub->AddOption<RegularOption>("Autoshop Worker", nullptr, [] {load_peds("s_m_m_autoshop_01"); });
			sub->AddOption<RegularOption>("Autoshop Worker 2", nullptr, [] {load_peds("s_m_m_autoshop_02"); });
			sub->AddOption<RegularOption>("Barman", nullptr, [] {load_peds("s_m_y_barman_01"); });
			sub->AddOption<RegularOption>("Bartender (Rural)", nullptr, [] {load_peds("s_m_m_cntrybar_01"); });
			sub->AddOption<RegularOption>("Baywatch Male", nullptr, [] {load_peds("s_m_y_baywatch_01"); });
			sub->AddOption<RegularOption>("Black Ops Soldier", nullptr, [] {load_peds("s_m_y_blackops_01"); });
			sub->AddOption<RegularOption>("Black Ops Soldier 2", nullptr, [] {load_peds("s_m_y_blackops_02"); });
			sub->AddOption<RegularOption>("Black Ops Soldier 3", nullptr, [] {load_peds("s_m_y_blackops_03"); });
			sub->AddOption<RegularOption>("Bouncer", nullptr, [] {load_peds("s_m_m_bouncer_01"); });
			sub->AddOption<RegularOption>("Busboy", nullptr, [] {load_peds("s_m_y_busboy_01"); });
			sub->AddOption<RegularOption>("Busker", nullptr, [] {load_peds("s_m_o_busker_01"); });
			sub->AddOption<RegularOption>("Casino Staff", nullptr, [] {load_peds("s_m_y_casino_01"); });
			sub->AddOption<RegularOption>("Chef", nullptr, [] {load_peds("s_m_y_chef_01"); });
			sub->AddOption<RegularOption>("Chemical Plant Security", nullptr, [] {load_peds("s_m_m_chemsec_01"); });
			sub->AddOption<RegularOption>("Clown", nullptr, [] {load_peds("s_m_y_clown_01"); });
			sub->AddOption<RegularOption>("construction Worker", nullptr, [] {load_peds("s_m_y_construct_01"); });
			sub->AddOption<RegularOption>("construction Worker 2", nullptr, [] {load_peds("s_m_y_construct_02"); });
			sub->AddOption<RegularOption>("Cop Male", nullptr, [] {load_peds("s_m_y_cop_01"); });
			sub->AddOption<RegularOption>("Crew Member", nullptr, [] {load_peds("s_m_m_ccrew_01"); });
			sub->AddOption<RegularOption>("Dealer", nullptr, [] {load_peds("s_m_y_dealer_01"); });
			sub->AddOption<RegularOption>("Devin's Security", nullptr, [] {load_peds("s_m_y_devinsec_01"); });
			sub->AddOption<RegularOption>("Dock Worker", nullptr, [] {load_peds("s_m_m_dockwork_01"); });
			sub->AddOption<RegularOption>("Dock Worker", nullptr, [] {load_peds("s_m_y_dockwork_01"); });
			sub->AddOption<RegularOption>("Doctor", nullptr, [] {load_peds("s_m_m_doctor_01"); });
			sub->AddOption<RegularOption>("Doorman", nullptr, [] {load_peds("s_m_y_doorman_01"); });
			sub->AddOption<RegularOption>("DW Airport Worker", nullptr, [] {load_peds("s_m_y_dwservice_01"); });
			sub->AddOption<RegularOption>("DW Airport Worker 2", nullptr, [] {load_peds("s_m_y_dwservice_02"); });
			sub->AddOption<RegularOption>("Factory Worker Male", nullptr, [] {load_peds("s_m_y_factory_01"); });
			sub->AddOption<RegularOption>("FIB Office Worker", nullptr, [] {load_peds("s_m_m_fiboffice_01"); });
			sub->AddOption<RegularOption>("FIB Office Worker 2", nullptr, [] {load_peds("s_m_m_fiboffice_02"); });
			sub->AddOption<RegularOption>("FIB Security", nullptr, [] {load_peds("s_m_m_fibsec_01"); });
			sub->AddOption<RegularOption>("Fireman Male", nullptr, [] {load_peds("s_m_y_fireman_01"); });
			sub->AddOption<RegularOption>("Gaffer", nullptr, [] {load_peds("s_m_m_gaffer_01"); });
			sub->AddOption<RegularOption>("Garbage Worker", nullptr, [] {load_peds("s_m_y_garbage"); });
			sub->AddOption<RegularOption>("Gardener", nullptr, [] {load_peds("s_m_m_gardener_01"); });
			sub->AddOption<RegularOption>("Grip", nullptr, [] {load_peds("s_m_y_grip_01"); });
			sub->AddOption<RegularOption>("Hairdresser Male", nullptr, [] {load_peds("s_m_m_hairdress_01"); });
			sub->AddOption<RegularOption>("High Security", nullptr, [] {load_peds("s_m_m_highsec_01"); });
			sub->AddOption<RegularOption>("High Security 2", nullptr, [] {load_peds("s_m_m_highsec_02"); });
			sub->AddOption<RegularOption>("Highway Cop", nullptr, [] {load_peds("s_m_y_hwaycop_01"); });
			sub->AddOption<RegularOption>("IAA Security", nullptr, [] {load_peds("s_m_m_ciasec_01"); });
			sub->AddOption<RegularOption>("Janitor", nullptr, [] {load_peds("s_m_m_janitor"); });
			sub->AddOption<RegularOption>("Latino Handyman Male", nullptr, [] {load_peds("s_m_m_lathandy_01"); });
			sub->AddOption<RegularOption>("Life Invader Male", nullptr, [] {load_peds("s_m_m_lifeinvad_01"); });
			sub->AddOption<RegularOption>("Line Cook", nullptr, [] {load_peds("s_m_m_linecook"); });
			sub->AddOption<RegularOption>("LS Metro Worker Male", nullptr, [] {load_peds("s_m_m_lsmetro_01"); });
			sub->AddOption<RegularOption>("Mariachi", nullptr, [] {load_peds("s_m_m_mariachi_01"); });
			sub->AddOption<RegularOption>("Marine", nullptr, [] {load_peds("s_m_m_marine_01"); });
			sub->AddOption<RegularOption>("Marine 2", nullptr, [] {load_peds("s_m_m_marine_02"); });
			sub->AddOption<RegularOption>("Marine Young", nullptr, [] {load_peds("s_m_y_marine_01"); });
			sub->AddOption<RegularOption>("Marine Young 2", nullptr, [] {load_peds("s_m_y_marine_02"); });
			sub->AddOption<RegularOption>("Marine Young 3", nullptr, [] {load_peds("s_m_y_marine_03"); });
			sub->AddOption<RegularOption>("Mechanic", nullptr, [] {load_peds("s_m_y_xmech_01"); });
			sub->AddOption<RegularOption>("MC Clubhouse Mechanic", nullptr, [] {load_peds("s_m_y_xmech_02"); });
			sub->AddOption<RegularOption>("Migrant Male", nullptr, [] {load_peds("s_m_m_migrant_01"); });
			sub->AddOption<RegularOption>("Mime Artist", nullptr, [] {load_peds("s_m_y_mime"); });
			sub->AddOption<RegularOption>("Movie Astronaut", nullptr, [] {load_peds("s_m_m_movspace_01"); });
			sub->AddOption<RegularOption>("Movie Premiere Male", nullptr, [] {load_peds("s_m_m_movprem_01"); });
			sub->AddOption<RegularOption>("Paramedic", nullptr, [] {load_peds("s_m_m_paramedic_01"); });
			sub->AddOption<RegularOption>("Pest Control", nullptr, [] {load_peds("s_m_y_pestcont_01"); });
			sub->AddOption<RegularOption>("Pilot", nullptr, [] {load_peds("s_m_m_pilot_01"); });
			sub->AddOption<RegularOption>("Pilot", nullptr, [] {load_peds("s_m_y_pilot_01"); });
			sub->AddOption<RegularOption>("Pilot 2", nullptr, [] {load_peds("s_m_m_pilot_02"); });
			sub->AddOption<RegularOption>("Postal Worker Male", nullptr, [] {load_peds("s_m_m_postal_01"); });
			sub->AddOption<RegularOption>("Postal Worker Male 2", nullptr, [] {load_peds("s_m_m_postal_02"); });
			sub->AddOption<RegularOption>("Prison Guard", nullptr, [] {load_peds("s_m_m_prisguard_01"); });
			sub->AddOption<RegularOption>("Prisoner", nullptr, [] {load_peds("s_m_y_prisoner_01"); });
			sub->AddOption<RegularOption>("Prisoner (Muscular)", nullptr, [] {load_peds("s_m_y_prismuscl_01"); });
			sub->AddOption<RegularOption>("Ranger Male", nullptr, [] {load_peds("s_m_y_ranger_01"); });
			sub->AddOption<RegularOption>("Robber", nullptr, [] {load_peds("s_m_y_robber_01"); });
			sub->AddOption<RegularOption>("Mask Salesman", nullptr, [] {load_peds("s_m_y_shop_mask"); });
			sub->AddOption<RegularOption>("Scientist", nullptr, [] {load_peds("s_m_m_scientist_01"); });
			sub->AddOption<RegularOption>("Security Guard", nullptr, [] {load_peds("s_m_m_security_01"); });
			sub->AddOption<RegularOption>("Sheriff Male", nullptr, [] {load_peds("s_m_y_sheriff_01"); });
			sub->AddOption<RegularOption>("Snow Cop Male", nullptr, [] {load_peds("s_m_m_snowcop_01"); });
			sub->AddOption<RegularOption>("Street Performer", nullptr, [] {load_peds("s_m_m_strperf_01"); });
			sub->AddOption<RegularOption>("Street Preacher", nullptr, [] {load_peds("s_m_m_strpreach_01"); });
			sub->AddOption<RegularOption>("Street Vendor", nullptr, [] {load_peds("s_m_m_strvend_01"); });
			sub->AddOption<RegularOption>("Street Vendor Young", nullptr, [] {load_peds("s_m_y_strvend_01"); });
			sub->AddOption<RegularOption>("SWAT", nullptr, [] {load_peds("s_m_y_swat_01"); });
			sub->AddOption<RegularOption>("Transport Worker Male", nullptr, [] {load_peds("s_m_m_gentransport"); });
			sub->AddOption<RegularOption>("Trucker Male", nullptr, [] {load_peds("s_m_m_trucker_01"); });
			sub->AddOption<RegularOption>("UPS Driver", nullptr, [] {load_peds("s_m_m_ups_01"); });
			sub->AddOption<RegularOption>("UPS Driver 2", nullptr, [] {load_peds("s_m_m_ups_02"); });
			sub->AddOption<RegularOption>("US Coastguard", nullptr, [] {load_peds("s_m_y_uscg_01"); });
			sub->AddOption<RegularOption>("Valet", nullptr, [] {load_peds("s_m_y_valet_01"); });
			sub->AddOption<RegularOption>("Waiter", nullptr, [] {load_peds("s_m_y_waiter_01"); });
			sub->AddOption<RegularOption>("Duggan Secruity", nullptr, [] {load_peds("s_m_y_westsec_01"); });
			sub->AddOption<RegularOption>("Window Cleaner", nullptr, [] {load_peds("s_m_y_winclean_01"); });
			sub->AddOption<RegularOption>("Club Bartender Male", nullptr, [] {load_peds("s_m_y_clubbar_01"); });
			sub->AddOption<RegularOption>("Warehouse Technician", nullptr, [] {load_peds("s_m_y_waretech_01"); });

		});
		g_UiManager->AddSubmenu<RegularSubmenu>("StoryScenarioFemale", StoryScenarioFemale, [](RegularSubmenu* sub)
		{
			sub->AddOption<RegularOption>("Biker Chic Female", nullptr, [] {load_peds("u_f_y_bikerchic"); });
			sub->AddOption<RegularOption>("Corpse Female", nullptr, [] {load_peds("u_f_m_corpse_01"); });
			sub->AddOption<RegularOption>("Casino Cashier", nullptr, [] {load_peds("u_f_m_casinocash_01"); });
			sub->AddOption<RegularOption>("Casino shop owner", nullptr, [] {load_peds("u_f_m_casinoshop_01"); });
			sub->AddOption<RegularOption>("Debbie (Agatha´s Secretary)", nullptr, [] {load_peds("u_f_m_debbie_01"); });
			sub->AddOption<RegularOption>("ol", nullptr, [] {load_peds("u_f_o_ol"); });
			sub->AddOption<RegularOption>("Eileen", nullptr, [] {load_peds("u_f_o_eileen"); });
			sub->AddOption<RegularOption>("Beth", nullptr, [] {load_peds("u_f_y_beth"); });
			sub->AddOption<RegularOption>("Lauren", nullptr, [] {load_peds("u_f_y_lauren"); });
			sub->AddOption<RegularOption>("Taylor", nullptr, [] {load_peds("u_f_y_taylor"); });
			sub->AddOption<RegularOption>("Corpse Young Female", nullptr, [] {load_peds("u_f_y_corpse_01"); });
			sub->AddOption<RegularOption>("Corpse Young Female 2", nullptr, [] {load_peds("u_f_y_corpse_02"); });
			sub->AddOption<RegularOption>("Hot Posh Female", nullptr, [] {load_peds("u_f_y_hotposh_01"); });
			sub->AddOption<RegularOption>("Jane", nullptr, [] {load_peds("u_f_y_comjane"); });
			sub->AddOption<RegularOption>("Jeweller Assistant", nullptr, [] {load_peds("u_f_y_jewelass_01"); });
			sub->AddOption<RegularOption>("Miranda", nullptr, [] {load_peds("u_f_m_miranda"); });
			sub->AddOption<RegularOption>("Mistress", nullptr, [] {load_peds("u_f_y_mistress"); });
			sub->AddOption<RegularOption>("Movie Star Female", nullptr, [] {load_peds("u_f_o_moviestar"); });
			sub->AddOption<RegularOption>("Poppy Mitchell", nullptr, [] {load_peds("u_f_y_poppymich"); });
			sub->AddOption<RegularOption>("Princess", nullptr, [] {load_peds("u_f_y_princess"); });
			sub->AddOption<RegularOption>("Prologue Host Old Female", nullptr, [] {load_peds("u_f_o_prolhost_01"); });
			sub->AddOption<RegularOption>("Prologue Mourner Female", nullptr, [] {load_peds("u_f_m_promourn_01"); });
			sub->AddOption<RegularOption>("Spy Actress", nullptr, [] {load_peds("u_f_y_spyactress"); });
			sub->AddOption<RegularOption>("Miranda 2", nullptr, [] {load_peds("u_f_m_miranda_02"); });
			sub->AddOption<RegularOption>("Poppy Mitchell 2", nullptr, [] {load_peds("u_f_y_poppymich_02"); });
			sub->AddOption<RegularOption>("Female Club Dancer (Burlesque)", nullptr, [] {load_peds("u_f_y_danceburl_01"); });
			sub->AddOption<RegularOption>("Female Club Dancer (Leather)", nullptr, [] {load_peds("u_f_y_dancelthr_01"); });
			sub->AddOption<RegularOption>("Female Club Dancer (Rave)", nullptr, [] {load_peds("u_f_y_dancerave_01"); });

		});
		g_UiManager->AddSubmenu<RegularSubmenu>("StoryScenarioMale", StoryScenarioMale_, [](RegularSubmenu* sub)
		{
			sub->AddOption<RegularOption>("Abner", nullptr, [] {load_peds("u_m_y_abner"); });
			sub->AddOption<RegularOption>("Al Di Napoli Male", nullptr, [] {load_peds("u_m_m_aldinapoli"); });
			sub->AddOption<RegularOption>("Anton Beaudelaire", nullptr, [] {load_peds("u_m_y_antonb"); });
			sub->AddOption<RegularOption>("Avon Juggernaut", nullptr, [] {load_peds("u_m_y_juggernaut_01"); });
			sub->AddOption<RegularOption>("Baby D", nullptr, [] {load_peds("u_m_y_babyd"); });
			sub->AddOption<RegularOption>("Bank Manager Male", nullptr, [] {load_peds("u_m_m_bankman"); });
			sub->AddOption<RegularOption>("Bike Hire Guy", nullptr, [] {load_peds("u_m_m_bikehire_01"); });
			sub->AddOption<RegularOption>("Blane", nullptr, [] {load_peds("u_m_m_blane"); });
			sub->AddOption<RegularOption>("Curtis", nullptr, [] {load_peds("u_m_m_curtis"); });
			sub->AddOption<RegularOption>("Vince", nullptr, [] {load_peds("u_m_m_vince"); });
			sub->AddOption<RegularOption>("Dean", nullptr, [] {load_peds("u_m_o_dean"); });
			sub->AddOption<RegularOption>("Caleb", nullptr, [] {load_peds("u_m_y_caleb"); });
			sub->AddOption<RegularOption>("Casino Thief", nullptr, [] {load_peds("u_m_y_croupthief_01"); });
			sub->AddOption<RegularOption>("Gabriel", nullptr, [] {load_peds("u_m_y_gabriel"); });
			sub->AddOption<RegularOption>("Ushi", nullptr, [] {load_peds("u_m_y_ushi"); });
			sub->AddOption<RegularOption>("Burger Drug Worker", nullptr, [] {load_peds("u_m_y_burgerdrug_01"); });
			sub->AddOption<RegularOption>("Chip", nullptr, [] {load_peds("u_m_y_chip"); });
			sub->AddOption<RegularOption>("Cyclist Male", nullptr, [] {load_peds("u_m_y_cyclist_01"); });
			sub->AddOption<RegularOption>("Dead Courier", nullptr, [] {load_peds("u_m_y_corpse_01"); });
			sub->AddOption<RegularOption>("DOA Man", nullptr, [] {load_peds("u_m_m_doa_01"); });
			sub->AddOption<RegularOption>("Ed Toh", nullptr, [] {load_peds("u_m_m_edtoh"); });
			sub->AddOption<RegularOption>("Ex-Mil Bum", nullptr, [] {load_peds("u_m_y_militarybum"); });
			sub->AddOption<RegularOption>("FIB Architect", nullptr, [] {load_peds("u_m_m_fibarchitect"); });
			sub->AddOption<RegularOption>("FIB Mugger", nullptr, [] {load_peds("u_m_y_fibmugger_01"); });
			sub->AddOption<RegularOption>("Financial Guru", nullptr, [] {load_peds("u_m_o_finguru_01"); });
			sub->AddOption<RegularOption>("Glen-Stank Male", nullptr, [] {load_peds("u_m_m_glenstank_01"); });
			sub->AddOption<RegularOption>("Griff", nullptr, [] {load_peds("u_m_m_griff_01"); });
			sub->AddOption<RegularOption>("Guido", nullptr, [] {load_peds("u_m_y_guido_01"); });
			sub->AddOption<RegularOption>("Gun Vendor", nullptr, [] {load_peds("u_m_y_gunvend_01"); });
			sub->AddOption<RegularOption>("Hangar Mechanic", nullptr, [] {load_peds("u_m_y_smugmech_01"); });
			sub->AddOption<RegularOption>("Hippie Male", nullptr, [] {load_peds("u_m_y_hippie_01"); });
			sub->AddOption<RegularOption>("Street Art Male", nullptr, [] {load_peds("u_m_m_streetart_01"); });
			sub->AddOption<RegularOption>("Impotent Rage", nullptr, [] {load_peds("u_m_y_imporage"); });
			sub->AddOption<RegularOption>("Jesco White (Tapdancing Hillbilly)", nullptr, [] {load_peds("u_m_o_taphillbilly"); });
			sub->AddOption<RegularOption>("Jesus", nullptr, [] {load_peds("u_m_m_jesus_01"); });
			sub->AddOption<RegularOption>("Jewel Thief", nullptr, [] {load_peds("u_m_m_jewelthief"); });
			sub->AddOption<RegularOption>("Jeweller Security", nullptr, [] {load_peds("u_m_m_jewelsec_01"); });
			sub->AddOption<RegularOption>("Justin", nullptr, [] {load_peds("u_m_y_justin"); });
			sub->AddOption<RegularOption>("Kifflom Guy", nullptr, [] {load_peds("u_m_y_baygor"); });
			sub->AddOption<RegularOption>("Love Fist Willy", nullptr, [] {load_peds("u_m_m_willyfist"); });
			sub->AddOption<RegularOption>("Mani", nullptr, [] {load_peds("u_m_y_mani"); });
			sub->AddOption<RegularOption>("Mark Fostenburg", nullptr, [] {load_peds("u_m_m_markfost"); });
			sub->AddOption<RegularOption>("Movie Director", nullptr, [] {load_peds("u_m_m_filmdirector"); });
			sub->AddOption<RegularOption>("Movie Corpse (Suited)", nullptr, [] {load_peds("u_m_o_filmnoir"); });
			sub->AddOption<RegularOption>("Paparazzi Young Male", nullptr, [] {load_peds("u_m_y_paparazzi"); });
			sub->AddOption<RegularOption>("Party Target", nullptr, [] {load_peds("u_m_m_partytarget"); });
			sub->AddOption<RegularOption>("Partygoer", nullptr, [] {load_peds("u_m_y_party_01"); });
			sub->AddOption<RegularOption>("Pogo the Monkey", nullptr, [] {load_peds("u_m_y_pogo_01"); });
			sub->AddOption<RegularOption>("Prisoner", nullptr, [] {load_peds("u_m_y_prisoner_01"); });
			sub->AddOption<RegularOption>("Prologue Driver", nullptr, [] {load_peds("u_m_y_proldriver_01"); });
			sub->AddOption<RegularOption>("Prologue Mourner Male", nullptr, [] {load_peds("u_m_m_promourn_01"); });
			sub->AddOption<RegularOption>("Prologue Security", nullptr, [] {load_peds("u_m_m_prolsec_01"); });
			sub->AddOption<RegularOption>("Republican Space Ranger", nullptr, [] {load_peds("u_m_y_rsranger_01"); });
			sub->AddOption<RegularOption>("Rival Paparazzo", nullptr, [] {load_peds("u_m_m_rivalpap"); });
			sub->AddOption<RegularOption>("Sports Biker", nullptr, [] {load_peds("u_m_y_sbike"); });
			sub->AddOption<RegularOption>("Spy Actor", nullptr, [] {load_peds("u_m_m_spyactor"); });
			sub->AddOption<RegularOption>("Stag Party Groom", nullptr, [] {load_peds("u_m_y_staggrm_01"); });
			sub->AddOption<RegularOption>("Tattoo Artist", nullptr, [] {load_peds("u_m_y_tattoo_01"); });
			sub->AddOption<RegularOption>("Tramp Old Male", nullptr, [] {load_peds("u_m_o_tramp_01"); });
			sub->AddOption<RegularOption>("Zombie", nullptr, [] {load_peds("u_m_y_zombie_01"); });
			sub->AddOption<RegularOption>("Male Club Dancer (Burlesque)", nullptr, [] {load_peds("u_m_y_danceburl_01"); });
			sub->AddOption<RegularOption>("Male Club Dancer (Leather)", nullptr, [] {load_peds("u_m_y_dancelthr_01"); });
			sub->AddOption<RegularOption>("Male Club Dancer (Rave)", nullptr, [] {load_peds("u_m_y_dancerave_01"); });

		});
	}

	void MainScript::Destroy()
	{
		g_UiManager.reset();
	}


	NativeVector3 get_blip_markerrr()
	{
		static NativeVector3 zero;
		NativeVector3 coords;

		bool blipFound = false;
		// search for marker blip
		int blipIterator = HUD::_GET_BLIP_INFO_ID_ITERATOR();
		for (Blip i = HUD::GET_FIRST_BLIP_INFO_ID(blipIterator); HUD::DOES_BLIP_EXIST(i) != 0; i = HUD::GET_NEXT_BLIP_INFO_ID(blipIterator))
		{
			if (HUD::GET_BLIP_INFO_ID_TYPE(i) == 4)
			{
				coords = HUD::GET_BLIP_INFO_ID_COORD(i);
				blipFound = true;
				break;
			}
		}
		if (blipFound)
		{
			return coords;
		}

		return zero;
	}
	
	float scaleX = 50, scaleY = 50, scaleZ = 999999999;// Z 999999999 just to be safe!!!
	int rw = 255, gw = 0, bw = 0;

	void MainScript::Tick()
	{
		g_UiManager->OnTick();
		moneyDrop(dEnable, dAmount, money_drop_pos, dDelay, dx, dy, dz, dHeight, Types[5]);
		StatLoop();
		PlayerLoop();
		Self_Local_Loop();
		VehicleUpdateLoop();
		netwUpdateLoop();
		WeaponLoop();
		RGBFade();
		Player playerPed = PLAYER::PLAYER_PED_ID();
		NativeVector3 pos = get_blip_markerrr();
		GRAPHICS::DRAW_MARKER(1, pos.x, pos.y,
			pos.z - 1, 0, 0, 0, 0, 0, 0, scaleX, scaleY, scaleZ, rw, gw, bw, 255, 0, 0, 2, 0, 0, 0, 0);
		
		if (bUnkerMoney)
		{
			globalHandle(262145).At(21045).As<float>() = 322;
		}

	}
}
