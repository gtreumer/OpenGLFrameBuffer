#ifndef CAMERA_H_
#define CAMERA_H_

#include <Math/Matrix.h>
#include <memory>

namespace Runner
{
    class Camera
    {
    public:
        Camera();
        ~Camera();

        void setViewport(const Math::Vec2f& vMin, const Math::Vec2f& vMax);
        void setProjection(const Math::Mat4& proj);
        void setTransform(const Math::Mat4& trans);

        const Math::Mat4& getProjection() const;
        const Math::Mat4& getTransform() const;
        const Math::Vec2f& getViewportMin() const;
        const Math::Vec2f& getViewportMax() const;
        Math::Mat4 getViewProj() const;
    private:
        Math::Mat4 mProjection;
        Math::Mat4 mTransform;
        Math::Vec2f mViewportMin;
        Math::Vec2f mViewportMax;
    };
    typedef std::shared_ptr<Camera> CameraPtr;
}

#endif /*CAMERA_H_*/