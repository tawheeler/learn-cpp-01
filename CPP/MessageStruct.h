/*
========================================================================

	OutputStruct - A structure defining an input given to an entity

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include "Property.h"
#include <string>
#include <list>

namespace MysticDave {
    struct MessageStruct {
        int targetEntityID;     // the id name of the entity that will receive input
        std::string inputName;  // the input on the target entity that will be triggered, ex: “Open”
        int        timeDelay;   // Num ticks to wait before firing
    };
}
