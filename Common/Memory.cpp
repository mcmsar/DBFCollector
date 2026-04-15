// Memory access functions  

// Precompiled system headers
#include <stdio.h>
#pragma hdrstop

// Memory headers
#include "Memory_Functions.h"

// Cmemmgr specific headers
#include "cMMlib.h"

//#define EMS_DEBUG

#ifdef EMS_DEBUG
#include "debugwin.h"
static CDebugWin debugWin;
static char szDebug[256];
#endif // EMS_DEBUG

//---------------------------------------------------------------------------
TSuccess Allocate( char *AllocName, void **AllocP, long AllocSize )
{
   TSuccess Success;
   long Size=0, lActualSize=0;

   Success = false;
   *AllocP = 0;
   if (strlen(AllocName) < 17)
   {
      Size = (AllocSize + 1023) / 1024;
#ifdef EMS_DEBUG
      wsprintf( szDebug, "MEMORY: Requested %15s:%8d  bytes\n", AllocName, AllocSize );
		 debugWin.OutputMsg( szDebug );
#endif
      *AllocP = CMM_CreateMem( AllocName, &Size );

#ifdef EMS_DEBUG
      wsprintf( szDebug, "CMM_CreateMem: ptr(%ld) %s size(%ld)", *AllocP, AllocName, Size );
		 debugWin.OutputMsg( szDebug );
#endif

      if ( *AllocP != NULL )
      {
         if ( Size != 0 )
         {
			 	lActualSize = Size;
#ifdef EMS_DEBUG
            wsprintf( szDebug, "ALLOC: Created %15s:%8d  bytes @%08x (Unused=%d bytes)\n",
               AllocName, Size*1024, *AllocP, Size*1024-AllocSize );
				 debugWin.OutputMsg( szDebug );
#endif
            Success = true;
         }
         else
         {
#ifdef EMS_DEBUG
            wsprintf( szDebug, "ALLOC: Error creating memory area %s\n", AllocName );
				 debugWin.OutputMsg( szDebug );
#endif
         }
      }
      else
      {
         *AllocP = CMM_OpenMem( AllocName, &lActualSize );
         if ( *AllocP != NULL )
         {
#ifdef EMS_DEBUG
            wsprintf( szDebug, "ALLOC: Opened %15s @%08x\n", AllocName, *AllocP );
				 debugWin.OutputMsg( szDebug );
#endif
            Success = true;
         }
         else
         {
#ifdef EMS_DEBUG
            wsprintf( szDebug, "ALLOC: Error opening memory area %15s\n", AllocName );
				 debugWin.OutputMsg( szDebug );
#endif
         }
      }
   }
   else
   {
#ifdef EMS_DEBUG
      wsprintf( szDebug, "ALLOC: Error naming memory area %s\n", AllocName );
		 debugWin.OutputMsg( szDebug );
#endif
   }
#ifdef EMS_DEBUG
     wsprintf( szDebug, " Tracer %ld - %ld \n",  lActualSize * 1024, AllocSize ); 	
		debugWin.OutputMsg( szDebug );
#endif // EMS_DEBUG
	// let's make sure that what we received is what we asked for		
	if ( Success && ( ( lActualSize * 1024 ) < AllocSize ) )
	{
		Success = FALSE;
	}

   return( Success );
}

//---------------------------------------------------------------------------
TSuccess ReAllocate( char *AllocName, void **AllocP )
{
   TSuccess Success;
   long lActualSize=0;

   Success = false;
   *AllocP = 0;
   if (strlen(AllocName) < 17)
   {
#ifdef EMS_DEBUG
      wsprintf( szDebug, "MEMORY: Requested %15s\n", AllocName );
		 debugWin.OutputMsg( szDebug );

#endif
      *AllocP = CMM_OpenMem( AllocName, &lActualSize );
      if ( *AllocP != NULL )
      {
#ifdef EMS_DEBUG
         wsprintf( szDebug, "ALLOC: Opened %15s @%08x\n", AllocName, *AllocP );
			 debugWin.OutputMsg( szDebug );
#endif
         Success = true;
      }
      else
      {
#ifdef EMS_DEBUG
         wsprintf( szDebug,"ALLOC: Error opening memory area %15s\n", AllocName );
		 	debugWin.OutputMsg( szDebug );
#endif
      }
   }
   else
   {
#ifdef EMS_DEBUG
      wsprintf( szDebug, "ALLOC: Error naming memory area %s\n", AllocName );
		 debugWin.OutputMsg( szDebug );
#endif
   }

   return( Success );
}

//---------------------------------------------------------------------------
TSuccess DeAllocate( char *AllocName, void *AllocP )
{
   TSuccess Success;

   Success = false;
   if (strlen(AllocName) < 17)
   {
      if (AllocP)
      {
         CMM_CloseMem( AllocName );
         Success = true;
      }
   }
   else
   {
#ifdef EMS_DEBUG
      wsprintf( szDebug, "ALLOC: Error naming memory area %s\n", AllocName );
		 debugWin.OutputMsg( szDebug );
#endif
   }

   return( Success );
}

//---------------------------------------------------------------------------
