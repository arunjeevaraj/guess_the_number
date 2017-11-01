/*
 * uart_api.c
 *
 *  Created on: Oct 15, 2017
 *      Author: arun
 */
#include "uart_api.h"


// Uart instance.
static XUartLite UartLite;


int initialize_uart(u16 device_id)
{
	xil_printf("Setting up UART.\n\r");
	int status;
	status = XUartLite_Initialize(&UartLite, device_id);
	if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	return XST_SUCCESS;
}

u32 receive_binary_file(void* data_buffer, u32 size)
{
	xil_printf("Waiting for file read.\n\r");
	u8* data_buffer_p = (u8*)data_buffer;
	while (size) {
		if ( XUartLite_Recv(&UartLite, data_buffer_p, 1)) {
			data_buffer_p++;
			size--;
		}
	}
	xil_printf("File read done.\n\r");
	return 0;
}


/*   function    : receives ascii to number through UART.
 * 				   through polling method. Any non-numerical
 * 				   ASCII exits the function.
*   returns      : the number after processing
*   parameters   : none
*   requirements : intialize_uart()
*/
u32 reveive_ascii_to_number()
{
	u32 data = 0;
	u8 buffer;
	while (1) {
		if ( XUartLite_Recv(&UartLite, &buffer, 1)) {
			if (buffer > 47 && buffer <= 57) {
				data = data*10 + (buffer - 48);
			} else {
				break;
			}
		}
	}
	return data;
}
