//
// Created by suraj on 12/3/17.
//

#ifndef CGENGINE_NODE_H
#define CGENGINE_NODE_H

#include <vector>
#include <memory>
#include "Transform.h"
#include "Componet.h"
#include "../Graphics/Renderer.h"


namespace CG184
{
    class Node
    {
    public:
        explicit Node(const char* name);
        Node(Transform& a_Trans, const char* name);
        Node(Node* node);
        virtual ~Node();

        std::shared_ptr<Node> GetChildNodeAt(uint32_t index);
        std::shared_ptr<Node> GetParent();
        void SetParent(std::shared_ptr<Node> parentNode);

		uint32_t GetNumOfChildNode();
        void AddChild(std::shared_ptr<Node> node);

        void AttachComponent(Component* a_Component);
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
    private:

        const char* m_NodeName;
        const int m_InstanceID;

        std::vector<std::shared_ptr<Node>> m_ChildNodes;
        std::vector<Component*> m_Components;
        std::shared_ptr<Node> m_ParentNode;

        static int uID;
    };

    typedef std::shared_ptr<Node> NodePtr;

}


#endif //CGENGINE_NODE_H
