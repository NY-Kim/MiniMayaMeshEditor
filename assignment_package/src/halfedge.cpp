#include <halfedge.h>

int Vertex::id_count = 0;

Vertex::Vertex() : id(id_count), pos(glm::vec3(0, 0, 0)), half_edge(nullptr), sharp(false)
{
    this->setText(QString::number(id_count));
    this->id_count++;
}

Vertex::~Vertex() {}

Vertex::Vertex(glm::vec3 pos) : id(id_count), pos(pos), half_edge(nullptr), sharp(false)
{
    this->setText(QString::number(id_count));
    this->id_count++;
}

int Face::id_count = 0;

Face::Face() : id(id_count), color(glm::vec3(0, 0, 0)), half_edge(nullptr), sharp(false)
{
    this->setText(QString::number(id_count));
    this->id_count++;
}

Face::~Face() {}

Face::Face(glm::vec3 color) : id(id_count), color(color), half_edge(nullptr), sharp(false)
{
    this->setText(QString::number(id_count));
    this->id_count++;
}

int HalfEdge::id_count = 0;

HalfEdge::HalfEdge()
    : id(id_count), next(nullptr), sym(nullptr), face(nullptr), vertex(nullptr), sharp(false)
{
    this->setText(QString::number(id_count));
    this->id_count++;
}

HalfEdge::~HalfEdge() {}

HalfEdge::HalfEdge(Face* face)
    : id(id_count), next(nullptr), sym(nullptr), face(face), vertex(nullptr), sharp(false)
{
    this->setText(QString::number(id_count));
    this->id_count++;
}
