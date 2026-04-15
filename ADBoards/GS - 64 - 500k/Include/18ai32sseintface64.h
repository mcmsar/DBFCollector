/******************************************************************************
 *
 * File Name:
 *
 *     18AI32SSeintface.h
 *
 * Description:
 *
 *     This file contains all the 18AI32SS Driver function prototypes.
 *
 * Revision:
 *
 *     06-25-09 : 18AI32SS eDriver C 1.0
 *
 ******************************************************************************/

#ifdef  __cplusplus
extern "C" {
#endif


//==============================================================================
// Board Register Addresses
//==============================================================================
#define       BCR                0x00
#define       ICR                0x04
#define       IN_DATA_BUFF       0x08
#define       IN_DATA_CNTRL      0x0C
#define       RATE_A             0x10
#define       RATE_B             0x14
#define       BUFF_SIZE		     0x18
#define       BURST_SIZE	     0x1C
#define       SCAN_CNTRL         0x20
#define       ACTIVE_CHAN        0x24
#define       FW_REV             0x28
#define       AUTOCAL            0x2C
#define		  UVAL				 0x30
#define		  AUX SYNC			 0x34
#define		  SCAN_MARKER_U		 0x38
#define		  SCAN_MARKER_L		 0x3C
#define		  TEST_UTIL			 0x40
//#define		  PRETRIG_CNT_LO	 0x44
//#define		  PRETRIG_CNT_HI	 0x48

#define       LOCAL              0
#define       DMA			     1
#define		  MINUS_ONE_LONG     0xFFFFFFFFL

typedef struct _GS_NOTIFY_OBJECT
{
    U32 IsValidTag;                  // Magic number to determine validity
    U64 pWaitObject;                 // -- INTERNAL -- Wait object used by the driver
    U64 hEvent;                      // User event handle (HANDLE can be 32 or 64 bit)
} GS_NOTIFY_OBJECT;

typedef struct _GS_PHYSICAL_MEM
{
    U64 UserAddr;                    // User-mode virtual address
    U64 PhysicalAddr;                // Bus physical address
    U64 CpuPhysical;                 // CPU physical address
    U32 Size;                        // Size of the buffer
} GS_PHYSICAL_MEM;

typedef struct _GS_DMA_DESCRIPTOR
{
	U32 BytesDesc_1;				 // BYTES to transfer (U32 = 4 Bytes)
	U32 BytesDesc_2;				 // Max transfer size is 23 bits
	U32 BytesDesc_3;				 // such that max U32 transfer size
	U32 BytesDesc_4;				 // is (2097151) 0x1FFFFF
	U64 PhyAddrDesc_1;				 // Valid PHYSICAL address for contiguous
	U64 PhyAddrDesc_2;				 // memory block
	U64 PhyAddrDesc_3;				 // DO NOT use an address obtained from
	U64 PhyAddrDesc_4;				 // malloc() or similiar functions
	U32 NumDescriptors	 : 4;		 // Number of Descriptor blocks to use
	U8  LocalToPciDesc_1 : 1;		 // NOTE: Valid info MUST be provided for
	U8  LocalToPciDesc_2 : 1;		 // the # of Descriptor blocks specified
	U8  LocalToPciDesc_3 : 1;
	U8  LocalToPciDesc_4 : 1;		 // Direction of Transfer : 1 = Local->Pci
	U8  InterruptDesc_1  : 1;		 // Enable interrupt at Descriptor completion
	U8  InterruptDesc_2  : 1;
    U8  InterruptDesc_3  : 1;
	U8  InterruptDesc_4  : 1;
    U8  DmaChannel       : 1;        // DMA Channel 0 or 1
	U64 Reserved;
} GS_DMA_DESCRIPTOR;

//Function ProtoTypes

//==============================================================================
//	Find ALL Devices
//  Sets Board #: Bus: Slot: Type: Ser#  in pDeviceInfo for PLX boards found
//  Returns # Boards found
//==============================================================================
U32 __cdecl GS66_18AI32SS_FindBoards(char *pDeviceInfo, U32 *ulError);

//==============================================================================
//
//  Initializes Handle for the passed board number IN THE DRIVER
//  
//==============================================================================
U32 __cdecl GS66_18AI32SS_Get_Handle(U32 *ulError, U32 BoardNumber);

//==============================================================================
//
//  Closes Handle for the passed board number IN THE DRIVER
//  
//==============================================================================
void __cdecl GS66_18AI32SS_Close_Handle(U32 BoardNumber, U32 *ulError);

//==============================================================================
//	Read Local Register Data from the Device (32Bit)
//
//  See Users Manual for register bit definitions
//
//  Returns register value 
//==============================================================================
U32 __cdecl GS66_18AI32SS_Read_Local32(U32 BoardNumber, U32 *ulError, U32 ulRegister);

//==============================================================================
//	Write Local Register Data to the Device (32Bit)
//
//  See Users Manual for register bit definitions
//
//==============================================================================
void __cdecl GS66_18AI32SS_Write_Local32(U32 BoardNumber, U32 *ulError, U32 ulRegister, U32 ulValue);

//==============================================================================
//
//	Initializes the board, i.e. reset
//
//==============================================================================
void __cdecl GS66_18AI32SS_Initialize(U32 BoardNumber, U32 *ulErrorIn);

//==============================================================================
//
//	Initiates Auto Calibration 
//
//==============================================================================
U32 __cdecl GS66_18AI32SS_Autocal(U32 BoardNumber, U32 *ulErrorIn);

//==============================================================================
//
//	Sets Background Calibration Mode: ON=1, OFF=0
//
//==============================================================================
void __cdecl GS66_18AI32SS_Set_Background_Cal(U32 BoardNumber, U32 *ulError, U32 ulMode);


//==============================================================================
//
//	Sets Input Mode: System, Zero or +VREF Selftest
//
//  NOTE: Check Users Manual for valid modes - Board Type Dependent
//
//==============================================================================
void __cdecl GS66_18AI32SS_Set_Input_Mode(U32 BoardNumber, U32 *ulErrorIn, U32 ulInputMode);


//==============================================================================
//
//	Clears the Analog Input buffer
//
//==============================================================================
void __cdecl GS66_18AI32SS_Clear_Input_Buffer(U32 BoardNumber, U32 *ulErrorIn);

//==============================================================================
//
//	Enables the ADC Clock
//
//==============================================================================
void __cdecl GS66_18AI32SS_Enable_Clocking(U32 BoardNumber, U32 *ulError);

//==============================================================================
//
//	Disables the ADC Clock
//
//==============================================================================
void __cdecl GS66_18AI32SS_Disable_Clocking(U32 BoardNumber, U32 *ulError);

//==============================================================================
//	Enable Interrupts for the Device
//
//  ulType = 0 : Local Interrupts IRQ0 or IRQ1
//               ulValue - See Users Manual for value equates
//  ulType = 1 : DMA Interrupts DMA0 or DMA1
//               ulValue = 0 for DMA0 : 1 for DMA1 
//
//  Returns Interrupt value set for Local Interrupts, or ulValue for DMA
//==============================================================================
U32 __cdecl GS66_18AI32SS_EnableInterrupt(U32 BoardNumber, U32 ulValue, U32 ulType, U32 *ulError);

//==============================================================================
//	Disable Interrupts for the Device
//
//  ulType = 0 : Local Interrupts IRQ0 or IRQ1
//               ulValue - See Users Manual for value equates
//  ulType = 1 : DMA Interrupts DMA0 or DMA1
//               ulValue = 0 for DMA0 : 1 for DMA1 
//
//==============================================================================
void __cdecl GS66_18AI32SS_DisableInterrupt(U32 BoardNumber, U32 ulValue, U32 ulType, U32 *ulError);


//==============================================================================
//	Open DMA Channel for the Device
//
//==============================================================================
void __cdecl GS66_18AI32SS_Open_DMA_Channel(U32 ulBoardNumber, U32 ulChannel, U32 *ulError);

//==============================================================================
//	DMA Transfer from the Device
//
//  Returns # words transferred
//==============================================================================
U32 __cdecl GS66_18AI32SS_DMA_FROM_Buffer(U32 BoardNumber, U32 ulChannel, U32 ulWords, U32* uData,U32 *ulError);

//==============================================================================
//	Close DMA Channel for the Device
//
//==============================================================================

void __cdecl GS66_18AI32SS_Close_DMA_Channel(U32 BoardNumber, U32 ulChannel, U32 *ulError);

//==============================================================================
//	Setup CmdChaining DMA for the Device
//
//==============================================================================
U32 __cdecl GS66_18AI32SS_Setup_DmaCmdChaining(U32 BoardNumber, GS_DMA_DESCRIPTOR *DmaSetup, U32 *ulError);

//==============================================================================
//	Start CmdChaining DMA for the Device
//
//==============================================================================
U32 __cdecl GS66_18AI32SS_Start_DmaCmdChaining(U32 BoardNumber, U32 ulChannel, U32 *ulError);

//==============================================================================
//	Close CmdChaining DMA for the Device
//
//==============================================================================
void __cdecl GS66_18AI32SS_Close_DmaCmdChaining(U32 BoardNumber, U32 ulChannel, U32 *ulError);

//==============================================================================
//	Software Reset for the Device
//
//==============================================================================
void __cdecl GS66_18AI32SS_Reset_Device(U32 BoardNumber, U32 *ulError);

//==============================================================================
//	Get block of contiguous Physical Memory
//  and map to virtual memory
//==============================================================================
U32 __cdecl GS66_18AI32SS_Get_Physical_Memory(U32 BoardNumber, GS_PHYSICAL_MEM *memPtr, BOOLEAN bSmallerOk, U32 *ulError);

//==============================================================================
//	Umap & Free Physical Memory
//  
//==============================================================================
void __cdecl GS66_18AI32SS_Free_Physical_Memory(U32 BoardNumber, GS_PHYSICAL_MEM *memPtr, U32 *ulError);

//==============================================================================
//
//	Registers user event for interrupt notification
//  ulType = 0 : Local Interrupts IRQ0 or IRQ1
//               ulIntr - See Users Manual for value equates 
//  ulType = 1 : DMA Interrupts DMA0 or DMA1
//               ulIntr = 0 for DMA0 : 1 for DMA1 
//
//==============================================================================
void __cdecl GS66_18AI32SS_Register_Interrupt_Notify(U32 BoardNumber, GS_NOTIFY_OBJECT * event, U32 ulIntr, U32 ulType, U32 *ulError);

//==============================================================================
//	Cancels interrupt notification for specified event
//
//==============================================================================
void __cdecl GS66_18AI32SS_Cancel_Interrupt_Notify(U32 BoardNumber, GS_NOTIFY_OBJECT * event, U32 *ulError);

//==============================================================================
//	Sets the DMA Data mode - one(1) = Pack data, zero(0) = normal (default)
//  Packed data will be 2 channels per 32 bit lword (16 bits/channel), no tag,
//  Odd channel upper word, Even channel lower word 
//==============================================================================
void __cdecl GS66_18AI32SS_Dma_DataMode(U32 BoardNumber, U32 ulPack, U32 *ulError);






#ifdef  __cplusplus
}
#endif
