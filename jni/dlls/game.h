/*
*
*   This program is free software; you can redistribute it and/or modify it
*   under the terms of the GNU General Public License as published by the
*   Free Software Foundation; either version 2 of the License, or (at
*   your option) any later version.
*
*   This program is distributed in the hope that it will be useful, but
*   WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*   General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program; if not, write to the Free Software Foundation,
*   Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*   In addition, as a special exception, the author gives permission to
*   link the code of this program with the Half-Life Game Engine ("HL
*   Engine") and Modified Game Libraries ("MODs") developed by Valve,
*   L.L.C ("Valve").  You must obey the GNU General Public License in all
*   respects for all of the code used other than the HL Engine and MODs
*   from Valve.  If you modify this file, you may extend this exception
*   to your version of the file, but you are not obligated to do so.  If
*   you do not wish to do so, delete this exception statement from your
*   version.
*
*/

#ifndef GAME_H
#define GAME_H
#ifdef _WIN32
#pragma once
#endif

#define LOG_ENEMYATTACK		1
#define LOG_TEAMMATEATTACK	2

// playerid
#define PLAYERID_MODE_EVERYONE	0
#define PLAYERID_MODE_TEAMONLY	1
#define PLAYERID_MODE_OFF	2

#define PLAYERID_EVERYONE 0
#define PLAYERID_TEAMONLY 1
#define PLAYERID_OFF 2

extern cvar_t *g_psv_gravity;
extern cvar_t *g_psv_aim;
extern cvar_t *g_footsteps;
extern cvar_t *g_psv_accelerate;
extern cvar_t *g_psv_friction;
extern cvar_t *g_psv_stopspeed;

extern cvar_t displaysoundlist;
extern cvar_t timelimit;
extern cvar_t flashlight;
extern cvar_t decalfrequency;
extern cvar_t fadetoblack;
extern cvar_t fragsleft;
extern cvar_t timeleft;
extern cvar_t friendlyfire;
extern cvar_t allowmonsters;
extern cvar_t roundtime;
extern cvar_t buytime;
extern cvar_t freezetime;
extern cvar_t c4timer;
extern cvar_t ghostfrequency;
extern cvar_t autokick;
extern cvar_t autokick_timeout;
extern cvar_t restartround;
extern cvar_t sv_restart;
extern cvar_t limitteams;
extern cvar_t autoteambalance;
extern cvar_t tkpunish;
extern cvar_t hostagepenalty;
extern cvar_t mirrordamage;
extern cvar_t logmessages;
extern cvar_t forcecamera;
extern cvar_t forcechasecam;
extern cvar_t mapvoteratio;
extern cvar_t logdetail;
extern cvar_t startmoney;
extern cvar_t maxrounds;
extern cvar_t winlimit;
extern cvar_t windifference;
extern cvar_t playerid;
extern cvar_t allow_spectators;
extern cvar_t mp_chattime;
extern cvar_t kick_percent;
extern cvar_t humans_join_team;
extern cvar_t sk_plr_9mm_bullet1;
extern cvar_t sk_plr_9mm_bullet2;
extern cvar_t sk_plr_9mm_bullet3;
extern cvar_t sk_plr_357_bullet1;
extern cvar_t sk_plr_357_bullet2;
extern cvar_t sk_plr_357_bullet3;
extern cvar_t sk_plr_9mmAR_bullet1;
extern cvar_t sk_plr_9mmAR_bullet2;
extern cvar_t sk_plr_9mmAR_bullet3;
extern cvar_t sk_plr_9mmAR_grenade1;
extern cvar_t sk_plr_9mmAR_grenade2;
extern cvar_t sk_plr_9mmAR_grenade3;
extern cvar_t sk_plr_buckshot1;
extern cvar_t sk_plr_buckshot2;
extern cvar_t sk_plr_buckshot3;
extern cvar_t sk_plr_rpg1;
extern cvar_t sk_plr_rpg2;
extern cvar_t sk_plr_rpg3;
extern cvar_t sk_12mm_bullet1;
extern cvar_t sk_12mm_bullet2;
extern cvar_t sk_12mm_bullet3;
extern cvar_t sk_9mmAR_bullet1;
extern cvar_t sk_9mmAR_bullet2;
extern cvar_t sk_9mmAR_bullet3;
extern cvar_t sk_9mm_bullet1;
extern cvar_t sk_9mm_bullet2;
extern cvar_t sk_9mm_bullet3;
extern cvar_t sk_suitcharger1;
extern cvar_t sk_suitcharger2;
extern cvar_t sk_suitcharger3;
extern cvar_t sk_battery1;
extern cvar_t sk_battery2;
extern cvar_t sk_battery3;
extern cvar_t sk_healthcharger1;
extern cvar_t sk_healthcharger2;
extern cvar_t sk_healthcharger3;
extern cvar_t sk_healthkit1;
extern cvar_t sk_healthkit2;
extern cvar_t sk_healthkit3;
extern cvar_t sk_scientist_heal1;
extern cvar_t sk_scientist_heal2;
extern cvar_t sk_scientist_heal3;

extern cvar_t gamemode;
extern cvar_t maxkills;
/*
extern cvar_t inventory_primary;
extern cvar_t inventory_secondary;
extern cvar_t inventor_melee;
extern cvar_t inventory_explosive;
extern cvar_t inventory_special;*/

extern cvar_t sv_unlimited_reserve_ammo;

///weapons damage
extern cvar_t weapon_damage_game_ak47;
extern cvar_t weapon_damage_game_aksopmod;
extern cvar_t weapon_damage_game_aug_hbar;
extern cvar_t weapon_damage_game_aug;
extern cvar_t weapon_damage_game_augblitz;
extern cvar_t weapon_damage_game_p90;
extern cvar_t weapon_damage_game_aug_a3_silencer;
extern cvar_t weapon_damage_game_f2000;
extern cvar_t weapon_damage_game_famas_g2;
extern cvar_t weapon_damage_game_g36c;
extern cvar_t weapon_damage_game_k1;
extern cvar_t weapon_damage_game_k2;
extern cvar_t weapon_damage_game_kriss_sv;
extern cvar_t weapon_damage_game_kriss_sv_dual;
extern cvar_t weapon_damage_game_kriss_sv_silencer;
extern cvar_t weapon_damage_game_kriss_sv_silencer_dual;
extern cvar_t weapon_damage_game_m4_cqb_lv1;
extern cvar_t weapon_damage_game_m4_cqb_lv2;
extern cvar_t weapon_damage_game_m4a1;
extern cvar_t weapon_damage_game_m4a1_s;
extern cvar_t weapon_damage_game_mp7;
extern cvar_t weapon_damage_game_oa93;
extern cvar_t weapon_damage_game_oa93_dual;
extern cvar_t weapon_damage_game_p90_mc;
extern cvar_t weapon_damage_game_pindad_ss2_v5;
extern cvar_t weapon_damage_game_groza;
extern cvar_t weapon_damage_game_sc2010;
extern cvar_t weapon_damage_game_scar_carbine;
extern cvar_t weapon_damage_game_kriss_sv_crb;
extern cvar_t weapon_damage_game_kriss_sv_crb_dual;
extern cvar_t weapon_damage_game_mp5k;
extern cvar_t weapon_damage_game_m4_azure;
extern cvar_t weapon_damage_game_mp9;
extern cvar_t weapon_damage_game_sg550;
extern cvar_t weapon_damage_game_l115a1;
extern cvar_t weapon_damage_game_cheytac_m200;
extern cvar_t weapon_damage_game_dragunov;
extern cvar_t weapon_damage_game_kar98k;
extern cvar_t weapon_damage_game_rangemaster_338;
extern cvar_t weapon_damage_game_m82a1;
extern cvar_t weapon_damage_game_tactilite_t2;
extern cvar_t weapon_damage_game_ssg69;
extern cvar_t weapon_damage_game_m4_spr_lv1;
extern cvar_t weapon_damage_game_m4_spr_lv2;
extern cvar_t weapon_damage_game_m1887;
extern cvar_t weapon_damage_game_spas_15;
extern cvar_t weapon_damage_game_zombie_s;
extern cvar_t weapon_damage_game_870mcs;
extern cvar_t weapon_damage_game_ak_sopmod_cg;
extern cvar_t weapon_damage_game_aug_esport;
extern cvar_t weapon_damage_game_t77;
extern cvar_t weapon_damage_game_apc;
extern cvar_t weapon_damage_game_fg42;
extern cvar_t weapon_damage_game_msbs;
extern cvar_t weapon_damage_game_as50;
extern cvar_t weapon_damage_game_m1887_w;
extern cvar_t weapon_damage_game_pgm;
extern cvar_t weapon_damage_game_ump;
extern cvar_t weapon_damage_game_sig;
extern cvar_t weapon_damage_game_spectre;
extern cvar_t weapon_damage_game_tar;
extern cvar_t weapon_damage_game_xm8;
extern cvar_t weapon_damage_game_water_gun;//
extern cvar_t weapon_damage_game_colt_python;
extern cvar_t weapon_damage_game_deagle_dual;
extern cvar_t weapon_damage_game_dual_handgun;
extern cvar_t weapon_damage_game_raging_bull;
extern cvar_t weapon_damage_game_deagle;
extern cvar_t weapon_damage_game_k5;
extern cvar_t weapon_damage_game_glock;

//draw
extern cvar_t weapon_draw_time_ak47;
extern cvar_t weapon_draw_time_aksopmod;
extern cvar_t weapon_draw_time_aug_hbar;
extern cvar_t weapon_draw_time_aug;
extern cvar_t weapon_draw_time_augblitz;
extern cvar_t weapon_draw_time_p90;
extern cvar_t weapon_draw_time_aug_a3_silencer;
extern cvar_t weapon_draw_time_f2000;
extern cvar_t weapon_draw_time_famas_g2;
extern cvar_t weapon_draw_time_g36c;
extern cvar_t weapon_draw_time_k1;
extern cvar_t weapon_draw_time_k2;
extern cvar_t weapon_draw_time_kriss_sv;
extern cvar_t weapon_draw_time_kriss_sv_dual;
extern cvar_t weapon_draw_time_kriss_sv_silencer;
extern cvar_t weapon_draw_time_kriss_sv_silencer_dual;
extern cvar_t weapon_draw_time_m4_cqb_lv1;
extern cvar_t weapon_draw_time_m4_cqb_lv2;
extern cvar_t weapon_draw_time_m4a1;
extern cvar_t weapon_draw_time_m4a1_s;
extern cvar_t weapon_draw_time_mp7;
extern cvar_t weapon_draw_time_oa93;
extern cvar_t weapon_draw_time_oa93_dual;
extern cvar_t weapon_draw_time_p90_mc;
extern cvar_t weapon_draw_time_pindad_ss2_v5;
extern cvar_t weapon_draw_time_groza;
extern cvar_t weapon_draw_time_sc2010;
extern cvar_t weapon_draw_time_scar_carbine;
extern cvar_t weapon_draw_time_kriss_sv_crb;
extern cvar_t weapon_draw_time_kriss_sv_crb_dual;
extern cvar_t weapon_draw_time_mp5k;
extern cvar_t weapon_draw_time_m4_azure;
extern cvar_t weapon_draw_time_mp9;
extern cvar_t weapon_draw_time_sg550;
extern cvar_t weapon_draw_time_l115a1;
extern cvar_t weapon_draw_time_cheytac_m200;
extern cvar_t weapon_draw_time_dragunov;
extern cvar_t weapon_draw_time_kar98k;
extern cvar_t weapon_draw_time_rangemaster_338;
extern cvar_t weapon_draw_time_m82a1;
extern cvar_t weapon_draw_time_tactilite_t2;
extern cvar_t weapon_draw_time_ssg69;
extern cvar_t weapon_draw_time_m4_spr_lv1;
extern cvar_t weapon_draw_time_m4_spr_lv2;
extern cvar_t weapon_draw_time_m1887;
extern cvar_t weapon_draw_time_spas_15;
extern cvar_t weapon_draw_time_zombie_s;
extern cvar_t weapon_draw_time_870mcs;
extern cvar_t weapon_draw_time_ak_sopmod_cg;
extern cvar_t weapon_draw_time_aug_esport;
extern cvar_t weapon_draw_time_t77;
extern cvar_t weapon_draw_time_apc;
extern cvar_t weapon_draw_time_fg42;
extern cvar_t weapon_draw_time_msbs;
extern cvar_t weapon_draw_time_as50;
extern cvar_t weapon_draw_time_m1887_w;
extern cvar_t weapon_draw_time_pgm;
extern cvar_t weapon_draw_time_ump;
extern cvar_t weapon_draw_time_sig;
extern cvar_t weapon_draw_time_spectre;
extern cvar_t weapon_draw_time_tar;
extern cvar_t weapon_draw_time_xm8;
extern cvar_t weapon_draw_time_water_gun;//
extern cvar_t weapon_draw_time_colt_python;
extern cvar_t weapon_draw_time_deagle_dual;
extern cvar_t weapon_draw_time_dual_handgun;
extern cvar_t weapon_draw_time_raging_bull;
extern cvar_t weapon_draw_time_deagle;
extern cvar_t weapon_draw_time_k5;
extern cvar_t weapon_draw_time_glock;

//reload
extern cvar_t weapon_reload_time_ak47;
extern cvar_t weapon_reload_time_aksopmod;
extern cvar_t weapon_reload_time_aug_hbar;
extern cvar_t weapon_reload_time_aug;
extern cvar_t weapon_reload_time_augblitz;
extern cvar_t weapon_reload_time_p90;
extern cvar_t weapon_reload_time_aug_a3_silencer;
extern cvar_t weapon_reload_time_f2000;
extern cvar_t weapon_reload_time_famas_g2;
extern cvar_t weapon_reload_time_g36c;
extern cvar_t weapon_reload_time_k1;
extern cvar_t weapon_reload_time_k2;
extern cvar_t weapon_reload_time_kriss_sv;
extern cvar_t weapon_reload_time_kriss_sv_dual;
extern cvar_t weapon_reload_time_kriss_sv_silencer;
extern cvar_t weapon_reload_time_kriss_sv_silencer_dual;
extern cvar_t weapon_reload_time_m4_cqb_lv1;
extern cvar_t weapon_reload_time_m4_cqb_lv2;
extern cvar_t weapon_reload_time_m4a1;
extern cvar_t weapon_reload_time_m4a1_s;
extern cvar_t weapon_reload_time_mp7;
extern cvar_t weapon_reload_time_oa93;
extern cvar_t weapon_reload_time_oa93_dual;
extern cvar_t weapon_reload_time_p90_mc;
extern cvar_t weapon_reload_time_pindad_ss2_v5;
extern cvar_t weapon_reload_time_groza;
extern cvar_t weapon_reload_time_sc2010;
extern cvar_t weapon_reload_time_scar_carbine;
extern cvar_t weapon_reload_time_kriss_sv_crb;
extern cvar_t weapon_reload_time_kriss_sv_crb_dual;
extern cvar_t weapon_reload_time_mp5k;
extern cvar_t weapon_reload_time_m4_azure;
extern cvar_t weapon_reload_time_mp9;
extern cvar_t weapon_reload_time_sg550;
extern cvar_t weapon_reload_time_l115a1;
extern cvar_t weapon_reload_time_cheytac_m200;
extern cvar_t weapon_reload_time_dragunov;
extern cvar_t weapon_reload_time_kar98k;
extern cvar_t weapon_reload_time_rangemaster_338;
extern cvar_t weapon_reload_time_m82a1;
extern cvar_t weapon_reload_time_tactilite_t2;
extern cvar_t weapon_reload_time_ssg69;
extern cvar_t weapon_reload_time_m4_spr_lv1;
extern cvar_t weapon_reload_time_m4_spr_lv2;
extern cvar_t weapon_reload_time_m1887;
extern cvar_t weapon_reload_time_spas_15;
extern cvar_t weapon_reload_time_zombie_s;
extern cvar_t weapon_reload_time_870mcs;
extern cvar_t weapon_reload_time_ak_sopmod_cg;
extern cvar_t weapon_reload_time_aug_esport;
extern cvar_t weapon_reload_time_t77;
extern cvar_t weapon_reload_time_apc;
extern cvar_t weapon_reload_time_fg42;
extern cvar_t weapon_reload_time_msbs;
extern cvar_t weapon_reload_time_as50;
extern cvar_t weapon_reload_time_m1887_w;
extern cvar_t weapon_reload_time_pgm;
extern cvar_t weapon_reload_time_ump;
extern cvar_t weapon_reload_time_sig;
extern cvar_t weapon_reload_time_spectre;
extern cvar_t weapon_reload_time_tar;
extern cvar_t weapon_reload_time_xm8;
extern cvar_t weapon_reload_time_water_gun;//reload 
extern cvar_t weapon_reload_time_colt_python;
extern cvar_t weapon_reload_time_deagle_dual;
extern cvar_t weapon_reload_time_dual_handgun;
extern cvar_t weapon_reload_time_raging_bull;
extern cvar_t weapon_reload_time_deagle;
extern cvar_t weapon_reload_time_k5;
extern cvar_t weapon_reload_time_glock;

//TODO sight
extern cvar_t weapon_sight_ak47;
extern cvar_t weapon_sight_aksopmod;
extern cvar_t weapon_sight_aug_hbar;
extern cvar_t weapon_sight_aug;
extern cvar_t weapon_sight_augblitz;
extern cvar_t weapon_sight_p90;
extern cvar_t weapon_sight_aug_a3_silencer;
extern cvar_t weapon_sight_f2000;
extern cvar_t weapon_sight_famas_g2;
extern cvar_t weapon_sight_g36c;
extern cvar_t weapon_sight_k1;
extern cvar_t weapon_sight_k2;
extern cvar_t weapon_sight_kriss_sv;
extern cvar_t weapon_sight_kriss_sv_dual;
extern cvar_t weapon_sight_kriss_sv_silencer;
extern cvar_t weapon_sight_kriss_sv_silencer_dual;
extern cvar_t weapon_sight_m4_cqb_lv1;
extern cvar_t weapon_sight_m4_cqb_lv2;
extern cvar_t weapon_sight_m4a1;
extern cvar_t weapon_sight_m4a1_s;
extern cvar_t weapon_sight_mp7;
extern cvar_t weapon_sight_oa93;
extern cvar_t weapon_sight_oa93_dual;
extern cvar_t weapon_sight_p90_mc;
extern cvar_t weapon_sight_pindad_ss2_v5;
extern cvar_t weapon_sight_groza;
extern cvar_t weapon_sight_sc2010;
extern cvar_t weapon_sight_scar_carbine;
extern cvar_t weapon_sight_kriss_sv_crb;
extern cvar_t weapon_sight_kriss_sv_crb_dual;
extern cvar_t weapon_sight_mp5k;
extern cvar_t weapon_sight_m4_azure;
extern cvar_t weapon_sight_mp9;
extern cvar_t weapon_sight_sg550;
extern cvar_t weapon_sight_l115a1;
extern cvar_t weapon_sight_cheytac_m200;
extern cvar_t weapon_sight_dragunov;
extern cvar_t weapon_sight_kar98k;
extern cvar_t weapon_sight_rangemaster_338;
extern cvar_t weapon_sight_m82a1;
extern cvar_t weapon_sight_tactilite_t2;
extern cvar_t weapon_sight_ssg69;
extern cvar_t weapon_sight_m4_spr_lv1;
extern cvar_t weapon_sight_m4_spr_lv2;
extern cvar_t weapon_sight_m1887;
extern cvar_t weapon_sight_spas_15;
extern cvar_t weapon_sight_zombie_s;
extern cvar_t weapon_sight_870mcs;
extern cvar_t weapon_sight_ak_sopmod_cg;
extern cvar_t weapon_sight_aug_esport;
extern cvar_t weapon_sight_t77;
extern cvar_t weapon_sight_apc;
extern cvar_t weapon_sight_fg42;
extern cvar_t weapon_sight_msbs;
extern cvar_t weapon_sight_as50;
extern cvar_t weapon_sight_m1887_w;
extern cvar_t weapon_sight_pgm;
extern cvar_t weapon_sight_ump;
extern cvar_t weapon_sight_sig;
extern cvar_t weapon_sight_spectre;
extern cvar_t weapon_sight_tar;
extern cvar_t weapon_sight_xm8;
extern cvar_t weapon_sight_water_gun;
extern cvar_t weapon_sight_colt_python;//
extern cvar_t weapon_sight_deagle_dual;
extern cvar_t weapon_sight_dual_handgun;
extern cvar_t weapon_sight_raging_bull;
extern cvar_t weapon_sight_deagle;
extern cvar_t weapon_sight_k5;
extern cvar_t weapon_sight_glock;

extern cvar_t weapon_sound_ak47;
extern cvar_t weapon_sound_aksopmod;
extern cvar_t weapon_sound_aug_hbar;
extern cvar_t weapon_sound_aug;
extern cvar_t weapon_sound_augblitz;
extern cvar_t weapon_sound_p90;
extern cvar_t weapon_sound_aug_a3_silencer;
extern cvar_t weapon_sound_f2000;
extern cvar_t weapon_sound_famas_g2;
extern cvar_t weapon_sound_g36c;
extern cvar_t weapon_sound_k1;
extern cvar_t weapon_sound_k2;
extern cvar_t weapon_sound_kriss_sv;
extern cvar_t weapon_sound_kriss_sv_dual;
extern cvar_t weapon_sound_kriss_sv_silencer;
extern cvar_t weapon_sound_kriss_sv_silencer_dual;
extern cvar_t weapon_sound_m4_cqb_lv1;
extern cvar_t weapon_sound_m4_cqb_lv2;
extern cvar_t weapon_sound_m4a1;
extern cvar_t weapon_sound_m4a1_s;
extern cvar_t weapon_sound_mp7;
extern cvar_t weapon_sound_oa93;
extern cvar_t weapon_sound_oa93_dual;
extern cvar_t weapon_sound_p90_mc;
extern cvar_t weapon_sound_pindad_ss2_v5;
extern cvar_t weapon_sound_groza;
extern cvar_t weapon_sound_sc2010;
extern cvar_t weapon_sound_scar_carbine;
extern cvar_t weapon_sound_kriss_sv_crb;
extern cvar_t weapon_sound_kriss_sv_crb_dual;
extern cvar_t weapon_sound_mp5k;
extern cvar_t weapon_sound_m4_azure;
extern cvar_t weapon_sound_mp9;
extern cvar_t weapon_sound_sg550;
extern cvar_t weapon_sound_l115a1;
extern cvar_t weapon_sound_cheytac_m200;
extern cvar_t weapon_sound_dragunov;
extern cvar_t weapon_sound_kar98k;
extern cvar_t weapon_sound_rangemaster_338;
extern cvar_t weapon_sound_m82a1;
extern cvar_t weapon_sound_tactilite_t2;
extern cvar_t weapon_sound_ssg69;
extern cvar_t weapon_sound_m4_spr_lv1;
extern cvar_t weapon_sound_m4_spr_lv2;
extern cvar_t weapon_sound_m1887;
extern cvar_t weapon_sound_spas_15;
extern cvar_t weapon_sound_zombie_s;
extern cvar_t weapon_sound_870mcs;
extern cvar_t weapon_sound_ak_sopmod_cg;
extern cvar_t weapon_sound_aug_esport;
extern cvar_t weapon_sound_t77;
extern cvar_t weapon_sound_apc;
extern cvar_t weapon_sound_fg42;
extern cvar_t weapon_sound_msbs;
extern cvar_t weapon_sound_as50;
extern cvar_t weapon_sound_m1887_w;
extern cvar_t weapon_sound_pgm;
extern cvar_t weapon_sound_ump;
extern cvar_t weapon_sound_sig;
extern cvar_t weapon_sound_spectre;
extern cvar_t weapon_sound_tar;
extern cvar_t weapon_sound_xm8;
extern cvar_t weapon_sound_water_gun;//
extern cvar_t weapon_sound_colt_python;
extern cvar_t weapon_sound_deagle_dual;
extern cvar_t weapon_sound_dual_handgun;
extern cvar_t weapon_sound_raging_bull;
extern cvar_t weapon_sound_deagle;
extern cvar_t weapon_sound_k5;
extern cvar_t weapon_sound_glock;


void GameDLLInit();

#endif // GAME_H
