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

		void Render();

		void SendProjectionMatrixData(Matrix4D& projMat);
        void SendViewMatrixData		 (Matrix4D& viewMat);
		void SendModelMatrixData	 (Matrix4D& modelMat);
		void SendCameraPosData		 (CameraPtr cam);
		void SendLightData			 (LightPtr light, int index = 0);
		void SendMaterialData();

		Material&               GetMaterial()             { return m_Material; }
		Mesh*		            GetMesh()		          { return &m_Mesh; }
        shared_ptr<Mesh>        GetSharedMesh()           { return m_SharedMesh; }
        Material*               GetSharedMaterial() const { return m_SharedMaterial; }
//		MeshFilter*             GetMeshFilter()           { return &m_MeshFilter;}

		inline void SetRenderMode(RenderMode mode) { m_RenderMode = mode; }
		inline void SetMaterial(Material* material) { m_Material = *material; m_SharedMaterial = material; }
		inline void SetMesh(Mesh* mesh) { m_SharedMesh = make_shared<Mesh>(mesh); m_Mesh = *mesh; m_MeshFilter = new MeshFilter(mesh);
		}

    private:
        Matrix4D GetModelMatrix() const;

        MeshFilter*             m_MeshFilter;
        Material*               m_SharedMaterial;
        shared_ptr<Mesh>        m_SharedMesh;

		Mesh                    m_Mesh;
        Material                m_Material;
		RenderMode				m_RenderMode;
	};

	
}