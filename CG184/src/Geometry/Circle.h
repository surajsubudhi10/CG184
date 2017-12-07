//
// Created by suraj on 12/7/17.
//

#ifndef CGENGINE_CIRCLE_H
#define CGENGINE_CIRCLE_H


#include "Mesh.h"

namespace CG184 {
    class Circle : public Mesh
    {
    public:
        Circle();
        Circle(Circle& cir);
        Circle(float rad, unsigned int seg);
        ~Circle();

        inline void SetRadius(float rad){ m_Radius = rad;}
        inline void SetSegments(unsigned int seg){ m_EdgeSegments = seg;}

        inline float GetRadius(){ return  m_Radius;}
        inline Vector2D GetSegments() const { return m_EdgeSegments;}


    private:
        float m_Radius;
        unsigned int m_EdgeSegments;

        void InitMesh() override;
    };
}


#endif //CGENGINE_CIRCLE_H
