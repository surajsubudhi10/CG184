//
// Created by suraj on 12/5/17.
//

#include "Light.h"


namespace CG184{

    Light::Light():
        position(Vector4D(0, 0, 0, 1)),
		m_DiffuseColor(WHITE),
		m_AmbientColor(WHITE),
		m_SpecularColor(WHITE),
		m_Type(LightType::Point)
    {}

    Light::Light(Vector3D &lightPos, LightType& type, Color& diffCol, Color& specCol, Color& ambCol):
        position(Vector4D(0, 0, 0, 1)),
		m_DiffuseColor(diffCol),
		m_AmbientColor(specCol),
		m_SpecularColor(ambCol),
		m_Type(type)
    {
		position.x = lightPos.x;
		position.y = lightPos.y;
		position.z = lightPos.z;
		
		if (m_Type == LightType::DirectionalLight)
			position.w = 0.0;
		else
			position.w = 1.0;
		
	}

    Light::Light(const Light &light):
        position(light.position),
		m_DiffuseColor(light.m_DiffuseColor),
		m_AmbientColor(light.m_AmbientColor),
		m_SpecularColor(light.m_SpecularColor),
		m_Type(light.m_Type)
    {}

    Light::~Light() = default;
}