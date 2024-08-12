# Makefile for SFML Circle Movement

CXX = g++
CXXFLAGS = -std=c++17 -Wall -I/path/to/sfml/include
LDFLAGS = -L/path/to/sfml/lib -lsfml-graphics -lsfml-window -lsfml-system

SRC = main.cpp
OBJ = $(SRC:.cpp=.o)
EXE = circle_movement

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJ) $(EXE)
