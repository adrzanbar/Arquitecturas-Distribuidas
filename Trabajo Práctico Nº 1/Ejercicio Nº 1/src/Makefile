# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -pthread

# Target executable
TARGET = run

# Source files
SRCS = logarithm.cpp

# Compile target
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# Clean up compiled files
clean:
	rm -f $(TARGET)
