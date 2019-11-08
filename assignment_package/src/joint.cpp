#include <joint.h>

int Joint::id_count = 0;

Joint::Joint(QString name, Joint *parent, glm::vec3 position, glm::quat rotation)
    : name(name), parent(parent), children(std::vector<Joint*>()),
      position(position), rotation(rotation), bind_matrix(glm::mat4(1.0f)), id(id_count)
{
    this->setText(0, name);
    this->id_count++;
}

Joint::~Joint() {}

glm::mat4 Joint::getLocalTransformation() {
    glm::mat4 T = glm::mat4(glm::vec4(1, 0, 0, 0),
                            glm::vec4(0, 1, 0, 0),
                            glm::vec4(0, 0, 1, 0),
                            glm::vec4(this->position, 1));
    glm::mat4 R = glm::toMat4(this->rotation);

    return T * R;
}

glm::mat4 Joint::getOverallTransformation() {
    if (parent == nullptr) {
        return this->getLocalTransformation();
    } else {
        return parent->getOverallTransformation() * this->getLocalTransformation();
    }
}
