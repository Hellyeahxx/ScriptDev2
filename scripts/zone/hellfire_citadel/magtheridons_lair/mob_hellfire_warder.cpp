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
SDName: Mob_Hellfire_Warder
SD%Complete: 100
SDComment: 
SDCategory: Hellfire Citadel, Magtheridon's lair
EndScriptData */

#include "sc_creature.h"

#define SPELL_SHADOW_BOLT_VOLLEY    39175
#define SPELL_DEATH_COIL            33130
#define SPELL_RAIN_OF_FIRE          38635

struct MANGOS_DLL_DECL mob_hellfire_warderAI : public ScriptedAI
{
    mob_hellfire_warderAI(Creature *c) : ScriptedAI(c) {Reset();}

    uint32 Shadow_Timer;
    uint32 Death_Timer;
    uint32 Rain_Timer;

    int RandTime(int time) {return ((rand()%time)*1000);}

    void Reset()
    {
        Shadow_Timer = 10000;
        Death_Timer = 50000;
        Rain_Timer = 30000;
    }

    void Aggro(Unit *who)
    {
    }

    void UpdateAI(const uint32 diff)
    {
        //Return since we have no target
        if (!m_creature->SelectHostilTarget() || !m_creature->getVictim() )
            return;

        if (Shadow_Timer < diff)
        {
            Unit* target = NULL;
            target = SelectUnit(SELECT_TARGET_RANDOM,0);

            if (target)
                DoCast(target,SPELL_SHADOW_BOLT_VOLLEY);
            else
                DoCast(m_creature->getVictim(),SPELL_SHADOW_BOLT_VOLLEY);

            Shadow_Timer = RandTime(60);
        }else Shadow_Timer -= diff;

        if (Death_Timer < diff)
        {
            Unit* target = NULL;
            target = SelectUnit(SELECT_TARGET_TOPAGGRO,1);

            if (target)
                DoCast(target,SPELL_DEATH_COIL);
            else
                DoCast(m_creature->getVictim(),SPELL_DEATH_COIL);

            Death_Timer = RandTime(60);
        }else Death_Timer -= diff;

        if (Rain_Timer < diff)
        {
            Unit* target = NULL;
            target = SelectUnit(SELECT_TARGET_RANDOM,0);

            if (target)
                DoCast(target,SPELL_RAIN_OF_FIRE);
            else
                DoCast(m_creature->getVictim(),SPELL_RAIN_OF_FIRE);

            Rain_Timer = RandTime(60);
        }else Rain_Timer -= diff;

        DoMeleeAttackIfReady();
    }

};

CreatureAI* GetAI_mob_hellfire_warder(Creature *_Creature)
{
    return new mob_hellfire_warderAI (_Creature);
}

void AddSC_mob_hellfire_warder()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name="mob_hellfire_warder";
    newscript->GetAI = GetAI_mob_hellfire_warder;
    m_scripts[nrscripts++] = newscript;
}
