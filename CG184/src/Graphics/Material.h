//
// Created by suraj on 12/2/17.
//

#ifndef CGENGINE_MATERIAL_H
#define CGENGINE_MATERIAL_H

#include "Shader.h"
#include "./../Maths/Maths.h"
#include "../Lights/Light.h"

namespace CG184 {
    class Material {

    public:
        Material();
        Material(Shader& a_Shader);
        ~Material();

        void AttachShader(Shader& a_Shader);

        inline Shader* GetShader(){ return m_Shader;}

		friend class Renderer;
    private:
		Color m_Ambient;
		Color m_Diffuse;
		Color m_Specular;
		Color m_Emission;
		
		float m_Shininess;


    private:
        Shader* m_Shader;
    };
}


#endif //CGENGINE_MATERIAL_H
