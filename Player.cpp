#include "Common.hpp"
#include "fmt/core.h"
#include "fmt/format.h"
#include "fmt/format-inl.h"
namespace Big
{
	using namespace Nano;

	bool _Spectate;
	bool God = false;
	bool Invisible;
	bool Invisiblee = true;
	bool NoRagdoll;
	bool NoClip;
	bool NeverWanted;
	bool Fly;
	bool Freecam;
	bool superRun;
	bool SuperJump;
	bool ForceField;
	bool util;

	float fastboi = 1.f;
	float fastboi2 = 1.f;

	bool f7;
	bool f5;
	bool f4;

	bool otr;

	int wantedlevel;

	bool ToggledOn = false;

	bool walkingnoclip;
	float walkingnoclipspeed = 1.0f;

	NativeVector3 get_blip_marker()
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

	void tpToDestination(Entity e, NativeVector3 coords)
	{
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, coords.x, coords.y, coords.z, 0, 0, 1);
		SYSTEM::WAIT(0);
	}


	void tpToMarker()
	{
		NativeVector3 coords = get_blip_marker();

		if (coords.x == 0 && coords.y == 0)
		{
			return;
		}

		// get entity to teleport
		Entity entity = PLAYER::PLAYER_PED_ID();
		if (PED::IS_PED_IN_ANY_VEHICLE(entity, 0))
		{
			entity = PED::GET_VEHICLE_PED_IS_USING(entity);
		}
		bool worldLevel = false;
		static float groundCheckHeight[] =
		{ 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 300.0, 350.0, 400.0, 450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0 };
		for (int i = 0; i < 800 / sizeof(float); i++)
		{
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(entity, coords.x, coords.y, groundCheckHeight[i], 0, 0, 1);
			SYSTEM::WAIT(0);
			if (MISC::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, groundCheckHeight[i], &coords.z, 0))
			{
				worldLevel = true;
				coords.z += 3.0;
				break;
			}
		}
		if (!worldLevel)
		{
			coords.z = 100.0f;
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFBAB5776, 1, 0);
		}
		tpToDestination(entity, coords);
	}

	


	void LoadPlayerInfo(int player) {
		Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);

		if (!ENTITY::DOES_ENTITY_EXIST(ped)) return;

		g_UiManager->DrawInfoTitle(PLAYER::GET_PLAYER_NAME(player));

		Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, false);

		NativeVector3 coords = ENTITY::GET_ENTITY_COORDS(ped, false);

		bool isConnected = NETWORK::NETWORK_IS_SESSION_ACTIVE();

		bool isInAnyVehicle = PED::IS_PED_IN_ANY_VEHICLE(ped, true);

		// Draw Player Marker
		if (ped != PLAYER::PLAYER_PED_ID()) {
			GRAPHICS::DRAW_MARKER(2, coords.x, coords.y, coords.z + 1.3f, 0.0f, 0.0f, 0.0f, 0.0f, 180.0f, 0.0f, 0.3f, 0.3f, 0.3f, 169, 169, 169, 220, 1, 1, 1, 0, 0, 0, 0);
		}

		Hash street[2]{};
		PATHFIND::GET_STREET_NAME_AT_COORD(coords.x, coords.y, coords.z, &street[0], &street[1]);


		NativeVector3 selfCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);

		float distance = get_distance(&selfCoords, &coords);

		float newDistance{};

		distance > 1000 ? newDistance = round((distance / 1000) * 100) / 100 : newDistance = round(distance * 1000) / 100;

		const char* headShot = "CHAR_MULTIPLAYER";

		int headshotIndex = 1383710;

		for (int x = 0; x <= 150; x += 5) {
			int playerId = globalHandle(headshotIndex).At(x).As<int>();

			if (playerId == player)
			{
				int logo = globalHandle(headshotIndex).At(x).At(1).As<int>();
				headShot = PED::GET_PEDHEADSHOT_TXD_STRING(logo);
			}
		}

		float health = (float)ENTITY::GET_ENTITY_HEALTH(ped);
		float maxHealth = (float)ENTITY::GET_ENTITY_MAX_HEALTH(ped);
		float healthPercent = health * 100 / maxHealth;

		float armor = (float)PED::GET_PED_ARMOUR(ped);
		float maxArmor = (float)PLAYER::GET_PLAYER_MAX_ARMOUR(player);
		float armorPercent = armor * 100 / maxArmor;

		int money = globalHandle(1590535).At(player, 876).At(211).At(3).As<int>();
		int rp = globalHandle(1590535).At(player, 876).At(211).At(5).As<int>();
		int rank = globalHandle(1590535).At(player, 876).At(211).At(6).As<int>();
		int kills = globalHandle(1590535).At(player, 876).At(211).At(28).As<int>();
		int deaths = globalHandle(1590535).At(player, 876).At(211).At(29).As<int>();
		float kd = globalHandle(1590535).At(player, 876).At(211).At(26).As<float>();
		int earnings = globalHandle(1590535).At(player, 876).At(211).At(56).As<int>();
		int bank = earnings - money;

		Hash vehHash = ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_IN(ped, 0));


		//RID
		int netHandle[13];
		NETWORK::NETWORK_HANDLE_FROM_PLAYER(player, netHandle, 13);
		const char* UserID = NETWORK::NETWORK_MEMBER_ID_FROM_GAMER_HANDLE(&netHandle[0]);
		
		
			/*char ipBuf[32] = {};// ip
			static auto ipkee = (std::uintptr_t(*)(int))(Memory::pattern("40 53 48 83 EC 20 33 DB 38 1D ? ? ? ? 74 1C").count(1).get(0).get<void>(0));
			auto PLAYERIP = ipkee(g_SelectedPlayer);
			if (!NETWORK::NETWORK_IS_PLAYER_CONNECTED(g_SelectedPlayer)) {
				for (int i = 0; i < 3; i++)
				{
					if (PLAYER::PLAYER_PED_ID())
					{
						if (PLAYERIP)
						{
							auto ip__ = *(uintptr_t*)(PLAYERIP + 0x10b8);
							if (ip__)
							{
								auto ip = (BYTE*)(ip__ + 0x44);
								std::snprintf(ipBuf, sizeof(ipBuf) - 1, "~g~Hidden", i);
							}
						}
					}
					else
					{
						if (PLAYERIP)
						{
							auto ip__ = *(uintptr_t*)(PLAYERIP + 0x10b8);
							if (ip__)
							{
								auto ip = (BYTE*)(ip__ + 0x44);
								std::snprintf(ipBuf, sizeof(ipBuf) - 1, "~g~Hidden", i);
							}
						}
					}
				}
			}
			else {
				if (PLAYERIP)
				{
					auto ip__ = *(uintptr_t*)(PLAYERIP + 0x10b8);
					if (ip__)
					{
						auto ip = (BYTE*)(ip__ + 0x44);
						std::snprintf(ipBuf, sizeof(ipBuf) - 1, "%u.%u.%u.%u", ip[3], ip[2], ip[1], *ip);
					}
				}
			}
			/*	if (Option("GEO"))
				GRABDONNY = true;
			if (GRABDONNY)
			{
				CC = GEOCountry(ipBuf);
				RR = GEORegion(ipBuf);
				CY_ = GEOCity(ipBuf);
				notifyMap(CC);
				notifyMap(RR);
				notifyMap(CY_);
				GRABDONNY = false;
			}*/

	

	/*	g_UiManager->AddInfo("Speed", fmt::format("{0} m/s", (round(isInAnyVehicle ? (ENTITY::GET_ENTITY_SPEED(vehicle) * 100) : (ENTITY::GET_ENTITY_SPEED(ped) * 100)) / 100)));
		g_UiManager->AddInfo("Vehicle", isInAnyVehicle ? HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(vehHash)) : "~r~Not In A Vehicle");
		g_UiManager->AddInfo("Wanted Level", fmt::format("{0}", PLAYER::GET_PLAYER_WANTED_LEVEL(player)));
		g_UiManager->AddInfo("Distance", fmt::format("{0} {1}", newDistance, distance > 1000 ? "Kilometers" : "Meters"));
		g_UiManager->AddInfo("Zone", HUD::_GET_LABEL_TEXT(ZONE::GET_NAME_OF_ZONE(coords.x, coords.y, coords.z)));
		g_UiManager->AddInfo("Street", HUD::GET_STREET_NAME_FROM_HASH_KEY(street[0]));*/

		
	}

	std::string PlayerName(int Player) {
		int money = globalHandle(1590535).At(Player, 876).At(211).At(3).As<int>();
		NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(Player);
		if (IsPlayerFriend(Player)) {
		/*	if (Modders[Player])
			{
				return PLAYER::GET_PLAYER_NAME(Player) + (std::string)" ~g~[FRIEND] ~r~[Modder]";
			}
			return PLAYER::GET_PLAYER_NAME(Player) + (std::string)" ~g~[FRIEND]";*/
		}
		else if (NETWORK::IS_PLAYER_IN_CUTSCENE(Player))
		{
			return PLAYER::GET_PLAYER_NAME(Player) + (std::string)" ~y~[Cutscene]";
		}
		else if (Player == PLAYER::PLAYER_ID())
		{
			return PLAYER::GET_PLAYER_NAME(Player) + (std::string)" ~g~[Self]";
		}
		else if (PLAYER::GET_PLAYER_INVINCIBLE(Player))
		{
			if (Player != PLAYER::PLAYER_ID())
				return PLAYER::GET_PLAYER_NAME(Player) + (std::string)" ~r~[Modder]";
		}
		else if (money >= 15000000)
		{
			if (Player != PLAYER::PLAYER_ID())
				return PLAYER::GET_PLAYER_NAME(Player) + (std::string)" ~r~[Modded]";
		}
	/*	else if (Modders[Player]) //so make a log of modders doing a harmful script to you, and add to list
		{
			return PLAYER::GET_PLAYER_NAME(Player) + (std::string)" ~r~[Modder]";		
		}*/
		else
		{
			return PLAYER::GET_PLAYER_NAME(Player);
		}
	}

	void PlayerLoop()
	{

		ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), !Invisible, 0);

		

		if (NoRagdoll)
		{
			PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(PLAYER::PLAYER_PED_ID(), !NoRagdoll);
			PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), !NoRagdoll);
		}

		if (_Spectate)
		{
				Ped SelectedCoords = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
				NativeVector3 SelectCoords = ENTITY::GET_ENTITY_COORDS(SelectedCoords, true);
				GRAPHICS::DRAW_MARKER(2, SelectCoords.x, SelectCoords.y, SelectCoords.z + 1.25, 0, 0, 0, 0, 180, 0, 0.25, 0.25, 0.25, 200, 94, 100, 255, 1, 1, 1, 0, 0, 0, 0);
				NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(1, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer));
		}
		else 
		{
			NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(true, PLAYER::PLAYER_PED_ID());
		}


		if (NeverWanted)
		{
			PLAYER::SET_MAX_WANTED_LEVEL(6);
			PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), 0, 0);
			PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), 0);
			wantedlevel = 0;
		}
		else
		{

		}

		if (Fly)
		{
			Hash hash = MISC::GET_HASH_KEY("GADGET_PARACHUTE");

			PLAYER::SET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID(), true);
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), hash, 1, 1);
			PED::SET_PED_TO_RAGDOLL_WITH_FALL(PLAYER::PLAYER_PED_ID(), 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0);

			if (ENTITY::IS_ENTITY_IN_AIR(PLAYER::PLAYER_PED_ID()) && !PED::IS_PED_RAGDOLL(PLAYER::PLAYER_PED_ID()))
			{
				if (GetAsyncKeyState(VK_SHIFT))
				{
					ApplyForceToEntity(PLAYER::PLAYER_PED_ID(), 0, 6, 0);
				}
				if (GetAsyncKeyState(0x53))
				{
					ApplyForceToEntity(PLAYER::PLAYER_PED_ID(), 0, -6, 0);
				}
				if (GetAsyncKeyState(VK_SPACE))
				{
					ApplyForceToEntity(PLAYER::PLAYER_PED_ID(), 0, 0, 6);
				}
			}
		}
		else
		{

		}



		if (util)
		{
			Vehicle Veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()));
			int Handle = PLAYER::PLAYER_PED_ID();
			int Handle2 = PED::GET_VEHICLE_PED_IS_IN(Handle, 0);

			ENTITY::SET_ENTITY_COLLISION(Handle, false, false);
			ENTITY::SET_ENTITY_COLLISION(Handle2, false, false);
			playerinv = true;
			ENTITY::SET_ENTITY_VISIBLE(Veh, !util, 0);
		}
		else
		{
			Vehicle Veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()));
			int Handle = PLAYER::PLAYER_PED_ID();
			int Handle2 = PED::GET_VEHICLE_PED_IS_IN(Handle, 0);

			ENTITY::SET_ENTITY_COLLISION(Handle, true, true);
			ENTITY::SET_ENTITY_COLLISION(Handle2, true, true);
			ENTITY::SET_ENTITY_VISIBLE(Veh, !util, 0);
			playerinv = false;
		}

		if (Freecam)
		{
			static bool lock;
			static std::int32_t cam;
			static float dist;

			auto rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
			auto coord = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);

			NativeVector3 p_coord = { 0,0,0 };

			int Handle = PLAYER::PLAYER_PED_ID();
			int Handle2 = PED::GET_VEHICLE_PED_IS_IN(Handle, 0);

			ENTITY::SET_ENTITY_VISIBLE(Handle, false, 0);


			util = true;
			if (!CAM::DOES_CAM_EXIST(cam)) {
				cam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
				CAM::SET_CAM_ROT(cam, rot.x, rot.y, rot.z, 0);
				CAM::SET_CAM_COORD(cam, coord.x, coord.y, coord.z);
			}
			if (!Freecam)
			{
				NativeVector3 BenAndJerrys = CAM::GET_CAM_COORD(cam);
				ENTITY::SET_ENTITY_COORDS(Handle, BenAndJerrys.x, BenAndJerrys.y, BenAndJerrys.z, 0, 0, 0, 1);
				CAM::RENDER_SCRIPT_CAMS(false, true, 700, 1, 1, 1);
				CAM::SET_CAM_ACTIVE(cam, 0);
				CAM::DESTROY_CAM(cam, true);
				PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_PED_ID(), 0);

			}
			else if (!Freecam == false)
			{
				ENTITY::SET_ENTITY_COLLISION(Handle, true, true);
				ENTITY::SET_ENTITY_COLLISION(Handle2, true, true);

				NativeVector3 BenAndJerrys = CAM::GET_CAM_COORD(cam);
				if (PED::IS_PED_IN_ANY_VEHICLE(Handle, 0))
				{
					ENTITY::SET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_IN(Handle, false), BenAndJerrys.x, BenAndJerrys.y, BenAndJerrys.z, 0, 0, 0, 1);
				}
				else
				{
					ENTITY::SET_ENTITY_COORDS(Handle, BenAndJerrys.x, BenAndJerrys.y, BenAndJerrys.z, 0, 0, 0, 1);
				}

			}

			CAM::RENDER_SCRIPT_CAMS(true, true, 700, 1, 1, 1);
			CAM::SET_CAM_ACTIVE(cam, 1);
			CAM::SET_CAM_ROT(cam, rot.x, rot.y, rot.z, 0);

			p_coord = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);

			//ENTITY::SET_ENTITY_COORDS_NO_OFFSET(PLAYER::PLAYER_PED_ID(), p_coord.x, p_coord.y, p_coord.z, 0, 0, 0);
			//PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_PED_ID(), 1);
			HUD::HIDE_HUD_AND_RADAR_THIS_FRAME();

			auto speed = .5f;
			if (IsKeyPressed(VK_LSHIFT))
			{
				speed += .3f;
			}

			if (IsKeyPressed(VK_KEY_S))
			{
				speed /= -1;
				auto c = add(&CAM::GET_CAM_COORD(cam), &multiply(&rot_to_direction(&rot), speed));
				CAM::SET_CAM_COORD(cam, c.x, c.y, c.z);
			}

			if (IsKeyPressed(VK_KEY_W))
			{
				auto c = add(&CAM::GET_CAM_COORD(cam), &multiply(&rot_to_direction(&rot), speed));
				CAM::SET_CAM_COORD(cam, c.x, c.y, c.z);
			}

		}
		else
		{

			static bool lock;
			static std::int32_t cam;
			static float dist;
			auto rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
			auto coord = CAM::GET_GAMEPLAY_CAM_COORD();
			Vector3 p_coord = { 0,0,0 };

			int Handle = PLAYER::PLAYER_PED_ID();
			int Handle2 = PED::GET_VEHICLE_PED_IS_IN(Handle, 0);

			CAM::SET_CAM_ACTIVE(cam, false);
			CAM::DESTROY_ALL_CAMS(cam);
			PLAYER::SET_PLAYER_CONTROL(Handle, true, 0);
			CAM::RENDER_SCRIPT_CAMS(false, false, 3000, 1, 0, 1);

			util = false;

		}



		if (superRun)
		{

			if (BRAIN::IS_PED_RUNNING(PLAYER::PLAYER_PED_ID()) || BRAIN::IS_PED_SPRINTING(PLAYER::PLAYER_PED_ID()))
			{
				ENTITY::APPLY_FORCE_TO_ENTITY(PLAYER::PLAYER_PED_ID(), 1, 0.f, 1.5f, 0.f, 0.f, 0.f, 0.f, 1, true, true, true, false, true);
			}


		}

#define playerPed PLAYER::PLAYER_PED_ID()
		if (walkingnoclip)
		{
			auto ped = PLAYER::PLAYER_PED_ID();
			auto pos = ENTITY::GET_ENTITY_COORDS(ped, false);
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ped, pos.x, pos.y, pos.z, true, true, true);

			if (GetAsyncKeyState(0x57) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 269))
			{
				NativeVector3 pos = add(&ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false), &multiply(&rot_to_direction(&CAM::GET_GAMEPLAY_CAM_ROT(0)), walkingnoclipspeed));
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, true, true, true);
			}
		}

		if (SuperJump)
		{
			MISC::SET_SUPER_JUMP_THIS_FRAME(PLAYER::PLAYER_ID());
		}

		if (ForceField)
		{
			NativeVector3 pCoords = ENTITY::GET_ENTITY_COORDS(playerPed, 0);
			TEST::ADD_EXPLOSION(pCoords.x + 2, pCoords.y + 2, pCoords.z, 7, 9.0f, false, true, 0.0f);
			TEST::ADD_EXPLOSION(pCoords.x + 3, pCoords.y + 3, pCoords.z, 7, 9.0f, false, true, 0.0f);
			TEST::ADD_EXPLOSION(pCoords.x + 4, pCoords.y + 4, pCoords.z, 7, 9.0f, false, true, 0.0f);
			TEST::ADD_EXPLOSION(pCoords.x + 5, pCoords.y + 5, pCoords.z, 7, 9.0f, false, true, 0.0f);
			TEST::ADD_EXPLOSION(pCoords.x + 6, pCoords.y + 6, pCoords.z, 7, 9.0f, false, true, 0.0f);
			TEST::ADD_EXPLOSION(pCoords.x + 7, pCoords.y + 7, pCoords.z, 7, 9.0f, false, true, 0.0f);
		}

		if (f5)
		{
			if (GetAsyncKeyState(VK_F5) & 1)
			{
				if (Freecam == true)
				{
					Freecam = false;
				}
				else
				{
					Freecam = true;
				}
			}
		}

		if (f7)
		{
			if (GetAsyncKeyState(VK_F7) & 1)
			{
				tpToMarker();
			}
		}

		if (f4)
		{
			if (GetAsyncKeyState(VK_F4) & 1)
			{
				if (VehFly == true)
				{
					VehFly = false;
				}
				else
				{
					VehFly = true;
				}
			}
		}


	}





}