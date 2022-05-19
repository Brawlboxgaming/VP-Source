#pragma once
#include <kamek.h>
#include <common.h>
#include <screen.h>



class CharacterSelectButtons: public LayoutUIControl{
public:
    CharacterSelectButtons(); //vtable 808d3038
    virtual ~CharacterSelectButtons(); //80627008
    CharacterId selectedCharacter;
    u8 unknown_0x178[0x184-0x178];
    u32 unknown_0x184; //807e25d4
    u32 playerCount;
    bool unknown_0x18C; //result of 8081d020, loop at 0x807e2610
    bool unknown_0x18D; //result of 8081d020
    bool unknown_0x18E; //result of 8081d020
    bool unknown_0x18F; //result of 8081d020
    bool unknown_0x190; //result of 8081d020
    bool unknown_0x191; //result of 8081d020
    bool unknown_0x192; //result of 8081d020
    bool unknown_0x193; //result of 8081d020
    bool unknown_0x194; //result of 8081d020
    bool unknown_0x195; //result of 8081d020
    bool unknown_0x196; //result of 8081d020
    bool unknown_0x197; //result of 8081d020
    bool unknown_0x198; //result of 8081d020
    bool unknown_0x199; //result of 8081d020
    bool unknown_0x19A; //result of 8081d020
    bool unknown_0x19B; //result of 8081d020
    bool unknown_0x19c; //result of 8081d020
    bool unknown_0x19D; //result of 8081d020
    bool unknown_0x19F; //result of 8081d020
    bool unknown_0x1A0; //result of 8081d020
    bool unknown_0x1a3; //result of 8081d020
    bool unknown_0x1A4; //same but outside of the loop
    bool unknown_0x1A5; //same but outside of the loop
    u8 unknown_0x1A6[2];
    u32 unknown_0x1a8; //init at 4
    u32 unlockedCharactersCount; // 0x1a if all unlocked 0x1AC
    UnkType *array_0x1B0; //seems to be a class inherited from PushButton ctor 807e2808 vtable 808D3074
    u32 unknown_0x1B4; 
    ptmfHolder ptmfHolder_0x1B8; //vtable = 0x808bd2c4 function = 807e35fc (onBtnClick)
    ptmfHolder ptmfHolder_0x1CC; //vtable = 0x808bd2c4 function = 807e36f4 (onSelect)
    ptmfHolder ptmfHolder_0x1E0; //vtable = 0x808bd2c4 function = 807e37d4 (onDeselect)
    ptmfHolder ptmfHolder_0x1F4; //vtable = 0x808bd2c4 function = 807e3880 (onMiiBtnClick)   
    ptmfHolder ptmfHolder_0x208; //vtable = 0x808bd2c4 function = 807e39cc (onMiiSelect)  
    ptmfHolder ptmfHolder_0x21C; //vtable = 0x808bd2c4 function = 807e3aac (onMiiDeSelect)
}; //total size 0x230


class VehSelModelPosition : public ModelPosition{ //this c
public:
    VehSelModelPosition(); //805f39bc vtable 808B9B0C 805f39bc
    virtual ~VehSelModelPosition(); //805f39f8

    float unknown_0x180;
}; //Total size 0x184


class CharacterSelectScreen: public InteractableScreen {
public:
    CharacterSelectScreen(); //80626c10
    virtual ~CharacterSelectScreen(); //vtable 808d92c0 
    virtual void onInit(); //8083d55c
    virtual void Load(); //8083da78
    ScreenActionController screenActionController;
    UnkType unknown_0x654;
    ptmfHolder ptmfHolder_0x658; //vtable = 0x808bd1d4 function = 8083e740 on itself
    ptmfHolder ptmfHolder_0x66C; //vtable = 0x808bd1d4 offset = 0x64 call is virtual on itself
    ptmfHolder ptmfHolder_0x680; //vtable = 0x808bd1d4 function = 8083E924 on itself
    ptmfHolder onBackPressHandler; //vtable = 0x808BD1C8 function = 8083E928 (onBackPress)
    ptmfHolder handler; //vtable = 0x808bd1c8 offset = 0x7c call is virtual on itself Handler
    u32 unknown_0x6BC[2]; //constructed at 1
    CharacterSelectButtons buttons;
    UnkType *localPlayerMii;
    u8 unknwon_0x8F8[0x904-0x8f8];
    u32 playerCount; //0x904
    u32 unknwon_0x908;
    UITimer *timer; //0x90c
    UnkType **unk_array_0x910; //pointer to an array of an unknown class inherited from layoutUIControl, of size 0x178
    UnkType **unk_array_0x914; //pointer to an array of an unknown class inherited from layoutUIControl, of size 0x188

}; //Total Size 0x918


class UnkClassVehSel : public LayoutUIControl {
    UnkClassVehSel();//805f39bc vtable 808d3420
    virtual ~UnkClassVehSel(); //80627374
    UnkType **unk_array_0x174; //pointer to an array of an unknown class inherited from layoutUIControl, of size 0x17C 807e7d88 ctor
    UnkType **unk_array_0x178; //pointer to an array of pointers related to machinePara.bin getting dumped
    UnkType **unk_array_0x17c; //same but probably for vehicles and the other for characters?
    u32 unknown_0x180; //init at 0x7
}; //total size 0x184

class VehicleSelectScreen: public InteractableScreen {
public:
    VehicleSelectScreen(); //80627060
    virtual ~VehicleSelectScreen(); //vtable 808d9880
    virtual void onInit(); //80844d68
    virtual void Load(); //80845510
    ScreenActionController screenActionController;
    UnkType unknown_0x654;
    ptmfHolder ptmfHolder_0x658; //vtable = 0x808bd1dc function = 80846c1c on itself (onClick)
    ptmfHolder ptmfHolder_0x66C; //vtable = 0x808bd1dc offset = 0x64 call is virtual on itself (onSelect)
    ptmfHolder ptmfHolder_0x680; //vtable = 0x808bd1dc function = 80846fbc on itself (onDeSelect, just a blr)
    ptmfHolder onBackPressHandler; //vtable = 0x808BD1b0 function = 80846fc0 (onBackPress)
    ptmfHolder handler; //vtable = 0x808bd1b0 offset = 0x7c call is virtual on itself Handler (onStartPress?)
    u32 unknown_0x6BC[2]; //constructed at 1
    u32 unknwown_0x6C4; //init at -1
    bool unknown_0x6C8[0x6EC-0x6C8]; //result of 8081cfb4, always 1 on construct
    u32 unknwon_0x6EC; //init at 2
    UITimer *timer;
    u32 buttonId;
    VehSelModelPosition vehSelModelPosition;
    UnkClassVehSel _0x87c; //808d3420 inherited from LayoutUIControl, 
    float unknown_0xA00;
    float unknown_0xA04;
    u32 unlockedVehiclesCount; //if 3, will display only 3 vehicles, the rest will be ?
   
}; //Total Size 0xA0C


class UnkVehSelBattleStruct :public LayoutUIControl{
public:
    virtual ~UnkVehSelBattleStruct(); //0x8062912c
}; //total size 0x178


class VehicleSelectBattleScreen : public InteractableScreen {
public:
    VehicleSelectBattleScreen(); //80628e3c vtable 0x808D8F40
    virtual ~VehicleSelectBattleScreen(); //8083b014
    ScreenActionController screenActionController;
    UnkType unknown_0x654;
    ptmfHolder ptmfHolder_0x658; //vtable = 0x808bd114 function = 8083A918 on itself (onClick)
    ptmfHolder ptmfHolder_0x66C; //vtable = 0x808bd114 offset = 0x64 call is virtual on itself (onSelect)
    ptmfHolder ptmfHolder_0x680; //vtable = 0x808bd114 function = 8083AB78 on itself (onDeSelect, just a blr)
    ptmfHolder onBackPressHandler; //vtable = 0x808BD108 function = 8083AB80 (onBackPress)
    ptmfHolder handler; //vtable = 0x808BD108 offset = 0x7c call is virtual on itself Handler (onStartPress?)
    u32 unknown_0x6BC[2]; //constructed at 1
    u32 unknwown_0x6C4; //init at -1
    UITimer *timer;
    u32 unknown_0x6CC;
    VehSelModelPosition modelPosition; //0x6D0
    UnkVehSelBattleStruct unkClass; //0x854
    UnkClassVehSel  _0x9cc;

}; // Total Size 0xb50


class DriftSelectScreen: public InteractableScreen {
public:
    DriftSelectScreen(); //806273cc
    virtual ~DriftSelectScreen(); //vtable 808d9db0
    virtual void onInit(); //8084ddfc might be for 6c
    virtual void Load(); //8084e13c
    ScreenActionController screenActionController;
    UnkType unknown_0x654;
    ptmfHolder ptmfHolder_0x658; //vtable = 0x808bd15c function = 8084e388 on itself (onClick)
    ptmfHolder ptmfHolder_0x66C; //vtable = 0x808bd15c offset = 0x64 call is virtual on itself (onSelect)
    ptmfHolder ptmfHolder_0x680; //vtable = 0x808bd15c function = 8084e6f4 on itself (onDeSelect, just a blr)
    ptmfHolder onBackPressHandler; //vtable = 0x808BD1150 function = 8084e6f8 (onBackPress)
    ptmfHolder handler; //vtable = 0x808bd150 offset = 0x7c call is virtual on itself Handler
    u32 playerCount; //0x6BC
    u32 unknown_0x6C0;
    UITimer *timer; //0x6C4
    MenuType menuId;
   
}; //Total Size 0x6CC


class ScreenElementTimer : public LayoutUIControl{
public:
    ScreenElementTimer(); //0x805C3CD4
    virtual ~ScreenElementTimer(); //805c3d18
    virtual void OnUpdate(); //805c407c
    virtual void BeforeChildUpdate(); //80650218
    virtual void AfterChildUpdate(); //80650274
    virtual void func_vtable(); //vtable 0x808b7dc0

    UITimer *timer;
    bool unknown_0x178;
    u8 unknown_0x179[0x17C-0x179];
}; //total size 0x17C

class InputThing{
public:
    InputThing(); //805eeb68 0x808b9a98 vtable is full of functions that perfom slw/and, likely to check an input
    virtual void func_vtable();
    virtual void OnInit(); //8064fcfc
    u32 playerFlags;
    u8 unknown_0x8[0xC-0x8];
    bool unknown_0xC;
    bool isMultiplayer;
    u8 unknown_0xE[0x10-0xE];
};//total size 0x10

struct PlayerInfo{
    u8 aid; //shared by players on the same console
    u8 hudSlotid; //0 for P1, 1 for P2 on the same console etc....
    u8 unknown_0x2[2]; //never stored likely padding
    u32 team; //0x2 if no team (depending on the menu), 0x0 blue, 0x1 red 0x1F8
    u16 randomThing; //806519c4, no idea, gets the current license then does a bunch of operations 0x1FC
    u16 randomThing2; //80651a20, very similar, but uses a different address to start the operations
};//total size0xC

class TimerScreen : public Screen {
public:
    TimerScreen(); //8064fbdc vtable 0x808c069c
    virtual ~TimerScreen(); //8064fc70
    virtual void OnResume(); //806507a0

    ptmfHolder disconnectHandler;
    InputThing inputThing;
    TimerScreenStatus status; //0x68
    UITimer timer; //0x6C
    ScreenElementTimer TimerElement; //0x78
    PlayerInfo infos[12]; //large loop at 0x80651980, one per player it seems
    u32 unknown_0x284;
    u32 engineClass;
    u32 battleType; //init at 2 8064fe14
    MiiGroup miiGroup; //0x290
}; //total size 0x328

class CtrlMenuPageTitleText : public LayoutUIControl{
public:
    virtual ~CtrlMenuPageTitleText(); //805baf10 vtable 0x808d36d4 
}; //total size 0x174


class CtrlMenuBottomMessage : public LayoutUIControl{
public: 
    virtual ~CtrlMenuBottomMessage(); //805c00c0 vtable 0x808d3698 named based on string in the UIControl part
}; //total size 0x174


class VotingScreen : public Screen {
public:
    VotingScreen(); //8064a3f4 vtable 0x808bfd0c
    virtual ~VotingScreen(); //0x8064a4e0
    ptmfHolder disconnectHandler; //purely based on the previous screen 808bfd70 8064ae6c
    ScreenActionController screenActionController; 
    CtrlMenuPageTitleText ctrlMenuBackButton;
    CtrlMenuBottomMessage ctrlMenuBottomMessage;
    PushButton pushButton; //0x564
    LayoutUIControl vrScreenElements[12];
    u32 unknown_0x1928;
}; //total size 0x192c








class RaceScreen: public Screen {
public:
    RaceScreen(); //ctor seems inlined, vtable 0x808da710
    virtual ~RaceScreen();
    virtual int getNextScreen();
    virtual void func_0x20();
    virtual void Init();
    virtual void clearInstance(); //sets 0x809c4680 to 0
    virtual void func_0x34(); //sets 0x44 to 0
    virtual void func_0x48(); //extensively patched in advanced watch replay
    virtual void func_0x4C(); //also patched in advanced watch replay
    virtual int get809cXXXX(); //returns 809C4640
    int getCtrlRaceBaseCount(); //returns how screen elements there should be
    void InitCtrlRaceBase(u32 bitField); //inits all of the screen elements 

    u32 nextScreenId;
    UnkClass unkClass;
    UnkClass2 unkClass2;
    u8 unknown_0x1C0[0x1DC-0x1C0]; //based on all of the new such as 806234f4
}; //Total Size 0x1DC

class TTScreen: public RaceScreen { //just an example, ID 0xd
    TTScreen(){//806247cc
        u32 gamemode = *(&raceData->main.scenarios[0].settings.gamemode);
        nextScreenId = 0x21;
        if(gamemode == MODE_TIME_TRIAL || gamemode ==  MODE_GHOST_RACE){
            nextScreenId = 0x2D;
        }
    }; 
    virtual void func_vtable(); //0x808be478
};






extern RaceScreen *raceScreen;