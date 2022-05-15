#include <kamek.h>
#include <racedata.h>
#include <raceinfo.h>
#include <menudata.h>
#include <settings.h>
#include <player.h>
#include <rknetcontroller.h>
#include <musichandler.h>

extern Racedata *racedata;
extern Raceinfo *raceinfo;
extern Settings settings;
extern Rknetcontroller *rknetcontroller;
extern PlayerHolder *player;
extern MusicHandler *musichandler;
extern "C" {
int PlayBRSARSound(int r3, u32 soundId, u32 r5);
void ChangeMusic(MusicHandler *musichandler, RaceState raceState);
}

int miiheads(Racedata *racedata, int r4, int r5, u8 id){
    u32 charId = (&racedata->main)->scenarios[0].players[id].characterId;
    if (settings.miiHeads){
        if (charId < 0x2a){
            if (id == 0){
            charId = 0x2a;
            }
            else if(rknetcontroller->connectionState != 0)
            {
                charId = 0x2a;
            }
        }
    }
    return charId;
}

kmCall(0x807eb154, &miiheads);
kmWrite32(0x807eb15c, 0x60000000);
kmWrite32(0x807eb160, 0x88de01b4);

void musicSpeedup(int r3, u32 jingle, u32 r5){
    RaceinfoPlayer *localPlayer = raceinfo->players[(&racedata->main)->scenarios[0].settings.hudPlayerIds[0]];
    PlayerSound *playerSound = *(&player->players[localPlayer->id]->pointers.playerSound);
	u8 maxLap = localPlayer->maxLap;
    if (maxLap == (&racedata->main)->scenarios[0].settings.lapCount){
        if (settings.finalLapSpeedup){
            Timer *raceTimer = &raceinfo->timerManager->timers[0];
            Timer *playerTimer = &localPlayer->lapFinishTimes[maxLap-2];
            Timer difference = *raceTimer - playerTimer;
            if(difference.minutes < 1 && difference.seconds < 5){
                BasicSound *basicSound = NODE_TO_ITEM(playerSound->brstmData->linkList->initialNode.next, BasicSound, initialNode);
                basicSound->ambientPitch += 0.0002f;
            }
            if (maxLap != playerSound->currentLap){
                PlayBRSARSound(r3, 0x74, r5);
            }
        }
        else{
            if ((maxLap != playerSound->currentLap) && (*(&musichandler->raceState) == 0x4 || *(&musichandler->raceState) == 0x6)){
                ChangeMusic(musichandler, (RaceState)0x5); //0x5 is racestate FAST
            }
        }
    }
    
    else{
        if (maxLap != playerSound->currentLap){
            PlayBRSARSound(r3, jingle, r5);
        }
    }
	return;
}

kmCall(0x8070b2f8, &musicSpeedup);

kmWrite32(0x8070b2c0, 0x60000000);
kmWrite32(0x8070b2d4, 0x60000000);

// Silent Controller Changing
kmCallDefAsm(0x8061AF94){

    nofralloc
    
    lis r12, settings.silentController@ha
    lbz r12, settings.silentController@l(r12)
    cmpwi r12, 0
    bne+ end
    cmpwi r0, 0

    end:
    blr
}