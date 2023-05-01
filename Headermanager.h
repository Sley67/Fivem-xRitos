#pragma once
#include <stdint.h>
namespace Big
{
	class YTDLoader
	{
	public:
		void LoadYTD();
	};
	inline std::unique_ptr<YTDLoader> g_YtdLoader;
}