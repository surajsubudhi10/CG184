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

    public:
        Mesh(std::vector<Vector3D> a_Pos, std::vector<uint32_t>a_Ind);
        explicit Mesh(Mesh *pMesh);

        void CopyMesh(const Mesh& pMesh);

        void SetPosition(uint32_t at, const Vector3D& a_Position);
		void SetColor(uint32_t at, const Vector3D& a_Color);
		void SetNormal(uint32_t at, const Vector3D& a_Normal);
		void SetUV(uint32_t at, const Vector2D& a_TexCoord);

        void SetPositions(std::vector<Vector3D> a_Positions);
        void SetColors(std::vector<Vector3D> a_Colors);
        void SetColor(Vector3D a_Color);
        void SetColor(float a_ColorR, float a_ColorG, float a_ColorB);
        void SetNormals(std::vector<Vector3D> a_Normals);
        void SetUVs(std::vector<Vector2D> a_UV);

        bool IsDirty() const;
        bool IsStatic() const;
        void MakeStatic(bool staticMode);
        void MakeClean(){m_IsDirty = false;}

        ~Mesh();

        void Update();

        friend class MeshFilter;

        void SetIndicies(std::vector<uint32_t>a_Ind);
    protected:
        Mesh();
        virtual void InitMesh();

    private:

//        const int m_InstanceID;
        bool m_IsDirty;
        bool m_IsStatic;

        std::vector<Vector3D> vertPosition;
        std::vector<Vector3D> vertColor;
        std::vector<Vector3D> vertNormal;
        std::vector<Vector2D> vertTexCoord;

        uint32_t m_NumOfVert;
        std::vector<uint32_t> m_Indices;

    };
}


#endif //CGENGINE_MESH_H
