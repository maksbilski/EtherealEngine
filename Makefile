CXX = g++
CXXFLAGS = -g -std=c++20 -Wall -Wextra -Isrc -Isrc/Components -Isrc/Systems -Isrc/gl_facade -Isrc/vendor/glm -I/path/to/assimp/include # Add Assimp include path here if needed
LDFLAGS = -lglfw -lGLEW -lGL -lassimp -lsfml-audio# Add -lassimp to link against Assimp library
SRCDIR = src
OBJDIR = obj
BINDIR = bin
SRC = $(shell find $(SRCDIR) -name "*.cpp" -not -path "$(SRCDIR)/vendor/glm/*")
OBJ = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(filter-out $(SRCDIR)/vendor/glm/%, $(SRC)))
EXEC = $(BINDIR)/cube

# Rules
all: directories $(EXEC) tests

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

tests: enemy_health_component_test player_health_component_test transform_component_test weapon_component_test
	$(BINDIR)/EnemyHealthComponentTestCase --success
	$(BINDIR)/PlayerHealthComponentTestCase --success
	$(BINDIR)/TransformComponentTestCase --success
	$(BINDIR)/WeaponComponentTestCase --success

enemy_health_component_test:
	mkdir bin
	$(CXX) $(CXX_FLAGS) src/components/EnemyHealthComponent.cpp src/tests/EnemyHealthComponentTest.cpp -o $(BINDIR)/EnemyHealthComponentTestCase

player_health_component_test:
	$(CXX) $(CXX_FLAGS) src/components/PlayerHealthComponent.cpp src/tests/PlayerHealthComponentTest.cpp -o $(BINDIR)/PlayerHealthComponentTestCase

transform_component_test:
	$(CXX) $(CXX_FLAGS) src/components/TransformComponent.cpp src/tests/TransformComponentTest.cpp -o $(BINDIR)/TransformComponentTestCase

weapon_component_test:
	$(CXX) $(CXX_FLAGS) src/components/WeaponComponent.cpp src/tests/WeaponComponentTest.cpp -o $(BINDIR)/WeaponComponentTestCase
