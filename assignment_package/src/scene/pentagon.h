#pragma once

#include "drawable.h"
#include <la.h>

#include <QOpenGLContext>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

class Pentagon : public Drawable
{
public:
    Pentagon(OpenGLContext* mp_context);
    virtual void create();
};
