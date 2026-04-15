/*********************************************************************
* Win32Stubs.cpp
*
* Stub implementations of MKL functions used by HGTEigenVectors.cpp.
* Intel MKL 2025.1 on this system is x64-only; no Win32 (ia32) MKL
* libraries are available.  These no-op stubs allow the Win32 build
* to link.  The eigendecomposition will not produce correct results
* on Win32; callers that require it should guard with #ifdef _WIN64.
*
* Compiled only for Win32 (_WIN64 is not defined); on x64 the entire
* file compiles to nothing.
*********************************************************************/

#ifndef _WIN64

#include "mkl_trans.h"
#include "mkl_lapacke.h"
#include <string.h>

void MKL_Cimatcopy( char ordering, char trans,
                    size_t rows, size_t cols,
                    const MKL_Complex8 alpha,
                    MKL_Complex8* AB, size_t lda, size_t ldb )
{
    /* Win32 stub: MKL not available for 32-bit builds. */
}

lapack_int LAPACKE_cheevd( int matrix_layout, char jobz, char uplo,
                            lapack_int n,
                            lapack_complex_float* a, lapack_int lda,
                            float* w )
{
    /* Win32 stub: MKL not available for 32-bit builds.
       Zero the output eigenvalue array so callers don't read garbage. */
    if ( w && n > 0 )
        memset( w, 0, (size_t)n * sizeof(float) );
    return 0;
}

#endif /* !_WIN64 */
