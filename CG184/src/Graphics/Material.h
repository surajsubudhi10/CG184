//
// Created by suraj on 12/2/17.
//

#ifndef CGENGINE_MATERIAL_H
#define CGENGINE_MATERIAL_H

#include "Shader.h"
#include "./../Maths/Maths.h"

namespace CG184 {
    class Material {

    public:
        Material();
        Material(Shader& a_Shader);
        ~Material();

        void AttachShader(Shader& a_Shader);

        inline Shader* GetShader()
        {
            return m_Shader;
        }

    public:
        Vector3D diffuseColor;
        Vector3D specularColor;
        float shinyness;


    private:
        Shader* m_Shader;
    };
}


#endif //CGENGINE_MATERIAL_H
