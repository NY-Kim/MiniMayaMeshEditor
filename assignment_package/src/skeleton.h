#ifndef SKELETON_H
#define SKELETON_H
#include <joint.h>
#include <drawable.h>
#include <smartpointerhelp.h>

class Skeleton : public Drawable
{
public:
    std::vector<uPtr<Joint>> joints;
    int selectedJoint;

    Skeleton(OpenGLContext* context);
    ~Skeleton();
    void create() override;
    GLenum drawMode() override;
};

#endif // SKELETON_H
