#include <GL/glew.h>

#include "vertexbufferobject.h"


VertexBufferObject::VertexBufferObject() {
    glGenBuffers(1, &_id);
}

VertexBufferObject::~VertexBufferObject() {
    glDeleteBuffers(1, &_id);
}

void VertexBufferObject::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, _id);
}

void VertexBufferObject::BufferData(const void *data, const int size) const {
    glBindBuffer(GL_ARRAY_BUFFER, _id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBufferObject::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
