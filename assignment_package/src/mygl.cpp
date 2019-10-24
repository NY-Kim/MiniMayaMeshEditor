#include "mygl.h"
#include <la.h>
#include <smartpointerhelp.h>
#include <limits>

#include <iostream>
#include <QApplication>
#include <QKeyEvent>



MyGL::MyGL(QWidget *parent)
    : OpenGLContext(parent),
      m_geomSquare(this),
      m_progLambert(this), m_progFlat(this),
      m_glCamera(),
      m_mesh(this),
      m_vertDisplay(this), m_faceDisplay(this), m_halfEdgeDisplay(this) {}

MyGL::~MyGL()
{
    makeCurrent();
    glDeleteVertexArrays(1, &vao);
    m_geomSquare.destroy();
    m_mesh.destroy();
}

void MyGL::initializeGL()
{
    // Create an OpenGL context using Qt's QOpenGLFunctions_3_2_Core class
    // If you were programming in a non-Qt context you might use GLEW (GL Extension Wrangler)instead
    initializeOpenGLFunctions();
    // Print out some information about the current OpenGL context
    debugContextVersion();

    // Set a few settings/modes in OpenGL rendering
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    // Set the size with which points should be rendered
    glPointSize(5);
    // Set the color with which the screen is filled at the start of each render call.
    glClearColor(0.5, 0.5, 0.5, 1);

    printGLErrorLog();

    // Create a Vertex Attribute Object
    glGenVertexArrays(1, &vao);

    //Create the instances of Cylinder and Sphere.
    m_geomSquare.create();
    m_mesh.createCubeMesh();
    m_mesh.create();

    // Create and set up the diffuse shader
    m_progLambert.create(":/glsl/lambert.vert.glsl", ":/glsl/lambert.frag.glsl");
    // Create and set up the flat lighting shader
    m_progFlat.create(":/glsl/flat.vert.glsl", ":/glsl/flat.frag.glsl");


    // We have to have a VAO bound in OpenGL 3.2 Core. But if we're not
    // using multiple VAOs, we can just bind one once.
    glBindVertexArray(vao);

    emit sendMesh(&m_mesh);
}

void MyGL::resizeGL(int w, int h)
{
    //This code sets the concatenated view and perspective projection matrices used for
    //our scene's camera view.
    m_glCamera = Camera(w, h);
    glm::mat4 viewproj = m_glCamera.getViewProj();

    // Upload the view-projection matrix to our shaders (i.e. onto the graphics card)

    m_progLambert.setViewProjMatrix(viewproj);
    m_progFlat.setViewProjMatrix(viewproj);

    printGLErrorLog();
}

//This function is called by Qt any time your GL window is supposed to update
//For example, when the function update() is called, paintGL is called implicitly.
void MyGL::paintGL()
{
    // Clear the screen so that we only see newly drawn images
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_progFlat.setViewProjMatrix(m_glCamera.getViewProj());
    m_progLambert.setViewProjMatrix(m_glCamera.getViewProj());
    m_progLambert.setCamPos(m_glCamera.eye);

//#define NOPE
#ifndef NOPE
    //Create a model matrix. This one scales the sphere uniformly by 3, then translates it by <-2,0,0>.
    //Note that we have to transpose the model matrix before passing it to the shader
    //This is because OpenGL expects column-major matrices, but you've
    //implemented row-major matrices.
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(-2,0,0)) * glm::rotate(glm::mat4(), 0.25f * 3.14159f, glm::vec3(0,1,0));
    //Send the geometry's transformation matrix to the shader
    m_progFlat.setModelMatrix(model);
    m_progLambert.setModelMatrix(model);

    m_progLambert.draw(m_mesh);
    glDisable(GL_DEPTH_TEST);
    m_progFlat.draw(m_vertDisplay);
    m_progFlat.draw(m_faceDisplay);
    m_progFlat.draw(m_halfEdgeDisplay);
    glEnable(GL_DEPTH_TEST);
;
#endif

}

void MyGL::keyPressEvent(QKeyEvent *e)
{
    float amount = 2.0f;
    if(e->modifiers() & Qt::ShiftModifier){
        amount = 10.0f;
    }
    // http://doc.qt.io/qt-5/qt.html#Key-enum
    // This could all be much more efficient if a switch
    // statement were used
    if (e->key() == Qt::Key_Escape) {
        QApplication::quit();
    } else if (e->key() == Qt::Key_Right) {
        m_glCamera.RotateAboutUp(-amount);
    } else if (e->key() == Qt::Key_Left) {
        m_glCamera.RotateAboutUp(amount);
    } else if (e->key() == Qt::Key_Up) {
        m_glCamera.RotateAboutRight(-amount);
    } else if (e->key() == Qt::Key_Down) {
        m_glCamera.RotateAboutRight(amount);
    } else if (e->key() == Qt::Key_1) {
        m_glCamera.fovy += amount;
    } else if (e->key() == Qt::Key_2) {
        m_glCamera.fovy -= amount;
    } else if (e->key() == Qt::Key_W) {
        m_glCamera.TranslateAlongLook(amount);
    } else if (e->key() == Qt::Key_S) {
        m_glCamera.TranslateAlongLook(-amount);
    } else if (e->key() == Qt::Key_D) {
        m_glCamera.TranslateAlongRight(amount);
    } else if (e->key() == Qt::Key_A) {
        m_glCamera.TranslateAlongRight(-amount);
    } else if (e->key() == Qt::Key_Q) {
        m_glCamera.TranslateAlongUp(-amount);
    } else if (e->key() == Qt::Key_E) {
        m_glCamera.TranslateAlongUp(amount);
    } else if (e->key() == Qt::Key_R) {
        m_glCamera = Camera(this->width(), this->height());
    } else if (e->key() == Qt::Key_N) {
        if (m_halfEdgeDisplay.representedHalfEdge) {
            emit sendSelectedHE(m_halfEdgeDisplay.representedHalfEdge->next);
        }
    } else if (e->key() == Qt::Key_M) {
        if (m_halfEdgeDisplay.representedHalfEdge) {
            emit sendSelectedHE(m_halfEdgeDisplay.representedHalfEdge->sym);
        }
    } else if (e->key() == Qt::Key_F) {
        if (m_halfEdgeDisplay.representedHalfEdge) {
            emit sendSelectedFace(m_halfEdgeDisplay.representedHalfEdge->face);
        }
    } else if (e->key() == Qt::Key_V) {
        if (m_halfEdgeDisplay.representedHalfEdge) {
            emit sendSelectedVertex(m_halfEdgeDisplay.representedHalfEdge->vertex);
        }
    } else if ((e->modifiers() & Qt::ShiftModifier) && e->key() == Qt::Key_H) {
        if (m_faceDisplay.representedFace) {
            emit sendSelectedHE(m_faceDisplay.representedFace->half_edge);
        }
    } else if (e->key() == Qt::Key_H) {
        if (m_vertDisplay.representedVertex) {
            emit sendSelectedHE(m_vertDisplay.representedVertex->half_edge);
        }
    }
    m_glCamera.RecomputeAttributes();
    update();  // Calls paintGL, among other things
}

void MyGL::reset() {
    m_vertDisplay.representedVertex = nullptr;
    m_halfEdgeDisplay.representedHalfEdge = nullptr;
    m_faceDisplay.representedFace = nullptr;
    this->recreate();
}

void MyGL::recreate() {
    m_vertDisplay.destroy();
    m_faceDisplay.destroy();
    m_halfEdgeDisplay.destroy();
    m_mesh.destroy();
    m_vertDisplay.create();
    m_faceDisplay.create();
    m_halfEdgeDisplay.create();
    m_mesh.create();
}

void MyGL::splitHalfEdge() {
    HalfEdge* he1 = m_halfEdgeDisplay.representedHalfEdge;
    HalfEdge* he2 = he1->sym;
    Vertex* v1 = he1->vertex;
    Vertex* v2 = he2->vertex;

    glm::vec3 v = v1->pos + v2->pos;
    uPtr<Vertex> v3 = mkU<Vertex>(glm::vec3(v[0] / 2, v[1] / 2, v[2] / 2));

    uPtr<HalfEdge> he1b = mkU<HalfEdge>();
    uPtr<HalfEdge> he2b = mkU<HalfEdge>();
    he1b->vertex = v1;
    he2b->vertex = v2;
    he1b->face = he1->face;
    he2b->face = he2->face;

    he1b->next = he1->next;
    he2b->next = he2->next;
    he1->next = he1b.get();
    he2->next = he2b.get();
    he1->vertex = v3.get();
    he2->vertex = v3.get();
    he1->sym = he2b.get();
    he2b->sym = he1;
    he2->sym = he1b.get();
    he1b->sym = he2;

    m_mesh.vertices.push_back(std::move(v3));
    m_mesh.half_edges.push_back(std::move(he1b));
    m_mesh.half_edges.push_back(std::move(he2b));

}

bool MyGL::isTriangle(Face* face) {
    int num_edge = 0;
    HalfEdge* half_edge = face->half_edge;
    do {
        num_edge++;
        half_edge = half_edge->next;
    } while (half_edge != face->half_edge);
    return num_edge <= 3;
}

void MyGL::triangulate(Face* face1) {
    while (!isTriangle(face1)) {
        triangulateQuadrangle(face1);
    }
}

glm::vec3 MyGL::getNormal(HalfEdge* half_edge) {
    glm::vec3 curr_pos = half_edge->vertex->pos;
    glm::vec3 prev_pos = half_edge->sym->vertex->pos;
    glm::vec3 next_pos = half_edge->next->vertex->pos;

    return glm::normalize(glm::cross(prev_pos - curr_pos, next_pos - curr_pos));

}
void MyGL::triangulateQuadrangle(Face *face1) {
    HalfEdge* he0 = face1->half_edge;
    uPtr<HalfEdge> heA = mkU<HalfEdge>();
    uPtr<HalfEdge> heB = mkU<HalfEdge>();
    heA->vertex = he0->vertex;
    heB->vertex = he0->next->next->vertex;
    heA->sym = heB.get();
    heB->sym = heA.get();

    uPtr<Face> face2 = mkU<Face>(face1->color);
    heA->face = face2.get();
    he0->next->face = face2.get();
    he0->next->next->face = face2.get();
    heB->face = face1;
    face2->half_edge = heA.get();
    heB->next = he0->next->next->next;
    he0->next->next->next = heA.get();
    heA->next = he0->next;
    he0->next = heB.get();

    m_mesh.faces.push_back(std::move(face2));
    m_mesh.half_edges.push_back(std::move(heA));
    m_mesh.half_edges.push_back(std::move(heB));
}

bool MyGL::isPlanar(Face *face) {
    if (isTriangle(face)) {
        return true;
    }

    HalfEdge* half_edge = face->half_edge;
    glm::vec3 normal = getNormal(half_edge);

    do {
        glm::vec3 n = getNormal(half_edge);
        if (std::abs(n[0] - normal[0]) > DBL_EPSILON ||
            std::abs(n[1] - normal[1]) > DBL_EPSILON ||
            std::abs(n[2] - normal[2]) > DBL_EPSILON) {
            return false;
        }
        half_edge = half_edge->next;
    } while (half_edge != face->half_edge);
    return true;
}

void MyGL::planarOperation() {
    for (int i = 0; i < m_mesh.faces.size(); i++) {
        Face* face = m_mesh.faces[i].get();
        if (!isPlanar(face)) {
            triangulate(face);
        }
    }
}
