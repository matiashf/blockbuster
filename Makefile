CC=g++
CCOPT=-std=c++11 -Wall -g -I/usr/include/bullet/
LDOPT=-l BulletDynamics -l BulletCollision -l LinearMath

# Headers: .hpp-files
HEADERS=$(wildcard *.hpp)
# All objects: All .o-files
OBJECTS=$(patsubst %.cpp,%.o,$(wildcard *.cpp))
# Included objects: .o-files for all pairs of corresponding .hpp and .cpp files
INCLUDED_OBJECTS=$(filter $(patsubst %.hpp,%.o,$(HEADERS)),$(OBJECTS))
# Executable objects: .o-files for all .cpp files without a corresponding .hpp-file
EXECUTABLE_OBJECTS=$(filter-out $(INCLUDED_OBJECTS),$(OBJECTS))
# Executables: The complete, runnable binaries. One for each executable object
EXECUTABLES=$(patsubst %.o,%,$(EXECUTABLE_OBJECTS))

all: $(EXECUTABLES)

$(OBJECTS): %.o: %.cpp $(HEADERS)
	$(CC) $(CCOPT) -c -o $@ $<

$(EXECUTABLES): %: %.o $(INCLUDED_OBJECTS)
	$(CC) -o $@ $^ $(LDOPT)

clean:
	-$(RM) $(EXECUTABLES) $(OBJECTS)

.PHONY: all clean
