#include "Common.hpp"




namespace Big
{
    bool SpawnInVeh = false;
    bool DeleteVeh = false;
    bool MaxVeh = false;
	bool VehFly;
    bool flyCollision_veh = true;
    bool vehicleInvincible;
    bool autoFlip;
    bool autoFix;
    bool Hornboost;
    bool Seatbelt;
    bool vehInvisible = true;
    bool Rainbow;
    bool reducegrip;
    bool nolimit;
    bool ib;
    int speed;

    int r = 255, g = 0, bb = 0;
    void RGBFade()
    {
        if (r > 0 && bb == 0) {
            r--;
            g++;
        }
        if (g > 0 && r == 0) {
            g--;
            bb++;
        }
        if (bb > 0 && g == 0) {
            r++;
            bb--;
        }
    }

    std::vector<std::string> fVehicleList()
    {
        std::string folderpath = "C:\\Viper\\Favorite Vehicles\\";
        if (!fs::exists(folderpath.c_str()))
        {
            fs::create_directory(folderpath.c_str());
        }
        std::vector<std::string> tempVector;
        int fileCount = 0;
        std::stringstream tempStringStream;
        for (auto& collectedFiles : std::experimental::filesystem::v1::directory_iterator("C:\\Viper\\Favorite Vehicles\\"))
        {
            tempStringStream << collectedFiles;
            std::string oing = tempStringStream.str();
            if (oing.substr(oing.find_last_of(".") + 1) == "ini")
            {
                unsigned foundAmount = oing.find_last_of("/\\");
                std::string TempHolder = oing.substr(0, foundAmount);
                std::string TempHolder2 = oing.substr(foundAmount + 1);
                tempVector.push_back(TempHolder2.substr(0, TempHolder2.find(".", 0)));
                outfitNames = tempVector;
            }
        }
        return tempVector;
    }

	void VehicleUpdateLoop()
	{
		if (VehFly)
		{
            auto selectedSpeedd = 100.0f;
            auto veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);

            if (PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()) != NULL)
            {
                VEHICLE::SET_VEHICLE_GRAVITY(veh, false);
                ENTITY::SET_ENTITY_MAX_SPEED(veh, 10000000.f);

                NativeVector3 yy = CAM::GET_GAMEPLAY_CAM_ROT(2);
                ENTITY::SET_ENTITY_ROTATION(veh, yy.x, yy.y, yy.z, 2, 1);

                if (PAD::IS_DISABLED_CONTROL_PRESSED(2, INPUT_VEH_FLY_THROTTLE_UP))
                {
                    VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, selectedSpeedd);
                }
                else
                {
                    VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 0.0f);
                }
            }
        }
        else
        {
            VEHICLE::SET_VEHICLE_GRAVITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), true);
        }

		
        if (flyCollision_veh)
        {
            auto veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
            ENTITY::SET_ENTITY_COLLISION(veh, true, true);
        }
        else
        {
            auto veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
            ENTITY::SET_ENTITY_COLLISION(veh, false, false);
        }

        if (vehicleInvincible)
        {
            auto veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
            ENTITY::SET_ENTITY_INVINCIBLE(veh, true);
        }

        if (autoFlip)
        {
            auto veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
            float roll = ENTITY::GET_ENTITY_ROLL(veh);
            if (ENTITY::IS_ENTITY_UPSIDEDOWN(veh) && (roll > 160 || roll < -160))
            {   
                Hash model = ENTITY::GET_ENTITY_MODEL(veh);
                if (!ENTITY::IS_ENTITY_IN_AIR(veh) && !ENTITY::IS_ENTITY_IN_WATER(veh) && !VEHICLE::IS_THIS_MODEL_A_PLANE(veh) && !VEHICLE::IS_THIS_MODEL_A_HELI(veh))
                {
                    RequestControlOfEnt(veh);
                    ENTITY::SET_ENTITY_ROTATION(veh, 0, 0, ENTITY::GET_ENTITY_ROTATION(veh, 2).z, 2, 1);

                }
            }
        }

        if (autoFix)
        {
            VEHICLE::SET_VEHICLE_FIXED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false));
            VEHICLE::SET_VEHICLE_DIRT_LEVEL(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 0.0f);
            VEHICLE::SET_VEHICLE_ENGINE_HEALTH(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 2000.0f);
            VEHICLE::SET_VEHICLE_BODY_HEALTH(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 2000.0f);
        }

        if (Hornboost && PAD::IS_CONTROL_PRESSED(2, INPUT_VEH_HORN))
        {
            Vehicle plvh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);

            if (!ENTITY::DOES_ENTITY_EXIST(plvh))
                return;

            if (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(plvh) != 0)
            {
                NETWORK::SET_NETWORK_ID_CAN_MIGRATE(plvh, true);
                NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(plvh);
            }


            AUDIO::SET_VEHICLE_BOOST_ACTIVE(plvh, true);
            ENTITY::APPLY_FORCE_TO_ENTITY(plvh, speed, 0.0f, 1.7f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 1, 1, 1, 0, 1);
            AUDIO::SET_VEHICLE_BOOST_ACTIVE(plvh, false);
        }

        if (Seatbelt)
        {
            PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(), 1);
            PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 32, false);
        }
        else
        {
            PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(), 0);
            PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 32, true);
        }

        if (nolimit)
        {
            Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
            ENTITY::SET_ENTITY_MAX_SPEED(veh, 99999999999);
        }

        if (Rainbow)
        {
            RGBFade();
            Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());

            DWORD model = ENTITY::GET_ENTITY_MODEL(veh);

            if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
            {
                VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, r, g, bb);
                VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, r, g, bb);



                if (VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(veh, 0) && VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(veh, 1) && VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(veh, 2) && VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(veh, 3))
                {
                    VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, r, g, bb);
                }
                else
                {
                    VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
                    VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
                    VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
                    VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
                    VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, r, g, bb);
                }


                VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, r, g, bb);
            }
        }
        Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
        VEHICLE::SET_VEHICLE_REDUCE_GRIP(veh, reducegrip);


        if (vehInvisible)
        {
            ENTITY::SET_ENTITY_VISIBLE(veh, true, 0);
        }
        else
        {
            ENTITY::SET_ENTITY_VISIBLE(veh, false, 0);
        }

        if (ib)
        {
            if (GetAsyncKeyState(VK_KEY_R) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 268)) {

                Vehicle Veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()), false);
                NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Veh);
                if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(Veh))
                {
                    VEHICLE::SET_VEHICLE_FORWARD_SPEED(Veh, 0);
                }
                else
                {

                }
            }
            else
            {

            }
        }
        

	}

    
    
    
   


}