#include <atmel_start.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

#include "i2c_lcd.h"

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	uint8_t bits[5];
	uint8_t i,j = 0;
	uint8_t result;
	int8_t temperature = 0;
	int8_t humidity = 0;
	char buffer[20];
	//Enables interrupts and initialize I2C interface
	sei();
	I2C_0_init();
	//Initialize LCD
	i2c_lcd_init();
	i2c_lcd_led_on();
	i2c_lcd_set_cursor(0,0);
	
	while (1){//Main loop
		if(dht11_getdata(&temperature, &humidity) != -1) {
			itoa(temperature, buffer, 10);
			//Write temperature
			i2c_lcd_write_text("Temperature;  ");
			//utoa(temperature, buffer, 10);
			i2c_lcd_write_text(buffer);
			itoa(humidity, buffer, 10);
			
			//Write humidity
			i2c_lcd_set_cursor(0,1);
			i2c_lcd_write_text("Humidity;  ");
			//utoa(humidity, buffer, 10);
			i2c_lcd_write_text(buffer);
		}
		else {
			i2c_lcd_clear();
			i2c_lcd_write_text("Error!  ");
		}
		_delay_ms(1500);
		i2c_lcd_clear();
		_delay_ms(15);	
	}
}