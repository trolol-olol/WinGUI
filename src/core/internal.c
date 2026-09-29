#include <windows.h>
#include "wingui.h"
#include "wingui_internal.h"

static HINSTANCE g_wingui_instance=NULL;

static WINGUI_EVENT_TYPE wingui_internal_code2event_btn(int code){
    WINGUI_EVENT_TYPE event_type;
    switch (code){
        case BN_CLICKED: event_type=CLICK;break;
        case BN_DBLCLK: event_type=DBLCLICK;break;
        case BN_DISABLE: event_type=DISABLE;break;
        case BN_KILLFOCUS: event_type=KILLFOCUS;break;
        case BN_SETFOCUS: event_type=SETFOCUS;break;
        default: event_type=OTHER;
    }
    return event_type;
}

static WINGUI_EVENT_TYPE wingui_internal_code2event_stat(int code){
    WINGUI_EVENT_TYPE event_type;
    switch (code){
        case STN_CLICKED: event_type=CLICK;break;
        case STN_DBLCLK: event_type=DBLCLICK;break;
        case STN_DISABLE: event_type=DISABLE;break;
        case STN_ENABLE: event_type=ENABLE;break;
        default: event_type=OTHER;
    }
    return event_type;
}

static WINGUI_EVENT_TYPE wingui_internal_code2event_edit(int code){
    WINGUI_EVENT_TYPE event_type;
    switch (code){
        case EN_CHANGE: event_type=CHANGE;break;
        case EN_KILLFOCUS: event_type=KILLFOCUS;break;
        case EN_MAXTEXT: event_type=MAXTEXT;break;
        case EN_SETFOCUS: event_type=SETFOCUS;break;
        default: event_type=OTHER;
    }
    return event_type;
}

static WINGUI_EVENT_TYPE wingui_internal_code2event_lbox(int code){
    WINGUI_EVENT_TYPE event_type;
    switch (code){
        case LBN_DBLCLK: event_type=DBLCLICK;break;
        case LBN_KILLFOCUS: event_type=KILLFOCUS;break;
        case LBN_SELCANCEL: event_type=CANCEL;break;
        case LBN_SELCHANGE: event_type=SELECT;break;
        case LBN_SETFOCUS: event_type=SETFOCUS;break;
        default: event_type=OTHER;
    }
    return event_type;
}



void wingui_internal_set_instance(HINSTANCE inst){
    g_wingui_instance=inst;
}

HINSTANCE wingui_internal_get_instance(){
    return g_wingui_instance;
}

WINGUI_EVENT_TYPE wingui_internal_code2event(int code,WINGUI_WIDGET_TYPE type){
    WINGUI_EVENT_TYPE event_type;
    switch (type){
        case BUTTON: event_type=wingui_internal_code2event_btn(code);break;
        case CHECKBOX: event_type=wingui_internal_code2event_btn(code);break;
        case LABEL: event_type=wingui_internal_code2event_stat(code);break;
        case ENTRY: event_type=wingui_internal_code2event_edit(code);break;
        case LISTBOX: event_type=wingui_internal_code2event_lbox(code);break;
        default: event_type=OTHER;
    }
    return event_type;
}

WINGUI_WIDGET* wingui_internal_id2widget(WINGUI_WINDOW *window,int id){
    if (window==NULL || window->widgets==NULL) return NULL;
    for (int i=0;i<window->widgets->count;i++){
        WINGUI_WIDGET *widget=list_get(window->widgets,i);
        if (widget->id==(HMENU)id){
            return widget;
        }
    }
    return NULL;
}

WINGUI_TIMER* wingui_internal_id2timer(WINGUI_WINDOW *window,UINT timer_id){
    if (window==NULL || window->timers==NULL) return NULL;
    for (int i=0;i<window->timers->count;i++){
        WINGUI_TIMER *timer=list_get(window->timers,i);
        if (timer->id==timer_id){
            return timer;
        }
    }
    return NULL;
}
