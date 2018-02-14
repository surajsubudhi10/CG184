#pragma once

#include <string>

#include "../Graphics/Window.h"
#include "../Maths/Maths.h"

namespace CG184 
{
    class Scene;
    class Shader;
    class Material;

    // A Selection stores information about any object or widget that is
    // selected in the scene, which could include a mesh, a light, a
    // camera, or any piece of an object, such as a vertex in a mesh or
    // a rotation handle on a camera.
    class Selection
    {
    public:
        // Types used for scene elements that have well-
        // defined axes (e.g., transformation widgets)
        enum class Axis { X, Y, Z, Center, None };

        Selection() { clear(); }

        void clear() {
            object = nullptr;
            element = nullptr;
            coordinates = Vector3D(0.f, 0.f, 0.f);
            axis = Axis::None;
        }

        bool operator==(const Selection &s) const {
            return object == s.object && element == s.element && axis == s.axis &&
                   coordinates.x == s.coordinates.x &&
                   coordinates.y == s.coordinates.y && coordinates.z == s.coordinates.z;
        }

        bool operator!=(const Selection &s) const { return !(*this == s); }

        class Mesh* object;                 // the selected object
        class HalfEdgeElement *element;     // unused unless object is a mesh
        Vector3D coordinates;               // for optionally selecting a single point
        Axis axis;                          // for optionally selecting an axis

    }; // End of selection class


    class Input
    {
    public:
        explicit Input(WindowPtr window, Scene* scene);

        bool			KeyPressed(std::string key);
        bool			IsKeyPressed(int keyVal); // Temporary
        bool			KeyReleased(std::string key);
        bool			IsMouseButtonDown(int button);
        bool			IsMouseButtonUp(int button);

        void			RenderSelection();
        void			ProcessSelection();

        /**
        * Finds the object pointed to by the given (x, y) point.
        * x and y are from -1 to 1, NOT screenW to screenH.
        * Note that hoverIdx (and therefore has_hover) is automatically updated every
        * time this function is called.
        */
        void            GetHoveredObject(const Vector2D &p, bool getElement = true, bool transformed = false);

        ~Input();

        /* Keep track of which elements of the scene (if any) are currently
        * under the cursor, selected, or being edited. */
        Selection hovered;
        Selection selected;
        Selection edited;

        static Vector2D mousePosition;
    private:
        void			ProcessInput();
        
        WindowPtr		m_Window;
        Scene*			m_ScenePtr;
        Shader*			m_PickerShaderPtr;
        Material*		m_PickerMaterialPtr;
    };

    // Mapping between integer and 8-bit RGB values (used for picking)
    static inline void IndexToRGB(int i, unsigned char &R, unsigned char &G, unsigned char &B)
    {
        R = (i & 0x000000FF) >> 0;
        G = (i & 0x0000FF00) >> 8;
        B = (i & 0x00FF0000) >> 16;
    }

    // Mapping between 8-bit RGB values and integer (used for picking)
    static inline int RGBToIndex(unsigned char R, unsigned char G,
                                 unsigned char B) {
        return R + G * 256 + 256 * 256 * B;
    }


}   // End of CG184