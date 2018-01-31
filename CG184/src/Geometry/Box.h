//
// Created by suraj on 12/6/17.
//

#ifndef CGENGINE_BOX_H
#define CGENGINE_BOX_H

#include "Mesh.h"

namespace CG184
{
    class Box : public Mesh
    {
    public:
        Box();
        Box(Box& a_Box);
        Box(float width, float height, float depth);
        ~Box();

    private:
        float				m_Width;
        float				m_Height;
        float				m_Depth;

        void				InitMesh() override;
    };
}


#endif //CGENGINE_BOX_H
