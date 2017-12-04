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
        Node();
        explicit Node(Transform& a_Trans);

        virtual ~Node();

        Node* GetChildNodeAt(unsigned int index);
        Node* GetParent();
        void SetParent(Node* parentNode);

        unsigned int GetNumOfChildNode();
        void AddChild(Node& node);

        void AttachComponent(Component& a_Component);
        bool HasComponent(ComponentType comType);

        void SetPosition(float _x, float _y, float _z);
        void SetLocalScale(float _x, float _y, float _z);

        template <typename T>
        T* GetComponent()
        {
            for (auto m_Component : m_Components) {
                if (dynamic_cast<T*>(m_Component))
                    return (T *) m_Component;
            }
            return nullptr;
        }

    public:
        Transform transform;
        Matrix4D worldModelMatrix;

    private:
        void SetWorldModelMatrix();
        std::vector<Node> m_ChildNodes;
        std::vector<Component*> m_Components;
        Node* m_ParentNode;

//        Renderer* m_Renderer;

    };
}


#endif //CGENGINE_NODE_H
