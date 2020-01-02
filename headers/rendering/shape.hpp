#pragma once

#include <vector>
#include "glm/glm.hpp"
#include "buffers/buffers.hpp"
#include <iostream>

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
    static Shape Box(glm::vec3, glm::vec3);

    // Methods
    void buffer(Buffers&) const;
    void translate(float x, float y, float z);

    // Operators
    Shape operator+(const Shape &other) const;
    void operator+=(const Shape &other);
    friend std::ostream& operator<<(std::ostream& out, const Shape& sh);
};

void push_vector(std::vector<float> &vec, const glm::vec3 &v);