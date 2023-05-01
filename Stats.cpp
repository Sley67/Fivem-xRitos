#include "Common.hpp"


namespace Big
{
	bool sixnine;
	int sellAmount = 67000000;


	void StatLoop()
	{
		if (sixnine)
		{

			globalHandle(99007).At(970).As<int>() = 65000000;
			//globalHandle(26269 + 0).As<int>() = sellAmount;
			
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MPPLY_VEHICLE_SELL_TIME"), 0, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("%0_MONEY_EARN_SELLING_VEH"), 50000, true);

		}
		
	}

}
