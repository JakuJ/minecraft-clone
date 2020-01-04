#include "buffers/buffers.hpp"
#include <iostream>

Buffers::Buffers() : vertices(0), texCoords(1) {}

size_t Buffers::size() const
{
    return indices.size();
}

void Buffers::clear()
{
    vertices.clear();
    indices.clear();
    texCoords.clear();
}

void Buffers::bufferData()
{
    vertices.bufferData();
    indices.bufferData();
    texCoords.bufferData();
}

QuadBuffers::QuadBuffers()
{
    std::cout << "QuadBuffers created" << std::endl;
}

void QuadBuffers::bufferMesh(const QuadMesh &mesh)
{
    vertices.append(mesh.vertices);
    indices.append(mesh.indices);
    texCoords.append(mesh.texCoords);
}

InstanceBuffers::InstanceBuffers() : offsets(2)
{
    const std::vector<float> verts{0, 0, 0,
                                   1, 0, 0,
                                   1, 1, 0,
                                   0, 1, 0,
                                   0, 0, 1,
                                   1, 0, 1,
                                   1, 1, 1,
                                   0, 1, 1};

    vertices.append(verts);

    const std::vector<u_int> ixs{2, 6, 7, 3, std::numeric_limits<u_int>::max(),
                                 4, 5, 1, 0, std::numeric_limits<u_int>::max(),
                                 5, 1, 7, 6, std::numeric_limits<u_int>::max(),
                                 0, 1, 2, 3, std::numeric_limits<u_int>::max(),
                                 1, 0, 3, 7, std::numeric_limits<u_int>::max(),
                                 1, 5, 6, 2, std::numeric_limits<u_int>::max()};

    indices.append(ixs);

    std::vector<float> coords(48);

    const float du = 1.0 / (float)Block::FACES;
    const float dv = 1.0 / (float)Block::TYPES;

    for (u_int i = 0; i < Block::FACES; i++)
    {
        const float u = (float)i;
        const float uvs[] = {u, 0, u + du, 0, u + du, dv, u, dv};
        coords.insert(coords.end(), uvs, std::end(uvs));
    }

    texCoords.append(coords);

    std::cout << "InstanceBuffers created" << std::endl;
}

size_t InstanceBuffers::instances() const
{
    return offsets.size();
}

void InstanceBuffers::clear()
{
    offsets.clear();
}

void InstanceBuffers::bufferData()
{
    Buffers::bufferData();
    offsets.bufferData();
}

void InstanceBuffers::bufferMesh(const InstanceMesh &mesh)
{
    offsets.append(mesh.offsets);
}