
// InstanceRenderer::InstanceRenderer() : Renderer("data/shaders/instance.vert", "data/shaders/quad.frag"), buffered_instances(0)
// {
//     glBindBuffer(GL_ARRAY_BUFFER, 0);
//     glVertexAttribDivisor(2, 1);
//     glVertexAttribDivisor(3, 1);
// }

// void InstanceRenderer::constructMesh(const ChunkSector &cs)
// {
//     InstanceMesh mesh = cs.getInstanceMesh();

//     buffers.clear();
//     buffers.bufferMesh(mesh);
// }

// void InstanceRenderer::bufferMesh()
// {
//     buffers.bufferData();
//     buffered_size = buffers.size();
//     buffered_instances = buffers.instances();
// }

// void InstanceRenderer::render(World &world, Player &player)
// {
//     Renderer::render(world, player);
//     glDrawArraysInstanced(GL_TRIANGLES, 0, buffered_size, buffered_instances);
// }