#include <windows.h>
#include "wingui.h"

WINGUI_WIDGET* wingui_label_create(WINGUI_WINDOW *parent,const TCHAR *text,int x,int y,int w,int h,WINGUI_WIDGET_CALLBACK on_event,void *callback_data){
    return wingui_widget_create(parent,text,TEXT("STATIC"),x,y,w,h,0,LABEL,on_event,callback_data);
}
