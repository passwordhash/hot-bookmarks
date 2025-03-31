#include "keyboard.h"
#include "logger.h"
/** @note
 * Это стандартная библиотека Apple, объединяющая несколько API для macOS,
 * включая Quartz Event Services для обработки глобальных событий клавиатуры и
 * мыши.
 */
#include <ApplicationServices/ApplicationServices.h>
#include <stdio.h>

#define STR_LEN 10

int main(void)
{
    log_info("Запуск программы...");

    // создаем event tap для прослушивания клавиатуры (точка перехвата глобальных событий)
    CFMachPortRef event_tap = CGEventTapCreate(kCGSessionEventTap, kCGHeadInsertEventTap, kCGEventTapOptionDefault,
                                               CGEventMaskBit(kCGEventKeyDown), keyboard_callback, NULL);

    // добавляем источник событий в run loop
    CFRunLoopSourceRef run_loop_source =
        CFMachPortCreateRunLoopSource(kCFAllocatorDefault, event_tap, 0); // связывает наш Event Tap с системным циклом обработки событий
    CFRunLoopAddSource(CFRunLoopGetCurrent(), run_loop_source, kCFRunLoopCommonModes);
    CGEventTapEnable(event_tap, true);

    CFRunLoopRun();

    return 0;
}
