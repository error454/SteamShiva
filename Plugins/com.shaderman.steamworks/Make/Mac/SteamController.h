//-----------------------------------------------------------------------------
#ifndef __SteamController_h__
#define __SteamController_h__
//-----------------------------------------------------------------------------

#include "steam_api.h"

#include <string>
#include <vector>
#include <map>

// Main Controller class: 1.35
class CSteamCon
{
private:

	// ShiVa vars
	S3DX::AIVariable hU;

	// action lists - for reference only
	std::vector<std::string> DigitalActionList;
	std::vector<std::string> AnalogActionList;
	std::vector<std::string> ActionSetList;

	// action handles - maps instead of enums for flexibility
	std::map<std::string, ControllerDigitalActionHandle_t> DigitalActionHandles;
	std::map<std::string, ControllerAnalogActionHandle_t> AnalogActionHandles;
	std::map<std::string, ControllerActionSetHandle_t> ActionSetHandles;
	std::map<ControllerActionSetHandle_t, std::string> ActionSetHandlesReverse;

	// action states
	std::map<std::string, bool> DigitalActionStates[STEAM_CONTROLLER_MAX_COUNT];
	std::map<std::string, bool> AnalogActionStates[STEAM_CONTROLLER_MAX_COUNT];


public:

	CSteamCon(const char* sAIModel);
	~CSteamCon(){};

	//-----------------------------------------------------------------------------
	//  ShiVa vars
	//-----------------------------------------------------------------------------

	// the calling user AI model name, we need it for callbacks
	const char* m_sAIModel;
	
	// control bool TRUE for active controller
	bool bConActive;
	
	// AIModel table where we write all the controller IDs to as strings
	S3DX::AIVariable tSconIDs;
	
	//-----------------------------------------------------------------------------
	//  STEAM vars
	//-----------------------------------------------------------------------------

	// array of controller handles
	ControllerHandle_t conHandles[STEAM_CONTROLLER_MAX_COUNT];

	// A handle to the currently active Steam Controller / controller 0
	ControllerHandle_t m_ActiveControllerHandle;

	//-----------------------------------------------------------------------------
	//  methods
	//-----------------------------------------------------------------------------

	// controller count - call every frame
	int getConnectedControllers();

	// resolve actions on startup
	bool fillAnalogActions(std::string analogActionCSV);
	bool fillDigitalActions(std::string digitalActionCSV);
	bool fillActionSets(std::string actionSetCSV);

	// get/set actionsets
	const char* getActionSet(std::string controllerID);
	void setActionSet(std::string controllerID, std::string actionSet);

	// These calls return a plugin constant describing which controller button the action is currently bound to
	int GetConstForControllerOriginDigital(const char* cID, const char* cAS, const char* cDA);
	int GetConstForControllerOriginAnalog(const char* cID, const char* cAS, const char* cAA);

	// Steam Controller rebind panel
	bool showRebindPanel(std::string controllerID);

	// groups stuff that needs to be called every frame
	void sconLoop();

	// force feedback light
	void hapticFeedback(std::string sControllerID, float kPad, float nTime);

};


//-----------------------------------------------------------------------------
#endif // __SteamController_h__
//-----------------------------------------------------------------------------