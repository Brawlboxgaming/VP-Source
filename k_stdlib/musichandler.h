#pragma once
#include <egg.h>
#include <common.h>
#include <racedata.h>
#include <kamek.h>

typedef enum RaceState{
	RACEINTRO = 0x2,
	BEFORECOUNTDOWN = 0x3,
	NORMAL = 0x4,
	FAST = 0x5,
	RACEFINISHED = 0x7
};

class MusicHandlerSub{
	u8 unknown_0[0x8-0x0];
	virtual void unknown_vtable();
	//vtable 0x808c91e0
	u8 unknown[0x1c-0xc];
};//total size 0x1C

class MusicHandler : public EGG::Disposer {
public:
	CourseId courseId;
	u8 unknown_0x14[0x30-0x14];
	Timer unk_Timer;
	u8 unknown_0x3C[0x40-0x3C];
	u32 raceState;
	GameMode gameMode;
	GameType gameType;
	u8 unknown_0x4d;
	u8 playerCount;
	u8 unknown_0x4e[0x54-0x4e];
	MusicHandlerSub sub;
	u8 unknown_0x70[0x178-0x70];
};//Total Size 0x178

extern MusicHandler *musichandler;