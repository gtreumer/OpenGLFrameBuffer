#ifndef SCENE_H_
#define SCENE_H_

#include <Node.h>
#include <Camera.h>
#include "Program.h"

#include <memory>

namespace Runner
{
class Scene : public Node
{
public:
    typedef std::vector<float> FloatDataVec;

    class RenderCommand
    {
    public:
        RenderCommand() {}
        ~RenderCommand() {}

        virtual void apply() = 0;
    };

    class Buffer : public RenderCommand
    {
    public:
        Buffer();
        ~Buffer();

        void validate(const FloatDataVec& data);
        void apply();
    private:
        size_t mId;
    };

    Scene(size_t width, size_t height);
    ~Scene();

    void render();
    void update();

private:
    void validateDefaultCamera();
    CameraPtr mDefaultCamera;
    ProgramPtr mShaderProgram;
    size_t mWidth;
    size_t mHeight;
};

typedef std::shared_ptr<Scene> ScenePtr;

}
#endif /*SCENE_H_*/