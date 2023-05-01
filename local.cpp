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

using namespace Big;
using namespace Nano;




bool godmodee = false;
bool superman = false;
bool neverwanted = false;
bool Shortplayer = false;
bool SuperRun = false;

bool playerinv = false;
bool ragdollno = true;
bool yesclip = false;
bool keeeppp = true;
bool coll_ = true;
int wantedlevel;

void Self_Local_Loop()
{
	Player player = PLAYER::PLAYER_PED_ID();

	
	if (neverwanted)
	{
		PLAYER::SET_MAX_WANTED_LEVEL(6);
		PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), 0, 0);
		PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), 0);
		wantedlevel = 0;
	}
	


	if (yesclip)
	{
		static auto noClipSpeed = 1.5f;
		auto ped = PLAYER::PLAYER_PED_ID();
		auto startDist = std::distance(&CAM::GET_GAMEPLAY_CAM_COORD(), &ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true));

		auto pos = ENTITY::GET_ENTITY_COORDS(ped, false);
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ped, pos.x, pos.y, pos.z, false, false, false);

		if (GetAsyncKeyState(VK_KEY_S) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 268))
		{
			if (IsKeyPressed(VK_LSHIFT) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 21))
				startDist -= 3.0;
			if (IsKeyPressed(VK_SPACE) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 22))
				startDist += .5;

			startDist -= noClipSpeed;
			startDist -= .3f;
			NativeVector3 coords = add(&ENTITY::GET_ENTITY_COORDS(ped, 1), &multiply(&rot_to_direction(&CAM::GET_GAMEPLAY_CAM_ROT(0)), startDist));

			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ped, coords.x, coords.y, coords.z, false, false, false);
		}
		if (GetAsyncKeyState(VK_KEY_W) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 269))
		{
			if (IsKeyPressed(VK_LSHIFT) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 21))
				startDist += 3.0;
			if (IsKeyPressed(VK_SPACE) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 22))
				startDist -= .5;

			startDist += noClipSpeed;
			startDist += 1.f;
			NativeVector3 coords = add(&ENTITY::GET_ENTITY_COORDS(ped, 1), &multiply(&rot_to_direction(&CAM::GET_GAMEPLAY_CAM_ROT(0)), startDist));

			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ped, coords.x, coords.y, coords.z, false, false, false);
		}
	}

	PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(PLAYER::PLAYER_PED_ID(), !ragdollno);	
	PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), !ragdollno);
	ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), !playerinv, 0);
	PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 223, Shortplayer);


	
}




