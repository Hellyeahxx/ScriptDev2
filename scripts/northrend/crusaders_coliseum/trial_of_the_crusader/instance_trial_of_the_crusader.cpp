#include "precompiled.h"
#include "instance_trial_of_the_crusader.h"
//DUMMY
 
 
bool GossipHello_Barrett_Ramsey(Player *player, Creature *_Creature)
{
ScriptedInstance* pInstance = ((ScriptedInstance*)_Creature->GetInstanceData());
if( pInstance && pInstance->GetData(DOOR1) == NOT_STARTED)
{
	 if (pInstance && pInstance->GetData(BOSS1) != DONE)
	 {
		 player->ADD_GOSSIP_ITEM( 5, "BEGIN THE EVENT" , GOSSIP_SENDER_MAIN, 1);
		 player->ADD_GOSSIP_ITEM( 5, "KILL ME!" , GOSSIP_SENDER_MAIN, 333);
		  player->PlayerTalkClass->SendGossipMenu(907, _Creature->GetGUID());
	 } else {
			 if (pInstance && pInstance->GetData(BOSS2) != DONE)
			{	
				 player->ADD_GOSSIP_ITEM( 5, "START 2" , GOSSIP_SENDER_MAIN, 2);
				 		 player->ADD_GOSSIP_ITEM( 5, "KILL ME!" , GOSSIP_SENDER_MAIN, 333);
				 player->PlayerTalkClass->SendGossipMenu(907, _Creature->GetGUID());
			} else {
				 if (pInstance && pInstance->GetData(BOSS3) != DONE)
				{
					 player->ADD_GOSSIP_ITEM( 5, "START 3" , GOSSIP_SENDER_MAIN, 3);
					 		 player->ADD_GOSSIP_ITEM( 5, "KILL ME!" , GOSSIP_SENDER_MAIN, 333);
					  player->PlayerTalkClass->SendGossipMenu(907, _Creature->GetGUID());
				 } else {
					player->ADD_GOSSIP_ITEM( 5, "START 4" , GOSSIP_SENDER_MAIN, 4);
							 player->ADD_GOSSIP_ITEM( 5, "KILL ME!" , GOSSIP_SENDER_MAIN, 333);
					 player->PlayerTalkClass->SendGossipMenu(907, _Creature->GetGUID());
				}
			}
 }
}
}
 
bool GossipSelect_Barrett_Ramsey(Player *player, Creature *_Creature, uint32 sender, uint32 action)
{
 
		ScriptedInstance* pInstance = ((ScriptedInstance*)_Creature->GetInstanceData());
     pInstance->SetData(action, IN_PROGRESS);
	player->CLOSE_GOSSIP_MENU();
 
 
 
}
 
 
struct MANGOS_DLL_DECL instance_trial_of_the_crusader : public ScriptedInstance
{
    instance_trial_of_the_crusader(Map* pMap) : ScriptedInstance(pMap) {Initialize();};
 
    uint32 m_auiEncounter[MAX_ENCOUNTER];
	uint32 DOOR;
    std::string strInstData;
 
    uint64 m_uiTirionFordringGUID;
    uint64 m_uiGormokGUID;
	uint64	m_uiDreadscaleGUID;
	uint64	m_uiAcidmawGUID;
	uint64	m_uiIcehowlGUID;
 
    uint64 m_uiDoorMainGUID;
	uint32 CloseGate_Timer;
	uint32 Wait_Timer ;
	uint32 Intro;
	uint32 OpenGate_Timer;
	uint32 emotetimer;
	uint32 IntroPhase;
	uint32 Swap_Timer;
	bool Swap;
 
    void Initialize()
    {
        memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));
 
        m_uiTirionFordringGUID = 0;
        m_uiGormokGUID = 0;
		m_uiDreadscaleGUID = 0;
		m_uiAcidmawGUID = 0;
		m_uiIcehowlGUID = 0;
 
        m_uiDoorMainGUID = 0;
		Wait_Timer = 4000;
    }
 
    void OnCreatureCreate(Creature* pCreature)
    {
        switch(pCreature->GetEntry())
        {
            case TirionFordring: m_uiTirionFordringGUID = pCreature->GetGUID(); break;
            case Gormok: m_uiGormokGUID = pCreature->GetGUID(); break;
			case Dreadscale: m_uiDreadscaleGUID = pCreature->GetGUID(); break;
			case Acidmaw: m_uiAcidmawGUID = pCreature->GetGUID(); break;
			case Icehowl: m_uiIcehowlGUID = pCreature->GetGUID(); break;
        }
    }
 
    void OnObjectCreate(GameObject* pGo)
    {
        switch(pGo->GetEntry())
        {
            case GO_MAIN_DOOR:
                m_uiDoorMainGUID = pGo->GetGUID();
                if (DOOR == DONE)
                    pGo->SetGoState(GO_STATE_ACTIVE);
                break;
        }
    }
	///////// CONTROLLER
	//Timers
 
 
void Update(const uint32 diff)
	{
	//0 = open gate
	//1 = move boss
	//2 = nothing
 
		Creature* pGormok = instance->GetCreature(m_uiGormokGUID);
		Creature* pDreadscale = instance->GetCreature(m_uiDreadscaleGUID);
		Creature* pAcidmaw = instance->GetCreature(m_uiAcidmawGUID);
		Creature* pIcehowl = instance->GetCreature(m_uiIcehowlGUID);
		//MOVE INTRO
	if(Intro == 1)
	{
		if(Wait_Timer < diff)
		{
			switch(IntroPhase)
			{
				case 1:
					pGormok->GetMotionMaster()->MovePoint(0, 563.589294, 139.645645, 393.836578);
					pGormok->MonsterYell("HELLO!!!!!!!!!", LANG_UNIVERSAL, 0);
				break;
				case 2:
					pDreadscale->GetMotionMaster()->MovePoint(0, 563.589294, 139.645645, 393.836578);
					pDreadscale->MonsterYell("HGfdgdhr", LANG_UNIVERSAL, 0);
					emotetimer = 4000;
		//			EmoteIsntDone = false;
				break;
				case 3: 
					pIcehowl->GetMotionMaster()->MovePoint(0, 563.589294, 139.645645, 393.836578);
				break;
 
 
			}
				CloseGate_Timer = 4000;
				Intro = 2;			
		} else Wait_Timer -= diff;
	}
 
	//**********OPEN GATE**********///	
			if(OpenGate_Timer < diff && Intro == 0)
			{
				Intro = 1;
				SetData(DOOR1, DONE);
				Wait_Timer = 3000;
			}else OpenGate_Timer -= diff;
	//*********CLOSE GATE*************///
			if(CloseGate_Timer < diff && GetData(DOOR1) == DONE)
			{
				SetData(DOOR1, IN_PROGRESS); //closegate
				DoUseDoorOrButton(m_uiDoorMainGUID);
			}else CloseGate_Timer -= diff;
 
 
	//////////SPECIAL///////////////
/*	if(EmoteIsntDone == false)
	{
		if(emotetimer < diff)
		{
		Creature *pAcidmaw = pDreadscale->SummonCreature(Acidmaw,538.347, 165.509, 394.6500, 5.431659,TEMPSUMMON_MANUAL_DESPAWN, 0);
		pAcidmaw->HandleEmoteCommand(Emerge);
			EmoteIsntDone = true;
			
		}else emotetimer -= diff; 
	}*/
		if(GetData(BOSS2) == IN_PROGRESS)
		{
			if(Swap_Timer < diff)
			{
				if(Swap == false){
				SetData(100, SWAP_SWAP); 
				Swap_Timer = 55000;
				pDreadscale->MonsterYell("Me Swap", LANG_UNIVERSAL, 0);
				} else SetData(100, SWAP_Orginal);;
			}else Swap_Timer -= diff;
 
			if (pDreadscale && pDreadscale->isDead() && pAcidmaw && pAcidmaw->isDead())
			{
				SetData(BOSS2, DONE);
			}
		}
	}
 
 
/*
    void DoSpeech()
    {
        Creature* pAda = instance->GetCreature(m_uiAdaGUID);
        Creature* pAsh = instance->GetCreature(m_uiAshGUID);
 
        if (pAda && pAda->isAlive() && pAsh && pAsh->isAlive())
        {
            DoScriptText(SAY_BOSS_DIE_AD,pAda);
            DoScriptText(SAY_BOSS_DIE_AS,pAsh);
        }
    } */
 
    void SetData(uint32 uiType, uint32 uiData)
    {
	Creature* pTirionFordring = instance->GetCreature(m_uiTirionFordringGUID);
        switch(uiType)
        {
			case DOOR1:
                if (uiData == DONE)
                    DoUseDoorOrButton(m_uiDoorMainGUID);
                m_auiEncounter[0] = uiData;
            break;
            case 1:
                if (uiData == IN_PROGRESS)
				{
					IntroPhase = 1;
					OpenGate_Timer = 8000;
					Intro = 0;
					DoScriptText(INTRO1, pTirionFordring);
					Creature *pGormok = pTirionFordring->SummonCreature(Gormok,563.539551, 213.565628, 395.098206, 4.66094,TEMPSUMMON_MANUAL_DESPAWN, 0);
					pGormok->RemoveMonsterMoveFlag(MONSTER_MOVE_WALK);
				}
                m_auiEncounter[1] = uiData;
                break;
			case 2:
                if (uiData == IN_PROGRESS)
				{
				IntroPhase = 2;
				Intro = 0;
				DoScriptText(INTRO2, pTirionFordring);
				OpenGate_Timer = 3500;
				Creature *pDreadscale = pTirionFordring->SummonCreature(Dreadscale,563.539551, 213.565628, 395.098206, 4.66094,TEMPSUMMON_MANUAL_DESPAWN, 0);
				pDreadscale->RemoveMonsterMoveFlag(MONSTER_MOVE_WALK);
				}
				if (uiData == DONE)
				SetData(BOSS3, IN_PROGRESS);
                m_auiEncounter[2] = uiData;
            break;
			case 3:
                if (uiData == IN_PROGRESS)
				{
				IntroPhase = 3;
				Intro = 0;
				DoScriptText(INTRO3, pTirionFordring);
				OpenGate_Timer = 3500;
				Swap_Timer = 55000;
				Creature *pIcehowl = pTirionFordring->SummonCreature(Icehowl,563.539551, 213.565628, 395.098206, 4.66094,TEMPSUMMON_MANUAL_DESPAWN,0);
				pIcehowl->RemoveMonsterMoveFlag(MONSTER_MOVE_WALK);
				}
                m_auiEncounter[3] = uiData;
            break;
			case 100:
				if(uiData == SWAP_Orginal)
				Swap = false;
				if(uiData == SWAP_SWAP)
				Swap = true;
			break;
        }
 
        if (uiData == DONE)
        {
            OUT_SAVE_INST_DATA;
 
            std::ostringstream saveStream;
            saveStream << m_auiEncounter[0] << " " << m_auiEncounter[1] << " " << m_auiEncounter[2] << " " << m_auiEncounter[3];
 
            strInstData = saveStream.str();
 
            SaveToDB();
            OUT_SAVE_INST_DATA_COMPLETE;
        }
    }
 
    uint32 GetData(uint32 uiType)
    {
        switch(uiType)
        {
			case DOOR1:
                return m_auiEncounter[0];
            case BOSS1:
                return m_auiEncounter[1];
			case BOSS2:
                return m_auiEncounter[2];
			case BOSS3:
                return m_auiEncounter[3];
 
        }
        return 0;
    }
	       uint64 GetData64(uint32 uiData)
       {
           switch(uiData)
           {
               case Dreadscale:       return m_uiDreadscaleGUID;
			   case Acidmaw:       return m_uiAcidmawGUID;
 
           }
   
           return 0;
       }
 
 /*   uint64 GetData64(uint32 id)
    {
        switch(id)
        {
            case Gormok:      return m_uiGormokGUID;
 
        }
        return 0;
    }*/
 
 
 
    const char* Save()
    {
        return strInstData.c_str();
    }
 
    void Load(const char* chrIn)
    {
        if (!chrIn)
        {
            OUT_LOAD_INST_DATA_FAIL;
            return;
        }
 
        OUT_LOAD_INST_DATA(chrIn);
 
        std::istringstream loadStream(chrIn);
        loadStream >> m_auiEncounter[0] >> m_auiEncounter[1] >> m_auiEncounter[2] >> m_auiEncounter[3];
 
        for(uint8 i = 0; i < MAX_ENCOUNTER; ++i)
        {
            if (m_auiEncounter[i] == IN_PROGRESS)
                m_auiEncounter[i] = NOT_STARTED;
        }
			m_auiEncounter[0] = NOT_STARTED;
        OUT_LOAD_INST_DATA_COMPLETE;
    }
};
 
InstanceData* GetInstanceData_instance_trial_of_the_crusader(Map* pMap)
{
    return new instance_trial_of_the_crusader(pMap);
}
 
void AddSC_instance_trial_of_the_crusader()
{
	newscript = new Script;
	newscript->Name="Barrett_Ramsey";
	newscript->pGossipHello = &GossipHello_Barrett_Ramsey;
	newscript->pGossipSelect = &GossipSelect_Barrett_Ramsey;
    newscript->RegisterSelf();
 
    Script* newscript;
    newscript = new Script;
    newscript->Name = "instance_trial_of_the_crusader";
    newscript->GetInstanceData = &GetInstanceData_instance_trial_of_the_crusader;
    newscript->RegisterSelf();
 
}
 