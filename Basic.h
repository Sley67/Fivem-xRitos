#pragma once

namespace Big
{

	struct WC
	{
		static NativeVector3 SetPos(Entity e);
		static NativeVector3 GetPos(Entity e);

	}; extern WC wc;

	namespace Nano
	{
#pragma pack(push, 1)
		typedef struct
		{
			float x;
			DWORD _paddingx;
			float y;
			DWORD _paddingy;
			float z;
			DWORD _paddingz;
		} n_Vector3;
#pragma pack(pop)

		n_Vector3 rot_to_directionnnn(n_Vector3* rot);
		NativeVector3 rot_to_direction(NativeVector3* rot);
		NativeVector3 add(NativeVector3* vectorA, NativeVector3* vectorB);
		NativeVector3 multiply(NativeVector3* vector, float x);
		NativeVector3 rotDirection(NativeVector3* rot);
		float get_distance(NativeVector3* pointA, NativeVector3* pointB);
		float get_vector_length(NativeVector3* vector);
		float distanceBetween(NativeVector3 A, NativeVector3 B);

	}

	/* BASIC UTILLITY*/
	void notifyMap(int notifyColor, const char* fmt, ...);
	void TPto(Nano::n_Vector3 Coords);
	char* StringToChar(std::string string);
	std::string FloatToString(float flt);
	DWORD StringToDWORD(std::string str);
	float StringToFloat(std::string str);
	void ApplyForceToEntity(Entity e, float x, float y, float z);
	Hash $(std::string str);
	Ped ClonePed(Ped ped);
	int IconNotification(const char* text,  const char* text2, const char* Subject);
	void Teleport(float pX, float pY, float pZ);
	BOOL IsPlayerFriend(Player player);
	bool isPlayerFriend(Player player, bool& result);
	void SETMODEL(const char* Model);
	void Spriter(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a);

	/* CONTROL */
	void RequestControlOfid(Entity netid);
	void RequestControlOfEnt(Entity entity);
	float GravityGunGoto(float aimX, float entityX);

	/* INI */
	void WriteStringToIni(std::string string, std::string file, std::string app, std::string key);
	std::string ReadStringFromIni(std::string file, std::string app, std::string key);
	void WriteIntToIni(int intValue, std::string file, std::string app, std::string key);
	int ReadIntFromIni(std::string file, std::string app, std::string key);
	void WriteFloatToIni(float floatValue, std::string file, std::string app, std::string key);
	float ReadFloatFromIni(std::string file, std::string app, std::string key);
	void WriteBoolToIni(bool b00l, std::string file, std::string app, std::string key);
	bool ReadBoolFromIni(std::string file, std::string app, std::string key);



	namespace NanoStuff
	{
		typedef DWORD Void;
		typedef DWORD Any;
		typedef DWORD uint;
		typedef DWORD Hash;
		typedef int Entity;
		typedef int Player;
		typedef int FireId;
		typedef int Ped;
		typedef int Vehicle;
		typedef int Cam;
		typedef int CarGenerator;
		typedef int Group;
		typedef int Train;
		typedef int Pickup;
		typedef int Object;
		typedef int Weapon;
		typedef int Interior;
		typedef int Blip;
		typedef int Texture;
		typedef int TextureDict;
		typedef int CoverPoint;
		typedef int Camera;
		typedef int TaskSequence;
		typedef int ColourIndex;
		typedef int Sphere;
		typedef int ScrHandle;
	}

	struct ObjectInfo
	{
		DWORD hash;
		float X;
		float Y;
		float Z;
		float RotX;
		float RotY;
		float RotZ;
	};
	typedef DWORD uint;

	uint Weapons[] = {
	0x92A27487, 0x958A4A8F, 0xF9E6AA4B, 0x84BD7BFD, 0xA2719263, 0x8BB05FD7, 0x440E4788, 0x4E875F73, 0xF9DCBF2D, 0xD8DF3C3C, 0x99B507EA, 0xDD5DF8D9, 0xDFE37640, 0x678B81B1, 0x19044EE0, 0xCD274149, 0x94117305, 0x3813FC08, // Melee
	0x1B06D571, 0xBFE256D4, 0x5EF9FEC4, 0x22D8FE39, 0x3656C8C1, 0x99AEEB3B, 0xBFD21232, 0x88374054, 0xD205520E, 0x83839C4, 0x47757124, 0xDC4DB296, 0xC1B3C3D1, 0xCB96392F, 0x97EA20B8, // Handguns
	0x13532244, 0x2BE6766B, 0x2BE6766B, 0xEFE7E2DF, 0x0A3D4D34, 0xDB1AA450, 0xBD248B55, // Submachine Guns
	0x1D073A89, 0x555AF99A, 0x7846A318, 0xE284C527, 0x9D61E50F, 0xA89CB99E, 0x3AABBBAA, 0xEF951FBB, 0x12E82D3D, // Shotguns
	0xBFEFFF6D, 0x394F415C, 0x83BF0278, 0xFAD1F1C9, 0xAF113F99, 0xC0A3098D, 0x969C3D67, 0x7F229F94, 0x84D6FAFD, 0x624FE830, // Assault Rifles
	0x9D07F764, 0x7FD62962, 0xDBBD7280, 0x61012683, // Light Machine Guns
	0x05FC3C11, 0x0C472FE2, 0xA914799, 0xC734385A, 0x6A6C02E0, // Sniper Rifles
	0xB1CA77B1, 0xA284510B, 0x4DD2DC56, 0x42BF8A85, 0x7F7497E5, 0x6D544C99, 0x63AB0442, 0x0781FE4A, // Heavy Weapons
	0x93E220BD, 0xA0973D5E, 0x24B17070, 0x2C3731D9, 0xAB564B93, 0x787F0BB, 0xBA45E8B8, 0x23C9F95C, 0xFDBC8A50, 0x497FACC3, // Throwables
	0x34A67B97, 0xFBAB5776, 0x060EC506, // Miscellaneous
	0xAF3696A1, 0x476BF155, 0xB62D1F67,	 // 1.46
	0x2B5EF5EC, 0x2CE227AC, 0x832A1A76, 0x917F6C8C //Casino
	};
}