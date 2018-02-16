//
// Created by suraj on 12/2/17.
//

#ifndef CGENGINE_MESH_H
#define CGENGINE_MESH_H

#include <vector>
#include <string>

#include <GL/glew.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../Maths/Vector3D.h"
#include "../Maths/Vector2D.h"
#include "../Scene/Componet.h"
#include "HalfEdgeElement.h"


namespace CG184 
{

    class Mesh
    {
    public:
        Mesh();
        Mesh(std::vector<Vector3D> a_Pos, std::vector<uint32_t>a_Ind);
        explicit Mesh(Mesh *pMesh);
        ~Mesh();

        void						SetPosition (uint32_t at, const Vector3D& a_Position);
        void						SetColor	(uint32_t at, const Vector3D& a_Color);
        void						SetNormal   (uint32_t at, const Vector3D& a_Normal);
        void						SetUV		(uint32_t at, const Vector2D& a_TexCoord);

        void						SetPositions(std::vector<Vector3D> a_Positions);
        void						SetColors(std::vector<Vector3D> a_Colors);
        void						SetColor(Vector3D a_Color);
        void						SetColor(float a_ColorR, float a_ColorG, float a_ColorB);
        void						SetNormals(std::vector<Vector3D> a_Normals);
        void						SetUVs(std::vector<Vector2D> a_UV);

        void						CopyMesh(const Mesh& pMesh);
        bool						IsDirty() const;
        bool						IsStatic() const;
        void						MakeStatic(bool staticMode);
        void						MakeClean(){m_IsDirty = false;}
        
        void						Update();
        void						SetIndicies(std::vector<uint32_t>a_Ind);
        void                        LoadModel(const std::string &modelPath);
        void                        BuildHalfEdgeMesh();

        inline HalfEdgeMesh*         GetHalfEdgeMesh() { return &mesh; }

        // map from picking IDs to mesh elements, generated during draw_pick
        // and used by setSelection
        std::map<int, HalfEdgeElement *> idToElement;

        friend class MeshFilter;
    protected:
        virtual void				InitMesh();

    private:

        bool						m_IsDirty;
        bool						m_IsStatic;
        uint32_t					m_NumOfVert;

        std::vector<Vector3D>		m_VertPosition;
        std::vector<Vector3D>		m_VertColor;
        std::vector<Vector3D>		m_VertNormal;
        std::vector<Vector2D>		m_VertTexCoord;
        std::vector<uint32_t>		m_Indices;
        HalfEdgeMesh                mesh;

        void                        ProcessNode(aiNode *node, const aiScene *scene);
        void                        ProcessMesh(aiMesh *mesh, const aiScene *scene);
    };
}   // End of CG184


#endif //CGENGINE_MESH_H
