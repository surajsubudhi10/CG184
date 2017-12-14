#pragma once

#include <GL/glew.h>
#include <vector>
#include "IndexBuffer.h"

#include "../Maths/Maths.h"
#include "Material.h"
#include "../Scene/Componet.h"
#include "../Geometry/MeshFilter.h"

namespace CG184 
{

	class Mesh;
	class VertexData;

	class Renderer : public Component
	{
	public:

		Renderer(Mesh& a_Mesh, Material& a_Material);
		~Renderer();

		void Render();

        void SendProjectionMatrixData(Matrix4D& projMat);
        void SendViewMatrixData(Matrix4D& viewMat);

		void SendLightData(Light& light);
		void SendMaterialData();

    private:
        Matrix4D GetModelMatrix();
		
		MeshFilter* m_MeshFilter;
        Material* m_Material;

	};

	
}