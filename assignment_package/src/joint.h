#ifndef JOINT_H
#define JOINT_H
#include <la.h>
#include <QListWidget>
#include <glm/gtx/quaternion.hpp>

class Joint : public QListWidgetItem
{
public:
    QString name;
    Joint *parent;
    std::vector<Joint*> children;
    glm::vec4 position;
    glm::quat rotation;
    glm::mat4 bind_matrix;

    glm::mat4 getLocalTransformation();
    glm::mat4 getOverallTransformation();
};

#endif
