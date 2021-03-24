#pragma once
#include "CString.h"

class CString0 : public CString{
public:
    using CString::operator=;
    using CString::CString;
    int output() override;

    CString0(const char* inp = "", const char *FileName = nullptr);
    CString0(const CString& r) : CString(r) { }
    CString0(CString&& r) : CString(std::move(r)) { }
    ~CString0() {}

    friend CString0 operator+(const CString0& l, const CString& r);
};
