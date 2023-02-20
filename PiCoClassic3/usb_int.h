
typedef void (*USB_CB_t)(struct USB_UTR *, uint16_t, uint16_t);
typedef void*           VP;             
typedef long            ER;             
typedef VP              USB_MH_t;       
    typedef struct
    {
        VP              msghead;        
    } T_MSG;
typedef volatile struct st_usb0 __evenaccess*   USB_REGADR_t;
typedef ER              USB_ER_t;       
typedef T_MSG           USB_MSG_t;      

typedef struct USB_UTR
{
    USB_MH_t        msghead;        
    uint16_t        msginfo;        
	uint16_t        keyword;        
    USB_REGADR_t    ipp;            
    uint16_t        ip;             
    uint16_t        result;         
    USB_CB_t        complete;       
    void            *tranadr;       
    uint32_t        tranlen;        
    uint16_t        *setup;         
    uint16_t        status;         
    uint16_t        pipectr;        
    uint8_t         errcnt;         
    uint8_t         segment;        
    int16_t         fn;             
    void            *usr_data;      
} USB_UTR_t;

extern USB_ER_t usb_cstd_iSndMsg( uint8_t id, USB_MSG_t* mess );

#define USB_ISND_MSG(ID, MESS)      usb_cstd_iSndMsg( (uint8_t)ID, (USB_MSG_t*)MESS )

extern USB_UTR_t       usb_gcstd_IntMsg[USB_NUM_USBIP][USB_INTMSGMAX]; 
extern uint16_t        usb_gcstd_IntMsgCnt[USB_NUM_USBIP];             
extern USB_UTR_t       usb_gcstd_IntMsgD0fifo;

extern USB_REGADR_t    usb_cstd_GetUsbIpAdr( uint16_t ipnum );
extern void usb_cstd_InterruptClock(USB_UTR_t *ptr);
extern uint16_t usb_cstd_is_host_mode(USB_UTR_t *ptr);
extern void usb_pstd_InterruptHandler(USB_UTR_t *ptr);
extern void    usb_creg_clr_dreqe( USB_UTR_t *ptr, uint16_t pipemode );
extern void usb_cpu_d0fifo_stop_dma(USB_UTR_t *ptr);
