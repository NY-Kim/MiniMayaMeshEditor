#include <display.h>
#include <iostream>
#include <glm/gtx/rotate_vector.hpp>

HalfEdgeDisplay::HalfEdgeDisplay(OpenGLContext* context)
    : Drawable(context), representedHalfEdge(nullptr) {}

HalfEdgeDisplay::~HalfEdgeDisplay() {}

void HalfEdgeDisplay::create() {

    std::vector<GLuint> idx;
    std::vector<glm::vec4> pos;
    std::vector<glm::vec4> col;

    if (representedHalfEdge) {
        pos.push_back(glm::vec4(representedHalfEdge->sym->vertex->pos, 1));
        col.push_back(glm::vec4(1, 0, 0, 1));
        idx.push_back(GLuint(0));

        pos.push_back(glm::vec4(representedHalfEdge->vertex->pos, 1));
        col.push_back(glm::vec4(1, 1, 0, 1));
        idx.push_back(GLuint(1));
    }
    count = idx.size();

    generateIdx();
    mp_context->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIdx);
    mp_context->glBufferData(GL_ELEMENT_ARRAY_BUFFER, idx.size() * sizeof(GLuint), idx.data(), GL_STATIC_DRAW);

    generatePos();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufPos);
    mp_context->glBufferData(GL_ARRAY_BUFFER, pos.size() * sizeof(glm::vec4), pos.data(), GL_STATIC_DRAW);

    generateCol();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufCol);
    mp_context->glBufferData(GL_ARRAY_BUFFER, col.size() * sizeof(glm::vec4), col.data(), GL_STATIC_DRAW);
}

void HalfEdgeDisplay::updateHalfEdge(HalfEdge *halfEdge) {
    representedHalfEdge = halfEdge;
}

GLenum HalfEdgeDisplay::drawMode() {
    return GL_LINES;
}

FaceDisplay::FaceDisplay(OpenGLContext *context)
    : Drawable(context), representedFace(nullptr) {}

FaceDisplay::~FaceDisplay() {}

void FaceDisplay::create() {

    std::vector<GLuint> idx;
    std::vector<glm::vec4> pos;
    std::vector<glm::vec4> col;

    if (representedFace) {
        HalfEdge* curr_edge = representedFace->half_edge;

        do {
            // color
            col.push_back(glm::vec4(std::abs(representedFace->color[0] - 1),
                                    std::abs(representedFace->color[1] - 1),
                                    std::abs(representedFace->color[2] - 1),
                                    1));

            // position
            glm::vec3 curr_pos = curr_edge->vertex->pos;
            pos.push_back(glm::vec4(curr_pos, 1));

            curr_edge = curr_edge->next;
        }
        while (curr_edge != representedFace->half_edge);

        for (unsigned int j = 0; j < pos.size() - 1; j++) {
            idx.push_back(GLuint(j));
            idx.push_back(GLuint(j + 1));
        }
        idx.push_back(GLuint(pos.size() - 1));
        idx.push_back(0);
    }
    count = idx.size();

    generateIdx();
    mp_context->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIdx);
    mp_context->glBufferData(GL_ELEMENT_ARRAY_BUFFER, idx.size() * sizeof(GLuint), idx.data(), GL_STATIC_DRAW);

    generatePos();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufPos);
    mp_context->glBufferData(GL_ARRAY_BUFFER, pos.size() * sizeof(glm::vec4), pos.data(), GL_STATIC_DRAW);

    generateCol();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufCol);
    mp_context->glBufferData(GL_ARRAY_BUFFER, col.size() * sizeof(glm::vec4), col.data(), GL_STATIC_DRAW);
}

void FaceDisplay::updateFace(Face *face) {
    representedFace = face;
}

GLenum FaceDisplay::drawMode() {
    return GL_LINES;
}

VertexDisplay::VertexDisplay(OpenGLContext *context)
    : Drawable(context), representedVertex(nullptr) {}

VertexDisplay::~VertexDisplay() {}

void VertexDisplay::create() {

    std::vector<GLuint> idx;
    std::vector<glm::vec4> pos;
    std::vector<glm::vec4> col;

    if (representedVertex) {
        pos.push_back(glm::vec4(representedVertex->pos, 1));
        col.push_back(glm::vec4(0, 0, 0, 0));
        idx.push_back(GLuint(0));
    }
    count = idx.size();

    generateIdx();
    mp_context->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIdx);
    mp_context->glBufferData(GL_ELEMENT_ARRAY_BUFFER, idx.size() * sizeof(GLuint), idx.data(), GL_STATIC_DRAW);

    generatePos();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufPos);
    mp_context->glBufferData(GL_ARRAY_BUFFER, pos.size() * sizeof(glm::vec4), pos.data(), GL_STATIC_DRAW);

    generateCol();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufCol);
    mp_context->glBufferData(GL_ARRAY_BUFFER, col.size() * sizeof(glm::vec4), col.data(), GL_STATIC_DRAW);
}

void VertexDisplay::updateVertex(Vertex *vertex) {
    representedVertex = vertex;
}

GLenum VertexDisplay::drawMode() {
    return GL_POINTS;
}

JointDisplay::JointDisplay(OpenGLContext *context) : Drawable(context) {}

JointDisplay::~JointDisplay() {}

void JointDisplay::create() {

    std::vector<GLuint> idx;
    std::vector<glm::vec4> pos;
    std::vector<glm::vec4> col;

    glm::vec4 offset = glm::vec4(0, 0.5, 0, 1);
    for (int j = 0; j < 12; j++) {
        pos.push_back(representedJoint->getOverallTransformation() * offset);
        col.push_back(glm::vec4(0, 1, 1, 1));
        offset = glm::rotateX(offset, glm::radians(30.f));

        if (j == 11) {
            idx.push_back(GLuint(j));
            idx.push_back(GLuint(0));
        } else {
            idx.push_back(GLuint(j));
            idx.push_back(GLuint(j + 1));
        }
    }

    offset = glm::vec4(0, 0, 0.5, 1);
    for (int j = 12; j < 24; j++) {
        pos.push_back(representedJoint->getOverallTransformation() * offset);
        col.push_back(glm::vec4(1, 0, 1, 1));
        offset = glm::rotateY(offset, glm::radians(30.f));

        if (j == 23) {
            idx.push_back(GLuint(j));
            idx.push_back(GLuint(12));
        } else {
            idx.push_back(GLuint(j));
            idx.push_back(GLuint(j + 1));
        }
    }

    offset = glm::vec4(0.5, 0, 0, 1);
    for (int j = 24; j < 36; j++) {
        pos.push_back(representedJoint->getOverallTransformation() * offset);
        col.push_back(glm::vec4(1, 1, 0, 1));
        offset = glm::rotateZ(offset, glm::radians(30.f));

        if (j == 35) {
            idx.push_back(GLuint(j));
            idx.push_back(GLuint(24));
        } else {
            idx.push_back(GLuint(j));
            idx.push_back(GLuint(j + 1));
        }
    }

    count = idx.size();

    generateIdx();
    mp_context->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIdx);
    mp_context->glBufferData(GL_ELEMENT_ARRAY_BUFFER, idx.size() * sizeof(GLuint), idx.data(), GL_STATIC_DRAW);

    generatePos();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufPos);
    mp_context->glBufferData(GL_ARRAY_BUFFER, pos.size() * sizeof(glm::vec4), pos.data(), GL_STATIC_DRAW);

    generateCol();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufCol);
    mp_context->glBufferData(GL_ARRAY_BUFFER, col.size() * sizeof(glm::vec4), col.data(), GL_STATIC_DRAW);
}

void JointDisplay::updateJoint(Joint *joint) {
    representedJoint = joint;
}

GLenum JointDisplay::drawMode() {
    return GL_LINES;
}
