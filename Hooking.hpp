#pragma once
#include "VMTHook.hpp"

extern HANDLE mainFiber;
extern DWORD wakeAt;

extern bool m_RemoveWeapons;
extern bool m_Give_Weapons;
extern bool m_SoundEvent;
extern bool m_WantedLevel;
extern bool m_Explosions;
extern bool m_Weather;
extern bool m_Clock;
extern bool m_Fire;
extern bool m_ClearPedTasks;
extern bool m_PTFX;
extern bool m_RequestPickup;
extern bool m_ReportMyself;
extern bool m_ReportCashSpawn;
extern bool m_RequestControl;

namespace Big
{
	struct Hooks
	{
		static int JoinPlayer(__int64 a1, int a2, __int64* a3, int a4);
		static bool IsDlcPresent(std::uint32_t hash);
		static bool EventManager(void* events, CNetGamePlayers* sourcePlayer, CNetGamePlayers* targetPlayer);
		static const char* GetLabelText(void* unk, const char* label);
		static bool GetEventData(std::int32_t eventGroup, std::int32_t eventIndex, std::int64_t* args, std::uint32_t argCount);
		static LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static void joinDetect(class CGameScriptHandlerMgr* _this, CNetGamePlayer* player);
		static constexpr auto PresentIndex = 8;
		static HRESULT Present(IDXGISwapChain* dis, UINT syncInterval, UINT flags);
		static int TriggerScriptEvent(bool unk0, uint64_t* args, int argCount, int bitFlags);
		static void NetworkManager(__int64 a1, __int64 a2, __int64 a3, unsigned __int16 a4, int a5, int a6, __int64 a7, __int64 a8);
		static constexpr auto ResizeBuffersIndex = 13;
		static HRESULT ResizeBuffers(IDXGISwapChain* dis, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags);
		
	};

	class Hooking
	{
	public:
		explicit Hooking();
		~Hooking() noexcept;
		Hooking(Hooking const&) = delete;
		Hooking(Hooking&&) = delete;
		Hooking& operator=(Hooking const&) = delete;
		Hooking& operator=(Hooking&&) = delete;

		void Hook();
		void Unhook();

		friend struct Hooks;
	private:
		void* m_OriginalJoinPlayer{};
		void* m_NtQueryVirtualMemory{};
		void* m_OriginalEventManager{};
		void* m_OriginalIsDlcPresent{};
		void* m_OriginalGetLabelText{};
		void* m_OriginalGetEventData{};
		void* m_OriginalWndProc{};
		void* m_OriginalTriggerScriptEvent{};
		void* m_OriginalNetworkManager{};
		VMTHook m_D3DHook;

		char* m_ObjectBypass;
		char m_OriginalObjectBypass[2];
	};

	inline std::unique_ptr<Hooking> g_Hooking;
}

void WAIT(DWORD ms);