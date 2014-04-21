# what flags you want to pass to the C compiler & linker
CPPFLAGS = -c -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -DVERSION=\"$(VERSION)\" -isystem libs

BUILD_DIR = ../build

SOURCES_RAW = clipper/clipper.cpp 

HEADERS_RAW = clipper/clipper.hpp 

noinst_LIBRARIES = $(BUILD_DIR)/libclipper.a

__BUILD_DIR__libclipper_a_SOURCES = $(SOURCES_RAW) $(HEADERS_RAW)
