#pragma once

extern int Join;
extern bool Joiner;
extern int RIDNumber;

namespace rage
{
	struct scrNativeRegistration;
}

namespace Big
{
	class GameVariables
	{
	public:
		explicit GameVariables();
		~GameVariables() noexcept = default;
		GameVariables(GameVariables const&) = delete;
		GameVariables(GameVariables&&) = delete;
		GameVariables& operator=(GameVariables const&) = delete;
		GameVariables& operator=(GameVariables&&) = delete;

		void PostInit();

		bool* is_session_started;
		uint64_t m_WorldPtr;
		__int64** m_GlobalPtr;

		std::uint32_t* m_GameState;
		std::uint32_t* m_FrameCount;
		HWND m_GameWindow;
		IDXGISwapChain* m_Swapchain;
		rage::scrNativeRegistration** m_NativeRegistrations;
		std::uint64_t** m_GlobalBase;
		char* m_GameBuild;
		char* m_NativeRetn;
		char m_OriginalNativeRetn[2];

		void EnableNativePatch();
		void DisableNativePatch();
		void* GetNativeReturnAddress();
	};

	class GameFunctions
	{
	public:
		explicit GameFunctions();
		~GameFunctions() noexcept = default;
		GameFunctions(GameFunctions const&) = delete;
		GameFunctions(GameFunctions&&) = delete;
		GameFunctions& operator=(GameFunctions const&) = delete;
		GameFunctions& operator=(GameFunctions&&) = delete;

		using IsDlcPresent = bool(std::uint32_t hash);
		IsDlcPresent* m_IsDlcPresent;

		using WndProc = LRESULT(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		WndProc* m_WndProc;

		using SessionWeather = void(char a1, int a2, int a3, __int64 a4);
		SessionWeather* m_SessionWeather;

		using TriggerScriptEvent = int(bool unk0, uint64_t* args, int argCount, int bitFlags);
		TriggerScriptEvent* m_TriggerScriptEvent;

		using GetEventData = bool(std::int32_t eventGroup, std::int32_t eventIndex, std::int64_t* args, std::uint32_t argCount);
		GetEventData* m_GetEventData;

		using NetworkMgr = void(__int64 a1, __int64 a2, __int64 a3, unsigned __int16 a4, int a5, int a6, __int64 a7, __int64 a8);
		NetworkMgr* m_NetworkEvents;

		using GetLabelText = const char*(void* unk, const char* label);
		GetLabelText* m_GetLabelText;

		using FileRegister = std::uint32_t(std::uint32_t* texture_id, const char* path, bool p1, const char* name, bool p2);
		FileRegister* m_FileRegister;

		using GetPlayerNetworkId = CNetGamePlayers * (int player);
		GetPlayerNetworkId* m_GetPlayerNetworkId;
		
		using pJoinPattern = int(__int64 a1, int a2, __int64* a3, int a4);
		pJoinPattern* m_JoinPattern;
	};

	inline std::unique_ptr<GameVariables> g_GameVariables;
	inline std::unique_ptr<GameFunctions> g_GameFunctions;
}
