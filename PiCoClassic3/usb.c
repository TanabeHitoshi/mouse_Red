#include "iodefine.h"
#include "usb_define.h"
#include "usb.h"
#include "machine.h"
//#include "sci.h"
#include "string.h"

extern void wait_ms(int wtime);

uint8_t cdc_init_msg[] = "RT CORPORATION";

uint8_t cdc_string_descriptor0[ STRING_DESCRIPTOR0_LEN + ( STRING_DESCRIPTOR0_LEN % 2 ) ] =
{   /* UNICODE 0x0409 English (United States) */
    STRING_DESCRIPTOR0_LEN,               /*  0:bLength */
    USB_DT_STRING,                      /*  1:bDescriptorType */
    0x09, 0x04                          /*  2:wLANGID[0] */
};

uint8_t cdc_string_descriptor1[ STRING_DESCRIPTOR1_LEN + ( STRING_DESCRIPTOR1_LEN % 2 ) ] =
{   /* iManufacturer */
    STRING_DESCRIPTOR1_LEN,               /*  0:bLength */
    USB_DT_STRING,                      /*  1:bDescriptorType */
    'R', 0x00,                          /*  2:wLANGID[0] */
    'T', 0x00,
    'C', 0x00,
    'O', 0x00,
    'R', 0x00,
    'P', 0x00,
    'O', 0x00,
    'R', 0x00,
    'A', 0x00,
    'T', 0x00,
    'I', 0x00,
    'O', 0x00,
    'N', 0x00
};

uint8_t cdc_string_descriptor2[ STRING_DESCRIPTOR2_LEN + ( STRING_DESCRIPTOR2_LEN % 2 ) ] =
{   /* iProduct */
    STRING_DESCRIPTOR2_LEN,               /*  0:bLength */
    USB_DT_STRING,                      /*  1:bDescriptorType */
    'C', 0x00,
    'D', 0x00,
    'C', 0x00,
    ' ', 0x00,
    'U', 0x00,
    'S', 0x00,
    'B', 0x00,
    ' ', 0x00,
    'D', 0x00,
    'e', 0x00,
    'm', 0x00,
    'o', 0x00,
    'n', 0x00,
    's', 0x00,
    't', 0x00,
    'r', 0x00,
    'a', 0x00,
    't', 0x00,
    'i', 0x00,
    'o', 0x00,
    'n', 0x00
};

uint8_t cdc_string_descriptor3[ STRING_DESCRIPTOR3_LEN + ( STRING_DESCRIPTOR3_LEN % 2 ) ] =
{   /* iInterface */
    STRING_DESCRIPTOR3_LEN,               /*  0:bLength */
    USB_DT_STRING,                      /*  1:bDescriptorType */
    'C', 0x00,
    'o', 0x00,
    'm', 0x00,
    'm', 0x00,
    'u', 0x00,
    'n', 0x00,
    'i', 0x00,
    'c', 0x00,
    'a', 0x00,
    't', 0x00,
    'i', 0x00,
    'o', 0x00,
    'n', 0x00,
    's', 0x00,
    ' ', 0x00,
    'D', 0x00,
    'e', 0x00,
    'v', 0x00,
    'i', 0x00,
    'c', 0x00,
    'e', 0x00,
    's', 0x00
};

uint8_t cdc_string_descriptor4[ STRING_DESCRIPTOR4_LEN + ( STRING_DESCRIPTOR4_LEN % 2 ) ] =
{   /* iConfiguration */
    STRING_DESCRIPTOR4_LEN,               /*  0:bLength */
    USB_DT_STRING,                      /*  1:bDescriptorType */
    'F', 0x00,                          /*  2:wLANGID[0] */
    'u', 0x00,
    'l', 0x00,
    'l', 0x00,
    '-', 0x00,
    'S', 0x00,
    'p', 0x00,
    'e', 0x00,
    'e', 0x00,
    'd', 0x00
};


uint8_t cdc_string_descriptor5
    [ STRING_DESCRIPTOR5_LEN + ( STRING_DESCRIPTOR5_LEN % 2 ) ] =
{   /* iSerialNumber */
    STRING_DESCRIPTOR5_LEN,               /*  0:bLength */
    USB_DT_STRING,                      /*  1:bDescriptorType */
    '0', 0x00,                          /*  2:wLANGID[0] */
    '0', 0x00,
    '0', 0x00,
    '0', 0x00,
    '0', 0x00,
    '0', 0x00,
    '0', 0x00,
    '0', 0x00,
    '0', 0x00,
    '0', 0x00,
    '0', 0x00,
    '0', 0x00,
    '1', 0x00,
};

uint8_t *cdc_string_descriptor_ptr[USB_STRINGNUM] =
{
    cdc_string_descriptor0,
    cdc_string_descriptor1,
    cdc_string_descriptor2,
    cdc_string_descriptor3,
    cdc_string_descriptor4,
    cdc_string_descriptor5,
};

/* For Full-Speed */
uint8_t usb_gpcdc_FsConfigration[ USB_PCDC_CD1_LEN + ( USB_PCDC_CD1_LEN % 2 ) ] =
{
    9,                                  /*  0:bLength */
    USB_DT_CONFIGURATION,               /*  1:bDescriptorType */
    USB_PCDC_CD1_LEN % 256,             /*  2:wTotalLength(L) */
    USB_PCDC_CD1_LEN / 256,             /*  3:wTotalLength(H) */
    2,                                  /*  4:bNumInterfaces */
    1,                                  /*  5:bConfigurationValue */
    0,                                  /*  6:iConfiguration */
    USB_CF_RESERVED | USB_CF_SELFP,     /*  7:bmAttributes */
    (10 / 2),                           /*  8:MAXPower (2mA unit) */

    /* Interface Descriptor */
        9,                              /*  0:bLength */
        USB_DT_INTERFACE,               /*  1:bDescriptor */
        0,                              /*  2:bInterfaceNumber */
        0,                              /*  3:bAlternateSetting */
        1,                              /*  4:bNumEndpoints */
        USB_IFCLS_CDCC,                 /*  5:bInterfaceClass */
                                        /*  6:bInterfaceSubClass */
        USB_PCDC_CLASS_SUBCLASS_CODE_ABS_CTR_MDL,
        1,                              /*  7:bInterfaceProtocol */
        0,                              /*  8:iInterface */

        /* Communications Class Functional Descriptorss */
            5,                          /*  0:bLength */
            USB_PCDC_CS_INTERFACE,      /*  1:bDescriptorType */
                                        /*  2:bDescriptorSubtype */
            USB_PCDC_DT_SUBTYPE_HEADER_FUNC,
            USB_PCDC_BCD_CDC % 256, /*  3:bcdCDC_lo */
            USB_PCDC_BCD_CDC / 256, /*  4:bcdCDC_hi */
        /* Communications Class Functional Descriptorss */
            4,                          /*  0:bLength */
            USB_PCDC_CS_INTERFACE,          /*  1:bDescriptorType */
                                        /*  2:bDescriptorSubtype */
            USB_PCDC_DT_SUBTYPE_ABSTRACT_CTR_MANAGE_FUNC,
            2,                          /*  3:bmCapabilities */
        /* Communications Class Functional Descriptorss */
            5,                          /*  0:bLength */
            USB_PCDC_CS_INTERFACE,          /*  1:bDescriptorType */
                                        /*  2:bDescriptorSubtype */
            USB_PCDC_DT_SUBTYPE_UNION_FUNC,
            0,                          /*  3:bMasterInterface */
            1,                          /*  4:bSlaveInterface0 */

        /* Communications Class Functional Descriptorss */
            5,                          /*  0:bLength */
            USB_PCDC_CS_INTERFACE,      /*  1:bDescriptorType */
                                        /*  2:bDescriptorSubtype */
            USB_PCDC_DT_SUBTYPE_CALL_MANAGE_FUNC,
            /* D1:1-Device can send/receive call management
                    information over a Data Class interface. */
            /* D0:1-Device handles call management itself. */
            3,                          /*  3:bmCapabilities */
            1,                          /*  4:bDataInterface */

        /* Endpoint Descriptor 0 */
            7,                          /*  0:bLength */
            USB_DT_ENDPOINT,            /*  1:bDescriptorType */
            USB_EP_IN  | USB_EP3,       /*  2:bEndpointAddress */
            USB_EP_INT,                 /*  3:bmAttribute */
            16,                         /*  4:wMAXPacketSize_lo */
            0,                          /*  5:wMAXPacketSize_hi */
            0x10,                       /*  6:bInterval */

    /* Interface Descriptor */
        9,                              /*  0:bLength */
        USB_DT_INTERFACE,               /*  1:bDescriptor */
        1,                              /*  2:bInterfaceNumber */
        0,                              /*  3:bAlternateSetting */
        2,                              /*  4:bNumEndpoints */
        USB_IFCLS_CDCD,                 /*  5:bInterfaceClass */
        0,                              /*  6:bInterfaceSubClass */
        0,                              /*  7:bInterfaceProtocol */
        0,                              /*  8:iInterface */

        /* Endpoint Descriptor 0 */
            7,                          /*  0:bLength */
            USB_DT_ENDPOINT,            /*  1:bDescriptorType */
            USB_EP_IN | USB_EP1,        /*  2:bEndpointAddress */
            USB_EP_BULK,                /*  3:bmAttribute */
            64,                         /*  4:wMAXPacketSize_lo */
            0,                          /*  5:wMAXPacketSize_hi */
            0,                          /*  6:bInterval */

        /* Endpoint Descriptor 1 */
            7,                          /*  0:bLength */
            USB_DT_ENDPOINT,            /*  1:bDescriptorType */
            USB_EP_OUT | USB_EP2,       /*  2:bEndpointAddress */
            USB_EP_BULK,                /*  3:bmAttribute */
            64,                         /*  4:wMAXPacketSize_lo */
            0,                          /*  5:wMAXPacketSize_hi */
            0,                          /*  6:bInterval */
};


uint8_t *cdc_config_descriptor_ptr[] =
{
    (uint8_t*)usb_gpcdc_FsConfigration
};

/* Configuration 1 */
uint16_t cdc_eptbl1[] =
{

    USB_PCDC_USE_PIPE_IN,                               /* Pipe No. */
    /* TYPE    / BFRE        / DBLB       / CNTMD        / SHTNAK       / DIR          / EPNUM */
    USB_BULK | USB_BFREOFF | USB_DBLBOFF | USB_CNTMDOFF | USB_SHTNAKON | USB_DIR_P_IN | USB_EP1,     /* PIPECFG */
    USB_NONE,
    64,                                                 /* PIPEMAXP */
    USB_IFISOFF | USB_IITV_TIME(0u),                    /* PIPEPERI */
    USB_CUSE,                                           /* FIFO Access mode */
    //USB_D0DMA,
    USB_PCDC_USE_PIPE_OUT,                              /* Pipe No. */
    /* TYPE    / BFRE        / DBLB       / CNTMD        / SHTNAK       / DIR          / EPNUM */
    USB_BULK | USB_BFREOFF | USB_DBLBOFF | USB_CNTMDOFF | USB_SHTNAKON | USB_DIR_P_OUT | USB_EP2,    /* PIPECFG */
    USB_NONE,
    64,                                                 /* PIPEMAXP */
    USB_IFISOFF | USB_IITV_TIME(0u),                    /* PIPEPERI */
    USB_CUSE,                                           /* FIFO Access mode */
    //USB_D0DMA,
    USB_PCDC_USE_PIPE_STATUS,                           /* Pipe No. */
    /* TYPE    / DIR          / EPNUM */
    USB_INT  | USB_DIR_P_IN | USB_EP3,                  /* PIPECFG */
    USB_NONE,
    16u,                                                /* PIPEMAXP */
    USB_IITV_TIME(0u),                                  /* PIPEPERI */
    USB_CUSE,                                           /* FIFO Access mode */

/* Pipe end */
    USB_PDTBLEND,
};

/* Configuration 2 */
uint16_t cdc_eptbl2[] =
{
    0
};
/* Configuration 3 */
uint16_t cdc_eptbl3[] =
{
    0
};
/* Configuration 4 */
uint16_t cdc_eptbl4[] =
{
    0
};
/* Configuration 5 */
uint16_t cdc_eptbl5[] =
{
    0
};
uint16_t *cdc_eptbl_ptr[] =
{
    cdc_eptbl1,
    cdc_eptbl2,
    cdc_eptbl3,
    cdc_eptbl4,
    cdc_eptbl5
};
uint8_t cdc_device_descriptor[ USB_PCDC_DD_LEN + ( USB_PCDC_DD_LEN % 2 ) ] =
{
    /*  0:bLength */
    USB_PCDC_DD_LEN,
    /*  1:bDescriptorType */
    USB_DT_DEVICE,
    /*  2:bcdUSB_lo */
    (USB_BCDNUM                     & (uint8_t)0xffu),
    /*  3:bcdUSB_hi */
    ((uint8_t)(USB_BCDNUM >> 8)     & (uint8_t)0xffu),
    /*  4:bDeviceClass */
    USB_IFCLS_CDCC,
    /*  5:bDeviceSubClass */
    0,
    /*  6:bDeviceProtocol */
    0,
    /*  7:bMAXPacketSize(for DCP) */
    (uint8_t)USB_DCPMAXP,
    /*  8:idVendor_lo */
    (USB_VENDORID                   & (uint8_t)0xffu),
    /*  9:idVendor_hi */
    ((uint8_t)(USB_VENDORID >> 8)   & (uint8_t)0xffu),
    /* 10:idProduct_lo */
    ((uint16_t)USB_PRODUCTID        & (uint8_t)0xffu),
    /* 11:idProduct_hi */
    ((uint8_t)(USB_PRODUCTID >> 8)  & (uint8_t)0xffu),
    /* 12:bcdDevice_lo */
    (USB_RELEASE                    & (uint8_t)0xffu),
    /* 13:bcdDevice_hi */
    ((uint8_t)(USB_RELEASE >> 8)    & (uint8_t)0xffu),
    /* 14:iManufacturer */
    1,
    /* 15:iProduct */
    2,
    /* 16:iSerialNumber */
    5,
    /* 17:bNumConfigurations */
    USB_CONFIGNUM
};

/******************************************************************************
Private global variables and functions
******************************************************************************/
uint32_t    * g_dtc_table_work[2];
static bool usb_gstd_is_opened[2] = { false, false };

USB_UTR_t       usb_gcstd_IntMsg[USB_NUM_USBIP][USB_INTMSGMAX]; /* Interrupt message */
uint16_t        usb_gcstd_IntMsgCnt[USB_NUM_USBIP];             /* Interrupt message count */
USB_UTR_t       usb_gcstd_IntMsgD0fifo;
uint16_t        usb_gcstd_HsEnable[USB_NUM_USBIP];

uint16_t    com_port_receive_size;
uint8_t     com_port_receive_data[CDC_DATA_LEN + 4];

uint16_t    usb_tx_wait_f;          /* Send Complete wait flag  */
uint16_t    usb_rx_wait_f;
uint16_t    usb_status_wait_f;
sci_hdl_t   sci_console;
USB_SCI_SerialState_t  cdc_serial_state;

uint8_t usb_gpcdc_SerialState_Table[USB_CDC_SETUP_TBL_BSIZE]
    = { 0xA1,           /* bmRequestType */
        0x20,           /* bNotification:SERIAL_STATE */
        0x00,0x00,      /* wValue:Zero */
        0x00,0x00,      /* wIndex:Interface */
        0x02,0x00,      /* wLength:2 */
        0x00,0x00 };    /* Data:UART State bitmap */
USB_PCDC_ControlLineState_t usb_gcdc_ControlLineState;
uint16_t usb_gcdc_SendBreakDuration;

uint16_t usb_gcstd_D0fifo[2u] = {0,0};      /* D0fifo0 Interrupt Request enable */
uint16_t usb_gcstd_D1fifo[2u] = {0,0};      /* D1fifo0 Interrupt Request enable */
uint16_t        usb_gpstd_ConfigNum = 0;                    /* Current configuration number */
uint16_t        usb_gpstd_RemoteWakeup = USB_NO;            /* Remote wakeup enable flag */
uint16_t        usb_gpstd_intsts0;                          /* INTSTS0 */

USB_PCDREG_t    usb_gpstd_Driver = 
{
    (uint16_t**)&usb_cstd_DummyFunction,    /* Pipe define table address */
    (uint8_t*)  &usb_cstd_DummyFunction,    /* Device descriptor table address */
    (uint8_t*)  &usb_cstd_DummyFunction,    /* Qualifier descriptor table address */
    (uint8_t**) &usb_cstd_DummyFunction,    /* Configuration descriptor table address */
    (uint8_t**) &usb_cstd_DummyFunction,    /* Other configuration descriptor table address */
    (uint8_t**) &usb_cstd_DummyFunction,    /* String descriptor table address */
    &usb_cstd_DummyFunction,                /* Driver init */
    &usb_cstd_DummyFunction,                /* Device default */
    &usb_cstd_DummyFunction,                /* Device configured */
    &usb_cstd_DummyFunction,                /* Device detach */
    &usb_cstd_DummyFunction,                /* Device suspend */
    &usb_cstd_DummyFunction,                /* Device resume */
    &usb_cstd_DummyFunction,                /* Interfaced change */
    &usb_cstd_DummyTrn,                     /* Control transfer */
};

uint16_t        usb_gpstd_EpTblIndex[2][USB_MAX_EP_NO + 1u];   /* Index of endpoint information table */
uint16_t        usb_gpstd_ReqType;                          /* Request type */
uint16_t        usb_gpstd_ReqTypeType;                      /* Request type TYPE */
uint16_t        usb_gpstd_ReqTypeRecip;                     /* Request type RECIPIENT */
uint16_t        usb_gpstd_ReqRequest;                       /* Request */
uint16_t        usb_gpstd_ReqValue;                         /* Value */
uint16_t        usb_gpstd_ReqIndex;                         /* Index */
uint16_t        usb_gpstd_ReqLength;                        /* Length */

uint16_t        usb_gpstd_AltNum[USB_ALT_NO];               /* Alternate number */
uint16_t        usb_gcstd_XckeMode;
USB_REQUEST_t   usb_gpstd_ReqReg;           /* Device Request - Request structure */

dtc_transfer_data_cfg_t    usb_td_cfg[2];
dtc_transfer_data_t        usb_dtc_transfer_data[2];
static bool g_is_opened = false; /* Indicate whether DTC is opened. */
BSP_CFG_USER_LOCKING_TYPE g_bsp_Locks[BSP_NUM_LOCKS];  


/* USB data transfer */
/* PIPEn Buffer counter */
uint32_t        usb_gcstd_DataCnt[USB_NUM_USBIP][USB_MAX_PIPE_NO + 1u];
/* DMA0 direction */
uint16_t        usb_gcstd_Dma0Dir[USB_NUM_USBIP];
/* DMA0 buffer size */
uint32_t        usb_gcstd_Dma0Size[USB_NUM_USBIP];
/* DMA0 FIFO buffer size */
uint16_t        usb_gcstd_Dma0Fifo[USB_NUM_USBIP];
/* DMA0 pipe number */
uint16_t        usb_gcstd_Dma0Pipe[USB_NUM_USBIP];
/* PIPEn Buffer pointer(8bit) */
uint8_t         *usb_gcstd_DataPtr[USB_NUM_USBIP][USB_MAX_PIPE_NO + 1u];

uint8_t     usb_dtc_alignment_size;         /* Rounded 4Byte Alignent size for USB DTC Transfer data size */
uint8_t     usb_dtc_alignment_data[4];      /* Store rounded 4Byte Alignent data for USB DTC Transfer data */

/* Message pipe */
USB_UTR_t       *usb_gcstd_Pipe[USB_NUM_USBIP][USB_MAX_PIPE_NO + 1u];

/* Priority Table */
static USB_MSG_t*   usb_scstd_TableAdd[USB_PRIMAX][USB_TABLEMAX];
static uint8_t      usb_scstd_TableID[USB_PRIMAX][USB_TABLEMAX];
static uint8_t      usb_scstd_PriR[USB_PRIMAX];
static uint8_t      usb_scstd_PriW[USB_PRIMAX];
static uint8_t      usb_scstd_Pri[USB_IDMAX];

/* Schedule Set Flag  */
static uint8_t      usb_scstd_ScheduleFlag;

/* Fixed-sized memory pools */
static USB_UTR_t    usb_scstd_Block[USB_BLKMAX];
static uint8_t      usb_scstd_BlkFlg[USB_BLKMAX];
static USB_MSG_t*   usb_scstd_Add_use;
static uint8_t      usb_scstd_ID_use;

/* Wait MSG */
static USB_MSG_t*   usb_scstd_WaitAdd[USB_IDMAX][USB_WAIT_EVENT_MAX];
static uint16_t     usb_scstd_WaitCounter[USB_IDMAX][USB_WAIT_EVENT_MAX];

/* PCDC <--> USB massage */
USB_UTR_t usb_gpcdc_Mess[10];
/* Line Coding data */
USB_PCDC_LineCoding_t usb_gcdc_LineCoding;
/* Line Coding Set Request data */
USB_PCDC_LineCoding_t usb_gcdc_LineCodingReq;

/* Call Back Function Info Transfer end */
USB_CB_t usb_gpcdc_TxCB;
/* Call Back Function Info Receive complete */
USB_CB_t usb_gpcdc_RxCB;
/* Call Back Function Info Serial Status Transfer end*/
USB_CB_t usb_gpcdc_StatCB;


uint16_t        usb_gpstd_StallPipe[USB_MAX_PIPE_NO + 1u];  /* Stall Pipe info */
USB_CB_t        usb_gpstd_StallCB;                          /* Stall Callback function */

static USB_PCDINFO_t    *usb_spstd_PcdMsg;  /* Pcd Task receive message */

uint16_t    usb_gcdc_connected;                 /* Peri CDC application enable */
uint8_t     cdc_trans_data[CDC_DATA_LEN + 4];   /* USB transfer Data */
uint32_t    cdc_trans_len;
USB_UTR_t   cdc_utr;                            /* USB IP channel no, USB IP base address */
DEV_INFO_t  cdc_dev_info;                       /* CDC device control structure */

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char tx_buf[100];


void usbwritecomplete(USB_UTR_t *mess, uint16_t data1, uint16_t data2)
{
	usb_tx_wait_f = PROCESS_WAIT_OFF;
}

void USB_PRINTF(char *format, ...)
{
  volatile char  i ,j,k;
  volatile char f, ch, z, n, c, m;
  char          scratch[16], *ptr,flag;
  uint32_t      val , base;
  va_list       ap;
  uint16_t event;
	
	flag=0;
	i=0;
	val=0;

	va_start(ap,format);
	for(;;)
	{
		while ((f = *format++) != '%')
		{
			if (!f)	{
				va_end (ap);
				tx_buf[i] =0x00;
				flag=1;
				break;
			}else{
				tx_buf[i]=f;
				i++;
			}
		}
		if(flag==1)	break;

		c =0;
		if (!(z=(f = *format++) == '0')) format--;
		f = *format++;
		if(f >='1' && f<='9') n = f - '0'; else{n = 0;	format--;}
		
		m =0 ;
		switch(f = *format++){
			case 'c':
				f = va_arg(ap,int);
			default:
				tx_buf[i]=f;
				i++;
				continue;
			case 's':
				ptr = va_arg(ap,char *);
				for(j=0;j<strlen(ptr);j++){
					tx_buf[i++] = *ptr;
					ptr++;
				}
				continue;
			case 'o':
				val = va_arg(ap,long);
				base = 8L;
				goto CONV_LOOP;
			case 'd':
				val = va_arg(ap,long);
				base = 10L;
				if((long)val < 0L){
					m=1;
					val = -val;
				}
				goto CONV_LOOP;
			case 'b':
				val = va_arg(ap,uint32_t);
				base = 2L;
				goto CONV_LOOP;
			case'u':
				val = (long)va_arg(ap,uint32_t);
				base =10L;
				goto CONV_LOOP;
			case 'X':
				c=1;
			case 'x':
				base = 16L;
				val = (long)va_arg(ap,uint32_t);
CONV_LOOP:
			for(j=0; j<16; j++)scratch[j]= z ? '0' : ' ';
			ptr = scratch + 16;
			*--ptr = 0;
			j=0;
			do {
				ch = (char) val % base + '0';
          			if (ch > '9') ch += (c ? 'A' : 'a')  - '9' - 1;
          			*--ptr = ch;
          			val /= base;
					j++;
        		} while (val);
        	if (m) {*--ptr = '-';j++;}
			if(n>j){
				for(k=0;k<(n-j);k++){
					--ptr;
					j++;
				}
			}
//        	if (n) ptr = scratch + 15 - n;//n‚ÍŒ…”
//			for(j=0;j<(strlen(ptr));j++){
			for(k=0;k<j;k++){
				tx_buf[i++]=*ptr;
				ptr++;
			}//for
		}//switch
	}//for
	
	flag=0;
	
    while(1)
    {
        usb_cdc_driver();                           /* USB Driver(Peripheral CDC) */
        switch( cdc_dev_info.state )                /* Check application state */
        {
        case STATE_DATA_TRANSFER:                           /* Data transfer state */
			event =cdc_event_get();
			if(event == EVENT_USB_WRITE_START){
				R_usb_pcdc_SendData( &cdc_utr, (uint8_t *)tx_buf, (uint32_t)i,	(USB_CB_t)&cdc_write_complete);
				usb_tx_wait_f = PROCESS_WAIT_ON;
			}else if(event == EVENT_USB_WRITE_COMPLETE){
				usb_tx_wait_f = PROCESS_WAIT_OFF;
				flag=1;
			}else{
		        if( PROCESS_WAIT_OFF == usb_tx_wait_f )
        		{
		            com_port_receive_size = NOT_DATA_RECEIVE;
                    cdc_event_set( EVENT_USB_WRITE_START );       /* Set Event()  */
                }
			}
	        break;
        case STATE_ATTACH:                          /* Wait Connect(USB Configured) state */
            cdc_connect_wait();
    	    break;
        case STATE_DETACH:
            cdc_detach_device();                    /* Detach process */
        	break;
        default:
	        break;
        }
		if(flag==1){
			break;
		}
    }
}
	
void USB_CHECK(void){
	static char counter=0;
	if(counter==0){
		usb_cdc_driver();
		switch( cdc_dev_info.state ){
		        case STATE_DATA_TRANSFER:                   /* Data transfer state */
				if(counter==0){
					R_usb_pcdc_SendData( &cdc_utr, (uint8_t *)cdc_init_msg, sizeof( cdc_init_msg ),(USB_CB_t)&usb_cstd_DummyFunction );
					counter=1;
				}
		 	case STATE_ATTACH:                          /* Wait Connect(USB Configured) state */
    	   	     		cdc_connect_wait();
    		    		break;
      		  	case STATE_DETACH:
       	     			cdc_detach_device();                /* Detach process */
        			break;
       			default:
		       	 	break;
        	}
	}
}
	

void init_usb( void )
{

	usb_mcu_init();              /* USB pin function and port mode setting. */
	usb_driver_init();           /* USB Initialization process */
	apl_init();                  /* Peripheral CDC Sample APL Initialize Command Send */
	
    cdc_low_power_control( STATE_ATTACH );  /* MCU Low power control */
	usb_tx_wait_f = PROCESS_WAIT_OFF;

	
}
///////////////////////////////////////////////////////////////////////////////
/// Peripheral CDC Driver
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
Function Name   : usb_cdc_driver
Description     : USB Driver(Peripheral CDC)
Arguments       : none 
Return value    : none
******************************************************************************/
void usb_cdc_driver( void )
{

    R_usb_cstd_Scheduler();                         /* The scheduler. */
    if( USB_FLGSET == R_usb_cstd_CheckSchedule() )  /* Check message for task */
    {
        R_usb_pstd_PcdTask((USB_VP_INT)0);          /* PCD Task */
        R_usb_pcdc_task(0);                         /* Peripheral Communications Devices Class Task */
    }

}   /* eof usb_cdc_driver() */

/******************************************************************************
Function Name   : R_usb_pcdc_task
Description     : Call Peripheral CDC task
Arguments       : USB_VP_INT_t stacd        : start code
Return value    : none
******************************************************************************/
void R_usb_pcdc_task(USB_VP_INT_t stacd)
{
    /* Peripheral CDC Task call */
    usb_pcdc_task( stacd );
} /* eof R_usb_pcdc_task */

/******************************************************************************
Function Name   : usb_pcdc_task
Description     : Peripheral Communications Devices Class main task
Arguments       : USB_VP_INT_t stacd        : start code
Return value    : none
******************************************************************************/
void usb_pcdc_task(USB_VP_INT_t stacd)
{
    uint16_t ret;
    USB_UTR_t   *mess;
    USB_ER_t    err = 0l;

    /* Pipe Transfer */
    err = R_USB_TRCV_MSG( USB_PCDC_MBX, (USB_MSG_t**)&mess, (uint16_t)3000 );
    if( err == USB_E_OK )
    {
        switch( mess->msginfo  )
        {
        /* Get Line Coding */
        case USB_PCDC_PGET_LINE_CODING:
            /* CallBack function (SND_MSG) */
            (mess->complete)(mess, 0, 0 );

            err = USB_REL_BLK(USB_PCDC_MPL, (USB_MH_t)mess);
            if( err != USB_E_OK )
            {
                //SCI_printf( "### pcdcTask case else rel_blk error (%ld)\n", err);
            }
            break;

        /* CDC Class Request Set Line Coding */
        case USB_PCDC_PSET_LINE_CODING:
            /* Line coding set parameter check */
            ret = usb_cpu_Sci_SetDataChk(
                (uint8_t *)&usb_gcdc_LineCodingReq.dwDTERate
                , usb_gcdc_LineCodingReq.bCharFormat
                , usb_gcdc_LineCodingReq.bParityType
                , usb_gcdc_LineCodingReq.bDataBits);
            if( ret == USB_OK )
            {
                /* Line Coding Parameter set */
                memcpy(&usb_gcdc_LineCoding,&usb_gcdc_LineCodingReq,7);
            }

            /* CallBack function (SND_MSG) */
            (mess->complete)(mess, 0, 0 );

            err = R_USB_REL_BLK(USB_PCDC_MPL, (USB_MH_t)mess);
            if( err != USB_E_OK )
            {
                //SCI_printf( "### pcdcTask case else rel_blk error (%ld)\n", err);
            }
            break;

        /* CDC Class Request Set Control Line State */
        case USB_PCDC_PSET_CONTROL_LINE_STATE:
            /* RS-232 signal RTS & DTR Set */
            /* If RTS/DTR control function is prepared, calls this function here */

            /* CallBack function (SND_MSG) */
            (mess->complete)(mess, 0, 0 );

            err = R_USB_REL_BLK(USB_PCDC_MPL, (USB_MH_t)mess);
            if( err != USB_E_OK )
            {
                //SCI_printf( "### pcdcTask case else rel_blk error (%ld)\n", err);
            }
            break;

        /* CDC Class Request Send Break */
        case USB_PCDC_PSEND_BREAK:
            /* RS-232 style break */
            /* If BREAK signal output function is prepared, calls this function here */

            /* CallBack function (SND_MSG) */
            (mess->complete)(mess, 0, 0 );
            err = R_USB_REL_BLK(USB_PCDC_MPL, (USB_MH_t)mess);
            if( err != USB_E_OK )
            {
                //SCI_printf( "### pcdcTask case else rel_blk error (%ld)\n", err);
            }
            break;
        case USB_PCDC_PSEND_DATA:
            usb_gpcdc_TxCB  = (USB_CB_t)mess->complete;

            mess->complete = &usb_pcdc_InTransResult;
            /* Data send request for Host */
            err = usb_pcdc_UserDataTrans(mess, USB_PCDC_USE_PIPE_IN, mess->tranlen, mess->tranadr);

            err = R_USB_REL_BLK(USB_PCDC_MPL, (USB_MH_t)mess);
            if( err != USB_E_OK )
            {
                //SCI_printf("### pcdcTask SendData rel_blk error (%ld)\n", err);
            }
            break;
        case USB_PCDC_PRECEIVE_DATA:
            usb_gpcdc_RxCB  = (USB_CB_t)mess->complete;

            mess->complete = &usb_pcdc_OutTransResult;
            /* Data Receive request for Host */
            err = usb_pcdc_UserDataTrans(mess, USB_PCDC_USE_PIPE_OUT, mess->tranlen, mess->tranadr);

            err = R_USB_REL_BLK(USB_PCDC_MPL, (USB_MH_t)mess);
            if( err != USB_E_OK )
            {
                //SCI_printf("### pcdcTask ReceiveData rel_blk error (%ld)\n", err);
            }
            break;
        case USB_PCDC_PSERIAL_STATE_NOTIFICATION:
            usb_gpcdc_StatCB    = (USB_CB_t)mess->complete;

            mess->complete = &usb_pcdc_StatusTransResult;
            /* Serial State send request for Host */
            err = usb_pcdc_UserDataTrans(mess, USB_PCDC_USE_PIPE_STATUS, mess->tranlen, mess->tranadr);

            /* Class Notification Serial State for USB Host */
            err = R_USB_REL_BLK(USB_PCDC_MPL, (USB_MH_t)mess);
            if( err != USB_E_OK )
            {
                //SCI_printf("### pcdcTask SerialStateTx rel_blk error (%ld)\n", err);
            }
            break;
        case USB_PCDC_PDATASND:
            /* Data Send Transfer complete call back */
            (usb_gpcdc_TxCB)(mess,0,0);
            break;
        case USB_PCDC_PDATARCV:
            /* Data Receive Transfer complete call back */
            (usb_gpcdc_RxCB)(mess,0,0);
            break;
        case USB_PCDC_PSTATUSSND:
            /* Status Send Transfer complete call back */
            (usb_gpcdc_StatCB)(mess,0,0);
            break;
        default:
            break;
        }
    }
} /* eof usb_pcdc_task */

/******************************************************************************
Function Name   : usb_cpu_Sci_SetDataChk
Description     : Line coding set data check
Arguments       : data_rate   : Data terminal rate in bits per second
                : stop_bit    : Stop bits 0-1Stopbit 1-1.5Stopbit 2-2Stopbit
                : parity      : Parity 0-None 1-Odd 2-Even 3-Mark 4-Spase
                : data_bit    : Data bits(5,6,7,8 or 16)
Return value    : Error code  : Error code
******************************************************************************/
uint16_t usb_cpu_Sci_SetDataChk(uint8_t *data_rate_top, uint8_t stop_bit, uint8_t parity, uint8_t data_bit)
{
    uint16_t ret_code = USB_OK;
    uint32_t data_rate;

    /* DATA RATE Set */
    data_rate = (uint32_t)data_rate_top[0];
    data_rate |= (uint32_t)data_rate_top[1] << 8;
    data_rate |= (uint32_t)data_rate_top[2] << 16;
    data_rate |= (uint32_t)data_rate_top[3] << 24;

    /* DATA RATE Setting */
    if((data_rate != USB_SCI_SPEED_1200)
        && (data_rate != USB_SCI_SPEED_2400)
        && (data_rate != USB_SCI_SPEED_4800)
        && (data_rate != USB_SCI_SPEED_9600)
        && (data_rate != USB_SCI_SPEED_14400)
        && (data_rate != USB_SCI_SPEED_19200)
        && (data_rate != USB_SCI_SPEED_38400)
        && (data_rate != USB_SCI_SPEED_57600)
        && (data_rate != USB_SCI_SPEED_115200))
    {
        ret_code = USB_NG;
    }

    /* STOP BIT Setting */
    if((stop_bit != USB_SCI_STOP_BIT_1)
        && (stop_bit != USB_SCI_STOP_BIT_2))
    {
        ret_code = USB_NG;
    }

    /* PARITY BIT Setting */
    if((parity != USB_SCI_PARITY_BIT_NONE)
        && (parity != USB_SCI_PARITY_BIT_ODD)
        && (parity != USB_SCI_PARITY_BIT_EVEN))
    {
        ret_code = USB_NG;
    }

    /* CHARACTER LENGTH Setting */
    if((data_bit != USB_SCI_DATA_BIT_8) 
        && (data_bit != USB_SCI_DATA_BIT_7))
    {
        ret_code = USB_NG;
    }

    return ret_code;
}


/******************************************************************************
Function Name   : usb_pcdc_StatusTransResult
Description     : CallBack Function
Arguments       : USB_UTR_t *mess  ; Information of the result when UART state is sent to Host
                : uint16_t  data1  ; Not use
                : uint16_t  data2  ; Not use 
Return value    : none
******************************************************************************/
void usb_pcdc_StatusTransResult(USB_UTR_t *mess, uint16_t data1, uint16_t data2)
{
    USB_ER_t    err;

    /* From USB device to PCDC */
    mess->msginfo = (uint16_t)USB_PCDC_PSTATUSSND;
    if( mess->status == USB_DATA_STOP )
    {
        //SCI_printf("### Peripheral Communications Devices driver stoped !\n");
    }
    err = R_USB_SND_MSG(USB_PCDC_MBX, (USB_MSG_t*)mess);
    if( err != USB_E_OK )
    {
        /* Send message failure */
        //SCI_printf("### pcdcTransResult snd_msg error (%ld)\n", err);
    }
} /* eof usb_pcdc_StatusTransResult */

/******************************************************************************
Function Name   : R_usb_cstd_SndMsg
Description     : Send a message to the specified id (mailbox).
Argument        : uint8_t id        : ID number (mailbox).
                : USB_MSG_t* mess   : Message pointer
Return          : USB_ER_t          : USB_E_OK / USB_E_ERROR
******************************************************************************/
USB_ER_t R_usb_cstd_SndMsg( uint8_t id, USB_MSG_t* mess )
{
    USB_ER_t    status;

    status = usb_cstd_SndMsg( id, mess );

    return status;
}

/******************************************************************************
Function Name   : usb_pcdc_OutTransResult
Description     : OUT Data Transfer Callback Function 
Argument        : USB_UTR_t *mess      ; OUT Transfer result information
                : uint16_t  data1      ; Not use
                : uint16_t  data2      ; Not use
Return          : none
******************************************************************************/
void usb_pcdc_OutTransResult(USB_UTR_t *mess, uint16_t data1, uint16_t data2)
{
    USB_ER_t    err;

    /* From USB device to PCDC */
    mess->msginfo = (uint16_t)USB_PCDC_PDATARCV;
    if( mess->status == USB_DATA_STOP )
    {
        //SCI_printf("### Peripheral Comm Devices driver stoped !\n");
    }
    err = R_USB_SND_MSG(USB_PCDC_MBX, (USB_MSG_t*)mess);
    if( err != USB_E_OK )
    {
        /* Send message failure */
        //SCI_printf("### pcdcTransResult snd_msg error (%ld)\n", err);
    }
} /* eof usb_pcdc_OutTransResult */

/******************************************************************************
Function Name   : usb_pcdc_UserDataTrans
Description     : Data Transfer Processing to USB Host
Argument        : USB_UTR_t *ptr   ; USB system internal structure. Selects channel.
                : uint16_t pipe    ; Pipe No
                : uint32_t size    ; Size
                : uint8_t  *table  ; Transfer Data Start address
Return          : USB_ER_t         ; 
******************************************************************************/
USB_ER_t usb_pcdc_UserDataTrans(USB_UTR_t *ptr, uint16_t pipe, uint32_t size, uint8_t *table)
{   
    /* PIPE Transfer set */
    usb_gpcdc_Mess[pipe].msghead    = (USB_MH_t)NULL;
    usb_gpcdc_Mess[pipe].keyword    = pipe;
    usb_gpcdc_Mess[pipe].tranadr    = table;
    usb_gpcdc_Mess[pipe].tranlen    = size;
    usb_gpcdc_Mess[pipe].setup  = 0;
    usb_gpcdc_Mess[pipe].complete   = ptr->complete;
    usb_gpcdc_Mess[pipe].segment    = USB_TRAN_END;

    usb_gpcdc_Mess[pipe].ipp        = ptr->ipp;
    usb_gpcdc_Mess[pipe].ip     = ptr->ip;

    return( R_usb_pstd_TransferStart((USB_UTR_t *)&usb_gpcdc_Mess[pipe]) );
} /* eof usb_pcdc_UserDataTrans */

/******************************************************************************
Function Name   : R_usb_pstd_TransferStart
Description     : Transfer the data of each pipe 
                : Request PCD to transfer data, and the PCD transfers the data 
                  based on the transfer information stored in ptr
Arguments       : USB_UTR_t *ptr : keyword, msghead and msginfo are used for...  $REA
Return value    : USB_ER_t       : Error info.
******************************************************************************/
USB_ER_t R_usb_pstd_TransferStart(USB_UTR_t *ptr)
{
    USB_ER_t        err;
    uint16_t        pipenum;

    pipenum = ptr->keyword;
    if( usb_gcstd_Pipe[ptr->ip][pipenum] != USB_NULL )
    {
        /* Get PIPE TYPE */
        if( usb_cstd_GetPipeType(ptr, pipenum) != USB_ISO )
        {
            //SCI_printf("### R_usb_pstd_TransferStart overlaps %d\n", pipenum);
            return USB_E_QOVR;
        }
    }

    /* Check state ( Configured ) */
    if( usb_pstd_ChkConfigured(ptr) != USB_YES )
    {
        //SCI_printf("### R_usb_pstd_TransferStart not configured\n");
        return USB_E_ERROR;
    }

    if( pipenum == USB_PIPE0 )
    {
        //SCI_printf("### R_usb_pstd_TransferStart PIPE0 is not support\n");
        return USB_E_ERROR;
    }

    ptr->msghead    = (USB_MH_t)USB_NULL;
    ptr->msginfo    = USB_MSG_PCD_SUBMITUTR;
    /* Send message */
    err = USB_SND_MSG(USB_PCD_MBX, (USB_MSG_t*)ptr);
    if( err != USB_E_OK )
    {
        //SCI_printf("### pTransferStart snd_msg error (%ld)\n", err);
    }
    return err;
}/* eof R_usb_pstd_TransferStart() */

/******************************************************************************
Function Name   : usb_cstd_SndMsg
Description     : Send a message to the specified id (mailbox).
Argument        : uint8_t id        : ID number (mailbox).
                : USB_MSG_t* mess   : Message pointer
Return          : USB_ER_t          : USB_E_OK / USB_E_ERROR
******************************************************************************/
USB_ER_t usb_cstd_SndMsg( uint8_t id, USB_MSG_t* mess )
{
    USB_ER_t    status;

    /* USB interrupt disable */
    usb_cpu_int_disable((USB_UTR_t*)mess);
    status = usb_cstd_iSndMsg(id,mess);
    /* USB interrupt enable */
    usb_cpu_int_enable((USB_UTR_t*)mess);
    return status;
}

/******************************************************************************
Function Name   : usb_pstd_ChkConfigured
Description     : Check if USB Device is in a CONFIGURED state. 
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
Return value    : Configuration state (YES/NO)
******************************************************************************/
uint16_t usb_pstd_ChkConfigured(USB_UTR_t *ptr)
{
    uint16_t    buf;

    buf = usb_creg_read_intsts( ptr );
    /* Device Status - Configured check */
    if( (buf & USB_DVSQ) == USB_DS_CNFG )
    {
        /* Configured */
        return USB_YES;
    }
    else
    {
        /* not Configured */
        return USB_NO;
    }
} /* eof usb_pstd_ChkConfigured() */

/******************************************************************************
Function Name   : usb_cstd_GetPipeType
Description     : Fetch and return PIPE TYPE.
Arguments       : uint16_t pipe            : Pipe number.
Return value    : uint16_t Pipe type
******************************************************************************/
uint16_t usb_cstd_GetPipeType(USB_UTR_t *ptr, uint16_t pipe)
{
    uint16_t        buffer;

    /* Pipe select */
    usb_creg_write_pipesel( ptr, pipe );
    /* Read Pipe direction */
    buffer = usb_creg_read_pipecfg( ptr );
    return (uint16_t)(buffer & USB_TYPFIELD);
}

/******************************************************************************
Function Name   : usb_pcdc_InTransResult
Description     : IN Data Transfer Callback Function 
Argument        : USB_UTR_t *mess       ; IN Transfer result information
                : uint16_t  data1       ; Not use
                : uint16_t  data2       ; Not use
Return          : none
******************************************************************************/
void usb_pcdc_InTransResult(USB_UTR_t *mess, uint16_t data1, uint16_t data2)
{
    USB_ER_t    err;

    /* From USB device to PCDC */
    mess->msginfo = (uint16_t)USB_PCDC_PDATASND;
    if( mess->status == USB_DATA_STOP )
    {
        //SCI_printf("### Peripheral Comm Devices driver stoped !\n");
    }
    err = R_USB_SND_MSG(USB_PCDC_MBX, (USB_MSG_t*)mess);
    if( err != USB_E_OK )
    {
        /* Send message failure */
        //SCI_printf("### pcdcTransResult snd_msg error (%ld)\n", err);
    }
} /* eof usb_pcdc_InTransResult */

/******************************************************************************
Function Name   : R_usb_cstd_RelBlk
Description     : Call the function to release a memory block.
Argument        : uint8_t id        : ID number (mailbox).
                : USB_UTR_t* blk    : Memory block pointer.
Return          : USB_ER_t          : USB_E_OK / USB_E_ERROR
******************************************************************************/
USB_ER_t R_usb_cstd_RelBlk( uint8_t id,  USB_UTR_t* blk )
{
    USB_ER_t err;

    err = usb_cstd_RelBlk( id, blk );

    return  err;
}

/******************************************************************************
Function Name   : usb_cstd_RelBlk
Description     : Release a memory block.
Argument        : uint8_t id        : ID number (mailbox).
                : USB_UTR_t* blk    : Memory block pointer.
Return          : USB_ER_t          : USB_E_OK / USB_E_ERROR
******************************************************************************/
USB_ER_t usb_cstd_RelBlk( uint8_t id,  USB_UTR_t* blk )
{
    uint16_t    usb_s_rblk_c;

    if( id < USB_IDMAX )
    {
        usb_s_rblk_c = USB_CNTCLR;
        while(usb_s_rblk_c != USB_BLKMAX)
        {
            if(blk == &usb_scstd_Block[usb_s_rblk_c])
            {
                /* Release fixed-size memory block */
                usb_scstd_BlkFlg[usb_s_rblk_c] = USB_FLGCLR;
                return  USB_E_OK;
            }
            usb_s_rblk_c++;
        }
        /* Error of BLK Flag is not CLR !!  */
        //SCI_printf("TskBlk NO CLR !!\n");
    }
    return  USB_E_ERROR;
}

/******************************************************************************
Function Name   : R_usb_cstd_RecMsg
Description     : Receive a message to the specified id (mailbox).
Argument        : uint8_t id        : ID number (mailbox).
                : USB_MSG_t** mess  : Message pointer
                : USB_TM_t tm       : Timeout Value
Return          : uint16_t          : USB_E_OK / USB_E_ERROR
******************************************************************************/
USB_ER_t R_usb_cstd_RecMsg( uint8_t id, USB_MSG_t** mess, USB_TM_t tm )
{
    USB_ER_t err;

    err = usb_cstd_RecMsg( id,  mess, tm );

    return err;
}

/******************************************************************************
Function Name   : usb_cstd_RecMsg
Description     : Receive a message to the specified id (mailbox).
Argument        : uint8_t id        : ID number (mailbox).
                : USB_MSG_t** mess  : Message pointer
                : USB_TM_t tm       : Timeout Value
Return          : uint16_t          : USB_E_OK / USB_E_ERROR
******************************************************************************/
USB_ER_t usb_cstd_RecMsg( uint8_t id, USB_MSG_t** mess, USB_TM_t tm )
{
    if(( id < USB_IDMAX ) && ( usb_scstd_ID_use < USB_IDMAX ))
    {
        if( id == usb_scstd_ID_use )
        {
            *mess = usb_scstd_Add_use;
            return  USB_E_OK;
        }
    }   
    return  USB_E_ERROR;
}

/******************************************************************************
Function Name   : R_usb_pstd_PcdTask
Description     : Call PCD (Peripheral Control Driver) task (API for nonOS).
Arguments       : USB_VP_INT stacd: Start Code
Return value    : none
******************************************************************************/
void R_usb_pstd_PcdTask(USB_VP_INT stacd)
{
    usb_pstd_PcdTask( stacd );
}/* eof R_usb_pstd_PcdTask() */

/******************************************************************************
Function Name   : usb_pstd_PcdTask
Description     : The Peripheral Control Driver(PCD) task.
Arguments       : USB_VP_INT stacd
Return value    : none
******************************************************************************/
void usb_pstd_PcdTask(USB_VP_INT stacd)
{
    USB_UTR_t       *mess, *ptr;
    /* Error code */
    USB_ER_t        err;
    uint16_t        pipenum;

    err = USB_TRCV_MSG(USB_PCD_MBX, (USB_MSG_t**)&mess, (USB_TM_t)10000);
    if( (err != USB_E_OK) )
    {
        return;
    }

    ptr = (USB_UTR_t *)mess;

    usb_spstd_PcdMsg = (USB_PCDINFO_t*)mess;
    pipenum = usb_spstd_PcdMsg->keyword;

    /* Detach is all device */
    switch( usb_spstd_PcdMsg->msginfo )
    {
    case USB_MSG_PCD_INT:
        /* USB INT */
        usb_pstd_Interrupt((USB_UTR_t*)usb_spstd_PcdMsg);
        break;
    case USB_MSG_PCD_PCUTINT:
        /* Start Oscillation : Interrupt wakeup */
        usb_cstd_InterruptClock(ptr);
        ptr = (USB_UTR_t*)usb_spstd_PcdMsg;
        /* USB interrupt Handler */
        usb_pstd_InterruptHandler(ptr);
        /* USB INT */
        usb_pstd_Interrupt((USB_UTR_t*)usb_spstd_PcdMsg);
        ptr->msginfo = USB_MSG_PCD_INT;
        break;

    case USB_MSG_PCD_SUBMITUTR:
        /* USB Submit utr */
        usb_pstd_SetSubmitutr(ptr, (USB_UTR_t*)usb_spstd_PcdMsg);
        break;
    case USB_MSG_PCD_REMOTEWAKEUP:
        usb_cstd_SelfClock(ptr);
        usb_pstd_RemoteWakeup(ptr);
        /* Process Done Callback function */
        (usb_spstd_PcdMsg->complete)(ptr, (uint16_t)USB_NO_ARG, USB_MSG_PCD_REMOTEWAKEUP);
        /* PCD memory pool release */
        usb_pstd_PcdRelMpl((uint16_t)1u);
        break;

    case USB_MSG_PCD_CLRSEQBIT:
        usb_creg_set_sqclr(ptr, pipenum);
        /* Process Done Callback function */
        (usb_spstd_PcdMsg->complete)(ptr, (uint16_t)USB_NO_ARG, USB_MSG_PCD_CLRSEQBIT);
        /* PCD memory pool release */
        usb_pstd_PcdRelMpl((uint16_t)2u);
        break;
    case USB_MSG_PCD_SETSTALL:
        usb_pstd_SetStall(ptr, pipenum);
        usb_gpstd_StallPipe[pipenum] = USB_YES;
        usb_gpstd_StallCB = usb_spstd_PcdMsg->complete;
        /* PCD memory pool release */
        usb_pstd_PcdRelMpl((uint16_t)3u);
        break;

    case USB_MSG_PCD_TRANSEND1:
        /* End of all pipes */
        if( usb_gcstd_Pipe[ptr->ip][pipenum] != USB_NULL )
        {
            /* Transfer timeout */
            usb_cstd_ForcedTermination(ptr, pipenum, (uint16_t)USB_DATA_TMO);
        }
        else
        {
            //SCI_printf("### Peri not transferd-1 %d\n", pipenum);
        }
        /* PCD memory pool release */
        usb_pstd_PcdRelMpl((uint16_t)4u);
        break;
    case USB_MSG_PCD_TRANSEND2:
        /* End of all pipes */
        if( usb_gcstd_Pipe[ptr->ip][pipenum] != USB_NULL )
        {
            /* Transfer stop */
            usb_cstd_ForcedTermination(ptr, pipenum, (uint16_t)USB_DATA_STOP);
        }
        else
        {
            //SCI_printf("### Peri not transferd-2 %d\n", pipenum);
        }
        /* PCD memory pool release */
        usb_pstd_PcdRelMpl((uint16_t)5u);
        break;

    case USB_MSG_PCD_DETACH:
        usb_cstd_SelfClock(ptr);
        /* USB detach */
        usb_pstd_DetachProcess(ptr);
        /* Process Done Callback function */
        (usb_spstd_PcdMsg->complete)(ptr, (uint16_t)USB_NO_ARG, USB_MSG_PCD_DETACH);
        /* PCD memory pool release */
        usb_pstd_PcdRelMpl((uint16_t)6u);
        break;
    case USB_MSG_PCD_ATTACH:
        usb_cstd_SelfClock(ptr);
        usb_pstd_AttachProcess(ptr);
        /* Process Done Callback function */
#ifdef USB_PERI_BC_ENABLE
        (usb_spstd_PcdMsg->complete)(ptr, (uint16_t)g_usb_bc_detect, USB_MSG_PCD_ATTACH);
#else
        (usb_spstd_PcdMsg->complete)(ptr, (uint16_t)USB_NO_ARG, USB_MSG_PCD_ATTACH);
#endif
        /* PCD memory pool release */
        usb_pstd_PcdRelMpl((uint16_t)7u);
        break;

    case USB_MSG_PCD_DP_ENABLE:
        usb_pstd_DpEnable(ptr);
        /* Process Done Callback function */
        (usb_spstd_PcdMsg->complete)(ptr, (uint16_t)USB_NO_ARG, USB_MSG_PCD_DP_ENABLE);
        /* PCD memory pool release */
        usb_pstd_PcdRelMpl((uint16_t)8u);
        break;
    case USB_MSG_PCD_DP_DISABLE:
        usb_pstd_DpDisable(ptr);
        /* Process Done Callback function */
        (usb_spstd_PcdMsg->complete)(ptr, (uint16_t)USB_NO_ARG, USB_MSG_PCD_DP_DISABLE);
        /* PCD memory pool release */
        usb_pstd_PcdRelMpl((uint16_t)9u);
        break;
    case USB_MSG_PCD_DM_ENABLE:
        /* Process Done Callback function */
        (usb_spstd_PcdMsg->complete)(ptr, (uint16_t)USB_NO_ARG, USB_MSG_PCD_DM_ENABLE);
        /* PCD memory pool release */
        usb_pstd_PcdRelMpl((uint16_t)10u);
        break;
    case USB_MSG_PCD_DM_DISABLE:
        /* Process Done Callback function */
        (usb_spstd_PcdMsg->complete)(ptr, (uint16_t)USB_NO_ARG, USB_MSG_PCD_DM_DISABLE);
        /* PCD memory pool release */
        usb_pstd_PcdRelMpl((uint16_t)11u);
        break;

    case USB_MSG_PCD_D0FIFO_INT:
        usb_cstd_D0fifoInt(ptr);
        break;

	case USB_MSG_PCD_D1FIFO_INT:
        break;

    case USB_MSG_PCD_RESM_INT:
        break;

    default:
        while( 1 )
        {
        };
        break;
    }
}

/******************************************************************************
Function Name   : usb_cstd_D0fifoInt
Description     : Set end of DMA/DTC transfer. Set to restart DMA/DTC trans-
                : fer according to data size of remaining functions to be pro-
                : cessed.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
Return value    : none
******************************************************************************/
void usb_cstd_D0fifoInt(USB_UTR_t *ptr)
{
    uint16_t pipe;
    uint16_t ip;
    uint16_t maxps;
    uint32_t *transfer_count;

    ip = ptr->ip;
    pipe = usb_gcstd_Dma0Pipe[ip];
    maxps = usb_gcstd_Dma0Fifo[ip];
    transfer_count = &usb_gcstd_DataCnt[ip][pipe];

    if ( *transfer_count >= maxps )                             /* Transfer count >= MAXPS */
    {
        *transfer_count %= maxps;                               /* DMA Transfer count update */
        if( *transfer_count != 0 )                              /* Transfer continue check */
        {
            /* Transfer count != MAXPS * N */
            if(ptr->ip == USB_USBIP_0)                          /* Odd size data check  */

            {
                if( (*transfer_count & 0x0001u) != 0u )         /* if count == odd */
                {
                    usb_creg_set_mbw( ptr, USB_D0DMA, USB_MBW_8 );
                }
            }
            else if(ptr->ip == USB_USBIP_1)
            {
                if( (*transfer_count & 0x0001u) != 0u )                    /* if count == odd */
                {
                    usb_creg_set_mbw( ptr, USB_D0DMA, USB_MBW_8 );
                }
            }
            usb_gcstd_Dma0Size[ip] = *transfer_count;           /* DMA Transfer size update */
            usb_cpu_d0fifo_restart_dma(ptr);                    /* DMA Restart */
            usb_cpu_d0fifo_enable_dma(ptr);                     /* DTC(D0FIFO) interrupt enable */
            usb_creg_set_dreqe( ptr, USB_D0DMA );               /* DMA Transfer Request Set */
        }
        else
        {
            if( usb_dtc_alignment_size )                        /* Check Rounded data for 4Byte Alignment */
            {
                /* count == odd ( 1 to 3 ) */
                *transfer_count = usb_dtc_alignment_size;
                usb_creg_set_mbw( ptr, USB_D0DMA, USB_MBW_8 );
                usb_gcstd_Dma0Size[ip] = *transfer_count;       /* DMA Transfer size update */
                usb_cpu_d0fifo_restart_dma(ptr);                /* DMA Restart */
                usb_cpu_d0fifo_enable_dma(ptr);                 /* DTC(D0FIFO) interrupt enable */
                usb_creg_set_dreqe( ptr, USB_D0DMA );           /* DMA Transfer Request Set */
                usb_dtc_alignment_size = 0;
            }
        }
    }
    else if( *transfer_count == 0 )
    {
        return;                                         /* More than enough Interrupt */
    }
    else
    {
        usb_cstd_dtc_write_not_4alignment(ptr);         /* Write Rounded data for D0FIFO */
        usb_creg_set_bval( ptr, USB_D0DMA );            /* Transfer count < MAXPS */
        *transfer_count = 0;                            /* Transfer complete */
    }
    if( *transfer_count == 0 )                          /* Transfer complete check */
    {
        usb_creg_set_bempenb(ptr, pipe);                /* Enable Empty Interrupt */
    }
}/* eof usb_cstd_D0fifoInt() */

/******************************************************************************
Function Name   : usb_cstd_dtc_write_not_4alignment
Description     : Write Rounded data for D0FIFO
Arguments       : USB_UTR_t *ptr        : USB internal structure. Selects USB channel. 
Return value    : none
******************************************************************************/
void usb_cstd_dtc_write_not_4alignment(USB_UTR_t *ptr)
{
    /* Check alignment data */
    if( usb_dtc_alignment_size > USB_BYTE_SIZE_0 )
    {
        /* DMA buffer clear mode & MBW set */
        usb_creg_set_mbw( ptr, USB_D0DMA, USB_MBW_8 );

        /* Write alignment data for D0FIFO */
        if( usb_dtc_alignment_size == USB_BYTE_SIZE_3 )
        {
            usb_creg_write_fifo8( ptr, USB_D0DMA, usb_dtc_alignment_data[0] );
            usb_creg_write_fifo8( ptr, USB_D0DMA, usb_dtc_alignment_data[1] );
            usb_creg_write_fifo8( ptr, USB_D0DMA, usb_dtc_alignment_data[2] );
        }
        else if( usb_dtc_alignment_size == USB_BYTE_SIZE_2 )
        {
            usb_creg_write_fifo8( ptr, USB_D0DMA, usb_dtc_alignment_data[0] );
            usb_creg_write_fifo8( ptr, USB_D0DMA, usb_dtc_alignment_data[1] );
        }
        else
        {
            usb_creg_write_fifo8( ptr, USB_D0DMA, usb_dtc_alignment_data[0] );
        }

        usb_dtc_alignment_size = USB_BYTE_SIZE_0;
    }
}   /* eof usb_cstd_dtc_write_not_4alignment() */

/******************************************************************************
Function Name   : usb_cpu_d0fifo_enable_dma
Description     : DTC(D0FIFO) interrupt enable (Interrupt priority 5 set)
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel. 
Return value    : none
******************************************************************************/
void usb_cpu_d0fifo_enable_dma(USB_UTR_t *ptr)
{
    if( ptr->ip == USB_USBIP_0 )
    {
        /* Priority D0FIFO0 = 0(Disable)
        b3-b0 IPR      Interrupt priority
        b7-b4 Reserved 0
        */
        IPR( USB0, D0FIFO0 ) = 0x05;
    }
}

/******************************************************************************
Function Name   : usb_cpu_d0fifo_restart_dma
Description     : DMA Restart
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel. 
Return value    : none
******************************************************************************/
void usb_cpu_d0fifo_restart_dma( USB_UTR_t *ptr )
{
    uint16_t    size;
    uint32_t    tmp;
    dtc_activation_source_t    act_src;    /* activation source is Software Interrupt */


    if(ptr->ip == USB_USBIP_0)
    {
        act_src = DTCE_USB0_D0FIFO0;

        if( (usb_gcstd_Dma0Size[ptr->ip] & 0x0001u) != 0u )
        {
            /* if count == odd */
            tmp = usb_gcstd_Dma0Size[ptr->ip];

            /* DTC mode register A (Byte Size)
            b1-b0 Reserved 0
            b3-b2 SM       source address mode bit
            b5-b4 SZ       DTC data transfer size bit
            b7-b6 MD       DTC mode bit
            */
            usb_td_cfg[ptr->ip].data_size = DTC_DATA_SIZE_BYTE;

            /* DTC source address register (Table address)
            b31-b0 SAR Source address
            */
            usb_td_cfg[ptr->ip].dest_addr = usb_cstd_GetD0fifo8Adr(ptr);
        }
        else
        {
            tmp = usb_gcstd_Dma0Size[ptr->ip] / 2;

            /* DTC mode register A (Word Size)
            b1-b0 Reserved 0
            b3-b2 SM       source address mode bit
            b5-b4 SZ       DTC data transfer size bit
            b7-b6 MD       DTC mode bit
            */
            usb_td_cfg[ptr->ip].data_size = DTC_DATA_SIZE_WORD;
        }
    }

    /* DTC source address register (Table address)
    b31-b0 SAR Destination address
    */
    usb_td_cfg[ptr->ip].source_addr = usb_dtc_transfer_data[ptr->ip].lw2;

    size = (uint8_t)(tmp);

    /* DTC transfer count registerA
    b15-b0 CRA Transfer count
    */
    usb_td_cfg[ptr->ip].block_size = (uint16_t)(size);

    /* DTC transfer count registerB (Block count)
    b15-b0 CRB Transfer count
    */
    usb_td_cfg[ptr->ip].transfer_count = (uint16_t)(1);
    
    if( ptr->ip == USB_USBIP_0 )
    {
        IEN( USB0, D0FIFO0 ) = 0;
        R_DTC_Create( act_src, &usb_dtc_transfer_data[ptr->ip], &usb_td_cfg[ptr->ip], 0 );
        IEN( USB0, D0FIFO0 ) = 1;
    }
    /* DTC Transfer enable
    b0    DTCST    DTC module start bit
    b7-b1 Reserved 0
    */
    R_DTC_Control( DTC_CMD_DTC_START, NULL, 0 );

    if( ptr->ip == USB_USBIP_0 )
    {
        /* DTC start enable register (USB0 D0FIFO transfer)
        b0    DTCE     DTC start enable bit
        b7-b1 Reserved 0
        */
        DTCE( USB0, D0FIFO0 ) = 1;
    }
}

/*******************************************************************************
* Function Name: R_DTC_Control
* Description  : Starts / Stops DTC, enables or disables Data transfer read skip,
*                selects an interrupt source as DTC activation.
* Arguments    : command -
*                    Action will be done
*                p_stat -
*                    Pointer to the status of DTC module when command is 
*                     DTC_CMD_GET_STATUS, casted to void *.
*                p_args -
*                    Pointer to argument of command, casted to void *.
* Return Value : DTC_SUCCESS -
*                    Successful operation
*                DTC_ERR_NOT_OPEN -
*                    The DTC is not initialized yet.
*                DTC_ERR_INVALID_COMMAND -
*                    Command parameters are invalid.
*                DTC_ERR_NULL_PTR -
*                    The argument is NULL when commnad is valid.
*                DTC_ERR_BUSY
*                    The resource are locked by another process.
*
*******************************************************************************/
dtc_err_t R_DTC_Control(dtc_command_t command, dtc_stat_t *p_stat, dtc_cmd_arg_t *p_args)
{
#if (1 == DTC_CFG_PARAM_CHECKING_ENABLE)

    if ((DTC_CMD_STATUS_GET == command) && (NULL == p_stat))
    {
        return DTC_ERR_NULL_PTR;
    }
    else if ((DTC_CMD_ACT_SRC_ENABLE == command) || (DTC_CMD_ACT_SRC_DISABLE == command) || 
             (DTC_CMD_CHAIN_TRANSFER_ABORT == command))
    {
        if (NULL == p_args) /* Require argument */
        {
            return DTC_ERR_NULL_PTR;
        }
    }
    else
    {
        /* do nothing */
    }

#endif /* DTC_CFG_PARAM_CHECKING_ENABLE */

    if (false == g_is_opened)
    {
        r_dtc_release_hw_lock();
        return DTC_ERR_NOT_OPEN;
    }

    switch (command)
    {
        case DTC_CMD_DTC_START: /* Start DTC module. */
            DTC.DTCST.BIT.DTCST = 1;
        break;

        case DTC_CMD_DTC_STOP: /* Stop DTC module. */
            DTC.DTCST.BIT.DTCST = 0;
        break;

        case DTC_CMD_DATA_READ_SKIP_ENABLE: /* Enable Transfer Data Read Skip. */
            DTC.DTCCR.BIT.RRS = 1;
        break;

        case DTC_CMD_DATA_READ_SKIP_DISABLE: /* Disable Transfer Data Read Skip. */
            DTC.DTCCR.BIT.RRS = 0;
        break;

        case DTC_CMD_ACT_SRC_ENABLE: /* Select one interrupt as a DTC activation source. */
            ICU.DTCER[p_args->act_src].BIT.DTCE = 1;
        break;

        case DTC_CMD_ACT_SRC_DISABLE: /* Remove one interrupt as a DTC activation source. */
            ICU.DTCER[p_args->act_src].BIT.DTCE = 0;
        break;

        case DTC_CMD_STATUS_GET:
            if (0 == (DTC.DTCSTS.WORD & DTC_ACT_BIT_MASK)) /* DTC transfer operation is not in progress. */
            {
                p_stat->in_progress = false;
                /* DTC is not in progress. -> vector number is invalid. */
            }
            else /* DTC transfer operation is in progress. */
            {
                p_stat->in_progress = true;
                /* Get the current vector number. */
                p_stat->vect_nr = (uint8_t)(DTC.DTCSTS.WORD & DTC_VECT_NR_MASK); /* get lower 8 bits: 0-7*/
            }
        break;

        case DTC_CMD_CHAIN_TRANSFER_ABORT:
            r_dtc_abort_chain_transfer(p_args->chain_transfer_nr);
        break;

        default:
            return DTC_ERR_INVALID_COMMAND;
        break;
    }

    return DTC_SUCCESS;
}

/*******************************************************************************
* Function Name: r_dtc_abort_chain_transfer
* Description  : Aborts the current active chain transfer.
* Arguments    : chain_transfer_nr -
*                   Number of chain transfer
* Return Value : true -
*                   Abort successfully.
*                false
*                   Can not abort.
*******************************************************************************/
static bool r_dtc_abort_chain_transfer(uint32_t chain_transfer_nr)
{
    volatile uint32_t cnt = 0;
    uint16_t          status_reg = 0;

    status_reg = DTC.DTCSTS.WORD;

    volatile dtc_internal_registers_t *td_ptr = NULL;

    if (0 == (status_reg & 0x8000)) /* DTC is not active. */
    {
        return false;
    }

    status_reg &= 0xFF; /* Get the vector number. */
    td_ptr = (volatile dtc_internal_registers_t *)*((uint32_t *)DTC.DTCVBR + status_reg) + chain_transfer_nr - 1;

    while (cnt < chain_transfer_nr)
    {
        td_ptr->FIRST_LWORD.REG.MRB.BIT.CHNE = 0;
        td_ptr--;
        cnt++;
    }

    return true;
}

/*******************************************************************************
* Function Name: r_dtc_release_hw_lock
* Description  : release hardware lock BSP_LOCK_DTC.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
static void r_dtc_release_hw_lock(void)
{
    R_BSP_HardwareUnlock(BSP_LOCK_DTC);
    return;
}

/***********************************************************************************************************************
* Function Name: R_BSP_HardwareUnlock
* Description  : Release hold on lock.
* Arguments    : hw_index -
*                    Index in locks array to the hardware resource to unlock.
* Return Value : true -
*                    Lock was released.
*                false -
*                    Lock was not released.
***********************************************************************************************************************/
bool R_BSP_HardwareUnlock (mcu_lock_t const hw_index)
{
    /* Pass actual lock to software unlock function. */
    return R_BSP_SoftwareUnlock(&g_bsp_Locks[hw_index]);
} /* End of function R_BSP_HardwareUnlock() */

/***********************************************************************************************************************
* Function Name: R_BSP_SoftwareUnlock
* Description  : Release hold on lock.
* Arguments    : plock -
*                    Pointer to lock structure with lock to release.
* Return Value : true -
*                    Lock was released.
*                false -
*                    Lock was not released.
***********************************************************************************************************************/
bool R_BSP_SoftwareUnlock (BSP_CFG_USER_LOCKING_TYPE * const plock)
{
    /* Set lock back to unlocked. */
    plock->lock = false;

    return true;
} /* End of function R_BSP_SoftwareUnlock() */

/*******************************************************************************
* Function Name: R_DTC_Create
* Description  : Creates the Transfer data for a specified interrupt source.
* Arguments    : act_source -
*                    Activation source
*                p_transfer_data -
*                    Pointer to start address of Transfer data area on RAM
*                p_data_cfg -
*                    Pointer to contains the settings for Transfer data
*                chain_transfer_nr -
*                    Number of chain transfer
* Return Value : DTC_SUCCESS -
*                    Successful operation
*                DTC_ERR_NOT_OPEN -
*                    The DTC is not initialized yet.
*                DTC_ERR_INVALID_ARG -
*                    Parameters are invalid.
*                DTC_ERR_NULL_PTR -
*                    The pointers are NULL.
*                DTC_ERR_BUSY -
*                    The resource are locked by another process.
*******************************************************************************/
dtc_err_t R_DTC_Create(dtc_activation_source_t act_source, dtc_transfer_data_t *p_transfer_data,
                       dtc_transfer_data_cfg_t *p_data_cfg, uint32_t chain_transfer_nr)
{
    uint32_t  count       = chain_transfer_nr + 1;
    uint32_t *ptr         = NULL;
    uint8_t   dtce_backup = 0;
    uint8_t   rrs_backup  = 0;

#if (1 == DTC_CFG_PARAM_CHECKING_ENABLE)

    if ((NULL == p_data_cfg) || (NULL == p_transfer_data))
    {
        return DTC_ERR_NULL_PTR;
    }

    if ((p_data_cfg->transfer_count < DTC_MIN_COUNT_VAL) || (p_data_cfg->transfer_count > DTC_MAX_16BITS_COUNT_VAL))
    {
        return DTC_ERR_INVALID_ARG;
    }

#endif /* DTC_CFG_PARAM_CHECKING_ENABLE */

    if (false == g_is_opened) /* DTC is not initialized yet. */
    {
        r_dtc_release_hw_lock();
        return DTC_ERR_NOT_OPEN;
    }

    /* Store old value of DTCERn.DTCE bit. */
    dtce_backup = ICU.DTCER[act_source].BIT.DTCE;
    /* Disable the interrupt source. Clear the DTCER */
    ICU.DTCER[act_source].BIT.DTCE = 0;

    /* Store old value of DTCCR.RRS bit. */
    rrs_backup = DTC.DTCCR.BIT.RRS;
    /* Clear RRS bit. */
    DTC.DTCCR.BIT.RRS = 0;

    /* The row in Vector table corresponding to act_source */
    ptr = (uint32_t *)((uint32_t)DTC.DTCVBR + (4 * act_source));
    /* Write start address of Transfer data to Vector table. */
    *ptr = (uint32_t)p_transfer_data;

    while (count > 0)
    {
        if (DTC_SUCCESS != r_dtc_set_transfer_data(p_transfer_data, p_data_cfg))
        { /* Fail to apply configurations for Transfer data. */
            /* Restore RRS bit */
            DTC.DTCCR.BIT.RRS = rrs_backup;
            /* Restore the DTCE bit. */
            ICU.DTCER[act_source].BIT.DTCE = dtce_backup;
            return DTC_ERR_INVALID_ARG;
        }
        else
        {
            p_data_cfg++;
            p_transfer_data++;
        }
        count--;
    }

    /* Restore RRS bit. */
    DTC.DTCCR.BIT.RRS = rrs_backup;
    /* Restore the DTCE bit. */
    ICU.DTCER[act_source].BIT.DTCE = dtce_backup;

    return DTC_SUCCESS;
}

/*******************************************************************************
* Function Name: r_dtc_set_transfer_data
* Description  : Applies configurations to a Transfer data area, it is an internal
*                function called by R_DTC_Create(); and all arguments are validated
*                in R_DTC_Create()
* Arguments    : transfer_data -
*                    Start address of Transfer data
*                data_cfg -
*                    Contains configurations for the Transfer data
* Return Value : DTC_SUCCESS -
*                    Apply configurations for Transfer data successfully.
*                DTC_ERR_INVALID_ARG
*                    Fail to apply configurations for Transfer data.
*******************************************************************************/
static dtc_err_t r_dtc_set_transfer_data(dtc_transfer_data_t *p_transfer_data,
                                   dtc_transfer_data_cfg_t *p_cfg)
{
    dtc_mra_t                          t_mra;
    dtc_mrb_t                          t_mrb;
    dtc_cra_t                          t_cra;
    dtc_crb_t                          t_crb;
    volatile dtc_internal_registers_t *td_ptr = (volatile dtc_internal_registers_t *)p_transfer_data;

    /* Set for MRA - . */
    t_mra.BYTE = (uint8_t)(p_cfg->src_addr_mode | p_cfg->data_size | p_cfg->transfer_mode);
    t_mrb.BYTE = (uint8_t)(p_cfg->dest_addr_mode | p_cfg->repeat_block_side | p_cfg->response_interrupt |
                            p_cfg->chain_transfer_enable | p_cfg->chain_transfer_mode);

    switch (t_mra.BIT.MD) /* DTC transfer mode */
    {
        case 0x0: /* Normal mode */
            if (DTC_MAX_16BITS_COUNT_VAL == p_cfg->transfer_count)/* Transfer count = 65536 */
            {
                t_cra.WORD = 0x0000;
            }
            else /* 1 - 65535 */
            {
                t_cra.WORD = (uint16_t)p_cfg->transfer_count;
            }
        break;

        case 0x1: /* Repeat mode */
            /* Set counter. */
            if (p_cfg->transfer_count < DTC_MAX_8BITS_COUNT_VAL) /* count 1-255 */
            {
                t_cra.BYTE.CRA_H = (uint8_t)p_cfg->transfer_count;
                t_cra.BYTE.CRA_L = (uint8_t)p_cfg->transfer_count;
            }
            else if (DTC_MAX_8BITS_COUNT_VAL == p_cfg->transfer_count)
            {
                t_cra.BYTE.CRA_H = 0x00;
                t_cra.BYTE.CRA_L = 0x00;
            }
            else /* Transfer count > 256 */
            {
                return DTC_ERR_INVALID_ARG;
            }
        break;

        case 0x2: /* DTC_TRANSFER_MODE_BLOCK - Block transfer mode */
            /* Set counter. */
            if (DTC_MAX_16BITS_COUNT_VAL == p_cfg->transfer_count)/* Transfer count = 65536 */
            {
                t_crb.WORD = 0x0000;
            }
            else /* 1 - 65535 */
            {
                t_crb.WORD = (uint16_t)p_cfg->transfer_count;
            }

            if (p_cfg->block_size < DTC_MAX_8BITS_COUNT_VAL) /* Block size 1-255 */
            {
                t_cra.BYTE.CRA_H = (uint8_t)p_cfg->block_size;
                t_cra.BYTE.CRA_L = (uint8_t)p_cfg->block_size;
            }
            else if (DTC_MAX_8BITS_COUNT_VAL == p_cfg->block_size) /* Block size = 256 */
            {
                t_cra.BYTE.CRA_H = 0;
                t_cra.BYTE.CRA_L = 0;
            }
            else /* Invalid block size */
            {
                return DTC_ERR_INVALID_ARG;
            }
        break;

        default:
            return DTC_ERR_INVALID_ARG;
        break;
    }

/* Full-address mode */
    /* settings for fist long word: MRA & MRB */
    td_ptr->FIRST_LWORD.REG.MRA.BYTE = t_mra.BYTE; /* 1 byte MRA */
    td_ptr->FIRST_LWORD.REG.MRB.BYTE = t_mrb.BYTE; /* 1 byte MRB */

    /* settings for second long word: SAR */
    td_ptr->SECOND_LWORD.SAR = p_cfg->source_addr; /* 4 byte SAR */

    /* settings for third long word: DAR */
    td_ptr->THIRD_LWORD.DAR = p_cfg->dest_addr; /* 4 byte DAR */

    /* settings for fourth long word: CRA & CRB */
    td_ptr->FOURTH_LWORD.REG.CRA.WORD = t_cra.WORD;
    td_ptr->FOURTH_LWORD.REG.CRB.WORD = t_crb.WORD;
    return DTC_SUCCESS;
}

/******************************************************************************
Function Name   : usb_pstd_DpEnable
Description     : D+ Line Pull-up Enable
Arguments       : USB_UTR_t *ptr    : USB system internal structure.
Return value    : none
******************************************************************************/
void usb_pstd_DpEnable(USB_UTR_t *ptr)
{

    usb_preg_set_dprpu( ptr );

}

/******************************************************************************
Function Name   : usb_pstd_DpDisable
Description     : D+ Line Pull-up Disable
Arguments       : USB_UTR_t *ptr    : USB system internal structure.
Return value    : none
**************************************************************************/
void usb_pstd_DpDisable(USB_UTR_t *ptr)
{

    usb_preg_clr_dprpu( ptr );

}

/******************************************************************************
Function Name   : usb_pstd_AttachProcess
Description     : USB attach setting.
Arguments       : none
Return value    : none
******************************************************************************/
void usb_pstd_AttachProcess(USB_UTR_t *ptr)
{
    usb_pstd_AttachFunction( ptr );
    usb_cpu_DelayXms((uint16_t)10);
#ifdef USB_PERI_BC_ENABLE
    usb_pstd_bc_detect_process(ptr);
#endif /* USB_PERI_BC_ENABLE */
    usb_preg_set_dprpu( ptr );

}

/******************************************************************************
Function Name   : usb_cpu_DelayXms
Description     : xms Delay timer
Arguments       : uint16_t  time        ; Delay time(*1ms)
Return value    : void
Note            : Please change for your MCU
******************************************************************************/
void usb_cpu_DelayXms(uint16_t time)
{
    /* Wait xms (Please change for your MCU) */
    volatile register uint32_t  i;

    /* Wait 1ms */
    for( i = 0; i < (6500 * time); ++i )
    {
    };
        /* When "ICLK=120MHz" is set, this code is waiting for 1ms.
          Please change this code with CPU Clock mode. */
}

/******************************************************************************
Function Name   : usb_pstd_AttachFunction
Description     : Processing for attach detect.(Waiting time of stabilize VBUS.)
Arguments       : USB_UTR_t *ptr    : USB system internal structure.
Return value    : none
******************************************************************************/
void usb_pstd_AttachFunction(USB_UTR_t *ptr)
{
    /* Delay about 10ms(Waiting time of stabilize VBUS.) */
    usb_cpu_DelayXms((uint16_t)10);
}

/******************************************************************************
Function Name   : usb_cstd_DummyFunction
Description     : dummy function
Arguments       : uint16_t data1    : Not used.
                : uint16_t data2    : Not used.
Return value    : none
******************************************************************************/
void usb_cstd_DummyFunction(USB_UTR_t *ptr, uint16_t data1, uint16_t data2)
{
}

/******************************************************************************
Function Name   : usb_cstd_DummyTrn
Description     : dummy function
Arguments       : USB_REQUEST_t *data1  : Not used.
                : uint16_t data2        : Not used.
Return value    : none
******************************************************************************/
void usb_cstd_DummyTrn(USB_UTR_t *ptr, USB_REQUEST_t *data1, uint16_t data2)
{
}

/******************************************************************************
Function Name   : usb_pstd_DetachProcess
Description     : Initialize USB registers for detaching, and call the callback
                : function that completes the detach.
Arguments       : USB_UTR_t *ptr    : USB system internal structure.
Return value    : none
******************************************************************************/
void usb_pstd_DetachProcess(USB_UTR_t *ptr)
{
    uint16_t        i, conf;
    uint16_t        *tbl;

    usb_creg_clr_cnen( ptr );
    /* Pull-up disable */
    usb_preg_clr_dprpu( ptr );
    usb_cpu_Delay1us((uint16_t)2);
    usb_creg_set_dcfm( ptr );
    usb_cpu_Delay1us((uint16_t)1);
    usb_creg_clr_dcfm( ptr );

    conf = usb_gpstd_ConfigNum;
    if( conf < (uint16_t)1 )
    {
        /* Address state */
        conf = (uint16_t)1;
    }

    /* Configuration number */
    usb_gpstd_ConfigNum = 0;
    /* Remote wakeup enable flag */
    usb_gpstd_RemoteWakeup = USB_NO;

    /* INTSTS0 clear */
    usb_gpstd_intsts0 = 0;

    tbl = usb_gpstd_Driver.pipetbl[conf - 1];
    for( i = 0; tbl[i] != USB_PDTBLEND; i += USB_EPL )
    {
        usb_cstd_ForcedTermination(ptr, tbl[i], (uint16_t)USB_DATA_STOP);
        usb_cstd_ClrPipeCnfg(ptr, tbl[i]);
    }
    /* Callback */
    (*usb_gpstd_Driver.devdetach)(ptr, (uint16_t)USB_NO_ARG, (uint16_t)USB_NO_ARG);
    usb_cstd_StopClock(ptr);
}

/******************************************************************************
Function Name   : usb_cstd_StopClock
Description     : Not processed as the functionality is provided by R8A66597(ASSP).
Arguments       : USB_UTR_t *ptr    : Not used
Return value    : none
******************************************************************************/
void usb_cstd_StopClock(USB_UTR_t *ptr)
{
}/* eof usb_cstd_StopClock() */

/******************************************************************************
Function Name   : usb_cstd_ClrPipeCnfg
Description     : Clear specified pipe configuration register.
Arguments       : USB_UTR_t *ptr    : USB system internal structure. Selects channel.
                : uint16_t pipe_no  : pipe number
Return value    : none
******************************************************************************/
void usb_cstd_ClrPipeCnfg(USB_UTR_t *ptr, uint16_t pipe_no)
{
    uint16_t    buffer;

    usb_gcstd_Pipe[ptr->ip][pipe_no] = (USB_UTR_t*)USB_NULL;

    /* PID=NAK & clear STALL */
    usb_cstd_ClrStall(ptr, pipe_no);
    
    /* Interrupt disable */
    /* Ready         Int Disable */
    usb_creg_clr_brdyenb( ptr, pipe_no );

    /* NotReady      Int Disable */
    usb_creg_clr_nrdyenb( ptr, pipe_no );

    /* Empty/SizeErr Int Disable */
    usb_creg_clr_bempenb( ptr, pipe_no );

    /* PIPE Configuration */
    usb_cstd_chg_curpipe(ptr, (uint16_t)USB_PIPE0, (uint16_t)USB_CUSE, USB_NO);
    /* Clear D0FIFO-port */
    buffer = usb_creg_read_fifosel( ptr, USB_D0DMA );

    if( (buffer & USB_CURPIPE) == pipe_no )
    {
        usb_cpu_d0fifo_stop_dma(ptr);

        usb_cstd_D0fifoStopUsb(ptr);
        usb_cstd_chg_curpipe(ptr, (uint16_t)USB_PIPE0, (uint16_t)USB_D0USE, USB_NO);
    }
    /* Clear D1FIFO-port */
    buffer = usb_creg_read_fifosel( ptr, USB_D1DMA );

    if( (buffer & USB_CURPIPE) == pipe_no )
    {
        if(ptr->ip == USB_USBIP_0)
        {
            usb_creg_set_mbw( ptr, USB_D1USE, USB0_D1FIFO_MBW );
        }
        else if (ptr->ip == USB_USBIP_1)
        {
            usb_creg_set_mbw( ptr, USB_D1USE, USB1_D1FIFO_MBW );
        }

        usb_cstd_chg_curpipe(ptr, (uint16_t)USB_PIPE0, (uint16_t)USB_D1USE, USB_NO);
    }
    usb_creg_write_pipesel( ptr, pipe_no );
    usb_creg_write_pipecfg( ptr, 0 );

    usb_creg_write_pipebuf( ptr, 0 );
    usb_creg_write_pipemaxp( ptr, 0 );
    usb_creg_write_pipeperi( ptr, 0 );
    usb_creg_write_pipesel( ptr, 0 );

    /* FIFO buffer DATA-PID initialized */
    /* SQCLR */
    usb_creg_set_sqclr(ptr, pipe_no);
    /* ACLRM */
    usb_cstd_DoAclrm(ptr, pipe_no);
    /* CSSTS */
    usb_creg_set_csclr(ptr, pipe_no);
    usb_cstd_ClrTransactionCounter(ptr, pipe_no);
    
    /* Interrupt status clear */
    /* Ready         Int Clear */
    usb_creg_clr_sts_brdy( ptr, pipe_no );

    /* NotReady      Int Clear */
    usb_creg_clr_sts_nrdy( ptr, pipe_no );

    /* Empty/SizeErr Int Clear */
    usb_creg_clr_sts_bemp( ptr, pipe_no );
}/* eof usb_cstd_ClrPipeCnfg() */

/******************************************************************************
Function Name   : usb_cstd_ClrTransactionCounter
Description     : Clear specified Pipe Transaction Counter Register.
Arguments       : USB_UTR_t *ptr    : USB system internal structure. Selects channel.
                : uint16_t trnreg   : Pipe Number
Return value    : none
******************************************************************************/
void usb_cstd_ClrTransactionCounter(USB_UTR_t *ptr, uint16_t trnreg)
{
    usb_creg_clr_trenb( ptr, trnreg );
    usb_creg_set_trclr( ptr, trnreg );
}/* eof usb_cstd_ClrTransactionCounter() */

/******************************************************************************
Function Name   : usb_cstd_D0fifoStopUsb
Description     : Setup external variables used for USB data transfer; to reg-
                : ister if you want to stop the transfer of DMA/DTC.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
Return value    : none
******************************************************************************/
void usb_cstd_D0fifoStopUsb(USB_UTR_t *ptr)
{
    uint16_t    ip = ptr->ip;
    uint16_t    pipe = usb_gcstd_Dma0Pipe[ip];
    uint32_t    transfer_size = usb_gcstd_Dma0Size[ip];
    uint32_t    *request_size = &usb_gcstd_DataCnt[ip][pipe];
    uint8_t     *tran_data_ptr = (uint8_t *)&usb_gcstd_DataPtr[ip][pipe];

    usb_creg_clr_dreqe( ptr, USB_D0DMA );

    /* Direction check */
    if( usb_gcstd_Dma0Dir[ip] == USB_BUF2FIFO )
    {
        /* Buffer to FIFO */
        if( *request_size < transfer_size )
        {
            /* >yes then set BVAL */
            *tran_data_ptr += *request_size;
            *request_size = (uint32_t)0u;
            /* Disable Ready Interrupt */
            usb_creg_clr_brdyenb(ptr, pipe);
            /* Set BVAL */
            usb_creg_set_bval( ptr, USB_D0DMA );
        }
        else
        {
            *tran_data_ptr += transfer_size;
            /* Set data count to remain */
            *request_size -= transfer_size;
        }
    }
    else
    {
        /* FIFO to Buffer */
        *tran_data_ptr += transfer_size;
        /* Set data count to remain */
        if( *request_size < transfer_size )
        {
            *request_size = transfer_size - *request_size;
        }
        else
        {
            *request_size -= transfer_size;
        }
    }
}/* eof usb_cstd_D0fifoStopUsb() */

/******************************************************************************
Function Name   : usb_cpu_d0fifo_stop_dma
Description     : DMA stop
Arguments       : USB_UTR_t *ptr        : USB internal structure. Selects USB channel. 
Return value    : void
******************************************************************************/
void usb_cpu_d0fifo_stop_dma(USB_UTR_t *ptr)
{
    if( ptr->ip == USB_USBIP_0 )
    {
        /* Interrupt request register
        b0    IR       Interrupt status flag
        b7-b1 Reserved 0
        */
        IR( USB0, D0FIFO0 ) = 0;

        /* Priority D0FIFO0=0
        b3-b0 IPR      Interrupt priority
        b7-b4 Reserved 0
        */
        IPR( USB0, D0FIFO0 ) = 0x00;

        /* Interrupt enable register (USB0 D0FIFO disable(IEN4))
        b0 IEN0 Interrupt enable bit
        b1 IEN1 Interrupt enable bit
        b2 IEN2 Interrupt enable bit
        b3 IEN3 Interrupt enable bit
        b4 IEN4 Interrupt enable bit
        b5 IEN5 Interrupt enable bit
        b6 IEN6 Interrupt enable bit
        b7 IEN7 Interrupt enable bit
        */
        IEN( USB0, D0FIFO0 ) = 0;

        /* DTC start enable register (USB0 D0FIFO transfer disable)
        b0    DTCE     DTC start enable bit
        b7-b1 Reserved 0
        */
        DTCE( USB0, D0FIFO0 ) = 0;
    }
}

/******************************************************************************
Function Name   : usb_cstd_chg_curpipe
Description     : Switch FIFO and pipe number.
Arguments       : USB_UTR_t *ptr    : USB system internal structure. Selects channel.
                : uint16_t pipe     : Pipe number.
                : uint16_t fifosel  : FIFO selected (CPU, D0, D1..)
                : uint16_t isel     : CFIFO Port Access Direction.(Pipe1 to 9:Set to 0)
Return value    : none
******************************************************************************/
void usb_cstd_chg_curpipe(USB_UTR_t *ptr, uint16_t pipe, uint16_t fifosel, uint16_t isel)
{
    uint16_t    buffer;

    /* Select FIFO */
    switch( fifosel )
    {
    /* CFIFO use */
    case USB_CUSE:
        /* ISEL=1, CURPIPE=0 */
        usb_creg_rmw_fifosel( ptr, USB_CUSE, (USB_RCNT|isel|pipe), (USB_RCNT|USB_ISEL|USB_CURPIPE) );
        do
        {
            buffer = usb_creg_read_fifosel( ptr, USB_CUSE );
        }
        while( (buffer & (uint16_t)(USB_ISEL|USB_CURPIPE))
            != (uint16_t)(isel|pipe) );
    break;
    /* D0FIFO use */
    case USB_D0USE:
    /* continue */
    /* D0FIFO DMA */
    case USB_D0DMA:
        /* D0FIFO pipe select */
        usb_creg_set_curpipe( ptr, USB_D0DMA, pipe );
        do
        {
            buffer = usb_creg_read_fifosel( ptr, USB_D0DMA );
        }
        while( (uint16_t)(buffer & USB_CURPIPE) != pipe );
        break;
    /* D1FIFO use */
    case USB_D1USE:
        /* continue */
    /* D1FIFO DMA */
    case USB_D1DMA:
        /* D1FIFO pipe select */
        usb_creg_set_curpipe( ptr, USB_D1DMA, pipe );

        do
        {
            buffer = usb_creg_read_fifosel( ptr, USB_D1DMA );
        }
        while( (uint16_t)(buffer & USB_CURPIPE) != pipe );
        break;
    default:
        break;
    }
}/* eof usb_cstd_chg_curpipe() */

/******************************************************************************
Function Name   : usb_creg_set_curpipe
Description     : Set pipe to the number given; in the FIFOSEL corresponding 
                : to specified PIPEMODE.
Arguments       : USB_UTR_t *ptr       : USB internal structure. Selects USB channel.
                : uint16_t pipemode : CUSE/D0DMA/D1DMA.
                : uint16_t pipeno   : Pipe number.
Return value    : none
******************************************************************************/
void    usb_creg_set_curpipe( USB_UTR_t *ptr, uint16_t  pipemode, uint16_t  pipeno )
{
    volatile uint16_t    *reg_p;
    uint16_t    reg;

    reg_p = usb_creg_get_fifosel_adr( ptr, pipemode );
    reg = *reg_p;

    reg &= ~USB_CURPIPE;
    reg |= pipeno;
    
    *reg_p = reg;
} /* eof usb_creg_set_curpipe() */

/******************************************************************************
Function Name   : usb_cstd_SetTransactionCounter
Description     : Set specified Pipe Transaction Counter Register.
Arguments       : USB_UTR_t *ptr    : USB system internal structure. Selects channel.
                : uint16_t trnreg   : Pipe number
                : uint16_t trncnt       : Transaction counter
Return value    : none
******************************************************************************/
void usb_cstd_SetTransactionCounter(USB_UTR_t *ptr, uint16_t trnreg, uint16_t trncnt)
{

    usb_creg_set_trclr( ptr, trnreg );
    usb_creg_write_pipetrn( ptr, trnreg, trncnt );
    usb_creg_set_trenb( ptr, trnreg );

}/* eof usb_cstd_SetTransactionCounter() */

/******************************************************************************
Function Name   : usb_cstd_DoAclrm
Description     : Set the ACLRM-bit (Auto Buffer Clear Mode) of the specified 
                : pipe.
Arguments       : USB_UTR_t *ptr : USB internal structure. Selects e.g. channel.
                : uint16_t pipe  : Pipe number.
Return value    : none
******************************************************************************/
void usb_cstd_DoAclrm(USB_UTR_t *ptr, uint16_t pipe)
{
    /* Control ACLRM */
    usb_creg_set_aclrm( ptr, pipe );
    usb_creg_clr_aclrm( ptr, pipe );
}

/******************************************************************************
Function Name   : usb_cstd_ClrStall
Description     : Set up to NAK the specified pipe, and clear the STALL-bit set
                : to the PID of the specified pipe.
Arguments       : USB_UTR_t *ptr : USB internal structure. Selects e.g. channel.
                : uint16_t pipe  : Pipe number.
Return value    : none
Note            : PID is set to NAK.
******************************************************************************/
void usb_cstd_ClrStall(USB_UTR_t *ptr, uint16_t pipe)
{
    /* Set NAK */
    usb_cstd_SetNak(ptr, pipe);
    /* Clear STALL */
    usb_creg_clr_pid( ptr, pipe, USB_PID_STALL );
}

/******************************************************************************
Function Name   : usb_cstd_SetNak
Description     : Set up to NAK the specified pipe.
Arguments       : USB_UTR_t *ptr    : USB system internal structure. Selects channel.
                : uint16_t pipe     : Pipe Number
Return value    : none
******************************************************************************/
void usb_cstd_SetNak(USB_UTR_t *ptr, uint16_t pipe)
{
    uint16_t        buf, n;

    /* Set NAK */
    usb_creg_clr_pid( ptr, pipe, (uint16_t)USB_PID_BUF );

    /* The state of PBUSY continues while transmitting the packet when it is a detach. */
    /* 1ms comes off when leaving because the packet duration might not exceed 1ms.  */
    /* Whether it is PBUSY release or 1ms passage can be judged. */
    for( n = 0; n < 0xFFFFu; ++n )
    {
        /* PIPE control reg read */
        buf = usb_creg_read_pipectr( ptr, pipe );
        if( (uint16_t)(buf & USB_PBUSY) == 0 )
        {
            n = 0xFFFEu;
        }
    }
}/* eof usb_cstd_SetNak() */

/******************************************************************************
Function Name   : usb_cpu_Delay1us
Description     : 1us Delay timer
Arguments       : uint16_t  time        ; Delay time(*1us)
Return value    : none
Note            : Please change for your MCU
******************************************************************************/
void usb_cpu_Delay1us(uint16_t time)
{
    volatile register uint16_t  i;

    /* Wait 1us (Please change for your MCU) */
    for( i = 0; i < (5 * time); ++i )
    {
    };
}

/******************************************************************************
Function Name   : usb_cstd_ForcedTermination
Description     : Terminate data transmission and reception.
Arguments       : USB_UTR_t *ptr    : USB system internal structure. Selects channel.
                : uint16_t pipe     : Pipe Number
                : uint16_t status   : Transfer status type
Return value    : none
Note            : In the case of timeout status, it does not call back.
******************************************************************************/
void usb_cstd_ForcedTermination(USB_UTR_t *ptr, uint16_t pipe, uint16_t status)
{
    uint16_t    buffer;

    /* PID = NAK */
    /* Set NAK */
    usb_cstd_SetNak(ptr, pipe);

    /* Disable Interrupt */
    /* Disable Ready Interrupt */
    usb_creg_clr_brdyenb(ptr, pipe);
    /* Disable Not Ready Interrupt */
    usb_creg_clr_nrdyenb(ptr, pipe);
    /* Disable Empty Interrupt */
    usb_creg_clr_bempenb(ptr, pipe);

    usb_cstd_ClrTransactionCounter(ptr, pipe);

    /* Clear D1FIFO-port */
    buffer = usb_creg_read_fifosel( ptr, USB_CUSE );
    if( (buffer & USB_CURPIPE) == pipe )
    {
        if(ptr->ip == USB_USBIP_0)
        {
            usb_creg_set_mbw( ptr, USB_CUSE, USB0_CFIFO_MBW );
        }
        else if (ptr->ip == USB_USBIP_1)
        {
            usb_creg_set_mbw( ptr, USB_CUSE, USB1_CFIFO_MBW );
        }

        /* Changes the FIFO port by the pipe. */
        usb_cstd_chg_curpipe(ptr, (uint16_t)USB_PIPE0, (uint16_t)USB_CUSE, USB_NO);
    }
    /* Clear D0FIFO-port */
    buffer = usb_creg_read_fifosel( ptr, USB_D0DMA );
    if( (buffer & USB_CURPIPE) == pipe )
    {
        /* Stop DMA,FIFO access */
        usb_cpu_d0fifo_stop_dma(ptr);

        usb_cstd_D0fifoStopUsb(ptr);
        usb_cstd_D0FifoselSet(ptr);
        if(ptr->ip == USB_USBIP_0)
        {
            usb_creg_write_dmacfg( ptr, USB_D0DMA, USB_CPU_ADR_RD_WR );
        }
        else if (ptr->ip == USB_USBIP_1)
        {
//            usb_creg_set_mbw( ptr, USB_D1USE, USB1_D1FIFO_MBW );
        }
        /* Changes the FIFO port by the pipe. */
        usb_cstd_chg_curpipe(ptr, (uint16_t)USB_PIPE0, (uint16_t)USB_D0USE, USB_NO);
    }
    /* Clear D1FIFO-port */
    buffer = usb_creg_read_fifosel( ptr, USB_D1DMA );
    if( (buffer & USB_CURPIPE) == pipe )
    {
        if(ptr->ip == USB_USBIP_0)
        {
            usb_creg_set_mbw( ptr, USB_D1USE, USB0_D1FIFO_MBW );
        }
        else if (ptr->ip == USB_USBIP_1)
        {
            usb_creg_set_mbw( ptr, USB_D1USE, USB1_D1FIFO_MBW );
        }
        /* Changes the FIFO port by the pipe. */
        usb_cstd_chg_curpipe(ptr, (uint16_t)USB_PIPE0, (uint16_t)USB_D1USE, USB_NO);
    }

    /* Changes the FIFO port by the pipe. */
    usb_cstd_chg_curpipe(ptr, pipe, (uint16_t)USB_CUSE, USB_NO);
    buffer = usb_creg_read_fifoctr( ptr, USB_CUSE );
    if( (uint16_t)(buffer & USB_FRDY) == USB_FRDY )
    {
        /* Clear BVAL */
        usb_creg_set_bclr( ptr, USB_CUSE );
    }

    /* FIFO buffer SPLIT transaction initialized */
    usb_cstd_chg_curpipe(ptr, (uint16_t)USB_PIPE0, (uint16_t)USB_CUSE, USB_NO);
    usb_creg_set_csclr(ptr, pipe);

    /* Call Back */
    if( usb_gcstd_Pipe[ptr->ip][pipe] != USB_NULL )
    {
        /* Transfer information set */
        usb_gcstd_Pipe[ptr->ip][pipe]->tranlen  = usb_gcstd_DataCnt[ptr->ip][pipe];
        usb_gcstd_Pipe[ptr->ip][pipe]->status   = status;
        usb_gcstd_Pipe[ptr->ip][pipe]->pipectr  = usb_creg_read_pipectr(ptr, pipe);
        usb_gcstd_Pipe[ptr->ip][pipe]->errcnt   = 0;

        usb_gcstd_Pipe[ptr->ip][pipe]->ipp  = ptr->ipp;
        usb_gcstd_Pipe[ptr->ip][pipe]->ip   = ptr->ip;

        if( USB_NULL != ( usb_gcstd_Pipe[ptr->ip][pipe]->complete ) )
        {
            (usb_gcstd_Pipe[ptr->ip][pipe]->complete)(usb_gcstd_Pipe[ptr->ip][pipe], 0, 0);
        }
        usb_gcstd_Pipe[ptr->ip][pipe] = (USB_UTR_t*)USB_NULL;
    }
}/* eof usb_cstd_ForcedTermination() */

/******************************************************************************
Function Name   : usb_cstd_D0FifoselSet
Description     : Set DOFIFO access width, set to DMA buffer clear mode and 
                : the endian setting.
Arguments       : USB_UTR_t *ptr    : USB system internal structure. Selects channel.
Return value    : none
******************************************************************************/
void usb_cstd_D0FifoselSet(USB_UTR_t *ptr)
{
    /* DMA buffer clear mode set */
    usb_creg_clr_dclrm( ptr, USB_D0DMA );
    /* Maximum bit width for FIFO access set */
    if(ptr->ip == USB_USBIP_0)
    {
        usb_creg_set_mbw( ptr, USB_D0DMA, USB0_D0FIFO_MBW );
    }
    else if (ptr->ip == USB_USBIP_1)
    {
        usb_creg_set_mbw( ptr, USB_D0DMA, USB1_D0FIFO_MBW );
    }

}/* eof usb_cstd_D0FifoselSet() */

/******************************************************************************
Function Name   : usb_pstd_PcdRelMpl
Description     : PCD REL_BLK send                          $REA
Arguments       : uint16_t n                                $REA
Return value    : none
******************************************************************************/
void usb_pstd_PcdRelMpl(uint16_t n)
{
    USB_ER_t        err;

    /* PCD memory pool release */
    err = USB_REL_BLK(USB_PCD_MPL, (USB_MH_t)usb_spstd_PcdMsg);
    if( err != USB_E_OK )
    {
        //SCI_printf("### usb_pstd_PcdRelMpl (%d) rel_blk error: %d\n", n, err);
    }
}

/******************************************************************************
Function Name   : usb_pstd_RemoteWakeup
Description     : Set the USB peripheral to implement remote wake up.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
Return value    : none
******************************************************************************/
void usb_pstd_RemoteWakeup(USB_UTR_t *ptr)
{
    uint16_t    buf;
    uint16_t    dev_info[8];

    /* Get USB Device information */
    R_usb_pstd_DeviceInformation(ptr, (uint16_t *)&dev_info );

    /* Support remote wakeup ? */
    if( dev_info[4] == USB_YES )
    {
        /* RESM interrupt disable */
        usb_preg_clr_enb_rsme( ptr );
        
        /* External clock enable */
        usb_creg_set_xcke( ptr );

        /* RESM status read */
        buf = usb_creg_read_intsts( ptr );
        if( (buf & USB_RESM) != (uint16_t)0 )
        {
            /* RESM status clear */
            usb_preg_clr_sts_resm( ptr );
        }
        else
        {
            if( (buf & USB_DS_SUSP) != (uint16_t)0 )
            {
                /* Remote wakeup set */
                usb_preg_set_wkup( ptr );
                usb_gpstd_intsts0   &= (uint16_t)(~USB_DS_SUSP);
            }
        }
    }
} /* eof usb_pstd_RemoteWakeup() */

/******************************************************************************
Function Name   : R_usb_pstd_DeviceInformation
Description     : Get USB Device information such as USB Device status and con-
                : figuration No. etc. 
Arguments       : USB_UTR_t *ptr : USB system internal structure.
                : uint16_t *tbl  : Device information storage pointer TBL. This 
                : pointer is used to provide the caller with the device's sta-
                : tus, speed, configuration and interface number, and the value
                : of the remote wakeup flag.
Return value    : none
******************************************************************************/
void R_usb_pstd_DeviceInformation(USB_UTR_t *ptr, uint16_t *tbl)
{
    /* Device status */
    tbl[0] = usb_creg_read_intsts( ptr ) & (uint16_t)(USB_VBSTS|USB_DVSQ);

    /* Speed */
    tbl[1] = usb_cstd_PortSpeed(ptr, (uint16_t)USB_PORT0);

    /* Configuration number */
    tbl[2] = usb_gpstd_ConfigNum;

    /* Interface number */
    tbl[3] = usb_pstd_GetInterfaceNum(usb_gpstd_ConfigNum);

    /* Remote Wakeup Flag */
    tbl[4] = usb_gpstd_RemoteWakeup;
}/* eof R_usb_pstd_DeviceInformation() */

/******************************************************************************
Function Name   : usb_pstd_GetInterfaceNum
Description     : Get interface number 
Arguments       : uint16_t con_num : Configuration Number
Return value    : uint16_t : Number of this interface 
                : (bNumInterfaces)
******************************************************************************/
uint16_t usb_pstd_GetInterfaceNum(uint16_t con_num)
{
    uint16_t    conf;
    uint16_t    num_if = 0;
    uint16_t    tbl_index;

    conf = con_num;
    if( conf < (uint16_t)1 )
    {
        /* Address state */
        conf = (uint16_t)1;
    }

    /* Get Configuration descriptor table index */
    tbl_index = usb_pstd_get_confignum_to_tblindex( conf );

    /* Get NumInterfaces.        4:bNumInterfaces */
    num_if = *(uint8_t*)(usb_gpstd_Driver.configtbl[tbl_index] + USB_DEV_B_NUM_INTERFACES);

    return num_if;
}

/******************************************************************************
Function Name   : usb_pstd_get_confignum_to_tblindex
Description     : Get Configuration descriptor table index 
Arguments       : uint16_t con_num : Configuration Number
Return value    : uint16_t : Configuration descriptor table index 
******************************************************************************/
uint16_t usb_pstd_get_confignum_to_tblindex(uint16_t con_num)
{
    uint16_t    conf;
    uint16_t    i;
    uint16_t    tbl_index = 0;

    conf = con_num;
    if( conf < (uint16_t)1 )
    {
        /* Address state */
        conf = (uint16_t)1;
    }

    /* Configuration Descriptor search loop */
    for( i = 0; i < con_num; i++ )
    {
        /* Check Configuration Number.   5:bConfigurationValue */
        if( *(uint8_t*)(usb_gpstd_Driver.configtbl[i] + USB_DEV_B_CONFIGURATION_VALUE) == con_num )
        {
            /* Set Configuration tabile index */
            tbl_index = i;
            break;
        }
    }

    return tbl_index;
}

/******************************************************************************
Function Name   : usb_cstd_PortSpeed
Description     : Get USB-speed of the specified port.
Arguments       : USB_UTR_t *ptr : USB internal structure. Selects e.g. channel.
                : uint16_t port  : Root port
Return value    : uint16_t       : HSCONNECT : Hi-Speed
                :                : FSCONNECT : Full-Speed
                :                : LSCONNECT : Low-Speed
                :                : NOCONNECT : not connect
******************************************************************************/
uint16_t usb_cstd_PortSpeed(USB_UTR_t *ptr, uint16_t port)
{
    uint16_t    buf, ConnInf;

    buf = usb_creg_read_dvstctr( ptr, port );

    /* Reset handshake status get */
    buf = (uint16_t)(buf & USB_RHST);

    switch( buf )
    {
    /* Get port speed */
    case USB_HSMODE:    ConnInf = USB_HSCONNECT;    break;
    case USB_FSMODE:    ConnInf = USB_FSCONNECT;    break;
    case USB_LSMODE:    ConnInf = USB_LSCONNECT;    break;
    case USB_HSPROC:    ConnInf = USB_NOCONNECT;    break;
    default:        ConnInf = USB_NOCONNECT;    break;
    }

    return (ConnInf);
}

/******************************************************************************
Function Name   : usb_cstd_SelfClock
Description     : Not processed as the functionality is provided by R8A66597(ASSP).
Arguments       : USB_UTR_t *ptr    : Not used
Return value    : none
******************************************************************************/
void usb_cstd_SelfClock(USB_UTR_t *ptr)
{
}/* eof usb_cstd_SelfClock() */

/******************************************************************************
Function Name   : usb_pstd_SetSubmitutr
Description     : USB Peripheral Submit utr.
Arguments       : USB_UTR_t *ptr    : USB system internal structure.
                : USB_UTR_t *utrmsg             $REA
Return value    : USB_ER_t
******************************************************************************/
USB_ER_t usb_pstd_SetSubmitutr(USB_UTR_t *ptr, USB_UTR_t *utrmsg)
{
    uint16_t    pipenum;

    pipenum = utrmsg->keyword;
    usb_gcstd_Pipe[ptr->ip][pipenum] = utrmsg;

    /* Check state ( Configured ) */
    if( usb_pstd_ChkConfigured(ptr) == USB_YES )
    {
        /* Data transfer */
        usb_pstd_SetReTransfer(ptr, pipenum);
    }
    else
    {
        /* Transfer stop */
        usb_cstd_ForcedTermination(ptr, pipenum, (uint16_t)USB_DATA_ERR);
    }
    return USB_DONE;
}

/******************************************************************************
Function Name   : usb_pstd_SetReTransfer
Description     : Start transmission/reception of data transfer based on the 
                : specified transfer direction.
Arguments       : USB_UTR_t *ptr    : USB system internal structure.
                : uint16_t pipe     : Pipe nr.
Return value    : none
******************************************************************************/
void usb_pstd_SetReTransfer(USB_UTR_t *ptr, uint16_t pipe)
{
    /* Data transfer */
    if( usb_cstd_GetPipeDir(ptr, pipe) == USB_DIR_P_OUT )
    {   /* Out transfer */
        usb_cstd_ReceiveStart(ptr, pipe);
    }
    else
    {
        /* In transfer */
        usb_cstd_SendStart(ptr, pipe);
    }
}

/******************************************************************************
Function Name   : usb_cstd_SendStart
Description     : Start data transmission using CPU/DMA transfer to USB host/
                : /device.
Arguments       : USB_UTR_t *ptr : USB internal structure. Selects e.g. channel.
                : uint16_t pipe  : Pipe no.
Return value    : none
******************************************************************************/
void usb_cstd_SendStart(USB_UTR_t *ptr, uint16_t pipe)
{
    USB_UTR_t       *pp;
    uint32_t        length;
    uint16_t        useport;

    /* Evacuation pointer */
    pp = usb_gcstd_Pipe[ptr->ip][pipe];
    length  = pp->tranlen;

    /* Check transfer count */
    if( pp->segment == USB_TRAN_CONT )
    {
        /* Sequence toggle */
        usb_cstd_DoSqtgl(ptr, pipe, pp->pipectr);
    }

    /* Select NAK */
    usb_cstd_SelectNak(ptr, pipe);
    /* Set data count */
    usb_gcstd_DataCnt[ptr->ip][pipe] = length;
    /* Set data pointer */
    usb_gcstd_DataPtr[ptr->ip][pipe] = (uint8_t*)pp->tranadr;

    /* BEMP Status Clear */
    usb_creg_clr_sts_bemp( ptr, pipe );
    /* BRDY Status Clear */
    usb_creg_clr_sts_brdy( ptr, pipe );

    /* Pipe number to FIFO port select */
    useport = usb_cstd_Pipe2Fport(ptr, pipe);
    /* Check use FIFO access */
    switch( useport )
    {
    /* CFIFO use */
    case USB_CUSE:
        /* Buffer to FIFO data write */
        usb_cstd_Buf2Fifo(ptr, pipe, useport);
        /* Set BUF */
        usb_cstd_SetBuf(ptr, pipe);
        break;
    /* D0FIFO use */
    case USB_D0USE:
        /* D0 FIFO access is NG */
        //SCI_printf("### USB-ITRON is not support(SND-D0USE:pipe%d)\n", pipe);
        usb_cstd_ForcedTermination(ptr, pipe, (uint16_t)USB_DATA_ERR);
        break;
    /* D1FIFO use */
    case USB_D1USE:
        /* Buffer to FIFO data write */
        usb_cstd_Buf2Fifo(ptr, pipe, useport);
        /* Set BUF */
        usb_cstd_SetBuf(ptr, pipe);
        break;

    /* D0FIFO DMA */
    case USB_D0DMA:
        /* Setting for use PIPE number */
        usb_gcstd_Dma0Pipe[ptr->ip] = pipe;
        /* PIPE direction */
        usb_gcstd_Dma0Dir[ptr->ip]  = usb_cstd_GetPipeDir(ptr, pipe);
        /* Buffer size */
        usb_gcstd_Dma0Fifo[ptr->ip] = usb_cstd_GetBufSize(ptr, pipe);
        /* Check data count */
        if( usb_gcstd_DataCnt[ptr->ip][usb_gcstd_Dma0Pipe[ptr->ip]] <= usb_gcstd_Dma0Fifo[ptr->ip] )
        {
            /* Transfer data size */
            usb_gcstd_Dma0Size[ptr->ip] = (uint16_t)usb_gcstd_DataCnt[ptr->ip][usb_gcstd_Dma0Pipe[ptr->ip]];
            /* Enable Empty Interrupt */
            usb_creg_set_bempenb(ptr, usb_gcstd_Dma0Pipe[ptr->ip]);
        }
        else
        {
            /* Data size == FIFO size */
            usb_gcstd_Dma0Size[ptr->ip] = usb_gcstd_Dma0Fifo[ptr->ip];
        }

        usb_cstd_Buf2fifoStartDma( ptr, pipe, useport );

        /* Set BUF */
        usb_cstd_SetBuf(ptr, pipe);
        break;
    /* D1FIFO DMA */
    case USB_D1DMA:
        /* D1 FIFO access is NG */
        //SCI_printf("### USB-ITRON is not support(SND-D1DMA:pipe%d)\n", pipe);
        usb_cstd_ForcedTermination(ptr, pipe, (uint16_t)USB_DATA_ERR);
        break;

    default:
        /* Access is NG */
        //SCI_printf("### USB-ITRON is not support(SND-else:pipe%d)\n", pipe);
        usb_cstd_ForcedTermination(ptr, pipe, (uint16_t)USB_DATA_ERR);
        break;
    }
}

/******************************************************************************
Function Name   : usb_cstd_Buf2fifoStartDma
Description     : Start transfer using DMA/DTC. If transfer size is 0, write 
                : more data to buffer.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t pipe   : Pipe nr.
                : uint16_t useport: FIFO select
Return value    : none
******************************************************************************/
void    usb_cstd_Buf2fifoStartDma( USB_UTR_t *ptr, uint16_t pipe, uint16_t useport )
{
    /* Transfer size check */
    if(usb_gcstd_Dma0Size[ptr->ip] != 0)
    {
        if(ptr->ip == USB_USBIP_0)
        {
            if((usb_gcstd_Dma0Size[ptr->ip] & 0x0001u) == 0u)
            {
                /* 16bit access */
                /* DMA access Buffer to FIFO start */
                usb_cpu_buf2d0fifo_start_dma(ptr, usb_cstd_GetD0fifo16Adr(ptr));
            }
            else
            {
                /* 8bit access */
                /* DMA access Buffer to FIFO start */
                usb_cpu_buf2d0fifo_start_dma(ptr, usb_cstd_GetD0fifo8Adr(ptr));
            }
        }
        else if(ptr->ip == USB_USBIP_1)
        {
            if((usb_gcstd_Dma0Size[ptr->ip] & 0x0001u) == 0u)
            {
                /* 16bit access */
                /* DMA access Buffer to FIFO start */
                usb_cpu_buf2d0fifo_start_dma(ptr, usb_cstd_GetD0fifo16Adr(ptr));
            }
            else
            {
                /* 8bit access */
                /* DMA access Buffer to FIFO start */
                usb_cpu_buf2d0fifo_start_dma(ptr, usb_cstd_GetD0fifo8Adr(ptr));
            }
        }

        /* Changes the FIFO port by the pipe. */
        usb_cstd_chg_curpipe(ptr, pipe, useport, USB_NO);
        /* Enable Not Ready Interrupt */
        usb_cstd_NrdyEnable(ptr, pipe);
        /* CPU access Buffer to FIFO start */
        usb_cstd_Buf2D0fifoStartUsb(ptr);
    }
    else
    {
        /* Buffer to FIFO data write */
        usb_cstd_Buf2Fifo(ptr, pipe, useport);
    }
}/* eof usb_cstd_Buf2fifoStartDma() */

/******************************************************************************
Function Name   : usb_cstd_Buf2D0fifoStartUsb
Description     : Setup to start DMA/DTC transfer from data buffer to D0FIFO.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
Return value    : none
******************************************************************************/
void usb_cstd_Buf2D0fifoStartUsb(USB_UTR_t *ptr)
{
    uint16_t    mbw;

    /* Write (MEMORY -> FIFO) : USB register set */
    if(ptr->ip == USB_USBIP_0)  /* USB0 */
    {
        if((usb_gcstd_Dma0Size[ptr->ip] & 0x0001u) == 0u)
        {
            mbw = USB_MBW_16;
        }
        else
        {
            mbw = USB_MBW_8;
        }
    }
    else if(ptr->ip == USB_USBIP_1) /* USBHS */
    {
        if((usb_gcstd_Dma0Size[ptr->ip] & 0x0001u) == 0u)
        {
            mbw = USB_MBW_16;
        }
        else
        {
            mbw = USB_MBW_8;
        }
    }

    /* Change MBW setting */
    usb_creg_set_mbw( ptr, USB_D0DMA, mbw );

    /* DTC(D0FIFO) interrupt enable */
    usb_cpu_d0fifo_enable_dma(ptr);

    /* Set DREQ enable */
    usb_creg_set_dreqe( ptr, USB_D0DMA );
}/* eof usb_cstd_Buf2D0fifoStartUsb() */

/******************************************************************************
Function Name   : usb_cstd_NrdyEnable
Description     : Enable NRDY interrupt of the specified pipe.
Arguments       : USB_UTR_t *ptr : USB internal structure. Selects e.g. channel.
                : uint16_t pipe  : Pipe number.
Return value    : none
******************************************************************************/
void usb_cstd_NrdyEnable(USB_UTR_t *ptr, uint16_t pipe)
{
    /* Check current function */
    if( usb_cstd_is_host_mode(ptr) == USB_NO )
    {
        /*  At the peripheral operation, interrupt is disabled, */
        /*  because handler becomes busy. */
    }
    else
    {
        /* Enable NRDY */
        usb_creg_set_nrdyenb( ptr, pipe );
    }
}

/******************************************************************************
Function Name   : usb_cstd_is_host_mode
Description     : Check current function
Arguments       : none
Return value    : uint16_t    : YES = Host
                :             : NO = Peripheral
******************************************************************************/
uint16_t usb_cstd_is_host_mode(USB_UTR_t *ptr)
{
    uint16_t    buf;
    buf = usb_creg_read_syscfg( ptr, USB_PORT0 );
    if( (buf & USB_DCFM) == USB_DCFM )
    {
        /* Host Function mode */
        return USB_YES;
    }
    else
    {
        /* Peripheral Function mode */
        return USB_NO;
    }
}

/******************************************************************************
Function Name   : usb_cstd_GetD0fifo16Adr
Description     : Get 16 bits of used channel's D0FIFO register content.
Arguments       : USB_UTR_t *ptr : USB system internal structure. Selects channel.
Return          : Address of D0FIFO
******************************************************************************/
uint32_t    usb_cstd_GetD0fifo16Adr( USB_UTR_t *ptr )
{
    if(ptr->ip == USB_USBIP_0)
    {
        return (uint32_t)(&ptr->ipp->D0FIFO.WORD);
    }
    else if(ptr->ip == USB_USBIP_1)
    {
        return (uint32_t)(&ptr->ipp->D0FIFO.WORD);
    }

    return 0;
}/* eof usb_cstd_GetD0fifo16Adr() */

/******************************************************************************
Function Name   : usb_cpu_buf2d0fifo_start_dma
Description     : Buffer to FIFO data write DMA start
Arguments       : USB_UTR_t *ptr        : USB internal structure. Selects USB channel. 
                : uint32_t DistAdr      : Destination address
Return value    : void
******************************************************************************/
void usb_cpu_buf2d0fifo_start_dma(USB_UTR_t *ptr, uint32_t DistAdr)
{
    uint16_t    size;
    uint32_t    tmp;
    dtc_activation_source_t    act_src;    /* activation source is Software Interrupt */


    /* DTC Transfer enable
    b0    DTCST    DTC module start bit
    b7-b1 Reserved 0
    */
    R_DTC_Control( DTC_CMD_DTC_START, NULL, 0 );

    /* DTC control register (Transfer Information Read No Skip)
    b2-b0 Reserved 0
    b3    Reserved 0
    b4    RRS      DTC Transfer Information Read Skip enable bit
    b7-b5 Reserved 0
    */
    R_DTC_Control( DTC_CMD_DATA_READ_SKIP_DISABLE, NULL, 0 );

    /* DTC mode register A (Block Transfer Set)
    b1-b0 Reserved 0
    b3-b2 SM       source address mode bit
    b5-b4 SZ       DTC data transfer size bit
    b7-b6 MD       DTC mode bit
    */
    usb_td_cfg[ptr->ip].transfer_mode = DTC_TRANSFER_MODE_BLOCK;

    if(ptr->ip == USB_USBIP_0)
    {
        act_src = DTCE_USB0_D0FIFO0;
        if( (usb_gcstd_Dma0Size[ptr->ip] & 0x0001) != 0 )
        {
            /* if count == odd */
            tmp = usb_gcstd_Dma0Size[ptr->ip];

            /* DTC mode register A (Byte Size)
            b1-b0 Reserved 0
            b3-b2 SM       source address mode bit
            b5-b4 SZ       DTC data transfer size bit
            b7-b6 MD       DTC mode bit
            */
            usb_td_cfg[ptr->ip].data_size = DTC_DATA_SIZE_BYTE;
        }
        else
        {
            tmp = usb_gcstd_Dma0Size[ptr->ip] / 2;

            /* DTC mode register A (Word Size)
            b1-b0 Reserved 0
            b3-b2 SM       source address mode bit
            b5-b4 SZ       DTC data transfer size bit
            b7-b6 MD       DTC mode bit
            */
            usb_td_cfg[ptr->ip].data_size = DTC_DATA_SIZE_WORD;
        }
    }

    /* DTC mode register A (Source Address Increment)
    b1-b0 Reserved 0
    b3-b2 SM       source address mode bit
    b5-b4 SZ       DTC data transfer size bit
    b7-b6 MD       DTC mode bit
    */
    usb_td_cfg[ptr->ip].src_addr_mode = DTC_SRC_ADDR_INCR;

    /* DTC mode register B (Chain Transfer disable)
    b1-b0 Reserved 0
    b3-b2 DM       Destination address mode bit
    b4    DTS      DTC transfer mode select bit
    b5    DISEL    DTC interrupt select bit
    b6    CHNS     DTC chain transfer select bit
    b7    CHNE     DTC chain transfer enable bit
    */
    usb_td_cfg[ptr->ip].chain_transfer_enable = DTC_CHAIN_TRANSFER_DISABLE;

    /* DTC mode register B (Select Data Transfer End Interrupt)
    b1-b0 Reserved 0
    b3-b2 DM       Destination address mode bit
    b4    DTS      DTC transfer mode select bit
    b5    DISEL    DTC interrupt select bit
    b6    CHNS     DTC chain transfer select bit
    b7    CHNE     DTC chain transfer enable bit
    */
    usb_td_cfg[ptr->ip].response_interrupt = DTC_INTERRUPT_AFTER_ALL_COMPLETE;

    /* DTC mode register B (Destination Side Block Area)
    b1-b0 Reserved 0
    b3-b2 DM       Destination address mode bit
    b4    DTS      DTC transfer mode select bit
    b5    DISEL    DTC interrupt select bit
    b6    CHNS     DTC chain transfer select bit
    b7    CHNE     DTC chain transfer enable bit
    */
    usb_td_cfg[ptr->ip].repeat_block_side = DTC_REPEAT_BLOCK_DESTINATION;

    /* DTC mode register B (Destination Address fixed)
    b1-b0 Reserved 0
    b3-b2 DM       Destination address mode bit
    b4    DTS      DTC transfer mode select bit
    b5    DISEL    DTC interrupt select bit
    b6    CHNS     DTC chain transfer select bit
    b7    CHNE     DTC chain transfer enable bit
    */
    usb_td_cfg[ptr->ip].dest_addr_mode = DTC_DES_ADDR_FIXED;

    /* DTC source address register (Table address)
    b31-b0 SAR Destination address
    */
    usb_td_cfg[ptr->ip].source_addr = (uint32_t)(usb_gcstd_DataPtr[ptr->ip][usb_gcstd_Dma0Pipe[ptr->ip]]);


    /* DTC source address register (FIFO port address)
    b31-b0 SAR Source address
    */
    usb_td_cfg[ptr->ip].dest_addr = (uint32_t)(DistAdr);

    size = (uint8_t )(tmp);

    /* DTC transfer count registerA
    b15-b0 CRA Transfer count
    */
    usb_td_cfg[ptr->ip].block_size = (uint16_t)(size);

    /* DTC transfer count registerB (Block count)
    b15-b0 CRB Transfer count
    */
    usb_td_cfg[ptr->ip].transfer_count =
        (uint16_t)(usb_gcstd_DataCnt[ptr->ip][usb_gcstd_Dma0Pipe[ptr->ip]] / usb_gcstd_Dma0Size[ptr->ip]);

    /* DTC address mode register (Full Address Mode)
    b0    SHORT    Short address mode bit
    b7-b1 Reserved 0
    */

    /* DTC control register (Transfer Information Read No Skip)
    b2-b0 Reserved 0
    b3    Reserved 0
    b4    RRS      DTC Transfer Information Read Skip enable bit
    b7-b5 Reserved 0
    */
    R_DTC_Control(DTC_CMD_DATA_READ_SKIP_ENABLE, NULL, 0);

    if( ptr->ip == USB_USBIP_0 )
    {
        /* Priority D0FIFO0=0
        b3-b0 IPR      Interrupt priority
        b7-b4 Reserved 0
        */
        IPR( USB0, D0FIFO0 ) = 0x00;

        /* Interrupt enable register (USB0 D0FIFO enable(IEN4))
        b0 IEN0 Interrupt enable bit
        b1 IEN1 Interrupt enable bit
        b2 IEN2 Interrupt enable bit
        b3 IEN3 Interrupt enable bit
        b4 IEN4 Interrupt enable bit
        b5 IEN5 Interrupt enable bit
        b6 IEN6 Interrupt enable bit
        b7 IEN7 Interrupt enable bit
        */
        IEN( USB0, D0FIFO0 ) = 0;
        R_DTC_Create( act_src, &usb_dtc_transfer_data[ptr->ip], &usb_td_cfg[ptr->ip], 0 );
        IEN( USB0, D0FIFO0 ) = 1;

        /* DTC start enable register (USB0 D0FIFO transfer)
        b0    DTCE     DTC start enable bit
        b7-b1 Reserved 0
        */
        DTCE( USB0, D0FIFO0 ) = 1;
    }
}

/******************************************************************************
Function Name   : usb_cstd_GetBufSize
Description     : Return buffer size, or max packet size, of specified pipe.
Arguments       : USB_UTR_t *ptr    : USB system internal structure. Selects channel.
                : uint16_t pipe     : Pipe number.
Return value    : uint16_t          : FIFO buffer size or max packet size.
******************************************************************************/
uint16_t usb_cstd_GetBufSize(USB_UTR_t *ptr, uint16_t pipe)
{
    uint16_t    size, buffer;

    if(ptr->ip == USB_USBIP_0)
    {
        if( pipe == USB_PIPE0 )
        {
            /* Not continuation transmit */
            buffer = usb_creg_read_dcpmaxp( ptr );
        }
        else
        {
            /* Pipe select */
            usb_creg_write_pipesel( ptr, pipe );
            buffer = usb_creg_read_pipemaxp( ptr );
        }
        /* Max Packet Size */
        size = (uint16_t)(buffer & USB_MXPS);
    }
    else
    {
        if( pipe == USB_PIPE0 )
        {
            buffer = usb_creg_read_dcpcfg( ptr );
            if( (buffer & USB_CNTMDFIELD) == USB_CNTMDFIELD )
            {
                /* Continuation transmit */
                /* Buffer Size */
                size = USB_PIPE0BUF;
            }
            else
            {
                /* Not continuation transmit */
                buffer = usb_creg_read_dcpmaxp( ptr );
                /* Max Packet Size */
                size = (uint16_t)(buffer & USB_MAXP);
            }
        }
        else
        {
            /* Pipe select */
            usb_creg_write_pipesel( ptr, pipe );
            
            /* Read CNTMD */
            buffer = usb_creg_read_pipecfg( ptr );
            if( (buffer & USB_CNTMDFIELD) == USB_CNTMDFIELD )
            {
                buffer = usb_creg_read_pipebuf( ptr );
                /* Buffer Size */
                size = (uint16_t)((uint16_t)((buffer >> USB_BUFSIZE_BIT) + 1) * USB_PIPEXBUF);
            }
            else
            {
                buffer = usb_creg_read_pipemaxp( ptr );
                /* Max Packet Size */
                size = (uint16_t)(buffer & USB_MXPS);
            }
        }
    }
    return size;
}/* eof usb_cstd_GetBufSize() */

/******************************************************************************
Function Name   : usb_cstd_SetBuf
Description     : Set PID (packet ID) of the specified pipe to BUF.
Arguments       : USB_UTR_t *ptr : USB internal structure. Selects e.g. channel.
                : uint16_t pipe  : Pipe number.
Return value    : none
******************************************************************************/
void usb_cstd_SetBuf(USB_UTR_t *ptr, uint16_t pipe)
{
    /* PIPE control reg set */
    usb_creg_set_pid( ptr, pipe, USB_PID_BUF );
}

/******************************************************************************
Function Name   : usb_cstd_Buf2Fifo
Description     : Set USB registers as required to write from data buffer to USB 
                : FIFO, to have USB FIFO to write data to bus.
Arguments       : USB_UTR_t *ptr : USB internal structure. Selects e.g. channel.
                : uint16_t pipe     : Pipe no.
                : uint16_t useport  : Port no.
Return value    : none
******************************************************************************/
void usb_cstd_Buf2Fifo(USB_UTR_t *ptr, uint16_t pipe, uint16_t useport)
{
    uint16_t    end_flag;

    /* Disable Ready Interrupt */
    usb_creg_clr_brdyenb(ptr, pipe);

    end_flag = usb_cstd_write_data( ptr, pipe, useport );

    /* Check FIFO access sequence */
    switch( end_flag )
    {
    case USB_WRITING:
        /* Continue of data write */
        /* Enable Ready Interrupt */
        usb_creg_set_brdyenb(ptr, pipe);
        /* Enable Not Ready Interrupt */
        usb_cstd_NrdyEnable(ptr, pipe);
        break;
    case USB_WRITEEND:
        /* End of data write */
        /* continue */
    case USB_WRITESHRT:
        /* End of data write */
        /* Enable Empty Interrupt */
        usb_creg_set_bempenb(ptr, pipe);
        /* Enable Not Ready Interrupt */
        usb_cstd_NrdyEnable(ptr, pipe);
        break;
    case USB_FIFOERROR:
        /* FIFO access error */
        //SCI_printf("### FIFO access error \n");
        usb_cstd_ForcedTermination(ptr, pipe, (uint16_t)USB_DATA_ERR);
        break;
    default:
        usb_cstd_ForcedTermination(ptr, pipe, (uint16_t)USB_DATA_ERR);
        break;
    }
}

/******************************************************************************
Function Name   : usb_cstd_write_data
Description     : Switch PIPE, request the USB FIFO to write data, and manage 
                : the size of written data.
Arguments       : USB_UTR_t *ptr : USB internal structure. Selects e.g. channel.
                : uint16_t pipe         : Pipe no.
                : uint16_t pipemode     : CUSE/D0DMA/D1DMA
Return value    : uint16_t end_flag
******************************************************************************/
uint16_t usb_cstd_write_data(USB_UTR_t *ptr, uint16_t pipe, uint16_t pipemode )
{
    uint16_t    size, count, buffer, mxps;
    uint16_t    end_flag;

    /* Changes FIFO port by the pipe. */
    if( (pipemode == USB_CUSE) && (pipe == USB_PIPE0) )
    {
        buffer = usb_cstd_is_set_frdy(ptr, pipe, (uint16_t)USB_CUSE, (uint16_t)USB_ISEL);
    }
    else
    {
        buffer = usb_cstd_is_set_frdy(ptr, pipe, (uint16_t)pipemode, USB_NO);
    }

    /* Check error */
    if( buffer == USB_FIFOERROR )
    {
        /* FIFO access error */
        return (USB_FIFOERROR);
    }
    /* Data buffer size */
    size = usb_cstd_GetBufSize(ptr, pipe);
    /* Max Packet Size */
    mxps = usb_cstd_GetMaxPacketSize(ptr, pipe);

    /* Data size check */
    if( usb_gcstd_DataCnt[ptr->ip][pipe] <= (uint32_t)size )
    {
        count = (uint16_t)usb_gcstd_DataCnt[ptr->ip][pipe];
        /* Data count check */
        if( count == 0 )
        {
            /* Null Packet is end of write */
            end_flag = USB_WRITESHRT;
        }
        else if( (count % mxps) != 0 )
        {
            /* Short Packet is end of write */
            end_flag = USB_WRITESHRT;
        }
        else
        {
            if( pipe == USB_PIPE0 )
            {
                /* Just Send Size */
                end_flag = USB_WRITING;
            }
            else
            {
                /* Write continues */
                end_flag = USB_WRITEEND;
            }
        }
    }
    else
    {
        /* Write continues */
        end_flag = USB_WRITING;
        count = size;
    }

    usb_gcstd_DataPtr[ptr->ip][pipe] = usb_cstd_write_fifo( ptr, count, pipemode, usb_gcstd_DataPtr[ptr->ip][pipe] );

    /* Check data count to remain */
    if( usb_gcstd_DataCnt[ptr->ip][pipe] < (uint32_t)size )
    {
        /* Clear data count */
        usb_gcstd_DataCnt[ptr->ip][pipe] = (uint32_t)0u;
        /* Read CFIFOCTR */
        buffer = usb_creg_read_fifoctr( ptr, pipemode );
        /* Check BVAL */
        if( (buffer & USB_BVAL) == 0u )
        {
            /* Short Packet */
            usb_creg_set_bval( ptr, pipemode );
        }
    }
    else
    {
        /* Total data count - count */
        usb_gcstd_DataCnt[ptr->ip][pipe] -= count;
    }
    /* End or Err or Continue */
    return end_flag;
}

/******************************************************************************
Function Name   : usb_cstd_write_fifo
Description     : Write specified amount of data to specified USB FIFO. 
Arguments       : USB_UTR_t *ptr        : USB system internal structure. Selects channel.
                : uint16_t  count       : Write size.
                : uint16_t  pipemode    : The mode of CPU/DMA(D0)/DMA(D1).
                : uint16_t  *write_p    : Address of buffer of data to write.
Return value    : The incremented address of last argument (write_p).
******************************************************************************/
uint8_t *usb_cstd_write_fifo( USB_UTR_t *ptr, uint16_t count, uint16_t pipemode, uint8_t *write_p )
{
    uint16_t    even;

    for( even = (uint16_t)(count >> 1); (even != 0); --even )
    {
        /* 16bit access */
        usb_creg_write_fifo16( ptr, pipemode, *((uint16_t *)write_p) );

        /* Renewal write pointer */
        write_p += sizeof(uint16_t);
    }

    if( (count & (uint16_t)0x0001u) != 0u )
    {
        /* 8bit access */
        /* count == odd */
        /* Change FIFO access width */
        usb_creg_set_mbw( ptr, pipemode, USB_MBW_8 );

        /* FIFO write */
        usb_creg_write_fifo8( ptr, pipemode, *write_p );

        /* Return FIFO access width */
        usb_creg_set_mbw( ptr, pipemode, USB_MBW_16 );

        /* Renewal write pointer */
        write_p++;
    }

    return write_p;

}/* eof usb_cstd_write_fifo() */

/******************************************************************************
Function Name   : usb_cstd_GetMaxPacketSize
Description     : Fetch MaxPacketSize of the specified pipe.
Arguments       : USB_UTR_t *ptr : USB internal structure. Selects e.g. channel.
                : uint16_t pipe  : Pipe number.
Return value    : uint16_t MaxPacketSize
******************************************************************************/
uint16_t usb_cstd_GetMaxPacketSize(USB_UTR_t *ptr, uint16_t pipe)
{
    uint16_t    size, buffer;

    if( pipe == USB_PIPE0 )
    {
        buffer = usb_creg_read_dcpmaxp( ptr );
    }
    else
    {
        /* Pipe select */
        usb_creg_write_pipesel( ptr, pipe );
        buffer = usb_creg_read_pipemaxp( ptr );
    }
    /* Max Packet Size */
    size = (uint16_t)(buffer & USB_MXPS);

    return size;
}

/******************************************************************************
Function Name   : usb_cstd_Pipe2Fport
Description     : Get port No. from the specified pipe No. by argument
Arguments       : USB_UTR_t *ptr : USB internal structure. Selects e.g. channel.
                : uint16_t pipe  : Pipe number.
Return value    : uint16_t       : FIFO port selector.
******************************************************************************/
uint16_t usb_cstd_Pipe2Fport(USB_UTR_t *ptr, uint16_t pipe)
{
    uint16_t        i, *table;

    /* Check current function */
    if( usb_cstd_is_host_mode(ptr) == USB_NO )
    {
        uint16_t    conf;

        conf = usb_gpstd_ConfigNum;
        if( conf < (uint16_t)1 )
        {
            /* Address state */
            conf = (uint16_t)1;
        }
        /* Peripheral */
        /* Get FIFO port from PIPE number */
        table = (uint16_t*)((uint16_t**)
            (usb_gpstd_Driver.pipetbl[conf - 1]));
        /* EP table loop */
        for( i = 0; table[i] != USB_PDTBLEND; i += USB_EPL )
        {
            if( table[i] == pipe )
            {
                return table[i + 5];
            }
        }
    }
    else
    {
    }

    return USB_ERROR;
}

/******************************************************************************
Function Name   : void usb_cstd_SelectNak(uint16_t pipe)
Description     : Set the specified pipe PID to send a NAK if the transfer type 
                : is BULK/INT. 
Arguments       : uint16_t pipe     : Pipe number.
Return value    : none
******************************************************************************/
void usb_cstd_SelectNak(USB_UTR_t *ptr, uint16_t pipe)
{
    /* Check PIPE TYPE */
    if( usb_cstd_GetPipeType(ptr, pipe) != USB_ISO )
    {
        usb_cstd_SetNak(ptr, pipe);
    }
}

/******************************************************************************
Function Name   : usb_cstd_DoSqtgl
Description     : Toggle setting of the toggle-bit for the specified pipe by 
                : argument.
Arguments       : USB_UTR_t *ptr : USB internal structure. Selects e.g. channel.
                : uint16_t pipe     : Pipe number.
                : uint16_t toggle   : Current toggle status.
Return value    : none
******************************************************************************/
void usb_cstd_DoSqtgl(USB_UTR_t *ptr, uint16_t pipe, uint16_t toggle)
{
    /* Check toggle */
    if( (toggle & USB_SQMON) == USB_SQMON )
    {
        /* Do pipe SQSET */
        usb_creg_set_sqset(ptr, pipe);
    }
    else
    {
        /* Do pipe SQCLR */
        usb_creg_set_sqclr(ptr, pipe);
    }
}

/******************************************************************************
Function Name   : usb_cstd_ReceiveStart
Description     : Start data reception using CPU/DMA transfer to USB Host/USB
                : device.
Arguments       : USB_UTR_t *ptr : USB internal structure. Selects e.g. channel.
                : uint16_t pipe  : Pipe no.
Return value    : none
******************************************************************************/
void usb_cstd_ReceiveStart(USB_UTR_t *ptr, uint16_t pipe)
{
    USB_UTR_t       *pp;
    uint32_t        length;
    uint16_t        mxps, useport;


    /* Evacuation pointer */
    pp      = usb_gcstd_Pipe[ptr->ip][pipe];
    length  = pp->tranlen;

    /* Check transfer count */
    if( pp->segment == USB_TRAN_CONT )
    {
        /* Sequence toggle */
        usb_cstd_DoSqtgl(ptr, pipe, pp->pipectr);
    }

    /* Select NAK */
    usb_cstd_SelectNak(ptr, pipe);
    /* Set data count */
    usb_gcstd_DataCnt[ptr->ip][pipe] = length;
    /* Set data pointer */
    usb_gcstd_DataPtr[ptr->ip][pipe] = (uint8_t*)pp->tranadr;

    /* Pipe number to FIFO port select */
    useport = usb_cstd_Pipe2Fport(ptr, pipe);

    /* Check use FIFO access */
    switch( useport )
    {
    /* D0FIFO use */
    case USB_D0USE:
        /* D0 FIFO access is NG */
        //SCI_printf("### USB-ITRON is not support(RCV-D0USE:pipe%d)\n", pipe);
        usb_cstd_ForcedTermination(ptr, pipe, (uint16_t)USB_DATA_ERR);
        break;
        
    /* CFIFO use */
    case USB_CUSE:
        /* continue */
        
    /* D1FIFO use */
    case USB_D1USE:
        /* Changes the FIFO port by the pipe. */
        usb_cstd_chg_curpipe(ptr, pipe, useport, USB_NO);
        /* Max Packet Size */
        mxps = usb_cstd_GetMaxPacketSize(ptr, pipe);
        if( length != (uint32_t)0u )
        {
            /* Data length check */
            if( (length % mxps) == (uint32_t)0u )
            {
                /* Set Transaction counter */
                usb_cstd_SetTransactionCounter(ptr, pipe, (uint16_t)(length / mxps));
            }
            else
            {
                /* Set Transaction counter */
                usb_cstd_SetTransactionCounter(ptr, pipe, (uint16_t)((length / mxps) + (uint32_t)1u));
            }
        }
        /* Set BUF */
        usb_cstd_SetBuf(ptr, pipe);
        /* Enable Ready Interrupt */
        usb_creg_set_brdyenb(ptr, pipe);
        /* Enable Not Ready Interrupt */
        usb_cstd_NrdyEnable(ptr, pipe);
        break;
        
    /* D0FIFO DMA */
    case USB_D0DMA:
        /* Setting for use PIPE number */
        usb_gcstd_Dma0Pipe[ptr->ip] = pipe;
        /* PIPE direction */
        usb_gcstd_Dma0Dir[ptr->ip]  = usb_cstd_GetPipeDir(ptr, pipe);
        /* Buffer size */
        usb_gcstd_Dma0Fifo[ptr->ip] = usb_cstd_GetBufSize(ptr, pipe);
        /* Check data count */
        if( usb_gcstd_DataCnt[ptr->ip][usb_gcstd_Dma0Pipe[ptr->ip]] < usb_gcstd_Dma0Fifo[ptr->ip] )
        {
            /* Transfer data size */
            usb_gcstd_Dma0Size[ptr->ip] = (uint16_t)usb_gcstd_DataCnt[ptr->ip][usb_gcstd_Dma0Pipe[ptr->ip]];
        }
        else
        {
            /* Data size == FIFO size */
            usb_gcstd_Dma0Size[ptr->ip] = usb_gcstd_Dma0Fifo[ptr->ip];
        }

        usb_cstd_Fifo2BufStartDma( ptr, pipe, useport, length );

        break;
        
    /* D1FIFO DMA */
    case USB_D1DMA:
        /* D1 FIFO access is NG */
        //SCI_printf("### USB-ITRON is not support(RCV-D1DMA:pipe%d)\n", pipe);
        usb_cstd_ForcedTermination(ptr, pipe, (uint16_t)USB_DATA_ERR);
        break;

    default:
        //SCI_printf("### USB-ITRON is not support(RCV-else:pipe%d)\n", pipe);
        usb_cstd_ForcedTermination(ptr, pipe, (uint16_t)USB_DATA_ERR);
        break;
    }
}

/******************************************************************************
Function Name   : usb_cstd_Fifo2BufStartDma
Description     : Start transfer using DMA/DTC. If transfer size is 0, clear DMA. 
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t pipe   : Pipe nr.
                : uint16_t useport: FIFO select
                : uint32_t length
Return value    : none
******************************************************************************/
void    usb_cstd_Fifo2BufStartDma( USB_UTR_t *ptr, uint16_t pipe, uint16_t useport, uint32_t length )
{
    uint16_t        mxps;

    /* Data size check */
    if( usb_gcstd_Dma0Size[ptr->ip] != 0u )
    {
        if(ptr->ip == USB_USBIP_0)
        {
            if((usb_gcstd_Dma0Size[ptr->ip] & 0x0001u) == 0u)
            {
                /* 16bit access */
                /* DMA access Buffer to FIFO start */
                usb_cpu_d0fifo2buf_start_dma(ptr, usb_cstd_GetD0fifo16Adr(ptr));
            }
            else
            {
                /* 8bit access */
                /* DMA access Buffer to FIFO start */
                usb_cpu_d0fifo2buf_start_dma(ptr, usb_cstd_GetD0fifo8Adr(ptr));
            }
        }
        else if(ptr->ip == USB_USBIP_1)
        {
            if((usb_gcstd_Dma0Size[ptr->ip] & 0x0001u) == 0u)
            {
                /* 16bit access */
                /* DMA access Buffer to FIFO start */
                usb_cpu_d0fifo2buf_start_dma(ptr, usb_cstd_GetD0fifo16Adr(ptr));
            }
            else
            {
                /* 8bit access */
                /* DMA access Buffer to FIFO start */
                usb_cpu_d0fifo2buf_start_dma(ptr, usb_cstd_GetD0fifo8Adr(ptr));
            }

        }

        /* Changes the FIFO port by the pipe. */
        usb_cstd_chg_curpipe(ptr, pipe, useport, USB_NO);
        /* Max Packet Size */
        mxps = usb_cstd_GetMaxPacketSize(ptr, pipe);
        if( length != (uint32_t)0u )
        {
            /* Data length check */
            if( (length % mxps) == (uint32_t)0u )
            {
                /* Set Transaction counter */
                usb_cstd_SetTransactionCounter(ptr, pipe, (uint16_t)(length / mxps));
            }
            else
            {
                /* Set Transaction counter */
                usb_cstd_SetTransactionCounter(ptr, pipe, (uint16_t)((length / mxps) + (uint32_t)1u));
            }
        }
        /* Set BUF */
        usb_cstd_SetBuf(ptr, pipe);
        /* Enable Ready Interrupt */
        usb_creg_set_brdyenb(ptr, pipe);
        /* Enable Not Ready Interrupt */
        usb_cstd_NrdyEnable(ptr, pipe);
        usb_cstd_D0fifo2BufStartUsb(ptr);
    }
    else
    {
        /* Changes the FIFO port by the pipe. */
        usb_cstd_chg_curpipe(ptr, pipe, useport, USB_NO);
        /* DMA buffer clear mode set */
        usb_creg_set_dclrm( ptr, USB_D0DMA );
        /* Set BUF */
        usb_cstd_SetBuf(ptr, pipe);
        /* Enable Ready Interrupt */
        usb_creg_set_brdyenb(ptr, pipe);
        /* Enable Not Ready Interrupt */
        usb_cstd_NrdyEnable(ptr, pipe);
    }
} /* eof usb_cstd_Fifo2BufStartDma() */

/******************************************************************************
Function Name   : usb_cstd_D0fifo2BufStartUsb
Description     : Setup to start DMA/DTC transfer D0FIFO to buffer.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
Return value    : none
******************************************************************************/
void usb_cstd_D0fifo2BufStartUsb(USB_UTR_t *ptr)
{
    /* Read (FIFO -> MEMORY) : USB register set */
    /* DMA buffer clear mode & MBW set */
    if(ptr->ip == USB_USBIP_0)  /* USB0 */
    {
        usb_creg_set_mbw( ptr, USB_D0DMA, (uint16_t)(USB_MBW_16) );
    }
    else if(ptr->ip == USB_USBIP_1) /* USBHS */
    {

        usb_creg_set_mbw( ptr, USB_D0DMA, (uint16_t)(USB_MBW_16) );
    }
    usb_creg_clr_dclrm( ptr, USB_D0DMA );

    /* Set DREQ enable */
    usb_creg_set_dreqe( ptr, USB_D0DMA );
}/* eof usb_cstd_D0fifo2BufStartUsb */

/******************************************************************************
Function Name   : usb_cpu_d0fifo2buf_start_dma
Description     : FIFO to Buffer data read DMA start
Arguments       : USB_UTR_t *ptr        : USB internal structure. Selects USB channel. 
                : uint32_t SourceAddr   : Source address
Return value    : void
******************************************************************************/
void usb_cpu_d0fifo2buf_start_dma(USB_UTR_t *ptr, uint32_t SourceAddr)
{
    uint16_t    size;
    uint32_t    tmp;
    dtc_activation_source_t    act_src;    /* activation source is Software Interrupt */


    /* DTC Transfer enable
    b0    DTCST    DTC module start bit
    b7-b1 Reserved 0
    */
    R_DTC_Control(DTC_CMD_DTC_START, NULL, 0);

    /* DTC control register (Transfer Information Read No Skip)
    b2-b0 Reserved 0
    b3    Reserved 0
    b4    RRS      DTC Transfer Information Read Skip enable bit
    b7-b5 Reserved 0
    */
    R_DTC_Control(DTC_CMD_DATA_READ_SKIP_DISABLE, NULL, 0);

    /* DTC mode register A (Block Transfer Set)
    b1-b0 Reserved 0
    b3-b2 SM       source address mode bit
    b5-b4 SZ       DTC data transfer size bit
    b7-b6 MD       DTC mode bit
    */
    usb_td_cfg[ptr->ip].transfer_mode = DTC_TRANSFER_MODE_BLOCK;

    if(ptr->ip == USB_USBIP_0)
    {
        act_src = DTCE_USB0_D0FIFO0;
        tmp = ((usb_gcstd_Dma0Fifo[ptr->ip] - 1) / 2) + 1;

        /* DTC mode register A (Word Size)
        b1-b0 Reserved 0
        b3-b2 SM       source address mode bit
        b5-b4 SZ       DTC data transfer size bit
        b7-b6 MD       DTC mode bit
        */
        usb_td_cfg[ptr->ip].data_size = DTC_DATA_SIZE_WORD;
    }

    /* DTC mode register A (Source Address fixed)
    b1-b0 Reserved 0
    b3-b2 SM       source address mode bit
    b5-b4 SZ       DTC data transfer size bit
    b7-b6 MD       DTC mode bit
    */
    usb_td_cfg[ptr->ip].src_addr_mode = DTC_SRC_ADDR_FIXED;

    /* DTC mode register B (Chain Transfer disable)
    b1-b0 Reserved 0
    b3-b2 DM       Destination address mode bit
    b4    DTS      DTC transfer mode select bit
    b5    DISEL    DTC interrupt select bit
    b6    CHNS     DTC chain transfer select bit
    b7    CHNE     DTC chain transfer enable bit
    */
    usb_td_cfg[ptr->ip].chain_transfer_enable = DTC_CHAIN_TRANSFER_DISABLE;

    /* DTC mode register B (Select Data Transfer End Interrupt)
    b1-b0 Reserved 0
    b3-b2 DM       Destination address mode bit
    b4    DTS      DTC transfer mode select bit
    b5    DISEL    DTC interrupt select bit
    b6    CHNS     DTC chain transfer select bit
    b7    CHNE     DTC chain transfer enable bit
    */
    usb_td_cfg[ptr->ip].response_interrupt = DTC_INTERRUPT_AFTER_ALL_COMPLETE;

    /* DTC mode register B (Source Side Block Area)
    b1-b0 Reserved 0
    b3-b2 DM       Destination address mode bit
    b4    DTS      DTC transfer mode select bit
    b5    DISEL    DTC interrupt select bit
    b6    CHNS     DTC chain transfer select bit
    b7    CHNE     DTC chain transfer enable bit
    */
    usb_td_cfg[ptr->ip].repeat_block_side = DTC_REPEAT_BLOCK_SOURCE;

    /* DTC mode register B (Destination Address Increment)
    b1-b0 Reserved 0
    b3-b2 DM       Destination address mode bit
    b4    DTS      DTC transfer mode select bit
    b5    DISEL    DTC interrupt select bit
    b6    CHNS     DTC chain transfer select bit
    b7    CHNE     DTC chain transfer enable bit
    */
    usb_td_cfg[ptr->ip].dest_addr_mode = DTC_DES_ADDR_INCR;

    /* DTC source address register (FIFO port address)
    b31-b0 SAR Destination address
    */
    usb_td_cfg[ptr->ip].source_addr = SourceAddr;

    /* DTC source address register (Table address)
    b31-b0 SAR Source address
    */
    usb_td_cfg[ptr->ip].dest_addr = (uint32_t)(usb_gcstd_DataPtr[ptr->ip][usb_gcstd_Dma0Pipe[ptr->ip]]);

    size = (uint8_t)(tmp);

    /* DTC transfer count registerA
    b15-b0 CRA Transfer count
    */
    usb_td_cfg[ptr->ip].block_size = (uint16_t)(size);

    /* DTC transfer count registerB (Block count)
    b15-b0 CRB Transfer count
    */
    usb_td_cfg[ptr->ip].transfer_count =
        (uint16_t)((usb_gcstd_DataCnt[ptr->ip][usb_gcstd_Dma0Pipe[ptr->ip]] -1) / usb_gcstd_Dma0Fifo[ptr->ip]) +1;

    /* DTC address mode register (Full Address Mode)
    b0    SHORT    Short address mode bit
    b7-b1 Reserved 0
    */

    /* DTC control register (Transfer Information Read No Skip)
    b2-b0 Reserved 0
    b3    Reserved 0
    b4    RRS      DTC Transfer Information Read Skip enable bit
    b7-b5 Reserved 0
    */
    R_DTC_Control(DTC_CMD_DATA_READ_SKIP_ENABLE, NULL, 0);

    if( ptr->ip == USB_USBIP_0 )
    {
        /* Priority D0FIFO0=0
        b3-b0 IPR      Interrupt priority
        b7-b4 Reserved 0
        */
        IPR( USB0, D0FIFO0 ) = 0x00;

        /* Interrupt enable register (USB0 D0FIFO enable(IEN4))
        b0 IEN0 Interrupt enable bit
        b1 IEN1 Interrupt enable bit
        b2 IEN2 Interrupt enable bit
        b3 IEN3 Interrupt enable bit
        b4 IEN4 Interrupt enable bit
        b5 IEN5 Interrupt enable bit
        b6 IEN6 Interrupt enable bit
        b7 IEN7 Interrupt enable bit
        */
        IEN( USB0, D0FIFO0 ) = 0;
        R_DTC_Create( act_src, &usb_dtc_transfer_data[ptr->ip], &usb_td_cfg[ptr->ip], 0 );
        IEN( USB0, D0FIFO0 ) = 1;

        /* DTC start enable register (USB0 D0FIFO transfer)
        b0    DTCE     DTC start enable bit
        b7-b1 Reserved 0
        */
        DTCE( USB0, D0FIFO0 ) = 1;
    }
}

/******************************************************************************
Function Name   : usb_cstd_GetPipeDir
Description     : Get PIPE DIR
Arguments       : uint16_t pipe  : Pipe number.
Return value    : uint16_t Pipe direction.
******************************************************************************/
uint16_t usb_cstd_GetPipeDir(USB_UTR_t *ptr, uint16_t pipe)
{
    uint16_t        buffer;

    /* Pipe select */
    usb_creg_write_pipesel( ptr, pipe );
    /* Read Pipe direction */
    buffer = usb_creg_read_pipecfg( ptr );
    return (uint16_t)(buffer & USB_DIRFIELD);
}

/******************************************************************************
Function Name   : usb_cstd_InterruptClock
Description     : Not processed as the functionality is provided by R8A66597(ASSP).
Arguments       : USB_UTR_t *ptr    : Not used
Return value    : none
******************************************************************************/
void usb_cstd_InterruptClock(USB_UTR_t *ptr)
{
}/* eof usb_cstd_InterruptClock() */

/******************************************************************************
Function Name   : usb_pstd_Interrupt
Description     : Analyze the USB Peripheral interrupt event and execute the
                : appropriate process.
Arguments       : USB_UTR_t *p    : USB system internal structure.
Return value    : none
******************************************************************************/
void usb_pstd_Interrupt(USB_UTR_t *ptr)
{
    uint16_t    intsts, status, stginfo;

    intsts = ptr->keyword;
    status = ptr->status;

    usb_gpstd_intsts0 = usb_creg_read_intsts( ptr );

    /* check interrupt status */
    switch( intsts )
    {

    /* BRDY, BEMP, NRDY */
    case USB_INT_BRDY:
        usb_pstd_BrdyPipe(ptr, status);
        break;
    case USB_INT_BEMP:
        usb_pstd_BempPipe(ptr, status);
        break;
    case USB_INT_NRDY:
        usb_pstd_NrdyPipe(ptr, status);
        break;
    /* Resume */
    case USB_INT_RESM:
        //SCI_printf("RESUME int peri\n");
        /* Callback */
        (*usb_gpstd_Driver.devresume)(ptr, (uint16_t)USB_NO_ARG, (uint16_t)USB_NO_ARG);
        usb_pstd_ResumeProcess(ptr);
        break;
    /* VBUS */
    case USB_INT_VBINT:
        usb_creg_set_cnen( ptr );
        if( usb_pstd_ChkVbsts(ptr) == USB_ATTACH )
        {
            //SCI_printf("VBUS int attach\n");
            /* USB attach */
            usb_pstd_AttachProcess(ptr);
        }
        else
        {
            //SCI_printf("VBUS int detach\n");
            /* USB detach */
            usb_pstd_DetachProcess(ptr);
        }
        break;
    /* SOF */
    case USB_INT_SOFR:
        /* User program */
        break;

    /* DVST */
    case USB_INT_DVST:
        switch( (uint16_t)(status & USB_DVSQ) )
        {
        /* Power state  */
        case USB_DS_POWR:
            break;
        /* Default state  */
        case USB_DS_DFLT:
            //SCI_printf("USB-reset int peri\n");
            usb_pstd_BusReset(ptr);
            break;
        /* Address state  */
        case USB_DS_ADDS:
            break;
        /* Configured state  */
        case USB_DS_CNFG:
            //SCI_printf("Device configuration int peri\n");
            break;
        /* Power suspend state */
        case USB_DS_SPD_POWR:
            /* Continue */
        /* Default suspend state */
        case USB_DS_SPD_DFLT:
            /* Continue */
        /* Address suspend state */
        case USB_DS_SPD_ADDR:
            /* Continue */
        /* Configured Suspend state */
        case USB_DS_SPD_CNFG:
            //SCI_printf("SUSPEND int peri\n");
            usb_pstd_SuspendProcess(ptr);
            break;
        /* Error */
        default:
            break;
        }
        break;

    /* CTRT */
    case USB_INT_CTRT:
        stginfo = (uint16_t)(status & USB_CTSQ);
        if( (stginfo == USB_CS_IDST) )
        {
        }
        else
        {
            if( ((stginfo == USB_CS_RDDS) || (stginfo == USB_CS_WRDS)) || (stginfo == USB_CS_WRND) )
            {
                /* Save request register */
                usb_pstd_SaveRequest(ptr);
            }
        }

        if( usb_gpstd_ReqTypeType == USB_STANDARD )
        {
                /* Switch on the control transfer stage (CTSQ). */
            switch( stginfo )
            {
            /* Idle or setup stage */
            case USB_CS_IDST:
                usb_pstd_StandReq0(ptr);
                break;
            /* Control read data stage */
            case USB_CS_RDDS:
                usb_pstd_StandReq1(ptr);
                break;
            /* Control write data stage */
            case USB_CS_WRDS:
                usb_pstd_StandReq2(ptr);
                break;
                    /* Status stage of a control write where there is no data stage. */
            case USB_CS_WRND:
                usb_pstd_StandReq3(ptr);
                break;
            /* Control read status stage */
            case USB_CS_RDSS:
                usb_pstd_StandReq4(ptr);
                break;
            /* Control write status stage */
            case USB_CS_WRSS:
                usb_pstd_StandReq5(ptr);
                break;
            /* Control sequence error */
            case USB_CS_SQER:
                usb_pstd_ControlEnd(ptr, (uint16_t)USB_DATA_ERR);
                break;
            /* Illegal */
            default:
                usb_pstd_ControlEnd(ptr, (uint16_t)USB_DATA_ERR);
                break;
            }
        }
        else
        {
            /* Vender Specific */
            usb_gpstd_ReqReg.ReqType        = usb_gpstd_ReqType;
            usb_gpstd_ReqReg.ReqTypeType    = usb_gpstd_ReqTypeType;
            usb_gpstd_ReqReg.ReqTypeRecip   = usb_gpstd_ReqTypeRecip;
            usb_gpstd_ReqReg.ReqRequest     = usb_gpstd_ReqRequest;
            usb_gpstd_ReqReg.ReqValue       = usb_gpstd_ReqValue;
            usb_gpstd_ReqReg.ReqIndex       = usb_gpstd_ReqIndex;
            usb_gpstd_ReqReg.ReqLength      = usb_gpstd_ReqLength;
            /* Callback */
            (*usb_gpstd_Driver.ctrltrans)(ptr, (USB_REQUEST_t *)&usb_gpstd_ReqReg, stginfo);
        }
        break;

    /* Error */
    case USB_INT_UNKNOWN:
        //SCI_printf("pINT_UNKNOWN\n");
        break;
    default:
        //SCI_printf("pINT_default %X\n", intsts);
        break;
    }
}

/******************************************************************************
Function Name   : usb_pstd_ControlEnd
Description     : End control transfer
Arguments       : USB_UTR_t *ptr    : USB system internal structure.
                : uint16_t status   : Transfer end status
Return value    : none
******************************************************************************/
void usb_pstd_ControlEnd(USB_UTR_t *ptr, uint16_t status)
{
    /* Interrupt disable */
    /* BEMP0 disable */
    usb_creg_clr_bempenb(ptr, (uint16_t)USB_PIPE0);
    /* BRDY0 disable */
    usb_creg_clr_brdyenb(ptr, (uint16_t)USB_PIPE0);
    /* NRDY0 disable */
    usb_creg_clr_nrdyenb(ptr, (uint16_t)USB_PIPE0);

    if(ptr -> ip == USB_USBIP_0)
    {
        usb_creg_set_mbw( ptr, USB_CUSE, USB0_CFIFO_MBW );
    }
    else if (ptr -> ip == USB_USBIP_1)
    {
        usb_creg_set_mbw( ptr, USB_CUSE, USB1_CFIFO_MBW );
    }

    if( (status == USB_DATA_ERR) || (status == USB_DATA_OVR) )
    {
        /* Request error */
        usb_pstd_SetStallPipe0( ptr );
    }
    else if( status == USB_DATA_STOP )
    {
        /* Pipe stop */
        usb_cstd_SetNak(ptr, (uint16_t)USB_PIPE0);
    }
    else
    {
        /* Set CCPL bit */
        usb_preg_set_ccpl( ptr );
    }
}

/******************************************************************************
Function Name   : usb_pstd_SetStallPipe0
Description     : Set pipe "0" PID to STALL.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
Return value    : none
******************************************************************************/
void usb_pstd_SetStallPipe0(USB_UTR_t *ptr)
{
    /* PIPE control reg set */
    usb_creg_set_pid( ptr, USB_PIPE0, USB_PID_STALL );
} /* eof usb_pstd_SetStallPipe0() */

/******************************************************************************
Function Name   : R_usb_pstd_ControlEnd
Description     : End control transfer.
Arguments       : USB_UTR_t *ptr    : USB system internal structure.
                : uint16_t status   : Control transfer status.
Return value    : none
******************************************************************************/
void R_usb_pstd_ControlEnd(USB_UTR_t *ptr, uint16_t status)
{
    usb_pstd_ControlEnd( ptr, status);
}

/******************************************************************************
Function Name   : usb_pstd_StandReq0
Description     : The idle and setup stages of a standard request from host.
Arguments       : USB_UTR_t *ptr    : USB system internal structure.
Return value    : none
******************************************************************************/
void usb_pstd_StandReq0(USB_UTR_t *ptr)
{
    switch( usb_gpstd_ReqRequest )
    {
        case USB_CLEAR_FEATURE:
            /* Clear Feature0 */
            usb_pstd_ClearFeature0();
        break;
        case USB_SET_FEATURE:
            /* Set Feature0 */
            usb_pstd_SetFeature0();
        break;
        case USB_SET_ADDRESS:
            /* Set Address0 */
            usb_pstd_SetAddress0();
        break;
        case USB_SET_CONFIGURATION:
            /* Set Configuration0 */
            usb_pstd_SetConfiguration0(ptr);
        break;
        case USB_SET_INTERFACE:
            /* Set Interface0 */
            usb_pstd_SetInterface0(ptr);
        break;
        default:
        break;
    }
}

/******************************************************************************
Function Name   : usb_pstd_SetInterface0
Description     : Call callback function to notify reception of SetInterface com-
                : mand. For idle/setup stage.
Arguments       : USB_UTR_t *ptr    : USB system internal structure.
Return value    : none
******************************************************************************/
void usb_pstd_SetInterface0(USB_UTR_t *ptr)
{
    /* Interfaced change function call */
    (*usb_gpstd_Driver.interface)(ptr, usb_gpstd_AltNum[usb_gpstd_ReqIndex], (uint16_t)USB_NO_ARG);
}

/******************************************************************************
Function Name   : usb_pstd_SetConfiguration0
Description     : Call callback function to notify the reception of SetConfiguration command
                : (for idle /setup stage)
Arguments       : USB_UTR_t *ptr    : USB system internal structure.
Return value    : none
******************************************************************************/
void usb_pstd_SetConfiguration0(USB_UTR_t *ptr)
{
    uint16_t config_num;

    config_num = usb_gpstd_ConfigNum;

    /* Configuration number set */
    usb_pstd_SetConfigNum(usb_gpstd_ReqValue);

    if( usb_gpstd_ReqValue != config_num )
    {
        /* Registration open function call */
        (*usb_gpstd_Driver.devconfig)(ptr, usb_gpstd_ConfigNum, (uint16_t)USB_NO_ARG);
    }
}

/******************************************************************************
Function Name   : usb_pstd_SetConfigNum
Description     : Set specified configuration number.
Arguments       : uint16_t value    : Configuration number
Return value    : none
******************************************************************************/
void usb_pstd_SetConfigNum(uint16_t value)
{
    /* Set configuration number */
    usb_gpstd_ConfigNum = value;
    /* Alternate setting clear */
    usb_pstd_ClearAlt();
}

/******************************************************************************
Function Name   : usb_pstd_ClearAlt
Description     : Zero-clear the alternate table (buffer).
Arguments       : none
Return value    : none
******************************************************************************/
void usb_pstd_ClearAlt(void)
{
    uint16_t    i;

    for( i = 0; i < USB_ALT_NO; ++i )
    {
        /* Alternate table clear */
        usb_gpstd_AltNum[i] = 0;
    }
}

/******************************************************************************
Function Name   : usb_pstd_SetAddress0
Description     : Set Address0 (for idle/setup stage).
Arguments       : none
Return value    : none
******************************************************************************/
void usb_pstd_SetAddress0(void)
{
}

/******************************************************************************
Function Name   : usb_pstd_SetFeature0
Description     : Set Feature0 (for idle/setup stage)
Arguments       : none
Return value    : none
******************************************************************************/
void usb_pstd_SetFeature0(void)
{
}

/******************************************************************************
Function Name   : usb_pstd_ClearFeature0
Description     : Clear Feature0
Arguments       : none
Return value    : none
******************************************************************************/
void usb_pstd_ClearFeature0(void)
{
}

/******************************************************************************
Function Name   : usb_pstd_StandReq1
Description     : The control read data stage of a standard request from host.
Arguments       : USB_UTR_t *ptr    : USB system internal structure.
Return value    : none
******************************************************************************/
void usb_pstd_StandReq1(USB_UTR_t *ptr)
{
    switch( usb_gpstd_ReqRequest )
    {
        case USB_GET_STATUS:
            /* Get Status1 */
            usb_pstd_GetStatus1(ptr);
        break;
        case USB_GET_DESCRIPTOR:
            /* Get Descriptor1 */
            usb_pstd_GetDescriptor1(ptr);
        break;
        case USB_GET_CONFIGURATION:
            /* Get Configuration1 */
            usb_pstd_GetConfiguration1(ptr);
        break;
        case USB_GET_INTERFACE:
            /* Get Interface1 */
            usb_pstd_GetInterface1(ptr);
        break;
        case USB_SYNCH_FRAME:
            /* Synch Frame */
            usb_pstd_SynchFrame1(ptr);
        break;
        default:
            /* Set pipe USB_PID_STALL */
            usb_pstd_SetStallPipe0( ptr );
        break;
    }
}

/******************************************************************************
Function Name   : usb_pstd_SynchFrame1
Description     : Return STALL response to SynchFrame command.
Arguments       : none
Return value    : none
******************************************************************************/
void usb_pstd_SynchFrame1(USB_UTR_t *ptr)
{
    /* Set pipe USB_PID_STALL */
    usb_pstd_SetStallPipe0( ptr );
}

/******************************************************************************
Function Name   : usb_pstd_GetInterface1
Description     : Analyze a Get Interface command and process it.
Arguments       : USB_UTR_t *ptr    : USB system internal structure.
Return value    : none
******************************************************************************/
void usb_pstd_GetInterface1(USB_UTR_t *ptr)
{
    static uint8_t    tbl[2];

    /* check request */
    if( ((usb_gpstd_ReqTypeRecip == USB_INTERFACE) && (usb_gpstd_ReqValue == 0)) && (usb_gpstd_ReqLength == 1) )
    {
        if( usb_gpstd_ReqIndex < USB_ALT_NO )
        {
            tbl[0] = (uint8_t)usb_gpstd_AltNum[usb_gpstd_ReqIndex];
            /* Start control read */
            usb_pstd_ControlRead(ptr, (uint32_t)1, tbl);
        }
        else
        {
            /* Request error */
            usb_pstd_SetStallPipe0( ptr );
        }
    }
    else
    {
        /* Request error */
        usb_pstd_SetStallPipe0( ptr );
    }
}

/******************************************************************************
Function Name   : usb_pstd_ControlRead
Description     : Called by R_usb_pstd_ControlRead, see it for description.
Arguments       : USB_UTR_t *ptr    : USB system internal structure.
                : uint32_t bsize    : Read size in bytes.
                : uint8_t *table    : Start address of read data buffer.
Return value    : uint16_t          : USB_WRITESHRT/USB_WRITE_END/USB_WRITING/
                :                   : USB_FIFOERROR.
******************************************************************************/
uint16_t usb_pstd_ControlRead(USB_UTR_t *ptr, uint32_t bsize, uint8_t *table)
{
    uint16_t    end_flag;

    usb_gcstd_DataCnt[ptr->ip][USB_PIPE0] = bsize;
    usb_gcstd_DataPtr[ptr->ip][USB_PIPE0] = table;

    usb_cstd_chg_curpipe(ptr, (uint16_t)USB_PIPE0, (uint16_t)USB_CUSE, (uint16_t)USB_ISEL);
    
    /* Buffer clear */
    usb_creg_set_bclr( ptr, USB_CUSE );

    usb_creg_clr_sts_bemp( ptr, USB_PIPE0 );

    /* Peripheral Control sequence */
    end_flag = usb_cstd_write_data( ptr, USB_PIPE0, USB_CUSE );

    /* Peripheral control sequence */
    switch( end_flag )
    {
    /* End of data write */
    case USB_WRITESHRT:
        /* Enable not ready interrupt */
        usb_cstd_NrdyEnable(ptr, (uint16_t)USB_PIPE0);
        /* Set PID=BUF */
        usb_cstd_SetBuf(ptr, (uint16_t)USB_PIPE0);
        break;
    /* End of data write (not null) */
    case USB_WRITEEND:
        /* Continue */
    /* Continue of data write */
    case USB_WRITING:
        /* Enable empty interrupt */
        usb_creg_set_bempenb(ptr, (uint16_t)USB_PIPE0);
        /* Enable not ready interrupt */
        usb_cstd_NrdyEnable(ptr, (uint16_t)USB_PIPE0);
        /* Set PID=BUF */
        usb_cstd_SetBuf(ptr, (uint16_t)USB_PIPE0);
        break;
    /* FIFO access error */
    case USB_FIFOERROR:
        break;
    default:
        break;
    }
    /* End or error or continue */
    return (end_flag);
}

/******************************************************************************
Function Name   : usb_pstd_GetConfiguration1
Description     : Analyze a Get Configuration command and process it.
                : (for control read data stage)
Arguments       : USB_UTR_t *ptr    : USB system internal structure.
Return value    : none
******************************************************************************/
void usb_pstd_GetConfiguration1(USB_UTR_t *ptr)
{
    static uint8_t    tbl[2];

    /* check request */
    if( (((usb_gpstd_ReqTypeRecip == USB_DEVICE) 
        && (usb_gpstd_ReqValue == 0)) 
        && (usb_gpstd_ReqIndex == 0)) 
        && (usb_gpstd_ReqLength == 1) )
    {
        tbl[0] = (uint8_t)usb_gpstd_ConfigNum;
        /* Control read start */
        usb_pstd_ControlRead(ptr, (uint32_t)1, tbl);
    }
    else
    {
        /* Set pipe USB_PID_STALL */
        usb_pstd_SetStallPipe0( ptr );
    }
}

/******************************************************************************
Function Name   : usb_pstd_GetDescriptor1
Description     : Analyze a Get Descriptor command from host and process it.
Arguments       : USB_UTR_t *ptr    : USB system internal structure.
Return value    : none
******************************************************************************/
void usb_pstd_GetDescriptor1(USB_UTR_t *ptr)
{
    uint16_t    len;
    uint16_t    idx;
    uint8_t     *table;

    if(usb_gpstd_ReqTypeRecip == USB_DEVICE )
    {
        idx = (uint16_t)(usb_gpstd_ReqValue & USB_DT_INDEX);
        switch( (uint16_t)USB_GET_DT_TYPE(usb_gpstd_ReqValue) )
        {
            /*---- Device descriptor ----*/
            case USB_DT_DEVICE:
                if((usb_gpstd_ReqIndex == (uint16_t)0) && (idx == (uint16_t)0))
                {
                    table = usb_gpstd_Driver.devicetbl;
                    if( usb_gpstd_ReqLength < table[0] )
                    {
                        /* Control read start */
                        usb_pstd_ControlRead(ptr, (uint32_t)usb_gpstd_ReqLength, table);
                    }
                    else
                    {
                        /* Control read start */
                        usb_pstd_ControlRead(ptr, (uint32_t)table[0], table);
                    }
                }
                else
                {
                    /* Request error */
                    usb_pstd_SetStallPipe0( ptr );
                }
            break;
            /*---- Configuration descriptor ----*/
            case USB_DT_CONFIGURATION:
                if(( usb_gpstd_ReqIndex == 0 ) && (idx == (uint16_t)0))
                {
                    table = usb_gpstd_Driver.configtbl[idx];
                    len   = (uint16_t)(*(uint8_t*)((uint32_t)table + (uint32_t)3));
                    len   = (uint16_t)(len << 8);
                    len   += (uint16_t)(*(uint8_t*)((uint32_t)table + (uint32_t)2));
                    /* Descriptor > wLength */
                    if( usb_gpstd_ReqLength < len )
                    {
                        /* Control read start */
                        usb_pstd_ControlRead(ptr, (uint32_t)usb_gpstd_ReqLength, table);
                    }
                    else
                    {
                        /* Control read start */
                        usb_pstd_ControlRead(ptr, (uint32_t)len, table);
                    }
                }
                else
                {
                    /* Request error */
                    usb_pstd_SetStallPipe0( ptr );
                }
            break;
            /*---- String descriptor ----*/
            case USB_DT_STRING:
                if( idx < USB_STRINGNUM )
                {
                    table = usb_gpstd_Driver.stringtbl[idx];
                    len   = (uint16_t)(*(uint8_t*)((uint32_t)table + (uint32_t)0));
                    if( usb_gpstd_ReqLength < len )
                    {
                        /* Control read start */
                        usb_pstd_ControlRead(ptr, (uint32_t)usb_gpstd_ReqLength, table);
                    }
                    else
                    {
                        /* Control read start */
                        usb_pstd_ControlRead(ptr, (uint32_t)len, table);
                    }
                }
                else
                {
                    /* Request error */
                    usb_pstd_SetStallPipe0( ptr );
                }
            break;
            /*---- Interface descriptor ----*/
            case USB_DT_INTERFACE:
                /* Set pipe USB_PID_STALL */
                usb_pstd_SetStallPipe0( ptr );
            break;
            /*---- Endpoint descriptor ----*/
            case USB_DT_ENDPOINT:
                /* Set pipe USB_PID_STALL */
                usb_pstd_SetStallPipe0( ptr );
            break;
            case USB_DT_DEVICE_QUALIFIER:
                if( ((usb_cstd_HiSpeedEnable(ptr, (uint16_t)USB_PORT0) == USB_YES)
                    && (usb_gpstd_ReqIndex == 0)) && (idx == 0) )
                {
                    table = usb_gpstd_Driver.qualitbl;
                    if( usb_gpstd_ReqLength < table[0] )
                    {
                        /* Control read start */
                        usb_pstd_ControlRead(ptr, (uint32_t)usb_gpstd_ReqLength, table);
                    }
                    else
                    {
                        /* Control read start */
                        usb_pstd_ControlRead(ptr, (uint32_t)table[0], table);
                    }
                }
                else
                {
                    /* Request error */
                    usb_pstd_SetStallPipe0( ptr );
                }
            break;
            case USB_DT_OTHER_SPEED_CONF:
                if( (usb_cstd_HiSpeedEnable(ptr, (uint16_t)USB_PORT0) == USB_YES)
                    && (usb_gpstd_ReqIndex == 0) && (idx == (uint16_t)0))
                {
                    table = usb_gpstd_Driver.othertbl[idx];
                    len     = (uint16_t)(*(uint8_t*)((uint32_t)table + (uint32_t)3));
                    len     = (uint16_t)(len << 8);
                    len += (uint16_t)(*(uint8_t*)((uint32_t)table + (uint32_t)2));
                    /* Descriptor > wLength */
                    if( usb_gpstd_ReqLength < len )
                    {
                        /* Control read start */
                        usb_pstd_ControlRead(ptr, (uint32_t)usb_gpstd_ReqLength, table);
                    }
                    else
                    {
                        /* Control read start */
                        usb_pstd_ControlRead(ptr, (uint32_t)len, table);
                    }
                }
                else
                {
                    /* Request error */
                    usb_pstd_SetStallPipe0( ptr );
                }
            break;
            case USB_DT_INTERFACE_POWER:
                /* Not support */
                usb_pstd_SetStallPipe0( ptr );
            break;
            default:
                /* Set pipe USB_PID_STALL */
                usb_pstd_SetStallPipe0( ptr );
            break;
        }
    }
    else if( usb_gpstd_ReqTypeRecip == USB_INTERFACE )
    {
        usb_gpstd_ReqReg.ReqType        = usb_gpstd_ReqType;
        usb_gpstd_ReqReg.ReqTypeType    = usb_gpstd_ReqTypeType;
        usb_gpstd_ReqReg.ReqTypeRecip   = usb_gpstd_ReqTypeRecip;
        usb_gpstd_ReqReg.ReqRequest     = usb_gpstd_ReqRequest;
        usb_gpstd_ReqReg.ReqValue       = usb_gpstd_ReqValue;
        usb_gpstd_ReqReg.ReqIndex       = usb_gpstd_ReqIndex;
        usb_gpstd_ReqReg.ReqLength      = usb_gpstd_ReqLength;
        (*usb_gpstd_Driver.ctrltrans)(ptr, (USB_REQUEST_t *)&usb_gpstd_ReqReg, (uint16_t)USB_NO_ARG);
    }
    else
    {
        /* Set pipe USB_PID_STALL */
        usb_pstd_SetStallPipe0( ptr );
    }
}

/******************************************************************************
Function Name   : usb_cstd_HiSpeedEnable
Description     : Check if set to Hi-speed.
Arguments       : USB_UTR_t *ptr : USB internal structure. Selects e.g. channel.    ;
                : uint16_t port  : Root port
Return value    : uint16_t       : YES; Hi-Speed enabled.
                :                : NO; Hi-Speed disabled.
******************************************************************************/
uint16_t usb_cstd_HiSpeedEnable(USB_UTR_t *ptr, uint16_t port)
{
    uint16_t    buf;

    buf = usb_creg_read_syscfg( ptr, port );

    if( (buf & USB_HSE) == USB_HSE )
    {
        /* Hi-Speed Enable */
        return USB_YES;
    }
    else
    {
        /* Hi-Speed Disable */
        return USB_NO;
    }
}

/******************************************************************************
Function Name   : usb_pstd_GetStatus1
Description     : Analyze a Get Status command and process it.
Arguments       : USB_UTR_t *ptr    : USB system internal structure.
Return value    : none
******************************************************************************/
void usb_pstd_GetStatus1(USB_UTR_t *ptr)
{
    static uint8_t  tbl[2];
    uint16_t        ep;
    uint16_t        buffer, pipe;

    if( (usb_gpstd_ReqValue == 0) && (usb_gpstd_ReqLength == 2) )
    {
        tbl[0] = 0;
        tbl[1] = 0;
        /* Check request type */
        switch( usb_gpstd_ReqTypeRecip )
        {
            case USB_DEVICE:
                if( usb_gpstd_ReqIndex == 0 )
                {
                    /* Self powered / Bus powered */
                    tbl[0] = usb_pstd_GetCurrentPower();
                    /* Support remote wakeup ? */
                    if( usb_gpstd_RemoteWakeup == USB_YES )
                    {
                        tbl[0] |= USB_GS_REMOTEWAKEUP;
                    }
                    /* Control read start */
                    usb_pstd_ControlRead(ptr, (uint32_t)2, tbl);
                }
                else
                {
                    /* Request error */
                    usb_pstd_SetStallPipe0( ptr );
                }
            break;
            case USB_INTERFACE:
                if( usb_pstd_ChkConfigured(ptr) == USB_YES )
                {
                    if( usb_gpstd_ReqIndex < usb_pstd_GetInterfaceNum(usb_gpstd_ConfigNum) )
                    {
                        /* Control read start */
                        usb_pstd_ControlRead(ptr, (uint32_t)2, tbl);
                    }
                    else
                    {
                        /* Request error (not exist interface) */
                        usb_pstd_SetStallPipe0( ptr );
                    }
                }
                else
                {
                    /* Request error */
                    usb_pstd_SetStallPipe0( ptr );
                }
            break;
            case USB_ENDPOINT:
                /* Endpoint number */
                ep = (uint16_t)(usb_gpstd_ReqIndex & USB_EPNUMFIELD);
                /* Endpoint 0 */
                if( ep == 0 )
                {
                    buffer = usb_creg_read_dcpctr( ptr );
                    if( (buffer & USB_PID_STALL) != (uint16_t)0 )
                    {
                       /* Halt set */
                       tbl[0] = USB_GS_HALT;
                    }
                    /* Control read start */
                    usb_pstd_ControlRead(ptr, (uint32_t)2, tbl);
                }
                /* EP1 to max */
                else if( ep <= USB_MAX_EP_NO )
                {
                    if( usb_pstd_ChkConfigured(ptr) == USB_YES )
                    {
                        pipe = usb_cstd_Epadr2Pipe(ptr, usb_gpstd_ReqIndex);
                        if( pipe == USB_ERROR )
                        {
                            /* Set pipe USB_PID_STALL */
                            usb_pstd_SetStallPipe0( ptr );
                        }
                        else
                        {
                            buffer = usb_cstd_GetPid(ptr, pipe);
                            if( (buffer & USB_PID_STALL) != (uint16_t)0 )
                            {
                                /* Halt set */
                                tbl[0] = USB_GS_HALT;
                            }
                            /* Control read start */
                            usb_pstd_ControlRead(ptr, (uint32_t)2, tbl);
                        }
                    }
                    else
                    {
                        /* Set pipe USB_PID_STALL */
                        usb_pstd_SetStallPipe0( ptr );
                    }
                }
                else
                {
                    /* Set pipe USB_PID_STALL */
                    usb_pstd_SetStallPipe0( ptr );
                }
            break;
            default:
                /* Set pipe USB_PID_STALL */
                usb_pstd_SetStallPipe0( ptr );
            break;
        }
    }
    else
    {
        /* Set pipe USB_PID_STALL */
        usb_pstd_SetStallPipe0( ptr );
    }
}

/******************************************************************************
Function Name   : usb_cstd_GetPid
Description     : Fetch specified pipe's PID.
Arguments       : USB_UTR_t *ptr : USB internal structure. Selects e.g. channel.
                : uint16_t pipe  : Pipe number.
Return value    : uint16_t PID-bit status
******************************************************************************/
uint16_t usb_cstd_GetPid(USB_UTR_t *ptr, uint16_t pipe)
{
    uint16_t    buf;

    /* PIPE control reg read */
    buf = usb_creg_read_pipectr( ptr, pipe );
    return (uint16_t)(buf & USB_PID);
}

/******************************************************************************
Function Name   : usb_cstd_Epadr2Pipe
Description     : Get the associated pipe no. of the specified endpoint.
Arguments       : USB_UTR_t *ptr : USB internal structure. Selects e.g. channel.
                : uint16_t dir_ep : Direction + endpoint number.
Return value    : uint16_t        : OK    : Pipe number.
                :                 : ERROR : Error.
******************************************************************************/
uint16_t usb_cstd_Epadr2Pipe(USB_UTR_t *ptr, uint16_t dir_ep)
{
    uint16_t        i, direp, tmp, *table;

    /* Check current function */
    if( usb_cstd_is_host_mode(ptr) == USB_NO )
    {
        uint16_t conf;

        conf = usb_gpstd_ConfigNum;
        if( conf < (uint16_t)1 )
        {
            /* Address state */
            conf = (uint16_t)1;
        }

        /* Peripheral */
        /* Get PIPE Number from Endpoint address */
        table = (uint16_t*)((uint16_t**)(usb_gpstd_Driver.pipetbl[conf - 1]));
        direp = (uint16_t)(((dir_ep & 0x80) >> 3) | (dir_ep & 0x0F));
        /* EP table loop */
        for( i = 0; table[i] != USB_PDTBLEND; i += USB_EPL )
        {
            tmp = (uint16_t)(table[i + 1] & (USB_DIRFIELD | USB_EPNUMFIELD));
            /* EP table endpoint dir check */
            if( direp == tmp )
            {
                return table[i];
            }
        }
    }
    else
    {
    }
    return USB_ERROR;
}

/******************************************************************************

Function Name   : usb_pstd_GetCurrentPower
Description     : Find out how the peripheral is powered by looking at the con-
                : figuration descriptor.
Arguments       : none
Return value    : uint8_t : Current power means; self-powered or bus-powered
                : (GS_SELFPOWERD/GS_BUSPOWERD).
******************************************************************************/
uint8_t usb_pstd_GetCurrentPower(void)
{
    /*
     * Please answer the currently power of your system.
     */

    uint8_t tmp, currentpower, conf;
    uint16_t    tbl_index;

    conf = (uint8_t)usb_gpstd_ConfigNum;
    if( conf < (uint8_t)1 )
    {
        /* Address state */
        conf = (uint8_t)1;
    }

    /* Get Configuration descriptor table index */
    tbl_index = usb_pstd_get_confignum_to_tblindex( conf );

    /* Standard configuration descriptor */
    tmp = *(uint8_t*)((uint32_t)usb_gpstd_Driver.configtbl[tbl_index] + (uint32_t)7u);
    if( (tmp & USB_CF_SELFP) == USB_CF_SELFP )
    {
        /* Self Powered */
        currentpower = USB_GS_SELFPOWERD;
    }
    else
    {
        /* Bus Powered */
        currentpower = USB_GS_BUSPOWERD;
    }

    /* Check currently powered */

    return currentpower;
}

/******************************************************************************
Function Name   : usb_pstd_StandReq2
Description     : The control write data stage of a standard request from host.
Arguments       : USB_UTR_t *ptr    : USB system internal structure.
Return value    : none
******************************************************************************/
void usb_pstd_StandReq2(USB_UTR_t *ptr)
{
    if( usb_gpstd_ReqRequest == USB_SET_DESCRIPTOR )
    {
        /* Set Descriptor2 */
        usb_pstd_SetDescriptor2(ptr);
    }
    else
    {
        /* Set pipe USB_PID_STALL */
        usb_pstd_SetStallPipe0( ptr );
    }
}

/******************************************************************************
Function Name   : usb_pstd_SetDescriptor2
Description     : Return STALL in response to a Set Descriptor command.
Arguments       : USB_UTR_t *ptr    : USB system internal structure.
Return value    : none
******************************************************************************/
void usb_pstd_SetDescriptor2(USB_UTR_t *ptr)
{
    /* Not specification */
    usb_pstd_SetStallPipe0( ptr );
}

/******************************************************************************
Function Name   : usb_pstd_StandReq3
Description     : Standard request process. This is for the status stage of a 
                : control write where there is no data stage.
Arguments       : USB_UTR_t *ptr    : USB system internal structure.
Return value    : none
******************************************************************************/
void usb_pstd_StandReq3(USB_UTR_t *ptr)
{
    switch( usb_gpstd_ReqRequest )
    {
        case USB_CLEAR_FEATURE:
            /* ClearFeature3 */
            usb_pstd_ClearFeature3(ptr);
        break;
        case USB_SET_FEATURE:
            /* SetFeature3 */
            usb_pstd_SetFeature3(ptr);
        break;
        case USB_SET_ADDRESS:
            /* SetAddress3 */
            usb_pstd_SetAddress3(ptr);
        break;
        case USB_SET_CONFIGURATION:
            /* SetConfiguration3 */
            usb_pstd_SetConfiguration3(ptr);
        break;
        case USB_SET_INTERFACE:
            /* SetInterface3 */
            usb_pstd_SetInterface3(ptr);
        break;
        default:
            /* Set pipe USB_PID_STALL */
            usb_pstd_SetStallPipe0( ptr );
        break;
    }
    /* Control transfer stop(end) */
    usb_pstd_ControlEnd(ptr, (uint16_t)USB_CTRL_END);
}

/******************************************************************************
Function Name   : usb_pstd_ClearFeature3
Description     : Analyze a Clear Feature command and process it.
Arguments       : USB_UTR_t *ptr    : USB system internal structure.
Return value    : none
******************************************************************************/
void usb_pstd_ClearFeature3(USB_UTR_t *ptr)
{
    uint16_t        pipe;
    uint16_t        ep;

    if( usb_gpstd_ReqLength == 0 )
    {
        /* check request type */
        switch( usb_gpstd_ReqTypeRecip )
        {
            case USB_DEVICE:
                if( (usb_gpstd_ReqValue == USB_DEV_REMOTE_WAKEUP)
                    && (usb_gpstd_ReqIndex == 0) )
                {
                    if( usb_pstd_ChkRemote() == USB_YES )
                    {
                        usb_gpstd_RemoteWakeup = USB_NO;
                        /* Set pipe PID_BUF */
                        usb_cstd_SetBuf(ptr, (uint16_t)USB_PIPE0);
                    }
                    else
                    {
                        /* Not support remote wakeup */
                        /* Request error */
                        usb_pstd_SetStallPipe0( ptr );
                    }
                }
                else
                {
                    /* Not specification */
                    usb_pstd_SetStallPipe0( ptr );
                }
            break;
            case USB_INTERFACE:
                /* Request error */
                usb_pstd_SetStallPipe0( ptr );
            break;
            case USB_ENDPOINT:
                /* Endpoint number */
                ep = (uint16_t)(usb_gpstd_ReqIndex & USB_EPNUMFIELD);
                if( usb_gpstd_ReqValue == USB_ENDPOINT_HALT )
                {
                    /* EP0 */
                    if( ep == 0 )
                    {
                        /* Stall clear */
                        usb_cstd_ClrStall(ptr, (uint16_t)USB_PIPE0);
                        /* Set pipe PID_BUF */
                        usb_cstd_SetBuf(ptr, (uint16_t)USB_PIPE0);
                    }
                    /* EP1 to max */
                    else if( ep <= USB_MAX_EP_NO )
                    {
                        pipe = usb_cstd_Epadr2Pipe(ptr, usb_gpstd_ReqIndex);
                        if( pipe == USB_ERROR )
                        {
                            /* Request error */
                            usb_pstd_SetStallPipe0( ptr );
                        }
                        else
                        {
                            if( usb_cstd_GetPid(ptr, pipe) == USB_PID_BUF )
                            {
                                usb_cstd_SetNak(ptr, pipe);
                                /* SQCLR=1 */
                                usb_creg_set_sqclr(ptr, pipe);
                                /* Set pipe PID_BUF */
                                usb_cstd_SetBuf(ptr, pipe);
                            }
                            else
                            {
                                usb_cstd_ClrStall(ptr, pipe);
                                /* SQCLR=1 */
                                usb_creg_set_sqclr(ptr, pipe);
                            }
                            /* Set pipe PID_BUF */
                            usb_cstd_SetBuf(ptr, (uint16_t)USB_PIPE0);
                            if( usb_gpstd_StallPipe[pipe] == USB_YES )
                            {
                                usb_gpstd_StallPipe[pipe] = USB_DONE;
                                (*usb_gpstd_StallCB)(ptr, pipe, (uint16_t)0);
                            }
                        }
                    }
                    else
                    {
                        /* Request error */
                        usb_pstd_SetStallPipe0( ptr );
                    }
                }
                else
                {
                    /* Request error */
                    usb_pstd_SetStallPipe0( ptr );
                }
            break;
            default:
                usb_pstd_SetStallPipe0( ptr );
            break;
        }
    }
    else
    {
        /* Not specification */
        usb_pstd_SetStallPipe0( ptr );
    }
}

/******************************************************************************
Function Name   : usb_pstd_ChkRemote
Description     : Check if the RemoteWakeUp bit for the configuration descrip-
                : tor is set.
Arguments       : none
Return value    : uint16_t : remote wakeup status (YES/NO).
******************************************************************************/
uint16_t usb_pstd_ChkRemote(void)
{
    uint8_t atr;
    uint16_t    tbl_index;

    if( usb_gpstd_ConfigNum == 0 )
    {
        return USB_NO;
    }

    /* Get Configuration descriptor table index */
    tbl_index = usb_pstd_get_confignum_to_tblindex( usb_gpstd_ConfigNum );

    /* Get Configuration Descriptor - bmAttributes */
    atr = *(uint8_t*)((uint32_t)usb_gpstd_Driver.configtbl[tbl_index] + (uint32_t)7u);
    /* Remote Wakeup check(= D5) */
    if( (atr & USB_CF_RWUPON) == USB_CF_RWUPON )
    {
        return USB_YES;
    }
    return USB_NO;
}

/******************************************************************************
Function Name   : usb_pstd_SetFeature3
Description     : Analyze a Set Feature command and process it.
Arguments       : USB_UTR_t *ptr    : USB system internal structure.
Return value    : none
******************************************************************************/
void usb_pstd_SetFeature3(USB_UTR_t *ptr)
{
    uint16_t    pipe;
    uint16_t    ep;

    if( usb_gpstd_ReqLength == 0 )
    {
        /* check request type */
        switch( usb_gpstd_ReqTypeRecip )
        {
            case USB_DEVICE:
                switch( usb_gpstd_ReqValue )
                {
                    case USB_DEV_REMOTE_WAKEUP:
                        if( usb_gpstd_ReqIndex == 0 )
                        {
                            if( usb_pstd_ChkRemote() == USB_YES )
                            {
                                usb_gpstd_RemoteWakeup = USB_YES;
                                /* Set pipe PID_BUF */
                                usb_cstd_SetBuf(ptr, (uint16_t)USB_PIPE0);
                            }
                            else
                            {
                                /* Not support remote wakeup */
                                /* Request error */
                                usb_pstd_SetStallPipe0( ptr );
                            }
                        }
                        else
                        {
                            /* Not specification */
                            usb_pstd_SetStallPipe0( ptr );
                        }
                    break;

                    default:
                        usb_pstd_SetFeatureFunction(ptr);
                    break;
                }
            break;
            case USB_INTERFACE:
                /* Set pipe USB_PID_STALL */
                usb_pstd_SetStallPipe0( ptr );
            break;
            case USB_ENDPOINT:
                /* Endpoint number */
                ep = (uint16_t)(usb_gpstd_ReqIndex & USB_EPNUMFIELD);
                if( usb_gpstd_ReqValue == USB_ENDPOINT_HALT )
                {
                    /* EP0 */
                    if( ep == 0 )
                    {
                        /* Set pipe PID_BUF */
                        usb_cstd_SetBuf(ptr, (uint16_t)USB_PIPE0);
                    }
                    /* EP1 to max */
                    else if( ep <= USB_MAX_EP_NO )
                    {
                        pipe = usb_cstd_Epadr2Pipe(ptr, usb_gpstd_ReqIndex);
                        if( pipe == USB_ERROR )
                        {
                            /* Request error */
                            usb_pstd_SetStallPipe0( ptr );
                        }
                        else
                        {
                            /* Set pipe USB_PID_STALL */
                            usb_pstd_SetStall(ptr, pipe);
                            /* Set pipe PID_BUF */
                            usb_cstd_SetBuf(ptr, (uint16_t)USB_PIPE0);
                        }
                    }
                    else
                    {
                        /* Request error */
                        usb_pstd_SetStallPipe0( ptr );
                    }
                }
                else
                {
                    /* Not specification */
                    usb_pstd_SetStallPipe0( ptr );
                }
            break;

            default:
                /* Request error */
                usb_pstd_SetStallPipe0( ptr );
            break;
        }
    }
    else
    {
        /* Request error */
        usb_pstd_SetStallPipe0( ptr );
    }
}

/******************************************************************************
Function Name   : usb_pstd_SetFeatureFunction
Description     : Process a SET_FEATURE request.
Arguments       : USB_UTR_t *ptr    : USB system internal structure.
Return value    : none
******************************************************************************/
void usb_pstd_SetFeatureFunction(USB_UTR_t *ptr)
{
    /* Request error */
    usb_pstd_SetStallPipe0(ptr);
}

/******************************************************************************
Function Name   : usb_pstd_SetAddress3
Description     : Analyze a Set Address command and process it.
Arguments       : USB_UTR_t *ptr    : USB system internal structure.
Return value    : none
******************************************************************************/
void usb_pstd_SetAddress3(USB_UTR_t *ptr)
{
    if( usb_gpstd_ReqTypeRecip == USB_DEVICE )
    {
        if( (usb_gpstd_ReqIndex == 0) && (usb_gpstd_ReqLength == 0) )
        {
            if( usb_gpstd_ReqValue <= 127 )
            {
                /* Set pipe PID_BUF */
                usb_cstd_SetBuf(ptr, (uint16_t)USB_PIPE0);
            }
            else
            {
                /* Not specification */
                usb_pstd_SetStallPipe0( ptr );
            }
        }
        else
        {
            /* Not specification */
            usb_pstd_SetStallPipe0( ptr );
        }
    }
    else
    {
        /* Request error */
        usb_pstd_SetStallPipe0( ptr );
    }
}

/******************************************************************************
Function Name   : usb_pstd_SetConfiguration3
Description     : Analyze a Set Configuration command and process it. This is
                : for the status stage of a control write where there is no data
                : stage.
Arguments       : USB_UTR_t *ptr    : USB system internal structure.
Return value    : none
******************************************************************************/
void usb_pstd_SetConfiguration3(USB_UTR_t *ptr)
{
    uint16_t    i, j;
    uint16_t    ifc, cfgnum, cfgok;
    uint16_t    *table;
    uint8_t     *table2;

    if( usb_gpstd_ReqTypeRecip == USB_DEVICE )
    {
        cfgnum  = usb_pstd_GetConfigNum();
        cfgok   = USB_NG;

        for ( j = 0; j < cfgnum; j++ )
        {
            table2 = usb_gpstd_Driver.configtbl[j];

            if( (((usb_gpstd_ReqValue == table2[5]) || (usb_gpstd_ReqValue == 0))
                && (usb_gpstd_ReqIndex == 0)) && (usb_gpstd_ReqLength == 0) )
            {
                usb_cstd_SetBuf(ptr, (uint16_t)USB_PIPE0);
                cfgok    = USB_OK;

                if( ( usb_gpstd_ReqValue > 0 ) && ( usb_gpstd_ReqValue != usb_gpstd_ConfigNum ) )
                {
                    usb_pstd_ClearEpTblIndex();
                    ifc = usb_pstd_GetInterfaceNum(usb_gpstd_ReqValue);
                    for( i = 0; i < ifc; ++i )
                    {
                        /* Pipe Information Table ("endpoint table") initialize */
                        usb_pstd_SetEpTblIndex(usb_gpstd_ReqValue, i, (uint16_t)0);
                    }
                    table = usb_gpstd_Driver.pipetbl[usb_gpstd_ReqValue - 1];
                    /* Clear pipe configuration register */
                    usb_pstd_SetPipeRegister(ptr, (uint16_t)USB_CLRPIPE, table);
                    /* Set pipe configuration register */
                    usb_pstd_SetPipeRegister(ptr, (uint16_t)USB_PERIPIPE, table);
                }
                break;
            }
        }
        if( cfgok == USB_NG )
        {
            /* Request error */
            usb_pstd_SetStallPipe0( ptr );
        }
    }
    else
    {
        /* Request error */
        usb_pstd_SetStallPipe0( ptr );
    }
}

/******************************************************************************
Function Name   : usb_pstd_SetPipeRegister
Description     : Configure specified pipe.
Arguments       : uint16_t pipe_number  : Pipe number.
                : uint16_t *tbl         : DEF_EP table pointer.
Return value    : none
******************************************************************************/
void usb_pstd_SetPipeRegister(USB_UTR_t *ptr, uint16_t pipe_number, uint16_t *tbl)
{
    uint16_t        i, pipe, ep;
    uint16_t        buf;
    uint16_t    dir;

    switch( pipe_number )
    {
    /* All pipe initialized */
    case USB_USEPIPE:
        /* Current FIFO port Clear */
        usb_cstd_chg_curpipe(ptr, (uint16_t)USB_PIPE0, (uint16_t)USB_CUSE,  USB_NO);
        usb_cstd_chg_curpipe(ptr, (uint16_t)USB_PIPE0, (uint16_t)USB_D0USE, USB_NO);
        usb_cstd_chg_curpipe(ptr, (uint16_t)USB_PIPE0, (uint16_t)USB_D1USE, USB_NO);
        for( i = 0; tbl[i] != USB_PDTBLEND; i += USB_EPL )
        {
            /* Pipe number */
            pipe = (uint16_t)(tbl[i + 0] & USB_CURPIPE);
            usb_cstd_pipe_init(ptr, pipe, tbl, i);
        }
        break;
    /* Peripheral pipe initialized */
    case USB_PERIPIPE:
        /* Current FIFO port Clear */
        usb_cstd_chg_curpipe(ptr, (uint16_t)USB_PIPE0, (uint16_t)USB_CUSE,  USB_NO);
        usb_cstd_chg_curpipe(ptr, (uint16_t)USB_PIPE0, (uint16_t)USB_D0USE, USB_NO);
        usb_cstd_chg_curpipe(ptr, (uint16_t)USB_PIPE0, (uint16_t)USB_D1USE, USB_NO);
        for( ep = USB_EP1; ep <= USB_MAX_EP_NO; ++ep )
        {
            for( dir = 0; dir <2; dir++ )
            {
                if( usb_gpstd_EpTblIndex[dir][ep] != USB_ERROR )
                {
                    i = (uint16_t)(USB_EPL * usb_gpstd_EpTblIndex[dir][ep]);
                    /* Pipe number */
                    pipe = (uint16_t)(tbl[i + 0] & USB_CURPIPE);
                    usb_cstd_pipe_init(ptr, pipe, tbl, i);
                }
            }
        }
        break;
    /* Clear Peripheral pipe register */
    case USB_CLRPIPE:
        /* Current FIFO port Clear */
        usb_cstd_chg_curpipe(ptr, (uint16_t)USB_PIPE0, (uint16_t)USB_CUSE,  USB_NO);
        usb_cstd_chg_curpipe(ptr, (uint16_t)USB_PIPE0, (uint16_t)USB_D0USE, USB_NO);
        usb_cstd_chg_curpipe(ptr, (uint16_t)USB_PIPE0, (uint16_t)USB_D1USE, USB_NO);
        for( ep = USB_EP1; ep <= USB_MAX_EP_NO; ++ep )
        {
            for( dir = 0; dir <2; dir++ )
            {
                if( usb_gpstd_EpTblIndex[dir][ep] != USB_ERROR )
                {
                    i = (uint16_t)(USB_EPL * usb_gpstd_EpTblIndex[dir][ep]);
                    /* Pipe number */
                    pipe = (uint16_t)(tbl[i + 0] & USB_CURPIPE);
                    usb_cstd_ClrPipeCnfg(ptr, pipe);
                }
            }
        }
        break;
    /* Pipe initialized */
    default:
        /* Current FIFO port clear */
        usb_cstd_chg_curpipe(ptr, (uint16_t)USB_PIPE0, (uint16_t)USB_CUSE, USB_NO);
        /* D0FIFO */
        buf = usb_creg_read_fifosel( ptr, USB_D0DMA );
        if( (buf & USB_CURPIPE) == pipe_number )
        {
            usb_cstd_chg_curpipe(ptr, (uint16_t)USB_PIPE0, (uint16_t)USB_D0USE, USB_NO);
        }
        /* D1FIFO */
        buf = usb_creg_read_fifosel( ptr, USB_D1DMA );
        if( (buf & USB_CURPIPE) == pipe_number )
        {
            usb_cstd_chg_curpipe(ptr, (uint16_t)USB_PIPE0, (uint16_t)USB_D1USE, USB_NO);
        }
        for( i = 0; tbl[i] != USB_PDTBLEND; i += USB_EPL )
        {
            /* Pipe number */
            pipe = (uint16_t)(tbl[i + 0] & USB_CURPIPE);
            if( pipe == pipe_number )
            {
                usb_cstd_pipe_init(ptr, pipe, tbl, i);
            }
        }
        break;
    }
}

/******************************************************************************
Function Name   : usb_cstd_pipe_init
Description     : Initialization of registers associated with specified pipe.
Arguments       : USB_UTR_t *ptr    : USB system internal structure. Selects channel.
                : uint16_t pipe     : Pipe Number
                : uint16_t *tbl     : ep table
                : uint16_t ofs      : ep table offset
Return value    : none
******************************************************************************/
void usb_cstd_pipe_init(USB_UTR_t *ptr, uint16_t pipe, uint16_t *tbl, uint16_t ofs)
{

    usb_gcstd_Pipe[ptr->ip][pipe] = (USB_UTR_t*)USB_NULL;

    /* Interrupt Disable */
    /* Ready         Int Disable */
    usb_creg_clr_brdyenb( ptr, pipe );

    /* NotReady      Int Disable */
    usb_creg_clr_nrdyenb( ptr, pipe );

    /* Empty/SizeErr Int Disable */
    usb_creg_clr_bempenb( ptr, pipe );

    /* PID=NAK & clear STALL */
    usb_cstd_ClrStall(ptr, pipe);
    
    /* PIPE Configuration */
    usb_creg_write_pipesel( ptr, pipe );

    if( USB_D0DMA == tbl[ofs + 5] )
    {
        tbl[ofs + 1] |= USB_BFREON;
    }

    usb_creg_write_pipecfg( ptr, tbl[ofs + 1]);

    usb_creg_write_pipebuf( ptr, tbl[ofs + 2] );
    usb_creg_write_pipemaxp( ptr, tbl[ofs + 3] );
    usb_creg_write_pipeperi( ptr, tbl[ofs + 4] );

    /* FIFO buffer DATA-PID initialized */
    usb_creg_write_pipesel( ptr, USB_PIPE0 );

    /* SQCLR */
    usb_creg_set_sqclr(ptr, pipe);
    /* ACLRM */
    usb_cstd_DoAclrm(ptr, pipe);
    /* CSSTS */
    usb_creg_set_csclr(ptr, pipe);
    
    /* Interrupt status clear */
    /* Ready         Int Clear */
    usb_creg_clr_sts_brdy( ptr, pipe );

    /* NotReady      Int Clear */
    usb_creg_clr_sts_nrdy( ptr, pipe );

    /* Empty/SizeErr Int Clear */
    usb_creg_clr_sts_bemp( ptr, pipe );
}/* eof usb_cstd_pipe_init() */

/******************************************************************************
Function Name   : usb_pstd_SetEpTblIndex
Description     : Set endpoint index in table (buffer) region based on config-
                : uration descriptor. In other words, set which endpoints to 
                : use based on specified configuration, 
Arguments       : uint16_t con_num : Configuration Number.
                : uint16_t int_num : Interface Number.
                : uint16_t alt_num : Alternate Setting.
Return value    : none
******************************************************************************/
void usb_pstd_SetEpTblIndex(uint16_t con_num, uint16_t int_num, uint16_t alt_num)
{
    uint8_t         *ptr;
    uint16_t        i, j, length, conf;
    uint16_t        start, numbers, ep;
    uint16_t    tbl_index;
    uint16_t    dir;

    conf = con_num;
    if( conf < (uint16_t)1 )
    {
        /* Address state */
        conf = (uint16_t)1;
    }

    /* Get Configuration descriptor table index */
    tbl_index = usb_pstd_get_confignum_to_tblindex( conf );

    /* Configuration descriptor */
    ptr = usb_gpstd_Driver.configtbl[tbl_index];
    i = *ptr;
    length = (uint16_t)(*(uint8_t*)((uint32_t)ptr + (uint32_t)3u));
    length = (uint16_t)(length << 8);
    length += (uint16_t)(*(uint8_t*)((uint32_t)ptr + (uint32_t)2u));
    ptr =(uint8_t*)((uint32_t)ptr + *ptr);
    start = 0;
    numbers = 0;
    j = 0;

    for(  ; i < length;  )
    {
        /* Descriptor type ? */
        switch(*(uint8_t*)((uint32_t)ptr + (uint32_t)1u) )
        {
        /* Interface */
        case USB_DT_INTERFACE:
            if((*(uint8_t*)((uint32_t)ptr + (uint32_t)2u) == int_num)
                && (*(uint8_t*)((uint32_t)ptr + (uint32_t)3u) == alt_num))
            {
                numbers = *(uint8_t*)((uint32_t)ptr + (uint32_t)4u);
            }
            else
            {
                start += *(uint8_t*)((uint32_t)ptr + (uint32_t)4u);
            }
            i += *ptr;
            ptr =(uint8_t*)((uint32_t)ptr + *ptr);
            break;
        /* Endpoint */
        case USB_DT_ENDPOINT:
            if( j < numbers )
            {
                ep = (uint16_t)*(uint8_t*)((uint32_t)ptr + (uint32_t)2u);
                if( USB_EP_IN == (ep & USB_EP_DIRMASK) )
                {
                    dir = 1;    /* IN */
                }
                else
                {
                    dir = 0;    /* OUT */
                }
                ep &= (uint16_t)0x0f;
                usb_gpstd_EpTblIndex[dir][ep] = (uint8_t)(start + j);
                ++j;
            }
            i += *ptr;
            ptr = (uint8_t*)((uint32_t)ptr + *ptr);
            break;
        /* Device */
        case USB_DT_DEVICE:
            /* Continue */
        /* Configuration */
        case USB_DT_CONFIGURATION:
            /* Continue */
        /* String */
        case USB_DT_STRING:
            /* Continue */
        /* Class, Vendor, else */
        default:
            i += *ptr;
            ptr = (uint8_t*)((uint32_t)ptr + *ptr);
            break;
        }
    }
}

/******************************************************************************
Function Name   : usb_pstd_ClearEpTblIndex
Description     : Clear Endpoint Index Table (buffer).
Arguments       : none
Return value    : none
******************************************************************************/
void usb_pstd_ClearEpTblIndex(void)
{
    uint16_t    i;

    for( i = 0; i <= USB_MAX_EP_NO; ++i )
    {
        /* Endpoint index table clear */
        usb_gpstd_EpTblIndex[0][i] = USB_ERROR;
        usb_gpstd_EpTblIndex[1][i] = USB_ERROR;
    }
}

/******************************************************************************
Function Name   : usb_pstd_GetConfigNum
Description     : Get number of possible configurations.
Arguments       : none
Return value    : uint16_t : Number of possible configurations.
                : (bNumConfigurations)
******************************************************************************/
uint16_t usb_pstd_GetConfigNum(void)
{
    /* Configuration Number */
    return (uint16_t)(usb_gpstd_Driver.devicetbl[USB_DEV_NUM_CONFIG]);
}

/******************************************************************************
Function Name   : usb_pstd_SetInterface3
Description     : Analyze a Set Interface command and request the process for 
                : the command. This is for a status stage of a control write 
                : where there is no data stage.
Arguments       : none
Return value    : none
******************************************************************************/
void usb_pstd_SetInterface3(USB_UTR_t *ptr)
{
    uint16_t    *table;
    uint16_t    conf;

    conf = usb_gpstd_ConfigNum;
    if( conf < (uint16_t)1 )
    {
        /* Address state */
        conf = (uint16_t)1;
    }

    /* Configured ? */
    if( (usb_pstd_ChkConfigured(ptr) == USB_YES) 
        && (usb_gpstd_ReqTypeRecip == USB_INTERFACE) )
    {
        if( (usb_gpstd_ReqIndex <= usb_pstd_GetInterfaceNum(usb_gpstd_ConfigNum)) && (usb_gpstd_ReqLength == 0) )
        {
            if( usb_gpstd_ReqValue <= usb_pstd_GetAlternateNum(usb_gpstd_ConfigNum, usb_gpstd_ReqIndex) )
            {
                usb_gpstd_AltNum[usb_gpstd_ReqIndex] = (uint16_t)(usb_gpstd_ReqValue & USB_ALT_SET);
                usb_cstd_SetBuf(ptr, (uint16_t)USB_PIPE0);
                usb_pstd_ClearEpTblIndex();
                /* Search endpoint setting */
                usb_pstd_SetEpTblIndex(usb_gpstd_ConfigNum, usb_gpstd_ReqIndex, usb_gpstd_AltNum[usb_gpstd_ReqIndex]);
                table = usb_gpstd_Driver.pipetbl[conf - 1];
                /* Set pipe configuration register */
                usb_pstd_SetPipeRegister(ptr, (uint16_t)USB_PERIPIPE, table);
            }
            else
            {
                /* Request error */
                usb_pstd_SetStallPipe0( ptr );
            }
        }
        else
        {
            /* Request error */
            usb_pstd_SetStallPipe0( ptr );
        }
    }
    else
    {
        /* Request error */
        usb_pstd_SetStallPipe0( ptr );
    }
}

/******************************************************************************
Function Name   : usb_pstd_GetAlternateNum
Description     : Get Alternate Setting Number
Arguments       : uint16_t con_num : Configuration Number
                : uint16_t int_num : Interface Number
Return value    : uint16_t : Value used to select this alternate
                : (bAlternateSetting)
******************************************************************************/
uint16_t usb_pstd_GetAlternateNum(uint16_t con_num, uint16_t int_num)
{
    uint16_t    i, conf;
    uint16_t    alt_num = 0;
    uint8_t     *ptr;
    uint16_t    length;
    uint16_t    tbl_index;

    conf = con_num;
    if( conf < (uint16_t)1 )
    {
        /* Address state */
        conf = (uint16_t)1;
    }

    /* Get Configuration descriptor table index */
    tbl_index = usb_pstd_get_confignum_to_tblindex( conf );

    ptr = usb_gpstd_Driver.configtbl[tbl_index];
    i = ptr[0];
    /* Interface descriptor[0] */
    ptr = (uint8_t*)((uint32_t)ptr + ptr[0]);
    length = (uint16_t)(*(uint8_t*)((uint32_t)  usb_gpstd_Driver.configtbl[tbl_index] + (uint16_t)2u));
    length |= (uint16_t)((uint16_t)(*(uint8_t*)((uint32_t)usb_gpstd_Driver.configtbl[tbl_index] + (uint16_t)3u)) << 8u);
    
    /* Search descriptor table size */
    for(  ; i < length;  )
    {
        /* Descriptor type ? */
        switch( ptr[1] )
        {
        /* Interface */
        case USB_DT_INTERFACE:
            if( int_num == ptr[2] )
            {
                /* Alternate number count */
                alt_num = (uint16_t)ptr[3];
            }
            i += ptr[0];
            /* Interface descriptor[0] */
            ptr =(uint8_t*)((uint32_t)ptr + ptr[0]);
            break;
        /* Device */
        case USB_DT_DEVICE:
            /* Continue */
        /* Configuration */
        case USB_DT_CONFIGURATION:
            /* Continue */
        /* String */
        case USB_DT_STRING:
            /* Continue */
        /* Endpoint */
        case USB_DT_ENDPOINT:
            /* Continue */
        /* Class, Vendor, else */
        default:
            i += ptr[0];
            /* Interface descriptor[0] */
            ptr =(uint8_t*)((uint32_t)ptr + ptr[0]);
            break;
        }
    }
    return alt_num;
}

/******************************************************************************
Function Name   : usb_pstd_StandReq4
Description     : The control read status stage of a standard request from host.
Arguments       : none
Return value    : none
******************************************************************************/
void usb_pstd_StandReq4(USB_UTR_t *ptr)
{
    switch( usb_gpstd_ReqRequest )
    {
        case USB_GET_STATUS:
            /* GetStatus4 */
            usb_cstd_SetBuf(ptr, (uint16_t)USB_PIPE0);
        break;
        case USB_GET_DESCRIPTOR:
            /* GetDescriptor4 */
            usb_cstd_SetBuf(ptr, (uint16_t)USB_PIPE0);
        break;
        case USB_GET_CONFIGURATION:
            /* GetConfiguration4 */
            usb_cstd_SetBuf(ptr, (uint16_t)USB_PIPE0);
        break;
        case USB_GET_INTERFACE:
            /* GetInterface4 */
            usb_cstd_SetBuf(ptr, (uint16_t)USB_PIPE0);
        break;
        case USB_SYNCH_FRAME:
            /* SynchFrame4 */
            usb_cstd_SetBuf(ptr, (uint16_t)USB_PIPE0);
        break;
        default:
            /* Set pipe USB_PID_STALL */
            usb_pstd_SetStallPipe0( ptr );
        break;
    }
    /* Control transfer stop(end) */
    usb_pstd_ControlEnd(ptr, (uint16_t)USB_CTRL_END);
}

/******************************************************************************
Function Name   : usb_pstd_StandReq5
Description     : The control write status stage of a standard request from host.
Arguments       : USB_UTR_t *ptr    : USB system internal structure.
Return value    : none
******************************************************************************/
void usb_pstd_StandReq5(USB_UTR_t *ptr)
{
    if( usb_gpstd_ReqRequest == USB_SET_DESCRIPTOR )
    {
        /* Set pipe PID_BUF */
        usb_cstd_SetBuf(ptr, (uint16_t)USB_PIPE0);
    }
    else
    {
        /* Set pipe USB_PID_STALL */
        usb_pstd_SetStallPipe0( ptr );
    }
    /* Control transfer stop(end) */
    usb_pstd_ControlEnd(ptr, (uint16_t)USB_CTRL_END);
}

/******************************************************************************
Function Name   : usb_pstd_SaveRequest
Description     : Save received USB command.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
Return value    : none
******************************************************************************/
void usb_pstd_SaveRequest(USB_UTR_t *ptr)
{
    uint16_t    buf;

    /* Valid clear */
    usb_preg_clr_sts_valid( ptr );
    buf = usb_creg_read_usbreq( ptr );

    usb_gpstd_ReqType      = (uint16_t)(buf & USB_BMREQUESTTYPE);
    usb_gpstd_ReqTypeType  = (uint16_t)(buf & USB_BMREQUESTTYPETYPE);
    usb_gpstd_ReqTypeRecip = (uint16_t)(buf & USB_BMREQUESTTYPERECIP);
    usb_gpstd_ReqRequest   = (uint16_t)(buf & USB_BREQUEST);

    usb_gpstd_ReqValue  = usb_creg_read_usbval( ptr );
    usb_gpstd_ReqIndex  = usb_creg_read_usbindx( ptr );
    usb_gpstd_ReqLength = usb_creg_read_usbleng( ptr );
} /* eof usb_pstd_SaveRequest() */

/******************************************************************************
Function Name   : usb_pstd_SuspendProcess
Description     : Perform a USB peripheral suspend.
Arguments       : none
Return value    : none
******************************************************************************/
void usb_pstd_SuspendProcess(USB_UTR_t *ptr)
{
    uint16_t    intsts0, buf;

    /* Resume interrupt enable */
    usb_preg_set_enb_rsme( ptr );

    intsts0 = usb_creg_read_intsts( ptr );

      buf = usb_creg_read_syssts( ptr, USB_PORT0 );

    if(((intsts0 & USB_DS_SUSP) != (uint16_t)0) && ((buf & USB_LNST) == USB_FS_JSTS))
    {
        /* Suspend */
        usb_cstd_StopClock(ptr);
        usb_pstd_SuspendFunction(ptr);
        /* Callback */
        (*usb_gpstd_Driver.devsuspend)(ptr, (uint16_t)usb_gpstd_RemoteWakeup, (uint16_t)USB_NO_ARG);
    }
    /* --- SUSPEND -> RESUME --- */
    else
    {
        /* RESM status clear */
        usb_preg_clr_sts_resm( ptr );
        /* RESM interrupt disable */
        usb_preg_clr_enb_rsme( ptr );
    }
}

/******************************************************************************
Function Name   : usb_pstd_SuspendFunction
Description     : Processing for suspend signal detection.
Arguments       : USB_UTR_t *ptr    : USB system internal structure.
Return value    : none
******************************************************************************/
void usb_pstd_SuspendFunction(USB_UTR_t *ptr)
{
}

/******************************************************************************
Function Name   : usb_pstd_BusReset
Description     : A USB bus reset was issued by the host. Execute relevant pro-
                : cessing.
Arguments       : USB_UTR_t *ptr    : USB system internal structure.
Return value    : none
******************************************************************************/
void usb_pstd_BusReset(USB_UTR_t *ptr)
{
    uint16_t    connect_info;

    /* Bus Reset */
    usb_pstd_BusresetFunction(ptr);

    /* Memory clear */
    usb_pstd_ClearMem();
    connect_info = usb_cstd_PortSpeed(ptr, (uint16_t)USB_PORT0);
    /* Callback */
#ifdef USB_PERI_BC_ENABLE
    (*usb_gpstd_Driver.devdefault)(ptr, connect_info, (uint16_t)g_usb_bc_detect);
#else
    (*usb_gpstd_Driver.devdefault)(ptr, connect_info, (uint16_t)USB_NO_ARG);
#endif
    /* DCP configuration register  (0x5C) */
    usb_creg_write_dcpcfg( ptr, 0 );
    /* DCP maxpacket size register (0x5E) */
    usb_creg_write_dcpmxps( ptr, usb_gpstd_Driver.devicetbl[USB_DEV_MAX_PKT_SIZE]);
}

/******************************************************************************
Function Name   : usb_creg_write_dcpmxps
Description     : Specified data is written to DCPMAXP register.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  data  : The value to write.
Return value    : none
******************************************************************************/
void    usb_creg_write_dcpmxps( USB_UTR_t *ptr, uint16_t data )
{
    ptr->ipp->DCPMAXP.WORD = data;
} /* eof usb_creg_write_dcpmxps() */

/******************************************************************************
Function Name   : usb_pstd_ClearMem
Description     : Initialize global variables defined for peripheral mode.
Arguments       : none
Return value    : none
******************************************************************************/
void usb_pstd_ClearMem(void)
{
    /* Configuration number */
    usb_gpstd_ConfigNum = 0;
    /* Remote wakeup enable flag */
    usb_gpstd_RemoteWakeup = USB_NO;
    usb_gcstd_XckeMode = USB_NO;
    /* Alternate setting clear */
    usb_pstd_ClearAlt();
}

/******************************************************************************
Function Name   : usb_pstd_BusresetFunction
Description     : Processing for USB bus reset detection.
Arguments       : USB_UTR_t *ptr    : USB system internal structure.
Return value    : none
******************************************************************************/
void usb_pstd_BusresetFunction(USB_UTR_t *ptr)
{
}

/******************************************************************************
Function Name   : usb_pstd_ChkVbsts
Description     : Return the VBUS status.
Arguments       : USB_UTR_t *ptr    : USB system internal structure.
Return          : uint16_t connection status(ATTACH/DETACH)
******************************************************************************/
uint16_t usb_pstd_ChkVbsts(USB_UTR_t *ptr)
{
    uint16_t    buf1, buf2, buf3;
    uint16_t    connect_info;

    /* VBUS chattering cut */
    do
    {
        buf1 = usb_creg_read_intsts( ptr );
        usb_cpu_Delay1us((uint16_t)10);
        buf2 = usb_creg_read_intsts( ptr );
        usb_cpu_Delay1us((uint16_t)10);
        buf3 = usb_creg_read_intsts( ptr );
    }
    while( ((buf1 & USB_VBSTS) != (buf2 & USB_VBSTS))
          || ((buf2 & USB_VBSTS) != (buf3 & USB_VBSTS)) );

    /* VBUS status judge */
    if( (buf1 & USB_VBSTS) != (uint16_t)0 )
    {
        /* Attach */
        connect_info = USB_ATTACH;
    }
    else
    {
        /* Detach */
        connect_info = USB_DETACH;
    }
    return connect_info;
}

/******************************************************************************
Function Name   : usb_pstd_ResumeProcess
Description     : Set USB registers to implement resume processing.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
Return value    : none
******************************************************************************/
void usb_pstd_ResumeProcess(USB_UTR_t *ptr)
{
    /* RESM status clear */
    usb_preg_clr_sts_resm( ptr );

    /* RESM interrupt disable */
    usb_preg_clr_enb_rsme( ptr );

} /* eof usb_pstd_ResumeProcess() */

/******************************************************************************
Function Name   : usb_pstd_NrdyPipe
Description     : Execute appropriate processing for the PIPE for which a NRDY 
                : interrupt occurred.
Arguments       : uint16_t bitsts : NRDYSTS register & NRDYENB register.
Return value    : none
******************************************************************************/
void usb_pstd_NrdyPipe(USB_UTR_t *ptr, uint16_t bitsts)
{
    /* The function for peripheral driver is created here. */
    if( (bitsts & USB_NRDY0) == USB_NRDY0 )
    {
    }
    else
    {
        /* Nrdy Pipe interrupt */
        usb_cstd_NrdyPipe(ptr, bitsts);
    }
}

/******************************************************************************
Function Name   : usb_cstd_NrdyPipe
Description     : Search for PIPE No. that occurred NRDY interrupt, and execute 
                  the process for PIPE when NRDY interrupt occurred
Arguments       : USB_UTR_t *ptr
                : uint16_t bitsts       ; NRDYSTS Register & NRDYENB Register
Return value    : none
******************************************************************************/
void usb_cstd_NrdyPipe(USB_UTR_t *ptr, uint16_t bitsts)
{
/* PERI spec                                                            */
/*  Transmitting pipe                                                   */
/* @5       a) only NRDY                                                */
/* @1       b) NRDY+OVRN    (Isochronous)                               */
/*  Receive pipe                                                        */
/* @5       a) only NRDY                                                */
/* @1       b) NRDY+OVRN    (Isochronous)                               */
/* @2       c) only NRDY    (interval error of isochronous)             */
/* HOST spec                                                            */
/*  Transmitting pipe                                                   */
/* @1       a) NRDY+OVRN    (Isochronous)                               */
/* @4       b) NRDY+NAK     (Ignore)                                    */
/* @3       c) NRDY+STALL   (Receive STALL)                             */
/*  Receive pipe                                                        */
/* @1       a) NRDY+OVRN    (Isochronous)                               */
/* @4       b) NRDY+NAK     (Ignore)                                    */
/* @2       c) NRDY         (Ignore of isochronous)                     */
/* @2       d) NRDY         (CRC error of isochronous)                  */
/* @3       e) NRDY+STALL   (Receive STALL)                             */

    uint16_t        buffer, i;

    for( i = USB_MIN_PIPE_NO; i <= USB_MAX_PIPE_NO; i++ )
    {
        if( (bitsts & USB_BITSET(i)) != 0 )
        {
            /* Interrupt check */
            if( usb_gcstd_Pipe[ptr->ip][i] != USB_NULL )
            {
                if( usb_cstd_GetPipeType(ptr, i) == USB_ISO )
                {
                    /* Wait for About 60ns */
                    buffer = usb_creg_read_frmnum( ptr );
                    if( (buffer & USB_OVRN) == USB_OVRN )
                    {
                        /* @1 */
                        /* End of data transfer */
                        usb_cstd_ForcedTermination(ptr, i, (uint16_t)USB_DATA_OVR);
                        //SCI_printf("###ISO OVRN %d\n", usb_gcstd_DataCnt[ptr->ip][i]);
                    }
                    else
                    {
                        /* @2 */
                        /* End of data transfer */
                        usb_cstd_ForcedTermination(ptr, i, (uint16_t)USB_DATA_ERR);
                    }
                }
                else
                {
                    usb_cstd_nrdy_endprocess( ptr, i );
                }
            }
        }
    }
}

/******************************************************************************
Function Name   : usb_cstd_nrdy_endprocess
Description     : NRDY interrupt processing. (Forced termination of data trans-
                : mission and reception of specified pipe.)
Arguments       : USB_UTR_t *ptr       : USB system internal structure. Selects channel.
                : uint16_t  pipe        : Pipe No
Return value    : none
Note            : none
******************************************************************************/
void    usb_cstd_nrdy_endprocess( USB_UTR_t *ptr, uint16_t pipe )
{
    if( usb_cstd_is_host_mode(ptr) == USB_YES )
    {
    }
}/* eof usb_cstd_nrdy_endprocess() */

/******************************************************************************
Function Name   : usb_pstd_BempPipe
Description     : Execute data transfer for the PIPE for which a BEMP interrupt 
                : occurred.
Arguments       : uint16_t bitsts : BEMPSTS register & BEMPENB register.
Return value    : none
******************************************************************************/
void usb_pstd_BempPipe(USB_UTR_t *ptr, uint16_t bitsts)
{
    /* When operating by the peripheral function, usb_cstd_bemp_pipe() is executed with PIPEx request because */
    /* two BEMP messages are issued even when the demand of PIPE0 and PIPEx has been generated at the same time. */
    if( (bitsts & USB_BEMP0) == USB_BEMP0 )
    {
        switch( usb_cstd_write_data( ptr, USB_PIPE0, USB_CUSE ) )
        {
            /* End of data write (not null) */
            case USB_WRITEEND:
                /* Continue */
            /* End of data write */
            case USB_WRITESHRT:
                /* Enable empty interrupt */
                usb_creg_clr_bempenb(ptr, (uint16_t)USB_PIPE0);
            break;
            /* Continue of data write */
            case USB_WRITING:
                /* PID = BUF */
                usb_cstd_SetBuf(ptr, (uint16_t)USB_PIPE0);
            break;
            /* FIFO access error */
            case USB_FIFOERROR:
                //SCI_printf("### FIFO access error \n");
                /* Control transfer stop(end) */
                usb_pstd_ControlEnd(ptr, (uint16_t)USB_DATA_ERR);
            break;
            default:
            break;
        }
    }
    else
    {
        /* BEMP interrupt */
        usb_cstd_BempPipe(ptr, bitsts);
    }
}

/******************************************************************************
Function Name   : usb_cstd_BempPipe
Description     : Search for PIPE No. that BEMP interrupt occurred, and complete data transmission for the PIPE
Arguments       : USB_UTR_t *ptr
                : uint16_t bitsts       ; BEMPSTS Register & BEMPENB Register
Return value    : none
******************************************************************************/
void usb_cstd_BempPipe(USB_UTR_t *ptr, uint16_t bitsts)
{
    uint16_t        buffer, i;
    uint16_t        useport;

    for( i = USB_MIN_PIPE_NO; i <= USB_PIPE5; i++ )
    {
        if( (bitsts & USB_BITSET(i)) != 0 )
        {
            /* Interrupt check */
            if( usb_gcstd_Pipe[ptr->ip][i] != USB_NULL )
            {
                buffer = usb_cstd_GetPid(ptr, i);
                /* MAX packet size error ? */
                if( (buffer & USB_PID_STALL) == USB_PID_STALL )
                {
                    //SCI_printf("### STALL Pipe %d\n", i);
                    usb_cstd_ForcedTermination(ptr, i, (uint16_t)USB_DATA_STALL);
                }
                else
                {
                    if( (usb_creg_read_pipectr( ptr, i ) & USB_INBUFM) != USB_INBUFM )
                    {
                        /* Pipe number to FIFO port select */
                        useport = usb_cstd_Pipe2Fport(ptr, i);
                        if( useport == USB_D0DMA )
                        {
                            usb_creg_clr_sts_bemp( ptr, i );
                        }
                        /* End of data transfer */
                        usb_cstd_DataEnd(ptr, i, (uint16_t)USB_DATA_NONE);
                    }
                }
            }
        }
    }
    for( i = USB_PIPE6; i <= USB_MAX_PIPE_NO; i++ )
    {
        /* Interrupt check */
        if( (bitsts & USB_BITSET(i)) != 0 )
        {
            if( usb_gcstd_Pipe[ptr->ip][i] != USB_NULL )
            {
                buffer = usb_cstd_GetPid(ptr, i);
                /* MAX packet size error ? */
                if( (buffer & USB_PID_STALL) == USB_PID_STALL )
                {
                    //SCI_printf("### STALL Pipe %d\n", i);
                    usb_cstd_ForcedTermination(ptr, i, (uint16_t)USB_DATA_STALL);
                }
                else
                {
                    /* End of data transfer */
                    usb_cstd_DataEnd(ptr, i, (uint16_t)USB_DATA_NONE);
                }
            }
        }
    }
}

/******************************************************************************
Function Name   : usb_cstd_DataEnd
Description     : Set USB registers as appropriate after data transmission/re-
                : ception, and call the callback function as transmission/recep-
                : tion is complete.
Arguments       : uint16_t pipe     : Pipe no.
                : uint16_t status   : Transfer status type.
Return value    : none
******************************************************************************/
void usb_cstd_DataEnd(USB_UTR_t *ptr, uint16_t pipe, uint16_t status)
{
    uint16_t    useport;

    /* PID = NAK */
    /* Set NAK */
    usb_cstd_SelectNak(ptr, pipe);
    /* Pipe number to FIFO port select */
    useport = usb_cstd_Pipe2Fport(ptr, pipe);

    /* Disable Interrupt */
    /* Disable Ready Interrupt */
    usb_creg_clr_brdyenb(ptr, pipe);
    /* Disable Not Ready Interrupt */
    usb_creg_clr_nrdyenb(ptr, pipe);
    /* Disable Empty Interrupt */
    usb_creg_clr_bempenb(ptr, pipe);

    /* Disable Transaction count */
    usb_cstd_ClrTransactionCounter(ptr, pipe);

    /* Check use FIFO */
    switch( useport )
    {
    /* CFIFO use */
    case USB_CUSE:
        break;
    /* D0FIFO use */
    case USB_D0USE:
        break;

    /* D0FIFO DMA */
    case USB_D0DMA:
        /* DMA buffer clear mode clear */
        usb_creg_clr_dclrm( ptr, USB_D0DMA );
        if(ptr -> ip == USB_USBIP_0)
        {
            usb_creg_set_mbw( ptr, USB_D0DMA, USB0_D0FIFO_MBW );
        }
        else if (ptr -> ip == USB_USBIP_1)
        {
            usb_creg_set_mbw( ptr, USB_D0DMA, USB1_D0FIFO_MBW );
        }
        usb_creg_write_dmacfg( ptr, USB_D0DMA, USB_CPU_ADR_RD_WR );
        break;

    /* D1FIFO use */
    case USB_D1USE:
        break;

    /* D1FIFO DMA */
    case USB_D1DMA:
        /* continue */

    default:
        break;
    }

    /* Call Back */
    if( usb_gcstd_Pipe[ptr->ip][pipe] != USB_NULL )
    {
        /* Check PIPE TYPE */
        if( usb_cstd_GetPipeType(ptr, pipe) != USB_ISO )
        {
            /* Transfer information set */
            usb_gcstd_Pipe[ptr->ip][pipe]->tranlen  = usb_gcstd_DataCnt[ptr->ip][pipe];
            usb_gcstd_Pipe[ptr->ip][pipe]->status   = status;
            usb_gcstd_Pipe[ptr->ip][pipe]->pipectr  = usb_creg_read_pipectr(ptr, pipe);
            usb_gcstd_Pipe[ptr->ip][pipe]->errcnt   = 0;

            usb_gcstd_Pipe[ptr->ip][pipe]->ipp  = ptr->ipp;
            usb_gcstd_Pipe[ptr->ip][pipe]->ip   = ptr->ip;

            (usb_gcstd_Pipe[ptr->ip][pipe]->complete)(usb_gcstd_Pipe[ptr->ip][pipe], 0, 0);
            usb_gcstd_Pipe[ptr->ip][pipe] = (USB_UTR_t*)USB_NULL;
        }
        else
        {
            /* Transfer information set */
            usb_gcstd_Pipe[ptr->ip][pipe]->tranlen  = usb_gcstd_DataCnt[ptr->ip][pipe];
            usb_gcstd_Pipe[ptr->ip][pipe]->pipectr  = usb_creg_read_pipectr(ptr, pipe);
            usb_gcstd_Pipe[ptr->ip][pipe]->errcnt   = 0;

            usb_gcstd_Pipe[ptr->ip][pipe]->ipp  = ptr->ipp;
            usb_gcstd_Pipe[ptr->ip][pipe]->ip   = ptr->ip;

            /* Data Transfer (restart) */
            if( usb_cstd_GetPipeDir(ptr, pipe) == USB_BUF2FIFO )
            {
                /* OUT Transfer */
                usb_gcstd_Pipe[ptr->ip][pipe]->status   = USB_DATA_WRITING;
                (usb_gcstd_Pipe[ptr->ip][pipe]->complete)(usb_gcstd_Pipe[ptr->ip][pipe], 0, 0);
            }
            else
            {
                /* IN Transfer */
                usb_gcstd_Pipe[ptr->ip][pipe]->status   = USB_DATA_READING;
                (usb_gcstd_Pipe[ptr->ip][pipe]->complete)(usb_gcstd_Pipe[ptr->ip][pipe], 0, 0);
            }
        }
    }
}

/******************************************************************************
Function Name   : usb_pstd_BrdyPipe
Description     : Execute data transfer for the PIPE for which a BRDY interrupt 
                : occurred.
Arguments       : uint16_t bitsts : BRDYSTS register & BRDYENB register.
Return value    : none
******************************************************************************/
void usb_pstd_BrdyPipe(USB_UTR_t *ptr, uint16_t bitsts)
{
    /* When operating by the peripheral function, usb_cstd_brdy_pipe() is executed with PIPEx request because */
    /* two BRDY messages are issued even when the demand of PIPE0 and PIPEx has been generated at the same time. */
    if( (bitsts & USB_BRDY0) == USB_BRDY0 )
    {
        switch( usb_cstd_read_data( ptr, USB_PIPE0, USB_CUSE ) )
        {
            /* End of data read */
            case USB_READEND:
                /* Continue */
            /* End of data read */
            case USB_READSHRT:
                usb_creg_clr_brdyenb(ptr, (uint16_t)USB_PIPE0);
            break;
            /* Continue of data read */
            case USB_READING:
                /* PID = BUF */
                usb_cstd_SetBuf(ptr, (uint16_t)USB_PIPE0);
            break;
            /* FIFO access error */
            case USB_READOVER:
                //SCI_printf("### Receive data over PIPE0 \n");
                /* Clear BVAL */
                usb_creg_set_bclr( ptr, USB_CUSE );
                /* Control transfer stop(end) */
                usb_pstd_ControlEnd(ptr, (uint16_t)USB_DATA_OVR);
            break;
            /* FIFO access error */
            case USB_FIFOERROR:
                //SCI_printf("### FIFO access error \n");
                /* Control transfer stop(end) */
                usb_pstd_ControlEnd(ptr, (uint16_t)USB_DATA_ERR);
            break;
            default:
            break;
        }
    }
    else
    {
        /* not PIPE0 */
        usb_cstd_BrdyPipe(ptr, bitsts);
    }
}


/******************************************************************************
Function Name   : usb_cstd_BrdyPipe
Description     : Search for the PIPE No. that BRDY interrupt occurred, and 
                  request data transmission/reception from the PIPE
Arguments       : USB_UTR_t *ptr
                : uint16_t bitsts       ; BRDYSTS Register & BRDYENB Register
Return value    : none
******************************************************************************/
void usb_cstd_BrdyPipe(USB_UTR_t *ptr, uint16_t bitsts)
{
    usb_cstd_brdy_pipe(ptr,  bitsts);//modify
}

/******************************************************************************
Function Name   : usb_cstd_brdy_pipe
Description     : Search for the PIPE No. that BRDY interrupt occurred, and 
                  request data transmission/reception from the PIPE
Arguments       : USB_UTR_t *ptr
                : uint16_t bitsts       ; BRDYSTS Register & BRDYENB Register
Return value    : none
******************************************************************************/
void usb_cstd_brdy_pipe(USB_UTR_t *ptr, uint16_t bitsts)
{
    uint16_t        useport;
    uint16_t        i;
    uint16_t ip;

    uint16_t        buffer;
    uint16_t maxps;
    uint16_t set_dtc_brock_cnt;
    uint16_t trans_dtc_block_cnt;

    ip = ptr->ip;
    maxps = usb_gcstd_Dma0Fifo[ip];
    for( i = USB_PIPE1; i <= USB_MAX_PIPE_NO; i++ )
    {
        if( (bitsts & USB_BITSET(i)) != 0 )
        {
            /* Interrupt check */
            usb_creg_clr_sts_bemp( ptr, i );

            if( usb_gcstd_Pipe[ip][i] != USB_NULL )
            {
                /* Pipe number to FIFO port select */
                useport = usb_cstd_Pipe2Fport(ptr, i);
                if( useport == USB_D0DMA )
                {
                    /* DMA Transfer request disable */
                    usb_creg_clr_dreqe( ptr, USB_D0DMA );

                    /* DMA stop */
                    usb_cpu_d0fifo_stop_dma(ptr);

                    /* Changes FIFO port by the pipe. */
                    buffer = usb_cstd_is_set_frdy(ptr, i, useport, USB_NO);

                    set_dtc_brock_cnt = (uint16_t)((usb_gcstd_DataCnt[ip][usb_gcstd_Dma0Pipe[ip]] -1)
                        / usb_gcstd_Dma0Fifo[ip]) +1;

                    trans_dtc_block_cnt = usb_cpu_get_dtc_block_count(ptr);
                    /* Get D0fifo Receive Data Length */
                    usb_gcstd_Dma0Size[ip]
                        = (uint32_t)(buffer & USB_DTLN) + (set_dtc_brock_cnt - (trans_dtc_block_cnt + 1)) * maxps;

                    /* Check data count */
                    if( usb_gcstd_Dma0Size[ip] == usb_gcstd_DataCnt[ptr->ip][i] )
                    {
                        usb_gcstd_DataCnt[ip][i] = 0;
                        /* End of data transfer */
                        usb_cstd_DataEnd(ptr, i, (uint16_t)USB_DATA_OK);
                    }
                    else if( usb_gcstd_Dma0Size[ip] > usb_gcstd_DataCnt[ip][i] )
                    {
                        /* D0FIFO access DMA stop */
                        usb_cstd_D0fifoStopUsb(ptr);
                        /* End of data transfer */
                        usb_cstd_DataEnd(ptr, i, (uint16_t)USB_DATA_OVR);
                    }
                    else
                    {
                        /* D0FIFO access DMA stop */
                        usb_cstd_D0fifoStopUsb(ptr);
                        /* End of data transfer */
                        usb_cstd_DataEnd(ptr, i, (uint16_t)USB_DATA_SHT);
                    }
                    /* Set BCLR */
                    usb_creg_set_bclr( ptr, USB_D0DMA );
                }
                else
                {
                    if( usb_cstd_GetPipeDir(ptr, i) == USB_BUF2FIFO )
                    {
                        /* Buffer to FIFO data write */
                        usb_cstd_Buf2Fifo(ptr, i, useport);
                    }
                    else
                    {
                        /* FIFO to Buffer data read */
                        usb_cstd_Fifo2Buf(ptr, i, useport);
                    }
                }
            }
        }
    }
}/* eof usb_cstd_brdy_pipe() */

/******************************************************************************
Function Name   : usb_cpu_get_dtc_block_count
Description     : Get DTC Transfer count reg B(CRB).
Arguments       : USB_UTR_t *ptr        : USB internal structure. Selects USB channel. 
Return value    : DTC Transfer count reg B(CRB)
******************************************************************************/
uint16_t usb_cpu_get_dtc_block_count(USB_UTR_t *ptr)
{
    uint16_t value;
    uint16_t status_reg = 0;
    
    /* Wait Complete DTC Transfer */
    do
    {
        status_reg = DTC.DTCSTS.WORD;
    }
    while( 0 != ( status_reg & 0x8000 ) );  /* DTC is not active */
 
    /* Read DTC transfer count (CRB) */
    value = (uint16_t)(usb_dtc_transfer_data[ptr->ip].lw4 & 0xffff);
    
    return value;
}

/******************************************************************************
Function Name   : usb_cstd_Fifo2Buf
Description     : Request readout from USB FIFO to buffer and process depending
                : on status; read complete or reading.
Arguments       : USB_UTR_t *ptr : USB internal structure. Selects e.g. channel.
                : uint16_t pipe  : Pipe no.
Return value    : none
******************************************************************************/
void usb_cstd_Fifo2Buf(USB_UTR_t *ptr, uint16_t pipe, uint16_t useport)
{
    uint16_t    end_flag;

    end_flag = USB_ERROR;

    end_flag = usb_cstd_read_data( ptr, pipe, useport );

    /* Check FIFO access sequence */
    switch( end_flag )
    {
    case USB_READING:
        /* Continue of data read */
        break;
        
    case USB_READEND:
        /* End of data read */
        usb_cstd_DataEnd(ptr, pipe, (uint16_t)USB_DATA_OK);
        break;
        
    case USB_READSHRT:
        /* End of data read */
        usb_cstd_DataEnd(ptr, pipe, (uint16_t)USB_DATA_SHT);
        break;
        
    case USB_READOVER:
        /* Buffer over */
        //SCI_printf("### Receive data over PIPE%d\n",pipe);
        usb_cstd_ForcedTermination(ptr, pipe, (uint16_t)USB_DATA_OVR);
        break;
        
    case USB_FIFOERROR:
        /* FIFO access error */
        //SCI_printf("### FIFO access error \n");
        usb_cstd_ForcedTermination(ptr, pipe, (uint16_t)USB_DATA_ERR);
        break;
        
    default:
        usb_cstd_ForcedTermination(ptr, pipe, (uint16_t)USB_DATA_ERR);
        break;
    }
}

/******************************************************************************
Function Name   : usb_cstd_read_data
Description     : Request to read data from USB FIFO, and manage the size of 
                : the data read.
Arguments       : uint16_t pipe            : Pipe no.
Return value    : uint16_t end_flag
******************************************************************************/
uint16_t usb_cstd_read_data(USB_UTR_t *ptr, uint16_t pipe, uint16_t pipemode)
{
    uint16_t    count, buffer, mxps, dtln;
    uint16_t    end_flag;

    /* Changes FIFO port by the pipe. */
    buffer = usb_cstd_is_set_frdy(ptr, pipe, (uint16_t)pipemode, USB_NO);
    if( buffer == USB_FIFOERROR )
    {
//#ifndef ISO_USE
        /* FIFO access error */
        return (USB_FIFOERROR);
//#endif
    }
    dtln = (uint16_t)(buffer & USB_DTLN);
    /* Max Packet Size */
    mxps = usb_cstd_GetMaxPacketSize(ptr, pipe);

    if( usb_gcstd_DataCnt[ptr->ip][pipe] < dtln )
    {
        /* Buffer Over ? */
        end_flag = USB_READOVER;
        /* Set NAK */
        usb_cstd_SetNak(ptr, pipe);
        count = (uint16_t)usb_gcstd_DataCnt[ptr->ip][pipe];
        usb_gcstd_DataCnt[ptr->ip][pipe] = dtln;
    }
    else if( usb_gcstd_DataCnt[ptr->ip][pipe] == dtln )
    {
        /* Just Receive Size */
        count = dtln;
        if( (pipe == USB_PIPE0) && ((dtln % mxps) == 0) )
        {
            /* Just Receive Size */
            if( usb_cstd_is_host_mode(ptr) == USB_NO )
            {
                /* Peripheral Function */
                end_flag = USB_READING;
            }
            else
            {
                /* Host Function */
                end_flag = USB_READEND;
                /* Set NAK */
                usb_cstd_SelectNak(ptr, pipe);
            }
        }
        else
        {
            end_flag = USB_READEND;
            /* Set NAK */
            usb_cstd_SelectNak(ptr, pipe);
        }
    }
    else
    {
        /* Continus Receive data */
        count = dtln;
        end_flag = USB_READING;
        if( count == 0 )
        {
            /* Null Packet receive */
            end_flag = USB_READSHRT;
            /* Select NAK */
            usb_cstd_SelectNak(ptr, pipe);
        }
        if( (count % mxps) != 0 )
        {
            /* Null Packet receive */
            end_flag = USB_READSHRT;
            /* Select NAK */
            usb_cstd_SelectNak(ptr, pipe);
        }
    }

    if( dtln == 0 )
    {
        /* 0 length packet */
        /* Clear BVAL */
        usb_creg_set_bclr( ptr, pipemode );
    }
    else
    {
        usb_gcstd_DataPtr[ptr->ip][pipe] = usb_cstd_read_fifo( ptr, count, pipemode, usb_gcstd_DataPtr[ptr->ip][pipe] );
    }
    usb_gcstd_DataCnt[ptr->ip][pipe] -= count;

    /* End or Err or Continue */
    return (end_flag);
}

/******************************************************************************
Function Name   : usb_cstd_read_fifo
Description     : Read specified buffer size from the USB FIFO.
Arguments       : USB_UTR_t *ptr        : USB system internal structure. Selects channel.
                : uint16_t  count       : Read size.
                : uint16_t  pipemode    : The mode of CPU/DMA(D0)/DMA(D1).
                : uint16_t  *write_p    : Address of buffer to store the read data.
Return value    : Pointer to a buffer that contains the data to be read next.
******************************************************************************/
uint8_t *usb_cstd_read_fifo( USB_UTR_t *ptr, uint16_t count, uint16_t pipemode, uint8_t *read_p )
{
    uint16_t    even;
    uint32_t    odd_byte_data_temp;

    for( even = (uint16_t)(count >> 1); (even != 0); --even )
    {
        /* 16bit FIFO access */
        *(uint16_t *)read_p= usb_creg_read_fifo16( ptr, pipemode );

        /* Renewal read pointer */
        read_p += sizeof( uint16_t );
    }
    if( (count & (uint16_t)0x0001) != 0 )
    {
         /* 16bit FIFO access */
        odd_byte_data_temp = usb_creg_read_fifo16( ptr, pipemode );
        *read_p = (uint8_t)( odd_byte_data_temp & 0x00ff);
        /* Renewal read pointer */
        read_p += sizeof( uint8_t );
    }
    return read_p;
}/* eof usb_cstd_read_fifo() */

/******************************************************************************
Function Name   : usb_creg_read_fifo16
Description     : Data is read from the specified pipemode's FIFO register, 16-bits 
                : wide, corresponding to the specified PIPEMODE.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  pipemode  : CUSE/D0DMA/D1DMA
Return value    : CFIFO/D0FIFO/D1FIFO content (16-bit)
******************************************************************************/
uint16_t    usb_creg_read_fifo16( USB_UTR_t *ptr, uint16_t pipemode )
{
    uint16_t    data;

        switch( pipemode )
        {
            case    USB_CUSE:
                data = ptr->ipp->CFIFO.WORD;
                break;
            case    USB_D0USE:
            case    USB_D0DMA:
                data = ptr->ipp->D0FIFO.WORD;
                break;
            case    USB_D1USE:
            case    USB_D1DMA:
                data = ptr->ipp->D1FIFO.WORD;
                break;
            default:
                USB_DEBUG_HOOK( USB_DEBUG_HOOK_STD | USB_DEBUG_HOOK_CODE4 );
                break;
        }

    return data;
} /* eof usb_creg_read_fifo16() */


/******************************************************************************
Function Name   : cdc_connect_wait
Description     : Hid device conntect process.
Arguments       : none
Return value    : LCD update request(USB_YES/USB_NO)
******************************************************************************/
uint16_t cdc_connect_wait( void )
{

    uint16_t    event;
    uint16_t    lcd_update = USB_NO;

    event = cdc_event_get();                        /* Get event code */
    if( EVENT_CONFIGERD == event )                  /* Check event code */
    {
        lcd_update = USB_YES;

        cdc_dev_info.state = STATE_DATA_TRANSFER;   /* Set Application status  */
        cdc_event_set( EVENT_USB_READ_START );      /* Set Event(CDC class request start)  */
    }

    return lcd_update;

}   /* eof cdc_connect_wait() */

/******************************************************************************
Function Name   : cdc_event_set
Description     : Set event.
Arguments       : uint16_t  event  : Event code
Return value    : none
******************************************************************************/
void cdc_event_set( uint16_t event )
{

    if( cdc_dev_info.event_cnt < EVENT_MAX )    /* Check max event count */
    {
        cdc_dev_info.event[cdc_dev_info.event_cnt] = event; /* Set event */
        cdc_dev_info.event_cnt++;               /* Update event count */
    }
    else
    {
        USB_DEBUG_HOOK( USB_DEBUG_HOOK_APL | USB_DEBUG_HOOK_CODE2 );
    }

}   /* eof cdc_event_set() */

/******************************************************************************
Function Name   : cdc_event_get
Description     : Get event.
Arguments       : none
Return value    : none
******************************************************************************/
uint16_t cdc_event_get( void )
{

    uint16_t    event = EVENT_NONE;
    uint8_t     i;

    if( cdc_dev_info.event_cnt > 0 )                    /* Check event count */
    {
        event = cdc_dev_info.event[0];                  /* Get event */
        cdc_dev_info.event_cnt--;                       /* Update event count */
        for( i = 0; i < cdc_dev_info.event_cnt; i++ )   /* Shife event buffer */
        {
            cdc_dev_info.event[i] = cdc_dev_info.event[(i + 1)];
        }
    }
    return event;

}   /* eof cdc_event_get() */

/******************************************************************************
Function Name   : cdc_detach_device
Description     : Detach process
Arguments       : none
Return          : none
******************************************************************************/
void    cdc_detach_device( void )
{

    R_usb_pstd_TransferEnd( &cdc_utr, USB_PCDC_USE_PIPE_IN, USB_DATA_STOP );
    R_usb_pstd_TransferEnd( &cdc_utr, USB_PCDC_USE_PIPE_OUT, USB_DATA_STOP );
    R_usb_pstd_TransferEnd( &cdc_utr, USB_PCDC_USE_PIPE_STATUS, USB_DATA_STOP );

    /* Clear data for USB TX and RX */
    memset( cdc_trans_data, 0, CDC_DATA_LEN );
    cdc_dev_info.state = STATE_ATTACH;      /* Set Application status  */

}   /* eof cdc_detach_device() */

/******************************************************************************
Function Name   : R_usb_pstd_TransferEnd
Description     : Force termination of data transfer of specified pipe. Request 
                : PCD to force termination 
                  data transfer, and the PCD forced-terminates data transfer. 
Arguments       : USB_UTR_t *ptr : USB system internal structure. Selects channel. 
                : uint16_t pipe     : Pipe number.
                : uint16_t status   : End status.
Return value    : USB_ER_t          : Error info.
******************************************************************************/
USB_ER_t R_usb_pstd_TransferEnd(USB_UTR_t *ptr, uint16_t pipe, uint16_t status)
{
    uint16_t        info;

    if( usb_gcstd_Pipe[ptr->ip][pipe] == USB_NULL )
    {
        //SCI_printf("### R_usb_pstd_TransferEnd overlaps\n");
        return USB_E_QOVR;
    }

    /* check Time out */
    if( status == USB_DATA_TMO )
    {
        info = USB_MSG_PCD_TRANSEND1;
    }
    else
    {
        info = USB_MSG_PCD_TRANSEND2;
    }

    /* PCD Send Mailbox */
    return usb_pstd_PcdSndMbx(ptr, info, pipe, &usb_cstd_DummyFunction);
}/* eof R_usb_pstd_TransferEnd() */

/******************************************************************************
Function Name   : usb_pstd_PcdSndMbx
Description     : PCD Send Mailbox
Arguments       : USB_UTR_t *ptr            : USB system internal structure.
                : uint16_t msginfo          : USB system internal structure.
                : uint16_t keyword          : USB system internal structure.
                : USB_CB_t complete         : Callback function.
Return value    : USB_ER_t                  : Error Info
******************************************************************************/
USB_ER_t usb_pstd_PcdSndMbx(USB_UTR_t *ptr, uint16_t msginfo, uint16_t keyword, USB_CB_t complete)
{
    USB_MH_t        p_blf;
    USB_ER_t        err, err2;
    USB_PCDINFO_t   *pp;

    /* Get Memory pool for send message */
    err = USB_PGET_BLK(USB_PCD_MPL, &p_blf);
    if( err == USB_E_OK )
    {
        pp = (USB_PCDINFO_t*)p_blf;
        pp->msghead     = (USB_MH_t)USB_NULL;
        pp->msginfo     = msginfo;
        pp->keyword     = keyword;
        pp->complete    = complete;

        pp->ipp         = ptr->ipp;
        pp->ip          = ptr->ip;

        /* Send message for usb_pstd_PcdTask */
        err = USB_SND_MSG(USB_PCD_MBX, (USB_MSG_t*)p_blf);
        if( err != USB_E_OK )
        {
            //SCI_printf("### pPcdSndMbx snd_msg error (%ld)\n", err);
            err2 = USB_REL_BLK(USB_PCD_MPL,(USB_MH_t)p_blf);
            if( err2 != USB_E_OK )
            {
                //SCI_printf("### pPcdSndMbx rel_blk error (%ld)\n", err2);
            }
        }
    }
    else
    {
        //SCI_printf("### pPcdSndMbx pget_blk error\n", err);
    }
    return err;
}

/******************************************************************************
Function Name   : usb_cstd_PgetBlk
Description     : Get a memory block for the caller.
Argument        : uint8_t id        : ID number (mailbox).
                : USB_UTR_t** blk   : Memory block pointer.
Return          : USB_ER_t          : USB_E_OK / USB_E_ERROR
******************************************************************************/
USB_ER_t usb_cstd_PgetBlk( uint8_t id, USB_UTR_t** blk )
{
    uint8_t usb_s_pblk_c;

    if( id < USB_IDMAX )
    {
        usb_s_pblk_c = USB_CNTCLR;
        while(usb_s_pblk_c != USB_BLKMAX)
        {
            if(usb_scstd_BlkFlg[usb_s_pblk_c] == USB_FLGCLR)
            {
                /* Acquire fixed-size memory block */
                *blk    = &usb_scstd_Block[usb_s_pblk_c];
                usb_scstd_BlkFlg[usb_s_pblk_c]  = USB_FLGSET;
                return  USB_E_OK;
            }
            usb_s_pblk_c++;
        }
        /* Error of BLK Table Full !!  */
        //SCI_printf("usb_scBlkFlg[%d][] Full !!\n",id);
    }
    return  USB_E_ERROR;
}


/******************************************************************************
Function Name   : cdc_write_complete
Description     : CallBack Function
Argument        : USB_UTR_t *mess           : Transfer result message
Return          : none
******************************************************************************/
void cdc_write_complete(USB_UTR_t *mess, uint16_t data1, uint16_t data2)
{
    cdc_event_set( EVENT_USB_WRITE_COMPLETE );          /* Set Event()  */
}   /* eof cdc_write_complete() */


/******************************************************************************
Function Name   : R_usb_cstd_PgetBlk
Description     : Call the get memory block function to get a memory block for 
                : the caller.
Argument        : uint8_t id        : ID number (mailbox).
                : USB_UTR_t** blk   : Memory block pointer.
Return          : USB_ER_t          : USB_E_OK / USB_E_ERROR
******************************************************************************/
USB_ER_t R_usb_cstd_PgetBlk( uint8_t id, USB_UTR_t** blk )
{
    USB_ER_t err;

    err = usb_cstd_PgetBlk( id, blk );

    return err;
}

/******************************************************************************
Function Name   : R_usb_pcdc_SendData
Description     : Data send request for Host
Arguments       : USB_UTR_t     *ptr        ; USB system internal structure. Selects channel.
                : uint8_t       *Table      ; Pointer to Data stored buffer 
                : uint32_t      size        ; Data size
                : USB_CB_t      complete    ; Pointer to Callback function
Return value    : none
******************************************************************************/
void R_usb_pcdc_SendData(USB_UTR_t *ptr, uint8_t *Table, uint32_t size, USB_CB_t complete)
{
    USB_MH_t    p_blf;
    USB_ER_t    err, err2;
    USB_UTR_t   *cp;

    /* Get mem pool blk */
    err = R_USB_PGET_BLK(USB_PCDC_MPL, &p_blf);
    if( err == USB_E_OK )
    {
        cp = (USB_UTR_t*)p_blf;
        cp->msghead = (USB_MH_t)NULL;
        cp->msginfo = (uint16_t)USB_PCDC_PSEND_DATA;            /* Set message information. */
        cp->keyword = (uint16_t)USB_NOT_USED;                   /* Not use */
        cp->status      = (uint16_t)USB_NOT_USED;               /* Not use */
        cp->complete    = (USB_CB_t)complete;                   /* Set Callback function */
        cp->tranadr = (void *)Table;                            /* Transfer data Start address */
        cp->tranlen = (uint32_t)size;                           /* Transfer data length */
        cp->ip = ptr->ip;                                       /* IP number(0or1) */
        cp->ipp = ptr->ipp;                                     /* IP Address(USB0orUSB1) */

        /* Send message */
        err = R_USB_SND_MSG(USB_PCDC_MBX, (USB_MSG_t*)p_blf);
        if( err != USB_E_OK )
        {
            /* Send message failure */
            //SCI_printf( "### pcdcSendData snd_msg error (%ld)\n", err );
            err2 = R_USB_REL_BLK(USB_PCDC_MPL, (USB_MH_t)p_blf);
            if( err2 != USB_E_OK )
            {
                /* Release memoryblock failure */
                //SCI_printf( "### pcdcSendData rel_blk error (%ld)\n", err2 );
            }
        }
    }
    else
    {
        /* Get momoryblock failure */
        //SCI_printf( "### pcdcSendData pget_blk error (%ld)\n", err );
    }
} /* eof R_usb_pcdc_SendData */

/******************************************************************************
Function Name   : R_usb_pcdc_ReceiveData
Description     : Data Receive request for Host
Arguments       : USB_UTR_t     *ptr        ; USB system internal structure. Selects channel.
                : uint8_t       *Table      ; Pointer to Data stored buffer 
                : uint32_t      size        ; Data size
                : USB_CB_t      complete    ; Pointer to Callback function
Return value    : none
******************************************************************************/
void R_usb_pcdc_ReceiveData(USB_UTR_t *ptr, uint8_t *Table, uint32_t size, USB_CB_t complete)
{
    USB_MH_t    p_blf;
    USB_ER_t    err, err2;
    USB_UTR_t   *cp;

    /* Get mem pool blk */
    err = R_USB_PGET_BLK(USB_PCDC_MPL, &p_blf);
    if( err == USB_E_OK )
    {
        cp = (USB_UTR_t*)p_blf;
        cp->msghead = (USB_MH_t)NULL;
        cp->msginfo = (uint16_t)USB_PCDC_PRECEIVE_DATA;         /* Set message information. */
        cp->keyword = (uint16_t)USB_NOT_USED;                   /* Not use */
        cp->status      = (uint16_t)USB_NOT_USED;               /* Not use */
        cp->complete    = (USB_CB_t)complete;                   /* Set Callback function */
        cp->tranadr = (void *)Table;                            /* Transfer data Start address */
        cp->tranlen = (uint32_t)size;                           /* Transfer data length */
        cp->ip = ptr->ip;                                       /* IP number(0or1) */
        cp->ipp = ptr->ipp;                                     /* IP Address(USB0orUSB1) */

        /* Send message */
        err = R_USB_SND_MSG(USB_PCDC_MBX, (USB_MSG_t*)p_blf);
        if( err != USB_E_OK )
        {
            /* Send message failure */
            //SCI_printf( "### pcdcReceiveData snd_msg error (%ld)\n", err );
            err2 = R_USB_REL_BLK(USB_PCDC_MPL, (USB_MH_t)p_blf);
            if( err2 != USB_E_OK )
            {
                /* Release memoryblock failure */
                //SCI_printf( "### pcdcReceiveData rel_blk error (%ld)\n", err2 );
            }
        }
    }
    else
    {
        /* Get momoryblock failure */
        //SCI_printf( "### pcdcReceiveData pget_blk error (%ld)\n", err );
    }
} /* eof R_usb_pcdc_ReceiveData */

/******************************************************************************
Function Name   : cdc_read_complete
Description     : CallBack Function
Argument        : USB_UTR_t *mess           : Transfer result message
Return          : none
******************************************************************************/
void cdc_read_complete(USB_UTR_t *mess, uint16_t data1, uint16_t data2)
{
    if( (USB_DATA_OK == mess->status) || (USB_DATA_SHT == mess->status) )   /* Check usb receive status */
    {
        cdc_trans_len = CDC_DATA_LEN - mess->tranlen;       /* Set Receive data length */
        if( cdc_trans_len > 0 )
        {
            cdc_event_set( EVENT_USB_READ_COMPLETE );       /* Set Event()  */
        }
        else
        {
            cdc_event_set( EVENT_USB_READ_START );          /* Set Event()  */
        }
    }
}   /* eof cdc_read_complete() */

/******************************************************************************
Function Name   : usb_mcu_init
Description     : USB port mode and Switch mode Initialize
Arguments       : none
Return value    : none
******************************************************************************/
void usb_mcu_init(void)
{
	
	MPC.PWPR.BIT.B0WI  = 0;
	MPC.PWPR.BIT.PFSWE = 1;
    /* Set port direction as input(USB0 DRUPE/VBUS) */
	PORT1.PDR.BIT.B6           = 0;
	PORT1.PMR.BIT.B6           = 0;     /* Port mode register (Disable USB0 VBUS) */
 	PORT1.PMR.BIT.B4           = 0;		/* Port mode register (DPUPE)*/
    /* Port mode register write enable */
 	MPC.PWPR.BYTE           = 0x00;
	MPC.PWPR.BYTE           = 0x40;

    /* Initial setting of USB0 */
	MPC.P14PFS.BYTE    = 0x11;		/* DPUPE output enable */
    MPC.P16PFS.BYTE= 0x11;			/* VBUS  input  enable */
    /* Enable USB0 DPUPE pullup register */
	MPC.PFUSB0.BIT.PUPHZS= 1;		/* DPUPE eneble */
	/* Port mode register write disable */
	MPC.PWPR.BYTE      = 0x80;      /* PFS register write protect on */
	PORT1.PMR.BIT.B6   = 1;         /* Port mode register (Enable USB0 VBUS) */
	PORT1.PMR.BIT.B4   = 1;			/*USB0_DPRPU_PMR*/
	MPC.PWPR.BIT.PFSWE = 0;
	MPC.PWPR.BIT.B0WI  = 1;
#ifdef USB_DEBUG
	result = R_DTC_Open();
	switch(result)
	{
		case DTC_ERR_OPENED :
			//SCI_printf("\n\rDTC_ERR_OPENED");
			break;
		case DTC_ERR_BUSY :
			//SCI_printf("\n\rDTC_ERR_BUSY");
			break;
		case DTC_SUCCESS :
			//SCI_printf("\n\rDTC_SUCCESS");
			break;
	}		
#else
	R_DTC_Open();					/* Initializes the DTC module */
#endif

	USB.DPUSR0R.BIT.FIXPHY0 = 0;	/* USB0 Transceiver Output fixed */
	IEN( USB0, D0FIFO0 )    = 0;	/* D0FIFO0 disable */
	IEN( USB0, D1FIFO0 )    = 0;	/* D1FIFO0 disable */
	IEN( USB, USBR0 )       = 1;	/* USBR0 enable */
	IPR( USB0, D0FIFO0 )    = 0;	/* D0FIFO0 */
	IPR( USB0, D1FIFO0 )    = 0;	/* D1FIFO0 */
	IPR( USB, USBR0 )       = 0;	/* USBR0 */
	IPR( USB0, USBI0 )      = 3;	/* USBI0 in vector 128 */
	IEN( USB0, USBI0 )      = 1;	/* USBI0 enable in vector 128 */
}   /* eof usb_mcu_init() */

/*******************************************************************************
* Function Name: R_DTC_Open
* Description  : Initializes the DTC module. It's only called once.
* Arguments    : None
* Return Value : DTC_SUCCESS -
*                    Successful operation
*                DTC_ERR_INVALID_ARG -
*                    Parameters are invalid.
*                DTC_ERR_OPENED -
*                    The DTC has been already initialized.
*                DTC_ERR_BUSY -
*                    DTC is opened already.
*******************************************************************************/
dtc_err_t R_DTC_Open(void)
{
    uint8_t * dtc_table_work2 = 0;

    if (false == r_dtc_acquire_hw_lock())
    {
        /* Lock has already been acquired by another task. Need to try again later. */
        return DTC_ERR_BUSY;
    }

    if (true == g_is_opened) /* DTC is opened. */
    {
        r_dtc_release_hw_lock();
        return DTC_ERR_OPENED;
    }

    g_dtc_table_work[0] = 0x0000;

    g_dtc_table_work[1] = g_dtc_table_work[0];
    dtc_table_work2 = (uint8_t *)g_dtc_table_work[1];

    r_dtc_clear_all_dtce_bits();

    /* Cancel module stop for DMAC and DTC. */
    r_dtc_module_enable();
    /* Set DTC Vector Table Base Register. */
    DTC.DTCVBR = dtc_table_work2;

    /* Set DTC address mode. */
/* Full-address mode */
    DTC.DTCADMOD.BIT.SHORT = 0;

    /* Set the Transfer Data Read Skip bit. */
    DTC.DTCCR.BIT.RRS = 1;

	g_is_opened = true; /* DTC module is initialized successfully. */

    return DTC_SUCCESS;
}

/*******************************************************************************
* Function Name: r_dtc_module_enable
* Description  : Releases module stop state.
* Arguments    : None
* Return Value : None
*******************************************************************************/
void r_dtc_module_enable(void)
{
    /* Enable writing to MSTP registers. */
	SYSTEM.PRCR.WORD = 0xA502;
    MSTP(DTC) = 0;
	SYSTEM.PRCR.WORD = 0xA500;
	
    return;
}

/*******************************************************************************
* Function Name: r_dtc_clear_all_dtce_bits
* Description  : Clears all DTCERn.DTCE bit corresponding to the interrupt that
*                can be selected as DTC activation sources.
* Arguments    : addr -
*                  Address need to be validated
* Return Value : true -
*                  The address is valid.
*                false -
*                  The address is invalid.
*******************************************************************************/
static void r_dtc_clear_all_dtce_bits(void)
{
    volatile uint32_t dtce_cnt = 0;

    /* Clear all DTCER registers.
     * Scan through all available DTCER registers in Array.
     */
    while (dtce_cnt < DTC_NUM_INTERRUPT_SRC)
    {
        ICU.DTCER[source_array2[dtce_cnt]].BIT.DTCE = 0;
        dtce_cnt++;
    }

    return;
}

/*******************************************************************************
* Function Name: r_dtc_acquire_hw_lock
* Description  : Gets the hardware lock BSP_LOCK_DTC.
* Arguments    : None.
* Return Value : true -
*                  The lock is acquired successfully
*                false -
*                  Fails to get the lock
*******************************************************************************/
static bool r_dtc_acquire_hw_lock(void)
{
    return R_BSP_HardwareLock(BSP_LOCK_DTC);
}

/***********************************************************************************************************************
* Function Name: R_BSP_HardwareLock
* Description  : Attempt to acquire the lock that has been sent in. This function takes in a peripheral index into the
*                array that holds hardware locks.
* Arguments    : hw_index -
*                    Index in locks array to the hardware resource to lock.
* Return Value : true -
*                    Lock was acquired.
*                false -
*                    Lock was not acquired.
***********************************************************************************************************************/
bool R_BSP_HardwareLock (mcu_lock_t const hw_index)
{
    return R_BSP_SoftwareLock(&g_bsp_Locks[hw_index]);
} /* End of function R_BSP_HardwareLock() */

/***********************************************************************************************************************
* Function Name: R_BSP_SoftwareLock
* Description  : Attempt to acquire the lock that has been sent in.
* Arguments    : plock -
*                    Pointer to lock structure with lock to try and acquire.
* Return Value : true -
*                    Lock was acquired.
*                false -
*                    Lock was not acquired.
***********************************************************************************************************************/
bool R_BSP_SoftwareLock (BSP_CFG_USER_LOCKING_TYPE * const plock)
{
    bool ret = false;

    /* Variable used in trying to acquire lock. Using the xchg instruction makes this atomic */
    int32_t is_locked = true;
    
    /* This example uses the RX MCU's atomic xchg() instruction. plock->lock is the lock we are trying to reserve. 
       The way this works is that 'is_locked' gets the value of the plock->lock and plock->lock gets the value of 
       'is_locked' which we just set to 'true'. Basically this is an atomic 'swap' command. If the lock had not yet been
       reserved then its value would be 'false' and after the xchg() instruction finished 'is_locked' would have 
       'false'. If it had already been reserved then 'is_locked' would have 'true' after the xchg() instruction. Since 
       plock->lock was already 'true' and we just set it back to 'true' everything is ok. To see if we reserved the lock
       we just need to check the value of 'is_locked' after this instruction finishes. */

    /* Try to acquire semaphore to obtain lock */
    xchg(&is_locked, &plock->lock);
    
    /* Check to see if semaphore was successfully taken */
    if (is_locked == false)
    {        
        /* Lock obtained, return success. */
        ret = true;
    }
    else
    {
        /* Lock was not obtained, another task already has it. */
    }

    return ret;   
} /* End of function R_BSP_SoftwareLock() */

/******************************************************************************
Function Name   : usb_driver_init
Description     : Start task CSTD; "common" basic USB low level task.
Arguments       : USB_UTR_t *ptr      : 
Return value    : none
******************************************************************************/
void usb_driver_init( void )
{

    USB_ER_t    err;
//    USB_UTR_t   *ptr;

    cdc_utr.ip = USB_USBIP_0;                               /* USB IP no.(0) */
    cdc_utr.ipp = R_usb_cstd_GetUsbIpAdr( cdc_utr.ip );     /* Set USB IP Registor base address */

    usb_cstd_ScheInit();                                    /* Scheduler init */

//    R_usb_pstd_usbdriver_start( ptr );                    /* Peripheral USB Driver Start Setting */
    R_usb_pstd_usbdriver_start( &cdc_utr );                 /* Peripheral USB Driver Start Setting */
    cdc_registration();                                     /* Peripheral CDC Application registration. */

    err = R_USB_Open( USB_IP0 );            				/* Initializes the USB module */
    if( USB_E_OK == err )
    {
        R_usb_cstd_UsbIpInit( &cdc_utr, USB_PERI );        /* Initialize the USB IP. */
    }
    else
    {
        USB_DEBUG_HOOK( USB_DEBUG_HOOK_APL | USB_DEBUG_HOOK_CODE1 );
    }

    R_usb_pcdc_driver_start();                              /* Init peripheral class driver task. */

}   /* eof usb_driver_init() */

/******************************************************************************
Function Name   : R_usb_pcdc_driver_start
Description     : USB Vendor Peripheral Driver Start
Argument        : none
Return          : none
******************************************************************************/
void R_usb_pcdc_driver_start( void )
{
    R_usb_cstd_SetTaskPri(USB_PCDC_TSK, USB_PRI_4);
} /* eof R_usb_pcdc_driver_start */

/******************************************************************************
Function Name   : R_usb_cstd_SetTaskPri
Description     : Set a task's priority.
Argument        : uint8_t tasknum   : Task id.
                : uint8_t pri       : The task priority to be set.
Return          : none
******************************************************************************/
void R_usb_cstd_SetTaskPri(uint8_t tasknum, uint8_t pri)
{
    if(tasknum < USB_IDMAX)
    {
        if(pri < USB_PRIMAX)
        {
            usb_scstd_Pri[tasknum]=pri;
        }
        else if(pri == (uint8_t)USB_IDCLR)
        {
            usb_scstd_Pri[tasknum]=(uint8_t)USB_IDCLR;
        }
        else
        {
        }
    }
}

/******************************************************************************
Function Name   : R_usb_cstd_UsbIpInit
Description     : Initialize the USB IP.
Arguments       : USB_UTR_t *ptr : USB system internal structure.
                : uint16_t  usb_mode    : USB mode (Host/Peripheral).
Return value    : none
******************************************************************************/
void R_usb_cstd_UsbIpInit( USB_UTR_t *ptr, uint16_t usb_mode )
{
    usb_cstd_WaitUsbip( ptr );      	/* Wait USB-H/W access enable */
    usb_cstd_AsspConfig( ptr );     	/* Set ASSP pin_config */
    usb_cstd_InitialClock( ptr );   	/* Start clock */
    R_usb_cstd_ClearHwFunction( ptr );	/* nitinalize USB register (Host/Peripheral common) */
    usb_cstd_Pinconfig( ptr );      	/* Set pin_config */

    usb_cstd_set_usbip_mode( ptr, usb_mode );
}/* eof R_usb_cstd_UsbIpInit */

/******************************************************************************
Function Name   : usb_cstd_set_usbip_mode
Description     : Set the Host mode or Peripheral mode to USB H/W
Arguments       : USB_UTR_t *ptr : USB system internal structure.
                : uint16_t function : Host mode/Peripheral mode
Return value    : none
******************************************************************************/
void usb_cstd_set_usbip_mode(USB_UTR_t *ptr, uint16_t function)
{
    /* USB interrupt message initialize */
    usb_cstd_InitUsbMessage(ptr, function);
    /* Select HW function */
    usb_cstd_set_usbip_mode_sub(ptr, function);
}/* eof usb_cstd_set_usbip_mode() */

/******************************************************************************
Function Name   : usb_cstd_InitUsbMessage
Description     : Initialization of message to be used at time of USB interrupt.
Arguments       : USB_UTR_t *ptr : USB internal structure. Selects e.g. channel.
                : uint16_t  function    : Host or peripheral mode.
Return value    : none
******************************************************************************/
void usb_cstd_InitUsbMessage(USB_UTR_t *ptr, uint16_t function)
{
    /* TD.5.4 The interruption message of PCD is notified to HCD.  */
    uint16_t        i, msg_info;

    if( function == USB_PERI )
    {
        /* Peripheral Function */
        msg_info = USB_MSG_PCD_INT;
    }
    else
    {
        /* Host Function */
        msg_info = USB_MSG_HCD_INT;
    }

    for( i = 0; i < USB_INTMSGMAX; i++ )
    {
        usb_gcstd_IntMsg[ptr->ip][i].msginfo = msg_info;
    }

    usb_gcstd_IntMsgCnt[ptr->ip] = 0;
}

/******************************************************************************
Function Name   : usb_cstd_set_usbip_mode_sub
Description     : USB init depending on mode (host peripharal). 
Arguments       : USB_UTR_t *ptr    : USB system internal structure.
                : uint16_t function : HOST/PERI
Return value    : none
******************************************************************************/
void usb_cstd_set_usbip_mode_sub(USB_UTR_t *ptr, uint16_t function)
{

	usb_cstd_set_sofcfg_intl( ptr );
    
    
    if (function == (uint16_t)USB_PERI)
    {
        usb_creg_clr_drpd( ptr, USB_PORT0 );
        usb_preg_write_physlew( ptr );
        
        /* Interrupt Enable */
        usb_cstd_BerneEnable(ptr);
        usb_pstd_InitConnect(ptr);
    }
    else
    {
    }
}

/******************************************************************************
Function Name   : usb_pstd_InitConnect
Description     : Set up interrupts and initialize.
Arguments       : USB_UTR_t *ptr    : USB system internal structure.
Return value    : none
******************************************************************************/
void usb_pstd_InitConnect(USB_UTR_t *ptr)
{
    uint16_t        connect_info;

    /* Interrupt enable */
    usb_pstd_InterruptEnable(ptr);
    usb_cstd_SetHse(ptr, (uint16_t)USB_PORT0, usb_gcstd_HsEnable[ptr->ip]);

    usb_creg_set_cnen( ptr );
    connect_info = usb_pstd_InitFunction( ptr );
    
    switch( connect_info )
    {
    /* Attach host controller */
    case USB_ATTACH:
        usb_pstd_AttachProcess(ptr);
        break;
    /* Detach host controller */
    case USB_DETACH:
        usb_pstd_DetachProcess(ptr);
        break;
    default:
        break;
    }
}

/******************************************************************************
Function Name   : usb_pstd_InitFunction
Description     : Call function that checks VBUS status.
Arguments       : USB_UTR_t *ptr    : USB system internal structure.
Return value    : none
******************************************************************************/
uint16_t usb_pstd_InitFunction(USB_UTR_t *ptr)
{
    /* Wait USB_VBSTS */
    return usb_pstd_ChkVbsts( ptr );
}

/******************************************************************************
Function Name   : usb_cstd_SetHse
Description     : Set/clear the HSE-bit of the specified port.
Arguments       : uint16_t port     : Root port.
                : uint16_t speed    : HS_ENABLE/HS_DISABLE.
Return value    : none
******************************************************************************/
void usb_cstd_SetHse(USB_UTR_t *ptr, uint16_t port, uint16_t speed)
{
    if( speed == USB_HS_DISABLE )
    {
        /* HSE = disable */
        usb_creg_clr_hse( ptr, port );
    }
    else
    {
        /* HSE = enable */
        usb_creg_set_hse( ptr, port );
    }
}

/******************************************************************************
Function Name   : usb_cstd_BerneEnable
Description     : Enable BRDY/NRDY/BEMP interrupt.
Arguments       : USB_UTR_t *ptr : USB internal structure. Selects e.g. channel.
Return value    : none
******************************************************************************/
void usb_cstd_BerneEnable(USB_UTR_t *ptr)
{
    /* Enable BEMP, NRDY, BRDY */
    usb_creg_set_intenb( ptr, (USB_BEMPE|USB_NRDYE|USB_BRDYE) );
}

/******************************************************************************
Function Name   : usb_cstd_set_sofcfg_intl
Description     : Set Interrupt sence mode(Level sence) for SOFCFG.
Arguments       : USB_UTR_t *ptr    : USB system internal structure.
Return value    : none
******************************************************************************/
void usb_cstd_set_sofcfg_intl( USB_UTR_t *ptr )
{
    usb_creg_set_sofcfg( ptr, USB_INTL );
} /* eof usb_cstd_set_sofcfg_intl() */

/******************************************************************************
Function Name   : usb_cstd_Pinconfig
Description     : Set FIFO select register. This will assign a pipe to the FIFOs, 
                : and control how FIFOs are accessed.
Arguments       : USB_UTR_t *ptr    : USB system internal structure. Selects channel.
Return value    : -
******************************************************************************/
void usb_cstd_Pinconfig(USB_UTR_t *ptr)
{
    if(ptr->ip == USB_USBIP_0)
    {
        /* CFIFO Port Select Register  (0x20) */
        usb_creg_write_fifosel( ptr, USB_CUSE, USB0_CFIFO_MBW );
        /* D0FIFO Port Select Register (0x28) */
        usb_creg_write_fifosel( ptr, USB_D0USE, USB0_D0FIFO_MBW );
        /* D1FIFO Port Select Register (0x2C) */
        usb_creg_write_fifosel( ptr, USB_D1USE, USB0_D1FIFO_MBW );
    }
    else if(ptr->ip == USB_USBIP_1)
    {
        /* CFIFO Port Select Register  (0x20) */
        usb_creg_write_fifosel( ptr, USB_CUSE, USB1_CFIFO_MBW );
        /* D0FIFO Port Select Register (0x28) */
        usb_creg_write_fifosel( ptr, USB_D0USE, USB1_D0FIFO_MBW );
        /* D1FIFO Port Select Register (0x2C) */
        usb_creg_write_fifosel( ptr, USB_D1USE, USB1_D1FIFO_MBW );
    }
    /* setting ENDIAN for CFIFOSEL */
    usb_creg_set_bigend( ptr, USB_CUSE, USB_FIFOENDIAN );
    /* setting ENDIAN for D0FIFOSEL */
    usb_creg_set_bigend( ptr, USB_D0USE, USB_FIFOENDIAN );
    /* setting ENDIAN for D1FIFOSEL */
    usb_creg_set_bigend( ptr, USB_D1USE, USB_FIFOENDIAN );
} /* eof usb_cstd_Pinconfig() */

/******************************************************************************
Function Name   : R_usb_cstd_ClearHwFunction
Description     : Initinalize USB register (Host/Peripheral common)
Arguments       : USB_UTR_t *ptr : USB system internal structure.
Return value    : none
******************************************************************************/
void R_usb_cstd_ClearHwFunction(USB_UTR_t *ptr)
{
    usb_cstd_SelfClock(ptr);

    usb_cstd_SetNak(ptr, USB_PIPE0);

    usb_creg_set_bus_wait( ptr );

    usb_cstd_ClearIntEnb( ptr );

    /* Interrupt Disable(BRDY,NRDY,USB_BEMP) */
    usb_creg_write_brdyenb( ptr, 0 );
    usb_creg_write_nrdyenb( ptr, 0 );
    usb_creg_write_bempenb( ptr, 0 );

    /* Interrupt status clear */
    usb_cstd_ClearIntSts( ptr );

    /* Interrupt status clear(USB_BRDY,NRDY,USB_BEMP) */
    usb_creg_write_brdysts( ptr, 0 );
    usb_creg_write_nrdysts( ptr, 0 );
    usb_creg_write_bempsts( ptr, 0 );

    /* D+/D- control line set */
    usb_cstd_ClearDline( ptr );

    usb_creg_clr_hse( ptr, USB_PORT0 );
    usb_creg_clr_hse( ptr, USB_PORT1 );

    /* Function controller select */
    usb_creg_clr_dcfm( ptr ); 
    usb_cstd_SwReset(ptr);

}/* eof R_usb_cstd_ClearHwFunction */

/******************************************************************************
Function Name   : usb_cstd_ClearDline
Description     : Clear DRPD/DPRPU; host pulldown of resistors for D+ D- lines.
Arguments       : USB_UTR_t *ptr : USB internal structure. Selects e.g. channel.
Return value    : none
******************************************************************************/
void    usb_cstd_ClearDline( USB_UTR_t *ptr )
{
    usb_creg_clr_cnen( ptr );
    usb_preg_clr_dprpu( ptr );
}

/******************************************************************************
Function Name   : usb_cstd_SwReset
Description     : Request USB IP software reset
Arguments       : USB_UTR_t *ptr : USB internal structure. Selects e.g. channel.
Return value    : none
******************************************************************************/
void usb_cstd_SwReset(USB_UTR_t *ptr)
{
    /* USB Enable */
    usb_creg_set_usbe( ptr );
    /* USB Reset */
    usb_creg_clr_usbe( ptr );
    /* USB Enable */
    usb_creg_set_usbe( ptr );
}

/******************************************************************************
Function Name   : usb_cstd_ClearIntSts
Description     : Clear the INTSTS register.
Arguments       : USB_UTR_t *ptr : USB internal structure. Selects e.g. channel.
Return value    : none
******************************************************************************/
void    usb_cstd_ClearIntSts( USB_UTR_t *ptr )
{
    usb_creg_write_intsts( ptr, 0 );
/* Conditional compile dep. on difference of USB function */
}

/******************************************************************************
Function Name   : usb_cstd_ClearIntEnb
Description     : Clear teh INTENB register.
Arguments       : USB_UTR_t *ptr : USB internal structure. Selects e.g. channel.
Return value    : none
******************************************************************************/
void    usb_cstd_ClearIntEnb( USB_UTR_t *ptr )
{
    usb_creg_write_intenb( ptr, 0 );
    /* Conditional compile dep. on difference of USB function */
}

/******************************************************************************
Function Name   : usb_cstd_InitialClock
Description     : Enable USB module clock. Resets and starts peripheral.
Arguments       : USB_UTR_t *ptr    : USB system internal structure. Selects channel.
Return value    : none
******************************************************************************/
void usb_cstd_InitialClock(USB_UTR_t *ptr)
{
    if (ptr -> ip  == USB_USBIP_0)
    {
        usb_creg_set_scke( ptr );
    }
    else if (ptr -> ip == USB_USBIP_1)
    {
        usb_creg_set_scke( ptr );
    }
    else{
    }

}/* eof usb_cstd_InitialClock() */

/******************************************************************************
Function Name   : usb_cstd_AsspConfig
Description     : Not processed as the functionality is provided by R8A66597(ASSP).
Arguments       : not used
Return value    : -
******************************************************************************/
void usb_cstd_AsspConfig(USB_UTR_t *ptr)
{
}/* eof usb_cstd_AsspConfig() */

/******************************************************************************
Function Name   : usb_cstd_WaitUsbip
Description     : Wait USB ASSP ready
Arguments       : USB_UTR_t *ptr    : USB system internal structure. Selects channel.
Return value    : none
******************************************************************************/
void usb_cstd_WaitUsbip(USB_UTR_t *ptr)
{
    /* XCKE Mode Flag */
    usb_gcstd_XckeMode = USB_NO;

    if(ptr->ip == USB_USBIP_0)
    {
        /* Hi-speed enable */
        usb_gcstd_HsEnable[ptr->ip] = USB_HS_DISABLE;
    }
    else if(ptr->ip == USB_USBIP_1)
    {
        /* Hi-speed enable */
        usb_gcstd_HsEnable[ptr->ip] = USB_HS_DISABLE;
    }
}/* eof usb_cstd_WaitUsbip() */

/******************************************************************************
Function Name   : R_USB_Open
Description     : Initializes the USB module. It's only called once.
Arguments       : usb_ip_t ip_type  : USB_IP0/USB_IP1
Return value    : USB_SUCCESS -
                    USB module is initialized successfully
                  USB_ERR_OPENED
                    USB is opened already
                  USB_ERR_BUSY
                    Lock has already been acquired by another task
******************************************************************************/
usb_err_t R_USB_Open( usb_ip_t ip_type )
{
    return usb_cpu_module_start( ip_type );
}

/******************************************************************************
Function Name   : usb_cpu_module_start
Description     : USB module start
Arguments       : usb_ip_t ip_type  : USB_IP0/USB_IP1
Return value    : none
******************************************************************************/
usb_err_t usb_cpu_module_start( usb_ip_t ip_type )
{
    if( USB_IP0 == ip_type )
    {
        if(R_BSP_HardwareLock(BSP_LOCK_USB0) == false)
        {
            /* Lock has already been acquired by another task. Need to try again later */
            return USB_ERR_BUSY;
        }
        if(usb_gstd_is_opened[ip_type] == true)
        {
            R_BSP_HardwareUnlock(BSP_LOCK_USB0);
            return USB_ERR_OPENED;
        }

		/* Enable writing to MSTP registers */
		SYSTEM.PRCR.WORD = 0xA502;
		/* Enable power for USB0 */
		SYSTEM.MSTPCRB.BIT.MSTPB19 = 0;
		/* Disable writing to MSTP registers */
	   	SYSTEM.PRCR.WORD = 0xA500;

        R_BSP_HardwareUnlock(BSP_LOCK_USB0);
    }
    else
    {
    }
    usb_gstd_is_opened[ip_type] = true;

    return USB_SUCCESS;
}

/******************************************************************************
Function Name   : cdc_registration
Description     : Registration of peripheral Communications Devices Driver
Arguments       : USB_UTR_t *ptr        : USB system internal structure.
Return value    : none
******************************************************************************/
void cdc_registration( void )
{

    USB_PCDREG_t    driver;

    /* Driver registration */
    driver.pipetbl      = &cdc_eptbl_ptr[0];                    /* Pipe Define Table address */
    driver.devicetbl    = (uint8_t*)&cdc_device_descriptor;     /* Device descriptor Table address */
    driver.configtbl    = (uint8_t**)&cdc_config_descriptor_ptr;/* Configuration descriptor Table address */
    driver.stringtbl    = (uint8_t**)&cdc_string_descriptor_ptr;/* String descriptor Table address */
    driver.classinit    = &usb_cstd_DummyFunction;              /* Driver init */
    driver.devconfig    = (USB_CB_t)&cdc_configured;            /* Device configuered */
    driver.devdetach    = (USB_CB_t)&cdc_detach;                /* Device detach */
    driver.devsuspend   = (USB_CB_t)&cdc_suspend;               /* Device suspend */
    driver.devresume    = &usb_cstd_DummyFunction;              /* Device resume */
    driver.interface    = &R_usb_pcdc_set_interface;            /* Interfaced change */
    driver.ctrltrans    = (USB_CB_TRN_t)&R_usb_pcdc_usr_ctrl_trans_function;    /* Control Transfer */
    driver.qualitbl     = (uint8_t*)USB_NULL;                   /* Qualifier descriptor Table address */
    driver.othertbl     = (uint8_t**)USB_NULL;                  /* Other configuration descriptor Table address */
    driver.devdefault   = (USB_CB_t)&cdc_detach;                /* Device default */
	
	R_usb_pstd_DriverRegistration( &cdc_utr, &driver );         /* PCDC class driver registration  */
	
}   /* eof cdc_registration() */

/******************************************************************************
Function Name   : R_usb_pcdc_usr_ctrl_trans_function
Description     : Class request processing for CDC 
Arguments       : USB_UTR_t *ptr       ; USB system internal structure. Selects channel.
                : USB_REQUEST_t *preq  ; Class request information
                : uint16_t ctsq        ; Control Stage
Return value    : none
******************************************************************************/
void R_usb_pcdc_usr_ctrl_trans_function(USB_UTR_t *ptr, USB_REQUEST_t *preq, uint16_t ctsq)
{
    if( preq->ReqTypeType == USB_CLASS )
    {
        switch( ctsq )
        {
        /* Idle or setup stage */
        case USB_CS_IDST:   usb_pcdc_ControlTrans0(ptr, preq);  break;
        /* Control read data stage */
        case USB_CS_RDDS:   usb_pcdc_ControlTrans1(ptr, preq);  break;
        /* Control write data stage */
        case USB_CS_WRDS:   usb_pcdc_ControlTrans2(ptr, preq);  break;
        /* Control write nodata status stage */
        case USB_CS_WRND:   usb_pcdc_ControlTrans3(ptr, preq);  break;
        /* Control read status stage */
        case USB_CS_RDSS:   usb_pcdc_ControlTrans4(ptr, preq);  break;
        /* Control write status stage */
        case USB_CS_WRSS:   usb_pcdc_ControlTrans5(ptr, preq);  break;

        /* Control sequence error */
        case USB_CS_SQER:
            R_usb_pstd_ControlEnd(ptr, (uint16_t)USB_DATA_ERR); break;
        /* Illegal */
        default:
            R_usb_pstd_ControlEnd(ptr, (uint16_t)USB_DATA_ERR); break;
        }
    }
    else
    {
        //SCI_printf("R_usb_pcdc_usr_ctrl_trans_function Err: %x %x\n"
//            , preq->ReqTypeType, ctsq);
//        usb_pstd_SetStallPipe0( ptr );
    }
} /* eof R_usb_pcdc_usr_ctrl_trans_function */

/******************************************************************************
Function Name   : usb_pcdc_ControlTrans1
Description     : Class request processing (control read)
Arguments       : USB_UTR_t *ptr       ; USB system internal structure. Selects channel.
                : USB_REQUEST_t *req   ; Class request information
Return value    : none
******************************************************************************/
void usb_pcdc_ControlTrans1(USB_UTR_t *ptr, USB_REQUEST_t *req)
{
    /* Is a request receive target Interface? */
    if( (req->ReqIndex == 0) && (req->ReqTypeRecip == USB_INTERFACE) )
    {
        /* Is a Request Type GetLineCoding? */
        if( req->ReqRequest == USB_PCDC_GET_LINE_CODING )
        {
            /* send get_line_coding */
            R_usb_pstd_ControlRead(ptr, (uint32_t)USB_PCDC_GET_LINE_CODING_LENGTH
                , (uint8_t *)&usb_gcdc_LineCodingReq);
        }
        else
        {
            /* Set Stall */
            usb_pstd_SetStallPipe0( ptr );    /* Req Error */
        }
    }
    else
    {
        /* Set Stall */
        usb_pstd_SetStallPipe0( ptr );        /* Req Error */
    }
} /* eof usb_pcdc_ControlTrans1 */

/******************************************************************************
Function Name   : R_usb_pstd_ControlRead
Description     : Start control read transfer (API). When a valid control read 
                : request is received from host, the ControlRead function gen-
                : erates data for transmission to the host and writes it to the 
                : FIFO.
Arguments       : uint32_t bsize    : Read size in bytes.
                : uint8_t *table    : Start address of read data buffer.
Return value    : uint16_t          : USB_WRITESHRT/USB_WRITE_END/USB_WRITING/
                :                   : USB_FIFOERROR.
******************************************************************************/
uint16_t R_usb_pstd_ControlRead(USB_UTR_t *ptr, uint32_t bsize, uint8_t *table)
{
    uint16_t    end_flag;

    end_flag = usb_pstd_ControlRead( ptr, bsize, table);

    return (end_flag);
}

/******************************************************************************
Function Name   : usb_pcdc_ControlTrans4
Description     : Class request processing (control read status stage)
Arguments       : USB_UTR_t *ptr       ; USB system internal structure. Selects channel.
                : USB_REQUEST_t *req   ; Pointer to Class request information
Return value    : none
******************************************************************************/
void usb_pcdc_ControlTrans4(USB_UTR_t *ptr, USB_REQUEST_t *req)
{
    /* Is a Request Type GetLineCoding? */
    if( req->ReqRequest == USB_PCDC_GET_LINE_CODING )
    {
        usb_cstd_SetBuf(ptr, (uint16_t)USB_PIPE0);          /* Set BUF */
        /* Get Line Coding Request */
        usb_pcdc_GetLineCoding_req(ptr);
    }
    else
    {
        /* Set Stall */
        usb_pstd_SetStallPipe0( ptr );        /* Req Error */
    }
    R_usb_pstd_ControlEnd(ptr, (uint16_t)USB_CTRL_END);
} /* eof usb_pcdc_ControlTrans4 */

/******************************************************************************
Function Name   : usb_pcdc_GetLineCoding_req
Description     : Class request processing for GetLineCoding request
Arguments       : USB_UTR_t *ptr       ; USB system internal structure. Selects channel.
Return value    : none
******************************************************************************/
void usb_pcdc_GetLineCoding_req(USB_UTR_t *ptr)
{
    /* Class request Get_Line_Coding */
    usb_pcdc_GetLineCoding(ptr, &usb_cstd_DummyFunction);
} /* eof usb_pcdc_GetLineCoding_req */

/******************************************************************************
Function Name   : usb_pcdc_GetLineCoding
Description     : Peripheral Get Line Coding request
Arguments       : USB_UTR_t     *ptr        ; USB system internal structure. Selects channel.
                : USB_CB_t complete    ; Callback function
Return value    : none
******************************************************************************/
void usb_pcdc_GetLineCoding(USB_UTR_t *ptr, USB_CB_t complete)
{
    USB_MH_t    p_blf;
    USB_ER_t    err, err2;
    USB_UTR_t   *cp;

    /* Get mem pool blk */
    err = R_USB_PGET_BLK(USB_PCDC_MPL, &p_blf);
    if( err == USB_E_OK )
    {
        cp = (USB_UTR_t*)p_blf;
        cp->msghead = (USB_MH_t)NULL;
        cp->msginfo = (uint16_t)USB_PCDC_PGET_LINE_CODING;      /* Set message information. */
        cp->keyword = (uint16_t)USB_NOT_USED;                   /* Not use */
        cp->status      = (uint16_t)USB_NOT_USED;               /* Not use */
        cp->complete    = (USB_CB_t)complete;                   /* Set Callback function */
        cp->ip = ptr->ip;                                       /* IP number(0or1) */
        cp->ipp = ptr->ipp;                                     /* IP Address(USB0orUSB1) */

        /* Send message */
        err = R_USB_SND_MSG(USB_PCDC_MBX, (USB_MSG_t*)p_blf);
        if( err != USB_E_OK )
        {
            /* Send message failure */
            //SCI_printf( "### pcdcSetLineCoding snd_msg error (%ld)\n", err );
            err2 = R_USB_REL_BLK(USB_PCDC_MPL, (USB_MH_t)p_blf);
            if( err2 != USB_E_OK )
            {
                /* Release memoryblock failure */
                //SCI_printf( "### pcdcSetLineCoding rel_blk error (%ld)\n", err2 );
            }
        }
    }
    else
    {
        /* Get momoryblock failure */
        //SCI_printf( "### pcdcSetLineCoding pget_blk error (%ld)\n", err );
    }
} /* eof usb_pcdc_GetLineCoding */

/******************************************************************************
Function Name   : usb_pcdc_ControlTrans3
Description     : Class request processing(control no data write)
Arguments       : USB_UTR_t *ptr       ; USB system internal structure. Selects channel.
                : USB_REQUEST_t *req   ; Pointer to Class request information
Return value    : none
******************************************************************************/
void usb_pcdc_ControlTrans3(USB_UTR_t *ptr, USB_REQUEST_t *req)
{
    /* Is a request receive target Interface? */
    if( (req->ReqIndex == 0) && (req->ReqTypeRecip == USB_INTERFACE) )
    {
        /* Is a Request Type SetControlLineState? */
        if( req->ReqRequest == USB_PCDC_SET_CONTROL_LINE_STATE )
        {
            usb_cstd_SetBuf(ptr, (uint16_t)USB_PIPE0);          /* Set BUF */
            /* DTR & RTS set value store */
            *(uint16_t *)&usb_gcdc_ControlLineState = req->ReqValue;

            /* send Set_Control_Line_State */
            usb_pcdc_SetControlLineState_req(ptr);
        }
        else if( req->ReqRequest == USB_PCDC_SEND_BREAK )
        {
            /* Set Stall */
            usb_pstd_SetStallPipe0( ptr );    /* Req Error */
        }
        else
        {
            /* Set Stall */
            usb_pstd_SetStallPipe0( ptr );    /* Req Error */
        }
    }
    else
    {
        /* Set Stall */
        usb_pstd_SetStallPipe0( ptr );        /* Req Error */
    }
    if( req->ReqRequest != 0 )
    {
        R_usb_pstd_ControlEnd(ptr, (uint16_t)USB_CTRL_END);
    }
} /* eof usb_pcdc_ControlTrans3 */

/******************************************************************************
Function Name   : usb_pcdc_SetControlLineState_req
Description     : Class request processing for SetControlLineState request
Arguments       : USB_UTR_t *ptr       ; USB system internal structure. Selects channel.
Return value    : none
******************************************************************************/
void usb_pcdc_SetControlLineState_req(USB_UTR_t *ptr)
{
    /* Class request Set_Control_Line_State */
    usb_pcdc_SetControlLineState(ptr, &usb_cstd_DummyFunction);
} /* eof usb_pcdc_SetControlLineState_req */

/******************************************************************************
Function Name   : usb_pcdc_SetControlLineState
Description     : Peripheral Set Control Line State request
Arguments       : USB_UTR_t     *ptr        ; USB system internal structure. Selects channel.
                : USB_CB_t complete    ; Pointer to Callback function
Return value    : none
******************************************************************************/
void usb_pcdc_SetControlLineState(USB_UTR_t *ptr, USB_CB_t complete)
{
    USB_MH_t    p_blf;
    USB_ER_t    err, err2;
    USB_UTR_t   *cp;

    /* Get mem pool blk */
    err = R_USB_PGET_BLK(USB_PCDC_MPL, &p_blf);
    if( err == USB_E_OK )
    {
        cp = (USB_UTR_t*)p_blf;
        cp->msghead = (USB_MH_t)NULL;
        cp->msginfo = (uint16_t)USB_PCDC_PSET_CONTROL_LINE_STATE;   /* Set message information. */
        cp->keyword = (uint16_t)USB_NOT_USED;                   /* Not use */
        cp->status      = (uint16_t)USB_NOT_USED;               /* Not use */
        cp->complete    = (USB_CB_t)complete;                   /* Set Callback function */
        cp->ip = ptr->ip;                                       /* IP number(0or1) */
        cp->ipp = ptr->ipp;                                     /* IP Address(USB0orUSB1) */

        /* Send message */
        err = R_USB_SND_MSG(USB_PCDC_MBX, (USB_MSG_t*)p_blf);
        if( err != USB_E_OK )
        {
            /* Send message failure */
            //SCI_printf( "### pcdcSetControlLineState snd_msg error (%ld)\n", err);
            err2 = R_USB_REL_BLK(USB_PCDC_MPL, (USB_MH_t)p_blf);
            if( err2 != USB_E_OK )
            {
                /* Release memoryblock failure */
                //SCI_printf( "### pcdcSetControlLineState rel_blk error (%ld)\n", err2 );
            }
        }
    }
    else
    {
        /* Get momoryblock failure */
        //SCI_printf( "### pcdcSetControlLineState pget_blk error (%ld)\n", err);
    }
} /* eof usb_pcdc_SetControlLineState */

/******************************************************************************
Function Name   : usb_pcdc_ControlTrans0
Description     : Class request processing(idle or setup stage)
Arguments       : USB_UTR_t *ptr       ; USB system internal structure. Selects channel.
                : USB_REQUEST_t *req   ; Pointer to Class request information
Return value    : none
******************************************************************************/
void usb_pcdc_ControlTrans0(USB_UTR_t *ptr, USB_REQUEST_t *req)
{
} /* eof usb_pcdc_ControlTrans0 */

/******************************************************************************
Function Name   : usb_pcdc_ControlTrans2
Description     : Class request processing (control write data stage)
Arguments       : USB_UTR_t *ptr       ; USB system internal structure. Selects channel.
                : USB_REQUEST_t *req   ; Pointer to Class request information
Return value    : none
******************************************************************************/
void usb_pcdc_ControlTrans2(USB_UTR_t *ptr, USB_REQUEST_t *req)
{
    /* Is a request receive target Interface? */
    if( (req->ReqIndex == 0) && (req->ReqTypeRecip == USB_INTERFACE) )
    {
        /* Is a Request Type SetLineCoding? */
        if( req->ReqRequest == USB_PCDC_SET_LINE_CODING )
        {
            /* send Set_Line_Coding */
            R_usb_pstd_ControlWrite(ptr, 7, (uint8_t *)&usb_gcdc_LineCodingReq);
        }
        else
        {
            /* Set Stall */
            usb_pstd_SetStallPipe0( ptr );    /* Req Error */
        }
    }
    else
    {
        /* Set Stall */
        usb_pstd_SetStallPipe0( ptr );        /* Req Error */
    }
} /* eof usb_pcdc_ControlTrans2 */

/******************************************************************************
Function Name   : R_usb_pstd_ControlWrite
Description     : Start control write transfer (API). When a valid control write 
                : request from host is received, the ControlWrite function 
                : enables data reception from the host.
Arguments       : USB_UTR_t *ptr    : USB system internal structure.
                : uint32_t bsize    : Write size in bytes.
                : uint8_t *table    : Start address of write data buffer.
Return value    : none
******************************************************************************/
void R_usb_pstd_ControlWrite(USB_UTR_t *ptr, uint32_t bsize, uint8_t *table)
{
    usb_gcstd_DataCnt[ptr->ip][USB_PIPE0] = bsize;
    usb_gcstd_DataPtr[ptr->ip][USB_PIPE0] = table;

    usb_cstd_chg_curpipe(ptr, (uint16_t)USB_PIPE0, (uint16_t)USB_CUSE, USB_NO);
    /* Buffer clear */
    usb_creg_set_bclr( ptr, USB_CUSE );

    /* Interrupt enable */
    /* Enable ready interrupt */
    usb_creg_set_brdyenb(ptr, (uint16_t)USB_PIPE0);
    /* Enable not ready interrupt */
    usb_cstd_NrdyEnable(ptr, (uint16_t)USB_PIPE0);

    /* Set PID=BUF */
    usb_cstd_SetBuf(ptr, (uint16_t)USB_PIPE0);
}

/******************************************************************************
Function Name   : usb_pcdc_ControlTrans5
Description     : Process class request (control write status stage)
Arguments       : USB_UTR_t *ptr       ; USB system internal structure. Selects channel.
                : USB_REQUEST_t *req   ; Pointer to Class request information
Return value    : none
******************************************************************************/
void usb_pcdc_ControlTrans5(USB_UTR_t *ptr, USB_REQUEST_t *req)
{
    /* Is a request receive target Interface? */
    if( (req->ReqIndex == 0) && (req->ReqTypeRecip == USB_INTERFACE) )
    {
        /* Is a Request Type SetLineCoding? */
        if( req->ReqRequest == USB_PCDC_SET_LINE_CODING )
        {
            usb_cstd_SetBuf(ptr, (uint16_t)USB_PIPE0);          /* Set BUF */
            /* send Set_Line_Coding */
            usb_pcdc_SetLineCoding_req(ptr);
        }
        else
        {
            /* Set Stall */
            usb_pstd_SetStallPipe0( ptr );    /* Req Error */
        }
    }
    else
    {
        /* Set Stall */
        usb_pstd_SetStallPipe0( ptr );        /* Req Error */
    }
    R_usb_pstd_ControlEnd(ptr, (uint16_t)USB_CTRL_END);
} /* eof usb_pcdc_ControlTrans5 */

/******************************************************************************
Function Name   : usb_pcdc_SetLineCoding_req
Description     : Class request processing for SetLineCoding request
Arguments       : USB_UTR_t *ptr       ; USB system internal structure. Selects channel.
Return value    : none
******************************************************************************/
void usb_pcdc_SetLineCoding_req(USB_UTR_t *ptr)
{
    /* Class request Set_Line_Coding */
    usb_pcdc_SetLineCoding(ptr, &usb_cstd_DummyFunction);
} /* eof usb_pcdc_SetLineCoding_req */

/******************************************************************************
Function Name   : usb_pcdc_SetLineCoding
Description     : Peripheral Set Line Coding request
Arguments       : USB_UTR_t     *ptr        ; USB system internal structure. Selects channel.
                : USB_CB_t complete    ; Pointer to Callback function
Return value    : none
******************************************************************************/
void usb_pcdc_SetLineCoding(USB_UTR_t *ptr, USB_CB_t complete)
{
    USB_MH_t    p_blf;
    USB_ER_t    err, err2;
    USB_UTR_t   *cp;

    /* Get mem pool blk */
    err = R_USB_PGET_BLK(USB_PCDC_MPL, &p_blf);
    if( err == USB_E_OK )
    {
        cp = (USB_UTR_t*)p_blf;
        cp->msghead = (USB_MH_t)NULL;
        cp->msginfo = (uint16_t)USB_PCDC_PSET_LINE_CODING;      /* Set message information. */
        cp->keyword = (uint16_t)USB_NOT_USED;                   /* Not use */
        cp->status      = (uint16_t)USB_NOT_USED;               /* Not use */
        cp->complete    = (USB_CB_t)complete;                   /* Set Callback function */
        cp->ip = ptr->ip;                                       /* IP number(0or1) */
        cp->ipp = ptr->ipp;                                     /* IP Address(USB0orUSB1) */

        /* Send message */
        err = R_USB_SND_MSG(USB_PCDC_MBX, (USB_MSG_t*)p_blf);
        if( err != USB_E_OK )
        {
            /* Send message failure */
            //SCI_printf( "### pcdcGetLineCoding snd_msg error (%ld)\n", err );
            err2 = R_USB_REL_BLK(USB_PCDC_MPL, (USB_MH_t)p_blf);
            if( err2 != USB_E_OK )
            {
                /* Release memoryblock failure */
                //SCI_printf( "### pcdcGetLineCoding rel_blk error (%ld)\n", err2 );
            }
        }
    }
    else
    {
        /* Get momoryblock failure */
        //SCI_printf( "### pcdcGetLineCoding pget_blk error (%ld)\n", err );
    }
} /* eof usb_pcdc_SetLineCoding */



/******************************************************************************
Function Name   : R_usb_pcdc_set_interface
Description     : Set_Interface
Arguments       : USB_UTR_t *ptr       ; USB system internal structure. Selects channel.
                : uint16_t data1       ; Not use
                : uint16_t data2       ; Not use
Return value    : none
******************************************************************************/
void R_usb_pcdc_set_interface(USB_UTR_t *ptr, uint16_t data1, uint16_t data2)
{
} /* eof R_usb_pcdc_set_interface */

/******************************************************************************
Function Name   : cdc_suspend
Description     : Peripheral Communications Devices Class suspend function
Arguments       : USB_UTR_t *ptr            : IP Information(Mode,IP No.,Reg Address)
                : uint16_t data1            : Not use
                : uint16_t data2            : Not use
Return value    : none
******************************************************************************/
void cdc_suspend(USB_UTR_t *ptr, uint16_t data1, uint16_t data2)
{

    USB_SUSPEND_SLEEP( ptr );

}   /* eof cdc_suspend() */

/******************************************************************************
Function Name   : cdc_detach
Description     : Peripheral Communications Devices Class close function
Arguments       : USB_UTR_t *ptr            : IP Information(Mode,IP No.,Reg Address)
                : uint16_t data1            : Not use
                : uint16_t data2            : Not use
Return value    : none
******************************************************************************/
void cdc_detach(USB_UTR_t *ptr, uint16_t data1, uint16_t data2)
{

    if( USB_ON == usb_gcdc_connected )
    {
        cdc_dev_info.state = STATE_DETACH;      /* Set Application status  */
        usb_gcdc_connected = USB_OFF;           /* Peri CDC Application process disable */
    }
    cdc_low_power_control( STATE_ATTACH );  /* MCU Low power control */

}   /* eof cdc_detach() */

/******************************************************************************
Function Name   : cdc_configured
Description     : Peripheral Communications Devices Class open function
Arguments       : USB_UTR_t *ptr            : IP Information(Mode,IP No.,Reg Address)
                : uint16_t data1            : Not use
                : uint16_t data2            : Not use
Return value    : none
******************************************************************************/
void cdc_configured(USB_UTR_t *ptr, uint16_t data1, uint16_t data2)
{

    usb_gcdc_connected = USB_ON;            /* Peri CDC Application process enable */
    cdc_event_set( EVENT_CONFIGERD );       /* Set Event()  */

}   /* eof cdc_configured() */

/******************************************************************************
Function Name   : R_usb_pstd_DriverRegistration
Description     : Register pipe information table, descriptor information table, 
                : callback function, etc. This info is specified by the data in
                : the structure USB_PCDREG_t.
Arguments       : USB_UTR_t *ptr : USB system internal structure.
                : USB_PCDREG_t *registinfo : Class driver structure.
Return value    : none
******************************************************************************/
void R_usb_pstd_DriverRegistration(USB_UTR_t *ptr, USB_PCDREG_t *registinfo)
{
    USB_PCDREG_t    *driver;

    driver = &usb_gpstd_Driver;
    /* Pipe define table address */
    driver->pipetbl     = registinfo->pipetbl;
    /* Device descriptor table address */
    driver->devicetbl   = registinfo->devicetbl;
    /* Qualifier descriptor table address */
    driver->qualitbl    = registinfo->qualitbl;
    /* Configuration descriptor table address */
    driver->configtbl   = registinfo->configtbl;
    /* Other configuration descriptor table address */
    driver->othertbl    = registinfo->othertbl;
    /* String descriptor table address */
    driver->stringtbl   = registinfo->stringtbl;
    /* Driver init */
    driver->classinit   = registinfo->classinit;
    /* Device default */
    driver->devdefault  = registinfo->devdefault;
    /* Device configured */
    driver->devconfig   = registinfo->devconfig;
    /* Device detach */
    driver->devdetach   = registinfo->devdetach;
    /* Device suspend */
    driver->devsuspend  = registinfo->devsuspend;
    /* Device resume */
    driver->devresume   = registinfo->devresume;
    /* Interfaced change */
    driver->interface   = registinfo->interface;
    /* Control transfer */
    driver->ctrltrans   = registinfo->ctrltrans;
    /* Initialized device driver */
    (*driver->classinit)(ptr, (uint16_t)USB_NO_ARG, (uint16_t)USB_NO_ARG);
}/* eof R_usb_pstd_DriverRegistration() */

/******************************************************************************
Function Name   : R_usb_pstd_usbdriver_start
Description     :  Start peripheral USB low-level driver task.
Argument        : none
Return          : none
******************************************************************************/
void R_usb_pstd_usbdriver_start( USB_UTR_t *ptr )
{
    /* Task Start Processing */
    R_usb_pstd_PcdOpen(ptr);            /* Pcd open */
}

/******************************************************************************
Function Name   : R_usb_pstd_PcdOpen
Description     : Start PCD(Peripheral Control Driver) task (RTOS version)
                : Initialize pipe information (non-OS version).
Arguments       : USB_UTR_t *ptr : USB system internal structure. Selects channel.
Return value    : USB_ER_t       : Error info.
******************************************************************************/
USB_ER_t R_usb_pstd_PcdOpen(USB_UTR_t *ptr)
{
    uint16_t    i;

    R_usb_cstd_SetTaskPri(USB_PCD_TSK,  USB_PRI_0);

    for( i = USB_PIPE0; i <= USB_MAX_PIPE_NO; i++ )
    {
        usb_gpstd_StallPipe[i]  = USB_DONE;
        usb_gcstd_Pipe[ptr->ip][i]      = (USB_UTR_t*)USB_NULL;
    }

    return USB_E_OK;
}/* eof R_usb_pstd_PcdOpen */

/******************************************************************************
Function Name   : R_usb_cstd_GetUsbIpAdr  
Description     : Return USB register base address of specified USB IP.
Arguments       : uint16_t  ipno        : USB IP No. that requires the base 
                                          address value 
Return value    : USB_REGADR_t          : Address value
******************************************************************************/
USB_REGADR_t    R_usb_cstd_GetUsbIpAdr( uint16_t ipno )
{
    return (USB_REGADR_t)usb_cstd_GetUsbIpAdr( ipno );
}/* eof R_usb_cstd_GetUsbIpAdr */
 
/******************************************************************************
Function Name   : usb_cstd_GetUsbIpAdr
Description     : Get base address of the selected USB channel's peripheral 
                : registers.
Argument        : uint16_t ipnum  : USB_USBIP_0 (0), or USB_USBIP_1 (1).
Return          : USB_REGADR_t    : A pointer to the USB_597IP register 
                                  : structure USB_REGISTER containing all USB
                                  : channel's registers.
******************************************************************************/
USB_REGADR_t    usb_cstd_GetUsbIpAdr( uint16_t ipnum )
{
    USB_REGADR_t    ptr;

    if( ipnum == USB_USBIP_0 )
    {
        ptr = (USB_REGADR_t)&USB0;
    }
    else if( ipnum == USB_USBIP_1 )
    {

        USB_DEBUG_HOOK( USB_DEBUG_HOOK_STD | USB_DEBUG_HOOK_CODE1 );
    }
    else
    {
        USB_DEBUG_HOOK( USB_DEBUG_HOOK_STD | USB_DEBUG_HOOK_CODE1 );
    }

    return ptr;
} /* eof usb_cstd_GetUsbIpAdr() */

/******************************************************************************
Function Name   : apl_init
Description     : Peri CDC Application memory clear
Argument        : USB_UTR_t *ptr        : USB system internal structure.
Return          : none
******************************************************************************/
void apl_init( void )
{

    uint8_t     j;

    /* Initialeze hid device state */
    cdc_dev_info.state = STATE_ATTACH;                      /* Set Application status  */
    cdc_dev_info.event_cnt = 0;
    for( j = 0; j < EVENT_MAX; j++ )
    {
        cdc_dev_info.event[j] = EVENT_NONE;
    }

    /* Clear data for USB TX and RX */
    memset( cdc_trans_data, 0, CDC_DATA_LEN );

}   /* eof apl_init() */

/******************************************************************************
Function Name   : cdc_low_power_control
Description     : 
Arguments       : none
Return value    : none
******************************************************************************/
void cdc_low_power_control( uint16_t state )
{

    uint16_t    res[8];

    R_usb_pstd_DeviceInformation( &cdc_utr, (uint16_t *)res );
    if( 0 == (  USB_VBSTS & res[0] ) )
    {
        if( STATE_ATTACH == state )
        {
			USB_DETACH_SLEEP( &cdc_utr );

        }
    }
    else if( USB_DS_SPD_CNFG == (  USB_DS_SPD_CNFG & res[0] ) )
    {
        if( STATE_DATA_TRANSFER == state )
        {
            USB_SUSPEND_SLEEP( &cdc_utr );
        }
    }
    else
    {
    }

}   /* eof cdc_low_power_control() */

/******************************************************************************
Function Name   : usb_cstd_ScheInit
Description     : Scheduler initialization.
Argument        : none
Return          : none
******************************************************************************/
void usb_cstd_ScheInit(void)
{
    uint8_t i;
    uint8_t j;

    /* Initial Scheduler */
    usb_scstd_ID_use        = USB_NONE;
    usb_scstd_ScheduleFlag  = USB_NONE;

    /* Initialize  priority table pointer and priority table */
    for(i=0;i!=USB_PRIMAX;i++)
    {
        usb_scstd_PriR[i]   = USB_NONE;
        usb_scstd_PriW[i]   = USB_NONE;
        for(j=0;j!=USB_TABLEMAX;j++)
        {
            usb_scstd_TableID[i][j] = USB_IDMAX;
        }
    }

    /* Initialize block table */
    for(i=0;i!=USB_BLKMAX;i++)
    {
        usb_scstd_BlkFlg[i]         = USB_NONE;
    }

    /* Initialize priority */
    for(i=0;i!=USB_IDMAX;i++)
    {
        usb_scstd_Pri[i]            = (uint8_t)USB_IDCLR;
        for( j =0; j <USB_WAIT_EVENT_MAX ; j++ )
        {
            usb_scstd_WaitAdd[i][j] = (USB_MSG_t*)USB_NONE;
            usb_scstd_WaitCounter[i][j] = USB_NONE;
        }
    }
}

/******************************************************************************
Function Name   : R_usb_cstd_Scheduler
Description     : The scheduler.
Argument        : none
Return          : none
******************************************************************************/
void R_usb_cstd_Scheduler(void)
{
    uint8_t    usb_pri;         /* Priority Counter */
    uint8_t    usb_read;        /* Priority Table read pointer */

    /* wait msg */
    usb_cstd_WaitScheduler();

    /* Priority Table reading */
    usb_pri = USB_CNTCLR;
    while( usb_pri < USB_PRIMAX )
    {
        usb_read    = usb_scstd_PriR[usb_pri];
        if( usb_read != usb_scstd_PriW[usb_pri] )
        {
            /* Priority Table read pointer increment */
            usb_read++;     
            if( usb_read >= USB_TABLEMAX )
            {
                usb_read = USB_TBLCLR;
            }
            /* Set practise message */
            usb_scstd_ID_use    = usb_scstd_TableID[usb_pri][usb_read];
            usb_scstd_Add_use   = usb_scstd_TableAdd[usb_pri][usb_read];
            usb_scstd_TableID[usb_pri][usb_read]    = USB_IDMAX;
            usb_scstd_PriR[usb_pri]                 = usb_read;
            usb_scstd_ScheduleFlag                  = USB_FLGSET;
            usb_pri = USB_PRIMAX;
        }
        else
        {
            usb_pri++;
        }
    }
}

/******************************************************************************
Function Name   : usb_cstd_WaitScheduler
Description     : Schedules a wait request.
Argument        : none
Return          : none
******************************************************************************/
void usb_cstd_WaitScheduler(void)
{
    USB_ER_t    err;
    uint8_t     id;
    uint8_t i;

    for( id=0; id < USB_IDMAX; id++ )
    {
        for( i =0; i <USB_WAIT_EVENT_MAX ; i++ )
        {
            if(usb_scstd_WaitCounter[id][i] != 0)
            {
                usb_scstd_WaitCounter[id][i]--;
                if(usb_scstd_WaitCounter[id][i] == 0)
                {
                    err = usb_cstd_SndMsg(id, usb_scstd_WaitAdd[id][i]);
                    if( err != USB_E_OK )
                    {
                        usb_scstd_WaitCounter[id][i]++;
                    }
                }
            }
        }
    }
}

/******************************************************************************
Function Name   : R_usb_cstd_CheckSchedule
Description     : Check schedule flag to see if caller's "time has come", then 
                : clear it.
Argument        : none
Return          : flg   : usb_scstd_ScheduleFlag
******************************************************************************/
uint8_t R_usb_cstd_CheckSchedule(void)
{
    uint8_t flg;

    flg = usb_scstd_ScheduleFlag;
    usb_scstd_ScheduleFlag = USB_FLGCLR;
    return flg;
}

/******************************************************************************
Function Name   : usb_cstd_iSndMsg
Description     : Send a message to the specified id (mailbox) while executing 
                : an interrupt.
Argument        : uint8_t id        : ID number (mailbox).
                : USB_MSG_t* mess   : Message pointer
Return          : USB_ER_t          : USB_E_OK / USB_E_ERROR
******************************************************************************/
USB_ER_t usb_cstd_iSndMsg( uint8_t id, USB_MSG_t* mess )
{
    uint8_t usb_pri;        /* Task Priority */
    uint8_t usb_write;      /* Priority Table Writing pointer */

    if( id < USB_IDMAX )
    {
        /* Read priority and table pointer */
        usb_pri     = usb_scstd_Pri[id];
        usb_write   = usb_scstd_PriW[usb_pri];
        if( usb_pri < USB_PRIMAX )
        {
            /* Renewal write pointer */
            usb_write++;
            if( usb_write >= USB_TABLEMAX )
            {
                usb_write = USB_TBLCLR;
            }
            /* Check pointer */
            if( usb_write == usb_scstd_PriR[usb_pri])
            {
                return  USB_E_ERROR;
            }
            /* Save message */
            /* Set priority table */
            usb_scstd_TableID[usb_pri][usb_write]   = id;
            usb_scstd_TableAdd[usb_pri][usb_write]  = mess;
            usb_scstd_PriW[usb_pri]                 = usb_write;
            return  USB_E_OK;
        }
    }
    //SCI_printf("SND_MSG ERROR !!\n");
    return  USB_E_ERROR;

}

/******************************************************************************
Function Name   : usb_cpu_int_enable
Description     : USB Interrupt Enable
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel. 
Return value    : void
******************************************************************************/
void usb_cpu_int_enable(USB_UTR_t *ptr)
{
    if( ptr->ip == USB_USBIP_0 )
    {
        /* Interrupt enable register (USB0 USBIO enable)
        b0 IEN0 Interrupt enable bit
        b1 IEN1 Interrupt enable bit
        b2 IEN2 Interrupt enable bit
        b3 IEN3 Interrupt enable bit
        b4 IEN4 Interrupt enable bit
        b5 IEN5 Interrupt enable bit
        b6 IEN6 Interrupt enable bit
        b7 IEN7 Interrupt enable bit
        */
        ICU.IER[4].BIT.IEN3     = 1;
        ICU.IER[4].BIT.IEN1     = usb_gcstd_D0fifo[ptr->ip];
        ICU.IER[4].BIT.IEN2     = usb_gcstd_D1fifo[ptr->ip];
    }

    if (ptr->ip == USB_USBIP_1)
    {
        /* Interrupt enable register (USB1 USBIO enable)
        b0 IEN0 Interrupt enable bit
        b1 IEN1 Interrupt enable bit
        b2 IEN2 Interrupt enable bit
        b3 IEN3 Interrupt enable bit
        b4 IEN4 Interrupt enable bit
        b5 IEN5 Interrupt enable bit
        b6 IEN6 Interrupt enable bit
        b7 IEN7 Interrupt enable bit
        */
        ICU.IER[4].BIT.IEN6     = 1;
        ICU.IER[4].BIT.IEN4     = usb_gcstd_D0fifo[ptr->ip];
        ICU.IER[4].BIT.IEN5     = usb_gcstd_D1fifo[ptr->ip];
    }
}

/******************************************************************************
Function Name   : usb_cpu_int_disable
Description     : USB Interrupt disable
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel. 
Return value    : void
******************************************************************************/
void usb_cpu_int_disable(USB_UTR_t *ptr)
{
    if( ptr->ip == USB_USBIP_0 )
    {
        /* Interrupt enable register (USB0 USBIO disable)
        b0 IEN0 Interrupt enable bit
        b1 IEN1 Interrupt enable bit
        b2 IEN2 Interrupt enable bit
        b3 IEN3 Interrupt enable bit
        b4 IEN4 Interrupt enable bit
        b5 IEN5 Interrupt enable bit
        b6 IEN6 Interrupt enable bit
        b7 IEN7 Interrupt enable bit
        */
        ICU.IER[4].BIT.IEN3         = 0;
        usb_gcstd_D0fifo[ptr->ip]   = ICU.IER[4].BIT.IEN1;
        ICU.IER[4].BIT.IEN1         = 0;
        usb_gcstd_D1fifo[ptr->ip]   = ICU.IER[4].BIT.IEN2;
        ICU.IER[4].BIT.IEN2         = 0;
    }

    if (ptr->ip == USB_USBIP_1)
    {
        /* Interrupt enable register (USB1 USBIO disable)
        b0 IEN0 Interrupt enable bit
        b1 IEN1 Interrupt enable bit
        b2 IEN2 Interrupt enable bit
        b3 IEN3 Interrupt enable bit
        b4 IEN4 Interrupt enable bit
        b5 IEN5 Interrupt enable bit
        b6 IEN6 Interrupt enable bit
        b7 IEN7 Interrupt enable bit
        */
        ICU.IER[4].BIT.IEN6         = 0;
        usb_gcstd_D0fifo[ptr->ip]   = ICU.IER[4].BIT.IEN4;
        ICU.IER[4].BIT.IEN4         = 0;
        usb_gcstd_D1fifo[ptr->ip]   = ICU.IER[4].BIT.IEN5;
        ICU.IER[4].BIT.IEN5         = 0;
    }
}

/******************************************************************************
Function Name   : usb_pstd_InterruptEnable
Description     : Enable the VBSE interrupt (VBUS), and the DVSE (Device State 
                : Transition) and CTRE (Control Transfer Stage Transition) int-
                : errupts.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
Return value    : none
******************************************************************************/
void usb_pstd_InterruptEnable(USB_UTR_t *ptr)
{
    /* Enable VBSE, DVSE, CTRE */
    usb_creg_set_intenb( ptr, (USB_VBSE | USB_DVSE | USB_CTRE ));
} /* eof usb_pstd_InterruptEnable() */

/******************************************************************************
Function Name   : usb_pstd_SetStall
Description     : Set the specified pipe's PID to STALL.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t pipe   : Pipe Number
Return value    : none
******************************************************************************/
void usb_pstd_SetStall(USB_UTR_t *ptr, uint16_t pipe)
{
    /* PIPE control reg set */
    usb_creg_set_pid( ptr, pipe, USB_PID_STALL );
} /* eof usb_pstd_SetStall() */

/******************************************************************************
Function Name   : usb_pstd_InterruptHandler
Description     : Determine which USB interrupt occurred and report results to 
                : the USB_UTR_t argument's ipp, keyword, and status members.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
Return value    : none
******************************************************************************/
void usb_pstd_InterruptHandler(USB_UTR_t *ptr)
{
    uint16_t    intsts0, intenb0, ists0;
    uint16_t    brdysts, brdyenb, bsts;
    uint16_t    nrdysts, nrdyenb, nsts;
    uint16_t    bempsts, bempenb, ests;

    /* Register Save */
    intsts0 = ptr->ipp->INTSTS0.WORD;
    brdysts = ptr->ipp->BRDYSTS.WORD;
    nrdysts = ptr->ipp->NRDYSTS.WORD;
    bempsts = ptr->ipp->BEMPSTS.WORD;
    intenb0 = ptr->ipp->INTENB0.WORD;
    brdyenb = ptr->ipp->BRDYENB.WORD;
    nrdyenb = ptr->ipp->NRDYENB.WORD;
    bempenb = ptr->ipp->BEMPENB.WORD;
    
    ptr->keyword = USB_INT_UNKNOWN;
    ptr->status  = 0;

    /* Interrupt status get */
    ists0 = (uint16_t)(intsts0 & intenb0);
    bsts  = (uint16_t)(brdysts & brdyenb);
    nsts  = (uint16_t)(nrdysts & nrdyenb);
    ests  = (uint16_t)(bempsts & bempenb);

    if( (intsts0 & (USB_VBINT|USB_RESM|USB_SOFR|USB_DVST|USB_CTRT|USB_BEMP|USB_NRDY|USB_BRDY)) == 0u )
    {
        return;
    }

    /***** Processing USB bus signal *****/
    /***** Resume signal *****/
    if( (ists0 & USB_RESM) == USB_RESM )
    {
        ptr->ipp->INTSTS0.WORD = (uint16_t)~USB_RESM;
        ptr->keyword = USB_INT_RESM;
    }
    /***** Vbus change *****/
    else if( (ists0 & USB_VBINT) == USB_VBINT )
    {
        /* Status clear */
        ptr->ipp->INTSTS0.WORD = (uint16_t)~USB_VBINT;
        ptr->keyword = USB_INT_VBINT;
    }
    /***** SOFR change *****/
    else if( (ists0 & USB_SOFR) == USB_SOFR )
    {
        /* SOFR Clear */
        ptr->ipp->INTSTS0.WORD = (uint16_t)~USB_SOFR;
        ptr->keyword = USB_INT_SOFR;
    }

    /***** Processing device state *****/
    /***** DVST change *****/
    else if( (ists0 & USB_DVST) == USB_DVST )
    {
        /* DVST clear */
        ptr->ipp->INTSTS0.WORD = (uint16_t)~USB_DVST;
        ptr->keyword = USB_INT_DVST;
        ptr->status  = intsts0;
    }

    /***** Processing PIPE0 data *****/
    else if( ((ists0 & USB_BRDY) == USB_BRDY) && ((bsts & USB_BRDY0) == USB_BRDY0) )
    {
        ptr->ipp->BRDYSTS.WORD = (uint16_t)~USB_BRDY0;
        ptr->keyword = USB_INT_BRDY;
        ptr->status  = USB_BRDY0;
    }
    else if( ((ists0 & USB_BEMP) == USB_BEMP) && ((ests & USB_BEMP0) == USB_BEMP0) )
    {
        ptr->ipp->BEMPSTS.WORD = (uint16_t)~USB_BEMP0;
        ptr->keyword = USB_INT_BEMP;
        ptr->status  = USB_BEMP0;
    }
    else if( ((ists0 & USB_NRDY) == USB_NRDY) && ((nsts & USB_NRDY0) == USB_NRDY0) )
    {
        ptr->ipp->NRDYSTS.WORD = (uint16_t)~USB_NRDY0;
        ptr->keyword = USB_INT_NRDY;
        ptr->status  = USB_NRDY0;
    }

    /***** Processing setup transaction *****/
    else if( (ists0 & USB_CTRT) == USB_CTRT )
    {
        /* CTSQ bit changes later than CTRT bit for ASSP. */
        /* CTSQ reloading */
        ptr->status = usb_creg_read_intsts( ptr );
        /* USB_CTRT clear */
        ptr->ipp->INTSTS0.WORD = (uint16_t)~USB_CTRT;
        ptr->keyword = USB_INT_CTRT;

        if( (uint8_t)(ptr->status & USB_CTSQ) == USB_CS_SQER )
        {
            usb_preg_clr_sts_valid( ptr );
            ptr->keyword = USB_INT_UNKNOWN;
            ptr->status  = 0;
            return;
        }
    }

    /***** Processing PIPE1-MAX_PIPE_NO data *****/
    /***** EP0-7 BRDY *****/
    else if( (ists0 & USB_BRDY) == USB_BRDY )
    {
        ptr->ipp->BRDYSTS.WORD = (uint16_t)~bsts;
        ptr->keyword = USB_INT_BRDY;
        ptr->status  = bsts;
    }
    /***** EP0-7 BEMP *****/
    else if( (ists0 & USB_BEMP) == USB_BEMP )
    {
        ptr->ipp->BEMPSTS.WORD = (uint16_t)~ests;
        ptr->keyword = USB_INT_BEMP;
        ptr->status  = ests;
    }
    /***** EP0-7 NRDY *****/
    else if( (ists0 & USB_NRDY) == USB_NRDY )
    {
        ptr->ipp->NRDYSTS.WORD = (uint16_t)~nsts;
        ptr->keyword = USB_INT_NRDY;
        ptr->status  = nsts;
    }
    else
    {
    }
} /* eof usb_pstd_InterruptHandler() */

/******************************************************************************
Function Name   : usb_cstd_is_set_frdy
Description     : Changes the specified FIFO port by the specified pipe.
                : Please change the wait time for your MCU.
Arguments       : USB_UTR_t *ptr    : USB system internal structure. Selects channel.
                : uint16_t pipe     : Pipe Number
                : uint16_t fifosel  : FIFO select
                : uint16_t isel     : ISEL bit status
Return value    : FRDY status
******************************************************************************/
uint16_t usb_cstd_is_set_frdy(USB_UTR_t *ptr, uint16_t pipe, uint16_t fifosel, uint16_t isel)
{
    uint16_t    buffer, i;

    /* Changes the FIFO port by the pipe. */
    usb_cstd_chg_curpipe(ptr, pipe, fifosel, isel);

    for( i = 0; i < 4; i++ )
    {
        buffer = usb_creg_read_fifoctr( ptr, fifosel );

        if( (uint16_t)(buffer & USB_FRDY) == USB_FRDY )
        {
            return (buffer);
        }
        //SCI_printf("*** FRDY wait pipe = %d\n", pipe);
        
        /* Caution!!!
     * Depending on the external bus speed of CPU, you may need to wait
     * for 100ns here.
     * For details, please look at the data sheet.   */
    /***** The example of reference. *****/
        buffer = usb_creg_read_syscfg( ptr, USB_PORT0 );
        buffer = usb_creg_read_syssts( ptr, USB_PORT0 );
    /*************************************/
    }
    return (USB_FIFOERROR);
}/* eof of function usb_cstd_is_set_frdy() */

/*****************************************************************************
ƒŒƒWƒXƒ^ƒAƒNƒZƒX
*****************************************************************************/
/******************************************************************************
Function Name   : usb_creg_set_mbw
Description     : Set MBW-bits (CFIFO Port Access Bit Width) of the FIFOSEL cor-
                : responding to the specified PIPEMODE, to select 8 or 16-bit 
                : wide FIFO port access.
Arguments       : USB_UTR_t *ptr       : USB internal structure. Selects USB channel.
                : uint16_t pipemode : CUSE/D0DMA/D1DMA.
                : uint16_t data     : Defined value of 8 (data = 0x0000) or 16 bit 
                : (data = 0x0400), 32 bit (data = 0x0800) access mode.
Return value    : none
******************************************************************************/
void    usb_creg_set_mbw( USB_UTR_t *ptr, uint16_t pipemode, uint16_t data )
{
    volatile uint16_t    *reg_p;

    reg_p = usb_creg_get_fifosel_adr( ptr, pipemode );
    if( ptr->ip == USB_USBIP_0 )
    {
        if( data != 0 )
        {
            *reg_p |= USB_MBW_16;
        }
        else
        {
            *reg_p &= ~USB_MBW_16;
        }
    }
    else if ( ptr->ip == USB_USBIP_1 )
    {
        *reg_p &= ~USB_MBW;

        if( data != 0 )
        {
            *reg_p |= data;
        }
    }
} /* eof usb_creg_set_mbw() */

/******************************************************************************
Function Name   : usb_creg_read_intsts
Description     : Returns INTSTS0 register content.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
Return value    : INTSTS0 content
******************************************************************************/
uint16_t    usb_creg_read_intsts( USB_UTR_t *ptr )
{
    return ptr->ipp->INTSTS0.WORD;
} /* eof usb_creg_read_intsts() */

/******************************************************************************
Function Name   : usb_creg_write_pipesel
Description     : Specified data is written to PIPESEL register.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  data  : The value to write.
Return value    : none
******************************************************************************/
void    usb_creg_write_pipesel( USB_UTR_t *ptr, uint16_t data )
{
    ptr->ipp->PIPESEL.WORD = data;
} /* eof usb_creg_write_pipesel() */

/******************************************************************************
Function Name   : usb_creg_read_pipecfg
Description     : Returns PIPECFG register content.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
Return value    : PIPECFG content
******************************************************************************/
uint16_t    usb_creg_read_pipecfg( USB_UTR_t *ptr )
{
    return (uint16_t)ptr->ipp->PIPECFG.WORD;
} /* eof usb_creg_read_pipecfg() */

/******************************************************************************
Function Name   : usb_preg_clr_sts_valid
Description     : Clear the Setup Packet Reception interrupt flag.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel. 
Return value    : none
******************************************************************************/
void    usb_preg_clr_sts_valid( USB_UTR_t *ptr )
{
    ptr->ipp->INTSTS0.WORD = (uint16_t)~USB_VALID;
} /* eof usb_preg_clr_sts_valid() */

/******************************************************************************
Function Name   : usb_creg_set_intenb
Description     : Bit(s) to be set in INTENB register, 
                : enabling the respective USB interrupt(s).
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  data  : Bit pattern: Respective interrupts with '1' 
                                  : will be enabled.
Return value    : none
******************************************************************************/
void    usb_creg_set_intenb( USB_UTR_t *ptr, uint16_t data )
{
    ptr->ipp->INTENB0.WORD |= data;
} /* eof usb_creg_set_intenb() */

/******************************************************************************
Function Name   : usb_creg_set_sqclr
Description     : The SQCLR-bit (Toggle Bit Clear) is set in the specified pipe's 
                : control register. Setting SQSET to 1 makes DATA0 the expected 
                : data in the pipe's next transfer.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  pipeno: Pipe number.
Return value    : none
******************************************************************************/
void    usb_creg_set_sqclr( USB_UTR_t *ptr, uint16_t pipeno )
{
    if( pipeno == USB_PIPE0 )
    {
        ptr->ipp->DCPCTR.WORD |= USB_SQCLR;
    }
    else
    {
        volatile uint16_t    *reg_p;

        reg_p = ((uint16_t *)&(ptr->ipp->PIPE1CTR) + (pipeno - 1));
        *reg_p |= USB_SQCLR;
    }
} /* eof usb_creg_set_sqclr() */

/******************************************************************************
Function Name   : usb_preg_set_dprpu
Description     : Set DPRPU-bit SYSCFG register.
                : (Enable D+Line pullup when PeripheralController function is selected) 
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel. 
Return value    : none
******************************************************************************/
void    usb_preg_set_dprpu( USB_UTR_t *ptr )
{
//#ifdef LSFUNC
//    ptr->ipp->SYSCFG.WORD |= USB_DMRPU;
//#else
    ptr->ipp->SYSCFG.WORD |= USB_DPRPU;
//#endif
} /* eof usb_preg_set_dprpu() */

/******************************************************************************
Function Name   : usb_preg_clr_dprpu
Description     : Clear DPRPU-bit of the SYSCFG register.
                : (Disable D+Line pullup when PeripheralController function is 
                : selected.)
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel. 
Return value    : none
******************************************************************************/
void    usb_preg_clr_dprpu( USB_UTR_t *ptr )
{
//#ifdef LSFUNC
//    ptr->ipp->SYSCFG.WORD &= ~USB_DMRPU;
//#else
    ptr->ipp->SYSCFG.WORD &= ~USB_DPRPU;
//#endif
} /* eof usb_preg_clr_dprpu() */

/******************************************************************************
Function Name   : usb_creg_set_bempenb
Description     : A bit is set in the specified pipe's BEMPENB enabling the 
                : respective pipe's BEMP interrupt(s).
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  pipeno: Pipe number.
Return value    : none
******************************************************************************/
void    usb_creg_set_bempenb( USB_UTR_t *ptr, uint16_t pipeno )
{
    ptr->ipp->BEMPENB.WORD |= (1 << pipeno);
} /* eof usb_creg_set_bempenb() */

/******************************************************************************
Function Name   : usb_creg_get_fifoctr_adr
Description     : Returns the *address* of the FIFOCTR register corresponding to 
                : specified PIPEMODE.
                : (FIFO Port Control Register.)
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t pipemode : CUSE/D0DMA/D1DMA.
Return value    : none
******************************************************************************/
static  void    *usb_creg_get_fifoctr_adr( USB_UTR_t *ptr, uint16_t pipemode )
{
    void    *reg_p;

    switch( pipemode )
    {
        case    USB_CUSE:
            reg_p = (void *)&(ptr->ipp->CFIFOCTR);
            break;
        case    USB_D0USE:
        case    USB_D0DMA:
            reg_p = (void *)&(ptr->ipp->D0FIFOCTR);
            break;
        case    USB_D1USE:
        case    USB_D1DMA:
            reg_p = (void *)&(ptr->ipp->D1FIFOCTR);
            break;
        default:
            USB_DEBUG_HOOK( USB_DEBUG_HOOK_STD | USB_DEBUG_HOOK_CODE13 );
            break;
    }
    return reg_p;
} /* eof usb_creg_get_fifoctr_adr() */

/******************************************************************************
Function Name   : usb_creg_write_fifo8
Description     : Data is written to the specified pipemode's FIFO register, 8-bits 
                : wide, corresponding to the specified PIPEMODE.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  pipdemode   : CUSE/D0DMA/D1DMA
                : uint8_t   data        : The value to write.
Return value    : none
******************************************************************************/
void        usb_creg_write_fifo8( USB_UTR_t *ptr, uint16_t pipemode, uint8_t data )
{

        switch( pipemode )
        {
            case    USB_CUSE:
                ptr->ipp->CFIFO.BYTE.L = data;
                break;
            case    USB_D0USE:
            case    USB_D0DMA:
                ptr->ipp->D0FIFO.BYTE.L = data;
                break;
            case    USB_D1USE:
            case    USB_D1DMA:
                ptr->ipp->D1FIFO.BYTE.L = data;
                break;
            default:
                USB_DEBUG_HOOK( USB_DEBUG_HOOK_STD | USB_DEBUG_HOOK_CODE10 );
                break;
        }
} /* eof usb_creg_write_fifo8() */

/******************************************************************************
Function Name   : usb_creg_get_fifosel_adr
Description     : Returns the *address* of the FIFOSEL register corresponding to 
                : specified PIPEMODE.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  pipemode  : CUSE/D0DMA/D1DMA
Return value    : none
******************************************************************************/
static  void    *usb_creg_get_fifosel_adr( USB_UTR_t *ptr, uint16_t pipemode )
{
    void    *reg_p;

    switch( pipemode )
    {
        case    USB_CUSE:
            reg_p = (void *)&(ptr->ipp->CFIFOSEL);
            break;
        case    USB_D0USE:
        case    USB_D0DMA:
            reg_p = (void *)&(ptr->ipp->D0FIFOSEL);
            break;
        case    USB_D1USE:
        case    USB_D1DMA:
            reg_p = (void *)&(ptr->ipp->D1FIFOSEL);
            break;
        default:
            USB_DEBUG_HOOK( USB_DEBUG_HOOK_STD | USB_DEBUG_HOOK_CODE12 );
            break;
    }
    return reg_p;
} /* eof usb_creg_get_fifosel_adr() */

/******************************************************************************
Function Name   : usb_cstd_GetD0fifo8Adr
Description     : Get 8 bits of used channel's D0FIFO register content.
Arguments       : USB_UTR_t *ptr : USB system internal structure. Selects channel.
Return          : Address of D0FIFO
******************************************************************************/
uint32_t    usb_cstd_GetD0fifo8Adr( USB_UTR_t *ptr )
{
    if(ptr->ip == USB_USBIP_0)
    {
        return (uint32_t)(&ptr->ipp->D0FIFO.BYTE.L);
    }
    else if(ptr->ip == USB_USBIP_1)
    {
        return (uint32_t)(&ptr->ipp->D0FIFO.BYTE.L);
    }

    return 0;
}/* eof usb_cstd_GetD0fifo8Adr() */

/******************************************************************************
Function Name   : usb_creg_set_dcfm
Description     : DCFM-bit set of register SYSCFG
                : (USB Host mode is selected.)
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
Return value    : none
******************************************************************************/
void    usb_creg_set_dcfm( USB_UTR_t *ptr )
{

    ptr->ipp->SYSCFG.WORD |= USB_DCFM;

} /* eof usb_creg_set_dcfm() */

/******************************************************************************
Function Name   : usb_creg_clr_dcfm
Description     : DCFM-bit clear of register SYSCFG.
                : (USB Peripheral mode is selected.)
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
Return value    : none
******************************************************************************/
void    usb_creg_clr_dcfm( USB_UTR_t *ptr )
{

    ptr->ipp->SYSCFG.WORD &= ~USB_DCFM;

} /* eof usb_creg_clr_dcfm() */

/******************************************************************************
Function Name   : usb_creg_clr_sts_bemp
Description     : Clear the PIPExBEMP status bit of the specified pipe to clear 
                : its BEMP interrupt status.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  pipeno: Pipe number.
Return value    : none
******************************************************************************/
void    usb_creg_clr_sts_bemp( USB_UTR_t *ptr, uint16_t pipeno )
{
    ptr->ipp->BEMPSTS.WORD = (uint16_t)~(1 << pipeno);
} /* eof usb_creg_clr_sts_bemp() */

/******************************************************************************
Function Name   : usb_creg_clr_sts_nrdy
Description     : Clear the PIPExNRDY status bit of the specified pipe to clear 
                : its NRDY interrupt status.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  pipeno: Pipe number.
Return value    : none
******************************************************************************/
void    usb_creg_clr_sts_nrdy( USB_UTR_t *ptr, uint16_t pipeno )
{
    ptr->ipp->NRDYSTS.WORD = (uint16_t)~(1 << pipeno);
} /* eof usb_creg_clr_sts_nrdy() */

/******************************************************************************
Function Name   : usb_creg_clr_sts_brdy
Description     : Clear the PIPExBRDY status bit of the specified pipe to clear 
                : its BRDY interrupt status.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  pipeno: Pipe number.
Return value    : none
******************************************************************************/
void    usb_creg_clr_sts_brdy( USB_UTR_t *ptr, uint16_t pipeno )
{
    ptr->ipp->BRDYSTS.WORD = (uint16_t)~(1 << pipeno);
} /* eof usb_creg_clr_sts_brdy() */

/******************************************************************************
Function Name   : usb_creg_set_csclr
Description     : Set CSCLR bit in the specified pipe's PIPECTR register
Arguments       : USB_UTR_t *ptr   : USB internal structure. Selects USB channel.
                : uint16_t  pipeno : Pipe number
Return value    : none
******************************************************************************/
void    usb_creg_set_csclr( USB_UTR_t *ptr, uint16_t pipeno )
{
    volatile uint16_t    *reg_p;

    reg_p = (uint16_t *)&(ptr->ipp->PIPE1CTR) + (pipeno - 1);

    *reg_p |= USB_CSCLR;
} /* eof usb_creg_set_csclr() */

/******************************************************************************
Function Name   : usb_creg_clr_brdyenb
Description     : Clear the PIPExBRDYE-bit of the specified pipe to prohibit 
                : BRDY interrupts of that pipe.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  pipeno: Pipe number.
Return value    : none
******************************************************************************/
void    usb_creg_clr_brdyenb( USB_UTR_t *ptr, uint16_t  pipeno )
{
    ptr->ipp->BRDYENB.WORD &= ~(1 << pipeno);
} /* eof usb_creg_clr_brdyenb() */	

/******************************************************************************
Function Name   : usb_creg_clr_nrdyenb
Description     : Clear the PIPExNRDYE-bit of the specified pipe to prohibit 
                : NRDY interrupts of that pipe.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  pipeno: Pipe number.
Return value    : none
******************************************************************************/
void    usb_creg_clr_nrdyenb(USB_UTR_t *ptr, uint16_t pipeno )
{
    ptr->ipp->NRDYENB.WORD &= ~(1 << pipeno);
} /* eof usb_creg_clr_nrdyenb() */

/******************************************************************************
Function Name   : usb_creg_clr_bempenb
Description     : Clear the PIPExBEMPE-bit of the specified pipe to prohibit 
                : BEMP interrupts of that pipe.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  pipeno: Pipe number.
Return value    : none
******************************************************************************/
void    usb_creg_clr_bempenb( USB_UTR_t *ptr, uint16_t pipeno )
{
    ptr->ipp->BEMPENB.WORD &= ~(1 << pipeno);
} /* eof usb_creg_clr_bempenb() */

/******************************************************************************
Function Name   : usb_creg_set_aclrm
Description     : The ACLRM-bit (Auto Buffer Clear Mode) is set in the specified 
                : pipe's control register.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  pipeno: Pipe number.
Return value    : none
******************************************************************************/
void    usb_creg_set_aclrm( USB_UTR_t *ptr, uint16_t pipeno )
{
    volatile uint16_t    *reg_p;

    reg_p = (uint16_t *)&(ptr->ipp->PIPE1CTR) + (pipeno - 1);

    *reg_p |= USB_ACLRM;
} /* eof usb_creg_set_aclrm() */

/******************************************************************************
Function Name   : usb_creg_clr_aclrm
Description     : Clear the ACLRM bit in the specified pipe's control register
                : to disable Auto Buffer Clear Mode.
                : its BEMP interrupt status.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  pipeno: Pipe number.
Return value    : none
******************************************************************************/
void    usb_creg_clr_aclrm( USB_UTR_t *ptr, uint16_t pipeno )
{
    volatile uint16_t    *reg_p;

    reg_p = (uint16_t *)&(ptr->ipp->PIPE1CTR) + (pipeno - 1);

    *reg_p &= ~USB_ACLRM;
} /* eof usb_creg_clr_aclrm() */

/******************************************************************************
Function Name   : usb_creg_set_trclr
Description     : The TRENB-bit (Transaction Counter Clear) is set in the speci-
                : fied pipe's control register to clear the current counter 
                : value.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  pipeno: Pipe number.
Return value    : none
******************************************************************************/
void    usb_creg_set_trclr( USB_UTR_t *ptr, uint16_t pipeno )
{
    volatile uint16_t    *reg_p;

    reg_p = (uint16_t *)&(ptr->ipp->PIPE1TRE) + (pipeno - 1) * 2;

    *reg_p |= USB_TRCLR;

} /* eof usb_creg_set_trclr() */

/******************************************************************************
Function Name   : usb_creg_write_pipetrn
Description     : Specified data is written to the specified pipe's PIPETRN reg-
                : ister.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  pipeno: Pipe number.
                : uint16_t  data  : The value to write.
Return value    : none
******************************************************************************/
void    usb_creg_write_pipetrn( USB_UTR_t *ptr, uint16_t pipeno, uint16_t data )
{
    volatile uint16_t    *reg_p;

    reg_p = (uint16_t *)&(ptr->ipp->PIPE1TRN) + ((pipeno - 1) * 2);

    *reg_p = data;
} /* eof usb_creg_write_pipetrn */

/******************************************************************************
Function Name   : usb_creg_set_trenb
Description     : The TRENB-bit (Transaction Counter Enable) is set in the speci-
                : fied pipe's control register, to enable the counter.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  pipeno: Pipe number.
Return value    : none
******************************************************************************/
void    usb_creg_set_trenb( USB_UTR_t *ptr, uint16_t pipeno )
{
    volatile uint16_t    *reg_p;

    reg_p = (uint16_t *)&(ptr->ipp->PIPE1TRE) + (pipeno - 1) * 2;

    *reg_p |= USB_TRENB;
} /* eof usb_creg_set_trenb() */

/******************************************************************************
Function Name   : usb_creg_write_pipecfg
Description     : Specified data is written to PIPECFG register.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  data  : The value to write.
Return value    : none
******************************************************************************/
void    usb_creg_write_pipecfg( USB_UTR_t *ptr, uint16_t data )
{
    ptr->ipp->PIPECFG.WORD = data;
} /* eof usb_creg_write_pipecfg() */

/******************************************************************************
Function Name   : usb_creg_write_pipebuf
Description     : Specified the value by 2nd argument is set to PIPEBUF register.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  data  : The value to write.
Return value    : none
******************************************************************************/
void    usb_creg_write_pipebuf( USB_UTR_t *ptr, uint16_t data )
{

} /* eof usb_creg_write_pipebuf() */

/******************************************************************************
Function Name   : usb_creg_write_pipemaxp
Description     : Specified data is written to PIPEMAXP register.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  data  : The value to write.
Return value    : none
******************************************************************************/
void    usb_creg_write_pipemaxp( USB_UTR_t *ptr, uint16_t data )
{
    ptr->ipp->PIPEMAXP.WORD = data;
} /* eof usb_creg_write_pipemaxp() */

/******************************************************************************
Function Name   : usb_creg_write_pipeperi
Description     : Specified data is written to PIPEPERI register.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  data  : The value to write.
Return value    : none
******************************************************************************/
void    usb_creg_write_pipeperi( USB_UTR_t *ptr, uint16_t data )
{
    ptr->ipp->PIPEPERI.WORD = data;
} /* eof usb_creg_write_pipeperi() */

/******************************************************************************
Function Name   : usb_creg_clr_trenb
Description     : The TRENB-bit (Transaction Counter Enable) is cleared in the 
                : specified pipe's control register, to disable the counter.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  pipeno: Pipe number.
Return value    : none
******************************************************************************/
void    usb_creg_clr_trenb( USB_UTR_t *ptr, uint16_t pipeno )
{
    volatile uint16_t    *reg_p;

    reg_p = (uint16_t *)&(ptr->ipp->PIPE1TRE) + (pipeno - 1) * 2;

    *reg_p &= ~USB_TRENB;
} /* eof usb_creg_clr_trenb() */

/******************************************************************************
Function Name   : usb_creg_read_pipectr
Description     : Returns DCPCTR or the specified pipe's PIPECTR register content.
                : The Pipe Control Register returned is determined by the speci-
                : fied pipe number.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  pipeno: Pipe number.
Return value    : PIPExCTR content
******************************************************************************/
uint16_t    usb_creg_read_pipectr( USB_UTR_t *ptr, uint16_t pipeno )
{
    volatile uint16_t    *reg_p;

    if( USB_PIPE0 == pipeno )
    {
        reg_p = (uint16_t *)&(ptr->ipp->DCPCTR);
    }
    else
    {
        reg_p = (uint16_t *)&(ptr->ipp->PIPE1CTR) + (pipeno - 1);
    }

    return *reg_p;
} /* eof usb_creg_read_pipectr() */

/******************************************************************************
Function Name   : usb_creg_clr_dclrm
Description     : Reset DCLRM-bits (FIFO buffer not auto-cleared) of the FIFOSEL 
                : corresponding to the specified PIPEMODE.
Arguments       : USB_UTR_t *ptr       : USB internal structure. Selects USB channel.
                : uint16_t pipemode : CUSE/D0DMA/D1DMA.
Return value    : none
******************************************************************************/
void    usb_creg_clr_dclrm( USB_UTR_t *ptr, uint16_t pipemode )
{
    volatile uint16_t    *reg_p;

    reg_p = usb_creg_get_fifosel_adr( ptr, pipemode );

    *reg_p &= ~USB_DCLRM;
} /* eof usb_creg_clr_dclrm() */

/******************************************************************************
Function Name   : usb_creg_set_bclr
Description     : Set BCLR (CPU Buffer Clear) to the number given; in the 
                : FIFOCTR corresponding to the specified PIPEMODE.
Arguments       : USB_UTR_t *ptr       : USB internal structure. Selects USB channel.
                : uint16_t pipemode : CUSE/D0DMA/D1DMA.
Return value    : none
******************************************************************************/
void    usb_creg_set_bclr( USB_UTR_t *ptr, uint16_t pipemode )
{
    volatile uint16_t *reg_p;

    reg_p = (uint16_t *)usb_creg_get_fifoctr_adr( ptr, pipemode );

    *reg_p = USB_BCLR;
} /* eof usb_creg_set_bclr() */

/******************************************************************************
Function Name   : usb_creg_write_dmacfg
Description     : Not processed as the functionality is provided by R8A66597(ASSP).
Arguments       : USB_UTR_t *ptr    : USB system internal data.
Return value    : none
******************************************************************************/
void    usb_creg_write_dmacfg( USB_UTR_t *ptr, uint16_t pipemode, uint16_t data )
{
} /* eof usb_creg_write_dmacfg() */

/******************************************************************************
Function Name   : usb_creg_clr_cnen
Description     : Disable single end receiver.
Arguments       : USB_UTR_t *ptr : USB system internal structure. Selects channel.
Return value    : -
******************************************************************************/
void    usb_creg_clr_cnen( USB_UTR_t *ptr )
{

} /* eof usb_creg_clr_scke() */

/******************************************************************************
Function Name   : usb_creg_clr_pid
Description     : Clear the specified PID-bits of the specified pipe's DCPCTR/
                : PIPECTR register.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  pipeno: Pipe number.
                : uint16_t  data  : NAK/BUF/STALL - to be cleared.
Return value    : none
******************************************************************************/
void    usb_creg_clr_pid( USB_UTR_t *ptr, uint16_t pipeno, uint16_t data )
{
    volatile uint16_t *reg_p;

    if( pipeno == USB_PIPE0 )
    {
        reg_p = ((uint16_t *)&(ptr->ipp->DCPCTR));
    }
    else
    {
        reg_p = ((uint16_t *)&(ptr->ipp->PIPE1CTR) + (pipeno - 1));
    }
    *reg_p &= ~data;
} /* eof usb_creg_clr_pid() */

/******************************************************************************
Function Name   : usb_creg_rmw_fifosel
Description     : Data is written to the specified pipemode's FIFOSEL register 
                : (the FIFOSEL corresponding to the specified PIPEMODE), using 
                : read-modify-write.
Arguments       : USB_UTR_t *ptr       : USB internal structure. Selects USB channel.
                : uint16_t pipemode : CUSE/D0DMA/D1DMA.
                : uint16_t data     : The value to write.
                : uint16_t bitptn   : bitptn: Bit pattern to read-modify-write.
Return value    : none
******************************************************************************/
void    usb_creg_rmw_fifosel( USB_UTR_t *ptr, uint16_t pipemode, uint16_t data, uint16_t bitptn )
{
    uint16_t    buf;
    volatile uint16_t    *reg_p;

    reg_p = (uint16_t *)usb_creg_get_fifosel_adr( ptr, pipemode );

    buf = *reg_p;
    buf &= ~bitptn;
    buf |= (data & bitptn);
    *reg_p = buf;
} /* eof usb_creg_rmw_fifosel() */

/******************************************************************************
Function Name   : usb_creg_read_fifosel
Description     : Returns the value of the specified pipemode's FIFOSEL register.
Arguments       : USB_UTR_t *ptr       : USB internal structure. Selects USB channel.
                : uint16_t  pipemode  : CUSE/D0DMA/D1DMA
Return value    : FIFOSEL content
******************************************************************************/
uint16_t    usb_creg_read_fifosel( USB_UTR_t *ptr, uint16_t pipemode )
{
    volatile uint16_t    *reg_p;

    reg_p = (uint16_t *)usb_creg_get_fifosel_adr( ptr, pipemode );

    return *reg_p;
} /* eof usb_creg_read_fifosel() */

/******************************************************************************
Function Name   : usb_creg_clr_dreqe
Description     : Clear DREQE-bits (To prohibit the output of the signal DxREQ_N)
                : of the FIFOSEL corresponding to the specified PIPEMODE.
Arguments       : USB_UTR_t *ptr       : USB internal structure. Selects USB channel.
                : uint16_t pipemode : CUSE/D0DMA/D1DMA
Return value    : none
******************************************************************************/
void    usb_creg_clr_dreqe( USB_UTR_t *ptr, uint16_t pipemode )
{
    volatile uint16_t    *reg_p;

    reg_p = usb_creg_get_fifosel_adr( ptr, pipemode );

    *reg_p &= ~USB_DREQE;
} /* eof usb_creg_clr_dreqe() */

/******************************************************************************
Function Name   : usb_creg_set_dreqe
Description     : Set DREQE-bits (to output signal DxREQ_Na) of the FIFOSEL cor-
                : responding to specified PIPEMODE.
Arguments       : USB_UTR_t *ptr       : USB internal structure. Selects USB channel.
                : uint16_t pipemode : CUSE/D0DMA/D1DMA.
Return value    : none
******************************************************************************/
void    usb_creg_set_dreqe( USB_UTR_t *ptr, uint16_t pipemode )
{
    volatile uint16_t    *reg_p;

    reg_p = usb_creg_get_fifosel_adr( ptr, pipemode );

    *reg_p |= USB_DREQE;
} /* eof usb_creg_set_dreqe() */

/******************************************************************************
Function Name   : usb_creg_set_bval
Description     : Set BVAL (Buffer Memory Valid Flag) to the number given; in 
                : the FIFOCTR corresponding to the specified PIPEMODE.
Arguments       : USB_UTR_t *ptr       : USB internal structure. Selects USB channel.
                : uint16_t pipemode : CUSE/D0DMA/D1DMA.
Return value    : none
******************************************************************************/
void    usb_creg_set_bval( USB_UTR_t *ptr, uint16_t pipemode )
{
    volatile uint16_t *reg_p;

    reg_p = (uint16_t *)usb_creg_get_fifoctr_adr( ptr, pipemode );

    *reg_p |= USB_BVAL;
} /* eof usb_creg_set_bval() */

/******************************************************************************
Function Name   : usb_creg_read_fifoctr
Description     : Returns the value of the FIFOCTR register corresponding to 
                : specified PIPEMODE.
Arguments       : USB_UTR_t *ptr       : USB internal structure. Selects USB channel.
                : uint16_t pipemode : CUSE/D0DMA/D1DMA.
Return value    : FIFOCTR content
******************************************************************************/
uint16_t    usb_creg_read_fifoctr( USB_UTR_t *ptr, uint16_t pipemode )
{
    volatile uint16_t    *reg_p;

    reg_p = (uint16_t *)usb_creg_get_fifoctr_adr( ptr, pipemode );

    return *reg_p;
} /* eof usb_creg_read_fifoctr() */

/******************************************************************************
Function Name   : usb_preg_clr_enb_rsme
Description     : Disable interrupt from RESUME
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel. 
Return value    : none
******************************************************************************/
void    usb_preg_clr_enb_rsme( USB_UTR_t *ptr )
{
    ptr->ipp->INTENB0.WORD &= ~USB_RSME;
} /* eof usb_preg_set_enb_rsme() */

/******************************************************************************
Function Name   : usb_creg_set_xcke
Description     : Not processed as the functionality is provided by R8A66597(ASSP).
Arguments       : USB_UTR_t *ptr    : USB system internal data.
Return value    : none
******************************************************************************/
void    usb_creg_set_xcke( USB_UTR_t *ptr )
{
} /* eof usb_creg_set_xcke() */

/******************************************************************************
Function Name   : usb_preg_clr_sts_resm
Description     : Clear interrupt status of RESUME.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel. 
Return value    : none
******************************************************************************/
void    usb_preg_clr_sts_resm( USB_UTR_t *ptr )
{
    ptr->ipp->INTSTS0.WORD = (uint16_t)~USB_RESM;
} /* eof usb_preg_clr_sts_resm() */

/******************************************************************************
Function Name   : usb_preg_set_wkup
Description     : Set WKUP-bit DVSTCTR register.
                : (Output Remote wakeup signal when PeripheralController function is selected)
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel. 
Return value    : none
******************************************************************************/
void    usb_preg_set_wkup( USB_UTR_t *ptr )
{
    ptr->ipp->DVSTCTR0.WORD |= USB_WKUP;
} /* eof usb_preg_set_wkup() */

/******************************************************************************
Function Name   : usb_creg_read_dvstctr
Description     : Returns the specified port's DVSTCTR register content.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  port  : USB port number. ($REA not used.)
Return value    : DVSTCTR0 content
******************************************************************************/
uint16_t    usb_creg_read_dvstctr( USB_UTR_t *ptr, uint16_t port )
{
    return (uint16_t)(ptr->ipp->DVSTCTR0.WORD);
} /* eof usb_creg_read_dvstctr() */

/******************************************************************************
Function Name   : usb_creg_set_nrdyenb
Description     : A bit is set in the specified pipe's NRDYENB, enabling the 
                : respective pipe NRDY interrupt(s).
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  pipeno: Pipe number.
Return value    : none
******************************************************************************/
void    usb_creg_set_nrdyenb( USB_UTR_t *ptr, uint16_t pipeno )
{
    ptr->ipp->NRDYENB.WORD |= (1 << pipeno);
} /* eof usb_creg_set_nrdyenb() */

/******************************************************************************
Function Name   : usb_creg_read_syscfg
Description     : Returns the specified port's SYSCFG register value.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t port   : Port number (not used $REA)
Return value    : SYSCFG content.
******************************************************************************/
uint16_t    usb_creg_read_syscfg( USB_UTR_t *ptr, uint16_t port )
{
    return ptr->ipp->SYSCFG.WORD;
} /* eof usb_creg_read_syscfg() */

/******************************************************************************
Function Name   : usb_creg_read_dcpmaxp
Description     : Returns DCPMAXP register content.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
Return value    : DCPMAXP content
******************************************************************************/
uint16_t    usb_creg_read_dcpmaxp( USB_UTR_t *ptr )
{
    return (uint16_t)ptr->ipp->DCPMAXP.WORD;
} /* eof usb_creg_read_dcpmaxp() */

/******************************************************************************
Function Name   : usb_creg_read_pipemaxp
Description     : Returns PIPEMAXP register content.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
Return value    : PIPEMAXP content
******************************************************************************/
uint16_t    usb_creg_read_pipemaxp( USB_UTR_t *ptr )
{
    return (uint16_t)ptr->ipp->PIPEMAXP.WORD;
} /* eof usb_creg_read_pipemaxp() */

/******************************************************************************
Function Name   : usb_creg_read_pipebuf
Description     : Returns PIPECFG register content.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
Return value    : PIPEBUF content
******************************************************************************/
uint16_t    usb_creg_read_pipebuf( USB_UTR_t *ptr )
{
    return 0;
} /* eof usb_creg_read_pipebuf() */

/******************************************************************************
Function Name   : usb_creg_read_dcpcfg
Description     : Returns DCPCFG register content.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
Return value    : DCPCFG content
******************************************************************************/
uint16_t    usb_creg_read_dcpcfg( USB_UTR_t *ptr )
{
//#if defined(BSP_MCU_RX62N) || defined(BSP_MCU_RX63T)
//    return (uint16_t)ptr->ipp->DCPCFG.WORD;
//#else
    return 0;
//#endif /* defined(BSP_MCU_RX62N) || defined(BSP_MCU_RX63T) */
} /* eof usb_creg_read_dcpcfg() */

/******************************************************************************
Function Name   : usb_creg_set_pid
Description     : Set the specified PID of the specified pipe's DCPCTR/PIPECTR 
                : register.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  pipeno: Pipe number.
                : uint16_t  data  : NAK/BUF/STALL.
Return value    : none
******************************************************************************/
void    usb_creg_set_pid( USB_UTR_t *ptr, uint16_t pipeno, uint16_t data )
{
    volatile uint16_t *reg_p;

    if( pipeno == USB_PIPE0 )
    {
        reg_p = ((uint16_t *)&(ptr->ipp->DCPCTR));
    }
    else
    {
        reg_p = ((uint16_t *)&(ptr->ipp->PIPE1CTR) + (pipeno - 1));
    }
    *reg_p &= ~USB_PID;
    *reg_p |= data;
} /* eof usb_creg_set_pid() */

/******************************************************************************
Function Name   : usb_creg_set_brdyenb
Description     : A bit is set in the specified pipe's BRDYENB, enabling the 
                : respective pipe BRDY interrupt(s).
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  pipeno: Pipe number.
Return value    : none
******************************************************************************/
void    usb_creg_set_brdyenb( USB_UTR_t *ptr, uint16_t  pipeno )
{
    ptr->ipp->BRDYENB.WORD |= (1 << pipeno);
} /* eof usb_creg_set_brdyenb() */

/******************************************************************************
Function Name   : usb_creg_write_fifo16
Description     : Data is written to the specified pipemode's FIFO register, 16-bits 
                : wide, corresponding to the specified PIPEMODE.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  pipemode  : CUSE/D0DMA/D1DMA
                : uint16_t  data      : The value to write.
Return value    : none
******************************************************************************/
void    usb_creg_write_fifo16( USB_UTR_t *ptr, uint16_t pipemode, uint16_t data )
{

        switch( pipemode )
        {
            case    USB_CUSE:
                ptr->ipp->CFIFO.WORD = data;
                break;
            case    USB_D0USE:
            case    USB_D0DMA:
                ptr->ipp->D0FIFO.WORD = data;
                break;
            case    USB_D1USE:
            case    USB_D1DMA:
                ptr->ipp->D1FIFO.WORD = data;
                break;
            default:
                USB_DEBUG_HOOK( USB_DEBUG_HOOK_STD | USB_DEBUG_HOOK_CODE6 );
                break;
        }

} /* eof usb_creg_write_fifo16() */

/******************************************************************************
Function Name   : usb_creg_set_sqset
Description     : The SQSET-bit (Toggle Bit Set) is set in the specified pipe's 
                : control register. Setting SQSET to 1 makes DATA1 the expected 
                : data in the next transfer.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  pipeno: Pipe number.
Return value    : none
******************************************************************************/
void    usb_creg_set_sqset( USB_UTR_t *ptr, uint16_t pipeno )
{
    if( pipeno == USB_PIPE0 )
    {
        ptr->ipp->DCPCTR.WORD |= USB_SQSET;
    }
    else
    {
        volatile uint16_t    *reg_p;

        reg_p = ((uint16_t *)&(ptr->ipp->PIPE1CTR) + (pipeno - 1));
        *reg_p |= USB_SQSET;
    }
} /* eof usb_creg_set_sqset() */

/******************************************************************************
Function Name   : usb_creg_set_dclrm
Description     : Set DCLRM-bits (FIFO buffer auto clear) of the FIFOSEL cor-
                : responding to specified PIPEMODE.
Arguments       : USB_UTR_t *ptr       : USB internal structure. Selects USB channel.
                : uint16_t pipemode : CUSE/D0DMA/D1DMA.
Return value    : none
******************************************************************************/
void    usb_creg_set_dclrm( USB_UTR_t *ptr, uint16_t pipemode )
{
    volatile uint16_t    *reg_p;

    reg_p = (uint16_t *)usb_creg_get_fifosel_adr( ptr, pipemode );

    *reg_p |= USB_DCLRM;
} /* eof usb_creg_set_dclrm() */

/******************************************************************************
Function Name   : usb_creg_set_cnen
Description     : Enable single end receiver.
Arguments       : USB_UTR_t *ptr : USB system internal structure. Selects channel.
Return value    : -
******************************************************************************/
void    usb_creg_set_cnen( USB_UTR_t *ptr )
{

} /* eof usb_creg_set_xcke */

/******************************************************************************
Function Name   : usb_preg_clr_sts_valid
Description     : Enable termination of control transfer status stage.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel. 
Return value    : none
******************************************************************************/
void    usb_preg_set_ccpl( USB_UTR_t *ptr )
{
    ptr->ipp->DCPCTR.WORD |= USB_CCPL;
} /* eof usb_preg_set_ccpl() */

/******************************************************************************
Function Name   : usb_creg_read_dcpctr
Description     : Returns DCPCTR register content.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
Return value    : DCPCTR content
******************************************************************************/
uint16_t    usb_creg_read_dcpctr( USB_UTR_t *ptr )
{
    return (uint16_t)ptr->ipp->DCPCTR.WORD;
} /* eof usb_creg_read_dcpctr() */

/******************************************************************************
Function Name   : usb_creg_read_usbreq
Description     : Returns USBREQ register content.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
Return value    : USBREQ content
******************************************************************************/
uint16_t    usb_creg_read_usbreq( USB_UTR_t *ptr )
{
    return (uint16_t)ptr->ipp->USBREQ.WORD;
} /* eof usb_creg_read_usbreq() */

/******************************************************************************
Function Name   : usb_creg_read_usbval
Description     : Returns USBVAL register content.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
Return value    : USBVAL content
******************************************************************************/
uint16_t    usb_creg_read_usbval( USB_UTR_t *ptr )
{
    return (uint16_t)ptr->ipp->USBVAL;
} /* eof usb_creg_read_usbval() */

/******************************************************************************
Function Name   : usb_creg_read_usbindx
Description     : Returns USBINDX register content.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
Return value    : USBINDX content
******************************************************************************/
uint16_t    usb_creg_read_usbindx( USB_UTR_t *ptr )
{
    return (uint16_t)ptr->ipp->USBINDX;
} /* eof usb_creg_read_usbindx() */

/******************************************************************************
Function Name   : usb_creg_read_usbleng
Description     : Returns USBLENG register content.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
Return value    : USBLENG content
******************************************************************************/
uint16_t    usb_creg_read_usbleng( USB_UTR_t *ptr )
{
    return (uint16_t)ptr->ipp->USBLENG;
} /* eof usb_creg_read_usbleng() */

/******************************************************************************
Function Name   : usb_creg_read_syssts
Description     : Returns the value of the specified port's SYSSTS register.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  port  : USB port number. ($REA not used.)
Return value    : SYSSTS0 content
******************************************************************************/
uint16_t    usb_creg_read_syssts( USB_UTR_t *ptr, uint16_t port )
{
    return (uint16_t)(ptr->ipp->SYSSTS0.WORD);
} /* eof usb_creg_read_syssts() */

/******************************************************************************
Function Name   : usb_preg_set_enb_rsme
Description     : Enable interrupt from RESUME
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel. 
Return value    : none
******************************************************************************/
void    usb_preg_set_enb_rsme( USB_UTR_t *ptr )
{
    ptr->ipp->INTENB0.WORD |= USB_RSME;
} /* eof usb_preg_set_enb_rsme() */

/******************************************************************************
Function Name   : usb_creg_write_dcpcfg
Description     : Specified data is written to DCPCFG register.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  data
Return value    : none
******************************************************************************/
void    usb_creg_write_dcpcfg( USB_UTR_t *ptr, uint16_t data )
{
//#if defined(BSP_MCU_RX62N) || defined(BSP_MCU_RX63T)
//    ptr->ipp->DCPCFG.WORD = data;
//#endif /* defined(BSP_MCU_RX62N) || defined(BSP_MCU_RX63T) */
} /* eof usb_creg_write_dcpcfg()*/

/******************************************************************************
Function Name   : usb_creg_read_frmnum
Description     : Returns FRMNUM register content.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
Return value    : FRMNUM content
******************************************************************************/
uint16_t    usb_creg_read_frmnum( USB_UTR_t *ptr )
{
    return (uint16_t)ptr->ipp->FRMNUM.WORD;
} /* eof usb_creg_read_frmnum() */

/******************************************************************************
Function Name   : usb_creg_set_sofcfg
Description     : Set Bit pattern for SOFCFG
                : 
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  data  : The value to OR.
Return value    : none
******************************************************************************/
void    usb_creg_set_sofcfg( USB_UTR_t *ptr, uint16_t data )
{
    if(ptr->ip == USB_USBIP_1)
    {
        ptr->ipp->SOFCFG.WORD |= data;
    }
} /* eof usb_creg_set_sofcfg() */

/******************************************************************************
Function Name   : usb_creg_clr_drpd
Description     : Clear bit of the specified port's SYSCFG DRPD register.
                : (for USB Host mode; Enable D + / D-line PullDown.)
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  port  : Port number
Return value    : none
******************************************************************************/
void    usb_creg_clr_drpd( USB_UTR_t *ptr, uint16_t port )
{

    if( USB_PORT0 == port )
    {
        ptr->ipp->SYSCFG.WORD &= ~USB_DRPD;
    }

} /* eof usb_creg_clr_drpd() */

/******************************************************************************
Function Name   : usb_preg_write_physlew
Description     : Set the PHYSLEW register's for funcrion mode
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
Return value    : none
******************************************************************************/
void    usb_preg_write_physlew( USB_UTR_t *ptr )
{

} /* eof usb_preg_write_physlew() */

/******************************************************************************
Function Name   : usb_creg_clr_hse
Description     : Clears HSE bit of the specified port's SYSCFG register
Arguments       : USB_UTR_t *ptr : USB system internal structure. Selects channel.
                : uint16_t  port : Port number
Return value    : none
******************************************************************************/
void    usb_creg_clr_hse( USB_UTR_t *ptr, uint16_t port )
{

} /* eof usb_creg_clr_hse() */

/******************************************************************************
Function Name   : usb_creg_set_hse
Description     : Not processed as the functionality is provided by R8A66597(ASSP).
Arguments       : USB_UTR_t *ptr  : Not used.
                : uint16_t  port  : Not used.
Return value    : none
******************************************************************************/
void    usb_creg_set_hse( USB_UTR_t *ptr, uint16_t port )
{

} /* eof usb_creg_set_hse() */

/******************************************************************************
Function Name   : usb_creg_write_fifosel
Description     : Data is written to the specified pipemode's FIFOSEL register, 8-bits 
                : wide, corresponding to the specified PIPEMODE.
Arguments       : USB_UTR_t *ptr       : USB internal structure. Selects USB channel.
                : uint16_t pipemode  : CUSE/D0DMA/D1DMA
                : uint16_t data     : The value to write.
Return value    : none
******************************************************************************/
void    usb_creg_write_fifosel( USB_UTR_t *ptr, uint16_t pipemode, uint16_t data )
{
    volatile uint16_t    *reg_p;

    reg_p = (uint16_t *)usb_creg_get_fifosel_adr( ptr, pipemode );

    *reg_p = data;
} /* eof usb_creg_write_fifosel() */

/******************************************************************************
Function Name   : usb_creg_set_bigend
Description     : Set BIGEND-bit of the FIFOSEL corresponding to the specified 
                : PIPEMODE to select big or little endian of CFIFO.
                : mode of the CFIFO.
Arguments       : USB_UTR_t *ptr       : USB internal structure. Selects USB channel.
                : uint16_t pipemode : CUSE/D0DMA/D1DMA.
                : uint16_t data     : Defined value of big/little endian.
Return value    : none
******************************************************************************/
void    usb_creg_set_bigend( USB_UTR_t *ptr, uint16_t pipemode, uint16_t data )
{
    volatile uint16_t    *reg_p;

    reg_p = usb_creg_get_fifosel_adr( ptr, pipemode );

    if( data != 0 )
    {
        *reg_p |= USB_BIGEND;
    }
    else
    {
        *reg_p &= ~USB_BIGEND;
    }
} /* eof usb_creg_set_bigend() */

/******************************************************************************
Function Name   : usb_creg_set_bus_wait
Description     : Set BUSWAIT register.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
Return value    : none
******************************************************************************/
void    usb_creg_set_bus_wait( USB_UTR_t *ptr )
{

} /* eof usb_creg_set_bus_wait() */

/******************************************************************************
Function Name   : usb_creg_write_brdyenb
Description     : Data is written to BRDYENB register, 
                : enabling/disabling each respective pipe's BRDY interrupt. 
                : (The BRDY interrupt indicates that a FIFO port is accessible.)
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  data        : The value to write.
Return value    : none
******************************************************************************/
void    usb_creg_write_brdyenb( USB_UTR_t *ptr, uint16_t data )
{
    ptr->ipp->BRDYENB.WORD = data;
} /* eof usb_creg_write_brdyenb() */

/******************************************************************************
Function Name   : usb_creg_write_nrdyenb
Description     : Data is written to NRDYENB register, 
                : enabling/disabling each respective pipe's NRDY interrupt
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  data  : The value to write.
Return value    : none
******************************************************************************/
void    usb_creg_write_nrdyenb( USB_UTR_t *ptr, uint16_t data )
{
    ptr->ipp->NRDYENB.WORD = data;
} /* eof usb_creg_write_nrdyenb() */
/******************************************************************************
Function Name   : usb_creg_write_bempenb
Description     : Data is written to BEMPENB register, 
                : enabling/disabling each respective pipe's BEMP interrupt. 
                : (The BEMP interrupt indicates that the USB buffer is empty, 
                : and so the FIFO can now be written to.)
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  data  : The value to write.
Return value    : none
******************************************************************************/
void    usb_creg_write_bempenb( USB_UTR_t *ptr, uint16_t data )
{
    ptr->ipp->BEMPENB.WORD = data;
} /* eof usb_creg_write_bempenb() */
/******************************************************************************
Function Name   : usb_creg_write_brdysts
Description     : Data is written to BRDYSTS register, to set the BRDY interrupt status.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  data  : The value to write.
Return value    : none
******************************************************************************/
void        usb_creg_write_brdysts( USB_UTR_t *ptr, uint16_t data )
{
    ptr->ipp->BRDYSTS.WORD = data;
} /* eof usb_creg_write_brdysts() */

/******************************************************************************
Function Name   : usb_creg_write_nrdysts
Description     : Data is written to NRDYSTS register, to
                : set the NRDY interrupt status.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  data  : The value to write.
Return value    : none
******************************************************************************/
void        usb_creg_write_nrdysts( USB_UTR_t *ptr, uint16_t data )
{
    ptr->ipp->NRDYSTS.WORD = data;
} /* eof usb_creg_write_nrdysts() */

/******************************************************************************
Function Name   : usb_creg_read_bempstsusb_creg_write_bempsts
Description     : Returns BEMPSTS register content.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
Return value    : BEMPSTS content
******************************************************************************/
uint16_t    usb_creg_read_bempsts( USB_UTR_t *ptr )
{
    return (uint16_t)ptr->ipp->BEMPSTS.WORD;
} /* eof usb_creg_read_bempsts() */

/******************************************************************************
Function Name   : usb_creg_write_bempsts
Description     : Data is written to BEMPSTS register, to set the BEMP interrupt status.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  data        : The value to write.
Return value    : none
******************************************************************************/
void    usb_creg_write_bempsts( USB_UTR_t *ptr, uint16_t data )
{
    ptr->ipp->BEMPSTS.WORD = data;
} /* eof usb_creg_write_bempsts() */

/******************************************************************************
Function Name   : usb_creg_set_usbe
Description     : Enable USB operation.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
Return value    : none
******************************************************************************/
void    usb_creg_set_usbe( USB_UTR_t *ptr )
{

    ptr->ipp->SYSCFG.WORD |= USB_USBE;

} /* eof usb_creg_set_usbe() */


/******************************************************************************
Function Name   : usb_creg_clr_usbe
Description     : Enable USB operation.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
Return value    : none
******************************************************************************/
void    usb_creg_clr_usbe( USB_UTR_t *ptr )
{

    ptr->ipp->SYSCFG.WORD &= ~USB_USBE;

} /* eof usb_creg_clr_usbe() */

/******************************************************************************
Function Name   : usb_creg_write_intsts
Description     : Data is written to INTSTS0 register.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  data  : The value to write.
Return value    : none
******************************************************************************/
void    usb_creg_write_intsts( USB_UTR_t *ptr, uint16_t data )
{
    ptr->ipp->INTSTS0.WORD = data;
} /* eof usb_creg_write_intsts() */
/******************************************************************************
Function Name   : usb_creg_write_intenb
Description     : Data is written to INTENB register, 
                : enabling/disabling the various USB interrupts.
Arguments       : USB_UTR_t *ptr  : USB internal structure. Selects USB channel.
                : uint16_t  data  : The value to write.
Return value    : none
******************************************************************************/
void    usb_creg_write_intenb( USB_UTR_t *ptr, uint16_t data )
{
    ptr->ipp->INTENB0.WORD = data;
} /* eof usb_creg_write_intenb() */

/******************************************************************************
Function Name   : usb_creg_set_scke
Description     : Enable USB module clock.
Arguments       : USB_UTR_t *ptr : USB system internal structure. Selects channel.
Return value    : -
******************************************************************************/
void    usb_creg_set_scke( USB_UTR_t *ptr )
{
    ptr->ipp->SYSCFG.WORD |= USB_SCKE;
} /* eof usb_creg_set_xcke */
