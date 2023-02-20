#include "iodefine.h"
#include "usb_define.h"
#include "usb_int.h"
#include "sci.h"



/******************************************************************************
Function Name   : usb_cpu_usb_int_hand_r
Description     : 
Arguments       : none
Return value    : none
******************************************************************************/
void usb_cpu_usb_int_hand_r( void )
{
	USB_UTR_t       *ptr;
	/* Initial pointer */
    ptr = &usb_gcstd_IntMsg[0][usb_gcstd_IntMsgCnt[0]];
    ptr->ip  = USB_USBIP_0;
    ptr->ipp = usb_cstd_GetUsbIpAdr( ptr->ip );

    usb_cstd_InterruptClock( ptr );

    /* Check Host or Peripheral */
    if( usb_cstd_is_host_mode(ptr) == USB_NO )
    {
        USB_ER_t        err;

        /* Peripheral Function */
        /* Peripheral Interrupt handler */
        usb_pstd_InterruptHandler(ptr);
        ptr->msghead = (USB_MH_t)USB_NULL;
        /* Send message */
        err = USB_ISND_MSG(USB_PCD_MBX, (USB_MSG_t*)ptr);
        if( err != USB_E_OK )
        {
            //SCI_printf("### lib_UsbHandler DEF1 isnd_msg error (%ld)\n", err);
        }
    }
    else
    {
    }

    /* Renewal Message count  */
    usb_gcstd_IntMsgCnt[0]++;
    if( usb_gcstd_IntMsgCnt[0] == USB_INTMSGMAX )
    {
        usb_gcstd_IntMsgCnt[0] = 0;
    }

}   /* eof usb_cpu_usb_int_hand_r() */



/******************************************************************************
Function Name   : usb_cpu_d0fifo_int_hand
Description     : D0FIFO interrupt Handler
Arguments       : none
Return value    : none
******************************************************************************/
void usb_cpu_d0fifo_int_hand(void)
{
//usb_cstd_DmaHandler();      /* Call interrupt routine */

	USB_UTR_t       *ptr;

    ptr = &usb_gcstd_IntMsgD0fifo;
    ptr->msghead = (USB_MH_t)USB_NULL;
    ptr->keyword = 0;
    ptr->status  = 0;
    ptr->ip  = USB_USBIP_0;
    ptr->ipp = usb_cstd_GetUsbIpAdr( ptr->ip );

    usb_creg_clr_dreqe( ptr, USB_D0DMA );       /* DMA Transfer request disable */
    usb_cpu_d0fifo_stop_dma(ptr);               /* Stop DMA,FIFO access */

    if( usb_cstd_is_host_mode(ptr) == USB_NO )
    {
        USB_ER_t        err;

        /* Peripheral Function */
        ptr->msginfo = USB_MSG_PCD_D0FIFO_INT;
        /* Send message */
        err = USB_ISND_MSG(USB_PCD_MBX, (USB_MSG_t*)ptr);
        if( err != USB_E_OK )
        {
            //SCI_printf("### DmaHandler DEF1 isnd_msg error (%ld)\n", err);
        }
    }
    else
    {
    }
}