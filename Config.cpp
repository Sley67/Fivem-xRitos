#include "Common.hpp"




namespace Big
{
	int i_OpenKey;
	int i_Back;
	int i_Enter;
	int i_Left;
	int i_Right;
	int i_Up;
	int i_Down;

	bool FileExists(const std::string& fileName)
	{
		struct stat buffer;
		return (stat(fileName.c_str(), &buffer) == 0);
	}

	std::string path = "C:\\Viper\\Viper.ytd";

	void Setup()
	{

		std::string mainFolder = "C:\\Viper";

		if (FileExists(mainFolder))
		{
			std::string Headers = "C:\\Viper\\Headers";
			std::string Vehicles = "C:\\Viper\\Vehicles";
			std::string Outfits = "C:\\Viper\\Outfits";
			std::string Configs = "C:\\Viper\\Configs";
			std::string fVehicles = "C:\\Viper\\Favorite Vehicles";
			std::string pdPath = "C:\\Viper\\Configs\\Detection.ini";
			std::string logPoint = "Players";
			std::string logPointt = "Vehicles";
			if (FileExists(pdPath))
			{

			}
			else
			{
				WriteStringToIni("Example", pdPath, logPoint, "Player1");
				WriteStringToIni("Example", pdPath, logPoint, "Player2");
				WriteStringToIni("Example", pdPath, logPoint, "Player3");
				WriteStringToIni("Example", pdPath, logPoint, "Player4");
				WriteStringToIni("Example", pdPath, logPoint, "Player5");

				WriteStringToIni("Example", pdPath, logPointt, "Vehicle1");
				WriteStringToIni("Example", pdPath, logPointt, "Vehicle2");
				WriteStringToIni("Example", pdPath, logPointt, "Vehicle3");
				WriteStringToIni("Example", pdPath, logPointt, "Vehicle4");
				WriteStringToIni("Example", pdPath, logPointt, "Vehicle5");
			}

			if (!FileExists(fVehicles))
			{
				notifyMap(HUD_COLOUR_BLUEDARK, ("Creating Directory: C:\\Viper\\Favorite Vehicles"));
				_mkdir("C:\\Viper\\Favorite Vehicles");
			}

			if (FileExists(Configs))
			{

			}
			else
			{
				notifyMap(HUD_COLOUR_BLUEDARK, ("Creating Directory: C:\\Viper\\Configs"));
				_mkdir("C:\\Viper\\Configs");
			}

			if (FileExists(Headers))
			{

			}
			else
			{
				notifyMap(HUD_COLOUR_BLUEDARK, ("Creating Directory: C:\\Viper\\Headers"));
				_mkdir("C:\\Viper\\Headers");
			}

			if (FileExists(Vehicles))
			{

			}
			else
			{
				_mkdir("C:\\Viper\\Vehicles");
				notifyMap(HUD_COLOUR_BLUEDARK, ("Creating Directory: C:\\Viper\\Vehicles"));
			}

			if (FileExists(Outfits))
			{

			}
			else
			{
				_mkdir("C:\\Viper\\Outfits");
				notifyMap(HUD_COLOUR_BLUEDARK, ("Creating Directory: C:\\Viper\\Outfits"));
			}

		}
		else
		{	
			CreateDirectory("C:\\Viper", NULL);

			std::string Headers = "C:\\Viper\\Headers";
			std::string Vehicles = "C:\\Viper\\Vehicles";
			std::string Outfits = "C:\\Viper\\Outfits";
			std::string Configs = "C:\\Viper\\Configs";
			std::string fVehicles = "C:\\Viper\\Favorite Vehicles";
			std::string pdPath = "C:\\Viper\\Configs\\Detection.ini";
			std::string logPoint = "Players";
			std::string logPointt = "Vehicles";	
			if (FileExists(pdPath))
			{

			}
			else
			{
				WriteStringToIni("Example", pdPath, logPoint, "Player1");
				WriteStringToIni("Example", pdPath, logPoint, "Player2");
				WriteStringToIni("Example", pdPath, logPoint, "Player3");
				WriteStringToIni("Example", pdPath, logPoint, "Player4");
				WriteStringToIni("Example", pdPath, logPoint, "Player5");

				WriteStringToIni("Example", pdPath, logPointt, "Vehicle1");
				WriteStringToIni("Example", pdPath, logPointt, "Vehicle2");
				WriteStringToIni("Example", pdPath, logPointt, "Vehicle3");
				WriteStringToIni("Example", pdPath, logPointt, "Vehicle4");
				WriteStringToIni("Example", pdPath, logPointt, "Vehicle5");
			}

			if (FileExists(fVehicles))
			{

			}
			else
			{
				notifyMap(HUD_COLOUR_BLUEDARK, ("Creating Directory: C:\\Viper\\Favorite Vehicles"));
				_mkdir("C:\\Viper\\Favorite Vehicles");
			}

			if (FileExists(Configs))
			{

			}
			else
			{
				notifyMap(HUD_COLOUR_BLUEDARK, ("Creating Directory: C:\\Viper\\Configs"));
				_mkdir("C:\\Viper\\Configs");
			}

			if (FileExists(Headers))
			{

			}
			else
			{
				notifyMap(HUD_COLOUR_BLUEDARK, ("Creating Directory: C:\\Viper\\Headers"));
				_mkdir("C:\\Viper\\Headers");
			}

			if (FileExists(Vehicles))
			{

			}
			else
			{
				_mkdir("C:\\Viper\\Vehicles");
				notifyMap(HUD_COLOUR_BLUEDARK, ("Creating Directory: C:\\Viper\\Vehicles"));
			}

			if (FileExists(Outfits))
			{

			}
			else
			{
				_mkdir("C:\\Viper\\Outfits");
				notifyMap(HUD_COLOUR_BLUEDARK, ("Creating Directory: C:\\Viper\\Outfits"));
			}

			if (FileExists(pdPath))
			{

			}
			else
			{


				WriteStringToIni("Example", pdPath, logPoint, "Player1");
				WriteStringToIni("Example", pdPath, logPoint, "Player2");
				WriteStringToIni("Example", pdPath, logPoint, "Player3");
				WriteStringToIni("Example", pdPath, logPoint, "Player4");
				WriteStringToIni("Example", pdPath, logPoint, "Player5");

				WriteStringToIni("Example", pdPath, logPointt, "Vehicle1");
				WriteStringToIni("Example", pdPath, logPointt, "Vehicle2");
				WriteStringToIni("Example", pdPath, logPointt, "Vehicle3");
				WriteStringToIni("Example", pdPath, logPointt, "Vehicle4");
				WriteStringToIni("Example", pdPath, logPointt, "Vehicle5");
			}
		}
		std::string pdPath = "C:\\Viper\\Configs\\Detection.ini";
		std::string logPoint = "Players";
		std::string logPointt = "Vehicles";

		if (FileExists(pdPath))
		{

		}
		else
		{


			WriteStringToIni("Example", pdPath, logPoint, "Player1");
			WriteStringToIni("Example", pdPath, logPoint, "Player2");
			WriteStringToIni("Example", pdPath, logPoint, "Player3");
			WriteStringToIni("Example", pdPath, logPoint, "Player4");
			WriteStringToIni("Example", pdPath, logPoint, "Player5");

			WriteStringToIni("Example", pdPath, logPointt, "Vehicle1");
			WriteStringToIni("Example", pdPath, logPointt, "Vehicle2");
			WriteStringToIni("Example", pdPath, logPointt, "Vehicle3");
			WriteStringToIni("Example", pdPath, logPointt, "Vehicle4");
			WriteStringToIni("Example", pdPath, logPointt, "Vehicle5");
		}
	}



	void FirstConfig()
	{
		std::string iniPath = "C:\\Viper\\Configs\\MenuConfig.ini";
		std::string Player = "Player";
		std::string Network = "Network";
		std::string Networkk = "Network/Protections";
		std::string Weapon = "Weapon";
		std::string Vehicle = "Vehicle";	

		WriteStringToIni("Adder", "C:\\Viper\\Favorite Vehicles\\Adder.ini", "Adder", "Adder");
		WriteStringToIni("Adder", "C:\\Viper\\Favorite Vehicles\\You can add more in the Favorite Vehicles Folder.ini", "Adder", "Adder");
		
		/* CONTROLS */
		i_OpenKey = VK_F8;
		i_Back = VK_BACK;
		i_Enter = VK_RETURN;
		i_Up = VK_UP;
		i_Down = VK_DOWN;
		i_Left = VK_LEFT;
		i_Right = VK_RIGHT;

		WriteIntToIni(i_OpenKey, iniPath, "Controls", "Open");
		WriteIntToIni(i_Back, iniPath, "Controls", "Back");
		WriteIntToIni(i_Enter, iniPath, "Controls", "Enter");
		WriteIntToIni(i_Up, iniPath, "Controls", "Up");
		WriteIntToIni(i_Down, iniPath, "Controls", "Down");
		WriteIntToIni(i_Left, iniPath, "Controls", "Left");
		WriteIntToIni(i_Right, iniPath, "Controls", "Right");

		/* PLAYER */
		WriteBoolToIni(false, iniPath, Player, "Invincible");
		WriteBoolToIni(false, iniPath, Player, "Never Wanted");
		WriteBoolToIni(false, iniPath, Player, "No Ragdoll");
		WriteBoolToIni(false, iniPath, Player, "Forcefield");
		WriteBoolToIni(false, iniPath, Player, "Fly");
		WriteBoolToIni(false, iniPath, Player, "Freecam");
		WriteBoolToIni(false, iniPath, Player, "Super Run");
		WriteBoolToIni(false, iniPath, Player, "Super Jump");
		WriteBoolToIni(false, iniPath, Player, "No Clip");

		/* NETWORK */
		WriteBoolToIni(false, iniPath, Network, "Off Radar");
		WriteBoolToIni(false, iniPath, Network, "Anti AFK");
		WriteBoolToIni(false, iniPath, Network, "Bypass Chat Restrictions");
		WriteBoolToIni(false, iniPath, Network, "Bypass World Restrictions");

		WriteBoolToIni(false, iniPath, Network, "Notify");
		WriteBoolToIni(false, iniPath, Network, "Kick");
		WriteBoolToIni(false, iniPath, Network, "Crash");
		WriteBoolToIni(false, iniPath, Network, "Joining");
		WriteBoolToIni(false, iniPath, Network, "Me");
		WriteBoolToIni(false, iniPath, Network, "Friends");

		WriteBoolToIni(false, iniPath, Networkk, "Kick");
		WriteBoolToIni(false, iniPath, Networkk, "Infinite Loading");
		WriteBoolToIni(false, iniPath, Networkk, "Transaction Error");
		WriteBoolToIni(false, iniPath, Networkk, "CEO Kick");
		WriteBoolToIni(false, iniPath, Networkk, "Send To Job");
		WriteBoolToIni(false, iniPath, Networkk, "Passivemode");
		WriteBoolToIni(false, iniPath, Networkk, "Block R* ID Join");

		WriteBoolToIni(false, iniPath, Network, "Enable");

		/* Weapon */
		WriteBoolToIni(false, iniPath, Weapon, "Gravity");
		WriteBoolToIni(false, iniPath, Weapon, "Infinite");
		WriteBoolToIni(false, iniPath, Weapon, "Airstrike");
		WriteBoolToIni(false, iniPath, Weapon, "One shot");
		WriteBoolToIni(false, iniPath, Weapon, "Rope");
		WriteBoolToIni(false, iniPath, Weapon, "Firework");
		WriteBoolToIni(false, iniPath, Weapon, "Force");
		WriteBoolToIni(false, iniPath, Weapon, "Teleport");

		WriteBoolToIni(false, iniPath, Vehicle, "SpawnInVeh");
		WriteBoolToIni(false, iniPath, Vehicle, "RemoveVehicle");
		WriteBoolToIni(false, iniPath, Vehicle, "MaxVeh");

	}


	void CurrentConfig()
	{
		std::string MainPath = "C:\\Viper\\Configs\\MenuConfig.ini";
		std::string Player = "Player";
		std::string Network = "Network";
		std::string Networkk = "Network/Protections";
		std::string Weapon = "Weapon";
		std::string Controls = "Controls";
		std::string Vehicle = "Vehicle";

		/* CONTROLS */
		i_OpenKey = ReadIntFromIni(MainPath, Controls, "Open");
		i_Back = ReadIntFromIni(MainPath, Controls, "Back");
		i_Enter = ReadIntFromIni(MainPath, Controls, "Enter");
		i_Left = ReadIntFromIni(MainPath, Controls, "Left");
		i_Right = ReadIntFromIni(MainPath, Controls, "Right");
		i_Up = ReadIntFromIni(MainPath, Controls, "Up");
		i_Down = ReadIntFromIni(MainPath, Controls, "Down");

		/* PLAYER */
		if (ReadBoolFromIni(MainPath, Player, "Invincible") == true)
		{
			godmodee = true;
		}
		if (ReadBoolFromIni(MainPath, Player, "Never Wanted") == true)
		{
			NeverWanted = true;
		}
		if (ReadBoolFromIni(MainPath, Player, "No Ragdoll") == true)
		{
			NoRagdoll = true;
		}
		if (ReadBoolFromIni(MainPath, Player, "Forcefield") == true)
		{
			ForceField = true;
		}
		if (ReadBoolFromIni(MainPath, Player, "Fly") == true)
		{
			Fly = true;
		}
		if (ReadBoolFromIni(MainPath, Player, "Freecam") == true)
		{
			Freecam = true;
		}
		if (ReadBoolFromIni(MainPath, Player, "Super Run") == true)
		{
			SuperRun = true;
		}
		if (ReadBoolFromIni(MainPath, Player, "Super Jump") == true)
		{
			SuperJump = true;
		}
		if (ReadBoolFromIni(MainPath, Player, "No Clip") == true)
		{
			yesclip = true;
		}

		/* Network */

		if (ReadBoolFromIni(MainPath, Network, "Off Radar") == true)
		{
			otr = true;
		}
		if (ReadBoolFromIni(MainPath, Network, "Anti AFK") == true)
		{
			antiAFK = true;
		}
		if (ReadBoolFromIni(MainPath, Network, "Bypass Chat Restrictions") == true)
		{
			chatBypass = true;
		}
		if (ReadBoolFromIni(MainPath, Network, "Bypass World Restrictions") == true)
		{
			restricted = true;
		}

		if (ReadBoolFromIni(MainPath, Networkk, "Kick") == true)
		{
			antiKick = true;
		}
		if (ReadBoolFromIni(MainPath, Networkk, "Infinite Loading") == true)
		{
			InfiniteLoading = true;
		}
		if (ReadBoolFromIni(MainPath, Networkk, "Transaction Error") == true)
		{
			antitransaction_error = true;
		}
		if (ReadBoolFromIni(MainPath, Networkk, "CEO Kick") == true)
		{
			antiCeoKick = true;
		}
		if (ReadBoolFromIni(MainPath, Networkk, "Send To Job") == true)
		{
			antiSsend_player_to_job = true;
		}
		if (ReadBoolFromIni(MainPath, Networkk, "Passivemode") == true)
		{
			antiPassive = true;
		}
		if (ReadBoolFromIni(MainPath, Networkk, "Block R* ID Join") == true)
		{
			lockLobby = true;
		}

		if (ReadBoolFromIni(MainPath, Network, "Notify") == true)
		{
			notify = true;
		}
		if (ReadBoolFromIni(MainPath, Network, "Kick") == true)
		{
			kick = true;
		}
		if (ReadBoolFromIni(MainPath, Network, "Crash") == true)
		{
			crash = true;
		}
		if (ReadBoolFromIni(MainPath, Network, "Joining") == true)
		{
			joinNotify = true;
		}
		if (ReadBoolFromIni(MainPath, Network, "Me") == true)
		{
			exMe = true;
		}
		if (ReadBoolFromIni(MainPath, Network, "Friends") == true)
		{
			exFriends = true;
		}

		if (ReadBoolFromIni(MainPath, Network, "Enable") == true)
		{
			serverScanner = true;
		}

		/* Weapon */
		if (ReadBoolFromIni(MainPath, Weapon, "Gravity") == true)
		{
			gravityGun = true;
		}
		if (ReadBoolFromIni(MainPath, Weapon, "Infinite") == true)
		{
			InfiniteAmmo = true;
		}
		if (ReadBoolFromIni(MainPath, Weapon, "Airstrike Gun") == true)
		{
			AirstrikeGun = true;
		}
		if (ReadBoolFromIni(MainPath, Weapon, "One Shot") == true)
		{
			Oneshot = true;
		}
		if (ReadBoolFromIni(MainPath, Weapon, "Rope") == true)
		{
			ROPEGUN = true;
		}
		if (ReadBoolFromIni(MainPath, Weapon, "Firework") == true)
		{
			fireworkgun = true;
		}
		if (ReadBoolFromIni(MainPath, Weapon, "Force") == true)
		{
			forcegun = true;
		}
		if (ReadBoolFromIni(MainPath, Weapon, "Teleport") == true)
		{
			tpgun = true;
		}

		/* Vehicle */
		if (ReadBoolFromIni(MainPath, Vehicle, "SpawnInVeh") == true)
		{
			SpawnInVeh = true;
		}
		if (ReadBoolFromIni(MainPath, Vehicle, "RemoveVehicle") == true)
		{
			DeleteVeh = true;
		}
		if (ReadBoolFromIni(MainPath, Vehicle, "MaxVeh") == true)
		{
			MaxVeh = true;
		}
	}
	

	bool LocalFiles;
	bool NetworkFiles;
	bool WeaponFiles;
	bool VehicleFiles;
	bool MiscellaneousFiles;
	bool WorldFiles;

	void SaveConfig()	
	{
		std::string iniPath = "C:\\Viper\\Configs\\MenuConfig.ini";
		std::string Player = "Player";
		std::string Network = "Network";
		std::string Networkk = "Network/Protections";
		std::string Weapon = "Weapon";
		std::string Vehicle = "Vehicle";

		if (LocalFiles == true)
		{
			if (godmodee == true)
			{
				WriteBoolToIni(true, iniPath, Player, "Invincible");
			}
			if (NeverWanted == true)
			{
				WriteBoolToIni(true, iniPath, Player, "Never Wanted");
			}
			if (NoRagdoll == true)
			{
				WriteBoolToIni(true, iniPath, Player, "No Ragdoll");
			}
			if (ForceField == true)
			{
				WriteBoolToIni(true, iniPath, Player, "Forcefield");
			}
			if (Fly == true)
			{
				WriteBoolToIni(true, iniPath, Player, "Fly");
			}
			if (Freecam == true)
			{
				WriteBoolToIni(true, iniPath, Player, "Freecam");
			}
			if (SuperRun == true)
			{
				WriteBoolToIni(true, iniPath, Player, "Super Run");
			}
			if (SuperJump == true)
			{
				WriteBoolToIni(true, iniPath, Player, "Super Jump");
			}
			if (yesclip == true)
			{
				WriteBoolToIni(true, iniPath, Player, "No Clip");
			}
		}
		if (NetworkFiles == true)
		{
			if (otr == true)
			{
				WriteBoolToIni(true, iniPath, Network, "Off Radar");
			}
			if (antiAFK == true)
			{
				WriteBoolToIni(true, iniPath, Network, "Anti AFK");
			}
			if (chatBypass == true)
			{
				WriteBoolToIni(true, iniPath, Network, "Bypass Chat Restrictions");
			}
			if (restricted == true)
			{
				WriteBoolToIni(true, iniPath, Network, "Bypass World Restrictions");
			}

			if (antiKick == true)
			{
				WriteBoolToIni(true, iniPath, Networkk, "Kick");
			}
			if (InfiniteLoading == true)
			{
				WriteBoolToIni(true, iniPath, Networkk, "Infinite Loading");
			}
			if (antitransaction_error == true)
			{
				WriteBoolToIni(true, iniPath, Networkk, "Transaction Error");
			}
			if (antiCeoKick == true)
			{
				WriteBoolToIni(true, iniPath, Networkk, "CEO Kick");
			}
			if (antiSsend_player_to_job == true)
			{
				WriteBoolToIni(true, iniPath, Networkk, "Send To Job");
			}
			if (antiPassive == true)
			{
				WriteBoolToIni(true, iniPath, Networkk, "Passivemode");
			}
			if (lockLobby == true)
			{
				WriteBoolToIni(true, iniPath, Networkk, "Block R* ID Join");
			}

			if (notify == true)
			{
				WriteBoolToIni(true, iniPath, Network, "Notify");	
			}
			if (kick == true)
			{
				WriteBoolToIni(true, iniPath, Network, "Kick");
			}
			if (crash == true)
			{
				WriteBoolToIni(true, iniPath, Network, "Crash");
			}
			if (joinNotify == true)
			{
				WriteBoolToIni(true, iniPath, Network, "Joining");
			}
			if (exMe == true)
			{
				WriteBoolToIni(true, iniPath, Network, "Me");
			}
			if (exFriends == true)
			{
				WriteBoolToIni(true, iniPath, Network, "Friends");
			}

			if (serverScanner == true)
			{
				WriteBoolToIni(true, iniPath, Network, "Enable");
			}
		}
		if (WeaponFiles == true)
		{
			if (gravityGun == true)
			{
				WriteBoolToIni(true, iniPath, Weapon, "Gravity");
			}
			if (InfiniteAmmo == true)
			{
				WriteBoolToIni(true, iniPath, Weapon, "Infinite");
			}
			if (AirstrikeGun == true)
			{
				WriteBoolToIni(true, iniPath, Weapon, "Airstrike Gun");
			}
			if (Oneshot == true)
			{
				WriteBoolToIni(true, iniPath, Weapon, "One Shot");
			}
			if (ROPEGUN == true)
			{
				WriteBoolToIni(true, iniPath, Weapon, "Rope");
			}
			if (fireworkgun == true)
			{
				WriteBoolToIni(true, iniPath, Weapon, "Firework");
			}
			if (forcegun == true)
			{
				WriteBoolToIni(true, iniPath, Weapon, "Force");
			}
			if (tpgun == true)
			{
				WriteBoolToIni(true, iniPath, Weapon, "Teleport");
			}

		}
		if (VehicleFiles == true)
		{
			if (SpawnInVeh)
			{
				WriteBoolToIni(true, iniPath, Vehicle, "SpawnInVeh");
			}
			if (DeleteVeh)
			{
				WriteBoolToIni(true, iniPath, Vehicle, "RemoveVehicle");
			}
			if (MaxVeh)
			{
				WriteBoolToIni(true, iniPath, Vehicle, "MaxVeh");
			}
		}
		if (WorldFiles == true)
		{

		}




	}

	int KeyLevel;

	bool KeyWindow;

	bool IHateMyLife(std::string key)
	{
		std::string iniPath = "C:\\Viper\\Configs\\MenuConfig.ini";
		std::string Controls = "Controls";

		if (KeyLevel == 1)
		{
			if (key == "Insert")
			{
				i_OpenKey = VK_INSERT;
			}
			if (key == "*")
			{
				i_OpenKey = VK_MULTIPLY;
			}
			if (key == "F1")
			{
				i_OpenKey = VK_F1;
			}
			if (key == "F2")
			{
				i_OpenKey = VK_F2;
			}
			if (key == "F3")
			{
				i_OpenKey = VK_F3;
			}
			if (key == "F4")
			{
				i_OpenKey = VK_F4;
			}
			if (key == "F5")
			{
				i_OpenKey = VK_F5;
			}
			if (key == "F6")
			{
				i_OpenKey = VK_F6;
			}
			if (key == "F6")
			{
				i_OpenKey = VK_F6;
			}
			if (key == "F7")
			{
				i_OpenKey = VK_F7;
			}
			if (key == "F8")
			{
				i_OpenKey = VK_F8;
			}
			if (key == "F9")
			{
				i_OpenKey = VK_F9;
			}
			if (key == "F10")
			{
				i_OpenKey = VK_F10;
			}
			if (key == "F11")
			{
				i_OpenKey = VK_F11;
			}
			if (key == "F12")
			{
				i_OpenKey = VK_F12;
			}
			if (key == "9")
			{
				i_OpenKey = VK_NUMPAD9;
			}
			if (key == "8")
			{
				i_OpenKey = VK_NUMPAD8;
			}
			if (key == "7")
			{
				i_OpenKey = VK_NUMPAD7;
			}
			if (key == "6")
			{
				i_OpenKey = VK_NUMPAD6;
			}
			if (key == "5")
			{
				i_OpenKey = VK_NUMPAD5;
			}
			if (key == "4")
			{
				i_OpenKey = VK_NUMPAD4;
			}
			if (key == "3")
			{
				i_OpenKey = VK_NUMPAD3;
			}
			if (key == "2")
			{
				i_OpenKey = VK_NUMPAD2;
			}
			if (key == "1")
			{
				i_OpenKey = VK_NUMPAD1;
			}

			WriteIntToIni(i_OpenKey, iniPath, Controls, "Open");
		}
		if (KeyLevel == 2)
		{
			if (key == "Insert")
			{
				i_Back = VK_INSERT;
			}
			if (key == "*")
			{
				i_Back = VK_MULTIPLY;
			}
			if (key == "F1")
			{
				i_Back = VK_F1;
			}
			if (key == "F2")
			{
				i_Back = VK_F2;
			}
			if (key == "F3")
			{
				i_Back = VK_F3;
			}
			if (key == "F4")
			{
				i_Back = VK_F4;
			}
			if (key == "F5")
			{
				i_Back = VK_F5;
			}
			if (key == "F6")
			{
				i_Back = VK_F6;
			}
			if (key == "F6")
			{
				i_Back = VK_F6;
			}
			if (key == "F7")
			{
				i_Back = VK_F7;
			}
			if (key == "F8")
			{
				i_Back = VK_F8;
			}
			if (key == "F9")
			{
				i_Back = VK_F9;
			}
			if (key == "F10")
			{
				i_Back = VK_F10;
			}
			if (key == "F11")
			{
				i_Back = VK_F11;
			}
			if (key == "F12")
			{
				i_Back = VK_F12;
			}

			if (key == "9")
			{
				i_Back = VK_NUMPAD9;
			}
			if (key == "8")
			{
				i_Back = VK_NUMPAD8;
			}
			if (key == "7")
			{
				i_Back = VK_NUMPAD7;
			}
			if (key == "6")
			{
				i_Back = VK_NUMPAD6;
			}
			if (key == "5")
			{
				i_Back = VK_NUMPAD5;
			}
			if (key == "4")
			{
				i_Back = VK_NUMPAD4;
			}
			if (key == "3")
			{
				i_Back = VK_NUMPAD3;
			}
			if (key == "2")
			{
				i_Back = VK_NUMPAD2;
			}
			if (key == "1")
			{
				i_Back = VK_NUMPAD1;
			}
			if (key == "0")
			{
				i_Back = VK_NUMPAD0;
			}

			WriteIntToIni(i_Back, iniPath, Controls, "Back");
		}
		if (KeyLevel == 3)
		{
			if (key == "Insert")
			{
				i_Enter = VK_INSERT;
			}
			if (key == "*")
			{
				i_Enter = VK_MULTIPLY;
			}
			if (key == "F1")
			{
				i_Enter = VK_F1;
			}
			if (key == "F2")
			{
				i_Enter = VK_F2;
			}
			if (key == "F3")
			{
				i_Enter = VK_F3;
			}
			if (key == "F4")
			{
				i_Enter = VK_F4;
			}
			if (key == "F5")
			{
				i_Enter = VK_F5;
			}
			if (key == "F6")
			{
				i_Enter = VK_F6;
			}
			if (key == "F6")
			{
				i_Enter = VK_F6;
			}
			if (key == "F7")
			{
				i_Enter = VK_F7;
			}
			if (key == "F8")
			{
				i_Enter = VK_F8;
			}
			if (key == "F9")
			{
				i_Enter = VK_F9;
			}
			if (key == "F10")
			{
				i_Enter = VK_F10;
			}
			if (key == "F11")
			{
				i_Enter = VK_F11;
			}
			if (key == "F12")
			{
				i_Enter = VK_F12;
			}

			if (key == "9")
			{
				i_Enter = VK_NUMPAD9;
			}
			if (key == "8")
			{
				i_Enter = VK_NUMPAD8;
			}
			if (key == "7")
			{
				i_Enter = VK_NUMPAD7;
			}
			if (key == "6")
			{
				i_Enter = VK_NUMPAD6;
			}
			if (key == "5")
			{
				i_Enter = VK_NUMPAD5;
			}
			if (key == "4")
			{
				i_Enter = VK_NUMPAD4;
			}
			if (key == "3")
			{
				i_Enter = VK_NUMPAD3;
			}
			if (key == "2")
			{
				i_Enter = VK_NUMPAD2;
			}
			if (key == "1")
			{
				i_Enter = VK_NUMPAD1;
			}

			WriteIntToIni(i_Enter, iniPath, Controls, "Enter");
		}
		if (KeyLevel == 4)
		{
			if (key == "Insert")
			{
				i_Up = VK_INSERT;
			}
			if (key == "*")
			{
				i_Up = VK_MULTIPLY;
			}
			if (key == "F1")
			{
				i_Up = VK_F1;
			}
			if (key == "F2")
			{
				i_Up = VK_F2;
			}
			if (key == "F3")
			{
				i_Up = VK_F3;
			}
			if (key == "F4")
			{
				i_Up = VK_F4;
			}
			if (key == "F5")
			{
				i_Up = VK_F5;
			}
			if (key == "F6")
			{
				i_Up = VK_F6;
			}
			if (key == "F6")
			{
				i_Up = VK_F6;
			}
			if (key == "F7")
			{
				i_Up = VK_F7;
			}
			if (key == "F8")
			{
				i_Up = VK_F8;
			}
			if (key == "F9")
			{
				i_Up = VK_F9;
			}
			if (key == "F10")
			{
				i_Up = VK_F10;
			}
			if (key == "F11")
			{
				i_Up = VK_F11;
			}
			if (key == "F12")
			{
				i_Up = VK_F12;
			}

			if (key == "9")
			{
				i_Up = VK_NUMPAD9;
			}
			if (key == "8")
			{
				i_Up = VK_NUMPAD8;
			}
			if (key == "7")
			{
				i_Up = VK_NUMPAD7;
			}
			if (key == "6")
			{
				i_Up = VK_NUMPAD6;
			}
			if (key == "5")
			{
				i_Up = VK_NUMPAD5;
			}
			if (key == "4")
			{
				i_Up = VK_NUMPAD4;
			}
			if (key == "3")
			{
				i_Up = VK_NUMPAD3;
			}
			if (key == "2")
			{
				i_Up = VK_NUMPAD2;
			}
			if (key == "1")
			{
				i_Up = VK_NUMPAD1;
			}

			WriteIntToIni(i_Up, iniPath, Controls, "Up");
		}
		if (KeyLevel == 5)
		{
			if (key == "Insert")
			{
				i_Down = VK_INSERT;
			}
			if (key == "*")
			{
				i_Down = VK_MULTIPLY;
			}
			if (key == "F1")
			{
				i_Down = VK_F1;
			}
			if (key == "F2")
			{
				i_Down = VK_F2;
			}
			if (key == "F3")
			{
				i_Down = VK_F3;
			}
			if (key == "F4")
			{
				i_Down = VK_F4;
			}
			if (key == "F5")
			{
				i_Down = VK_F5;
			}
			if (key == "F6")
			{
				i_Down = VK_F6;
			}
			if (key == "F6")
			{
				i_Down = VK_F6;
			}
			if (key == "F7")
			{
				i_Down = VK_F7;
			}
			if (key == "F8")
			{
				i_Down = VK_F8;
			}
			if (key == "F9")
			{
				i_Down = VK_F9;
			}
			if (key == "F10")
			{
				i_Down = VK_F10;
			}
			if (key == "F11")
			{
				i_Down = VK_F11;
			}
			if (key == "F12")
			{
				i_Down = VK_F12;
			}

			if (key == "9")
			{
				i_Down = VK_NUMPAD9;
			}
			if (key == "8")
			{
				i_Down = VK_NUMPAD8;
			}
			if (key == "7")
			{
				i_Down = VK_NUMPAD7;
			}
			if (key == "6")
			{
				i_Down = VK_NUMPAD6;
			}
			if (key == "5")
			{
				i_Down = VK_NUMPAD5;
			}
			if (key == "4")
			{
				i_Down = VK_NUMPAD4;
			}
			if (key == "3")
			{
				i_Down = VK_NUMPAD3;
			}
			if (key == "2")
			{
				i_Down = VK_NUMPAD2;
			}
			if (key == "1")
			{
				i_Down = VK_NUMPAD1;
			}

			WriteIntToIni(i_Down, iniPath, Controls, "Down");
		}
		if (KeyLevel == 6)
		{
			if (key == "Insert")
			{
				i_Left = VK_INSERT;
			}
			if (key == "*")
			{
				i_Left = VK_MULTIPLY;
			}
			if (key == "F1")
			{
				i_Left = VK_F1;
			}
			if (key == "F2")
			{
				i_Left = VK_F2;
			}
			if (key == "F3")
			{
				i_Left = VK_F3;
			}
			if (key == "F4")
			{
				i_Left = VK_F4;
			}
			if (key == "F5")
			{
				i_Left = VK_F5;
			}
			if (key == "F6")
			{
				i_Left = VK_F6;
			}
			if (key == "F6")
			{
				i_Left = VK_F6;
			}
			if (key == "F7")
			{
				i_Left = VK_F7;
			}
			if (key == "F8")
			{
				i_Left = VK_F8;
			}
			if (key == "F9")
			{
				i_Left = VK_F9;
			}
			if (key == "F10")
			{
				i_Left = VK_F10;
			}
			if (key == "F11")
			{
				i_Left = VK_F11;
			}
			if (key == "F12")
			{
				i_Left = VK_F12;
			}

			if (key == "9")
			{
				i_Left = VK_NUMPAD9;
			}
			if (key == "8")
			{
				i_Left = VK_NUMPAD8;
			}
			if (key == "7")
			{
				i_Left = VK_NUMPAD7;
			}
			if (key == "6")
			{
				i_Left = VK_NUMPAD6;
			}
			if (key == "5")
			{
				i_Left = VK_NUMPAD5;
			}
			if (key == "4")
			{
				i_Left = VK_NUMPAD4;
			}
			if (key == "3")
			{
				i_Left = VK_NUMPAD3;
			}
			if (key == "2")
			{
				i_Left = VK_NUMPAD2;
			}
			if (key == "1")
			{
				i_Left = VK_NUMPAD1;
			}

			WriteIntToIni(i_Left, iniPath, Controls, "Left");
		}
		if (KeyLevel == 7)
		{
			if (key == "Insert")
			{
				i_Right = VK_INSERT;
			}
			if (key == "*")
			{
				i_Right = VK_MULTIPLY;
			}
			if (key == "F1")
			{
				i_Right = VK_F1;
			}
			if (key == "F2")
			{
				i_Right = VK_F2;
			}
			if (key == "F3")
			{
				i_Right = VK_F3;
			}
			if (key == "F4")
			{
				i_Right = VK_F4;
			}
			if (key == "F5")
			{
				i_Right = VK_F5;
			}
			if (key == "F6")
			{
				i_Right = VK_F6;
			}
			if (key == "F6")
			{
				i_Right = VK_F6;
			}
			if (key == "F7")
			{
				i_Right = VK_F7;
			}
			if (key == "F8")
			{
				i_Right = VK_F8;
			}
			if (key == "F9")
			{
				i_Right = VK_F9;
			}
			if (key == "F10")
			{
				i_Right = VK_F10;
			}
			if (key == "F11")
			{
				i_Right = VK_F11;
			}
			if (key == "F12")
			{
				i_Right = VK_F12;
			}

			if (key == "9")
			{
				i_Right = VK_NUMPAD9;
			}
			if (key == "8")
			{
				i_Right = VK_NUMPAD8;
			}
			if (key == "7")
			{
				i_Right = VK_NUMPAD7;
			}
			if (key == "6")
			{
				i_Right = VK_NUMPAD6;
			}
			if (key == "5")
			{
				i_Right = VK_NUMPAD5;
			}
			if (key == "4")
			{
				i_Right = VK_NUMPAD4;
			}
			if (key == "3")
			{
				i_Right = VK_NUMPAD3;
			}
			if (key == "2")
			{
				i_Right = VK_NUMPAD2;
			}
			if (key == "1")
			{
				i_Right = VK_NUMPAD1;
			}

			WriteIntToIni(i_Right, iniPath, Controls, "Right");
		}

		return true;
	}
}


