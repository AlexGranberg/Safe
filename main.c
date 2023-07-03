#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdbool.h>
#include "uart.h"
#include "millis.h"
#include "servo.h"

#define BUTTON_PIN 0
#define LED_GREEN 1
#define LED_RED 2

#define BIT_SET(a, b) ((a) |= (1ULL << (b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1ULL<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1ULL<<(b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b)))) 

#define BUTTON_IS_CLICKED(PINB,BUTTON_PIN) !BIT_CHECK(PINB,BUTTON_PIN)


void openSafe(){
    servo1_set_percentage(100);
}

void closeSafe(){
    servo1_set_percentage(-100);
}

int main(void){
    init_servo();
    servo1_set_percentage(-100);
    sei();

    //Sätt till INPUT_PULLUP
    BIT_CLEAR(DDRB,BUTTON_PIN); // INPUT MODE
    BIT_SET(PORTB,BUTTON_PIN); 

    BIT_CLEAR(DDRB, LED_GREEN);
    BIT_SET(DDRB, LED_RED);

    bool buttonIsPressed = false;
    while(1){
        if(!BIT_CHECK(PINB, BUTTON_PIN)){ //nedtryckt
            _delay_ms(100);
            buttonIsPressed = !buttonIsPressed;

            // printf("BUTTON PRESSED    ");
        }
        if(buttonIsPressed){
            BIT_SET(PORTB,LED_GREEN);
            BIT_CLEAR(PORTB,LED_RED);
            openSafe();
            _delay_ms(3000);
            BIT_CLEAR(PORTB,LED_GREEN);
            BIT_SET(PORTB,LED_RED);
            closeSafe();
            buttonIsPressed = false;
        }

    }
    return 0;
}