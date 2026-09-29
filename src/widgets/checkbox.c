#include "wingui.h"
#include <windows.h>

WINGUI_WIDGET* wingui_checkbox_create(WINGUI_WINDOW *parent,const TCHAR *text,int x,int y,int w,int h,WINGUI_WIDGET_CALLBACK on_event,void *callback_data){
    return wingui_widget_create(parent,text,TEXT("BUTTON"),x,y,w,h,BS_AUTOCHECKBOX,CHECKBOX,on_event,callback_data);
}

void wingui_checkbox_set_state(WINGUI_WIDGET *widget,bool state){
    if (widget==NULL || widget->hwnd==NULL) return;
    SendMessage(widget->hwnd,BM_SETCHECK,state,0);
}

bool wingui_checkbox_get_state(WINGUI_WIDGET *widget){
    if (widget==NULL || widget->hwnd==NULL) return false;
    return SendMessage(widget->hwnd,BM_GETCHECK,0,0);
}
