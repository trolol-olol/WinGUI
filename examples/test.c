#include "wingui.h"
#include "messagebox.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    WINGUI_WIDGET *entry;
    WINGUI_WIDGET *label;
} EntryAndLabel;
bool enabled=true;

void callback(WINGUI_EVENT_TYPE event,WINGUI_WIDGET *self,void *data){
    printf("%d",event);
    if (event==CLICK){
        EntryAndLabel *pair=(EntryAndLabel*)data;
        WINGUI_WIDGET *entry=pair->entry;
        WINGUI_WIDGET *label=pair->label;
        int len=wingui_widget_get_text_length(entry);
        TCHAR *buf=malloc(len+1);
        wingui_widget_get_text(entry,buf,len+1);
        puts(buf);
        SIZE size=wingui_text_get_size_for(label,buf,len);
        wingui_widget_resize(label,size.cx,size.cy);
        wingui_widget_set_text(label,buf);
        free(buf);
        showerror(TEXT("CLICKED"),TEXT("HI"));
        if (enabled){
            wingui_widget_disable(entry);
            enabled=false;
        }
        else{
            wingui_widget_enable(entry);
            enabled=true;
        }
    }
    showwarning(TEXT("EVENT"),TEXT("LOL"));
}

void callback2(WINGUI_EVENT_TYPE event,WINGUI_WIDGET *self,void *data){
    WINGUI_WIDGET *box=(WINGUI_WIDGET*)data;
    if (event==SELECT){
        int index=wingui_listbox_get_selindex(box);
        int len=wingui_listbox_get_textlen(box,index);
        TCHAR *buf=malloc(len);
        wingui_listbox_index2elem(box,buf,index);
        printf("%s\n",buf);
        showinfo(TEXT("RLY"),TEXT("LOOOL"));
    }
}

void callback3(void *data){
    WINGUI_WINDOW *window=(WINGUI_WINDOW*)data;
    printf("HELLO FROM TIMER\n");
    wingui_after(window,50,callback3,window);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow){
    wingui_init(hInstance);

    EntryAndLabel pair;

    WINGUI_WINDOW *window=wingui_window_create(TEXT("WinGUI Test Window"),400,300);
    WINGUI_WIDGET *label=wingui_label_create(window,TEXT("Hello!"),100,100,40,20,NULL,NULL);
    WINGUI_FONT *font=wingui_create_font(TEXT("Arial"),36,0);
    wingui_set_font(label,font);
    WINGUI_WIDGET *entry=wingui_entry_create(window,100,0,100,20,NULL,NULL);

    pair.entry=entry;
    pair.label=label;

    WINGUI_WIDGET *button=wingui_button_create(window,TEXT("Click"),100,200,40,20,callback,&pair);
    WINGUI_WIDGET *lbox=wingui_listbox_create(window,300,0,100,400,callback2,NULL);
    wingui_widget_set_callback_data(lbox,lbox);
    wingui_listbox_add_elem(lbox,TEXT("Hi"));
    wingui_listbox_add_elem(lbox,TEXT("Example!"));

    UINT timer=wingui_set_timer(window,250,callback3,NULL);
    wingui_delete_timer(window,timer);
    wingui_after(window,50,callback3,window);

    wingui_window_show(window,nCmdShow);

    wingui_run();

    return 0;
}
