/*
 * Copyright (c) 2010 Intel, Inc.
 *
 * The Control Center is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * The Control Center is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with the Control Center; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Author: Thomas Wood <thos@gnome.org>
 */


#ifndef _CC_SHELL_CATEGORY_VIEW_H
#define _CC_SHELL_CATEGORY_VIEW_H

#include <gtk/gtk.h>
#include "cc-shell-item-view.h"

G_BEGIN_DECLS

#define CC_TYPE_SHELL_CATEGORY_VIEW cc_shell_category_view_get_type()

#define CC_SHELL_CATEGORY_VIEW(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), \
  CC_TYPE_SHELL_CATEGORY_VIEW, CcShellCategoryView))

#define CC_SHELL_CATEGORY_VIEW_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), \
  CC_TYPE_SHELL_CATEGORY_VIEW, CcShellCategoryViewClass))

#define CC_IS_SHELL_CATEGORY_VIEW(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), \
  CC_TYPE_SHELL_CATEGORY_VIEW))

#define CC_IS_SHELL_CATEGORY_VIEW_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), \
  CC_TYPE_SHELL_CATEGORY_VIEW))

#define CC_SHELL_CATEGORY_VIEW_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), \
  CC_TYPE_SHELL_CATEGORY_VIEW, CcShellCategoryViewClass))

typedef struct _CcShellCategoryView CcShellCategoryView;
typedef struct _CcShellCategoryViewClass CcShellCategoryViewClass;
typedef struct _CcShellCategoryViewPrivate CcShellCategoryViewPrivate;

struct _CcShellCategoryView
{
  GtkFrame parent;

  CcShellCategoryViewPrivate *priv;
};

struct _CcShellCategoryViewClass
{
  GtkFrameClass parent_class;
};

GType cc_shell_category_view_get_type (void) G_GNUC_CONST;

GtkWidget *cc_shell_category_view_new (const gchar  *name,
                                       GtkTreeModel *model);
CcShellItemView* cc_shell_category_view_get_item_view (CcShellCategoryView *self);

G_END_DECLS

#endif /* _CC_SHELL_CATEGORY_VIEW_H */
