#include "Headermanager.h"
#include "Common.hpp"

namespace Big
{
	

	void YTDLoader::LoadYTD()
	{
		g_Settings.m_Header = "cumplex";
		uint32_t textureID;
		char buffers[255];

		std::sprintf(buffers, "C:\\Viper\\cumplex.ytd", &g_Settings.m_Header);
		std::sprintf(buffers, "cumplex.ytd", &g_Settings.m_Header);
		g_GameFunctions->m_FileRegister(&textureID, buffers, true, buffers, false);
	}

	
}


