#include <gtk/gtk.h>

static void on_save (GtkWidget *widget, gpointer user_data) {
    GtkWidget *window = gtk_widget_get_toplevel(widget);
    GtkFileChooserNative *win32_native_file_chooser = \
        gtk_file_chooser_native_new("Enregistrer",
        GTK_WINDOW(window),
        GTK_FILE_CHOOSER_ACTION_SAVE,
        "Enregistrer",
        "Annuler");

    gtk_native_dialog_show(GTK_NATIVE_DIALOG(win32_native_file_chooser));
}

static void on_open (GtkWidget *widget, gpointer user_data) {
    GtkWidget *window = gtk_widget_get_toplevel(widget);
    GtkFileChooserNative *win32_native_file_chooser = \
        gtk_file_chooser_native_new("Ouvrir",
        GTK_WINDOW(window),
        GTK_FILE_CHOOSER_ACTION_SAVE,
        "Ouvrir",
        "Annuler");

    gtk_native_dialog_show(GTK_NATIVE_DIALOG(win32_native_file_chooser));
}


int main (int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *grid = gtk_grid_new();
    GtkWidget *save_button = gtk_button_new_with_label("Enregistrer");
    GtkWidget *open_button = gtk_button_new_with_label("Ouvrir");

    gtk_grid_attach(GTK_GRID(grid), save_button, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), open_button, 1, 0, 1, 1);

    g_signal_connect(save_button, "clicked", G_CALLBACK(on_save), NULL);
    g_signal_connect(open_button, "clicked", G_CALLBACK(on_open), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_container_add(GTK_CONTAINER(window), grid);
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
