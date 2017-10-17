 
 
#include <gtk/gtk.h>
 
static void create_win32_native_file_chooser(GtkWidget *widget, gpointer user_data)  ;
 
static void create_win32_native_file_chooser(GtkWidget *widget, gpointer user_data) {
 
  GtkWidget *window = gtk_widget_get_toplevel(widget) ;
 
  GtkFileChooserNative *win32_native_file_chooser = gtk_file_chooser_native_new("title", 
                                                   GTK_WINDOW(window), 
                                                  GTK_FILE_CHOOSER_ACTION_SAVE, // C'est ça qui bug.
                                                  "accept label",
                                                  "cancel label") ; 
 
  gtk_native_dialog_show(GTK_NATIVE_DIALOG(win32_native_file_chooser)) ;
}
 
 
int main (int argc, char *argv[]) {
 
  gtk_init(&argc, &argv) ;
 
  GtkWidget *window, *button ;
 
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL) ;
 
  button= gtk_button_new_with_label("test") ;
 
  g_signal_connect(button, "clicked", G_CALLBACK(create_win32_native_file_chooser) , NULL);
 
  gtk_container_add(GTK_CONTAINER(window), button) ;
  gtk_widget_show_all(window);
 
  gtk_main() ;
 
  return 0 ;
}
