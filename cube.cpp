#include <GL/freeglut.h>

float angle = 0.0;

// Handles the keyboard event
void specialKeys(int key, int x, int y) {
  switch (key) {
  case GLUT_KEY_RIGHT:
    angle += 5.0f;
    break;
  case GLUT_KEY_LEFT:
    angle -= 5.0f;
    break;
  default:
    break;
  }
  glutPostRedisplay();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  glRotatef(angle, 0.0, 1.0, 0.0);

  glColor3f(1.0, 0.0, 0.0);

  glutWireCube(1.0);

  glutSwapBuffers();
}

// Add reshape function to handle window resizing events
void reshape(int width, int height) {
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (float)width / (float)height, 1.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(400, 400);
  glutCreateWindow("OpenGL Cube");

  glEnable(GL_DEPTH_TEST);

  glutDisplayFunc(display);
  glutReshapeFunc(reshape); // Set the reshape callback for the current window.
  glutSpecialFunc(specialKeys);

  glutMainLoop();

  return 0;
}
