#pragma once

#include <GL/glew.h>

#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"

// clang-format off
#define ASSERT(x)\
  if (!(x))\
    __builtin_trap();
#define GLCall(x)\
  GLClearError();\
  x;\
  ASSERT(GLLogCall(#x, __FILE__, __LINE__))
// clang-format on

void GLClearError();

bool GLLogCall(const char *function, const char *file, int line);

class Renderer {
public:
  void Clear() const;
  void Draw(const VertexArray &va, const IndexBuffer &ib,
            const Shader &shader) const;
};