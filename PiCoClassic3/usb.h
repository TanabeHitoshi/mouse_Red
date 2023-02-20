#ifndef __USB_H__
#define __USB_H__
/*****************************************************************************
Enumerated Types
******************************************************************************/
typedef enum
{
    USB_SCI_DATA_BIT_7  = 7u,   /* Line Coding 7Data bits */
    USB_SCI_DATA_BIT_8  = 8u    /* Line Coding 8Data bits */
} USB_SCI_DATA_BIT_t;

typedef enum
{
    USB_SCI_PARITY_BIT_NONE = 0u,   /* Line Coding None Parity */
    USB_SCI_PARITY_BIT_ODD  = 1u,   /* Line Coding Odd Parity */
    USB_SCI_PARITY_BIT_EVEN = 2u    /* Line Coding Even Parity */
}
USB_SCI_PARITY_BIT_t;

typedef enum
{
    USB_SCI_SPEED_1200      = 1200u,    /* Line Coding 1200bps */
    USB_SCI_SPEED_2400      = 2400u,    /* Line Coding 2400bps */
    USB_SCI_SPEED_4800      = 4800u,    /* Line Coding 4800bps */
    USB_SCI_SPEED_9600      = 9600u,    /* Line Coding 9600bps */
    USB_SCI_SPEED_14400     = 14400u,   /* Line Coding 14400bps */
    USB_SCI_SPEED_19200     = 19200u,   /* Line Coding 19200bps */
    USB_SCI_SPEED_38400     = 38400u,   /* Line Coding 38400bps */
    USB_SCI_SPEED_57600     = 57600u,   /* Line Coding 57600bps */
    USB_SCI_SPEED_115200    = 115200u,  /* Line Coding 115200bps */
}
USB_SCI_LINE_SPEED_t;

typedef enum
{
    USB_SCI_STOP_BIT_1  = 0u,   /* Line Coding 1Stop bits */
    USB_SCI_STOP_BIT_2  = 2u    /* Line Coding 2Stop bits */
}
USB_SCI_STOT_BIT_t;

typedef enum
{
    STATE_ATTACH,
    STATE_DATA_TRANSFER,
    STATE_DETACH,
}
STATE_t;

typedef enum
{
    EVENT_NONE,
    EVENT_CONFIGERD,
    EVENT_DETACH,
    EVENT_USB_READ_START,
    EVENT_USB_READ_COMPLETE,
    EVENT_USB_WRITE_START,
    EVENT_USB_WRITE_COMPLETE,
    EVENT_COM_NOTIFY_START,
    EVENT_COM_NOTIFY_COMPLETE,
}
EVENT_t;

enum usb_gpcdc_Phase
{
    /* Class Request SET_LINE_CODING */
    USB_PCDC_PSET_LINE_CODING               = 0x10,
    /* Class Request GET_LINE_CODING */
    USB_PCDC_PGET_LINE_CODING               = 0x11,
    /* Class Request SET_CONTROL_LINE_STATE */
    USB_PCDC_PSET_CONTROL_LINE_STATE        = 0x12,
    /* Class Request SEND_BREAK */
    USB_PCDC_PSEND_BREAK                    = 0x13,
    /* Send Data ( Device to Host ) */
    USB_PCDC_PDATASND                       = 0x14,
    /* Receive Data ( Host to Device ) */
    USB_PCDC_PDATARCV                       = 0x15,
    /* Data send request for USB Host */
    USB_PCDC_PSEND_DATA                     = 0x17,
    /* Data receive request for USB Host */
    USB_PCDC_PRECEIVE_DATA                  = 0x18,
    /* Class Notification Serial State */
    USB_PCDC_PSERIAL_STATE_NOTIFICATION     = 0x19,
    /* Send Serial Status ( Device to Host ) */
    USB_PCDC_PSTATUSSND                     = 0x20,
};

typedef enum enum_dtce dtc_activation_source_t;

typedef enum e_dtc_data_size
{
    DTC_DATA_SIZE_BYTE  = (0),      /* = (0 << 4): 8-bit (byte) data */
    DTC_DATA_SIZE_WORD  = (1 << 4), /* 16-bit (word) data */
    DTC_DATA_SIZE_LWORD = (2 << 4)  /* 32-bit (long word) data */
} dtc_data_size_t;

typedef enum e_dtc_transfer_mode
{
    DTC_TRANSFER_MODE_NORMAL = (0),      /* = (0 << 6): Normal mode */
    DTC_TRANSFER_MODE_REPEAT = (1 << 6), /* Repeat mode */
    DTC_TRANSFER_MODE_BLOCK  = (2 << 6)  /* Block mode */
} dtc_transfer_mode_t;

typedef enum e_dtc_src_addr_mode
{
    DTC_SRC_ADDR_FIXED =  (0),      /* = (0 << 2): Source address is fixed. */
    DTC_SRC_ADDR_INCR  =  (2 << 2), /* Source address is incremented after each transfer. */
    DTC_SRC_ADDR_DECR  =  (3 << 2)  /* Source address is decremented after each transfer. */
} dtc_src_addr_mode_t;

typedef enum e_dtc_chain_transfer
{
    DTC_CHAIN_TRANSFER_DISABLE      = (0),      /* Disable Chain transfer. */
    DTC_CHAIN_TRANSFER_ENABLE       = (1 << 7)  /* Enable Chain transfer. */
} dtc_chain_transfer_t;

/* Configurable options for how chain transfer is performed. */
typedef enum e_dtc_chain_transfer_mode
{
    DTC_CHAIN_TRANSFER_CONTINUOUSLY = (0),     /* = (0 << 6): Chain transfer is performed continuously. */
    DTC_CHAIN_TRANSFER_NORMAL       = (1 << 6) /* Chain transfer is performed only when the counter */
                                               /* is changed to 0 or CRAH. */
} dtc_chain_transfer_mode_t;

/* Configurable options for Interrupt */
typedef enum e_dtc_interrupt
{
    DTC_INTERRUPT_AFTER_ALL_COMPLETE  = (0),     /* Interrupt is generated when specified data transfer is completed. */
    DTC_INTERRUPT_PER_SINGLE_TRANSFER = (1 << 5) /* Interrupt is generated when each transfer time is completed. */
} dtc_interrupt_t;

typedef enum e_dtc_repeat_block_side
{
    DTC_REPEAT_BLOCK_DESTINATION = (0),     /* = (0 << 4): Destination is repeat or block area. */
    DTC_REPEAT_BLOCK_SOURCE      = (1 << 4) /* Source is repeat or block area. */
} dtc_repeat_block_side_t;

typedef enum e_dtc_dest_addr_mode
{
    DTC_DES_ADDR_FIXED = (1 << 2), /* Destination address is fixed. */
    DTC_DES_ADDR_INCR  = (2 << 2), /* Destination address is incremented after each transfer. */
    DTC_DES_ADDR_DECR  = (3 << 2)  /* Destination address is decremented after each transfer. */
} dtc_dest_addr_mode_t;


typedef enum e_dtc_command {
    DTC_CMD_DTC_START,               /* DTC will can accept activation requests. */
    DTC_CMD_DTC_STOP,                /* DTC will not accept new activation request. */
    DTC_CMD_ACT_SRC_ENABLE,          /* Enable an activation source specified by vector number. */
    DTC_CMD_ACT_SRC_DISABLE,         /* Disable an activation source specified by vector number. */
    DTC_CMD_DATA_READ_SKIP_ENABLE,   /* Enable Transfer Data Read Skip. */
    DTC_CMD_DATA_READ_SKIP_DISABLE,  /* Disable Transfer Data Read Skip. */
    DTC_CMD_STATUS_GET,              /* Get the current status of DTC. */
    DTC_CMD_CHAIN_TRANSFER_ABORT     /* Abort the current Chain transfer process. */
} dtc_command_t;

typedef enum e_dtc_err       /* DTC API error codes */
{
    DTC_SUCCESS_DMAC_BUSY = 0,  /* One or some DMAC resources are locked by another process. */
    DTC_SUCCESS,
    DTC_ERR_OPENED,             /* DTC was initialized already. */
    DTC_ERR_NOT_OPEN,           /* DTC module is not initialized yet. */
    DTC_ERR_INVALID_ARG,        /* Arguments are invalid. */
    DTC_ERR_INVALID_COMMAND,    /* Command parameters are invalid. */
    DTC_ERR_NULL_PTR,           /* Argument pointers are NULL. */
    DTC_ERR_BUSY                /* The DTC resources are locked by another process. */

} dtc_err_t;


typedef enum 
{
    BSP_LOCK_AD = 0,           
    BSP_LOCK_BSC,       
    BSP_LOCK_CAN0,      
    BSP_LOCK_CAN1,      
    BSP_LOCK_CAN2,      
    BSP_LOCK_CMT,       
    BSP_LOCK_CMT0,      
    BSP_LOCK_CMT1,      
    BSP_LOCK_CMT2,      
    BSP_LOCK_CMT3,      
    BSP_LOCK_CRC,       
    BSP_LOCK_DA,        
    BSP_LOCK_DMAC,      
    BSP_LOCK_DMAC0,     
    BSP_LOCK_DMAC1,     
    BSP_LOCK_DMAC2,     
    BSP_LOCK_DMAC3,     
    BSP_LOCK_DTC,       
    BSP_LOCK_EDMAC,
    BSP_LOCK_ETHERC,
    BSP_LOCK_EXDMAC,
    BSP_LOCK_EXDMAC0,
    BSP_LOCK_EXDMAC1,
    BSP_LOCK_FLASH,     
    BSP_LOCK_ICU,

    BSP_LOCK_IRQ0,
    BSP_LOCK_IRQ1,
    BSP_LOCK_IRQ2,
    BSP_LOCK_IRQ3,
    BSP_LOCK_IRQ4,
    BSP_LOCK_IRQ5,
    BSP_LOCK_IRQ6,
    BSP_LOCK_IRQ7,
    BSP_LOCK_IRQ8,
    BSP_LOCK_IRQ9,
    BSP_LOCK_IRQ10,
    BSP_LOCK_IRQ11,
    BSP_LOCK_IRQ12,
    BSP_LOCK_IRQ13,
    BSP_LOCK_IRQ14,
    BSP_LOCK_IRQ15,

    BSP_LOCK_IEB,       
    BSP_LOCK_IWDT,      
    BSP_LOCK_MPC,       
    BSP_LOCK_MPU,           
    BSP_LOCK_MTU,       
    BSP_LOCK_MTU0,      
    BSP_LOCK_MTU1,      
    BSP_LOCK_MTU2,      
    BSP_LOCK_MTU3,      
    BSP_LOCK_MTU4,      
    BSP_LOCK_MTU5,      
    BSP_LOCK_PDC,
    BSP_LOCK_POE,
    BSP_LOCK_PORT,
    BSP_LOCK_PORT0,
    BSP_LOCK_PORT1,
    BSP_LOCK_PORT2,
    BSP_LOCK_PORT3,
    BSP_LOCK_PORT4,
    BSP_LOCK_PORT5,
    BSP_LOCK_PORT6,
    BSP_LOCK_PORT7,
    BSP_LOCK_PORT8,
    BSP_LOCK_PORT9,
    BSP_LOCK_PORTA,
    BSP_LOCK_PORTB,
    BSP_LOCK_PORTC,
    BSP_LOCK_PORTD,
    BSP_LOCK_PORTE,
    BSP_LOCK_PORTF,
    BSP_LOCK_PORTG,
    BSP_LOCK_PORTJ,
    BSP_LOCK_PPG0,      
    BSP_LOCK_PPG1,      
    BSP_LOCK_RIIC0,     
    BSP_LOCK_RIIC1,     
    BSP_LOCK_RIIC2,     
    BSP_LOCK_RIIC3,     
    BSP_LOCK_RSPI0,     
    BSP_LOCK_RSPI1,     
    BSP_LOCK_RSPI2,     
    BSP_LOCK_RTC,       
    BSP_LOCK_S12AD,     
    BSP_LOCK_SCI0,      
    BSP_LOCK_SCI1,      
    BSP_LOCK_SCI2,      
    BSP_LOCK_SCI3,      
    BSP_LOCK_SCI4,      
    BSP_LOCK_SCI5,      
    BSP_LOCK_SCI6,      
    BSP_LOCK_SCI7,      
    BSP_LOCK_SCI8,      
    BSP_LOCK_SCI9,      
    BSP_LOCK_SCI10,     
    BSP_LOCK_SCI11,     
    BSP_LOCK_SCI12,     
    BSP_LOCK_SMCI0,     
    BSP_LOCK_SMCI1,     
    BSP_LOCK_SMCI2,     
    BSP_LOCK_SMCI3,     
    BSP_LOCK_SMCI4,     
    BSP_LOCK_SMCI5,     
    BSP_LOCK_SMCI6,     
    BSP_LOCK_SMCI7,     
    BSP_LOCK_SMCI8,     
    BSP_LOCK_SMCI9,     
    BSP_LOCK_SMCI10,    
    BSP_LOCK_SMCI11,    
    BSP_LOCK_SMCI12,    
    BSP_LOCK_SYSTEM,    
    BSP_LOCK_TEMPS,     
    BSP_LOCK_TMR0,      
    BSP_LOCK_TMR1,      
    BSP_LOCK_TMR2,      
    BSP_LOCK_TMR3,      
    BSP_LOCK_TMR01,     
    BSP_LOCK_TMR23,     
    BSP_LOCK_TPU0,      
    BSP_LOCK_TPU1,      
    BSP_LOCK_TPU2,      
    BSP_LOCK_TPU3,      
    BSP_LOCK_TPU4,      
    BSP_LOCK_TPU5,      
    BSP_LOCK_TPU6,      
    BSP_LOCK_TPU7,      
    BSP_LOCK_TPU8,      
    BSP_LOCK_TPU9,      
    BSP_LOCK_TPU10,     
    BSP_LOCK_TPU11,     
    BSP_LOCK_TPUA,      
    BSP_LOCK_TPUB,      
    BSP_LOCK_USB,       
    BSP_LOCK_USB0,      
    BSP_LOCK_USB1,      
    BSP_LOCK_WDT,       
    BSP_NUM_LOCKS //This entry is not a valid lock. It is used for sizing g_bsp_Locks[] array below. Do not touch!
} mcu_lock_t;

typedef enum e_sci_mode     // SCI operational modes
{
    SCI_MODE_OFF=0,         // channel not in use
    SCI_MODE_ASYNC,         // Asynchronous
    SCI_MODE_SSPI,          // Simple SPI
    SCI_MODE_SYNC,          // Synchronous
    SCI_MODE_MAX,           // End of modes currently supported
} sci_mode_t;

typedef enum e_sci_cmd
{
    // All modes
    SCI_CMD_CHANGE_BAUD,        // change baud/bit rate

    // Async commands
    SCI_CMD_EN_NOISE_CANCEL,    // enable noise cancellation
    SCI_CMD_EN_TEI,             // enable TEI interrupts
    SCI_CMD_OUTPUT_BAUD_CLK,    // output baud clock on the SCK pin
    SCI_CMD_START_BIT_EDGE,     // detect start bit as falling edge of RXDn pin
                                // (default detect as low level on RXDn pin)
    SCI_CMD_GENERATE_BREAK,     // generate break condition
    SCI_CMD_TX_Q_FLUSH,         // flush transmit queue
    SCI_CMD_RX_Q_FLUSH,         // flush receive queue
    SCI_CMD_TX_Q_BYTES_FREE,    // get count of unused transmit queue bytes
    SCI_CMD_RX_Q_BYTES_AVAIL_TO_READ, // get num bytes ready for reading

    // Async/Sync commands
    SCI_CMD_EN_CTS_IN,          // enable CTS input (default RTS output)

    // SSPI/Sync commands
    SCI_CMD_CHECK_XFER_DONE,    // see if send, rcv, or both are done; SCI_SUCCESS if yes
    SCI_CMD_ABORT_XFER,
    SCI_CMD_XFER_LSB_FIRST,
    SCI_CMD_XFER_MSB_FIRST,
    SCI_CMD_INVERT_DATA,

    // SSPI commands
    SCI_CMD_CHANGE_SPI_MODE
} sci_cmd_t;

typedef enum e_usb_err_t
{
    USB_SUCCESS = 0,        
    USB_ERR_OPENED,         /* USB was initialized already */
    USB_ERR_NOT_OPEN,       /* USB module is not initialized yet */
    USB_ERR_INVALID_ARG,    /* Arguments are invalid */
    USB_ERR_NULL_PTR,       /* Argument pointers are NULL */
    USB_ERR_BUSY,           /* The USB resources is locked by another process */
} usb_err_t;

typedef enum e_usb_ip       /* USB IP type */
{
    USB_IP0 = 0,
    USB_IP1 = 1,
} usb_ip_t;

/******************************************************************************
Typedef definitions
******************************************************************************/
typedef struct st_sci_ch_rom    // SCI ROM info for channel control block
{
    volatile  __evenaccess struct st_sci12  *regs;  // base ptr to ch registers
    volatile  __evenaccess uint32_t *mstp;      // ptr to mstp register
    uint32_t                        stop_mask;  // mstp mask to disable ch
    volatile  __evenaccess uint8_t  *ipr;       // ptr to IPR register
    volatile  __evenaccess uint8_t  *ir_rxi;    // ptr to RXI IR register
    volatile  __evenaccess uint8_t  *ir_txi;    // ptr to TXI IR register
    volatile  __evenaccess uint8_t  *ir_tei;    // ptr to TEI IR register
    /* 
    * DO NOT use the enable/disable interrupt bits in the SCR 
    * register. Pending interrupts can be lost that way.
    */
    volatile  __evenaccess uint8_t  *icu_rxi;   // ptr to ICU register
    volatile  __evenaccess uint8_t  *icu_txi;   
    volatile  __evenaccess uint8_t  *icu_tei; 
    uint16_t    group12_ch_mask;    // bit mask to enable/disable rx error int in ICU
    uint8_t     rxi_en_mask;    // bit mask to enable/disable rxi INT in ICU
    uint8_t     txi_en_mask;    // bit mask to enable/disable txi INT in ICU   
    uint8_t     tei_en_mask;    // bit mask to enable/disable tei INT in ICU
} sci_ch_rom_t;
typedef struct st_sci_ch_ctrl       // SCI channel control (for handle)
{
    sci_ch_rom_t const *rom;        // pointer to rom info
    sci_mode_t      mode;           // operational mode
    uint32_t        baud_rate;      // baud rate
    void          (*callback)(void *p_args); // function ptr for rcvr errs
    union
    {
#if (SCI_CFG_ASYNC_INCLUDED)
        byteq_hdl_t     que;        // async transmit queue handle
#endif
        uint8_t         *buf;       // sspi/sync tx buffer ptr
    } u_tx_data;
    union
    {
#if (SCI_CFG_ASYNC_INCLUDED)
        byteq_hdl_t     que;        // async receive queue handle
#endif
        uint8_t         *buf;       // sspi/sync rx buffer ptr
    } u_rx_data;
    bool            tx_idle;        // TDR is empty (async); TSR is empty (sync/sspi)
#if (SCI_CFG_SSPI_INCLUDED || SCI_CFG_SYNC_INCLUDED)
    bool            save_rx_data;   // save the data that is clocked in
    uint16_t        tx_cnt;         // number of bytes to transmit
    bsp_lock_t      xcvr_lock;
    bool            tx_dummy;       // transmit dummy byte, not buffer
#endif
} sci_ch_ctrl_t;

typedef void (*USB_CB_t)(struct USB_UTR *, uint16_t, uint16_t);
typedef volatile struct st_usb0 __evenaccess*   USB_REGADR_t;

typedef void*           VP;             /* Pointer to variable      */
typedef long            ER;             /* Error code               */
typedef long            VP_INT;         /* Integer data             */
typedef long            TMO;            /* Time out                 */
typedef short           ID;             /* Object ID (xxxid)        */

/*----------- msghead -----------*/
    typedef struct
    {
        VP              msghead;        /* Message header               */
    } T_MSG;
	
typedef VP              USB_MH_t;       /* ITRON Message Header     */
typedef ER              USB_ER_t;       /* ITRON system call err    */
typedef T_MSG           USB_MSG_t;      /* ITRON message            */
typedef VP_INT          USB_VP_INT_t;
typedef TMO             USB_TM_t;       /* ITRON time out           */
typedef ID              USB_ID_t;       /* ITRON system call define */

typedef struct USB_UTR      USB_PCDINFO_t;

typedef struct st_sci_ch_ctrl * sci_hdl_t;


typedef struct DEV_INFO             /* Structure for HID device control */
{
    uint16_t    state;              /* State for application */
    uint16_t    event_cnt;          /* Event count */
    uint16_t    event[EVENT_MAX];   /* Event no. */
}
DEV_INFO_t;

typedef struct
{
    uint16_t        ReqType;            /* Request type */
    uint16_t        ReqTypeType;        /* Request type TYPE */
    uint16_t        ReqTypeRecip;       /* Request type RECIPIENT */
    uint16_t        ReqRequest;         /* Request */
    uint16_t        ReqValue;           /* Value */
    uint16_t        ReqIndex;           /* Index */
    uint16_t        ReqLength;          /* Length */
} USB_REQUEST_t;

typedef struct USB_UTR
{
    USB_MH_t        msghead;        /* Message header (for SH-solution) */
    uint16_t        msginfo;        /* Message Info for F/W */
    uint16_t        keyword;        /* Rootport / Device address / Pipe number */
    USB_REGADR_t    ipp;            /* IP Address(USB0orUSB1)*/
    uint16_t        ip;             /* IP number(0or1) */
    uint16_t        result;         /* Result */
    USB_CB_t        complete;       /* Call Back Function Info */
    void            *tranadr;       /* Transfer data Start address */
    uint32_t        tranlen;        /* Transfer data length */
    uint16_t        *setup;         /* Setup packet(for control only) */
    uint16_t        status;         /* Status */
    uint16_t        pipectr;        /* Pipe control register */
    uint8_t         errcnt;         /* Error count */
    uint8_t         segment;        /* Last flag */
    int16_t         fn;             /* File Number */
    void            *usr_data;      
} USB_UTR_t;

typedef void (*USB_CB_TRN_t)(USB_UTR_t *, USB_REQUEST_t*, uint16_t ctsq);


typedef struct
{
    /* reserve */
    uint16_t                    rsv:14;
    /* RTS */
    uint16_t                    bRTS:1;
    /* DTR */
    uint16_t                    bDTR:1;
}
USB_PCDC_ControlLineState_t;

typedef struct
{
    /* Data terminal rate, in bits per second */
    uint32_t                    dwDTERate;
    /* Stop bits */
    uint8_t                     bCharFormat;
    /* Parity */
    uint8_t                     bParityType;
    /* Data bits */
    uint8_t                     bDataBits;
    /* reserve */
    uint8_t                     rsv;
}
USB_PCDC_LineCoding_t;


/* Full-address mode */
typedef struct st_transfer_data { /* 4 long-words */
    uint32_t lw1;
    uint32_t lw2;
    uint32_t lw3;
    uint32_t lw4;
} dtc_transfer_data_t;

typedef struct st_dtc_transfer_data_cfg {
    dtc_transfer_mode_t       transfer_mode;         /* DTC transfer mode */
    dtc_data_size_t           data_size;             /* Size of data */
    dtc_src_addr_mode_t       src_addr_mode;         /* Address mode of source */
    dtc_chain_transfer_t      chain_transfer_enable; /* Chain transfer is enabled or not. */
    dtc_chain_transfer_mode_t chain_transfer_mode;   /* How chain transfer is performed. */
    dtc_interrupt_t           response_interrupt;    /* How response interrupt is raised */
    dtc_repeat_block_side_t   repeat_block_side;     /* The side being repeat or block in */
                                                     /*  repeat / block transfer mode. */
    dtc_dest_addr_mode_t      dest_addr_mode;        /* Address mode of destination */
    uint32_t                  source_addr;           /* Start address of source */
    uint32_t                  dest_addr;             /* Start address of destination */
    uint32_t                  transfer_count;        /* Transfer count */
    uint16_t                  block_size;            /* Size of a block in block transfer mode */
} dtc_transfer_data_cfg_t;


typedef struct st_dtc_stat {
    uint8_t    vect_nr;                              /* the current vector number */
    bool       in_progress;                          /* Active flag of DTC module */
} dtc_stat_t;

typedef struct st_dtc_cmd_arg {
    dtc_activation_source_t act_src;                 /* The activation source will be controlled */
    uint32_t                chain_transfer_nr;       /* Number of chain transfer when command */
                                                     /* is DTC_CMD_CHAIN_TRANSFER_ABORT. */
} dtc_cmd_arg_t;


typedef union dtc_mra {
    uint8_t BYTE;
    struct {
        uint8_t MD:2; /* b7,b6: DTC Transfer Mode Select */
        uint8_t SZ:2; /* DTC Data Transfer Size */
        uint8_t SM:2; /* Transfer Source Address Addressing Mode */
        uint8_t rs:2; /* reserved */
    } BIT;

} dtc_mra_t;

/* The DTC Mode Register B (MRB) structure */
typedef union dtc_mrb {
    uint8_t BYTE;
    struct {
        uint8_t CHNE :1;  /* b7: DTC Chain Transfer Enable */
        uint8_t CHNS :1;  /* DTC Chain Transfer Select */
        uint8_t DISEL:1;  /* DTC Interrupt Select */
        uint8_t DTS  :1;  /* DTC Transfer Mode Select */
        uint8_t DM   :2;  /* Transfer Destination Address Addressing Mode */
        uint8_t rs   :2;  /* reserved */
    } BIT;

} dtc_mrb_t;

/* The DTC Transfer Count Register A (CRA) structure */
typedef union dtc_cra {
    uint16_t WORD;
    struct {
        uint8_t CRA_L;
        uint8_t CRA_H;
    } BYTE;
} dtc_cra_t;

/* The DTC Transfer Count Register B (CRB) structure */
typedef union dtc_crb {
    uint16_t WORD;
} dtc_crb_t;

typedef struct st_dtc_full_transfer_data {
    union {
        uint32_t LWORD;
        struct {
            uint16_t  reserver; /* reserve area */
            dtc_mrb_t MRB;
            dtc_mra_t MRA;
        } REG;
    } FIRST_LWORD;
    union {
        uint32_t SAR;
    } SECOND_LWORD;
    union {
        uint32_t DAR;
    } THIRD_LWORD;
    union {
        uint32_t LWORD;
        struct {
            dtc_crb_t CRB;
            dtc_cra_t CRA;
        } REG;
    } FOURTH_LWORD;
} dtc_internal_registers_t;



typedef struct
{
    /* The actual lock. int32_t is used because this is what the xchg() instruction takes as parameters. */
    int32_t     lock;
    /* Could add a ID for locking and unlocking. In this could protect against any function being able to unlock. */
} bsp_lock_t;

typedef struct USB_PCDREG
{
    uint16_t        **pipetbl;      /* Pipe Define Table address */
    uint8_t         *devicetbl;     /* Device descriptor Table address */
    uint8_t         *qualitbl;      /* Qualifier descriptor Table address */
    uint8_t         **configtbl;    /* Configuration descriptor
                                        Table address */
    uint8_t         **othertbl;     /* Other configuration descriptor
                                        Table address */
    uint8_t         **stringtbl;    /* String descriptor Table address */
    USB_CB_t        classinit;      /* Driver init */
    USB_CB_t        devdefault;     /* Device default */
    USB_CB_t        devconfig;      /* Device configured */
    USB_CB_t        devdetach;      /* Device detach */
    USB_CB_t        devsuspend;     /* Device suspend */
    USB_CB_t        devresume;      /* Device resume */
    USB_CB_t        interface;      /* Interface changed */
    USB_CB_TRN_t    ctrltrans;      /* Control Transfer */
} USB_PCDREG_t;

typedef struct st_sci_baud
{
    uint32_t    pclk;       // peripheral clock speed; e.g. 24000000 is 24MHz
    uint32_t    rate;       // e.g. 9600, 19200, 115200
} sci_baud_t;

typedef struct
{
    /* reserve */
    uint16_t                    rsv:9;
    /* Over Run error */
    uint16_t                    bOverRun:1;
    /* Parity error */
    uint16_t                    bParity:1;
    /* Framing error */
    uint16_t                    bFraming:1;
    /* State of ring signal detection of the device */
    uint16_t                    bRingSignal:1;
    /* State of break detection mechanism of teh device */
    uint16_t                    bBreak:1;
    /* DSR signal */
    uint16_t                    bTxCarrier:1;
    /* DCD signal */
    uint16_t                    bRxCarrier:1;
}
USB_SCI_SerialState_t;

typedef struct st_baud_divisor
{
    int16_t     divisor;    // clock divisor
    uint8_t     abcs;       // abcs value to get divisor
    uint8_t     cks;        // cks  value to get divisor (cks = n)
} baud_divisor_t;


const dtc_activation_source_t source_array2[DTC_NUM_INTERRUPT_SRC] =
{
DTCE_ICU_SWINT,
DTCE_CMT0_CMI0,
DTCE_CMT1_CMI1,
DTCE_CMT2_CMI2,
DTCE_CMT3_CMI3,
DTCE_USB0_D0FIFO0,
DTCE_USB0_D1FIFO0,
DTCE_USB1_D0FIFO1,
DTCE_USB1_D1FIFO1,
DTCE_RSPI0_SPRI0,
DTCE_RSPI0_SPTI0,
DTCE_RSPI1_SPRI1,
DTCE_RSPI1_SPTI1,
DTCE_RSPI2_SPRI2,
DTCE_RSPI2_SPTI2,
DTCE_ICU_IRQ0,
DTCE_ICU_IRQ1,
DTCE_ICU_IRQ2,
DTCE_ICU_IRQ3,
DTCE_ICU_IRQ4,
DTCE_ICU_IRQ5,
DTCE_ICU_IRQ6,
DTCE_ICU_IRQ7,
DTCE_ICU_IRQ8,
DTCE_ICU_IRQ9,
DTCE_ICU_IRQ10,
DTCE_ICU_IRQ11,
DTCE_ICU_IRQ12,
DTCE_ICU_IRQ13,
DTCE_ICU_IRQ14,
DTCE_ICU_IRQ15,
DTCE_AD_ADI0,
DTCE_S12AD_S12ADI0,
DTCE_TPU0_TGI0A,
DTCE_TPU0_TGI0B,
DTCE_TPU0_TGI0C,
DTCE_TPU0_TGI0D,
DTCE_TPU1_TGI1A,
DTCE_TPU1_TGI1B,
DTCE_TPU2_TGI2A,
DTCE_TPU2_TGI2B,
DTCE_TPU3_TGI3A,
DTCE_TPU3_TGI3B,
DTCE_TPU3_TGI3C,
DTCE_TPU3_TGI3D,
DTCE_TPU4_TGI4A,
DTCE_TPU4_TGI4B,
DTCE_TPU5_TGI5A,
DTCE_TPU5_TGI5B,
DTCE_TPU6_TGI6A,
DTCE_TPU6_TGI6B,
DTCE_TPU6_TGI6C,
DTCE_TPU6_TGI6D,
DTCE_MTU0_TGIA0,
DTCE_MTU0_TGIB0,
DTCE_MTU0_TGIC0,
DTCE_MTU0_TGID0,
DTCE_TPU7_TGI7A,
DTCE_TPU7_TGI7B,
DTCE_MTU1_TGIA1,
DTCE_MTU1_TGIB1,
DTCE_TPU8_TGI8A,
DTCE_TPU8_TGI8B,
DTCE_MTU2_TGIA2,
DTCE_MTU2_TGIB2,
DTCE_TPU9_TGI9A,
DTCE_TPU9_TGI9B,
DTCE_TPU9_TGI9C,
DTCE_TPU9_TGI9D,
DTCE_MTU3_TGIA3,
DTCE_MTU3_TGIB3,
DTCE_MTU3_TGIC3,
DTCE_MTU3_TGID3,
DTCE_TPU10_TGI10A,
DTCE_TPU10_TGI10B,
DTCE_MTU4_TGIA4,
DTCE_MTU4_TGIB4,
DTCE_MTU4_TGIC4,
DTCE_MTU4_TGID4,
DTCE_MTU4_TCIV4,
DTCE_TPU11_TGI11A,
DTCE_TPU11_TGI11B,
DTCE_MTU5_TGIU5,
DTCE_MTU5_TGIV5,
DTCE_MTU5_TGIW5,
DTCE_TMR0_CMIA0,
DTCE_TMR0_CMIB0,
DTCE_TMR1_CMIA1,
DTCE_TMR1_CMIB1,
DTCE_TMR2_CMIA2,
DTCE_TMR2_CMIB2,
DTCE_TMR3_CMIA3,
DTCE_TMR3_CMIB3,
DTCE_RIIC0_RXI0,
DTCE_RIIC0_TXI0,
DTCE_RIIC1_RXI1,
DTCE_RIIC1_TXI1,
DTCE_RIIC2_RXI2,
DTCE_RIIC2_TXI2,
DTCE_RIIC3_RXI3,
DTCE_RIIC3_TXI3,
DTCE_DMAC_DMAC0I,
DTCE_DMAC_DMAC1I,
DTCE_DMAC_DMAC2I,
DTCE_DMAC_DMAC3I,
DTCE_EXDMAC_EXDMAC0I,
DTCE_EXDMAC_EXDMAC1I,
DTCE_DEU_DEU0,
DTCE_DEU_DEU1,
DTCE_PDC_PCDFI,
DTCE_SCI0_RXI0,
DTCE_SCI0_TXI0,
DTCE_SCI1_RXI1,
DTCE_SCI1_TXI1,
DTCE_SCI2_RXI2,
DTCE_SCI2_TXI2,
DTCE_SCI3_RXI3,
DTCE_SCI3_TXI3,
DTCE_SCI4_RXI4,
DTCE_SCI4_TXI4,
DTCE_SCI5_RXI5,
DTCE_SCI5_TXI5,
DTCE_SCI6_RXI6,
DTCE_SCI6_TXI6,
DTCE_SCI7_RXI7,
DTCE_SCI7_TXI7,
DTCE_SCI8_RXI8,
DTCE_SCI8_TXI8,
DTCE_SCI9_RXI9,
DTCE_SCI9_TXI9,
DTCE_SCI10_RXI10,
DTCE_SCI10_TXI10,
DTCE_SCI11_RXI11,
DTCE_SCI11_TXI11,
DTCE_SCI12_RXI12,
DTCE_SCI12_TXI12
};

#endif  /* __USB_H__ */

/*****************************************************************************
Function
******************************************************************************/
void usb_mcu_init(void);
void usb_cdc_driver( void );
uint16_t cdc_connect_wait( void );
void cdc_detach_device( void );
uint16_t cdc_data_transfer( void );
void cdc_low_power_control( uint16_t state );
void usb_driver_init( void );
void apl_init( void );
void R_usb_cstd_Scheduler(void);
void usb_cstd_WaitScheduler(void);
USB_ER_t R_usb_cstd_SndMsg( uint8_t id, USB_MSG_t* mess );
USB_ER_t usb_cstd_SndMsg( uint8_t id, USB_MSG_t* mess );
void usb_cpu_int_disable(USB_UTR_t *ptr);
USB_ER_t usb_cstd_iSndMsg( uint8_t id, USB_MSG_t* mess );
void usb_cpu_int_enable(USB_UTR_t *ptr);
void usb_cstd_ScheInit(void);
uint8_t R_usb_cstd_CheckSchedule(void);
void R_usb_pstd_PcdTask(USB_VP_INT stacd);
void R_usb_pcdc_task(USB_VP_INT_t stacd);
void usb_pcdc_task(USB_VP_INT_t stacd);
USB_ER_t R_usb_cstd_RecMsg( uint8_t id, USB_MSG_t** mess, USB_TM_t tm );
USB_ER_t usb_cstd_RelBlk( uint8_t id,  USB_UTR_t* blk );
uint16_t usb_cpu_Sci_SetDataChk(uint8_t *data_rate_top, uint8_t stop_bit, uint8_t parity, uint8_t data_bit);
USB_ER_t R_usb_cstd_RelBlk( uint8_t id,  USB_UTR_t* blk );
void usb_pcdc_InTransResult(USB_UTR_t *mess, uint16_t data1, uint16_t data2);
USB_ER_t usb_pcdc_UserDataTrans(USB_UTR_t *ptr, uint16_t pipe, uint32_t size, uint8_t *table);
void usb_pcdc_OutTransResult(USB_UTR_t *mess, uint16_t data1, uint16_t data2);
void usb_pcdc_StatusTransResult(USB_UTR_t *mess, uint16_t data1, uint16_t data2);
USB_ER_t R_usb_pstd_TransferStart(USB_UTR_t *ptr);
uint16_t usb_cstd_GetPipeType(USB_UTR_t *ptr, uint16_t pipe);
uint16_t usb_pstd_ChkConfigured(USB_UTR_t *ptr);
USB_ER_t usb_cstd_SndMsg( uint8_t id, USB_MSG_t* mess );
uint16_t usb_creg_read_intsts( USB_UTR_t *ptr );
void usb_creg_write_pipesel( USB_UTR_t *ptr, uint16_t data );
uint16_t usb_creg_read_pipecfg( USB_UTR_t *ptr );
USB_ER_t usb_cstd_RecMsg( uint8_t id, USB_MSG_t** mess, USB_TM_t tm );
void usb_pstd_PcdTask(USB_VP_INT stacd);
void usb_pstd_InterruptHandler(USB_UTR_t *ptr);
void usb_preg_clr_sts_valid( USB_UTR_t *ptr );
void usb_pstd_InterruptEnable(USB_UTR_t *ptr);
void usb_creg_set_intenb( USB_UTR_t *ptr, uint16_t data );
void usb_pstd_Interrupt(USB_UTR_t *ptr);
void usb_cstd_InterruptClock(USB_UTR_t *ptr);
USB_ER_t usb_pstd_SetSubmitutr(USB_UTR_t *ptr, USB_UTR_t *utrmsg);
void usb_cstd_SelfClock(USB_UTR_t *ptr);
void usb_pstd_RemoteWakeup(USB_UTR_t *ptr);
void usb_pstd_PcdRelMpl(uint16_t n);
void usb_creg_set_sqclr( USB_UTR_t *ptr, uint16_t pipeno );
void usb_pstd_SetStall(USB_UTR_t *ptr, uint16_t pipe);
void usb_cstd_ForcedTermination(USB_UTR_t *ptr, uint16_t pipe, uint16_t status);
void usb_pstd_DetachProcess(USB_UTR_t *ptr);
void usb_pstd_AttachProcess(USB_UTR_t *ptr);
void usb_pstd_DpDisable(USB_UTR_t *ptr);
void usb_pstd_DpEnable(USB_UTR_t *ptr);
void usb_preg_clr_dprpu( USB_UTR_t *ptr );
void usb_preg_set_dprpu( USB_UTR_t *ptr );
void usb_cstd_D0fifoInt(USB_UTR_t *ptr);
void usb_creg_set_mbw( USB_UTR_t *ptr, uint16_t pipemode, uint16_t data );
void usb_cpu_d0fifo_restart_dma( USB_UTR_t *ptr );
void usb_cpu_d0fifo_enable_dma(USB_UTR_t *ptr);
void usb_creg_set_dreqe( USB_UTR_t *ptr, uint16_t pipemode );
void usb_cstd_dtc_write_not_4alignment(USB_UTR_t *ptr);
void usb_creg_set_bval( USB_UTR_t *ptr, uint16_t pipemode );
void usb_creg_set_bempenb( USB_UTR_t *ptr, uint16_t pipeno );
static  void *usb_creg_get_fifoctr_adr( USB_UTR_t *ptr, uint16_t pipemode );
void  usb_creg_write_fifo8( USB_UTR_t *ptr, uint16_t pipemode, uint8_t data );
static  void *usb_creg_get_fifosel_adr( USB_UTR_t *ptr, uint16_t pipemode );
uint32_t usb_cstd_GetD0fifo8Adr( USB_UTR_t *ptr );
dtc_err_t R_DTC_Create(dtc_activation_source_t act_source, dtc_transfer_data_t *p_transfer_data, dtc_transfer_data_cfg_t *p_data_cfg, uint32_t chain_transfer_nr);
dtc_err_t R_DTC_Control(dtc_command_t command, dtc_stat_t *p_stat, dtc_cmd_arg_t *p_args);
static void r_dtc_release_hw_lock(void);
static bool r_dtc_abort_chain_transfer(uint32_t chain_transfer_nr);
bool R_BSP_HardwareUnlock (mcu_lock_t const hw_index);
bool R_BSP_SoftwareUnlock (BSP_CFG_USER_LOCKING_TYPE * const plock);
static dtc_err_t r_dtc_set_transfer_data(dtc_transfer_data_t *p_transfer_data, dtc_transfer_data_cfg_t *p_cfg);
void usb_pstd_AttachFunction(USB_UTR_t *ptr);
void usb_cpu_DelayXms(uint16_t time);
void usb_creg_clr_cnen( USB_UTR_t *ptr );
void usb_cpu_Delay1us(uint16_t time);
void usb_creg_set_dcfm( USB_UTR_t *ptr );
void usb_creg_clr_dcfm( USB_UTR_t *ptr );
void usb_cstd_DummyFunction(USB_UTR_t *ptr, uint16_t data1, uint16_t data2);
void usb_cstd_DummyTrn(USB_UTR_t *ptr, USB_REQUEST_t *data1, uint16_t data2);
void usb_cstd_ClrPipeCnfg(USB_UTR_t *ptr, uint16_t pipe_no);
void usb_cstd_StopClock(USB_UTR_t *ptr);
void usb_cstd_ClrStall(USB_UTR_t *ptr, uint16_t pipe);
void usb_cstd_SetNak(USB_UTR_t *ptr, uint16_t pipe);
void usb_creg_clr_pid( USB_UTR_t *ptr, uint16_t pipeno, uint16_t data) ;
void usb_creg_clr_sts_bemp( USB_UTR_t *ptr, uint16_t pipeno );
void usb_creg_clr_sts_nrdy( USB_UTR_t *ptr, uint16_t pipeno );
void usb_creg_clr_sts_brdy( USB_UTR_t *ptr, uint16_t pipeno );
void usb_creg_set_csclr( USB_UTR_t *ptr, uint16_t pipeno );
void usb_creg_clr_brdyenb( USB_UTR_t *ptr, uint16_t  pipeno );
void usb_creg_clr_nrdyenb(USB_UTR_t *ptr, uint16_t pipeno );
void usb_creg_clr_bempenb( USB_UTR_t *ptr, uint16_t pipeno );
void usb_cstd_DoAclrm(USB_UTR_t *ptr, uint16_t pipe);
void usb_creg_set_aclrm( USB_UTR_t *ptr, uint16_t pipeno );
void usb_creg_clr_aclrm( USB_UTR_t *ptr, uint16_t pipeno );
void usb_cstd_SetTransactionCounter(USB_UTR_t *ptr, uint16_t trnreg, uint16_t trncnt);
void usb_creg_set_trclr( USB_UTR_t *ptr, uint16_t pipeno );
void usb_creg_write_pipetrn( USB_UTR_t *ptr, uint16_t pipeno, uint16_t data );
void usb_creg_set_trenb( USB_UTR_t *ptr, uint16_t pipeno );
void usb_cstd_chg_curpipe(USB_UTR_t *ptr, uint16_t pipe, uint16_t fifosel, uint16_t isel);
uint16_t usb_creg_read_fifosel( USB_UTR_t *ptr, uint16_t pipemode );
void usb_cpu_d0fifo_stop_dma(USB_UTR_t *ptr);
void usb_cstd_D0fifoStopUsb(USB_UTR_t *ptr);
void usb_creg_write_pipecfg( USB_UTR_t *ptr, uint16_t data );
void usb_creg_write_pipebuf( USB_UTR_t *ptr, uint16_t data );
void usb_creg_write_pipemaxp( USB_UTR_t *ptr, uint16_t data );
void usb_creg_write_pipeperi( USB_UTR_t *ptr, uint16_t data );
void usb_cstd_ClrTransactionCounter(USB_UTR_t *ptr, uint16_t trnreg);
void usb_creg_clr_trenb( USB_UTR_t *ptr, uint16_t pipeno );
void usb_creg_clr_dreqe( USB_UTR_t *ptr, uint16_t pipemode );
void usb_creg_rmw_fifosel( USB_UTR_t *ptr, uint16_t pipemode, uint16_t data, uint16_t bitptn );
uint16_t usb_creg_read_pipectr( USB_UTR_t *ptr, uint16_t pipeno );
uint16_t usb_creg_read_fifoctr( USB_UTR_t *ptr, uint16_t pipemode );
void usb_cstd_D0FifoselSet(USB_UTR_t *ptr);
void usb_creg_write_dmacfg( USB_UTR_t *ptr, uint16_t pipemode, uint16_t data );
void usb_creg_set_bclr( USB_UTR_t *ptr, uint16_t pipemode );
void usb_creg_clr_dclrm( USB_UTR_t *ptr, uint16_t pipemode );
void R_usb_pstd_DeviceInformation(USB_UTR_t *ptr, uint16_t *tbl);
void usb_preg_clr_enb_rsme( USB_UTR_t *ptr );
void usb_creg_set_xcke( USB_UTR_t *ptr );
void usb_preg_clr_sts_resm( USB_UTR_t *ptr );
void usb_preg_set_wkup( USB_UTR_t *ptr );
uint16_t usb_cstd_PortSpeed(USB_UTR_t *ptr, uint16_t port);
uint16_t usb_pstd_GetInterfaceNum(uint16_t con_num);
uint16_t usb_pstd_get_confignum_to_tblindex(uint16_t con_num);
uint16_t usb_creg_read_dvstctr( USB_UTR_t *ptr, uint16_t port );
void usb_pstd_SetReTransfer(USB_UTR_t *ptr, uint16_t pipe);
uint16_t usb_cstd_GetPipeDir(USB_UTR_t *ptr, uint16_t pipe);
void usb_cstd_ReceiveStart(USB_UTR_t *ptr, uint16_t pipe);
void usb_cstd_SendStart(USB_UTR_t *ptr, uint16_t pipe);
void usb_cstd_DoSqtgl(USB_UTR_t *ptr, uint16_t pipe, uint16_t toggle);
void usb_cstd_SelectNak(USB_UTR_t *ptr, uint16_t pipe);
uint16_t usb_cstd_Pipe2Fport(USB_UTR_t *ptr, uint16_t pipe);
void usb_cstd_Buf2Fifo(USB_UTR_t *ptr, uint16_t pipe, uint16_t useport);
void usb_cstd_SetBuf(USB_UTR_t *ptr, uint16_t pipe);
uint16_t usb_cstd_GetBufSize(USB_UTR_t *ptr, uint16_t pipe);
void usb_cstd_Buf2fifoStartDma( USB_UTR_t *ptr, uint16_t pipe, uint16_t useport );
void usb_cpu_buf2d0fifo_start_dma(USB_UTR_t *ptr, uint32_t DistAdr);
uint32_t usb_cstd_GetD0fifo16Adr( USB_UTR_t *ptr );
void usb_cstd_NrdyEnable(USB_UTR_t *ptr, uint16_t pipe);
void usb_cstd_Buf2D0fifoStartUsb(USB_UTR_t *ptr);
uint16_t usb_cstd_is_host_mode(USB_UTR_t *ptr);
void usb_creg_set_nrdyenb( USB_UTR_t *ptr, uint16_t pipeno );
uint16_t usb_creg_read_syscfg( USB_UTR_t *ptr, uint16_t port );
uint16_t usb_creg_read_dcpmaxp( USB_UTR_t *ptr );
uint16_t usb_creg_read_pipemaxp( USB_UTR_t *ptr );
uint16_t usb_creg_read_dcpcfg( USB_UTR_t *ptr );
uint16_t usb_creg_read_pipebuf( USB_UTR_t *ptr );
void usb_creg_set_pid( USB_UTR_t *ptr, uint16_t pipeno, uint16_t data );
uint16_t usb_cstd_write_data(USB_UTR_t *ptr, uint16_t pipe, uint16_t pipemode );
void usb_creg_set_brdyenb( USB_UTR_t *ptr, uint16_t  pipeno );
uint16_t usb_cstd_is_set_frdy(USB_UTR_t *ptr, uint16_t pipe, uint16_t fifosel, uint16_t isel);
uint16_t usb_cstd_GetMaxPacketSize(USB_UTR_t *ptr, uint16_t pipe);
uint8_t *usb_cstd_write_fifo( USB_UTR_t *ptr, uint16_t count, uint16_t pipemode, uint8_t *write_p );
void usb_creg_write_fifo16( USB_UTR_t *ptr, uint16_t pipemode, uint16_t data );
void usb_creg_set_sqset( USB_UTR_t *ptr, uint16_t pipeno );
void usb_cstd_Fifo2BufStartDma( USB_UTR_t *ptr, uint16_t pipe, uint16_t useport, uint32_t length );
void usb_cpu_d0fifo2buf_start_dma(USB_UTR_t *ptr, uint32_t SourceAddr);
void usb_cstd_D0fifo2BufStartUsb(USB_UTR_t *ptr);
void usb_creg_set_dclrm( USB_UTR_t *ptr, uint16_t pipemode );
void usb_pstd_BrdyPipe(USB_UTR_t *ptr, uint16_t bitsts);
void usb_pstd_BempPipe(USB_UTR_t *ptr, uint16_t bitsts);
void usb_pstd_NrdyPipe(USB_UTR_t *ptr, uint16_t bitsts);
void usb_pstd_ResumeProcess(USB_UTR_t *ptr);
void usb_creg_set_cnen( USB_UTR_t *ptr );
uint16_t usb_pstd_ChkVbsts(USB_UTR_t *ptr);
void usb_pstd_BusresetFunction(USB_UTR_t *ptr);
void usb_pstd_BusReset(USB_UTR_t *ptr);
void usb_pstd_SuspendProcess(USB_UTR_t *ptr);
void usb_pstd_SaveRequest(USB_UTR_t *ptr);
void usb_pstd_StandReq5(USB_UTR_t *ptr);
void usb_pstd_StandReq4(USB_UTR_t *ptr);
void usb_pstd_StandReq3(USB_UTR_t *ptr);
void usb_pstd_StandReq2(USB_UTR_t *ptr);
void usb_pstd_StandReq1(USB_UTR_t *ptr);
void usb_pstd_StandReq0(USB_UTR_t *ptr);
void R_usb_pstd_ControlEnd(USB_UTR_t *ptr, uint16_t status);
void usb_pstd_ControlEnd(USB_UTR_t *ptr, uint16_t status);
void usb_pstd_SetStallPipe0(USB_UTR_t *ptr);
void usb_preg_set_ccpl( USB_UTR_t *ptr );
void usb_pstd_ClearFeature0(void);
void usb_pstd_SetFeature0(void);
void usb_pstd_SetAddress0(void);
void usb_pstd_SetConfiguration0(USB_UTR_t *ptr);
void usb_pstd_SetInterface0(USB_UTR_t *ptr);
void usb_pstd_SetConfigNum(uint16_t value);
void usb_pstd_ClearAlt(void);
void usb_pstd_GetStatus1(USB_UTR_t *ptr);
void usb_pstd_GetDescriptor1(USB_UTR_t *ptr);
void usb_pstd_GetConfiguration1(USB_UTR_t *ptr);
void usb_pstd_GetInterface1(USB_UTR_t *ptr);
void usb_pstd_SynchFrame1(USB_UTR_t *ptr);
uint16_t usb_pstd_ControlRead(USB_UTR_t *ptr, uint32_t bsize, uint8_t *table);
uint16_t usb_cstd_HiSpeedEnable(USB_UTR_t *ptr, uint16_t port);
uint8_t usb_pstd_GetCurrentPower(void);
uint16_t usb_creg_read_dcpctr( USB_UTR_t *ptr );
uint16_t usb_cstd_Epadr2Pipe(USB_UTR_t *ptr, uint16_t dir_ep);
uint16_t usb_cstd_GetPid(USB_UTR_t *ptr, uint16_t pipe);
void usb_pstd_SetDescriptor2(USB_UTR_t *ptr);
void usb_pstd_SetInterface3(USB_UTR_t *ptr);
void usb_pstd_SetConfiguration3(USB_UTR_t *ptr);
void usb_pstd_SetAddress3(USB_UTR_t *ptr);
void usb_pstd_SetFeature3(USB_UTR_t *ptr);
void usb_pstd_ClearFeature3(USB_UTR_t *ptr);
uint16_t usb_pstd_ChkRemote(void);
void usb_pstd_SetFeatureFunction(USB_UTR_t *ptr);
uint16_t usb_pstd_GetConfigNum(void);
void usb_pstd_ClearEpTblIndex(void);
void usb_pstd_SetEpTblIndex(uint16_t con_num, uint16_t int_num, uint16_t alt_num);
void usb_pstd_SetPipeRegister(USB_UTR_t *ptr, uint16_t pipe_number, uint16_t *tbl);
void usb_cstd_pipe_init(USB_UTR_t *ptr, uint16_t pipe, uint16_t *tbl, uint16_t ofs);
uint16_t usb_pstd_GetAlternateNum(uint16_t con_num, uint16_t int_num);
uint16_t usb_creg_read_usbreq( USB_UTR_t *ptr );
uint16_t usb_creg_read_usbval( USB_UTR_t *ptr );
uint16_t usb_creg_read_usbindx( USB_UTR_t *ptr );
uint16_t usb_creg_read_usbleng( USB_UTR_t *ptr );
uint16_t usb_creg_read_syssts( USB_UTR_t *ptr, uint16_t port );
void usb_preg_set_enb_rsme( USB_UTR_t *ptr );
void usb_pstd_SuspendFunction(USB_UTR_t *ptr);
void usb_pstd_ClearMem(void);
void usb_creg_write_dcpcfg( USB_UTR_t *ptr, uint16_t data );
void usb_creg_write_dcpmxps( USB_UTR_t *ptr, uint16_t data );
void usb_cstd_NrdyPipe(USB_UTR_t *ptr, uint16_t bitsts);
uint16_t usb_creg_read_frmnum( USB_UTR_t *ptr );
void usb_cstd_nrdy_endprocess( USB_UTR_t *ptr, uint16_t pipe );
void usb_cstd_BempPipe(USB_UTR_t *ptr, uint16_t bitsts);
void usb_cstd_DataEnd(USB_UTR_t *ptr, uint16_t pipe, uint16_t status);
uint16_t usb_cstd_read_data(USB_UTR_t *ptr, uint16_t pipe, uint16_t pipemode);
void usb_cstd_BrdyPipe(USB_UTR_t *ptr, uint16_t bitsts);
void usb_cstd_brdy_pipe(USB_UTR_t *ptr, uint16_t bitsts);
void usb_cstd_Fifo2Buf(USB_UTR_t *ptr, uint16_t pipe, uint16_t useport);
uint16_t usb_cpu_get_dtc_block_count(USB_UTR_t *ptr);
uint8_t *usb_cstd_read_fifo( USB_UTR_t *ptr, uint16_t count, uint16_t pipemode, uint8_t *read_p );
uint16_t usb_creg_read_fifo16( USB_UTR_t *ptr, uint16_t pipemode );
uint16_t cdc_event_get( void );
void cdc_event_set( uint16_t event );
USB_ER_t R_usb_pstd_TransferEnd(USB_UTR_t *ptr, uint16_t pipe, uint16_t status);
USB_ER_t usb_pstd_PcdSndMbx(USB_UTR_t *ptr, uint16_t msginfo, uint16_t keyword, USB_CB_t complete);
USB_ER_t usb_cstd_PgetBlk( uint8_t id, USB_UTR_t** blk );
void cdc_read_complete(USB_UTR_t *mess, uint16_t data1, uint16_t data2);
void R_usb_pcdc_ReceiveData(USB_UTR_t *ptr, uint8_t *Table, uint32_t size, USB_CB_t complete);
void R_usb_pcdc_SendData(USB_UTR_t *ptr, uint8_t *Table, uint32_t size, USB_CB_t complete);
void cdc_write_complete(USB_UTR_t *mess, uint16_t data1, uint16_t data2);
USB_ER_t R_usb_cstd_PgetBlk( uint8_t id, USB_UTR_t** blk );
dtc_err_t R_DTC_Open(void);
static bool r_dtc_acquire_hw_lock(void);
static void r_dtc_clear_all_dtce_bits(void);
void r_dtc_module_enable(void);
bool R_BSP_HardwareLock (mcu_lock_t const hw_index);
bool R_BSP_SoftwareLock (BSP_CFG_USER_LOCKING_TYPE * const plock);
USB_REGADR_t R_usb_cstd_GetUsbIpAdr( uint16_t ipno );
void R_usb_pstd_usbdriver_start( USB_UTR_t *ptr );
void cdc_registration( void );
usb_err_t R_USB_Open( usb_ip_t ip_type );
void R_usb_cstd_UsbIpInit( USB_UTR_t *ptr, uint16_t usb_mode );
void R_usb_pcdc_driver_start( void );
void R_usb_cstd_SetTaskPri(uint8_t tasknum, uint8_t pri);
void usb_cstd_AsspConfig(USB_UTR_t *ptr);
void usb_cstd_WaitUsbip(USB_UTR_t *ptr);
void usb_cstd_InitialClock(USB_UTR_t *ptr);
void R_usb_cstd_ClearHwFunction(USB_UTR_t *ptr);
void usb_cstd_Pinconfig(USB_UTR_t *ptr);
void usb_cstd_set_usbip_mode_sub(USB_UTR_t *ptr, uint16_t function);
void usb_cstd_set_usbip_mode(USB_UTR_t *ptr, uint16_t function);
void usb_cstd_InitUsbMessage(USB_UTR_t *ptr, uint16_t function);
void usb_cstd_set_sofcfg_intl( USB_UTR_t *ptr );
void usb_creg_set_sofcfg( USB_UTR_t *ptr, uint16_t data );
void usb_creg_clr_drpd( USB_UTR_t *ptr, uint16_t port );
void usb_preg_write_physlew( USB_UTR_t *ptr );
void usb_cstd_BerneEnable(USB_UTR_t *ptr);
void usb_pstd_InitConnect(USB_UTR_t *ptr);
void usb_cstd_SetHse(USB_UTR_t *ptr, uint16_t port, uint16_t speed);
uint16_t usb_pstd_InitFunction(USB_UTR_t *ptr);
void usb_creg_clr_hse( USB_UTR_t *ptr, uint16_t port );
void usb_creg_set_hse( USB_UTR_t *ptr, uint16_t port );
void usb_creg_write_fifosel( USB_UTR_t *ptr, uint16_t pipemode, uint16_t data );
void usb_creg_set_bigend( USB_UTR_t *ptr, uint16_t pipemode, uint16_t data );
void usb_creg_set_bus_wait( USB_UTR_t *ptr );
void usb_cstd_ClearIntEnb( USB_UTR_t *ptr );
void usb_creg_write_brdyenb( USB_UTR_t *ptr, uint16_t data );
void usb_creg_write_nrdyenb( USB_UTR_t *ptr, uint16_t data );
void usb_creg_write_bempenb( USB_UTR_t *ptr, uint16_t data );
void usb_cstd_ClearIntSts( USB_UTR_t *ptr );
void usb_creg_write_brdysts( USB_UTR_t *ptr, uint16_t data );
void usb_creg_write_nrdysts( USB_UTR_t *ptr, uint16_t data );
uint16_t usb_creg_read_bempsts( USB_UTR_t *ptr );
void usb_creg_write_bempsts( USB_UTR_t *ptr, uint16_t data );
void usb_cstd_ClearDline( USB_UTR_t *ptr );
void usb_cstd_SwReset(USB_UTR_t *ptr);
void usb_creg_set_usbe( USB_UTR_t *ptr );
void usb_creg_clr_usbe( USB_UTR_t *ptr );
void usb_creg_write_intsts( USB_UTR_t *ptr, uint16_t data );
void usb_creg_write_intenb( USB_UTR_t *ptr, uint16_t data );
void usb_creg_set_scke( USB_UTR_t *ptr );
usb_err_t usb_cpu_module_start( usb_ip_t ip_type );
USB_REGADR_t usb_cstd_GetUsbIpAdr( uint16_t ipnum );
USB_ER_t R_usb_pstd_PcdOpen(USB_UTR_t *ptr);
void R_usb_pstd_DriverRegistration(USB_UTR_t *ptr, USB_PCDREG_t *registinfo);
void cdc_configured(USB_UTR_t *ptr, uint16_t data1, uint16_t data2);
void cdc_detach(USB_UTR_t *ptr, uint16_t data1, uint16_t data2);
void cdc_suspend(USB_UTR_t *ptr, uint16_t data1, uint16_t data2);
void R_usb_pcdc_set_interface(USB_UTR_t *ptr, uint16_t data1, uint16_t data2);
void R_usb_pcdc_usr_ctrl_trans_function(USB_UTR_t *ptr, USB_REQUEST_t *preq, uint16_t ctsq);
void usb_pcdc_ControlTrans5(USB_UTR_t *ptr, USB_REQUEST_t *req);
void usb_pcdc_ControlTrans2(USB_UTR_t *ptr, USB_REQUEST_t *req);
void usb_pcdc_ControlTrans0(USB_UTR_t *ptr, USB_REQUEST_t *req);
void usb_pcdc_ControlTrans3(USB_UTR_t *ptr, USB_REQUEST_t *req);
void usb_pcdc_ControlTrans4(USB_UTR_t *ptr, USB_REQUEST_t *req);
void usb_pcdc_ControlTrans1(USB_UTR_t *ptr, USB_REQUEST_t *req);
uint16_t R_usb_pstd_ControlRead(USB_UTR_t *ptr, uint32_t bsize, uint8_t *table);
void usb_pcdc_GetLineCoding_req(USB_UTR_t *ptr);
void usb_pcdc_GetLineCoding(USB_UTR_t *ptr, USB_CB_t complete);
void usb_pcdc_SetControlLineState_req(USB_UTR_t *ptr);
void usb_pcdc_SetControlLineState(USB_UTR_t *ptr, USB_CB_t complete);
void R_usb_pstd_ControlWrite(USB_UTR_t *ptr, uint32_t bsize, uint8_t *table);
void usb_pcdc_SetLineCoding_req(USB_UTR_t *ptr);
void usb_pcdc_SetLineCoding(USB_UTR_t *ptr, USB_CB_t complete);
void usb_creg_set_curpipe( USB_UTR_t *ptr, uint16_t  pipemode, uint16_t  pipeno );


