#pragma once
#include <memory>
#include "CString.h"
#include "CString0.h"
#include "CString1.h"

class Creator {
public:
    virtual CString* create(std::string inp, std::string file) = 0;
};

class CreatorString0 : public Creator {
public:
    CString* create(std::string inp, std::string file) override;
};

class CreatorString1 : public Creator {
public:
    CString* create(std::string inp, std::string file) override;
};
