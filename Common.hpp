#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT _WIN32_WINNT_WIN7
#include <winsdkver.h>
#include <sdkddkver.h>
#include <windows.h>
#include <winternl.h>
#include <d3d11.h>

/*  AUTH   */

/*
#include "Networking/atlrx.h"
#include "Networking/RegExp.h"
#include "Networking/sha512.hh"
#include "Networking/StringProcess.h"
#include "Networking/Web2.0.h"
#include "Networking/WinHttpClient.h"
*/

#include <cassert>
#include <cinttypes>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <direct.h>
#include <algorithm>
#include <atomic>
#include <chrono>
#include <deque>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <mutex>
#include <optional>
#include <sstream>
#include <stack>
#include <string>
#include <thread>
#include <type_traits>
#include <unordered_map>
#include <vector>
#include <map>
#include <intrin.h>
#include <time.h>
#include <timeapi.h>
#include "Enum.h"
#include "Loader.h"
#include "Headermanager.h"
#include "UI/UIManager.hpp"
#include <thread>
# pragma comment(lib, "secur32.lib")
# pragma comment(lib, "winmm.lib")
# pragma comment(lib, "dmoguids.lib")
# pragma comment(lib, "wmcodecdspuuid.lib")
# pragma comment(lib, "msdmo.lib")
# pragma comment(lib, "Strmiids.lib")




#include "network stuff.h"
#define BIGBASE_WIDE_IMPL(str) L ## str
#define BIGBASE_WIDE(str) BIGBASE_WIDE_IMPL(str)

#define BIGBASE_STRINGIZE_IMPL(x) #x
#define BIGBASE_STRINGIZE(x) BIGBASE_STRINGIZE_IMPL(x)

#define BIGBASE_NAME "Viper"

namespace Big
{
	using namespace std::chrono_literals;
	namespace fs = std::filesystem;

	inline HMODULE g_Module{};
	inline std::atomic_bool g_Running = true;

	inline std::uint32_t g_SelectedPlayer{};

	inline bool g_LogScriptEvents = false;
}
#include "thxhydronite.h"
#include "Settings.hpp"
#include "Logger.hpp"
#include "Util.hpp"
#include "Memory.hpp"
#include "Game.hpp"
#include "ScriptGlobal.hpp"
#include "MemoryEdit.h"
#include "Headermanager.h"
#include "Basic.h"
#include "Natives.hpp"
#include "Player.h"
#include "ScriptCallback.hpp"
#include "Stats.h"
#include "TIck.h"
#include "Vehicle.h"
#include "Interpolation.h"
#include "Network.h"
#include "Weapons.h"
#include "Auth.h"

/*OFFSETS*/
//offset from WORLD
#define OFFSET_PLAYER					0x08			//playerbase
#define OFFSET_NET_PLAYER				0x1C8

//entity offsets
#define OFFSET_ENTITY_POSBASE			0x30			//base of a structure that contains entity coords
#define	OFFSET_ENTITY_POSBASE_COS		0x20
#define	OFFSET_ENTITY_POSBASE_SIN		0x30
#define OFFSET_ENTITY_POSBASE_POS		0x50			//vector3
#define OFFSET_ENTITY_POS				0x90			//vector3
#define OFFSET_ENTITY_GOD				0x189			//godmode; on = 1, off = 0; byte
#define OFFSET_ENTITY_HEALTH			0x280			//entity health (except for vehicles); float cur, float max
#define OFFSET_ENTITY_HEALTH_MAX		0x2A0			//they moved this away from curHealth in 1.36 :(
#define OFFSET_ENTITY_ATTACKER			0x2A8			//base to a list of the last 3 entities that attacked the current entity

//player (entity) offsets
#define OFFSET_PLAYER_VEHICLE					0xD28			//ptr to last used vehicle
#define OFFSET_NET_PLAYER_INFO					0xA8
#define OFFSET_PLAYER_INFO						0x10C8			//playerInfo struct
#define OFFSET_PLAYER_INFO_NAME					0x84
#define OFFSET_PLAYER_INFO_SWIM_SPD				0x150			//swim speed; def 1; float
#define	OFFSET_PLAYER_INFO_RUN_SPD				0xCD0			//run speed; def 1; float
#define OFFSET_PLAYER_INFO_FRAMEFLAGS			0x1F9			//frame flags; DWORD
#define OFFSET_PLAYER_INFO_WANTED_CAN_CHANGE	0x71C			//fWantedCanChange
#define OFFSET_PLAYER_INFO_NPC_IGNORE			0x850			//npc ignore; DWORD; everyone = 0x450000;
#define OFFSET_PLAYER_INFO_WANTED				0x868			//wanted level; DWORD
#define OFFSET_PLAYER_INFO_STAMINA				0xCD4			//fStamina, fStaminaMax
#define OFFSET_PLAYER_RAGDOLL					0x10B8			//byte; CPed.noRagdoll: 0x20 = off; 0x00/0x01 = on
#define OFFSET_PLAYER_SEATBELT					0xC00			//byte; CPed.seatBelt: 0xC8 = off; 0xC9 = on
#define OFFSET_PLAYER_INVEHICLE					0x1477
#define OFFSET_PLAYER_ARMOR						0x14E0			//armour
#define OFFSET_PLAYER_WATER_PROOF				0x188			//water proof; DWORD; +0x1000000 = on
#define OFFSET_PLAYER_VEHICLE_DAMAGE_MP			0xCFC			//super punck/kick;float;

//vehicle offsets
#define OFFSET_VEHICLE_HEALTH						0x908			//vehicle health; 0.f-1000.f
#define	OFFSET_VEHICLE_HEALTH2						0x844			//vehicle health2; 0.f-1000.f
#define OFFSET_VEHICLE_HANDLING						0x938
#define OFFSET_VEHICLE_HANDLING_MASS				0xC				//fMass
#define OFFSET_VEHICLE_HANDLING_BUOYANCY			0x40			//fBuoyancy
#define OFFSET_VEHICLE_HANDLING_ACCELERATION		0x4C
#define OFFSET_VEHICLE_HANDLING_UPSHIFT				0x58
#define OFFSET_VEHICLE_HANDLING_DOWNSHIFT			0x5C
#define OFFSET_VEHICLE_HANDLING_BRAKEFORCE			0x6C
#define OFFSET_VEHICLE_HANDLING_HANDBRAKEFORCE		0x7C			//fHandbrakeForce
#define OFFSET_VEHICLE_HANDLING_TRACTION_CURVE_MIN	0x90			//fTractionCurveMin
#define OFFSET_VEHICLE_HANDLING_SUSPENSION_FORCE	0xBC			//fSuspensionForce
#define OFFSET_VEHICLE_HANDLING_SUSPENSION_HEIGH	0xD0			//fSuspensionHeight
#define OFFSET_VEHICLE_HANDLING_COLISION_DAMAGE_MP	0xF0			//fColisionDamageMult
#define OFFSET_VEHICLE_HANDLING_WEAPON_DAMAGE_MP	0xF4			//fWeaponDamageMult
#define OFFSET_VEHICLE_HANDLING_DEFORM_MULTIPLIER	0xF8			//fDeformationDamageMult
#define OFFSET_VEHICLE_HANDLING_ENGINE_DAMAGE_MP	0xFC			//fEngineDamageMult
#define OFFSET_VEHICLE_BULLETPROOF_TIRES			0x943			//btBulletproofTires; (btBulletproofTires & 0x20) ? true : false
#define OFFSET_VEHICLE_GRAVITY						0xC5C			//fGravity
#define OFFSET_VEHICLE_BOOST						0x320			//fBoost
#define OFFSET_VEHICLE_RECHARGE_SPEED				0x324			//fRocketRechargeSpeed
#define OFFSET_VEHICLE_MISSLES						0x1280			//btVehicleMissles
#define OFFSET_VEHICLE_BOMBS						0x1294			//btAircraftBombs
#define OFFSET_VEHICLE_COUNTERMEASURES				0x1298			//btAircraftCountermeasures
#define OFFSET_VEHICLE_MK2_MISSLES					0x1284			//btOppressorMK2Misseles
#define OFFSET_VEHICLE_TAMPA_MISSLES				0x127C			//btTampaMissles
#define	OFFSET_VEHICLE_CUSTOM						0x48
#define	OFFSET_VEHICLE_CUSTOM_EMS					0x3D6			//btEngineManagementSystem; 0x3 = max
#define	OFFSET_VEHICLE_CUSTOM_BRAKES				0x3D7			//btBrakes; 0x6 = max
#define	OFFSET_VEHICLE_CUSTOM_TRANSMISSION			0x3D8			//btTransmission; 0x8 = max
#define	OFFSET_VEHICLE_CUSTOM_SUSPENSION			0x3DA			//btSuspension; 0x1B = max
#define	OFFSET_VEHICLE_CUSTOM_ARMOR					0x3DB			//btArmor; 0x1B = max
#define	OFFSET_VEHICLE_CUSTOM_TURBO_TUNING			0x3DD			//btTurboTuning; 0x1 = on
#define	OFFSET_VEHICLE_CUSTOM_NEON_LIGHT_R			0x3A2			//btNeonLightRed
#define	OFFSET_VEHICLE_CUSTOM_NEON_LIGHT_G			0x3A1			//btNeonLightGreen
#define	OFFSET_VEHICLE_CUSTOM_NEON_LIGHT_B			0x3A0			//btNeonLightBlue
#define	OFFSET_VEHICLE_CUSTOM_NEON_LIGHTS_L			0x402			//btNeonLightLeft; 0x0 = off; 0x1 = on
#define	OFFSET_VEHICLE_CUSTOM_NEON_LIGHTS_R			0x403			//btNeonLightRight; 0x0 = off; 0x1 = on
#define	OFFSET_VEHICLE_CUSTOM_NEON_LIGHTS_F			0x404			//btNeonLightFront; 0x0 = off; 0x1 = on
#define	OFFSET_VEHICLE_CUSTOM_NEON_LIGHTS_B			0x405			//btNeonLightBack; 0x0 = off; 0x1 = on
#define	OFFSET_VEHICLE_CUSTOM_TYRE_SMOKE			0x3DF			//btTyreSmoke; 0x1 = on
#define	OFFSET_VEHICLE_CUSTOM_TYRE_SMOKE_R			0x3FC			//btTyreSmokeRed
#define	OFFSET_VEHICLE_CUSTOM_TYRE_SMOKE_G			0x3FD			//btTyreSmokeGreen
#define	OFFSET_VEHICLE_CUSTOM_TYRE_SMOKE_B			0x3FE			//btTyreSmokeBlue
#define	OFFSET_VEHICLE_CUSTOM_LIMO_WINDOWS			0x3FF			//btLimoWindows; 0x1 = on

//weapon offsets
#define OFFSET_WEAPON_MANAGER			0x10D8			//from playerbase
#define OFFSET_WEAPON_CURRENT			0x20			//from weapon manager
#define OFFSET_WEAPON_AMMOINFO			0x60			//from weaponbase
#define OFFSET_WEAPON_AMMOINFO_MAX		0x28			//ammoinfo
#define OFFSET_WEAPON_AMMOINFO_CUR_1	0x08			//ptr lvl 1, ptr 1
#define OFFSET_WEAPON_AMMOINFO_CUR_2	0x00			//ptr tr lvl 2, ptr 1
#define OFFSET_WEAPON_AMMOINFO_CURAMMO	0x18			//offset to cur ammo
#define OFFSET_WEAPON_AMMOINFO_TYPE		0x0C			//offset to projectile type?
#define OFFSET_WEAPON_SPREAD			0x7C			//float set to 0
#define OFFSET_WEAPON_BULLET_DMG		0xBC			//float times 10 (so when 0, it will stay 0)
#define OFFSET_WEAPON_RELOAD_MULTIPLIER	0x134			//float times 10
#define OFFSET_WEAPON_RECOIL			0x2F4			//float set to 0
#define OFFSET_WEAPON_MODEL_HASH		0x14
#define OFFSET_WEAPON_NAME_HASH			0x10
#define OFFSET_WEAPON_RELOAD_VEHICLE	0x130
#define OFFSET_WEAPON_RANGE				0x28C
#define OFFSET_WEAPON_SPINUP			0x144
#define OFFSET_WEAPON_SPIN				0x148
#define OFFSET_WEAPON_BULLET_BATCH		0x124			//dwBulletInBatch
#define OFFSET_WEAPON_MUZZLE_VELOCITY	0x11C			//fMuzzleVelocity
#define OFFSET_WEAPON_IMPACT_TYPE		0x20			//dwImpactType; 1: Fists,3; Bullets,5: Explosives
#define OFFSET_WEAPON_IMPACT_EXPLOSION	0x24			//dwImpactExplosion
#define OFFSET_WEAPON_PENETRATION		0x110			//fPenetration
#define OFFSET_WEAPON_FORCE_ON_PED		0xDC			//fForceOnPed
#define OFFSET_WEAPON_FORCE_ON_VEHICLE	0xE0			//fForceOnVehicle(Bullet Mass)
#define OFFSET_WEAPON_FORCE_ON_HELI		0xE4			//fForceOnHeli


//tunable offsets
#define OFFSET_TUNABLE_RP_MULTIPLIER			0x10
#define OFFSET_TUNABLE_AP_MULTIPLIER			0x30F80
#define OFFSET_TUNABLE_MIN_MISSION_PAYOUT		0x4BC8			//fMinMissionPayout
#define OFFSET_TUNABLE_ANTI_IDLE_KICK1			0x2C0			//AFK;DWORD;2000000000 = Anti idle kick
#define OFFSET_TUNABLE_ANTI_IDLE_KICK2			0x2C8
#define OFFSET_TUNABLE_ANTI_IDLE_KICK3			0x2D0
#define OFFSET_TUNABLE_ANTI_IDLE_KICK4			0x2D8
#define OFFSET_TUNABLE_ORBITAL_CANNON_COOLDOWN	0x2C188			//OrbitalCannonCooldown;DWORD
#define OFFSET_TUNABLE_BUNKER_RESEARCH			0x29BB8			//UnlockAllBunkerResearch;DWORD


#define OFFSET_ATTACKER_DISTANCE		0x18			//changed to 0x18, from 0x10

//replay interface offsets
#define OFFSET_REPLAY_PED_INTERFACE			0x18
#define OFFSET_REPLAY_PICKUP_INTERFACE		0x20
#define OFFSET_INTERFACE_LIST				0x100
#define OFFSET_INTERFACE_CUR_NUMS			0x110
#define OFFSET_REPLAY_PICKUP_HASH			0x488

//unk model
#define OFFSET_MODEL_HASH		0x2640

//globals
#define GLOBAL_TUNEABLES		262145
#define GLOBAL_VEHICLE_HASH		2460715
#define GLOBAL_MERRYWEATHER		2537071
#define GLOBAL_BLOCK_SCRIPT_EVENTS	1391799
#define GLOBAL_BUSINESS			1590535

//feature indexing
#define FEATURE_P_GOD				0x00
#define FEATURE_P_NEVERWANTED		0x01
#define FEATURE_P_ANTINPC			0x02
#define FEATURE_V_GOD				0x03
#define FEATURE_W_SPREAD			0x04
#define FEATURE_W_RECOIL			0x05
#define FEATURE_W_RELOAD			0x06
#define FEATURE_W_DAMAGE			0x07
#define FEATURE_W_AMMO				0x08
#define FEATURE_W_RANGE				0x09
#define FEATURE_W_SPINUP			0x0A
#define FEATURE_P_RUNSPD			0x0B
#define FEATURE_P_SWIMSPD			0x0C
#define FEATURE_P_TRUEGOD			0x0D
#define FEATURE_P_SUPERJUMP			0x0E
#define FEATURE_P_EXPLOSIVEMELEE	0x0F
#define FEATURE_W_EXPLOSIVEAMMO		0x10
#define FEATURE_W_FIREAMMO			0x11
#define FEATURE_V_TRUEGOD			0x12
#define FEATURE_P_NORAGDOLL			0x13
#define FEATURE_V_SEATBELT			0x14
#define FEATURE_W_NORELOAD			0x15
#define FEATURE_V_ACCELERATION		0x16
#define FEATURE_V_BRAKEFORCE		0x17
#define FEATURE_V_TRACTION			0x18
#define FEATURE_V_GRAVITY			0x19
#define FEATURE_V_BULLETPROOFTIRES	0x1A
#define FEATURE_P_WANTED			0x1B
#define FEATURE_W_BULLET_BATCH		0x1C
#define FEATURE_W_MUZZLE_VELOCITY	0x1D
#define FEATURE_V_DEFORMATION		0x1E
#define FEATURE_V_UPSHIFT			0x1F
#define FEATURE_V_SUSPENSION_FORCE	0x21
#define FEATURE_P_STAMINA			0x22
#define FEATURE_V_DOWNSHIFT			0x24
#define FEATURE_P_SUICIDE			0x25
#define FEATURE_W_FILL_AMMO			0x26
#define FEATURE_P_WATER_PROOF		0x27
#define FEATURE_P_HEAL				0x28
#define FEATURE_P_UNDEAD_OFFRADAR	0x29
#define FEATURE_P_SUPER_PUNCH		0x2A
#define FEATURE_V_MASS				0x2B
#define FEATURE_V_BUOYANCY			0x2C
#define FEATURE_V_HANDBRAKEFORCE	0x2D
#define FEATURE_V_SUSPENSION_HEIGH	0x2E
#define FEATURE_V_COLISION_DAMAGE_MP 0x2F
#define FEATURE_V_WEAPON_DAMAGE_MP	0x30
#define FEATURE_V_ENGINE_DAMAGE_MP	0x31
#define FEATURE_V_BOOST				0x32
#define FEATURE_V_RECHARGE_SPEED	0x33
#define FEATURE_V_HEAL				0x34
#define FEATURE_T_RP_MP				0x35
#define FEATURE_T_AP_MP				0x36
#define FEATURE_T_MISSION_PAYOUT	0x37
#define FEATURE_W_FILL_ALL_AMMO		0x38
#define FEATURE_W_FORCE_ON_PED		0x39
#define FEATURE_W_FORCE_ON_VEHICLE	0x3A
#define FEATURE_W_FORCE_ON_HELI		0x3B
#define FEATURE_W_BULLET_EDIT		0x3C
#define FEATURE_P_NPC_IGNORE		0x3D
#define FEATURE_T_ORBITAL_CANNON	0x3E
#define FEATURE_T_BUNKER_RESEARCH	0x3F
#define FEATURE_T_ANTI_IDLE_KICK	0x40
#define FEATURE_P_PLAYER_LIST		0x41
#define FEATURE_P_MONERY_DROP		0x42
#define FEATURE_G_CASINO_CUT_0		0x43
#define FEATURE_G_CASINO_CUT_1		0x44
#define FEATURE_G_CASINO_CUT_2		0x45
#define FEATURE_G_CASINO_CUT_3		0x46
#define FEATURE_G_DISABLE_THE_PHONE	0x47








#define VK_NOTHING	0x00				/*NULL*/
#define VK_KEY_0	0x30                //('0')	0
#define VK_KEY_1	0x31                //('1')	1
#define VK_KEY_2	0x32                //('2')	2
#define VK_KEY_3	0x33                //('3')	3
#define VK_KEY_4	0x34                //('4')	4
#define VK_KEY_5	0x35                //('5')	5
#define VK_KEY_6	0x36                //('6')	6
#define VK_KEY_7	0x37                //('7')	7
#define VK_KEY_8	0x38                //('8')	8
#define VK_KEY_9	0x39                //('9')	9
#define VK_KEY_A	0x41                //('A')	A
#define VK_KEY_B	0x42                //('B')	B
#define VK_KEY_C	0x43                //('C')	C
#define VK_KEY_D	0x44                //('D')	D
#define VK_KEY_E	0x45                //('E')	E
#define VK_KEY_F	0x46                //('F')	F
#define VK_KEY_G	0x47                //('G')	G
#define VK_KEY_H	0x48                //('H')	H
#define VK_KEY_I	0x49                //('I')	I
#define VK_KEY_J	0x4A                //('J')	J
#define VK_KEY_K	0x4B                //('K')	K
#define VK_KEY_L	0x4C                //('L')	L
#define VK_KEY_M	0x4D                //('M')	M
#define VK_KEY_N	0x4E                //('N')	N
#define VK_KEY_O	0x4F                //('O')	O
#define VK_KEY_P	0x50                //('P')	P
#define VK_KEY_Q	0x51                //('Q')	Q
#define VK_KEY_R	0x52                //('R')	R
#define VK_KEY_S	0x53                //('S')	S
#define VK_KEY_T	0x54                //('T')	T
#define VK_KEY_U	0x55                //('U')	U
#define VK_KEY_V	0x56                //('V')	V
#define VK_KEY_W	0x57                //('W')	W
#define VK_KEY_X	0x58                //('X')	X
#define VK_KEY_Y	0x59                //('Y')	Y
#define VK_KEY_Z	0x5A                //('Z')	Z


extern bool forplayer;

extern float degToRad(float degs);