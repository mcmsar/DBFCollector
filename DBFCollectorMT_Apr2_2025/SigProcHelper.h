#ifndef SIG_PROC_HELPERS_H
#define SIG_PROC_HELPERS_H

#include "emsDBFtypes2.h"
#include <math.h>

class CSigProcHelpers {
public:
    static float _EMSsMaxExt(const float *vec, int len, ULONG* index) {
        float fMaxVal = -1.0;
        for(ULONG i = 0; i < (ULONG)len; i++) {
            if(fMaxVal < vec[i]) {
                fMaxVal = vec[i];
                *index = i;
            }
        }
        return fMaxVal;
    }

    static float _EMSsMean(const float *vec, ULONG len) {
        float fMean = 0.0;
        for(ULONG i = 0; i < len; i++) fMean += vec[i];
        return (len > 0) ? fMean / (float)len : 0.0f;
    }

    static void _EMScbPowerSpectr(const EMSCOMPLEX *src, float *spectr, ULONG length) {
        if(src && spectr) {
            for(ULONG i = 0; i < length; i++) {
                spectr[i] = (float)sqrt(src[i].re * src[i].re + src[i].im * src[i].im);
            }
        }
    }
};

#endif