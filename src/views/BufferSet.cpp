#include "views/BufferSet.hpp"
#include <algorithm>

size_t BufferSet::elements() const
{
    if (vbos.size() == 0)
    {
        return 0;
    }
    return vbos[0]->size();
}

VBOProxy* BufferSet::operator[](unsigned int index)
{
    return vbos[index].get();
}

void BufferSet::addVBO(VBOProxy* vbo)
{
    vbos.push_back(std::unique_ptr<VBOProxy>(vbo));
}

void BufferSet::clear()
{
    for (auto& vbo : vbos)
    {
        vbo->clear();
    }
}

void BufferSet::bufferData()
{
    for (auto& vbo : vbos)
    {
        vbo->bufferData();
    }
}

size_t IndexedBufferSet::elements() const
{
    return ebo.size();
}

void IndexedBufferSet::clear()
{
    BufferSet::clear();
    ebo.clear();
}

void IndexedBufferSet::bufferData()
{
    BufferSet::bufferData();
    ebo.bufferData();
}