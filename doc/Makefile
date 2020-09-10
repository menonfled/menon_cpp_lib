CXXSRCS	=	$(shell ls ../menon/*.hh ../menon/bits/*.hh)
INDEX		=	./html/index.html

all: $(INDEX)

$(INDEX): $(CXXSRCS) Doxyfile
	doxygen

clean:
	rm -rf html rtf

.PHONY: all clean
