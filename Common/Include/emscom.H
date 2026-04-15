/********************************************************************
*	Module:			EMSCom.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Platform independent Component Object Model defines
*						and macros
*						
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	   Copyright (c) 2000 by EMS Technologies Canada, Ltd. Ottawa ON
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies Canada, Ltd.  It may 
* not be reproduced in whole or in part, in any form or by any means 
* whatsoever without the express written permission of EMS Technologies 
* Canada, Ltd.
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	99/07/27		rvw	start

********************************************************************/
#ifndef INC_EMSCOM
#define INC_EMSCOM

#include "emstypes.h"

#ifdef _WIN32
	#include <objbase.h>
#endif // _WIN32

#include "emserror.h"

#ifndef STDAPICALLTYPE

#ifdef _MAC
#define STDAPICALLTYPE          pascal

#define STDAPI                  EXTERN_C STDAPICALLTYPE HRESULT
#define STDAPI_(type)           EXTERN_C STDAPICALLTYPE type

#else   //  !_MAC

#ifdef WIN32
	#define STDAPICALLTYPE          __export __stdcall

	#define STDAPI                  EXTERN_C HRESULT STDAPICALLTYPE
	#define STDAPI_(type)           EXTERN_C type STDAPICALLTYPE

#elif _WIN16
	#define STDAPICALLTYPE          __export FAR _pascal

	#define STDAPI                  EXTERN_C HRESULT STDAPICALLTYPE
	#define STDAPI_(type)           EXTERN_C type STDAPICALLTYPE
#else
	#define STDAPICALLTYPE          FAR PASCAL

	#define STDAPI                  EXTERN_C HRESULT STDAPICALLTYPE
	#define STDAPI_(type)           EXTERN_C type STDAPICALLTYPE

#endif

#endif //!_MAC

#endif // !STDAPICALLTYPE


#ifndef STDMETHODCALLTYPE
	#if defined(_WIN32) || defined(_MPPC_)
		#ifdef _MPPC_
			#define STDMETHODCALLTYPE       __cdecl
		#else
			#define STDMETHODCALLTYPE       __stdcall
		#endif
	#elif defined(_WIN16)
		#define STDMETHODCALLTYPE       __export FAR CDECL
	#else
		#define STDMETHODCALLTYPE			FAR CDECL
	#endif
#endif

#ifndef STDMETHODIMP
	#define STDMETHODIMP            EMS_RESULT STDMETHODCALLTYPE
#endif

#ifndef STDMETHODIMP_
	#define STDMETHODIMP_(type)     type STDMETHODCALLTYPE
#endif


#ifndef EXTERN_C
	#ifdef __cplusplus
		#define EXTERN_C    extern "C"
	#else
		#define EXTERN_C    extern
	#endif
#endif

#ifndef GUID_DEFINED
	#define GUID_DEFINED
	typedef struct _GUID
	{
    unsigned long Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char Data4[8];
	} GUID;
#endif /* GUID_DEFINED */

#if !defined( __IID_DEFINED__ )
	#define __IID_DEFINED__
	typedef GUID IID;
	#define IID_NULL            GUID_NULL
	typedef GUID CLSID;
	#define CLSID_NULL          GUID_NULL

#if defined(__cplusplus)
#ifndef _REFGUID_DEFINED
	#define _REFGUID_DEFINED
	#define REFGUID             const GUID FAR &
#endif

#ifndef _REFIID_DEFINED
	#define _REFIID_DEFINED
	#define REFIID              const IID FAR &
#endif

#ifndef _REFCLSID_DEFINED
	#define _REFCLSID_DEFINED
	#define REFCLSID            const CLSID FAR &
#endif
#else
#ifndef _REFGUID_DEFINED
#define _REFGUID_DEFINED
#define REFGUID             const GUID FAR * const
#endif
#ifndef _REFIID_DEFINED
#define _REFIID_DEFINED
#define REFIID              const IID FAR * const
#endif
#ifndef _REFCLSID_DEFINED
#define _REFCLSID_DEFINED
#define REFCLSID            const CLSID FAR * const
#endif
#endif
#endif

#ifdef EMSINITGUID
	#ifdef WIN32
		#define INITGUID
	#else
		#undef INITGUID
	#endif
#endif

#ifndef DEFINE_GUID
#ifndef INITGUID
	#define DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
  	EXTERN_C const GUID FAR name
	#else
		#define DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
        EXTERN_C const GUID FAR name \
                = { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }
#endif // INITGUID
#endif // DEFINE_GUID

#ifndef IsEqualIID
#include <memory.h>		/* for memcmp */

#ifdef __cplusplus
	inline BOOL IsEqualGUID(REFGUID rguid1, REFGUID rguid2)
	{
    return !_fmemcmp(&rguid1, &rguid2, sizeof(GUID));
	}

	inline void SetGUID(GUID& rguid1, REFGUID rguid2)
	{
    _fmemcpy(&rguid1, &rguid2, sizeof(GUID));
	}
#else
	#define IsEqualGUID(rguid1, rguid2) (!_fmemcmp(rguid1, rguid2, sizeof(GUID)))
	#define SetGUID(rguid1, rguid2) (_fmemcpy(rguid1, rguid2, sizeof(GUID)))
#endif

#define IsEqualIID(riid1, riid2) IsEqualGUID(riid1, riid2)
#define IsEqualCLSID(rclsid1, rclsid2) IsEqualGUID(rclsid1, rclsid2)

#define SetIID(riid1, riid2)	    SetGUID(riid1, riid2)
#define SetCLSID(rclsid1, rclsid2)  SetGUID(rclsid1, rclsid2)
#endif // IsEqualIID

#if !defined(DECLSPEC_IMPORT)
	#if (defined(_M_MRX000) || defined(_M_IX86) || defined(_M_ALPHA) || defined(_M_PPC)) && !defined(MIDL_PASS)
		#define DECLSPEC_IMPORT __declspec(dllimport)
	#else
		#define DECLSPEC_IMPORT
	#endif
#endif


#ifndef WINOLEAPI
	#ifdef _OLE32_
	#define WINOLEAPI        STDAPI
	#define WINOLEAPI_(type) STDAPI_(type)
	#else

	#ifdef _68K_
	#ifndef REQUIRESAPPLEPASCAL
	#define WINOLEAPI        EXTERN_C DECLSPEC_IMPORT HRESULT PASCAL
	#define WINOLEAPI_(type) EXTERN_C DECLSPEC_IMPORT type PASCAL
	#else
	#define WINOLEAPI        EXTERN_C DECLSPEC_IMPORT PASCAL HRESULT
	#define WINOLEAPI_(type) EXTERN_C DECLSPEC_IMPORT PASCAL type
	#endif
	#else
	#define WINOLEAPI        EXTERN_C DECLSPEC_IMPORT HRESULT STDAPICALLTYPE
	#define WINOLEAPI_(type) EXTERN_C DECLSPEC_IMPORT type STDAPICALLTYPE
	#endif

	#endif

#endif // WINOLEAPI

/****** Interface Declaration ***********************************************/

#ifndef STDMETHOD
	#if defined(__cplusplus) && !defined(CINTERFACE)
//		#ifdef __TURBOC__
		#ifdef __BORLANDC__
			#define interface               struct FAR
//			#define interface               struct huge
		#else
			#define interface               struct FAR
		#endif
	#define STDMETHOD(method)       virtual EMS_RESULT STDMETHODCALLTYPE method
	#define STDMETHOD_(type,method) virtual type STDMETHODCALLTYPE method
	#define PURE                    = 0
	#define THIS_
	#define THIS                    void
	#define DECLARE_INTERFACE(iface)    interface iface
	#define DECLARE_INTERFACE_(iface, baseiface)    interface iface : public baseiface

	#if !defined(BEGIN_INTERFACE)
	#if defined(_MPPC_)  && \
    	( (defined(_MSC_VER) || defined(__SC__) || defined(__MWERKS__)) && \
    	!defined(NO_NULL_VTABLE_ENTRY) )
   	#define BEGIN_INTERFACE virtual void a() {}
   	#define END_INTERFACE
	#else
   	#define BEGIN_INTERFACE
   	#define END_INTERFACE
	#endif
	#endif

	#else

	#define interface               struct

	#define STDMETHOD(method)       EMS_RESULT (STDMETHODCALLTYPE * method)
	#define STDMETHOD_(type,method) type (STDMETHODCALLTYPE * method)

	#if !defined(BEGIN_INTERFACE)
	#if defined(_MPPC_)
    	#define BEGIN_INTERFACE       void    *b;
    	#define END_INTERFACE
	#else
    	#define BEGIN_INTERFACE
    	#define END_INTERFACE
	#endif
	#endif


	#define PURE
	#define THIS_                   INTERFACE FAR* This,
	#define THIS                    INTERFACE FAR* This
	#ifdef CONST_VTABLE
	#undef CONST_VTBL
	#define CONST_VTBL const
	#define DECLARE_INTERFACE(iface)    typedef interface iface { \
                                    	const struct iface##Vtbl FAR* lpVtbl; \
                                	} iface; \
                                	typedef const struct iface##Vtbl iface##Vtbl; \
                                	const struct iface##Vtbl
	#else
	#undef CONST_VTBL
	#define CONST_VTBL
	#define DECLARE_INTERFACE(iface)    typedef interface iface { \
                                    	struct iface##Vtbl FAR* lpVtbl; \
                                	} iface; \
                                	typedef struct iface##Vtbl iface##Vtbl; \
                                	struct iface##Vtbl
	#endif
	#define DECLARE_INTERFACE_(iface, baseiface)    DECLARE_INTERFACE(iface)

	#endif
#endif // STDMETHOD


#ifndef __IUnknown_INTERFACE_DEFINED__
#define __IUnknown_INTERFACE_DEFINED__
/*
 *  IID_IUnknown:
 *
 *	{00000000-0000-0000-C000000000000046}
 *
 */
DEFINE_GUID(IID_IUnknown, 0x00000000, 0x0000, 0x0000, 0xC0, 0x00, 
				0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

#undef  INTERFACE
#define INTERFACE   IUnknown

DECLARE_INTERFACE(IUnknown)
{
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR * ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;
};

typedef        IUnknown FAR* LPUNKNOWN;

#endif // __IUnknown_INTERFACE_DEFINED__

#ifndef InterlockedIncrement
    #ifndef WIN32
	    #error "Not implemented for non-WIN32 platforms."
    #endif
#endif

#ifndef InterlockedDecrement
    #ifndef WIN32
        #error "Not implemented for non-WIN32 platforms."
    #endif
#endif

typedef enum tagEMSCLSCTX
{
	EMSCLSCTX_UNKNOWN			= 0x0,
	EMSCLSCTX_INPROC_SERVER	= 0x1,
	EMSCLSCTX_INPROC_HANDLER	= 0x2,
	EMSCLSCTX_LOCAL_SERVER	= 0x4,
	EMSCLSCTX_INPROC_SERVER16	= 0x8,
	EMSCLSCTX_REMOTE_SERVER	= 0x10,
	EMSCLSCTX_INPROC_HANDLER16	= 0x20,
	EMSCLSCTX_INPROC_SERVERX86	= 0x40,
	EMSCLSCTX_INPROC_HANDLERX86	= 0x80,
	EMSCLSCTX_ESERVER_HANDLER	= 0x100
}	EMSCLSCTX;

typedef enum tagEMSTHREADMODEL
{
	EMSTHREADMODEL_UNKNOWN		= 0x0,
	EMSTHREADMODEL_FREE			= 0x1,
	EMSTHREADMODEL_BOTH			= 0x2,
	EMSTHREADMODEL_APARTMENT	= 0x3
} EMSTHREADMODEL;



#endif     // INC_EMSCOM
