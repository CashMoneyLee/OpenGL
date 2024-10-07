#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

int FlatShaded = 0;
int Wireframed = 0;

int ViewX = 0, ViewY = 0;

void InitLight() {
    GLfloat mat_diffuse[] = { 0.5, 0.4, 0.3, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
    GLfloat mat_shininess[] = { 15.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat light_position[] = { -3, 6, 3.0, 0.0 };
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void MyMouseMove(GLint X, GLint Y) {
    ViewX = X;
    ViewY = Y;
    glutPostRedisplay();
}

void MyKeyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'q': case 'Q': case '\033':
        exit(0);
        break;
    case 's':
        if (FlatShaded) {
            FlatShaded = 0;
            glShadeModel(GL_SMOOTH);
        }
        else {
            FlatShaded = 1;
            glShadeModel(GL_FLAT);
        }
        glutPostRedisplay();
        break;
    case 'w':
        Wireframed = !Wireframed;
        glutPostRedisplay();
        break;
    }
}

void DrawTable() {
    // 테이블 상판
    glPushMatrix();
    glTranslatef(0.0, -0.5, -1.0); // 상판을 바닥에서 0.5 떨어지도록 수정
    glScalef(1.0, 0.05, 1.0); // 테이블 상판의 크기 조정
    if (Wireframed) {
        glutWireCube(1.0);
    }
    else {
        glutSolidCube(1.0);
    }
    glPopMatrix();

    // 테이블 다리 (위치 수정)
    float legHeight = 0.5; // 다리 높이
    float legWidth = 0.05; // 다리 폭

    // 첫 번째 다리
    glPushMatrix();
    glTranslatef(0.45, -0.75, -0.55); // 다리 위치 수정
    glScalef(legWidth, legHeight, legWidth);
    if (Wireframed) {
        glutWireCube(1.0);
    }
    else {
        glutSolidCube(1.0);
    }
    glPopMatrix();

    // 두 번째 다리
    glPushMatrix();
    glTranslatef(-0.45, -0.75, -0.55);
    glScalef(legWidth, legHeight, legWidth);
    if (Wireframed) {
        glutWireCube(1.0);
    }
    else {
        glutSolidCube(1.0);
    }
    glPopMatrix();

    // 세 번째 다리
    glPushMatrix();
    glTranslatef(0.45, -0.75, -1.45);
    glScalef(legWidth, legHeight, legWidth);
    if (Wireframed) {
        glutWireCube(1.0);
    }
    else {
        glutSolidCube(1.0);
    }
    glPopMatrix();

    // 네 번째 다리
    glPushMatrix();
    glTranslatef(-0.45, -0.75, -1.45);
    glScalef(legWidth, legHeight, legWidth);
    if (Wireframed) {
        glutWireCube(1.0);
    }
    else {
        glutSolidCube(1.0);
    }
    glPopMatrix();
}

void DrawObjects() {
    // 다양한 기하학적 물체 모델링
    glPushMatrix();
    glTranslatef(-0.3, -0.38, -1.0); // 탁자 상판 높이에 맞게 수정
    if (Wireframed) {
        glutWireSphere(0.1, 16, 16);
    }
    else {
        glutSolidSphere(0.1, 16, 16);
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.3, -0.38, -1.0); // 탁자 상판 높이에 맞게 수정
    if (Wireframed) {
        glutWireCube(0.2);
    }
    else {
        glutSolidCube(0.2);
    }
    glPopMatrix();

    // 원뿔을 90도 회전
    glPushMatrix();
    glTranslatef(0.0, -0.38, -0.7); // 탁자 상판 높이에 맞게 수정
    glRotatef(-90, 1.0, 0.0, 0.0); // x축을 기준으로 90도 회전
    if (Wireframed) {
        glutWireCone(0.1, 0.2, 16, 16);
    }
    else {
        glutSolidCone(0.1, 0.2, 16, 16);
    }
    glPopMatrix();
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0.0, 0.0, 2.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);

    // 탁자 그리기
    DrawTable();

    // 기하학적 물체 그리기
    DrawObjects();

    glFlush();
}

void MyReshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 10.0);
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Table with Geometric Objects");

    glClearColor(0.4, 0.4, 0.4, 0.0);
    InitLight();
    glutDisplayFunc(MyDisplay);
    glutKeyboardFunc(MyKeyboard);
    glutMotionFunc(MyMouseMove);
    glutReshapeFunc(MyReshape);
    glutMainLoop();
}



