//
// Created by suraj on 12/5/17.
//

#include "Light.h"


namespace CG184
{

    Light::Light():
            m_Position(Vector4D(0, 0, 0, 1)),
            m_DiffuseColor(WHITE),
            m_AmbientColor(WHITE),
            m_SpecularColor(WHITE),
            m_Attenuation(Vector3D(1.0)),
            m_Type(LightType::Point)
    {}

    Light::Light(Vector3D &lightPos, LightType& type, Color& diffCol, Color& specCol, Color& ambCol):
            m_Position(Vector4D(0, 0, 0, 1)),
            m_DiffuseColor(diffCol),
            m_AmbientColor(specCol),
            m_SpecularColor(ambCol),
            m_Attenuation(Vector3D(1.0)),
            m_Type(type)
{
        m_Position.x = lightPos.x;
        m_Position.y = lightPos.y;
        m_Position.z = lightPos.z;
        
        if (m_Type == LightType::DirectionalLight)
            m_Position.w = 0.0;
        else
            m_Position.w = 1.0;
        
    }

    Light::Light(const Light &light):
        m_Position(light.m_Position),
        m_DiffuseColor(light.m_DiffuseColor),
        m_AmbientColor(light.m_AmbientColor),
        m_SpecularColor(light.m_SpecularColor),
        m_Attenuation(light.m_Attenuation),
        m_Type(light.m_Type)
{}

    Light::~Light() = default;
}   // End of CG184