CXX = g++
CXXFLAGS = -g -std=c++20 -Wall -Wextra -Isrc -Isrc/Components -Isrc/Systems -Isrc/engine -Isrc/vendor/glm -I/path/to/assimp/include # Add Assimp include path here if needed
LDFLAGS = -lglfw -lGLEW -lGL -lassimp -lsfml-audio# Add -lassimp to link against Assimp library
SRCDIR = src
OBJDIR = obj
BINDIR = bin
SRC = $(shell find $(SRCDIR) -name "*.cpp" -not -path "$(SRCDIR)/vendor/glm/*")
OBJ = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(filter-out $(SRCDIR)/vendor/glm/%, $(SRC)))
EXEC = $(BINDIR)/cube

# Rules
all: directories $(EXEC)

directories: $(OBJDIR) $(BINDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

$(EXEC): $(OBJ) $(OBJDIR)/main.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/main.o: main.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)
