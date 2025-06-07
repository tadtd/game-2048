CXX = g++
CXXFLAGS = -std=c++11 -O0
TARGET = 2048
SOURCES = main.cpp Resources/*.cpp

all:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

.PHONY: all clean