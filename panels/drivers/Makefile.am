cappletname = drivers

INCLUDES = 						\
	$(PANEL_CFLAGS)					\
	$(DRIVERS_PANEL_CFLAGS)				\
	-DGNOMECC_UI_DIR="\"$(uidir)\""			\
	-DGNOMELOCALEDIR="\"$(datadir)/locale\""	\
	-DBINDIR="\"$(bindir)\""			\
	-DGNOMECC_DATA_DIR="\"$(pkgdatadir)\""		\
	$(NULL)

ccpanelsdir = $(PANELS_DIR)
ccpanels_LTLIBRARIES = libdrivers.la

libdrivers_la_SOURCES =		\
	drivers-module.c		\
	cc-drivers-panel.c	\
	cc-drivers-panel.h

libdrivers_la_LIBADD = $(PANEL_LIBS) $(DRIVERS_PANEL_LIBS)
libdrivers_la_LDFLAGS = $(PANEL_LDFLAGS)

uidir = $(pkgdatadir)/ui
dist_ui_DATA = drivers.ui

@INTLTOOL_DESKTOP_RULE@

desktopdir = $(datadir)/applications
desktop_in_files = gnome-drivers-panel.desktop.in
desktop_DATA = $(desktop_in_files:.desktop.in=.desktop)

CLEANFILES = $(desktop_in_files) $(desktop_DATA)

-include $(top_srcdir)/git.mk
