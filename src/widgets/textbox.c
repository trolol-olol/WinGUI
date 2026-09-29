#include <windows.h>
#include "wingui.h"

WINGUI_WIDGET* wingui_textbox_create(WINGUI_WINDOW *parent,int x,int y,int w,int h,WINGUI_WIDGET_CALLBACK on_event,void *callback_data){
    return wingui_widget_create(parent,NULL,TEXT("EDIT"),x,y,w,h,WS_BORDER | ES_AUTOHSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_WANTRETURN,ENTRY,on_event,callback_data);
}
