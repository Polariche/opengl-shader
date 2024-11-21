#pragma once

class Shader
{
private:
    unsigned int m_RendererID;
public:
    Shader(const std::string& filepath);
    ~Shader();

    void Bind() const;
    void Unbind();

    void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);
    
private:
    unsigned int GetUniformLocation(const std::string& name);
}