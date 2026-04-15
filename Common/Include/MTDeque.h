/********************************************************************
*	Module:			MTDeque.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	 
*					 
*				This file contains the definition for general class MTDeque, a
*					double ended queue of any type that is multithread safe.
*					This class is used to implemnet the I/O buffers for class
*					Win32Port and SARAntenna.
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2001 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth			Changes
	===	====			====			=======

	0.0	2001/05/01		Igor Zabarsky	start

********************************************************************/


#if !defined(AFX_MTDEQUE_H__C8328842_583A_11D5_9E1F_9C520CE36739__INCLUDED_)
#define AFX_MTDEQUE_H__C8328842_583A_11D5_9E1F_9C520CE36739__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

template <class T>
class MTdeque
{
protected :
    const int m_iMaxSize;
    deque<T> m_Queue;
    CRITICAL_SECTION m_Lock;
public :
    MTdeque( int max_size ) : m_iMaxSize( max_size )
    {
        ::InitializeCriticalSection( &m_Lock );
    }
    ~MTdeque()
    {
        ::DeleteCriticalSection( &m_Lock );
    }
    //
    // This is a multithread safe version of the function
    // that tells us how much free space is in the queue.
    // There is a belt and suspenders check to make sure we
    // don't return a negative number if the user has
    // somehow exceeded the maximum size of the queue.
    //
    int SpaceFree()
    {
        ::EnterCriticalSection( &m_Lock );
        int size = m_iMaxSize - m_Queue.size();
        ::LeaveCriticalSection( &m_Lock );
        return ( size < 0 ) ? 0 : size;
    }


    int SpaceUsed()
    {
        ::EnterCriticalSection( &m_Lock );
        int size = m_Queue.size();
        ::LeaveCriticalSection( &m_Lock );
        return size;
    }


    int Insert( T c )
    {
        int return_value;
        ::EnterCriticalSection( &m_Lock );
        if ( m_Queue.size() < m_iMaxSize ) {
            m_Queue.push_back( c );
            return_value = 1;				//OK
        } else
            return_value = -1;				//FALSE
        ::LeaveCriticalSection( &m_Lock );
        return return_value;
    }


    int Insert( T *data, int count )
    {
        ::EnterCriticalSection( &m_Lock );
        int actual = m_iMaxSize - m_Queue.size() ;
        if ( actual < 0 )
            actual = 0;
        if ( count < actual )
            actual = count;
        for ( int i = 0 ; i < actual ; i++ )
            m_Queue.push_back( *data++ );
        ::LeaveCriticalSection( &m_Lock );
        return actual;
    }

	int DisplayIn(T *data, int count)
	{
		::EnterCriticalSection(&m_Lock);
		int actual = m_iMaxSize - m_Queue.size() - count;
		while(actual++ < 0)
			m_Queue.pop_front();
		for(int i = 0; i < count; i++)
			m_Queue.push_back(*data++);
		::LeaveCriticalSection(&m_Lock);
		return count;
	}

    int Extract( T *data, int max )
    {
        int i = 0;
        ::EnterCriticalSection( &m_Lock );
        while ( i < max && m_Queue.size() ) 
		{
            data[ i++ ] = m_Queue.front();
            m_Queue.pop_front();
        }
        ::LeaveCriticalSection( &m_Lock );
        return i;
    }


    int Peek( T *data, int max )
    {
		int i;
        ::EnterCriticalSection( &m_Lock );
        if ( max > m_Queue.size() )
            max = m_Queue.size();
        for ( i = 0 ; i < max ; i++ )
            data[ i ] = m_Queue.begin()[ i ];
        ::LeaveCriticalSection( &m_Lock );
        return i;
    }


    T Extract()
    {
        T ret_val;

        ::EnterCriticalSection( &m_Lock );
        if ( m_Queue.size() ) 
		{
            ret_val = m_Queue.front() & 0xff;
            m_Queue.pop_front();
        }
        ::LeaveCriticalSection( &m_Lock );
        return ret_val;
    }
    //
    T ExtractD()
    {
        T ret_val;

        ::EnterCriticalSection( &m_Lock );
        if ( m_Queue.size() ) 
		{
            ret_val = m_Queue.front();
            m_Queue.pop_front();
        }
        ::LeaveCriticalSection( &m_Lock );
        return ret_val;
    }
    //
    // This member just empties the queue.
    //
    void Clear()
    {
        ::EnterCriticalSection( &m_Lock );
        m_Queue.clear();
        ::LeaveCriticalSection( &m_Lock );
    }

	bool Cansel(T data)
	{
		T ret_val;
		bool find = false;

        ::EnterCriticalSection( &m_Lock );
        for(int i = m_Queue.size(); i; i--)
			if(T == m_Queue.back())
			{
				find = true;
				m_Queue.pop_back();
			}
			else
			{
				ret_val = m_Queue.pop_end();
				m_Queue.push(ret_val);
			}
        ::LeaveCriticalSection( &m_Lock );

		return find;
	}
};

#endif // !defined(AFX_MTDEQUE_H__C8328842_583A_11D5_9E1F_9C520CE36739__INCLUDED_)
