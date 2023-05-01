#include "Game.hpp"
#include "Invoker.hpp"
void(*rage::scrNativeCallContext::SetVectorResults)(rage::scrNativeCallContext*) = nullptr;

int Join = 0;
bool Joiner;

int RIDNumber;

namespace Big
{
	GameVariables::GameVariables():
		m_GameState(Signature("48 85 C9 74 4B 83 3D").Scan().Add(7).Rip().As<decltype(m_GameState)>()),
		m_FrameCount(Signature("F3 0F 10 0D ? ? ? ? 44 89 6B 08").Scan().Add(4).Rip().Sub(8).As<decltype(m_GameState)>()),
		m_GameWindow(FindWindowA("grcWindow", "Grand Theft Auto V")),
		m_Swapchain(Signature("48 8B 0D ? ? ? ? 48 8D 55 A0 48 8B 01").Scan().Add(3).Rip().As<decltype(m_Swapchain)&>()),
		m_NativeRegistrations(Signature("48 83 EC 20 48 8D 0D ? ? ? ? E8 ? ? ? ? 0F B7 15 ? ? ? ? 33 FF").Scan().Add(7).Rip().As<decltype(m_NativeRegistrations)>()),
		m_GlobalBase(Signature("4C 8D 4D 08 48 8D 15 ? ? ? ? 4C 8B C0").Scan().Add(7).Rip().As<decltype(m_GlobalBase)>()),
		is_session_started(Signature("44 38 1D ? ? ? ? 0F 84 ? ? ? ? 48 8B 01 FF 90 ? ? ? ? 48 8B 85").Scan().Add(3).Rip().As<bool*>()),
		m_NativeRetn(Signature("44 89 75 9F 49 8D 0C C1").Scan().Add(19).As<char*>())
	{
		std::copy_n(m_NativeRetn, 2, m_OriginalNativeRetn);

		char* c_location = nullptr;
		//World Pointer
		auto p_worldPtr = Memory::pattern("48 8B 05 ? ? ? ? 45 ? ? ? ? 48 8B 48 08 48 85 C9 74 07");
		c_location = p_worldPtr.count(1).get(0).get<char>(0);
		m_WorldPtr = reinterpret_cast<uint64_t>(c_location) + *reinterpret_cast<int*>(reinterpret_cast<uint64_t>(c_location) + 3) + 7;
		
		auto p_fixVector3Result = Memory::pattern("83 79 18 00 48 8B D1 74 4A FF 4A 18");
		auto void_location = p_fixVector3Result.count(1).get(0).get<void>(0);
		if (void_location != nullptr) rage::scrNativeCallContext::SetVectorResults = (void(*)(rage::scrNativeCallContext*))(void_location);

	}

	void GameVariables::PostInit()
	{
	}

	void GameVariables::EnableNativePatch()
	{
		std::uint8_t data[2] = { (std::uint8_t)0xFF, (std::uint8_t)0x23 };
		std::copy(std::begin(data), std::end(data), (std::uint8_t*)m_NativeRetn);
	}
	void GameVariables::DisableNativePatch()
	{
		std::copy(std::begin(m_OriginalNativeRetn), std::end(m_OriginalNativeRetn), m_NativeRetn);
	}
	void* GameVariables::GetNativeReturnAddress()
	{
		return m_NativeRetn;
	}

	GameFunctions::GameFunctions():
		m_IsDlcPresent(Signature("84 C0 74 0D 8D 53 0C").Scan().Sub(63).As<decltype(m_IsDlcPresent)>()),
		m_WndProc(Signature("48 8B 0D ? ? ? ? 48 8D 55 EF FF 15").Scan().Sub(853).As<decltype(m_WndProc)>()),
		m_GetEventData(Signature("48 85 C0 74 14 4C 8B 10").Scan().Sub(28).As<decltype(m_GetEventData)>()),
		m_NetworkEvents(Signature("66 41 83 F9 ? 0F 83 ? ? ? ?").Scan().As<decltype(m_NetworkEvents)>()),
		m_GetLabelText(Signature("75 ? E8 ? ? ? ? 8B 0D ? ? ? ? 65 48 8B 04 25 ? ? ? ? BA ? ? ? ? 48 8B 04 C8 8B 0C 02 D1 E9").Scan().Sub(19).As<decltype(m_GetLabelText)>()),
		m_FileRegister(Signature("48 89 5C 24 ? 48 89 6C 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 83 EC 50 48 8B EA 4C 8B FA 48 8B D9 4D 85 C9").Scan().Add(1).As<decltype(m_FileRegister)>()),
		m_GetPlayerNetworkId(Signature("80 F9 20 73 13 48 8B").Scan().As<decltype(m_GetPlayerNetworkId)>()),
		m_SessionWeather(Signature("E8 ? ? ? ? 48 85 C0 74 12 4C 8B C3").Scan().Add(116).As<decltype(m_SessionWeather)>()),
		m_JoinPattern(Signature("48 8B C4 48 89 58 10 48 89 70 18 48 89 78 20 48 89 48 08 55 41 54 41 55 41 56 41 57 48 8D 68 A8 48 81 EC ? ? ? ? 33 DB ").Scan().As<decltype(m_JoinPattern)>())
	{
		
	}
}
