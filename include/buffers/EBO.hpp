#pragma once

#include <vector>
#include "buffers/BufferObject.hpp"

/// Element Buffer Object.
class EBO : public BufferObject<unsigned int> {
public:
    EBO();

    [[nodiscard]] size_t size() const override;

    void bufferData() override;
};

