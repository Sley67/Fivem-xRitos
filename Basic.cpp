#include "Common.hpp"
#include "Fibers.hpp"

namespace Big
{

#define playerPedId	PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID())

	NativeVector3 WC::SetPos(Entity e) { ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(e, 0.0, 0.0, 0.0); }
	NativeVector3 WC::GetPos(Entity e) { ENTITY::GET_ENTITY_COORDS(e, false); return ENTITY::GET_ENTITY_COORDS(e, false); }

	bool MessageBox_(char* BIGTEXT, char* SMALLTEXT)
	{
		int scaleform = GRAPHICS::REQUEST_SCALEFORM_MOVIE("mp_big_message_freemode");
		while (!GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED)
		{
			SYSTEM::WAIT(0);
		}
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(scaleform, "SHOW_SHARD_WASTED_MP_MESSAGE");
		GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_STRING(BIGTEXT);
		GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_STRING(SMALLTEXT);
		GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_INT(5);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
		GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(scaleform, 255, 255, 255, 255, 1);
	}

	bool MessageBox__(char* BIGTEXT, char* SMALLTEXT)
	{
		int scaleform = GRAPHICS::REQUEST_SCALEFORM_MOVIE("MP_AWARD_BASE");
		while (!GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED)
		{
			SYSTEM::WAIT(0);
		}
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(scaleform, "SHOW_AWARD_AND_MESSAGE");
		GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_STRING(BIGTEXT);
		GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_STRING(SMALLTEXT);
		GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_INT(5);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
		GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(scaleform, 255, 255, 255, 255, 1);
	}

	void Spriter(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a)
	{
		if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED((char*)Streamedtexture.c_str()))
		{
			GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT((char*)Streamedtexture.c_str(), false);
		}
		else
		{
			GRAPHICS::DRAW_SPRITE((char*)Streamedtexture.c_str(), (char*)textureName.c_str(), x, y, width, height, rotation, r, g, b, a, 0);
		}
	}

	char* StringToChar(std::string string)
	{
		return _strdup(string.c_str());
	}

	Ped ClonePed(Ped ped)
	{
		if (ENTITY::DOES_ENTITY_EXIST(ped) && !ENTITY::IS_ENTITY_DEAD(ped, 0))
		{
			return PED::CLONE_PED(ped, ENTITY::GET_ENTITY_HEADING(ped), 1, 1);
		}

		return 0;
	}

	Hash $(std::string str) {
		return MISC::GET_HASH_KEY(&str[0u]);
	}

	std::string FloatToString(float flt)
	{
		std::ostringstream ss;
		ss << flt;
		std::string str(ss.str());
		return str;
	}

	DWORD StringToDWORD(std::string str)
	{
		DWORD doubleWord;
		std::string dwordHexString = str;
		std::stringstream dwordStream;
		dwordStream << dwordHexString;
		dwordStream >> std::hex >> doubleWord;
		return doubleWord;
	}

	float StringToFloat(std::string str)
	{
		return ::atof(str.c_str());
	}

	void notifyMap(int notifyColor, const char* fmt, ...)
	{
		char buf[2048] = { 0 };
		va_list va_alist;

		va_start(va_alist, fmt);
		vsprintf_s(buf, fmt, va_alist);
		va_end(va_alist);

		char buff2[2048] = { 0 };
		sprintf_s(buff2, "%s", buf);

		HUD::SET_TEXT_OUTLINE();
		HUD::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(buff2);
		HUD::_DRAW_NOTIFICATION(FALSE, FALSE);
		HUD::_SET_NOTIFICATION_BACKGROUND_COLOR(notifyColor);
	}	void notifyMap(std::string str) { notifyMap(&str[0]); }

	Nano::n_Vector3 TPCoords;
	void TPto(Nano::n_Vector3 Coords)
	{
		int Handle = PLAYER::PLAYER_PED_ID();
		if (PED::IS_PED_IN_ANY_VEHICLE(Handle, 0))
		{
			ENTITY::SET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_IN(Handle, false), Coords.x, Coords.y, Coords.z, 0, 0, 0, 1);
		}
		else
		{
			ENTITY::SET_ENTITY_COORDS(Handle, Coords.x, Coords.y, Coords.z, 0, 0, 0, 1);
		}
	}

	void ApplyForceToEntity(Entity e, float x, float y, float z)
	{
		if (e != PLAYER::PLAYER_PED_ID() && NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(e) == FALSE)
		{
			RequestControlOfEnt(e);
		}

		ENTITY::APPLY_FORCE_TO_ENTITY(e, 1, x, y, z, 0, 0, 0, 0, 1, 1, 1, 0, 1);

	}

	int IconNotification(const char* text, const char* text2, const char* Subject)
	{
		HUD::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
		HUD::_SET_NOTIFICATION_MESSAGE_CLAN_TAG("CHAR_GANGAPP", "CHAR_GANGAPP", true, 7, text2, Subject, 1.0, "___CMPX");
		return HUD::_DRAW_NOTIFICATION(1, 1);
	}

	BOOL IsPlayerFriend(Player player)
	{
		int handle[76];
		NETWORK::NETWORK_HANDLE_FROM_PLAYER(player, &handle[0], 13);
		return NETWORK::NETWORK_IS_FRIEND(&handle[0]);
	}


	bool isPlayerFriend(Player player, bool& result)
	{
		int NETWORK_HANDLE[76];
		NETWORK::NETWORK_HANDLE_FROM_PLAYER(player, &NETWORK_HANDLE[0], 13);
		if (NETWORK::NETWORK_IS_HANDLE_VALID(&NETWORK_HANDLE[0], 13))
		{
			result = NETWORK::NETWORK_IS_FRIEND(&NETWORK_HANDLE[0]);
			return true;
		}
		return false;
	}

	void SETMODEL(const char* Model)
	{
		Hash model = MISC::GET_HASH_KEY(Model);
		g_CallbackScript->AddCallback<ModelCallback>((model), [=] {
			if (STREAMING::IS_MODEL_VALID(model)) {
				STREAMING::REQUEST_MODEL(model);
				while (!STREAMING::HAS_MODEL_LOADED(model)) g_FiberScript->Wait(0);
				PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), model);
				PED::SET_PED_DEFAULT_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID());
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
			}
		});
	}

	namespace Nano
	{
		NativeVector3 rot_to_direction(NativeVector3* rot)
		{
			float radiansZ = rot->z * 0.0174532924f;
			float radiansX = rot->x * 0.0174532924f;
			float num = abs((float)cos((double)radiansX));
			NativeVector3 dir;
			dir.x = (float)((double)((float)(-(float)sin((double)radiansZ))) * (double)num);
			dir.y = (float)((double)((float)cos((double)radiansZ)) * (double)num);
			dir.z = (float)sin((double)radiansX);
			return dir;
		}

		n_Vector3 rot_to_directionnnn(n_Vector3* rot)
		{
			float radiansZ = rot->z * 0.0174532924f;
			float radiansX = rot->x * 0.0174532924f;
			float num = abs((float)cos((double)radiansX));
			n_Vector3 dir;
			dir.x = (float)((double)((float)(-(float)sin((double)radiansZ))) * (double)num);
			dir.y = (float)((double)((float)cos((double)radiansZ)) * (double)num);
			dir.z = (float)sin((double)radiansX);
			return dir;
		}

		NativeVector3 add(NativeVector3* vectorA, NativeVector3* vectorB)
		{
			NativeVector3 result;
			result.x = vectorA->x;
			result.y = vectorA->y;
			result.z = vectorA->z;
			result.x += vectorB->x;
			result.y += vectorB->y;
			result.z += vectorB->z;
			return result;
		}

		NativeVector3 multiply(NativeVector3* vector, float x)
		{
			NativeVector3 result;
			result.x = vector->x;
			result.y = vector->y;
			result.z = vector->z;
			result.x *= x;
			result.y *= x;
			result.z *= x;
			return result;
		}

		float get_distance(NativeVector3* pointA, NativeVector3* pointB)
		{
			float a_x = pointA->x;
			float a_y = pointA->y;
			float a_z = pointA->z;
			float b_x = pointB->x;
			float b_y = pointB->y;
			float b_z = pointB->z;
			double x_ba = (double)(b_x - a_x);
			double y_ba = (double)(b_y - a_y);
			double z_ba = (double)(b_z - a_z);
			double y_2 = y_ba * y_ba;
			double x_2 = x_ba * x_ba;
			double sum_2 = y_2 + x_2;
			return(float)sqrt(sum_2 + z_ba);
		}

		float get_vector_length(NativeVector3* vector)
		{
			double x = (double)vector->x;
			double y = (double)vector->y;
			double z = (double)vector->z;
			return(float)sqrt(x * x + y * y + z * z);
		}

		NativeVector3 rotDirection(NativeVector3* rot)
		{
			float radianz = rot->z * 0.0174532924f;
			float radianx = rot->x * 0.0174532924f;
			float num = std::abs((float)std::cos((double)radianx));

			NativeVector3 dir;

			dir.x = (float)((double)((float)(-(float)std::sin((double)radianz))) * (double)num);
			dir.y = (float)((double)((float)std::cos((double)radianz)) * (double)num);
			dir.z = (float)std::sin((double)radianx);

			return dir;
		}

		float distanceBetween(NativeVector3 A, NativeVector3 B) {
			return MISC::GET_DISTANCE_BETWEEN_COORDS(A.x, A.y, A.z, B.x, B.y, B.z, 1);
		}
	}

	//CONTROL
	void RequestControlOfid(Entity netid)
	{
		int tick = 0;

		while (!NETWORK::NETWORK_HAS_CONTROL_OF_NETWORK_ID(netid) && tick <= 25)
		{
			NETWORK::NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(netid);
			tick++;
		}
	}

	void RequestControlOfEnt(Entity entity)
	{
		int tick = 0;
		while (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(entity) && tick <= 25)
		{
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(entity);
			tick++;
		}
		if (NETWORK::NETWORK_IS_SESSION_STARTED())
		{
			int netID = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(entity);
			RequestControlOfid(netID);
			NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netID, 1);
		}
	}

	void Teleport(float pX, float pY, float pZ)
	{
		Entity Player = PLAYER::PLAYER_PED_ID();
		Entity tp_OP;
		if (ENTITY::IS_ENTITY_A_PED(Player) && PED::IS_PED_IN_ANY_VEHICLE(Player, 1))
			tp_OP = PED::GET_VEHICLE_PED_IS_IN(Player, 0);
		else tp_OP = Player;

		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(tp_OP, pX, pY, pZ, 0, 0, 1);
	}

	/* INI*/
	void WriteStringToIni(std::string string, std::string file, std::string app, std::string key)
	{
		WritePrivateProfileStringA(app.c_str(), key.c_str(), string.c_str(), file.c_str());
	}

	std::string ReadStringFromIni(std::string file, std::string app, std::string key)
	{
		char buf[100];
		GetPrivateProfileStringA(app.c_str(), key.c_str(), "NULL", buf, 100, file.c_str());
		return (std::string)buf;
	}

	void WriteIntToIni(int intValue, std::string file, std::string app, std::string key)
	{
		WriteStringToIni(std::to_string(intValue), file, app, key);
	}

	int ReadIntFromIni(std::string file, std::string app, std::string key)
	{
		return std::stoi(ReadStringFromIni(file, app, key));
	}

	void WriteFloatToIni(float floatValue, std::string file, std::string app, std::string key)
	{
		WriteStringToIni((std::to_string(floatValue)), file, app, key);
	}

	float ReadFloatFromIni(std::string file, std::string app, std::string key)
	{
		return std::stof(ReadStringFromIni(file, app, key));
	}

	void WriteBoolToIni(bool b00l, std::string file, std::string app, std::string key)
	{
		WriteStringToIni(b00l ? "true" : "false", file, app, key);
	}

	bool ReadBoolFromIni(std::string file, std::string app, std::string key)
	{
		return ReadStringFromIni(file, app, key) == "true" ? true : false;
	}


	float GravityGunGoto(float aimX, float entityX)
	{
		static float GravityGunVeloPos;
		if (aimX > 0 && entityX > 0)
		{
			GravityGunVeloPos = aimX - (entityX);
		}

		if (aimX < 0 && entityX < 0)
		{
			GravityGunVeloPos = aimX - (entityX);
		}

		if (aimX > 0 && entityX < 0)
		{
			GravityGunVeloPos = aimX + (entityX);
		}

		if (aimX < 0 && entityX > 0)
		{
			GravityGunVeloPos = aimX + (entityX);
		}

		return GravityGunVeloPos;
	}
}