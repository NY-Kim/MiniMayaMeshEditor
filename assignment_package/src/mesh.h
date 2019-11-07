#ifndef MESH_H
#define MESH_H
#include <primitives.h>
#include <drawable.h>
#include <smartpointerhelp.h>

class Mesh : public Drawable
{
public:
    std::vector<uPtr<Face>> faces;
    std::vector<uPtr<HalfEdge>> half_edges;
    std::vector<uPtr<Vertex>> vertices;

    Mesh(OpenGLContext* context);
    ~Mesh();
    void create() override;
    void createCubeMesh();
};

#endif
