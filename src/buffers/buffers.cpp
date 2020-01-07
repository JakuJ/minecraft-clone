#include "buffers/buffers.hpp"
#include "utility/timing.hpp"
#include <iostream>

Buffers::Buffers() : vertices(0), texCoords(1) {}

void Buffers::clear()
{
    vertices.clear();
    texCoords.clear();
}

void Buffers::bufferData()
{
    MeanScopedTimer timer("Buffers::bufferData");
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
    MeanScopedTimer timer("QuadBuffers::bufferData");
    Buffers::bufferData();
    indices.bufferData();
}

void QuadBuffers::bufferMesh(const QuadMesh &mesh)
{
    vertices.append(mesh.vertices);
    indices.append(mesh.indices);
    texCoords.append(mesh.texCoords);
}

InstanceBuffers::InstanceBuffers() : offsets(2), typeInfos(3)
{
    std::vector<float> verts;
    verts.reserve(2 * 3 * 3);

    const float vs[]{0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0};

    const u_int ixs[]{0, 1, 2, 0, 2, 3};

    auto addVert = [&](u_int ix) {
        verts.push_back(vs[3 * ix] - 0.5);
        verts.push_back(vs[3 * ix + 1] - 0.5);
        verts.push_back(vs[3 * ix + 2] - 0.5);
    };

    for (auto &ix : ixs)
    {
        addVert(ix);
    }

    vertices.append(verts);

    std::vector<float> coords;
    coords.reserve(2 * 3 * 2);

    const float du = 1.0 / (float)Block::FACES;
    const float dv = 1.0 / (float)Block::TYPES;

    const float uvs[] = {0, 0, du, 0, du, dv, 0, 0, du, dv, 0, dv};
    coords.insert(coords.end(), uvs, std::end(uvs));

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
    typeInfos.clear();
}

void InstanceBuffers::bufferData()
{
    Buffers::bufferData();

    MeanScopedTimer timer("InstanceBuffers::bufferData");
    offsets.bufferData();
    typeInfos.bufferData();
}

void InstanceBuffers::bufferMesh(const InstanceMesh &mesh)
{
    offsets.append(mesh.offsets);
    typeInfos.append(mesh.typeInfos);
}