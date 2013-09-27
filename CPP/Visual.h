/*
========================================================================

	An object which can be rendered on the screen

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

namespace MysticDave {
    class Visual {
    public:
						    Visual();
						    ~Visual();
	    virtual void		Cleanup() = 0;
	    virtual void		Render() = 0;
    };
}