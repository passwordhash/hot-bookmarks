#include "gtk_app.h"

#include <CoreFoundation/CoreFoundation.h>
#include <gtk/gtk.h>

// TODO: move to const
#define GUI_MAIN_WINDOW_TITLE "🔥Hot Bookmarks"

void on_activate(GtkApplication *app, gpointer user_data)
{
    (void)user_data;
    GtkWidget *widget_window = gtk_application_window_new(GTK_APPLICATION(app));
    GtkWindow *window = GTK_WINDOW(widget_window);
    gtk_window_set_title(window, GUI_MAIN_WINDOW_TITLE);
    gtk_window_set_default_size(window, 400, 400);

    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), NULL);

    gtk_widget_show(widget_window);
}

void on_window_destroy(GtkWidget *window, gpointer data)
{
    (void)window;
    (void)data;
    CFRunLoopStop(CFRunLoopGetCurrent());
}
