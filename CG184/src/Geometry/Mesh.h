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


    class VertexData
    {
    public:
        Vector3D position;
        Vector3D color;
        Vector3D normal;
        Vector2D texCoord;
    };


    struct FaceData
    {
        uint32_t _v1;
        uint32_t _v2;
        uint32_t _v3;

        Vector3D faceNormal;
    };


    class Mesh //: public Component
    {

    public:

        //TODO Add SubMesh support for Multiple materials for a Mesh (ignore now for Simplicity)
//        std::vector<SubMesh*> m_SubMeshes;
//        std::vector<FaceData> faces;

        VertexData* vertices;
		uint32_t m_NumOfVert;
        std::vector<uint32_t> m_Indices;

        Mesh(std::vector<Vector3D> a_Pos, std::vector<uint32_t>a_Ind);
        Mesh(std::vector<VertexData> a_Vertices, std::vector<uint32_t>a_Ind);

        void SetPositions(std::vector<Vector3D> a_Positions);
        void SetColors(std::vector<Vector3D> a_Colors);
        void SetColor(Vector3D a_Color);
        void SetNormals(std::vector<Vector3D> a_Normals);
        void SetUVs(std::vector<Vector2D> a_UV);
        ~Mesh();

    protected:
        Mesh();
        void SetIndicies(std::vector<uint32_t>a_Ind);
        virtual void InitMesh() = 0;

    };
}


#endif //CGENGINE_MESH_H
