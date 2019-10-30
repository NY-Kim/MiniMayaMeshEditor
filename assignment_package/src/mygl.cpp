#include "mygl.h"
#include <la.h>
#include <smartpointerhelp.h>
#include <limits>

#include <iostream>
#include <QApplication>
#include <QKeyEvent>
#include <set>
#include <random>


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
    //Send the geometry's transformation matrix to the shader
    m_progFlat.setModelMatrix(glm::mat4(1.0f));
    m_progLambert.setModelMatrix(glm::mat4(1.0f));

    m_progFlat.draw(m_mesh);
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
//        m_glCamera.RotateAboutUp(-amount);
        m_glCamera.rotatePhi(-amount);
    } else if (e->key() == Qt::Key_Left) {
//        m_glCamera.RotateAboutUp(amount);
        m_glCamera.rotatePhi(amount);
    } else if (e->key() == Qt::Key_Up) {
//        m_glCamera.RotateAboutRight(-amount);
        m_glCamera.rotateTheta(amount);
    } else if (e->key() == Qt::Key_Down) {
//        m_glCamera.RotateAboutRight(amount);
        m_glCamera.rotateTheta(-amount);
    } else if (e->key() == Qt::Key_1) {
        m_glCamera.fovy += amount;
    } else if (e->key() == Qt::Key_2) {
        m_glCamera.fovy -= amount;
    }  else if (e->key() == Qt::Key_3) {
        m_glCamera.translateZoom(amount);
    } else if (e->key() == Qt::Key_4) {
        m_glCamera.translateZoom(-amount);
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
    uPtr<Vertex> v = mkU<Vertex>((he1->vertex->pos + he1->sym->vertex->pos) / 2.0f);

    Vertex* v3 = v.get();
    m_mesh.vertices.push_back(std::move(v));
    splitByPoint(he1, v3);
}

void MyGL::splitByPoint(HalfEdge* he1, Vertex* v3) {
        HalfEdge* he2 = he1->sym;
        Vertex* v1 = he1->vertex;
        Vertex* v2 = he2->vertex;

        uPtr<HalfEdge> he1b = mkU<HalfEdge>();
        uPtr<HalfEdge> he2b = mkU<HalfEdge>();

        v3->half_edge = he1;
        v1->half_edge = he1b.get();
        v2->half_edge = he2b.get();
        he1b->face = he1->face;
        he2b->face = he2->face;
        he1b->next = he1->next;
        he2b->next = he2->next;
        he1->next = he1b.get();
        he2->next = he2b.get();
        he1b->vertex = v1;
        he2b->vertex = v2;
        he1->vertex = v3;
        he2->vertex = v3;
        he1->sym = he2b.get();
        he2b->sym = he1;
        he2->sym = he1b.get();
        he1b->sym = he2;

        if (he1->sharp) {
            he1b->sharp = true;
            he2b->sharp = true;
        }

        m_mesh.half_edges.push_back(std::move(he1b));
        m_mesh.half_edges.push_back(std::move(he2b));
}


int MyGL::getNumEdge(Face* face) {
    int num_edge = 0;
    HalfEdge* half_edge = face->half_edge;
    do {
        num_edge++;
        half_edge = half_edge->next;
    } while (half_edge != face->half_edge);
    return num_edge;
}

void MyGL::triangulate(Face* face) {
    int num_edge = getNumEdge(face);
    while (num_edge > 3) {
        triangulateQuadrangle(face);
        num_edge--;
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
    if (getNumEdge(face) == 3) {
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
    for (unsigned int i = 0; i < m_mesh.faces.size(); i++) {
        Face* face = m_mesh.faces[i].get();
        if (!isPlanar(face)) {
            triangulate(face);
        }
    }
}

void MyGL::subdivide() {
    std::vector<Vertex*> vertices;
    for (unsigned int i = 0; i < m_mesh.vertices.size(); i++) {
        vertices.push_back(m_mesh.vertices[i].get());
    }

    // compute centroids
    std::vector<Vertex*> centroids;
    for (unsigned int i = 0; i < m_mesh.faces.size(); i++) {
        Face* face = m_mesh.faces[i].get();

        HalfEdge* half_edge = face->half_edge;
        int num_edge = 0;
        glm::vec3 sum_position = glm::vec3(0);
        do {
            num_edge++;
            sum_position += half_edge->vertex->pos;
            half_edge = half_edge->next;
        } while (half_edge != face->half_edge);

        uPtr<Vertex> centroid = mkU<Vertex>(sum_position / float(num_edge));
        centroids.push_back(centroid.get());
        m_mesh.vertices.push_back(std::move(centroid));
    }

    std::set<Vertex*> sharp_vert; // stores vertices treated as sharp in sharp face
    std::set<HalfEdge*> sharp_he; // stores half-edges treated as sharp in sharp face
    for (unsigned int i = 0; i < m_mesh.faces.size(); i++) {
        Face* face = m_mesh.faces[i].get();
        if (face->sharp) {
            HalfEdge* half_edge = face->half_edge;
            do {
                sharp_he.insert(half_edge);
                sharp_he.insert(half_edge->sym);
                sharp_vert.insert(half_edge->vertex);
                half_edge = half_edge->next;
            } while (half_edge != face->half_edge);
        }
    }

    // compute smoothed midpoint
    std::set<HalfEdge*> computed;
    unsigned int num_half_edges = m_mesh.half_edges.size();
    for (unsigned int i = 0; i < num_half_edges; i++) {
        HalfEdge* half_edge = m_mesh.half_edges[i].get();
        if (computed.find(half_edge->next->sym) != computed.end()) {
            computed.insert(half_edge);
            continue;
        }

        glm::vec3 mid_pos;
        if ((sharp_he.find(half_edge) != sharp_he.end()) || half_edge->sharp) {
            Vertex* v1 = half_edge->vertex;
            Vertex* v2 = half_edge->sym->vertex;

            mid_pos = (v1->pos + v2->pos) * 0.5f;
        } else {
            Vertex* v1 = half_edge->vertex;
            Vertex* v2 = half_edge->sym->vertex;
            Vertex* f1 = centroids[half_edge->face->id];
            Vertex* f2 = centroids[half_edge->sym->face->id];

            mid_pos = (v1->pos + v2->pos + f1->pos + f2->pos) / 4.0f;
        }

        uPtr<Vertex> midpoint = mkU<Vertex>(mid_pos);
        Vertex* mp = midpoint.get();
        m_mesh.vertices.push_back(std::move(midpoint));
        splitByPoint(half_edge, mp);

        computed.insert(half_edge);
    }

    // smooth original vertices
    for (Vertex* vertex : vertices) {
        if ((sharp_vert.find(vertex) != sharp_vert.end()) || vertex->sharp) {
            continue;
        }

        std::vector<HalfEdge*> sharp_edge;
        int n = 0;
        glm::vec3 v = vertex->pos;
        glm::vec3 f = glm::vec3(0);
        glm::vec3 e = glm::vec3(0);
        HalfEdge* half_edge = vertex->half_edge;
        do {
            if (half_edge->sharp) {
                sharp_edge.push_back(half_edge);
            }
            n++;
            f += centroids[half_edge->face->id]->pos;
            e += half_edge->sym->vertex->pos;
            half_edge = half_edge->next->sym;
        } while(half_edge != vertex->half_edge);

        if (sharp_edge.size() < 2) {
            vertex->pos = (n - 2.0f) * v / float(n) + e / float(n * n) + f / float(n * n);
        } else if (sharp_edge.size() == 2) {
            glm::vec3 v1 = sharp_edge[0]->sym->vertex->pos;
            glm::vec3 v2 = sharp_edge[1]->sym->vertex->pos;
            vertex->pos = 0.75f * v + 0.125f * v1 + 0.125f * v2;
        }
    }

    // quadrangulate face
    unsigned int num_faces = m_mesh.faces.size();
    for (unsigned int i = 0; i < num_faces; i++) {

        Face* face = m_mesh.faces[i].get();
        Vertex* start_vertex = face->half_edge->vertex;
        face->half_edge = face->half_edge->next;
        HalfEdge* half_edge = face->half_edge;
        Vertex* centroid = centroids[face->id];

        HalfEdge* next;
        HalfEdge* first_sym = nullptr;
        HalfEdge* last_sym = nullptr;

        do {
            uPtr<Face> new_face = mkU<Face>();
            new_face->color = face->color - face->color * float(rand() % 2) * 0.2f;
            new_face->color -= glm::vec3(0.2f, 0.2f, 0.2f);
            uPtr<HalfEdge> to_centroid = mkU<HalfEdge>();
            uPtr<HalfEdge> from_centroid = mkU<HalfEdge>();

            Vertex* next_start_vertex;

            new_face->half_edge = half_edge;

            next = half_edge->next->next;
            next_start_vertex = half_edge->next->vertex;

            half_edge->face = new_face.get();
            half_edge->next->face = new_face.get();
            half_edge->next->next = to_centroid.get();

            to_centroid->face = new_face.get();
            to_centroid->next = from_centroid.get();
            to_centroid->vertex = centroid;

            from_centroid->face = new_face.get();
            from_centroid->next = half_edge;
            from_centroid->vertex = start_vertex;
            if (first_sym == nullptr) {
                first_sym = from_centroid.get();
            }
            if (last_sym != nullptr) {
                from_centroid->sym = last_sym;
                last_sym->sym = from_centroid.get();
            }

            last_sym = to_centroid.get();;
            start_vertex = next_start_vertex;
            half_edge = next;

            if (face->sharp) {
                new_face->sharp = true;
                new_face->color = face->color;
                HalfEdge* half_edge = new_face->half_edge;
                do {
                    sharp_he.insert(half_edge);
                    sharp_he.insert(half_edge->sym);
                    sharp_vert.insert(half_edge->vertex);
                    half_edge = half_edge->next;
                } while (half_edge != new_face->half_edge);
            }

            m_mesh.faces.push_back(std::move(new_face));
            m_mesh.half_edges.push_back(std::move(to_centroid));
            m_mesh.half_edges.push_back(std::move(from_centroid));
        } while(half_edge->next->next != face->half_edge);

        uPtr<HalfEdge> to_centroid = mkU<HalfEdge>();
        uPtr<HalfEdge> from_centroid = mkU<HalfEdge>();

        face->half_edge = half_edge;
        half_edge->face = face;
        half_edge->next->face = face;
        half_edge->next->next = to_centroid.get();

        to_centroid->face = face;
        to_centroid->next = from_centroid.get();
        to_centroid->vertex = centroid;
        to_centroid->sym = first_sym;
        first_sym->sym = to_centroid.get();

        from_centroid->face = face;
        from_centroid->next = half_edge;
        from_centroid->vertex = start_vertex;
        from_centroid->sym = last_sym;
        last_sym->sym = from_centroid.get();

        centroid->half_edge = to_centroid.get();

        m_mesh.half_edges.push_back(std::move(to_centroid));
        m_mesh.half_edges.push_back(std::move(from_centroid));
    }
}

void MyGL::extrudeFace() {
    Face* face = m_faceDisplay.representedFace;
    HalfEdge* half_edge = face->half_edge;
    glm::vec3 normal;
    do {
        glm::vec3 curr_pos = half_edge->vertex->pos;
        glm::vec3 prev_pos = half_edge->sym->vertex->pos;
        glm::vec3 next_pos = half_edge->next->vertex->pos;

        normal = glm::cross(prev_pos - curr_pos, next_pos - curr_pos);

        if (std::abs(normal[0]) > DBL_EPSILON ||
            std::abs(normal[1]) > DBL_EPSILON ||
            std::abs(normal[2]) > DBL_EPSILON) {
            break;
        }

        half_edge = half_edge->next;
    } while (half_edge != face->half_edge);

    half_edge = face->half_edge;
    glm::vec3 displacement = 0.75f * glm::normalize(normal);

    uPtr<Vertex> vertex1 = mkU<Vertex>(half_edge->sym->vertex->pos + displacement);
    Vertex* vertex = vertex1.get();
    m_mesh.vertices.push_back(std::move(vertex1));
    Vertex* last_vert = vertex;
    HalfEdge* last_sym = nullptr;
    HalfEdge* first_sym = nullptr;

    do {
        uPtr<Face> new_face = mkU<Face>(face->color * 0.8f);
        new_face->color -= glm::vec3(0.1, 0.1, 0.1);
        uPtr<HalfEdge> he1 = mkU<HalfEdge>();
        uPtr<HalfEdge> he2 = mkU<HalfEdge>();
        uPtr<HalfEdge> he3 = mkU<HalfEdge>();
        uPtr<HalfEdge> he4 = mkU<HalfEdge>();
        uPtr<Vertex> new_vertex = mkU<Vertex>(half_edge->vertex->pos + displacement);

        new_face->half_edge = he1.get();
        he1->face = new_face.get();
        he2->face = new_face.get();
        he3->face = new_face.get();
        he4->face = new_face.get();

        he1->next = he2.get();
        he2->next = he3.get();
        he3->next = he4.get();
        he4->next = he1.get();

        he1->vertex = new_vertex.get();
        he2->vertex = last_vert;
        he3->vertex = half_edge->sym->vertex;
        he4->vertex = half_edge->vertex;

        if (first_sym == nullptr) {
            first_sym = he3.get();
        }
        if (last_sym != nullptr) {
            he3->sym = last_sym;
            last_sym->sym = he3.get();
        }
        last_sym = he1.get();

        he4->sym = half_edge->sym;
        half_edge->sym->sym = he4.get();
        he2->sym = half_edge;
        half_edge->sym = he2.get();

        half_edge->vertex = new_vertex.get();
        new_vertex->half_edge = half_edge;

        half_edge = half_edge->next;
        last_vert = new_vertex.get();

        m_mesh.faces.push_back(std::move(new_face));
        m_mesh.half_edges.push_back(std::move(he1));
        m_mesh.half_edges.push_back(std::move(he2));
        m_mesh.half_edges.push_back(std::move(he3));
        m_mesh.half_edges.push_back(std::move(he4));
        m_mesh.vertices.push_back(std::move(new_vertex));
    } while (half_edge->next != face->half_edge);

    uPtr<Face> new_face = mkU<Face>(face->color - glm::vec3(0.05, 0.05, 0.05));
    uPtr<HalfEdge> he1 = mkU<HalfEdge>();
    uPtr<HalfEdge> he2 = mkU<HalfEdge>();
    uPtr<HalfEdge> he3 = mkU<HalfEdge>();
    uPtr<HalfEdge> he4 = mkU<HalfEdge>();

    new_face->half_edge = he1.get();
    he1->face = new_face.get();
    he2->face = new_face.get();
    he3->face = new_face.get();
    he4->face = new_face.get();

    he1->next = he2.get();
    he2->next = he3.get();
    he3->next = he4.get();
    he4->next = he1.get();

    he1->vertex = vertex;
    he2->vertex = last_vert;
    he3->vertex = half_edge->sym->vertex;
    he4->vertex = half_edge->vertex;

    he3->sym = last_sym;
    last_sym->sym = he3.get();
    first_sym->sym = he1.get();
    he1->sym = first_sym;

    he4->sym = half_edge->sym;
    half_edge->sym->sym = he4.get();
    he2->sym = half_edge;
    half_edge->sym = he2.get();

    half_edge->vertex = vertex;
    vertex->half_edge = half_edge;

    m_mesh.faces.push_back(std::move(new_face));
    m_mesh.half_edges.push_back(std::move(he1));
    m_mesh.half_edges.push_back(std::move(he2));
    m_mesh.half_edges.push_back(std::move(he3));
    m_mesh.half_edges.push_back(std::move(he4));
}

void MyGL::loadObj(QString filename) {
    std::vector<uPtr<Vertex>> vertices;
    std::vector<uPtr<HalfEdge>> half_edges;
    std::vector<uPtr<Face>> faces;
    std::map<std::pair<int, int>, int> sym_map;

    QFile file(filename);
    if (file.open(QIODevice::ReadOnly)) {
        Vertex::id_count = 0;
        HalfEdge::id_count = 0;
        Face::id_count = 0;

        QTextStream in(&file);

        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList tok_list = line.split(" ");

            if (tok_list[0] == "v"){
                uPtr<Vertex> vertex = mkU<Vertex>(glm::vec3(tok_list[1].toDouble(),
                                                            tok_list[2].toDouble(),
                                                            tok_list[3].toDouble()));
                vertices.push_back(std::move(vertex));
            } else if (tok_list[0] == "f"){
                float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                uPtr<Face> face = mkU<Face>(glm::vec3(r, g, b));

                HalfEdge* first_edge = nullptr;
                HalfEdge* last_edge = nullptr;

                int first_idx = -1;
                int last_idx = -1;
                for (int i = 1; i < tok_list.size(); i++) {
                    int index = tok_list[i].split("/")[0].toInt() - 1;

                    uPtr<HalfEdge> half_edge = mkU<HalfEdge>();
                    vertices[index]->half_edge = half_edge.get();
                    if (first_edge == nullptr) {
                        first_edge = half_edge.get();
                    }
                    if (last_edge != nullptr) {
                        last_edge->next = half_edge.get();

                        if (sym_map.find(std::pair<int, int>(index, last_idx)) != sym_map.end()) {
                            int sym_idx = sym_map[std::pair<int, int>(index, last_idx)];
                            half_edge->sym = half_edges[sym_idx].get();
                            half_edges[sym_idx]->sym = half_edge.get();
                        } else {
                            sym_map[std::pair<int, int>(last_idx, index)] =  half_edge->id;
                        }
                    }

                    last_edge = half_edge.get();
                    half_edge->vertex = vertices[index].get();
                    half_edge->face = face.get();

                    if (first_idx == -1) {
                        first_idx = index;
                    }

                    last_idx = index;
                    half_edges.push_back(std::move(half_edge));
                }
                last_edge->next = first_edge;
                face->half_edge = first_edge;

                if (sym_map.find(std::pair<int, int>(first_idx, last_idx)) != sym_map.end()) {
                    int sym_idx = sym_map[std::pair<int, int>(first_idx, last_idx)];
                    first_edge->sym = half_edges[sym_idx].get();
                    half_edges[sym_idx]->sym = first_edge;
                } else {
                    sym_map[std::pair<int, int>(last_idx, first_idx)] =  first_edge->id;
                }
                faces.push_back(std::move(face));
            }
        }
        file.close();

        m_mesh.vertices = std::move(vertices);
        m_mesh.half_edges = std::move(half_edges);
        m_mesh.faces = std::move(faces);
    }
}
