#ifndef PRIMITIVES_H
#define PRIMITIVES_H
#include <la.h>
#include <QListWidget>
#include <joint.h>

class HalfEdge;

class Vertex : public QListWidgetItem
{
public:
    int id;
    glm::vec3 pos;
    HalfEdge* half_edge;
    static int id_count;
    bool sharp;
    std::vector<std::pair<int, float>> joint_inf;

    Vertex();
    ~Vertex();
    Vertex(glm::vec3 pos);
};

class Face : public QListWidgetItem
{
public:
    int id;
    glm::vec3 color;
    HalfEdge* half_edge;
    static int id_count;
    bool sharp;

    Face();
    ~Face();
    Face(glm::vec3 color);
};

class HalfEdge : public QListWidgetItem
{
public:
    int id;
    HalfEdge* next;
    HalfEdge* sym; 
    Face* face;
    Vertex* vertex;
    static int id_count;
    bool sharp;

    HalfEdge();
    ~HalfEdge();
    HalfEdge(Face* face);
};
#endif
