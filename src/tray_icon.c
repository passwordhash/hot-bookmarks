#include "consts.h"
#include "glib.h"
#include "keyboard.h"
#include "logger.h"
#include "types.h"
#include <gtk/gtk.h>
#include <signal.h>

static GtkStatusIcon *status_icon = NULL;
static GtkWidget *popup_menu = NULL;
static GtkApplication *global_app = NULL;

static void status_icon_activate(GtkStatusIcon *status_icon, gpointer user_data)
{
    (void)status_icon;
    (void)user_data;
    log_info("Клик по иконке в трее");
}

void init_tray_icon(GtkApplication *app)
{
    log_info("Инициализация иконки в трее");

    global_app = app;

    status_icon = gtk_status_icon_get_icon_name("hot-bookmarks");
    gtk_status_icon_set_title(status_icon, "Hot Bookmarks");

    gtk_status_icon_set_visible(status_icon, TRUE);

    log_info("Иконка в трее инициализирована");
}