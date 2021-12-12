// Lab. work ¹4
// Done by Max Shevtsov
// Group: KM-01
#ifdef __APPLE_CC__
#include <iostream>
#include <GLUT/glut.h>
#else
#include <iostream>
#include <GL/glut.h>
#endif

using namespace std;

// For color change.
float red = 0.0;
float green = 1.0;
float blue = 0.0;

// For rotation
bool is_rotate = false;
int axis_z = 1;
int axis_y = 0;
float spin = 0.0;
float spin_speed = 0.01;

// Rotation
void spinDisplay()
{
	spin = spin + spin_speed;
	if (spin > 360.0){
        spin = 0.0;
	}
	glutPostRedisplay();
}

// Object
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(red, green, blue);

    glRotatef(spin_speed, 0, axis_y, axis_z);

    glutWireTeapot(1);

    glFlush();
}

// Change speed
void arrow_keys(int key, int x, int y){
    switch (key){
        case GLUT_KEY_UP:
            cout << "Up key" << endl;
            spin_speed += 0.01;
            break;
        case GLUT_KEY_DOWN:
            cout << "Down key" << endl;
            spin_speed -= 0.01;
            break;
    }
}

// Chnge axis of rotationg and exit
void keyboard(unsigned char key, int x, int y){
    switch (key){
        case 27:
            cout << "Exit key" << endl;
            exit(0);
            break;
        case 32:
            cout << "Space key" << endl;
            if (axis_y == 0){
                axis_z = 0;
                axis_y = 1;
            } else{
                axis_y = 0;
                axis_z = 1;
            }
            break;
    }
}

// Mouse clicking
void mouse(int button, int state, int x, int y){
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
        cout << "Left mouse button" << endl;
        // red green blue
        if (red >= 1.0){
            red = 0.0;
            green = 1.0;
            blue = 0.0;
        } else if (green >= 1.0){
            red = 0.0;
            green = 0.0;
            blue = 1.0;
        } else if (blue >= 1.0){
            red = 1.0;
            green = 0.0;
            blue = 0.0;
        }
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP){
        cout << "Right mouse button" << endl;
        if (is_rotate == false){
            is_rotate = true;
            spin_speed = 0.01;
            glutIdleFunc(spinDisplay);
        } else if(is_rotate == true){
            is_rotate = false;
            spin_speed = 0.0;
            glutIdleFunc(NULL);
        }
    }
}

// Initial state
void init() {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-2, 2, -1.5, 1.5, 1, 40);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -3);
}

// Entry point
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(800, 600);
    glutCreateWindow("LAB 4");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(arrow_keys);
    glutMouseFunc(mouse);

    glutMainLoop();
}
