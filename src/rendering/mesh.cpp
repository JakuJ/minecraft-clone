#include "rendering/mesh.hpp"
#include <algorithm>

#pragma region QuadMesh

void QuadMesh::addQuad(const std::vector<float> &vs, Block::Type texId, Block::Face faceId) {
    u_int offset = vertices.size() / 3;

    vertices.insert(vertices.end(), vs.cbegin(), vs.cend());

    for (u_int k : {0, 1, 2, 0, 2, 3}) {
        indices.push_back(k + offset);
    }

    const float ds = 1.0 / 6.0;
    const float dt = 1.0 / static_cast<float>(Block::TYPES);

    float s0 = static_cast<float>(faceId) * ds;
    float t0 = static_cast<float>(texId) * dt;

    for (float k : {s0, t0, s0 + ds, t0, s0 + ds, t0 + dt, s0, t0 + dt}) {
        texCoords.push_back(k);
    }
}

void QuadMesh::operator+=(const QuadMesh &other) {
    u_int offset = vertices.size() / 3;

    // Copy vertices
    vertices.insert(vertices.end(), other.vertices.cbegin(), other.vertices.cend());

    // Copy texture coordinates
    texCoords.insert(texCoords.end(), other.texCoords.cbegin(), other.texCoords.cend());

    std::transform(other.indices.cbegin(), other.indices.cend(), std::back_inserter(indices),
                   [&offset](unsigned int ix) {
                       return ix + offset;
                   });
}

std::ostream &operator<<(std::ostream &out, const QuadMesh &mesh) {
    out << "Quad Mesh with " << mesh.vertices.size() / 3 << " vertices, " << mesh.indices.size() << " indices and "
        << mesh.texCoords.size() / 2 << " tex coords";
    return out;
}

#pragma endregion
#pragma region InstanceMesh

void InstanceMesh::addCube(float x, float y, float z, Block::Type texId, Block::Face faceId) {
    const float offs[] = {x, y, z};
    offsets.insert(offsets.end(), offs, std::end(offs));

    const float infos[] = {static_cast<float>(faceId) / Block::FACES, static_cast<float>(texId) / Block::TYPES,
                           static_cast<float>(faceId)};
    typeInfos.insert(typeInfos.end(), infos, std::end(infos));
}

void InstanceMesh::operator+=(const InstanceMesh &other) {
    offsets.insert(offsets.end(), other.offsets.cbegin(), other.offsets.cend());
    typeInfos.insert(typeInfos.end(), other.typeInfos.cbegin(), other.typeInfos.cend());
}

std::ostream &operator<<(std::ostream &out, const InstanceMesh &mesh) {
    return out << "Instance Mesh with " << mesh.offsets.size() / 3 << " instances";
}

#pragma endregion