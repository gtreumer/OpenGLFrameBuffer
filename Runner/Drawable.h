#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include "Node.h"
#include <Math/Vector.h>

namespace Runner
{
    class Drawable : public Node
    {
    public:
        Drawable();
        ~Drawable();

        void setSize(const Math::Vec2f& size);
        Math::Vec2f getSize() const;
    private:
        Math::Vec2f mSize;
    };
}

#endif /*DRAWABLE_H_*/