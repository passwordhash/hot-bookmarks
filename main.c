/** @note
 * Это стандартная библиотека Apple, объединяющая несколько API для macOS,
 * включая Quartz Event Services для обработки глобальных событий клавиатуры и
 * мыши.
 */
#include <ApplicationServices/ApplicationServices.h>
#include <stdio.h>

#define STR_LEN 10

CGEventRef keyboard_callback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon)
{
    (void)proxy;

    if (type != kCGEventKeyDown)
    {
        return event;
    }

    // получаем нажатую клавишу и флаги
    CGEventFlags flags = CGEventGetFlags(event);
    UniChar pressed_str[STR_LEN];
    UniCharCount pressed_str_len;
    CGEventKeyboardGetUnicodeString(event, STR_LEN, &pressed_str_len, pressed_str);

    // проверяем, была ли использована клавиша Comand + цифра
    if (flags & kCGEventFlagMaskCommand)
    {
        if (pressed_str_len == 1 && pressed_str[0] >= '0' && pressed_str[0] <= '9')
        {
            printf("command + %c pressed!\n", pressed_str[0]);
            fflush(stdout);
        }
    }

    return event;
}

int main(void)
{
    // создаем event tap для прослушивания клавиатуры (точка перехвата глобальных событий)
    CFMachPortRef event_tap = CGEventTapCreate(kCGSessionEventTap, kCGHeadInsertEventTap, kCGEventTapOptionDefault,
                                               CGEventMaskBit(kCGEventKeyDown), keyboard_callback, NULL);

    // добавляем источник событий в run loop
    CFRunLoopSourceRef run_loop_source = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, event_tap, 0); // связывает наш Event Tap с системным циклом обработки событий
    CFRunLoopAddSource(CFRunLoopGetCurrent(), run_loop_source, kCFRunLoopCommonModes);
    CGEventTapEnable(event_tap, true);

    CFRunLoopRun();

    return 0;
}
