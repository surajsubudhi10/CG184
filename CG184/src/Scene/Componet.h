//
// Created by suraj on 12/3/17.
//

#ifndef CGENGINE_COMPONET_H
#define CGENGINE_COMPONET_H

namespace CG184{
    class Node;

    enum class ComponentType
    {
        RENDERER,

        // TODO we will be adding extra components as we create derived component classes
        OTHER
    };

    class Component{
    public:
        Component() : m_IsEnable(true), m_Type(ComponentType::OTHER)
        {
            m_AttachedNode = nullptr;
        }
        virtual ~Component(){ m_AttachedNode = nullptr;}

        Node* GetAttachedNode(){ return m_AttachedNode;}
        ComponentType GetComponentType() const { return m_Type;}

        void SetAttachedNode(Node* a_Node){m_AttachedNode = a_Node;}
        void SetComponentType(ComponentType type){m_Type = type;}

        void SetEnable(bool isEnable){
            m_IsEnable = isEnable;
        }

        bool IsEnabled(){ return  m_IsEnable;}

    protected:

        bool m_IsEnable;
        Node* m_AttachedNode;
        ComponentType m_Type;

    };
}


#endif //CGENGINE_COMPONET_H
