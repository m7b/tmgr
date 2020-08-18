# Changelog
All notable changes to this project will be documented in this file.
The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/).


## [v2.2.0] - 2020-xx-xx

### Changed
- Architecture from 32bit to 64bit.
- Update boost from version 1.71.0 to 1.73.0 ([supply source](https://www.boost.org/)).
- Update SQLite from version 3.30.0 to 3.32.3 ([supply source](http://sqlite.org/index.html)).
- Update spdlog from version 1.4.1 to 1.6.1 ([supply source](https://github.com/gabime/spdlog/releases)).
- Update wxWidgets from version 3.0.4 to 3.0.5.1 ([supply source](https://https://github.com/wxWidgets/wxWidgets/releases)).

### Added
### Fixed


## [v2.1.9] - 2020-06-23

### Changed
- Update boost from version 1.70.0 to 1.71.0 ([supply source](https://www.boost.org/)).
- Report with assignement durations with changed durations (colored with more than 1, 2 and 3
  years of assignement duration).


## [v2.1.8] - 2019-10-07

### Changed
- Update boost from version 1.70.0 to 1.71.0 ([supply source](https://www.boost.org/)). - COMPILE ERROR BOOST PROCESS^2^.
- Update boost from version 1.71.0 to 1.70.0 ([supply source](https://www.boost.org/)).
- Update spdlog from version 1.3.1 to 1.4.1 ([supply source](https://github.com/gabime/spdlog/releases)).
- DSGVO related changes are switchable at compile time (in this version switched off).
- Update SQLite from version 3.29.0 to 3.30.0 ([supply source](http://sqlite.org/index.html)).

^2^ Boost Process is not compiling anymore. Error somewhere at boost/process/detail/windows/handle_workaround.hpp.

## [v2.1.7] - 2019-08-01

### Changed
- Reports are now with description and timestamp in their filenames.
- Sizer behaviour for history table in action panel.

### Added
- Text modules for comment field (CLR, GDM, RKG).
- Report unassigned territories for vacation replacement.
- Report assigned territories for enquiry.

### Fixed

## [v2.1.6] - 2019-07-29

### Changed
- Hiding territorries by assignee now case insensitive.
- Update SQLite from version 3.28.0 to 3.29.0 ([supply source](http://sqlite.org/index.html)).
- Image processing now with ImageMagick 7.x
  - Tested with version 7.0.8-54 and Maperitive 2.4.3
  - Version 6 is no longer supported.

### Fixed
- Last processing status in inlet corrected.

## [v2.1.5] - 2019-05-21

### Changed
- DSGVO related changes:
  - C_wxDataListPanel_NoVisits now without name.
  - Report for no-visits now without name column.
  - Inlet no-visits without name.
  - Booklet no-visits without name.

### Added
- In category window fade unassigned territories that has been assigned to a
  specified assignee in the past x months.

### Removed
- src/C_wxPanelNoVisits.cpp (was replaced by src/C_wxDataListPanel_NoVisits.cpp)
- src/C_wxPanelTips.cpp (was replaced by src/C_wxDataListPanel_Tips.cpp)
- Class C_wxListPanel (was replaced by C_wxDataListPanel)

## [v2.1.4] - 2019-04-17

### Added
- Storing and restoring pane properties by switching landscape and portrait mode.
- In statistic overview:
  - how many territories are assigned more than 2,3,4 years.
  - how many territories are unassigned since pre last year of service.

### Changed
- Update boost from version 1.69.0 to 1.70.0 ([supply source](https://www.boost.org/)).
- Update spdlog from version 1.2.1 to 1.3.0 ([supply source](https://github.com/gabime/spdlog/releases)).
- Update spdlog from version 1.3.0 to 1.3.1 ([supply source](https://github.com/gabime/spdlog/releases)).
- Removed info table for territories. Those informations are now on the window
  title.
- Set splitter from properiy grids to left.
- Font size of popup menus increased.
- Update SQLite from version 3.24.0 to 3.28.0 ([supply source](http://sqlite.org/index.html)).
- Changed svg template from inkscape version 0.91 r13725 to 0.92.2 (5c3e80d, 2017-08-06). Corrected
  dpi change from 90 to 96dpi


### Fixed
- Fixed crashing at startup on some machines.
- Fixed SQL queries with not assigned territories related with newer version of
  sqlite3.

## [v2.1.3] - 2019-01-09
### Added
- Table view of territories

### Changed
- Update SQLite from version 3.24.0 to 3.26.0 ([supply source](http://sqlite.org/index.html)). - QUERIES NOT CORRECT^1^.
- Update SQLite from version 3.26.0 to 3.24.0 ([supply source](http://sqlite.org/index.html)).
- Font size of more widgets are changable

## [v2.1.2] - 2018-12-12
### Added
- Sash size is now configurable in settings.

### Changed
- Update boost from version 1.68.0 to 1.69.0 ([supply source](https://www.boost.org/)).
- Update spdlog from version 0.17.0 to 1.2.1 ([supply source](https://github.com/gabime/spdlog/releases)).
- Update SQLite from version 3.24.0 to 3.25.0 ([supply source](http://sqlite.org/index.html)) - QUERIES NOT CORRECT^1^.
- Update SQLite from version 3.25.0 to 3.25.1 ([supply source](http://sqlite.org/index.html)) - QUERIES NOT CORRECT^1^.
- Update SQLite from version 3.25.1 to 3.25.2 ([supply source](http://sqlite.org/index.html)) - QUERIES NOT CORRECT^1^.
- Update SQLite from version 3.25.2 to 3.24.0 ([supply source](http://sqlite.org/index.html)).

^1^ Date order of displayed working state each territory and action are wrong.
Date should be decreasing, but is increasing.

## [v2.1.1] - 2018-08-02
### Added
- New report with assignement durations (colored with more than 2, 3 and 4
  years of assignement duration).

## [v2.1.0] - 2018-07-19
### Added
- GUI now managed with AUI.

### Changed
- Update boost from version 1.67.0 to 1.68.0 beta ([supply source](https://www.boost.org/)).

## [v2.0.2] - 2018-07-02
### Changed
- Toolchain information available in Info-dialog. Only visible if pressed
  shift-button during opening of Info-dialog.
- Update SQLite from version 3.23.1 to 3.24.0 ([supply source](http://sqlite.org/index.html)).

### Fixed
- Changed territory properties updated in info table.
- NSIS Installer fixed.
- No LaTeX warnings anymore by creating the overview report.

## [v2.0.1] - 2018-06-04
### Added
- Changelog information available in Info-dialog.
- SVN-Log information available in Info-dialog. Only visible if pressed
  shift-button during opening of Info-dialog.
- Information amount of families in territory are also printed in the territory
  info page.
- Hints are also printed in the territory info page.
- Release executable packed with UPX 3.94w ([supply source](https://upx.github.io/)).
- Information amount of families in territory are also printed in the territory
  booklet page.
- Compiler optimizations with `-Ofast -m32 -mfpmath=sse -march=atom -mtune=atom -funroll-loops`.

### Changed
- Compiled with GCC 7.3 ([supply source](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/7.3.0/threads-posix/dwarf/)).
- Update SQLite from version 3.23.0 to 3.23.1 ([supply source](http://sqlite.org/index.html)).
- Info-dialog restructured.
- Also the label of the territory will be part of the pdf file by creating the
  info page.
- Main-Window/Statistic-tab restructured.
- Update spdlog from version 0.16.3 to 0.17.0 ([supply source](https://github.com/gabime/spdlog)).
- Update boost from version 1.66.0 to 1.67.0 ([supply source](https://www.boost.org/)).

## [v2.0.0] - 2017-03-14
### Changed
- Complete rework of the GUI.

## [v1.0.0] - 2016-12-14
- Initial version.