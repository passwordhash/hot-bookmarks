#include "cf_loop.h"
#include "gtk_app.h"
#include "keyboard.h"
#include "logger.h"
/** @note
 * Это стандартная библиотека Apple, объединяющая несколько API для macOS,
 * включая Quartz Event Services для обработки глобальных событий клавиатуры и
 * мыши.
 */
#include <ApplicationServices/ApplicationServices.h>
#include <CoreFoundation/CoreFoundation.h>
#include <gtk/gtk.h>
#include <stdio.h>

#define STR_LEN 10

int main(void)
{
    log_info("Запуск программы...");

    GtkApplication *app = gtk_application_new("com.passwordhash.hot-bookmarks", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);

    CFRunLoopTimerRef timer = create_cf_timer();
    CFRunLoopAddTimer(CFRunLoopGetCurrent(), timer, kCFRunLoopDefaultMode);

    // создаем event tap для прослушивания клавиатуры (точка перехвата глобальных событий)
    CFMachPortRef event_tap = CGEventTapCreate(kCGSessionEventTap, kCGHeadInsertEventTap, kCGEventTapOptionDefault,
                                               CGEventMaskBit(kCGEventKeyDown), keyboard_callback, NULL);

    // добавляем источник событий в run loop
    CFRunLoopSourceRef run_loop_source =
        CFMachPortCreateRunLoopSource(kCFAllocatorDefault, event_tap, 0); // связывает наш Event Tap с системным циклом обработки событий
    CFRunLoopAddSource(CFRunLoopGetCurrent(), run_loop_source, kCFRunLoopCommonModes);
    CGEventTapEnable(event_tap, true);

    int status = g_application_run(G_APPLICATION(app), 0, NULL);

    CFRelease(timer);
    g_object_unref(app);

    CFRunLoopRun();

    return status;
}
