
#
# Files and folders configuration
#

INCDIR = include
SRCDIR = src
TESTDIR = test

# Compile the library
LIBNAME = can
LIBSRCS  = $(wildcard $(SRCDIR)/*.cpp)
LIBOBJS = $(LIBSRCS:.cpp=.o)

# Support for Vector stuff
LIBSRCS += $(wildcard $(SRCDIR)/Vector/*.cpp)
LIBSRCS += $(wildcard $(SRCDIR)/Vector/CANalyzer/*.cpp)
LIBSRCS += $(wildcard $(SRCDIR)/Vector/XLDriverLibrary/*.cpp)
CPPFLAGS += -DENABLE_VECTOR

# Compile library test program(s)
TESTNAME = test
TESTSRCS = $(wildcard $(TESTDIR)/*.cpp)
TESTOBJS = $(TESTSRCS:.cpp=.o)


#
# Toolchain setup
#
CPP = g++
CPPFLAGS += -I$(INCDIR)
CPPFLAGS += -std=gnu++14
CPPFLAGS += -Wall -Wextra -pedantic
CPPFLAGS += -lpthread
CPPFLAGS += -g
CPPFLAGS += -O3
# Required for linking to shared library:
CPPFLAGS += -fPIC

RM = rm -f


#
# Targets
#

all: lib $(TESTDIR)/$(TESTNAME)

lib: lib$(LIBNAME).so

lib$(LIBNAME).so: $(LIBOBJS)
	@$(RM) $@
	$(CPP) $(CPPFLAGS) -shared -o $@ $^

$(TESTDIR)/$(TESTNAME): $(TESTOBJS) lib$(LIBNAME).so
	@$(RM) $@
	$(CPP) $(CPPFLAGS) -o $@ $^

test: $(TESTDIR)/$(TESTNAME)
	@./$<

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -o $@ -c $^

clean:
	@$(RM) $(SRCDIR)/*.o lib$(LIBNAME).so $(TESTDIR)/$(TESTNAME)
