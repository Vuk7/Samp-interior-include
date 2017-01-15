#define MAX_INTERIORS_CHANGE 55

#include <a_samp>
#include <interior>
#include <zcmd>

new test;
new inte;

main()
{
	print("\n----------------------------------");
	print(" Test for interior include by Vuk ");
	print("----------------------------------\n");
}

public OnGameModeInit()
{
	SetGameModeText("test");
	AddPlayerClass(0, 0.0,0.0,4.0,0.0, 0, 0, 0, 0, 0, 0);
    inte = CreateInterior(52,"test",0.0,0.0,4.0,0.0,-1861.936889,54.908092,1061.143554,0.0,0,0,14,1);
	return 1;
}

public OnGameModeExit()
{
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
	SetPlayerPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraLookAt(playerid, 1958.3783, 1343.1572, 15.3746);
	return 1;
}

public OnPlayerConnect(playerid)
{
    ResetPlayerInterior(playerid);
    new str[120];
	format(str,sizeof(str),"%d",GetPlayerInteriorID(playerid));
	SendClientMessageToAll(-1,str);
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	return 1;
}

public OnInteriorCreated(id,name[],Float:enterx,Float:entery,Float:enterz,Float:enteraz,Float:exitx,Float:exity,Float:exitz,Float:exitaz,interiorin,vwin,interiorout,vwout)
{
	if(id == 0) return print("uspjesno");
	return 1;
}

public OnPlayerTryToEnterInInterior(playerid,interiorid)
{
	if(test == 0)
	{
	    SendClientMessageToAll(-1,"test ti je na 0");
	    return 0;
	}
	new str[120];
	format(str,sizeof(str),"OnPlayerTryToEnterInInterior, |%d | %d|",playerid,interiorid);
	SendClientMessageToAll(-1,str);
	return 1;
}

public OnPlayerEnterInInterior(playerid,interiorid)
{
	new str[120];
	format(str,sizeof(str),"OnPlayerEnterInInterior, |%d | %d|",playerid,interiorid);
	SendClientMessageToAll(-1,str);
	return 1;
}

public OnPlayerTryToExitInInterior(playerid,interiorid)
{
	if(test == 1)
	{
	    SendClientMessageToAll(-1,"test ti je na 1");
	    return 0;
	}
	new str[120];
	format(str,sizeof(str),"OnPlayerTryToExitInInterior, |%d | %d|",playerid,interiorid);
	SendClientMessageToAll(-1,str);
	return 1;
}

public OnPlayerExitFromInterior(playerid,interiorid)
{
	new str[120];
	format(str,sizeof(str),"OnPlayerExitFromInterior, |%d | %d|",playerid,interiorid);
	SendClientMessageToAll(-1,str);
	return 1;
}

public OnInteriorsNameChanged(interiorid,name[])
{
    new str[120];
	format(str,sizeof(str),"OnInteriorsNameChanged, |%d | %s|",interiorid,name);
	SendClientMessageToAll(-1,str);
	return 1;
}

CMD:test(playerid,params[])
{
	if(test == 0)
	{
		test = 1;
	}
	else
	{
		test = 0;
	}
	return 1;
}

CMD:test1(playerid,params[])
{
    ChangeInteriorName(inte,"{0xAFAFAFAA}test123{0x33AA33AA}");
	return 1;
}
CMD:test2(playerid,params[]) return DestroyInterior(inte);

CMD:test3(playerid,params[])
{
    if(IsInteriorExist(52)) return SendClientMessageToAll(-1,"Postoji");
    return 1;
}
CMD:test4(playerid,params[])
{
    inte = CreateInterior(52,"test",0.0,0.0,4.0,0.0,-1861.936889,54.908092,1061.143554,0.0,0,0,14,1);
	return 1;
}
