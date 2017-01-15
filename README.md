# Samp-interior-include
With this include you can simple creating interiors.
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
