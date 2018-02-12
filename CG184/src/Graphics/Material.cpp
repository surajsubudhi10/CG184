//
// Created by suraj on 12/2/17.
//

#include <Graphics/Material.h>

namespace CG184 {
    Material::Material():
        m_Ambient(GREEN),
        m_Diffuse(GREY),
        m_Specular(WHITE),
        m_Emission(BLACK),
        m_Shininess(0.0)
    {
        // TODO Create default shader (Phong, Blin, etc)
        //m_ShaderPtr = new Shader("TestShaders/BoxSolid.vs", "TestShaders/BoxSolid.fs");
    }

    Material::Material(const Material& mat):
        m_Ambient  (mat.m_Ambient),
        m_Diffuse  (mat.m_Diffuse),
        m_Specular (mat.m_Specular),
        m_Emission (mat.m_Emission),
        m_Shininess(mat.m_Shininess)
    {
        m_ShaderPtr = mat.m_ShaderPtr;
    }

    Material::Material(Shader *a_Shader):
        m_Ambient(GREEN),
        m_Diffuse(GREY),
        m_Specular(WHITE),
        m_Emission(BLACK),
        m_Shininess(1.0)
    {
        m_ShaderPtr = a_Shader;
    }

    Material::~Material() {
        //delete[] m_ShaderPtr;
        m_ShaderPtr = nullptr;
    }

    void Material::AttachShader(Shader* a_Shader) {
        m_ShaderPtr = a_Shader;
    }
}   // End of CG184
