#include "rendering/mesh.hpp"

void Mesh::buffer(QuadBuffers &b) const
{
    b.vertices.append(vertices);
    b.indices.append(indices);
    b.texCoords.append(texCoords);
}

void Mesh::addQuad(const std::vector<float> &vs, Block::Type texId, Block::Face faceId)
{
    u_int offset = vertices.size() / 3;
    
    vertices.insert(vertices.end(), vs.cbegin(), vs.cend());

    for (u_int k : {0, 1, 2, 0, 2, 3})
    {
        indices.push_back(k + offset);
    }

    const float ds = 1.0 / 6.0;
    const float dt = 1.0 / (float)Block::TYPES;

    float s0 = faceId * ds;
    float t0 = texId * dt;

    for (float k : {s0, t0, s0 + ds, t0, s0 + ds, t0 + dt, s0, t0 + dt})
    {
        texCoords.push_back(k);
    }
}

void Mesh::operator+=(const Mesh &other)
{
    u_int offset = vertices.size() / 3;
    
    // Copy vertices
    vertices.insert(vertices.end(), other.vertices.cbegin(), other.vertices.cend());

    // Copy texture coordinates
    texCoords.insert(texCoords.end(), other.texCoords.cbegin(), other.texCoords.cend());
    
    std::transform(other.indices.cbegin(), other.indices.cend(), std::back_inserter(indices), [&offset](unsigned int ix) {
        return ix + offset;
    });
}

std::ostream &operator<<(std::ostream &out, const Mesh &mesh)
{
    out << "Mesh with " << mesh.vertices.size() / 3 << " vertices, " << mesh.indices.size() << " indices and " << mesh.texCoords.size() / 2 << " tex coords";
    return out;
}