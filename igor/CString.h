#pragma once

#include <cstddef>
#include <cstring>
#include <fstream>
#include <iostream>

size_t strsize(const char* str);

class CString{
protected:
    char* str;
    size_t size;
    char* file;
public:
    CString();
    CString(const char* inp);
    CString(const CString& r);
    CString(CString&& r) noexcept;
    virtual ~CString();
    operator const char*() const;
    int getSize() { return size; }
    CString& operator+=(const CString& r);
    CString& operator=(const CString& r);
    CString& operator=(CString&& r) noexcept;
    CString& operator=(const char* inp){
        size = strsize(inp);
        delete[] str;
        delete[] file;
        file = nullptr;
        str = new char[size+1];
        memcpy(str,inp,size+1);
        return *this;
    }

    virtual int output()=0;
};
