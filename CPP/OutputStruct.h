/*
========================================================================

	OutputStruct - used by entities to manage their outputs

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include <string>

namespace MysticDave {
    struct OutputStruct {
        std::string outputName;   // what event causes the output to fire, ex: “OnDeath”
        std::string targetEntity; // the name of the entity that will receive input
        std::string inputName;    // the input on the target entity that will be triggered, ex: “Open”
        float       timeDelay;    // the number of seconds to wait after the output event occurs before firing
        bool        fireOnceOnly; // whether this output will be deleted after it fires
    };
}
