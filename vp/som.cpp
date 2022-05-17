#include <vp.h>

void CtrlRaceSpeedo::Load(char* variant, u8 id){ //blatant copy
   this->hudSlotId = id;
   ScreenController screenController(this);
   const char* anims[10] = {"eHundreds", "texture_pattern_0_9_0", NULL, "eTens", "texture_pattern_0_9_1", NULL, "eUnits", "texture_pattern_0_9_2", NULL, NULL};

   screenController.LoadCtr("game_image", "speedometer", variant, anims);
   void *effectPointer = this->AnimationThing.EffectById(0);
   DisplayEffect(effectPointer, 0, 0.0f);
   effectPointer = this->AnimationThing.EffectById(1);
   DisplayEffect(effectPointer, 0, 0.0f);
   effectPointer = this->AnimationThing.EffectById(2);
   DisplayEffect(effectPointer, 0, 0.0f);
}

void CtrlRaceSpeedo::Init(){
   this->HudSlotColorEnabled("speed0", true);
   this->HudSlotColorEnabled("speed1", true);
   this->HudSlotColorEnabled("speed2", true);
   this->HudSlotColorEnabled("kmh", true);
   LayoutUIControl::Init();
}

void CtrlRaceSpeedo::OnUpdate(){
   this->UpdatePausePosition();
   u8 id = this->getPlayerId();
   u32 engineSpeed = (u32) (fabs((playerHolder->players[id]->pointers.playerSub10->vehicleSpeed)) + 0.5f);
   float hundreds;
   float tens;
   float units;
   units = (float) (engineSpeed % 10 / 1);  
   tens = (float) (engineSpeed % 100 / 10);
   hundreds = (float) (engineSpeed % 1000 / 100);
   if (engineSpeed < 10){
      tens = 10.0f;
      hundreds = 10.0f;
   }
   else if (engineSpeed < 100) {
      hundreds = 10.0f;
   }

   void *effectPointer = this->AnimationThing.EffectById(2); //third digit
   DisplayEffect(effectPointer, 0, units);
   effectPointer = this->AnimationThing.EffectById(1); //second digit
   DisplayEffect(effectPointer, 0, tens);
   effectPointer = this->AnimationThing.EffectById(0); //first digit
   DisplayEffect(effectPointer, 0, hundreds);
}

void patchCtrlRaceBaseCount(RaceScreen *raceScreen, u32 controlCount)
{
   u8 localPlayerCount = *(&raceData->main.scenarios[0].localPlayerCount);
   raceScreen->InitControlGroup(controlCount + localPlayerCount);
}

void createSOM(RaceScreen *raceScreen, u32 bitField){
   u8 localPlayerCount = *(&raceData->main.scenarios[0].localPlayerCount) ; //to make it 0 indexed
   u32 firstIndex = raceScreen->scontrolGroup.controlCount - localPlayerCount;
   for (int i = 0; i < localPlayerCount; i++){
      CtrlRaceSpeedo *som = new(CtrlRaceSpeedo);
      raceScreen->AddControl(firstIndex + i, som, 0); //If 0x9 screens, in solo localplayer = 1, 
      u8 speedoType = localPlayerCount;
      if(localPlayerCount == 3) speedoType = 4;
      char variant[0x20];
      snprintf(variant, 0x20, "CtrlRaceSpeedo_%1d_%1d", speedoType, i);
      som->Load(variant, i);
   }
   raceScreen->InitCtrlRaceBase(bitField);
}

kmCall(0x808562d0, &patchCtrlRaceBaseCount);
kmCall(0x808562dc,&createSOM);