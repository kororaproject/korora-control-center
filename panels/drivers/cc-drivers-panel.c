/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*-
 *
 * Copyright (C) 2010 Red Hat, Inc
 * Copyright (C) 2011 Richard Hughes <richard@hughsie.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 */

#include <config.h>

#include <glib/gi18n.h>
#include <gtk/gtk.h>
#include <gdk/gdkx.h>

#include "cc-drivers-panel.h"

#define WID(b, w) (GtkWidget *) gtk_builder_get_object (b, w)

G_DEFINE_DYNAMIC_TYPE (CcDriversPanel, cc_drivers_panel, CC_TYPE_PANEL)

#define DRIVERS_PANEL_PRIVATE(o) \
  (G_TYPE_INSTANCE_GET_PRIVATE ((o), CC_TYPE_DRIVERS_PANEL, CcDriversPanelPrivate))

struct _CcDriversPanelPrivate
{
  GCancellable  *cancellable;
  GDBusProxy    *proxy;
  GSettings     *settings;
  GtkBuilder    *builder;
  GtkTreeStore  *list_store_devices;
  GtkWidget     *main_window;
};

enum {
  GCM_PREFS_COLUMN_DEVICE_PATH,
  GCM_PREFS_COLUMN_SORT,
  GCM_PREFS_COLUMN_ICON,
  GCM_PREFS_COLUMN_TITLE,
  GCM_PREFS_COLUMN_STATUS,
  GCM_PREFS_COLUMN_STATUS_IMAGE,
  GCM_PREFS_COLUMN_TOOLTIP,
  GCM_PREFS_COLUMN_RADIO_ACTIVE,
  GCM_PREFS_COLUMN_RADIO_VISIBLE,
  GCM_PREFS_COLUMN_NUM_COLUMNS
};

enum {
  GCM_PREFS_COMBO_COLUMN_TEXT,
  GCM_PREFS_COMBO_COLUMN_PROFILE,
  GCM_PREFS_COMBO_COLUMN_TYPE,
  GCM_PREFS_COMBO_COLUMN_NUM_COLUMNS
};

typedef enum {
  GCM_PREFS_ENTRY_TYPE_PROFILE,
  GCM_PREFS_ENTRY_TYPE_IMPORT
} GcmPrefsEntryType;

#define GCM_SETTINGS_SCHEMA     "org.gnome.settings-daemon.plugins.color"

/* max number of devices and profiles to cause auto-expand at startup */
#define GCM_PREFS_MAX_DEVICES_PROFILES_EXPANDED         5

static void     gcm_prefs_device_add_cb (GtkWidget *widget, CcDriversPanel *prefs);

static void
gcm_prefs_combobox_add_profile (GtkWidget *widget,
                                GcmPrefsEntryType entry_type,
                                GtkTreeIter *iter)
{

}

static void
gcm_prefs_default_cb (GtkWidget *widget, CcDriversPanel *prefs)
{
}

static void
gcm_prefs_treeview_popup_menu (CcDriversPanel *prefs, GtkWidget *treeview)
{
}

static gboolean
gcm_prefs_treeview_popup_menu_cb (GtkWidget *treeview, CcDriversPanel *prefs)
{
}

static void
gcm_prefs_calibrate_cb (GtkWidget *widget, CcDriversPanel *prefs)
{
}

static void
gcm_prefs_device_add_cb (GtkWidget *widget, CcDriversPanel *prefs)
{
}

static gboolean
gcm_prefs_is_profile_suitable_for_device ()
{
}

static gint
gcm_prefs_combo_sort_func_cb (GtkTreeModel *model,
                              GtkTreeIter *a,
                              GtkTreeIter *b,
                              gpointer user_data)
{
}

static gboolean
gcm_prefs_combo_set_default_cb (gpointer user_data)
{
}

static gboolean
gcm_prefs_profile_exists_in_array (GPtrArray *array)
{
}

static void
gcm_prefs_add_profiles_suitable_for_devices (CcDriversPanel *prefs,
                                             GtkWidget *widget,
                                             GPtrArray *profiles)
{
}

static void
gcm_prefs_profile_add_cb (GtkWidget *widget, CcDriversPanel *prefs)
{
}

static void
gcm_prefs_profile_remove_cb (GtkWidget *widget, CcDriversPanel *prefs)
{
}

static void
gcm_prefs_make_profile_default_cb (GObject *object,
                                   GAsyncResult *res,
                                   gpointer user_data)
{
}

static void
gcm_prefs_profile_make_default_internal (CcDriversPanel *prefs,
                                         GtkTreeModel *model,
                                         GtkTreeIter *iter_selected)
{
}

static void
gcm_prefs_profile_view_cb (GtkWidget *widget, CcDriversPanel *prefs)
{
}

static void
gcm_prefs_button_assign_cancel_cb (GtkWidget *widget, CcDriversPanel *prefs)
{
}

static void
gcm_prefs_button_assign_ok_cb (GtkWidget *widget, CcDriversPanel *prefs)
{
}

static gboolean
gcm_prefs_profile_delete_event_cb (GtkWidget *widget,
                                   GdkEvent *event,
                                   CcDriversPanel *prefs)
{
}

static void
gcm_prefs_delete_cb (GtkWidget *widget, CcDriversPanel *prefs)
{
}

static void
gcm_prefs_treeview_renderer_toggled (GtkCellRendererToggle *cell,
                                     const gchar *path, CcDriversPanel *prefs)
{
}

static void
gcm_prefs_add_devices_columns (CcDriversPanel *prefs,
                               GtkTreeView *treeview)
{
}

static void
gcm_prefs_set_calibrate_button_sensitivity (CcDriversPanel *prefs)
{
}

static void
gcm_prefs_device_clicked (CcDriversPanel *prefs)
{
}

static void
gcm_prefs_profile_clicked (CcDriversPanel *prefs)
{
}

static void
gcm_prefs_devices_treeview_clicked_cb (GtkTreeSelection *selection,
                                       CcDriversPanel *prefs)
{
}

static void
gcm_prefs_treeview_row_activated_cb (GtkTreeView *tree_view,
                                     GtkTreePath *path,
                                     GtkTreeViewColumn *column,
                                     CcDriversPanel *prefs)
{
}

static void
gcm_prefs_set_combo_simple_text (GtkWidget *combo_box)
{
}

static void
gcm_prefs_profile_combo_changed_cb (GtkWidget *widget,
                                    CcDriversPanel *prefs)
{
}

static void
gcm_prefs_client_sensor_changed_cb (CcDriversPanel *prefs)
{
}

static gchar *
gcm_prefs_get_profile_created_for_sort ()
{

}

static gchar *
gcm_prefs_get_profile_title (CcDriversPanel *prefs)
{
}

static void
gcm_prefs_device_remove_profiles_phase1 (CcDriversPanel *prefs, GtkTreeIter *parent)
{
}

static void
gcm_prefs_device_remove_profiles_phase2 (CcDriversPanel *prefs, GtkTreeIter *parent)
{
}

static GtkTreeIter *
get_iter_for_profile (GtkTreeModel *model, GtkTreeIter *parent)
{
}

static void
gcm_prefs_device_set_model_by_iter (CcDriversPanel *prefs, GtkTreeIter *iter)
{
}

static void
gcm_prefs_device_changed_cb (CcDriversPanel *prefs)
{
}

static void
gcm_prefs_add_device (CcDriversPanel *prefs)
{
}

static void
gcm_prefs_remove_device (CcDriversPanel *prefs)
{
}

static void
gcm_prefs_update_device_list_extra_entry (CcDriversPanel *prefs)
{
}

static void
gcm_prefs_device_added_cb (CcDriversPanel *prefs)
{
}

static void
gcm_prefs_changed_cb (CcDriversPanel *prefs)
{
  g_debug ("changed: (doing nothing)");
}

static void
gcm_prefs_device_removed_cb (CcDriversPanel *prefs)
{
}

static gboolean
gcm_prefs_tree_model_count_cb (GtkTreeModel *model,
                               GtkTreePath *path,
                               GtkTreeIter *iter,
                               gpointer user_data)
{
}

static void
gcm_prefs_get_devices_cb (GObject *object,
                          GAsyncResult *res,
                          gpointer user_data)
{
}

static void
gcm_prefs_button_virtual_add_cb (GtkWidget *widget, CcDriversPanel *prefs)
{
}

static void
gcm_prefs_button_virtual_cancel_cb (GtkWidget *widget, CcDriversPanel *prefs)
{
}

static gboolean
gcm_prefs_virtual_delete_event_cb (GtkWidget *widget,
                                   GdkEvent *event,
                                   CcDriversPanel *prefs)
{
}

static void
gcm_prefs_setup_virtual_combobox (GtkWidget *widget)
{
}

static gboolean
gcm_prefs_virtual_set_from_file (CcDriversPanel *prefs, GFile *file)
{
}

static void
gcm_prefs_virtual_drag_data_received_cb (GtkWidget *widget,
                                         GdkDragContext *context,
                                         gint x, gint y,
                                         GtkSelectionData *data,
                                         guint info,
                                         guint _time,
                                         CcDriversPanel *prefs)
{
}

static void
gcm_prefs_setup_drag_and_drop (GtkWidget *widget)
{
}

static void
gcm_prefs_connect_cb (GObject *object,
                      GAsyncResult *res,
                      gpointer user_data)
{
}

static void
gcm_prefs_window_realize_cb (GtkWidget *widget, CcDriversPanel *prefs)
{
}

static const char *
cc_drivers_panel_get_help_uri (CcPanel *panel)
{
  return "help:gnome-help/color";
}

static void
cc_drivers_panel_get_property (GObject    *object,
                              guint       property_id,
                              GValue     *value,
                              GParamSpec *pspec)
{
  switch (property_id)
  {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
  } 
}

static void
cc_drivers_panel_set_property (GObject      *object,
                              guint         property_id,
                              const GValue *value,
                              GParamSpec   *pspec)
{
  switch (property_id)
  {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
  }
}

static void
cc_drivers_panel_dispose (GObject *object)
{
  g_warning("Panel ... cc_drivers_panel_dispose!");

  CcDriversPanelPrivate *priv = CC_DRIVERS_PANEL (object)->priv;

  if (priv->settings)
    {
      g_object_unref (priv->settings);
      priv->settings = NULL;
    }
  if (priv->cancellable != NULL)
    {
      g_cancellable_cancel (priv->cancellable);
      g_object_unref (priv->cancellable);
      priv->cancellable = NULL;
    }
  if (priv->builder != NULL)
    {
      g_object_unref (priv->builder);
      priv->builder = NULL;
    }


  G_OBJECT_CLASS (cc_drivers_panel_parent_class)->dispose (object);
}

static void
cc_drivers_panel_finalize (GObject *object)
{
  g_warning("Panel ... cc_drivers_panel_finalize!");

  G_OBJECT_CLASS (cc_drivers_panel_parent_class)->finalize (object);
}

static void
cc_drivers_panel_class_init (CcDriversPanelClass *klass)
{
  g_warning("Panel ... cc_drivers_panel_class_init!");

  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  g_type_class_add_private (klass, sizeof (CcDriversPanelPrivate));

  object_class->get_property = cc_drivers_panel_get_property;
  object_class->set_property = cc_drivers_panel_set_property;
  object_class->dispose = cc_drivers_panel_dispose;
  object_class->finalize = cc_drivers_panel_finalize;
}

static void
cc_drivers_panel_class_finalize (CcDriversPanelClass *klass)
{
  g_warning("Panel ... cc_drivers_panel_class_finalize!");
}

static void
cc_drivers_panel_init (CcDriversPanel *prefs)
{
  CcDriversPanelPrivate *priv;
  GError *error = NULL;
  GtkStyleContext *context;
  GtkTreeSelection *selection;
  GtkWidget *widget;

  g_warning("Panel ... Fingers crossed!");
    
  priv = prefs->priv = DRIVERS_PANEL_PRIVATE (prefs);

  priv->builder = gtk_builder_new ();
  gtk_builder_add_from_file (priv->builder,
                             GNOMECC_UI_DIR "/drivers.ui",
                             &error);

  if (error != NULL)
    {
      g_warning ("Could not load interface file: %s", error->message);
      g_error_free (error);
      return;
    }

  g_warning("Panel ... INIT");
    
  priv->cancellable = g_cancellable_new ();

  /* setup defaults */
  priv->settings = g_settings_new (GCM_SETTINGS_SCHEMA);

  /* create list stores */
  priv->list_store_devices = gtk_tree_store_new (GCM_PREFS_COLUMN_NUM_COLUMNS,
                                                 G_TYPE_STRING,
                                                 G_TYPE_STRING,
                                                 G_TYPE_STRING,
                                                 G_TYPE_STRING,
                                                 G_TYPE_STRING,
                                                 G_TYPE_STRING,
                                                 G_TYPE_STRING,
                                                 G_TYPE_BOOLEAN,
                                                 G_TYPE_BOOLEAN);

  /* assign buttons */
  widget = GTK_WIDGET (gtk_builder_get_object (priv->builder,
                                               "toolbutton_driver_toggle"));
  g_signal_connect (widget, "clicked",
                    G_CALLBACK (gcm_prefs_profile_add_cb), prefs);

  /* create device tree view */
  widget = GTK_WIDGET (gtk_builder_get_object (priv->builder,
                                               "treeview_devices"));
  gtk_tree_view_set_model (GTK_TREE_VIEW (widget),
                           GTK_TREE_MODEL (priv->list_store_devices));
  gtk_tree_view_set_enable_tree_lines (GTK_TREE_VIEW (widget), TRUE);
  gtk_tree_view_set_level_indentation (GTK_TREE_VIEW (widget), 0);
  selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (widget));
  g_signal_connect (selection, "changed",
                    G_CALLBACK (gcm_prefs_devices_treeview_clicked_cb),
                    prefs);
  g_signal_connect (GTK_TREE_VIEW (widget), "row-activated",
                    G_CALLBACK (gcm_prefs_treeview_row_activated_cb),
                    prefs);
  g_signal_connect (GTK_TREE_VIEW (widget), "popup-menu",
                    G_CALLBACK (gcm_prefs_treeview_popup_menu_cb),
                    prefs);

  /* add columns to the tree view */
  gcm_prefs_add_devices_columns (prefs, GTK_TREE_VIEW (widget));

  /* force to be at least ~6 rows high */
  widget = GTK_WIDGET (gtk_builder_get_object (priv->builder,
                                               "scrolledwindow_devices"));
  gtk_scrolled_window_set_min_content_height (GTK_SCROLLED_WINDOW (widget),
                                              200);

  widget = GTK_WIDGET (gtk_builder_get_object (priv->builder,
                                               "toolbutton_device_default"));
  g_signal_connect (widget, "clicked",
                    G_CALLBACK (gcm_prefs_default_cb), prefs);
  widget = GTK_WIDGET (gtk_builder_get_object (priv->builder,
                                               "toolbutton_device_remove"));
  g_signal_connect (widget, "clicked",
                    G_CALLBACK (gcm_prefs_delete_cb), prefs);
  widget = GTK_WIDGET (gtk_builder_get_object (priv->builder,
                                               "toolbutton_device_add"));
  g_signal_connect (widget, "clicked",
                    G_CALLBACK (gcm_prefs_device_add_cb), prefs);
  widget = GTK_WIDGET (gtk_builder_get_object (priv->builder,
                                               "toolbutton_device_calibrate"));
  g_signal_connect (widget, "clicked",
                    G_CALLBACK (gcm_prefs_calibrate_cb), prefs);

  /* make devices toolbar sexy */
  widget = GTK_WIDGET (gtk_builder_get_object (priv->builder,
                                               "scrolledwindow_devices"));
  context = gtk_widget_get_style_context (widget);
  gtk_style_context_set_junction_sides (context, GTK_JUNCTION_BOTTOM);

  widget = GTK_WIDGET (gtk_builder_get_object (priv->builder,
                                               "toolbar_devices"));
  context = gtk_widget_get_style_context (widget);
  gtk_style_context_add_class (context, GTK_STYLE_CLASS_INLINE_TOOLBAR);
  gtk_style_context_set_junction_sides (context, GTK_JUNCTION_TOP);

  /* set up virtual dialog */
  widget = GTK_WIDGET (gtk_builder_get_object (priv->builder,
                                               "dialog_virtual"));
  g_signal_connect (widget, "delete-event",
                    G_CALLBACK (gcm_prefs_virtual_delete_event_cb),
                    prefs);
  g_signal_connect (widget, "drag-data-received",
                    G_CALLBACK (gcm_prefs_virtual_drag_data_received_cb),
                    prefs);
  gcm_prefs_setup_drag_and_drop (widget);

  widget = GTK_WIDGET (gtk_builder_get_object (priv->builder,
                                               "button_virtual_add"));
  g_signal_connect (widget, "clicked",
                    G_CALLBACK (gcm_prefs_button_virtual_add_cb),
                    prefs);

  widget = GTK_WIDGET (gtk_builder_get_object (priv->builder,
                                               "button_virtual_cancel"));
  g_signal_connect (widget, "clicked",
                    G_CALLBACK (gcm_prefs_button_virtual_cancel_cb),
                    prefs);
  widget = GTK_WIDGET (gtk_builder_get_object (priv->builder,
                                               "combobox_virtual_type"));
  gcm_prefs_setup_virtual_combobox (widget);

  /* set up assign dialog */
  widget = GTK_WIDGET (gtk_builder_get_object (priv->builder,
                                               "dialog_assign"));
  g_signal_connect (widget, "delete-event",
                    G_CALLBACK (gcm_prefs_profile_delete_event_cb), prefs);
  widget = GTK_WIDGET (gtk_builder_get_object (priv->builder,
                                               "button_assign_cancel"));
  g_signal_connect (widget, "clicked",
                    G_CALLBACK (gcm_prefs_button_assign_cancel_cb), prefs);
  widget = GTK_WIDGET (gtk_builder_get_object (priv->builder,
                                               "button_assign_ok"));
  g_signal_connect (widget, "clicked",
                    G_CALLBACK (gcm_prefs_button_assign_ok_cb), prefs);

  /* setup icc profiles list */
  widget = GTK_WIDGET (gtk_builder_get_object (priv->builder,
                                               "combobox_profile"));
  gcm_prefs_set_combo_simple_text (widget);
  gtk_widget_set_sensitive (widget, FALSE);
  g_signal_connect (G_OBJECT (widget), "changed",
                    G_CALLBACK (gcm_prefs_profile_combo_changed_cb), prefs);

  /* set calibrate button sensitivity */
  gcm_prefs_set_calibrate_button_sensitivity (prefs);

  widget = WID (priv->builder, "dialog-vbox1");
  gtk_widget_reparent (widget, (GtkWidget *) prefs);
  g_signal_connect (widget, "realize",
                    G_CALLBACK (gcm_prefs_window_realize_cb),
                    prefs);
}

void
cc_drivers_panel_register (GIOModule *module)
{
  cc_drivers_panel_register_type (G_TYPE_MODULE (module));
  g_io_extension_point_implement (CC_SHELL_PANEL_EXTENSION_POINT,
                                  CC_TYPE_DRIVERS_PANEL,
                                  "drivers", 0);

  g_warning("Registered.");
}

