/********************************************************************
*	Module:			sigproc.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	 Signal processing lib interface
*
*					 
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	Copyright (c) 2001-2005 by EMS Technologies, Inc.,
*					All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth			Changes
	===	====			=============	=======

	0.0	2002/05/16		RVW				Start
	0.1 2006/11/20		RVW				added Intel PP support

********************************************************************/
#include <stdio.h>

#include "sigproc.h"
#include "emsexcpt.h"
#include "emsDBF.h"
#include "LogMsgParam.h"

const int c_emsNoScaleFactor = 0;

BOOL CEMSSignalProcLib::m_bInitialized = FALSE;	

#if defined (EMS_USE_INTEL_SPL)

void emssbCopy( const float  *lpfSrc, float  *lpfDest, int nCount )
{
	if ( nCount > 0 )
		nspsbCopy( lpfSrc, lpfDest, nCount );
	else
		throw CEMSException( EMS_SBCOPY_ZERO_LENGTH );
}

void emscbCopy( const EMSCOMPLEX  *lpfSrc, EMSCOMPLEX  *lpfDest, int nCount )
{
	if ( nCount > 0 )
		nspcbCopy( lpfSrc, lpfDest, nCount );
	else
		throw CEMSException( EMS_CBCOPY_ZERO_LENGTH );
}

void emswbCopy( const short *lpfSrc, short *lpfDest, int nCount )
{
	if ( nCount > 0 )
		nspwbCopy( lpfSrc, lpfDest, nCount );
	else
		throw CEMSException( EMS_WBCOPY_ZERO_LENGTH );
}

static NSPStatus __stdcall _nspErrorCallback( NSPStatus status, const char* lpcszFunc, const char *lpcszContext, const char *file, int line )
{
	if ( status == NSP_StsOk )
	{
		return status;
	}
	else
	{
		EMS_RESULT hrSubcode = EMS_UNKNOWN_ERROR;

		switch ( status )
		{
			case NSP_StsBackTrace: //     -1         /* pseudo error for back trace     */
				break;

			case NSP_StsInternal: //      -3         /* internal error (bad state)      */
				break;

			case NSP_StsNoMem: //         -4         /* out of memory                   */
				hrSubcode = EMS_NO_MEMORY;
				break;

			case NSP_StsBadArg: //        -5         /* function arg/param is bad       */
				hrSubcode = EMS_BAD_PARAM;
				break;

			case NSP_StsBadFunc: //       -6         /* unsupported function            */
				break;

			case NSP_StsNoConv: //        -7         /* iter. didn't converge           */
				break;

			case NSP_StsAutoTrace: //     -8         /* Tracing through nsptrace.h      */
				break;

			case NSP_StsError: //         -2         /* unknown /unspecified error      */
			default:
				break;
		}
		nspSetErrStatus( status );

		CEMSLogMsgParam	param;
		param.Add( lpcszFunc );
		param.Add( lpcszContext );
		throw CEMSException( __LINE__, TEXT(__FILE__), EMS_EXCEPTION_CONTEXT, param, hrSubcode );

//		TCHAR szComment[ 256 ];
//		sprintf( szComment, TEXT( "%s : %s" ), lpcszFunc, lpcszContext );
//		throw CEMSException( szComment, (EMS_RESULT)0x300, hrSubcode );
	}

}

void CEMSSignalProcLib::Initialize( void )
{
	if ( !m_bInitialized )
	{
		nspRedirectError( _nspErrorCallback );

		m_bInitialized = TRUE;
	}
}

void CEMSSignalProcLib::Release( void )
{
	if ( m_bInitialized )
	{
		nspRedirectError( 0 );

		m_bInitialized = FALSE;
	}
}

#elif defined (EMS_USE_INTEL_PP )

#include <math.h>

void _emsIppException( IppStatus retCode, int nLine, LPCTSTR lpcszFile )
{
	switch ( retCode )
	{
		case ippStsNoErr:
			break;

		default:
			throw CEMSException( nLine, lpcszFile );
	}
}

void emssbCopy( const float  *lpfSrc, float  *lpfDest, int nCount )
{
	if ( nCount > 0 )
		ippsCopy_32f( lpfSrc, lpfDest, nCount );
	else
		throw CEMSException( EMS_SBCOPY_ZERO_LENGTH );
}

void emscbCopy( const EMSCOMPLEX  *lpfSrc, EMSCOMPLEX  *lpfDest, int nCount )
{
	if ( nCount > 0 )
		ippsCopy_32fc( lpfSrc, lpfDest, nCount );
	else
		throw CEMSException( EMS_CBCOPY_ZERO_LENGTH );
}

void emswbCopy( const short *lpfSrc, short *lpfDest, int nCount )
{
	if ( nCount > 0 )
		ippsCopy_16s( lpfSrc, lpfDest, nCount );
	else
		throw CEMSException( EMS_WBCOPY_ZERO_LENGTH );
}


void emssbZero( const float  *src, int n )
{
	IppStatus retCode = ippsZero_32f( (float*)src, n );

	if ( ippStsNoErr != retCode )
		_emsIppException( retCode, __LINE__, TEXT(__FILE__) );
}

void emscbZero( const EMSCOMPLEX  *src, int n )
{
	IppStatus retCode = ippsZero_32fc( (EMSCOMPLEX*)src, n );

	if ( ippStsNoErr != retCode )
		_emsIppException( retCode, __LINE__, TEXT(__FILE__) );
}

void emswbZero( const short *src, int n )
{
	IppStatus retCode = ippsZero_16s( (short*)src, n );

	if ( ippStsNoErr != retCode )
		_emsIppException( retCode, __LINE__, TEXT(__FILE__) );
}

void CEMSSignalProcLib::Initialize( void )
{
	if ( !m_bInitialized )
	{
//		nspRedirectError( _nspErrorCallback );

		m_bInitialized = TRUE;
	}
}

void CEMSSignalProcLib::Release( void )
{
	if ( m_bInitialized )
	{
//		nspRedirectError( 0 );

		m_bInitialized = FALSE;
	}
}

void emswbSub1( const short val, short *dst, int n, int nScaleMode, int *lpnScaleFactor )
{
	IppStatus status = ippStsAacSfValErr;  // unsupported Scale Factor

	switch ( nScaleMode & 0xFFFE )
	{
		case EMS_SPL_NO_SCALE:
			status = ippsSubC_16s_I( val, dst, n );
			break;

		case EMS_SPL_FIXED_SCALE:
			status = ippsSubC_16s_ISfs( val, dst, n , *lpnScaleFactor );
			break;

		case EMS_SPL_AUTO_SCALE:
			break;

		default:
			break;
	}

	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );
}

void emssbSub1( const float val, float *dst, int n )
{
	IppStatus status = ippsSubC_32f_I(val, dst, n );

	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );
}

void emssbSub3( const float *src, const float *val, float *dst, int n )
{
	IppStatus status = ippsSub_32f( src, val, dst, n );

	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );
}


void emssbAdd1( const float val, float *dst, int n )
{
	IppStatus status = ippsAddC_32f_I(val, dst, n );

	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );
}

void emssbAdd2( const float *src, float *dst, int n )
{
	IppStatus status = ippsAdd_32f_I( src, dst, n );

	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );
}

void emssbAdd3( const float *srcA, const float *srcB, float *dst, int n )
{
	IppStatus status = ippsAdd_32f( srcA, srcB, dst, n );

	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );
}


void emscbMpy1( const EMSCOMPLEX val, EMSCOMPLEX *dst, int n )
{
	IppStatus status = ippsMulC_32fc_I( val, dst, n );

	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );
}


void emssbMpy1( const float val, float *dst, int n )
{
	IppStatus status = ippsMulC_32f_I( val, dst, n );

	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );
}

void emswbMpy1( const short val, short *dst, int n, int nScaleMode, int *lpnScaleFactor )
{
	IppStatus status = ippStsAacSfValErr;  // unsupported Scale Factor

	switch ( nScaleMode & 0xFFFE )
	{
		case EMS_SPL_NO_SCALE:
			status = ippsMulC_16s_I( val, dst, n );
			break;

		case EMS_SPL_FIXED_SCALE:
			status = ippsMulC_16s_ISfs( val, dst, n , *lpnScaleFactor );
			break;

		case EMS_SPL_AUTO_SCALE:
			break;

		default:
			break;
	}

	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );
}

void emssbMpy2( const float *src, float *dst, int n)
{
	IppStatus status = ippsMul_32f_I( src, dst, n );

	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );
}

void emssbMpy3( const float *srcA, const float *srcB, float *dst, int n)
{
	IppStatus status = ippsMul_32f( srcA, srcB, dst, n );

	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );
}

void emscbMpy2( const EMSCOMPLEX *src, EMSCOMPLEX *dst, int n)
{
	IppStatus status = ippsMul_32fc_I( src, dst, n );

	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );
}

void emscbMpy3( const EMSCOMPLEX *srcA, const EMSCOMPLEX *srcB, EMSCOMPLEX *dst, int n)
{
	IppStatus status = ippsMul_32fc( srcA, srcB, dst, n );

	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );
}


EMSCOMPLEX emscDotProd(const EMSCOMPLEX *srcA, const EMSCOMPLEX *srcB, int len)
{
	EMSCOMPLEX result;
	IppStatus status = ippsDotProd_32fc( srcA, srcB, len, &result );
	
	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );

	return result;
}

EMSCOMPLEXD emscDotProdv2(const EMSCOMPLEXD *srcA, const EMSCOMPLEXD *srcB, int len)
{
	EMSCOMPLEXD result;
	//IppStatus status = ippsDotProd_64fc( srcA, srcB, len, &result );
	IppStatus status = ippsDotProd_32fc( srcA, srcB, len, &result );

	
	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );

	return result;
}

short emswDotProd(const short  *srcA, const short  *srcB, int len,
                                   int nScaleMode, int *lpnScaleFactor)
{
	short wResult=0;
	IppStatus status = ippStsAacSfValErr;  // unsupported Scale Factor

	switch ( nScaleMode & 0xFFFE )
	{
		case EMS_SPL_NO_SCALE:
			status = ippsDotProd_16s_Sfs( srcA, srcB, len, &wResult, c_emsNoScaleFactor );
			break;

		case EMS_SPL_FIXED_SCALE:
			status = ippsDotProd_16s_Sfs( srcA, srcB, len, &wResult, *lpnScaleFactor );
			break;

		case EMS_SPL_AUTO_SCALE:
			break;

		default:
			break;
	}

	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );

	return wResult;
}

float emssDotProd(const float  *srcA, const float  *srcB, int len)
{
	float fResult = 0.0;

	IppStatus status = ippsDotProd_32f( srcA, srcB, len, &fResult );
	
	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );

	return fResult;
}

double emssDotProd64(const double  *srcA, const double  *srcB, int len)
{
	double fResult = 0.0;

	IppStatus status = ippsDotProd_64f( srcA, srcB, len, &fResult );
	
	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );

	return fResult;
}

void emssbAbs1( float *vec, int len)
{
	IppStatus status = ippsAbs_32f_I( vec, len );

	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );
}


void emsvbReal(const EMSWCOMPLEX *src,short  *dst,int length)
{
	IppStatus status = ippsReal_16sc( src, dst, length );

	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );
}

void emsvbImag(const EMSWCOMPLEX *src,short  *dst,int length)
{
	IppStatus status = ippsImag_16sc( src, dst, length );

	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );
}


void emscbConj1( EMSCOMPLEX *vec, int n)
{
	IppStatus status = ippsConj_32fc_I( vec, n);

	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );
}

void emscbConj2( const EMSCOMPLEX *src, EMSCOMPLEX *dst, int n)
{
	IppStatus status = ippsConj_32fc( src, dst, n );

	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );
}

void emscbConj2d( const EMSCOMPLEXD *src, EMSCOMPLEXD *dst, int n)
{
	//IppStatus status = ippsConj_64fc( src, dst, n );
	IppStatus status = ippsConj_32fc( src, dst, n );

	/*if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );*/
}


void emssbFloatToInt(const float  *src, void *dst, int len, int wordSize, int flags)
{
	IppStatus status = ippStsNotSupportedModeErr;
	IppRoundMode rndMode = ( flags & EMS_SPL_TruncZero ) ? ippRndZero : ippRndNear;
	bool bUnsigned = EMS_SPL_Unsigned == ( flags & EMS_SPL_Unsigned );

	switch ( wordSize )
	{
		case 8:
			if ( bUnsigned )
				status = ippsConvert_32f8u_Sfs( src, (unsigned char*)dst, len, rndMode, c_emsNoScaleFactor );
			else
				status = ippsConvert_32f8s_Sfs( src, (signed char *)dst, len, rndMode, c_emsNoScaleFactor );
			break;

		case 16:
			if ( bUnsigned )
				status = ippsConvert_32f16u_Sfs( src, (unsigned short*)dst, len, rndMode, c_emsNoScaleFactor );
			else
				status = ippsConvert_32f16s_Sfs( src, (short *)dst, len, rndMode, c_emsNoScaleFactor );
			break;

		case 32:
			status = ippsConvert_32f32s_Sfs( src, (int *)dst, len, rndMode, c_emsNoScaleFactor );
			break;

		default:
			break;
	}


	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );
}


void emssbIntToFloat(const void *src, float  *dst, int len, int wordSize, int flags)
{
	IppStatus status = ippStsNotSupportedModeErr;
	bool bUnsigned = EMS_SPL_Unsigned == ( flags & EMS_SPL_Unsigned );

	switch ( wordSize )
	{
		case 8:
			if ( bUnsigned )
				status = ippsConvert_8u32f( (unsigned char *)src, dst, len );
			else
				status = ippsConvert_8s32f( (signed char *)src, dst, len );
			break;

		case 16:
			if ( bUnsigned )
				status = ippsConvert_16u32f( (unsigned short *)src, dst, len );
			else
				status = ippsConvert_16s32f( (short *)src, dst, len ) ;
			break;

		case 32:
			status = ippsConvert_32s32f( (int*)src, dst, len );
			break;

		default:
			break;
	}


	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );
}


float emssMax(const float *vec, int len)
{
	float fResult = 0.0;
	IppStatus status = ippsMax_32f( vec, len, &fResult );

	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );

	return fResult;
}


float emssMaxExt(const float  *vec, int len, int* index)
{
	float fResult = 0.0;
	IppStatus status = ippsMaxIndx_32f( vec, len, &fResult, index );

	if ( ippStsNoErr != status ) 
		_emsIppException( status, __LINE__, TEXT(__FILE__) );

	return fResult;
}


float emssMinExt(const float  *vec, int len, int* index)

{
	float fResult = 0.0;
	IppStatus status = ippsMinIndx_32f( vec, len, &fResult, index );

	if ( ippStsNoErr != status ) 
		_emsIppException( status, __LINE__, TEXT(__FILE__) );

	return fResult;
}

void emscbMag(const EMSCOMPLEX *src,float *mag,int length)
{
	IppStatus status = ippsMagnitude_32fc( src, mag, length );

	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );
}


void emscbPowerSpectr(const EMSCOMPLEX *src, float *spectr,int length)
{
	IppStatus status = ippsPowerSpectr_32fc( src, spectr, length );

	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );
}


float emssMean(const float *vec, int len)
{
	float fResult = 0.0;
	IppStatus status = ippsMean_32f( vec, len, &fResult, ippAlgHintNone );

	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );

	return fResult;
}


short emswMean(const short *vec, int len)
{
	short nResult = 0;
	IppStatus status = ippsMean_16s_Sfs( vec, len, &nResult, c_emsNoScaleFactor );

	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );

	return nResult;
}

float emssStdDev(const float *vec, int len)
{
	float fResult = 0.0;
	IppStatus status = ippsStdDev_32f( vec, len, &fResult, ippAlgHintNone );

	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );

	return fResult;
}

void emssbSet(float val, float *dst, int n)
{
	IppStatus status = ippsSet_32f( val, dst, n );

	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );
}

void emssbLn2(const float  *src, float  *dst, int len)
{
	IppStatus status = ippsLn_32f( src, dst, len );

	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );
}

void emswbrPhase(const short  *srcReal,const short *srcImag, short *phase, int length)
{
	IppStatus status = ippsPhase_16s_Sfs( srcReal, srcImag, phase, length, c_emsNoScaleFactor );

	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );
}


void emscbPhase(const EMSCOMPLEX *src,float  *phase,int length)
{
	IppStatus status = ippsPhase_32fc( src, phase, length );

	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );
}


void emssbThresh1(float  *vec, int len, float  thresh, int relOp)
{
	IppStatus status =  ippStsNotSupportedModeErr;

	switch ( relOp )
	{
	case EMS_SPL_GT:
		status = ippsThreshold_GT_32f_I( vec, len, thresh );
		break;

	case EMS_SPL_LT:
		status = ippsThreshold_LT_32f_I( vec, len, thresh );
		break;

	default:
		break;
	}

	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );
}

void emssbThresh2(const float  *src,    float  *dst,int len,
                                float   thresh, int     relOp)
{
		IppStatus status =  ippStsNotSupportedModeErr;

	switch ( relOp )
	{
	case EMS_SPL_GT:
		status = ippsThreshold_GT_32f( src, dst, len, thresh );
		break;

	case EMS_SPL_LT:
		status = ippsThreshold_LT_32f( src, dst, len, thresh );
		break;

	default:
		break;
	}

	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );
}


void emssbInvThresh1(float  *vec, int len, float  thresh)
{
	IppStatus status = ippsThreshold_LTInv_32f_I( vec, len, thresh );

	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );
}


void emscFirInit(const EMSCOMPLEX *tapVals, int          tapsLen,
                          const EMSCOMPLEX *dlyVals, NSPFirState *statePtr)
{
	if ( statePtr )
	{
		memset( statePtr, 0, sizeof( NSPFirState ) );

		IppStatus status = ippsFIRInitAlloc_32fc( &(statePtr->pState), 
										tapVals, tapsLen, dlyVals );

		if ( ippStsNoErr == status )
			statePtr->wFirType = 0x32FC;
		else
			_emsIppException( status, __LINE__, TEXT(__FILE__) );
	}
	else
		_emsIppException( ippStsNotSupportedModeErr, __LINE__, TEXT(__FILE__) );
}


void emscbFir(NSPFirState *statePtr,const EMSCOMPLEX *inSamps,
                       EMSCOMPLEX *outSamps, int numIters)
{
	if ( statePtr && ( 0x32FC == statePtr->wFirType ) )
	{
		IppStatus status = ippsFIR_32fc( inSamps, outSamps, numIters, statePtr->pState );

		if ( ippStsNoErr != status )
			_emsIppException( status, __LINE__, TEXT(__FILE__) );
	}
	else
		_emsIppException( ippStsNotSupportedModeErr, __LINE__, TEXT(__FILE__) );
}

void emsFirFree(NSPFirState *statePtr )
{
	IppStatus status = ippStsNoErr;

	if ( statePtr )
	{
		switch ( statePtr->wFirType )
		{
			case 0x32FC:
				ippsFree( statePtr->pState );
				statePtr->pState = 0;
				break;
		}
		statePtr->wFirType = 0;
	}
}

void emssCcsFftNip(const EMSCOMPLEX *inSamps, float  *outSamps,
                                 int    order,   int     flags)
{
	// ****** IMPLEMENT ********
	// ****** IMPLEMENT ********
	// ****** IMPLEMENT ********

	_emsIppException( ippStsNotSupportedModeErr, __LINE__, TEXT(__FILE__) );
}


void emswDownSample(const short* src, const int srcLen,
                           short  *dst, int* dstLen, const int factor, int* phase)
{

	// ****** IMPLEMENT ********
	// ****** IMPLEMENT ********
	// ****** IMPLEMENT ********

	_emsIppException( ippStsNotSupportedModeErr, __LINE__, TEXT(__FILE__) );
}


void emscFft(EMSCOMPLEX *samps, int order, int flags)
{
	IppStatus status = ippStsNoErr;
	
	int nFlags = IPP_FFT_NODIV_BY_ANY;

	if( EMS_SPL_FWD == flags )
	{
//		nFlags = IPP_FFT_DIV_FWD_BY_N;
	}
	else if( EMS_SPL_INV == flags )
	{
//		nFlags = IPP_FFT_DIV_FWD_BY_N;
	}


	IppsFFTSpec_C_32fc *pSpec = 0;

	status = ippsFFTInitAlloc_C_32fc( &pSpec, order, nFlags, ippAlgHintNone );

	if ( ippStsNoErr == status )
	{
		if( EMS_SPL_FWD == flags )
		{
			status = ippsFFTFwd_CToC_32fc_I(samps, pSpec, NULL);
		}
		else if( EMS_SPL_INV == flags )
		{
			status = ippsFFTInv_CToC_32fc_I(samps, pSpec, NULL);
		}
		else
		{
			_emsIppException( ippStsNotSupportedModeErr, __LINE__, TEXT(__FILE__) );
		}

		if ( ippStsNoErr != status )
			_emsIppException( status, __LINE__, TEXT(__FILE__) );
		
		if ( pSpec )
			ippsFree( pSpec );
	}
}


void emssRealFftNip(const float  *inSamps,  EMSCOMPLEX *outSamps,
                                  int     order,    int    flags)
{
	IppStatus status = ippStsNoErr;
	
	int nFlags = IPP_FFT_NODIV_BY_ANY;

	if( EMS_SPL_FWD == flags )
	{
//		nFlags = IPP_FFT_DIV_FWD_BY_N;
	}
	else if( EMS_SPL_INV == flags )
	{
//		nFlags = IPP_FFT_DIV_INV_BY_N;
	}

	IppsFFTSpec_R_32f *pSpec = NULL;


	status = ippsFFTInitAlloc_R_32f( &pSpec, order, nFlags, ippAlgHintNone );

	if ( ippStsNoErr == status )
	{

		if( EMS_SPL_FWD == flags )
		{
			status = ippsFFTFwd_RToCCS_32f( inSamps, (Ipp32f*) outSamps, pSpec, NULL );
		}
		else if( EMS_SPL_INV == flags )
		{
			status = ippsFFTInv_CCSToR_32f( inSamps, (Ipp32f*) outSamps, pSpec, NULL );
		}
		else
		{
			_emsIppException( ippStsNotSupportedModeErr, __LINE__, TEXT(__FILE__) );
		}

		if ( ippStsNoErr != status )
			_emsIppException( status, __LINE__, TEXT(__FILE__) );
		
		if ( pSpec )
		{
			ippsFree( pSpec );
			pSpec = NULL;
		}

		if ( ippStsNoErr != status )
			_emsIppException( status, __LINE__, TEXT(__FILE__) );

	}
}

void emscFftNip(const EMSCOMPLEX *inSamps,  EMSCOMPLEX *outSamps,
                              int    order,    int     flags)
{
	IppStatus status = ippStsNoErr;
	
	int nFlags = IPP_FFT_NODIV_BY_ANY;

	if( EMS_SPL_FWD == flags )
	{
//		nFlags = IPP_FFT_DIV_FWD_BY_N;
	}
	else if( EMS_SPL_INV == flags )
	{
		//nFlags = IPP_FFT_DIV_FWD_BY_N;
//		nFlags = IPP_FFT_DIV_BY_SQRTN;
	}


	IppsFFTSpec_C_32fc *pSpec = 0;

	status = ippsFFTInitAlloc_C_32fc( &pSpec, order, nFlags, ippAlgHintNone );

	if ( ippStsNoErr == status )
	{
		if( EMS_SPL_FWD == flags )
		{
			status = ippsFFTFwd_CToC_32fc( inSamps, outSamps, pSpec, NULL );
		}
		else if( EMS_SPL_INV == flags )
		{
			status = ippsFFTInv_CToC_32fc( inSamps, outSamps, pSpec, NULL );
		}
		else
		{
			_emsIppException( ippStsNotSupportedModeErr, __LINE__, TEXT(__FILE__) );
		}

		if ( ippStsNoErr != status )
			_emsIppException( status, __LINE__, TEXT(__FILE__) );
		
		if ( pSpec )
			ippsFree( pSpec );
	}
}

//--------------------------------------------------------------------------------------------------
// New routines for DBF

void emscbAdd2( const EMSCOMPLEX *src, EMSCOMPLEX *dst, int n )
{
	IppStatus status = ippsAdd_32fc_I( src, dst, n );

	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );
}

void emscbMul2( const EMSCOMPLEX *src, EMSCOMPLEX *dst, int n )
{
	IppStatus status = ippsMul_32fc_I( src, dst, n );

	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );
}


void emscbMul3( const EMSCOMPLEX *src1, const EMSCOMPLEX *src2, EMSCOMPLEX *dst, int n )
{
	IppStatus status = ippsMul_32fc( src1, src2, dst, n );

	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );
}



void emssbNormalize( const float *src, float *dst, int n, const float valuesub, const float valuediv )
{
	IppStatus status = ippsNormalize_32f( src, dst, n, valuesub, valuediv);

	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );
}

void emssbMatrixInverse( const float *src, float *dst, int n )
{
	float* tempbuffer = new float[ n * n + n ];

	IppStatus status = ippmInvert_m_32f( src, n * sizeof(float), sizeof(float),
		tempbuffer, dst, n * sizeof(float), sizeof(float), n);

	if ( tempbuffer )
	{
		delete [] tempbuffer;
		tempbuffer = NULL;
	}
	
	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );

}

void emssbMatrixInverseD( const double  *src, double *dst, int n )
{
	double* tempbuffer = new double[ n * n + n ];
	
	IppStatus status = ippmInvert_m_64f( src, n * sizeof(double), sizeof(double),
		tempbuffer, dst, n * sizeof(double), sizeof(double), n);

	if ( tempbuffer )
	{
		delete [] tempbuffer;
		tempbuffer = NULL;
	}

	if ( ippStsNoErr != status )
		_emsIppException( status, __LINE__, TEXT(__FILE__) );
}

void emscbMatrixTranspose( const EMSCOMPLEX *src, EMSCOMPLEX *dst, int n, int m )
{
	int k = 0;
	for ( int i = 0; i < n; i++ )
	{
		for ( int j = 0; j < m; j++ )
		{
			dst[k++] = src[j*n + i];
		}
	}

}
void emscbMatrixTransposed( const EMSCOMPLEXD *src, EMSCOMPLEXD *dst, int n, int m )
{
	int k = 0;
	for ( int i = 0; i < n; i++ )
	{
		for ( int j = 0; j < m; j++ )
		{
			dst[k++] = src[j*n + i];
		}
	}

}
void emssbMatrixTranspose( const float *src, float *dst, int n, int m )
{
	int k = 0;
	for ( int i = 0; i < n; i++ )
	{
		for ( int j = 0; j < m; j++ )
		{
			dst[k++] = src[j*n + i];
		}
	}
}

void emscbMatrixMultiply( const EMSCOMPLEX *src1, int m1, int n1, const EMSCOMPLEX *src2, int m2, int n2, EMSCOMPLEX *dst )
{

	if ( n1 == m2 )
	{
		EMSCOMPLEX* scr2Transpose = new EMSCOMPLEX [ m2 * n2 ];

		emscbMatrixTranspose( src2, scr2Transpose, m2, n2);

		int k = 0;

		for ( int i = 0; i < m1*n1; i+= n1 )
		{
			for ( int j = 0; j < n2*m2; j+= m2 )
			{
				dst[k++] = emscDotProd( &src1[i], &scr2Transpose[j], n1 );
			}
		}

		if ( scr2Transpose )
		{
			delete [] scr2Transpose;
			scr2Transpose = NULL;
		}

	}
	else
	{
		IppStatus status = ippStsSizeMatchMatrixErr;
		_emsIppException( status, __LINE__, TEXT(__FILE__) );
	}

}

//Sichuns version 13th Jan,2021
void emscbMatrixMultiplyd( const EMSCOMPLEXD *src1, int m1, int n1, const EMSCOMPLEXD *src2, int m2, int n2, EMSCOMPLEXD *dst )
{

	if ( n1 == m2 )
	{
		EMSCOMPLEXD* scr2Transpose = new EMSCOMPLEXD [ m2 * n2 ];

		emscbMatrixTransposed( src2, scr2Transpose, n2, m2);

		int k = 0;

		for ( int i = 0; i < m1*n1; i+= n1 )
		{
			for ( int j = 0; j < n2*m2; j+= m2 )
			{
				dst[k++] = emscDotProdv2( &src1[i], &scr2Transpose[j], n1 );
			}
		}

		if ( scr2Transpose )
		{
			delete [] scr2Transpose;
			scr2Transpose = NULL;
		}

	}
	else
	{
		IppStatus status = ippStsSizeMatchMatrixErr;
		_emsIppException( status, __LINE__, TEXT(__FILE__) );
	}

}


EMSCOMPLEXD _CAdd ( EMSCOMPLEXD cData1, EMSCOMPLEXD cData2 )
{
	EMSCOMPLEXD cOutput;
	cOutput.re = cData1.re + cData2.re ;
	cOutput.im = cData1.im + cData2.im;
	return cOutput;
}
EMSCOMPLEXD _CMultiply ( EMSCOMPLEXD cData1, EMSCOMPLEXD cData2 )
{
	EMSCOMPLEXD cOutput;
	cOutput.re = cData1.re * cData2.re - cData1.im * cData2.im;
	cOutput.im = cData1.re * cData2.im + cData1.im * cData2.re;;
	return cOutput;
}


EMSCOMPLEXD _CSub ( EMSCOMPLEXD cData1, EMSCOMPLEXD cData2 )
{
	EMSCOMPLEXD cOutput;
	cOutput.re = cData1.re - cData2.re ;
	cOutput.im = cData1.im - cData2.im;
	return cOutput;
}

EMSCOMPLEXD _CDivide ( EMSCOMPLEXD& cData)
{
	EMSCOMPLEXD cOutput;
	double dMagnitude = cData.re * cData.re + cData.im * cData.im;
	cOutput.re = cData.re/dMagnitude;
	cOutput.im = -cData.im/dMagnitude;
	return cOutput;
}
EMS_RESULT
_ComplexMatrix2x2Inverse( EMSCOMPLEXD* acMatrix, EMSCOMPLEXD* acMatrixInverse )
{
	EMS_RESULT hr = EMS_OK;
	EMSCOMPLEXD cDATA1 = _CMultiply (  acMatrix[0],  acMatrix[3] );
	EMSCOMPLEXD cDATA2 = _CMultiply (  acMatrix[1],  acMatrix[2] );
	cDATA1 = _CSub( cDATA1, cDATA2 );
	cDATA1 = _CDivide( cDATA1 );
	cDATA2.re = -cDATA1.re;
	cDATA2.im = -cDATA1.im;
	acMatrixInverse[0] = _CMultiply(acMatrix[3], cDATA1 );
	acMatrixInverse[1] = _CMultiply(acMatrix[1], cDATA2 );
	acMatrixInverse[2] = _CMultiply(acMatrix[2], cDATA2 );
	acMatrixInverse[3] = _CMultiply(acMatrix[0], cDATA1 );
	return hr;
}
EMS_RESULT
_CMultipy2x2( EMSCOMPLEXD* cM1, EMSCOMPLEXD* cM2, EMSCOMPLEXD* cM3)
{
	EMS_RESULT hr = EMS_OK;
	memset( cM3, 0, 4*sizeof(EMSCOMPLEXD) );

	cM3[0] = _CAdd( _CMultiply( cM1[0], cM2[0]) , _CMultiply( cM1[1], cM2[2]) );
	cM3[1] = _CAdd( _CMultiply( cM1[0], cM2[1]) , _CMultiply( cM1[1], cM2[3]) );
	cM3[2] = _CAdd( _CMultiply( cM1[2], cM2[0]) , _CMultiply( cM1[3], cM2[2]) );
	cM3[3] = _CAdd( _CMultiply( cM1[2], cM2[1]) , _CMultiply( cM1[3], cM2[3]) );

	return hr;
}
EMS_RESULT
_ComplexMatrix4x4Inverse( EMSCOMPLEXD* acMatrix, EMSCOMPLEXD* acMatrixInverse )
{

//
//  M = [ A, B ; C, D]

//  inv(M) = [ W+ZX, -Z; -YX, Y ]

//  W = inv(A)
//  X = CW
//  Y = inv(D-XB)
//  Z = WBY

	EMS_RESULT hr = EMS_OK;
	EMSCOMPLEXD cA[4] = { acMatrix[0], acMatrix[1], acMatrix[4], acMatrix[5] };
	EMSCOMPLEXD cB[4] = { acMatrix[2], acMatrix[3], acMatrix[6], acMatrix[7] };
	EMSCOMPLEXD cC[4] = { acMatrix[8], acMatrix[9], acMatrix[12],acMatrix[13] };
	EMSCOMPLEXD cD[4] = { acMatrix[10],acMatrix[11],acMatrix[14],acMatrix[15] };
	//EMSCOMPLEXD
	EMSCOMPLEXD cW[4];
	EMSCOMPLEXD cX[4];
	EMSCOMPLEXD cY[4];
	EMSCOMPLEXD cZ[4];
	EMSCOMPLEXD cTemp[4];
	EMSCOMPLEXD cOut[16];
	EMSCOMPLEXD cMinus;

	int iIndex[16] = { 0,1,4,5,2,3,6,7,8,9,12,13,10,11,14,15};
	cMinus.re = -1.0;
	cMinus.im = 0.0;

	hr = _ComplexMatrix2x2Inverse( cA, cW );
	hr = _CMultipy2x2( cC, cW, cX);
	hr = _CMultipy2x2( cX, cB, cTemp);

	for( int i = 0; i < 4; i++ )
	{
		cTemp[i] = _CSub ( cD[i] ,  cTemp[i] );
	}

	hr = _ComplexMatrix2x2Inverse( cTemp, cY );

	hr = _CMultipy2x2( cB, cY, cTemp);
	hr = _CMultipy2x2( cW, cTemp, cZ);

	hr = _CMultipy2x2( cZ, cX, cTemp);

	for( int i = 0; i < 4; i++ )
	{
		cOut[i] = _CAdd ( cW[i] ,  cTemp[i] );
	}

	for( int i = 4; i < 8; i++ )
	{
		cOut[i] = _CMultiply( cMinus, cZ[i-4] );
	}

	hr = _CMultipy2x2( cY, cX, cTemp );

	for( int i = 8; i < 12; i++ )
	{
		cOut[i] = _CMultiply( cMinus, cTemp[i-8]);
	}

	for( int i = 12; i < 16; i++ )
	{
		cOut[i] = cY[i-12];
	}

	for( int i = 0; i < 16; i++ )
	{
		acMatrixInverse[i] = cOut[iIndex[i]];
	}

	emscbMatrixMultiplyd( acMatrix, 4, 4, acMatrixInverse, 4, 4, cOut );

	return hr;
}

void
_EMSsbNormalize( const float *src, float *dst, ULONG n, const float valuesub, const float valuediv )
{
	if( src && dst )
	{
		for( ULONG i = 0; i < n; i++ )
		{
			dst[i] = ( src[i] -  valuesub ) / valuediv;
		}
	}
}


double
_EMScMeanStdDev(const EMSCOMPLEXD *vec, ULONG len, EMSCOMPLEXD* pfMean )
{
	double fStdDev = 0.0;
	EMSCOMPLEXD fSum, fMean;
	
	fSum.re =0.0;
	fSum.im =0.0;
	fMean.re =0.0;
	fMean.im =0.0;
	
    ULONG i;

    for(i = 0; i < len; ++i)
    {
        fSum.re += vec[i].re;
		fSum.im += vec[i].im;
    }

    fMean.re = fSum.re/(float)len;
	fMean.im = fSum.im/(float)len;
	*pfMean = fMean;

    fStdDev = 0.0;
    for(i = 0; i < len; ++i)
        fStdDev += ( pow(vec[i].re - fMean.re, 2) + pow(vec[i].im - fMean.im, 2)    );

    return sqrt(fStdDev / (float)(len-1));
}

double
_EMSsMeanStdDev(const float *vec, ULONG len, double* pfMean )
{
	double fSum = 0.00;
	double fMean = 0.00; 
	double fStdDev = 0.00;

    ULONG i;

    for(i = 0; i < len; ++i)
    {
        fSum += vec[i];
    }

    fMean = fSum/len;
	*pfMean = fMean;

    for(i = 0; i < len; ++i)
        fStdDev += pow(vec[i] - fMean, 2);

    return sqrt(fStdDev / len);
}



void
_EMScNormalize( const EMSCOMPLEXD *src, EMSCOMPLEXD *dst, ULONG n, const EMSCOMPLEXD& valuesub, const float valuediv )
{
	if( src && dst )
	{
		for( ULONG i = 0; i < n; i++ )
		{
			dst[i].re = ( src[i].re -  valuesub.re ) / valuediv;
			dst[i].im = ( src[i].im -  valuesub.im ) / valuediv;
		}
	}
}

void emsbMatrixMultiply( const float *src1, int m1, int n1, const float *src2, int m2, int n2, float *dst )
{

	if ( n1 == m2 )
	{
		float* scr2Transpose = new float [ m2 * n2 ];

		emssbMatrixTranspose( src2, scr2Transpose, n2, m2 );

		int k = 0;

		for ( int i = 0; i < m1*n1; i+= n1 )
		{
			for ( int j = 0; j < n2*m2; j+= m2 )
			{
				dst[k++] = emssDotProd( &src1[i], &scr2Transpose[j], n1 );
			}
		}

		if ( scr2Transpose )
		{
			delete [] scr2Transpose;
			scr2Transpose = NULL;
		}

	}
	else
	{
		IppStatus status = ippStsSizeMatchMatrixErr;
		//_emsIppException( status, __LINE__, TEXT(__FILE__) );
	}

}
EMS_RESULT
_ComplexMatrixNxNInverse( EMSCOMPLEXD* acMatrix, EMSCOMPLEXD* acMatrixInverse, ULONG ulMSize  )
{
	
	EMS_RESULT hr = EMS_OK;
	

	if (ulMSize > DBF_MAX_SATELLITES)
	{
		hr = EMS_FALSE;
	}
	else
	{
		// The following equations provide the complex matrix inverse
		//
		// z = A + i*C
		// z inverse = y00 + i*y10

		// Define:
		//
		//	r0 = inv(A)*C
		//  r1 = C*r0
		//  y11 = inv(r1 + A)
		//  y00 = y11;
		//  y01 = r0*y11
		//  y10 = -y01

		float A[DBF_MAX_SATELLITES*DBF_MAX_SATELLITES];
		float C[DBF_MAX_SATELLITES*DBF_MAX_SATELLITES];
		float r0[DBF_MAX_SATELLITES*DBF_MAX_SATELLITES];
		float r1[DBF_MAX_SATELLITES*DBF_MAX_SATELLITES];
		float AI[DBF_MAX_SATELLITES*DBF_MAX_SATELLITES];
		float y00[DBF_MAX_SATELLITES*DBF_MAX_SATELLITES];
		float y10[DBF_MAX_SATELLITES*DBF_MAX_SATELLITES];
		float y01[DBF_MAX_SATELLITES*DBF_MAX_SATELLITES];
		float y11[DBF_MAX_SATELLITES*DBF_MAX_SATELLITES];

		for ( ULONG i = 0; i < ulMSize*ulMSize; i++ )
		{
			A[i] = acMatrix[i].re;
			C[i] = acMatrix[i].im;
		}

		emssbMatrixInverse(  A, AI, ulMSize );

		emsbMatrixMultiply( AI, ulMSize, ulMSize, C, ulMSize, ulMSize, r0 );

		emsbMatrixMultiply( C, ulMSize, ulMSize, r0, ulMSize, ulMSize, r1 );

		emssbAdd3( r1, A, y10, ulMSize*ulMSize );
		emssbMatrixInverse(  y10, y11, ulMSize );

		emsbMatrixMultiply( r0, ulMSize, ulMSize, y11, ulMSize, ulMSize, y01 );

		for ( ULONG i = 0; i < ulMSize*ulMSize; i++ )
		{
			acMatrixInverse[i].re = y11[i];
			acMatrixInverse[i].im = -y01[i];
		}

	}
	return hr;

}

EMS_RESULT _ComplexMatrixInverse( EMSCOMPLEXD* acMatrix, EMSCOMPLEXD* acMatrixInverse, ULONG ulMSize  )
{
	EMS_RESULT hr = EMS_OK;
	int iIndex[9] = { 0,1,2,4,5,6,8,9,10 };
	EMSCOMPLEXD cTest[16];

	switch (ulMSize)
	{
		case 1:
			acMatrixInverse[0] = _CDivide ( acMatrix[0] );
			break;

		case 2:
			_ComplexMatrix2x2Inverse( acMatrix, acMatrixInverse );
			break;

		case 3:
			EMSCOMPLEXD cIN[16], cOUT[16];
			memset( cIN, 0, 16*sizeof( EMSCOMPLEXD ) );
			memset( cOUT, 0, 16*sizeof( EMSCOMPLEXD ) );

			for( int i = 0; i < 9; i++ )
			{
				cIN[iIndex[i]] = acMatrix[i];
			}
			cIN[15].re = 1.0;
			cIN[15].im = 0.0;
		
			hr = _ComplexMatrix4x4Inverse( cIN, cOUT );
		
			for( int i = 0; i < 9; i++ )
			{
				acMatrixInverse[i] = cOUT[iIndex[i]];
			}
			break;

		case 4:
			hr = _ComplexMatrix4x4Inverse( acMatrix, acMatrixInverse );
			return hr;
		
		default:
			hr = _ComplexMatrixNxNInverse( acMatrix, acMatrixInverse, ulMSize );
			break;
	}

	return hr;
}


//--------------------------------------------------------------------------------------------------

#endif
