#ifndef __USB_TYPEDEF_H__
#define __USB_TYPEDEF_H__


/* Peripheral CDC Transfer Pipe */
#define USB_PCDC_USE_PIPE_IN            USB_PIPE1
#define USB_PCDC_USE_PIPE_OUT           USB_PIPE2
#define USB_PCDC_USE_PIPE_STATUS        USB_PIPE6




#define USB_DETACH_SLEEP(x)             /* Not use */
#define USB_SUSPEND_SLEEP(x)            /* Not use */
#define USB_DEBUG_HOOK(x)
#define R_USB_TRCV_MSG(ID, MESS, TM)    R_usb_cstd_RecMsg( (uint8_t)ID, (USB_MSG_t**)MESS, (USB_TM_t)TM )
#define USB_REL_BLK(ID, BLK)        usb_cstd_RelBlk( (uint8_t)ID,  (USB_UTR_t*)BLK )
#define R_USB_REL_BLK(ID, BLK)      R_usb_cstd_RelBlk( (uint8_t)ID,  (USB_UTR_t*)BLK )
#define R_USB_SND_MSG(ID, MESS)     R_usb_cstd_SndMsg( (uint8_t)ID, (USB_MSG_t*)MESS )
#define USB_SND_MSG(ID, MESS)       usb_cstd_SndMsg( (uint8_t)ID, (USB_MSG_t*)MESS )
#define USB_TRCV_MSG(ID, MESS, TM)  usb_cstd_RecMsg( (uint8_t)ID, (USB_MSG_t**)MESS, (USB_TM_t)TM )
#define USB_BITSET(x)           (uint16_t)((uint16_t)1 << (x))
#define USB_PGET_BLK(ID, BLK)       usb_cstd_PgetBlk( (uint8_t)ID, (USB_UTR_t**)BLK )
#define USB_DEL_MPL(ID)             USB_NG
#define R_USB_PGET_BLK(ID, BLK)     R_usb_cstd_PgetBlk( (uint8_t)ID, (USB_UTR_t**)BLK )
#define USB_ISND_MSG(ID, MESS)      usb_cstd_iSndMsg( (uint8_t)ID, (USB_MSG_t*)MESS )

/*****************************************************************************
Macro definitions
******************************************************************************/
#define bool _Bool
#define false 0
#define true 1
#define NULL 0

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int16_t;
typedef unsigned short uint16_t;
typedef signed long int32_t;
typedef unsigned long uint32_t;
typedef signed long long int64_t;
typedef unsigned long long uint64_t;
//typedef unsigned int _Bool;
typedef unsigned long size_t;

#define USB_BUF_SIZE(x)                     ((uint16_t)(((x) / 64u) - 1u) << 10u)
#define USB_BUF_NUMB(x)                     (x)

/* Interface class Define */
#define USB_IFCLS_NOT                       0x00u   /* Un corresponding Class */
#define USB_IFCLS_AUD                       0x01u   /* Audio Class */
#define USB_IFCLS_CDC                       0x02u   /* CDC Class */
#define USB_IFCLS_CDCC                      0x02u   /* CDC-Control Class */
#define USB_IFCLS_HID                       0x03u   /* HID Class */
#define USB_IFCLS_PHY                       0x05u   /* Physical Class */
#define USB_IFCLS_IMG                       0x06u   /* Image Class */
#define USB_IFCLS_PRN                       0x07u   /* Printer Class */
#define USB_IFCLS_MAS                       0x08u   /* Mass Storage Class */
#define USB_IFCLS_HUB                       0x09u   /* HUB Class */
#define USB_IFCLS_CDCD                      0x0Au   /* CDC-Data Class */
#define USB_IFCLS_CHIP                      0x0Bu   /* Chip/Smart Card Class */
#define USB_IFCLS_CNT                       0x0Cu   /* Content-Security Class */
#define USB_IFCLS_VID                       0x0Du   /* Video Class */
#define USB_IFCLS_DIAG                      0xDCu   /* Diagnostic Device */
#define USB_IFCLS_WIRE                      0xE0u   /* Wireless Controller */
#define USB_IFCLS_APL                       0xFEu   /* Application-Specific */
#define USB_IFCLS_VEN                       0xFFu   /* Vendor-Specific Class */

/* CDC Class Requests IDs*/
#define USB_PCDC_SET_LINE_CODING            0x2000
#define USB_PCDC_GET_LINE_CODING            0x2100
#define USB_PCDC_SET_CONTROL_LINE_STATE     0x2200
#define USB_PCDC_SEND_BREAK                 0x2300

/* Header Functional Descriptor */
#define     USB_PCDC_DT_SUBTYPE_HEADER_FUNC                     0x00
/* Call Management Functional Descriptor. */
#define     USB_PCDC_DT_SUBTYPE_CALL_MANAGE_FUNC                0x01
/* Abstract Control Management Functional Descriptor. */
#define     USB_PCDC_DT_SUBTYPE_ABSTRACT_CTR_MANAGE_FUNC        0x02
/* Union Functional Descriptor */
#define     USB_PCDC_DT_SUBTYPE_UNION_FUNC                      0x06
/* Communications Class Subclass Codes */
#define     USB_PCDC_CLASS_SUBCLASS_CODE_ABS_CTR_MDL            0x02
/* USB Class Definitions for Communications Devices Specification 
   release number in binary-coded decimal. */
#define     USB_PCDC_BCD_CDC                                    0x0110
/* GET_LINE_CODING request wLength */
#define     USB_PCDC_GET_LINE_CODING_LENGTH                     0x07
/* Class-Specific Configuration Descriptors */
#define     USB_PCDC_CS_INTERFACE                               0x24

/* bcdUSB */
#define USB_BCDNUM                      (0x0200u)
/* Release Number */
#define USB_RELEASE                     (0x0100u)
/* DCP max packet size */
#define USB_DCPMAXP                     (64u)
/* Configuration number */
#define USB_CONFIGNUM                   (1u)
/* Vendor ID */
#define USB_VENDORID                    0x2b72//RT
/* Product ID */
#define USB_PRODUCTID                   0x0012//RT»•i”Ô†

/* Descriptor length */
#define USB_PCDC_DD_LEN               18
#define USB_PCDC_QD_LEN               10
#define USB_PCDC_CD1_LEN              67
#define STRING_DESCRIPTOR0_LEN        4
#define STRING_DESCRIPTOR1_LEN        28
#define STRING_DESCRIPTOR2_LEN        44
#define STRING_DESCRIPTOR3_LEN        46
#define STRING_DESCRIPTOR4_LEN        22
#define STRING_DESCRIPTOR5_LEN        28

#define USB_IFISFIELD                       0x1000u /* Isochronous in-buf flash mode */
#define USB_IFISON                          0x1000u
#define USB_IFISOFF                         0x0000u
#define USB_IITVFIELD                       0x0007u /* Isochronous interval */
#define USB_IITV_TIME(x)                    (x)

/* SPEED mode */
#define USB_HS_DISABLE          (uint16_t)0
#define USB_HS_ENABLE           (uint16_t)1

#define USB_FIFO_LITTLE         (0x0000u)   /* Little endian */
#define USB_FIFOENDIAN      USB_FIFO_LITTLE

/* Interrupt message num */
#define USB_INTMSGMAX           (uint16_t)15
#define USB_DMAMSGMAX           (uint16_t)15

#define USB_MSG_HCD_INT                     0x0117u

/* Task priority define */
#define USB_PRI_0           0u                  /* Priority 0 */
#define USB_PRI_1           1u                  /* Priority 1 */
#define USB_PRI_2           2u                  /* Priority 2 */
#define USB_PRI_3           3u                  /* Priority 3 */
#define USB_PRI_4           4u                  /* Priority 4 */
#define USB_PRI_5           5u                  /* Priority 5 */
#define USB_PRI_6           6u                  /* Priority 6 */

#define BSP_CFG_USER_LOCKING_TYPE       bsp_lock_t

#define USB_CDC_SETUP_TBL_BSIZE             10

/* The number of USBIP */
#define USB_NUM_USBIP           1

/* Root port */
#define USB_PORT0                           0u
#define USB_PORT1                           1u

/* Device connect information */
#define USB_ATTACH                          0x0040u
#define USB_ATTACHL                         0x0041u
#define USB_ATTACHF                         0x0042u
#define USB_DETACH                          0x0043u

/* Pipe define */
#define USB_USEPIPE                         0x00FEu
#define USB_PERIPIPE                        0x00FDu
#define USB_CLRPIPE                         0x00FCu /* Clear Pipe registration */
#define USB_PIPE0                           0x0000u /* PIPE 0 */
#define USB_PIPE1                           0x0001u /* PIPE 1 */
#define USB_PIPE2                           0x0002u /* PIPE 2 */
#define USB_PIPE3                           0x0003u /* PIPE 3 */
#define USB_PIPE4                           0x0004u /* PIPE 4 */
#define USB_PIPE5                           0x0005u /* PIPE 5 */
#define USB_PIPE6                           0x0006u /* PIPE 6 */
#define USB_PIPE7                           0x0007u /* PIPE 7 */
#define USB_PIPE8                           0x0008u /* PIPE 8 */
#define USB_PIPE9                           0x0009u /* PIPE 9 */
#define USB_MAX_PIPE_NO                     9u      /* PIPE0 ... PIPE9 */

/* Pipe define table end code */
#define USB_PDTBLEND                        0xFFFFu /* End of table */



/* Transfer status Type */
#define USB_CTRL_END                        0u
#define USB_DATA_NONE                       1u
#define USB_DATA_WAIT                       2u
#define USB_DATA_OK                         3u
#define USB_DATA_SHT                        4u
#define USB_DATA_OVR                        5u
#define USB_DATA_STALL                      6u
#define USB_DATA_ERR                        7u
#define USB_DATA_STOP                       8u
#define USB_DATA_TMO                        9u
#define USB_CTRL_READING                    17u
#define USB_CTRL_WRITING                    18u
#define USB_DATA_READING                    19u
#define USB_DATA_WRITING                    20u

/* Pipe configuration table define */
#define USB_EPL                             6u      /* Pipe configuration table length */
#define USB_TYPFIELD                        0xC000u /* Transfer type */
#define USB_PERIODIC                      0x8000u /* Periodic pipe */
#define USB_ISO                           0xC000u /* Isochronous */
#define USB_INT                           0x8000u /* Interrupt */
#define USB_BULK                          0x4000u /* Bulk */
#define USB_NOUSE                         0x0000u /* Not configuration */
#define USB_BFREFIELD                       0x0400u /* Buffer ready interrupt mode select */
#define USB_BFREON                        0x0400u
#define USB_BFREOFF                       0x0000u
#define USB_DBLBFIELD                       0x0200u /* Double buffer mode select */
#define USB_DBLBON                        0x0200u
#define USB_DBLBOFF                       0x0000u
#define USB_CNTMDFIELD                      0x0100u /* Continuous transfer mode select */
#define USB_CNTMDON                       0x0100u
#define USB_CNTMDOFF                      0x0000u
#define USB_SHTNAKFIELD                     0x0080u /* Transfer end NAK */
#define USB_SHTNAKON                      0x0080u
#define USB_SHTNAKOFF                     0x0000u
#define USB_DIRFIELD                        0x0010u /* Transfer direction select */
#define USB_DIR_H_OUT                     0x0010u /* HOST OUT */
#define USB_DIR_P_IN                      0x0010u /* PERI IN */
#define USB_DIR_H_IN                      0x0000u /* HOST IN */
#define USB_DIR_P_OUT                     0x0000u /* PERI OUT */
#define USB_BUF2FIFO                      0x0010u /* Buffer --> FIFO */
#define USB_FIFO2BUF                      0x0000u /* FIFO --> buffer */
#define USB_EPNUMFIELD                      0x000Fu /* Endpoint number select */
#define USB_MAX_EP_NO                       15u     /* EP0 EP1 ... EP15 */
#define USB_EP0                           0x0000u
#define USB_EP1                           0x0001u
#define USB_EP2                           0x0002u
#define USB_EP3                           0x0003u
#define USB_EP4                           0x0004u
#define USB_EP5                           0x0005u
#define USB_EP6                           0x0006u
#define USB_EP7                           0x0007u
#define USB_EP8                           0x0008u
#define USB_EP9                           0x0009u
#define USB_EP10                          0x000Au
#define USB_EP11                          0x000Bu
#define USB_EP12                          0x000Cu
#define USB_EP13                          0x000Du
#define USB_EP14                          0x000Eu
#define USB_EP15                          0x000Fu

/* USB Peripheral task message command */
#define USB_MSG_PCD_INT                     0x0151u
#define USB_MSG_PCD_SUBMITUTR               0x0152u
#define USB_MSG_PCD_TRANSEND1               0x0153u
#define USB_MSG_PCD_TRANSEND2               0x0154u
#define USB_MSG_PCD_REMOTEWAKEUP            0x0155u
#define USB_MSG_PCD_DETACH                  0x0161u
#define USB_MSG_PCD_ATTACH                  0x0162u
#define USB_MSG_PCD_CLRSEQBIT               0x0163u
#define USB_MSG_PCD_SETSTALL                0x0164u
#define USB_MSG_PCD_PCUTINT                 0x0156u

#define USB_MSG_PCD_DP_ENABLE               0x0157u
#define USB_MSG_PCD_DP_DISABLE              0x0158u
#define USB_MSG_PCD_DM_ENABLE               0x0159u
#define USB_MSG_PCD_DM_DISABLE              0x015Au

#define USB_MSG_PCD_DMAINT                  0x015bu

/* USB interrupt type (common)*/
#define USB_INT_UNKNOWN                     0x0000u
#define USB_INT_BRDY                        0x0001u
#define USB_INT_BEMP                        0x0002u
#define USB_INT_NRDY                        0x0003u

/* USB interrupt type (PERI)*/
#define USB_INT_VBINT                       0x0011u
#define USB_INT_RESM                        0x0012u
#define USB_INT_SOFR                        0x0013u
#define USB_INT_DVST                        0x0014u
#define USB_INT_CTRT                        0x0015u
#define USB_INT_ATTACH                      0x0016u
#define USB_INT_DETACH                      0x0017u


#define USB_MSG_PCD_D0FIFO_INT              0x0144u
#define USB_MSG_PCD_D1FIFO_INT              0x0145u
#define USB_MSG_PCD_RESM_INT                0x0146u

/* Utr member (segment) */
#define USB_TRAN_CONT                       0x00u
#define USB_TRAN_END                        0x80u

/* Callback argument */
#define USB_NO_ARG                          0u

#define USB_NONE            (uint16_t)(0)
#define USB_YES             (uint16_t)(1)
#define USB_NO              (uint16_t)(0)
#define USB_DONE            (uint16_t)(0)
#define USB_ERROR           (uint16_t)(0xFFFF)
#define USB_OK              (uint16_t)(0)
#define USB_NG              (uint16_t)(0xFFFF)
#define USB_ON              (uint16_t)(1)
#define USB_OFF             (uint16_t)(0)
#define USB_OTG_DONE        (uint16_t)(2)
#define USB_NOT_USED        (uint16_t)(0)

#ifndef NULL
	#define   NULL    0u
#endif  /* NULL */

#define USB_NULL        NULL

#define E_OK        0L                  /* Normal end               */
#define E_QOVR      (-43L)              /* Queuing over flow        */


#define USB_E_OK        E_OK
#define USB_E_QOVR      E_QOVR      /* Submit overlap error */
#define USB_E_ERROR (-1L)
#define USB_VP_INT      VP_INT



#define USB_IDMAX           11u                 /* Maximum Task ID +1 */
#define USB_PRIMAX          8u                  /* Maximum Priority number +1 */
#define USB_BLKMAX          20u                 /* Maximum block */
#define USB_TABLEMAX        USB_BLKMAX          /* Maximum priority table */
#define USB_WAIT_EVENT_MAX  (5u)

#define CDC_DATA_LEN              64   /* Peri CDC Application receive data size */
#define EVENT_MAX                 5                   /* Max event pool count */

/* Scheduler use define */
#define USB_TBLCLR          0u                  /* Table clear */
#define USB_CNTCLR          0u                  /* Counter clear */
#define USB_FLGCLR          0u                  /* Flag clear */
#define USB_FLGSET          1u                  /* Flag set */
#define USB_IDCLR           0xFFu               /* Priority clear */

/* USB IP Number */
#define USB_USBIP_0             (uint16_t)0
#define USB_USBIP_1             (uint16_t)1

/* H/W function type */
#define USB_HOST                (uint16_t)1     /* Host mode */
#define USB_PERI                (uint16_t)2     /* Peripheral mode */
#define USB_HOST_PERI           (uint16_t)3     /* Host/Peri mode */
#define USB_OTG                 (uint16_t)4     /* Otg mode */

/* USB Device Connect */
#define USB_DEV_NO_CONNECT      (uint16_t)0
#define USB_DEV_CONNECTED       (uint16_t)1

/* Task ID define */
#define USB_TID_0           0u                  /* Task ID 0 */
#define USB_TID_1           1u                  /* Task ID 1 */
#define USB_TID_2           2u                  /* Task ID 2 */
#define USB_TID_3           3u                  /* Task ID 3 */
#define USB_TID_4           4u                  /* Task ID 4 */
#define USB_TID_5           5u                  /* Task ID 5 */
#define USB_TID_6           6u                  /* Task ID 6 */
#define USB_TID_7           7u                  /* Task ID 7 */
#define USB_TID_8           8u                  /* Task ID 8 */
#define USB_TID_9           9u                  /* Task ID 9 */
#define USB_TID_10          10u                 /* Task ID 9 */

/* USB_BMREQUESTTYPETYPE    0x0060u(b6-5) */
#define USB_STANDARD                        0x0000u
#define USB_CLASS                           0x0020u
#define USB_VENDOR                          0x0040u

/* Peripheral Control Driver Task */
#define USB_PCD_TSK         USB_TID_0           /* Task ID */
#define USB_PCD_MBX         USB_PCD_TSK         /* Mailbox ID */
#define USB_PCD_MPL         USB_PCD_TSK         /* Memorypool ID */

/* Peripheral CDC Driver Task */
#define USB_PCDC_TSK        USB_TID_4           /* Task ID */
#define USB_PCDC_MBX        USB_PCDC_TSK        /* Mailbox ID */
#define USB_PCDC_MPL        USB_PCDC_TSK        /* Memorypool ID */

/* FIFO port & access define */
#define USB_CUSE                            0u  /* CFIFO CPU trans */
#define USB_D0USE                           1u  /* D0FIFO CPU trans */
#define USB_D0DMA                           2u  /* D0FIFO DMA trans */
#define USB_D1USE                           3u  /* D1FIFO CPU trans */
#define USB_D1DMA                           4u  /* D1FIFO DMA trans */
#define USB_CUSE2                           5u  /* CFIFO CPU trans (not trans count) */

#define USB_WVALUE              (0xFFFFu)   /* b15-0: wValue */
#define USB_DT_TYPE             (0xFF00u)
#define USB_GET_DT_TYPE(v)      (((v) & USB_DT_TYPE) >> 8)
#define USB_DT_INDEX            (0x00FFu)
#define USB_CONF_NUM            (0x00FFu)
#define USB_ALT_SET             (0x00FFu)
#define USB_ALT_NO                          255u

/* Standard Device status */
#define USB_GS_BUSPOWERD                    0x0000u
#define USB_GS_SELFPOWERD                   0x0001u
#define USB_GS_REMOTEWAKEUP                 0x0002u

/* Standard Feature Selector */
#define USB_ENDPOINT_HALT                   0x0000u
#define USB_DEV_REMOTE_WAKEUP               0x0001u
#define USB_TEST_MODE                       0x0002u

#define USB_DEV_MAX_PKT_SIZE                7u  /* Index of bMAXPacketSize */
#define USB_DEV_NUM_CONFIG                  17u /* Index of bNumConfigurations */

#define PROCESS_WAIT_ON             1
#define PROCESS_WAIT_OFF            0
#define NOT_DATA_RECEIVE            0
#define USB_PSMPL_ERROR_SET         1
#define USB_PSMPL_ERROR_CLEAR       0

/* Endpoint status */
#define USB_GS_NOTHALT                      0x0000u
#define USB_GS_HALT                         0x0001u

#define USB_STRINGNUM                   (7u)

/* USB Request Type Register */
/*#define USB_USBREQ        (*((REGP*)(USB_BASE+0x54))) */
#define USB_BREQUEST            (0xFF00u)   /* b15-8: USB_BREQUEST */
#define USB_BMREQUESTTYPE       (0x00FFu)   /* b7-0: USB_BMREQUESTTYPE */
#define USB_BMREQUESTTYPEDIR    (0x0080u)   /* b7  : Data transfer direction */
#define USB_BMREQUESTTYPETYPE   (0x0060u)   /* b6-5: Type */
#define USB_BMREQUESTTYPERECIP  (0x001Fu)   /* b4-0: Recipient */

/* Endpoint Descriptor  Define */
#define USB_EP_DIRMASK                      0x80u   /* Endpoint direction mask [2] */
#define USB_EP_IN                           0x80u   /* In Endpoint */
#define USB_EP_OUT                          0x00u   /* Out Endpoint */
#define USB_EP_NUMMASK                      0x0Fu   /* Endpoint number mask [2] */
#define USB_EP_USGMASK                      0x30u   /* Usage type mask [2] */
#define USB_EP_SYNCMASK                     0x0Cu   /* Synchronization type mask [2] */
#define USB_EP_TRNSMASK                     0x03u   /* Transfer type mask [2] */
#define USB_EP_CNTRL                        0x00u   /* Control Transfer */
#define USB_EP_ISO                          0x01u   /* Isochronous Transfer */
#define USB_EP_BULK                         0x02u   /* Bulk Transfer */
#define USB_EP_INT                          0x03u   /* Interrupt Transfer */

/* Configuration descriptor bit define */
#define USB_CF_RESERVED                     0x80u   /* Reserved(set to 1) */
#define USB_CF_SELFP                        0x40u   /* Self Powered */
#define USB_CF_BUSP                         0x00u   /* Bus Powered */
#define USB_CF_RWUPON                       0x20u   /* Remote Wakeup ON */
#define USB_CF_RWUPOFF                      0x00u   /* Remote Wakeup OFF */

/* Descriptor type  Define */
#define USB_DT_DEVICE                       0x01u   /* Configuration Descriptor */
#define USB_DT_CONFIGURATION                0x02u   /* Configuration Descriptor */
#define USB_DT_STRING                       0x03u   /* Configuration Descriptor */
#define USB_DT_INTERFACE                    0x04u   /* Interface Descriptor */
#define USB_DT_ENDPOINT                     0x05u   /* Endpoint Descriptor */
#define USB_DT_DEVICE_QUALIFIER             0x06u   /* Device Qualifier Descriptor */
#define USB_DT_OTHER_SPEED_CONF             0x07u   /* Other Speed Configuration Descriptor */
#define USB_DT_INTERFACE_POWER              0x08u   /* Interface Power Descriptor */
#define USB_DT_OTGDESCRIPTOR                0x09u   /* OTG Descriptor */
#define USB_DT_HUBDESCRIPTOR                0x29u   /* HUB descriptor */

/* USB_BMREQUESTTYPERECIP   0x001Fu(b4-0) */
#define USB_DEVICE                          0x0000u
#define USB_INTERFACE                       0x0001u
#define USB_ENDPOINT                        0x0002u
#define USB_OTHER                           0x0003u

/* USB Standard request */
/* USB_BREQUEST         0xFF00u(b15-8) */
#define USB_GET_STATUS                      0x0000u
#define USB_CLEAR_FEATURE                   0x0100u
#define USB_REQRESERVED                     0x0200u
#define USB_SET_FEATURE                     0x0300u
#define USB_REQRESERVED1                    0x0400u
#define USB_SET_ADDRESS                     0x0500u
#define USB_GET_DESCRIPTOR                  0x0600u
#define USB_SET_DESCRIPTOR                  0x0700u
#define USB_GET_CONFIGURATION               0x0800u
#define USB_SET_CONFIGURATION               0x0900u
#define USB_GET_INTERFACE                   0x0A00u
#define USB_SET_INTERFACE                   0x0B00u
#define USB_SYNCH_FRAME                     0x0C00u


/* FIFO read / write result */
#define USB_FIFOERROR                       USB_ERROR   /* FIFO not ready */
#define USB_WRITEEND                        0x0000u     /* End of write (but packet may not be outputting) */
#define USB_WRITESHRT                       0x0001u     /* End of write (send short packet) */
#define USB_WRITING                         0x0002u     /* Write continues */
#define USB_READEND                         0x0000u     /* End of read */
#define USB_READSHRT                        0x0001u     /* Insufficient (receive short packet) */
#define USB_READING                         0x0002u     /* Read continues */
#define USB_READOVER                        0x0003u     /* Buffer size over */

#define DTC_NUM_INTERRUPT_SRC       (136)
#define DTC_ACT_BIT_MASK            (0x8000) /* DTC Active flag (DTCSTS.ACT) bit mask */
#define DTC_VECT_NR_MASK            (0x00FF) /* DTC-Activating Vector Number bits mask */
#define DTC_MAX_16BITS_COUNT_VAL    (65536)  /* The maximum value of 16bit count value */
#define DTC_MAX_8BITS_COUNT_VAL     (256)    /* The maximum value of 8bit count value */
#define DTC_MIN_COUNT_VAL           (1)      /* The minimum of count value  and block size */

#define USB0_CFIFO_MBW          USB_MBW_16
#define USB0_D0FIFO_MBW         USB_MBW_16
#define USB0_D1FIFO_MBW         USB_MBW_16
#define USB1_CFIFO_MBW          USB_MBW_16
#define USB1_D0FIFO_MBW         USB_MBW_16
#define USB1_D1FIFO_MBW         USB_MBW_16

#define USB_BUFSIZE_BIT 10
#define USB_BUFSIZE             (0x7C00u)   /* b14-10: Pipe buffer size */
#define USB_BUFNMB              (0x007Fu)   /* b6-0: Pipe buffer number */
#define USB_PIPE0BUF            (256u)
#define USB_PIPEXBUF            (64u)


#define USB_BYTE_SIZE_0             0           /* 0Byte size */
#define USB_BYTE_SIZE_1             1           /* 1Byte size */
#define USB_BYTE_SIZE_2             2           /* 2Byte size */
#define USB_BYTE_SIZE_3             3           /* 3Byte size */
#define USB_BYTE_SIZE_4             4           /* 4Byte size */

/* Error discrimination */
#define USB_DEBUG_HOOK_HWR      0x0100
#define USB_DEBUG_HOOK_HOST     0x0200
#define USB_DEBUG_HOOK_PERI     0x0400
#define USB_DEBUG_HOOK_STD      0x0800
#define USB_DEBUG_HOOK_CLASS    0x1000
#define USB_DEBUG_HOOK_APL      0x2000

/* Error Code */
#define USB_DEBUG_HOOK_CODE1    0x0001
#define USB_DEBUG_HOOK_CODE2    0x0002
#define USB_DEBUG_HOOK_CODE3    0x0003
#define USB_DEBUG_HOOK_CODE4    0x0004
#define USB_DEBUG_HOOK_CODE5    0x0005
#define USB_DEBUG_HOOK_CODE6    0x0006
#define USB_DEBUG_HOOK_CODE7    0x0007
#define USB_DEBUG_HOOK_CODE8    0x0008
#define USB_DEBUG_HOOK_CODE9    0x0009
#define USB_DEBUG_HOOK_CODE10   0x000A
#define USB_DEBUG_HOOK_CODE11   0x000B
#define USB_DEBUG_HOOK_CODE12   0x000C
#define USB_DEBUG_HOOK_CODE13   0x000D
#define USB_DEBUG_HOOK_CODE14   0x000E
#define USB_DEBUG_HOOK_CODE15   0x000F

/* Reset Handshake result */
#define USB_NOCONNECT                       0x0000u /* Speed undecidedness */
#define USB_HSCONNECT                       0x00C0u /* Hi-Speed connect */
#define USB_FSCONNECT                       0x0080u /* Full-Speed connect */
#define USB_LSCONNECT                       0x0040u /* Low-Speed connect */

    /* Start Pipe No */
#define USB_MIN_PIPE_NO         USB_PIPE1


/* Standard Configuration Descriptor Define */
//#define   USB_DEV_B_LENGTH                    0u      /* Size of descriptor */
//#define   USB_DEV_B_DESCRIPTOR_TYPE           1u      /* Descriptor type */
#define USB_DEV_W_TOTAL_LENGTH_L            2       /* Total length of data returned for this configuration */
#define USB_DEV_W_TOTAL_LENGTH_H            3       /* Total length of data returned for this configuration */
#define USB_DEV_B_NUM_INTERFACES            4       /* Number of interfaces supported by this configuration */
#define USB_DEV_B_CONFIGURATION_VALUE       5       /* Configuration value */
#define USB_DEV_I_CONFIGURATION             6       /* Index of string descriptor describing this configuration */
#define USB_DEV_BM_ATTRIBUTES               7       /* Configuration characteristics */
#define USB_DEV_B_MAX_POWER                 8       /* Max power consumption of the USB device from the bus */

/*#define USB_FRMNUM        (*((REGP*)(USB_BASE+0x4C))) */
#define USB_OVRN                (0x8000u)   /* b15: Overrun error */
#define USB_CRCE                (0x4000u)   /* b14: Received data error */
#define USB_FRNM                (0x07FFu)   /* b10-0: Frame number */


/*#define USB_SYSSTS0       (*((REGP*)(USB_BASE+0x04))) */
#define USB_OVCMON              (0xC000u)   /* b15-14: Over-current monitor */
#define USB_OVCBIT              (0x8000u)   /* b15-14: Over-current bit */
#define USB_HTACT               (0x0040u)   /* b6: USB Host Sequencer Status Monitor */
#define USB_IDMON               (0x0004u)   /* b2: ID-pin monitor */
#define USB_LNST                (0x0003u)   /* b1-0: D+, D- line status */
#define USB_SE1                 (0x0003u)   /* SE1 */
#define USB_FS_KSTS             (0x0002u)   /* Full-Speed K State */
#define USB_FS_JSTS             (0x0001u)   /* Full-Speed J State */
#define USB_LS_JSTS             (0x0002u)   /* Low-Speed J State */
#define USB_LS_KSTS             (0x0001u)   /* Low-Speed K State */
#define USB_SE0                 (0x0000u)   /* SE0 */

/*#define USB_PIPEMAXP      (*((REGP*)(USB_BASE+0x6C))) */
#define USB_DEVSEL              (0xF000u)   /* b15-14: Device address select */
#define USB_MAXP                (0x007Fu)   /* b6-0: Maxpacket size of default control pipe */
#define USB_MXPS                (0x07FFu)   /* b10-0: Maxpacket size */

/* CFIFO/DxFIFO Port Select Register */
/*#define USB_CFIFOSEL        (*((REGP*)(USB_BASE+0x20))) */
/*#define USB_D0FIFOSEL       (*((REGP*)(USB_BASE+0x28))) */
/*#define USB_D1FIFOSEL       (*((REGP*)(USB_BASE+0x2C))) */
#define USB_RCNT                (0x8000u)   /* b15: Read count mode */
#define USB_REW                 (0x4000u)   /* b14: Buffer rewind */
#define USB_DCLRM               (0x2000u)   /* b13: DMA buffer clear mode */
#define USB_DREQE               (0x1000u)   /* b12: DREQ output enable */
#define USB_MBW                 (0x0400u)   /* b10: Maximum bit width for FIFO access */
#define USB_MBW_8               (0x0000u)   /*  8bit */
#define USB_MBW_16              (0x0400u)   /* 16bit */
#define USB_BIGEND              (0x0100u)   /* b8: Big endian mode */
#define USB_FIFO_LITTLE         (0x0000u)   /* Little endian */
#define USB_FIFO_BIG            (0x0100u)   /* Big endian */
#define USB_ISEL                (0x0020u)   /* b5: DCP FIFO port direction select */
#define USB_CURPIPE             (0x000Fu)   /* b2-0: PIPE select */

/* CFIFO/DxFIFO Port Control Register */
/*#define USB_CFIFOCTR        (*((REGP*)(USB_BASE+0x22))) */
/*#define USB_D0FIFOCTR       (*((REGP*)(USB_BASE+0x2A))) */
/*#define USB_D1FIFOCTR       (*((REGP*)(USB_BASE+0x2E))) */
#define USB_BVAL                (0x8000u)   /* b15: Buffer valid flag */
#define USB_BCLR                (0x4000u)   /* b14: Buffer clear */
#define USB_FRDY                (0x2000u)   /* b13: FIFO ready */
#define USB_DTLN                (0x0FFFu)   /* b11-0: FIFO data length */


/* Interrupt Enable Register 0 */
/*#define USB_INTENB0     (*((REGP*)(USB_BASE+0x30))) */
#define USB_VBSE                (0x8000u)   /* b15: VBUS interrupt */
#define USB_RSME                (0x4000u)   /* b14: Resume interrupt */
#define USB_SOFE                (0x2000u)   /* b13: Frame update interrupt */
#define USB_DVSE                (0x1000u)   /* b12: Device state transition interrupt */
#define USB_CTRE                (0x0800u)   /* b11: Control transfer stage transition interrupt */
#define USB_BEMPE               (0x0400u)   /* b10: Buffer empty interrupt */
#define USB_NRDYE               (0x0200u)   /* b9: Buffer notready interrupt */
#define USB_BRDYE               (0x0100u)   /* b8: Buffer ready interrupt */

/* Interrupt Enable Register 1 */
/*#define USB_INTENB1     (*((REGP*)(USB_BASE+0x32))) */
/*#define USB_INTENB2     (*((REGP*)(USB_BASE+0x34))) */
#define USB_OVRCRE              (0x8000u)   /* b15: Over-current interrupt */
#define USB_BCHGE               (0x4000u)   /* b14: USB bus change interrupt */
#define USB_DTCHE               (0x1000u)   /* b12: Detach sense interrupt */
#define USB_ATTCHE              (0x0800u)   /* b11: Attach sense interrupt */
#define USB_EOFERRE             (0x0040u)   /* b6: EOF error interrupt */
#define USB_SIGNE               (0x0020u)   /* b5: SETUP IGNORE interrupt */
#define USB_SACKE               (0x0010u)   /* b4: SETUP ACK interrupt */

/* BRDY Interrupt Enable/Status Register */
/*#define USB_BRDYENB     (*((REGP*)(USB_BASE+0x36))) */
/*#define USB_BRDYSTS     (*((REGP*)(USB_BASE+0x46))) */
#define USB_BRDY9               (0x0200u)   /* b9: PIPE9 */
#define USB_BRDY8               (0x0100u)   /* b8: PIPE8 */
#define USB_BRDY7               (0x0080u)   /* b7: PIPE7 */
#define USB_BRDY6               (0x0040u)   /* b6: PIPE6 */
#define USB_BRDY5               (0x0020u)   /* b5: PIPE5 */
#define USB_BRDY4               (0x0010u)   /* b4: PIPE4 */
#define USB_BRDY3               (0x0008u)   /* b3: PIPE3 */
#define USB_BRDY2               (0x0004u)   /* b2: PIPE2 */
#define USB_BRDY1               (0x0002u)   /* b1: PIPE1 */
#define USB_BRDY0               (0x0001u)   /* b1: PIPE0 */

/* NRDY Interrupt Enable/Status Register */
/*#define USB_NRDYENB     (*((REGP*)(USB_BASE+0x38))) */
/*#define USB_NRDYSTS     (*((REGP*)(USB_BASE+0x48))) */
#define USB_NRDY9               (0x0200u)   /* b9: PIPE9 */
#define USB_NRDY8               (0x0100u)   /* b8: PIPE8 */
#define USB_NRDY7               (0x0080u)   /* b7: PIPE7 */
#define USB_NRDY6               (0x0040u)   /* b6: PIPE6 */
#define USB_NRDY5               (0x0020u)   /* b5: PIPE5 */
#define USB_NRDY4               (0x0010u)   /* b4: PIPE4 */
#define USB_NRDY3               (0x0008u)   /* b3: PIPE3 */
#define USB_NRDY2               (0x0004u)   /* b2: PIPE2 */
#define USB_NRDY1               (0x0002u)   /* b1: PIPE1 */
#define USB_NRDY0               (0x0001u)   /* b1: PIPE0 */

/* BEMP Interrupt Enable/Status Register */
/*#define USB_BEMPENB     (*((REGP*)(USB_BASE+0x3A))) */
/*#define USB_BEMPSTS     (*((REGP*)(USB_BASE+0x4A))) */
#define USB_BEMP9               (0x0200u)   /* b9: PIPE9 */
#define USB_BEMP8               (0x0100u)   /* b8: PIPE8 */
#define USB_BEMP7               (0x0080u)   /* b7: PIPE7 */
#define USB_BEMP6               (0x0040u)   /* b6: PIPE6 */
#define USB_BEMP5               (0x0020u)   /* b5: PIPE5 */
#define USB_BEMP4               (0x0010u)   /* b4: PIPE4 */
#define USB_BEMP3               (0x0008u)   /* b3: PIPE3 */
#define USB_BEMP2               (0x0004u)   /* b2: PIPE2 */
#define USB_BEMP1               (0x0002u)   /* b1: PIPE1 */
#define USB_BEMP0               (0x0001u)   /* b0: PIPE0 */

/* SOF Pin Configuration Register */
/*#define USB_SOFCFG          (*((REGP*)(USB_BASE+0x3C))) */
#define USB_TRNENSEL            (0x0100u)   /* b8: Select transaction enable period */
#define USB_BRDYM               (0x0040u)   /* b6: BRDY clear timing */
#define USB_INTL                (0x0020u)   /* b5: Interrupt sense select */
#define USB_EDGESTS             (0x0010u)   /* b4:  */
#define USB_SOFMODE             (0x000Cu)   /* b3-2: SOF pin select */
#define USB_SOF_125US           (0x0008u)   /* SOF 125us Frame Signal */
#define USB_SOF_1MS             (0x0004u)   /* SOF 1ms Frame Signal */
#define USB_SOF_DISABLE         (0x0000u)   /* SOF Disable */


/* Interrupt Status Register 0 */
/*#define USB_INTSTS0     (*((REGP*)(USB_BASE+0x40))) */
#define USB_VBINT               (0x8000u)   /* b15: VBUS interrupt */
#define USB_RESM                (0x4000u)   /* b14: Resume interrupt */
#define USB_SOFR                (0x2000u)   /* b13: SOF update interrupt */
#define USB_DVST                (0x1000u)   /* b12: Device state transition interrupt */
#define USB_CTRT                (0x0800u)   /* b11: Control transfer stage transition interrupt */
#define USB_BEMP                (0x0400u)   /* b10: Buffer empty interrupt */
#define USB_NRDY                (0x0200u)   /* b9: Buffer notready interrupt */
#define USB_BRDY                (0x0100u)   /* b8: Buffer ready interrupt */
#define USB_VBSTS               (0x0080u)   /* b7: VBUS input port */
#define USB_DVSQ                (0x0070u)   /* b6-4: Device state */
#define USB_DS_SPD_CNFG         (0x0070u)   /* Suspend Configured */
#define USB_DS_SPD_ADDR         (0x0060u)   /* Suspend Address */
#define USB_DS_SPD_DFLT         (0x0050u)   /* Suspend Default */
#define USB_DS_SPD_POWR         (0x0040u)   /* Suspend Powered */
#define USB_DS_SUSP             (0x0040u)   /* Suspend */
#define USB_DS_CNFG             (0x0030u)   /* Configured */
#define USB_DS_ADDS             (0x0020u)   /* Address */
#define USB_DS_DFLT             (0x0010u)   /* Default */
#define USB_DS_POWR             (0x0000u)   /* Powered */
#define USB_DVSQS               (0x0030u)   /* b5-4: Device state */
#define USB_VALID               (0x0008u)   /* b3: Setup packet detect flag */
#define USB_CTSQ                (0x0007u)   /* b2-0: Control transfer stage */
#define USB_CS_SQER             (0x0006u)   /* Sequence error */
#define USB_CS_WRND             (0x0005u)   /* Ctrl write nodata status stage */
#define USB_CS_WRSS             (0x0004u)   /* Ctrl write status stage */
#define USB_CS_WRDS             (0x0003u)   /* Ctrl write data stage */
#define USB_CS_RDSS             (0x0002u)   /* Ctrl read status stage */
#define USB_CS_RDDS             (0x0001u)   /* Ctrl read data stage */
#define USB_CS_IDST             (0x0000u)   /* Idle or setup stage */

/* Default Control Pipe Control Register */
/*#define USB_DCPCTR        (*((REGP*)(USB_BASE+0x60))) */
/* Pipex Control Register */
/*#define USB_PIPE1CTR      (*((REGP*)(USB_BASE+0x70))) */
/*#define USB_PIPE2CTR      (*((REGP*)(USB_BASE+0x72))) */
/*#define USB_PIPE3CTR      (*((REGP*)(USB_BASE+0x74))) */
/*#define USB_PIPE4CTR      (*((REGP*)(USB_BASE+0x76))) */
/*#define USB_PIPE5CTR      (*((REGP*)(USB_BASE+0x78))) */
/*#define USB_PIPE6CTR      (*((REGP*)(USB_BASE+0x7A))) */
/*#define USB_PIPE7CTR      (*((REGP*)(USB_BASE+0x7C))) */
/*#define USB_PIPE8CTR      (*((REGP*)(USB_BASE+0x7E))) */
/*#define USB_PIPE9CTR      (*((REGP*)(USB_BASE+0x80))) */
#define USB_BSTS                (0x8000u)   /* b15: Buffer status */
#define USB_SUREQ               (0x4000u)   /* b14: Send USB request  */
#define USB_INBUFM              (0x4000u)   /* b14: IN buffer monitor (Only for PIPE1 to 5) */
#define USB_CSCLR               (0x2000u)   /* b13: c-split status clear */
#define USB_CSSTS               (0x1000u)   /* b12: c-split status */
#define USB_SUREQCLR            (0x0800u)   /* b11: stop setup request */
#define USB_ATREPM              (0x0400u)   /* b10: Auto repeat mode */
#define USB_ACLRM               (0x0200u)   /* b9: buffer auto clear mode */
#define USB_SQCLR               (0x0100u)   /* b8: Sequence bit clear */
#define USB_SQSET               (0x0080u)   /* b7: Sequence bit set */
#define USB_SQMON               (0x0040u)   /* b6: Sequence bit monitor */
#define USB_PBUSY               (0x0020u)   /* b5: pipe busy */
#define USB_PINGE               (0x0010u)   /* b4: ping enable */
#define USB_CCPL                (0x0004u)   /* b2: Enable control transfer complete */
#define USB_PID                 (0x0003u)   /* b1-0: Response PID */
#define USB_PID_STALL           (0x0002u)   /* STALL */
#define USB_PID_BUF             (0x0001u)   /* BUF */
#define USB_PID_NAK             (0x0000u)   /* NAK */

/* System Configuration Control Register */
/*#define USB_SYSCFG0     (*((REGP*)(USB_BASE+0x00))) */
#define USB_SCKE                (0x0400u)   /* b10: USB clock enable */
#define USB_CNEN                (0x0100u)   /* b8: Single end receiver */
#define USB_HSE                 (0x0080u)   /* b7: Hi-speed enable */
#define USB_DCFM                (0x0040u)   /* b6: Function select */
#define USB_DRPD                (0x0020u)   /* b5: D+/D- pull down control */
#define USB_DPRPU               (0x0010u)   /* b4: D+ pull up control */
#define USB_DMRPU               (0x0010u)   /* b4: D- pull up control *//* For low speed */
#define USB_USBE                (0x0001u)   /* b0: USB module enable */

/* PIPExTRE */
/*#define USB_PIPE1TRE      (*((REGP*)(USB_BASE+0x90))) */
/*#define USB_PIPE2TRE      (*((REGP*)(USB_BASE+0x94))) */
/*#define USB_PIPE3TRE      (*((REGP*)(USB_BASE+0x98))) */
/*#define USB_PIPE4TRE      (*((REGP*)(USB_BASE+0x9C))) */
/*#define USB_PIPE5TRE      (*((REGP*)(USB_BASE+0xA0))) */
#define USB_TRENB               (0x0200u)   /* b9: Transaction count enable */
#define USB_TRCLR               (0x0100u)   /* b8: Transaction count clear */


/* PIPExTRN */
/*#define USB_PIPE1TRN      (*((REGP*)(USB_BASE+0x92))) */
/*#define USB_PIPE2TRN      (*((REGP*)(USB_BASE+0x96))) */
/*#define USB_PIPE3TRN      (*((REGP*)(USB_BASE+0x9A))) */
/*#define USB_PIPE4TRN      (*((REGP*)(USB_BASE+0x9E))) */
/*#define USB_PIPE5TRN      (*((REGP*)(USB_BASE+0xA2))) */
#define USB_TRNCNT              (0xFFFFu)   /* b15-0: Transaction counter */

/* DMAx Pin Configuration Register */
/*#define USB_DMA0CFG     (*((REGP*)(USB_BASE+0x10))) */
/*#define USB_DMA1CFG     (*((REGP*)(USB_BASE+0x12))) */
#define USB_DREQA               (0x4000u)   /* b14: Dreq active select */
#define USB_BURST               (0x2000u)   /* b13: Burst mode */
#define USB_DACKA               (0x0400u)   /* b10: Dack active select */
#define USB_DFORM               (0x0380u)   /* b9-7: DMA mode select */
#define USB_CPU_ADR_RD_WR       (0x0000u)   /* Address + RD/WR mode (CPU bus) */
#define USB_CPU_DACK_RD_WR      (0x0100u)   /* DACK + RD/WR (CPU bus) */
#define USB_CPU_DACK_ONLY       (0x0180u)   /* DACK only (CPU bus) */
#define USB_SPLIT_DACK_ONLY     (0x0200u)   /* DACK only (SPLIT bus) */
#define USB_DENDA               (0x0040u)   /* b6: Dend active select */
#define USB_PKTM                (0x0020u)   /* b5: Packet mode */
#define USB_DENDE               (0x0010u)   /* b4: Dend enable */
#define USB_OBUS                (0x0004u)   /* b2: OUTbus mode */

/* Device State Control Register */
/*#define USB_DVSTCTR0      (*((REGP*)(USB_BASE+0x08))) */
#define USB_HNPBTOA             (0x0800u)   /* b11: Host negotiation protocol (BtoA) */
#define USB_EXICEN              (0x0400u)   /* b10: EXICEN output terminal control */
#define USB_VBUSEN              (0x0200u)   /* b9: VBUS output terminal control */
#define USB_WKUP                (0x0100u)   /* b8: Remote wakeup */
#define USB_RWUPE               (0x0080u)   /* b7: Remote wakeup sense */
#define USB_USBRST              (0x0040u)   /* b6: USB reset enable */
#define USB_RESUME              (0x0020u)   /* b5: Resume enable */
#define USB_UACT                (0x0010u)   /* b4: USB bus enable */
#define USB_RHST                (0x0007u)   /* b2-0: Reset handshake status */
#define USB_HSPROC              (0x0004u)   /* HS handshake processing */
#define USB_HSMODE              (0x0003u)   /* Hi-Speed mode */
#define USB_FSMODE              (0x0002u)   /* Full-Speed mode */
#define USB_LSMODE              (0x0001u)   /* Low-Speed mode */
#define USB_UNDECID             (0x0000u)   /* Undecided */

#endif  /* __USB_TYPEDEF_H__ */
/******************************************************************************
End  Of File
******************************************************************************/