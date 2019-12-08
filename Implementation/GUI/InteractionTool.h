#include "Picture.h"

#ifndef INTERACTION_TOOL_H
#define INTERACTION_TOOL_H

class InetractionTool{
	public:
		void show(Picture pic);
        bool useTool(Picture pic);
        bool createPic();
        bool importPic();
		
	private:
		Picture pic;
};

#endif /* !INTERACTION_TOOL_H */
