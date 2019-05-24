#include "mbed.h"
#include "rtos.h"
#include "TextLCD.h"

Serial pc(USBTX, USBRX);
DigitalIn sw1(PTD1, PullUp);
DigitalIn sw2(PTE31, PullUp);
TextLCD lcd(PTE29, PTE30, PTE20, PTE21, PTE22, PTE23);  // RS, E, D4-D7, LCDType=LCD16x2, BL=NC, E2=NC, LCDTCtrl=HD44780

//Ticker task1_timer;
float timer_value = 0.0f;
float current_temp;
float temp_inputs[32] = {13,13,45,64,23,13,24,43,13,13,45,64,23,13,24,43,13,13,45,64,23,13,24,43};
int index_max=32;
int input_index=0;
float temps[32] = {0.0f};
int array_index = 0;
//Thread task1_thread;
Thread task2_thread;
Thread task3_thread;
Thread task4_thread;
Thread task5_thread;

void task1(void const *arg);
void task2();
void task3();
void task4();
void task5();
float average_calculator();


void task1(void const *arg){
    timer_value = timer_value + 0.1f;
    int decimal = (int) timer_value;
    int first_float = (int)((float)((float)timer_value - decimal)*10);
    if(first_float == 0 && ((int) timer_value % 5 == 0)){
        task2_thread.signal_set(0x1);
    }
    if(first_float == 0){
        task4_thread.signal_set(0x3);
    }
}

void task2(){
    while(true){
        Thread::signal_wait(0x1);
        if(input_index<32){
            current_temp = temp_inputs[input_index];
            input_index++;
            }else{
                pc.printf("Overflow ERROR!\r\n");
                 //lcd.printf("Overflow ERROR!\r\n");
                }
            pc.printf("Time: %d Temperature was read: %.2f\n", (int)timer_value, current_temp);
            //lcd.printf("Time: %d Temperature was read: %.2f\n", (int)timer_value, current_temp);
            //task3_thread.start(task3);
            task3_thread.signal_set(0x2);
    }
}

void task3(){
    while(true){
        Thread::signal_wait(0x2);
        temps[array_index] = current_temp;
        array_index ++;
        array_index = array_index % 32;
    }
}

void task4(){
    while(true){
        Thread::signal_wait(0x3);
        pc.printf("Task4 Time:%d \n", (int)timer_value);
        //lcd.printf("Task4 Time:%d \n", (int)timer_value);
        if(sw1 == 0){
            pc.printf("Task4 Current Temperature: %.2f \n", current_temp);
            //lcd.printf("Task4 Current Temperature: %.2f ", current_temp);
        }else if(sw2 == 0){
            pc.printf("Task4 Average Temperature: %.2f \n", average_calculator());
            //lcd.printf("Task4 Average Temperature: %.2f \n", average_calculator());
        }
    }
}

void task5(){
    while(1){}
}

float average_calculator(){
    float sum = 0;
    for(int i=0; i<32 ; i++){
        sum += (float)temps[i];
    }
    
    return ((float)sum)/32;
}

int main(){
    //Set timer of tasks
    RtosTimer task1_timer(task1, osTimerPeriodic, (void *) 1);
    //task1_timer.attach(&task1_starter, 0.1);
    //task1_thread.set_priority(osPriorityAboveNormal);
    task2_thread.set_priority(osPriorityNormal);
    task3_thread.set_priority(osPriorityBelowNormal);
    task4_thread.set_priority(osPriorityLow);
    task5_thread.set_priority(osPriorityIdle);
    task1_timer.start(100);
    task2_thread.start(task2);
    task3_thread.start(task3);
    task4_thread.start(task4);
    task5_thread.start(task5);
    while(1){}
}