/********************************************************************
*	              Copyright (c) 2013 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#include "EMScombinations.h"

CEMSCOMINATIONS::CEMSCOMINATIONS()
{
}

//-------------------------------------------------------------------------------------------------------------

CEMSCOMINATIONS::~CEMSCOMINATIONS()
{
}

//-------------------------------------------------------------------------------------------------------------

ULONG
CEMSCOMINATIONS::GetCombinations( ULONG N, ULONG K, ULONG **lpCombinations, ULONG ulRowCount, ULONG ulColCount )
{
	if( ulColCount < K )
	{
		K = ulColCount;
	}
	
	ULONG ulCombinations = NchooseK( N, K );

	if( ulCombinations >= ulRowCount )
	{
		ulCombinations = ulRowCount-1; // Allow one less and fill last one with all zeros
	}



	// Initialize
	for( ULONG i = 0; i < K; i++ )
	{
		lpCombinations[0][i] = i;
	}

	for( ULONG i = 1; i < ulCombinations; i++ )
	{
		for( ULONG j = 0; j < K; j++ )
		{
			lpCombinations[i][j] = lpCombinations[i-1][j];
			lpCombinations[i+1][j] = 0;
		}
		lpCombinations[i][K-1] += 1;

		for( ULONG j = K-1; j > 0; j-- )
		{
			if ( lpCombinations[i][j] > N - (K - j) )
			{
				lpCombinations[i][j-1] += 1;
				for( ULONG j1 = j; j1 < K; j1++ )
				{
					lpCombinations[i][j1] = lpCombinations[i][j1-1] + 1;
				}
			}
		}
			
	}
	return ulCombinations;
}

//-------------------------------------------------------------------------------------------------------------

ULONG
CEMSCOMINATIONS::NchooseK( ULONG N, ULONG K )
{
	ULONG nCombinations = 0;
	if( K <= N && K > 0 )
	{
		double dN = 1;
		double dK = 1;
		for( ULONG i = N; i > N-K; i--) dN *= i;
		for( ULONG i = 1; i < K+1; i++) dK *= i;
		nCombinations = ULONG (dN / dK);
	}
	return nCombinations;
}

//-------------------------------------------------------------------------------------------------------------

