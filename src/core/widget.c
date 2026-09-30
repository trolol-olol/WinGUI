#include <windows.h>
#include "wingui.h"

WINGUI_WIDGET* wingui_widget_create(WINGUI_WINDOW *parent,const TCHAR *text,const TCHAR *class_name,int x,int y,int w,int h,DWORD style,WINGUI_WIDGET_TYPE type,WINGUI_WIDGET_CALLBACK on_event, void *data){
    if (parent==NULL || parent->hwnd==NULL || parent->widgets==NULL) return NULL;
    HMENU id=(HMENU)parent->widget_ctr;

    HWND hwnd=CreateWindow(class_name,
                           text,
                           WS_VISIBLE|WS_CHILD|style,
                           x,y,
                           w,h,
                           parent->hwnd,id,NULL,NULL);
    if (hwnd==NULL) return NULL;
    WINGUI_WIDGET *widget=malloc(sizeof(WINGUI_WIDGET));
    if (widget==NULL){
        DestroyWindow(hwnd);
        return NULL;
    }

    widget->hwnd=hwnd;
    widget->parent=parent;
    widget->type=type;
    widget->id=id;
    widget->font=NULL;
    widget->on_event=on_event;
    widget->callback_data=data;
    if (list_append(parent->widgets,widget)==-1) {
        DestroyWindow(hwnd);
        free(widget);
        return NULL;
    }
    parent->widget_ctr+=1;
    return widget;
}

int wingui_widget_get_text(WINGUI_WIDGET *widget,TCHAR *buf,int max_len){
    if (widget==NULL || widget->hwnd==NULL || buf==NULL) return -1;
    return GetWindowText(widget->hwnd,buf,max_len);
}

int wingui_widget_get_text_length(WINGUI_WIDGET *widget){
    if (widget==NULL ||widget->hwnd==NULL) return -1;
    return GetWindowTextLength(widget->hwnd);
}

TCHAR* wingui_widget_get_text_full(WINGUI_WIDGET *widget){
    if (widget==NULL || widget->hwnd==NULL) return NULL;
    int len=wingui_widget_get_text_length(widget);
    TCHAR *buf=malloc((len+1)*sizeof(TCHAR));
    if (buf==NULL) return NULL;
    wingui_widget_get_text(widget,buf,len+1);
    return buf;
}

bool wingui_widget_set_text(WINGUI_WIDGET *widget,TCHAR *text){
    if (widget==NULL || widget->hwnd==NULL || text==NULL) return false;
    return SetWindowText(widget->hwnd,text);
}

bool wingui_widget_resize(WINGUI_WIDGET *widget,int w,int h){
    if (widget==NULL || widget->hwnd==NULL) return false;
    if (w<0 || h<0) return false;
    return SetWindowPos(widget->hwnd,NULL,0,0,
                        w,h,SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
}

bool wingui_widget_move(WINGUI_WIDGET *widget,int x,int y){
    if (widget==NULL || widget->hwnd==NULL) return false;
    return SetWindowPos(widget->hwnd,NULL,x,y,
                        0,0,SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
}
