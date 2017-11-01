/*
 * timer_api.c
 *
 *  Created on: Oct 15, 2017
 *      Author: arun
 */
#include "timer_api.h"


// Timer instance
static XTmrCtr TimerCounter;

static u32 time_start;
static u32 time_stop;
static u16 timer_expired_count;


int setup_timer(u16 device_id,  u8 TmrCtrNumber)
{
	int status;
	xil_printf("setting up timer module \r\n");
	// initialize the timer module.
	status = XTmrCtr_Initialize(&TimerCounter, device_id);
	if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	// clear the timer values.
	time_start = 0;
	time_stop = 0;
	timer_expired_count = 0;

	// Set the Capture register to 0
	XTmrCtr_WriteReg(TimerCounter.BaseAddress, TmrCtrNumber,
		  XTC_TLR_OFFSET, 0);
	// Reset the timer and the interrupt
	XTmrCtr_WriteReg(TimerCounter.BaseAddress, TmrCtrNumber,
		  XTC_TCSR_OFFSET, XTC_CSR_INT_OCCURED_MASK | XTC_CSR_LOAD_MASK);
	// Set the control/status register to enable timer
	XTmrCtr_WriteReg(TimerCounter.BaseAddress, TmrCtrNumber,
		  XTC_TCSR_OFFSET, XTC_CSR_ENABLE_TMR_MASK);

	return XST_SUCCESS;
}

// start the timer for the profiling.
void start_timer(u8 TmrCtrNumber)
{
	// Reset the timer and the interrupt
	XTmrCtr_WriteReg(TimerCounter.BaseAddress, TmrCtrNumber,
		XTC_TCSR_OFFSET, XTC_CSR_INT_OCCURED_MASK | XTC_CSR_LOAD_MASK);
	// Set the control/status register to enable timer
	XTmrCtr_WriteReg(TimerCounter.BaseAddress, TmrCtrNumber,
		XTC_TCSR_OFFSET, XTC_CSR_ENABLE_TMR_MASK);
	// read the timer value.
	time_start = XTmrCtr_ReadReg(TimerCounter.BaseAddress,
		TmrCtrNumber, XTC_TCR_OFFSET);
}

// stops the timer for the profiling, and returns the time ticks elapsed.
u32 stop_timer(u8 TmrCtrNumber)
{	// read the timer value.
	time_stop = XTmrCtr_ReadReg(TimerCounter.BaseAddress,
		TmrCtrNumber, XTC_TCR_OFFSET);
	// disable the timer.
	XTmrCtr_WriteReg(TimerCounter.BaseAddress, TmrCtrNumber,
		XTC_TCSR_OFFSET, 0);
	// elapsed ticks between start timer and stop timer.
	return (time_stop-time_start);
}
