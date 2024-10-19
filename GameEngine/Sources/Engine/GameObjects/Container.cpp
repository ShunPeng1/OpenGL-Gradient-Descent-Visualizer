#include "Engine/GameObjects/Container.h"

Container::Container() : GameObject(), mTransform(Transform(this))
{

}

Container::~Container() noexcept
{
}
