#ifndef PRIMITIVES_H
#define PRIMITIVES_H
#include <la.h>
#include <QListWidget>

class HalfEdge;

class Vertex : public QListWidgetItem
{
public:
    glm::vec3 pos;
    HalfEdge* half_edge;
    int id;
    static int id_count;
    bool sharp;

    Vertex();
    ~Vertex();
    Vertex(glm::vec3 pos);
};

class Face : public QListWidgetItem
{
public:
    HalfEdge* half_edge;
    glm::vec3 color;
    int id;
    static int id_count;
    bool sharp;

    Face();
    ~Face();
    Face(glm::vec3 color);
};

class HalfEdge : public QListWidgetItem
{
public:
    HalfEdge* next;
    HalfEdge* sym; 
    Face* face;
    Vertex* vertex;
    int id;
    static int id_count;
    bool sharp;

    HalfEdge();
    ~HalfEdge();
    HalfEdge(Face* face);
};
#endif
