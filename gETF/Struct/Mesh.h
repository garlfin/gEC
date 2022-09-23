//
// Created by scion on 9/22/2022.
//

#pragma once
#include <cstdint>
#include "Vertex.h"
#include "IWriteable.h"

namespace gETF
{
    struct SubMesh : public IWriteable {
        uint32_t VertexCount;
        Vertex* Vertices;
        uint32_t FaceCount;
        glm::uvec3* Faces;
        uint16_t MaterialID;

        ~SubMesh() {
            delete Vertices;
            delete Faces;
        }

        void Write(std::fstream &fstream) override
        {
            fstream.write((char*) &VertexCount, sizeof(uint32_t));
            fstream.write((char*) Vertices, sizeof(Vertex) * VertexCount);

            fstream.write((char*) &FaceCount, sizeof(uint32_t));
            if(FaceCount)
            {
                fstream.write((char*) Faces, sizeof(glm::uvec3) * FaceCount);
            }
            fstream.write((char*) &MaterialID, sizeof(uint16_t));
        }

        void Read(std::fstream &fstream) override
        {
            fstream.read((char*) &VertexCount, sizeof(uint32_t));
            Vertices = new Vertex[VertexCount];
            fstream.read((char*) Vertices, sizeof(Vertex) * VertexCount);
            fstream.read((char*) &FaceCount, sizeof(uint32_t));
            if(FaceCount)
            {
                Faces = new glm::uvec3[FaceCount];
                fstream.read((char *) Faces, sizeof(glm::uvec3) * FaceCount);
            }
            fstream.read((char*) &MaterialID, sizeof(uint16_t));
        }
    };

    struct Mesh : public IWriteable {
        char Magic[4] {'M', 'E', 'S', 'H'};
        uint8_t NameLength;
        char* Name;
        uint16_t ID;
        uint8_t SubMeshCount;
        SubMesh* SubMeshes;

        ~Mesh() {delete Name; delete SubMeshes; }

        void Write(std::fstream &fstream) override
        {
            fstream.write(Magic, 4);
            fstream.write((char*) &NameLength, sizeof(uint8_t));
            fstream.write(Name, NameLength);
            fstream.write((char*) &ID, sizeof(uint16_t));
            fstream.write((char*) &SubMeshCount, sizeof(uint8_t));
            fstream.write((char*) &SubMeshes, sizeof(SubMesh) * SubMeshCount);
        }

        void Read(std::fstream &fstream) override
        {
            fstream.read((char*) &Magic, 4);
            fstream.read((char*) &NameLength, sizeof(uint8_t));

            Name = new char[NameLength];
            fstream.read(Name, NameLength);

            fstream.read((char*) &SubMeshCount, sizeof(uint8_t));
            SubMeshes = new SubMesh[SubMeshCount];
            fstream.read((char*) &SubMeshes, sizeof(SubMesh) * SubMeshCount);
        }
    };
}
