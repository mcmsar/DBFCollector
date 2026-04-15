#ifndef Memory_Functions_H
#define Memory_Functions_H

// SARSAT standard headers
#include "Standards.h"

extern TSuccess Allocate( char *AllocName, void **AllocP, long AllocSize );

extern TSuccess ReAllocate( char *AllocName, void **AllocP );

extern TSuccess DeAllocate( char *AllocName, void *AllocP );

#endif
