#include "logger.h"
#include <stdio.h>
#include <time.h>

#define LOG_FILENAME "keybinder.log"

void log_message(LogLevel level, const char *message)
{
    const char *level_str;

    switch (level)
    {
        case LOG_DEBUG:
            level_str = "DEBUG";
            break;
        case LOG_INFO:
            level_str = "INFO";
            break;
        case LOG_ERROR:
            level_str = "ERROR";
            break;
        default:
            level_str = "UNKNOWN";
            break;
    }

    FILE *log_file = fopen(LOG_FILENAME, "a");
    if (!log_file)
    {
        printf("ошибка открытия файла логов\n");
        return;
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    char timebuf[64];
    strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", t);

    fprintf(log_file, "[%s][%s]: %s\n", timebuf, level_str, message);

    fflush(log_file);
    fclose(log_file);
}
