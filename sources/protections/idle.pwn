/*

	Aurthor:	Iain Gilbert
	Modified by ziggi

*/

#if defined _antiidle_included
	#endinput
#endif

#define _antiidle_included
#pragma library antiidle


/*
 * Vars
 */

static
	IsEnabled = ANTI_IDLE_ENABLED,
	MaxTime = ANTI_IDLE_TIME,
	gIdleTime[MAX_PLAYERS],
	Float:gIdlePos[MAX_PLAYERS][3];

/*
 * Config
 */

pt_idle_LoadConfig(file_config)
{
	ini_getInteger(file_config, "Protection_Idle_IsEnabled", IsEnabled);
	ini_getInteger(file_config, "Protection_Idle_MaxTime", MaxTime);
}

pt_idle_SaveConfig(file_config)
{
	ini_setInteger(file_config, "Protection_Idle_IsEnabled", IsEnabled);
	ini_setInteger(file_config, "Protection_Idle_MaxTime", MaxTime);
}


/*
 * For public
 */

pt_idle_OnGameModeInit()
{
	if (!IsEnabled) {
		return 0;
	}

	Log_Game("SERVER: (protections)AntiIdle module init");
	return 1;
}


/*
 * For timer
 */

pt_idle_PlayerTimer(playerid)
{
	if (!IsEnabled) {
		return 0;
	}

	if (IsGroundholdEnabled() && IsPlayerInAnyGround(playerid) && !IsPlayerRconAdmin(playerid)) {
		new Float:pos[3];
		GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

		if (pos[0] == gIdlePos[playerid][0] && pos[1] == gIdlePos[playerid][1] && pos[2] == gIdlePos[playerid][2]) {
			gIdleTime[playerid]++;
			
			if (gIdleTime[playerid] > MaxTime - 1) {
				new string[MAX_LANG_VALUE_STRING];
				format(string, sizeof(string), _(PROTECTION_ANTIIDLE_INFO), MaxTime - 1);
				SendClientMessage(playerid, COLOR_RED, string);
				SendClientMessage(playerid, COLOR_RED, _(PROTECTION_ANTIIDLE_LAST_WARN));
			}
			if (gIdleTime[playerid] > MaxTime) {
				gIdleTime[playerid] = 0;
				KickPlayer(playerid, _(PROTECTION_ANTIIDLE_KICK_REASON));
			}
		} else {
			gIdleTime[playerid] = 0;
		}

		gIdlePos[playerid][0] = pos[0];
		gIdlePos[playerid][1] = pos[1];
		gIdlePos[playerid][2] = pos[2];
	}

	return 1;
}