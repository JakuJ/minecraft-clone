#include "views/renderers/RendererT.hpp"

RendererT::RendererT(const std::string &vName, const std::string &fName) : program(vName, fName), bufferedElements(0) {}

void RendererT::bufferData()
{
    buffers->bufferData();
    bufferedElements = buffers->elements();
}
