//
// Created by scion on 9/22/2022.
//

#pragma once

#include <fstream>

class IWriteable
{
public:
    virtual void Write(std::fstream&) = 0;
    virtual void Read(std::fstream&) = 0;
};
