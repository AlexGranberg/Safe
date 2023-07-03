#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdbool.h>
#include "uart.h"
#include "millis.h"
#include "servo.h"

#define BUTTON_PIN 0

#define BIT_SET(a, b) ((a) |= (1ULL << (b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1ULL<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1ULL<<(b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b)))) 

#define BUTTON_IS_CLICKED(PINB,BUTTON_PIN) !BIT_CHECK(PINB,BUTTON_PIN)


void openSafe(){
    servo1_set_percentage(100);
    _delay_ms(1000);
}

void closeSafe(){
    servo1_set_percentage(-100);
    _delay_ms(1000);
}

int main(void){
    init_servo();
    servo1_set_percentage(-100);
    sei();

    //Sätt till INPUT_PULLUP
    BIT_CLEAR(DDRB,BUTTON_PIN); // INPUT MODE
    BIT_SET(PORTB,BUTTON_PIN); 

    bool buttonIsPressed = false;
    while(1){
      
        if(!BIT_CHECK(PINB, BUTTON_PIN)){ //nedtryckt
            _delay_ms(100);
            buttonIsPressed = !buttonIsPressed;

            // printf("BUTTON PRESSED    ");
        }
        if(buttonIsPressed){
            openSafe();
            _delay_ms(2000);
            closeSafe();
            buttonIsPressed = false;
        }

    }
    return 0;
}