#include "CString0.h"

CString0 operator+(const CString0 &l, const CString &r) {
    CString0 a = l;
    a += r;
    return a;
}

int CString0::output() {
    if(file == ""){
        return 1;
    }
    std::ofstream out(file,std::ios::app);
    for(size_t i = 0; i < getSize(); i++){
        out << str[i];
    }
    out << std::endl;
    out.close();
    return 0;
}
