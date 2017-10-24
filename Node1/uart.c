#define F_CPU 4915200

#include <avr/io.h>
#include <stdio.h>

#include "uart.h"

void uart_init(int baudRate, int node){
	//Asynchronous - No parity - 2 stop bits - 8 bit char size
	
	int UBRR = ((long)F_CPU/((long)16*baudRate) - 1);
	UBRR0L = UBRR; //Setting baud rate low byte
    UBRR0H = (UBRR>>8); //Setting baud rate high byte
	UCSR0B = (1<<RXEN0)|(1<<TXEN0); //Enable receiver and transmitter 
    UCSR0C = ((1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00)); //Set frame format: 2 stop bit, 8data.
    
	//Why doesn't the stuff below work? prints [00]
	
    //if (node == 1){ //URSEL should not be set in node 2
	//    UCSR0C = ((1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00)); //URSEL makes sure we won't access UBRRH during operation, but UCSRC.
	//}
	
		
	fdevopen(uart_putchar, uart_getchar); //Enable printf use
	return;
}

void uart_putchar(char c){
	while (!( UCSR0A & (1<<UDRE0))); //Wait for empty transmit buffer
	UDR0 = c; //Put data into buffer, sends the data
	return;
}

unsigned char uart_getchar(){
	while (!( UCSR0A & (1<<RXC0)));
	return UDR0;
}