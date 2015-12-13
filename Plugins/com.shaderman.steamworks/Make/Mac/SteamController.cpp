#include "PrecompiledHeader.h"

#include "steam_api.h"
#include "SteamController.h"

#include "Steamworks.h"

// helpers
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

//-----------------------------------------------------------------------------
// HELPERS
//-----------------------------------------------------------------------------

void logger(std::string in){
	S3DX::log.message(in.c_str());
}


// CSV-like string explode

std::vector<std::string> explodeCSV(std::string sCSV) {
	std::vector<std::string> vect;
	// just to make sure that there are no whitespaces
	std::replace(sCSV.begin(), sCSV.end(), ' ', '_');
	// replace comma with whitespace
	std::replace(sCSV.begin(), sCSV.end(), ',', ' ');

	std::stringstream ss(sCSV);
	std::string tmp;

	while (ss >> tmp) { vect.push_back(tmp); }
	return vect;
}

//-----------------------------------------------------------------------------
// CONSTRUCTOR
//-----------------------------------------------------------------------------

CSteamCon::CSteamCon(const char* sAIModel)
{
	// shiva communication
	m_sAIModel = sAIModel;
	bConActive = false;

	// steam init
	if (!SteamController()->Init()) {
		S3DX::log.warning("Could not initialize STEAM Controller");
	} else {
		S3DX::log.message("STEAM Controller loaded");
	}

}

//-----------------------------------------------------------------------------
// INIT n LOOPS
//-----------------------------------------------------------------------------

int CSteamCon::getConnectedControllers()
{
	int temp = SteamController()->GetConnectedControllers(conHandles);
	if ((temp > STEAM_CONTROLLER_MAX_COUNT) || (temp < 0)) return -1;
	else return temp;
}

void CSteamCon::sconLoop() {

	hU = S3DX::application.getCurrentUser();
	if (hU.IsNil()) return;

	// -- 1. continuously poll controllers

	// get table to write the controllerIDs to
	tSconIDs = S3DX::user.getAIVariable(hU, m_sAIModel, "tSconIDs");

	int temp = SteamController()->GetConnectedControllers(conHandles);
	// If there's an active controller, and if we're not already using it, select the first one.
	if (temp && (m_ActiveControllerHandle != conHandles[0])) {
		m_ActiveControllerHandle = conHandles[0];
	}

	// prepare ShiVa controllerID table
	S3DX::table.empty(tSconIDs);
		
	// loop 1: go through all controller handles
	for (int i = 0; i < STEAM_CONTROLLER_MAX_COUNT; ++i) {
		if (conHandles[i] < 1) continue; // probably 0

		// fill ShiVa controllerID table
		std::stringstream sCurConID;
		sCurConID << conHandles[i]; // current controller handle
		const std::string &tmpID = sCurConID.str();
		S3DX::table.add(tSconIDs, tmpID.c_str());


		// --2. continuously get action data

		// loop 2.1: all digital actions
		for (auto iter = DigitalActionHandles.begin(); iter != DigitalActionHandles.end(); ++iter) {
			if ((SteamController()->GetDigitalActionData(conHandles[i], iter->second)).bActive) {
				
				// get button origin
				EControllerActionOrigin origins[STEAM_CONTROLLER_MAX_ORIGINS];
				int nNumOrigins = SteamController()->GetDigitalActionOrigins(conHandles[i], SteamController()->GetCurrentActionSet(conHandles[i]), iter->second, origins);
				if (!nNumOrigins) nNumOrigins = 0;
				else nNumOrigins = origins[0];

				if ((SteamController()->GetDigitalActionData(conHandles[i], iter->second)).bState && (!DigitalActionStates[i][iter->first])) { // pressed, but shiva says false
					// switch on event
					DigitalActionStates[i][iter->first] = true;
					// send event
					S3DX::user.sendEventImmediate(hU, m_sAIModel, "onSconDigitalActionOn", tmpID.c_str(), (iter->first).c_str(), getActionSet(tmpID.c_str()), (float)nNumOrigins);
				}
				else if (!(SteamController()->GetDigitalActionData(conHandles[i], iter->second)).bState && (DigitalActionStates[i][iter->first])) { // not pressed any longer, but shiva still says true
					// switch off event
					DigitalActionStates[i][iter->first] = false;
					// send event
					S3DX::user.sendEventImmediate(hU, m_sAIModel, "onSconDigitalActionOff", tmpID.c_str(), (iter->first).c_str(), getActionSet(tmpID.c_str()), (float)nNumOrigins);
					//ActionSetHandles (SteamController()->GetCurrentActionSet(conHandles[i]))
				}
			}
		} // 2.1 end


		// loop 2.2: all analog actions
		for (auto iter = AnalogActionHandles.begin(); iter != AnalogActionHandles.end(); ++iter) {
			if ((SteamController()->GetAnalogActionData(conHandles[i], iter->second)).bActive) {

				// get origin
				EControllerActionOrigin origins[STEAM_CONTROLLER_MAX_ORIGINS];
				int nNumOrigins = SteamController()->GetAnalogActionOrigins(conHandles[i], SteamController()->GetCurrentActionSet(conHandles[i]), iter->second, origins);
				if (!nNumOrigins) nNumOrigins = 0;
				else nNumOrigins = origins[0];

				// continuous output
				S3DX::user.sendEventImmediate(hU, m_sAIModel, "onSconAnalogActionContinuous", tmpID.c_str(), (iter->first).c_str(), getActionSet(tmpID.c_str()), (SteamController()->GetAnalogActionData(conHandles[i], iter->second)).x, (SteamController()->GetAnalogActionData(conHandles[i], iter->second)).y, (float)nNumOrigins, (float)(SteamController()->GetAnalogActionData(conHandles[i], iter->second)).eMode);
			}
		} //2.2 end

	} // FOR end
}

//-----------------------------------------------------------------------------
// ACTIONS n SETS
//-----------------------------------------------------------------------------

bool CSteamCon::fillDigitalActions(std::string digitalActionCSV) {
	// explode CSV
	std::vector<std::string> vDA = explodeCSV(digitalActionCSV);

	if (!vDA.empty()) {
		for (std::vector<std::string>::iterator it = vDA.begin(); it != vDA.end(); ++it) {
			DigitalActionList.push_back(*it);
			DigitalActionHandles[*it] = SteamController()->GetDigitalActionHandle((*it).c_str());
		}
		// debug - show vector content
		// std::for_each(vDA.begin(), vDA.end(), logger);
		// std::for_each(DigitalActionList.begin(), DigitalActionList.end(), logger);
		return true;
	}

	return false;
}

bool CSteamCon::fillAnalogActions(std::string analogActionCSV) {
	// explode CSV
	std::vector<std::string> vAA = explodeCSV(analogActionCSV);

	if (!vAA.empty()) {
		for (std::vector<std::string>::iterator it = vAA.begin(); it != vAA.end(); ++it) {
			AnalogActionList.push_back(*it);
			AnalogActionHandles[*it] = SteamController()->GetAnalogActionHandle((*it).c_str());
		}
		return true;
	}

	return false;
}

bool CSteamCon::fillActionSets(std::string actionSetCSV) {
	// explode CSV
	std::vector<std::string> vAS = explodeCSV(actionSetCSV);

	if (!vAS.empty()) {
		for (std::vector<std::string>::iterator it = vAS.begin(); it != vAS.end(); ++it) {
			ActionSetList.push_back(*it);
			ActionSetHandles[*it] = SteamController()->GetActionSetHandle((*it).c_str());
			ActionSetHandlesReverse[SteamController()->GetActionSetHandle((*it).c_str())] = *it;
		}
		return true;
	}

	return false;
}

const char* CSteamCon::getActionSet(std::string controllerID){
	uint64 conID; // controller ID is a uint64 - conversion required
	std::stringstream ss(controllerID);
	ss >> conID;

	return (ActionSetHandlesReverse[SteamController()->GetCurrentActionSet(conID)]).c_str();
}

void CSteamCon::setActionSet(std::string controllerID, std::string actionSet){
	uint64 conID; // controller ID is a uint64 - conversion required
	std::stringstream ss(controllerID);
	ss >> conID;
	
	if (std::find(std::begin(conHandles), std::end(conHandles), conID) != std::end(conHandles))
		SteamController()->ActivateActionSet(conID, ActionSetHandles[actionSet]);
}

//-----------------------------------------------------------------------------
// ORIGINALS
//-----------------------------------------------------------------------------

int CSteamCon::GetConstForControllerOriginDigital(const char* cID, const char* cAS, const char* cDA) {

	EControllerActionOrigin origins[STEAM_CONTROLLER_MAX_ORIGINS];
	uint64 conID; // controller ID is a uint64 - conversion required
	std::stringstream ss(cID);
	ss >> conID;

	ControllerHandle_t hC = conID;
	ControllerActionSetHandle_t hAS = ActionSetHandles[cAS];
	ControllerDigitalActionHandle_t hDA = DigitalActionHandles[cDA];

	int nNumOrigins = SteamController()->GetDigitalActionOrigins(hC, hAS, hDA, origins);

	if (nNumOrigins)
	{
		// We should handle the case where this action is bound to multiple buttons, but
		// here we just grab the first. - Steam Quote
		return origins[0];
	}

	return 0; // Return "None"
}

int CSteamCon::GetConstForControllerOriginAnalog(const char* cID, const char* cAS, const char* cAA) {

	EControllerActionOrigin origins[STEAM_CONTROLLER_MAX_ORIGINS];
	uint64 conID; // controller ID is a uint64 - conversion required
	std::stringstream ss(cID);
	ss >> conID;

	ControllerHandle_t hC = conID;
	ControllerActionSetHandle_t hAS = ActionSetHandles[cAS];
	ControllerAnalogActionHandle_t hAA = AnalogActionHandles[cAA];

	int nNumOrigins = SteamController()->GetAnalogActionOrigins(hC, hAS, hAA, origins);

	if (nNumOrigins)
	{
		// We should handle the case where this action is bound to multiple buttons, but
		// here we just grab the first. - Steam Quote
		return origins[0];
	}

	return 0; // Return "None"
}

//-----------------------------------------------------------------------------
// REBIND PANEL
//-----------------------------------------------------------------------------

bool CSteamCon::showRebindPanel(std::string controllerID){
	uint64 conID; // controller ID is a uint64 - conversion required
	std::stringstream ss(controllerID);
	ss >> conID;
	return SteamController()->ShowBindingPanel(conID);
}

//-----------------------------------------------------------------------------
// FORCE FEEDBACK
//-----------------------------------------------------------------------------

void CSteamCon::hapticFeedback(std::string sControllerID, float kPad, float nTime) {
	uint64 conID; // controller ID is a uint64 - conversion required
	std::stringstream ss(sControllerID);
	ss >> conID;

	// error correction
	kPad = ((kPad > 1) || (kPad < 0)) ? 1 : kPad;
	nTime = (nTime > 0) ? nTime : 1;

	// check if pad exists
	if (std::find(std::begin(conHandles), std::end(conHandles), conID) != std::end(conHandles))
		SteamController()->TriggerHapticPulse(conID, (ESteamControllerPad) (int) kPad, (unsigned short) abs((int)nTime));
}