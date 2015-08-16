#include "Drawable.h"
using namespace Runner;

Drawable::Drawable()
{
    mSize = Math::Vec2f(1.0f, 1.0f);
}

Drawable::~Drawable()
{
}

void Drawable::setSize(const Math::Vec2f& size)
{
    mSize = size;
}

Math::Vec2f Drawable::getSize() const
{
    return mSize;
}