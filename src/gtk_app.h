#ifndef GTK_APP_H__
#define GTK_APP_H__

#include <gtk/gtk.h>

/**
 * @brief Функция, которая вызывается при активации приложения.
 * @param[in] app Указатель на приложение.
 * @param[in] user_data Указатель на пользовательские данные.
 */
void on_activate(GtkApplication *app, gpointer user_data);

/**
 * @brief Функция, которая вызывается при создании нового окна приложения.
 * @param[in] windget Указатель на созданное окно.
 */
void on_window_destroy(GtkWidget *widget, gpointer user_data);

#endif // GTK_APP_H__