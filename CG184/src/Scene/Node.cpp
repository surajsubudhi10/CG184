//
// Created by suraj on 12/3/17.
//

#include "Node.h"

namespace CG184
{
    int Node::uID = 0;

    Node::Node(const char* name):
        m_NodeName(name),
        m_InstanceID(uID++),
        m_Transform(Transform())
    {
        m_ParentNodePtr = nullptr;
    }

    Node::Node(Transform &a_Trans, const char* name):
            m_NodeName(name),
            m_InstanceID(uID++),
            m_Transform(a_Trans)
    {
        m_ParentNodePtr = nullptr;
    }

    void Node::AddChild(std::shared_ptr<Node> a_Node)
    {
        a_Node->SetParent(this);
        a_Node->UpdateWorldModelMatrix();
        m_ChildNodesPtr.push_back(a_Node);
    }

    NodePtr Node::GetChildNodeAt(uint32_t index)
    {
        if(index >= m_ChildNodesPtr.size())
            return nullptr;

        return m_ChildNodesPtr[index];
    }

    Node* Node::GetParent()
    {
        return m_ParentNodePtr;
    }

    uint32_t Node::GetNumOfChildNode() {
        return static_cast<uint32_t>(m_ChildNodesPtr.size());
    }

    void Node::UpdateWorldModelMatrix() {
        GetWorldTransform();
    }

    const Transform & Node::GetWorldTransform()
    {
        if (m_Transform.isDirty)
            m_Transform.UpdateLocalTransformMatrix();

        m_Transform.m_WorldTransformMat = m_Transform.m_LocalTransformMat;
        if (m_ParentNodePtr != nullptr){
            m_Transform.m_WorldTransformMat = m_ParentNodePtr->GetWorldTransform().m_WorldTransformMat * m_Transform.m_WorldTransformMat;
        }
        return m_Transform;
    }

    void Node::AttachComponent(Component* a_Component) {

        if (a_Component->GetComponentType() == ComponentType::RENDERER) {
            Renderer* renderer = GetComponent<Renderer>();
            if (renderer != nullptr) {
                renderer = dynamic_cast<Renderer*>(a_Component);
            }
        }

        m_ComponentsPtr.push_back(a_Component);
        a_Component->SetAttachedNode(this);
    }

    bool Node::HasComponent(ComponentType comType) {
        for (auto &m_Component : m_ComponentsPtr) {
            return m_Component->GetComponentType() == comType;
        }
        return false;
    }

    void Node::SetParent(Node* parentNode) {
        m_ParentNodePtr = parentNode;
    }

    Node::~Node()
    {
        if(m_ParentNodePtr != nullptr)
            m_ParentNodePtr = nullptr;
    }

    void Node::SetPosition(float _x, float _y, float _z) {
        m_Transform.m_LocalPosition = Vector3D(_x, _y, _z);
        m_Transform.isDirty = true;
    }

    void Node::SetPosition(const Vector3D& pos)
    {
        m_Transform.m_LocalPosition = pos;
        m_Transform.isDirty = true;
    }

    void Node::SetLocalScale(float _x, float _y, float _z) {
        m_Transform.m_LocalScale = Vector3D(_x, _y, _z);
        m_Transform.isDirty = true;
    }

    void Node::SetLocalEulerAngle(float _x, float _y, float _z) {
        m_Transform.m_EulerAngles = Vector3D(_x, _y, _z);
        m_Transform.m_Rotation = ToQuaternion(m_Transform.m_EulerAngles);
        m_Transform.isDirty = true;
    }

    void Node::SetRotation(float angle, Vector3D axis) 
    {
        axis.normalize();
        Quaternion quat(angle, axis);
        m_Transform.m_EulerAngles = quat.ToEulerAngles();
        m_Transform.m_Rotation = quat;
        m_Transform.isDirty = true;
    }

    Node::Node(const Node& node):
            m_NodeName(node.m_NodeName + std::to_string(uID)),
            m_InstanceID(uID++),
            m_Transform(node.m_Transform)
    {
        m_ParentNodePtr = node.m_ParentNodePtr;
        m_ChildNodesPtr = node.m_ChildNodesPtr;
        m_ComponentsPtr = node.m_ComponentsPtr;
    }
}   // End of CG184