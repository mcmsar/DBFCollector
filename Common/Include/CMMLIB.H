
extern "C" __declspec(dllimport) VOID * __stdcall CMM_CreateMem( char *pName, long *pSizeKB );
extern "C" __declspec(dllimport) VOID * __stdcall CMM_OpenMem(   char *pName, long *pSizeKB  );
extern "C" __declspec(dllimport) long   __stdcall CMM_CloseMem(  char *pName );
extern "C" __declspec(dllimport) VOID   __stdcall CMM_Debug(     long level  );
