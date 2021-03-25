#include "CString1.h"

CString1::CString1(const char* inp, const char *FileName) : CString(inp) {
    if(FileName == nullptr){
        file = nullptr;
        return;
    }
    size_t s = strsize(FileName) + 1;
    file = new char[s];
    memcpy(file,FileName,s);
}

CString1 operator+(const CString1 &l, const CString &r) {
    CString1 a = l;
    a += r;
    return a;
}

int CString1::output() {
    if(file == nullptr){
        return 1;
    }
    std::ofstream out(file,std::ios::app);
    for(size_t i = 1; i < getSize(); i++){
        out << str[i] << std::endl;
    }
    out << std::endl;
    out.close();
    return 0;
}

