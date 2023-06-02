CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Isrc/vendor/glm
LDFLAGS = -lglfw -lGLEW -lGL
SRCDIR = src
OBJDIR = obj
BINDIR = bin
SRC = $(shell find $(SRCDIR) -name "*.cpp")
OBJ = $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRC:%=%))
EXEC = $(BINDIR)/cube

# Rules
all: $(BINDIR) $(EXEC)

$(BINDIR):
	mkdir -p $(BINDIR)

$(EXEC): $(OBJ) obj/cube.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: %.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/cube.o: cube.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)
