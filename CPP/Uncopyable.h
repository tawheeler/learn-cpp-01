/*
========================================================================

	A base class which prevents an item from being copied

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

namespace MysticDave {
    class Uncopyable {
    protected:
        Uncopyable(){}    // allow construction of derived objects
        ~Uncopyable(){}   // allow destruction of derived objects
    private:
        Uncopyable( const Uncopyable& ); // prevent copying of derived objects
        Uncopyable& operator=( const Uncopyable& );
    };
}