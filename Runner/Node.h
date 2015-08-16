#ifndef NODE_H_
#define NODE_H_

#include <Math/Vector.h>
#include <Math/Quaternion.h>
#include <Math/Matrix.h>
#include <vector>
#include <memory>

namespace Runner
{
class Node
{
public:
    typedef std::shared_ptr<Node> NodePtr;
    typedef std::vector<NodePtr> NodePtrList;
    typedef std::vector<NodePtr>::iterator NodePtrListItr;

    Node();
    virtual ~Node();

    void setPosition(const Math::Vec3f& pos);
    void setRotation(const Math::Quaternion& rot);
    void setScale(const Math::Vec3f& scele);

    const Math::Vec3f& getPosition() const;
    const Math::Quaternion& getRotation() const;
    const Math::Vec3f& getScale() const;

    const Math::Mat4& getWorldTransform();
    const Math::Mat4& getLocalTransform();

    void addChild(NodePtr child);
    void removeChild(NodePtr child);
    NodePtrList& getChildrenList();
    void setParent(NodePtr parent);
    NodePtr getParent();
private:
    void invalidateTransformation();
    NodePtrList mChildrenList;
    NodePtr mParent;
    Math::Vec3f mPosition;
    Math::Quaternion mRotation;
    Math::Vec3f mScale;
    Math::Mat4 mWorldTransform;
    Math::Mat4 mLocalTransform;
};
}
#endif /*NODE_H_*/