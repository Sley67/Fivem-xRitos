#include "MainScript.hpp"
#include "ScriptCallback.hpp"
#include "Lists.hpp"
#include "Natives.hpp"
#include "Timer.hpp"
#include "Translation.hpp"
#include "CustomText.hpp"
#include "UI/UIManager.hpp"
#include "UI/BoolOption.hpp"
#include "UI/ChooseOption.hpp"
#include "UI/NumberOption.hpp"
#include "UI/RegularOption.hpp"
#include "UI/SubOption.hpp"
#include "UI/RegularSubmenu.hpp"
#include "UI/PlayerSubmenu.hpp"
#include "Enum.h"
#include "Basic.h"

using namespace Big;
using namespace Nano;

#define Vector3 NativeVector3
float degToRad(float degs)
{
	return degs * 3.141592653589793f / 180.f;
}

void SpawnVeh(const char* spawn)
{
	Hash model = MISC::GET_HASH_KEY(spawn);
	STREAMING::REQUEST_MODEL(model);
	Vector3 ourCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
	float forward = 5.f;
	float heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
	float xVector = forward * sin(degToRad(heading)) * -1.f;
	float yVector = forward * cos(degToRad(heading));

	if (DeleteVeh)
	{
		Vehicle car = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		VEHICLE::DELETE_VEHICLE(&car);
	}



	if (STREAMING::IS_MODEL_VALID(model))
	{
		if (STREAMING::HAS_MODEL_LOADED(model))
		{
			Vehicle veh = VEHICLE::CREATE_VEHICLE(model, ourCoords.x + xVector, ourCoords.y + yVector, ourCoords.z, heading, true, true, 1);

			_VehicleList.insert(_VehicleList.end(), veh);

			vehicleNumber++;

			const char* Vehiclename = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(ENTITY::GET_ENTITY_MODEL(veh));

			string vehicle = Vehiclename;

			const char* name = "C:\\Viper\\Manager\\VehicleManager\\";	
			
			string namepp = name + (string)Vehiclename + std::to_string(vehicleNumber);

			char* vehicleppname = StringToChar(namepp);

			_mkdir(vehicleppname);

			PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
			VEHICLE::SET_VEHICLE_ENGINE_ON(veh, true, true, true);
			VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh, 1);
			DECORATOR::DECOR_SET_INT(veh, "MPBitset", 0);
			VEHICLE::SET_VEHICLE_IS_STOLEN(veh, false);

			if (SpawnInVeh)
			{
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
				ENTITY::SET_ENTITY_HEADING(veh, ENTITY::GET_ENTITY_HEADING(veh));
			}
			if (MaxVeh) {

				VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
				for (int i = 0; i < 50; i++)
				{
					VEHICLE::SET_VEHICLE_MOD(veh, i, VEHICLE::GET_NUM_VEHICLE_MODS(veh, i) - 1, false);
				}
			}
		}
	}
}

void SpawnVeh_PLAYER(const char* spawn)
{
	Hash model = MISC::GET_HASH_KEY(spawn);
	STREAMING::REQUEST_MODEL(model);
	Vector3 ourCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(g_SelectedPlayer), false);
	float forward = 5.f;
	float heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
	float xVector = forward * sin(degToRad(heading)) * -1.f;
	float yVector = forward * cos(degToRad(heading));
	if (STREAMING::IS_MODEL_VALID(model))
	{
		Vehicle veh = VEHICLE::CREATE_VEHICLE(model, ourCoords.x + xVector, ourCoords.y + yVector, ourCoords.z, heading, true, true, 1);
		PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
		VEHICLE::SET_VEHICLE_ENGINE_ON(veh, true, true, true);
		VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh, 1);
		DECORATOR::DECOR_SET_INT(veh, "MPBitset", 0);
		VEHICLE::SET_VEHICLE_IS_STOLEN(veh, false);
	}

}

bool forplayer = false;

const char* spawnvehicleOption = "";
void SpawnOption(const char* spawn)
{
	if (!forplayer)
		SpawnVeh(spawn);
	else
		SpawnVeh_PLAYER(spawn);
}
void Superr()
{

	

	SpawnOption("adder");
	SpawnOption("autarch");
	SpawnOption("banshee2");
	SpawnOption("bullet");
	SpawnOption("cheetah");
	SpawnOption("deluxo");
	SpawnOption("entityxf");
	SpawnOption("fmj");
	SpawnOption("infernus");
	SpawnOption("nero");
	SpawnOption("nero2");
	SpawnOption("osiris");
	SpawnOption("le7b");
	SpawnOption("italigtb");
	SpawnOption("italigtb2");
	SpawnOption("pfister811");
	//SpawnOption("protoipo");
	SpawnOption("reaper");
	SpawnOption("sultanrs");
	SpawnOption("t20");
	SpawnOption("tempesta");
	SpawnOption("turismor");
	SpawnOption("tyrus");
	SpawnOption("tezeract");
	SpawnOption("entity2");
	SpawnOption("vacca");
	SpawnOption("voltic");
	SpawnOption("zentorno");
	SpawnOption("visione");
	SpawnOption("vigilante");
	SpawnOption("voltic2");
	SpawnOption("penetrator");
	SpawnOption("gp1");



}




void sportspinSpawner()
{

	SpawnOption("alpha");
	SpawnOption("banshee");
	SpawnOption("flashgt");
	SpawnOption("bestiagts");
	SpawnOption("blista2");
	SpawnOption("blista3");
	SpawnOption("italigto");
	SpawnOption("schlagen");
	SpawnOption("buffalo");
	SpawnOption("buffalo2");
	SpawnOption("buffalo3");
	SpawnOption("swinger");
	SpawnOption("comet4");
	SpawnOption("comet5");
	SpawnOption("carbonizzare");
	SpawnOption("comet2");
	SpawnOption("coquette");
	SpawnOption("cyclone");
	SpawnOption("elegy");
	SpawnOption("elegy2");
	SpawnOption("feltzer2");
	SpawnOption("furoregt");
	SpawnOption("fusilade");
	SpawnOption("futo");
	SpawnOption("jester");
	SpawnOption("jester2");
	SpawnOption("dominator3");
	SpawnOption("khamelion");
	SpawnOption("kuruma");
	SpawnOption("kuruma2");
	SpawnOption("zr380");
	SpawnOption("zr3803");
	SpawnOption("lynx");
	SpawnOption("massacro");
	SpawnOption("massacro2");
	SpawnOption("pariah");
	SpawnOption("raiden");
	SpawnOption("ninef");
	SpawnOption("ninef2");
	SpawnOption("omnis");
	SpawnOption("penumbra");
	SpawnOption("rapidgt");
	SpawnOption("tyrant");
	SpawnOption("hotring");
	SpawnOption("ellie");
	SpawnOption("rapidgt2");
	SpawnOption("raptor");
	SpawnOption("schafter3");
	SpawnOption("schafter4");
	SpawnOption("taipan");
	SpawnOption("schwarzer");
	SpawnOption("jester3");
	SpawnOption("seven70");
	SpawnOption("sultan");
	SpawnOption("surano");
	SpawnOption("specter");
	SpawnOption("specter2");
	SpawnOption("scramjet");
	SpawnOption("tampa2");
	SpawnOption("tropos");
	SpawnOption("verlierer2");
	SpawnOption("ruiner2");
	SpawnOption("phantom2");
	SpawnOption("ruston");




}
void sportclassicsspinSpawner()
{

	SpawnOption("btype");
	SpawnOption("btype3");
	SpawnOption("casco");
	SpawnOption("coquette2");
	SpawnOption("tulip");
	SpawnOption("vamos");
	SpawnOption("feltzer3");
	SpawnOption("jb700");
	SpawnOption("gt500");
	SpawnOption("neon");
	SpawnOption("hermes");
	SpawnOption("hustler");
	SpawnOption("mamba");
	SpawnOption("manana");
	SpawnOption("monroe");
	SpawnOption("peyote");
	SpawnOption("pigalle");
	SpawnOption("stinger");
	SpawnOption("viseris");
	SpawnOption("z190");
	SpawnOption("stingergt");
	SpawnOption("tornado");
	SpawnOption("revolter");
	SpawnOption("impaler");
	SpawnOption("impaler2");
	SpawnOption("impaler3");
	SpawnOption("impaler4");
	SpawnOption("tornado2");
	SpawnOption("tornado3");
	SpawnOption("tornado4");
	SpawnOption("tornado5");
	SpawnOption("tornado6");
	SpawnOption("deviant");
	SpawnOption("imperator");
	SpawnOption("imperator2");
	SpawnOption("imperator3");
	SpawnOption("ztype");
	SpawnOption("infernus2");
	SpawnOption("turismo2");
	SpawnOption("clique");
}
void SUVspinSpawner()//done
{

	SpawnOption("baller");
	SpawnOption("baller2");
	SpawnOption("baller3");
	SpawnOption("baller5");
	SpawnOption("baller4");
	SpawnOption("toros");
	SpawnOption("baller6");
	SpawnOption("bjxl");
	SpawnOption("cavalcade");
	SpawnOption("cavalcade2");
	SpawnOption("contender");
	SpawnOption("dubsta");
	SpawnOption("dubsta2");
	SpawnOption("streiter");
	SpawnOption("fq2");
	SpawnOption("granger");
	SpawnOption("gresley");
	SpawnOption("riata");
	SpawnOption("habanero");
	SpawnOption("huntley");
	SpawnOption("landstalker");
	SpawnOption("mesa");
	SpawnOption("mesa2");
	SpawnOption("patriot");
	SpawnOption("radi");
	SpawnOption("rocoto");
	SpawnOption("seminole");
	SpawnOption("serrano");
	SpawnOption("xls");
	SpawnOption("xls2");

}
void TrailerspinSpawner()
{

	SpawnOption("armytanker");
	SpawnOption("armytrailer");
	SpawnOption("terbyte");
	SpawnOption("pounder2");
	SpawnOption("armytrailer2");
	SpawnOption("baletrailer");
	SpawnOption("boattrailer");
	SpawnOption("docktrailer");
	SpawnOption("freighttrailer");
	SpawnOption("graintrailer");
	SpawnOption("proailer");
	SpawnOption("raketrailer");
	SpawnOption("tanker");
	SpawnOption("tanker2");
	SpawnOption("tr2");
	SpawnOption("tr3");
	SpawnOption("tr4");
	SpawnOption("pbus2");
	SpawnOption("mule4");
	SpawnOption("trailerlogs");
	SpawnOption("trailers");
	SpawnOption("trailers2");
	SpawnOption("trailers3");
	SpawnOption("trailersmall");
	SpawnOption("trflat");
	SpawnOption("tvtrailer");

}
void TranspinSpawner()
{

	SpawnOption("cablecar");
	SpawnOption("freight");
	SpawnOption("freightcar");
	SpawnOption("freightcont1");
	SpawnOption("freightcont2");
	SpawnOption("freightgrain");
	SpawnOption("metrotrain");
	SpawnOption("tankercar");
}
void UtilityspinSpawner()
{

	SpawnOption("airtug");
	SpawnOption("caddy");
	SpawnOption("caddy2");
	SpawnOption("docktug");
	SpawnOption("forklift");
	SpawnOption("mower");
	SpawnOption("ripley");
	SpawnOption("sadler");
	SpawnOption("sadler2");
	SpawnOption("scrap");
	SpawnOption("towtruck");
	SpawnOption("towtruck2");
	SpawnOption("kamacho");
	SpawnOption("tractor");
	SpawnOption("tractor2");
	SpawnOption("tractor3");
	SpawnOption("yosemite");
	SpawnOption("utillitruck");
	SpawnOption("utillitruck2");
	SpawnOption("utillitruck3");
	SpawnOption("bison");
	SpawnOption("bison2");
	SpawnOption("bison3");
	SpawnOption("bobcatxl");
	SpawnOption("boxville");
	SpawnOption("boxville2");
	SpawnOption("boxville3");
	SpawnOption("boxville4");
	SpawnOption("burrito");
	SpawnOption("burrito2");
	SpawnOption("burrito3");
	SpawnOption("burrito4");
	SpawnOption("burrito5");
	SpawnOption("gburrito");
	SpawnOption("gburrito2");
	SpawnOption("camper");
	SpawnOption("speedo");
	SpawnOption("journey");
	SpawnOption("minivan");
	SpawnOption("minivan2");
	SpawnOption("paradise");
	SpawnOption("pony");
	SpawnOption("pony2");
	SpawnOption("rumpo");
	SpawnOption("rumpo2");
	SpawnOption("rumpo3");
	SpawnOption("speedo");
	SpawnOption("speedo2");
	SpawnOption("surfer");
	SpawnOption("surfer2");
	SpawnOption("taco");
	SpawnOption("youga");
	SpawnOption("youga2");

}
void BoatspinSpawner()
{

	SpawnOption("dinghy");
	SpawnOption("dinghy2");
	SpawnOption("dinghy3");
	SpawnOption("dinghy4");
	SpawnOption("jetmax");
	SpawnOption("marquis");
	SpawnOption("predator");
	SpawnOption("seashark");
	SpawnOption("seashark2");
	SpawnOption("seashark3");
	SpawnOption("speeder");
	SpawnOption("speeder2");
	SpawnOption("squalo");
	SpawnOption("submersible");
	SpawnOption("submersible2");
	SpawnOption("suntrap");
	SpawnOption("toro");
	SpawnOption("toro2");
	SpawnOption("tropic");
	SpawnOption("tropic2");
	SpawnOption("tug");

}

void CommercialspinSpawner()
{

	SpawnOption("benson");
	SpawnOption("biff");
	SpawnOption("hauler");
	SpawnOption("mule");
	SpawnOption("packer");
	SpawnOption("phantom");
	SpawnOption("pounder");
	SpawnOption("stockade");
	SpawnOption("stockade3");


}
void CompactsspinSpawner()
{

	SpawnOption("rcbandito");
	SpawnOption("blista");
	SpawnOption("brioso");
	SpawnOption("slamvan4");
	SpawnOption("slamvan5");
	SpawnOption("slamvan6");
	SpawnOption("issi3");
	SpawnOption("issi4");
	SpawnOption("issi5");
	SpawnOption("issi6");
	SpawnOption("dilettante");
	SpawnOption("dilettante2");
	SpawnOption("freecrawler");
	SpawnOption("issi2");
	SpawnOption("panto");
	SpawnOption("prairie");
	SpawnOption("gb200");
	SpawnOption("michelli");
	SpawnOption("rhapsody");
	SpawnOption("sentinel3");
	SpawnOption("retinue");

}
void CoupesspinSpawner()
{

	SpawnOption("cogcabrio");
	SpawnOption("exemplar");
	SpawnOption("f620");
	SpawnOption("felon");
	SpawnOption("felon2");
	SpawnOption("jackal");
	SpawnOption("oracle");
	SpawnOption("oracle2");
	SpawnOption("sentinel");
	SpawnOption("sentinel2");
	SpawnOption("windsor");
	SpawnOption("windsor2");
	SpawnOption("savestra");
	SpawnOption("zion");
	SpawnOption("zion2");

}
void CyclesspinSpawner()
{

	SpawnOption("bmx");
	SpawnOption("cruiser");
	SpawnOption("scorcher");
	SpawnOption("fixter");
	SpawnOption("tribike3");
	SpawnOption("tribike");
	SpawnOption("tribike2");

}
void EmergencyspinSpawner()
{

	SpawnOption("ambulance");
	SpawnOption("fbi");
	SpawnOption("fbi2");
	SpawnOption("firetruk");
	SpawnOption("lguard");
	SpawnOption("pbus");
	SpawnOption("pranger");
	SpawnOption("police");
	SpawnOption("police2");
	SpawnOption("police3");
	SpawnOption("police4");
	SpawnOption("policeb");
	SpawnOption("policeold1");
	SpawnOption("policeold2");
	SpawnOption("policet");
	SpawnOption("sheriff");
	SpawnOption("sheriff2");
	SpawnOption("riot");
	SpawnOption("riot2");

}
void HelicoptersspinSpawner()
{

	SpawnOption("akula");
	SpawnOption("annihilator");
	SpawnOption("blimp");
	SpawnOption("blimp2");
	SpawnOption("blimp3");
	SpawnOption("buzzard");
	SpawnOption("buzzard2");
	SpawnOption("cargobob");
	SpawnOption("cargobob2");
	SpawnOption("cargobob3");
	SpawnOption("cargobob4");
	SpawnOption("frogger");
	SpawnOption("frogger2");
	SpawnOption("maverick");
	SpawnOption("havok");
	SpawnOption("hunter");
	SpawnOption("polmav");
	SpawnOption("savage");
	SpawnOption("skylift");
	SpawnOption("supervolito");
	SpawnOption("supervolito2");
	SpawnOption("swift");
	SpawnOption("swift2");
	SpawnOption("seasparrow");
	SpawnOption("valkyrie");
	SpawnOption("valkyrie2");
	SpawnOption("volatus");

}
void IndustrialspinSpawner()
{

	SpawnOption("bulldozer");
	SpawnOption("cutter");
	SpawnOption("dump");
	SpawnOption("mixer");
	SpawnOption("mixer2");
	SpawnOption("flatbed");
	SpawnOption("guardian");
	SpawnOption("handler");
	SpawnOption("rubble");
	SpawnOption("tiptruck");
	SpawnOption("tiptruck2");
	SpawnOption("cerberus1");
	SpawnOption("cerberus2");
	SpawnOption("cerberus3");
}
void MilitaryspinSpawner()
{

	SpawnOption("barracks");
	SpawnOption("barracks2");
	SpawnOption("barracks3");
	SpawnOption("caracara");
	SpawnOption("barrage");
	SpawnOption("oppressor2");
	SpawnOption("oppressor");
	SpawnOption("thruster");
	SpawnOption("crusader");
	SpawnOption("rhino");
	SpawnOption("menacer");
	SpawnOption("khanjali");
	SpawnOption("scarab");
	SpawnOption("scarab2");
	SpawnOption("scarab3");
	SpawnOption("riot2");



}
void MotorcyclespinSpawner()
{

	SpawnOption("avarus");
	SpawnOption("bagger");
	SpawnOption("bati");
	SpawnOption("bati2");
	SpawnOption("deathbike");
	SpawnOption("deathbike2");
	SpawnOption("deathbike3");
	SpawnOption("bf400");
	SpawnOption("carbonrs");
	SpawnOption("chimera");
	SpawnOption("daemon");
	SpawnOption("daemon2");
	SpawnOption("defiler");
	SpawnOption("double");
	SpawnOption("enduro");
	SpawnOption("esskey");
	SpawnOption("faggio");
	SpawnOption("faggio2");
	SpawnOption("faggio3");
	SpawnOption("gargoyle");
	SpawnOption("hakuchou");
	SpawnOption("hakuchou2");
	SpawnOption("hexer");
	SpawnOption("innovation");
	SpawnOption("lectro");
	SpawnOption("manchez");
	SpawnOption("nemesis");
	SpawnOption("nightblade");
	SpawnOption("pcj");
	SpawnOption("ratbike");
	SpawnOption("sanchez");
	SpawnOption("sanchez2");
	SpawnOption("sanctus");
	SpawnOption("shotaro");
	SpawnOption("sovereign");
	SpawnOption("thrust");
	SpawnOption("vader");
	SpawnOption("vindicator");
	SpawnOption("vortex");
	SpawnOption("wolfsbane");
	SpawnOption("zombiea");
	SpawnOption("zombieb");
	SpawnOption("diablous");
	SpawnOption("diablous2");
	SpawnOption("fcr");
	SpawnOption("fcr2");

}
void MusclespinSpawner()
{

	SpawnOption("blade");
	SpawnOption("buccaneer");
	SpawnOption("buccaneer2");
	SpawnOption("chino");
	SpawnOption("chino2");
	SpawnOption("dominator4");
	SpawnOption("dominator5");
	SpawnOption("dominator6");
	SpawnOption("coquette3");
	SpawnOption("dominator");
	SpawnOption("dominator2");
	SpawnOption("dukes");
	SpawnOption("dukes2");
	SpawnOption("gauntlet");
	SpawnOption("gauntlet2");
	SpawnOption("faction");
	SpawnOption("faction2");
	SpawnOption("faction3");
	SpawnOption("hotknife");
	SpawnOption("lurcher");
	SpawnOption("moonbeam");
	SpawnOption("moonbeam2");
	SpawnOption("nightshade");
	SpawnOption("phoenix");
	SpawnOption("picador");
	SpawnOption("ratloader");
	SpawnOption("rapidgt3");
	SpawnOption("ratloader2");
	SpawnOption("ruiner");
	SpawnOption("ruiner2");
	SpawnOption("ruiner3");
	SpawnOption("sabregt");
	SpawnOption("sabregt2");
	SpawnOption("slamvan");
	SpawnOption("slamvan2");
	SpawnOption("slamvan3");
	SpawnOption("stalion");
	SpawnOption("stalion2");
	SpawnOption("tampa");
	SpawnOption("vigero");
	SpawnOption("virgo");
	SpawnOption("virgo2");
	SpawnOption("virgo3");
	SpawnOption("voodoo");
	SpawnOption("voodoo2");


}
void OffRoadspinSpawner()
{

	SpawnOption("bruiser");
	SpawnOption("bruiser2");
	SpawnOption("bruiser3");
	SpawnOption("brutus");
	SpawnOption("brutus2");
	SpawnOption("brutus3");
	SpawnOption("bfinjection");
	SpawnOption("bifta");
	SpawnOption("blazer");
	SpawnOption("blazer2");
	SpawnOption("blazer3");
	SpawnOption("blazer4");
	SpawnOption("bodhi2");
	SpawnOption("brawler");
	SpawnOption("dloader");
	SpawnOption("dubsta3");
	SpawnOption("dune");
	SpawnOption("dune2");
	SpawnOption("insurgent");
	SpawnOption("insurgent2");
	SpawnOption("kalahari");
	SpawnOption("marshall");
	SpawnOption("mesa3");
	SpawnOption("monster");
	SpawnOption("monster3");
	SpawnOption("monster4");
	SpawnOption("monster5");
	SpawnOption("rancherxl");
	SpawnOption("rancherxl2");
	SpawnOption("rebel");
	SpawnOption("rebel2");
	SpawnOption("sandking");
	SpawnOption("sandking2");
	SpawnOption("technical");
	SpawnOption("trophytruck");
	SpawnOption("trophytruck2");
	SpawnOption("technical2");
	SpawnOption("dune4");
	SpawnOption("dune5");
	SpawnOption("blazer5");


}
void PlanesspinSpawner()
{

	SpawnOption("alphaz1");
	SpawnOption("avenger");
	SpawnOption("besra");
	SpawnOption("bombushka");
	SpawnOption("cargoplane");
	SpawnOption("cuban800");
	SpawnOption("dodo");
	SpawnOption("duster");
	SpawnOption("hydra");
	SpawnOption("jet");
	SpawnOption("lazer");
	SpawnOption("luxor");
	SpawnOption("luxor2");
	SpawnOption("seabreeze");
	SpawnOption("tula");
	SpawnOption("mammatus");
	SpawnOption("miljet");
	SpawnOption("nimbus");
	SpawnOption("rogue");
	SpawnOption("starling");
	SpawnOption("pyro");
	SpawnOption("mogul");
	SpawnOption("microlight");
	SpawnOption("molotok");
	SpawnOption("nokota");
	SpawnOption("howard");
	SpawnOption("shamal");
	SpawnOption("strikeforce");
	SpawnOption("stunt");
	SpawnOption("titan");
	SpawnOption("velum");
	SpawnOption("velum2");
	SpawnOption("vestra");
	SpawnOption("volatol");
	SpawnOption("fcr2");


}
void SedansspinSpawner()
{

	SpawnOption("asea");
	SpawnOption("asea2");
	SpawnOption("asterope");
	SpawnOption("cog55");
	SpawnOption("cog552");
	SpawnOption("cognoscenti");
	SpawnOption("cognoscenti2");
	SpawnOption("emperor");
	SpawnOption("emperor2");
	SpawnOption("emperor3");
	SpawnOption("fugitive");
	SpawnOption("glendale");
	SpawnOption("ingot");
	SpawnOption("intruder");
	SpawnOption("limo2");
	//add other limos"");
	SpawnOption("premier");
	SpawnOption("primo");
	SpawnOption("primo2");
	SpawnOption("regina");
	SpawnOption("romero");
	SpawnOption("schafter2");
	SpawnOption("schafter5");
	SpawnOption("schafter6");
	SpawnOption("stanier");
	SpawnOption("stratum");
	SpawnOption("stretch");
	SpawnOption("superd");
	SpawnOption("surge");
	SpawnOption("tailgater");
	SpawnOption("warrener");
	SpawnOption("washington");



}
void ServicespinSpawner()
{

	SpawnOption("airbus");
	SpawnOption("brickade");
	SpawnOption("bus");
	SpawnOption("coach");
	SpawnOption("rallytruck");
	SpawnOption("rentalbus");
	SpawnOption("taxi");
	SpawnOption("patriot2");
	SpawnOption("tourbus");
	SpawnOption("trash2");
	SpawnOption("wastelander");
}

