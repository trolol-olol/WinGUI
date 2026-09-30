#include <windows.h>
#include "wingui.h"

HFONT wingui_create_font(const TCHAR *name,int size,int attributes){
    if (name==NULL) name=TEXT("MS Shell Dlg");

    HFONT font=CreateFont(-size,0,0,0,
                          attributes&WINGUI_FONT_BOLD ? FW_BOLD : FW_NORMAL,
                          attributes&WINGUI_FONT_ITALIC,
                          attributes&WINGUI_FONT_UNDERLINED,
                          attributes&WINGUI_FONT_STRIKED,
                          DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
                          CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
                          DEFAULT_PITCH | FF_DONTCARE,
                          name);
    return font;
}

void wingui_set_font(WINGUI_WIDGET *widget,HFONT font){
    if (widget==NULL || font==NULL) return;
    if (widget->font!=NULL) DeleteObject(widget->font);
    widget->font=font;
    SendMessage(widget->hwnd,WM_SETFONT,(WPARAM)font,TRUE);
}

void wingui_reset_font(WINGUI_WIDGET *widget){
    if (widget==NULL) return;
    if (widget->font!=NULL) DeleteObject(widget->font);
    widget->font=NULL;
    SendMessage(widget->hwnd,WM_SETFONT,(WPARAM)NULL,TRUE);
}
