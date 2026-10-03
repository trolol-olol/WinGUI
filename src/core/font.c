#include <windows.h>
#include "wingui.h"

WINGUI_FONT* wingui_create_font(const TCHAR *name,int size,int attributes){
    if (name==NULL) name=TEXT("MS Shell Dlg");
    WINGUI_FONT *wing_font=malloc(sizeof(WINGUI_FONT));
    if (wing_font==NULL) return NULL;
    HFONT font=CreateFont(-size,0,0,0,
                          attributes&WINGUI_FONT_BOLD ? FW_BOLD : FW_NORMAL,
                          attributes&WINGUI_FONT_ITALIC,
                          attributes&WINGUI_FONT_UNDERLINED,
                          attributes&WINGUI_FONT_STRIKED,
                          DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
                          CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
                          DEFAULT_PITCH | FF_DONTCARE,
                          name);
    if (font==NULL){
        free(wing_font);
        return NULL;
    }
    wing_font->external=false;
    wing_font->font=font;
    wing_font->refctr=0;
    return wing_font;
}

WINGUI_FONT* wingui_font_from_hfont(HFONT font){
    if (font==NULL){
        return NULL;
    }
    WINGUI_FONT *wing_font=malloc(sizeof(WINGUI_FONT));
    if (wing_font==NULL) return NULL;
    wing_font->font=font;
    wing_font->external=true;
    return wing_font;
}

void wingui_set_font(WINGUI_WIDGET *widget,WINGUI_FONT *font){
    if (widget==NULL || font==NULL) return;
    if (widget->font!=NULL){
        if (!widget->font->external){
            font->refctr+=1;
        }
    }
    widget->font=font;
    SendMessage(widget->hwnd,WM_SETFONT,(WPARAM)font->font,TRUE);
}

void wingui_reset_font(WINGUI_WIDGET *widget){
    if (widget==NULL) return;
    if (widget->font!=NULL){
         if (!widget->font->external){
            widget->font->refctr-=1;
        }
    }
    widget->font=NULL;
    SendMessage(widget->hwnd,WM_SETFONT,(WPARAM)NULL,TRUE);
}

bool wingui_delete_font(WINGUI_FONT *font){
    if (font==NULL || font->external || font->refctr) return false;
    DeleteObject(font->font);
    font->font=NULL;
    return true;
}
