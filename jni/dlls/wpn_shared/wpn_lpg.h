#ifndef WPN_HEGRENADE_H
#define WPN_HEGRENADE_H
#ifdef _WIN32
#pragma once
#endif

//hegrenade
#define HEGRENADE_MAX_SPEED		200
#define HEGRENADE_MAX_SPEED_SHIELD	180

class CLPG : public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL CanDeploy();
	virtual BOOL CanDrop() { return FALSE; }
	virtual BOOL CanHolster();
	virtual BOOL Deploy();
	virtual void Holster(int skiplocal);
	float GetMaxSpeed() override { return KNIFE_SPEED; }
	virtual int iItemSlot() { return GRENADE_SLOT; }
	virtual void PrimaryAttack();
void QuickDeploy() override;
virtual void SecondaryAttack();

	virtual void WeaponIdle();
	virtual BOOL UseDecrement()
	{
#ifdef CLIENT_WEAPONS
		return TRUE;
#else
		return FALSE;
#endif
	}

public:
	bool ShieldSecondaryFire(int iUpAnim, int iDownAnim);
	void SetPlayerShieldAnim();
	void ResetPlayerShieldAnim();

public:
	unsigned short m_usCreateExplosion;
};
#endif
