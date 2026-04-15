#ifndef Standards_H
#define Standards_H

#include <windows.h>

// Satellite Identifier
typedef unsigned short TSatellite;

// Status code return
typedef unsigned long TStatus;

// Success boolean return
typedef bool TSuccess;

// Site Identifier
typedef unsigned short TSite;

// System States Mask
#define M_QENABLE    0x00000001  // Control for all
#define M_QCOLLECT   0x00000002  // Control for SARCollector
#define M_QPROCESS   0x00000004  // Control for SARWideband
#define M_QTRACK     0x00000008  // Control for SARAntenna
#define M_QREAD      0x00000010  // Control for SAREnvironment
#define M_QSEND      0x00000020  // Control for SARComms
#define M_QFILTER    0x00000040  // Control for SARFilter
#define M_QGUARD     0x00000080  // Control for SARGuard
#define M_QCLOCK     0x00000100  // Control for SARClock
#define M_QCHASM     0x00000200  // Control for SARChasm
#define M_QRESERVE6  0x00000400  // Control for RESERVED: PAIRED TO M_RESERVED6
#define M_QRESERVE5  0x00000800  // Control for RESERVED: PAIRED TO M_RESERVED5
#define M_QRESERVE4  0x00001000  // Control for RESERVED: PAIRED TO M_RESERVED4
#define M_QRESERVE3  0x00002000  // Control for RESERVED: PAIRED TO M_RESERVED3
#define M_QRESERVE2  0x00004000  // Control for RESERVED: PAIRED TO M_RESERVED2
#define M_QRESERVE1  0x00008000  // Control for RESERVED: PAIRED TO M_RESERVED1

#define M_ENABLED    0x00010000  // Response from all (handled by SARMaster only)
#define M_COLLECTING 0x00020000  // Response from SARCollector
#define M_PROCESSING 0x00040000  // Response from SARWideband
#define M_TRACKING   0x00080000  // Response from SARAntenna
#define M_READING    0x00100000  // Response from SAREnvironment
#define M_SENDING    0x00200000  // Response from SARComms
#define M_FILTERING  0x00300000  // Response from SARFilter
#define M_GUARDING   0x00400000  // Response from SARGuard
#define M_CLOCK      0x01000000  // Response from SARClock
#define M_CHASM      0x02000000  // Response from SARChasm
#define M_RESERVED6  0x04000000  // Response from RESERVED: PAIRED TO M_QRESERVE6
#define M_RESERVED5  0x08000000  // Response from RESERVED: PAIRED TO M_QRESERVE5
#define M_RESERVED4  0x10000000  // Response from RESERVED: PAIRED TO M_QRESERVE4
#define M_RESERVED3  0x20000000  // Response from RESERVED: PAIRED TO M_QRESERVE3
#define M_RESERVED2  0x40000000  // Response from RESERVED: PAIRED TO M_QRESERVE2
#define M_RESERVED1  0x80000000  // Response from RESERVED: PAIRED TO M_QRESERVE1

// Hard-wired device status LED codes used by the DeviceStatus field
#define COLOUR_BLACK      0
#define COLOUR_GREEN      1
#define COLOUR_AMBER      2
#define COLOUR_RED        3

// Hard-wired device indexes used by server device handling tasks
#define DEVICE_ANTENNA    0
#define DEVICE_COLLECTOR  1
#define DEVICE_CLOCK      2
#define DEVICE_COMPUTER   3
#define DEVICE_WIDEBAND   4
#define DEVICE_RESERVED5  5
#define DEVICE_RESERVED6  6
#define DEVICE_RESERVED7  7

// Hard-wired data indexes used by server device handling tasks
#define DATA_BPP406       0      // Leo / Geo
#define DATA_INT406       1      //       Geo
#define DATA_CBC121       2      // Leo
#define DATA_CBC243       3      // Leo
#define DATA_CBC406       4      // Leo / Geo
#define DATA_SWP121       5      // Leo
#define DATA_SWP243       6      // Leo
#define DATA_PDS          7      // Leo
#define DATA_SPECTRUM     8      // Leo / Geo
#define DATA_AUDIO        9      // Leo / Geo
#define DATA_RESERVED10  10      // Leo
#define DATA_RESERVED11  11      // Leo
#define DATA_RESERVED12  12      // Leo
#define DATA_RESERVED13  13      // Leo
#define DATA_RESERVED14  14      // Leo
#define DATA_RESERVED15  15      // Leo

// Simplifed bit access for above bit masks
#define BITSET(v,b) (v|=b)               // Set bit b in value v
#define BITCLR(v,b) (v&=~b)              // Clear bit b in value v
#define BITCHG(v,b) (v&b?(v&=~b):(v|=b)) // Toggle bit b in value v
#define BITCHK(v,b) (v&b?1:0)            // Boolean check of bit b in value v

// System States Types
typedef enum
{
   SSQEnable       = M_QENABLE,
   SSQCollect      = M_QCOLLECT,
   SSQProcess      = M_QPROCESS,
   SSQTrack        = M_QTRACK,
   SSQRead         = M_QREAD,
   SSQSend         = M_QSEND,
   SSQFilter       = M_QFILTER,
   SSQGuard        = M_QGUARD,
   SSQClock        = M_QCLOCK,
   SSQChasm        = M_QCHASM,
   SSQReserve6     = M_QRESERVE6,
   SSQReserve5     = M_QRESERVE5,
   SSQReserve4     = M_QRESERVE4,
   SSQReserve3     = M_QRESERVE3,
   SSQReserve2     = M_QRESERVE2,
   SSQReserve1     = M_QRESERVE1,

   SSEnabled       = M_ENABLED,
   SSCollecting    = M_COLLECTING,
   SSProcessing    = M_PROCESSING,
   SSTracking      = M_TRACKING,
   SSReading       = M_READING,
   SSSending       = M_SENDING,
   SSFilter        = M_FILTERING,
   SSGuard         = M_GUARDING,
   SSClock         = M_CLOCK,
   SSChasm         = M_CHASM,
   SSReserved6     = M_RESERVED6,
   SSReserved5     = M_RESERVED5,
   SSReserved4     = M_RESERVED4,
   SSReserved3     = M_RESERVED3,
   SSReserved2     = M_RESERVED2,
   SSReserved1     = M_RESERVED1,
} TSystemState;

#endif
