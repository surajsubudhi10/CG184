//
// Created by suraj on 12/3/17.
//

#ifndef CGENGINE_COMPONET_H
#define CGENGINE_COMPONET_H

namespace CG184{
    class Node;

    enum ComponentType
    {
        RendererType,

        // TODO we will be adding extra components as we create derived component classes
        CG184Type
    };

    class Component{
    public:
        Component() : m_Type(ComponentType::CG184Type)
        {
            m_AttachedNode = nullptr;
        }
        virtual ~Component(){ m_AttachedNode = nullptr;}

        inline Node* GetAttachedNode(){ return m_AttachedNode;}
        inline ComponentType GetComponentType(){ return m_Type;}

        inline void SetAttachedNode(Node* a_Node){m_AttachedNode = a_Node;}
        inline void SetComponentType(ComponentType type){m_Type = type;}

    protected:
        Node* m_AttachedNode;
        ComponentType m_Type;

    };
}


#endif //CGENGINE_COMPONET_H
