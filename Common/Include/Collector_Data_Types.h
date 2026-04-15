#ifndef Collector_Data_Types_H
#define Collector_Data_Types_H

// Required headers
#include "Standards.h"

// Data acquisition definitions

#define CAPS_SIZE       5
#define FIFO_SIZE       8192
#define SAMPLE_RATE     (2000000L)
#define SAMPLE_SIZE     ((int)(((SAMPLE_RATE+FIFO_SIZE-1)/FIFO_SIZE))*FIFO_SIZE)
#define TRIGGER_RATE    ((float)((float)SAMPLE_SIZE/(float)SAMPLE_RATE))
#define BUFFER_SIZE     (SAMPLE_SIZE*2)

// Digital down conversion definitions

#define FIR_SIZE        22
#define FIR_OVERLAP     (FIR_SIZE*2)
#define AGC_SAMPLE_SIZE (FIFO_SIZE*2)

// Phase locked loop definitions

#define OVERLAP_PERCENT     0.125
#define MOD_INDEX_THRESHOLD 1.75
#define MAX_FFTS            70
#define FFT_SIZE            8192
#define PSD_SIZE            4097
#define PHASE_BUFF_SIZE     ((int)(SAMPLE_SIZE/4+((int)FFT_SIZE*OVERLAP_PERCENT)))
//#define PHASE_BUFF_SIZE     ((int)(SAMPLE_RATE/4+((int)FFT_SIZE*OVERLAP_PERCENT)))

    // Frequency offset to add to input to centre the peak for the
    // data in the middle of the FFT to avoid aliasing.
#define ADC_RANGE                   65536.0
#define ADC_OFFSET                  8192 
#define PHASE_SAMPLE_RATE           (SAMPLE_RATE/4)
#define PHASE_CONVERSION            (ADC_RANGE/(float)PHASE_SAMPLE_RATE)
#define ACQUISITION_FRQ_OFFSET		((float)PHASE_SAMPLE_RATE/4.0)
#define ACQUISITION_PHASE_OFFSET	\
	     (ADC_RANGE*(float)ACQUISITION_FRQ_OFFSET/(float)PHASE_SAMPLE_RATE)

    // Length of interval between samples for estimating an initial
    // reference angle, the doppler frequency correction needed and phase
    // standard deviation
#define DECIMATION_FACTOR		8

    // Number of samples used in estimating the initial reference
    // phase angle
#define INITIAL_PHASE_EST_LEN	        417

    // The maximum number of iterations to do when determining the
    // doppler frequency correction
#define MAX_FRQ_CORRECTION_ITERATIONS	3

    // The maximum number of iterations to do when estimating the
    // reference phase angle
#define MAX_REF_ANGLE_EST_ITERATIONS	5

    // The maximum loop index for the actual phase unwrap.  Used in
    // making more accurate phase unwrap.  THIS MUST DIVIDE EVENLY INTO
    // PHASE_UNWRAP_BLOCK_SIZE!
#define MAX_UNWRAP_LOOP_IDX		8

// Power spectrum definitions

#define FFT_SCALE    (1.0/32767.0)

// Collector state engine
typedef enum
{
   ModeDAQShutdown = 0,
   ModeDAQIdle,
   ModeDAQStartCollection,
   ModeDAQCollecting,
   ModeDAQStopCollection
} TCollectorState;

#define EMS_max(a,b)  (((a) > (b)) ? (a) : (b))

// Raw DMA Buffer (Overlapped)
#define EMS_RAW_OVERLAP (int)(( FFT_SIZE * OVERLAP_PERCENT ))
//#define EMS_RAW_OVERLAP (int)(( FFT_SIZE ))
#define EMS_DMA_OVERLAP_SIZE ( EMS_max( FIR_OVERLAP, EMS_RAW_OVERLAP ) )

#define ARRAYLEN_TRAWDMA (EMS_DMA_OVERLAP_SIZE+SAMPLE_SIZE)
typedef unsigned short TRawDMA[ ARRAYLEN_TRAWDMA ];
//typedef unsigned short TRawDMA[FIR_OVERLAP+SAMPLE_SIZE];

// Raw Inphase Buffer
#define ARRAYLEN_TRAWINPHASE (SAMPLE_SIZE/2+FIR_SIZE)
typedef short TRawInphase[ARRAYLEN_TRAWINPHASE];

// Raw Quadrature Buffer
#define ARRAYLEN_TRAWQUADRATURE (SAMPLE_SIZE/2+FIR_SIZE)
typedef short TRawQuadrature[ARRAYLEN_TRAWQUADRATURE];

// Raw Phase Buffer (Overlapped)
typedef short TRawPhase[PHASE_BUFF_SIZE];

// Demodulated Phase Buffer (Overlapped)
typedef short TDemodulatedPhase[MAX_FFTS][FFT_SIZE];

#endif
