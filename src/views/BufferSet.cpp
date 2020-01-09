#include <algorithm>
#include <glad/glad.h>
#include <views/BufferSet.hpp>

BufferSet::BufferSet() {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
}

VBOProxy *BufferSet::operator[](unsigned int index) {
    return vbos[index].get();
}

void BufferSet::addVBO(VBOProxy *vbo) {
    vbos.push_back(std::unique_ptr<VBOProxy>(vbo));
}

void BufferSet::bufferData() {
    for (auto &vbo : vbos) {
        vbo->bufferData();
    }
}

void IndexedBufferSet::bufferData() {
    BufferSet::bufferData();
    ebo.bufferData();
}
