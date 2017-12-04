//
// Created by suraj on 12/3/17.
//

#ifndef CGENGINE_COMPONET_H
#define CGENGINE_COMPONET_H

namespace CG184{
    class Node;

    enum ComponentType
    {
        RendererType,

        // TODO we will be adding extra components as we create derived component classes
        CG184Type
    };

    class Component{
    public:
        Component() : type(ComponentType::CG184Type)
        {
            attachedNode = nullptr;
        }
        virtual ~Component(){}


        Node* attachedNode;
        ComponentType type;

    private:

    };
}


#endif //CGENGINE_COMPONET_H
