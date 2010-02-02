#include "precompiled.h"
#include "instance_trial_of_the_crusader.h"
 
 
struct MANGOS_DLL_DECL npc_dreadscaleAI : public ScriptedAI
{
npc_dreadscaleAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}
 
	uint32 acidicspew_timer; //phase 1  stationary first
	uint32 slimepool_timer;
	uint32 paralyticbite_timer;
	uint32 acidspit_timer;//phase 2
	uint32 sweep_timer;
	uint32 paralyticspray_timer;
	bool once;
	bool Swap;
 
	void Reset()
{
 
	acidicspew_timer = 5400;
	slimepool_timer = 10000;
	paralyticbite_timer =  4000;
 
	paralyticspray_timer = 12000;
	sweep_timer =  7000;
	acidspit_timer = 16000;
 
 
 
}
 
void Aggro(Unit *who)
	{
		m_creature->MonsterSay("Agro'ed!", LANG_UNIVERSAL, 0);
		Creature *pAcidmaw = m_creature->SummonCreature(Acidmaw,538.347, 165.509, 394.6500, 5.431659,TEMPSUMMON_MANUAL_DESPAWN, 0);
		pAcidmaw->HandleEmoteCommand(Emerge);
	}
 
void UpdateAI(const uint32 diff )
	{
		ScriptedInstance* pInstance = ((ScriptedInstance*)m_creature->GetInstanceData());
		//Return since we have no target
		if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
			return;
 
			//BEGIN AI
 
				//BOSS 1
			if(pInstance && pInstance->GetData(100) == SWAP_Orginal)
			{
				if(paralyticspray_timer < diff)      //para spray
				{
					m_creature->MonsterSay("SPRAYYYYYYY", LANG_UNIVERSAL, 0);
					DoCast(m_creature->getVictim(),paralyticspray);
					paralyticspray_timer = 12000;
				}else paralyticspray_timer -= diff;
 
				if(sweep_timer < diff)           //sweep
				{	
					DoCast(m_creature->getVictim(),sweep);
					sweep_timer =   7000;
					m_creature->MonsterSay("SWEEP!!", LANG_UNIVERSAL, 0);
				}else sweep_timer -= diff;
 
				if(acidspit_timer < diff)           //acid spit
				{	
					DoCast(m_creature->getVictim(),acidspit);
					acidspit_timer = 16000;
					m_creature->MonsterSay("Acid Spit!!", LANG_UNIVERSAL, 0);
				}else acidspit_timer -= diff;
			}else{
				if( paralyticbite_timer < diff)      //para bite
				{
					m_creature->MonsterSay("BITTTTEEEEE", LANG_UNIVERSAL, 0);
					DoCast(m_creature->getVictim(), paralyticbite);
					 paralyticbite_timer = 30000;
				}else  paralyticbite_timer -= diff;
 
				if(slimepool_timer < diff)           //slimepool
				{	
					DoCast(m_creature->getVictim(),slimepool);
					slimepool_timer = 10000;
					m_creature->MonsterSay("POOOOLLLL OF SLIME!!!", LANG_UNIVERSAL, 0);
				}else slimepool_timer -= diff;
 
				if(acidicspew_timer < diff)           //acidicspew
				{	
					DoCast(m_creature->getVictim(),acidicspew);
					acidicspew_timer = 10000;
					m_creature->MonsterSay("Acid spewwwwww!!", LANG_UNIVERSAL, 0);
				}else acidicspew_timer -= diff;
			}
 
				//determine if phase has ended
			   //   DoMeleeAttackIfReady();
	}
};
 
 
struct MANGOS_DLL_DECL npc_acidmawAI : public ScriptedAI
{
npc_acidmawAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}
 
	uint32 EndPhaseTwo;
	uint32 acidicspew_timer; //phase 1  stationary first
	uint32 slimepool_timer;
	uint32 paralyticbite_timer;
	uint32 acidspit_timer;//phase 2
	uint32 sweep_timer;
	uint32 paralyticspray_timer;
 
	void Reset()
{
 
	acidicspew_timer = 5400;
	slimepool_timer = 10000;
	paralyticbite_timer =  4000;
 
	paralyticspray_timer = 12000;
	acidspit_timer = 16000;
 
}
 
void Aggro(Unit *who)
	{
		m_creature->MonsterSay("Me Hungry!", LANG_UNIVERSAL, 0);
 
	}
 
void UpdateAI(const uint32 diff )
	{
		ScriptedInstance* pInstance = ((ScriptedInstance*)m_creature->GetInstanceData());
 
		//Return since we have no target
		if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
			return;
 
			//BEGIN AI
 
				//BOSS 1
 
 
 
 
				//*****BOSS2***//
			if(pInstance && pInstance->GetData(100) == SWAP_Orginal)
			{
				if( paralyticbite_timer < diff)      //para bite
				{
					m_creature->MonsterSay("BITTTTEEEEE", LANG_UNIVERSAL, 0);
					DoCast(m_creature->getVictim(), paralyticbite);
					 paralyticbite_timer = 30000;
				}else  paralyticbite_timer -= diff;
 
				if(slimepool_timer < diff)           //slimepool
				{	
					DoCast(m_creature->getVictim(),slimepool);
					slimepool_timer = 10000;
					m_creature->MonsterSay("POOOOLLLL OF SLIME!!!", LANG_UNIVERSAL, 0);
				}else slimepool_timer -= diff;
 
				if(acidicspew_timer < diff)           //acidicspew
				{	
					DoCast(m_creature->getVictim(),acidicspew);
					acidicspew_timer = 10000;
					m_creature->MonsterSay("Acid spewwwwww!!", LANG_UNIVERSAL, 0);
				}else acidicspew_timer -= diff;
			}else{
				if(paralyticspray_timer < diff)      //para spray
				{
					m_creature->MonsterSay("SPRAYYYYYYY", LANG_UNIVERSAL, 0);
					DoCast(m_creature->getVictim(),paralyticspray);
					paralyticspray_timer = 12000;
				}else paralyticspray_timer -= diff;
 
				if(sweep_timer < diff)           //sweep
				{	
					DoCast(m_creature->getVictim(),sweep);
					sweep_timer =   7000;
					m_creature->MonsterSay("SWEEP!!", LANG_UNIVERSAL, 0);
				}else sweep_timer -= diff;
 
				if(acidspit_timer < diff)           //acid spit
				{	
					DoCast(m_creature->getVictim(),acidspit);
					acidspit_timer = 16000;
					m_creature->MonsterSay("Acid Spit!!", LANG_UNIVERSAL, 0);
				}else acidspit_timer -= diff;
			}
				//determine if phase has ended
			   //   DoMeleeAttackIfReady();
	}
};
 
 
CreatureAI* GetAI_npc_dreadscale(Creature* pCreature)
{
    return new npc_dreadscaleAI(pCreature);
}
 
CreatureAI* GetAI_npc_acidmaw(Creature* pCreature)
{
    return new npc_acidmawAI(pCreature);
}
 
void AddSC_the_two_jormungar()
{
    Script* newscript;
 
    newscript = new Script;
    newscript->Name = "npc_dreadscale";
    newscript->GetAI = &GetAI_npc_dreadscale;
    newscript->RegisterSelf();
 
    newscript = new Script;
    newscript->Name = "npc_acidmaw";
    newscript->GetAI = &GetAI_npc_acidmaw;
    newscript->RegisterSelf();
}