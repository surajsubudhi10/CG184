//
// Created by suraj on 12/5/17.
//

#ifndef CGENGINE_LIGHT_H
#define CGENGINE_LIGHT_H

#include <memory>
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

    protected:
        Light();
        Light(const Light& light);
        Light(Vector3D& lightPos, LightType& type, Color& diffCol, Color& specCol = WHITE, Color& ambCol = WHITE);

        virtual ~Light();

    public:
		inline Color GetPosition() { return m_Position; }
		inline Color GetDiffuseColor()  { return m_DiffuseColor;  }
		inline Color GetSpecularColor() { return m_SpecularColor; }
		inline Color GetAmbientColor()  { return m_AmbientColor; }
		inline Vector3D GetAttenuation ()  { return m_Attenuation;  }

		inline void SetPosition(const Vector4D& pos) { m_Position = pos; }
		inline void SetDiffuseColor (const Color& col) { m_DiffuseColor  = col; }
		inline void SetSpecularColor(const Color& col) { m_SpecularColor = col; }
		inline void SetAmbientColor (const Color& col) { m_AmbientColor  = col; }

    protected:
        Color m_AmbientColor;
        Color m_DiffuseColor;
        Color m_SpecularColor;

        Vector4D m_Position;
		Vector3D m_Attenuation;

		LightType m_Type;
    };

    typedef std::shared_ptr<Light> LightPtr;
}


#endif //CGENGINE_LIGHT_H
