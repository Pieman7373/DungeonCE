# ----------------------------
# Set NAME to the program name
# Set DEBUGMODE to "DEBUG" to use debug functions
# Set ICON to the png icon file name
# Set DESCRIPTION to display within a compatible shell
# Set COMPRESSED to "YES" to create a compressed program
# ** Add all shared library names to L **
# ----------------------------

NAME        ?= Dungeon
ARCHIVED    ?= YES
COMPRESSED  ?= YES
ICON        ?= dungeonicon.png
DESCRIPTION ?= "CC22 Dungeon Crawler"

CFLAGS ?= -Wall -Wextra -Oz
CXXFLAGS ?= -Wall -Wextra -Oz

# ----------------------------

ifndef CEDEV
$(error CEDEV environment path variable is not set)
endif

include $(CEDEV)/meta/makefile.mk
