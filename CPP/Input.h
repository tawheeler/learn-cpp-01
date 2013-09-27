/*
========================================================================

	Input - objects which encapsulate messages sent into an entity

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include <string>
#include <list>
#include "Property.h"

namespace MysticDave {
    class Input {

    public:
                              Input() {}

        std::string           inputName; // the input on the target entity to trigger, ex: “Open”
        std::list< Property > params; // list of parameters

    };
}