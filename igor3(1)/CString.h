#pragma once
#include <string>
#include <cstddef>
#include <cstring>
#include <fstream>
#include <iostream>

class CString{
protected:
    std::string str;
    size_t size;
    std::string file;
public:
    CString();
    CString(std::string inp, std::string FileName);
    CString(const CString& r);
    CString(CString&& r) noexcept;
    virtual ~CString();
    operator const char*() const;
    size_t getSize() { return size; }
    CString& operator+=(const CString& r);
    CString& operator=(const CString& r);
    CString& operator=(CString&& r) noexcept;
    CString& operator=(std::string inp);

    virtual int output()=0;
};
