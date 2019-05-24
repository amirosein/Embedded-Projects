#include "mbed.h" 
#include <iostream>      
#include <string>  
#include <stdio.h>
#include <stdlib.h>  
using namespace std;

BusOut display(PTA1,PTA2,PTD4,PTA12,PTA4,PTA5,PTC8,PTC9);
DigitalOut redled(PTE4);
DigitalOut greenled(PTE5);

int TASK=1;
int taskarr[6]={0,4,4,3,2,1};
int ready2runArr[6]={0,1,1,0,0,0};

InterruptIn switch1(PTD2);
InterruptIn switch2(PTD1);
InterruptIn switch3(PTA13);


void scheduler(){
    for(int i=0;i<6;i++){
        if(taskarr[TASK]>taskarr[i]){
            if(ready2runArr[i]>=1){
                TASK=i;
                }
            }
        }
    }
void task1() {
        redled = 1;
        wait(0.04);
        redled = 0;
        wait(0.04);
        scheduler();   
}
void task2() {
        greenled = 1;
        wait(0.04);
        greenled = 0;
        wait(0.04);
        scheduler();
}
void task3() {
        redled = 1;
        greenled = 0;
        wait(0.04);
        redled=0;
        greenled=1;
        wait(0.04);
        ready2runArr[3]--;
        scheduler();
}
void task4() {
        redled = 1;
        greenled = 1;
        wait(0.04);
        redled=0;
        greenled=0;
        wait(0.04);
        ready2runArr[4]--;
        scheduler();
}
void task5() {
    unsigned char i;
//    unsigned char arr[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
    unsigned char arr[10]={0x40,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
    for (i=0; i<10; i++){
         display=arr[i];
         wait(1);
       }
       ready2runArr[5]--;
       scheduler();
}
void intrupt1(){
    ready2runArr[3]++;
    }
void intrupt2(){
    ready2runArr[4]++;
    }
void intrupt3(){
    ready2runArr[5]++;
    }
int main() {
    switch1.rise(&intrupt1);
    switch2.rise(&intrupt2);
    switch3.rise(&intrupt3);
    while(1) {
        if(TASK==1){
           task1();
           }
        else if(TASK==2){
//           task2();
           }
        else if(TASK==3){
           task3();
           }
        else if(TASK==4){
           task4();
           }
        else if(TASK==5){
           task5();
           }      
    }
}