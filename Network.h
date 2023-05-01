#pragma once

namespace Big
{
	extern bool Crash;

	void netwUpdateLoop();

	void instantCrash();

	float m_PosX = 0.87f;
	float m_PosY = 0.10f;
	float m_Width = 0.22f;

	void cagePlayer(Ped ped);
	void kick_to_new_lobby(int player);
	void airStrikePlayer(Ped player);
	void ceo_kek();
	void dupeCar(int player);

	extern bool antiAFK;
	extern bool chatBypass;
	extern bool restricted;
	extern bool sessionInfo;
	extern bool PlayerInfo; 
	extern bool serverScanner;
	extern bool NightClubMoney;
	extern bool notify;
	extern bool kick;
	extern bool crash;
	extern bool joinNotify;
	extern bool lockLobby;
	extern bool blacklistopmk2;
	extern bool exMe;
	extern bool exFriends;
	extern bool exIniPlayers;
	extern bool exclude(int pl);

	extern bool InfiniteLoading;
	extern bool antiKick;
	extern bool antitransaction_error;
	extern bool antiCeoKick;
	extern bool antiCEOban;
	extern bool antiSsend_player_to_job;
	extern bool antiPassive;
	extern bool antiAntismth;
	BOOL IsPlayerFriend(Player player);

	extern int dAmount;
	extern int dDelay;
	extern int dHeight;
	extern bool dEnable;
	extern int dx, dy, dz;

	void moneyDrop(bool enable, int amount, int droptype, int delay, int xPlus, int yPlus, int zPlus, int Height, Hash model);
	Hash modelDrop(int id);

	extern Hash emodel2;
	extern Hash emodel3;
	extern Hash emodel4;

	inline const char* TypeText[]
	{
		"Money"
	};

	inline const char* money_drop[]
	{
		"Money Bag", "X-Mas Tree", "Alien Egg", "Dildo", "Safe","Med Bag", "Gun Case", "Guitar", "Bag", "Alien", "Moneybag"
	};

	inline Hash Types[]
	{
		0xCE6FDD6B, 0x2C014CA6
	};

	inline std::size_t typePos = 0;
	inline std::size_t money_drop_pos = 0;

	extern int money_amount;
}