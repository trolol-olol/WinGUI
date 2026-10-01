#include <windows.h>
#include "wingui.h"
#include "wingui_internal.h"
#include "utils.h"

extern int g_wingui_windows;

void wingui_quit(void);

WINGUI_WINDOW* wingui_window_create(const TCHAR *title,int width,int height){
    HWND hwnd=CreateWindow(TEXT("WinGUIWindowClass"),
                           title,
                           WS_OVERLAPPEDWINDOW,
                           CW_USEDEFAULT,CW_USEDEFAULT,
                           width,height,
                           NULL,NULL,wingui_internal_get_instance(),NULL);
    if (hwnd==NULL) return NULL;
    WINGUI_WINDOW *window=malloc(sizeof(WINGUI_WINDOW));
    if (window==NULL) return NULL;
    List *widgets=list_create(16);
    if (widgets==NULL) {
        free(window);
        return NULL;
    }
    List *timers=list_create(8);
    if (timers==NULL){
        free(window);
        list_free(widgets);
        return NULL;
    }

    window->hwnd=hwnd;
    window->title=title;
    window->widgets=widgets;
    window->timers=timers;
    window->widget_ctr=1;
    window->timer_ctr=1;
    window->on_close=NULL;
    window->on_close_data=NULL;

    SetWindowLongPtr(hwnd,GWLP_USERDATA,(LONG_PTR)window);

    g_wingui_windows++;
    wingui_label_create(window,TEXT(""),0,0,width,height,NULL,NULL);
    return window;
}

void wingui_window_show(WINGUI_WINDOW *window,int type){
    if (window==NULL || window->hwnd==NULL) return;
    ShowWindow(window->hwnd,type);
}

void wingui_window_destroy(WINGUI_WINDOW *window) {
    if (window==NULL || window->hwnd==NULL) return;

    if (window->widgets) {
        for (int i=0;i<window->widgets->count;i++) {
            WINGUI_WIDGET *w=window->widgets->items[i];
            if (w){
                free(w);
            }
        }
        list_free(window->widgets);
    }
    if (window->timers){
        for (int i=0;i<window->timers->count;i++){
            WINGUI_TIMER *t=window->timers->items[i];
            if (t){
                KillTimer(window->hwnd,t->id);
                free(t);
            }
        }
        list_free(window->timers);
    }

    free(window);
    g_wingui_windows--;
    if (g_wingui_windows==0) wingui_quit();
}
