#include <gtk/gtk.h>

int main (int argc, char **argv)
{
    gtk_init (&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *label = gtk_label_new("Hello World!");

    gtk_window_set_title (GTK_WINDOW (window), "Hello World app");
    gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);
    gtk_container_add (GTK_CONTAINER (window), label);
    gtk_widget_show_all (window);

    g_signal_connect(window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

    gtk_main();

    return 0;
}
