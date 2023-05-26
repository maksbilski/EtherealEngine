CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra
LDFLAGS = -lglfw -lGLEW -lGL
SRCDIR = src
OBJDIR = obj
BINDIR = bin
SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
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

clean:
	rm -rf $(OBJDIR) $(BINDIR)