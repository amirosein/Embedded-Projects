#include "mbed.h" 
#include <iostream>      
#include <string>  
#include <stdio.h>
#include <stdlib.h>  
using namespace std;

InterruptIn switch1(PTD1);

DigitalOut EMERGENCY_LED(PTE1);

DigitalOut EASTR_LED(PTE3);
DigitalOut EASTY_LED(PTE2);
DigitalOut EASTG_LED(PTB11);

DigitalOut NORTHR_LED(PTC1);
DigitalOut NORTHY_LED(PTC2);
DigitalOut NORTHG_LED(PTB3);

DigitalOut NORTHLEFTR_LED(PTB2);
DigitalOut NORTHLEFTY_LED(PTB1);
DigitalOut NORTHLEFTG_LED(PTB0);

DigitalOut NORTHBUSR_LED(PTE30);
DigitalOut NORTHBUSY_LED(PTE23);
DigitalOut NORTHBUSG_LED(PTE29);

DigitalOut WESTBUSR_LED(PTB10);
DigitalOut WESTBUSY_LED(PTB9);
DigitalOut WESTBUSG_LED(PTB8);

DigitalOut SOUTHBUSR_LED(PTD7);
DigitalOut SOUTHBUSY_LED(PTE5);
DigitalOut SOUTHBUSG_LED(PTE4);

int EMERGENCY_YELLOW_TIME=0.5;
typedef enum {GoE,WaitE,GoN,WaitN,GoNW,WaitNW} state_t;
state_t state;

void turnOff(){
 EASTR_LED=0;
 EASTY_LED=0;
 EASTG_LED=0;

 NORTHR_LED=0;
 NORTHY_LED=0;
 NORTHG_LED=0;

 NORTHLEFTR_LED=0;
 NORTHLEFTY_LED=0;
 NORTHLEFTG_LED=0;

 NORTHBUSR_LED=0;
 NORTHBUSY_LED=0;
 NORTHBUSG_LED=0;

 WESTBUSR_LED=0;
 WESTBUSY_LED=0;
 WESTBUSG_LED=0;

 SOUTHBUSR_LED=0;
 SOUTHBUSY_LED=0;
 SOUTHBUSG_LED=0;
    }

void intrupt1(){
    
     switch (state){
                case GoE:
                    turnOff();  

                    NORTHR_LED=1;
                    NORTHLEFTR_LED=1;
                    NORTHBUSR_LED=1;
                    SOUTHBUSR_LED=1;

                    EASTY_LED=1;
                    WESTBUSY_LED=1;
                    wait(EMERGENCY_YELLOW_TIME);
                    EASTR_LED=1;
                    WESTBUSR_LED=1;
                    wait(0.1);
                    EMERGENCY_LED=1;
                    wait(3);
                    break;

                case WaitE:

                    turnOff();

                    EASTR_LED=1;
                    NORTHR_LED=1;
                    NORTHLEFTR_LED=1;
                    NORTHBUSR_LED=1;
                    WESTBUSR_LED=1;
                    SOUTHBUSR_LED=1;
         

                    wait(0.1);
                    EMERGENCY_LED=1;
                    wait(3);
                     break;
                 case GoN:

                    turnOff();

                    EASTR_LED=1;
                    NORTHY_LED=1;
                    NORTHLEFTR_LED=1;
                    NORTHBUSY_LED=1;
                    WESTBUSR_LED=1;
                    SOUTHBUSY_LED=1;

                    wait(EMERGENCY_YELLOW_TIME);

                    NORTHR_LED=1;
                    NORTHBUSR_LED=1;              
                    SOUTHBUSR_LED=1;

                    wait(0.1);
                    EMERGENCY_LED=1;
                    wait(3);
                     break;   
                case WaitN:

                    turnOff();

                    EASTR_LED=1;
                    NORTHR_LED=1;
                    NORTHLEFTR_LED=1;
                    NORTHBUSR_LED=1;
                    WESTBUSR_LED=1;
                    SOUTHBUSR_LED=1;

                    wait(0.1);
                    EMERGENCY_LED=1;
                    wait(3);

                    break;
                case GoNW:

                    turnOff();

                    EASTR_LED=1;
                    NORTHY_LED=1;
                    NORTHLEFTY_LED=1;
                    NORTHBUSR_LED=1;
                    WESTBUSR_LED=1;
                    SOUTHBUSR_LED=1;

                    wait(EMERGENCY_YELLOW_TIME);

                    NORTHR_LED=1;
                    NORTHLEFTR_LED=1;

                    wait(0.1);
                    EMERGENCY_LED=1;
                    wait(3);
                    break; 

                case WaitNW:

                    turnOff();

                    EASTR_LED=1;
                    NORTHR_LED=1;
                    NORTHLEFTR_LED=1;
                    NORTHBUSR_LED=1;
                    WESTBUSR_LED=1;
                    SOUTHBUSR_LED=1;

                    wait(0.1);
                    EMERGENCY_LED=1;
                    wait(3);
                     break; 
            }
    }
int main() {
    state=GoE;
    switch1.rise(&intrupt1);
  while (1) 
        {
            switch (state){
                case GoE:

                    turnOff();

                    EASTG_LED=1;
                    NORTHR_LED=1;
                    NORTHLEFTR_LED=1;
                    NORTHBUSR_LED=1;
                    WESTBUSG_LED=1;
                    SOUTHBUSR_LED=1;

                     wait(35);
                     state=WaitE;
                     break;

                case WaitE:

                    turnOff();

                    EASTY_LED=1;
                    NORTHR_LED=1;
                    NORTHLEFTR_LED=1;
                    NORTHBUSR_LED=1;
                    WESTBUSY_LED=1;
                    SOUTHBUSR_LED=1;

                     wait(3);
                     state=GoN;
                     break;
                 case GoN:

                    turnOff();

                    EASTR_LED=1;
                    NORTHG_LED=1;
                    NORTHLEFTR_LED=1;
                    NORTHBUSG_LED=1;
                    WESTBUSR_LED=1;
                    SOUTHBUSG_LED=1;

                     wait(15);
                     state=WaitN;
                     break;   
                case WaitN:

                    turnOff();

                    EASTR_LED=1;
                    NORTHY_LED=1;
                    NORTHLEFTR_LED=1;
                    NORTHBUSY_LED=1;
                    WESTBUSR_LED=1;
                    SOUTHBUSY_LED=1;

                    wait(3);
                    state=GoNW;
                    break;
                case GoNW:

                    turnOff();

                    EASTR_LED=1;
                    NORTHG_LED=1;
                    NORTHLEFTG_LED=1;
                    NORTHBUSR_LED=1;
                    WESTBUSR_LED=1;
                    SOUTHBUSR_LED=1;

                    wait(35);
                    state=WaitNW;
                    break; 

                case WaitNW:

                    turnOff();

                    EASTR_LED=1;
                    NORTHY_LED=1;
                    NORTHLEFTY_LED=1;
                    NORTHBUSR_LED=1;
                    WESTBUSR_LED=1;
                    SOUTHBUSR_LED=1;

                     wait(3); 
                     state=GoE;
                     break; 
            }
        }  
     }