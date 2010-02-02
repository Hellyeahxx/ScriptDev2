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
SDName: The Forge of Souls
SD%Complete: 95%
SDComment: PH.
SDCategory: The Forge of Souls
EndScriptData */
 
#include "precompiled.h"
#include "the_forge_of_souls.h"
 
#define GOSSIP_START_EVENT "What would you have me, my lady!"
#define GOSSIP_START_EVENT2 "What would you have me, Banshee Queen!"
// Proudmoore
#define SOUND_FS_Jaina_FS01  16617
#define SOUND_FS_Jaina_FS02  16618
#define SOUND_FS_Jaina_FS03  16619
#define SOUND_FS_Jaina_FS04  16620
#define SOUND_FS_Jaina_FS05  16621
#define SOUND_FS_Jaina_FS06  16622
#define SOUND_FS_Jaina_FS07  16623
#define SOUND_FS_Jaina_FS08  16624
#define SOUND_FS_Jaina_FS09  16625
 
#define SAY_FS_Jaina_FS01  "Thanks the Light for seeing you here safely! We have much work to do if we are to defeat the Lich King and put an end to the Scourge."
#define SAY_FS_Jaina_FS02  "Our allies within the Argend Cursade and the Knights of the Ebon Blade have broken through the front gate of Icecrown and are attemping to establish a foothold within the citadel."
#define SAY_FS_Jaina_FS03  "Their success hinges upon waht we discover within these cursed halls. Although our mission is a wrought with peril, we must persevere!"
#define SAY_FS_Jaina_FS04  "With the attention of the Lich King drawn towards the front gate, we will be working our way through the side in the search of Information that will enabele us to defeat the Scourge - once and for all."
#define SAY_FS_Jaina_FS05  "King Varian SI7 agents have gathered information about a private sanctum of the Lich Kings, deep within a place called the Halls of Reflection."
#define SAY_FS_Jaina_FS06  "We will carve a path through this wrerched place and find a way to enter the Halls of Reflection. I sense powerful magic hidden away within tohse halls. Magic that could be the key to destroying the Scourge!"
#define SAY_FS_Jaina_FS07  "Your first mission is to destroy the machines of death within this malevolent engine of souls, and clear a path for our soldiers."
#define SAY_FS_Jaina_FS08  "Make haste, champions. I will prepare the troops to fall in behind you."
#define SAY_FS_Jaina_FS09  "Excellent work champions, we shall set up our base camp in these chambers. My magi will get the Scourge transport device working shortly. Step inside it when you're ready for your next mission, I will meet you on the other side."
 
// Windrunner
#define SOUND_FS_Sylvanas_FS01  17038
#define SOUND_FS_Sylvanas_FS02  17039
#define SOUND_FS_Sylvanas_FS03  17040
#define SOUND_FS_Sylvanas_FS04  17041
#define SOUND_FS_Sylvanas_FS05  17042
#define SOUND_FS_Sylvanas_FS06  17043
#define SOUND_FS_Sylvanas_FS07  17044
 
#define SAY_FS_Sylvanas_FS01  "The Argent Crusade and the Knights of the Ebon Blade have assaulted the gates of the Icecrown Citadel and are preparing for a massive attack upon the scourge. Our mission is a bit more subtle but equally as important."
#define SAY_FS_Sylvanas_FS02  "With the attention of the Lich King turned towards the front gate, we'll be working our way through the side in search of information that will enable us to defeat him... Once and for all."
#define SAY_FS_Sylvanas_FS03  "Our scouts have reported that the Lich King has a private chamber outside of the Frozen Throne, deep within a place called the Halls of Reflection. That is our target, champions."
#define SAY_FS_Sylvanas_FS04  "We will cut a swath of destruction through this cursed place and find a way to enter the Halls of Reflection. If there is anything of value to be found here, it will be found in the Halls."
#define SAY_FS_Sylvanas_FS05  "Your first mission is to destroy the machines of death within this wretched engine of souls, and clear a path for our soldiers."
#define SAY_FS_Sylvanas_FS06  "The Dark Lady watches over you, make haste!"
#define SAY_FS_Sylvanas_FS07  "Excellent work, champions! We shall set up our base camp in these chambers. My magi will get the scourge transport device working shortly, step inside when you are ready for your next mission. I will meet you on the other side."
 
struct MANGOS_DLL_DECL npc_proudmooreAI : public ScriptedAI
{
    npc_proudmooreAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }
 
    ScriptedInstance* m_pInstance;
 
    void Reset()
    {
    }
 
	void StartEvent(Player* pPlayer)
    {
		m_creature->MonsterSay(SAY_FS_Jaina_FS01, LANG_UNIVERSAL, 0);
        DoPlaySoundToSet(m_creature, SOUND_FS_Jaina_FS01);
        Sleep(8000);
 
		m_creature->MonsterSay(SAY_FS_Jaina_FS02, LANG_UNIVERSAL, 0);
		DoPlaySoundToSet(m_creature, SOUND_FS_Jaina_FS02);
        Sleep(9000);
 
		m_creature->MonsterSay(SAY_FS_Jaina_FS03, LANG_UNIVERSAL, 0);
	    DoPlaySoundToSet(m_creature, SOUND_FS_Jaina_FS03);
        Sleep(9000);
 
        m_creature->MonsterSay(SAY_FS_Jaina_FS04, LANG_UNIVERSAL, 0);
	    DoPlaySoundToSet(m_creature, SOUND_FS_Jaina_FS04);
        Sleep(11000);
 
        m_creature->MonsterSay(SAY_FS_Jaina_FS05, LANG_UNIVERSAL, 0);
	    DoPlaySoundToSet(m_creature, SOUND_FS_Jaina_FS05);
        Sleep(9000);
 
		m_creature->MonsterSay(SAY_FS_Jaina_FS06, LANG_UNIVERSAL, 0);
	    DoPlaySoundToSet(m_creature, SOUND_FS_Jaina_FS06);
        Sleep(12000);
 
		m_creature->MonsterSay(SAY_FS_Jaina_FS07, LANG_UNIVERSAL, 0);
	    DoPlaySoundToSet(m_creature, SOUND_FS_Jaina_FS07);
        Sleep(7000);
 
		m_creature->MonsterSay(SAY_FS_Jaina_FS08, LANG_UNIVERSAL, 0);
	    DoPlaySoundToSet(m_creature, SOUND_FS_Jaina_FS08);
        Sleep(9000);
 
    }
 
    void KilledUnit(Unit *victim)
    {
    }
 
    void JustDied(Unit *victim)
    {
    }
 
    void Aggro(Unit* pWho)
    {
        m_creature->SetInCombatWithZone();
 
        if (m_pInstance)
            m_pInstance->SetData(NPC_PROUDMOORE, IN_PROGRESS);
    }
 
    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;
 
        DoMeleeAttackIfReady();
 
        EnterEvadeIfOutOfCombatArea(diff);
 
    }
 
};
 
CreatureAI* GetAI_npc_proudmoore(Creature* pCreature)
{
    return new npc_proudmooreAI(pCreature);
}
 
bool GossipHello_npc_proudmoore(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_START_EVENT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
 
    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}
 
bool GossipSelect_npc_proudmoore(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        ((npc_proudmooreAI*)pCreature->AI())->StartEvent(pPlayer);
    }
 
    return true;
}
 
struct MANGOS_DLL_DECL npc_windrunnerAI : public ScriptedAI
{
    npc_windrunnerAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }
 
    ScriptedInstance* m_pInstance;
 
    void Reset()
    {
    }
 
	void StartEvent(Player* pPlayer)
    {
	    m_creature->MonsterSay(SAY_FS_Sylvanas_FS01, LANG_UNIVERSAL, 0);
        DoPlaySoundToSet(m_creature, SOUND_FS_Sylvanas_FS01);
        Sleep(11000);
 
	    m_creature->MonsterSay(SAY_FS_Sylvanas_FS02, LANG_UNIVERSAL, 0);
        DoPlaySoundToSet(m_creature, SOUND_FS_Sylvanas_FS02);
        Sleep(11000);
 
	    m_creature->MonsterSay(SAY_FS_Sylvanas_FS03, LANG_UNIVERSAL, 0);
        DoPlaySoundToSet(m_creature, SOUND_FS_Sylvanas_FS03);
        Sleep(11000);
 
	    m_creature->MonsterSay(SAY_FS_Sylvanas_FS04, LANG_UNIVERSAL, 0);
        DoPlaySoundToSet(m_creature, SOUND_FS_Sylvanas_FS04);
        Sleep(11000);
 
	    m_creature->MonsterSay(SAY_FS_Sylvanas_FS05, LANG_UNIVERSAL, 0);
        DoPlaySoundToSet(m_creature, SOUND_FS_Sylvanas_FS05);
        Sleep(8000);
 
	    m_creature->MonsterSay(SAY_FS_Sylvanas_FS06, LANG_UNIVERSAL, 0);
        DoPlaySoundToSet(m_creature, SOUND_FS_Sylvanas_FS06);
        Sleep(9000);
    }
 
    void KilledUnit(Unit *victim)
    {
    }
 
    void JustDied(Unit *victim)
    {
    }
 
    void Aggro(Unit* pWho)
    {
        m_creature->SetInCombatWithZone();
 
        if (m_pInstance)
            m_pInstance->SetData(NPC_WINDRUNNER, IN_PROGRESS);
    }
 
    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;
 
        DoMeleeAttackIfReady();
 
        EnterEvadeIfOutOfCombatArea(diff);
 
    }
 
};
 
CreatureAI* GetAI_npc_windrunner(Creature* pCreature)
{
    return new npc_windrunnerAI(pCreature);
}
 
bool GossipHello_npc_windrunner(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_START_EVENT2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
 
    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}
 
bool GossipSelect_npc_windrunner(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        ((npc_windrunnerAI*)pCreature->AI())->StartEvent(pPlayer);
    }
 
    return true;
}
void AddSC_the_forge_of_souls()
{
    Script* NewScript;
 
    NewScript = new Script;
    NewScript->Name = "npc_proudmoore";
    NewScript->GetAI = &GetAI_npc_proudmoore;
    NewScript->pGossipHello = &GossipHello_npc_proudmoore;
    NewScript->pGossipSelect = &GossipSelect_npc_proudmoore;
    NewScript->RegisterSelf();
 
	NewScript = new Script;
    NewScript->Name = "npc_windrunner";
    NewScript->GetAI = &GetAI_npc_windrunner;
    NewScript->pGossipHello = &GossipHello_npc_windrunner;
    NewScript->pGossipSelect = &GossipSelect_npc_windrunner;
    NewScript->RegisterSelf();
 
}
/*UPDATE `creature_template` SET `ScriptName` = 'npc_proudmoore' WHERE `entry` =37597 LIMIT 1 ;
  UPDATE `creature_template` SET `npcflag` = '3' WHERE `entry` =37597 LIMIT 1 ;
  UPDATE `creature_template` SET `ScriptName` = 'npc_windrunner' WHERE `entry` =37596 LIMIT 1 ;
  UPDATE `creature_template` SET `npcflag` = '3' WHERE `entry` =37596 LIMIT 1 ;*/