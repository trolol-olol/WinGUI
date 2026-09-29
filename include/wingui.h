#ifndef WINGUI_H
#define WINGUI_H

#include <windows.h>
#include <stddef.h>
#include <stdbool.h>
#include "utils.h"

#define wingui_widget_set_callback_data(widget,data) if((widget)) (widget)->callback_data=(data)

typedef enum{
    BUTTON,
    LABEL,
    ENTRY,
    CHECKBOX,
    LISTBOX
} WINGUI_WIDGET_TYPE;

typedef enum{
    CLICK,
    DBLCLICK,
    SETFOCUS,
    KILLFOCUS,
    CHANGE,
    SELECT,
    CANCEL,
    MAXTEXT,
    OPEN,
    CLOSE,
    ENABLE,
    DISABLE,
    OTHER
} WINGUI_EVENT_TYPE;

typedef struct WINGUI_WIDGET WINGUI_WIDGET;
typedef struct WINGUI_TIMER WINGUI_TIMER;
typedef void(*WINGUI_WIDGET_CALLBACK)(WINGUI_EVENT_TYPE,WINGUI_WIDGET*,void*);
typedef void(*WINGUI_TIMER_CALLBACK)(void*);

typedef struct{
    HWND hwnd;
    const TCHAR* title;
    List *widgets;
    UINT widget_ctr;
    List *timers;
    UINT timer_ctr;
} WINGUI_WINDOW;

struct WINGUI_WIDGET{
    HWND hwnd;
    WINGUI_WIDGET_TYPE type;
    WINGUI_WINDOW *parent;
    WINGUI_WIDGET_CALLBACK on_event;
    HMENU id;
    void *callback_data;
};

struct WINGUI_TIMER{
    bool is_onetime;
    UINT id;
    WINGUI_TIMER_CALLBACK on_tick;
    void *callback_data;
};

//Windows

WINGUI_WINDOW* wingui_window_create(const TCHAR *title,int width,
                                   int height);
void wingui_window_show(WINGUI_WINDOW *window,int type);
void wingui_window_destroy(WINGUI_WINDOW *window);

//Widgets
WINGUI_WIDGET* wingui_widget_create(WINGUI_WINDOW *parent,const TCHAR *text,
                                    const TCHAR *class_name,int x,int y,int w,
                                    int h,DWORD style,WINGUI_WIDGET_TYPE type,
                                    WINGUI_WIDGET_CALLBACK on_event,void *data);

WINGUI_WIDGET* wingui_button_create(WINGUI_WINDOW *parent,const TCHAR *text,int x,
                                    int y,int w,int h,WINGUI_WIDGET_CALLBACK on_event,void *callback_data);
WINGUI_WIDGET* wingui_checkbox_create(WINGUI_WINDOW *parent,const TCHAR *text,int x,
                                    int y,int w,int h,WINGUI_WIDGET_CALLBACK on_event,void *callback_data);
WINGUI_WIDGET* wingui_listbox_create(WINGUI_WINDOW *parent,int x,int y,int w,int h,
                                     WINGUI_WIDGET_CALLBACK on_event,void *callback_data);
WINGUI_WIDGET* wingui_label_create(WINGUI_WINDOW *parent,const TCHAR *text,int x,int y,
                                   int w,int h,WINGUI_WIDGET_CALLBACK on_event,void *callback_data);
WINGUI_WIDGET* wingui_entry_create(WINGUI_WINDOW *parent,int x,int y,int w,int h,
                                   WINGUI_WIDGET_CALLBACK on_event,void *callback_data);
WINGUI_WIDGET* wingui_textbox_create(WINGUI_WINDOW *parent,int x,int y,int w,int h,
                                   WINGUI_WIDGET_CALLBACK on_event,void *callback_data);

int wingui_widget_get_text_length(WINGUI_WIDGET *widget);
int wingui_widget_get_text(WINGUI_WIDGET *widget,TCHAR *buf,int max_len);
bool wingui_widget_set_text(WINGUI_WIDGET *widget,TCHAR *text);
TCHAR* wingui_widget_get_text_full(WINGUI_WIDGET *widget);
bool wingui_widget_resize(WINGUI_WIDGET *widget,int w,int h);
bool wingui_widget_move(WINGUI_WIDGET *widget,int x,int y);

void wingui_checkbox_set_state(WINGUI_WIDGET *widget,bool state);
bool wingui_checkbox_get_state(WINGUI_WIDGET *widget);

bool wingui_listbox_add_elem(WINGUI_WIDGET *widget,TCHAR *elem);
bool wingui_listbox_del_index(WINGUI_WIDGET *widget,int index);
bool wingui_listbox_get_selelem(WINGUI_WIDGET *widget,TCHAR *buf);
int wingui_listbox_get_selindex(WINGUI_WIDGET *widget);
bool wingui_listbox_index2elem(WINGUI_WIDGET *widget,TCHAR *buf,int index);
int wingui_listbox_elem2index(WINGUI_WIDGET *widget,TCHAR *buf);
int wingui_listbox_get_textlen(WINGUI_WIDGET *widget,int index);
bool wingui_listbox_clear(WINGUI_WIDGET *widget);
int wingui_listbox_getlen(WINGUI_WIDGET *widget);

//Timers
UINT wingui_set_timer(WINGUI_WINDOW *window,UINT delay,WINGUI_TIMER_CALLBACK on_tick,void *callback_data);
bool wingui_delete_timer(WINGUI_WINDOW *window,UINT timer_id);
bool wingui_after(WINGUI_WINDOW *window,UINT delay,WINGUI_TIMER_CALLBACK on_tick,void *callback_data);

//Text

SIZE wingui_text_get_size(TCHAR *text,int length);
long wingui_text_get_width(TCHAR *text,int length);
long wingui_text_get_height(TCHAR *text,int length);

//Misc

void wingui_run(void);
void wingui_init(HINSTANCE hInstance);

#endif
