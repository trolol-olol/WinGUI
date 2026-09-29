#include <windows.h>
#include "wingui.h"

WINGUI_WIDGET* wingui_listbox_create(WINGUI_WINDOW *parent,int x,int y,int w,int h,WINGUI_WIDGET_CALLBACK on_event,void *callback_data){
    return wingui_widget_create(parent,NULL,TEXT("LISTBOX"),x,y,w,h,LBS_STANDARD ^ LBS_SORT,LISTBOX,on_event,callback_data);
}

bool wingui_listbox_add_elem(WINGUI_WIDGET *widget,TCHAR *elem){
    if (widget==NULL || elem==NULL || widget->hwnd==NULL) return false;
    int code=SendMessage(widget->hwnd,LB_ADDSTRING,0,(LPARAM)elem);
    return code!=LB_ERR && code!=LB_ERRSPACE;
}

bool wingui_listbox_del_index(WINGUI_WIDGET *widget,int index){
    if (widget==NULL || widget->hwnd==NULL) return false;
    return SendMessage(widget->hwnd,LB_DELETESTRING,(WPARAM)index,0)!=LB_ERR;
}

bool wingui_listbox_get_selelem(WINGUI_WIDGET *widget,TCHAR *buf){
    if (widget==NULL || buf==NULL || widget->hwnd==NULL) return false;
    int index=SendMessage(widget->hwnd,LB_GETCURSEL,0,0);
    if (index==LB_ERR)
        return false;
    return SendMessage(widget->hwnd,LB_GETTEXT,(WPARAM)index,(LPARAM)buf)!=LB_ERR;
}

int wingui_listbox_get_selindex(WINGUI_WIDGET *widget){
    if (widget==NULL || widget->hwnd==NULL) return LB_ERR;
    return SendMessage(widget->hwnd,LB_GETCURSEL,0,0);
}

bool wingui_listbox_index2elem(WINGUI_WIDGET *widget,TCHAR *buf,int index){
    if (widget==NULL || buf==NULL || widget->hwnd==NULL) return false;
    return SendMessage(widget->hwnd,LB_GETTEXT,(WPARAM)index,(LPARAM)buf)!=LB_ERR;
}

int wingui_listbox_elem2index(WINGUI_WIDGET *widget,TCHAR *buf){
    if (widget==NULL || buf==NULL || widget->hwnd==NULL) return LB_ERR;
    return SendMessage(widget->hwnd,LB_FINDSTRINGEXACT,(WPARAM)-1,(LPARAM)buf);
}

int wingui_listbox_get_textlen(WINGUI_WIDGET *widget,int index){
    if (widget==NULL || widget->hwnd==NULL) return LB_ERR;
    return SendMessage(widget->hwnd,LB_GETTEXTLEN,(WPARAM)index,0);
}

bool wingui_listbox_clear(WINGUI_WIDGET *widget){
    if (widget==NULL || widget->hwnd==NULL) return false;
    return SendMessage(widget->hwnd,LB_RESETCONTENT,0,0)!=LB_ERR;
}

int wingui_listbox_getlen(WINGUI_WIDGET *widget){
    if (widget==NULL || widget->hwnd==NULL) return LB_ERR;
    return SendMessage(widget->hwnd,LB_GETCOUNT,0,0);
}
