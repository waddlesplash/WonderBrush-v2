// CloseAction.h

#ifndef CLOSE_ACTION_H
#define CLOSE_ACTION_H

#include "PathAction.h"

class CloseAction : public PathAction {
 public:
								CloseAction(ShapeState* state,
											ShapeStroke* modifier);
	virtual						~CloseAction();

	virtual	status_t			Perform(CanvasView* view);
	virtual status_t			Undo(CanvasView* view);
	virtual status_t			Redo(CanvasView* view);

	virtual void				GetName(BString& name);

 private:
};

#endif // CLOSE_ACTION_H
