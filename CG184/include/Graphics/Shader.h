#pragma once

#include <GL/glew.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include <vector>

#include "Texture.h"
#include "../Maths/Maths.h"

namespace CG184 
{   
    class Uniform
    {
    public:
        std::string name;
        int size;
        uint32_t location;
    };

    class VertexAttribute
    {
    public:
        std::string name;
        int size;
        uint32_t location;
    };

    class Shader
    {
    public:
        Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
        Shader(const Shader& a_Shader);
        ~Shader();

        void								ActivateShader();
        void								DeactivateShader();
        void								AddTexture(const char* texturePath, TextureType texType);

        // TODO add More Uniform Setter functions
        void								SetUniform1f(std::string name, float _v1);
        void								SetUniform1i(std::string name, int _v1);
        void								SetUniform2f(std::string name, float _v1, float _v2);
        void								SetUniform3f(std::string name, float _v1, float _v2, float _v3);
        void								SetUniform4f(std::string name, float _v1, float _v2, float _v3, float _v4);
        void								SetUniform4f(std::string name, Vector4F _v4);
        void								SetUniformMat2f(std::string name, float* val);
        void								SetUniformMat3f(std::string name, float* val);
        void								SetUniformMat4f(std::string name, float* val);
        void								SetUniform4fArray(std::string name, uint32_t numOfElement, float* arrayList);

        uint32_t							GetShaderID() const { return shaderID; }

    private:
        uint32_t							shaderID;
        std::vector<Uniform>				m_Uniforms;
        std::vector<VertexAttribute>		m_Attributes;

        void								CompileShader(uint32_t shader, std::string type);
        
        Texture m_Textures[5] = {}; // TODO Fix -> Hard Coded Fixed No. of Texture Support.
    };

}   // End of CG184
