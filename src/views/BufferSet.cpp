#include "views/BufferSet.hpp"
#include <algorithm>

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
