/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2011 Red Hat, Inc.
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

#include "config.h"

#include <stdlib.h>
#include <stdio.h>

#include <gtk/gtk.h>
#include <gio/gio.h>
#include <glib/gi18n-lib.h>

#include "cc-keyboard-item.h"

#define CC_KEYBOARD_ITEM_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), CC_TYPE_KEYBOARD_ITEM, CcKeyboardItemPrivate))

#define CUSTOM_KEYS_SCHEMA "org.gnome.settings-daemon.plugins.media-keys.custom-keybinding"

struct CcKeyboardItemPrivate
{
  /* properties */
  int foo;

  /* internal */
};

enum {
  PROP_0,
  PROP_DESCRIPTION,
  PROP_BINDING,
  PROP_EDITABLE,
  PROP_TYPE,
  PROP_COMMAND
};

static void     cc_keyboard_item_class_init     (CcKeyboardItemClass *klass);
static void     cc_keyboard_item_init           (CcKeyboardItem      *keyboard_item);
static void     cc_keyboard_item_finalize       (GObject               *object);

G_DEFINE_TYPE (CcKeyboardItem, cc_keyboard_item, G_TYPE_OBJECT)

static gboolean
binding_from_string (const char             *str,
                     guint                  *accelerator_key,
                     guint                  *keycode,
                     GdkModifierType        *accelerator_mods)
{
  g_return_val_if_fail (accelerator_key != NULL, FALSE);
  guint *keycodes;

  if (str == NULL || strcmp (str, "disabled") == 0)
    {
      *accelerator_key = 0;
      *keycode = 0;
      *accelerator_mods = 0;
      return TRUE;
    }

  gtk_accelerator_parse_with_keycode (str, accelerator_key, &keycodes, accelerator_mods);

  if (keycode != NULL)
    *keycode = (keycodes ? keycodes[0] : 0);
  g_free (keycodes);

  if (*accelerator_key == 0)
    return FALSE;
  else
    return TRUE;
}

static void
_set_description (CcKeyboardItem *item,
                  const char       *value)
{
  g_free (item->description);
  item->description = g_strdup (value);
}

const char *
cc_keyboard_item_get_description (CcKeyboardItem *item)
{
  g_return_val_if_fail (CC_IS_KEYBOARD_ITEM (item), NULL);

  return item->description;
}

/* wrapper around g_settings_set_str[ing|v] */
static void
settings_set_binding (GSettings  *settings,
                      const char *key,
		      const char *value)
{
  GVariant *variant;

  variant = g_settings_get_value (settings, key);

  if (g_variant_is_of_type (variant, G_VARIANT_TYPE_STRING))
    g_settings_set_string (settings, key, value);
  else if (g_variant_is_of_type (variant, G_VARIANT_TYPE_STRING_ARRAY))
    {
      char **str_array;

      str_array = g_variant_dup_strv (variant, NULL);

      /* create a space for the new binding if empty */
      if (*str_array == NULL)
        {
          g_free (str_array);
          str_array = g_new0 (char *, 2);
        }

      /* replace the first binding */
      g_free (*str_array);
      *str_array = g_strdup (value);

      g_settings_set_strv (settings, key, (const char * const *)str_array);
      g_strfreev (str_array);
    }

  g_variant_unref (variant);
}


static void
_set_binding (CcKeyboardItem *item,
              const char     *value,
	      gboolean        set_backend)
{
  g_free (item->binding);
  item->binding = g_strdup (value);
  binding_from_string (item->binding, &item->keyval, &item->keycode, &item->mask);

  if (set_backend == FALSE)
    return;

  settings_set_binding (item->settings, item->key, item->binding);
}

const char *
cc_keyboard_item_get_binding (CcKeyboardItem *item)
{
  g_return_val_if_fail (CC_IS_KEYBOARD_ITEM (item), NULL);

  return item->binding;
}

static void
_set_type (CcKeyboardItem *item,
           gint            value)
{
  item->type = value;
}

static void
_set_command (CcKeyboardItem *item,
              const char       *value)
{
  g_free (item->command);
  item->command = g_strdup (value);
}

const char *
cc_keyboard_item_get_command (CcKeyboardItem *item)
{
  g_return_val_if_fail (CC_IS_KEYBOARD_ITEM (item), NULL);

  return item->command;
}

static void
cc_keyboard_item_set_property (GObject      *object,
                               guint         prop_id,
                               const GValue *value,
                               GParamSpec   *pspec)
{
  CcKeyboardItem *self;

  self = CC_KEYBOARD_ITEM (object);

  switch (prop_id) {
  case PROP_DESCRIPTION:
    _set_description (self, g_value_get_string (value));
    break;
  case PROP_BINDING:
    _set_binding (self, g_value_get_string (value), TRUE);
    break;
  case PROP_COMMAND:
    _set_command (self, g_value_get_string (value));
    break;
  case PROP_TYPE:
    _set_type (self, g_value_get_int (value));
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    break;
  }
}

static void
cc_keyboard_item_get_property (GObject    *object,
                               guint       prop_id,
                               GValue     *value,
                               GParamSpec *pspec)
{
  CcKeyboardItem *self;

  self = CC_KEYBOARD_ITEM (object);

  switch (prop_id) {
  case PROP_DESCRIPTION:
    g_value_set_string (value, self->description);
    break;
  case PROP_BINDING:
    g_value_set_string (value, self->binding);
    break;
  case PROP_EDITABLE:
    g_value_set_boolean (value, self->editable);
    break;
  case PROP_COMMAND:
    g_value_set_string (value, self->command);
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    break;
  }
}

static GObject *
cc_keyboard_item_constructor (GType                  type,
                              guint                  n_construct_properties,
                              GObjectConstructParam *construct_properties)
{
  CcKeyboardItem      *keyboard_item;

  keyboard_item = CC_KEYBOARD_ITEM (G_OBJECT_CLASS (cc_keyboard_item_parent_class)->constructor (type,
                                                                                                 n_construct_properties,
                                                                                                 construct_properties));

  return G_OBJECT (keyboard_item);
}

static void
cc_keyboard_item_class_init (CcKeyboardItemClass *klass)
{
  GObjectClass  *object_class = G_OBJECT_CLASS (klass);

  object_class->get_property = cc_keyboard_item_get_property;
  object_class->set_property = cc_keyboard_item_set_property;
  object_class->constructor = cc_keyboard_item_constructor;
  object_class->finalize = cc_keyboard_item_finalize;

  g_object_class_install_property (object_class,
                                   PROP_DESCRIPTION,
                                   g_param_spec_string ("description",
                                                        "description",
                                                        "description",
                                                        NULL,
                                                        G_PARAM_READWRITE));

  g_object_class_install_property (object_class,
                                   PROP_BINDING,
                                   g_param_spec_string ("binding",
                                                        "binding",
                                                        "binding",
                                                        NULL,
                                                        G_PARAM_READWRITE));

  g_object_class_install_property (object_class,
                                   PROP_EDITABLE,
                                   g_param_spec_boolean ("editable",
                                                         NULL,
                                                         NULL,
                                                         FALSE,
                                                         G_PARAM_READABLE));

  g_object_class_install_property (object_class,
                                   PROP_TYPE,
                                   g_param_spec_int ("type",
                                                     NULL,
                                                     NULL,
                                                     CC_KEYBOARD_ITEM_TYPE_NONE,
                                                     CC_KEYBOARD_ITEM_TYPE_GSETTINGS,
                                                     CC_KEYBOARD_ITEM_TYPE_NONE,
                                                     G_PARAM_CONSTRUCT_ONLY | G_PARAM_WRITABLE));

  g_object_class_install_property (object_class,
                                   PROP_COMMAND,
                                   g_param_spec_string ("command",
                                                        "command",
                                                        "command",
                                                        NULL,
                                                        G_PARAM_READWRITE));

  g_type_class_add_private (klass, sizeof (CcKeyboardItemPrivate));
}

static void
cc_keyboard_item_init (CcKeyboardItem *item)
{
  item->priv = CC_KEYBOARD_ITEM_GET_PRIVATE (item);
}

static void
cc_keyboard_item_finalize (GObject *object)
{
  CcKeyboardItem *item;

  g_return_if_fail (object != NULL);
  g_return_if_fail (CC_IS_KEYBOARD_ITEM (object));

  item = CC_KEYBOARD_ITEM (object);

  g_return_if_fail (item->priv != NULL);

  if (item->settings != NULL)
    g_object_unref (item->settings);

  /* Free memory */
  g_free (item->binding);
  g_free (item->gettext_package);
  g_free (item->gsettings_path);
  g_free (item->description);
  g_free (item->command);
  g_free (item->schema);
  g_free (item->key);

  G_OBJECT_CLASS (cc_keyboard_item_parent_class)->finalize (object);
}

CcKeyboardItem *
cc_keyboard_item_new (CcKeyboardItemType type)
{
  GObject *object;

  object = g_object_new (CC_TYPE_KEYBOARD_ITEM,
                         "type", type,
                         NULL);

  return CC_KEYBOARD_ITEM (object);
}

/* wrapper around g_settings_get_str[ing|v] */
static char *
settings_get_binding (GSettings  *settings,
                      const char *key)
{
  GVariant *variant;
  char *value = NULL;

  variant = g_settings_get_value (settings, key);
  if (g_variant_is_of_type (variant, G_VARIANT_TYPE_STRING))
    value = g_variant_dup_string (variant, NULL);
  else if (g_variant_is_of_type (variant, G_VARIANT_TYPE_STRING_ARRAY))
    {
      const char **str_array;

      str_array = g_variant_get_strv (variant, NULL);
      value = g_strdup (str_array[0]);
    }
  g_variant_unref (variant);

  return value;
}

static void
binding_changed (GSettings *settings,
		 const char *key,
		 CcKeyboardItem *item)
{
  char *value;

  value = settings_get_binding (item->settings, item->key);
  item->editable = g_settings_is_writable (item->settings, item->key);
  _set_binding (item, value, FALSE);
  g_free (value);
  g_object_notify (G_OBJECT (item), "binding");
}

gboolean
cc_keyboard_item_load_from_gsettings_path (CcKeyboardItem *item,
                                           const char     *path,
                                           gboolean        reset)
{
  item->schema = g_strdup (CUSTOM_KEYS_SCHEMA);
  item->gsettings_path = g_strdup (path);
  item->key = g_strdup ("binding");
  item->settings = g_settings_new_with_path (item->schema, path);
  item->editable = g_settings_is_writable (item->settings, item->key);
  item->desc_editable = g_settings_is_writable (item->settings, "name");
  item->cmd_editable = g_settings_is_writable (item->settings, "command");

  if (reset)
    {
      g_settings_reset (item->settings, "name");
      g_settings_reset (item->settings, "command");
      g_settings_reset (item->settings, "binding");
    }

  g_settings_bind (item->settings, "name",
                   G_OBJECT (item), "description", G_SETTINGS_BIND_DEFAULT);
  g_settings_bind (item->settings, "command",
                   G_OBJECT (item), "command", G_SETTINGS_BIND_DEFAULT);

  item->binding = settings_get_binding (item->settings, item->key);
  binding_from_string (item->binding, &item->keyval, &item->keycode, &item->mask);
  g_signal_connect (G_OBJECT (item->settings), "changed::binding",
		    G_CALLBACK (binding_changed), item);

  return TRUE;
}

gboolean
cc_keyboard_item_load_from_gsettings (CcKeyboardItem *item,
				      const char *description,
				      const char *schema,
				      const char *key)
{
  char *signal_name;

  item->schema = g_strdup (schema);
  item->key = g_strdup (key);
  item->description = g_strdup (description);

  item->settings = g_settings_new (item->schema);
  item->binding = settings_get_binding (item->settings, item->key);
  item->editable = g_settings_is_writable (item->settings, item->key);
  binding_from_string (item->binding, &item->keyval, &item->keycode, &item->mask);

  signal_name = g_strdup_printf ("changed::%s", item->key);
  g_signal_connect (G_OBJECT (item->settings), signal_name,
		    G_CALLBACK (binding_changed), item);
  g_free (signal_name);

  return TRUE;
}

gboolean
cc_keyboard_item_equal (CcKeyboardItem *a,
			CcKeyboardItem *b)
{
  if (a->type != b->type)
    return FALSE;
  switch (a->type)
    {
      case CC_KEYBOARD_ITEM_TYPE_GSETTINGS_PATH:
	return g_str_equal (a->gsettings_path, b->gsettings_path);
      case CC_KEYBOARD_ITEM_TYPE_GSETTINGS:
	return (g_str_equal (a->schema, b->schema) &&
		g_str_equal (a->key, b->key));
      default:
	g_assert_not_reached ();
    }

}

/*
 * vim: sw=2 ts=8 cindent noai bs=2
 */
