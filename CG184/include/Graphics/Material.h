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
        explicit Material(const Material& mat);
        explicit Material(Shader* a_Shader);
        ~Material();

        void				AttachShader(Shader* a_Shader);
        inline Shader*		GetShader(){ return m_ShaderPtr;}

        inline void			SetAmbient  (const Color &col)	{ m_Ambient = col; }
        inline void			SetDiffuse  (const Color &col)	{ m_Diffuse = col; }
        inline void			SetSpecular (const Color &col)	{ m_Specular = col; }
        inline void			SetEmission (const Color &col)	{ m_Emission = col; }
        inline void			SetShininess(float shine)		{ m_Shininess = shine; }


        friend class Renderer;
    private:
        Color				m_Ambient;
        Color				m_Diffuse;
        Color				m_Specular;
        Color				m_Emission;
        
        float				m_Shininess;
        Shader*				m_ShaderPtr;
    };
}   // End of CG184


#endif //CGENGINE_MATERIAL_H
