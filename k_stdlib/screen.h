
#pragma once
#include <ScreenElement.h>

class Screen;

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

class ScreenChild {
public:
    UnkType **array; //pointer to the array of ints/pointers, of length controlCount
    LayoutUIControl **control; //pointer to the array of controls, of length controlCount

    UnkType unknown_0xC;

    Screen *parentScreen;
    u32 controlCount;
};//Total Size 0x14


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
    virtual void func_0x24();
    virtual void Init(); //just a blr
    virtual void clearInstance(); //just a blr
    virtual void func_0x30(); //just a blr   
    virtual void func_0x34(); //just a blr
    virtual void func_0x38(); //just a blr
    virtual void func_0x3C(); //just a blr
    virtual void func_0x40(); //just a blr
    virtual void func_0x44(); //just a blr
    virtual void func_0x48(); //just a blr
    virtual void func_0x4C(); //just a blr
    virtual void func_0x50(); //just a blr
    virtual void func_0x54(); //just a blr
    virtual void func_0x58(); //just a blr
    virtual void func_0x5C(); //just a blr
    virtual int get809cXXXX(); //returns 809C1d10

    void InitScreenChild(u32 controlCount); //inits the sub class and sets the count to a specified value
    void AddControl(u32 arrayPosition, LayoutUIControl *control, u32 r6); //Adds a control to the screnChild control array at a specified position
    u32 screenId;
    UnkType unknown_0x8[3];
    float unknown_0x14[2];
    UnkType unknown_0x1C[2];
    ScreenChild screenChild;
    UnkType unknown_0x38[3];
}; //Total Size 0x44


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


class TTScreen: public RaceScreen { //just an example
    TTScreen(){//806247cc
        u32 gamemode = *(&racedata->main.scenarios[0].settings.gamemode);
        nextScreenId = 0x21;
        if(gamemode == MODE_TIME_TRIAL || gamemode ==  MODE_GHOST_RACE){
            nextScreenId = 0x2D;
        }
    }; 
    virtual void func_vtable(); //0x808be478
};


extern RaceScreen *raceScreen;