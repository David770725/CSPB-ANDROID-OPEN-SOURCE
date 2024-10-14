#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "player.h"
#include "weapons.h"
#include "wpn_kriss_sv_dual_silence.h"

//kriss silencer dual

enum scar_e
{
	
	SCARH_IDLE1,
	SCARH_RELOAD,
	SCARH_DRAW,
	SCARH_SHOOT1,
	SCARH_SHOOT2,
	SCARH_SHOOT3,
	CHANGE_SCARH, //dualoff
ANIM1,
ANIM2,
ANIM3,
ANIM4,
ANIM5
};


LINK_ENTITY_TO_CLASS(weapon_kriss_sv_dual_silence, CKriss_sv_dual_silence)

const int KSILENCER_AMMO = 80;

void CKriss_sv_dual_silence::Spawn(void)
{
	pev->classname = MAKE_STRING("weapon_kriss_sv_dual_silence");

	Precache();
	m_iId = WEAPON_SG550;
	SET_MODEL(ENT(pev), "models/w_scar.mdl");

	m_iDefaultAmmo = KSILENCER_AMMO;
	m_flAccuracy = 0.2;
	m_iShotsFired = 0;

	FallInit();

	m_pLink = nullptr;
	m_iSwing = 0;
}

#ifndef CLIENT_DLL
void CKriss_sv_dual_silence::AttachToPlayer(CBasePlayer *pPlayer)
{
	CBasePlayerWeapon::AttachToPlayer(pPlayer);

	// find the linked weapon
	while (!m_pLink)
	{
		for (int i = 0; i < MAX_ITEM_TYPES; ++i)
		{
			CBasePlayerItem *pItem = m_pPlayer->m_rgpPlayerItems[i];
			while (pItem != NULL)
			{
				if (!Q_stricmp(pItem->pszName(), "weapon_kriss_sv_silence"))
				{
					m_pLink = pItem;

					m_pLink->m_iSwing = 1;
					m_iSwing = 0;
				}

				pItem = pItem->m_pNext;
			}
		}
		if (!m_pLink)
			pPlayer->GiveNamedItem("weapon_kriss_sv_silence");

pPlayer->GiveNamedItem("weapon_kriss_sv_silence");

	}
}


void CKriss_sv_dual_silence::ItemPostFrame()
{
	m_iSwing = 0;
	if (m_pLink)
		m_pLink->m_iSwing = 1;
	return CBasePlayerWeapon::ItemPostFrame();
}

CKriss_sv_dual_silence::~CKriss_sv_dual_silence()
{
	CBaseEntity *pOther = m_pLink;
	if (pOther && pOther->m_pLink == this)
	{
		pOther->m_pLink = m_pLink = nullptr;
		pOther->SUB_Remove();
	}
}
#endif

void CKriss_sv_dual_silence::Precache(void)
{
	
PRECACHE_MODEL("models/billflx/v_kriss_sv_silence_2.mdl");

	PRECACHE_MODEL("models/p_kriss_sv_silence_2.mdl");
	

	PRECACHE_SOUND("weapons/kriss_sv_silence-1.wav");
	PRECACHE_SOUND("weapons/scar_l.wav");

	m_iShell = PRECACHE_MODEL("models/rshell.mdl");
	m_usFireKriss_sv_dual_silence = PRECACHE_EVENT(1, "events/ak47.sc");
}

int CKriss_sv_dual_silence::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "45acp";
	p->iMaxAmmo1 = MAX_AMMO_45ACP;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = KSILENCER_AMMO;
	p->iSlot = 0;
	p->iPosition = 18;
	p->iId = WEAPON_SG550;
	p->iFlags = 0;
	p->iWeight = 20;

	return 1;
}

BOOL CKriss_sv_dual_silence::Deploy(void)
{

	if (m_iSwing)
	{
		
DefaultDeploy("models/billflx/v_kriss_sv_silence_2.mdl", "models/p_kriss_sv_silence_2.mdl", SCARH_DRAW, "dualpistols", 0);

	}
	else
	{
		
DefaultDeploy("models/billflx/v_kriss_sv_silence_2.mdl", "models/p_kriss_sv_silence_2.mdl", SCARH_DRAW, "dualpistols", 0);

	}

	return TRUE;
}

void CKriss_sv_dual_silence::QuickDeploy()
{
SendWeaponAnim(ANIM1, 0);
m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.3;
m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}

void CKriss_sv_dual_silence::PrimaryAttack(void)
{
	
		Kriss_sv_dual_silenceFire((0.0275), 0.057, FALSE);


if (m_iClip > 0)
{
SendWeaponAnim(SCARH_SHOOT1, 0);
}
else if (m_iClip == 0)
{
SendWeaponAnim(SCARH_IDLE1, 0);
}

}

void CKriss_sv_dual_silence::Kriss_sv_dual_silenceFire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
{
	m_bDelayFire = true;
	m_iShotsFired++;
	m_flAccuracy = ((float)(m_iShotsFired * m_iShotsFired * m_iShotsFired) / 200.0) + 0.35;

	if (m_flAccuracy > 1.25)
		m_flAccuracy = 1.25;

	if (m_iClip <= 0)
	{
		if (m_fFireOnEmpty)
		{
			PlayEmptySound();
			m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.2;
		}

		return;
	}

	m_iClip--;
	m_pPlayer->pev->effects |= EF_MUZZLEFLASH;
#ifndef CLIENT_DLL
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);
#endif
	UTIL_MakeVectors(m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle);
	Vector vecSrc = m_pPlayer->GetGunPosition();
	Vector vecDir = m_pPlayer->FireBullets3(vecSrc, gpGlobals->v_forward, flSpread, 8192, 2, BULLET_PLAYER_762MM, 20, 0.96, m_pPlayer->pev, FALSE, m_pPlayer->random_seed);

	int flags;
#ifdef CLIENT_WEAPONS
	flags = FEV_NOTHOST;
#else
	flags = 0;
#endif

EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/kriss_sv_silence-1.wav", VOL_NORM, ATTN_NORM);


	PLAYBACK_EVENT_FULL(flags, m_pPlayer->edict(),m_usFireKriss_sv_dual_silence, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y, (int)(m_pPlayer->pev->punchangle.x * 100), (int)(m_pPlayer->pev->punchangle.y * 100), FALSE, FALSE);

	m_pPlayer->m_iWeaponVolume = NORMAL_GUN_VOLUME;
	m_pPlayer->m_iWeaponFlash = BRIGHT_GUN_FLASH;
	m_flNextPrimaryAttack = m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + flCycleTime;

#ifndef CLIENT_DLL
	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);
#endif
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 1.9;

	m_pPlayer->pev->punchangle.x -= UTIL_SharedRandomFloat(m_pPlayer->random_seed + 1, 0.5, 0.75) + m_pPlayer->pev->punchangle.x * 0.25;
	m_pPlayer->pev->punchangle.y += UTIL_SharedRandomFloat(m_pPlayer->random_seed + 2, -1.0, 0.2);
}

float CKriss_sv_dual_silence::GetDamage()
{
	return 39;
}


void CKriss_sv_dual_silence::WeaponIdle(void)
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
		return;

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 20;
	SendWeaponAnim(SCARH_IDLE1, UseDecrement() != FALSE);
}

//41
