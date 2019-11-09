#include <mesh.h>
#include <iostream>

Mesh::Mesh(OpenGLContext *context) : Drawable(context) {}

Mesh::~Mesh() {}

void Mesh::create() {
    std::vector<GLuint> idx;
    std::vector<glm::vec4> pos;
    std::vector<glm::vec4> nor;
    std::vector<glm::vec4> col;
    std::vector<glm::ivec2> jointID;
    std::vector<glm::vec2> jointWeight;

    for (unsigned int i = 0; i < faces.size(); i++) {
        Face* face = faces[i].get();
        HalfEdge* curr_edge = face->half_edge;
        int first_index = pos.size();
        do {
            // color
            col.push_back(glm::vec4(face->color, 1));
            // position
            glm::vec3 curr_pos = curr_edge->vertex->pos;
            pos.push_back(glm::vec4(curr_pos, 1));
            // normal
            glm::vec3 prev_pos = curr_edge->sym->vertex->pos;
            glm::vec3 next_pos = curr_edge->next->vertex->pos;
            glm::vec3 normal = glm::cross(prev_pos - curr_pos, next_pos - curr_pos);
            nor.push_back(glm::vec4(normal, 0));

            Vertex* vertex = curr_edge->vertex;
            if (vertex->joint_inf.size() > 0) {
                // joint ID
                jointID.push_back(glm::ivec2(vertex->joint_inf[0].first, vertex->joint_inf[1].first));
                // joint weight
                jointWeight.push_back(glm::vec2(vertex->joint_inf[0].second, vertex->joint_inf[1].second));
            }

            curr_edge = curr_edge->next;
        }
        while (curr_edge != face->half_edge);
        for (unsigned int j = first_index; j < pos.size() - 2; j++) {
            idx.push_back(GLuint(first_index));
            idx.push_back(GLuint(j + 1));
            idx.push_back(GLuint(j + 2));
        }
    }

    count = idx.size();

    generateIdx();
    mp_context->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIdx);
    mp_context->glBufferData(GL_ELEMENT_ARRAY_BUFFER, idx.size() * sizeof(GLuint), idx.data(), GL_STATIC_DRAW);

    generatePos();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufPos);
    mp_context->glBufferData(GL_ARRAY_BUFFER, pos.size() * sizeof(glm::vec4), pos.data(), GL_STATIC_DRAW);

    generateNor();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufNor);
    mp_context->glBufferData(GL_ARRAY_BUFFER, nor.size() * sizeof(glm::vec4), nor.data(), GL_STATIC_DRAW);

    generateCol();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufCol);
    mp_context->glBufferData(GL_ARRAY_BUFFER, col.size() * sizeof(glm::vec4), col.data(), GL_STATIC_DRAW);

    generateJointID();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufJointID);
    mp_context->glBufferData(GL_ARRAY_BUFFER, jointID.size() * sizeof(glm::ivec2), jointID.data(), GL_STATIC_DRAW);

    generateJointWeight();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufJointWeight);
    mp_context->glBufferData(GL_ARRAY_BUFFER, jointWeight.size() * sizeof(glm::vec2), jointWeight.data(), GL_STATIC_DRAW);
}

void Mesh::createCubeMesh() {
    uPtr<Vertex> v0 = mkU<Vertex>(glm::vec3(0.5, 0.5, 0.5));
    uPtr<Vertex> v1 = mkU<Vertex>(glm::vec3(-0.5, 0.5, 0.5));
    uPtr<Vertex> v2 = mkU<Vertex>(glm::vec3(-0.5, 0.5, -0.5));
    uPtr<Vertex> v3 = mkU<Vertex>(glm::vec3(0.5, 0.5, -0.5));
    uPtr<Vertex> v4 = mkU<Vertex>(glm::vec3(-0.5, -0.5, 0.5));
    uPtr<Vertex> v5 = mkU<Vertex>(glm::vec3(0.5, -0.5, 0.5));
    uPtr<Vertex> v6 = mkU<Vertex>(glm::vec3(0.5, -0.5, -0.5));
    uPtr<Vertex> v7 = mkU<Vertex>(glm::vec3(-0.5, -0.5, -0.5));

    vertices.push_back(std::move(v0));
    vertices.push_back(std::move(v1));
    vertices.push_back(std::move(v2));
    vertices.push_back(std::move(v3));
    vertices.push_back(std::move(v4));
    vertices.push_back(std::move(v5));
    vertices.push_back(std::move(v6));
    vertices.push_back(std::move(v7));

    for (int i = 0; i < 6; i++) {
        uPtr<Face> face = mkU<Face>();
        faces.push_back(std::move(face));
    }

    HalfEdge* first_he = nullptr;
    for (int i = 0; i < 24; i++) {
        uPtr<HalfEdge> half_edge = mkU<HalfEdge>(faces[i / 4].get());
        HalfEdge* curr_he = half_edge.get();

        half_edges.push_back(std::move(half_edge));

        if (i % 4 == 0) {
            first_he = curr_he;
            faces[i / 4]->half_edge = curr_he;
        } else if (i % 4 == 3)  {
            curr_he->next = first_he;
            half_edges[i - 1]->next = curr_he;
        } else {
            half_edges[i - 1]->next = curr_he;
        }
    }

    faces[0]->color = glm::vec3(1, 0, 0);
    faces[1]->color = glm::vec3(0, 1, 0);
    faces[2]->color = glm::vec3(1, 0, 0);
    faces[3]->color = glm::vec3(0, 1, 0);
    faces[4]->color = glm::vec3(0, 0, 1);
    faces[5]->color = glm::vec3(0, 0, 1);

    half_edges[0]->vertex = vertices[1].get();
    half_edges[1]->vertex = vertices[2].get();
    half_edges[2]->vertex = vertices[3].get();
    half_edges[3]->vertex = vertices[0].get();
    half_edges[4]->vertex = vertices[0].get();
    half_edges[5]->vertex = vertices[3].get();
    half_edges[6]->vertex = vertices[6].get();
    half_edges[7]->vertex = vertices[5].get();
    half_edges[8]->vertex = vertices[5].get();
    half_edges[9]->vertex = vertices[6].get();
    half_edges[10]->vertex = vertices[7].get();
    half_edges[11]->vertex = vertices[4].get();
    half_edges[12]->vertex = vertices[4].get();
    half_edges[13]->vertex = vertices[7].get();
    half_edges[14]->vertex = vertices[2].get();
    half_edges[15]->vertex = vertices[1].get();
    half_edges[16]->vertex = vertices[4].get();
    half_edges[17]->vertex = vertices[1].get();
    half_edges[18]->vertex = vertices[0].get();
    half_edges[19]->vertex = vertices[5].get();
    half_edges[20]->vertex = vertices[2].get();
    half_edges[21]->vertex = vertices[7].get();
    half_edges[22]->vertex = vertices[6].get();
    half_edges[23]->vertex = vertices[3].get();

    vertices[0]->half_edge = half_edges[3].get();
    vertices[1]->half_edge = half_edges[0].get();
    vertices[2]->half_edge = half_edges[1].get();
    vertices[3]->half_edge = half_edges[2].get();
    vertices[4]->half_edge = half_edges[11].get();
    vertices[5]->half_edge = half_edges[8].get();
    vertices[6]->half_edge = half_edges[9].get();
    vertices[7]->half_edge = half_edges[10].get();

    half_edges[0]->sym = half_edges[18].get();
    half_edges[18]->sym = half_edges[0].get();
    half_edges[1]->sym = half_edges[15].get();
    half_edges[15]->sym = half_edges[1].get();
    half_edges[2]->sym = half_edges[20].get();
    half_edges[20]->sym = half_edges[2].get();
    half_edges[3]->sym = half_edges[5].get();
    half_edges[5]->sym = half_edges[3].get();
    half_edges[4]->sym = half_edges[19].get();
    half_edges[19]->sym = half_edges[4].get();
    half_edges[6]->sym = half_edges[23].get();
    half_edges[23]->sym = half_edges[6].get();
    half_edges[7]->sym = half_edges[9].get();
    half_edges[9]->sym = half_edges[7].get();
    half_edges[8]->sym = half_edges[16].get();
    half_edges[16]->sym = half_edges[8].get();
    half_edges[10]->sym = half_edges[22].get();
    half_edges[22]->sym = half_edges[10].get();
    half_edges[11]->sym = half_edges[13].get();
    half_edges[13]->sym = half_edges[11].get();
    half_edges[12]->sym = half_edges[17].get();
    half_edges[17]->sym = half_edges[12].get();
    half_edges[14]->sym = half_edges[21].get();
    half_edges[21]->sym = half_edges[14].get();
}
