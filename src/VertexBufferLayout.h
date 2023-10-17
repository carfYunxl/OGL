#pragma once

#include <vector>
#include <glad/glad.h>

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetTypeSize(unsigned int type)
    {
        switch (type)
        {
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }

        return 0;
    }
};

class VertexBufferLayout
{
public:
    VertexBufferLayout()
        : m_Stride(0)
    {}

    inline unsigned int GetStride() const { return m_Stride; }
    inline const std::vector<VertexBufferElement>& GetElements() const { return m_elements; }


    template<typename T>
    void Push(unsigned int count)
    {
        //static_assert(false);
    }

    template<>
    void Push<float>(unsigned int count)
    {
        m_elements.push_back({ GL_FLOAT, count,  GL_FALSE});
        m_Stride += count * VertexBufferElement::GetTypeSize(GL_FLOAT);
    }

    template<>
    void Push<unsigned int>(unsigned int count)
    {
        m_elements.push_back({ GL_UNSIGNED_INT, count,  GL_FALSE });
        m_Stride += count * VertexBufferElement::GetTypeSize(GL_UNSIGNED_INT);
    }

    template<>
    void Push<unsigned char>(unsigned int count)
    {
        m_elements.push_back({ GL_UNSIGNED_BYTE, count,  GL_TRUE });
        m_Stride += count * VertexBufferElement::GetTypeSize(GL_UNSIGNED_BYTE);
    }
private:
    std::vector<VertexBufferElement> m_elements;
    unsigned int m_Stride;
};
