#ifndef WideBand_Data_Types_H
#define WideBand_Data_Types_H

// Data processing definitions
#define MAX_WBP_EVENTS 2

// Declarations of constants and macros
#define MAXMSG                  10      // Maximum of raw and integrated 406 messages
//#define MAXDET			 5     	// Maximum number of 406 beacon detections
#define MAX_BIT_WORDS	        18
#define EMS_NUM_SHORT_MSG_BITS      (112L)  // Number of bits in 406 short messages
#define EMS_NUM_LONG_MSG_BITS       (144L)  // Number of bits in 406 long messages
#define MSG_FORMAT_BIT          (25L)   // Format bit location in 406 messages
#define MSG_SHORT               0       // Short message indication for 406 messages
#define MSG_LONG                1       // Long message indication for 406 messages
//#define MESSAGE_TYPE            100     // GSARP data message
//#define TEST_TYPE               777     // GSARP test message

#define EMS_PF1_PROTECTED_BITS      (106L)  // Bits in protected field

#define PF1_PROTECTED_BITS      (EMS_PF1_PROTECTED_BITS)
#define NUM_SHORT_MSG_BITS      (EMS_NUM_SHORT_MSG_BITS) 
#define NUM_LONG_MSG_BITS      (EMS_NUM_LONG_MSG_BITS) 

#define BEACON_REP_RATE         50      // Ordinary beacon repetition rate
#define ORB_REP_RATE            30      // Orbitography/Test beacon repetition rate

// Extra bits used required to locate possible test frame syncs
#define EXTRA_BITS              12

// Window width for frequency measurement interpolation
#define  WINDOW_WIDTH           3

// RT parameter file default values

#define MAX_406_DETECTS        10
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

#endif
