#include "Common.hpp"
#include "Basic.h"


namespace Big
{
	bool mobile_radio = false;

	void World_Clear()
	{
		NativeVector3 Pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
		MISC::CLEAR_AREA(Pos.x, Pos.y, Pos.z, 250, true, true, true, true);
		MISC::CLEAR_AREA_OF_COPS(Pos.x, Pos.y, Pos.z, 250, 0);
		MISC::CLEAR_AREA_OF_OBJECTS(Pos.x, Pos.y, Pos.z, 250, 0);
		MISC::CLEAR_AREA_OF_VEHICLES(Pos.x, Pos.y, Pos.z, 250, 1, 1, 0, 0, 1, 0);
		MISC::CLEAR_AREA_OF_PEDS(Pos.x, Pos.y, Pos.z, 250, 0);
		MISC::CLEAR_AREA_OF_PROJECTILES(Pos.x, Pos.y, Pos.z, 250, 0);
	}

	void WorldSpeed(float speed)
	{
		MISC::SET_TIME_SCALE(speed);
	}
	void WorldWeather(char* HASH)
	{
		MISC::SET_WEATHER_TYPE_NOW_PERSIST(HASH);
	}

	void WorldFunctions()
	{

		if (mobile_radio)
		{
			Player playerPed = PLAYER::PLAYER_PED_ID();
			AUDIO::SET_FRONTEND_RADIO_ACTIVE(true);
			AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(true);
			AUDIO::SET_MOBILE_PHONE_RADIO_STATE(1);
			//AUDIO::PLAY_SOUND_FROM_ENTITY(-1, "Radio_On", playerPed, "TAXI_SOUNDS", 0, 0);

		}
		else
		{
			Player playerPed = PLAYER::PLAYER_PED_ID();
			AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(false);
			AUDIO::SET_MOBILE_PHONE_RADIO_STATE(0);
			//AUDIO::PLAY_SOUND_FROM_ENTITY(-1, "Radio_Off", playerPed, "TAXI_SOUNDS", 0, 0);
		}
	}

}