# ----------------------------
# Set NAME to the program name
# Set ICON to the png icon file name
# Set DESCRIPTION to display within a compatible shell
# Set COMPRESSED to "YES" to create a compressed program
# ----------------------------

NAME        ?= HAILSTRM
COMPRESSED  ?= YES
ICON        ?= iconc.png
DESCRIPTION ?= "Hailstorm 0.0.1"

# ----------------------------

include $(CEDEV)/include/.makefile
