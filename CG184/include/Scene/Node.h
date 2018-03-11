//
// Created by suraj on 12/3/17.
//

#ifndef CGENGINE_NODE_H
#define CGENGINE_NODE_H

#include <vector>
#include <memory>
#include "Transform.h"
#include "Componet.h"
#include <Graphics/Renderer.h>
#include <EventSystem/Input.h>


namespace CG184
{
    class Node
    {
    public:
        explicit Node(const char* name);
        Node(Transform& a_Trans, const char* name);
        Node(const Node& node);
        virtual ~Node();

        void					AddChild(std::shared_ptr<Node> node);
        void					AttachComponent(Component* a_Component);
        bool					HasComponent(ComponentType comType);
        void					UpdateWorldModelMatrix();

        void					SetParent(Node* parentNode);
        void					SetPosition(float _x, float _y, float _z);
        void					SetPosition(const Vector3F& pos);
        void					SetLocalScale(float _x, float _y, float _z);
        void					SetLocalEulerAngle(float _x, float _y, float _z);
        void					SetRotation(float angle, Vector3F axis);
        inline void				SetName(const char* name){m_NodeName = name;}

        Node*					GetParent();
        uint32_t				GetNumOfChildNode();
        std::shared_ptr<Node>	GetChildNodeAt(uint32_t index);
        const Transform&		GetWorldTransform();
        class Mesh*             GetMesh();

        inline Transform&		GetTransformComponent() { return m_Transform; }
        inline int				GetInstanceID(){ return m_InstanceID;}
        inline std::string		GetName(){ return m_NodeName;}

        
        void                    SetSelection(int pickID, Selection &selection);
        void                    newPickElement(int &pickID, HalfEdgeElement *e);
        void                    DrawPick(int &pickID, bool transformed, CameraPtr cam);

        template <typename T>
        T* GetComponent()
        {
            for (auto m_Component : m_ComponentsPtr) {
                if (dynamic_cast<T*>(m_Component))
                    return (T *) m_Component;
            }
            return nullptr;
        }


        bool                                    isPickable;
    protected:
        Transform								m_Transform;
    private:

        std::string								m_NodeName;
        const int								m_InstanceID;

        std::vector<std::shared_ptr<Node>>		m_ChildNodesPtr;
        std::vector<Component*>					m_ComponentsPtr; // TODO use list instead of vector
        Node*									m_ParentNodePtr;

    public:
        static int uID;
    };

    typedef std::shared_ptr<Node> NodePtr;

}   // End of CG184


#endif //CGENGINE_NODE_H
