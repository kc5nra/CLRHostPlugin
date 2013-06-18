#include "OBSApi.h"
#include "GraphicsSystem.h"

CLROBS::GraphicsSystem^ CLROBS::GraphicsSystem::Instance::get()
{
    if (!instance) {
        instance = gcnew CLROBS::GraphicsSystem(GS);
    }
    return instance;
}

CLROBS::GraphicsSystem::GraphicsSystem(::GraphicsSystem *graphicsSystem)
{
    this->graphicsSystem = graphicsSystem;
}

CLROBS::GraphicsSystem::~GraphicsSystem()
{
}