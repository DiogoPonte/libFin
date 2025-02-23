# Compiler settings
CXX = g++
CXXFLAGS = -std=c++11 -Wall -I.

# Directories
BUILDDIR = build
OBJDIR = $(BUILDDIR)/obj

# Source files
SOURCES = main.cpp StochasticRSI.cpp BollingerBands.cpp MovingAverages.cpp DateUtils.cpp
OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)

# Target executable
TARGET = $(BUILDDIR)/libFin

# Default target
all: $(BUILDDIR) $(OBJDIR) $(TARGET)

# Create build directories
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

# Link
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Compile
$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(BUILDDIR)

# Clean and rebuild
rebuild: clean all

# Phony targets
.PHONY: all clean rebuild