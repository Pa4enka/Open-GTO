/*
	Created: 04.06.11
	Aurthor: ZiGGi
*/

#if defined _bar_included
	#endinput
#endif

#define _bar_included
#pragma library bar


new Bars[][CoordInfo] = {
	{495.3609,-76.0381,998.7578}, // green bar
	{681.5761,-453.8308,-25.6172}, // Welcome Pump(Dillimore)
	{-2654.0112,1413.2083,906.2771}, // Jizzy's
	{1955.3743,1017.9493,992.4688}, // 4 Dragons Casino
	{1139.7212,-4.2430,1000.6719}, // Redsands Casino
	{-224.7835,1407.4834,27.7734} // Lil' Probe Inn
};

enum DrinkInfo {
	Name[MAX_NAME],
	Cost,
	Float:Hp,
	Float:Alcohol,
	Action,
}
new Drinks[][DrinkInfo] = {
	{"����� ������ �����",100,30.0,40.0,SPECIAL_ACTION_DRINK_SPRUNK},
	{"���� ����������",30,10.0,4.5,SPECIAL_ACTION_DRINK_BEER},
	{"���� ������� �������",30,10.0,10.0,SPECIAL_ACTION_DRINK_WINE},
	{"��� � ������� � �������",15,10.0,-20.0,SPECIAL_ACTION_DRINK_SPRUNK}
};

stock bar_OnGameModeInit()
{
	for(new b_id=0;b_id<sizeof(Bars);b_id++)
	{
	    CreatePickup(1551,23,Bars[b_id][Coord_X],Bars[b_id][Coord_Y],Bars[b_id][Coord_Z]);
	}
	GameMSG("SERVER: (services)Bar module init");
	return 1;
}

stock bar_OnPlayerKeyStateChange(playerid,newkeys,oldkeys)
{
	#pragma unused oldkeys,newkeys
	bar_ShowDialog(playerid);
	return 1;
}

stock bar_ShowDialog(playerid)
{
	new string[256];
	for(new i=0;i<sizeof(Drinks);i++)
		format(string,sizeof(string),"%s%s($%d, �����: %0.1f%%, ���������: %0.0f)\n",string,Drinks[i][Name],Drinks[i][Cost],Drinks[i][Alcohol],Drinks[i][Hp]);
	return ShowPlayerDialog(playerid,bar_DialogID,DIALOG_STYLE_LIST,
		"���� ������� ��������",
		string,
		"������","������"
	);
}

stock bar_OnDialogResponse(playerid,dialogid,response,listitem,inputtext[])
{
	#pragma unused inputtext
	if(dialogid == bar_DialogID)
	{
		if(!response) return 1;
		if(oGetPlayerMoney(playerid) < Drinks[listitem][Cost])
			return show_Msg_Dialog(playerid,"������� ��������","��� �� ������� �����!","��");
		oGivePlayerMoney(playerid,-Drinks[listitem][Cost],1);
		SetPlayerSpecialAction(playerid,Drinks[listitem][Action]);
		SetPlayerDrunkLevel(playerid,GetPlayerDrunkLevel(playerid) + floatround(Drinks[listitem][Alcohol]*100,floatround_round));
		if(Drinks[listitem][Hp] + oGetPlayerHealth(playerid) > GetMaxHealth(playerid))
			oSetPlayerHealth(playerid,GetMaxHealth(playerid));
		else
			oSetPlayerHealth(playerid,oGetPlayerHealth(playerid) + Drinks[listitem][Hp]);
		new string[MAX_STRING];
		format(string,sizeof(string),"�� ������ %s, �� $%d, ���������� %0.1f%% � ���������� �� %0.0f.",Drinks[listitem][Name],Drinks[listitem][Cost],Drinks[listitem][Alcohol],Drinks[listitem][Hp]);
		show_Msg_Dialog(playerid,"������� ��������",string,"��");
		return 1;
	}
	return 1;
}

stock IsPlayerAtBar(playerid)
{
	for(new b_id=0;b_id<sizeof(Bars);b_id++)
	{
		if(IsPlayerInRangeOfPoint(playerid,2,Bars[b_id][Coord_X],Bars[b_id][Coord_Y],Bars[b_id][Coord_Z]))
			return 1;
	}
	return 0;
}