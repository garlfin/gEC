//
// Created by scion on 9/22/2022.
//

#pragma once

#include "Header.h"
#include "IWriteable.h"
#include "Mesh.h"

namespace gETF
{
    struct gETF : public IWriteable
    {
        char Magic[4]{'g', 'E', 'T', 'F'};
        Header Header;
        Mesh* Meshes;

        void Write(std::fstream& fstream) override
        {
            fstream.write(Magic, 4);
            Header.Write(fstream);
            for (int i = 0; i < Header.MeshCount; i++) {
                Meshes[i].Write(fstream);
            }
        }

        void Read(std::fstream& fstream) override
        {
            Header.Read(fstream);
            Meshes = new Mesh[Header.MeshCount];
            for (int i = 0; i < Header.MeshCount; i++) Meshes[i].Read(fstream);
        }

        ~gETF()
        {
            delete Meshes;
        }
    };
}