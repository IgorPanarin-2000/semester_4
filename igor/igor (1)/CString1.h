#pragma once
#include "CString.h"

class CString1 : public CString{
public:
    using CString::operator=;
    using CString::CString;
    int output() override;

    CString1(const char* inp = "", const char* FileName = nullptr) : CString(inp, FileName) {}
    CString1(const CString& r) : CString(r) { }
    CString1(CString&& r) : CString(std::move(r)) { }
    ~CString1() { }

    friend CString1 operator+(const CString1& l, const CString& r);
};

