
# Ethereal Engine

This is a simple 3D game engine made from scratch using OpenGL. The goal of the project was to delve into how graphics rendering and game development works on the lowest possible level of implementation. Also we wanted to enhance our proficiency in Object-oriented design. It contains following features:

- Importing multi-mesh models
- Raycasting
- Collision Detection
- Simple NPC AI 
- Real-time user input 
- Rendering 300+ objects
- Model animations
## Tech Stack

We tried to keep it as simple as possible. We implemented most of the things from scratch using pure OpenGL, except for model importing we used a little help from Assimp library. 

| Category | Libraries |
| -------- | --------- |
| Graphics API | Mesa3D |
| Windowing System | GLFW |
| OpenGL Extension Management | GLEW |
| Sound Management | SFML |
| Asset Importing | Assimp |

## Installation

We used Mesa3D, which includes an implementation of OpenGL, that can run on most operation systems, including Windows, MacOS. However, it's more typically used on Unix-like systems, such as Linux or BSD.  

In order to build the project, you have to install all necessary libraries.

```bash
# Update package list
sudo apt update

# Install Assimp
sudo apt install libassimp-dev

# Install Mesa3D
sudo apt install mesa-common-dev
sudo apt install libglu1-mesa-dev

# Install GLFW
sudo apt install libglfw3-dev

# Install GLEW
sudo apt install libglew-dev

# Install SFML
sudo apt install libsfml-dev

# Build 
make 

```
    
## Entity-Component-System (ECS) Architecture

The game engine uses the ECS architecture, which separates concerns into three distinct elements:

- Entities - These are the game objects, which are represented as a simple unique ID.
- Components - These represent the data associated with different aspects of an entity (like a model, texture, sound, etc).
- Systems - These are the logic segments that operate on entities with a given set of components. They encapsulate the game's functionality.
The ECS architecture is data-oriented and promotes composition over inheritance. Each entity is essentially a composition of different components, and systems act on entities that possess components they are interested in.


## Design Patterns

We implemented following design patterns:
- Singleton (ResourceManager, EntityManager)
- Factory (EntityFactory)
- Facade (OpenGL abstraction)
- Dependency Injection


## Gameplay

It offers high-paced old-school doom-like first-person-shoort gameplay. Player starts in the middle of the map and flying monsters start to spawn all over the map. They fly towards the player and when collision with player occurs we lose health. When player's health drops to zero, the game ends. Enemy count increases with time, so the game is getting harder. 

![Game GIF](https://imgur.com/a/70ie7SN)
## License

[MIT](https://choosealicense.com/licenses/mit/)


## Authors

- [@mrozek](https://gitlab-stud.elka.pw.edu.pl/mrozek)
- [@mbilski](https://gitlab-stud.elka.pw.edu.pl/mbilski)
