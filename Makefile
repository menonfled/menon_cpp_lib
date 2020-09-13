# Makefile for Menon C++ Library
VER_TEXT	=	$(shell cat version.txt)
VER_LIST	=	$(subst ., ,$(VER_TEXT))
MAJOR_VER	=	$(word 1,$(VER_LIST))
MINOR_VER	=	$(word 2,$(VER_LIST))
PATCH_VER	=	$(word 3,$(VER_LIST))

DOXYFILE	=	./doc/Doxyfile
VERSION_HH	=	./menon/version.hh

all: build

build: $(VERSION_HH)
	make -C test all

clean:
	make -C test clean

doc: $(DOXYFILE)
	make -C doc all

realclean: clean
	make -C doc clean
	-rm -f $(DOXYFILE) $(VERSION_HH)

$(VERSION_HH): ./template/version.hh.in version.txt
	cp ./template/version.hh.in $@
	sed -i "s/%VERSION%/$(shell printf '%d%02d%02d' $(VER_LIST))/g" $@
	sed -i "s/%LIB_VERSION%/$(shell printf '%d_%d' $(VER_LIST))/g" $@

$(DOXYFILE): ./template/Doxyfile.in version.txt
	cp ./template/Doxyfile.in $@
	sed -i "s/%VERSION%/$(VER_TEXT)/g" $@

.PHONY: all clean doc realclean
