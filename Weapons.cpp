#include "Common.hpp"



namespace Big
{

	bool Infinite;
	bool Explosive;
	bool Rapid;
	bool Onehit;
	bool laser;
	bool NoRecoil;
	bool gravityGun;
	bool pedAimbot;

    Nano::n_Vector3 multiplyVectorr(Nano::n_Vector3 vector, float inc)
    {
        vector.x *= inc;
        vector.y *= inc;
        vector.z *= inc;
        vector._paddingx *= inc;
        vector._paddingy *= inc;
        vector._paddingz *= inc;
        return vector;
    }

    Nano::n_Vector3 addVectorr(Nano::n_Vector3 vector, Nano::n_Vector3 vector2)
    {
        return { vector.x += vector2.x, vector._paddingx += vector2._paddingx, vector.y += vector2.y, vector._paddingy += vector2._paddingy, vector.z += vector2.z, vector._paddingz += vector2._paddingz };
    }

	bool InfiniteAmmo, AirstrikeGun, Oneshot, ROPEGUN, fireworkgun, forcegun, tpgun = false;
	bool attached_first;
	Entity rope_ent0;

	int lol[5];

	void WeaponLoop()
	{
		if (gravityGun)
		{
			static Entity currEnt{lol[0]};
            static Entity lastEnt{lol[0, 1, 2, 3, 4, 5]};
            static int zoom = 10;



            if (GetAsyncKeyState(VK_RBUTTON) || PAD::IS_CONTROL_PRESSED(2, ControlAim))
            {
				if ((currEnt == lol[0, 5]) || (lastEnt == currEnt))
                    PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &currEnt);
                else
                {
                    Nano::n_Vector3 rot = REEEEEEEEE::GET_GAMEPLAY_CAM_ROT(0);
                    Nano::n_Vector3 dir = Nano::rot_to_directionnnn(&rot);
                    Nano::n_Vector3 spawnPosition = addVectorr(REEEEEEEEE::GET_GAMEPLAY_CAM_COORD(), multiplyVectorr(dir, zoom));
                    
                    if (ENTITY::IS_ENTITY_A_PED(currEnt) && PED::IS_PED_IN_ANY_VEHICLE(currEnt, 0))
                    {
                        currEnt = PED::GET_VEHICLE_PED_IS_IN(currEnt, 0);
                    }

                    g_CallbackScript->AddCallback<NetworkControlCallback>((currEnt), [=] { RequestControlOfEnt(currEnt); });

                    Nano::n_Vector3 getcoors = REEEEEEEEE::GET_ENTITY_COORDS(currEnt, 0);
                    float getaimcoorsX = GravityGunGoto(spawnPosition.x, getcoors.x);
                    float getaimcoorsY = GravityGunGoto(spawnPosition.y, getcoors.y);
                    float getaimcoorsZ = GravityGunGoto(spawnPosition.z, getcoors.z);
                    ENTITY::SET_ENTITY_VELOCITY(currEnt, getaimcoorsX * 2.0, getaimcoorsY * 2.0, getaimcoorsZ * 2.0);

                    if (GetAsyncKeyState(VK_LBUTTON) || PAD::IS_CONTROL_PRESSED(2, INPUT_ATTACK))
                    {
                        ENTITY::APPLY_FORCE_TO_ENTITY(currEnt, 1, dir.x * 10000.0f, dir.y * 10000.0f, dir.z * 10000.0f, 0.0f, 0.0f, 0.0f, 0, 0, 1, 1, 0, 1);
                        PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_ID(), false);
                        lastEnt = currEnt;
                    }
                    if (GetAsyncKeyState(0x45) || PAD::IS_CONTROL_PRESSED(2, INPUT_DUCK))
                    {
                        ENTITY::SET_ENTITY_HEADING(currEnt, ENTITY::GET_ENTITY_HEADING(currEnt) - 5);
                    }
                    if (GetAsyncKeyState(0x51) || PAD::IS_CONTROL_PRESSED(2, INPUT_VEH_HORN))
                    {
                        ENTITY::SET_ENTITY_HEADING(currEnt, ENTITY::GET_ENTITY_HEADING(currEnt) + 5);
                    }
                    if (PAD::IS_DISABLED_CONTROL_PRESSED(2, INPUT_PREV_WEAPON))
                    {
                        zoom += 1;
                    }
                    if (PAD::IS_DISABLED_CONTROL_PRESSED(2, INPUT_NEXT_WEAPON))
                    {
                        zoom -= 1;
                    }
                }
            }
		}

		if (pedAimbot)
		{
			if (IsKeyPressed(VK_RBUTTON))
			{
				PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_ID(), FALSE);

				//BRAIN::TASK_AIM_GUN_AT_COORD(PLAYER::PLAYER_PED_ID(), 0, 0, 0, 1, 0, 0);
				const int numElements = 10;
				const int arrSize = numElements * 2 + 2;
				int veh[arrSize];	//0 index is the size of the array	
				veh[0] = numElements;
				int count = PED::GET_PED_NEARBY_PEDS(PLAYER::PLAYER_PED_ID(), veh, -1);
				Ped closest = 0;
				if (veh != NULL) {		//Simple loop to go through results		
					for (int i = 0; i < count; i++)
					{
						int offsettedID = i * 2 + 2;			//Make sure it exists			
						if (veh[offsettedID] != NULL && ENTITY::DOES_ENTITY_EXIST(veh[offsettedID]))
						{				//Get all the peds in the vehicle				
							for (int j = -1; j <= 2; ++j)
							{

								Any ped = veh[offsettedID];
								NativeVector3 ped_coords = ENTITY::GET_ENTITY_COORDS(ped, TRUE);
								NativeVector3 self_coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), TRUE);
								if (closest == 0) closest = ped;
								else if (MISC::GET_DISTANCE_BETWEEN_COORDS(self_coords.x, self_coords.y, self_coords.z, ped_coords.x, ped_coords.y, ped_coords.z, TRUE) < MISC::GET_DISTANCE_BETWEEN_COORDS(self_coords.x, self_coords.y, self_coords.z, ENTITY::GET_ENTITY_COORDS(closest, TRUE).x, ENTITY::GET_ENTITY_COORDS(closest, TRUE).y, ENTITY::GET_ENTITY_COORDS(closest, TRUE).z, TRUE)) closest = ped;//                                                                                                                            
								Hash weaponhash;
								WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &weaponhash, 1);
								float screenX, screenY;
								BOOL onScreen = GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(ENTITY::GET_ENTITY_COORDS(closest, true).x, ENTITY::GET_ENTITY_COORDS(closest, true).y, ENTITY::GET_ENTITY_COORDS(closest, true).z, &screenX, &screenY);
								if (closest != NULL && !ENTITY::IS_ENTITY_DEAD(closest, 0) && onScreen)
								{

									NativeVector3 target_coords = PED::GET_PED_BONE_COORDS(closest, 0x796e, 0, 0, 0);

									if (IsKeyPressed(VK_LBUTTON) && GetTickCount() % 20 == 0)
									{
										MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(self_coords.x, self_coords.y, self_coords.z, target_coords.x, target_coords.y, target_coords.z, 50, 1, weaponhash, PLAYER::PLAYER_PED_ID(), 1, 1, 0xbf800000);
									}
									GRAPHICS::DRAW_MARKER(2, target_coords.x, target_coords.y, target_coords.z + 2, 0, 0, 0, 0, 180, 0, 1, 1, 1, 255, 128, 0, 50, 0, 1, 1, 0, 0, 0, 0);

								}
							}
						}
					}


				}
			}
		}

		if (InfiniteAmmo)
		{
			Hash cur;
			if (WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &cur, 1))
			{
				if (WEAPON::IS_WEAPON_VALID(cur))
				{
					int maxAmmo;
					if (WEAPON::GET_MAX_AMMO(PLAYER::PLAYER_PED_ID(), cur, &maxAmmo))
					{
						WEAPON::SET_PED_AMMO(PLAYER::PLAYER_PED_ID(), cur, maxAmmo, NULL);

						maxAmmo = WEAPON::GET_MAX_AMMO_IN_CLIP(PLAYER::PLAYER_PED_ID(), cur, 1);
						if (maxAmmo > 0)
							WEAPON::SET_AMMO_IN_CLIP(PLAYER::PLAYER_PED_ID(), cur, maxAmmo);
					}
				}
			}
		}
		if (tpgun)
		{
			if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
			{
				NativeVector3 coords;
				if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &coords))
				{
					ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), coords.x, coords.y, coords.z, 0, 0, 0, 1);
				}
			}
		}

		if (AirstrikeGun)
		{
			Ped playerPed = PLAYER::PLAYER_PED_ID();
			if (PED::IS_PED_SHOOTING(playerPed))
			{
				NativeVector3 coords;
				if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(playerPed, &coords))
				{
					Hash airStrike = MISC::GET_HASH_KEY("WEAPON_AIRSTRIKE_ROCKET");
					WEAPON::REQUEST_WEAPON_ASSET(airStrike, 31, false);
					while (!WEAPON::HAS_WEAPON_ASSET_LOADED(airStrike))
						WAIT(0);
					MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords.x, coords.y, coords.z + 50.f, coords.x, coords.y, coords.z, 250, 1, airStrike, playerPed, 1, 0, -1.0);
				}
			}
		}
		if (Oneshot)
		{
			Entity EntityTarget;
			if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &EntityTarget))
			{
				if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
				{

					if (ENTITY::IS_ENTITY_A_PED(EntityTarget)
						&& PED::IS_PED_IN_ANY_VEHICLE(EntityTarget, 1)) {
						EntityTarget = PED::GET_VEHICLE_PED_IS_IN(EntityTarget, 0);
					}
					VEHICLE::EXPLODE_VEHICLE(EntityTarget, true, false);
					VEHICLE::SET_VEHICLE_OUT_OF_CONTROL(EntityTarget, true, true);//idk
				}
			}
			PLAYER::SET_PLAYER_WEAPON_DAMAGE_MODIFIER(PLAYER::PLAYER_ID(), 9999999.9999f);
			PLAYER::SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER(PLAYER::PLAYER_ID(), 9999999.9999f, NULL);
			PLAYER::SET_PLAYER_WEAPON_DEFENSE_MODIFIER(PLAYER::PLAYER_ID(), 9999999.9999f);
			PLAYER::SET_PLAYER_MELEE_WEAPON_DEFENSE_MODIFIER(PLAYER::PLAYER_ID(), 9999999.9999f);
		}
		
		

		if (ROPEGUN)
		{
			Object first_rope;
			auto camCoords = CAM::GET_GAMEPLAY_CAM_COORD();
			auto farCoords = Nano::add(&CAM::GET_GAMEPLAY_CAM_COORD(), &Nano::multiply(&Nano::rot_to_direction(&CAM::GET_GAMEPLAY_CAM_ROT(0)), 100.f));
			auto ray = SHAPETEST::_START_SHAPE_TEST_RAY(camCoords.x, camCoords.y, camCoords.z, farCoords.x, farCoords.y, farCoords.z, -1, PLAYER::PLAYER_PED_ID(), 7);
			bool hit; NativeVector3 endCoords; NativeVector3 surfaceNormal; Entity ent = 0;
			SHAPETEST::GET_SHAPE_TEST_RESULT(ray, &hit, &endCoords, &surfaceNormal, &ent);

			if (PAD::IS_CONTROL_PRESSED(2, INPUT_AIM) || IsKeyPressed(VK_RBUTTON))
			{
				if (ENTITY::DOES_ENTITY_EXIST(ent) && (ENTITY::IS_ENTITY_A_PED(ent) || ENTITY::IS_ENTITY_A_VEHICLE(ent) || ENTITY::IS_ENTITY_AN_OBJECT(ent)))
				{
					if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
					{
						PHYSICS::ROPE_LOAD_TEXTURES();
						auto pweapon = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(PLAYER::PLAYER_PED_ID());
						auto pwep_coord = ENTITY::GET_ENTITY_COORDS(pweapon, 1);
						if (!attached_first)
						{
							first_rope = PHYSICS::ADD_ROPE(pwep_coord.x, pwep_coord.y, pwep_coord.z, 0, 0, 0, Nano::distanceBetween(ENTITY::GET_ENTITY_COORDS(ent, 1), pwep_coord), 1, 300, 0.5f, 0.5f, false, true, true, 1.0f, false, 0);
							NativeVector3 c0 = pwep_coord;
							NativeVector3 c1 = ENTITY::GET_ENTITY_COORDS(ent, 1);

							PHYSICS::ATTACH_ENTITIES_TO_ROPE(first_rope, pweapon, ent, c0.x, c0.y, c0.z, c1.x, c1.y, c1.z, Nano::distanceBetween(ENTITY::GET_ENTITY_COORDS(ent, 1), pwep_coord) + 40.f, 0, 0, NULL, NULL);
							PHYSICS::ACTIVATE_PHYSICS(first_rope);

							rope_ent0 = ent;
							attached_first = true;
						}
						else
						{
							PHYSICS::DELETE_ROPE(&first_rope);
							NativeVector3 c0 = ENTITY::GET_ENTITY_COORDS(rope_ent0, 1);
							NativeVector3 c1 = ENTITY::GET_ENTITY_COORDS(ent, 1);

							first_rope = PHYSICS::ADD_ROPE(pwep_coord.x, pwep_coord.y, pwep_coord.z, 0, 0, 0, Nano::distanceBetween(ENTITY::GET_ENTITY_COORDS(rope_ent0, 1), ENTITY::GET_ENTITY_COORDS(ent, 1)), 1, 300, 0.5f, 0.5f, false, true, true, 1.0f, false, 0);
							PHYSICS::ACTIVATE_PHYSICS(first_rope);
							PHYSICS::ATTACH_ENTITIES_TO_ROPE(first_rope, rope_ent0, ent, c0.x, c0.y, c0.z, c1.x, c1.y, c1.z, Nano::distanceBetween(ENTITY::GET_ENTITY_COORDS(rope_ent0, 1), ENTITY::GET_ENTITY_COORDS(ent, 1)), 0, 0, NULL, NULL);

							first_rope = NULL;
							attached_first = false;
						}
					}
				}
			}
			else
			{
				PHYSICS::DELETE_ROPE(&first_rope); attached_first = false;
			}

		}
		if (fireworkgun)
		{
			float startDistance = Nano::distanceBetween(CAM::GET_GAMEPLAY_CAM_COORD(), ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true));
			float endDistance = Nano::distanceBetween(CAM::GET_GAMEPLAY_CAM_COORD(), ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true));
			startDistance += 0.25;
			endDistance += 1000.0;
			if (PED::IS_PED_ON_FOOT(PLAYER::PLAYER_PED_ID()) && PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
			{
				Hash weaponAssetRocket = MISC::GET_HASH_KEY("WEAPON_FIREWORK"); //WEAPON_FIREWORK
				if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
				{
					WEAPON::REQUEST_WEAPON_ASSET(weaponAssetRocket, 31, false);
				}
				MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Nano::add(&CAM::GET_GAMEPLAY_CAM_COORD(), &Nano::multiply(&Nano::rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).x, Nano::add(&CAM::GET_GAMEPLAY_CAM_COORD(), &Nano::multiply(&Nano::rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).y, Nano::add(&CAM::GET_GAMEPLAY_CAM_COORD(), &Nano::multiply(&Nano::rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).z, Nano::add(&CAM::GET_GAMEPLAY_CAM_COORD(), &Nano::multiply(&Nano::rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).x, Nano::add(&CAM::GET_GAMEPLAY_CAM_COORD(), &Nano::multiply(&Nano::rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).y, Nano::add(&CAM::GET_GAMEPLAY_CAM_COORD(), &Nano::multiply(&Nano::rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).z, 250, 1, weaponAssetRocket, PLAYER::PLAYER_PED_ID(), 1, 0, -1.0);
			}
		}
		if (forcegun)
		{
			Entity EntityTarget;
			NativeVector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
			NativeVector3 dir = Nano::rotDirection(&rot);
			if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &EntityTarget))
			{
				if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
				{
					if (ENTITY::IS_ENTITY_A_PED(EntityTarget)
						&& PED::IS_PED_IN_ANY_VEHICLE(EntityTarget, 1)) {
						EntityTarget = PED::GET_VEHICLE_PED_IS_IN(EntityTarget, 0);
					}
					ENTITY::APPLY_FORCE_TO_ENTITY(EntityTarget, 1, dir.x * 100000.0f, dir.y * 100000.0f, dir.z * 100000.0f, 0.0f, 0.0f, 0.0f, 0, 0, 1, 1, 0, 1);
				}
			}
		}
		
	}


}