#ifndef INC_WideBand_Data_Types_H
#define INC_WideBand_Data_Types_H

// Required headers
#include "PDS_Data_Types.h"
//#include "TBeaconID.h"
//#include "TBeaconMsg.h"
//#include "TSARTime.h"
#include "emstime.h"

// NSP Library common header
#define nsp_UsesAll
#include "nsp.h"

// Data processing definitions
#define MAX_WBP_EVENTS 2

// Declarations of constants and macros
#define MAXMSG                  10      // Maximum of raw and integrated 406 messages
#define MAXDET			 5     	// Maximum number of 406 beacon detections
#define MAX_BIT_WORDS	        18
#define NUM_SHORT_MSG_BITS      (112L)  // Number of bits in 406 short messages
#define NUM_LONG_MSG_BITS       (144L)  // Number of bits in 406 long messages
#define MSG_FORMAT_BIT          (25L)   // Format bit location in 406 messages
#define MSG_SHORT               0       // Short message indication for 406 messages
#define MSG_LONG                1       // Long message indication for 406 messages
//#define MESSAGE_TYPE            100     // GSARP data message
//#define TEST_TYPE               777     // GSARP test message

#define PF1_PROTECTED_BITS      (106L)  // Bits in protected field
#define BEACON_REP_RATE         50      // Ordinary beacon repetition rate
#define ORB_REP_RATE            30      // Orbitography/Test beacon repetition rate

// Extra bits used required to locate possible test frame syncs
#define EXTRA_BITS              12

// Window width for frequency measurement interpolation
#define  WINDOW_WIDTH           3

// RT parameter file default values

#define MAX_406_DETECTS         5
#define NFLOOR0_DET		        16
#define NFLOOR1_DET		        16
#define THRESH_DET		        2.5
#define ON_DET			        0.7
#define OFF_DET			        0.3
#define FCOEFF_DET		        0.8
#define PROC_406_START		    20000.0 //5000.0
#define PROC_406_END		    30000.0 //100000.0
#define DETECT_TEST_MSG		    0
#define BAND_CENTRE_406         170000.0
#define BANDWIDTH_406           84000.0
#define FREQ_OFFSET_406         8000.0         // GEO: 0.0   LEO: 170000-42000=128000?

// Message integration controls

#define MAX_NUM_GROUPS          450
#define MAX_MSGS_PER_GROUP      10
#define MAX_INTEGRATIONS        32750
#define MAX_NUM_BEACONS         15

#define LIMIT_MAX_BIT_DIFF      106
#define LIMIT_FS_ERRORS         24
#define LIMIT_BCH_DETECT        3  // Detect 0,1,2,3 bit errors
#define LIMIT_BCH_CORRECT       3  // Correct up to 3 bit errors
#define LIMIT_BCH2_DETECT       2  // Detect 0,1,2 bit errors
#define LIMIT_BCH2_CORRECT      1  // Correct up to 1 bit error

#define DFT_MONITOR_FLAG        192
#define DFT_PROCESS_FLAG        63

#define DFT_INTEGRATION_RESTART false
#define DFT_DETECT_TEST_MSG     1
#define DFT_INTEGRATION_MODE    Full_Integration
#define DFT_GROUP_AGEOUT        10.0*60.0
#define DFT_FREQ_WINDOW         15.0
#define DFT_TIME_WINDOW         2.5
#define DFT_MAX_BIT_DIFF        28
#define DFT_FS_ERRORS           2
#define DFT_BCH_ERRORS          3
#define DFT_BCH2_ERRORS         2
#define DFT_NUM_INTEGRATIONS_FOR_PARTIAL_OUTPUT    6
#define DFT_TIME_FOR_PARTIAL_OUTPUT                8.5*60.0
#define DFT_MIN_POWER_LEVEL     20.0
#define DFT_MIN_CNO_LEVEL       0.0

// Data collection constants
#define MAX_FFTS                70
#define GeoSatMinId             200
#define SarSatMaxId             50
#define CBC_CALC_LIMIT          79

// Definitions of the inter-relationships of the constants used
// within the bpd software

#define  phase_samrat         (500000L)
#define  overlap_percent      (13L)

#define  zoomsz               (4096L)
//#define  nqfftmx              ((phase_samrat+not_overlap)/not_overlap)
#define  zfftsz               (128L)
#define  qfftsz               (8192L)

#define  f121c                (47000L)
#define  f243c                (94000L)

#define  f121w                (14000L)
#define  f243w                (27000L)
#define  max_f406w            (50000L)     // Uses Leo/Geo maximum

#define  msg_preamble         (0.160)      // sec
#define  nom_bit_rate         (400.0)      // bits/sec
#define  start_bit            (21L)

#define  bit_spec             (10.0)

#define  qfftsz2              (qfftsz/2)
#define  qfftsz4              (qfftsz/4)
#define  zfftsz2              (zfftsz/2)
#define  overlap              (((overlap_percent*zfftsz)/100)*(qfftsz/zfftsz))
#define  not_overlap          (qfftsz-overlap)
#define  z_overlap            ((overlap*zfftsz)/qfftsz)
#define  z_not_overlap        (zfftsz-z_overlap)
#define  nzfft                ((zoomsz+z_not_overlap-1)/z_not_overlap)
#define  qfftbinsz            ((1.0*phase_samrat)/qfftsz)
#define  zfftbinsz            (z_samrat/zoomsz)
#define  z_samrat             (phase_samrat*(zfftsz*1.0/qfftsz))
#define  kwin                 (zoomsz/4)
#define  kwin2                (zoomsz/8)
#define  f121s                ((f121c*qfftsz)/phase_samrat)
#define  f121n                ((f121w*qfftsz)/phase_samrat)
#define  f243s                ((f243c*qfftsz)/phase_samrat)
#define  f243n                ((f243w*qfftsz)/phase_samrat)
#define  max_f406n            ((max_f406w*qfftsz)/phase_samrat)
#define  f121l                (2*f121n + 1)
#define  f243l                (2*f243n + 1)
#define  f406cl                (170000L)
#define  f406wl                (42000L)
#define  f406sl                ((f406cl * qfftsz) / phase_samrat)
#define  f406nl                ((f406wl * qfftsz) / phase_samrat)
#define  f406ll                (2 * f406nl + 1)
#define  max_f406l            (2 * max_f406n + 1)
#define  binfak               (phase_samrat/(qfftsz*50.0))
#define  fftrat               ((1.0*phase_samrat)/not_overlap)
#define  fftbitrat            (fftrat/nom_bit_rate)
#define  bitinc               (fftbitrat*z_not_overlap)
#define  nbitinc              (__int32)(bitinc+0.5)

#define  pulse1               (msg_preamble*fftrat)                  // 11.2
#define  pulse2               (NUM_SHORT_MSG_BITS*fftbitrat + pulse1)// 30.7
#define  pulse3               (NUM_LONG_MSG_BITS*fftbitrat  + pulse1)// 36.3
#define  pulse4               (1.10*pulse3)                          // 39.9

// Monitor flags
#define  MON_FR               0x01
#define  MON_C1               0x02
#define  MON_S1               0x04
#define  MON_C2               0x08
#define  MON_S2               0x10
#define  MON_C4               0x20
#define  MON_DI               0x40
#define  MON_MI               0x80
#define  MON_PD               0x100

// Wideband state engine
typedef enum
{
   ModeWBPShutdown = 0,
   ModeWBPIdle,
   ModeWBPStartProcessing,
   ModeWBPProcessing,
   ModeWBPStopProcessing
} TWidebandState;

// Processing flags based on signal database 'ProcessFlag'
typedef enum
{
   // Process selection flag (bits 0=POWSD, 1=AUDIO, 2=CBC, 3=GSARP,
   //    4 =PDS, 5=Track)
   PROCESS_POWSD = 1,
   PROCESS_AUDIO = 2,
   PROCESS_CBC   = 4,
   PROCESS_GSARR = 8,
   PROCESS_PDS   = 16,
   PROCESS_TRACK = 32,
} TProcess;
/*s
// These vectors are used for the digital 406 detection algorithm
typedef struct
{
    long	ndet;
    long	fdet[ MAXDET ];
    long	bdet[ MAXDET ];
    long	ddet[ MAXDET ];
    float	pdet[ MAXDET ];
} BPD_Detection_T;

// Message integration structures
typedef enum
{
    No_Integration,
    Full_Integration,
    Partial_Integration
} BPD_Integration_Mode_T;

typedef struct
{
    unsigned __int64   bid;    //  Short beacon id; represents bits 26->85 as 0->31,32->59
    float      nominal_frq;    // Nominal frequency of reference beacon (offset from 406.0 MHz)
    short      rep_rate;       // Repetition rate; -1=unused slot, 30 or 50 are common
    short      group;          // Matched group index
    bool       suppress;       // Suppress beacon output if true. Defaults to false
} BPD_Reference_Beacon_T;

typedef struct
{
//    double earliest_time;      // Time of the first contributor ( seconds )
//    double latest_time;        // Time of the last contributor ( seconds )
//    double last_output_time;   // Time of the last output message ( seconds )

	  CEMSTime timeEarliest;	
	  CEMSTime timeLatest;
	  CEMSTime timeLastOutput;
                               // Set to 0 when group is created
    float ave_bit_power[ NUM_LONG_MSG_BITS ]; // Bit power levels
    float ave_freq;            // Average frequency ( Hertz )
    float earliest_freq;       // Frequency ( Hertz )
    float last_output_freq;    // Frequency drift ( Hertz / Minute )
    float freq_drift;          // Frequency drift ( Hertz / Minute )
    unsigned long group_id;    // Group ID used to track integrations
    long  message_count;       // Total Number of messages obtained from group
    short fstype;              // Message type
    short ref_beacon_flag;     // Set if message matches one of the predefined
		                       // beacons; if so, no purge or header updates
    short repetition_rate;     // 30 secs for orbitography beacons
		  	                   // 50 secs for other legitimate beacons
				               // Set to 0xFFFF when group is created
    short total_num_messages;  // Total number of messages in group (up to 10)
    short num_integrations;    // Current number of integrations
    short num_integrations_at_last_output;    // Number of integrations at last
						                      // output, set to 0 when group is created
    short group_flag;          // Group active flag
} BPD_Integration_Header_T;

typedef struct
{
//   double time;                // Burst time ( seconds offset )
   unsigned char msg[ MAX_BIT_WORDS ];    // 406 message
//   unsigned long msg_time;     // Burst time (seconds from 1970)
//   unsigned long msg_time_fraction; // Burst time fraction (nanoseconds)
	 CEMSTime timeMsg;
   float  bit_power[ NUM_LONG_MSG_BITS ]; // Bit power levels
   float  total_power;         // Total bit power
   float  freq;                // Frequency ( Hertz )
   float  power;               // Carrier to noise ratio ( C/No )
   float  sn0;                 // Signal to noise ratio ( S/No )
   float  mod_idx;             // Modulation index
   float  bit_rate;            // Bit rate ( bits/second )
   float  sat_frq_offset;      // Satellite frequency correction (Hz)
   bool   msg_flag;            // Set if a message is actually present
   short  contributor_flag;    // Set if message contributed to header
   short  output_flag;         // Set if message already output
   short  fstype;              // Frame sync type
   short  biterr_fs;           // Frame synch errors
   short  biterr_pf1;          // First protected field bit errors
   short  biterr_pf2;          // Second protected field bit errors
} BPD_Integration_1_Msg_T;

typedef struct
{
   BPD_Integration_Header_T header;
   BPD_Integration_1_Msg_T  messages[ MAX_MSGS_PER_GROUP ];
} BPD_Integration_1_Group_T;

typedef BPD_Integration_1_Group_T TWidebandIntegration[ MAX_NUM_GROUPS ];

typedef struct
{
   long	 max_406_detects;
   long	 nfloor0_det;
   long	 nfloor1_det;
   float thresh_det;
   float on_det;
   float off_det;
   float fcoeff_det;
   float proc_406_start;
   float proc_406_end;
   long	 detect_test_msg;
   float band_centre_406;
   float bandwidth_406;
   float freq_offset_406;
   float             MinCNRBPP;         // BPP minimum CNR level output (dB-Hz)
   unsigned short    MaxFSerrBPP;       // Maximum number of BPP frame synch bit errors allowed
} BPD_Rtcntrl_T;


typedef struct
{
    int             nfloor0;
    int             nfloor1;
    int             nsmooth0;
    int             nsmooth1;
    float           pkfak[3];
    float           amp[3];
    float           incoherent_offset;
	float           DetectThres121;
    float           DetectThres243;
	float           DetectThres406;
	float           MinFreq[3];
	float           MaxFreq[3];
	float           detFreq;
    unsigned short  DataC1;
    unsigned short  DataC2;
    unsigned short  DataC4;
} CBC_Rtcntrl_T;


typedef struct
{
   float                       BaudRate;
   float                       BaudWindow;
   float                       BaudStep;
   unsigned __int16            BaudDuration;
   float                       BaudStart;
   float                       BaudStop;
   unsigned __int16            BaudElapsed;
   Sat_Sarp_T                  SatSarp;
   unsigned short              SarpType;
   unsigned short              PlaybackPDS;
   float                       RefFreqOffset;
   char                        RolloverTime[25];
   unsigned short              DataPD;
   unsigned short              DataRP;
   unsigned short              DataTI;
   unsigned short              DataRPO;
                               // Control the output of raw_pds_msg
                               // DataRPO = 0: Not output; =1: Output
} PDS_Rtcntrl_T;

typedef struct
{
   bool  zero_fill;
   bool  integration_restart;
   bool  detect_test_msg;
   BPD_Integration_Mode_T integration_mode;
   float group_ageout;
   float freq_window;
   float time_window;
   short max_bit_diff;
   short frame_sync_errors;
   short bch_errors;
   short bch2_errors;
   short num_integrations_for_partial_output;
   float time_for_partial_output;
   float min_power_level;
   float min_cno_level;
   BPD_Reference_Beacon_T ref_beacons[ MAX_NUM_BEACONS ];
} BPD_Integration_Parms_T;

typedef struct
{
	 CEMSTime timeLatestFreq;
   float  sat_frq_offset;
   float  error_variance;
   float  measurement_noise;
   short  first_frq;
//   double latest_frq_time;
   float  latest_freq;
} TSatelliteFilter;


typedef struct
{
	CEMSTime			timeRx;// Time of current detection 
	CEMSTime			timeFirst;// Time of first detection

//    TSARTime        RxTime;             // Time of current detection in seconds
//    unsigned long   RxTimeFraction;     // Receive time fraction in nanoseconds
//    TSARTime        FirstTime;          // Time of first detection in seconds from 1970 (C internal format)

    unsigned short  Type;               // Data Type : BPP, PDS, Dump, RealTime, Test, etc.
    unsigned short  SatelliteID;        // Satellite Identifier number (according to COSPAS-SARSAT)
    unsigned long   GroupID;            // Group Identifier (GEO data only) or Pass Number (LEO data only)
//    TBeaconID       BeaconID;           // Beacon Identifier : 60 bit pattern (15 Hex Id)
//    TBeaconMsg      BeaconMsg;          // Full text message (144 bits)
//    TSARTime        FirstTime;          // Time of first detection in seconds from 1970 (C internal format)
    __int64         BeaconID;           // Beacon Identifier : 60 bit pattern (15 Hex Id)
    unsigned char   BeaconMsg[18];      // Full text message (144 bits)
    float           Frequency;          // Frequency in Hz
    float           FrequencyOffset;    // Frequency offset in Hz (satellite/ground station dependency)
    float           FrequencyBW;        // Frequency bandwidth of carrier in Hz (dependent upon Doppler)
    float           FirstFrequency;     // First measured frequency in Hz
    float           FrequencyDrift;     // Average frequency drift in Hz/min
    float           CNR;                // Carrier to Noise Ratio (dB-Hz) or Power (dBm)
    float           SNR;                // Signal to Noise Ration (dB-Hz)
    unsigned short  BER_PF1;            // Number of bit errors in first protected field
    unsigned short  BER_PF2;            // Number of bit errors in second protected field
    unsigned short  BER_FS;             // Number of bit errors in frame synch
    unsigned short  Counts;             // Number of integrated messages
    float           BitRate;            // Bit Rate in bits/sec
    float           ModIndex;           // Modulation Index in radians
    float           ShortMessIndex;     // Average bit power ratio of long message bits to short message bits
    float           FSMessIndex;        // Frame sync test to message power correlation ratio
    float           FSBitOffset;        // Direction and number of bits between the test and message frame sync
    short           RepetitionRate;     // Repetition rate of the group (-1(undefined), 30, or 50 seconds)
    unsigned short  ActiveGroups;       // Number of active groups
} TGeo406Data;


typedef struct
{
//    TSARTime        Time;              // Time in seconds
//    unsigned long   TimeFraction;      // Time fraction in nanoseconds

	CEMSTime				time;					

    unsigned short  Type;              // Data Type : BPP, PDS, Dump, RealTime, Test, etc.
    unsigned short  SatelliteID;       // Satellite Identifier number (according to COSPAS-SARSAT)
    unsigned long   GroupID;           // Group Identifier (GEO data only) or Pass Number (LEO data only)
//    TBeaconID       BeaconID;          // Beacon Identifier : 60 bit pattern (15 Hex Id)
//    TBeaconMsg      BeaconMsg;         // Full 144 bit pattern
    __int64         BeaconID;           // Beacon Identifier : 60 bit pattern (15 Hex Id)
    unsigned char   BeaconMsg[18];      // Full text message (144 bits)
    float           Frequency;         // Frequency in Hz
    float           FrequencyOffset;   // Frequency offset in Hz (satellite/ground station dependency)
    float           FrequencyBW;       // Frequency bandwidth of carrier in Hz (dependent upon Doppler)
    float           CNR;               // Carrier to Noise Ratio (dB-Hz) or Power (dBm)
    float           SNR;               // Signal to Noise Ration (dB-Hz)
    unsigned short  BER_PF1;           // Number of bit errors in first protected field
    unsigned short  BER_PF2;           // Number of bit errors in second protected field
    unsigned short  BER_FS;            // Number of bit errors in frame synch
    float           BitRate;           // Bit Rate in bits/sec
    float           ModIndex;          // Modulation Index in radians
    float           ShortMessIndex;    // Average bit power ratio of long message bits to short message bits
    float           FSMessIndex;       // Frame sync test to message power correlation ratio
    float           FSBitOffset;       // Direction and number of bits between the test and message frame sync
    float           RawBitPower[144];  // Raw bit power values (for message integration and diagnostics)
} TRaw406Data;
e*/
#endif  // INC_WideBand_Data_Types_H
