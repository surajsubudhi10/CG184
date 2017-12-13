//
// Created by suraj on 12/3/17.
//

#include "Node.h"


namespace CG184
{
    Node::Node():
		m_Transform(Transform())
    {
        m_ParentNode = nullptr;
    }

    Node::Node(Transform &a_Trans):
		m_Transform(a_Trans)
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

	const Transform & Node::GetWorldTransform()
	{
		if (m_Transform.isDirty)
			m_Transform.UpdateLocalTransformMatrix();

		m_Transform.worldTransformMat = m_Transform.localTransformMat;
		if (m_ParentNode != nullptr){
			m_Transform.worldTransformMat = m_ParentNode->GetWorldTransform().worldTransformMat * m_Transform.worldTransformMat;
		}
		return m_Transform;
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
    {

    }

    void Node::SetPosition(float _x, float _y, float _z) {
		m_Transform.localPosition = Vector3D(_x, _y, _z);
		m_Transform.isDirty = true;
		//m_Transform.UpdateLocalTransformMatrix();
    }

    void Node::SetLocalScale(float _x, float _y, float _z) {
		m_Transform.localScale = Vector3D(_x, _y, _z);
		m_Transform.isDirty = true;
		//m_Transform.UpdateLocalTransformMatrix();
    }

	void Node::SetLocalEulerAngle(float _x, float _y, float _z) {
		m_Transform.eulerAngles = Vector3D(_x, _y, _z);
		m_Transform.isDirty = true;
		//m_Transform.UpdateLocalTransformMatrix();
	}
}