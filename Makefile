CXX ?= g++
CPPFLAGS ?= -Iinclude
CXXFLAGS ?= -std=c++11 -Wall -Wextra
LDFLAGS ?=
LDLIBS ?=

TARGET := bin/tp3.out
SOURCES := $(wildcard src/*.cpp)
OBJECTS := $(patsubst src/%.cpp,obj/%.o,$(SOURCES))
HEADERS := $(wildcard include/*.h)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS) | bin
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

obj/%.o: src/%.cpp $(HEADERS) | obj
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

bin obj:
	mkdir -p $@

clean:
	rm -f $(OBJECTS) $(TARGET)
