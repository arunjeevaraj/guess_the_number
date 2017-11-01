/*
 * timer_api.h
 *
 *  Created on: Oct 15, 2017
 *      Author: arun
 */

#ifndef SRC_TIMER_API_H_
#define SRC_TIMER_API_H_

#include "system_config.h"


int setup_timer(u16 device_id,  u8 TmrCtrNumber);
void start_timer(u8 TmrCtrNumber);
u32 stop_timer(u8 TmrCtrNumber);

#endif /* SRC_TIMER_API_H_ */
