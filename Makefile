CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Isrc/vendor/glm
LDFLAGS = -lglfw -lGLEW -lGL
SRCDIR = src
VENDORDIR = $(SRCDIR)/vendor
OBJDIR = obj
BINDIR = bin
SRC = $(wildcard $(SRCDIR)/*.cpp)
VENDORSRC = $(wildcard $(VENDORDIR)/imgui/*.cpp) $(wildcard $(VENDORDIR)/stb_image/*.cpp)
OBJ = $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
VENDOROBJ = $(VENDORSRC:$(VENDORDIR)/imgui/%.cpp=$(OBJDIR)/%.o)
VENDOROBJ := $(VENDOROBJ:$(VENDORDIR)/stb_image/%.cpp=$(OBJDIR)/%.o)
EXEC = $(BINDIR)/cube

# Rules
all: $(BINDIR) $(OBJDIR) $(EXEC)

$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(EXEC): $(OBJ) $(VENDOROBJ) cube.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(VENDORDIR)/imgui/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(VENDORDIR)/stb_image/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)
