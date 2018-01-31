//
// Created by suraj on 12/7/17.
//

#ifndef CGENGINE_CIRCLE_H
#define CGENGINE_CIRCLE_H


#include "Mesh.h"

namespace CG184 
{
    class Circle : public Mesh
    {
    public:
        Circle();
        Circle(Circle& cir);
        Circle(float rad, uint32_t seg);
        ~Circle();

        inline void			SetRadius(float rad){ m_Radius = rad;}
        inline void			SetSegments(uint32_t seg){ m_EdgeSegments = seg;}

        inline float		GetRadius(){ return  m_Radius;}
        inline uint32_t		GetSegments() const { return m_EdgeSegments;}


    private:
        float				m_Radius;
		uint32_t			m_EdgeSegments;

        void				InitMesh() override;
    };
}


#endif //CGENGINE_CIRCLE_H
