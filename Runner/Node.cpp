#include <Node.h>

using namespace Runner;

Node::Node()
{
    mWorldTransform = Math::Mat4::Identity();
    mLocalTransform = Math::Mat4::Identity();
}

Node::~Node() {}

void Node::setPosition(const Math::Vec3f& pos)
{
    mPosition = pos;
}

void Node::setRotation(const Math::Quaternion& rot)
{
    mRotation = rot;
}

void Node::setScale(const Math::Vec3f& scale)
{
    mScale = scale;
}

const Math::Vec3f& Node::getPosition() const
{
    return mPosition;
}

const Math::Quaternion& Node::getRotation() const
{
    return mRotation;
}

const Math::Vec3f& Node::getScale() const
{
    return mScale;
}

const Math::Mat4& Node::getWorldTransform()
{
    if (mParent)
    {
        mWorldTransform = mParent->getWorldTransform() * getLocalTransform();
    }
    else
    {
        mWorldTransform = getLocalTransform();
    }

    return mWorldTransform;
}

const Math::Mat4& Node::getLocalTransform()
{
    Math::Mat4 translMatr = Math::Mat4::Translate(getPosition());
    Math::Mat4 rotateMatr(getRotation().ToMatrix());
    //const Math::Mat4 scaleMatr = Math::Mat4::Scale(getScale());
    mLocalTransform = rotateMatr * translMatr;

    return mLocalTransform;
}

void Node::addChild(NodePtr child)
{
    mChildrenList.push_back(child);
}

void Node::removeChild(NodePtr child)
{

}

Node::NodePtrList& Node::getChildrenList()
{
    return mChildrenList;
}

void Node::setParent(NodePtr parent)
{
    mParent = parent;
}

Node::NodePtr Node::getParent()
{
    return mParent;
}

void Node::invalidateTransformation()
{
    NodePtrList::iterator childItr = mChildrenList.begin();
    for (; childItr != mChildrenList.end(); ++childItr)
    {

    }
}