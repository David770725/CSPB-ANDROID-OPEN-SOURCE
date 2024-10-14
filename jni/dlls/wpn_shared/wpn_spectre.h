#ifndef WPN_M4A1_H
#define WPN_M4A1_H
#ifdef _WIN32
#pragma once
#endif

//m4a1
#define M4A1_MAX_SPEED		190
#define M4A1_DAMAGE		32
#define M4A1_DAMAGE_SIL		33
#define M4A1_RANGE_MODIFER      0.97
#define M4A1_RANGE_MODIFER_SIL  0.95
#define M4A1_RELOAD_TIME	3.05

class CSPECTRE : public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	virtual float GetMaxSpeed() { return M4A1_MAX_SPEED; }
	virtual int iItemSlot() { return PRIMARY_WEAPON_SLOT; }
	virtual void PrimaryAttack();
void QuickDeploy() override;



void QuickReload() override;
void Fov2();
void Fov3();
void Fov4();
void Fov5();
void Fov6();


void offFov2();
void offFov3();
void offFov4();
void offFov5();
void offFov6();

	void SecondaryAttack() override;
	virtual void Reload();
void ResetRunIdle();
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
	void M4A1Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim);

	int m_iShell;
	int iShellOn;
int m_iSprBeam;
bool m_bOnZoom = false;

private:
	unsigned short m_usFireM4A1;
};
#endif
