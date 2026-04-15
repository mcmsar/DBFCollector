/********************************************************************
*	Module:			emsoutlier.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	
*						
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:	
*
*********************************************************************
*	              Copyright (c) 2006 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2006/09/20		rcr		start

********************************************************************/
#include <math.h>
#include <memory.h>
#include "emsoutlier.h"
#include <crtdbg.h>

CEMSOutlier::CEMSOutlier()
{
		m_dMean   = 0.0;
		m_dStddev = 0.0;
		m_dMedian = 0.0;

		m_nOutliers = 0;
		m_nPts		= 0;
		//m_nMaxPts	= 0;
		m_nMaxPts	= 4096;

		m_lpDATA	= 0;
		m_lpIndex	= 0;
		m_lpOUTLIER = 0;
}

CEMSOutlier::~CEMSOutlier()
{
	m_nPts		= 0;
	m_nOutliers = 0;

	if ( m_lpDATA )
	{
		delete [] m_lpDATA;
		m_lpDATA = 0;
	}
	if ( m_lpIndex )
	{
		delete [] m_lpIndex;
		m_lpIndex = 0;
	}
	if ( m_lpOUTLIER )
	{
		delete [] m_lpOUTLIER;
		m_lpOUTLIER = 0;
	}
}

EMS_RESULT CEMSOutlier::Init( int nPts )
{
	EMS_RESULT hr = EMS_BAD_PARAM;

//	m_nMaxPts	= 0;
	m_nPts		= 0;
	m_nOutliers = 0;

	if ( m_lpDATA )
	{
		delete [] m_lpDATA;
		m_lpDATA = 0;
	}
	if ( m_lpIndex )
	{
		delete [] m_lpIndex;
		m_lpIndex = 0;
	}
	if ( m_lpOUTLIER )
	{
		delete [] m_lpOUTLIER;
		m_lpOUTLIER = 0;
	}

	if ( nPts )
	{
		m_nMaxPts = nPts;

		m_lpDATA = new double [ m_nMaxPts ];

		m_lpIndex = new int [ m_nMaxPts ];
		
		m_lpOUTLIER = new bool [ m_nMaxPts ];

//		m_nMaxPts = nPts;
	}


	if ( m_lpDATA && m_lpIndex && m_lpOUTLIER )
	{
		hr = EMS_OK;
	}

	return hr;
}

EMS_RESULT CEMSOutlier::AddRecord( double dDATA )
{
	EMS_RESULT hr = EMS_OK;

	if ( m_nPts < m_nMaxPts )
	{
		m_lpDATA[ m_nPts ] = dDATA;
		m_lpIndex[ m_nPts ] = m_nPts;
		m_lpOUTLIER[ m_nPts ] = false;
		m_nPts++;
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSOutlier::Reset()
{
	EMS_RESULT hr = EMS_OK;

	m_nPts = 0;
	memset( m_lpIndex , 0, m_nMaxPts*sizeof(int) );
	memset( m_lpDATA , 0, m_nMaxPts*sizeof(double) );
	memset( m_lpOUTLIER , 0, m_nMaxPts*sizeof(bool) );

	return hr;
}

EMS_RESULT CEMSOutlier::SetThreshold( double dThreshold, double dOffset )
{
	EMS_RESULT hr = EMS_OK;

	if ( m_nPts &&  m_lpDATA )
	{
		for (int i=0; i<m_nPts; i++)
		{
			if ( fabs( m_lpDATA[ i ] - dOffset ) > dThreshold )
				m_lpOUTLIER[ i ] = true;
			else
				m_lpOUTLIER[ i ] = false;
		}

		_CalculateStats();		
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSOutlier::SetCountThreshold( int nMaxPtsAllowed, double dOffset )
{

	// Assumes data has been sorted

	EMS_RESULT hr = EMS_OK;

	if ( m_nPts &&  m_lpDATA && (nMaxPtsAllowed <= m_nPts) )
	{
		int i1, i2;
		double dTest1, dTest2;

		i1 = 0;
		i2 = m_nPts-1;
		dTest1 = fabs( m_lpDATA[ i1 ] - dOffset );
		dTest2 = fabs( m_lpDATA[ i2 ] - dOffset );
		
		while ( (nMaxPtsAllowed > 0) && (i2 > i1) )
		{

			if ( dTest1 > dTest2 )
			{
				_ASSERT( i1 < m_nPts );

				m_lpOUTLIER[ i1 ] = true;				
				i1++;
				dTest1 = fabs( m_lpDATA[ i1 ] - dOffset );
			}
			else
			{
				_ASSERT( i2 < m_nPts );

				m_lpOUTLIER[ i2 ] = true;				
				i2--;
				dTest2 = fabs( m_lpDATA[ i2 ] - dOffset );
			}

			nMaxPtsAllowed--;
		}

		_CalculateStats();
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSOutlier::Sort()
{
	EMS_RESULT hr = EMS_OK;

	if ( m_lpDATA && m_nPts )
	{
		_HeapSort();
		
		_ASSERT( _TestSort() );

		_CalculateStats();		
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSOutlier::Calculate()
{
	EMS_RESULT hr = EMS_OK;

	if ( m_lpDATA && m_nPts )
	{
		_CalculateStats();		
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

bool CEMSOutlier::TestOutlier( int nIndex )
{
	bool bOUTLIER = false;

	if ( nIndex < m_nPts )
	{
		bOUTLIER = m_lpOUTLIER[ m_lpIndex[ nIndex ]];
	}

	return bOUTLIER;
}


void CEMSOutlier::_CalculateStats()
{

	// Assumes data sorted for median value calculation
	
	if ( m_lpDATA && m_nPts )
	{
		double dResidual;
		int nCount = 0;
		int nMaxIndex = 0;
		int nMinIndex = m_nPts;
		int nMedianIndex = int (m_nPts / 2);

		m_dMean   = 0.0;
		m_dStddev = 0.0;
		m_dMedian = 0.0;

		m_nOutliers = 0;
		
		for (int i=0; i<m_nPts; i++)
		{
			if ( !m_lpOUTLIER[ i ] )
			{
				dResidual  = m_lpDATA[ i ];
				m_dMean   += dResidual;
				m_dStddev += dResidual * dResidual;
				nCount++;
				if ( i < nMinIndex ) nMinIndex = i;
				if ( i > nMaxIndex ) nMaxIndex = i;
			}
			else
				m_nOutliers++;
		}

		if ( nCount )
		{
			m_dMean /= nCount;
			m_dStddev = sqrt( fabs( m_dStddev / nCount - m_dMean * m_dMean ) ); 

			nMedianIndex =  nMinIndex + int( (nMaxIndex - nMinIndex)/2 );

			if ( (nMedianIndex >= 0) && (nMedianIndex < m_nPts) )
				m_dMedian = m_lpDATA[ nMedianIndex ];
		}
	}

}

bool CEMSOutlier::_TestSort()
{
	bool bTestSort = true;

	for ( int i = 0; i< m_nPts-1; i++ )
	{
		if ( m_lpDATA[i] > m_lpDATA[i+1] )
		{
			bTestSort = false;
		}
	}
	return bTestSort;
}



// Heap Sort (saves original index set)
void CEMSOutlier::_HeapSort()
{
	if ( m_lpDATA && (m_nPts>1) )
	{
		int istart, iend;
		int nTemp;
		double dTemp;
 
		for( istart = (m_nPts/2)-1; istart >= 0; istart-- )
		{
			_HeapSiftDown( istart, m_nPts );
		}
 
		for( iend = m_nPts-1; iend >= 1; iend-- )
		{
			_ASSERT( iend < m_nPts );

			dTemp       = m_lpDATA[0];
			m_lpDATA[0] = m_lpDATA[iend];
			m_lpDATA[iend] = dTemp;

			nTemp        = m_lpIndex[0];
			m_lpIndex[0] = m_lpIndex[iend];
			m_lpIndex[iend] = nTemp;


			//_HeapSiftDown( 0, i-1 );
			_HeapSiftDown( 0, iend );
		}
	}
}
 
void CEMSOutlier::_HeapSiftDown( int nRoot, int nCount )
{
	bool done = false;
	int nChild;
	int nTemp;
	double dTemp;
 
	while( (nRoot*2+1 < nCount) && (!done) )
	{
		nChild = nRoot * 2 + 1;

		_ASSERT( nRoot < m_nPts );
		_ASSERT( nChild < m_nPts );
		_ASSERT( nCount <= m_nPts );

		if ( (nChild < nCount-1) &&
		   ( m_lpDATA[nChild] < m_lpDATA[nChild + 1] ) )
		{
			nChild = nChild + 1;
		}

		if( m_lpDATA[nRoot] < m_lpDATA[nChild] )
		{

			dTemp            = m_lpDATA[nRoot];
			m_lpDATA[nRoot]  = m_lpDATA[nChild];
			m_lpDATA[nChild] = dTemp;
			
			nTemp             = m_lpIndex[nRoot];
			m_lpIndex[nRoot]  = m_lpIndex[nChild];
			m_lpIndex[nChild] = nTemp;

			nRoot             = nChild;
		}
		else
		{
			done = true;
		}
	}
}
