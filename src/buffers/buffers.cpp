#include "buffers/buffers.hpp"
#include <iostream>

Buffers::Buffers() : vertices(0), texCoords(1) {}

void Buffers::clear()
{
    vertices.clear();
    texCoords.clear();
}

void Buffers::bufferData()
{
    vertices.bufferData();
    texCoords.bufferData();
}

QuadBuffers::QuadBuffers()
{
    std::cout << "QuadBuffers created" << std::endl;
}

size_t QuadBuffers::size() const
{
    return indices.size();
}

void QuadBuffers::clear()
{
    Buffers::clear();
    indices.clear();
}

void QuadBuffers::bufferData()
{
    Buffers::bufferData();
    indices.bufferData();
}

void QuadBuffers::bufferMesh(const QuadMesh &mesh)
{
    vertices.append(mesh.vertices);
    indices.append(mesh.indices);
    texCoords.append(mesh.texCoords);
}

InstanceBuffers::InstanceBuffers() : offsets(2)
{
    std::vector<float> verts;
    verts.reserve(6 * 2 * 3 * 3);

    const float vs[]{0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1};

    const u_int ixs[]{
        3, 2, 6, 3, 6, 7,
        4, 5, 1, 4, 1, 0,
        5, 4, 7, 5, 7, 6,
        0, 1, 2, 0, 2, 3,
        1, 5, 6, 1, 6, 2,
        4, 0, 3, 4, 3, 7};

    auto addVert = [&](u_int ix) {
        verts.push_back(vs[3 * ix]);
        verts.push_back(vs[3 * ix + 1]);
        verts.push_back(vs[3 * ix + 2]);
    };

    std::for_each(ixs, std::end(ixs), addVert);

    vertices.append(verts);

    std::vector<float> coords;
    coords.reserve(48);

    const float du = 1.0 / (float)Block::FACES;
    const float dv = 1.0 / (float)Block::TYPES;

    for (u_int i = 0; i < Block::FACES; i++)
    {
        const float u = du * (float)i;
        const float uvs[] = {u, 0, u + du, 0, u + du, dv, u, 0, u + du, dv, u, dv};
        coords.insert(coords.end(), uvs, std::end(uvs));
    }

    texCoords.append(coords);

    std::cout << "InstanceBuffers created" << std::endl;
}

size_t InstanceBuffers::size() const
{
    return vertices.size();
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