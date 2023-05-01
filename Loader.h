#pragma once
using namespace std;





namespace Big
{
	void Setup();

	void FirstConfig();
	void CurrentConfig();
	void SaveConfig();

	void CreateRIDConfig(string name, const char* id);
	void CreateVehicleFile(std::uint32_t name);
	//VehicleName
	extern std::vector<std::int32_t> _VehicleList;
	extern std::vector<std::int32_t> VehicleName;

	void MakeRIDManager();
	vector<string> RIDNames;

	extern bool LocalFiles;
	extern bool NetworkFiles;
	extern bool WeaponFiles;
	extern bool VehicleFiles;
	extern bool MiscellaneousFiles;
	extern bool WorldFiles;
	extern bool KeyWindow;

	//Open Keys
	extern int i_OpenKey;
	extern int i_Back;
	extern int i_Enter;
	extern int i_Back;
	extern int i_Left;
	extern int i_Right;
	extern int i_Up;
	extern int i_Down;

	extern int o1, o2, o3, o4, o5, o6, o7, o8, o9, o10, o11, o12, o13, o14, o155 = 0;

	extern std::string oName;

	extern bool CreateOutfitWindow;

	void CreateOutfitFile();

	extern std::vector<std::string> RIDList();

	extern std::vector<std::string> VehicleList();

	extern std::vector<std::string> RIDnames;

	extern std::vector<std::string> OutfitList();

	extern std::vector<std::string> outfitNames;

	void JoinRID(std::string name);

	void LoadOutfit(std::string name);

	void LoadPreset(std::string name);

	extern std::vector<std::string> listPresets();

	extern std::vector<std::string> omglolree;

	extern std::string currentKey;
	extern std::string currentKey;

	extern int KeyLevel;
	extern bool IHateMyLife(std::string key);

	extern std::vector<std::int32_t> living_peds_list;
	extern int pedNumber;
	void load_peds(const char* ped_name);
	extern bool add_to_folder;

	extern std::vector<std::string> alivepedlist();
}