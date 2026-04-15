#ifndef INC_MEMTYPES
#define INC_MEMTYPES

// Required headers
#include <time.h>

#include "emstypes.h"
#include "Standards.h"
#include "sigproc.h"

// Data collection headers

#include "Collector_Data_Types.h"

// Memory buffer names
#define MEM_DAQ      "$CMM_0.SAR_DAQ"
#define MEM_WBP      "$CMM_1.SAR_WBP"
#define MEM_DAT0     "$CMM_2.SAR_DAT0"
#define MEM_DAT1     "$CMM_3.SAR_DAT0"
#define MEM_MASTER   "$CMM_4.SAR_STATS"

// Data Collector structures
typedef EMSCOMPLEX TCollectorFft[MAX_FFTS][PSD_SIZE];   // Raw fft buffer
typedef float TCollectorPower[MAX_FFTS][PSD_SIZE]; // Raw cbc power spectrum buffer
typedef float TCollectorPsd[PSD_SIZE];             // Integrated power spectrum buffer

// Wideband Processor structures
typedef EMSCOMPLEX TWidebandFft[MAX_FFTS+MAX_FFTS/2][PSD_SIZE/2];

// Data Collector Common Memory Block
typedef struct
{
   TRawDMA           Dma;
   TRawInphase       DdcI;
   TRawQuadrature    DdcQ;
   TRawPhase         Phase;
   TDemodulatedPhase Pll;
} TCollectorMemory;

//*************
//*************
//*************
//*************

// Declarations of constants and macros
#define MAXMSG                  10      // Maximum of raw and integrated 406 messages
//#define MAXDET			 5     	// Maximum number of 406 beacon detections
#define MAX_BIT_WORDS	        18
//#define NUM_SHORT_MSG_BITS      (112L)  // Number of bits in 406 short messages
//#define NUM_LONG_MSG_BITS       (144L)  // Number of bits in 406 long messages
#define MSG_FORMAT_BIT          (25L)   // Format bit location in 406 messages
#define MSG_SHORT               0       // Short message indication for 406 messages
#define MSG_LONG                1       // Long message indication for 406 messages

// Message integration controls

#define MAX_NUM_GROUPS          450
#define MAX_MSGS_PER_GROUP      10
#define MAX_INTEGRATIONS        32750
#define MAX_NUM_BEACONS         15

// Data Collection Memory Export Structure
typedef struct
{
	WORD					wFFTCount;					// number of valid FFT bins ( 0.. )
	float					fFFTBinSize;				//	freq bandwidth of FFT bin ( Hz )
   TCollectorFft   Fft;                       // Raw fft buffer
   TCollectorPower Power;                     // Raw cbc power spectrum buffer
   TCollectorPsd   Psd;                       // Integrated power spectrum buffer
   unsigned long   Data_Identifier;           // Sequential identifer of current buffer
   unsigned long   Data_Timeouts;             // Number of detected data timeouts
   unsigned long   Data_Dropouts;             // Number of detected FIFO overflows
	EMSTIME			timeStart;                // Collection start time
	EMSTIME   		timeBuffer;               // End of buffer in seconds since GMT 01/JAN/1970
   float           AGC_RMS;                   // RMS of A/D samples
   float           AGC_Mean;                  // Mean value of A/D samples
   float           Carrier_Frequency;         // Carrier frequency (Hz)
   float           Mod_Index;                 // Maximum modulation index (radians)
   float           Mod_Index_Mean;            // Mean value of modulation index (radians)
   float           Mod_Index_RMS;             // RMS of modulation index (radians)
   unsigned long   Marker_Bit_Rate;           // Number of samples between marker bits
   unsigned short  Mod_Index_Block;           // Block number with maximum mod index
} TDataExport;

#endif // INC_MEMTYPES
