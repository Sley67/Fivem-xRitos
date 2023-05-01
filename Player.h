#pragma once

namespace Big
{
	extern bool God;
	extern bool Invisible;
	extern bool NoRagdoll;
	extern bool NoClip;
	extern bool NeverWanted;
	extern bool Fly;
	extern bool Freecam;
	extern bool superRun;
	extern bool SuperJump;
	extern bool ForceField;
	extern bool otr;
	extern bool ToggledOn;
	extern bool walkingnoclip;
	extern bool _Spectate;


	extern float fastboi;
	extern float fastboi2;

	extern bool f7;
	extern bool f5;
	extern bool f4;

	void PlayerLoop();
	void LoadPlayerInfo(int player);

	std::string PlayerName(int Player);

	//World stuff
	extern bool mobile_radio;
	void WorldWeather(char* HASH);
	void WorldSpeed(float speed);
	void World_Clear();
}