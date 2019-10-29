#ifndef MYGL_H
#define MYGL_H

#include <openglcontext.h>
#include <utils.h>
#include <shaderprogram.h>
#include <scene/squareplane.h>
#include <scene/pentagon.h>
#include "camera.h"
#include <display.h>
#include <mesh.h>

#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>


class MyGL
    : public OpenGLContext
{
    Q_OBJECT
private:
    SquarePlane m_geomSquare;// The instance of a unit cylinder we can use to render any cylinder
    ShaderProgram m_progLambert;// A shader program that uses lambertian reflection
    ShaderProgram m_progFlat;// A shader program that uses "flat" reflection (no shadowing at all)

    GLuint vao; // A handle for our vertex array object. This will store the VBOs created in our geometry classes.
                // Don't worry too much about this. Just know it is necessary in order to render geometry.

    Camera m_glCamera;


public:

    // Have an instance of VertexDisplay that is
    // drawn in paintGL, and has VBO data representing
    // the position of the currently selected Vertex so
    // it can be drawn as a GL_POINTS
    VertexDisplay m_vertDisplay;
    HalfEdgeDisplay m_halfEdgeDisplay;
    FaceDisplay m_faceDisplay;

    Mesh m_mesh;

    explicit MyGL(QWidget *parent = nullptr);
    ~MyGL();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void reset(); // reset highlighted components and redraw mesh
    void recreate(); // redraw components

    void splitHalfEdge(); // split half edge to add vertex
    void triangulate(Face* face); // triangulate face
    int getNumEdge(Face* face);
    void triangulateQuadrangle(Face* face1);

    void planarOperation(); // make all faces planar by triangulating
    bool isPlanar(Face* face);
    glm::vec3 getNormal(HalfEdge* half_edge);

    void subdivide(); // subdivide mesh into quadrangles
    void splitByPoint(HalfEdge* he1, Vertex* v3);

    void extrudeFace(); // extrude selected face
    void loadObj(QString filename); // load obj file

protected:
    void keyPressEvent(QKeyEvent *e);

signals:
    void sendMesh(Mesh*);
    void sendSelectedHE(QListWidgetItem*);
    void sendSelectedVertex(QListWidgetItem*);
    void sendSelectedFace(QListWidgetItem*);
};


#endif // MYGL_H
