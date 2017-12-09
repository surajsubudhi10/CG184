//
// Created by suraj on 12/3/17.
//

#include "Node.h"


namespace CG184
{
    Node::Node():
        transform(Transform()),
        worldModelMatrix(Matrix4D(1.0))
    {
        m_ParentNode = nullptr;
    }

    Node::Node(Transform &a_Trans):
            transform(a_Trans),
            worldModelMatrix(Matrix4D())
    {
        m_ParentNode = nullptr;
    }

    void Node::AddChild(Node& a_Node)
    {
        a_Node.SetParent(this);
        m_ChildNodes.push_back(a_Node);
    }

    Node* Node::GetChildNodeAt(unsigned int index)
    {
        if(index >= m_ChildNodes.size())
            return nullptr;

        return &m_ChildNodes[index];
    }

    Node* Node::GetParent()
    {
        return m_ParentNode;
    }

    unsigned int Node::GetNumOfChildNode() {

        return static_cast<unsigned int>(m_ChildNodes.size());
    }

    void Node::SetWorldModelMatrix() {
        if(m_ParentNode == nullptr)
            worldModelMatrix = transform.GetTransformMat();
        else
            worldModelMatrix = transform.GetTransformMat() * m_ParentNode->transform.GetTransformMat();
    }

    void Node::AttachComponent(Component &a_Component) {
        a_Component.attachedNode = this;
        m_Components.push_back(&a_Component);
    }

    bool Node::HasComponent(ComponentType comType) {
        for (auto &m_Component : m_Components) {
            return m_Component->type == comType;
        }
        return false;
    }

    void Node::SetParent(Node* parentNode) {
        m_ParentNode = parentNode;
    }

    Node::~Node()
    {

    }

    void Node::SetPosition(float _x, float _y, float _z) {
        transform.localPosition = Vector3D(_x, _y, _z);
        transform.UpdateTransformMatrix();
        worldModelMatrix = Transform::Translate(worldModelMatrix, _x, _y, _z);
    }

    void Node::SetLocalScale(float _x, float _y, float _z) {
        transform.localScale = Vector3D(_x, _y, _z);
        transform.UpdateTransformMatrix();
        worldModelMatrix = Transform::Scale(worldModelMatrix, _x, _y, _z);
    }

    void Node::SetLocalEulerAngle(float _x, float _y, float _z) {
        transform.eulerAngles = Vector3D(_x, _y, _z);
        transform.UpdateTransformMatrix();
        worldModelMatrix = Transform::Rotate(worldModelMatrix, _x, Vector3D(1, 0, 0));
        worldModelMatrix = Transform::Rotate(worldModelMatrix, _y, Vector3D(0, 1, 0));
        worldModelMatrix = Transform::Rotate(worldModelMatrix, _z, Vector3D(0, 0, 1));
    }

}