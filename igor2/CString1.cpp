#include "CString1.h"

CString1 operator+(const CString1 &l, const CString &r) {
    CString1 a = l;
    a += r;
    return a;
}

int CString1::output() {
    if(file == ""){
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

