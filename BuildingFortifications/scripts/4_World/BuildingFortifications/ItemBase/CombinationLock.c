
modded class CombinationLock
{
	// DayZRP fork: a BF barricade takes the lock off itself. DayZ 1.30 replaced the
	// vanilla UnlockServer with UnlockOnServer, so both versions route through here.
	protected bool BF_UnlockFromBarricade( EntityAI player, EntityAI parent )
	{
		if ( !BF_DoorBarricade.Cast( parent ) && !BF_DoubleDoorBarricade.Cast( parent ) )
			return false;

		if ( IsLockAttached() )
		{
			InventoryLocation inventory_location = new InventoryLocation;
			GetInventory().GetCurrentInventoryLocation( inventory_location );
			parent.GetInventory().SetSlotLock( inventory_location.GetSlot(), false );

			if (player)
			{
				player.ServerDropEntity( this );
				SetPosition( player.GetPosition() );
			}
			else
				parent.GetInventory().DropEntity(InventoryMode.SERVER, parent, this);
			PlaceOnSurface();

			m_LockActionPerformed = LockAction.UNLOCKED;
			SetTakeable(true);
			CheckLockedStateServer();
			Synchronize();
		}
		return true;
	}

#ifdef DAYZ_1_30
	override void UnlockOnServer( EntityAI player, EntityAI parent, bool isInsideLock = false )
	{
		if ( !BF_UnlockFromBarricade( player, parent ) )
			super.UnlockOnServer( player, parent, isInsideLock );
	}

	// Removed from vanilla in 1.30; the barricades and actions here still call it.
	void UnlockServer( EntityAI player, EntityAI parent )
	{
		UnlockOnServer( player, parent );
	}
#else
	override void UnlockServer( EntityAI player, EntityAI parent )
	{
		if ( !BF_UnlockFromBarricade( player, parent ) )
			super.UnlockServer( player, parent );
	}
#endif

	override bool IsLockedOnGate()
	{
		BF_DoorBarricade BF_DB = BF_DoorBarricade.Cast( GetHierarchyParent() );
		BF_DoubleDoorBarricade BF_DDB = BF_DoubleDoorBarricade.Cast( GetHierarchyParent() );
		if (BF_DB || BF_DDB)
		{
			if ( IsLocked() )
			{
				return true;
			}
		};
		return super.IsLockedOnGate();
	}
 		
	override bool IsLockAttached()
	{
		
		BF_DoorBarricade BF_DB = BF_DoorBarricade.Cast( GetHierarchyParent() );
		BF_DoubleDoorBarricade BF_DDB = BF_DoubleDoorBarricade.Cast( GetHierarchyParent() );
		if (BF_DB || BF_DDB)
		{
			return true;
		}
		
		return super.IsLockAttached();
	} 
	
}
