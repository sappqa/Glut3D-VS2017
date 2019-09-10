
#include <GL/glut.h>
#include <string>
#include <iostream>

using namespace std;


// Initial window settings
int initialXpos = 1000;
int initialYpos = 100;
int initialWidth = 300;
int initialHeight = 300;

// Transformation variables
const GLfloat Z_OFFSET = -8.0f;
GLfloat xAxisRotation = 0.0f;
GLfloat yAxisRotation = 0.0f;
GLfloat zAxisRotation = 0.0f;

// If constant rotation, then how fast?
GLfloat xAxisRotationSpeed = 0.0f;
GLfloat yAxisRotationSpeed = 0.0f;
GLfloat zAxisRotationSpeed = 0.0f;

// Perspective constants
const GLdouble FIELD_OF_VIEW = 60;
const GLdouble Z_NEAR_CLIP = 0.5;
const GLdouble Z_FAR_CLIP = 20;

// User defined variables
string currentObject = "teapot";
string axis = "";

// Glut 3D Object names
const int NUM_OBJECTS = 9;
const string NAMES[] = {
	"cone", "cube", "dodecahedron", "icosahedron",
	"octahedron", "sphere", "teapot", "tetrahedron", "torus"
};

// 3D object size constants
const GLint SLICES = 10;
const GLint STACKS = 10;
const double CONE_BASE = 3.0;
const double CONE_HEIGHT = 4.0;
const double CUBE_SIZE = 3.0;
const double TEAPOT_SIZE = 2.0;
const double SPHERE_RADIUS = 3.0;
const GLint TORUS_SIDES = 20;
const GLint TORUS_RINGS = 20;
const GLdouble TORUS_INNER_RADIUS = 1.0;
const GLdouble TORUS_OUTER_RADIUS = 3.0;


/**
 * Initializes display settings. 
 */
void init() {
	// Black background
	glClearColor(0.0, 0.0, 0.0, 0.0);

	// These settings need to be enabled to make the teapot look the way it does.
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glShadeModel(GL_SMOOTH);

	// Initialize the projection matrix so that we can view things in perspective.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

/**
 * Sets up perspective view.
 */
void reshape(int w, int h) {
	GLdouble aspect = (GLdouble)w / (GLdouble)h;

	// OpenGL will use the entire window space to draw.
	glViewport(0, 0, w, h);
	// Set up perspective viewing.
	gluPerspective(FIELD_OF_VIEW, aspect, Z_NEAR_CLIP, Z_FAR_CLIP);
	glutPostRedisplay();
}

/**
 * We need this to translate the user input to lowercase.
 * That way, the user's choice of case doesn't matter.
 */
string toLowerCase(string s) {
	int length = s.length();
	for (int i = 0; i < length; i++) {
		s[i] = tolower(s[i]);
	}

	return s;
}

/**
 * If the user wants to draw a different shape than the
 * default one, we need to ask them which shape they want to draw.
 */
void askWhichObject() {
	cout << "What 3D object do you want to draw?" << endl;

	// Prints the names of all GLUT pre-made 3D objects/shapes
	for (int i = 0; i < NUM_OBJECTS; i++) {
		cout << "(" << i+1 << ") " << NAMES[i] << endl;
	}

	/* Checks user input to make sure they actually request
	   to draw a shape. */
	int answer = -1;
	while (answer < 1 || answer > 9) {
		cin >> answer;
	}
	string s = toLowerCase(NAMES[answer - 1]);

	currentObject = s;
}

/**
 * Prompts the user to input which axis (x, y, or z) they wish to apply a rotation to.
 * Sets a variable accordingly.
 */
void askWhichAxis() {
	while (axis != "x" && axis != "y" && axis != "z") {
		cout << "Which axis do you want to rotate the " << currentObject << " around? (x, y, or z?)" << endl;
		cin >> axis;
	}
}

/**
 * Prompts the user to input a rotation value about the current axis.
 * Sets a variable accordingly.
 */
void setSnapRotationValues() {
	cout << "What degree angle do you want to rotate the " << axis << " axis?" << endl;
	GLfloat angle = 0;
	if (axis == "x") {
		cin >> angle;
		xAxisRotation += angle;
	} else if (axis == "y") {
		cin >> angle;
		yAxisRotation += angle;
	}

	else if (axis == "z") {
		cin >> angle;
		zAxisRotation += angle;

	} else {
		cout << "Something went wrong" << endl;
	}
}

/**
 * Prompts the user to input a value (1-10) for the continuous rotation speed about the current axis.
 * Sets a variable accordingly.
 */
void setRotationSpeedValues() {
	// Get a rotation speed value from the user.
	GLfloat userInput = -1.0f;
	while (userInput < 0 || userInput > 10) {
		cout << "How fast do you want to rotate about the " << axis << " axis? (0-10)" << endl;
		cin >> userInput;
	}

	// Multiply this by the user input to get a reasonable rotation speed.
	GLfloat scale = 0.01f;
	GLfloat speed = userInput * scale;
	if (axis == "x")
		xAxisRotationSpeed = speed;
	else if (axis == "y")
		yAxisRotationSpeed = speed;
	else if (axis == "z")
		zAxisRotationSpeed = speed;
	else
		cout << "Something went wrong" << endl;
}

/**
 * 
 */
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'o':
		askWhichObject();
		break;

	case 'r':
		askWhichAxis();
		setSnapRotationValues();
		axis = "";
		break;

	case 's':
		askWhichAxis();
		setRotationSpeedValues();
		axis = "";
		break;

	case 27: //Esc key
		exit(0);
		break;

	default:
		break;
	}
	glutPostRedisplay();
}

/**
 * Handles continuous rotation
 */
void idle() {
	// Rotation about the x axis
	xAxisRotation += xAxisRotationSpeed;
	if (xAxisRotation > 360.0) {
		xAxisRotation = 0;
	}

	// Rotation about the y axis
	yAxisRotation += yAxisRotationSpeed;
	if (yAxisRotation > 360.0) {
		yAxisRotation = 0;
	}

	// Rotation about the z axis
	zAxisRotation += zAxisRotationSpeed;
	if (zAxisRotation > 360.0) {
		zAxisRotation = 0;
	}

	glutPostRedisplay();
}

/**
 * Applies a rotation transformation to the modelview matrix.
 */
void rotateObject() {
	glRotatef(xAxisRotation, 1.0f, 0.0f, 0.0f);
	glRotatef(yAxisRotation, 0.0f, 1.0f, 0.0f);
	glRotatef(zAxisRotation, 0.0f, 0.0f, 1.0f);
}

/**
 * Renders the currently selected GLUT 3D primitive.
 */
void drawCurrentObject() {
	if (currentObject == NAMES[0]) {
		glutSolidCone(CONE_BASE, CONE_HEIGHT, SLICES, STACKS);
	} else if (currentObject == NAMES[1]) {
		glutSolidCube(CUBE_SIZE);
	} else if (currentObject == NAMES[2]) {
		glutSolidDodecahedron();
	} else if (currentObject == NAMES[3]) {
		glutSolidIcosahedron();
	} else if (currentObject == NAMES[4]) {
		glutSolidOctahedron();
	} else if (currentObject == NAMES[5]) {
		glutSolidSphere(SPHERE_RADIUS, SLICES, STACKS);
	} else if (currentObject == NAMES[6]) {
		glutSolidTeapot(TEAPOT_SIZE);
	} else if (currentObject == NAMES[7]) {
		glutSolidTetrahedron();
	} else if (currentObject == NAMES[8]) {
		glutSolidTorus(TORUS_INNER_RADIUS, TORUS_OUTER_RADIUS,
			TORUS_SIDES, TORUS_RINGS);
	}
}

/**
 * Displays the user specified surface plus any transformations.
 */
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Move the object into place (otherwise the camera wouldn't see it)
	glTranslatef(0.0f, 0.0f, Z_OFFSET);

	// Rotate the object and then draw it
	rotateObject();
	drawCurrentObject();
	glutSwapBuffers();
}

/**
 * Initializes GLUT and prompts the user.
 */
int main(int argc, char** argv) {
	// User commands
	cout << "Controls:" << endl;
	cout << "(o) Change object" << endl;
	cout << "(r) Apply snap rotation" << endl;
	cout << "(s) Apply continuous rotation" << endl;

	// Initialize the glut library
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	// Create the window
	glutInitWindowPosition(initialXpos, initialYpos);
	glutInitWindowSize(initialWidth, initialHeight);
	glutCreateWindow("3D");

	init();
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutMainLoop();
}