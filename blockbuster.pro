TEMPLATE = subdirs

SUBDIRS += src tests

# Allow running "make test"
test.depends = sub-tests
test.commands = bin/test
QMAKE_EXTRA_TARGETS += test

# Generate documentation with Doxygen using "make doc"
dox.target = doc
dox.depends = src
dox.commands = doxygen Doxyfile && xdg-open doc/html/index.html 2>/dev/null
QMAKE_EXTRA_TARGETS += dox

# FIXME: make clean does not delete the doc directory
cleandox.target = cleandoc
cleandox.commands = rm -rf doc
QMAKE_EXTRA_TARGETS += cleandox
