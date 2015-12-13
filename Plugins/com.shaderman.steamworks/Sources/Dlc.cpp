#include "PrecompiledHeader.h"
#include "Dlc.h"
#include "steam_api.h"

CSteamDlc::CSteamDlc(const char* sAIModel)
{
	m_sAIModel = sAIModel;
}

//-----------------------------------------------------------------------------
bool CSteamDlc::IsDLCInstalled(const char* sDlcID)
{
	bool bInstalled = false;

	// AppID_t is uint32
	AppId_t appId = S3DX::string.toNumber(sDlcID);
	bInstalled = SteamApps()->BIsDlcInstalled(appId);
	return bInstalled;
}