#include "test_run.h"
#include <stdlib.h>


void print_on_7seg(u8 data)
{
	u32 *data_ptr = (u32*) BCD_BASE_ADDR;
	*(data_ptr + 0) = data;
}

void test_hw()
{
	u32 *data_ptr = (u32*) BCD_BASE_ADDR;
	u32 data_read = 0;
	*(data_ptr + 0) = 3;
	data_read = *(data_ptr + 0);
	xil_printf("result from reg0: %d \r\n", data_read);
	xil_printf("result from LSB reg0: %d \r\n", (data_read & 0xf));
	*(data_ptr + 1) = 100;
	data_read = *(data_ptr + 1);
	xil_printf("result from reg 1: %d \r\n", data_read);
	*(data_ptr + 2) = 2;
	data_read = *(data_ptr + 2);
	xil_printf("result from reg 2: %d \r\n", data_read);
	data_read = *(data_ptr + 3);
	xil_printf("result from reg 3: %d \r\n", data_read);
}

int main()
{
	u32 *data_ptr = (u32*) BCD_BASE_ADDR;
	u32 data_read = 0;
	xil_printf("System Initialized \r\n");
	u8 tries = 9;
	u8 number, number_guess;
	xil_printf("Welcome to the Guess the Number game \r\n");
	initialize_uart(UARTLITE_DEVICE_ID);
	setup_timer(TIMER_DEVICE_ID,  0x0);
	u32 time_elapsed = 0;
	while (1) {
		start_timer(0x0);
		xil_printf("Tell me a number, this is a free trial \r\n");
		number_guess = reveive_ascii_to_number();
		time_elapsed = stop_timer(0x0);
		xil_printf("time elapsed %d \r\n", (time_elapsed & 0xff));
		// enter the seed for random function.
		srand((unsigned)(time_elapsed & 0xff));
		number = rand() % 100; // a number between 0 and 100
		xil_printf("number to guess :%d \r\n", number);

		xil_printf("You entered %d \r\n", number_guess);
		xil_printf("Good, Good -_- you have a way with number\r\n");

		xil_printf("lets the game start then \r\n");
		xil_printf("You have nine tries and guess the number between 0 and 99 \r\n");
		print_on_7seg(tries);
		xil_printf("Try out your luck today, this is real now *_* \r\n");
		while (tries) {
			number_guess = reveive_ascii_to_number();
			if (number_guess == number) {
				xil_printf(" This is a lucky day. Be aware !! \r\n");
				break;
			} else {
				 u8 diff = number_guess - number;
				 if (diff > 60) {
					 xil_printf(" You are far away \r\n");
				 } else if (diff > 40) {
					 xil_printf(" you are getting closer \r\n");
				 } else {
					 xil_printf(" you can almost smell it, can't you \r\n");
				 }
				tries--;
				print_on_7seg(tries);
			}

		}
		if (tries == 0) {
			xil_printf(" you lost, you can win, Try again \r\n");
		} else {
			xil_printf(" You won, won't you try gain.\r\n");
		}
	}
    return 0;
}


