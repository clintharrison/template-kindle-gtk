#include <gtk-2.0/gtk/gtk.h>
#include <iostream>
#include <thread>
#include "main.ui.xml.h"

void on_button_quit()
{
  g_print("Quit button clicked, goodbye!\n");
  gtk_main_quit();
}

GtkBuilder *gtk_builder_new_from_embedded_file(const char *data, size_t size)
{
  GError *err = NULL;
  GtkBuilder *builder = gtk_builder_new();
  gtk_builder_add_from_string(builder, data, size, &err);
  if (err)
  {
    g_printerr("gtk_builder_add_from_string(): %s\n", err->message);
    g_clear_error(&err);
    return NULL;
  }
  return builder;
}

int main(int argc, char *argv[])
{
  gtk_init(&argc, &argv);

  GtkBuilder *builder = gtk_builder_new_from_embedded_file(reinterpret_cast<const char *>(MAIN_UI_XML), MAIN_UI_XML_LEN);
  if (!builder)
  {
    g_printerr("gtk_builder_new_from_embedded_file() failed\n");
    return 1;
  }
  gtk_builder_connect_signals(builder, NULL);

  GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
  GtkWidget *button_quit = GTK_WIDGET(gtk_builder_get_object(builder, "title_button_left"));

  // Exit the application when the main window is closed
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  // Also exit when the quit button is clicked
  g_signal_connect(button_quit, "button-press-event", G_CALLBACK(on_button_quit), nullptr);

  // Set the background color to white: this looks a little better on the Kindle screen
  GdkColor color;
  if (gdk_color_parse("#ffffff", &color))
  {
    gtk_widget_modify_bg(window, GTK_STATE_NORMAL, &color);
  }

  gtk_widget_show(window);

  gtk_main();

  return 0;
}
