#include "CString0.h"

CString0::CString0(const char* inp, const char *FileName) : CString(inp) {
    if(FileName == nullptr){
        file = nullptr;
        return;
    }
    size_t s = strsize(FileName) + 1;
    file = new char[s];
    memcpy(file,FileName,s);
}

CString0 operator+(const CString0 &l, const CString &r) {
    CString0 a = l;
    a += r;
    return a;
}

int CString0::output() {
    if(file == nullptr){
        return 1;
    }
    std::ofstream out(file,std::ios::app);
    for(size_t i = 1; i < getSize(); i++){
        out << str[i];
    }
    out << std::endl;
    out.close();
    return 0;
}
