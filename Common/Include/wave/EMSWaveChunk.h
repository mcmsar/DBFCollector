/*********************************************************************
*	              Copyright (c) 2005 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log:
	$
********************************************************************/

#ifndef __WAVE_CHUNK_H__
#define __WAVE_CHUNK_H__

#include "emstypes.h"
#include "emsorbit.h"

// Pack on 1 byte alignment in order that any output waves are binary compatible with the
// standard.
#pragma pack(push,1)

//! The format chunk for a WAVE format RIFF.
typedef struct tagEMSWaveFmtChunk
{
	//! Contains the letters "fmt "
	//! (0x666d7420 big-endian form).
	DWORD	dwSubChunkID;

	//!	16 for PCM.  This is the size of the
	//!rest of the Subchunk which follows this number.
	DWORD	dwSubChunkSize;

	//! PCM = 1 (i.e. Linear quantization)
	//! Values other than 1 indicate some 
	//! form of compression.
	WORD	wAudioFormat;

	//! Mono = 1, Stereo = 2, etc.
	WORD	wNumChannels;

	//! Sample rate of the data (e.g., 8000, 44100, etc.)
	DWORD	dwSampleRate;

	//! equals SampleRate * NumChannels * BitsPerSample/8
	DWORD	dwByteRate;

	//! equals NumChannels * BitsPerSample/8
	//!The number of bytes for one sample including
	//! all channels.
	WORD	wBlockAlign;

	//! 8 bits = 8, 16 bits = 16, etc.
	WORD	wBitsPerSample;
} EMSWAVEFMTCHUNK;

//static const ULONG sculDataSize = 1024000;

//! The data chunk for a WAVE format RIFF.
typedef struct tagEMSWaveDataChunk
{
	//! Contains the letters "data"
	//! (0x64617461 big-endian form).
	DWORD	dwSubChunkID;

	//! NumSamples * NumChannels * BitsPerSample/8
	//!	This is the number of bytes in the data.
	//!	You can also think of this as the size
	//!	of the read of the subchunk following this 
	//!	number.
	DWORD	dwSubChunkSize;

	//! The data.
	BYTE*	abyData;

} EMSWAVEDATACHUNK;

typedef struct tagEMSWaveExtensionLutDetails
{
	DWORD dwLutID;
	DWORD dwFlags;
	EMSLOCATIOND location;
	WORD wAntennaID;
} EMSWAVEEXTLUTDETAILS;

typedef struct tagEMSWaveExtensionSatDetails
{
	DWORD dwSatID;
	DWORD dwFlags;
	DWORD dwOrbitNumber;
	EMSTLEDATA2 tleData;
	EMSCOORDSYSTEM eCoordSystem;
	double dProbability;
} EMSWAVEEXSATDETAILS;

typedef enum tagEMSWaveExtensionPhaseModulation
{
	EMS_PHASE_MOD_UNKNOWN = 0,
	//! Signal is phase modulated.
	EMS_PHASE_MOD_YES = 1,
	//! Signal is not phase modulated.
	EMS_PHASE_MOD_NO = 2
} EMSPHASEMODSTATE;

static const wchar_t* gs_cwszPhaseModUnknown = L"Unknown";
static const wchar_t* gs_cwszPhaseModYes = L"Modulated";
static const wchar_t* gs_cwszPhaseModNo = L"Unmodulated";

typedef enum tagEMSWaveExtensionDownConversion
{
	EMS_DC_UNKNOWN = 0,
	//! Signal is downconverted or doesn't require downconversion.
	EMS_DC_YES = 1,
	//! Signal is not downconverted, but requires it.
	EMS_DC_NO = 2
} EMSDCSTATE;

static const wchar_t* gs_cwszDCUnknown = L"Unknown";
static const wchar_t* gs_cwszDCYes = L"Not Required";
static const wchar_t* gs_cwszDCNo = L"Required";

typedef struct tagEMSWaveExtensionSignalDetails
{
	DWORD dwFlags;
	double dMaxADC;
	double dMeanADC;
	double dStdDevADC;
	double dMeanCarrierFreq;
	double dStdDevCarrierFreq;
	double dMaxModIndex;
	double dMeanModIndex;
	double dStdDevModIndex;
	EMSPHASEMODSTATE statePhaseMod;
	EMSDCSTATE stateDC;
} EMSWAVEEXSIGNALDETAILS;

typedef struct tagEMSWaveExtensionSubBand
{
	DWORD dwType;
	double dFreqStart;
	double dFreqEnd;
} EMSWAVEEXSUBBAND;

typedef struct tagEMSWaveExtensionSubBands
{
	WORD wNumber;
	DWORD dwFlags;
	EMSWAVEEXSUBBAND* aSubBand;
} EMSWAVEEXSUBBANDS;

//! General properties included in the EMS Wave extension chunk.
typedef struct tagEMSWaveExtensionProperties
{
	DWORD	dwChannelNumber;
	DWORD	dwHardwareVersion;
	DWORD	dwSoftwareVersion;
	EMSTIME	timeStart;
	double	dBinSize;
	DWORD	dwStartIdx;
	DWORD	dwEndIdx;
} EMSWAVEEXTPROPERTIES;

//! The EMS extension chuck for a WAVE format RIFF.
typedef struct tagEMSWaveExtensionChunk
{
	//! Contains the letters "emsx"
	DWORD	dwSubChunkID;

	//! Size of the data following this field.
	DWORD	dwSubChunkSize;

	EMSWAVEEXTLUTDETAILS lutDetails;
	EMSWAVEEXSATDETAILS satDetails;
	EMSWAVEEXSIGNALDETAILS signalDetails;
	EMSWAVEEXSUBBANDS subBandDetails;
	EMSWAVEEXTPROPERTIES properties;
} EMSWAVEEXTCHUNK;

typedef struct tagEMSWAVERIFFHEADER
{
	//! Contains the letters "RIFF" in ASCII form
	//! (0x52494646 big-endian form).
	DWORD				dwChunkID;

	//! 36 + SubChunk2Size, or more precisely:
	//!	4 + (8 + SubChunk1Size) + (8 + SubChunk2Size)
	//!	This is the size of the rest of the chunk 
	//!	following this number.  This is the size of the 
	//!	entire file in bytes minus 8 bytes for the
	//!	two fields not included in this count:
	//!	ChunkID and ChunkSize.
	DWORD				dwChunkSize;

	//! Contains the letters "WAVE"
	//! (0x57415645 big-endian form).
	DWORD				dwFormat;

} EMSWAVERIFFHEADER;

//! A standard WAVE format RIFF chunk.
typedef struct tagEMSSTDWAVERIFF
{
	//! The RIFF header.
	EMSWAVERIFFHEADER hdr;
	
	//! The format chunk.  A required chunk.
	EMSWAVEFMTCHUNK		fmtChunk;

	//! The data chunk.  A required chunk.
	EMSWAVEDATACHUNK	dataChunk;

} EMSSTDWAVERIFF;


//! A WAVE format RIFF chunk with an EMS extension chunk included.
typedef struct tagEMSWAVERIFF : tagEMSSTDWAVERIFF
{
	//! The EMS extension chunk.  An optional chunk.
	EMSWAVEEXTCHUNK		extChunk;

} EMSWAVERIFF;

#pragma pack(pop)

#endif