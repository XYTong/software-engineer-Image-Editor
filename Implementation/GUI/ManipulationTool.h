#include "Tool.h"

#ifndef MANIPULATION_TOOL_H
#define MANIPULATION_TOOL_H

class ManipulationTool{
	public:
		Tool getTool(int index);
        bool initTool(Tool tool);
	
	private:
		Tool* tools;
};

#endif /* !MANIPULATION_TOOL_H */
