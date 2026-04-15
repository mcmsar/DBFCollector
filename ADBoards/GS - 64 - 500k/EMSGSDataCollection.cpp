/*********************************************************************
*	              Copyright (c) 2011 by EMS Technologies, Inc.,
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

#include "EMSGSDataCollection.h"
#include "emserror.h"
#include <stdio.h>
#include "emsclock.h"				// CEMSSystemClock
#include <iostream>
//#include "emsexcpt.h"



CEMSGSDataCollection::CEMSGSDataCollection() : m_bRunning(false), m_bInitialized(false),
											   m_iNumChan(0), m_dwSampleRate(500000),
											   //m_iNumChan(0), m_dwSampleRate(5000000),

//											   m_aMainBuff(NULL), m_dwMainBuffSize(32000000),
											   m_aMainBuff(NULL), m_dwMainBuffSize(128000000),
											   m_blk1_allocated(0), m_blk2_allocated(0)
{
	m_hMainBuff = INVALID_HANDLE_VALUE;
	m_hSharedBuff = INVALID_HANDLE_VALUE;
}

CEMSGSDataCollection::CEMSGSDataCollection( const CEMSGSDataCollection& x )
{
}

CEMSGSDataCollection::~CEMSGSDataCollection()
{
	Reset();
}

void 
CEMSGSDataCollection::Reset()
{
	m_oCS.Enter();

	m_bRunning = false;

	try
	{
		unsigned long ulErr = 0;
		unsigned long ulBdNum = 1;
        m_Block1.Size = m_blk1_allocated;
        m_Block2.Size = m_blk2_allocated;
        GS66_18AI32SS_Free_Physical_Memory(ulBdNum, &m_Block1, &ulErr);
        GS66_18AI32SS_Free_Physical_Memory(ulBdNum, &m_Block2, &ulErr);
/*        free(wBuff);
		free(wBuffMain);
		free(aBuffers);
		free(aBuffersDesc);
		free(aSeqNums);
*/
		if( m_aMainBuff )
		{
			delete[] m_aMainBuff;
			m_aMainBuff = NULL;
		}
		m_oCS.Leave();
	}
	catch( ... )
	{
		m_oCS.Leave();
		throw;
	}
	
}

void
CEMSGSDataCollection::_Set_vRange(double range, unsigned unipolar)
{
}

//void
//CEMSGSDataCollection::_Initialize()
//{
//	if( !m_bInitialized )
//	{
//		char cBoardInfo[400];
//		unsigned long ulErr = 0;
//		unsigned long ulBdNum = 1;
//		unsigned long ulNumBds = 0;
//		unsigned long ulValueRead = 0;
//		unsigned long ulMemNeeded = 0;
//		unsigned long ulBytes_needed = 0;
//		ldiv_t result;
//
//
//		try
//		{
///*			if( m_lpLogFile )
//			{
//				fprintf( m_lpLogFile, "\n::_Init() - Begin\n" );
//				fflush( m_lpLogFile );
//			}
//*/
//			ulNumBds = GS66_18AI32SS_FindBoards(&cBoardInfo[0], &ulErr);
//
//			if(ulErr)
//			{
//				throw ulErr;
//			}
//
//			GS66_18AI32SS_Get_Handle(&ulErr, ulBdNum);
//			if(ulErr)
//			{
//				throw ulErr;
//			}
//
//
//			if(m_iNumChan == 0)
//			{
//				ulValueRead = GS66_18AI32SS_Read_Local32(ulBdNum, &ulErr, FW_REV);
//			    m_iNumChan = (ulValueRead&0x1000) ? 32:64;
//
//				//printf("FW_REV     * Undocumented * = %08lX : %02d Channels ",  ulValueRead,m_iNumChan );
//			}
//
//			ulMemNeeded = (U32)((double)m_dwSampleRate * (double)m_iNumChan);
//			ulBytes_needed = (U32)((double)ulMemNeeded*1.0*(double)4.0); //one second
//
//			LARGE_INTEGER sysFreq;
//			if(QueryPerformanceFrequency(&sysFreq) == 0)
//			{
//				throw 0;
//			}
//
//			memset(&m_Block1, 0, sizeof(GS_PHYSICAL_MEM));
//			memset(&m_Block2, 0, sizeof(GS_PHYSICAL_MEM));
//
//			// This is the memory we will be using for DMA
//			// Try for 1 seconds worth, but if > than can transfer in one block,
//			// decrement till there
//			while((ulMemNeeded*4) > ((1<<23)-1))
//				ulMemNeeded /= 2;
//
//			m_Block1.Size = ulMemNeeded*4;
//			GS66_18AI32SS_Get_Physical_Memory(ulBdNum, &m_Block1, 1, &ulErr); // but settle for less
//			m_blk1_allocated = m_Block1.Size;
//			result = ldiv(m_Block1.Size,m_iNumChan);
//			m_Block1.Size = (U32)(result.quot * m_iNumChan); // Ensure integer multiple of channels
//
//			m_Block2.Size = m_Block1.Size;// Try to make them both equal, regardless of size
//			GS66_18AI32SS_Get_Physical_Memory(ulBdNum, &m_Block2, 1, &ulErr); // 1 = will take less
//			m_blk2_allocated = m_Block2.Size;
//			result = ldiv(m_Block2.Size,m_iNumChan);
//			m_Block2.Size = (U32)(result.quot * m_iNumChan); // Ensure integer multiple of channels
//
//			GS66_18AI32SS_Initialize(ulBdNum, &ulErr);
//			Sleep(2000);
//
//			U32 ValueRead = 0;
//
//
//			//{
//			//	ValueRead = GS66_18AI32SS_Read_Local32(ulBdNum, &ulErr, BCR); 
//			//	ValueRead |= 0x40800;// Packed data & disable scan marker
//			//	GS66_18AI32SS_Write_Local32(ulBdNum, &ulErr, BCR, ValueRead);
//			//}
//
//
//			//set_vRange(5.00,BIPOLAR);
//			//{
//			//	ValueRead = GS66_18AI32SS_Read_Local32(ulBdNum, &ulErr, BCR);
//			//	ValueRead &= 0xFFFFFFC7;
//			//	//ValueRead |= 0x20;
//			//	ValueRead |= 0x28;
//			//	GS66_18AI32SS_Write_Local32(ulBdNum, &ulErr, BCR,ValueRead);
//			//	GS66_18AI32SS_Set_Processing_Mode(ulBdNum, &ulErr,0x0); // Std SE Mode
//			//}
//
//
//			{
//				GS66_18AI32SS_Write_Local32(ulBdNum, &ulErr, RATE_A, 0x10000 | ((60000000/m_dwSampleRate)&0xFFFF)); // Sample Rate 
//				//GS66_18AI32SS_Write_Local32(ulBdNum, &ulErr, RATE_A, 0x10000 | ((50000000/m_dwSampleRate)&0xFFFF)); // Sample Rate
//				GS66_18AI32SS_Write_Local32(ulBdNum, &ulErr, SCAN_CNTRL,0x800|((m_iNumChan==64)?6:5));
//				Sleep(200);
//				//  auto_cal(ulBdNum);
//				{
//
//					// Auto Calibration
//					unsigned long ulValue;
//					ulValue = GS66_18AI32SS_Autocal(ulBdNum, &ulErr);
//
//					switch(ulValue)
//					{
//					case 0: 
//						{
//							int x = 1;
//							x++;
//							//Autocal FAILED log an error
//							//printf("  Autocal FAILED BD#%ld  ...",ulBdNum);
//							break;
//						}
//					case MINUS_ONE_LONG:
//						{
//							// Autocal ERROR
//							//printf("  Autocal     ERROR BD#%ld  ...",ulBdNum);
//							break;
//						}
//					case 0x55:
//						{
//							//Insufficent Resources ERROR 
//							//printf("  Insufficent Resources ERROR BD#%ld  ...",ulBdNum);
//	
//							break;
//						}
//					case 0xAA:
//						{
//							//Autocal Interrupt ERROR
//							//printf("  Autocal Interrupt     ERROR BD#%ld  ...",ulBdNum);
//							break;
//						}
//					default:
//						//printf("     Default value  for GS66_18AI32SS_Autocal             ");
//						break;
//					}
//
//
//					Sleep(300);
//				}
//
//				ValueRead = GS66_18AI32SS_Read_Local32(ulBdNum, &ulErr, IN_DATA_CNTRL);
//				GS66_18AI32SS_Write_Local32(ulBdNum, &ulErr, IN_DATA_CNTRL,ValueRead|0x40000);
//
//			}
//
//
//			//GS66_18AI32SS_Write_Local32(ulBdNum, &ulErr, SCAN_CNTRL,0x800|((m_iNumChan==64)?6:5));
//			Sleep(200);
//
//
//			GS66_18AI32SS_Dma_DataMode(ulBdNum, 0 ); // Normal
//
//
//			// Setup CmdChaining here
//			memset(&m_DmaSetup, 0, sizeof(GS_DMA_DESCRIPTOR));
//			m_DmaSetup.DmaChannel = 1;
//			m_DmaSetup.NumDescriptors = 2;
//			m_DmaSetup.LocalToPciDesc_1 = 1;
//			m_DmaSetup.BytesDesc_1 = m_Block1.Size;
//			m_DmaSetup.PhyAddrDesc_1 = m_Block1.PhysicalAddr;
//			m_DmaSetup.InterruptDesc_1 = 1;
//			m_DmaSetup.LocalToPciDesc_2 = 1;
//			m_DmaSetup.BytesDesc_2 = m_Block2.Size;
//			m_DmaSetup.PhyAddrDesc_2 = m_Block2.PhysicalAddr;
//			m_DmaSetup.InterruptDesc_2 = 1;
//
//			if(GS66_18AI32SS_Setup_DmaCmdChaining(ulBdNum, &m_DmaSetup,  &ulErr))
//			{
//				Reset();
//				return;
//			}
//
//			Sleep(300);
//
//			m_hGSEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
//			
//			if( m_hGSEvent == NULL )
//			{
//				return;
//			}
//
//			//m_aMainBuff = new unsigned char[m_dwMainBuffSize/2]; // half second
//
//			if( !m_aMainBuff )
//			{
//				//throw 0; // memory exception
//			}
//
//			m_bInitialized = true;
//
//		}
//		catch(...)
//		{
//			throw;
//		}
//	}
//}

//void
//CEMSGSDataCollection::_Initialize()
//{
//	if( !m_bInitialized )
//	{
//		char cBoardInfo[400];
//		unsigned long ulErr = 0;
//		unsigned long ulBdNum = 1;
//		unsigned long ulNumBds = 0;
//		unsigned long ulValueRead = 0;
//		unsigned long ulMemNeeded = 0;
//		unsigned long ulBytes_needed = 0;
//		ldiv_t result;
//
//		m_dwSampleRate = 1000000;
//
//
//		try
//		{
///*			if( m_lpLogFile )
//			{
//				fprintf( m_lpLogFile, "\n::_Init() - Begin\n" );
//				fflush( m_lpLogFile );
//			}
//*/
//			ulNumBds = GS66_18AI32SS_FindBoards(&cBoardInfo[0], &ulErr);
//			//ulNumBds = GS66_18AI32SS_FindBoards(&cBoardInfo[0], &ulErr);
//
//			if(ulErr)
//			{
//				throw ulErr;
//			}
//
//			GS66_18AI32SS_Get_Handle(&ulErr, ulBdNum);
//			if(ulErr)
//			{
//				throw ulErr;
//			}
//
//
//			if(m_iNumChan == 0)
//			{
//				ulValueRead = GS66_18AI32SS_Read_Local32(ulBdNum, &ulErr, FW_REV);
//				m_iNumChan = ( ulValueRead & 0x10000 ) ? 16:32;
//			}
//
//			ulMemNeeded = (U32)((double)m_dwSampleRate * (double)m_iNumChan);
//			ulBytes_needed = (U32)((double)ulMemNeeded*1.0*(double)4.0); //one second
//
//			LARGE_INTEGER sysFreq;
//			if(QueryPerformanceFrequency(&sysFreq) == 0)
//			{
//				throw 0;
//			}
//
//			memset(&m_Block1, 0, sizeof(GS_PHYSICAL_MEM));
//			memset(&m_Block2, 0, sizeof(GS_PHYSICAL_MEM));
//
//			// This is the memory we will be using for DMA
//			// Try for 1 seconds worth, but if > than can transfer in one block,
//			// decrement till there
//			while((ulMemNeeded*4) > ((1<<23)-1))
//				ulMemNeeded /= 2;
//
//			m_Block1.Size = ulMemNeeded*4;
//			GS66_18AI32SS_Get_Physical_Memory(ulBdNum, &m_Block1, 1, &ulErr); // but settle for less
//			m_blk1_allocated = m_Block1.Size;
//			result = ldiv(m_Block1.Size,m_iNumChan);
//			m_Block1.Size = (U32)(result.quot * m_iNumChan); // Ensure integer multiple of channels
//
//			m_Block2.Size = m_Block1.Size;// Try to make them both equal, regardless of size
//			GS66_18AI32SS_Get_Physical_Memory(ulBdNum, &m_Block2, 1, &ulErr); // 1 = will take less
//			m_blk2_allocated = m_Block2.Size;
//			result = ldiv(m_Block2.Size,m_iNumChan);
//			m_Block2.Size = (U32)(result.quot * m_iNumChan); // Ensure integer multiple of channels
//
//			GS66_18AI32SS_Initialize(ulBdNum, &ulErr);
//			Sleep(2000);
//
//			GS66_18AI32SS_Write_Local32(ulBdNum, &ulErr, RATE_A, ((60000000/1000000)&0xFFFF));
//			//GS66_18AI32SS_Write_Local32(ulBdNum, &ulErr, RATE_A, 0x10000 | ((60000000/m_dwSampleRate)&0xFFFF)); // Sample Rate 
//			//GS66_18AI32SS_Write_Local32(ulBdNum, &ulErr, RATE_A, 0x10000 | ((36000000/m_dwSampleRate)&0xFFFF)); // Sample Rate
//			//ulValueRead = (m_iNumChan==32)?5:4;
//			//ulValueRead |= 0x28; // RATE A and Enable Selected Clocking
//			//GS66_18AI32SS_Write_Local32(ulBdNum, &ulErr, SCAN_CNTRL, ulValueRead);
//
//			ValueRead = GS66_18AI32SS_Read_Local32(ulBdNum, &ulErr, SCAN_CNTRL); 
//			GS66_18AI32SS_Write_Local32(ulBdNum, &ulErr, SCAN_CNTRL, (ValueRead | 0x800));// Enable adc clock prior to Autocal for the best accuracy
//
//			// Auto Calibration
//			unsigned long ulValue;
//			ulValue = GS66_18AI32SS_Autocal(ulBdNum, &ulErr);
//			switch(ulValue)
//			{
//			case 0: 
//				{
//					//Autocal FAILED log an error
//					break;
//				}
//			case MINUS_ONE_LONG:
//				{
//					// Autocal ERROR
//					break;
//				}
//			case 0x55:
//				{
//					//Insufficent Resources ERROR 
//					break;
//				}
//			case 0xAA:
//				{
//					//Autocal Interrupt ERROR
//					break;
//				}
//			default:
//				break;
//			}
//
//			Sleep(300);
//
//			GS66_18AI32SS_Dma_DataMode( ulBdNum, 0, &ulErr ); // Normal
//
//			// Setup CmdChaining here
//			memset(&m_DmaSetup, 0, sizeof(GS_DMA_DESCRIPTOR));
//			m_DmaSetup.DmaChannel = 1;
//			m_DmaSetup.NumDescriptors = 2;
//			m_DmaSetup.LocalToPciDesc_1 = 1;
//			m_DmaSetup.BytesDesc_1 = m_Block1.Size;
//			m_DmaSetup.PhyAddrDesc_1 = m_Block1.PhysicalAddr;
//			m_DmaSetup.InterruptDesc_1 = 1;
//			m_DmaSetup.LocalToPciDesc_2 = 1;
//			m_DmaSetup.BytesDesc_2 = m_Block2.Size;
//			m_DmaSetup.PhyAddrDesc_2 = m_Block2.PhysicalAddr;
//			m_DmaSetup.InterruptDesc_2 = 1;
//
//
//
//			if(GS66_18AI32SS_Setup_DmaCmdChaining(ulBdNum, &m_DmaSetup,  &ulErr))
//			{
//				// error
//				Reset();
//				return;
//			}
//
//			Sleep(300);
//
//			m_hGSEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
//			
//			if( m_hGSEvent == NULL )
//			{
//				//error
//				return;
//			}
//
//			//m_aMainBuff = new unsigned char[m_dwMainBuffSize/2]; // half second
//
//			if( !m_aMainBuff )
//			{
//				//throw 0; // memory exception
//			}
//
//			m_bInitialized = true;
//
//		}
//		catch(...)
//		{
//			throw;
//		}
//	}
//}

void
CEMSGSDataCollection::_Initialize()
{
	if( !m_bInitialized )
	{
		char cBoardInfo[400];
		unsigned long ulErr = 0;
		unsigned long ulBdNum = 1;
		unsigned long ulNumBds = 0;
		unsigned long ulValueRead = 0;
		unsigned long ulMemNeeded = 0;
		unsigned long ulBytes_needed = 0;
		ldiv_t result;


		try
		{
			/*if( m_lpLogFile )
			{
				fprintf( m_lpLogFile, "\n::_Init() - Begin\n" );
				fflush( m_lpLogFile );
			}*/

			ulNumBds = GS66_18AI32SS_FindBoards(&cBoardInfo[0], &ulErr);

			if(ulErr)
			{
				throw ulErr;
			}

			unsigned long ulHandle = GS66_18AI32SS_Get_Handle(&ulErr, ulBdNum);
			if(ulErr)
			{
				throw ulErr;
			}


			if(m_iNumChan == 0)
			{
				ulValueRead = GS66_18AI32SS_Read_Local32(ulBdNum, &ulErr, FW_REV);
				m_iNumChan = ( ulValueRead & 0x10000 ) ? 16:32;
			}

			double dSecondsToRun = 2.0;
			printf("CEMSGSDataCollection Initialize - Sample Rate: %d \n", m_dwSampleRate);
			ulMemNeeded = (U32)((double)m_dwSampleRate * (double)m_iNumChan);
			ulBytes_needed = ((double)ulMemNeeded*dSecondsToRun*(double)4.0); //one second

			LARGE_INTEGER sysFreq;
			if(QueryPerformanceFrequency(&sysFreq) == 0)
			{
				throw 0;
			}

			memset(&m_Block1, 0, sizeof(GS_PHYSICAL_MEM));
			memset(&m_Block2, 0, sizeof(GS_PHYSICAL_MEM));

			// This is the memory we will be using for DMA
			// Try for 1 seconds worth, but if > than can transfer in one block,
			// decrement till there
			while((ulMemNeeded*4) > ((1<<23)-1))
				ulMemNeeded /= 2;

			m_Block1.Size = ulMemNeeded*4;
			GS66_18AI32SS_Get_Physical_Memory(ulBdNum, &m_Block1, 1, &ulErr); // but settle for less
			m_blk1_allocated = m_Block1.Size;
			result = ldiv(m_Block1.Size,m_iNumChan);
			m_Block1.Size = (U32)(result.quot * m_iNumChan); // Ensure integer multiple of channels

			m_Block2.Size = m_Block1.Size;// Try to make them both equal, regardless of size
			GS66_18AI32SS_Get_Physical_Memory(ulBdNum, &m_Block2, 1, &ulErr); // 1 = will take less
			m_blk2_allocated = m_Block2.Size;
			result = ldiv(m_Block2.Size,m_iNumChan);
			m_Block2.Size = (U32)(result.quot * m_iNumChan); // Ensure integer multiple of channels

			GS66_18AI32SS_Initialize(ulBdNum, &ulErr);
			if(ulErr)
			{
				throw ulErr;
			}
			
			Sleep(2000);

			GS66_18AI32SS_Write_Local32(ulBdNum, &ulErr, RATE_A, 0x10000 | ((36000000/m_dwSampleRate)&0xFFFF)); // Sample Rate
			if(ulErr)
			{
				throw ulErr;
			}
			ulValueRead = (m_iNumChan==32)?5:4;
			ulValueRead |= 0x28; // RATE A and Enable Selected Clocking
			GS66_18AI32SS_Write_Local32(ulBdNum, &ulErr, SCAN_CNTRL, ulValueRead);
			if(ulErr)
			{
				throw ulErr;
			}
			// Auto Calibration
			unsigned long ulValue;
			ulValue = GS66_18AI32SS_Autocal(ulBdNum, &ulErr);
			if(ulErr)
			{
				throw ulErr;
			}


			switch(ulValue)
			{
			case 0: 
				{
					//Autocal FAILED log an error
					break;
				}
			case MINUS_ONE_LONG:
				{
					// Autocal ERROR
					break;
				}
			case 0x55:
				{
					//Insufficent Resources ERROR 
					break;
				}
			case 0xAA:
				{
					//Autocal Interrupt ERROR
					break;
				}
			default:
				break;
			}

			Sleep(300);

			// PLX_DEVICE_OBJECT m_pPlxObj;

			// memset(&m_pPlxObj, 0, sizeof(PLX_DEVICE_OBJECT));

			// PLX_DEVICE_KEY m_pPlxKey;

			// memset(&m_pPlxKey, -1, sizeof(PLX_DEVICE_KEY));

			// m_pPlxKey.DeviceId = 0x9056;
			// m_pPlxKey.VendorId = 0x10B5;

			// PLX_STATUS ps = PlxPci_DeviceFind(&m_pPlxKey, (U16)0);
			// if (ps != ApiSuccess)
			// {
			// // ERROR – Unable to locate any valid devices
			// } 

			// ps = PlxPci_DeviceOpen(&m_pPlxKey, &m_pPlxObj);

			// if (ps != ApiSuccess)
			// {
				// // ERROR - Unable to enable interrupts
			// } 

			// PLX_INTERRUPT m_pPlxIntr;

			// memset(&m_pPlxIntr, 0, sizeof(PLX_INTERRUPT));
 
			//m_pPlxIntr.LocalToPci = (1 << 0) | (1 << 1); //Sets local interrupt flag on PCI

			//ps = PlxPci_InterruptEnable(&m_pPlxObj, &m_pPlxIntr);

			//U32 ui_regValue = PlxPci_PlxRegisterRead(&m_pPlxObj, 0x54, &ps);

			//ui_regValue |= 0x3; //Sets interrupt enable and local interrupt enable bits

			//ps = PlxPci_PlxRegisterWrite(&m_pPlxObj, 0x54, ui_regValue);

			// void *m_usBarMap = NULL;

			// ps = PlxPci_PciBarMap(
                 // &m_pPlxObj,      // Opened device object
                 // 0,        // Which BAR? 0–5 on most PLX chips
                 // &m_usBarMap     // Returns mapping
             // );

			// {
				// //volatile U32 *pReg = (volatile U32 *)(&m_usBarMap + 0x54);
				// volatile U32 *pReg = (volatile U32 *)(&m_usBarMap + 0xE8);				
				// U32           val  = *pReg;
				// printf("Register @0x68 = 0x%08X\n", *pReg);

				// // To write:
				// *pReg |= 0x900;

				// printf("Register @0x68 = 0x%08X\n", *pReg);
			// }

			// PlxPci_PciBarUnmap(&m_pPlxObj, 0);

			// if (ps != ApiSuccess)
			// {
				// // ERROR - Unable to enable interrupts
			// } 

			SetThreadPriority(getHandle(),THREAD_PRIORITY_TIME_CRITICAL);

			GS66_18AI32SS_Dma_DataMode(ulBdNum, 0, &ulErr); // Normal
			if(ulErr)
			{
				throw ulErr;
			}

			// Setup CmdChaining here
			memset(&m_DmaSetup, 0, sizeof(GS_DMA_DESCRIPTOR));
			m_DmaSetup.DmaChannel = 1;
			m_DmaSetup.NumDescriptors = 2;
			m_DmaSetup.LocalToPciDesc_1 = 1;
			m_DmaSetup.BytesDesc_1 = m_Block1.Size;
			m_DmaSetup.PhyAddrDesc_1 = m_Block1.PhysicalAddr;
			m_DmaSetup.InterruptDesc_1 = 1;
			m_DmaSetup.LocalToPciDesc_2 = 1;
			m_DmaSetup.BytesDesc_2 = m_Block2.Size;
			m_DmaSetup.PhyAddrDesc_2 = m_Block2.PhysicalAddr;
			m_DmaSetup.InterruptDesc_2 = 1;

			if(GS66_18AI32SS_Setup_DmaCmdChaining(ulBdNum, &m_DmaSetup,  &ulErr))
			{
				// error
				Reset();
				return;
			}

			//Sleep(300);

			m_hGSEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
			
			if( m_hGSEvent == NULL )
			{
				//error
				return;
			}

			m_aMainBuff = new unsigned char[m_dwMainBuffSize/2]; // half second

			if( !m_aMainBuff )
			{
				//throw 0; // memory exception
			}

			m_bInitialized = true;

		}
		catch(...)
		{
			throw;
		}
	}
}

void
CEMSGSDataCollection::Start()
{
/*	if(!m_bInitialized)
	{
		_Initialize();
	}*/
	start();
}

void
CEMSGSDataCollection::run()
{
	if(!m_bInitialized)
	{
		_Initialize();
	}
	
	if( m_bInitialized )
	{
		EMS_RESULT hr = EMS_OK;
		unsigned long ulBdNum = 1;
		U32 ulErr = 0;
		unsigned long ulIndata = 0;
		unsigned long ulBufferIndex = 0;
		m_bRunning = true;


		HANDLE hEvent[2];

		hEvent[0] = m_hStopEvent;
		hEvent[1] = m_hGSEvent;

		DWORD dwTimeout = 2000; 
		DWORD dwEventCount = 2;

		bool b1Ready = 0;
		bool b2Ready = 0;
		bool bFirstOne = 1;

		//SetThreadPriority(getHandle(),THREAD_PRIORITY_TIME_CRITICAL); 
		
		//ulIndata = GS66_18AI32SS_Read_Local32(ulBdNum, &ulErr, BCR); // Set Local Interrupts to enabled on PCI Interrupt Register
		//unsigned long ulPciInterruptRegister = 0x68;
		//ulIndata = GS66_18AI32SS_Read_Local32(ulBdNum, &ulErr, ulPciInterruptRegister); // Set Local Interrupts to enabled on PCI Interrupt Register
		//unsigned long ulNewData = ulIndata | 0x800;
		//GS66_18AI32SS_Write_Local32(ulBdNum, &ulErr, ulPciInterruptRegister, ulNewData); 
		//ulIndata = GS66_18AI32SS_Read_Local32(ulBdNum, &ulErr, ulPciInterruptRegister); // Set Local Interrupts to enabled on PCI Interrupt Register

		
		// GS66_18AI32SS_Open_DMA_Channel(ulBdNum, 1, &ulErr);

		// ulIndata = GS66_18AI32SS_Read_Local32(ulBdNum, &ulErr, BCR);
		// ulIndata |= 0x800; // Disable Scan Marker - Only required for Native 18bit board
		// GS66_18AI32SS_Write_Local32(ulBdNum, &ulErr, BCR, ulIndata);

		// ulIndata = GS66_18AI32SS_Read_Local32(ulBdNum, &ulErr, RATE_A); // Disable Clock
		// GS66_18AI32SS_Write_Local32(ulBdNum, &ulErr, RATE_A, ulIndata|0x10000);

		// ulIndata = GS66_18AI32SS_Read_Local32(ulBdNum, &ulErr, IN_DATA_CNTRL); // Clear Buffer
		// GS66_18AI32SS_Write_Local32(ulBdNum, &ulErr, IN_DATA_CNTRL, ulIndata|0x40000);

		GS66_18AI32SS_EnableInterrupt(ulBdNum, 1, 1, &ulErr); // DMA Channel 1
		if(ulErr)
		{
			throw ulErr;
		}

		m_GSEvent.hEvent = (U64)m_hGSEvent;

		GS66_18AI32SS_Register_Interrupt_Notify(ulBdNum, &m_GSEvent, 1, 1, &ulErr);
		if(ulErr)
		{
			throw ulErr;
		}

		if(GS66_18AI32SS_Start_DmaCmdChaining(ulBdNum, m_DmaSetup.DmaChannel,  &ulErr))
		{
			// error
			Reset();
			return;
		}

		ulIndata = GS66_18AI32SS_Read_Local32(ulBdNum, &ulErr, RATE_A);         // Enable Clock
		GS66_18AI32SS_Write_Local32(ulBdNum, &ulErr, RATE_A, ulIndata & 0xFFFEFFFF); 
		if(ulErr)
		{
			throw ulErr;
		}

		int iCounterHalfSecond = 1;
		const CEMSSystemClock c_sysClock;

		EMSTIME timeStart;

		double dTDiff = 0.0;

		timeStart = c_sysClock.GetTime();

		while( m_bRunning )
		{
			
			try
			{
				hr = WaitForMultipleObjects( dwEventCount, hEvent, FALSE, dwTimeout ); // Wait for the interrupt
				//hr = WaitForSingleObject( m_hGSEvent, 2000 ); // Wait for the interrupt
				switch(hr)	
				 {						
					case WAIT_OBJECT_0:	
						{
							//stop
							m_bRunning = false;
						}
						break;
					case WAIT_OBJECT_0 + 1:
						{
							if( bFirstOne )
							{
								b1Ready = 1;
								b2Ready = 0;
								bFirstOne = 0;
							}

							if(b1Ready)
							{
								b1Ready = 0;

								memmove( &m_aSharedBuff[ulBufferIndex], (void*)(m_Block1.UserAddr), m_Block1.Size ); 

								ulBufferIndex += m_Block1.Size;
								b2Ready = 1;

							}
							else if(b2Ready)
							{
								b2Ready = 0;
								
								memmove(&m_aSharedBuff[ulBufferIndex], (void*)(m_Block2.UserAddr), m_Block2.Size); 

								ulBufferIndex += m_Block2.Size;
								b1Ready = 1;
								//SetEvent( m_hSharedBuff );
							}

							if( (ulBufferIndex+1) >= 64000000 )
//							if( (ulBufferIndex+1) >= 32000000 )
							{
//								if( ulBufferIndex > 32000000 )
								if( ulBufferIndex > 64000000 )
								{
									printf("\n ************** Check, overflow ********** size = %d", ulBufferIndex );
								}
								SetEvent( m_hSharedBuff );
								ulBufferIndex = 0;


								CEMSTime oCurrent(c_sysClock.GetTime());

								dTDiff = oCurrent.SecondsDifferent(timeStart);

								Sleep(5);
								//printf("\n half second RAW data, number: %d, timeDiff: %f", iCounterHalfSecond++, dTDiff );
								std::cout << "\n RAW data, number: " << iCounterHalfSecond++ << " timeDiff: " <<  dTDiff << std::endl;

								iCounterHalfSecond++;
								//if(iCounterHalfSecond >= 2000)
									//m_bRunning = false;

								if(iCounterHalfSecond == 9)
									m_bRunning = true;

								//timeStart = oCurrent;
							}
							ResetEvent(m_hGSEvent);
						}
						break;
					default:
						{
							//error
							//m_bRunning = false;
						}
						break;
				}
			}
			catch( ... )
			{
				// a error occured, log it and stop the thread.
				m_bRunning = false;
			}
		}

		m_bRunning = false;


		// Stop Cmd Chaining here
		GS66_18AI32SS_Cancel_Interrupt_Notify(ulBdNum, &m_GSEvent, &ulErr);
		GS66_18AI32SS_Close_DmaCmdChaining(ulBdNum, m_DmaSetup.DmaChannel,  &ulErr);
		m_Block1.Size = m_blk1_allocated;
		m_Block2.Size = m_blk2_allocated;
		GS66_18AI32SS_Free_Physical_Memory(ulBdNum, &m_Block1, &ulErr);
		GS66_18AI32SS_Free_Physical_Memory(ulBdNum, &m_Block2, &ulErr);
		CloseHandle(m_hGSEvent);
		m_hGSEvent = 0;
		GS66_18AI32SS_DisableInterrupt(ulBdNum, 0, 1, &ulErr);
//		GS66_18AI32SS_Reset_Device(ulBdNum, &ulErr);
		GS66_18AI32SS_Close_Handle(ulBdNum, &ulErr);
		if(ulErr)
		{
			//ShowAPIError(ulErr);
			//exit(0);
		}
	}
}

void 
CEMSGSDataCollection::Stop()
{
//	GS66_18AI32SS_Close_Handle(ulBdNum, &ulErr);
	m_bRunning = false;
}
