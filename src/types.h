
#ifndef TYPES_H__

#define TYPES_H__
#include "consts.h"

/**
 * @brief Структура для хранения информации о биндах клавиш.
 *
 * @param is_bound Флаг, указывающий, установлен ли биндинг.
 * @param app_path Путь к приложению, с которым связан биндинг.
 *
 * @note Максимальная длина пути к приложению определяется константой MAX_APP_PATH_LEN.
 */
typedef struct
{
    int is_bound;
    char app_path[MAX_APP_PATH_LEN];
} KeyBind;

#endif // TYPES_H__
