//
// Created by suraj on 12/3/17.
//

#include <Scene/Node.h>

namespace CG184
{
    int Node::uID = 0;

    Node::Node(const char* name):
        isPickable(true),
        m_NodeName(name),
        m_InstanceID(uID++),
        m_Transform(Transform())
    {
        m_ParentNodePtr = nullptr;
    }

    Node::Node(Transform &a_Trans, const char* name):
            isPickable(true),
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
        m_Transform.m_LocalPosition = Vector3F(_x, _y, _z);
        m_Transform.isDirty = true;
    }

    void Node::SetPosition(const Vector3F& pos)
    {
        m_Transform.m_LocalPosition = pos;
        m_Transform.isDirty = true;
    }

    void Node::SetLocalScale(float _x, float _y, float _z) {
        m_Transform.m_LocalScale = Vector3F(_x, _y, _z);
        m_Transform.isDirty = true;
    }

    void Node::SetLocalEulerAngle(float _x, float _y, float _z) {
        m_Transform.m_EulerAngles = Vector3F(_x, _y, _z);
        m_Transform.m_Rotation = ToQuaternion(m_Transform.m_EulerAngles);
        m_Transform.isDirty = true;
    }

    void Node::SetRotation(float angle, Vector3F axis) 
    {
        axis.normalize();
        QuaternionF quat(angle, axis);
        m_Transform.m_EulerAngles = quat.ToEulerAngles();
        m_Transform.m_Rotation = quat;
        m_Transform.isDirty = true;
    }

    Node::Node(const Node& node):
            isPickable(node.isPickable),
            m_NodeName(node.m_NodeName + std::to_string(uID)),
            m_InstanceID(uID++),
            m_Transform(node.m_Transform)
    {
        m_ParentNodePtr = node.m_ParentNodePtr;
        m_ChildNodesPtr = node.m_ChildNodesPtr;
        m_ComponentsPtr = node.m_ComponentsPtr;
    }

    Mesh* Node::GetMesh()
    {
        if (this->HasComponent(ComponentType::RENDERER)) {
            Renderer* renderer = (this->GetComponent<Renderer>());
            if (renderer != nullptr)
            {
                return renderer->GetMesh();
            }
        }
        return nullptr;
    }

    void Node::SetSelection(int pickID, Selection &selection)
    {
        // Set the selection to the element specified by the given picking ID;
        // these values were generated in Mesh::draw_pick.
        Mesh* mesh = GetMesh();
        if (mesh != nullptr) 
        {
            if (mesh->idToElement.find(pickID) != mesh->idToElement.end())
            {
                //cout << "Selected ID : " << pickID << endl;
                selection.clear();
                selection.object = this;
                selection.element = mesh->idToElement[pickID];
            }
        }
    }

    void Node::newPickElement(int &pickID, HalfEdgeElement *e) 
    {
        Mesh* mesh = GetMesh();
        if (mesh != nullptr) 
        {
            unsigned char R, G, B;
            IndexToRGB(pickID, R, G, B);
            glColor3ub(R, G, B);
            mesh->idToElement[pickID] = e;
            pickID++;
        }
    }

    void Node::DrawPick(int &pickID, bool transformed, CameraPtr cam) 
    {
        Matrix4F mat;
        glPushMatrix();
        glMatrixMode(GL_PROJECTION_MATRIX);
        glLoadIdentity();

        // Multipling the projection Matrix
        mat = cam->GetProjectionMatrix();
        glMultMatrixf(&mat.elements[0]);

        // Multipling the model * view(here identity) Matrix
        glMatrixMode(GL_MODELVIEW_MATRIX);
        mat = cam->GetViewMatrix();
        glMultMatrixf(&mat.elements[0]);


        Mesh* mesh = GetMesh();
        HalfEdgeMesh* half_edge_mesh = mesh->GetHalfEdgeMesh();
        if (mesh != nullptr) 
        {
            mesh->idToElement.clear();
            vector<Vector3F> original_vertex_positions;

            if (transformed) 
            {
                glPushMatrix();
                const auto world_mat = this->GetTransformComponent().GetWorldTransformMat();
                glMultMatrixf(&world_mat.elements[0]);

                for (VertexIter v = half_edge_mesh->verticesBegin(); v != half_edge_mesh->verticesEnd(); v++) 
                {
                    original_vertex_positions.push_back(v->position);
                    v->position +=  v->ComputeNormal() * (float)v->offset;
                }
            }

            for (FaceIter f = half_edge_mesh->facesBegin(); f != half_edge_mesh->facesEnd(); f++) 
            {
                Vector3F c = f->centroid();
                HalfEdgeIter h = f->halfedge();

                do {
                    HalfEdgeIter h1 = h;
                    HalfEdgeIter h2 = h->next();

                    Vector3F a1, b1, p1, q1, r1;
                    Vector3F a2, b2, p2, q2, r2;

                    h1->getPickPoints(a1, b1, p1, q1, r1);
                    h2->getPickPoints(a2, b2, p2, q2, r2);

                    glBegin(GL_TRIANGLES);

                    // vertex
                    newPickElement(pickID, elementAddress(h2->vertex()));
                    glVertex3fv(&a1.x);
                    glVertex3fv(&p1.x);
                    glVertex3fv(&r1.x);

                    // face
                    newPickElement(pickID, elementAddress(f));
                    glVertex3fv(&b1.x);
                    glVertex3fv(&b2.x);
                    glVertex3fv(&c.x);

                    glEnd();

                    glBegin(GL_QUADS);

                    // edge
                    newPickElement(pickID, elementAddress(h2->edge()));
                    glVertex3fv(&p1.x);
                    glVertex3fv(&r2.x);
                    glVertex3fv(&q2.x);
                    glVertex3fv(&q1.x);

                    // halfedge
                    newPickElement(pickID, elementAddress(h2));
                    /*glVertex3fv(&q1.x);
                    glVertex3fv(&q2.x);
                    glVertex3fv(&b2.x);
                    glVertex3fv(&b1.x);*/

                    glEnd();

                    h = h->next();
                } while (h != f->halfedge());
            }

            if (transformed) 
            {
                glPopMatrix();
                int i = 0;
                for (VertexIter v = half_edge_mesh->verticesBegin(); v != half_edge_mesh->verticesEnd(); v++) 
                {
                    v->position = original_vertex_positions[i++];
                }
            }
        }
    }


}   // End of CG184