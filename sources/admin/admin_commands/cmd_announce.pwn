/*

	About: announce admin command
	Author: ziggi

*/

#if defined _admin_cmd_announce_included
	#endinput
#endif

#define _admin_cmd_announce_included

/*
	Defines
*/

#if !defined ANNOUNCE_MAX_LENGTH
	#define ANNOUNCE_MAX_LENGTH 16
#endif

#if !defined ANNOUNCE_TIME
	#define ANNOUNCE_TIME 5000
#endif

/*
	Command
*/

COMMAND:announce(playerid, params[])
{
	if (!IsPlayerHavePrivilege(playerid, PlayerPrivilegeAdmin)) {
		return 0;
	}

	new
		type,
		text[ANNOUNCE_MAX_LENGTH];

	if (sscanf(params, "is[" #ANNOUNCE_MAX_LENGTH "]", type, text)) {
		Lang_SendText(playerid, "ADMIN_COMMAND_ANNOUNCE_HELP");
		return 1;
	}

	if (!(0 <= type <= 6)) {
		Lang_SendText(playerid, "ADMIN_COMMAND_ANNOUNCE_HELP");
		return 1;
	}

	GameTextForAll(text, ANNOUNCE_TIME, type);
	return 1;
}
