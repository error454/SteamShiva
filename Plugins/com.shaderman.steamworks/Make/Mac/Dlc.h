#ifndef DLC_H
#define DLC_H

#include "steam_api.h"

// From https://partner.steamgames.com/documentation/bootstrap_leaderboards
class CSteamDlc
{
private:

public:
	
	CSteamDlc(const char* sAIModel);
	~CSteamDlc(){};
	bool IsDLCInstalled( const char *sDlcID );

	// the calling user AI model name, we need it for callbacks
	const char* m_sAIModel;
};

#endif