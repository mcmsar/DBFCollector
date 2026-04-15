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


#ifndef __EMSSTANDARDDEVIATION_H__
#define __EMSSTANDARDDEVIATION_H__

#include <math.h>


//! @template<class T> class CEMSStandardDeviation
//! The object of this template class acts as a statistical packet, it accumulates   
//! count, sums, mean and standard deviation of added readings.
template<class T> class CEMSStandardDeviation  
{
public:
	CEMSStandardDeviation();
	CEMSStandardDeviation( const CEMSStandardDeviation<T>& StDObj );
	virtual ~CEMSStandardDeviation();

	//! @fn void AddReading( T& TReading )
	//! Adds a reading.
	//! @param T& TReading
	//! The reading. 
	virtual void AddReading( T& TReading );
	
	//! @fn double GetMean()
	//! Returns the mean of accumulated data.
	double GetMean();
	
	//! @fn double GetStD()
	//! Returns the standard deviation of accumulated data.
	double GetStD();
	
	//! @fn unsigned long GetCount()
	//! Returns the number of readings added.
	unsigned long GetCount();

	CEMSStandardDeviation<T>& operator=( const CEMSStandardDeviation<T>& StDObj );
	CEMSStandardDeviation<T>& operator+=( const CEMSStandardDeviation<T>& StDObj );

protected:
	void _CalculateMean();

protected:
	unsigned long m_ulCount;
	double m_dSum;
	double m_dSumSq;
	double m_dMean;
	double m_dStD;

};

/************************** CEMSStandardDeviation: Methods ************************/

template<class T> 
CEMSStandardDeviation<T>::CEMSStandardDeviation()
{
	m_ulCount = 0;
	m_dSum = 0;
	m_dSumSq = 0;
	m_dMean = 0.0;
	m_dStD = 0.0;
}

template<class T> 
CEMSStandardDeviation<T>::CEMSStandardDeviation( const CEMSStandardDeviation<T>& StDObj )
{
	m_ulCount = StDObj.m_ulCount;
	m_dSum = StDObj.m_dSum;
	m_dSumSq = StDObj.m_dSumSq;
	m_dMean = StDObj.m_dMean;
	m_dStD = StDObj.m_dStD;
}

template<class T> 
CEMSStandardDeviation<T>::~CEMSStandardDeviation()
{
}

template<class T>
unsigned long 
CEMSStandardDeviation<T>::GetCount()
{
	return m_ulCount;
}


template<class T>
void 
CEMSStandardDeviation<T>::AddReading( T& TReading )
{
	m_ulCount++;
	m_dSum += TReading;
    m_dSumSq += TReading * TReading;
}

template<class T>
void 
CEMSStandardDeviation<T>::_CalculateMean()
{
	if( m_ulCount > 0 )
	{
		m_dMean = (double) m_dSum/ (double)m_ulCount;
	}
	else
	{
		m_dMean = 0.0;
	}
}

template<class T>
double 
CEMSStandardDeviation<T>::GetMean()
{
	_CalculateMean();
	return m_dMean;
}


template<class T>
double 
CEMSStandardDeviation<T>::GetStD()
{
	if( m_ulCount > 0 )
	{
		_CalculateMean();
		m_dStD = m_dSumSq / (double)m_ulCount - m_dMean * m_dMean;
		if( m_dStD < 0.0 )
		{
			m_dStD *= -1.0;
		}
		m_dStD = sqrt( m_dStD );
	}
	else
	{
		m_dStD = 0.0;
	}
	return m_dStD;
}

template<class T>
CEMSStandardDeviation<T>& 
CEMSStandardDeviation<T>::operator=( const CEMSStandardDeviation<T>& StDObj )
{
	m_ulCount = StDObj.m_ulCount;
	m_dSum = StDObj.m_dSum;
	m_dSumSq = StDObj.m_dSumSq;
	return *this;
}

template<class T>
CEMSStandardDeviation<T>& 
CEMSStandardDeviation<T>::operator+=( const CEMSStandardDeviation<T>& StDObj )
{
	m_ulCount += StDObj.m_ulCount;
	m_dSum += StDObj.m_dSum;
	m_dSumSq += StDObj.m_dSumSq;
	return *this;
}

/**************************** CEMS_StD_MinMax **************************/

//! @template<class T> class CEMS_StD_MinMax
//! The object of this template class acts as a statistical packet, it accumulates   
//! count, sums, mean, standard deviation, Min, and Max of added readings.
template<class T> class CEMS_StD_MinMax: public CEMSStandardDeviation<T>
{
public:
	CEMS_StD_MinMax();
	CEMS_StD_MinMax( const CEMS_StD_MinMax<T>& MinMaxObj );
	virtual ~CEMS_StD_MinMax();

	//! @fn void AddReading( T& TReading )
	//! Adds a reading.
	//! @param T& TReading
	//! The reading. 
	virtual void AddReading( T& TReading );
	
	//! @fn T GetMin()
	//! Returns the minimum reading.
	T GetMin();

	//! @fn T GetMax()
	//! Returns the maximum reading.
	T GetMax();

	CEMS_StD_MinMax<T>& operator=( const CEMS_StD_MinMax<T>& MinMaxObj );
	CEMS_StD_MinMax<T>& operator+=( const CEMS_StD_MinMax<T>& MinMaxObj );

protected:
	T m_TMin;
	T m_TMax;

	bool m_bFirstReading;
};

/**************************** CEMS_StD_MinMax: Methods ****************************/

template<class T> 
CEMS_StD_MinMax<T>::CEMS_StD_MinMax()
{
	m_TMin = (T)0;
	m_TMax = (T)0;
	m_bFirstReading = true;
}

template<class T> 
CEMS_StD_MinMax<T>::CEMS_StD_MinMax( const CEMS_StD_MinMax<T>& MinMaxObj )
{
	m_ulCount = MinMaxObj.m_ulCount;
	m_dSum = MinMaxObj.m_dSum;
	m_dSumSq = MinMaxObj.m_dSumSq;
	m_dMean = MinMaxObj.m_dMean;
	m_dStD = MinMaxObj.m_dStD;
	m_bFirstReading = MinMaxObj.m_bFirstReading;
	m_TMin = MinMaxObj.m_TMin;
	m_TMax = MinMaxObj.m_TMax;
}

template<class T> 
CEMS_StD_MinMax<T>::~CEMS_StD_MinMax()
{
}

template<class T>
void 
CEMS_StD_MinMax<T>::AddReading( T& TReading )
{
	CEMSStandardDeviation<T>::AddReading( TReading );

	if( m_bFirstReading )
	{
		m_TMin = TReading;
		m_TMax = TReading;
		m_bFirstReading = false;
	}
	else
	{
		if( TReading > m_TMax )
		{
			m_TMax = TReading;
		}

		if( TReading < m_TMin )
		{
			m_TMin = TReading;
		}
	}
}

template<class T>
T 
CEMS_StD_MinMax<T>::GetMin()
{
	return m_TMin;
}


template<class T>
T 
CEMS_StD_MinMax<T>::GetMax()
{
	return m_TMax;
}

template<class T>
CEMS_StD_MinMax<T>& CEMS_StD_MinMax<T>::operator=( const CEMS_StD_MinMax<T>& MinMaxObj )
{
	m_ulCount = MinMaxObj.m_ulCount;
	m_dSum = MinMaxObj.m_dSum;
	m_dSumSq = MinMaxObj.m_dSumSq;
	m_bFirstReading = MinMaxObj.m_bFirstReading;
	m_TMin = MinMaxObj.m_TMin;
	m_TMax = MinMaxObj.m_TMax;

	return *this;
}

template<class T>
CEMS_StD_MinMax<T>& 
CEMS_StD_MinMax<T>::operator+=( const CEMS_StD_MinMax<T>& MinMaxObj )
{
	m_ulCount += MinMaxObj.m_ulCount;
	m_dSum += MinMaxObj.m_dSum;
	m_dSumSq += MinMaxObj.m_dSumSq;

	if( m_bFirstReading )
	{
		if( !MinMaxObj.m_bFirstReading )
		{
			m_TMin = MinMaxObj.m_TMin;
			m_TMax = MinMaxObj.m_TMax;
			m_bFirstReading = false;
		}
		
	}
	else
	{
		if( !MinMaxObj.m_bFirstReading )
		{
			if( MinMaxObj.m_TMax > m_TMax )
			{
				m_TMax = MinMaxObj.m_TMax;
			}

			if( MinMaxObj.m_TMin < m_TMin )
			{
				m_TMin = MinMaxObj.m_TMin;
			}
		}
	}
	return *this;
}


/***************************** CEMS_Median **************************/
//! @template<class T> class CEMS_Median
//! The object of this template class acts as a statistical packet, it accumulates   
//! count, sums, mean, standard deviation, Min, Max, and the Median of added readings.


template<class T> class CEMS_Median: public CEMS_StD_MinMax<T>
{
public:
	CEMS_Median();
	CEMS_Median( T minVal, T maxVal, T stepSize );
	CEMS_Median( const CEMS_Median<T>& MedianObj );
	virtual ~CEMS_Median();

	//! @fn void AddReading( T& TReading )
	//! Adds a reading.
	//! @param T& TReading
	//! The reading. 
	virtual void AddReading( T& TReading );
	
	//! @fn T GetMedian()
	//! Returns the medium reading.
	double GetMedian();

//	long GetHystogram();

	void SetMedianControl( T minVal, T maxVal, T stepSize );
	CEMS_Median<T>& operator=( const CEMS_Median<T>& MedianObj );
	CEMS_Median<T>& operator+=( const CEMS_Median<T>& MedianObj );


protected:
	double			m_dMedian;
	T               m_TMinVal;
	T               m_TMaxVal;
	T               m_TStepSize;
	long*			m_arrlBins;
	unsigned long   m_ulBinNumber;
};




/**************************** CEMS_Median: Methods ****************************/

template<class T> 
CEMS_Median<T>::CEMS_Median(): m_dMedian(0.0),
                               m_TMinVal(0),
							   m_TMaxVal(0),
							   m_TStepSize(0),
							   m_arrlBins(NULL),
							   m_ulBinNumber(0)
{
}

template<class T> 
CEMS_Median<T>::CEMS_Median( T minVal, T maxVal, T stepSize ): m_dMedian(0.0),
                                                               m_TMinVal(minVal),
															   m_TMaxVal(maxVal),
															   m_TStepSize(stepSize),
															   m_arrlBins(NULL),
															   m_ulBinNumber(0)
{
}

template<class T>
void 
CEMS_Median<T>::SetMedianControl(  T minVal, T maxVal, T stepSize  )
{
    m_TMinVal = minVal;
	m_TMaxVal = maxVal;
	m_TStepSize = stepSize;
	m_ulBinNumber = (unsigned long) (m_TMaxVal - m_TMinVal)/m_TStepSize;

	if( m_arrlBins )
	{
	    delete []m_arrlBins;
	}
    m_arrlBins = new long[m_ulBinNumber];

	memset( m_arrlBins, 0, sizeof(long) * m_ulBinNumber );
}


template<class T> 
CEMS_Median<T>::CEMS_Median( const CEMS_Median<T>& MedianObj )
{
	m_TMedian = MedianObj.m_TMedian;

}

template<class T> 
CEMS_Median<T>::~CEMS_Median()
{
	if( m_arrlBins )
	{
		delete []m_arrlBins;
		m_arrlBins = NULL;
	}
}



template<class T>
void 
CEMS_Median<T>::AddReading( T& TReading )
{
	unsigned long ulBinNumber = 0;
   
	if( TReading - m_TMinVal >= 0 )
	{
		ulBinNumber = (unsigned long)((TReading - m_TMinVal ) / m_TStepSize ) ;
		if( (ulBinNumber >= 0) && (ulBinNumber < m_ulBinNumber) )
		{
			m_arrlBins[ ulBinNumber ]++;
		  	CEMS_StD_MinMax<T>::AddReading( TReading );
		}
	}
}



template<class T>
double
CEMS_Median<T>::GetMedian()
{
	for ( unsigned long k = 0; k < m_ulBinNumber; k++ )
	{
		float fIndex = (float)(m_arrlBins[k]) / (float)( CEMSStandardDeviation<T>::GetCount() ); 

		if (fIndex <= 0.5 )										// still Cdf less than 50%
		{      
 			m_arrlBins[k+1] += m_arrlBins[k];
		}
		else
		{
			m_dMedian = (float) (m_TMinVal + (k + 0.5 ) * m_TStepSize); 
			break;
		}
	}
	return m_dMedian;
}


template<class T>
CEMS_Median<T>& CEMS_Median<T>::operator=( const CEMS_Median<T>& MedianObj )
{
	m_dMedian = MedianObj.m_dMedian;
	m_TMinVal = MedianObj.m_TMinVal;
	m_TMaxVal = MedianObj.m_TMaxVal;
	m_TStepSize = MedianObj.m_TStepSize;
	m_arrlBins = MedianObj.m_arrlBins;
	m_ulBinNumber = MedianObj.m_ulBinNumber;

	return *this;
}

template<class T>
CEMS_Median<T>& 
CEMS_Median<T>::operator+=( const CEMS_Median<T>& MedianObj )
{
	m_dMedian += MedianObj.m_dMedian;
	m_TMinVal += MedianObj.m_TMinVal;
	m_TMaxVal += MedianObj.m_TMaxVal;
	m_TStepSize += MedianObj.m_TStepSize;
	m_arrlBins += MedianObj.m_arrlBins;
	m_ulBinNumber += MedianObj.m_ulBinNumber;

	return *this;
}





/**************************** CEMS_StD_Trend **************************/
//! @template<class T> class CEMS_StD_Trend
//! The object of this template class acts as a statistical packet, it accumulates   
//! count, sums, mean, standard deviation, Min, Max, and the trend of added readings.
template<class T> class CEMS_StD_Trend: public CEMSStandardDeviation<T>
{
public:
	CEMS_StD_Trend();
	CEMS_StD_Trend( const CEMS_StD_Trend<T>& TrendObj );
	virtual ~CEMS_StD_Trend();

	//! @fn void AddReading( T& TReading )
	//! Adds a reading.
	//! @param T& TReading
	//! The reading. 
	virtual void AddReading( T& TReading );
	
	CEMS_StD_Trend<T>& operator=( const CEMS_StD_Trend<T>& TrendObj );
	CEMS_StD_Trend<T>& operator+=( const CEMS_StD_Trend<T>& TrendObj );

	//! @fn double GetTrend()
	//! Returns the trend of accumulated data.
	double GetTrend();

protected:
	double m_dTrendSum;
	double m_dTrend;
	T      m_TLastReading;

};

/**************************** CEMS_StD_Trend: Methods *****************************/

template<class T> 
CEMS_StD_Trend<T>::CEMS_StD_Trend()
{
	m_TLastReading = (T)0;
	m_dTrendSum = 0.0;
	m_dTrend = 0.0;

}

template<class T> 
CEMS_StD_Trend<T>::CEMS_StD_Trend( const CEMS_StD_Trend<T>& TrendObj )
{
	m_ulCount = TrendObj.m_ulCount;
	m_dSum = TrendObj.m_dSum;
	m_dSumSq = TrendObj.m_dSumSq;
	m_dMean = TrendObj.m_dMean;
	m_dStD = TrendObj.m_dStD;
	m_dTrendSum = TrendObj.m_dTrendSum;
}

template<class T> 
CEMS_StD_Trend<T>::~CEMS_StD_Trend()
{
}

template<class T>
void 
CEMS_StD_Trend<T>::AddReading( T& TReading )
{
	CEMSStandardDeviation<T>::AddReading( TReading );

	if( m_TLastReading > (T)0 )
	{
		m_dTrendSum += TReading * m_TLastReading;
	}
	else
	{
		m_dTrendSum += TReading * TReading;
	}
	m_TLastReading = TReading;
}

template<class T>
double 
CEMS_StD_Trend<T>::GetTrend()
{
	if( m_ulCount > 0 )
	{
		BOOL bNeg = FALSE;
		_CalculateMean();
		m_dTrend = m_dTrendSum / (double)m_ulCount - m_dMean * m_dMean;
		if( m_dTrend < 0.0 )
		{
			m_dTrend *= -1.0;
			bNeg = TRUE;
		}
		m_dTrend = sqrt( m_dTrend );
		if( bNeg )
		{
			m_dTrend *= -1.0;
		}
	}
	else
	{
		m_dTrend = 0.0;
	}
	return m_dTrend;
}

template<class T>
CEMS_StD_Trend<T>& 
CEMS_StD_Trend<T>::operator=( const CEMS_StD_Trend<T>& TrendObj )
{
	m_ulCount = TrendObj.m_ulCount;
	m_dSum = TrendObj.m_dSum;
	m_dSumSq = TrendObj.m_dSumSq;
	m_dTrendSum = TrendObj.m_dTrendSum;

	return *this;
}

template<class T>
CEMS_StD_Trend<T>& 
CEMS_StD_Trend<T>::operator+=( const CEMS_StD_Trend<T>& TrendObj )
{
	m_ulCount += TrendObj.m_ulCount;
	m_dSum += TrendObj.m_dSum;
	m_dSumSq += TrendObj.m_dSumSq;
	m_dTrendSum += TrendObj.m_dTrendSum;

	return *this;
}

#endif
