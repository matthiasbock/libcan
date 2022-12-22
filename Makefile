
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

TEST_ELF = $(TESTDIR)/test.elf


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


#
# Targets
#

all: lib $(TESTDIR)/$(TESTNAME)

lib: lib$(LIBNAME).so

lib$(LIBNAME).so: $(LIBOBJS)
	@$(RM) $@
	$(CPP) -shared -o $@ $^ $(CPPFLAGS)

$(TEST_ELF): $(TESTDIR)/test.o lib$(LIBNAME).so
	@$(RM) $@
	$(CPP) -o $@ $^ $(CPPFLAGS)

test: $(TEST_ELF)
	@./$<

%.o: %.cpp
	$(CPP) -o $@ -c $^ $(CPPFLAGS)

clean:
	@rm -fv $(SRCDIR)/*.o lib$(LIBNAME).so $(TEST_ELF) $(TESTDIR)/test-pcan.exe


#
# Windows targets
#
include windows.mk
