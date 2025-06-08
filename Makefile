CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
MAIN = main.cpp
OUT = program

all: $(OUT)

$(OUT): $(OBJ) $(MAIN)
	$(CXX) $(CXXFLAGS) $(OBJ) $(MAIN) -o $(OUT)

clean:
	rm -f $(OBJ) $(OUT)
