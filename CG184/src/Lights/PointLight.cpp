//
// Created by Suraj Subudhi.
//

#include "PointLight.h"


namespace CG184
{

    PointLight::PointLight():
        Light()
    {
        m_Type = LightType::Point;
    }

    PointLight::~PointLight()
    = default;

    PointLight::PointLight(const PointLight &pointLight):
        Light()
    {
        m_Type				= pointLight.m_Type;
        m_Position			= pointLight.m_Position;
        m_Attenuation		= pointLight.m_Attenuation;
        m_AmbientColor		= pointLight.m_AmbientColor;
        m_DiffuseColor		= pointLight.m_DiffuseColor;
        m_SpecularColor		= pointLight.m_SpecularColor;
    }
}