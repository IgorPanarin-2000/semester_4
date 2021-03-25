#include "CString.h"

size_t strsize(const char* str){
    if(str == nullptr) return 0;
    size_t ans = 0;
    for(auto i = str; *i != '\0'; i++) ans++;
    return ans;
}

CString::CString() {
    size = 0;
    str = new char[1];
    str[0] = '\0';
}

CString::CString(const char* inp) {
    size = strsize(inp);
    str = new char[size+1];
    memcpy(str,inp,size+1);
}

CString::CString(const CString& r){
    size = r.size;
    str = new char[size+1];
    memcpy(str,r.str,size+1);
    if(r.file == nullptr){
        file = nullptr;
        return;
    }
    size_t f = strsize(r.file);
    file = new char[f+1];
    memcpy(file,r.file,f+1);
}

CString::CString(CString&& r) noexcept{
    size = r.size;
    str = r.str;
    file = r.file;
    r.size = 0;
    r.file = nullptr;
    r.str = nullptr;
}

CString::~CString(){
    delete[] str;
    delete[] file;
    size = 0;
}

CString& CString::operator+=(const CString &r) {
    char* old = str;
    str = new char[size + r.size + 1];
    memcpy(str,old,size);
    memcpy(str+size,r.str,r.size+1);
    size = size + r.size;
    delete[] old;
    return *this;
}

CString &CString::operator=(const CString &r) {
    size = r.size;
    delete[] str;
    delete[] file;
    str = new char[size+1];
    memcpy(str,r.str,size+1);
    if(r.file == nullptr){
        file = nullptr;
        return *this;
    }
    size_t f = strsize(r.file);
    file = new char[f+1];
    memcpy(file,r.file,f+1);
    return *this;
}

CString &CString::operator=(CString &&r) noexcept {
    size = r.size;
    delete[] str;
    delete[] file;
    str = r.str;
    file = r.file;
    r.str = nullptr;
    r.file = nullptr;
    r.size = 0;
    return *this;
}

CString::operator const char *() const {
    return str;
}