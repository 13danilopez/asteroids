CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./headers
LDFLAGS = -L/usr/local/lib
LDLIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

TARGET = build/main
MAIN_OBJ = build/main.o
SRC_OBJ = $(patsubst src/%.cpp,build/%.o,$(wildcard src/*.cpp))
OBJ = $(MAIN_OBJ) $(SRC_OBJ)

all: $(TARGET)

build:
	mkdir -p build

$(MAIN_OBJ): main.cpp | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/%.o: src/%.cpp | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -rf build

.PHONY: all clean build