#ifndef CGENGINE_HALFEDGEELEMENT_H
#define CGENGINE_HALFEDGEELEMENT_H

#include <iostream>
#include <list>
#include <map>
#include <set>
#include <utility>
#include <vector>

#include "../Maths/Matrix4D.h"
#include <Maths/Vector2D.h>


using namespace std;

typedef std::vector<std::string> Info;

// For code clarity, we often want to distinguish between
// an integer that encodes an index (an "ordinal" number)
// from an integer that encodes a size (a "cardinal" number).
typedef size_t Index;
typedef size_t Size;

namespace CG184 
{
    /*
    * A HalfEdgeMesh is comprised of four atomic element types:
    * vertices, edges, faces, and halfedges.
    */
    class Vertex;
    class Edge;
    class Face;
    class HalfEdge;

    /*
    * Rather than using raw pointers to mesh elements, we store references
    * as STL::iterators---for convenience, we give shorter names to these
    * iterators (e.g., EdgeIter instead of list<Edge>::iterator).
    */
    typedef list<Vertex>::iterator VertexIter;
    typedef list<Edge>::iterator EdgeIter;
    typedef list<Face>::iterator FaceIter;
    typedef list<HalfEdge>::iterator HalfEdgeIter;

    /*
    * We also need "const" iterator types, for situations where a method takes
    * a constant reference or pointer to a HalfEdgeMesh.  Since these types are
    * used so frequently, we will use "CIter" as a shorthand abbreviation for
    * "constant iterator."
    */
    typedef list<Vertex>::const_iterator VertexCIter;
    typedef list<Edge>::const_iterator EdgeCIter;
    typedef list<Face>::const_iterator FaceCIter;
    typedef list<HalfEdge>::const_iterator HalfEdgeCIter;


    /*
    * Some algorithms need to know how to compare two iterators (which comes
    * first?)
    * Here we just say that one iterator comes before another if the address of the
    * object it points to is smaller.  (You should not have to worry about this!)
    */
    inline bool operator<(const HalfEdgeIter& i, const HalfEdgeIter& j) {
        return &*i < &*j;
    }
    inline bool operator<(const VertexIter& i, const VertexIter& j) {
        return &*i < &*j;
    }
    inline bool operator<(const EdgeIter& i, const EdgeIter& j) {
        return &*i < &*j;
    }
    inline bool operator<(const FaceIter& i, const FaceIter& j) {
        return &*i < &*j;
    }

    // We also need to know how to compare const iterators.
    inline bool operator<(const HalfEdgeCIter& i, const HalfEdgeCIter& j) {
        return &*i < &*j;
    }
    inline bool operator<(const VertexCIter& i, const VertexCIter& j) {
        return &*i < &*j;
    }
    inline bool operator<(const EdgeCIter& i, const EdgeCIter& j) {
        return &*i < &*j;
    }
    inline bool operator<(const FaceCIter& i, const FaceCIter& j) {
        return &*i < &*j;
    }

    /**
    * The elementAddress() function is defined only for convenience (and
    * readability), and returns the actual memory address associated with
    * a mesh element referred to by the given iterator.  (This is especially
    * helpful for things like debugging, where we want to check that one
    * element is properly pointing to another.)
    */
    inline HalfEdge* elementAddress(HalfEdgeIter h) { return &(*h); }
    inline Vertex*   elementAddress(VertexIter v)   { return &(*v); }
    inline Edge*     elementAddress(EdgeIter e)     { return &(*e); }
    inline Face*     elementAddress(FaceIter f)     { return &(*f); }

    /**
    * Same thing, just for constant references.
    */
    inline HalfEdge const* elementAddress(HalfEdgeCIter h)  { return &(*h); }
    inline Vertex   const* elementAddress(VertexCIter v)    { return &(*v); }
    inline Edge     const* elementAddress(EdgeCIter e)      { return &(*e); }
    inline Face     const* elementAddress(FaceCIter f)      { return &(*f); }


    class EdgeRecord
    {
    public:
        EdgeRecord(void) {}
        EdgeRecord(EdgeIter& _edge);

        EdgeIter edge;
        Vector3F optimalPoint;
        double score;
    
    }; // End of class EdgeRecord
    
    inline bool operator<(const EdgeRecord& r1, const EdgeRecord& r2)
    {
        if (r1.score != r2.score)
        {
            return (r1.score < r2.score);
        }

        EdgeIter e1 = r1.edge;
        EdgeIter e2 = r2.edge;
        return &*e1 < &*e2;
    } 


    /**
    * HalfEdgeElement is the base type for all mesh elements (halfedges,
    * vertices, edges, and faces).  This type is used whenever we want
    * a pointer to a generic element (i.e., we don't know if it's a vertex
    * edge, face, or halfedge).  It is mainly used for debugging and
    * visualization, and should probably not be used for most actual mesh
    * processing tasks.
    */

    class HalfEdgeElement 
    {
    public:
        /**
        * Check if the element is a halfEdge.
        * \return pointer to the half edge structure if the element is a half edge,
        * NULL otherwise.
        */
        HalfEdge* getHalfEdge();

        /**
        * Check if the element is a vertex.
        * \return pointer to the vertex structure if the element is a half edge, NULL
        * otherwise.
        */
        Vertex* getVertex();

        /**
        * Check if the element is an edge.
        * \return pointer to the edge structure if the element is an edge, NULL
        * otherwise.
        */
        Edge* getEdge();

        /**
        * Check if the element is a face.
        * \return pointer to the face structure if the element is a face, NULL
        * otherwise.
        */
        Face* getFace();

        /**
        * Destructor.
        */
        virtual ~HalfEdgeElement() {}
    
    }; // End of HalfEdgeElement class


    class HalfEdge : public HalfEdgeElement 
    {
    public:
        HalfEdgeIter&   twin()  { return _twin; }      ///< access the twin half edge
        HalfEdgeIter&   next()  { return _next; }      ///< access the next half edge
        VertexIter&     vertex(){ return _vertex; }    ///< access the vertex in the half edge
        EdgeIter&       edge()  { return _edge; }      ///< access the edge the half edge is on
        FaceIter&       face()  { return _face; }      ///< access the face the half edge is on

        HalfEdgeCIter   twin()   const { return _twin; }        ///< access the twin half edge (const iterator)
        HalfEdgeCIter   next()   const { return _next; }        ///< access the next half edge (comst iterator)
        VertexCIter     vertex() const { return _vertex; }      ///< access the vertex in the half edge (const iterator)
        EdgeCIter       edge()   const { return _edge; }        ///< access the edge the half edge is on (const iterator)
        FaceCIter       face()   const { return _face; }        ///< access the face the half edge is on (const iterator)

        /**
        * Check if the edge is a boundary edge.
        * \return true if yes, false otherwise
        */
        bool isBoundary() const;

        void getPickPoints(Vector3F& a, Vector3F& b, Vector3F& p, Vector3F& q, Vector3F& r) const;


        /**
        * For convenience, this method sets all of the
        * neighbors of this halfedge to the given values.
        */
        void setNeighbors(HalfEdgeIter next, HalfEdgeIter twin, VertexIter vertex, EdgeIter edge, FaceIter face) 
        {
            _next = next;
            _twin = twin;
            _vertex = vertex;
            _edge = edge;
            _face = face;
        }

    protected:
        HalfEdgeIter _twin;  ///< halfedge on the "other side" of the edge
        HalfEdgeIter _next;  ///< next halfedge around the current face
        VertexIter   _vertex;  ///< vertex at the "base" or "root" of this halfedge
        EdgeIter     _edge;      ///< associated edge
        FaceIter     _face;      ///< face containing this halfedge
    
    }; // End of HalfEdge class

    /**
    * A Face is a single polygon in the mesh.
    */
    class Face : public HalfEdgeElement 
    {
    public:
        /**
        * initializes the face, possibly setting its boundary flag
        * (by default, a Face does not encode a boundary loop)
        */
        Face(bool isBoundary = false) : _isBoundary(isBoundary) {}

        /**
        * Returns a reference to some halfedge of this face
        */
        HalfEdgeIter& halfedge() { return _halfedge; }

        /**
        * Returns some halfedge of this face
        */
        HalfEdgeCIter halfedge() const { return _halfedge; }

        /**
        * returns the number of edges (or equivalently, vertices) of this face
        */
        Size degree() const 
        {
            Size d = 0;  // degree 
            // walk around the face
            HalfEdgeIter h = _halfedge;
            do 
            {
                d++;  // increment the degree
                h = h->next();
            } while (h != _halfedge);  // done walking around the face

            return d;
        }

        /**
        * check if this face represents a boundary loop
        * \returns true if and only if this face represents a boundary loop, false
        * otherwise
        */
        bool isBoundary() const { return _isBoundary; }

        /**
        * Get a unit face normal (computed via the area vector).
        * \returns a unit face normal (computed via the area vector).
        */
        Vector3F normal() const;

        Vector3F centroid() const;

        Index id;
        Matrix4D quadric;

    protected:
        HalfEdgeIter _halfedge;  ///< one of the halfedges of this face
        bool _isBoundary;
    
    }; // End of Face class

    /**
    * A Vertex encodes one of the mesh vertices
    */
    class Vertex : public HalfEdgeElement {
    public:
        /**
        * returns some halfedge rooted at this vertex (reference)
        */
        HalfEdgeIter& halfedge(void) { return _halfedge; }

        /**
        * returns some halfedge rooted at this vertex
        */
        HalfEdgeCIter halfedge(void) const { return _halfedge; }

        Index id;
        Vector3F position;  ///< location in 3-space
        Vector3F color;     ///< color in 3-space
        Vector3F normal;    ///< normal in 3-space
        Vector2D textCoord;  ///< texture coordinate

        const double offset = 0.001;

        Vector3F newPosition; ///< For Loop subdivision, this will be the updated position of the vertex
        bool isNew; ///< For Loop subdivision, this flag should be true if and only if this vertex is a new vertex created by subdivision (i.e., if it corresponds to a vertex of the original mesh)

        /**
        * computes the average of the neighboring vertex positions and stores it in Vertex::centroid
        */
        void computeCentroid(void);

        Vector3F centroid; ///< average of neighbor positions, storing the value computed by Vertex::computeCentroid()

        Vector3F ComputeNormal(void) const;

        /**
        * Check if if this vertex is on the boundary of the surface
        * \return true if and only if this vertex is on the boundary
        * of the surface, false otherwise
        */
        bool isBoundary(void) const
        {
            // iterate over the halfedges incident on this vertex
            HalfEdgeIter h = _halfedge;
            do
            {
                // check if the current halfedge is on the boundary
                if (h->isBoundary())
                {
                    return true;
                }

                // move to the next halfedge around the vertex
                h = h->twin()->next();
            } while (h != _halfedge); // done iterating over halfedges

            return false;
        }

        /**
        * returns the number of edges (or equivalently, polygons) touching this vertex
        */
        Size degree(void) const
        {
            Size d = 0; // degree

                        // iterate over halfedges incident on this vertex
            HalfEdgeIter h = _halfedge;
            do
            {
                // don't count boundary loops
                if (!h->face()->isBoundary())
                {
                    d++; // increment degree
                }

                // move to the next halfedge around the vertex
                h = h->twin()->next();
            } while (h != _halfedge); // done iterating over halfedges

            return d;
        }

        Matrix4D quadric;

    protected:
        HalfEdgeIter _halfedge; ///< one of the halfedges "rooted" or "based" at this vertex
    
    };  // End of Vertex Class

    /**
    * A Edge encodes one of the mesh vertices
    */
    class Edge : public HalfEdgeElement {
    public:

        /**
        * returns one of the two halfedges of this vertex (reference)
        */
        HalfEdgeIter&  halfedge(void) { return _halfedge; }

        /**
        * returns one of the two halfedges of this vertex
        */
        HalfEdgeCIter  halfedge(void) const { return _halfedge; }

        bool isBoundary(void) const;

        double length(void) const
        {
            Vector3F p0 = halfedge()->vertex()->position;
            Vector3F p1 = halfedge()->twin()->vertex()->position;

            return (p1 - p0).length();
        }

        Vector3F newPosition; ///< For Loop subdivision, this will be the position for the edge midpoint
        bool isNew; ///< For Loop subdivision, this flag should be true if and only if this edge is a new edge created by subdivision (i.e., if it cuts across a triangle in the original mesh)

        EdgeRecord record;

    protected:
        HalfEdgeIter _halfedge; ///< one of the two halfedges associated with this edge
    }; // End of Edge Class

    class HalfEdgeMesh
    {
    public:

        /**
        * Constructor.
        */
        HalfEdgeMesh(void) {}

        /**
        * The assignment operator does a "deep" copy of the halfedge mesh data structure; in
        * other words, it makes new instances of each mesh element, and ensures that pointers
        * in the copy point to the newly allocated elements rather than elements in the original
        * mesh.  This behavior is especially important for making assignments, since the mesh
        * on the right-hand side of an assignment may be temporary (hence any pointers to elements
        * in this mesh will become invalid as soon as it is released.)
        */
        const HalfEdgeMesh& operator=(const HalfEdgeMesh& mesh);

        /**
        * The copy constructor likewise does a "deep" copy of the mesh (via the assignment operator).
        */
        HalfEdgeMesh(const HalfEdgeMesh& mesh);

        /**
        * This method initializes the halfedge data structure from a raw list of polygons,
        * where each input polygon is specified as a list of (0-based) vertex indices.
        * The input must describe a manifold, oriented surface, where the orientation of
        * a polygon is determined by the order of vertices in the list.
        */
        void build(const vector< vector<Index> >& polygons, 
            const vector<Vector3F>& vertexPositions,
            const vector<Vector3F>& vertexColors,
            const vector<Vector3F>& vertexNormals,
            const vector<Vector2D>& vertexTextCoord);

        void GetIndexArray(vector<uint32_t>& indices);

        // These methods return the total number of elements of each type.
        Size nHalfEdges(void)   const { return  halfedges.size(); } ///< get the number of halfedges
        Size nVertices(void)    const { return   vertices.size(); } ///< get the number of vertices
        Size nEdges(void)       const { return      edges.size(); } ///< get the number of edges
        Size nFaces(void)       const { return      faces.size(); } ///< get the number of faces
        Size nBoundaries(void)  const { return boundaries.size(); } ///< get the number of boundaries


        /*
        * These methods return iterators to the beginning and end of the lists of
        * each type of mesh element.  For instance, to iterate over all vertices
        * one can write
        *
        *    for( VertexIter v = mesh.verticesBegin(); v != mesh.verticesEnd(); v++ )
        *    {
        *       // do something interesting with v
        *    }
        *
        * Note that we have both const and non-const versions of these functions; when
        * a mesh is passed as a constant reference, we would instead write
        *
        *    for( VertexCIter v = ... )
        *
        * rather than VertexIter.
        */
        HalfEdgeIter halfedgesBegin(void)   { return  halfedges.begin(); } HalfEdgeCIter halfedgesBegin(void)   const { return  halfedges.begin();  }
        HalfEdgeIter halfedgesEnd(void)     { return  halfedges.end();   } HalfEdgeCIter halfedgesEnd(void)     const { return  halfedges.end();    }
        VertexIter   verticesBegin(void)    { return   vertices.begin(); } VertexCIter   verticesBegin(void)    const { return   vertices.begin();  }
        VertexIter   verticesEnd(void)      { return   vertices.end();   } VertexCIter   verticesEnd(void)      const { return   vertices.end();    }
        EdgeIter     edgesBegin(void)       { return      edges.begin(); } EdgeCIter     edgesBegin(void)       const { return      edges.begin();  }
        EdgeIter     edgesEnd(void)         { return      edges.end();   } EdgeCIter     edgesEnd(void)         const { return      edges.end();    }
        FaceIter     facesBegin(void)       { return      faces.begin(); } FaceCIter     facesBegin(void)       const { return      faces.begin();  }
        FaceIter     facesEnd(void)         { return      faces.end();   } FaceCIter     facesEnd(void)         const { return      faces.end();    }
        FaceIter     boundariesBegin(void)  { return boundaries.begin(); } FaceCIter     boundariesBegin(void)  const { return boundaries.begin();  }
        FaceIter     boundariesEnd(void)    { return boundaries.end();   } FaceCIter     boundariesEnd(void)    const { return boundaries.end();    }

        /*
        * These methods allocate new mesh elements, returning a pointer (i.e., iterator) to the new element.
        * (These methods cannot have const versions, because they modify the mesh!)
        */
        HalfEdgeIter newHalfEdge(void)  { return  halfedges.insert(halfedges.end(), HalfEdge()); }
        VertexIter   newVertex(void)    { return   vertices.insert(vertices.end(),  Vertex()); }
        EdgeIter     newEdge(void)      { return      edges.insert(edges.end(),     Edge()); }
        FaceIter     newFace(void)      { return      faces.insert(faces.end(),     Face(false)); }
        FaceIter     newBoundary(void)  { return boundaries.insert(boundaries.end(), Face(true)); }

        /*
        * These methods delete a specified mesh element.  One should think very, very carefully about
        * exactly when and how to delete mesh elements, since other elements will often still point
        * to the element that is being deleted, and accessing a deleted element will cause your
        * program to crash (or worse!).  A good exercise to think about is: suppose you're iterating
        * over a linked list, and want to delete some of the elements as you go.  How do you do this
        * without causing any problems?  For instance, if you delete the current element, will you be
        * able to iterate to the next element?  Etc.
        */
        void deleteHalfEdge(HalfEdgeIter h) { halfedges.erase(h); }
        void deleteVertex(VertexIter v)     { vertices.erase(v); }
        void deleteEdge(EdgeIter e)         { edges.erase(e); }
        void deleteFace(FaceIter f)         { faces.erase(f); }
        void deleteBoundary(FaceIter b)     { boundaries.erase(b); }

        /* For a triangle mesh, you will implement the following
        * basic edge operations.  (Can you generalize to other
        * polygonal meshes?)
        */
        EdgeIter        flipEdge(EdgeIter e); ///< flip an edge, returning a pointer to the flipped edge
        VertexIter      splitEdge(EdgeIter e); ///< split an edge, returning a pointer to the inserted midpoint vertex; the halfedge of this vertex should refer to one of the edges in the original mesh


        void check_for(HalfEdgeIter h) {
            for (HalfEdgeIter he = halfedgesBegin(); he != halfedgesEnd(); he++) {
                if (he == h)
                    cout << "HalfEdge " << elementAddress(h) << " found in list" << endl;
                if (he->twin() == h)
                    cout << "HalfEdge " << elementAddress(h) << " is twin of "
                    << elementAddress(he) << endl;
                if (he->next() == h)
                    cout << "HalfEdge " << elementAddress(h) << " is next of "
                    << elementAddress(he) << endl;
            }
            for (VertexIter v = verticesBegin(); v != verticesEnd(); v++) {

                if (v->halfedge() == h)
                    cout << "HalfEdge " << elementAddress(h) << " is h.e. of "
                    << elementAddress(v) << endl;
            }
            for (EdgeIter e = edgesBegin(); e != edgesEnd(); e++) {
                if (e->halfedge() == h)
                    cout << "HalfEdge " << elementAddress(h) << " is h.e. of "
                    << elementAddress(e) << endl;
            }
            for (FaceIter f = facesBegin(); f != facesEnd(); f++) {
                if (f->halfedge() == h)
                    cout << "HalfEdge " << elementAddress(h) << " is h.e. of "
                    << elementAddress(f) << endl;
            }

        }
        void check_for(VertexIter v) {
            for (HalfEdgeIter he = halfedgesBegin(); he != halfedgesEnd(); he++) {
                if (he->vertex() == v)
                    cout << "Vertex " << elementAddress(v) << " found in h.e. "
                    << elementAddress(he) << endl;
            }
        }
        void check_for(EdgeIter e) {
            for (HalfEdgeIter he = halfedgesBegin(); he != halfedgesEnd(); he++) {
                if (he->edge() == e)
                    cout << "Edge " << elementAddress(e) << " found in h.e. "
                    << elementAddress(he) << endl;
            }
        }
        void check_for(FaceIter f) {
            for (HalfEdgeIter he = halfedgesBegin(); he != halfedgesEnd(); he++) {
                if (he->face() == f)
                    cout << "Face " << elementAddress(f) << " found in h.e. "
                    << elementAddress(he) << endl;
            }
        }
    
    protected:

        /**
        * Here's where the mesh elements are actually stored---this is the one
        * and only place we have actual data (rather than pointers/iterators).
        */
        list<HalfEdge> halfedges;
        list<Vertex> vertices;
        list<Edge> edges;
        list<Face> faces;
        list<Face> boundaries;

    }; // class HalfEdgeMesh

    inline HalfEdge* HalfEdgeElement::getHalfEdge(void) { return dynamic_cast<HalfEdge*>(this); }
    inline Vertex*   HalfEdgeElement::getVertex(void) { return dynamic_cast  <Vertex*>(this); }
    inline Edge*     HalfEdgeElement::getEdge(void) { return dynamic_cast    <Edge*>(this); }
    inline Face*     HalfEdgeElement::getFace(void) { return dynamic_cast    <Face*>(this); }

}   // End of CG184


#endif //CGENGINE_HALFEDGEELEMENT_H