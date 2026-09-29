#include <windows.h>
#include "wingui.h"

WINGUI_WIDGET* wingui_entry_create(WINGUI_WINDOW *parent,int x,int y,int w,int h,WINGUI_WIDGET_CALLBACK on_event,void *callback_data){
    return wingui_widget_create(parent,NULL,TEXT("EDIT"),x,y,w,h,WS_BORDER | ES_AUTOHSCROLL,ENTRY,on_event,callback_data);
}
