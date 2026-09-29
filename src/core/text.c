#include <windows.h>
#include "wingui.h"

SIZE wingui_text_get_size_for(WINGUI_WIDGET *widget, TCHAR *text, int length){
    SIZE invalid={-1,-1};
    if (text==NULL || length<=0) return invalid;

    HDC dc = CreateCompatibleDC(NULL);
    if (dc==NULL) return invalid;
    SelectObject(dc,widget->font);

    SIZE size;
    BOOL result=GetTextExtentPoint32(dc,text,length,&size);

    DeleteDC(dc);

    return result ? size : invalid;
}

SIZE wingui_text_get_size(TCHAR *text,int length){
    return wingui_text_get_size_for(NULL,text,length);
}

long wingui_text_get_width_for(WINGUI_WIDGET *widget,TCHAR *text,int length){
    if (text==NULL) return -1;
    return wingui_text_get_size_for(widget,text,length).cx;
}

long wingui_text_get_width(TCHAR *text,int length){
    return wingui_text_get_width_for(NULL,text,length);
}

long wingui_text_get_height_for(WINGUI_WIDGET *widget,TCHAR *text,int length){
    if (text==NULL) return -1;
    return wingui_text_get_size_for(widget,text,length).cy;
}

long wingui_text_get_height(TCHAR *text,int length){
    return wingui_text_get_height_for(NULL,text,length);
}
