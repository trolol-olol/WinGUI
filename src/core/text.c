#include <windows.h>
#include "wingui.h"

HDC g_wingui_text_dc=NULL;

SIZE wingui_text_get_size_for(WINGUI_WIDGET *widget, TCHAR *text, int length){
    SIZE invalid={-1,-1};
    if (text==NULL || length<=0) return invalid;
    if (g_wingui_text_dc==NULL){
        g_wingui_text_dc=CreateCompatibleDC(NULL);
    }
    if (g_wingui_text_dc==NULL){
        return invalid;
    }
    SelectObject(g_wingui_text_dc,widget->font->font);

    SIZE size;
    BOOL result=GetTextExtentPoint32(g_wingui_text_dc,text,length,&size);

    SelectObject(g_wingui_text_dc,NULL);

    return result ? size : invalid;
}

SIZE wingui_text_get_size(TCHAR *text,int length){
    if (text==NULL || length<=0) return (SIZE){-1,-1};
    return wingui_text_get_size_for(NULL,text,length);
}

long wingui_text_get_width_for(WINGUI_WIDGET *widget,TCHAR *text,int length){
    if (text==NULL || length<=0) return -1;
    return wingui_text_get_size_for(widget,text,length).cx;
}

long wingui_text_get_width(TCHAR *text,int length){
    if (text==NULL || length<=0) return -1;
    return wingui_text_get_width_for(NULL,text,length);
}

long wingui_text_get_height_for(WINGUI_WIDGET *widget,TCHAR *text,int length){
    if (text==NULL || length<=0) return -1;
    return wingui_text_get_size_for(widget,text,length).cy;
}

long wingui_text_get_height(TCHAR *text,int length){
    if (text==NULL || length<=0) return -1;
    return wingui_text_get_height_for(NULL,text,length);
}
