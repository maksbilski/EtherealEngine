CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Isrc/vendor/glm
LDFLAGS = -lglfw -lGLEW -lGL
SRCDIR = src
OBJDIR = obj
BINDIR = bin
SRC = $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/vendor/stb_image/*.cpp)
OBJ = $(patsubst %.cpp,$(OBJDIR)/%.o,$(notdir $(SRC)))
EXEC = $(BINDIR)/cube

# Rules
all: $(BINDIR) $(OBJDIR) $(EXEC)

$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(EXEC): $(OBJ) cube.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/vendor/stb_image/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)
