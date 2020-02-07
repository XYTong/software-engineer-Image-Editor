#include "Picture.h"
#include "ManipulationTool.h"

#ifndef INTERACTION_TOOL_H
#define INTERACTION_TOOL_H

/*!
 * \class InteractionTool
 * \brief Koordiniert die Verwendung von Picture und ManipulationTool.
 */
class InteractionTool{
	public:
        bool useTool(toolParameters_t* param);
        Picture* getPicture();
        InteractionTool();
		
	private:
        Picture *pic;
        ManipulationTool *tools;
};

#endif /* !INTERACTION_TOOL_H */
