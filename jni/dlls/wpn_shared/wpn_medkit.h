#ifndef WPN_medkit_H
#define WPN_medkit_H
#ifdef _WIN32
#pragma once
#endif

//medkit
#define medkit_MAX_SPEED		200
#define medkit_MAX_SPEED_SHIELD	180

enum molotov_e
    {
        MOLLY_IDLE,
        MOLLY_PINPULL,
        MOLLY_THROW,
        MOLLY_DRAW,
MOLLY_UNDERHAND
    };

//med
class CMedkit : public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL CanDeploy();
	virtual BOOL CanDrop() { return FALSE; }
	virtual BOOL Deploy();
	virtual void Holster(int skiplocal);
	virtual float GetMaxSpeed() { return m_fMaxSpeed; }
	virtual int iItemSlot() { return GRENADE_SLOT; }
	const char* GetCSModelName() override { return "models/w_medkit.mdl"; }

	virtual void PrimaryAttack();
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
bool throw2 = FALSE;
unsigned short m_usCreateMedkit;
};


#endif
