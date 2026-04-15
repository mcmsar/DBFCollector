//! @file SITConverter.cpp
//! Implemenation of the CEMSSITConverter class.

#pragma warning(disable:4786)	// STL symbol size warning

#include "aobjbase.h"
#include "emssit.h"
#include "sitconverter.h"

#include "emsmstrm.h"
#include "emsfstrm.h"
#include "convutility.h"
#include "sittoken.h"
#include "sitparse.h"
#include "emserror.h"
#include "emsexcpt.h"
#include "mtlmsgs.h"
#include <list>

CEMSSITConverter::CEMSSITConverter()
{
}

CEMSSITConverter::CEMSSITConverter( const CEMSSITConverter& sitConverter )
{
}

CEMSSITConverter::~CEMSSITConverter()
{
}

void
CEMSSITConverter::Serialize( CEMSSitMessageBase* pSit, IEMSSeqStream*& pStream )
{
	if( !pSit )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	THROW_RUNTIME_EXCEPTION( EMS_NOT_IMPLEMENTED );

	//pSit->Generate( pStream );
}


void
CEMSSITConverter::Deserialize(	IEMSSeqStream* pStream, 
								const EMSINPUTTYPE ceInputType,
								int& iSits, 
								CEMSSitMessageBase**& apSit )
{
	CEMSSitMessageBase* pSitMsg = NULL;
	std::list<CEMSSitMessageBase*> lstpSits;

	try
	{
		CEMSSitTokenizer sitTokenizer( pStream );

		CEMSSitParser sitParser;


		EMS_RESULT hr = EMS_OK;
		
		switch( ceInputType )
		{
			case IT_FILESPEC:
				hr = sitParser.ParseSitStream( pStream, lstpSits );
				break;
			case IT_FILESPEC_XML:
				{
					CEMSSitMessageBase* pSitMsg = NULL;
					hr = sitParser.ParseXML( &sitTokenizer, &pSitMsg );

					if( EMS_OK == hr )
					{
						lstpSits.push_back( pSitMsg );
					}
				}
				break;
			case IT_FILESPEC_CSV:
				{
					CEMSSitMessageBase* pSitMsg = NULL;
					hr = sitParser.ParseCSV( &sitTokenizer, &pSitMsg );

					if( EMS_OK == hr )
					{
						lstpSits.push_back( pSitMsg );
					}
				}
				break;
			default:
				hr = EMS_MTL_UNSUPPORTED_INPUT_TYPE;
		}
		

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

		if( lstpSits.size() > 0 )
		{
			apSit = new CEMSSitMessageBase*[ lstpSits.size() ];

			if( !apSit )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			memset( apSit, 0, lstpSits.size()*sizeof(CEMSSitMessageBase*) );

			std::list<CEMSSitMessageBase*>::iterator it = lstpSits.begin();

			long lIndex = 0;
			while( it != lstpSits.end() )
			{
				apSit[lIndex] = *it;

				lIndex++;
				it++;
			}

			iSits = lstpSits.size();
		}
	}
	catch( ... )
	{
		if( apSit )
		{
			delete[] apSit;
			apSit = 0;
		}

		std::list<CEMSSitMessageBase*>::iterator it = lstpSits.begin();
		while( it != lstpSits.end() )
		{
			if( *it )
			{
				delete *it;
				*it = 0;
			}

			it++;
		}


		throw;
	}
}