#pragma once
#include "common/types.h"

namespace myecs
{
    using entity = size_t;
    entity max_entity = 0;
    entity CreateEntity()
    {
        static entity entities = 0;
        ++entities;
        max_entity = entities;
        return entities;
    }
}