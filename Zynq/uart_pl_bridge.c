// UART-PL Bridge for Zynq SoCs
// Created: 2024-08-25
// Modified: 2024-08-27 (status: tested on Vitis, works fine)

// Copyright (c) 2024 Kagan Dikmen
// See LICENSE for details

// Explanation:
// This is the Vitis code I have used to test a RISC-V core (clairvoyant) I had on the PL side
// of a Zynq series SoC. The core was ought to receive/transmit data through UART but the Zynq series 
// SoCs do not have any UART ports connecting directly to the PL side, but two pairs connecting to the 
// PS side. And what this program does is to program the PS side to be a bridge between the UART interface 
// of the SoC and the PL side through two AXI GPIO interfaces (gpio0 & gpio1).

#include <stdio.h>
#include <xstatus.h>
#include "platform.h"
#include "xil_printf.h"
#include "xuartps.h"
#include "xgpio.h"
#include "xparameters.h"
#include "xparameters_ps.h"

#define NUMBYTE 1

XUartPs_Config *uartConfig;
XUartPs uart0;

XGpio gpio0, gpio1;

int main()
{
    init_platform();
    printf("Setting up...");

    u32 buffer[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int status = 0;

    ////////////////////////////////////////////////////////////////
    // UART Initialization
    ////////////////////////////////////////////////////////////////

    uartConfig = XUartPs_LookupConfig(XPAR_XUARTPS_0_BASEADDR);
    if (NULL == uartConfig) {
        xil_printf("uartConfig Initialization Failed\r\n");
        return XST_FAILURE;
    }

    status = XUartPs_CfgInitialize(&uart0, uartConfig, uartConfig->BaseAddress);
    if (status != XST_SUCCESS) {
        xil_printf("uart0 Initialization Failed\r\n");
        return XST_FAILURE;
    }

    XUartPs_SetBaudRate(&uart0, 115200);

    ////////////////////////////////////////////////////////////////
    // GPIO Initialization
    ////////////////////////////////////////////////////////////////
    
    status = XGpio_Initialize(&gpio0, XPAR_XGPIO_0_BASEADDR);
	if (status != XST_SUCCESS) {
		xil_printf("gpio0 Initialization Failed\r\n");
		return XST_FAILURE;
	}

    status = XGpio_Initialize(&gpio1, XPAR_XGPIO_1_BASEADDR);
	if (status != XST_SUCCESS) {
		xil_printf("gpio1 Initialization Failed\r\n");
		return XST_FAILURE;
	}

    XGpio_SetDataDirection(&gpio0, 1, 1);     // input
    XGpio_SetDataDirection(&gpio1, 1, 0);     // output

    ////////////////////////////////////////////////////////////////
    // Transmission Logic
    ////////////////////////////////////////////////////////////////

    while(1) {
        status = 0;
        while(status < NUMBYTE) {
            status += XUartPs_Recv(&uart0, buffer, (NUMBYTE - status)); 
        };

        // For debugging purposes:
        // for(int i=0; i<10000; i++);
        // XUartPs_Send(&uart0, buffer, NUMBYTE + 2);
        // print("\r");

        XGpio_DiscreteWrite(&gpio1, 1, buffer[0]);

        // For some delay between transmission to the PL side and receiving data back from it:
        // for(int i=0; i < 10000; i++);

        u8 result = XGpio_DiscreteRead(&gpio0, 1);
        XUartPs_Send(&uart0, &result, 1);
    }

    printf("Terminating...");
    cleanup_platform();
    return 0;
}

