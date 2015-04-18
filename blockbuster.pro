TEMPLATE = subdirs

SUBDIRS += src tests

# Allow running "make test"
test.depends = sub-tests
test.commands = bin/test
QMAKE_EXTRA_TARGETS += test
