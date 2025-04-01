#include "cf_loop.h"

#include <CoreFoundation/CoreFoundation.h>
#include <gtk/gtk.h>

CFRunLoopTimerRef create_cf_timer()
{
    CFRunLoopTimerContext timer_context = {0, NULL, NULL, NULL, NULL};

    return CFRunLoopTimerCreate(NULL, CFAbsoluteTimeGetCurrent(), 0.01, 0, 0, gtk_iteration, &timer_context);
}

void gtk_iteration(CFRunLoopTimerRef timer, void *info)
{
    (void)timer;
    (void)info;
    // Цикл обработки всех ожидающих событий GTK/GLib без блокировки
    while (g_main_context_iteration(NULL, FALSE))
    {
    }
}
