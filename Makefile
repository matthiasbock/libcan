
#
# Files and folders configuration
#

INCDIR = include
SRCDIR = src
TESTDIR = test

# Compile the library
LIBNAME = can
LIBSRCS = $(wildcard $(SRCDIR)/*.cpp)
LIBOBJS = $(LIBSRCS:.cpp=.o)

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

RM = rm -f


#
# Targets
#

all: lib

lib: lib$(LIBNAME).so

lib$(LIBNAME).so: $(LIBSRCS)
	@$(RM) $@
	$(CPP) $(CPPFLAGS) -fPIC -shared $^ -o $@

$(TESTDIR)/$(TESTNAME): $(TESTOBJS) lib$(LIBNAME).so
	@$(RM) $@
	$(CPP) $(CPPFLAGS) -L. -l$(LIBNAME) $^ -o $@

test: $(TESTDIR)/$(TESTNAME)
	@./$<

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c $^ -o $@

clean:
	@$(RM) $(SRCDIR)/*.o lib$(LIBNAME).so $(TESTDIR)/$(TESTNAME)
