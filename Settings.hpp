#pragma once

namespace Big
{
	class Settings
	{
	public:
		std::atomic_bool m_LogWindow = true;
		std::atomic_bool m_LockMouse = false;
		const char* m_Header;
	};

	inline Settings g_Settings;
}
