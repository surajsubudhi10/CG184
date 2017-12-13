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
        transform(Transform()),
        worldModelMatrix(Matrix4D(1.0))
    {
        m_ParentNode = nullptr;
    }

    Node::Node(Transform &a_Trans, const char* name):
            m_NodeName(name),
            m_InstanceID(uID++),
            transform(a_Trans),
            worldModelMatrix(Matrix4D())
    {
        m_ParentNode = nullptr;
    }

    void Node::AddChild(Node* a_Node)
    {
        a_Node->SetParent(this);
        a_Node->UpdateWorldModelMatrix();
        m_ChildNodes.push_back(a_Node);
    }

    Node* Node::GetChildNodeAt(unsigned int index)
    {
        if(index >= m_ChildNodes.size())
            return nullptr;

        return m_ChildNodes[index];
    }

    Node* Node::GetParent()
    {
        return m_ParentNode;
    }

    unsigned int Node::GetNumOfChildNode() {

        return static_cast<unsigned int>(m_ChildNodes.size());
    }

    void Node::UpdateWorldModelMatrix() {
		GetWorldTransform();
    }

    void Node::AttachComponent(Component &a_Component) {
        a_Component.SetAttachedNode(this);
        m_Components.push_back(&a_Component);
    }

    bool Node::HasComponent(ComponentType comType) {
        for (auto &m_Component : m_Components) {
            return m_Component->GetComponentType() == comType;
        }
        return false;
    }

    void Node::SetParent(Node* parentNode) {
        m_ParentNode = parentNode;
    }

    Node::~Node()
    = default;

    void Node::SetPosition(float _x, float _y, float _z) {
        transform.localPosition = Vector3D(_x, _y, _z);
        transform.UpdateTransformMatrix();
    }

    void Node::SetLocalScale(float _x, float _y, float _z) {
        transform.localScale = Vector3D(_x, _y, _z);
        transform.UpdateTransformMatrix();
    }

    void Node::SetLocalEulerAngle(float _x, float _y, float _z) {
        transform.eulerAngles = Vector3D(_x, _y, _z);
		transform.UpdateTransformMatrix();
    }

    const Transform &Node::GetWorldTransform() {
        worldModelMatrix = transform.transformMat;
        if (m_ParentNode != nullptr){
            worldModelMatrix = m_ParentNode->GetWorldTransform().transformMat * worldModelMatrix;
        }

        return transform;
    }

}