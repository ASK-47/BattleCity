#pragma once

#include <vector>
#include <glad/glad.h>

namespace RenderEngine {
    struct VertexBufferLayoutElement {//buffer element
        GLint count;
        GLenum type;
        GLboolean normalized;
        unsigned int size;
    };

    class VertexBufferLayout {
    public:
        VertexBufferLayout();

        void reserveElements(const size_t count);
        unsigned int getStride() const { return m_stride; }
        void addElementLayoutFloat(const unsigned int count, const bool normalized);
        const std::vector<VertexBufferLayoutElement>& getLayoutElements() const { return m_layoutElments; }

    private:
        std::vector<VertexBufferLayoutElement> m_layoutElments;//vector of buffer elements
        unsigned int m_stride;
    };
}