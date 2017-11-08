
SRCDIR=src
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(SRCS:.cpp=.o)

# Compiler setup
CXX=g++
CPPFLAGS=-Isrc
CXXFLAGS=-std=gnu++14 -pedantic -Wall -Wextra
LIBS=

CXXFLAGS+=-g
CXXFLAGS+=-O3

RM=rm -f

.PHONY: all run clean rebuild

all: main.elf

run: main.elf
	@./$<

main.elf: $(OBJS)
	@$(RM) $@
	$(CXX) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

clean:
	@$(RM) $(SRCDIR)/*.o

rebuild: clean all
