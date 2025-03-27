#ifndef LOGGER_H__

typedef enum
{
    LOG_DEBUG,
    LOG_INFO,
    LOG_ERROR
} LogLevel;

void log_message(LogLevel level, const char *message);

#define log_debug(msg) log_message(LOG_DEBUG, msg)
#define log_info(msg) log_message(LOG_INFO, msg)
#define log_error(msg) log_message(LOG_ERROR, msg)

#endif // LOGGER_H__