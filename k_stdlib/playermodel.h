#pragma once
#include <egg.h>
#include <kamek.h>

class PlayerModelBones;
class MiiHeadsModel;

class PlayerModel : public EGG::Disposer {
public:
  /*PlayerPointers *PlayerPointers;
  u8 unknown_0x4[0x8-0x4];
  ItemHolderPlayer *unknown_0xC;*/
  //virtual int unknown_vtable(); //vtable 0x808d2ad8
  u8 unknown_0x10[0x38-0x10];
  u32 trickType;
  u32 trickDirection;
  u8 unknown_0x40[0x64-0x40];
  UnkType *unknown_0x64[4];
  float unknown_0x78[0xA8-0x78]; //related to the character, direction they are looking at, angle, scale, etc...
  bool isCpu;
  u8 unknown_0xa9[0xB8-0xA9];
  UnkType *unknown_0xB8;
  Vec3 unknown_0xBC;
  bool isHq;
  u8 unknown_0xC9[0xCC-0xC9];
  UnkType *unknown_0xCC[2];
  u8 unknown_0xD4[2];
  bool isNotFocusedInLiveView;
  u8 unknown_0xD7[2];
  UnkType unknown_0xD8[2];
  u8 unknown_0xE0[0xfa-0xe0];
  u16 currentAnimation;
  u16 lastAnimation;
  u8 unknown_0xF8[0x100-0xf8];
  MiiHeadsModel *miiHeads; //0x807c795c
  PlayerModelBones *bones;
  u8 unknown_0x108[0x10c-0x108];
  char* characterName;
  u8 unknown_0x110[0x6e4-0x110];
};//total size 0x6e4

class ModelDirector{
public:
  ModelDirector(); //0x8055b298 vtable 808d2e10
  virtual ~ModelDirector(); //0x8055b5bc
  u32 unk_bitfield;
  u32 unknown_0x8;
  void *rawData; //MDL0 magic? seems to be wrong
  UnkType *g3dHolder;
  UnkType g3dHolderList[2];
  u32 unknown_0x1c[2];
  u32 isTransparent;
  UnkType *modelTransformator;
  UnkType unknown_0x2c[0x44-0x2c];
  UnkType objRenderer;
  u32 unknown_0x4C;
}; //total size 0x4c

class MiiHeadsModel : public ModelDirector {
public:
  MiiHeadsModel(); //807dbe0c 808d2e10
  virtual ~MiiHeadsModel(); //807d6860
  u8 unknown_0x4c[0x70-0x4c];
}; //total size 0x70