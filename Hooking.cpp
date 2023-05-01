#include "Hooking.hpp"
#include "Game.hpp"
#include "ScriptManager.hpp"
#include "CustomText.hpp"
#include "Util.hpp"
#include "D3DRenderer.hpp"
#include "UI/UIManager.hpp"
#include <MinHook/MinHook.h>
#include "Common.hpp"

#ifdef BIGBASE_DEBUG
#  pragma comment(lib, "MinHook-Debug.lib")
#else
#  pragma comment(lib, "MinHook-Release.lib")
#endif

HANDLE mainFiber;
DWORD wakeAt;

void WAIT(DWORD ms)
{
	wakeAt = timeGetTime() + ms;
	SwitchToFiber(mainFiber);
}

void somethinggggg()
{
	if (mainFiber == nullptr)
		mainFiber = ConvertThreadToFiber(nullptr);

	if (timeGetTime() < wakeAt)
		return;
}

bool m_RemoveWeapons;
bool m_Give_Weapons;
bool m_SoundEvent;
bool m_WantedLevel;
bool m_Explosions;
bool m_Weather;
bool m_Clock;
bool m_Fire;
bool m_ClearPedTasks;
bool m_PTFX;
bool m_RequestPickup;
bool m_ReportMyself;
bool m_ReportCashSpawn;
bool m_RequestControl;

namespace Big
{
	namespace
	{
		std::uint32_t g_HookFrameCount{};
	}

	bool Hooks::IsDlcPresent(std::uint32_t hash)
	{
		if (g_Running && g_HookFrameCount != *g_GameVariables->m_FrameCount)
		{
			g_HookFrameCount = *g_GameVariables->m_FrameCount;
			g_ScriptManager->OnGameTick();
		}
		return static_cast<decltype(&IsDlcPresent)>(g_Hooking->m_OriginalIsDlcPresent)(hash);
	}

	const char* Hooks::GetLabelText(void* unk, const char* label)
	{
		if (g_Running)
			if (auto text = g_CustomText->GetText(Joaat(label)))
				return text;

		return static_cast<decltype(&GetLabelText)>(g_Hooking->m_OriginalGetLabelText)(unk, label);
	}

	void* GED_Nullpointer = nullptr;
	std::vector<int> kicks = {
	
 
	};
	std::vector<int> vehicle_kick =
	{		
		-1089379066, -130330100
	};
	std::vector<int> infinite_loading_screen = { -1253256204 };
	std::vector<int> transaction_error = { -881249731 }; //updated, thx paragon :))))) )) )) )) ))
	std::vector<int> ceo_kick = { -1775205375, -1028825138 };
	std::vector<int> send_player_to_job = { 1764541627 };
	std::vector<int> remote_teleport = { 1337731455, -1253256204 };
	std::vector<int> block_passive = { 1421531240 };
		
	std::vector<const char*> attackers = {};


	BOOL addProtection(std::vector<std::vector<int>> events, char* name, bool shouldAddToModderListOnDetect, std::int64_t* args, std::function<void()> onDetect = []() {})
	{
		Player player = args[1];
		const char* sender = PLAYER::GET_PLAYER_NAME(player);
		if (strcmp(sender, "**Invalid**") == 0 || strcmp(sender, PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())) == 0) return true;
		if (std::count(attackers.begin(), attackers.end(), sender))
		{
			return false;
		}	
		for (std::vector<int> event : events)
		{
			if (std::count(event.begin(), event.end(), args[0]))
			{
				IconNotification(&("Status: Blocked\nSender: " + (std::string)sender + (std::string)"" + std::to_string(args[0]))[0], (char*)"Viper Protections", (char*)name);
				(!std::count(attackers.begin(), attackers.end(), sender)) && shouldAddToModderListOnDetect ? IconNotification(&("Blocking all scrpt events from: " + (std::string)sender + (std::string)" until game restart.")[0], (char*)"Viper Protections", (char*)"") : IconNotification(&("Continuing to allow all scrpt events from: " + (std::string)sender + (std::string)" until game restart." + std::to_string(args[0]))[0], (char*)"Viper Protections", (char*)"");
				onDetect();
				if (shouldAddToModderListOnDetect) attackers.push_back(sender);
				return false;	
			}
		}
		return true;
	}	

	BOOL addnotify(std::vector<std::vector<int>> events, char* name, bool shouldAddToModderListOnDetect, std::int64_t* args, std::function<void()> onDetect = []() {})
	{
		Player player = args[1];
		const char* sender = PLAYER::GET_PLAYER_NAME(player);
		const char* ID = "ID: ";
		for (std::vector<int> event : events)
		{
			if (std::count(event.begin(), event.end(), args[0]))
			{
				IconNotification(&("Status: Blocked\nSender: " + (std::string)sender + (std::string)"\n" + ID + std::to_string(args[0]))[0], (char*)"Viper Protections", (char*)name);
			}
		}
		return true;
	}

	bool Hooks::GetEventData(std::int32_t eventGroup, std::int32_t eventIndex, std::int64_t* args, std::uint32_t argCount)
	{
		auto result = static_cast<decltype(&GetEventData)>(g_Hooking->m_OriginalGetEventData)(eventGroup, eventIndex, args, argCount);
		if (result)
		{
			if (!addnotify({ block_passive }, (char*)"Block Passive Mode", true, args)) return false;
			if (!addnotify({ kicks }, (char*)"Kick From Session", true, args)) return false;
			if (!addnotify({ infinite_loading_screen }, (char*)"Infinite Loading Screen", true, args)) return false;
			if (!addnotify({ ceo_kick }, (char*)"CEO Dismiss", true, args)) return false;
			if (!addnotify({ send_player_to_job }, (char*)"Send To Job", true, args)) return false;
			if (!addnotify({ remote_teleport }, (char*)"Remote Teleport", true, args)) return false;
			if (!addProtection({ kicks }, (char*)"Kick From Session", true, args)) return false;
			if (!addProtection({ infinite_loading_screen }, (char*)"Infinite Loading Screen", true, args, [&]() {IconNotification((char*)"Note: This can sometimes be a false flag for Remote Teleport.", (char*)"Viper Protections", (char*)""); })) return false;
			if (!addProtection({ transaction_error }, (char*)"Transaction Error", true, args)) return false;
			if (!addProtection({ ceo_kick }, (char*)"CEO Dismiss", true, args)) return false;
			if (!addProtection({ send_player_to_job }, (char*)"Send To Job", true, args)) return false;
			if (!addProtection({ remote_teleport }, (char*)"Remote Teleport", true, args)) return false;
			if (!addProtection({ block_passive }, (char*)"Block Passive Mode", true, args)) return false;		}
		return true;
	}	

	void Hooks::NetworkManager(__int64 a1, __int64 a2, __int64 a3, unsigned __int16 a4, int a5, int a6, __int64 a7, __int64 a8)
	{
		auto ptr = Memory::pattern("66 83 FA ? 73 13 0F B7 C2 4C 89 84 C1 ? ? ? ? 4C 89 8C C1").count(1).get(0).get<char>(0);
		auto num_events = *(std::uint8_t*)(ptr + 3);
		auto name_offset = *(std::int32_t*)(ptr + 21);
		auto eventName = reinterpret_cast<char*>(*reinterpret_cast<__int64*>(a1 + 8 * a4 + name_offset));

		BYTE SenderId = *reinterpret_cast<BYTE*>(a2 + 33);
		BYTE ReceiverId = *reinterpret_cast<BYTE*>(a3 + 33);

		const char* SourcePlayer = PLAYER::GET_PLAYER_NAME(SenderId);
		const char* DestinationPlayer = PLAYER::GET_PLAYER_NAME(ReceiverId);

		if (m_RemoveWeapons) {
			if (a4 == 14) {
				IconNotification("Weapon Crash", SourcePlayer, "Protections");
				return;
			}
		}
		if (m_Give_Weapons) {
			if (a4 == 12) {
				IconNotification("Weapon Crash", SourcePlayer, "Protections");
				return;
			}
		}
		if (m_SoundEvent) {
			if (DestinationPlayer == PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())) {
				if (a4 == 51) {
					IconNotification("Sound", SourcePlayer, "Protections");
					return;
				}
			}
		}
		if (m_WantedLevel) {
			if (a4 == 22) {
				IconNotification("Wanted", SourcePlayer, "Protections");
				return;
			}
		}
		if (m_Explosions) {
			if (a4 == 17) {
				IconNotification("Explosions", SourcePlayer, "Protections");
				return;
			}
		}
		if (m_Weather) {
			if (a4 == 10) {
				IconNotification("Weather", SourcePlayer, "Protections");
				return;
			}
		}
		if (m_Clock) {
			if (a4 == 9) {
				IconNotification("Time", SourcePlayer, "Protections");
				return;
			}
		}
		if (m_Fire) {
			if (a4 == 16) {
				IconNotification("Fire", SourcePlayer, "Protections");
				return;
			}
		}
		if (m_ClearPedTasks) {
			if (a4 == 43) {
				IconNotification("Freeze", SourcePlayer, "Protections");
				return;
			}
		}
		if (m_PTFX) {
			if (a4 == 75) {
				IconNotification("Effects", SourcePlayer, "Protections");
				return;
			}
		}
		if (m_ReportMyself) {
			if (a4 == 83) {
				IconNotification("Report Myself", SourcePlayer, "Protections");
				return;
			}
		}
		if (m_ReportCashSpawn) {
			if (a4 == 84) {
				IconNotification("Cash Spawn", SourcePlayer, "Protections");
				return;
			}
		}
		if (m_RequestControl) {
			if (a4 == 4) {
				IconNotification("Request Control", SourcePlayer, "Protections");
				return;
			}
		}


		return static_cast<decltype(&NetworkManager)>(g_Hooking->m_OriginalNetworkManager)(a1, a2, a3, a4, a5, a6, a7, a8);
	}

	/*BOOL addProtection(std::vector<std::vector<int>> events, char* name, bool shouldAddToModderListOnDetect, std::int64_t* args, std::function<void()> onDetect = []() {})
	{
		Player player = args[1];
		const char* sender = PLAYER::GET_PLAYER_NAME(player);
		if (strcmp(sender, "**Invalid**") == 0 || strcmp(sender, PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())) == 0) return true;
		if (std::count(attackers.begin(), attackers.end(), sender))
		{
			return false;
		}	
		
		IconNotification(&("Status: Blocked\nSender: " + (std::string)sender + (std::string)"" + std::to_string(args[0]))[0], (char*)"Viper Protections", (char*)name);

		for (std::vector<int> event : events)
		{
			if (std::count(event.begin(), event.end(), args[0]))
			{
				IconNotification(&("Status: Blocked\nSender: " + (std::string)sender + (std::string)"" + std::to_string(args[0]))[0], (char*)"Viper Protections", (char*)name);
				(!std::count(attackers.begin(), attackers.end(), sender)) && shouldAddToModderListOnDetect ? IconNotification(&("Blocking all scrpt events from: " + (std::string)sender + (std::string)" until game restart.")[0], (char*)"Viper Protections", (char*)"") : IconNotification(&("Continuing to allow all scrpt events from: " + (std::string)sender + (std::string)" until game restart." + std::to_string(args[0]))[0], (char*)"Viper Protections", (char*)"");
				onDetect();
				if (shouldAddToModderListOnDetect) attackers.push_back(sender);
				return false;

			}
		}
		return true;
	}	

	bool Hooks::GetEventData(std::int32_t eventGroup, std::int32_t eventIndex, std::int64_t* args, std::uint32_t argCount)
	{
		auto result = static_cast<decltype(&GetEventData)>(g_Hooking->m_OriginalGetEventData)(eventGroup, eventIndex, args, argCount);
		if (result)
		{
			if (!addProtection({ kicks }, (char*)"Kick From Session", true, args)) return false;
			if (!addProtection({ infinite_loading_screen }, (char*)"Infinite Loading Screen", true, args, [&]() {IconNotification((char*)"Note: This can sometimes be a false flag for Remote Teleport.", (char*)"Viper Protections", (char*)""); })) return false;
			if (!addProtection({ transaction_error }, (char*)"Transaction Error", true, args)) return false;
			if (!addProtection({ ceo_kick }, (char*)"CEO Dismiss", true, args)) return false;
			if (!addProtection({ send_player_to_job }, (char*)"Send To Job", true, args)) return false;
			if (!addProtection({ remote_teleport }, (char*)"Remote Teleport", true, args)) return false;
			if (!addProtection({ block_passive }, (char*)"Block Passive Mode", true, args)) return false;
		}
		return true;
	}

	int Hooks::TriggerScriptEvent(bool unk0, uint64_t* args, int argCount, int bitFlags)
	{
		return static_cast<decltype(&TriggerScriptEvent)>(g_Hooking->m_OriginalTriggerScriptEvent)(unk0, args, argCount, bitFlags);
	}

	bool Hooks::EventManager(void* events, CNetGamePlayers* sourcePlayer, CNetGamePlayers* targetPlayer)
	{
		if (targetPlayer == g_GameFunctions->m_GetPlayerNetworkId(PLAYER::PLAYER_ID()))
		{
			auto args = (std::int64_t*)(((std::uintptr_t)events) + 0x70);
			auto argCount = *(std::uint32_t*)(((std::uintptr_t)events) + 0x224) / sizeof(std::int64_t);
			switch (args[0])
			{
			
			
			}
		}
		return static_cast<decltype(&EventManager)>(g_Hooking->m_OriginalEventManager)(events, sourcePlayer, targetPlayer);
	}*/	
	

	void Hooks::joinDetect(class CGameScriptHandlerMgr* _this, CNetGamePlayer* player)
	{
		if (g_Running)
		{
			/*
			std::string oo = player->GetName();
			std::string ooo = " is joining";
			std::string ultraUWUWUW = oo + ooo;

			auto reee = StringToChar(ultraUWUWUW);

			IconNotification((char*)reee, (char*)"Viper Protections", (char*)"Player Detection");
			*/
		}
	}

	
	

	LRESULT Hooks::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		g_D3DRenderer->WndProc(hWnd, msg, wParam, lParam);
		return static_cast<decltype(&WndProc)>(g_Hooking->m_OriginalWndProc)(hWnd, msg, wParam, lParam);
	}

	HRESULT Hooks::Present(IDXGISwapChain* dis, UINT syncInterval, UINT flags)
	{
		if (g_Running)
		{
			g_D3DRenderer->BeginFrame();
			g_ScriptManager->OnD3DTick();
			g_D3DRenderer->EndFrame();
		}

		return g_Hooking->m_D3DHook.GetOriginal<decltype(&Present)>(PresentIndex)(dis, syncInterval, flags);
	}

	HRESULT Hooks::ResizeBuffers(IDXGISwapChain* dis, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags)
	{
		if (g_Running)
		{
			g_D3DRenderer->PreResize();
			auto hr = g_Hooking->m_D3DHook.GetOriginal<decltype(&ResizeBuffers)>(ResizeBuffersIndex)(dis, bufferCount, width, height, newFormat, swapChainFlags);
			if (SUCCEEDED(hr))
			{
				g_D3DRenderer->PostResize();
			}

			return hr;
		}

		return g_Hooking->m_D3DHook.GetOriginal<decltype(&ResizeBuffers)>(ResizeBuffersIndex)(dis, bufferCount, width, height, newFormat, swapChainFlags);
	}

	int Hooks::JoinPlayer(__int64 a1, int a2, __int64* a3, int a4) {
		if (Joiner)
		{
			if (a3 == 0)
			{
				return static_cast<decltype(&JoinPlayer)>(g_Hooking->m_OriginalJoinPlayer)(a1, a2, a3, a4);
			}
			*a3 = Join;	

		}
		return static_cast<decltype(&JoinPlayer)>(g_Hooking->m_OriginalJoinPlayer)(a1, a2, a3, a4);
	}

	Hooking::Hooking():
		m_D3DHook(g_GameVariables->m_Swapchain, 18),
		m_ObjectBypass(Signature("74 48 E8 ? ? ? ? 48 8B 48 48").Scan().Add(3).Rip().Add(30).As<char*>())
	{	
		std::copy_n(m_ObjectBypass, 2, m_OriginalObjectBypass);

		MH_Initialize();
		MH_CreateHook(g_GameFunctions->m_JoinPattern, &Hooks::JoinPlayer, &m_OriginalJoinPlayer);
		MH_CreateHook(g_GameFunctions->m_IsDlcPresent, &Hooks::IsDlcPresent, &m_OriginalIsDlcPresent);
		MH_CreateHook(g_GameFunctions->m_GetLabelText, &Hooks::GetLabelText, &m_OriginalGetLabelText);
		MH_CreateHook(g_GameFunctions->m_GetEventData, &Hooks::GetEventData, &m_OriginalGetEventData);
		MH_CreateHook(g_GameFunctions->m_NetworkEvents, &Hooks::NetworkManager, &m_OriginalNetworkManager);
		MH_CreateHook(g_GameFunctions->m_WndProc, &Hooks::WndProc, &m_OriginalWndProc);
		m_D3DHook.Hook(&Hooks::Present, Hooks::PresentIndex);
		m_D3DHook.Hook(&Hooks::ResizeBuffers, Hooks::ResizeBuffersIndex);
	}

	Hooking::~Hooking() noexcept
	{
		MH_RemoveHook(g_GameFunctions->m_JoinPattern); //Join pattern
		MH_RemoveHook(g_GameFunctions->m_WndProc);
		MH_RemoveHook(g_GameFunctions->m_GetEventData);
		MH_RemoveHook(g_GameFunctions->m_GetLabelText);
		MH_RemoveHook(g_GameFunctions->m_IsDlcPresent);
		MH_RemoveHook(g_GameFunctions->m_GetPlayerNetworkId);
		MH_RemoveHook(g_GameFunctions->m_NetworkEvents);
		MH_Uninitialize();
	}

	void Hooking::Hook()
	{
		std::fill_n(m_ObjectBypass, 2, '\x90');
		m_D3DHook.Enable();
		MH_EnableHook(MH_ALL_HOOKS);
	}

	void Hooking::Unhook()
	{
		std::copy_n(m_OriginalObjectBypass, 2, m_ObjectBypass);
		m_D3DHook.Disable();
		MH_DisableHook(MH_ALL_HOOKS);
	}
}

