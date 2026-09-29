#include <windows.h>
#include "wingui.h"
#include "messagebox.h"

void showinfo(TCHAR *title,TCHAR *message){
    MessageBox(NULL,message,title,MB_ICONINFORMATION | MB_OK);
}

void showwarning(TCHAR *title,TCHAR *message){
    MessageBox(NULL,message,title,MB_ICONWARNING | MB_OK);
}

void showerror(TCHAR *title,TCHAR *message){
    MessageBox(NULL,message,title,MB_ICONERROR | MB_OK);
}
