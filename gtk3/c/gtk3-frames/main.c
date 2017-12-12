#include <gtk/gtk.h>

#define MAX_FRAMES 5

typedef struct
{
    GtkWidget *image;
    GdkPixbuf *pixbufs[MAX_FRAMES];
    int n_frame;
} AppData;

gboolean on_timeout(gpointer user_data)
{
    AppData *appdata = user_data;

    /* Load the image if it's not in our image cache */
    if (appdata->pixbufs[appdata->n_frame] == NULL)
    {
        GError *error = NULL;
        char *frame_path = g_strdup_printf ("%d.png", appdata->n_frame);
        appdata->pixbufs[appdata->n_frame] = gdk_pixbuf_new_from_file(frame_path, &error);
        g_free (frame_path);

        /* Trigger a fatal error if an image is not found */
        if (error)
        {
            g_error ("%s", error->message);
            g_error_free (error);
        }
    }

    gtk_image_set_from_pixbuf (GTK_IMAGE (appdata->image),
            appdata->pixbufs[appdata->n_frame]);

    appdata->n_frame = (appdata->n_frame + 1) % MAX_FRAMES;

    return G_SOURCE_CONTINUE;
}

int main (int argc, char **argv)
{
    gtk_init (&argc, &argv);

    AppData *appdata = g_new0(AppData, 1);

    /* Create the user interface */
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *image  = appdata->image = gtk_image_new();
    gtk_container_add(GTK_CONTAINER (window), image);
    gtk_widget_show_all(window);

    /* Connect signals and add event sources */
    g_timeout_add_seconds (1,  on_timeout, appdata);
    g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (gtk_main_quit), NULL);

    gtk_main();

    g_free(appdata);

    return 0;
}
