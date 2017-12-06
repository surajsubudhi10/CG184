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
        unsigned int _v1;
        unsigned int _v2;
        unsigned int _v3;

        Vector3D faceNormal;
    };


    class Mesh //: public Component
    {

    public:

        //TODO Add SubMesh support for Multiple materials for a Mesh (ignore now for Simplicity)
//        std::vector<SubMesh*> m_SubMeshes;
//        std::vector<VertexData> vertices;

        VertexData* vertices;
//        std::vector<FaceData> faces;
        std::vector<unsigned int> m_Indices;
        unsigned int m_NumOfVert;

        Mesh(std::vector<Vector3D> a_Pos, std::vector<unsigned int>a_Ind);
        Mesh(std::vector<VertexData> a_Vertices, std::vector<unsigned int>a_Ind);

        void SetPositions(std::vector<Vector3D> a_Positions);
        void SetColors(std::vector<Vector3D> a_Colors);
        void SetColor(Vector3D a_Color);
        void SetNormals(std::vector<Vector3D> a_Normals);
        void SetUVs(std::vector<Vector2D> a_UV);
        ~Mesh();

    protected:
        Mesh();
        void SetIndicies(std::vector<unsigned int>a_Ind);

        virtual void InitMesh();

    };
}


#endif //CGENGINE_MESH_H
