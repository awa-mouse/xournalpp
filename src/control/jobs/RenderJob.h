/*
 * Xournal++
 *
 * A job which redraws a page or a page region
 *
 * @author Xournal++ Team
 * https://github.com/xournalpp/xournalpp
 *
 * @license GNU GPLv2 or later
 */

#pragma once

#include "Job.h"

#include <XournalType.h>

class Rectangle;
class XojPageView;
class RepaintWidgetHandler;

class RenderJob : public Job
{
public:
	RenderJob(XojPageView* view);

protected:
	virtual ~RenderJob();

public:
	virtual JobType getType();

	void* getSource();

	void run();

public:
	static void rerenderRectangle(RenderJob* renderJob, Rectangle* rect);
	static void cleanupStatic();

private:
	void rerenderRectangle(Rectangle* rect);

private:
	XOJ_TYPE_ATTRIB;

	XojPageView* view;

	static RepaintWidgetHandler* repaintHandler;
};
