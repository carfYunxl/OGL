#pragma once

#include "IndexBuffer.h"
#include "VertexArray.h"
#include "../include/shader/shader.h"

class Renderer
{
public:
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

    void Clear() const;
private:

};
