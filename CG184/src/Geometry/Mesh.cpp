//
// Created by suraj on 12/2/17.
//

#include <cassert>
#include "Mesh.h"
#include "../Scene/Node.h"

namespace CG184
{
    Mesh::Mesh(std::vector<Vector3D> a_Pos, std::vector<uint32_t>a_Ind) : m_IsDirty(true), m_IsStatic(false)//, m_InstanceID(Node::uID++)
    {
        m_NumOfVert = (uint32_t)a_Pos.size();
        m_Indices = std::move(a_Ind);
        vertPosition = a_Pos;

        for(uint32_t i = 0; i < a_Pos.size(); i++){
            vertColor.emplace_back(0.2f, 0.2f, 0.2f);
            vertNormal.emplace_back(0.0f, 1.0f, 0.0f);
            vertTexCoord.emplace_back(0.0f, 0.0f);
        }
    }

    Mesh::Mesh(Mesh *pMesh)//: m_InstanceID(Node::uID++)
    {
        m_NumOfVert = pMesh->m_NumOfVert;
        m_IsDirty = pMesh->m_IsDirty;
        m_IsStatic = pMesh->m_IsStatic;

        m_Indices = pMesh->m_Indices;
        vertPosition = pMesh->vertPosition;
        vertColor = pMesh->vertColor;
        vertNormal = pMesh->vertNormal;
        vertTexCoord = pMesh->vertTexCoord;
    }


    void Mesh::SetPositions(std::vector<Vector3D> a_Positions)
    {
        m_NumOfVert = (uint32_t)a_Positions.size();
        vertPosition = a_Positions;
        m_IsDirty = true;
    }

    void Mesh::SetColors(std::vector<Vector3D> a_Colors)
    {
        assert(a_Colors.size() == m_NumOfVert);
        vertColor = a_Colors;
        m_IsDirty = true;
    }

    void Mesh::SetColor(Vector3D a_Color)
    {
        vertColor.resize(m_NumOfVert);
        for(uint32_t i = 0; i < m_NumOfVert; i++){
            vertColor[i] = a_Color;
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
        vertNormal = a_Normals;
        m_IsDirty = true;
    }

    void Mesh::SetUVs(std::vector<Vector2D> a_UV)
    {
        assert(a_UV.size() == m_NumOfVert);
        vertTexCoord = a_UV;
        m_IsDirty = true;
    }

    Mesh::~Mesh()
    {
    }

    Mesh::Mesh() //: m_InstanceID(Node::uID++)
    {}

    void Mesh::SetIndicies(std::vector<uint32_t> a_Ind) {
        m_Indices = std::move(a_Ind);
        m_IsDirty = true;
    }

    void Mesh::InitMesh()
    {
    }

//    void Mesh::Update(){
//        if(!m_IsStatic && m_IsDirty){
//
//            m_IsDirty = false;
//        }
//    }

    bool Mesh::IsDirty() const {
        return m_IsDirty;
    }

    bool Mesh::IsStatic() const {
        return m_IsStatic;
    }

    void Mesh::MakeStatic(bool staticMode) {
        m_IsStatic = staticMode;
    }

    void Mesh::SetPosition(uint32_t at, const Vector3D &a_Position) {
        vertPosition[at] = a_Position;
        m_IsDirty = true;
    }

    void Mesh::CopyMesh(const Mesh& pMesh) {

        //m_InstanceID = Node::uID++;
        m_NumOfVert     = pMesh.m_NumOfVert;
        m_IsDirty       = pMesh.m_IsDirty;
        m_IsStatic      = pMesh.m_IsStatic;

        m_Indices       = pMesh.m_Indices;
        vertPosition    = pMesh.vertPosition;
        vertColor       = pMesh.vertColor;
        vertNormal      = pMesh.vertNormal;
        vertTexCoord    = pMesh.vertTexCoord;

    }


}