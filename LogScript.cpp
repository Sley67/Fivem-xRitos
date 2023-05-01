#include "Game.hpp"
#include "LogScript.hpp"
#include "UI/UIManager.hpp"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
static char abc[12];

static char KeyInputFromLogger[12];

static char keyFor_Logger[24];
static char keyFor_Logger1[24];
std::string Big::currentKey;
std::string currentKey1;
namespace Big
{


	bool LogScript::IsInitialized()
	{
		return m_Initialized;
	}

	ScriptType LogScript::GetType()
	{
		return ScriptType::D3D;
	}

	void LogScript::Initialize()
	{
		m_Initialized = true;
	}

	void LogScript::Destroy()
	{
	}

	namespace
	{
		std::size_t s_LastLogCount = 0;
	}

	void LogScript::Tick()
	{
		if (g_UiManager->m_Opened && g_Settings.m_LogWindow)
		{
			ImGui::SetNextWindowSize(ImVec2(500, 250), ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_FirstUseEver);
			if (ImGui::Begin("Log"))
			{
				std::lock_guard lock(g_Logger->GetMutex());
				auto msgs = g_Logger->GetMessages();

				for (std::size_t i = 0; i < msgs.second; ++i)
				{
					ImGui::TextUnformatted(msgs.first[i].get());
				}

				if (s_LastLogCount != msgs.second)
				{
					s_LastLogCount = msgs.second;
					ImGui::SetScrollHereY(1.f);
				}
			}  ImGui::End();
		}

		if (Big::CreateOutfitWindow)
		{
			ImGui::SetNextWindowSize(ImVec2(500, 250), ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_FirstUseEver);
			if (ImGui::Begin("Viper Input"))
			{


				ImGui::InputText("Outfit Name", abc, 24);

				oName = abc;


			}  ImGui::End();
		}

		if (Big::KeyWindow == true)
		{
			ImGui::SetNextWindowSize(ImVec2(500, 250), ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_FirstUseEver);
			if (ImGui::Begin("Viper Input"))
			{	
				ImGui::InputInt("Enter R*ID number", &RIDNumber, 20);
				ImGui::InputText("The Key you want modified", keyFor_Logger1, 12);
				ImGui::InputText("The Key you want assigned", keyFor_Logger, 12);
				currentKey = keyFor_Logger;
				currentKey1 = keyFor_Logger1; //idk why you would need to assign to string, it takes both lmao ;p

				if (currentKey1 == "Open")
				{
					KeyLevel = 1;
					IHateMyLife(currentKey);

				}
				else if (currentKey1 == "Back")
				{
					KeyLevel = 2;
					IHateMyLife(currentKey);
				}
				else if (currentKey1 == "Enter")
				{
					KeyLevel = 3;
					IHateMyLife(currentKey);
				}
				else if (currentKey1 == "Up")
				{
					KeyLevel = 4;
					IHateMyLife(currentKey);
				}
				else if (currentKey1 == "Down")
				{
					KeyLevel = 5;
					IHateMyLife(currentKey);
				}
				else if (currentKey1 == "Left")
				{
					KeyLevel = 6;
					IHateMyLife(currentKey);
				}
				else if (currentKey1 == "Right")
				{
					KeyLevel = 7;
					IHateMyLife(currentKey);
				}
				else
				{

				}

			}  ImGui::End();
		}

		if (Big::sessionInfo)
		{
			ImGui::SetNextWindowSize(ImVec2(500, 250), ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_FirstUseEver);
			if (ImGui::Begin("Session Info"))
			{






			}  ImGui::End();
		}


	}
}
