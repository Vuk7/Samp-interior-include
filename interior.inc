/*
================================================================================
--------------------------------------------------------------------------------
						Interior include
		   	      				  by Vuk
						||English version||
--------------------------------------------------------------------------------
Default max interior is 50.
Need to set ResetPlayerInterior(playerid); in OnPlayerConnect!
If you need more than 50 interieors above #include <a_samp> type #define MAX_INTERIORS_CHANGE enter the number of required interiors
--------------------------------------------------------------------------------
Functions:
InteriorLP(id); - update interior's text label
CreateInterior(id,name[],Float:enterx,Float:entery,Float:enterz,Float:enteraz,Float:exitx,Float:exity,Float:exitz,Float:exitaz,interiorin,vwin,interiorout,vwout) - create interior
PortPlayerInInterior(playerid,interiorid); - port player in interior
PortPlayerOutOfInterior(playerid,interiorid); - port player out of interior
GetPlayerInteriorID(playerid); - return player's interior id
IsPlayerInInterior(playerid); - return true if is player in interior, return false if player isn't in interior
DestroyInterior(id); - destroyng interior
ResetPlayerInterior(playerid); - reseting player interior id
ChangeInteriorName(interiorid,name[]); - change interiors name
IsInteriorExist(interiorid); - return true if interior exist, return false if interior do not exist
--------------------------------------------------------------------------------
Callbacks:
OnInteriorCreated(id,name[],Float:enterx,Float:entery,Float:enterz,Float:enteraz,Float:exitx,Float:exity,Float:exitz,Float:exitaz,interiorin,vwin,interiorout,vwout)
OnPlayerTryToEnterInInterior(playerid,interiorid) - If in this function reutrn 0 player will not enter in the interior
OnPlayerEnterInInterior(playerid,interiorid)
OnPlayerTryToExitInInterior(playerid,interiorid) - If in this function reutrn 0 player will not exit from the interior
OnPlayerExitFromInterior(playerid,interiorid)
OnInteriorsNameChanged(interiorid,name[])
--------------------------------------------------------------------------------
================================================================================
*/

#if defined _interior_included
  #endinput
#endif

#define _interior_included
#pragma library interior

#if defined MAX_INTERIORS_CHANGE
#define MAX_INTERIORS MAX_INTERIORS_CHANGE
#else
#define MAX_INTERIORS 50
#endif


#include <a_samp>

#define PRESSED(%0) \
	(((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))

forward OnInteriorCreated(id,name[],Float:enterx,Float:entery,Float:enterz,Float:enteraz,Float:exitx,Float:exity,Float:exitz,Float:exitaz,interiorin,vwin,interiorout,vwout);
forward OnPlayerTryToEnterInInterior(playerid,interiorid);
forward OnPlayerEnterInInterior(playerid,interiorid);
forward OnPlayerTryToExitInInterior(playerid,interiorid);
forward OnPlayerExitFromInterior(playerid,interiorid);
forward OnInteriorDestroyed(interiorid);
forward OnInteriorsNameChanged(interiorid,name[]);

enum iInfo
{
	iID,
	iName[24],
	Float:iX,
	Float:iY,
	Float:iZ,
	Float:iAZ,
	Float:iXX,
	Float:iYY,
	Float:iZZ,
	Float:iAZZ,
	iInteriorIn,
	iVWIN,
	iInterorOut,
	iVWOUT,
	iUsing,
	iPickup,
	iPickupp
}
new InteriorInfo[MAX_INTERIORS][iInfo];
new Text3D:iText[MAX_INTERIORS];
new InInterior[MAX_PLAYERS]=-1;

stock InteriorLP(id)
{
	new str[200];
 	format(str,sizeof(str),"[ %s ]",InteriorInfo[id][iName]);
	Update3DTextLabelText(iText[id], -1, str);
	return 1;
}

stock CreateInterior(id,name[],Float:enterx,Float:entery,Float:enterz,Float:enteraz,Float:exitx,Float:exity,Float:exitz,Float:exitaz,interiorin,vwin,interiorout,vwout)
{
	if(id > MAX_INTERIORS)
	{
		print("[ERROR]");
		printf("Interior %d was not created because id is bigger of max interiors!",id);
		return -1;
	}
	if(InteriorInfo[id][iUsing] == 1)
	{
		print("[ERROR]");
		printf("Interior %d was not created because alredy exist interior with this id!",id);
		return -1;
	}
	strmid(InteriorInfo[id][iName], name, 0, strlen(name), 24);
	InteriorInfo[id][iID] = id;
	InteriorInfo[id][iX] = enterx;
    InteriorInfo[id][iY] = entery;
    InteriorInfo[id][iZ] = enterz;
    InteriorInfo[id][iAZ] = enteraz;
    InteriorInfo[id][iXX] = exitx;
    InteriorInfo[id][iYY] = exity;
    InteriorInfo[id][iZZ] = exitz;
    InteriorInfo[id][iAZZ] = exitaz;
    InteriorInfo[id][iInteriorIn] = interiorin;
    InteriorInfo[id][iVWIN] = vwin;
    InteriorInfo[id][iInterorOut] = interiorout;
    InteriorInfo[id][iVWOUT] = interiorout;
    InteriorInfo[id][iUsing] = 1;
    iText[id] = Create3DTextLabel("Created", -1,InteriorInfo[id][iX], InteriorInfo[id][iY], InteriorInfo[id][iZ], 20.0, InteriorInfo[id][iVWIN], 1);
	InteriorLP(id);
	InteriorInfo[id][iPickup] = CreatePickup(1239, 1, InteriorInfo[id][iX], InteriorInfo[id][iY], InteriorInfo[id][iZ], InteriorInfo[id][iVWIN]);
	InteriorInfo[id][iPickupp] = CreatePickup(1239, 1, InteriorInfo[id][iXX], InteriorInfo[id][iYY], InteriorInfo[id][iZZ], InteriorInfo[id][iVWOUT]);
	//OnInteriorCreated(id,name[],Float:enterx,Float:entery,Float:enterz,Float:enteraz,Float:exitx,Float:exity,Float:exitz,Float:exitaz,interiorin,vwin,interiorout,vwout);
    CallLocalFunction("OnInteriorCreated", "dsffffffffdddd", id,name,enterx,entery,enterz,enteraz,exitx,exity,exitz,exitaz,interiorin,vwin,interiorout,vwout);
	return id;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(PRESSED(KEY_SECONDARY_ATTACK))
	{
		if(!IsPlayerInAnyVehicle(playerid))
		{
			for(new i=0;i<MAX_INTERIORS;i++)
			{
			    if(InteriorInfo[i][iUsing] == 1)
			    {
			        if(!IsPlayerInInterior(playerid))
			        {
						if(IsPlayerInRangeOfPoint(playerid,2.0,InteriorInfo[i][iX], InteriorInfo[i][iY], InteriorInfo[i][iZ]))
						{
						    //OnPlayerTryToEnterInInterior(playerid,InteriorInfo[i][iID]);
							new rt;
							rt = CallLocalFunction("OnPlayerTryToEnterInInterior", "dd",playerid,InteriorInfo[i][iID]);
							if(rt == 0) return 1;
							PortPlayerInInterior(playerid,InteriorInfo[i][iID]);
	                        //OnPlayerEnterInInterior(playerid,InteriorInfo[i][iID]);
	                        CallLocalFunction("OnPlayerEnterInInterior", "dd",playerid,InteriorInfo[i][iID]);
						}
					}
					else if(IsPlayerInInterior(playerid))
					{
					    if(IsPlayerInRangeOfPoint(playerid,2.0,InteriorInfo[i][iXX], InteriorInfo[i][iYY], InteriorInfo[i][iZZ]))
						{
						    //OnPlayerTryToExitInInterior(playerid,InteriorInfo[i][iID]);
						    new rtt;
						    rtt = CallLocalFunction("OnPlayerTryToExitInInterior", "dd",playerid,InteriorInfo[i][iID]);
							if(rtt == 0) return 1;
							PortPlayerOutOfInterior(playerid,GetPlayerInteriorID(playerid));
						    //OnPlayerExitFromInterior(playerid,InteriorInfo[i][iID]);
						    CallLocalFunction("OnPlayerExitFromInterior", "dd",playerid,InteriorInfo[i][iID]);
						}
					}
			    }
			}
		}
	}
	return 1;
}

stock PortPlayerInInterior(playerid,interiorid)
{
	SetPlayerPos(playerid,InteriorInfo[interiorid][iXX],InteriorInfo[interiorid][iYY],InteriorInfo[interiorid][iZZ]);
	SetPlayerFacingAngle(playerid,InteriorInfo[interiorid][iAZZ]);
	SetPlayerVirtualWorld(playerid,InteriorInfo[interiorid][iVWOUT]);
	SetPlayerInterior(playerid,InteriorInfo[interiorid][iInterorOut]);
	InInterior[playerid]=interiorid;
	return 1;
}

stock PortPlayerOutOfInterior(playerid,interiorid)
{
	SetPlayerPos(playerid,InteriorInfo[interiorid][iX],InteriorInfo[interiorid][iY],InteriorInfo[interiorid][iZ]);
	SetPlayerFacingAngle(playerid,InteriorInfo[interiorid][iAZ]);
	SetPlayerVirtualWorld(playerid,InteriorInfo[interiorid][iVWIN]);
	SetPlayerInterior(playerid,InteriorInfo[interiorid][iInteriorIn]);
	InInterior[playerid]=-1;
	return 1;
}

stock GetPlayerInteriorID(playerid) return InInterior[playerid];

stock IsPlayerInInterior(playerid) { if(GetPlayerInteriorID(playerid) == -1) { return false; } else { return true; } }

stock DestroyInterior(id)
{
	if(InteriorInfo[id][iUsing] == 0)
	{
		print("[ERROR]");
		printf("Interior %d do not exist!",id);
		return -1;
	}
	strmid(InteriorInfo[id][iName], "Destroyed", 0, strlen("Destroyed"), 24);
    InteriorInfo[id][iX] = 0.0;
    InteriorInfo[id][iY] = 0.0;
    InteriorInfo[id][iZ] = 0.0;
    InteriorInfo[id][iAZ] = 0.0;
    InteriorInfo[id][iXX] = 0.0;
    InteriorInfo[id][iYY] = 0.0;
    InteriorInfo[id][iZZ] = 0.0;
    InteriorInfo[id][iAZZ] = 0.0;
    InteriorInfo[id][iInteriorIn] = 0;
    InteriorInfo[id][iVWIN] = 0;
    InteriorInfo[id][iInterorOut] = 0;
    InteriorInfo[id][iVWOUT] = 0;
    InteriorInfo[id][iUsing] = 0;
    Delete3DTextLabel(iText[id]);
	DestroyPickup(InteriorInfo[id][iPickup]);
	DestroyPickup(InteriorInfo[id][iPickupp]);
	printf("Interior %d destroyed!",id);
	//OnInteriorDestroyed(id);
	CallLocalFunction("OnInteriorDestroyed", "d",id);
	return 1;
}

stock ResetPlayerInterior(playerid) return InInterior[playerid]=-1;

stock ChangeInteriorName(interiorid,name[])
{
	strmid(InteriorInfo[interiorid][iName], name, 0, strlen(name), 24);
	InteriorLP(interiorid);
	CallLocalFunction("OnInteriorsNameChanged","ds",interiorid,name);
	return 1;
}

stock IsInteriorExist(interiorid) { if(InteriorInfo[interiorid][iUsing] == 0) { return false; } else { return true; } }