/*
InputData is the class that handles all controller inputs
Contributors:
  Seeky (main documentation)
  SwareJonge
  _tZ
*/

#pragma once
#include <common.h>
#include <kamek.h>

typedef enum UniversalButtons{
  BUTTON_DPAD_LEFT,
  BUTTON_DPAD_RIGHT,
  BUTTON_DPAD_DOWN,
  BUTTON_DPAD_UP,
  BUTTON_A,
  BUTTON_B,
  BUTTON_X,
  BUTTON_Y,
  BUTTON_MINUS,
  BUTTON_PLUS,
  BUTTON_HOME,
  BUTTON_1,
  BUTTON_2,
  BUTTON_L,
  BUTTON_R,
  BUTTON_C,
  BUTTON_Z,
  BUTTON_ZL,
  C_STICK_LEFT,
  C_STICK_RIGHT,
  C_STICK_DOWN,
  C_STICK_UP
};

typedef enum Buttons{
  WHEEL_DPAD_LEFT=0x1,
  WHEEL_DPAD_RIGHT=0x2,
  WHEEL_DPAD_DOWN=0x4,
  WHEEL_DPAD_UP=0x8,
  WHEEL_A=0x800,
  WHEEL_B=0x400,
  WHEEL_MINUS=0x1000,
  WHEEL_PLUS=0x10,
  WHEEL_HOME=0x8000,
  WHEEL_1=0x200,
  WHEEL_2=0x100,

  NUNCHUCK_DPAD_LEFT=0x1,
  NUNCHUCK_DPAD_RIGHT=0x2,
  NUNCHUCK_DPAD_DOWN=0x4,
  NUNCHUCK_DPAD_UP=0x8,
  NUNCHUCK_A=0x800,
  NUNCHUCK_B=0x400,
  NUNCHUCK_MINUS=0x1000,
  NUNCHUCK_PLUS=0x10,
  NUNCHUCK_HOME=0x8000,
  NUNCHUCK_1=0x200,
  NUNCHUCK_2=0x100,
  NUNCHUCK_C=0x4000,
  NUNCHUCK_Z=0x2000,

  CLASSIC_DPAD_LEFT=0x2,
  CLASSIC_DPAD_RIGHT=0x2000,
  CLASSIC_DPAD_DOWN=0x4000,
  CLASSIC_DPAD_UP=0x1,
  CLASSIC_A=0x10,
  CLASSIC_B=0x40,
  CLASSIC_X=0x8,
  CLASSIC_Y=0x20,
  CLASSIC_MINUS=0x1000,
  CLASSIC_PLUS=0x40,
  CLASSIC_HOME=0x800,
  CLASSIC_L=0x2000,
  CLASSIC_R=0x200,
  CLASSIC_ZL=0x80,
  CLASSIC_Z=0x4,

  GCN_DPAD_LEFT=0x1,
  GCN_DPAD_RIGHT=0x2,
  GCN_DPAD_DOWN=0x4,
  GCN_DPAD_UP=0x8,
  GCN_A=0x100,
  GCN_B=0x200,
  GCN_X=0x400,
  GCN_Y=0x800,
  GCN_Z=0x10,
  GCN_START=0x1000,
  GCN_L=0x40,
  GCN_R=0x20
};


class InputState {
public:
  virtual void unknown_vtable();
  // vtable 808b2f2c
  u16 buttonActions; // bit flags:
    /* 
      0x1 = accelerate
      0x2 = brake + reverse (used for SSMT)
      0x4 = use item
      0x8 = hop + drift
      0x20 = rear-view camera
    */
  u16 buttonRaw; // bit flags, vary slightly by controller
  float stickX; // -1.0 to 1.0
  float stickY; // -1.0 to 1.0
  u8 quantisedStickX; // 0-14
  u8 quantisedStickY; // 0-14
  u8 motionControlFlick; // 1 up, 2 down, 3 left, 4 right; includes the first frame of d-pad presses
  u8 motionControlFlick2; // not sure what the difference is from the other one
  u8 unknown_0x14[0x18-0x14];
}; // Total size 0x18

struct GCNStruct{
  u8 unknown_0x94[0x94];
  s8 horizontalCStick;
  s8 verticalCStick; // -50 to 50
};

class ControllerHolder {
public:
  ControllerHolder(); // 80520f64 - inlined in RealControllerHolder()
  virtual ~ControllerHolder(); // 805222b4
  virtual int unknown1(); // 80521198
  virtual int unknown2(); // 80521110
  virtual int unknown3();// 805226f4
  virtual int unknown4();// 8051ce84
  virtual int  unknown5();// 8051ce8c
  virtual int  unknown6();// 80520ebc
  // vtable 808b2dd8
  GCNStruct *gcnStruct;
  u8 unknown_0x8[0x28-0x8];
  InputState inputStates[2]; // 0 is current frame, 1 is previous
  u8 unknown_0x58[0xd8-0x58];
}; // Total size 0xd8

class RealControllerHolder : public ControllerHolder {
public:
  RealControllerHolder(); // 805220bc
  virtual ~RealControllerHolder(); // 805222f4
  virtual int  unknown1(); // 80521768
  virtual int unknown2(); // 80522708
  virtual int unknown4(); // 80522700
  virtual int unknown5(); // 805226f8
  virtual int unknown6(); // 80520ebc
  
  // vtable 808b2d90
  void * rkgInputBuffer; // 0x2774 byte buffer for storing a controller input section of an RKG file
  u8 unknown_0xdc[0xe8-0xdc];
  void * unknown_0xe8; // 0x1c class with constructor 80524ac4
}; // Total size 0xec

class VirtualControllerHolder : public ControllerHolder {
public:
  virtual ~VirtualControllerHolder(); // 8052279c
  virtual int unknown3(); // 805219ac
  
  // vtable 808b2db4
  u8 unknown_0xd8[0x180-0xd8];
}; // Total size 0x180

class InputData {
public:
  static InputData * sInstance; // 809bd70c
  static InputData * getStaticInstance(); // 8052313c
  static void destroyStaticInstance(); // 8052318c
  InputData(); // 805232f0
  virtual ~InputData(); // 805231dc
  // vtable 808b2fc8
  RealControllerHolder realControllerHolders[4]; // Stores inputs from a real controller at the same console
  VirtualControllerHolder virtualControllerHolders[12]; // Stores inputs for all the other players in a race (I think the ones with a matching realControllerHolder go unused)
  u8 unknown_0x15b4[0x415c-0x15b4];
}; // Total size 0x415c

extern InputData *inputdata;