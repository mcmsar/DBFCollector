/********************************************************************
*	Module:			EMSFStrm.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2001/07/30		rvw		start
		2003/11/07		ch		Support open of an existing file for edit (previously 
								choices were read-existing OR write-new)

********************************************************************/
#ifndef INC_EMSFSTRM
#define INC_EMSFSTRM

#include "aobjbase.h"
#include "emspipe.h"

class CEMSFileStream : public IEMSRandomStream, public CApiObjBase
{
public:
	CEMSFileStream( );

/*********************************************************************
*	Public Methods
*********************************************************************/
	EMS_RESULT OpenFile( LPCTSTR lpcszFile, BOOL bReadWrite=TRUE, BOOL bAppend=FALSE, BOOL bAllowEdit=FALSE );
	EMS_RESULT CreateFile( LPCTSTR lpcszFile ) { return OpenFile( lpcszFile ); }
	EMS_RESULT CloseFile( void );

/*********************************************************************
*	IEMSSeqStream Methods
*********************************************************************/

	virtual HRESULT STDMETHODCALLTYPE Read( 
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbRead);
        
	virtual HRESULT STDMETHODCALLTYPE Write( 
            /* [size_is][in] */ const BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbWritten);

/*********************************************************************
*	IEMSRandomStream Methods
*********************************************************************/
	HRESULT STDMETHODCALLTYPE MoveFirst( void);
        
    HRESULT STDMETHODCALLTYPE MoveLast( void);
    
    HRESULT STDMETHODCALLTYPE Move( 
        /* [in] */ const long clIndex);

/*********************************************************************
*	IUnknown Methods
*********************************************************************/
	STDMETHOD(QueryInterface)		(THIS_ REFIID, LPVOID FAR *);
	STDMETHOD_(ULONG, AddRef)		(THIS);
	STDMETHOD_(ULONG, Release)		(THIS);

	EMS_RESULT OpenFileW( const wchar_t* cwszFile, BOOL bReadWrite=TRUE, BOOL bAppend=FALSE, BOOL bAllowEdit=FALSE );

	EMS_RESULT Flush();

protected: // methods
	virtual ~CEMSFileStream();

private: // methods
	EMS_RESULT _GetErrorCode( void );

private: // data
	LPVOID	m_lpFile;
};

#endif // INC_EMSFSTRM
