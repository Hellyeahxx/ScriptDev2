/* Copyright (C) 2006 - 2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
SDName: boss_black_guard_swordsmith
SD%Complete: 100
SDComment: 
SDCategory: Stratholme
EndScriptData */

#include "sc_creature.h"

// **** This script is still under Developement ****



// Unique NPC, only summoned after attempt to open item "Blacksmithing Plans", not a regular mob always around in instance
// The "Blacksmithing Plans" appear to the right of the stairs of the first ziggurat (not the same as the one for Crimson Hammersmith)

#define SPELL_DAZED    1604
#define SPELL_BANSHEECURSE    16867

struct MANGOS_DLL_DECL boss_black_guard_swordsmithAI : public ScriptedAI
{
    boss_black_guard_swordsmithAI(Creature *c) : ScriptedAI(c) {Reset();}

    uint32 Dazed_Timer;
    uint32 BansheeCurse_Timer;

    void Reset()
    {
        Dazed_Timer = 6000;
        BansheeCurse_Timer = 10000;
    }

    void Aggro(Unit *who)
    {
    }


    void UpdateAI(const uint32 diff)
    {
        //Return since we have no target
        if (!m_creature->SelectHostilTarget() || !m_creature->getVictim())
            return;

        //Dazed
        if (Dazed_Timer < diff)
        {
            //Cast
            if (rand()%100 < 75) //75% chance to cast
            {
                DoCast(m_creature->getVictim(),SPELL_DAZED);
            }
            //20 seconds until we should cast this again
            Dazed_Timer = 20000;
        }else Dazed_Timer -= diff;

        //BansheeCurse
        if (BansheeCurse_Timer < diff)
        {
            //Cast
            if (rand()%100 < 10) //10% chance to cast
            {
                DoCast(m_creature->getVictim(),SPELL_BANSHEECURSE);
            }
            //15 seconds until we should cast this again
            BansheeCurse_Timer = 15000;
        }else BansheeCurse_Timer -= diff;

        DoMeleeAttackIfReady();
    }
}; 
CreatureAI* GetAI_boss_black_guard_swordsmith(Creature *_Creature)
{
    return new boss_black_guard_swordsmithAI (_Creature);
}


void AddSC_boss_black_guard_swordsmith()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name="boss_black_guard_swordsmith";
    newscript->GetAI = GetAI_boss_black_guard_swordsmith;
    m_scripts[nrscripts++] = newscript;
}
