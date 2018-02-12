//
// Created by Suraj Subudhi.
//

#include <Lights/DirectionalLight.h>

namespace CG184
{

    DirectionalLight::DirectionalLight() :
        Light(),
        m_Direction(Vector3D(0, 1, 0))
    {
        m_Type = LightType::DirectionalLight;
        m_Attenuation = Vector3D(1, 0, 0);
    }

    DirectionalLight::DirectionalLight(const DirectionalLight &directionalLight):
        Light()
    {
        m_Type          = directionalLight.m_Type;
        m_Position      = directionalLight.m_Position;
        m_AmbientColor  = directionalLight.m_AmbientColor;
        m_DiffuseColor  = directionalLight.m_DiffuseColor;
        m_SpecularColor = directionalLight.m_SpecularColor;
        m_Direction     = directionalLight.m_Direction;
        m_Attenuation   = Vector3D(1, 0, 0);
    }

    DirectionalLight::DirectionalLight(Vector3D pos, Vector3D dir):
        Light(),
        m_Direction(dir.norm())
    {
        m_Type = LightType::DirectionalLight;
        m_Position = Vector4D(pos, 0.0f);
        m_Attenuation = Vector3D(1, 0, 0);
    }

    DirectionalLight::~DirectionalLight() = default;
}   // End of CG184