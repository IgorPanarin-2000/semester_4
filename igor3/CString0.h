#pragma once
#include "CString.h"

class CString0 : public CString{
public:
    using CString::operator=;
    int output() override;

    CString0(std::string inp = "", std::string FileName = "") : CString(inp, FileName) {}
    CString0(const CString& r) : CString(r) { }
    CString0(const CString0& r) : CString(r) { }
    CString0(CString&& r) noexcept : CString(std::move(r)) { }
    CString0(CString0&& r) noexcept : CString(std::move(r)) { }
    ~CString0() {}

    friend CString0 operator+(const CString0& l, const CString& r);
};
