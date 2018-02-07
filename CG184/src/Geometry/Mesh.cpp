//
// Created by suraj on 12/2/17.
//

#include <cassert>
#include "Mesh.h"
#include "../Scene/Node.h"

namespace CG184
{
 
    
    Mesh::Mesh() : m_IsDirty(true), m_IsStatic(false)
    {
        m_NumOfVert = 0;
        m_Indices.clear();
        m_VertPosition.clear();
        m_VertColor.clear();
        m_VertNormal.clear();
        m_VertTexCoord.clear();
    }

    Mesh::Mesh(std::vector<Vector3D> a_Pos, std::vector<uint32_t>a_Ind) : m_IsDirty(true), m_IsStatic(false)
    {
        m_NumOfVert = (uint32_t)a_Pos.size();
        m_Indices = std::move(a_Ind);
        m_VertPosition = a_Pos;

        for(uint32_t i = 0; i < a_Pos.size(); i++){
            m_VertColor.emplace_back(0.5f, 0.5f, 0.5f);
            m_VertNormal.emplace_back(0.0f, 1.0f, 0.0f);
            m_VertTexCoord.emplace_back(0.0f, 0.0f);
        }

        BuildHalfEdgeMesh();
    }

    Mesh::Mesh(Mesh *pMesh)
    {
        m_NumOfVert		= pMesh->m_NumOfVert;
        m_IsDirty		= pMesh->m_IsDirty;
        m_IsStatic		= pMesh->m_IsStatic;

        m_Indices		= pMesh->m_Indices;
        m_VertPosition	= pMesh->m_VertPosition;
        m_VertColor		= pMesh->m_VertColor;
        m_VertNormal	= pMesh->m_VertNormal;
        m_VertTexCoord	= pMesh->m_VertTexCoord;

        BuildHalfEdgeMesh();
    }


    void Mesh::SetPositions(std::vector<Vector3D> a_Positions)
    {
        m_NumOfVert		= (uint32_t)a_Positions.size();
        m_VertPosition	= a_Positions;
        m_IsDirty		= true;
    }

    void Mesh::SetColors(std::vector<Vector3D> a_Colors)
    {
        assert(a_Colors.size() == m_NumOfVert);
        m_VertColor = a_Colors;
        m_IsDirty	= true;
    }

    void Mesh::SetColor(Vector3D a_Color)
    {
        m_VertColor.resize(m_NumOfVert);
        for(uint32_t i = 0; i < m_NumOfVert; i++){
            m_VertColor[i] = a_Color;
        }
        m_IsDirty = true;
    }

    void Mesh::SetColor(float a_ColorR, float a_ColorG, float a_ColorB)
    {
        SetColor(Vector3D(a_ColorR, a_ColorG, a_ColorB));
    }

    void Mesh::SetNormals(std::vector<Vector3D> a_Normals)
    {
        assert(a_Normals.size() == m_NumOfVert);
        m_VertNormal = a_Normals;
        m_IsDirty = true;
    }

    void Mesh::SetUVs(std::vector<Vector2D> a_UV)
    {
        assert(a_UV.size() == m_NumOfVert);
        m_VertTexCoord = a_UV;
        m_IsDirty = true;
    }


    Mesh::~Mesh()
    {
    }

    

    void Mesh::SetIndicies(std::vector<uint32_t> a_Ind) 
    {
        m_Indices = std::move(a_Ind);
        m_IsDirty = true;
    }

    void Mesh::InitMesh()
    {
    }

    void Mesh::Update()
    {
        if(!m_IsStatic && m_IsDirty)
        {
            // Setting up Colors
            if (m_VertColor.size() != m_NumOfVert)
            {
                Vector3D lastVertColor = Vector3D(1.0f);
                if (!m_VertColor.empty()) {
                    lastVertColor = m_VertColor.back();
                }
                
                for (uint32_t i = m_VertColor.size(); i < m_NumOfVert; i++){
                    SetColor(i, lastVertColor);
                }
            }

            // Setting Up Normals
            if (m_VertNormal.size() != m_NumOfVert)
            {
                Vector3D lastVertNormal = Vector3D(0.0f, 1.0f, 0.0f);
                if (!m_VertNormal.empty()) {
                    lastVertNormal = m_VertNormal.back();
                }

                for (uint32_t i = m_VertNormal.size(); i < m_NumOfVert; i++) {
                    SetNormal(i, lastVertNormal);
                }
            }

            // Setting Up Texture Coordinate
            if (m_VertTexCoord.size() != m_NumOfVert)
            {
                Vector2D lastVertUV = Vector2D(0.0f, 0.0f);
                if (!m_VertTexCoord.empty()) {
                    lastVertUV = m_VertTexCoord.back();
                }

                for (uint32_t i = m_VertTexCoord.size(); i < m_NumOfVert; i++) {
                    SetUV(i, lastVertUV);
                }
            }
            m_IsDirty = false;
        }
    }

    bool Mesh::IsDirty() const 
    {
        return m_IsDirty;
    }

    bool Mesh::IsStatic() const 
    {
        return m_IsStatic;
    }

    void Mesh::MakeStatic(bool staticMode) 
    {
        m_IsStatic = staticMode;
    }

    void Mesh::SetPosition(uint32_t at, const Vector3D &a_Position) 
    {
        m_VertPosition[at] = a_Position;
        m_IsDirty = true;
    }

    void Mesh::SetColor(uint32_t at, const Vector3D& a_Color) 
    {
        if (m_VertColor.size() < m_NumOfVert)
            m_VertColor.resize(m_NumOfVert);

        m_VertColor[at] = a_Color;
        m_IsDirty = true;
    }
    
    void Mesh::SetNormal(uint32_t at, const Vector3D& a_Normal) 
    {
        if (m_VertNormal.size() < m_NumOfVert)
            m_VertNormal.resize(m_NumOfVert);

        m_VertNormal[at] = a_Normal;
        m_IsDirty = true;
    }
    
    void Mesh::SetUV(uint32_t at, const Vector2D& a_TexCoord) 
    {
        if (m_VertTexCoord.size() < m_NumOfVert)
            m_VertTexCoord.resize(m_NumOfVert);

        m_VertTexCoord[at] = a_TexCoord;
        m_IsDirty = true;
    }

    void Mesh::CopyMesh(const Mesh& pMesh) 
    {
        m_NumOfVert     = pMesh.m_NumOfVert;
        m_IsDirty       = pMesh.m_IsDirty;
        m_IsStatic      = pMesh.m_IsStatic;

        m_Indices       = pMesh.m_Indices;
        m_VertPosition  = pMesh.m_VertPosition;
        m_VertColor     = pMesh.m_VertColor;
        m_VertNormal    = pMesh.m_VertNormal;
        m_VertTexCoord  = pMesh.m_VertTexCoord;
    }

    void Mesh::BuildHalfEdgeMesh()
    {
        vector<vector<size_t>> indexVec;
        for (uint32_t i = 0; i < m_Indices.size() / 3; i++)
        {
            vector<size_t> tempVec;
            tempVec.push_back(m_Indices[(i * 3) + 0]);
            tempVec.push_back(m_Indices[(i * 3) + 1]);
            tempVec.push_back(m_Indices[(i * 3) + 2]);

            indexVec.push_back(tempVec);
        }

        mesh.build(indexVec, m_VertPosition);
    }

    void Mesh::LoadModel(const std::string &modelPath)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(modelPath,
                                                    aiProcess_Triangulate | 
                                                    aiProcess_OptimizeMeshes |
                                                    aiProcess_JoinIdenticalVertices |
                                                    aiProcess_RemoveComponent);

        //scene = importer.ApplyPostProcessing(aiProcess_RemoveComponent);
        
        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
        {
            std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
            return;
        }
    
        // retrieve the directory path of the filepath
        std:: string directory = modelPath.substr(0, modelPath.find_last_of('/'));
    
        // process ASSIMP's root node recursively
        ProcessNode(scene->mRootNode, scene);
        
        m_NumOfVert = static_cast<uint32_t >(m_VertPosition.size());
        std::cout << "Num of Vertices : " << m_NumOfVert << std::endl;

        BuildHalfEdgeMesh();
    }

    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void Mesh::ProcessNode(aiNode *node, const aiScene *scene)
    {
        // process each mesh located at the current node
        for(unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            // the node object only contains indices to index the actual objects in the scene.
            // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            ProcessMesh(mesh, scene);
        }
        // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
        for(unsigned int i = 0; i < node->mNumChildren; i++)
        {
            ProcessNode(node->mChildren[i], scene);
        }
        
    }
    
    void Mesh::ProcessMesh(aiMesh *mesh, const aiScene *scene)
    {
        // data to fill
        
        // Walk through each of the mesh's vertices
        for(unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            //Vertex vertex;
            Vector3D tempVec; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
            // positions
            tempVec.x = mesh->mVertices[i].x;
            tempVec.y = mesh->mVertices[i].y;
            tempVec.z = mesh->mVertices[i].z;
            m_VertPosition.push_back(tempVec);
            
            // vertex Color
            m_VertColor.emplace_back(0.5f, 0.5f, 0.5f);
            
            // normals
            if (mesh->mNormals) // does the mesh contain Normal
            {
                tempVec.x = mesh->mNormals[i].x;
                tempVec.y = mesh->mNormals[i].y;
                tempVec.z = mesh->mNormals[i].z;
                m_VertNormal.push_back(tempVec);
            }
            else 
            {
                m_VertNormal.emplace_back(0.0f, 0.0f, 0.0f);
            }

            // texture coordinates
            if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
            {
                Vector2D vec;
                // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
                // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                m_VertTexCoord.push_back(vec);
            }
            else
                m_VertTexCoord.emplace_back(0.0f, 0.0f);
            
            
        }
        // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
        for(uint32_t i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            // retrieve all indices of the face and store them in the indices vector
            for(uint32_t j = 0; j < face.mNumIndices; j++)
                m_Indices.push_back(face.mIndices[j]);
        }
        
    }
}   // End of CG184