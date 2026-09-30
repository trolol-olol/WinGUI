#ifndef WINGUI_INTERNAL_H
#define WINGUI_INTERNAL_H

#include "wingui.h"
#include <windows.h>

void wingui_internal_set_instance(HINSTANCE inst);
HINSTANCE wingui_internal_get_instance();

WINGUI_EVENT_TYPE wingui_internal_code2event(int code,WINGUI_WIDGET_TYPE type);
WINGUI_WIDGET* wingui_internal_id2widget(WINGUI_WINDOW *window,int id);

WINGUI_TIMER* wingui_internal_id2timer(WINGUI_WINDOW *window,UINT timer_id);

#endif
