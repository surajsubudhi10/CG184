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
        m_ParentNode = nullptr;
    }

    Node::Node(Transform &a_Trans, const char* name):
            m_NodeName(name),
            m_InstanceID(uID++),
            m_Transform(a_Trans)
    {
        m_ParentNode = nullptr;
    }

    void Node::AddChild(NodePtr a_Node)
    {
        a_Node->SetParent(NodePtr(this));
        a_Node->UpdateWorldModelMatrix();
        m_ChildNodes.push_back(a_Node);
    }

    NodePtr Node::GetChildNodeAt(uint32_t index)
    {
        if(index >= m_ChildNodes.size())
            return nullptr;

        return m_ChildNodes[index];
    }

    NodePtr Node::GetParent()
    {
        return m_ParentNode;
    }

	uint32_t Node::GetNumOfChildNode() {
        return static_cast<uint32_t>(m_ChildNodes.size());
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

    void Node::AttachComponent(Component* a_Component) {
		if (a_Component->GetComponentType() == ComponentType::RendererType) {
			Renderer* renderer = GetComponent<Renderer>();
			if (renderer != nullptr) {
				renderer = dynamic_cast<Renderer*>(a_Component);
			}
		}

		m_Components.push_back(a_Component);
		a_Component->SetAttachedNode(this);
    }

    bool Node::HasComponent(ComponentType comType) {
        for (auto &m_Component : m_Components) {
            return m_Component->GetComponentType() == comType;
        }
        return false;
    }

    void Node::SetParent(NodePtr parentNode) {
        m_ParentNode = std::move(parentNode);
    }

    Node::~Node()
    {
		m_ParentNode = nullptr;
    }

    void Node::SetPosition(float _x, float _y, float _z) {
		m_Transform.localPosition = Vector3D(_x, _y, _z);
		m_Transform.isDirty = true;
    }

    void Node::SetLocalScale(float _x, float _y, float _z) {
		m_Transform.localScale = Vector3D(_x, _y, _z);
		m_Transform.isDirty = true;
    }

	void Node::SetLocalEulerAngle(float _x, float _y, float _z) {
		m_Transform.eulerAngles = Vector3D(_x, _y, _z);
		m_Transform.rotation = ToQuaternion(m_Transform.eulerAngles);
		m_Transform.isDirty = true;
	}

	void Node::SetRotation(float angle, Vector3D axis) 
	{
		axis.normalize();
		Quaternion quat(angle, axis);
		m_Transform.eulerAngles = quat.ToEulerAngles();
		m_Transform.rotation = quat;
		m_Transform.isDirty = true;
	}

    Node::Node(const Node& node):
            m_NodeName(node.m_NodeName + std::to_string(uID)),
            m_InstanceID(uID++),
            m_Transform(node.m_Transform)
    {
        m_ParentNode = node.m_ParentNode;
        m_ChildNodes = node.m_ChildNodes;
        m_Components = node.m_Components;
    }
}