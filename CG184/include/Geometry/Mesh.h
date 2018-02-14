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
#include <EventSystem/Input.h>

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


        /// Assigns the next consecutive pickID to the given element, and
        /// sets the GL color accordingly.  Also increments pickID.
        void                        newPickElement(int &pickID, HalfEdgeElement *e);

        /**
        * Rather than drawing the object geometry for display, this method draws the
        * object with unique colors that can be used to determine which object was
        * selected or "picked" by the cursor.  The parameter pickID is the lowest
        * consecutive integer that has so far not been used by any other object as
        * a picking ID.  (Draw colors are then derived from these IDs.)  This data
        * will be used by Scene::getHoveredObject to make the final determination
        * of which object (and possibly element within that object) was picked.
        */
        void                        draw_pick(int &pickID, bool transformed = false);

        /** Assigns attributes of the selection based on the ID of the
        * object that was picked.  Can assume that pickID was one of
        * the IDs generated during this object's call to draw_pick().
        */
        void setSelection(int pickID, Selection &selection);


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

        // map from picking IDs to mesh elements, generated during draw_pick
        // and used by setSelection
        map<int, HalfEdgeElement*> m_IdToElement;

        void                        ProcessNode(aiNode *node, const aiScene *scene);
        void                        ProcessMesh(aiMesh *mesh, const aiScene *scene);
    };
}   // End of CG184


#endif //CGENGINE_MESH_H
