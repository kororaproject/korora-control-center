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

#ifndef __CC_KEYBOARD_ITEM_H
#define __CC_KEYBOARD_ITEM_H

#include <glib-object.h>

G_BEGIN_DECLS

#define CC_TYPE_KEYBOARD_ITEM         (cc_keyboard_item_get_type ())
#define CC_KEYBOARD_ITEM(o)           (G_TYPE_CHECK_INSTANCE_CAST ((o), CC_TYPE_KEYBOARD_ITEM, CcKeyboardItem))
#define CC_KEYBOARD_ITEM_CLASS(k)     (G_TYPE_CHECK_CLASS_CAST((k), CC_TYPE_KEYBOARD_ITEM, CcKeyboardItemClass))
#define CC_IS_KEYBOARD_ITEM(o)        (G_TYPE_CHECK_INSTANCE_TYPE ((o), CC_TYPE_KEYBOARD_ITEM))
#define CC_IS_KEYBOARD_ITEM_CLASS(k)  (G_TYPE_CHECK_CLASS_TYPE ((k), CC_TYPE_KEYBOARD_ITEM))
#define CC_KEYBOARD_ITEM_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), CC_TYPE_KEYBOARD_ITEM, CcKeyboardItemClass))

typedef enum
{
  BINDING_GROUP_SYSTEM,
  BINDING_GROUP_APPS,
  BINDING_GROUP_USER,
} BindingGroupType;

typedef enum {
	CC_KEYBOARD_ITEM_TYPE_NONE = 0,
	CC_KEYBOARD_ITEM_TYPE_GSETTINGS_PATH,
	CC_KEYBOARD_ITEM_TYPE_GSETTINGS
} CcKeyboardItemType;

typedef struct CcKeyboardItemPrivate CcKeyboardItemPrivate;

typedef struct
{
  GObject                parent;
  CcKeyboardItemPrivate *priv;

  /* Move to priv */
  CcKeyboardItemType type;

  /* common */
  /* FIXME move to priv? */
  guint keyval;
  guint keycode;
  GdkModifierType mask;
  BindingGroupType group;
  GtkTreeModel *model;
  char *description;
  char *gettext_package;
  char *binding;
  gboolean editable;

  /* GSettings path */
  char *gsettings_path;
  gboolean desc_editable;
  char *command;
  gboolean cmd_editable;

  /* GSettings */
  char *schema;
  char *key;
  GSettings *settings;
} CcKeyboardItem;

typedef struct
{
  GObjectClass   parent_class;
} CcKeyboardItemClass;

GType              cc_keyboard_item_get_type (void);

CcKeyboardItem * cc_keyboard_item_new         (CcKeyboardItemType type);
gboolean cc_keyboard_item_load_from_gsettings_path (CcKeyboardItem *item,
					            const char     *path,
					            gboolean        reset);
gboolean cc_keyboard_item_load_from_gsettings (CcKeyboardItem *item,
					       const char *description,
					       const char *schema,
					       const char *key);

const char * cc_keyboard_item_get_description (CcKeyboardItem *item);
const char * cc_keyboard_item_get_binding     (CcKeyboardItem *item);
const char * cc_keyboard_item_get_command     (CcKeyboardItem *item);

gboolean     cc_keyboard_item_equal           (CcKeyboardItem *a,
					       CcKeyboardItem *b);

G_END_DECLS

#endif /* __CC_KEYBOARD_ITEM_H */
