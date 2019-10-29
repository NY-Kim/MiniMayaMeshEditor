#ifndef DISPLAY_H
#define DISPLAY_H

#import <halfedge.h>
#import <drawable.h>

class HalfEdgeDisplay : public Drawable {
public:
    HalfEdge *representedHalfEdge;

    HalfEdgeDisplay(OpenGLContext *context);
    ~HalfEdgeDisplay();
    void create() override;
    void updateHalfEdge(HalfEdge *halfEdge);
    GLenum drawMode() override;
};

class FaceDisplay : public Drawable {
public:
    Face *representedFace;

    FaceDisplay(OpenGLContext *context);
    ~FaceDisplay();
    void create() override;
    void updateFace(Face *face);
    GLenum drawMode() override;
};

class VertexDisplay : public Drawable {
public:
    Vertex *representedVertex;

    VertexDisplay(OpenGLContext *context);
    ~VertexDisplay();
    void create() override;
    void updateVertex(Vertex *vertex);
    GLenum drawMode() override;
};

#endif
