#pragma once

#include <vector>
#include "glm/glm.hpp"
#include "buffers/VBO.hpp"
#include "buffers/EBO.hpp"

class Shape
{
protected:
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    std::vector<float> texCoords;

public:
    // Constructors
    Shape();
    Shape(const std::vector<float> &vertices, const std::vector<unsigned int> &indices, const std::vector<float> &texCoords);

    // Static factories
    static Shape Quad(glm::vec3, glm::vec3, glm::vec3, glm::vec3);
    static Shape Box(glm::vec3, glm::vec3);

    // Methods
    void buffer(VBO<float, 3> &vertexBuffer, EBO &indexBuffer, VBO<float, 2> &texCoordBuffer) const;

    // Operators
    Shape operator+(const Shape &other) const;
};

void push_vector(std::vector<float> &vec, const glm::vec3 &v);