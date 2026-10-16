modded class ActionNextCombinationLockDialOnTarget
{
#ifdef DAYZ_1_30
	// DayZRP fork: 1.30's Start() turns the dial of the side stored by
	// ActionCondition and does nothing while that side is -1. A BF barricade has
	// no per-side lock selections, so its lock is always dialled from outside,
	// as in ActionDialCombinationLockOnTarget; every other lock is vanilla's.
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (!target.GetObject())
			return false;

		CombinationLock lock = CombinationLock.Cast( target.GetObject() );
		if ( lock && BuildingFortficationsCore.Cast( lock.GetHierarchyParent() ) )
		{
			ConstructionActionData construction_action_data = player.GetConstructionActionData();
			construction_action_data.SetCombinationLock( lock );
			construction_action_data.SetCombinationLockSide( CombinationLock.FACING_OUTSIDE );
			return true;
		}
		return super.ActionCondition( player, target, item );
	}
#else
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (!target.GetObject())
			return false;

		CombinationLock lock = CombinationLock.Cast( target.GetObject() );
		if ( lock && lock.GetHierarchyParent() && Fence.Cast(lock.GetHierarchyParent()) || lock && lock.GetHierarchyParent() && BuildingFortficationsCore.Cast(lock.GetHierarchyParent()) )
		{
			ConstructionActionData construction_action_data = player.GetConstructionActionData();
			construction_action_data.SetCombinationLock( lock );

			return true;
		}

		return false;
	}
#endif
}
