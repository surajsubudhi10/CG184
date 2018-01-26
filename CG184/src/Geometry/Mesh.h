//
// Created by suraj on 12/2/17.
//

#ifndef CGENGINE_MESH_H
#define CGENGINE_MESH_H


#include <vector>
#include <GL/glew.h>
#include "../Maths/Vector3D.h"
#include "../Maths/Vector2D.h"
#include "../Scene/Componet.h"


namespace CG184 {


    class Mesh
    {

    private:
        std::vector<Vector3D> vertPosition;
        std::vector<Vector3D> vertColor;
        std::vector<Vector3D> vertNormal;
        std::vector<Vector2D> vertTexCoord;

        uint32_t m_NumOfVert;
        std::vector<uint32_t> m_Indices;

    public:
        Mesh(std::vector<Vector3D> a_Pos, std::vector<uint32_t>a_Ind);

        void SetPositions(std::vector<Vector3D> a_Positions);
        void SetColors(std::vector<Vector3D> a_Colors);
        void SetColor(Vector3D a_Color);
        void SetColor(float a_ColorR, float a_ColorG, float a_ColorB);
        void SetNormals(std::vector<Vector3D> a_Normals);
        void SetUVs(std::vector<Vector2D> a_UV);
        ~Mesh();

        friend class MeshFilter;
    protected:
        Mesh();
        void SetIndicies(std::vector<uint32_t>a_Ind);
        virtual void InitMesh();

    };
}


#endif //CGENGINE_MESH_H
