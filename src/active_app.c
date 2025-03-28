#include "active_app.h"
#include "logger.h"
#include <stdio.h>
#include <string.h>

#define APPLE_SCRIPT_CMD                                                                                                                   \
    "osascript -e 'tell application \"System Events\" to POSIX path of (application file of first process whose frontmost is true)'"

void get_active_app_path(char *path_buf, size_t buf_size)
{
    // запускает новый процесс с указанной командой и открывает канал для чтения
    FILE *fp = popen(APPLE_SCRIPT_CMD, "r");
    if (!fp)
    {
        log_error("Не удалось выполнить AppleScript для получения активного приложения");
        strncpy(path_buf, "", buf_size);
        return;
    }

    fgets(path_buf, buf_size, fp);

    path_buf[strcspn(path_buf, "\n")] = '\0';
    
    pclose(fp);
}
