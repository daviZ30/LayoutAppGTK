#include <gtk/gtk.h>
#include <iostream>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/listview.h>
#include <gtkmm/listitemfactory.h>
#include <gtkmm/image.h>
#include <giomm/appinfo.h>

static GtkWidget *btnHome;
static GtkWidget *btntasks;
static GtkWidget *lblHomeTitle, *imgHome;
static GtkWidget *lbltasksTitle, *imgTasks;
// funciones aparte, archivo aparte
/*static void miFuncionEstatica(GtkWidget paned)
{
    int ancho = 200;
    GtkWidget *btn1;
    GtkWidget *btn2;
    GtkWidget *boxIzq;
    GtkWidget *boxIzq2;
    GtkWidget *img;

    miFuncionEstatica(paned);

    btn1 = gtk_button_new_with_label("Home");
    btn2 = gtk_button_new_with_label("tasks");
    boxIzq = gtk_box_new(GTK_ORIENTATION_VERTICAL, 50);
    boxIzq2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 50);

    gtk_paned_set_position(GTK_PANED(paned), ancho);
    gtk_paned_set_start_child(GTK_PANED(paned), boxIzq);

    gtk_paned_set_resize_start_child(GTK_PANED(paned), false);

    img = gtk_image_new_from_file("wpf.jpg");
    gtk_box_append(GTK_BOX(boxIzq), img);
    gtk_box_append(GTK_BOX(boxIzq), boxIzq2);

    gtk_box_set_homogeneous(GTK_BOX(boxIzq2), false);

    gtk_box_append(GTK_BOX(boxIzq2), btn1);
    gtk_box_append(GTK_BOX(boxIzq2), btn2);

    gtk_image_set_pixel_size(GTK_IMAGE(img), ancho);
}*/

static void On_click_btnHome(GtkWidget *widget, gpointer box)
{
    if (lbltasksTitle != NULL || imgTasks != NULL)
    {
        gtk_box_remove(GTK_BOX(box), lbltasksTitle);
        gtk_box_remove(GTK_BOX(box), imgTasks);
    }
    // GList *mi_lista = gtk_container_get_children((widget));
    // g_print("Número de elementos en la lista: %u\n", g_list_length(mi_lista));
    if (gtk_widget_is_visible(widget) == true)
    {
        lblHomeTitle = gtk_label_new("Esto es Home");
        imgHome = gtk_image_new_from_file("resources/home.jpg");
        gtk_box_append(GTK_BOX(box), lblHomeTitle);
        gtk_box_append(GTK_BOX(box), imgHome);
        gtk_image_set_pixel_size(GTK_IMAGE(imgHome), 200);
        // gtk_box_set_baseline_child(GTK_BOX(data), 1);
    }
    gtk_widget_set_visible(widget, false);
    gtk_widget_set_visible(btntasks, true);
}
static void On_click_btnTasks(GtkWidget *widget, gpointer box)
{
    if (lblHomeTitle != NULL || imgHome != NULL)
    {
        gtk_box_remove(GTK_BOX(box), lblHomeTitle);
        gtk_box_remove(GTK_BOX(box), imgHome);
    }

    if (gtk_widget_is_visible(widget) == true)
    {

        lbltasksTitle = gtk_label_new("Esto es Tasks");
        imgTasks = gtk_image_new_from_file("resources/task.jpg");
        gtk_box_append(GTK_BOX(box), lbltasksTitle);
        gtk_box_append(GTK_BOX(box), imgTasks);
        gtk_image_set_pixel_size(GTK_IMAGE(imgTasks), 200);
        // gtk_box_set_baseline_child(GTK_BOX(data), 1);
    }
    gtk_widget_set_visible(widget, false);
    gtk_widget_set_visible(btnHome, true);
}

static void activate(GtkApplication *app, gpointer user_data)
{

    GtkWidget *window;
    window = gtk_application_window_new(app);
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 1000);
    gtk_window_set_title(GTK_WINDOW(window), "Layout");
    GtkWidget *paned, *boxDer, *boxIzq, *boxIzq2, *img, *lblTasksTitle;
    int ancho = 200;

    paned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_paned_set_resize_start_child(GTK_PANED(paned), false);
    gtk_paned_set_shrink_start_child(GTK_PANED(paned), false);
    // miFuncionEstatica(paned);

    // panel izquierdo
    btnHome = gtk_button_new_with_label("Home");

    btntasks = gtk_button_new_with_label("tasks");
    boxIzq = gtk_box_new(GTK_ORIENTATION_VERTICAL, 50);
    boxIzq2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 50);

    gtk_paned_set_position(GTK_PANED(paned), ancho);
    gtk_paned_set_start_child(GTK_PANED(paned), boxIzq);

    img = gtk_image_new_from_file("resources/wpf.jpg");
    gtk_box_append(GTK_BOX(boxIzq), img);
    gtk_box_append(GTK_BOX(boxIzq), boxIzq2);

    gtk_box_set_homogeneous(GTK_BOX(boxIzq2), true);

    gtk_box_append(GTK_BOX(boxIzq2), btnHome);
    gtk_box_append(GTK_BOX(boxIzq2), btntasks);

    gtk_image_set_pixel_size(GTK_IMAGE(img), ancho);

    // Panel derecho

    boxDer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 50);
    g_signal_connect(btnHome, "clicked", G_CALLBACK(On_click_btnHome), boxDer);
    g_signal_connect(btntasks, "clicked", G_CALLBACK(On_click_btnTasks), boxDer);
    lblTasksTitle = gtk_label_new("Esto es Tasks");

    gtk_paned_set_end_child(GTK_PANED(paned), boxDer);
    gtk_box_set_homogeneous(GTK_BOX(boxDer), true);

    gtk_window_set_child(GTK_WINDOW(window), paned);
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv)
{
    GtkApplication *app;
    int status;
   // GtkSelectionModel *model = create_application_list();
    GtkListItemFactory *factory = gtk_signal_list_item_factory_new();

    app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}