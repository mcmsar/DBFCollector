#ifndef INC_SARR_DATA_TYPES
#define INC_SARR_DATA_TYPES

#include "emstime.h"
#include "memtypes.h"
#include "wbdtypes.h"
#include "CBeaconMessage.h"


#define BASE_FREQ_406           406000000.0

typedef struct
{
    INT64   bid;    //  Short beacon id; represents bits 26->85 as 0->31,32->59
    float      nominal_frq;    // Nominal frequency of reference beacon (offset from 406.0 MHz)
    short      rep_rate;       // Repetition rate; -1=unused slot, 30 or 50 are common
    short      group;          // Matched group index
    bool       suppress;       // Suppress beacon output if true. Defaults to false
} BPD_Reference_Beacon_T;


typedef enum
{
    No_Integration,
    Full_Integration,
    Partial_Integration
} BPD_Integration_Mode_T;

// These vectors are used for the digital 406 detection algorithm
typedef struct
{
    long	ndet;
    long	fdet[ MAX_406_DETECTS ];
    long	bdet[ MAX_406_DETECTS ];
    long	ddet[ MAX_406_DETECTS ];
    float	pdet[ MAX_406_DETECTS ];
} BPD_Detection_T;


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


// Wideband Processor structures
typedef SCplx TWidebandFft[MAX_FFTS+MAX_FFTS/2][PSD_SIZE/2];

// Wide Band Processor Common Memory Block
typedef struct
{
   TWidebandFft         Fft;              // Raw fft buffer
   TWidebandIntegration mi_groups;        // 406 integration groups
} TWidebandMemory;


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
	__int64         BeaconID;           // Beacon Identifier : 60 bit pattern (15 Hex Id)
    CBeaconMessage      BeaconMsg;          // Full text message (144 bits)
//    TSARTime        FirstTime;          // Time of first detection in seconds from 1970 (C internal format)
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
	__int64         BeaconID;          // Beacon Identifier : 60 bit pattern (15 Hex Id)
    CBeaconMessage  BeaconMsg;         // Full 144 bit pattern
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


typedef struct {
    int         ccnum;
    char        ccshort[4];
    char        cclong[11];
} TCountryCode;

#endif   // INC_SARR_DATA_TYPES
