
#
# Files and folders configuration
#

INCDIR = include
SRCDIR = src
LIBDIR = lib
TESTDIR = test

# Compile the library
LIBNAME = can
LIBSRCS  = $(wildcard $(SRCDIR)/*.cpp)
LIBOBJS = $(LIBSRCS:.cpp=.o)

# Support for Vector stuff
ifdef ENABLE_VECTOR
LIBSRCS += $(wildcard $(SRCDIR)/Vector/*.cpp)
LIBSRCS += $(wildcard $(SRCDIR)/Vector/CANalyzer/*.cpp)
LIBSRCS += $(wildcard $(SRCDIR)/Vector/XLDriverLibrary/*.cpp)
CPPFLAGS += -DENABLE_VECTOR
endif


#
# Toolchain setup
#
CPP = g++
CPPFLAGS += -fdiagnostics-color=auto
CPPFLAGS += -std=gnu++14
CPPFLAGS += -Wall -Wextra -pedantic
CPPFLAGS += -g
CPPFLAGS += -O3

# Required for linking to shared library:
CPPFLAGS += -fPIC

CPPFLAGS += -I$(INCDIR)
CPPFLAGS += -lpthread

RM = rm -f


#
# Targets
#

all: lib $(TESTDIR)/$(TESTNAME)

lib: lib$(LIBNAME).so

lib$(LIBNAME).so: $(LIBOBJS)
	@$(RM) $@
	$(CPP) $(CPPFLAGS) -shared -o $@ $^

$(TESTDIR)/test: $(TESTDIR)/test.o lib$(LIBNAME).so
	@$(RM) $@
	$(CPP) $(CPPFLAGS) -o $@ $^

test: $(TESTDIR)/test
	@./$<

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -o $@ -c $^

clean:
	@$(RM) $(SRCDIR)/*.o lib$(LIBNAME).so $(TESTDIR)/test $(TESTDIR)/test-pcan.exe


#
# Windows targets
#
include windows.mk
