/* Copyright (C) 2006 - 2010 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
SDName: Devourer of Souls
SD%Complete: 0
SDComment: PH.
SDCategory: The Forge of Souls
EndScriptData */
 
#include "precompiled.h"
#include "the_forge_of_souls.h"
 
#define SAY_FS_DevourerFemale01_Aggro      "You dare look upon the host of souls? I shall devour you ..."
#define SAY_FS_DevourerFemale01_DarkGlare  "Stare into the abyss and see your end!"
#define SAY_FS_DevourerMale02_Death        "The swell of souls will not be abated. You only delay the inevitable!"
#define SAY_FS_DevourerMale02_Slay1        "Damnation!"
#define SAY_FS_DevourerMale02_Slay2        "Doomed for eternity!"
#define SAY_FS_DevourerMale02_SoulAttack   "Suffering! Anguish! Chaos! Rise and feed!"
 
#define SOUND_FS_DevourerFemale01_Aggro	         16890
#define SOUND_FS_FS_DevourerFemale01_DarkGlare	 16895
#define SOUND_FS_FS_DevourerFemale01_Death1	     16893
#define SOUND_FS_FS_DevourerFemale01_Slay1	     16891
#define SOUND_FS_FS_DevourerFemale01_Slay2	     16892
#define SOUND_FS_FS_DevourerFemale01_SoulAttack1 16894
#define SOUND_FS_FS_DevourerMale01_Aggro	     16884
#define SOUND_FS_FS_DevourerMale01_DarkGlare	 16888
#define SOUND_FS_FS_DevourerMale01_Death2	     16887
#define SOUND_FS_FS_DevourerMale01_Slay1	     16885
#define SOUND_FS_FS_DevourerMale01_Slay2	     16886
#define SOUND_FS_FS_DevourerMale01_SoulAttack2	 16889
#define SOUND_FS_FS_DevourerMale02_Death3	     16898
#define SOUND_FS_FS_DevourerMale02_Slay1	     16896
#define SOUND_FS_FS_DevourerMale02_Slay2	     16897
#define SOUND_FS_FS_DevourerMale02_SoulAttack3	 16899
 
#define SPELL_MIRRORED_SOUL    69051
#define SPELL_PHANTOM_BLAST    68982
#define SPELL_PHANTOM_BLAST_H  70322
#define SPELL_UNLEASHED_SOULS  68939
#define SPELL_WAILING_SOULS    68899
#define SPELL_WAILING_SOULS_H  68912
#define SPELL_WELL_OF_SOULS    68820
 
#define NPC_PROUDMOORE  38160
#define NPC_WINDRUNNER  38161
 
struct MANGOS_DLL_DECL boss_devourerAI : public ScriptedAI
{
    boss_devourerAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }
 
    ScriptedInstance* m_pInstance;
 
    void Reset()
    {
    }
 
    void KilledUnit(Unit *victim)
    {
	switch (urand(0,2))
        {
            case 0:
                DoPlaySoundToSet(m_creature, SOUND_FS_FS_DevourerFemale01_Slay1);
                m_creature->MonsterYell(SAY_FS_DevourerMale02_Slay1, LANG_UNIVERSAL, 0);
                break;
           	case 1:
                DoPlaySoundToSet(m_creature, SOUND_FS_FS_DevourerMale01_Slay1);
                m_creature->MonsterYell(SAY_FS_DevourerMale02_Slay1, LANG_UNIVERSAL, 0);
                break;
          
			case 2:
                DoPlaySoundToSet(m_creature, SOUND_FS_FS_DevourerMale02_Slay1);
                m_creature->MonsterYell(SAY_FS_DevourerMale02_Slay1, LANG_UNIVERSAL, 0);
                break;
         }
    }
 
    void JustDied(Unit *victim)
    {
	switch (urand(0,2))
        {	
            case 0:
                DoPlaySoundToSet(m_creature, SOUND_FS_FS_DevourerFemale01_Death1);
                m_creature->MonsterYell(SAY_FS_DevourerMale02_Death, LANG_UNIVERSAL, 0);
				m_creature->SummonCreature(NPC_PROUDMOORE, 5618.259, 2451.860, 705.851, 0.925806, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 80000);
                m_creature->SummonCreature(NPC_WINDRUNNER, 5618.259, 2451.860, 705.851, 0.925806, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 80000);
                break;					
            case 1:
                DoPlaySoundToSet(m_creature, SOUND_FS_FS_DevourerMale01_Death2);
                m_creature->MonsterYell(SAY_FS_DevourerMale02_Death, LANG_UNIVERSAL, 0);
				m_creature->SummonCreature(NPC_PROUDMOORE, 5618.259, 2451.860, 705.851, 0.925806, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 80000);
                m_creature->SummonCreature(NPC_WINDRUNNER, 5618.259, 2451.860, 705.851, 0.925806, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 80000);
                break;
			case 2:
                DoPlaySoundToSet(m_creature, SOUND_FS_FS_DevourerMale02_Death3);
                m_creature->MonsterYell(SAY_FS_DevourerMale02_Death, LANG_UNIVERSAL, 0);
				m_creature->SummonCreature(NPC_PROUDMOORE, 5618.259, 2451.860, 705.851, 0.925806, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 80000);
                m_creature->SummonCreature(NPC_WINDRUNNER, 5618.259, 2451.860, 705.851, 0.925806, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 80000);
                break;
		}
        if (m_pInstance)
            m_pInstance->SetData(BOSS_DEVOURER, DONE);
    }
 
    void Aggro(Unit* pWho)
    {
	switch(urand(0, 2))
        {
            case 0: 
                DoPlaySoundToSet(m_creature, SOUND_FS_DevourerFemale01_Aggro);
                m_creature->MonsterYell(SAY_FS_DevourerFemale01_Aggro, LANG_UNIVERSAL, 0);
                break;
            case 1:
                DoPlaySoundToSet(m_creature, SOUND_FS_FS_DevourerMale01_Aggro);
                m_creature->MonsterYell(SAY_FS_DevourerFemale01_Aggro, LANG_UNIVERSAL, 0);
                break;
        }
 
        m_creature->SetInCombatWithZone();
 
        if (m_pInstance)
            m_pInstance->SetData(BOSS_DEVOURER, IN_PROGRESS);
    }
 
    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;
//SPELLS TODO:
 
//
        DoMeleeAttackIfReady();
 
        EnterEvadeIfOutOfCombatArea(diff);
 
    }
 
};
 
CreatureAI* GetAI_boss_devourer(Creature* pCreature)
{
    return new boss_devourerAI(pCreature);
}
 
void AddSC_boss_devourer()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_devourer";
    newscript->GetAI = &GetAI_boss_devourer;
    newscript->RegisterSelf();
 
}
/*UPDATE `creature_template` SET `ScriptName` = 'boss_devourer' WHERE `entry` =36502 LIMIT 1 ;*/