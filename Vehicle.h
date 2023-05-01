#pragma once

namespace Big
{
	std::vector<std::string> fVehicleList();

	extern bool SpawnInVeh;

	extern bool DeleteVeh;

	extern bool MaxVeh;

	extern bool VehFly;

	extern bool flyCollision_veh;

	extern bool vehicleInvincible;

	extern bool autoFlip;

	extern bool autoFix;
	
	extern bool Hornboost;

	extern bool Seatbelt;

	extern bool vehInvisible;

	extern bool Rainbow;

	extern bool reducegrip;

	extern bool nolimit;

	extern bool ib;

	void RGBFade();

	void VehicleUpdateLoop();
}