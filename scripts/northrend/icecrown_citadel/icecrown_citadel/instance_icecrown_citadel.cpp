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
SDName: Instance_Naxxramas
SD%Complete: 90%
SDComment:
SDCategory: Naxxramas
EndScriptData */
 
#include "precompiled.h"
#include "def_icecrown_citadel.h"
 
struct MANGOS_DLL_DECL instance_icecrown_citadel : public ScriptedInstance
{
    instance_icecrown_citadel(Map* pMap) : ScriptedInstance(pMap) {Initialize();}
 
    std::string strInstData;
    uint32 m_auiEncounter[MAX_ENCOUNTER];
 
    uint64 m_uiLordMarrowgarGUID;
    uint64 m_uiLordMarrowgarDoorGUID;
 
    void Initialize()
    {
        memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));
 
        m_uiLordMarrowgarGUID        = 0;
    }
 
    void OnCreatureCreate(Creature* pCreature)
    {
        switch(pCreature->GetEntry())
        {
            case NPC_LORD_MARROWGAR: m_uiLordMarrowgarGUID = pCreature->GetGUID(); break;
        }
    }
 
    void OnObjectCreate(GameObject* pGo)
    {
        switch(pGo->GetEntry())
        {
            case GO_LORD_MARROWGAR_DOOR:
                m_uiLordMarrowgarGUID = pGo->GetGUID();
                break; 
        }
    }
 
    bool IsEncounterInProgress() const
    {
        for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
            if (m_auiEncounter[i] == IN_PROGRESS)
                return true;
 
        return false;
    }
 
    void SetData(uint32 uiType, uint32 uiData)
    {
        switch(uiType)
        {
            case TYPE_LORD_MARROWGAR:
                m_auiEncounter[0] = uiData;
                DoUseDoorOrButton(m_uiLordMarrowgarGUID);
                if (uiData == DONE)
                    DoUseDoorOrButton(m_uiLordMarrowgarGUID);
                break;
        }
 
        if (uiData == DONE)
        {
            OUT_SAVE_INST_DATA;
 
            std::ostringstream saveStream;
            saveStream << m_auiEncounter[0] << " " << m_auiEncounter[1] << " " << m_auiEncounter[2] << " "
                << m_auiEncounter[3] << " " << m_auiEncounter[4] << " " << m_auiEncounter[5] << " "
                << m_auiEncounter[6] << " " << m_auiEncounter[7] << " " << m_auiEncounter[8] << " "
                << m_auiEncounter[9] << " " << m_auiEncounter[10] << " " << m_auiEncounter[11] << " "
                << m_auiEncounter[12] << " " << m_auiEncounter[13] << " " << m_auiEncounter[14];
 
            strInstData = saveStream.str();
 
            SaveToDB();
            OUT_SAVE_INST_DATA_COMPLETE;
        }
    }
 
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
        loadStream >> m_auiEncounter[0] >> m_auiEncounter[1] >> m_auiEncounter[2] >> m_auiEncounter[3]
            >> m_auiEncounter[4] >> m_auiEncounter[5] >> m_auiEncounter[6] >> m_auiEncounter[7]
            >> m_auiEncounter[8] >> m_auiEncounter[9] >> m_auiEncounter[10] >> m_auiEncounter[11]
            >> m_auiEncounter[12] >> m_auiEncounter[13] >> m_auiEncounter[14];
 
        for(uint8 i = 0; i < MAX_ENCOUNTER; ++i)
        {
            if (m_auiEncounter[i] == IN_PROGRESS)
                m_auiEncounter[i] = NOT_STARTED;
        }
 
        OUT_LOAD_INST_DATA_COMPLETE;
    }
 
    uint32 GetData(uint32 uiType)
    {
        switch(uiType)
        {
            case TYPE_LORD_MARROWGAR:
                return m_auiEncounter[0];
        }
        return 0;
    }
 
    uint64 GetData64(uint32 uiData)
    {
        switch(uiData)
        {
            case NPC_LORD_MARROWGAR:
                return m_uiLordMarrowgarGUID;
        }
        return 0;
    }
};
 
InstanceData* GetInstanceData_instance_icecrown_citadel(Map* pMap)
{
    return new instance_icecrown_citadel(pMap);
}
 
void AddSC_instance_icecrown_citadel()
{
    Script* pNewScript;
    pNewScript = new Script;
    pNewScript->Name = "instance_icecrown_citadel";
    pNewScript->GetInstanceData = &GetInstanceData_instance_icecrown_citadel;
    pNewScript->RegisterSelf();
}
 