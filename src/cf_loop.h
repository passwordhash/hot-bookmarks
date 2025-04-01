#ifndef CF_LOOP_H__
#define CF_LOOP_H__

#include <CoreFoundation/CoreFoundation.h>

/**
 * @brief Создание таймера для запуска gtk_main_iteration
 * @return Таймер
 */
CFRunLoopTimerRef create_cf_timer(void);

/**
 *@brief Функция обратного вызова для таймера
 *@param[in] timer Таймер
 *@param[in] info Указатель на данные, переданные в таймер
 */
void gtk_iteration(CFRunLoopTimerRef timer, void *info);

#endif // CF_LOOP_H__
