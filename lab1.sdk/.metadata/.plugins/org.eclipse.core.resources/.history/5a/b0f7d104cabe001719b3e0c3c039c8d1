#include "test_run.h"

// DMA functions.
 void TxIntrHandler(void *Callback);
 void RxIntrHandler(void *Callback);
 int SetupIntrSystem(INTC * IntcInstancePtr,
	XAxiDma * AxiDmaPtr, u16 TxIntrId, u16 RxIntrId);


typedef float dt_dut;
u32 particle_cnt;
u32 size_of_frame;
u32 number_of_iter;

// for now static memory allocation.
dt_dut frame_in[256*6];	/* Buffer for Transmitting Data */
dt_dut frame_out[256*6];	/* Buffer for Receiving Data */
dt_dut frame_out_sw[256*6];	/* Buffer for Receiving Data */
dt_dut trans_mat[6*6]; // buffer to store the trans_mat

void load_trans_mat();
void load_frame(void *frame_ptr);
void clear_frame(void *frame_ptr);
void print_frame(void *frame_ptr);
void copy_to_tx_dma_addr(void *frame_i);
void sw_dut_exe(void *f_i, void *t_m, void *f_o);

int main()
{
	Xil_ICacheEnable();
	Xil_DCacheEnable();
	int status;
	u32 time_elapsed_sw = 0;
	u32 time_elapsed_hw = 0;
	xil_printf("-----Test initializing..\r\n");
	status = setup_timer(XPAR_AXI_TIMER_0_DEVICE_ID, 0x0);
	if (status!= XST_SUCCESS){
		xil_printf("Setting up timer failed\r\n");
		return XST_FAILURE;
	}
	initialize_uart(UARTLITE_DEVICE_ID);
	if (status!= XST_SUCCESS){
		xil_printf("Setting up Uartlite failed\r\n");
		return XST_FAILURE;
	}
	xil_printf("-----Test Settings Loading\r\n");
	xil_printf("paticle count set as 256 \r\n");
	particle_cnt = 256;
	size_of_frame = particle_cnt*6;
	xil_printf("setting number of iterations as 1 \r\n");
	number_of_iter = 1;
	xil_printf("loading test trans_mat \r\n");
	load_trans_mat();
	xil_printf("loading frame_i \r\n");
	load_frame(frame_in);
	clear_frame(frame_out_sw);
	xil_printf("launching SW TEST \r\n");
	start_timer(0);
	sw_dut_exe(frame_in, trans_mat, frame_out_sw);
	time_elapsed_sw = stop_timer(0);
	xil_printf("clock ticks for sw execution :%d \r\n", time_elapsed_sw);

	xil_printf("launching HW TEST \r\n");
	status = setup_dma();
	if (status!= XST_SUCCESS){
		xil_printf("Setting up DMA failed\r\n");
		return XST_FAILURE;
	}
	copy_to_tx_dma_addr(frame_in);
	xil_printf("TX copied Frame \r\n");
	//print_frame((void*)TX_BUFFER_BASE);
	//xil_printf("RX Buffer \r\n");
	//print_frame((void*)RX_BUFFER_BASE);
	clear_frame((void*)RX_BUFFER_BASE);
	xil_printf("clearing RX buffer\r\n");
	//print_frame((void*)RX_BUFFER_BASE);
	// print the results
	//xil_printf("input frame \r\n");
	//print_frame(frame_in);
	//xil_printf("Output frame \r\n");
	//print_frame(frame_out_sw);
	xil_printf("setup the hw accelerator \r\n");
	status = setup_hw_dut();
	if (status!= XST_SUCCESS){
		xil_printf("Setting up HW accelerator failed\r\n");
		return XST_FAILURE;
	}
	xil_printf("writing trans_mat to the HW \r\n");
	write_trans_mat_hw(trans_mat);
	start_timer(0);
	dma_rx_req((void*)RX_BUFFER_BASE, MAX_PKT_LEN);
	dma_tx_req((void*)TX_BUFFER_BASE, MAX_PKT_LEN);
	wait_till_tx_done();
	//xil_printf("DMA tx done\r\n");
	wait_till_rx_done();
	time_elapsed_hw = stop_timer(0);
	xil_printf("DMA rx done\r\n");
	xil_printf("Time needed for HW %d \r\n", time_elapsed_hw);
	xil_printf("Output frame from HW\r\n");
	print_frame((void*)RX_BUFFER_BASE);
	DisableIntrSystem(TX_INTR_ID, RX_INTR_ID);
	Xil_DCacheDisable();
	Xil_ICacheDisable();
    return 0;
}


void load_trans_mat()
{
	for (unsigned i = 0; i < 6 ; i ++) {
		for (unsigned j = 0; j < 6 ; j++) {
			trans_mat[6*i + j] = 1;
		//	printf(" %f ", trans_mat[6*i + j]);
		}
		//printf("\r\n");
	}
}

void load_frame(void *frame_ptr)
{
	data_type *buffer_ptr = (data_type*) frame_ptr;
	for (unsigned i = 0; i < particle_cnt; i++){
		for (unsigned j = 0; j < 6; j++){
			buffer_ptr[6*i + j] = i;
		}
	}

}

void clear_frame(void *frame_ptr)
{
	data_type *buffer_ptr = (data_type*) frame_ptr;
	for (unsigned i = 0; i < particle_cnt; i++){
		for (unsigned j = 0; j < 6; j++){
			buffer_ptr[6*i + j] = 0;
		}
	}

}

void print_frame(void *frame_ptr)
{
	data_type *buffer_ptr = (data_type*) frame_ptr;
	for (unsigned i = 0; i < 16; i++){
		for (unsigned j = 0; j < 6; j++){
			printf(" %f ",buffer_ptr[6*i + j]);
		}
		printf("\r\n");
	}

}

void copy_to_tx_dma_addr(void *frame_i)
{
	data_type *buffer = (data_type*) frame_i;
	data_type *tx_dma_buffer = (data_type*)TX_BUFFER_BASE;
	 for (unsigned i= 0; i < particle_cnt; i ++) {
		for (unsigned k = 0;k < 6; k++) {
			tx_dma_buffer[i*6 + k] = buffer[i*6 + k];
		}
	 }
}

void compare_frame(void *sw_result, void *hw_result)
{

}

void sw_dut_exe(void *f_i, void *t_m, void *f_o)
{

	data_type *f_i_b = (data_type*) f_i;
	data_type *f_o_b = (data_type*) f_o;
	data_type *t_m_b = (data_type*) t_m;

    // performing matrix multiplication on the input vector to get the output vector.
    for (unsigned i= 0; i < particle_cnt; i ++) {
        for (unsigned k = 0;k < 6; k++) {
            for (unsigned j = 0;j < 6; j++) {
                f_o_b[i*6 + j] += t_m_b[6*k + j] * f_i_b[6*i+k];
            }
        }
    }
}
