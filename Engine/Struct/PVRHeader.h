//
// Created by scion on 9/3/2022.
//

#ifndef IME_PVRHEADER_H
#define IME_PVRHEADER_H

#include <cstdint>

#ifdef __GNUC__
#define PACK( __Declaration__ ) __Declaration__ __attribute__((__packed__))
#endif

#ifdef _MSC_VER
#define PACK( __Declaration__ ) __pragma(pack(push,1)) __Declaration__ __pragma(pack(pop))
#endif

PACK(struct PVRHeader
{
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
});// __attribute__((packed)); // Spent hours tryna figure out why my textures looked super wrong... c++ padded my struct to 56 bytes 💀

#endif //IME_PVRHEADER_H
