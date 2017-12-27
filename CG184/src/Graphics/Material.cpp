//
// Created by suraj on 12/2/17.
//

#include "Material.h"

namespace CG184 {
    Material::Material():
		m_Ambient(GREEN),
		m_Diffuse(GREY),
		m_Specular(WHITE),
		m_Emission(BLACK),
		m_Shininess(0.0)
    {
        // TODO Create default shader (Phong, Blin, etc)
        m_Shader = new Shader("TestShaders/BoxSolid.vs", "TestShaders/BoxSolid.fs");
    }

    Material::Material(Shader *a_Shader):
		m_Ambient(GREEN),
		m_Diffuse(GREY),
		m_Specular(WHITE),
		m_Emission(BLACK),
		m_Shininess(1.0)
    {
        m_Shader = a_Shader;
    }

    Material::~Material() {
        m_Shader = nullptr;
    }

    void Material::AttachShader(Shader* a_Shader) {
        m_Shader = a_Shader;
    }
}
