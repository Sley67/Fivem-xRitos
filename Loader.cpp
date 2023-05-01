#include "Common.hpp"
#include "ScriptCallback.hpp"

#include <filesystem>

namespace Big
{


	/* OUTFITS */

	int o1, o2, o3, o4, o5, o6, o7, o8, o9, o10, o11, o12, o13, o14 = 0;

	std::string oName;

	bool CreateOutfitWindow = true;

	void CreateOutfitFile()
	{
		CreateOutfitWindow = true;

		std::string iniPath = "C:\\Viper\\Outfits\\" + oName + ".ini";

		WritePrivateProfileStringA("Outfit", "Face", std::to_string(o1).c_str(), iniPath.c_str());
		WritePrivateProfileStringA("Outfit", "Head", std::to_string(o2).c_str(), iniPath.c_str());
		WritePrivateProfileStringA("Outfit", "Hair", std::to_string(o3).c_str(), iniPath.c_str());
		WritePrivateProfileStringA("Outfit", "Torso", std::to_string(o4).c_str(), iniPath.c_str());
		WritePrivateProfileStringA("Outfit", "Legs", std::to_string(o5).c_str(), iniPath.c_str());
		WritePrivateProfileStringA("Outfit", "Hands", std::to_string(o6).c_str(), iniPath.c_str());
		WritePrivateProfileStringA("Outfit", "Feet", std::to_string(o7).c_str(), iniPath.c_str());
		WritePrivateProfileStringA("Outfit", "Eyes", std::to_string(o8).c_str(), iniPath.c_str());
		WritePrivateProfileStringA("Outfit", "Accessories", std::to_string(o9).c_str(), iniPath.c_str());
		WritePrivateProfileStringA("Outfit", "Tasks", std::to_string(o10).c_str(), iniPath.c_str());
		WritePrivateProfileStringA("Outfit", "Textures", std::to_string(o11).c_str(), iniPath.c_str());
		WritePrivateProfileStringA("Outfit", "Torso2", std::to_string(o12).c_str(), iniPath.c_str());
		WritePrivateProfileStringA("Outfit", "HeadProp", std::to_string(o13).c_str(), iniPath.c_str());
		WritePrivateProfileStringA("Outfit", "EyeProp", std::to_string(o14).c_str(), iniPath.c_str());
	}

	void CreateRIDConfig(string name, const char* id)
	{
		std::string iniPath = "C:\\Viper\\Manager\\RIDManager\\" + name + ".ini";

		WriteIntToIni(atoi(id), iniPath, name, "RID");
	}

	void CreateVehicleFile(std::uint32_t name)
	{
		std::string iniPath = "C:\\Viper\\Manager\\VehicleManager\\" + std::to_string(name) + ".ini";

		WritePrivateProfileStringA("Vehicle", std::to_string(name).c_str(), NULL, iniPath.c_str());
	}

	std::vector<std::string> outfitNames;

	std::vector<std::string> RIDnames;

	std::vector<std::int32_t> _VehicleList;

	std::vector<std::int32_t> VehicleName;


	std::vector<std::string> RIDList()
	{
		std::string folderpath = "C:\\Viper\\Manager\\RIDManager\\";
		if (!fs::exists(folderpath.c_str()))
		{
			fs::create_directory(folderpath.c_str());
		}
		std::vector<std::string> tempVector;
		int fileCount = 0;
		std::stringstream tempStringStream;
		for (auto& collectedFiles : std::experimental::filesystem::v1::directory_iterator("C:\\Viper\\Manager\\RIDManager\\"))
		{
			tempStringStream << collectedFiles;
			std::string oing = tempStringStream.str();
			if (oing.substr(oing.find_last_of(".") + 1) == "ini")
			{
				unsigned foundAmount = oing.find_last_of("/\\");
				std::string TempHolder = oing.substr(0, foundAmount);
				std::string TempHolder2 = oing.substr(foundAmount + 1);
				tempVector.push_back(TempHolder2.substr(0, TempHolder2.find(".", 0)));
				RIDnames = tempVector;
			}
		}
		return tempVector;
	}

	std::vector<std::string> VehicleList()
	{
		std::string folderpath = "C:\\Viper\\Manager\\VehicleManager\\";
		if (!fs::exists(folderpath.c_str()))
		{
			fs::create_directory(folderpath.c_str());
		}
		std::vector<std::string> tempVector;
		int fileCount = 0;
		std::stringstream tempStringStream;
		for (auto& collectedFiles : _VehicleList)	
		{
			tempStringStream << collectedFiles;
			std::string oing = tempStringStream.str();
			unsigned foundAmount = oing.find_last_of("/\\");
			std::string TempHolder = oing.substr(0, foundAmount);
			std::string TempHolder2 = oing.substr(foundAmount + 1);
			tempVector.push_back(TempHolder2.substr(0, TempHolder2.find(".", 0)));
		}
		return tempVector;
	}

	std::vector<std::string> OutfitList()
	{
		std::string folderpath = "C:\\Viper\\Outfits\\";
		if (!fs::exists(folderpath.c_str()))
		{
			fs::create_directory(folderpath.c_str());
		}
		std::vector<std::string> tempVector;
		int fileCount = 0;
		std::stringstream tempStringStream;
		for (auto& collectedFiles : std::experimental::filesystem::v1::directory_iterator("C:\\Viper\\Outfits\\"))
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

	//JoinRID
	void JoinRID(std::string name)
	{
		std::string iniPath = "C:\\\Viper\\Manager\\RIDManager\\" + name + ".ini";

		Join = ReadIntFromIni(iniPath.c_str(), name, "RID");
		Joiner = true;
		notifyMap(1, "~w~R*ID attached! \n ~g~Go to ONLINE, CREWS, CREW MEMBERS, selected an random crew member, hit JOIN game ");
	}

	void SetVehicleSub(Vehicle veh)
	{

	}

	void LoadOutfit(std::string name)
	{
		std::string iniPath = "C:\\Viper\\Outfits\\" + name + ".ini";
		char o1[255];
		char o2[255];
		char o3[255];
		char o4[255];
		char o5[255];
		char o6[255];
		char o7[255];
		char o8[255];
		char o9[255];
		char o10[255];
		char o11[255];
		char o12[255];
		char o13[255];
		char o14[255];
		char o15[255];
		GetPrivateProfileStringA("Outfit", "Face", "", o1, 255, iniPath.c_str());
		GetPrivateProfileStringA("Outfit", "Head", "", o2, 255, iniPath.c_str());
		GetPrivateProfileStringA("Outfit", "Hair", "", o3, 255, iniPath.c_str());
		GetPrivateProfileStringA("Outfit", "Torso", "", o4, 255, iniPath.c_str());
		GetPrivateProfileStringA("Outfit", "Legs", "", o5, 255, iniPath.c_str());
		GetPrivateProfileStringA("Outfit", "Hands", "", o6, 255, iniPath.c_str());
		GetPrivateProfileStringA("Outfit", "Feet", "", o7, 255, iniPath.c_str());
		GetPrivateProfileStringA("Outfit", "Eyes", "", o8, 255, iniPath.c_str());
		GetPrivateProfileStringA("Outfit", "Accessories", "", o9, 255, iniPath.c_str());
		GetPrivateProfileStringA("Outfit", "Tasks", "", o10, 255, iniPath.c_str());
		GetPrivateProfileStringA("Outfit", "Textures", "", o11, 255, iniPath.c_str());
		GetPrivateProfileStringA("Outfit", "Torso2", "", o12, 255, iniPath.c_str());
		GetPrivateProfileStringA("Outfit", "HeadProp", "", o13, 255, iniPath.c_str());
		GetPrivateProfileStringA("Outfit", "EyeProp", "", o14, 255, iniPath.c_str());
		GetPrivateProfileStringA("Outfit", "EarProp", "", o15, 255, iniPath.c_str());

		PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 0, atoi(o1), 0, 0);
		PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 1, atoi(o2), 0, 0);
		PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 2, atoi(o3), 0, 0);
		PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 3, atoi(o4), 0, 0);
		PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 4, atoi(o5), 0, 0);
		PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 5, atoi(o6), 0, 0);
		PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 6, atoi(o7), 0, 0);
		PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 7, atoi(o8), 0, 0);
		PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 8, atoi(o9), 0, 0);
		PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 9, atoi(o10), 0, 0);
		PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 10, atoi(o11), 0, 0);
		PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 11, atoi(o12), 0, 0);
		PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 1, atoi(o13), 0, 0);
		PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 2, atoi(o14), 0, 0);
		PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 3, atoi(o15), 0, 0);
	}

	/* INI Loader*/


	std::vector<std::string> omglolree;
	std::vector<std::string> listPresets()
	{
		std::vector<std::string> tempVector;
		int fileCount = 0;
		std::stringstream tempStringStream;
		for (auto& collectedFiles : std::experimental::filesystem::v1::directory_iterator("C:\\Viper\\Vehicles\\"))
		{
			tempStringStream << collectedFiles;
			std::string testing = tempStringStream.str();
			if (testing.substr(testing.find_last_of(".") + 1) == "ini") {
				unsigned foundAmount = testing.find_last_of("/\\");
				std::string TempHolder = testing.substr(0, foundAmount);
				std::string TempHolder2 = testing.substr(foundAmount + 1);
				tempVector.push_back(TempHolder2.substr(0, TempHolder2.find(".", 0)));
				omglolree = tempVector;
			}
		}
		return tempVector;
	}



	Object AttachObjectToVehicleByHash(Hash hash, float x, float y, float z, float rotx, float roty, float rotz, Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0)) {
		if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
			//CMenu::notifyBottom("~r~You need to be in a vehicle to load a preset !");
			return -1;
		}
		g_CallbackScript->AddCallback<ModelCallback>(hash, [hash] {

		});
		if (STREAMING::IS_MODEL_IN_CDIMAGE(hash)) {
			STREAMING::REQUEST_MODEL(hash);
			//while (!STREAMING::HAS_MODEL_LOADED(hash))
			NativeVector3 co = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
			Object obj = OBJECT::CREATE_OBJECT_NO_OFFSET(hash, co.x, co.y, co.z, 1, 0, 0);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(obj);
			ENTITY::FREEZE_ENTITY_POSITION(obj, 1);
			ENTITY::ATTACH_ENTITY_TO_ENTITY(obj, veh, 0, x, y, z, rotx, roty, rotz, 1, 0, 1, 0, 2, 1);
			return obj;
		}
		else
		{
			printf("Not in image");
			return -1;
		}
	}

	std::string ReadPresetKey(std::string name, std::string section, std::string key)
	{
		std::string iniPath = "C:\\Viper\\Vehicles\\" + name + ".ini";
		if (!std::ifstream(iniPath)) {
			std::ofstream file(iniPath);
		}
		char retVal[255];
		GetPrivateProfileStringA(section.c_str(), key.c_str(), "", retVal, 255, iniPath.c_str());
		return retVal;
	}

	bool DoesPresetKeyExists(std::string name, std::string section, std::string key)
	{
		return ReadPresetKey(name, section, key).length() > 0;
	}

	int GetNumberOfObjectFromFile(std::string name) {
		std::string iniPath = "C:\\Viper\\Vehicles\\" + name + ".ini";
		int no = 0;
		for (int i = 0; i < 150; i++)
		{
			if (DoesPresetKeyExists(name, FloatToString(i), "X"))
			{
				no++;
			}
			else
			{
				return no;
			}
		}
		return no;
	}

	Vehicle SpawnVehicleH(DWORD model, NativeVector3 coords, bool tpinto = 0, float heading = 0.0f) {
		if (STREAMING::IS_MODEL_IN_CDIMAGE(model)) {
			g_CallbackScript->AddCallback<ModelCallback>(model, [model, coords, heading, tpinto]
			{

			});
			Vehicle veh = TEST::CREATE_VEHICLE(model, coords, heading, *g_GameVariables->is_session_started, false);
			TEST::SET_VEHICLE_ON_GROUND_PROPERLY(veh);
			if (tpinto) {
				ENTITY::SET_ENTITY_HEADING(veh, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
			}
			VEHICLE::SET_VEHICLE_IS_STOLEN(veh, 0);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
			return veh;
		}

	}

	std::vector<int> ToggleTypes = { 17, 18, 19, 20, 21, 22 };
	std::vector<int> ModTypes = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 23, 24, 26, 25, 48, 37, 27, 28, 30, 33, 34, 35, 38, 39, 45 };
	std::vector<Object> Spawned;

	void printf(std::string f)
	{
		printf(f.c_str());
	}

	void WriteVehicle(std::string name, Vehicle veh)
	{
		std::string iniPath = "C:\\Viper\\Vehicles\\" + name + ".ini";
		for (int i = 0; i < ModTypes.size(); i++) {
			WritePrivateProfileStringA("Vehicle", FloatToString(ModTypes[i]).c_str(), FloatToString(VEHICLE::GET_VEHICLE_MOD(veh, ModTypes[i])).c_str(), iniPath.c_str());
		}
		int HUDColour, HUDLightsColour;
		//VEHICLE::_GET_INTERIOR_DASH_LIGHT_COLOR(veh, &HUDLightsColour);
		//VEHICLE::_GET_INTERIOR_COATING_COLOR(veh, &HUDColour);
		WritePrivateProfileStringA("Vehicle", "DashColor", FloatToString(HUDColour).c_str(), iniPath.c_str());
		WritePrivateProfileStringA("Vehicle", "DashLightColor", FloatToString(HUDLightsColour).c_str(), iniPath.c_str());
		int PpaintType = 0;
		int Pcolor = 0;
		int SpaintType = 0;
		int Scolor = 0;
		int Sr, Sg, Sb, Pr, Pg, Pb;
		int Prnd;
		int pearlescent, wheelColor;
		int wheelType = VEHICLE::GET_VEHICLE_WHEEL_TYPE(veh);
		int PlateIndex = VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(veh);
		const char* PlateText = TEST::GET_VEHICLE_NUMBER_PLATE_TEXT(veh); //const
		bool Bulletproof = !VEHICLE::GET_VEHICLE_TYRES_CAN_BURST(veh);
		bool CustomTyres = VEHICLE::GET_VEHICLE_MOD_VARIATION(veh, 23);
		WritePrivateProfileStringA("Vehicle", "Bulletproof", FloatToString(Bulletproof).c_str(), iniPath.c_str());
		WritePrivateProfileStringA("Vehicle", "CustomTyres", FloatToString(CustomTyres).c_str(), iniPath.c_str());
		int NeonR, NeonG, NeonB, SmokeR, SmokeG, SmokeB;
		bool NeonEnabled;
		VEHICLE::_GET_VEHICLE_NEON_LIGHTS_COLOUR(veh, &NeonR, &NeonG, &NeonB);
		VEHICLE::GET_VEHICLE_TYRE_SMOKE_COLOR(veh, &SmokeR, &SmokeG, &SmokeB);
		if (VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(veh, 0)) NeonEnabled = 1;
		for (int i = 0; i < ToggleTypes.size(); i++)
		{
			WritePrivateProfileStringA("Vehicle", std::string("TOGGLE_" + FloatToString(ToggleTypes[i])).c_str(), FloatToString(VEHICLE::IS_TOGGLE_MOD_ON(veh, ToggleTypes[i])).c_str(), iniPath.c_str());
		}
		int WindowTintIndex = VEHICLE::GET_VEHICLE_WINDOW_TINT(veh);
		WritePrivateProfileStringA("Vehicle", "NeonEnabled", FloatToString(NeonEnabled).c_str(), iniPath.c_str());
		WritePrivateProfileStringA("Vehicle", "NeonR", FloatToString(NeonR).c_str(), iniPath.c_str());
		WritePrivateProfileStringA("Vehicle", "NeonG", FloatToString(NeonG).c_str(), iniPath.c_str());
		WritePrivateProfileStringA("Vehicle", "NeonB", FloatToString(NeonB).c_str(), iniPath.c_str());
		WritePrivateProfileStringA("Vehicle", "SmokeR", FloatToString(SmokeR).c_str(), iniPath.c_str());
		WritePrivateProfileStringA("Vehicle", "SmokeG", FloatToString(SmokeG).c_str(), iniPath.c_str());
		WritePrivateProfileStringA("Vehicle", "SmokeB", FloatToString(SmokeB).c_str(), iniPath.c_str());
		WritePrivateProfileStringA("Vehicle", "WindowTint", FloatToString(WindowTintIndex).c_str(), iniPath.c_str());
		VEHICLE::GET_VEHICLE_MOD_COLOR_1(veh, &PpaintType, &Pcolor, &Prnd);
		VEHICLE::GET_VEHICLE_MOD_COLOR_2(veh, &SpaintType, &Scolor);
		VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, &Pr, &Pg, &Pb);
		VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, &Sr, &Sg, &Sb);
		VEHICLE::GET_VEHICLE_EXTRA_COLOURS(veh, &pearlescent, &wheelColor);
		std::ostringstream os; os << ENTITY::GET_ENTITY_MODEL(veh);
		WritePrivateProfileStringA("Vehicle", "Model", os.str().c_str(), iniPath.c_str());
		WritePrivateProfileStringA("Vehicle", "PrimaryPaintT", FloatToString(PpaintType).c_str(), iniPath.c_str());
		WritePrivateProfileStringA("Vehicle", "SecondaryPaintT", FloatToString(SpaintType).c_str(), iniPath.c_str());
		WritePrivateProfileStringA("Vehicle", "PrimaryPaint", FloatToString(Pcolor).c_str(), iniPath.c_str());
		WritePrivateProfileStringA("Vehicle", "SecondaryPaint", FloatToString(Scolor).c_str(), iniPath.c_str());
		WritePrivateProfileStringA("Vehicle", "Pearlescent", FloatToString(pearlescent).c_str(), iniPath.c_str());
		WritePrivateProfileStringA("Vehicle", "PrimaryR", FloatToString(Pr).c_str(), iniPath.c_str());
		WritePrivateProfileStringA("Vehicle", "PrimaryG", FloatToString(Pg).c_str(), iniPath.c_str());
		WritePrivateProfileStringA("Vehicle", "PrimaryB", FloatToString(Pb).c_str(), iniPath.c_str());
		WritePrivateProfileStringA("Vehicle", "SecondaryR", FloatToString(Sr).c_str(), iniPath.c_str());
		WritePrivateProfileStringA("Vehicle", "SecondaryG", FloatToString(Sg).c_str(), iniPath.c_str());
		WritePrivateProfileStringA("Vehicle", "SecondaryB", FloatToString(Sb).c_str(), iniPath.c_str());
		WritePrivateProfileStringA("Vehicle", "WheelsColor", FloatToString(wheelColor).c_str(), iniPath.c_str());
		WritePrivateProfileStringA("Vehicle", "WheelsType", FloatToString(wheelType).c_str(), iniPath.c_str());
		WritePrivateProfileStringA("Vehicle", "Unknown", FloatToString(Prnd).c_str(), iniPath.c_str());
		WritePrivateProfileStringA("Vehicle", "Unknown", FloatToString(PlateIndex).c_str(), iniPath.c_str());
		WritePrivateProfileStringA("Vehicle", "PlateText", PlateText, iniPath.c_str());
		for (int i = 0; i < 10; i++) {
			if (VEHICLE::DOES_EXTRA_EXIST(veh, i)) {
				WritePrivateProfileStringA("Vehicle", std::string("Extra_" + FloatToString(i)).c_str(), FloatToString(VEHICLE::IS_VEHICLE_EXTRA_TURNED_ON(veh, i)).c_str(), iniPath.c_str());
			}
		}
		//CMenu::notifyBottom("~g~Successfully saved vehicle. !");
	}

	void SavePreset(std::vector<ObjectInfo> ObjectList, std::string name, bool bWriteVehicle = 0) {
		std::string iniPath = "C:\\Viper\\Vehicles" + name + ".ini";
		if (bWriteVehicle) WriteVehicle(name, PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0));
		for (int i = 0; i < ObjectList.size(); i++) {
			std::ostringstream os;
			os << ObjectList[i].hash;
			ObjectList[i].X = round(ObjectList[i].X * 10000) / 10000;
			ObjectList[i].Y = round(ObjectList[i].Y * 10000) / 10000;
			ObjectList[i].Z = round(ObjectList[i].Z * 10000) / 10000;
			ObjectList[i].RotX = round(ObjectList[i].RotX * 10000) / 10000;
			ObjectList[i].RotY = round(ObjectList[i].RotY * 10000) / 10000;
			ObjectList[i].RotZ = round(ObjectList[i].RotZ * 10000) / 10000;
			WritePrivateProfileStringA(FloatToString(i).c_str(), "X", FloatToString(ObjectList[i].X).c_str(), iniPath.c_str());
			WritePrivateProfileStringA(FloatToString(i).c_str(), "Y", FloatToString(ObjectList[i].Y).c_str(), iniPath.c_str());
			WritePrivateProfileStringA(FloatToString(i).c_str(), "Z", FloatToString(ObjectList[i].Z).c_str(), iniPath.c_str());
			WritePrivateProfileStringA(FloatToString(i).c_str(), "RotX", FloatToString(ObjectList[i].RotX).c_str(), iniPath.c_str());
			WritePrivateProfileStringA(FloatToString(i).c_str(), "RotY", FloatToString(ObjectList[i].RotY).c_str(), iniPath.c_str());
			WritePrivateProfileStringA(FloatToString(i).c_str(), "RotZ", FloatToString(ObjectList[i].RotZ).c_str(), iniPath.c_str());
			WritePrivateProfileStringA(FloatToString(i).c_str(), "Model", os.str().c_str(), iniPath.c_str());
			printf("\r\n<SAVE # " + FloatToString(i) + " > \r\n");
			printf("\r\nName:" + name);
			printf("\r\X:" + FloatToString(ObjectList[i].X));
			printf("\r\nY:" + FloatToString(ObjectList[i].Y));
			printf("\r\nZ:" + FloatToString(ObjectList[i].Z));
			printf("\r\nRotX:" + FloatToString(ObjectList[i].RotX));
			printf("\r\nRotY:" + FloatToString(ObjectList[i].RotY));
			printf("\r\nRotZ:" + FloatToString(ObjectList[i].RotZ));
			printf("\r\n< END OF SAVE # " + FloatToString(i) + " > \r\n");
		}
		//CMenu::notifyBottom("Preset Saved !");
	}


	int st(std::string txt) { return atoi(txt.c_str()); }

	Vehicle LoadVehicle(std::string name) {
		std::string iniPath = "C:\\Viper\\Vehicles\\" + name + ".ini";
		if (DoesPresetKeyExists(name, "Vehicle", "Model"))
		{
			Hash Model = static_cast<DWORD>(atoll(ReadPresetKey(name, "Vehicle", "Model").c_str()));
			Vehicle veh = SpawnVehicleH(Model, TEST::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0, 5, 0), 1);
			RequestControlOfEnt(veh);
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
			int WheelsType;
			WheelsType = st(ReadPresetKey(name, "Vehicle", "WheelsType"));
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(veh, WheelsType);
			bool CustomTyres = st(ReadPresetKey(name, "Vehicle", "CustomTyres"));
			for (int i = 0; i < ModTypes.size(); i++) {
				int mod = st(ReadPresetKey(name, "Vehicle", FloatToString(ModTypes[i])));
				VEHICLE::SET_VEHICLE_MOD(veh, ModTypes[i], mod, CustomTyres);
			}
			int HUDColor = st(ReadPresetKey(name, "Vehicle", "DashColor"));
			int HUDLightsColor = st(ReadPresetKey(name, "Vehicle", "DashLightColor"));
			TEST::_SET_INTERIOR_DASH_LIGHT_COLOR(veh, HUDLightsColor);
			TEST::_SET_INTERIOR_COATING_COLOR(veh, HUDColor);
			std::string PlateText;
			int NeonR, NeonG, NeonB, SmokeR, SmokeG, SmokeB, BulletProof;
			bool NeonEnabled;
			for (int i = 0; i < ToggleTypes.size(); i++) {
				int mod = st(ReadPresetKey(name, "Vehicle", std::string("TOGGLE_" + FloatToString(ToggleTypes[i])).c_str()));

				VEHICLE::TOGGLE_VEHICLE_MOD(veh, ToggleTypes[i], mod);
			}
			int WindowTintIndex = st(ReadPresetKey(name, "Vehicle", "WindowTint"));
			NeonEnabled = st(ReadPresetKey(name, "Vehicle", "NeonEnabled"));
			NeonR = st(ReadPresetKey(name, "Vehicle", "NeonR"));
			NeonG = st(ReadPresetKey(name, "Vehicle", "NeonG"));
			NeonB = st(ReadPresetKey(name, "Vehicle", "NeonB"));
			SmokeR = st(ReadPresetKey(name, "Vehicle", "SmokeR"));
			SmokeG = st(ReadPresetKey(name, "Vehicle", "SmokeG"));
			SmokeB = st(ReadPresetKey(name, "Vehicle", "SmokeB"));
			BulletProof = st(ReadPresetKey(name, "Vehicle", "Bulletproof"));
			if (BulletProof == 1) {
				VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, 0);
				VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(veh, 0);
			}
			if (NeonEnabled) {
				VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
				VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
				VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
				VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
				VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, NeonR, NeonG, NeonB);
			}
			VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, WindowTintIndex);
			VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, SmokeR, SmokeG, SmokeB);
			int PrimaryPaintType, SecondaryPaintType, PrimaryPaintID, SecondaryPaintID, Pearlescent, PrimaryR, PrimaryG, PrimaryB, SecondaryR, SecondaryG, SecondaryB, WheelsColor, Unknown, PlateIndex;
			PrimaryPaintType = st(ReadPresetKey(name, "Vehicle", "PrimaryPaintT"));
			SecondaryPaintType = st(ReadPresetKey(name, "Vehicle", "SecondaryPaintT"));
			PrimaryPaintID = st(ReadPresetKey(name, "Vehicle", "PrimaryPaint"));
			SecondaryPaintID = st(ReadPresetKey(name, "Vehicle", "SecondaryPaint"));
			Pearlescent = st(ReadPresetKey(name, "Vehicle", "Pearlescent"));
			PrimaryR = st(ReadPresetKey(name, "Vehicle", "PrimaryR"));
			PrimaryG = st(ReadPresetKey(name, "Vehicle", "PrimaryG"));
			PrimaryB = st(ReadPresetKey(name, "Vehicle", "PrimaryB"));
			SecondaryR = st(ReadPresetKey(name, "Vehicle", "SecondaryR"));
			SecondaryG = st(ReadPresetKey(name, "Vehicle", "SecondaryG"));
			SecondaryB = st(ReadPresetKey(name, "Vehicle", "SecondaryB"));
			WheelsColor = st(ReadPresetKey(name, "Vehicle", "WheelsColor"));
			Unknown = st(ReadPresetKey(name, "Vehicle", "Unknown"));
			PlateIndex = st(ReadPresetKey(name, "Vehicle", "PlateIndex"));
			PlateText = ReadPresetKey(name, "Vehicle", "PlateText");
			VEHICLE::SET_VEHICLE_MOD_COLOR_1(veh, PrimaryPaintType, PrimaryPaintID, Unknown);
			VEHICLE::SET_VEHICLE_MOD_COLOR_2(veh, SecondaryPaintType, SecondaryPaintID);
			VEHICLE::SET_VEHICLE_COLOURS(veh, PrimaryPaintID, SecondaryPaintID);
			VEHICLE::SET_VEHICLE_EXTRA_COLOURS(veh, Pearlescent, WheelsColor);
			VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, PrimaryR, PrimaryG, PrimaryB);
			VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, SecondaryR, SecondaryG, SecondaryB);
			VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(veh, PlateIndex);
			VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, (char*)PlateText.c_str());
			//CMenu::notifyBottom("~g~Successfully loaded vehicle. !");
			for (int i = 0; i < 10; i++) {
				if (VEHICLE::DOES_EXTRA_EXIST(veh, i)) {
					int ExtraToggle = st(ReadPresetKey(name, "Vehicle", "Extra_" + FloatToString(i)));
					if (ExtraToggle == 1) {
						VEHICLE::SET_VEHICLE_EXTRA(veh, i, 0);
					}
					else {
						VEHICLE::SET_VEHICLE_EXTRA(veh, i, -1);
					}
				}
			}
			return veh;
		}
		return -1;
	}
	ObjectInfo ReadCustomPreset(std::string name, int id)
	{
		ObjectInfo oi;
		std::string iniPath = "C:\\Viper\\Vehicles\\" + name + ".ini";
		std::ostringstream ID; ID << id;
		oi.hash = static_cast<DWORD>(atoll(ReadPresetKey(name, ID.str(), "Model").c_str()));
		oi.X = StringToFloat((char*)ReadPresetKey(name, ID.str(), "X").c_str());
		oi.Y = StringToFloat((char*)ReadPresetKey(name, ID.str(), "Y").c_str());
		oi.Z = StringToFloat((char*)ReadPresetKey(name, ID.str(), "Z").c_str());
		oi.RotX = StringToFloat((char*)ReadPresetKey(name, ID.str(), "RotX").c_str());
		oi.RotY = StringToFloat((char*)ReadPresetKey(name, ID.str(), "RotY").c_str());
		oi.RotZ = StringToFloat((char*)ReadPresetKey(name, ID.str(), "RotZ").c_str());
		return oi;
	}


	void LoadPreset(std::string name)
	{
		Vehicle veh = LoadVehicle(name);
		for (int i = 0; i < GetNumberOfObjectFromFile(name); i++)
		{
			if (veh != -1)
			{
				ObjectInfo preset = ReadCustomPreset(name, i);
				Object ob = AttachObjectToVehicleByHash(preset.hash, preset.X, preset.Y, preset.Z, preset.RotX, preset.RotY, preset.RotZ, veh);
				Spawned.push_back(ob);
			}
			else
			{
				if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
					//CMenu::notifyBottom("You need to be in a vehicle to do this"); return;
				}
				ObjectInfo preset = ReadCustomPreset(name, i);
				Object ob = AttachObjectToVehicleByHash(preset.hash, preset.X, preset.Y, preset.Z, preset.RotX, preset.RotY, preset.RotZ);
				Spawned.push_back(ob);
			}
		}
	}

	bool add_to_folder;

	bool FileExistsssssssssssss(const std::string& fileName)
	{
		struct stat buffer;
		return (stat(fileName.c_str(), &buffer) == 0);
	}

	std::vector<std::int32_t> living_peds_list;
	int pedNumber;
	void load_peds(const char* ped_name)
	{
		int PedHash = MISC::GET_HASH_KEY(ped_name);

		NativeVector3 player_position = wc.GetPos(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()));

		STREAMING::REQUEST_MODEL(PedHash);
		Ped ped = PED::CREATE_PED(1, PedHash, player_position.x, player_position.y, player_position.z, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), 1, 1);
		
		

		if (add_to_folder)
		{
			if (FileExistsssssssssssss("C:\\Viper\\Pedestrian Manager\\" + (std::string)ped_name))
			{

			}
			else
			{
				WriteStringToIni(ped_name, "C:\\Viper\\Pedestrian Manager\\" + (std::string)ped_name, "a", "b");
			}
		}
	}

	

	std::vector<std::string> alivepedlist()
	{
		std::string folderpath = "C:\\Viper\\Pedestrian Manager\\Current\\";
		if (!fs::exists(folderpath.c_str()))
		{
			fs::create_directory(folderpath.c_str());
		}
		std::vector<std::string> tempVector;
		int fileCount = 0;
		std::stringstream tempStringStream;
		for (auto& collectedFiles : std::experimental::filesystem::v1::directory_iterator("C:\\Viper\\Pedestrian Manager\\Current\\"))
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
}