#include <gtk/gtk.h>

static void on_button_clicked(GtkButton *button, gpointer user_data) {
    g_print("Button clicked!\n");
}

// Function to create a button
GtkWidget *create_rect_button(const char *label_text) {
    // Create the button
    GtkWidget *button = gtk_button_new_with_label(label_text);

    // Give it a name for CSS styling
    gtk_widget_set_name(button, "rect_button");

    // Create CSS provider
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_string(provider,
        "#rect_button {"
        "  border-radius: 2px;"
        "  border: 1px solid black;"
        "  background-color: #f0f0f0;"
        "  padding: 2px 2px;"
        "}"
        , -1);

    // Apply CSS to default display
    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );

    g_object_unref(provider); // Free provider

    return button;
}


static void activate(GtkApplication *app, gpointer user_data) {
    // Creating the main window
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Music Player");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

    // Creating a button with a label
    GtkWidget *button = create_rect_button("Click Me");

    // Connect the clicked signal to the callback function
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);

    // Add the button to the window
    gtk_window_set_child(GTK_WINDOW(window), button);

    // Showing the window
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("com.example.GtkApp", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
