#include "msp.h"
#include "..\inc\bump.h"
#include "..\inc\Reflectance.h"
#include "..\inc\Clock.h"
#include "..\inc\SysTickInts.h"
#include "..\inc\CortexM.h"
#include "..\inc\LaunchPad.h"
#include "..\inc\FlashProgram.h"
#include "Ultrasonic.h"

uint8_t readingL, readingC, readingR;
uint32_t i = 0;
int distanceL=0;
int distanceC=0;
int distanceR=0;

void SysTick_Handler(void){ // every 1ms
    if (i%10==0)
        Ultrasonic_Start();
    else if (i%10==1) {
        readingL = UltrasonicL_End();
        readingC = UltrasonicC_End();
        readingR = UltrasonicR_End();
    }
    i++;

    if (readingL==0 && readingC==0 && readingR==0){}
        //i = 0;
    else{
        if(readingL!=0)
            distanceL = (i*1000/2)*343/100;
        else if (readingC!=0)
            distanceC = (i*1000/2)*343/100;
        else if (readingR!=0)
            distanceR = (i*1000/2)*343/100;
    }
}

int main(void){
  // write this as part of Lab 10
    Clock_Init48MHz();
    Ultrasonic_Init();
    SysTick_Init(48000,2);
    LaunchPad_Init();
    EnableInterrupts();
  while(1){
      WaitForInterrupt();
      LPF_Init(distanceL,256);
      LPF_Init(distanceC,256);
      LPF_Init(distanceR,256);

      newDL = LPF_Calc(distanceL);
      newDC = LPF_Calc(distanceC);
      newDR = LPF_Calc(distanceR);
  }
}

