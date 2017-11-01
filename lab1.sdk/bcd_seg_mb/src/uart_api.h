/*
 * uart_api.h
 *
 *  Created on: Oct 15, 2017
 *      Author: arun
 */

#ifndef SRC_UART_API_H_
#define SRC_UART_API_H_

#include "system_config.h"

int initialize_uart(u16 device_id);
u32 reveive_ascii_to_number();
u32 receive_binary_file(void* data_buffer, u32 size);


#endif /* SRC_UART_API_H_ */
