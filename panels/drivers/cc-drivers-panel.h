/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*-
 *
 * Copyright (C) 2010 Red Hat, Inc
 * Copyright (C) 2011 Richard Hughes <richard@hughsie.com>
 * Copyright (C) 2012 KororaProject Team <dev@kororaproject.org>    
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


#ifndef _CC_DRIVERS_PANEL_H
#define _CC_DRIVERS_PANEL_H

#include <shell/cc-panel.h>

G_BEGIN_DECLS

#define CC_TYPE_DRIVERS_PANEL cc_drivers_panel_get_type()

#define CC_DRIVERS_PANEL(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), \
  CC_TYPE_DRIVERS_PANEL, CcDriversPanel))

#define CC_DRIVERS_PANEL_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), \
  CC_TYPE_COLOR_PANEL, CcDriversPanelClass))

#define CC_IS_DRIVERS_PANEL(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), \
  CC_TYPE_DRIVERS_PANEL))

#define CC_IS_DRIVERS_PANEL_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), \
  CC_TYPE_DRIVERS_PANEL))

#define CC_DRIVERS_PANEL_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), \
  CC_TYPE_DRIVERS_PANEL, CcDriversPanelClass))

typedef struct _CcDriversPanel CcDriversPanel;
typedef struct _CcDriversPanelClass CcDriversPanelClass;
typedef struct _CcDriversPanelPrivate CcDriversPanelPrivate;

struct _CcDriversPanel
{
  CcPanel parent;

  CcDriversPanelPrivate *priv;
};

struct _CcDriversPanelClass
{
  CcPanelClass parent_class;
};

GType cc_drivers_panel_get_type (void) G_GNUC_CONST;

void  cc_drivers_panel_register (GIOModule *module);

G_END_DECLS

#endif /* _CC_DRIVERS_PANEL_H */
