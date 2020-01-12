#pragma once

#include <vector>
#include "buffers/BufferObject.hpp"

class EBO : BufferObject<unsigned int> {
private:
    std::vector<unsigned int> indices;

public:
    EBO();

    [[nodiscard]] size_t size() const override;

    void fill(const std::vector<unsigned int> &vec);

    void bufferData();
};

