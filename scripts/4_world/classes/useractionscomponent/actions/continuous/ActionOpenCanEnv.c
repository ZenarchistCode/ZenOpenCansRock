class ActionOpenCanEnvCB : ActionContinuousBaseCB
{
	private const float TIME_TO_CRAFT = 5;

	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(TIME_TO_CRAFT);
	}
};

class ActionOpenCanEnv : ActionContinuousBase
{
	const static float MIN_LOSS = 0.5;
	const static float MAX_LOSS = 0.8;

	void ActionOpenCanEnv()
	{
		m_CallbackClass = ActionOpenCanEnvCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_ASSEMBLE;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT;
		m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_HIGH;
		m_Text = "#STR_OpenCan0";
	}

	override void CreateConditionComponents()
	{
		m_ConditionTarget = new CCTCursor(UAMaxDistances.DEFAULT);
		m_ConditionItem = new CCINonRuined;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		// Action not allowed if player has broken legs
		if (player.GetBrokenLegs() == eBrokenLegs.BROKEN_LEGS)
			return false;

		Object targetObject = target.GetObject();
		return targetObject.IsRock();
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		float loss = Math.RandomFloatInclusive(MIN_LOSS, MAX_LOSS);
		action_data.m_MainItem.SetHealth(1);
		OpenItem.SwitchItems(action_data.m_MainItem, action_data.m_Player, loss, m_SpecialtyWeight);
	}

	override void OnStartAnimationLoop( ActionData action_data )
	{
		super.OnStartAnimationLoop( action_data );

		if ( !GetGame().IsMultiplayer() || GetGame().IsServer() )
		{
			Param2<bool, string> play = new Param2<bool, string>( true, "minePickAxe_SoundSet" );
			GetGame().RPCSingleParam( action_data.m_MainItem, ERPCs.RPC_SOUND_LOCK_ATTACH, play, true );
		}
	}
	
	override void OnEnd( ActionData action_data )
	{
		if ( !GetGame().IsMultiplayer() || GetGame().IsServer() )
		{
			Param2<bool, string> play = new Param2<bool, string>( false, "minePickAxe_SoundSet" );
			GetGame().RPCSingleParam( action_data.m_MainItem, ERPCs.RPC_SOUND_LOCK_ATTACH, play, true );
		}
	}
	
	override void OnEndAnimationLoop( ActionData action_data )
	{
		if ( !GetGame().IsMultiplayer() || GetGame().IsServer() )
		{
			Param2<bool, string> play = new Param2<bool, string>( false, "minePickAxe_SoundSet" );
			GetGame().RPCSingleParam( action_data.m_MainItem, ERPCs.RPC_SOUND_LOCK_ATTACH, play, true );
		}
	}
};
