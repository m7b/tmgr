# TerritoryMgr

Diese Applikation dienst zum Verwalten der Gebiete der Versammlung Reutlingen-Süd als auch die automatische Erstellung der Gebietskarten.
Folgende Programme werden weiter benötigt:

- Maperitive
- MiKTeX
- ImageMagick

Um die Gebietsgrenzen (`xxx_border.svg`) zu zeichnen wurde Inkscape verwendet.

## Hinweise zum Kompilieren

Derzeit wird das Projekt mit GCC 6.2.0 kompilliert mit CodeBlocks 16.01. Folgende Bibliotheken müssen vorhanden sein:

- wxWidgets 3.1.1 (unicode build) https://github.com/wxWidgets/wxWidgets
- Boost 1.63.0 https://github.com/boostorg/boost
- Boost.Process 0.6 https://github.com/klemens-morgenstern/boost-process
- SQLite3 3.17.0 (ist bereits im Projektverzeichnis) https://www.sqlite.org/
- easylogging++ 9.94 https://github.com/easylogging/easyloggingpp

### wxWidgets kompillieren
https://github.com/wxWidgets/wxWidgets.git

**Clean**

    (WXWIDGETS)\build\msw\mingw32-make -f makefile.gcc BUILD=debug SHARED=0 UNICODE=1 CXXFLAGS=-std=gnu++11 -Wall clean
    (WXWIDGETS)\build\msw\mingw32-make -f makefile.gcc BUILD=release SHARED=0 UNICODE=1 CXXFLAGS=-std=gnu++11 -Wall clean

**Build mit -march=i686 (wegen Boost 1.63)**

    (WXWIDGETS)\build\msw\mingw32-make -j5 -f makefile.gcc BUILD=debug SHARED=0 UNICODE=1 CXXFLAGS="-std=gnu++17 -march=i686 -Wall"
    (WXWIDGETS)\build\msw\mingw32-make -j5 -f makefile.gcc BUILD=release SHARED=0 UNICODE=1 CXXFLAGS="-std=gnu++17 -march=i686 -Wall"


### Boost kompillieren
https://github.com/boostorg/boost.git

- Launch "MinGW Command Prompt"
- Go to your Boost folder (e.g. C:/Boost)
- Run bootstrap gcc
- Run b2 toolset=gcc cxxflags=-std=gnu++17 --with-filesystem --with-date_time --with-system (or whatever b2 command you need)

#### Holen über GIT und bauen

git clone --recursive https://github.com/boostorg/boost
cd boost
bootstrap gcc
b2 headers
b2 toolset=gcc cxxflags=-std=gnu++17 --with-filesystem --with-date_time --with-system

### GIT Kommandos

git clone --recursive -j8 git://github.com/foo/bar.git  'cloning a repository including submodules
git submodule update --recursive --remote               'update a repository incl submodules
git pull                                                'update repository
git clone --depth 1 --recursive --branch master https://github.com/boostorg/boost.git

## Console Einstellungen

Um ImageMagick korrekt mit Unicode ausführen zu lassen, müssen folgende Dinge beachtet werden:

- der Befehl `chcp 65001` muss am Anfang der Batch-Datei aufgeführt sein
- Der Zeichensatz (Font) der Konsole muss auf `Lucida Console` eingestellt sein


## Gebietsgrenze Versammlung RT-Süd

### OSM Bounds

- `MaxX: 9.4112410378702478`
- `MaxY: 48.528035381824772`
- `MinX: 9.1305319296736478`
- `MinY: 48.306384885710379`

download-osm bounds=9.4112410378702478,48.528035381824772,9.1305319296736478,48.306384885710379 xapi-url="http://www.overpass-api.de/api/xapi_meta?*"
save-source Rt5.osm

ServiceURL="http://www.overpass-api.de/api/interpreter?*"

### commands with maperitive 2.4.3

download-osm-overpass bounds=9.4112410378702478,48.528035381824772,9.1305319296736478,48.306384885710379
save-source index=1 file=x:\trunk\Rt5.osm

### Anleitung umstellung 90 auf 96 DPI

- Dokumentengröße Einheit von [px] auf [mm] ändern.
- Dokumentengröße anpassen von ~140x80mm auf exakt 150x94mm
- Dokumentengröße Einheit von [mm] auf [px] ändern.
- Alle Elemente selektieren (Rahmen zuletzt mit Shift-Taste und Mausklick)
- Elemente skalieren auf 150x94mm (Einheit ggf. auf mm ändern)
- Elemente absolut auf Position 0, 0 verschieben

### Anleitung gebogenen Text in Inkscape, der auch nach Kartenerstellung sichtbar ist

- Text erstellen
- gebogene Linie erstellen
- beides selektieren
- Text an Pfad ausrichten
- Objekt in Pfad umwandeln

### History in tAktion Tabelle pflegen

http://www.sqlitetutorial.net/sqlite-trigger/

### TODO
Gebiet Grenze checken 393 (alt 105) Pfu aktuell / Ofi alt ?
Gebiet 045a (Border-Datei) löschen in Pfu

