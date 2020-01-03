#pragma once

#include <vector>
#include "buffers/helpers.hpp"

class EBO
{
private:
    unsigned int id;
    std::vector<unsigned int> indices;

    void bufferData() const;

public:
    EBO();
    EBO(const std::vector<unsigned int> &indices);

    void append(const std::vector<unsigned int> &vec);
    void clear();
};