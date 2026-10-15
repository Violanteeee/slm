CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2

all: slm

slm: src/main.o src/model.o src/TextGenerator.o
	$(CXX) $(CXXFLAGS) -o slm src/main.o src/model.o src/TextGenerator.o

src/main.o: src/main.cpp src/Model.h src/TextGenerator.h
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o $@

src/model.o: src/model.cpp src/Model.h
	$(CXX) $(CXXFLAGS) -c src/model.cpp -o $@

src/TextGenerator.o: src/TextGenerator.cpp src/TextGenerator.h src/Model.h
	$(CXX) $(CXXFLAGS) -c src/TextGenerator.cpp -o $@

clean:
	rm -f src/*.o slm

.PHONY: all clean
