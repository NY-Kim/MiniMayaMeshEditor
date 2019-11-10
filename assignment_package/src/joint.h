#ifndef JOINT_H
#define JOINT_H
#include <la.h>
#include <QTreeWidget>
#include <QComboBox>
#include <glm/gtx/quaternion.hpp>

class Joint : public QTreeWidgetItem
{
public:
    QString name;
    Joint *parent;
    std::vector<Joint*> children;
    glm::vec3 position;
    glm::quat rotation;
    glm::mat4 bind_matrix;
    int id;
    static int id_count;

    Joint(QString name, Joint *parent, glm::vec3 position, glm::quat rotation);
    ~Joint();
    glm::mat4 getLocalTransformation();
    glm::mat4 getOverallTransformation();
};

#endif
