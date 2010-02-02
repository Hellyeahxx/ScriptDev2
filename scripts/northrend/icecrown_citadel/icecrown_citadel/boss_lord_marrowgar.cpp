/* Copyright (C) 2006 - 2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
 
/* ScriptData
SDName: Lord Marrowgar
SD%Complete: 65%
SDComment: PH.
SDCategory: IceCrownCitadel
EndScriptData */
 
#include "precompiled.h"
#include "def_icecrown_citadel.h"
 
#define SOUND_IC_Marrowgar_Aggro01     16941
#define SOUND_IC_Marrowgar_Slay01      16942
#define SOUND_IC_Marrowgar_Slay02      16943
#define SOUND_IC_Marrowgar_Death01     16944
#define SOUND_IC_Marrowgar_Berserk01   16945
#define SOUND_IC_Marrowgar_WW01        16946
#define SOUND_IC_Marrowgar_BS01        16947
#define SOUND_IC_Marrowgar_BS02        16948
#define SOUND_IC_Marrowgar_BS03        16949
#define SOUND_IC_Marrowgar_AreaEntry01 16950
#define SOUND_IC_Marrowgar_Attack      16951
#define SOUND_IC_Marrowgar_Wound       16952
#define SOUND_IC_Marrowgar_WoundCrit   16953
 
#define SAY_IC_Marrowgar_Aggro01    "The Scourge will wash over this world as a swarm of death and destruction."
#define SAY_IC_Marrowgar_AreaEntry0 "This is the beginning and the end, mortals. None may enter the Master's sanctum."
#define SAY_IC_Marrowgar_Berserk0   "The Master's rage courses through me!"
#define SAY_IC_Marrowgar_BS01       "Bound by bones!"
#define SAY_IC_Marrowgar_BS02       "Stick around."
#define SAY_IC_Marrowgar_BS03       "Your only escape is death."
#define SAY_IC_Marrowgar_Death01    "I see ... only darkness."
#define SAY_IC_Marrowgar_Slay01     "More bones for the offering."
#define SAY_IC_Marrowgar_Slay02     "Languishing damnation."
#define SAY_IC_IC_Marrowgar_WW01    "Bone storm!"
 
#define SPELL_ENRAGE                 26662
#define SPELL_BONE_SPIKE_GRAVEYARD   69057
#define SPELL_BONE_SPIKE_GRAVEYARD_H 70826
#define SPELL_BONE_STROM             69076
#define SPELL_BONE_STROM1            69075
#define SPELL_BONE_STROM_H           70834
#define SPELL_SABER_LASH             69055
#define SPELL_SABER_LASH_H           70814
#define SPELL_SOUL_FEAST             71203
#define SPELL_COLDFLAME              69146
#define SPELL_COLDFLAME_H            70824       
 
struct MANGOS_DLL_DECL boss_lord_marrowgarAI : public ScriptedAI
{
    boss_lord_marrowgarAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
		m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }
    bool m_bIsRegularMode;
    ScriptedInstance* m_pInstance;
 
    uint32 Enrage_Timer;
    uint32 Coldflame_Timer;
	uint32 Coldflame_H_Timer;
	uint32 Bone_Spike_Graveyard_Timer;
	uint32 Bone_Spike_Graveyard_H_Timer;
	uint32 Saber_Lash_Timer;
	uint32 Saber_Lash_H_Timer;
	bool enrage;
	bool phase2;
 
    void Reset()
    {
	   Enrage_Timer = 600000;
	   Coldflame_Timer = 5000;
       Coldflame_H_Timer = 4000;
       Bone_Spike_Graveyard_Timer = 20000;
       Bone_Spike_Graveyard_H_Timer = 15000;
       Saber_Lash_Timer = 15000;
       Saber_Lash_H_Timer = 12000;
	   enrage = false;
	   phase2 = false;
    }
 
    void KilledUnit(Unit *victim)
    {
	switch(urand(0, 1))                                       // 50% chance to say something out of 2 texts
         {
          case 0: DoPlaySoundToSet(m_creature, SOUND_IC_Marrowgar_Slay01);
			      m_creature->MonsterYell(SAY_IC_Marrowgar_Slay01, LANG_UNIVERSAL, 0);break;
          case 1: DoPlaySoundToSet(m_creature, SOUND_IC_Marrowgar_Slay02); 
			      m_creature->MonsterYell(SAY_IC_Marrowgar_Slay02, LANG_UNIVERSAL, 0);break;
         }
    }
 
    void JustDied(Unit *victim)
    {
    if (m_pInstance)
        m_pInstance->SetData(TYPE_LORD_MARROWGAR, DONE);
	    m_creature->MonsterYell(SAY_IC_Marrowgar_Death01, LANG_UNIVERSAL, 0);
	    DoPlaySoundToSet(m_creature, SOUND_IC_Marrowgar_Death01);
    }
 
    void Aggro(Unit* pWho)
    {
	    DoPlaySoundToSet(m_creature, SOUND_IC_Marrowgar_Aggro01);
        m_creature->MonsterYell(SAY_IC_Marrowgar_Aggro01, LANG_UNIVERSAL, 0);
        m_creature->SetInCombatWithZone();
 
        if (m_pInstance)
            m_pInstance->SetData(TYPE_LORD_MARROWGAR, IN_PROGRESS);
    }
 
    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;
 
		if (Enrage_Timer < diff && !enrage && !phase2)
        {
            DoCast(m_creature, SPELL_ENRAGE);
            if (m_creature->HasAura(SPELL_ENRAGE))
            {
                enrage = true;
	            DoPlaySoundToSet(m_creature, SOUND_IC_Marrowgar_Berserk01);
                m_creature->MonsterYell(SAY_IC_Marrowgar_Berserk0, LANG_UNIVERSAL, 0);
            }
            else
                Enrage_Timer = 5000;
        }else Enrage_Timer -= diff;
 
		if (Coldflame_Timer < diff && !phase2)
        {
            if (Unit* target = SelectUnit(SELECT_TARGET_RANDOM,0))
                DoCast(target, m_bIsRegularMode ? SPELL_COLDFLAME : SPELL_COLDFLAME_H);
            Coldflame_Timer = m_bIsRegularMode ? 10000 :8000;
        }else Coldflame_Timer -= diff;
 
		if (Bone_Spike_Graveyard_Timer < diff && !phase2)
        {
            if (Unit* target = SelectUnit(SELECT_TARGET_RANDOM,0))
                DoCast(target, m_bIsRegularMode ? SPELL_BONE_SPIKE_GRAVEYARD : SPELL_BONE_SPIKE_GRAVEYARD_H);
            Bone_Spike_Graveyard_Timer = m_bIsRegularMode ? 20000 :18000;
        }else Bone_Spike_Graveyard_Timer -= diff;
 
		if (Saber_Lash_Timer < diff && !phase2)
        {
            if (Unit* target = SelectUnit(SELECT_TARGET_RANDOM,0))
                DoCast(target, m_bIsRegularMode ? SPELL_SABER_LASH : SPELL_SABER_LASH_H);
            Saber_Lash_Timer = m_bIsRegularMode ? 15000 :12000;
        }else Saber_Lash_Timer -= diff;
 
        if (!phase2)
            DoMeleeAttackIfReady();
 
    }
 
};
 
CreatureAI* GetAI_boss_lord_marrowgar(Creature* pCreature)
{
    return new boss_lord_marrowgarAI(pCreature);
}
 
void AddSC_boss_lord_marrowgar()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_lord_marrowgar";
    newscript->GetAI = &GetAI_boss_lord_marrowgar;
    newscript->RegisterSelf();
 
}
 
/*
UPDATE `creature_template` SET `ScriptName` = 'boss_lord_marrowgar' WHERE `entry` =36612 LIMIT 1 ;
*/