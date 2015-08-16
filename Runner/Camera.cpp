#include <Camera.h>
using namespace Runner;

Camera::Camera()
{
    mProjection = Math::Mat4::Identity();
    mTransform = Math::Mat4::Identity();
    mViewportMin = Math::Vec2f(0.0f, 0.0f);
    mViewportMax = Math::Vec2f(1.0f, 1.0f);;
}

Camera::~Camera()
{
}

void Camera::setViewport(const Math::Vec2f& vMin, const Math::Vec2f& vMax)
{
    mViewportMin = vMin;
    mViewportMax = vMax;
}

void Camera::setProjection(const Math::Mat4& proj)
{
    mProjection = proj;
}

void Camera::setTransform(const Math::Mat4& trans)
{
    mTransform = trans;
}

const Math::Mat4& Camera::getProjection() const
{
    return mProjection;
}

const Math::Mat4& Camera::getTransform() const
{
    return mTransform;
}

const Math::Vec2f& Camera::getViewportMin() const
{
    return mViewportMin;
}

const Math::Vec2f& Camera::getViewportMax() const
{
    return mViewportMax;
}

Math::Mat4 Camera::getViewProj() const
{
    Math::Mat4 viewProj = mProjection * mTransform;
    return viewProj;
}