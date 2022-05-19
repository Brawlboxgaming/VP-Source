/*
Credits:
kHacker35000vr and the Sanbo team (dolphin map, ScreenText)
stebler (names for some of the classes)
Melg
*/

#pragma once
#include <kamek.h>
#include <racedata.h>
#include <raceinfo.h>
#include <menudata.h>

class LayoutUIControl;
class Screen;
class ScreenActionController;
class PushButton;

typedef enum TimerScreenStatus{
    STATUS_WAITING = 0x2,
    STATUS_VR_SCREEN,
    STATUS_CUP_SELECT,
    STATUS_VOTES_SCREEN,
    STATUS_DISCONNECTED,
    STATUS_DISCONNECT_MSG = 0x8
};


typedef enum ScreenInput{ //each value represent an action, itself represented by an actionHandler in PushButton's screenElementActionHolder and a bool in the same struct 
    FORWARD_PRESS,
    BACK_PRESS,
    START_PRESS,
    UP_PRESS,
    DOWN_PRESS,
    LEFT_PRESS,
    RIGHT_PRESS,
    UNK_PRESS,
    SWITCH_PRESS //minus and Z 
};



struct UITimer{
    float value;
    bool isActive;
    u8 unknown_0x5[3];
    u32 seconds;
};//total size 0xC

struct PositionAndScale{
    Vec3 position;
    Vec2 scale;
    u8 opacity;
    u8 unknown_0x15[0x18-0x15];
}; //Total Size 0x18


class AnimationThing{
public:
    AnimationThing(); //0x8063c3ec
    UnkType *array; 
    u32 animationCount; //Unsure
    u32 unknown_0x0[2]; //2nd and 3rd stored at 0x8063c464 check Ghidra
    void *EffectById(u32 id);
}; //Total Size 0x10

class BMGThing{
public:
    BMGThing(); //0x805f8b34
    u32 *pointer_0x0;
    u32 *pointer_0x4;
    u32 *pointer_0x8; //points to UTF-16 strings of all bmg messages
    u32 unknown_0xC;
    u32 *pointer_0x10;
}; //Total Size 0x14

class ParentScreenLayout{
public:
    virtual ~ParentScreenLayout(); //vtable 808b950c
    nw4r::lyt::Layout layout; //from 0x0 to 0x0
    UnkType *pointer1_0x24;    //0x24
}; //Total size 0x28

class ScreenLayout : ParentScreenLayout {
public:
    ScreenLayout(); //vtable 808b94c4
    virtual ~ScreenLayout(); 
    char string[0x44]; //from 0x28 to 0x6
    u8 unknown_0x6C[0x9C-0x6C];
}; //Total Size 0x9C

class ControlGroup {
public:
    ControlGroup(); //0x805C23E4
    ~ControlGroup(); //0x805c2400
    LayoutUIControl **controlArray; //pointer to the array of controls
    LayoutUIControl **controlArray2; //pointer to the array of controls, of length controlCount, idk what is the difference look the same in game
    UnkType unknown_0x8;
    Screen *parentScreen;
    u32 controlCount;
};//Total Size 0x14


class UIControl { 
public:
    UIControl(); 
    virtual ~UIControl();  //vtable 808bf008
    virtual void Init();
    virtual void Update();
    virtual void Draw(); //inferred from the name of the child overriden function
    virtual void InitSelf(); //just a blr
    virtual void OnUpdate(); //just a blr
    virtual void setPosition(); 
    virtual void func_805BD2DC(); //just a blr
    virtual int get809cXXXX(); //returns 809c1e80
    virtual char* getClassName(); //how the class name was found
    virtual void func_0x30();
    virtual void func_805bd2d8(); //just a blr
    PositionAndScale positionAndscale[4]; //same structs repeats itself 4 times, but only the last one seems to do anything?
    UnkType *pointer; //0x64 points to the parent class holding all screens 
    ControlGroup controlGroup; 
    bool isVisible;
    u32 isVisible2; //setting this to anything but 0 removes the element
    bool unknown_0x84;
    u8 unknown_0x85[0x8C-0x85];
    float unknown_0x8C;
    u32 unknown_0x90[2];
}; //Total Size 0x98

class LayoutUIControl : public UIControl {
public:
    LayoutUIControl(); //0x8063d798
    virtual ~LayoutUIControl(); //vtable 808befb4
    virtual void Init();
    virtual void Update();
    virtual void Draw();
    virtual int get809cXXXX(); //returns 809c1e84
    virtual char* getClassName(); //how the class name was found
    virtual void func_0x30(); //called screen_buttonHolder
    virtual void func_0x38(); //called screen_buttonHolder too

    AnimationThing AnimationThing;
    ScreenLayout screenLayout;
    BMGThing bmgThing1;
    BMGThing bmgThing2;
    UnkType *pointer_0x16C;
    u32 unknown_0x170;
};//Total Size 0x174

class UnkClass {
public:
    UnkClass(); //seems to be inlined everytime
    virtual void func_vtable(); //0x808A2D44
    Timer timer;
    u8 unknown_0xC;
    u8 unknown_0xD[0x1C-0xD];
    u32 unknown_0x1C;
    u8 unknown_0x20[0x38-0x1C];
}; //Total Size 0x38

struct UnkArray{
    u8 unknown_0x0[0x104-0x0]; //each element is 0x34 bytes long
}; //Total Size 0x104

class UnkClass2 {
public:
    UnkClass2(); //805ef240
    ~UnkClass2(); //805ef2fc
    virtual void func_vtable(); //0x808b9a48
    u8 unknown_0x20[0x3C-0x0]; //has an array of something
    UnkArray array[5];
}; //Total Size 0x144


class Screen {
public:
    Screen(); //8060197c, vtable 0x808ba5c0
    virtual ~Screen();
    virtual int getPage(); //returns "(unknown page)"
    virtual int getNextScreen(); //returns -1
    virtual int func_0x14(); //returns 0
    virtual int func_0x18(); //returns 1 
    virtual void func_0x1C();
    virtual void func_0x20();
    virtual void AddScreenLayer(ScreenType id); //806025b0
    virtual void OnInit(); //just a blr
    virtual void clearInstance(); //just a blr
    virtual void OnLoad(); //just a blr   
    virtual void OnUnload(); //just a blr
    virtual void OnActivate(); //just a blr
    virtual void OnFocus(); //just a blr
    virtual void OnDefocus(); //just a blr
    virtual void func_0x44(); //just a blr
    virtual void BeforeChildUpdate(); //just a blr
    virtual void AfterChildUpdate(); //just a blr
    virtual void OnUpdate(); //just a blr
    virtual void OnResume(); //just a blr
    virtual void func_0x58(); //just a blr
    virtual void func_0x5C(); //just a blr
    virtual int get809cXXXX(); //returns 809C1d10
    void InitControlGroup(u32 controlCount); //inits the sub class and sets the count to a specified value
    void AddControl(u32 arrayPosition, LayoutUIControl *control, u32 r6); //Adds a control to the screnChild control array at a specified position
    void Setup(ScreenType screenId);
    void setActionController(); //0x80602474
    u32 screenId;
    UnkType unknown_0x8[3];
    float unknown_0x14[2];
    UnkType unknown_0x1C[2];
    ControlGroup controlGroup;
    ScreenActionController *screenActionController;
    UnkType unknown_0x3C[2];
}; //Total Size 0x44


class ScreenText {
public:
    u32 Unknown_0x0[9];
    u32 bmgId[9];
    u32 miis[9];
    u8 licenseId[9];
    u8 unknown_0x75[3];
    u32 playerId[9];
    UnkType *strings[9]; //no idea
    bool useColoredBorder;
    char unknown_0xC1[3];
}; //total size 0xC4

class ScreenElementActionHolder{
public:
    ScreenElementActionHolder *nextHolder; 
    ScreenElementActionHolder *prevHolder;
    virtual void unk_vtable(); //808b9a20
    UnkType *Pane;
    float unk;
    u8 unknown_0x14[0x24-0x14];
    ptmfHolder *onSelectHandler;
    ptmfHolder *onDeselectHandler;
    u8 unknown_0x2c[0x3c-0x2c];
    void *pointer_0x3c;
    ptmfHolder *actionHandlers[8]; //each corresponds to a ScreenInput
    u32 unknown_0x60;
    bool actionsSet[8]; //same
    u8 unknown_0x6c[0x84-0x6c];
}; //total size 0x84

class PushButton : public LayoutUIControl{
public:
    virtual void unk_vtable(); //0x808b776c
    ScreenElementActionHolder actionHolder;
    ptmfHolder onSelectHandlerObj;
    ptmfHolder onDeselectHandlerObj;
    ptmfHolder onclickHandlerObj;
    ptmfHolder *onClickHandler;
    ptmfHolder *onSelectHandler;
    ptmfHolder *onDeselectHandler;
    u32 buttonId;
    u32 playerCount;
    u8 unknown_0x248[0x254-0x248];
    void HandleClick(u32 r4, u32 r5);
};//Total Size 0x254

class ScreenActionHolderList{
public:
    virtual void func_vtable();
    ScreenElementActionHolder *actionHolder;
    u32 unknown_0x8;
}; //total size 0xc

class ButtonInfo {
public:
    virtual void func_vtable();
    u32 forwardPressTime; //2 or A
    u32 backPressTime; //1 or B
    u32 startPressTime; //+ or start
    u32 upPressTime;
    u32 downPressTime;    
    u32 leftPressTime;
    u32 rightPressTime;
    u32 unknown_0x20;
    u32 spectateSwitchPressTime; //- + x + z
    u8 unknown_0x28[0x34-0x28];
}; //total size 0x34

class ScreenActionHandler{
public:
    ScreenElementActionHolder *curActionHolder;
    u8 unknown_0x4[4];
    ButtonInfo buttonInfo;
    u32 enabledHandlers;
    u32 resetTime;
    u8 unknown_0x44[0x5C-0x44];
}; //total size 0x5C

class ScreenActionController{
public:
    virtual void func_vtable(); //0x808b99e8
    u32 playerCount;
    u8 unknown_0x8[0x10-0x8];
    ScreenActionHolderList screenActionHolderList;
    ptmfHolder *handlers[9];
    u8 unknown_0x40[0x54-0x40];
    ScreenActionHandler actionHandlers[5];
    UnkType calcDistanceFunc;
    void SetHandler(ScreenInput id, ptmfHolder *handler, bool enable, bool r7);
};//total size 0x224

class CtrlMenuBackButton : public PushButton {
    u32 bmgId;
    UnkType unknown_0x258;
    float alpha;
    char* pane;
}; //total size 0x264

class ModelPosition : public LayoutUIControl {
public:
    ModelPosition(); //805f42b4 vtable 808b9ad0
    virtual ~ModelPosition(); //805f42f0
    void onInit(); //80837134
    bool unknown_0x174;
    u8 unknown_0x175[3]; //might be padding
    u32 unknown_0x178; //result of 805f5a98, which seems to be the init func
    bool unknown_0x17C;
    u8 unknown_0x17D[3]; //might be padding
};

class InteractableScreen : public Screen {
public:
    InteractableScreen(); //seems to be inlined vtable 808d8d78
    virtual ~InteractableScreen();
    void Init(); //80836b9c
    void LoadNextScreen(ScreenType id, u32 animId); //80837720
    MiiGroup *playerMiis; //from MenuData98 //0x44
    PushButton **externObjects; //array to the PushButtons of all the buttons probably
    u32 externObjectsCount;
    PushButton *curSelect; //0x50
    CtrlMenuBackButton backButton; //0x54
    LayoutUIControl *topMenuTitle;
    LayoutUIControl *bottomMenu;
    u8 unknown_0x2C0[0x310-0x2C0];
    u32 videoCount;
    ScreenText text;
    u32 layoutCount;
    bool hasBackButton;
    u8 extraControlype; //affects controlCount
    u8 unknown_0x3DE[0x3E0-0x3dE];
    ModelPosition **modelPosition; //array [extraControlNumber] elements
    u32 titleBmgId;
    ScreenType nextScreenId;
    ScreenType prevScreenId;
    MenuType prevMenu;
    MenuType nextMenu;
    u32 controlSources; //0x80836cc8
    ptmfHolder loadPrevMenuPtmf;
    ptmfHolder initThpPtmf;
    u32 videoStartFrame;
    u32 extraControlNumber; //depends on the amount of local players and the screen
    bool isLocked;
    u8 unknown_0x42D[0x430-0x42D];
}; //total size 0x430

