//
// Created by suraj on 12/5/17.
//

#ifndef CGENGINE_LIGHT_H
#define CGENGINE_LIGHT_H

#include "../Maths/Vector3D.h"
#include "../Maths/Maths.h"

namespace CG184 {

	enum LightType
	{
		Point,
		SpotLight,
		DirectionalLight,
	};

    class Light {

    public:
        Light();
        Light(const Light& light);
        Light(Vector3D& lightPos, LightType& type, Color& diffCol, Color& specCol = WHITE, Color& ambCol = WHITE);
        ~Light();

		inline Color GetPosition() { return position; }
		inline Color GetDiffuseColor()  { return m_DiffuseColor;  }
		inline Color GetSpecularColor() { return m_SpecularColor; }
		inline Color GetAmbientColor()  { return m_AmbientColor; }
		inline Vector3D GetAttenuation ()  { return m_Attenuation;  }

		inline void SetPosition(const Vector4D& pos) { position = pos; }
		inline void SetDiffuseColor (const Color& col) { m_DiffuseColor  = col; }
		inline void SetSpecularColor(const Color& col) { m_SpecularColor = col; }
		inline void SetAmbientColor (const Color& col) { m_AmbientColor  = col; }
		inline void SetAttenuation(float constant, float linear, float quad) { m_Attenuation = Vector3D(constant, linear, quad); }

	private:
		Color m_DiffuseColor;
		Color m_SpecularColor;
		Color m_AmbientColor;

        Vector4D position;
		Vector3D m_Attenuation;

		LightType m_Type;
    };
}


#endif //CGENGINE_LIGHT_H
