#include "Scene.h"
#include <Math/Matrix.h>
#include "GLES2/gl2.h"

using namespace Runner;

namespace
{
    std::string vertShader =
        "attribute vec4 a_vertex; \n"
        "attribute vec2 a_texture; \n"
        "uniform mat4 projViewMatr;"
        "uniform mat4 modelMatr;"
        "varying vec2 tex_coords; \n"
        "void main (void) \n"
        "{ \n"
        "tex_coords = a_texture; \n"
        "gl_Position = projViewMatr * modelMatr * a_vertex; \n"
        "} \n";

    std::string fragShader = 
        "precision mediump float; \n"
        "uniform sampler2D tex; \n"
        "varying vec2 tex_coords; \n"
        "void main (void)  \n"
        "{ \n"
        //"vec4 color = texture2D(tex, tex_coords.st); \n"
        //"gl_FragColor = color; \n"
        "gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0); \n"
        "} \n";
}

Scene::Buffer::Buffer()
{
}

Scene::Buffer::~Buffer()
{

}

void Scene::Buffer::validate(const FloatDataVec& data)
{
    glGenBuffers(1, &mId);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data.at(0), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Scene::Buffer::apply()
{
}

Scene::Scene(size_t width, size_t height) :
    mWidth(width),
    mHeight(height)
{
    //mShaderProgram = ProgramPtr(new Program());
}

Scene::~Scene()
{

}

void Scene::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    //Math::Mat4 viewProj = mCamera->getViewProj();

    //NodePtrList childList = getChildrenList();
    //NodePtrListItr childItr = childList.begin();
    //for (; childItr != childList.end(); ++childItr)
    //{

    //}
}

void Scene::update()
{
}

void Scene::validateDefaultCamera()
{
    mDefaultCamera = CameraPtr(new Camera());
    float width = static_cast<float>(mWidth);
    float height = static_cast<float>(mHeight);
    mDefaultCamera->setViewport(Math::Vec2f(0.0f, 0.0f), Math::Vec2f(width, height));
    const Math::Vec3f eye(width / 2.0f, height / 2.0f, 0.0f);
    const Math::Vec3f at(width / 2.0f, height / 2.0f, 0.0f);
    const Math::Vec3f up(0.0f, 1.0f, 0.0f);
    mDefaultCamera->setTransform(Math::Mat4::LookAt(eye, at, up));
    mDefaultCamera->setProjection(Math::Mat4::Frustum(-width / 2.0f, +width / 2.0f, -height / 2.0f, height / 2.0f, 1.0f, 1000.0f));
}