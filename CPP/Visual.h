/*
========================================================================

	An object which can be rendered on the screen

========================================================================
*/

#pragma once

class Visual {
public:
						Visual();
						~Visual();
	virtual void		Cleanup() = 0;
	virtual void		Render() = 0;
};