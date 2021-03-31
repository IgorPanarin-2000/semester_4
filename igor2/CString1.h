#pragma once
#include "CString.h"

class CString1 : public CString{
public:
    using CString::operator=;
    int output() override;

    CString1(std::string inp = "", std::string FileName = "") : CString(inp, FileName) {}
    CString1(const CString& r) : CString(r) { }
    CString1(const CString1& r) : CString(r) { }
    CString1(CString&& r) noexcept : CString(std::move(r)) { }
    CString1(CString1&& r) noexcept : CString(std::move(r)) { }
    ~CString1() { }

    friend CString1 operator+(const CString1& l, const CString& r);
};

