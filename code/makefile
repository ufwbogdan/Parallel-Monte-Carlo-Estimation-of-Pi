# this is the makefile of the project used to run the experiments a lot easier and faster
#here are the compiler flags
CXX = g++
CXXFLAGS = -O2 -std=c++17 -Wall -fopenmp

TARGET = monteCarlo
SRC = monteCarlo.cpp   

# here you can change both the N (number of sample points) and the number of threads
N ?= 1000000000
NUM_THREADS ?= 12

all: $(TARGET)
	@echo "Running $(TARGET) with N=$(N), NUM_THREADS=$(NUM_THREADS)"
	./$(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -DN=$(N) -DNUM_THREADS=$(NUM_THREADS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) *.o
	@echo "Cleaned up!"

.PHONY: all clean
