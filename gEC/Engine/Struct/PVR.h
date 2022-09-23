//
// Created by scion on 9/3/2022.
//

#ifndef IME_PVR_H
#define IME_PVR_H

#include <cstdint>
#include <glm/vec2.hpp>
#include <fstream>
#include <iostream>

namespace PVR {
    struct Header {
        uint32_t Version;
        uint32_t Flags;
        uint64_t Format;
        uint32_t ColorSpace;
        uint32_t ChannelType;
        uint32_t Height;
        uint32_t Width;
        uint32_t Depth;
        uint32_t Surfaces;
        uint32_t Faces;
        uint32_t Mips;
        uint32_t MetaSize;

        [[nodiscard]] glm::u16vec2 Size() const;;

    } __attribute__((packed)); // Spent hours tryna figure out why my textures looked super wrong... c++ padded my struct 💀

    const Header *LoadHeader(std::ifstream& stream);;
}
#endif //IME_PVR_H
