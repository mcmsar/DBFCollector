#ifndef __PIPELINE_RETRY_H__
#define __PIPELINE_RETRY_H__

#include "emsexcpt.h"

static const wchar_t *c_wszKeyTimeOut = L"Pipeline.Write.Timeout";
static const wchar_t *c_wszKeyLutiD = L"LutID";

#define THROW_IF_FAILED(ComFunc)\
    FAILED(hr = ComFunc) ? throw CEMSException(__LINE__, __FILE__, hr ) : 0;

#endif