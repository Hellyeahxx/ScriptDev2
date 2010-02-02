#define DOOR1       0
#define BOSS1       1
#define BOSS2       2
#define BOSS3       3
#define SWAP_Orginal       10
#define SWAP_SWAP     11
 
#define INTRO1         -1900001
#define INTRO2         -1900000
#define INTRO3         -1900002
 
 
//spawn 563.539551 213.565628 395.098206 4.754064
//where they walk to 563.589294 139.645645 393.836578 4.714795
enum
{
    //List of text id's. The text is stored in database, also in a localized version
    //(if translation not exist for the textId, default english text will be used)
    //Not required to define in this way, but simplify if changes are needed.
	//NPC IDS
	Dreadscale = 34799,
	Acidmaw = 35144,
	Gormok = 34796,
	TirionFordring = 34996,
	Icehowl = 34797,
 
    //List of spells.
 
	//BOSS Gormok // FIRST BOSS
    H_stomp   = 67649, // heroic
	stomp   = 66330,
	H_impale = 67477,
    impale  = 67478,
    whirl   = 63666,
	FireBomb = 66313,
	HeadCrack = 66407,
	Batter = 66408,
	RisingAnger = 36300, //workaround
 
 
	//AcidMaw
		//mobile phase
		acidicspew = 66819,
		slimepool  = 66883,
		paralyticbite = 66824,
		//stationary phase
		acidspit = 66880,
		sweep = 66794,
		paralyticspray = 66901,
		enrage = 68335,
		Emerge = 449,
		SubMerge = 373, //not used anymore
 
 //DreadScale Boss
 
		// mobile phase
		burningbite = 66879,
		moltenspew = 66820,
		// statonary phase
		firespit = 66796,
		burningspray = 66902,
 
	 MAX_ENCOUNTER           = 5, // 5 ecounters we will go through
 
    SAY_INTRO         = -1033007,
 
	//DOOR
    GO_MAIN_DOOR       = 195647,                        //door to open when talking to NPC's
 
 
 
};