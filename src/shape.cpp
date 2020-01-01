#include "shape.hpp"
#include <iostream>
#include "buffers/helpers.hpp"

void push_vector(std::vector<float> &vec, const glm::vec3 &v)
{
    vec.push_back(v[0]);
    vec.push_back(v[1]);
    vec.push_back(v[2]);
}

Shape::Shape()
{
    vertices = std::vector<float>();
    indices = std::vector<unsigned int>();
    texCoords = std::vector<float>();
    std::cout << "Empty shape created" << std::endl;
}

Shape::Shape(const std::vector<float> &vertices, const std::vector<unsigned int> &indices, const std::vector<float> &texCoords) : vertices(vertices), indices(indices), texCoords(texCoords) {}

Shape Shape::Quad(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 v4)
{
    std::vector<float> vertices;
    push_vector(vertices, v1);
    push_vector(vertices, v2);
    push_vector(vertices, v3);
    push_vector(vertices, v4);

    std::vector<float> texCoords{0, 0, 1, 0, 1, 1, 0, 1};
    std::vector<unsigned int> indices{0, 1, 2, 0, 2, 3};

    std::cout << "Quad created" << std::endl;

    return Shape(vertices, indices, texCoords);
}

Shape Shape::Box(glm::vec3 near, glm::vec3 far)
{

    const auto &v1 = near;
    const auto &v7 = far;

    auto v2 = glm::vec3(far[0], near[1], near[2]);
    auto v3 = glm::vec3(far[0], far[1], near[2]);
    auto v4 = glm::vec3(near[0], far[1], near[2]);

    auto v5 = glm::vec3(near[0], near[1], far[2]);
    auto v6 = glm::vec3(far[0], near[1], far[2]);
    auto v8 = glm::vec3(near[0], far[1], far[2]);

    std::cout << "Box created" << std::endl;

    return Shape::Quad(v1, v2, v3, v4) + // front
           Shape::Quad(v2, v6, v7, v3) + // right
           Shape::Quad(v5, v1, v4, v8) + // left
           Shape::Quad(v6, v5, v8, v7) + // back
           Shape::Quad(v4, v3, v7, v8) + // top
           Shape::Quad(v5, v6, v2, v1);  // bottom
}

void Shape::buffer(Buffers &b) const
{
    b.vertices.append(vertices);
    b.indices.append(indices);
    b.texCoords.append(texCoords);
    b.size += indices.size();
}

void Shape::translate(float x, float y, float z)
{
    for (size_t i = 0; i < vertices.size() - 2; i += 3)
    {
        vertices[i] += x;
        vertices[i + 1] += y;
        vertices[i + 2] += z;
    }
}

Shape Shape::operator+(const Shape &other) const
{
    // Copy vertices
    auto newVs = std::vector<float>(vertices);
    newVs.insert(newVs.end(), other.vertices.begin(), other.vertices.end());

    // Copy texture coordinates
    auto newCoords = std::vector<float>(texCoords);
    newCoords.insert(newCoords.end(), other.texCoords.begin(), other.texCoords.end());

    // Copy indices with an offset
    auto newIndices = std::vector<unsigned int>(indices);
    unsigned int offset = vertices.size() / 3;

    std::transform(other.indices.cbegin(), other.indices.cend(), std::back_inserter(newIndices), [offset](unsigned int ix) {
        return ix + offset;
    });

    // Create and return a new shape
    return Shape(newVs, newIndices, newCoords);
}

void Shape::operator+=(const Shape &other)
{
    unsigned int offset = vertices.size() / 3;
    
    // Copy vertices
    vertices.insert(vertices.end(), other.vertices.cbegin(), other.vertices.cend());

    // Copy texture coordinates
    texCoords.insert(texCoords.end(), other.texCoords.cbegin(), other.texCoords.cend());

    std::transform(other.indices.cbegin(), other.indices.cend(), std::back_inserter(indices), [offset](unsigned int ix) {
        return ix + offset;
    });
}

std::ostream &operator<<(std::ostream &out, const Shape &sh)
{
    out << "Shape with " << sh.vertices.size() / 3 << " vertices, " << sh.indices.size() << " indices and " << sh.texCoords.size() / 2 << " tex coords" << std::endl;
    out << "Vertices: " << sh.vertices << std::endl;
    out << "Indices: " << sh.indices << std::endl;
    out << "TexCoords: " << sh.texCoords << std::endl;
    return out;
}
