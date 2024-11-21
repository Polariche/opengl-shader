#pragma once


class VertexBufferObject {

private:
    unsigned int _id;

public:
    VertexBufferObject();
    ~VertexBufferObject();

    void Bind() const;
    void BufferData(const void *data, const int size) const;
    void Unbind() const;
};
