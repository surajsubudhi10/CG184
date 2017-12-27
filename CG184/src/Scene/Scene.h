//
// Created by suraj on 12/4/17.
//

#ifndef CGENGINE_SCENE_H
#define CGENGINE_SCENE_H

#include <iostream>
#include "Node.h"
#include "../Camera/Camera.h"
#include "../Lights/Light.h"


namespace CG184 {



    class Scene
    {
    public:
        explicit Scene(CameraPtr cam);
        ~Scene();

        void Render();
        void AddToScene(NodePtr node);
        void AddLight(LightPtr light);

    private:
        CameraPtr m_Camera;
        std::vector<NodePtr> m_RenderQueue;
		std::vector<LightPtr> m_Lights;

        void TraverseAllChildNodes(Node& a_Node);

    };
}


#endif //CGENGINE_SCENE_H
