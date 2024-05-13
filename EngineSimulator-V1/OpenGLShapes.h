#ifndef OPENGL_SHAPES_H
#define OPENGL_SHAPES_H

#include <GL/glut.h>

void DrawSolidCylinder(float x, float y, float z, float rotation, float scaleX, float scaleY, float scaleZ, float scaleF, float r, float g, float b);
void DrawWireframeCylinder(float x, float y, float z, float rotation, float scaleX, float scaleY, float scaleZ, float scaleF, float r, float g, float b);

void DrawSolidTriangle(float x, float y, float z, float rotation, float size, float color[3]);
void DrawWireframeTriangle(float x, float y, float z, float rotation, float size, float color[3]);
void DrawSolidSphere(float x, float y, float z, float rotation, float radius, int slices, int stacks, float color[3]);
void DrawWireframeSphere(float x, float y, float z, float rotation, float radius, int slices, int stacks, float color[3]);

#endif // OPENGL_SHAPES_H
