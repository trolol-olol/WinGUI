#include <windows.h>
#include "wingui.h"
#include "wingui_internal.h"

UINT wingui_set_timer(WINGUI_WINDOW *window,UINT delay,WINGUI_TIMER_CALLBACK on_tick,void *callback_data){
    if (window==NULL || window->hwnd==NULL || window->timers==NULL || on_tick==NULL) return 0;
    UINT timer_id=(UINT)SetTimer(window->hwnd,window->timer_ctr,delay,NULL);
    if (timer_id==0){
        return 0;
    }
    WINGUI_TIMER *timer=malloc(sizeof(WINGUI_TIMER));
    if (timer==NULL){
        KillTimer(window->hwnd,(UINT_PTR)timer_id);
        return 0;
    }
    timer->is_onetime=false;
    timer->id=timer_id;
    timer->on_tick=on_tick;
    timer->callback_data=callback_data;
    if (list_append(window->timers,timer)==-1){
        KillTimer(window->hwnd,(UINT_PTR)timer_id);
        free(timer);
        return 0;
    }
    window->timer_ctr+=1;
    return timer_id;
}

bool wingui_delete_timer(WINGUI_WINDOW *window,UINT timer_id){
    if (window==NULL || window->hwnd==NULL || window->timers==NULL || timer_id==0) return false;
    for (int x=0;x<window->timers->count;x++){
        WINGUI_TIMER *timer=list_get(window->timers,x);
        if (timer->id==timer_id){
            KillTimer(window->hwnd,timer->id);
            free(timer);
            list_remove(window->timers,x);
            return true;
        }
    }
    return false;
}

bool wingui_after(WINGUI_WINDOW *window,UINT delay,WINGUI_TIMER_CALLBACK on_tick,void *callback_data){
    if (window==NULL || window->hwnd==NULL || window->timers==NULL || on_tick==NULL) return 0;
    UINT timer_id=(UINT)SetTimer(window->hwnd,window->timer_ctr,delay,NULL);
    if (timer_id==0){
        return 0;
    }
    WINGUI_TIMER *timer=malloc(sizeof(WINGUI_TIMER));
    if (timer==NULL){
        KillTimer(window->hwnd,(UINT_PTR)timer_id);
        return 0;
    }
    timer->is_onetime=true;
    timer->id=timer_id;
    timer->on_tick=on_tick;
    timer->callback_data=callback_data;
    if (list_append(window->timers,timer)==-1){
        KillTimer(window->hwnd,(UINT_PTR)timer_id);
        free(timer);
        return 0;
    }
    window->timer_ctr+=1;
    return true;
}
