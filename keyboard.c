#include "keyboard.h"
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

    // проверяем, была ли использована клавиша Command + цифра
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
