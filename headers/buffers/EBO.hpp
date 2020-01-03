#pragma once

#include <vector>
#include "buffers/helpers.hpp"

class EBO
{
private:
    unsigned int id;
    std::vector<unsigned int> indices;

public:
    EBO();
    EBO(const std::vector<unsigned int> &indices);

    u_int size() const;
    
    void append(const std::vector<unsigned int> &vec);
    void clear();
    void bufferData() const;
};