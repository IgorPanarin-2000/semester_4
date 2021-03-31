#include "CString.h"

size_t strsize(const char* str){
    if(str == nullptr) return 0;
    size_t ans = 0;
    for(auto i = str; *i != '\0'; i++) ans++;
    return ans;
}

CString::CString() {
    size = 0;
    file = "";
    str = "";
}

CString::CString(std::string inp, std::string FileName) {
    size = strsize(inp.c_str());
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
    str += r.str;
    size += r.size;
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
    size = strsize(inp.c_str());
    str.clear();
    file.clear();
    file = "";
    str = inp;
    return *this;
}