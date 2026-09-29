#include "wingui.h"
#include <windows.h>

WINGUI_WIDGET* wingui_button_create(WINGUI_WINDOW *parent,const TCHAR *text,int x,int y,int w,int h,WINGUI_WIDGET_CALLBACK on_event,void *callback_data){
    return wingui_widget_create(parent,text,TEXT("BUTTON"),x,y,w,h,0,BUTTON,on_event,callback_data);
}
