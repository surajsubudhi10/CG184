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
        explicit Scene(Camera* cam);
        ~Scene();

        void Render();
        void AddToScene(Node* node);
        void AddLight(Light* light);

    private:
        Camera* m_Camera;
        std::vector<Node*> m_RenderQueue;
		std::vector<Light*> m_Lights;

        void TraverseAllChildNodes(Node& a_Node);

    };
}


#endif //CGENGINE_SCENE_H
