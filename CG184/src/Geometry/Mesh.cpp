//
// Created by suraj on 12/2/17.
//

#include <cassert>
#include "Mesh.h"
#include "../Scene/Node.h"

namespace CG184
{
    Mesh::Mesh(std::vector<Vector3D> a_Pos, std::vector<uint32_t>a_Ind) : m_IsDirty(true), m_IsStatic(false)
    {
        m_NumOfVert = (uint32_t)a_Pos.size();
        m_Indices = std::move(a_Ind);
		m_VertPosition = a_Pos;

        for(uint32_t i = 0; i < a_Pos.size(); i++){
			m_VertColor.emplace_back(0.2f, 0.2f, 0.2f);
			m_VertNormal.emplace_back(0.0f, 1.0f, 0.0f);
			m_VertTexCoord.emplace_back(0.0f, 0.0f);
        }
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

    Mesh::Mesh() //: m_InstanceID(Node::uID++)
    {}

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
}