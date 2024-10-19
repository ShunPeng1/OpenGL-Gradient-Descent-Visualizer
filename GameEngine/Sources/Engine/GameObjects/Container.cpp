#include "Engine/GameObjects/Container.h"

Container::Container() : GameObject(), transform(Transform(this))
{

}

Container::~Container() noexcept
{
}
