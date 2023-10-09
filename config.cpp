class CfgPatches
{
	class ZenOpenCansRock
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[] = { "DZ_Data" };
	};
};

class CfgMods
{
	class ZenOpenCansRock
	{
		dir="ZenOpenCansRock";
		picture=""; 
		action="";
		hideName=1;
		hidePicture=1;
		name="Open Cans On Rocks";
		credits=""; 
		author="Zenarchist";
		authorID="0";  
		version="1.0";
		extra=0;
		type="mod";
		dependencies[] =
		{
			"Game",
			"World",
			"Mission"
		};
		class defs
		{
			class worldScriptModule
			{
				value = "";
				files[] = { "ZenOpenCansRock/scripts/4_world" };
			};
		}
	};
};

class CfgVehicles
{
	class Inventory_Base;
	class SmallStone : Inventory_Base
	{
		openItemSpillRange[] = { 50,75 };
	};
	class Stone : Inventory_Base
	{
		openItemSpillRange[] = { 70,90 };
	};
}