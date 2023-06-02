#pragma once

#include <glm/glm.hpp>

struct Color {
    unsigned int r, g, b, a;

    Color(unsigned int r, unsigned int g, unsigned int b, unsigned int a) : r(r), g(g), b(b), a(a) {}
    Color(unsigned int r, unsigned int g, unsigned int b) : r(r), g(g), b(b), a(255) {}
    Color(unsigned int r, unsigned int g) : r(r), g(g), b(255), a(255) {}
    Color(unsigned int r) : r(r), g(255), b(255), a(255) {}

    Color(float r, float g, float b, float a) : r((int) r * 255), g((int) g * 255), b((int) b * 255), a((int) a * 255) {}
    Color(float r, float g, float b) : r((int) r * 255), g((int) g * 255), b((int) g * 255), a(255) {}
    Color(float r, float g) : r((int) r * 255), g((int) g * 255), b(0), a(255) {}
    Color(float r) : r((int) r * 255), g(0), b(0), a(255) {}

    Color() : r(0), g(0), b(0), a(255) {}

    int get_r() { return r; }
    int get_g() { return g; }
    int get_b() { return b; }
    int get_a() { return a; }

    int get_float_r() { return r / 255.0f; }
    int get_float_g() { return g / 255.0f; }
    int get_float_b() { return b / 255.0f; }
    int get_float_a() { return a / 255.0f; }

    glm::vec3 get_rgb() { return glm::vec3(get_r(), get_g(), get_b()); }
    glm::vec4 get_rgba() { return glm::vec4(get_r(), get_g(), get_b(), get_a()); }
    
    glm::vec3 get_float_rgb() { return glm::vec3(get_float_r(), get_float_g(), get_float_b()); }
    glm::vec4 get_float_rgba() { return glm::vec4(get_float_r(), get_float_g(), get_float_b(), get_float_a()); }

    void set_r(unsigned int new_r) { this->r = new_r; }
    void set_g(unsigned int new_g) { this->g = new_g; }
    void set_b(unsigned int new_b) { this->b = new_b; }
    void set_a(unsigned int new_a) { this->a = new_a; }

    void set_float_r(float new_r) { this->r = (int) (new_r * 255); }
    void set_float_g(float new_g) { this->g = (int) (new_g * 255); }
    void set_float_b(float new_b) { this->b = (int) (new_b * 255); }
    void set_float_a(float new_a) { this->a = (int) (new_a * 255); }

    void set_rgb(glm::vec3 new_rgb) {
        this->r = new_rgb.r;
        this->g = new_rgb.g;
        this->b = new_rgb.b;
    }

    void set_rgba(glm::vec4 new_rgba) {
        this->r = new_rgba.r;
        this->g = new_rgba.g;
        this->b = new_rgba.b;
        this->a = new_rgba.b;
    }

    void set_float_rgb(glm::vec3 new_rgb) {
        this->r = (int) new_rgb.r * 255;
        this->g = (int) new_rgb.g * 255;
        this->b = (int) new_rgb.b * 255;
    }

    void set_float_rgba(glm::vec4 new_rgba) {
        this->r = (int) new_rgba.r * 255;
        this->g = (int) new_rgba.g * 255;
        this->b = (int) new_rgba.b * 255;
        this->a = (int) new_rgba.b * 255;
    }
};