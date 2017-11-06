#include <gtk/gtk.h>
#include <math.h>
#include <cairo.h>

#define WIDTH   640
#define HEIGHT  480

#define ZOOM_X  100.0
#define ZOOM_Y  100.0


gfloat f (gfloat x)
{
    return 0.03 * pow (x, 3);
}

static gboolean
on_expose_event (GtkWidget *widget, GdkEventExpose *event, gpointer user_data)
{
    cairo_t *cr = gdk_cairo_create (widget->window);
    GdkRectangle da;            /* GtkDrawingArea size */
    gdouble dx = 5.0, dy = 5.0; /* Pixels between each point */
    gdouble i, clip_x1 = 0.0, clip_y1 = 0.0, clip_x2 = 0.0, clip_y2 = 0.0;
    gint unused = 0;

    /* Define a clipping zone to improve performance */
    cairo_rectangle (cr,
            event->area.x,
            event->area.y,
            event->area.width,
            event->area.height);
    cairo_clip (cr);

    /* Determine GtkDrawingArea dimensions */
    gdk_window_get_geometry (widget->window,
            &da.x,
            &da.y,
            &da.width,
            &da.height,
            &unused);

    /* Draw on a black background */
    cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
    cairo_paint (cr);

    /* Change the transformation matrix */
    cairo_translate (cr, da.width / 2, da.height / 2);
    cairo_scale (cr, ZOOM_X, -ZOOM_Y);

    /* Determine the data points to calculate (ie. those in the clipping zone */
    cairo_device_to_user_distance (cr, &dx, &dy);
    cairo_clip_extents (cr, &clip_x1, &clip_y1, &clip_x2, &clip_y2);
    cairo_set_line_width (cr, dx);

    /* Draws x and y axis */
    cairo_set_source_rgb (cr, 0.0, 1.0, 0.0);
    cairo_move_to (cr, clip_x1, 0.0);
    cairo_line_to (cr, clip_x2, 0.0);
    cairo_move_to (cr, 0.0, clip_y1);
    cairo_line_to (cr, 0.0, clip_y2);
    cairo_stroke (cr);

    /* Link each data point */
    for (i = clip_x1; i < clip_x2; i += dx)
        cairo_line_to (cr, i, f (i));

    /* Draw the curve */
    cairo_set_source_rgba (cr, 1, 0.2, 0.2, 0.6);
    cairo_stroke (cr);

    cairo_destroy (cr);
    return FALSE;
}


int
main (int argc, char **argv)
{
    GtkWidget *window;
    GtkWidget *da;

    gtk_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size (GTK_WINDOW (window), WIDTH, HEIGHT);
    gtk_window_set_title (GTK_WINDOW (window), "Graph drawing");
    g_signal_connect (G_OBJECT (window), "destroy", gtk_main_quit, NULL);

    da = gtk_drawing_area_new ();
    gtk_container_add (GTK_CONTAINER (window), da);

    g_signal_connect (G_OBJECT (da),
            "expose-event",
            G_CALLBACK (on_expose_event),
            NULL);

    gtk_widget_show_all (window);
    gtk_main ();

    return 0;
}
