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
TESTS		=	$(CXXSRCS:%.cc=%.okay)

all: $(TESTS)

clean:
	-rm -f *.o $(TESTS) $(subst .okay,.out,$(TESTS)) $(DEPENDS)

%.okay: %.cc
	@echo $<
	@$(CXX) $(CXXFLAGS) -o $*.out $< $(LDFLAGS)
	@./$*.out
	@touch $@

-include $(DEPENDS)

.PHONY:	all clean
