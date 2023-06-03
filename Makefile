CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Isrc/vendor/glm
LDFLAGS = -lglfw -lGLEW -lGL
SRCDIR = src
OBJDIR = obj
BINDIR = bin
SRC = $(shell find $(SRCDIR) -name "*.cpp")
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
