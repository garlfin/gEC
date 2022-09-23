//
// Created by scion on 9/22/2022.
//

#pragma once

#include <cstdint>
#include "IWriteable.h"

namespace gETF {
    struct Header : IWriteable
    {
        char Magic[4] {'H', 'E', 'A', 'D'};
        uint16_t MaterialCount;
        uint16_t MeshCount;
        uint16_t NodeCount;

        void Write(std::fstream& fstream) override
        {
            fstream.write((char*) this, sizeof(Header));
        }

        void Read(std::fstream& fstream) override
        {
            fstream.read((char*) this, sizeof(Header));
        }
    };
}


