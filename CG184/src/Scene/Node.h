//
// Created by suraj on 12/3/17.
//

#ifndef CGENGINE_NODE_H
#define CGENGINE_NODE_H

#include <vector>
#include "Transform.h"
#include "Componet.h"
#include "../Graphics/Renderer.h"


namespace CG184 {


    class Node {

    public:
        explicit Node(const char* name);
        Node(Transform& a_Trans, const char* name);

        virtual ~Node();

        Node* GetChildNodeAt(uint32_t index);
        Node* GetParent();
        void SetParent(Node* parentNode);

		uint32_t GetNumOfChildNode();
        void AddChild(Node* node);

        void AttachComponent(Component& a_Component);
        bool HasComponent(ComponentType comType);

        void SetPosition(float _x, float _y, float _z);
        void SetLocalScale(float _x, float _y, float _z);
        void SetLocalEulerAngle(float _x, float _y, float _z);
		void SetRotation(float angle, Vector3D axis);

        void UpdateWorldModelMatrix();

		inline Transform& GetTransformComponent() { return m_Transform; }
		const Transform& GetWorldTransform();

        inline int GetInstanceID(){ return m_InstanceID;}
        inline const char* GetName(){ return m_NodeName;}
        inline void SetName(const char* name){m_NodeName = name;}

        template <typename T>
        T* GetComponent()
        {
            for (auto m_Component : m_Components) {
                if (dynamic_cast<T*>(m_Component))
                    return (T *) m_Component;
            }
            return nullptr;
        }

    protected:
        Transform m_Transform;
        //Matrix4D worldModelMatrix;
    private:

        const char* m_NodeName;
        const int m_InstanceID;

        std::vector<Node*> m_ChildNodes;
        std::vector<Component*> m_Components;
        Node* m_ParentNode;

        static int uID;
    };
}


#endif //CGENGINE_NODE_H
