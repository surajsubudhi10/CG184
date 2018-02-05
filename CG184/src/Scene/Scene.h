//
// Created by suraj on 12/4/17.
//

#ifndef CGENGINE_SCENE_H
#define CGENGINE_SCENE_H

#include <iostream>
#include "Node.h"
#include "../Camera/Camera.h"
#include "../Lights/Light.h"


namespace CG184 
{
    class Scene
    {
    public:
        explicit Scene(CameraPtr cam);
        ~Scene();

        void Render();
        void AddToScene(NodePtr node);
        void AddLight(LightPtr light);

        friend class Input;

    private:
        CameraPtr				m_CameraPtr;
        NodePtr					m_AnchorPtr;
        std::vector<NodePtr>	m_RenderQueue;
        std::vector<LightPtr>	m_LightsPtr;

        void TraverseAllChildNodes(Node& a_Node);
        void CreateAnchor();
    };
}   // End of CG184


#endif //CGENGINE_SCENE_H
