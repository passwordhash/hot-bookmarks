#include "keyboard.h"
#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define MAX_APP_PATH_LEN 512
#define MAX_CMD_LEN 1024

#define STR_LEN 10
#define MAX_BINDS 10

typedef struct
{
    int is_bound;                    // есть ли bind для цифры
    char app_path[MAX_APP_PATH_LEN]; // путь к приложению или идентификатор окна
} KeyBind;

KeyBind binds[MAX_BINDS] = {0};

typedef enum
{
    MODE_NORMAL,
    MODE_BIND_ADD,
    MODE_BIND_REMOVE
} AppMode;

AppMode current_mode = MODE_NORMAL;

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

    // проверяем, была ли использована клавиша Command
    if (!(flags & kCGEventFlagMaskCommand) || pressed_str_len != 1)
    {
        return event;
    }

    char pressed = pressed_str[0];

    if (pressed == '=')
    {
        current_mode = MODE_BIND_ADD;
        log_debug("Включен мод добавления бинда");
        return event;
    }

    if (pressed == '-')
    {
        current_mode = MODE_BIND_REMOVE;
        log_debug("Включен мод удаления бинда");
        return event;
    }

    if (pressed >= '0' && pressed <= '9')
    {
        int index = pressed - '0';

        if (current_mode == MODE_BIND_ADD)
        {
            // для теста добавляем калькулятор
            char app_to_bind[MAX_APP_PATH_LEN] = "/Applications/Cdye.app";
            strcpy(binds[index].app_path, app_to_bind);
            binds[index].is_bound = 1;
            log_message(LOG_INFO, "Добавлен биндинг");
        }
        else if (current_mode == MODE_BIND_REMOVE)
        {
            binds[index].is_bound = 0;
            binds[index].app_path[0] = '\0';
            log_debug("Удален биндинг");
        }
        else if (current_mode == MODE_NORMAL && binds[index].is_bound)
        {
            char cmd[MAX_CMD_LEN];

            snprintf(cmd, MAX_CMD_LEN, "open \"%s\" >> %s 2>&1", binds[index].app_path, LOG_FILENAME);
            int cmd_res = system(cmd);

            if (cmd_res != 0)
            {
                log_error("Ошибка при запуске приложения");
            }

            log_message(LOG_INFO, "Запущено приложение");
        }

        current_mode = MODE_NORMAL;
    }

    return event;
}
