#ifndef PDS_Data_Types_H
#define PDS_Data_Types_H

#include "nsp.h"

// Declarations of constants

#define PDS_BANDWIDTH                   1024
#define ANALOG_BITSTREAM_BUFFER_SIZE    5000
#define MANCHESTER_BUFFER_SIZE          (100000L)
#define MAX_WORDS                       9
#define MAX_DRUS                        3
#define NUMBER_OF_MESSAGE_STATUS_BYTES  2
#define MAX_BITS_IN_FRAME               1200
#define WORD_24_SIZE                    24
#define MAX_QUEUE_ELEMENTS              25
#define SAMPLES_PER_SEC                 (500000L)
#define SAMPLES_PER_BLOCK               (8192L)
#define FFT_OVERLAP_FACTOR              (0.125)
#define INCREMENT                       1
#define DECREMENT                       -1

#define PDS_UTILIZED_FFT_WIDTH          512
#define SAMPLE_RATE_LEO                 62500.0
                                 // 1/8th of the input bandwidth, 4k ffts
#define RAW_ID_LOCATION                 0
                                 // message status character indices
#define ORPHAN_BIT_LOCATION             1
#define BAD_DRU_BIT_LOCATION            1
#define LONG_BIT_LOCATION               1
#define BAD_DRU                         4    // bit patterns
#define ORPHAN_WORD                     2
#define LONG_MSG                        1
#define SARP_0_DRU1_INDICATOR           3   // maps to DRU1
#define SARP_0_DRU2_INDICATOR           5   // maps to DRU2

// there are 3 sarp -2 or -3 messages per 25 word frame
#define NUMBER_OF_SARP_MESSAGES_PER_FRAME 3
// SARP messages (long or short) are 8 24-bit words
#define SARP_MESSAGE_LENGTH_8_WORDS     8

// except SARSAT SARP-1: long msg = 9 24-bit words, short msg = 8 24-bit words
#define SARSAT_SARP_01_FORMAT_WORD      2   // word index
#define SARSAT_SARP_01_LONG             9   // length in 24 bit words
#define SARSAT_SARP_01_SHORT            8   // length in 24 bit words


#define COSPAS_SARP_1_FILLER_WORD       49  // location of filler word

#define COSPAS_SARP_1_LENGTH            8   // length in 24 bit words
#define COSPAS_SARP_2_FORMAT_WORD       3   // word index
#define COSPAS_SARP_2_LONG              8   // length in 24 bit words
#define COSPAS_SARP_2_SHORT             7   // length in 24 bit words


#define SARSAT_SARP_2_FORMAT_WORD       0   // word index
#define SARSAT_SARP_2_LONG              8   // length in 24 bit words
#define SARSAT_SARP_2_SHORT             7   // length in 24 bit words
#define SARSAT_SARP_3_FORMAT_WORD       2    // index of word containing format bit
#define SARSAT_SARP_3_LONG              SARSAT_SARP_2_LONG     /* SARP3 == SARP2 */
#define SARSAT_SARP_3_SHORT             SARSAT_SARP_2_SHORT    /* SARP3 == SARP2 */

#define SARP_01_OUTPUT_WORD_SIZE        5   // output is grouped in 5 digit words
#define SARP_2_OUTPUT_WORD_SIZE         6   // output is grouped in 6 digit words
#define SARP_3_OUTPUT_WORD_SIZE         6   // output is grouped in 6 digit words


#define FRAME_SYNC_PATTERN_LENGTH       24  // bits
#define MSG_SYNC_PATTERN_LENGTH         12  // bits
#define MAX_FRAME_SYNC_ERRORS           2   // bits
#define BIG_NEGATIVE_NUMBER             (-3.37e38)
#define NUMBER_OF_FRAMES_MULTIPLE       1   // used in location of frame syncs
#define SCORE_FACTOR                    10  // used in location of frame syncs
#define MAX_FRAME_SYNC_LOCATIONS        20  // max frame syncs in one processing
                                            // interval = 6,
                                            // 6 * NUMBER_OF_FRAMES_MULTIPLE = 18

#define NUMBER_OF_ZEROED_BINS           5   // approx. 60 Hz per bin, => 1200 Hz,
                                            // frequency components up to 1200 Hz
                                            // are filtered from the input signal
#define SAMPLES_INTO_FFT        SAMPLES_PER_BLOCK
#define BINS_OUT_OF_FFT         (SAMPLES_INTO_FFT / 2)
#define MAX_WORDS_IN_FRAME      MAX_BITS_IN_FRAME / WORD_24_SIZE
#define FFT_OVERLAP_PER_BLOCK   ((int) (SAMPLES_INTO_FFT * FFT_OVERLAP_FACTOR))
#define FFT_UNOVERLAP_PER_BLOCK (SAMPLES_INTO_FFT - FFT_OVERLAP_PER_BLOCK)
#define MAX_FFTS_PER_SEC        ((int) (SAMPLES_PER_SEC/FFT_UNOVERLAP_PER_BLOCK) + 1)
#define MAX_BINS_PER_SEC        (FFTS_PER_SEC * BINS_OUT_OF_FFT)

#define RADIANS_TO_ADC_VALUE(rads)      ((rads) * 0x10000 / (2 * _PI))
#define ADC_VALUE_TO_RADIANS(adc_val)   ((adc_val) * 2 * _PI / 0x10000)
#define CYCLES_TO_ADC_VALUE(rads)       ((rads) * 0x10000)
#define ADC_VALUE_TO_CYCLES(adc_val)    ((adc_val) / 0x10000)

#define NULL_PTR              ((void *) 0)
#define NULL_SYNC_MESSAGE     NULL_PTR   // null pointers to map to
#define NULL_RAW_PDS_MESSAGE  NULL_PTR   // queue element content    
#define NULL_PDS_DATA         NULL_PTR


#define FILLER_WORD_DIGIT_0   0x0       // filler word 0x000001
#define FILLER_WORD_DIGIT_1   0x0
#define FILLER_WORD_DIGIT_2   0x0
#define FILLER_WORD_DIGIT_3   0x0
#define FILLER_WORD_DIGIT_4   0x0
#define FILLER_WORD_DIGIT_5   0x1

#define MESSAGE_SYNC_WORD_DIGIT_0 0xd   // message sync word digits 0xd60
#define MESSAGE_SYNC_WORD_DIGIT_1 0x6
#define MESSAGE_SYNC_WORD_DIGIT_2 0x0

#define MAX_CORRELATION_VECTOR_SIZE   ANALOG_BITSTREAM_BUFFER_SIZE

#define FFT_OVERLAP ((int) (FFT_OVERLAP_FACTOR * PDS_UTILIZED_FFT_WIDTH * 2))


// Declarations of data structure
typedef enum { False = 0, True = 1 } Boolean_T;
typedef SCplx Short_FFT_Vector_T[PDS_BANDWIDTH];
typedef SCplx FFT_Vector_T[BINS_OUT_OF_FFT];
typedef FFT_Vector_T  FFT_Array_T[MAX_FFTS_PER_SEC];
typedef enum {COSPAS, SARSAT} Satellite_T;
typedef enum {SARP0, SARP1, SARP2, SARP3} Processor_T;
typedef enum {UNSYNCED, SYNCED, NO_SYNC, SYNC_LOSS } Sync_State_T;
typedef enum {DISABLED, ENABLED} Playback_T;
typedef enum {PLAYBACK, REALTIME} Source_T;
typedef enum {SYNC_MESSAGE, RAW_PDS_MESSAGE, PDS_DATA} Queue_Element_T;

typedef unsigned __int8 Bit_Data_T[MAX_BITS_IN_FRAME];


typedef struct
{
     Satellite_T satellite;
     Processor_T processor;
     Playback_T  playback;
} Sat_Sarp_T;


typedef struct
{
     float correlation_strength;
     unsigned __int32 analog_bitstream_index;
} Correlation_Element_T;


typedef struct
{
     __int32 correlation_vector_length;
     Correlation_Element_T correlation_data[MAX_CORRELATION_VECTOR_SIZE];
} Correlation_Vector_T;


typedef struct
{
     float power_value;
     unsigned __int32 manchester_data_index;
} Analog_Bitstream_Element_T;

typedef struct
{
     unsigned __int32 input_ptr;
     unsigned __int32 output_ptr;
     Analog_Bitstream_Element_T data[ANALOG_BITSTREAM_BUFFER_SIZE];
} Analog_Bitstream_T;

typedef struct
{
         int number_of_peaks;
     struct
     {
          unsigned __int32 correlation_vector_index;
          unsigned __int32 analog_bitstream_index;
          double correlation_strength;
     } data[MAX_FRAME_SYNC_LOCATIONS];
} Correlation_Peaks_T;

typedef struct
{
     unsigned int number_of_frames;
     unsigned int frame_size;
     unsigned int max_frame_size_error;
} Frame_Attributes_T;

typedef struct
{
     unsigned __int32 input_ptr;
     unsigned __int32 output_ptr;
     double align_it;
     float data[MANCHESTER_BUFFER_SIZE];
} Manchester_Data_T;


typedef struct
{
     unsigned int word_24:WORD_24_SIZE;
} Word_24_T;


typedef struct
{
     unsigned int b0:1;
     unsigned int b1:1;
     unsigned int b2:1;
     unsigned int b3:1;
     unsigned int b4:1;
     unsigned int b5:1;
     unsigned int b6:1;
     unsigned int b7:1;
     unsigned int b8:1;
     unsigned int b9:1;
     unsigned int b10:1;
     unsigned int b11:1;
     unsigned int b12:1;
     unsigned int b13:1;
     unsigned int b14:1;
     unsigned int b15:1;
     unsigned int b16:1;
     unsigned int b17:1;
     unsigned int b18:1;
     unsigned int b19:1;
     unsigned int b20:1;
     unsigned int b21:1;
     unsigned int b22:1;
     unsigned int b23:1;
} Bit_T;

typedef struct
{
     unsigned int d0:4;
     unsigned int d1:4;
     unsigned int d2:4;
     unsigned int d3:4;
     unsigned int d4:4;
     unsigned int d5:4;
} Digit_T;


typedef union
{
     Word_24_T word;
     Digit_T digits;
     Bit_T bits;
} Word_Union_T;


typedef struct
{
     unsigned __int32 filler;                      /* memory alignment filler */
     Word_Union_T content[MAX_WORDS];
     Boolean_T message_decode_in_progress;
     Boolean_T message_length_determined;
     __int32 expected_length;
     __int32 stored_length;
     Processor_T processor;
     char message_status[NUMBER_OF_MESSAGE_STATUS_BYTES];
} Single_Message_T;


typedef struct
{
     Single_Message_T message_data[MAX_DRUS + 1];
     // 1 is added because message_data[0] is not used - dru
     // numbers start at 1
} Messages_T;


typedef struct
{
     __int32 number_of_words;
     float baud_rate;
     Word_Union_T frame_data[MAX_WORDS_IN_FRAME];
} Frame_T;


typedef struct
{
     Queue_Element_T queue_element_type;
     union
     {
          Sync_State_T sync_message;
          Frame_T raw_pds_message;
          Single_Message_T pds_data;
     } data;
} Queue_Element_Content_T;


typedef struct
{
     __int32 content_count;
     Queue_Element_Content_T queue_data[MAX_QUEUE_ELEMENTS];
} Output_Queue_T;


typedef struct
{
    unsigned __int32    total_frames;
    unsigned __int32    total_messages;
    unsigned __int32    total_sync_losses;
    unsigned __int32    total_no_syncs;
    unsigned __int32    current_sync_losses;
    unsigned __int32    current_no_syncs;
} PDS_Statistics_T;

#endif
