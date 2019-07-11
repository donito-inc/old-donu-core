
Debian
====================
This directory contains files used to package donud/donu-qt
for Debian-based Linux systems. If you compile donud/donu-qt yourself, there are some useful files here.

## donu: URI support ##


donu-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install donu-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your donu-qt binary to `/usr/bin`
and the `../../share/pixmaps/donu128.png` to `/usr/share/pixmaps`

donu-qt.protocol (KDE)

## Building
Update the changelog. setting the version and series

Build and push with:

debuild -k<key id> -S -sa && dput ppa:donu/donu <path to changes file>
