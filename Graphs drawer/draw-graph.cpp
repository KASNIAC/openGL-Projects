// KASNIAC.com

#include "GL/glut.h"
#include<iostream>
#include<string>
#include<vector>
#include<cmath>

int windowWidth = 600; // Ancho de ventana inicial
int windowHeight = 600; // Alto de ventana inicial

int vertices, aristas;
constexpr double radio = 0.8;
constexpr double aumento = 0.08;
std::vector<int> lista[50]; // Máximo 50 vertices

void iniciar();
void reshape(int, int);
void dibujar();
void teclado(unsigned char, int, int);
void guarda_imagen();


int main(int argc, char* args[]){
    glutInit(&argc,args);

    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);


    // glutInitWindowPosition(0,0);

    int screenWidth = glutGet(GLUT_SCREEN_WIDTH); // Obtener el ancho de la pantalla
    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT); // Obtener el alto de la pantalla
    /// glutInitWindowSize(screenWidth, screenHeight); // Usar el tamaño de la pantalla como el tamaño de la ventana
    glutInitWindowSize(500, 500);

    std::cin>>vertices>>aristas;

    for(int i = 0; i<aristas; ++i){
       int v1,v2; std::cin>>v1>>v2;

       lista[v1].push_back(v2);
       // lista[v2].push_back(v1); /// Sólo si la gráfica es dirigida
    }


    int d = glutCreateWindow("Graficadora");  // std::cout<<d<<"\n";

    iniciar();

    glutMainLoop();
}

void iniciar(){
    // glClearColor(0.96,0.84,0.47,0.56);
    glClearColor(0.44,0.44,0.66,0.0); /// Color del fondo


    glutDisplayFunc(dibujar);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(teclado);
        // glColor3f(1.f,0,0);
        // glLineWidth(3.f);

    glOrtho(800,0,600,0,-1,1);

    glMatrixMode(GL_MODELVIEW); // Le decimos que vamos a usar MATRICES
    glLoadIdentity();   // Cargamos la matriz identidad, ahora ya tenemos un positivo en x y un negativo a partir del centro de la pantalla
}

void reshape(int w, int h){

     glViewport(0, 0, w, h);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();

     // Mantener relación de aspecto constante
     if (w <= h)
       glOrtho(-1.0, 1.0, -1.0 * (GLfloat)h / (GLfloat)w, 1.0 * (GLfloat)h / (GLfloat)w, -1.0, 1.0);
     else
       glOrtho(-1.0 * (GLfloat)w / (GLfloat)h, 1.0 * (GLfloat)w / (GLfloat)h, -1.0, 1.0, -1.0, 1.0);

     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
}

void dibujar(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    double grados = 360.0 / vertices;
    double pi = 3.14159265358979323846;
    double radianes = (grados * pi) / 180;

    // Primer dibujamos todas las aristas para evitar que se sobrepongan a los vértices
    for(int i = 0; i<vertices; ++i){
      glPushMatrix();
            // ----- Dibuja aristas -----
          glLineWidth(3.f);
          glColor4f(0.0, 0.0, 0.0,0.3);
          for(int vecino : lista[i]){
               if(vecino != i){
                  glBegin(GL_LINES);
                     glVertex2f(radio*std::cos(radianes*i),radio*std::sin(radianes*i));
                     glVertex2f(radio*std::cos(radianes*vecino),radio*std::sin(radianes*vecino));
                   glEnd();
               } else{
                  glPushMatrix();
                     glTranslatef((radio + aumento)*std::cos(radianes*i),(radio + aumento)*std::sin(radianes*i),0);

                     gluDisk(gluNewQuadric(), 0, 0.05, 20, 1);

                     glColor4f(0.44,0.44,0.66,0.0);
                     gluDisk(gluNewQuadric(), 0, 0.045, 20, 1);
                  glPopMatrix();
               }

          }
          // ----- Dibuja aristas -----
      glPopMatrix();
    }

    for(int i = 0; i<vertices; ++i){
      glPushMatrix();
          glTranslatef(radio*std::cos(radianes*i),radio*std::sin(radianes*i),0);
          // ----- Dibuja vértices -----
          // glColor4f(0.2*i, 0.0, 0.0,0.3);
          glColor4f(0.0, 0.0, 0.0,0.3);
          gluDisk(gluNewQuadric(), 0, 0.07, 30, 1);

          glColor4f(1.0, 1.0, 1.0,0.3);
          gluDisk(gluNewQuadric(), 0, 0.065, 20, 1);
          // ----- Dibuja vértices -----

          // ----- Escribe texto -----
          glColor3f(0.0, 0.0, 0.0); // Color del texto

          std::string numero = "v" + std::to_string(i);
          glRasterPos2f(-((float)numero.size())/100.0, 0.0);

          void* font = GLUT_BITMAP_9_BY_15;
          for (std::string::iterator j = numero.begin(); j != numero.end(); ++j){
              char c = *j;
              glutBitmapCharacter(font, c);
          }
          // ----- Escribe texto -----
      glPopMatrix();
    }

   /*
      glPointSize(10);
   glBegin(GL_POINTS);
      glVertex2f(1.2,0.0);
   glEnd();
   */

    glFlush();
}

void teclado(unsigned char key, int x, int y){
   switch(key){
      // case 'g': guarda_imagen(); break;
   }
}

