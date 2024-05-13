#include <GL/glut.h>
#include <iostream>
#include <map>
#include "ini.h"
#include "OpenGLShapes.h"
#include <cmath>

using namespace std;

int iniHandler(void* user, const char* section, const char* name, const char* value);
void parseResolution(const string& resolution, int& width, int& height);
double calculateCylinderVolume(double bore, double stroke, int numCylinders);
float calculatePressure(float default_volume, float current_volume, float default_pressure);

struct IniData {
    map<string, map<string, string>> sections;
};

const char* ConfigINI = "Config.ini";
const char* EngineINI = "./Engines/1JZ.ini";

float DefaultCylinderVolume = 0.0f;

bool wireframeMode = false;
float xPos = 0.0f;
float yPos = 0.0f;
float Sine = 0.0f;
float sizeScale = 1.0f;

double bore = 0.0f;
double stroke = 0.0f;
double compheight = 0.0f;

int FPS = 24;
int width = 0;
int height = 0;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    float red = 1.0f;
    float blue = 0.0f;
    float green = 0.0f;

    glPushMatrix();
    glTranslatef(xPos, yPos, 0.0f);

    if (wireframeMode) {
        DrawWireframeCylinder(0.0f, 0.0f, 0.0f, 0.0f, static_cast<float>(bore)/sizeScale, static_cast<float>(compheight)/sizeScale, 1.0f, 1.0f, blue, green, red);
    } else {
        DrawSolidCylinder(0.0f, 0.0f, 0.0f, 0.0f, static_cast<float>(bore)/sizeScale, static_cast<float>(compheight)/sizeScale, 1.0f, 1.0f, red, green, blue);
    }

    glPopMatrix();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    cout << "[ConfigLoader]: Loading " << ConfigINI <<  " file " << endl;

    IniData iniData;
    IniData engineData;

    if (ini_parse(ConfigINI, iniHandler, &iniData) < 0) {
        cout << "[ConfigLoader-Error]: Failed to load config file " << ConfigINI << endl;
        return 1;
    }

    if (iniData.sections.count("Graphics") && iniData.sections["Graphics"].count("resolution")) {
        parseResolution(iniData.sections["Graphics"]["resolution"], width, height);
        cout << "Width: " << width << endl;
        cout << "Height: " << height << endl;
    }

    if (iniData.sections.count("Graphics") && iniData.sections["Graphics"].count("fps")) {
        FPS = stoi(iniData.sections["Graphics"]["fps"]);
        cout << "FPS: " << FPS << endl;
    }

    if (iniData.sections.count("Settings") && iniData.sections["Settings"].count("size_scale")) {
        sizeScale = stoi(iniData.sections["Settings"]["size_scale"]);
        cout << "Size scale: " << sizeScale << " 1/mm" << endl;
    }

    if (ini_parse(EngineINI, iniHandler, &engineData) < 0) {
        cout << "[EngineLoader-Error]: Failed to load engine file " << EngineINI << endl;
        return 1;
    }

    if (engineData.sections.count("Size") && engineData.sections["Size"].count("bore") && engineData.sections["Size"].count("stroke") && engineData.sections["Size"].count("cylinders") && engineData.sections["Size"].count("compression_height")) {
        bore = stod(engineData.sections["Size"]["bore"]);
        stroke = stod(engineData.sections["Size"]["stroke"]);
        compheight = stod(engineData.sections["Size"]["compression_height"]);
        int cylinders = stoi(engineData.sections["Size"]["cylinders"]);

        float CylinderVolume = calculateCylinderVolume(bore/10, stroke/10, 1);
        float EngineVolume = CylinderVolume * cylinders;

        cout << "Engine volume: " << EngineVolume << " CC" << endl;

        cout << "Cylinder Volume: " << CylinderVolume << " CC" << endl;
        calculatePressure(CylinderVolume,420.0f,1);
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("EngineSimulator 2D - OpenGL");

    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5, 5, -5, 5, -5, 5);

    glutDisplayFunc(display);
    //glutKeyboardFunc(keyboard);
    //glutSpecialFunc(specialKeys);
    glutMainLoop();

    return 0;
}

int iniHandler(void* user, const char* section, const char* name, const char* value) {
    IniData* iniData = static_cast<IniData*>(user);
    string sec(section ? section : "");
    string key(name ? name : "");
    string val(value ? value : "");

    (*iniData).sections[sec][key] = val;

    return 1;
}

void parseResolution(const string& resolution, int& width, int& height) {
    size_t xPos = resolution.find('x');
    
    if (xPos != string::npos) {
        string widthStr = resolution.substr(0, xPos);
        string heightStr = resolution.substr(xPos + 1);

        width = stoi(widthStr);
        height = stoi(heightStr);
    } else {
        width = 0;
        height = 0;
    }
}

double calculateCylinderVolume(double bore, double stroke, int numCylinders) {
    double CC = 0.7854 * bore * bore * stroke * numCylinders;
    return CC;
}

float calculatePressure(float default_volume, float current_volume, float default_pressure) {
    float moles=1;
    float gas_constant=0.0821;

    float PressureATM = default_pressure * (current_volume / default_volume);
    float PressureBAR = PressureATM * 1.01325;

    cout << "Pressure: " << PressureATM << " atm" << endl;
    cout << "Pressure: " << PressureBAR << " bar" << endl;

    return 1;
}