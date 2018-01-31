#pragma once

#include <GL/glew.h>
#include <vector>
#include "IndexBuffer.h"

#include "../Maths/Maths.h"
#include "Material.h"
#include "../Scene/Componet.h"
#include "../Geometry/MeshFilter.h"
#include "../Camera/Camera.h"

namespace CG184 
{

	class Mesh;
	class VertexData;

	enum class RenderMode 
	{
		TRIANGLES,
		LINES,
		POINTS
	};


	class Renderer : public Component
	{
	public:

		Renderer(Mesh* a_Mesh, Material* a_Material);
		Renderer(const Renderer& renderer);
		~Renderer() override ;

		void					Render();
		void					SendProjectionMatrixData (Matrix4D& projMat);
        void					SendViewMatrixData		 (Matrix4D& viewMat);
		void					SendModelMatrixData		 (Matrix4D& modelMat);
		void					SendCameraPosData		 (CameraPtr cam);
		void					SendLightData			 (LightPtr light, int index = 0);
		void					SendMaterialData();

		Material&               GetMaterial()             { return m_Material; }
		Mesh*		            GetMesh()		          { return &m_Mesh; }
		std::shared_ptr<Mesh>   GetSharedMesh()           { return m_SharedMeshPtr; }
        Material*               GetSharedMaterial() const { return m_SharedMaterialPtr; }
		MeshFilter*             GetMeshFilter()           { return m_MeshFilterPtr;}

		inline void				SetRenderMode(RenderMode mode)	{ m_RenderMode = mode; }
		inline void				SetMaterial(Material* material) { m_Material = *material; m_SharedMaterialPtr = material; }
		inline void				SetMesh(Mesh* mesh)				{ m_SharedMeshPtr = std::make_shared<Mesh>(mesh); m_Mesh = *mesh; m_MeshFilterPtr = new MeshFilter(mesh);
		}

    private:
        Matrix4D				GetModelMatrix() const;

        MeshFilter*             m_MeshFilterPtr;
        Material*               m_SharedMaterialPtr;
		std::shared_ptr<Mesh>   m_SharedMeshPtr;

		Mesh                    m_Mesh;
        Material                m_Material;
		RenderMode				m_RenderMode;
	};

	
}