#include "CString.h"
#include <omp.h>

CString::CString() {
    size = 0;
    file = "";
    str = "";
}

CString::CString(std::string inp, std::string FileName) {
    size = inp.size();
    str = inp;
    if (FileName == "") {
        file = "";
        return;
    }
    file = FileName;
}

CString::CString(const CString& r){
    size = r.size;
    str = r.str;
    if(r.file == ""){
        file = "";
        return;
    }
    file = r.file;
}

CString::CString(CString&& r) noexcept{
    size = r.size;
    str = std::move(r.str);
    file = std::move(r.file);
    r.size = 0;
}

CString::~CString(){
    str.clear();
    file.clear();
    size = 0;
}

CString& CString::operator+=(const CString &r) {
    char* newS1 = new char[size + r.size + 1];
    memcpy(newS1, str.c_str(), size);
#pragma omp parallel for
    for (long long i = 0; i < long long(r.size); i++) {
        newS1[size+i] = r[i];
    }
    newS1[size + r.size] = '\0';
    str = newS1;
    size += r.size;
    delete[] newS1;
    return *this;
}

CString &CString::operator=(const CString &r) {
    str.clear();
    file.clear();
    size = r.size;
    str = r.str;
    if (r.file == "") {
        file = "";
        return *this;
    }
    file = r.file;
    return *this;
}

CString &CString::operator=(CString &&r) noexcept {
    str.clear();
    file.clear();
    size = r.size;
    str = std::move(r.str);
    file = std::move(r.file);
    r.size = 0;
    return *this;
}

CString::operator const char *() const {
    return str.c_str();
}

CString& CString::operator=(std::string inp) {
    size = inp.size();
    str.clear();
    file.clear();
    file = "";
    str = inp;
    return *this;
}