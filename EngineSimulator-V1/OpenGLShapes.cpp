#include "OpenGLShapes.h"

void DrawSolidCylinder(float x, float y, float z, float rotation, float scaleX, float scaleY, float scaleZ, float scaleF, float r, float g, float b) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(rotation, 0.0f, 1.0f, 0.0f);
    glColor3f(r, g, b);

    glScalef(scaleX, scaleY, scaleZ);
    glutSolidCube(scaleF);

    glPopMatrix();
}

void DrawWireframeCylinder(float x, float y, float z, float rotation, float scaleX, float scaleY, float scaleZ, float scaleF, float r, float g, float b) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(rotation, 0.0f, 1.0f, 0.0f);
    glColor3f(r, g, b);

    glScalef(scaleX, scaleY, scaleZ);
    glutWireCube(scaleF);

    glPopMatrix();
}

void DrawSolidTriangle(float x, float y, float z, float rotation, float scaleX, float scaleY, float scaleZ, float color[3]) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(rotation, 0.0f, 1.0f, 0.0f);
    glColor3fv(color);

    glScalef(scaleX, scaleY, scaleZ);
    glBegin(GL_TRIANGLES);
        glVertex3f(-0.5f, 0.0f, 0.0f);
        glVertex3f(0.5f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.5f, 0.0f);
    glEnd();

    glPopMatrix();
}

void DrawWireframeTriangle(float x, float y, float z, float rotation, float scaleX, float scaleY, float scaleZ, float color[3]) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(rotation, 0.0f, 1.0f, 0.0f);
    glColor3fv(color);

    glScalef(scaleX, scaleY, scaleZ);
    glBegin(GL_LINE_LOOP);
        glVertex3f(-0.5f, 0.0f, 0.0f);
        glVertex3f(0.5f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.5f, 0.0f);
    glEnd();

    glPopMatrix();
}

void DrawSolidSphere(float x, float y, float z, float rotation, float scaleX, float scaleY, float scaleZ, float radius, int slices, int stacks, float color[3]) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(rotation, 0.0f, 1.0f, 0.0f);
    glColor3fv(color);

    glScalef(scaleX, scaleY, scaleZ);
    glutSolidSphere(radius, slices, stacks);

    glPopMatrix();
}

void DrawWireframeSphere(float x, float y, float z, float rotation, float scaleX, float scaleY, float scaleZ, float radius, int slices, int stacks, float color[3]) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(rotation, 0.0f, 1.0f, 0.0f);
    glColor3fv(color);

    glScalef(scaleX, scaleY, scaleZ);
    glutWireSphere(radius, slices, stacks);

    glPopMatrix();
}
