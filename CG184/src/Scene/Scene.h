//
// Created by suraj on 12/4/17.
//

#ifndef CGENGINE_SCENE_H
#define CGENGINE_SCENE_H

#include <iostream>
#include "Node.h"
#include "../Camera/Camera.h"


namespace CG184 {


    class Scene : public Node
    {
    public:
        explicit Scene(Camera& cam);
        ~Scene() override;

        void Render();
        void AddToScene(Node& node);

    private:
        Camera* m_Camera;
        std::vector<Node> m_Nodes;

        void TraverseAllChildNodes(Node& a_Node);

    };
}


#endif //CGENGINE_SCENE_H
