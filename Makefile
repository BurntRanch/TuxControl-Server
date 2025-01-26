CXX       	?= g++
PREFIX	  	?= /usr
VARS  	  	?=

DEBUG		?= 1
# https://stackoverflow.com/a/1079861
# WAY easier way to build debug and release builds
ifeq ($(DEBUG), 1)
        BUILDDIR  = build/debug
        CXXFLAGS := -g -O2 -fsanitize=undefined -Wpedantic -Wall -Wextra -Wno-unused-parameter $(DEBUG_CXXFLAGS) $(CXXFLAGS)
		LDFLAGS := -fsanitize=undefined
else
        BUILDDIR  = build/release
        CXXFLAGS := -O2 $(CXXFLAGS)
endif

NAME		 = TuxControl-Server
TARGET		 = server
SRC 	   	 = $(sort $(wildcard src/*.cpp) $(wildcard src/backend/*.cpp))
OBJ 	   	 = $(SRC:.cpp=.o)
LDFLAGS   	+= -lavahi-client -lavahi-common -lfmt
CXXFLAGS  	?= -mtune=generic -march=native
CXXFLAGS        += -funroll-all-loops -Iinclude -Wall -std=c++17 $(VARS)

all: $(TARGET)

$(TARGET): $(OBJ)
	mkdir -p $(BUILDDIR)
	$(CXX) $(OBJ) -o $(BUILDDIR)/$(TARGET) $(LDFLAGS)

dist: $(TARGET)
	bsdtar -zcf $(NAME)-v$(VERSION).tar.gz LICENSE README.md -C $(BUILDDIR) $(TARGET)

clean:
	rm -rf $(BUILDDIR)/* $(OBJ)

distclean:
	rm -rf $(BUILDDIR) $(OBJ)

.PHONY: $(TARGET) distclean dist clean all
