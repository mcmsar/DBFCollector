#if !defined(U8)
	typedef unsigned char  U8;
#endif

#if !defined(U16)
	typedef unsigned short U16;
#endif

#if !defined(U32)
    typedef unsigned long           U32, *PU32;
#endif

#if !defined(ULONGLONG)
    typedef unsigned _int64         ULONGLONG;
#endif

#if !defined(U64)
	typedef unsigned _int64         U64;
#endif
 


// Barry's Windows Programming Tools
void CursorVisible(BOOL CVState);
void PositionCursor(U16 X, U16 Y);
void ClrScr(void);
void kbflush(void);
char wait_for_key(void);
char prompt_for_key(char *message);
char anykey(void);
void print_time(void);
void save_cursor(void);
void restore_cursor(void);
void Busy_Signal(int speed);
BOOL VersionDetect(void);
void SetColors(U16 ConsoleColor);
char dsp_time_scan_for_key(void);
void print_passed(void);
void print_failed(void);
void ShowAPIError(U32 APIReturnCode);

/******************************************
*             Definitions
******************************************/
#define PLX_STATUS_START               0x200   // Starting status code


// API Return Code Values
// typedef enum _PLX_STATUS
// {
    // ApiSuccess = PLX_STATUS_START,	// 512
    // ApiFailed,
    // ApiNullParam,
    // ApiUnsupportedFunction,
    // ApiNoActiveDriver,
    // ApiConfigAccessFailed,
    // ApiInvalidDeviceInfo,
    // ApiInvalidDriverVersion,
    // ApiInvalidOffset,				// 520
    // ApiInvalidData,
    // ApiInvalidSize,
    // ApiInvalidAddress,
    // ApiInvalidAccessType,
    // ApiInvalidIndex,
    // ApiInvalidPowerState,
    // ApiInvalidIopSpace,
    // ApiInvalidHandle,
    // ApiInvalidPciSpace,
    // ApiInvalidBusIndex,				// 530
    // ApiInsufficientResources,
    // ApiWaitTimeout,
    // ApiWaitCanceled,
    // ApiDmaChannelUnavailable,
    // ApiDmaChannelInvalid,
    // ApiDmaDone,
    // ApiDmaPaused,
    // ApiDmaInProgress,
    // ApiDmaCommandInvalid,
    // ApiDmaInvalidChannelPriority,	// 540
    // ApiDmaSglPagesGetError,
    // ApiDmaSglPagesLockError,
    // ApiMuFifoEmpty,
    // ApiMuFifoFull,
    // ApiPowerDown,
    // ApiHSNotSupported,
    // ApiVPDNotSupported,
    // ApiDeviceInUse,
    // ApiDmaNotReady,
	// ApiInvalidBoardNumber,			// 550
	// ApiInvalidDMANumWords,
    // ApiLastError               // Do not add API errors below this line
// } PLX_STATUS;

