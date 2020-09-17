# Menon C++ Libraryのテストコード用Makefile
CC			=	gcc
CXX 		=	g++

OSTYPE		=	$(shell echo $$OSTYPE);

-include config.mak

INCLUDES	+=	-iquote .. -iquote .
DEFINES 	+= 
WARNINGS	+=	-Wall -Wextra -Wconversion -Weffc++
CFLAGS		+=	-MMD -g -Og -std=gnu18 $(ENCODING) $(INCLUDES) $(DEFINES) $(WARNINGS)
CXXFLAGS	+=	-MMD -g -Og -std=gnu++20 $(ENCODING) $(INCLUDES) $(DEFINES) $(WARNINGS)
LDFLAGS		+=	-lm

CXXSRCS		=	$(filter %.cc,$(shell ls .))
OBJS		=	$(CXXSRCS:%.cc=%.o)
DEPENDS		=	$(CXXSRCS:%.cc=%.d)
TESTS		=	$(CXXSRCS:%.cc=%.test)

all: $(TESTS)

clean:
	-rm -f *.o $(TESTS) $(DEPENDS)

%.test: %.cc
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS)
	./$@

-include $(DEPENDS)

.PHONY:	all clean
