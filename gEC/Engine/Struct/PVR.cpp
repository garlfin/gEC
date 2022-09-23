//
// Created by scion on 9/20/2022.
//

#include "PVR.h"

const PVR::Header *PVR::LoadHeader(std::ifstream &stream) {
    Header* header = new PVR::Header;

    stream.seekg(0, std::ifstream::beg);
    stream.read((char*) header, sizeof(PVR::Header));

    if(header->Version == 0x50565203) std::cout << "Endianness does not match" << std::endl;

    return header;
}

glm::u16vec2 PVR::Header::Size() const { return glm::u16vec2(Width, Height); }
