# ----------------------------
# Set NAME to the program name
# Set DEBUGMODE to "DEBUG" to use debug functions
# Set ICON to the png icon file name
# Set DESCRIPTION to display within a compatible shell
# Set COMPRESSED to "YES" to create a compressed program
# ** Add all shared library names to L **
# ----------------------------

NAME        ?= Dungeon
DEBUGMODE   ?= DEBUG
ARCHIVED    ?= YES
COMPRESSED  ?= YES
ICON        ?= dungeonicon.png
DESCRIPTION ?= "CC22 Dungeon Crawler"

L ?= graphx keypadc fileioc

# ----------------------------
# Specify source and output locations
# ----------------------------

SRCDIR ?= src
OBJDIR ?= obj
BINDIR ?= bin
GFXDIR ?= src/gfx

# ----------------------------
# Use OS helper functions (Advanced)
# ----------------------------

USE_FLASH_FUNCTIONS ?= YES

include $(CEDEV)/include/.makefile