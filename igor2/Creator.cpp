#include "Creator.h"

CString* CreatorString0::create(std::string inp, std::string file) {
    return new CString0(inp, file);
}

CString* CreatorString1::create(std::string inp, std::string file) {
    return new CString1(inp, file);
}