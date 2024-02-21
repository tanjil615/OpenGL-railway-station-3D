#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>
#include "BmpLoader.h"
#include<mmsystem.h>

double Txval=0,Tyval=0,Tzval=0;
GLUquadric* qobj;

double windowHeight=2000, windowWidth=900;
GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0;
GLboolean bRotate = false, uRotate = false,welRotate = true, walkrotate1=true, walkrotate2=false,night=false;

GLfloat fTheta = 0.0 ;

GLfloat faTheta = 0.0 ;
GLfloat ftTheta = 0.0 ;
GLboolean fanFlag = false, spotLight = false, Light1 = false, Light2 = false, ambL = true, diffL = true, specL = true;
GLfloat dx, dy, dz, dxyz;
double roll_value = 0.2, pi = acos(-1), cs_angle=cos(pi/180), sn_angle=sin(pi/180);
unsigned int ID[1000];
int k=0;
float p=0;
float walk=0;
float walk2=0;
float walk3=0;
float walk4=0;
int wel[7]={28,29,30,31,32,33,34};
int sound=0;
/*float walk[100]={0.0};
float walk2[10]={0.0};
float walk3[10]={0.0};
float walk4[10]={0.0};*/
float ws=0;

GLboolean ambL1 = false, ambL2 = false, ambL3 = false, diffL1 = false, diffL2 = false, diffL3 = false, specL1 = false, specL2 = false, specL3 = false;
GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 }, light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_ambient1[]  = { 0.2, 0.2, 0.2, 1.0 }, light_diffuse1[]  = { 1.0, 1.0, 1.0, 1.0 };  //white
GLfloat light_ambient2[]  = {0.0, 0.0, 0.5, 1.0}, light_diffuse2[]  = { 0.0, 0.0, 1.0, 1.0 };  //blue
GLfloat light_ambient3[]  = {0.5, 0.5, 0.5, 1.0}, light_diffuse3[]  = { 1.0, 1.0, 1.0, 1.0 };  //white
GLfloat light_ambient4[]  = {0.5, 0.5, 0.5, 1.0}, light_diffuse4[]  = { 1.0, 1.0, 1.0, 1.0 };  //white
static int slices = 16;
static int stacks = 16;

static GLfloat v_pyramid[65][3] =
{
    {0.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {0.0, 1.0, 1.0},
    {1.0, 1.0, 0.0},
    {1.0, 1.0, 1.0},
    {1.57, 5.0, 1.0},
    {1.57, -5.0, 1.0},
    {1.0, 0.0, 0.0},//7
    {1.0, 0.0, 1.0},
    {0.0, 0.0, 1.0},//9
    {0.0, 10.0, 0.0}, //10
    {0.0, 0.0, 14.0},  //11
    {0.0, 10.0, 14.0},//12
    {-0.3, 0.7, 0.0},
    {-0.3, 0.7, 1.0},
    {1.3, 0.7, 0},
    {1.3, 0.7, 1.0},//16
    {-1.73, 1.0, 1.0},
    {-1.73, 1.0, 0.0},//18
    {-1.73, 3.0, 1.0},
    {-1.73, 3.0, 0.0},//20
    {0.0, 4.0, 1.0},
    {0.0, 4.0, 0.0},//22
    {1.73, 3.0, 0.0},//23
    {1.73, 3.0, 1.0},//24
    {1.73, 1.0, 1.0},//25
    {1.73, 1.0, 0.0},//26
    {1.0, 2.0, 0.0},//27 chimni point
    {3.0, 2.0, 0.0},//28
    {5, 0.0, 0.0},//29
    {0.0, 0.0, 2.0},//30
    {1.0, 2.0, 2.0},//31
    {3.0, 2.0, 2.0},//32
    {5.0, 0.0, 2.0},//33
    {0.0, 0.0, 0.0},//34
    {0.0, 1.0, 0.0},//35
    {0.0, 1.0, 1.0},//36
    {0.0, 0.0, 1.0},//37
    {0.0, 0.0, 0.0},//38 //rail uchu
    {0.0, 1.0, 0.2},//39
    {0.0, 1.0, 2.2},//40
    {0.0, 0.0, 2.4},//41
    {2.0, 0.0, 0.0},//42 //
    {2.0, 1.0, 0.2},//43
    {2.0, 1.0, 2.2},//44
    {2.0, 0.0, 2.4},//45//////////jhjs//dsd
    {-2.0, 0.0, 1.5},//46
    {-0.75, 0.0, 1.25},//47
    {-1.75, 0.0, 2.5},//48
    {-0.5, 0.0, 2},//49
    {0.0, 0.0, 4.0},//50
    { 0.5, 0.0, 2},//51
    {1.75, 0.0, 2.5},//52
    {0.75, 0.0, 1.25},//53
    {2.0, 0.0, 1.5},//54
    {-2.0, -0.25, 1.5},//55
    {-0.75, -0.25, 1.25},//56
    {-1.75, -0.25, 2.5},//57
    {-0.5, -0.25, 2},//58
    {0.0, -0.25, 4.0},//59
    { 0.5, -0.25, 2.0},//60
    {1.75, -0.25, 2.5},//61
    {0.75, -0.25, 1.25},//62
    {2.0, -0.25, 1.5},//63
    {0.0, -0.25, 0.0}//64
};

static GLubyte p_Indices[10][3] =
{
    {0, 1, 5},
    {1, 2, 5},
    {2,3, 5},
    {3,4, 5},
    {4,0, 5},
    {6, 1, 0},
    {6, 2, 1},
    {6,2, 3},
    {6,4, 3},
    {6,0, 4}

};
static GLubyte quadIndices[32][4] =
{
    {0, 7, 8, 9},
    {0, 9, 2, 1},
    {0, 1, 3, 7},
    {3, 7, 8, 4},
    {8, 4, 2, 9},//4
    {3, 7, 8, 4},
    {1, 2, 4, 3},
    {0, 11, 12, 10},
    {0, 7, 8, 9},//basket start 8
    {0, 7, 8, 9},
    {0, 7, 8, 9},
    {9, 14, 13, 0},
    {7, 15, 16, 8},
    {0, 13, 15, 7},
    {8, 16 ,14 ,9},
    {0, 9, 17, 18}, //hexa 15
    {18, 17, 19, 20},
    {20, 19, 21, 22},
    {22, 21, 24, 23},
    {23, 24, 25, 26},//19
    {26, 25, 9, 0},//20
    {0, 27, 28, 29},//21 chimni
    {30, 33, 32, 31},//22
    {28, 32, 33, 29},//23
    {27, 0, 30, 31},//24
    {27, 31, 32, 28},//25
    {38, 39, 40, 41},//26 rail uchu
    {38, 39, 43, 42},//27
    {42, 43, 44, 45},//28
    {39, 40, 44, 43},//29
    {41, 45, 44, 40},//30
    {38, 41, 45, 42}//31
};
static GLubyte leafqIndices[10][4] =
{
    {0, 64, 55, 46},
    {56, 47, 46, 55},
    {47, 56, 57, 48},
    {58, 49, 48, 57},
    {59, 50, 49, 58},
    {60, 51, 50, 59},
    {61, 52, 51, 60},
    {62, 53, 52, 61},
    {63, 54, 53, 62},
    {63, 64, 0, 54}
};
static GLubyte hexaIndices[2][6] =
{
    {0, 18, 20, 22, 23, 26},
    {9, 25, 24, 21, 19, 17}
};
static GLubyte hexa2Indices[2][10] =
{
    {0, 46, 47, 48, 49, 50, 51, 52, 53, 54},
    {64, 55, 56, 57, 58, 59, 60, 61, 62, 63}
};
static GLfloat colors[18][3] =
{
    {0.0, 0.0, 1.0},
    {0.5, 0.0, 1.0},
    {0.0, 1.0, 0.0},
    {0.0, 1.0, 1.0},
    {0.8, 0.0, 0.0},
    {0.0, 0.0, 1.0},
    {0.5, 1.0, 1.0},
    {0.0, 1.0, 0.0},
    {0.0, 1.0, 1.0},
    {0.8, 0.0, 0.0},
    {1.0, 0.3, 0.2},
    {0.0, 0.3, 0.2},
    {0.2, 1.0, 0.2},
    {0.4, 0.4, 1.0},
    {0.8, 0.8, 1.0},
    {0.8, 0.4, 0.2},
    {0.6, 0.6, 0.2},
    {0.2, 0.4, 0.2}
};

void cubes(float r , float g, float b, int a,float p)
{
    if(a==1){
    glBegin(GL_QUADS);
    for (GLint i = 0; i <7; i++)
    {
            GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
           GLfloat mat_ambient[] = { r*0.6, g*0.6,b*0.6, 1.0 };
           GLfloat mat_diffuse[] = {r, g, b, 1.0 };
           GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
           GLfloat mat_shininess[] = { 30 };

           glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
           glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
           glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
           glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
        /*glVertex3fv(&v_pyramid[quadIndices[i][0]][0]);glTexCoord2f(p,0);
        glVertex3fv(&v_pyramid[quadIndices[i][1]][0]);glTexCoord2f(p,p);
        glVertex3fv(&v_pyramid[quadIndices[i][2]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v_pyramid[quadIndices[i][3]][0]);glTexCoord2f(p,0);*/

        glVertex3fv(&v_pyramid[quadIndices[i][0]][0]);glTexCoord2f(p,p);
        glVertex3fv(&v_pyramid[quadIndices[i][1]][0]);glTexCoord2f(0,p);
        glVertex3fv(&v_pyramid[quadIndices[i][2]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v_pyramid[quadIndices[i][3]][0]);glTexCoord2f(p,0);
        /*glVertex3fv(&v_box[quadIndices[i][0]][0]);glTexCoord2f(1,1);
        glVertex3fv(&v_box[quadIndices[i][1]][0]);glTexCoord2f(1,0);
        glVertex3fv(&v_box[quadIndices[i][2]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v_box[quadIndices[i][3]][0]);glTexCoord2f(0,1);*/
    }
    glEnd();
    }
    else{

    glBegin(GL_QUADS);
    for (GLint i = 0; i <7; i++)
    {
            GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
           GLfloat mat_ambient[] = { colors[a+i][0]*0.5, colors[a+i][1]*0.5,colors[a+i][2]*0.5, 1.0 };
           GLfloat mat_diffuse[] = { colors[a+i][0],colors[a+i][1],colors[a+i][2], 1.0 };
           GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
           GLfloat mat_shininess[] = { 30 };

           glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
           glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
           glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
           glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

        glVertex3fv(&v_pyramid[quadIndices[i][0]][0]);glTexCoord2f(1,1);
        glVertex3fv(&v_pyramid[quadIndices[i][1]][0]);glTexCoord2f(1,0);
        glVertex3fv(&v_pyramid[quadIndices[i][2]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v_pyramid[quadIndices[i][3]][0]);glTexCoord2f(0,1);
        /*glVertex3fv(&v_box[quadIndices[i][0]][0]);glTexCoord2f(1,1);
        glVertex3fv(&v_box[quadIndices[i][1]][0]);glTexCoord2f(1,0);
        glVertex3fv(&v_box[quadIndices[i][2]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v_box[quadIndices[i][3]][0]);glTexCoord2f(0,1);*/
    }
    glEnd();
    }


}
void chimni(float r, float g,float b)
{

    glBegin(GL_QUADS);
    for (GLint i = 21; i <26; i++)
    {
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r*0.2, g*0.2, b*0.3, 1.0 };
    GLfloat mat_diffuse[] = { colors[i-6][0],colors[i-6][1],colors[i-6][2],1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 60 };

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
        glVertex3fv(&v_pyramid[quadIndices[i][0]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][1]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][2]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][3]][0]);
    }
    glEnd();


}
void Hexa(float r, float g, float b, float r2, float g2, float b2)
{
    glBegin(GL_QUADS);
    for (GLint i = 15; i <21; i++)
    {
        //glColor3f(colors[a+i][0],colors[a+i][1],colors[a+i][2]);

            GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
           GLfloat mat_ambient[] = { r*0.3, g*0.3, b*0.3, 1.0 };
           GLfloat mat_diffuse[] = { r , g ,  b , 1.0 }; //0.1 ,  0,,, 0,,,  1 1 1
           GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
           GLfloat mat_shininess[] = { 60 };

           glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
           glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
           glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
           glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

        glVertex3fv(&v_pyramid[quadIndices[i][0]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][1]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][2]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][3]][0]);
    }
    glEnd();
    glBegin(GL_POLYGON);
    for (GLint i = 0; i <2; i++)
    {
        //glColor3f(colors[i][0],colors[i][1],colors[i][2]);

            GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
           GLfloat mat_ambient[] = { r2*0.3, g2*0.3,b2*0.3, 1.0 };
           GLfloat mat_diffuse[] = { r2 , g2 ,b2 ,1.0 };
           GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
           GLfloat mat_shininess[] = { 60 };

           glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
           glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
           glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
           glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

        glVertex3fv(&v_pyramid[hexaIndices[i][0]][0]);
        glVertex3fv(&v_pyramid[hexaIndices[i][1]][0]);
        glVertex3fv(&v_pyramid[hexaIndices[i][2]][0]);
        glVertex3fv(&v_pyramid[hexaIndices[i][3]][0]);
        glVertex3fv(&v_pyramid[hexaIndices[i][4]][0]);
        glVertex3fv(&v_pyramid[hexaIndices[i][5]][0]);
    }
    glEnd();


}
void leaf( float r, float g, float b, float r2, float g2, float b2)
{
    glBegin(GL_POLYGON);
    for (GLint i = 0; i <1; i++)
    {
        //glColor3f(colors[i][0],colors[i][1],colors[i][2]);

            GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
           GLfloat mat_ambient[] = { r2*0.3, g2*0.3,b2*0.3, 1.0 };
           GLfloat mat_diffuse[] = { r2 , g2 ,b2 ,1.0 };
           GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
           GLfloat mat_shininess[] = { 60 };

           glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
           glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
           glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
           glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

        glVertex3fv(&v_pyramid[hexa2Indices[i][0]][0]);glTexCoord2f(0.5,1);
        glVertex3fv(&v_pyramid[hexa2Indices[i][1]][0]);glTexCoord2f(0,0.625);
        glVertex3fv(&v_pyramid[hexa2Indices[i][2]][0]);glTexCoord2f(0.2,0.7);
        glVertex3fv(&v_pyramid[hexa2Indices[i][3]][0]);glTexCoord2f(0.1,0.3);
        glVertex3fv(&v_pyramid[hexa2Indices[i][4]][0]);glTexCoord2f(0.25,0.4);
        glVertex3fv(&v_pyramid[hexa2Indices[i][5]][0]);glTexCoord2f(0.5,0);
        glVertex3fv(&v_pyramid[hexa2Indices[i][6]][0]);glTexCoord2f(0.75,0.3);
        glVertex3fv(&v_pyramid[hexa2Indices[i][7]][0]);glTexCoord2f(0.9,0.3);
        glVertex3fv(&v_pyramid[hexa2Indices[i][8]][0]);glTexCoord2f(0.7,0.6);
        glVertex3fv(&v_pyramid[hexa2Indices[i][9]][0]);glTexCoord2f(1,0.625);;
    }
    glEnd();
    glBegin(GL_QUADS);
    for (GLint i = 0; i <10; i++)
    {
        //glColor3f(colors[a+i][0],colors[a+i][1],colors[a+i][2]);

            GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
           GLfloat mat_ambient[] = { r*0.3, g*0.3, b*0.3, 1.0 };
           GLfloat mat_diffuse[] = { r , g ,  b , 1.0 }; //0.1 ,  0,,, 0,,,  1 1 1
           GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
           GLfloat mat_shininess[] = { 60 };

           glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
           glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
           glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
           glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

        glVertex3fv(&v_pyramid[leafqIndices[i][0]][0]);
        glVertex3fv(&v_pyramid[leafqIndices[i][1]][0]);
        glVertex3fv(&v_pyramid[leafqIndices[i][2]][0]);
        glVertex3fv(&v_pyramid[leafqIndices[i][3]][0]);
    }
    glEnd();


}
void Basket(float r , float g, float b, float p)
{
    glBegin(GL_QUADS);
    for (GLint i = 8; i <15; i++)
    {
            GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
            GLfloat mat_ambient[] = { r*0.5, g*0.5,b*0.5, 1.0 };
            GLfloat mat_diffuse[] = {r, g, b, 1.0 };
            GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
            GLfloat mat_shininess[] = { 60 };

           glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
           glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
           glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
           glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
        /*glVertex3fv(&v_pyramid[quadIndices[i][0]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][1]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][2]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][3]][0]);*/
        glVertex3fv(&v_pyramid[quadIndices[i][0]][0]);glTexCoord2f(p,p);
        glVertex3fv(&v_pyramid[quadIndices[i][1]][0]);glTexCoord2f(0,p);
        glVertex3fv(&v_pyramid[quadIndices[i][2]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v_pyramid[quadIndices[i][3]][0]);glTexCoord2f(p,0);
    }
    glEnd();


}

void floorr(int r, int g, int b)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r*0.2, g*0.2, b*0.3, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 60 };

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glBegin(GL_QUADS);
    for (GLint i = 0; i <1; i++)
    {
        glVertex3fv(&v_pyramid[quadIndices[i][0]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][1]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][2]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][3]][0]);
    }
    glEnd();


}
void floorr2(int r, int g, int b)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r*0.2, g*0.2, b*0.3, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 60 };

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glBegin(GL_QUADS);
    for (GLint i = 0; i <1; i++)
    {
        //glColor3f(colors[5][0],colors[5][1],colors[5][2]);
        glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
        glVertex3fv(&v_pyramid[quadIndices[i][0]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][1]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][2]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][3]][0]);
    }
    glEnd();


}
void sphere(float r, float g, float b)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r*0.2, g*0.2, b*0.3, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 60 };

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
        glutSolidSphere(1,50,50);
}
void wirsphere(int a)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.2, 0.2, 0.3, 1.0 };
    GLfloat mat_diffuse[] = { 1.0, 0.1, 0.1, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 60 };

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glutWireSphere(a,slices,stacks);
}
void init() // only call once on startup
{
  qobj = gluNewQuadric();
  gluQuadricNormals(qobj, GLU_SMOOTH);
}
void cylinder(float r, float g, float b)
{
        GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.2*r, 0.2*g, 0.3*b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 0.7 ,0.7, 0.7, 1.0 };
    GLfloat mat_shininess[] = { 60 };

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    const double PI = 3.14159;

    /* top triangle */
    double i, resolution  = 0.1;
    double height = 1;
    double radius = 0.5;

    glPushMatrix();
    glTranslatef(0, -0.5, 0);

    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f( 0.5, 0.5 );
        glVertex3f(0, height, 0);  /* center */
        for (i = 2 * PI; i >= 0; i -= resolution)

        {
                GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
                GLfloat mat_ambient[] = { 0.2*r, 0.2*g, 0.3*b, 1.0 };
                GLfloat mat_diffuse[] = { r, g, b, 1.0 };
                GLfloat mat_specular[] = { 0.7 ,0.7, 0.7, 1.0 };
                GLfloat mat_shininess[] = { 60 };

                glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
                glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
                glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
                glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
            glTexCoord2f( 0.5f * cos(i) + 0.5f, 0.5f * sin(i) + 0.5f );
            glVertex3f(radius * cos(i), height, radius * sin(i));
        }
        /* close the loop back to 0 degrees */
        glTexCoord2f( 0.5, 0.5 );
        glVertex3f(radius, height, 0);
    glEnd();

    /* bottom triangle: note: for is in reverse order */
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f( 0.5, 0.5 );
        glVertex3f(0, 0, 0);  /* center */
        for (i = 0; i <= 2 * PI; i += resolution)
        {
                GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
                GLfloat mat_ambient[] = { 0.2*r, 0.2*g, 0.3*b, 1.0 };
                GLfloat mat_diffuse[] = { r, g, b, 1.0 };
                GLfloat mat_specular[] = { 0.7 ,0.7, 0.7, 1.0 };
                GLfloat mat_shininess[] = { 60 };

                glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
                glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
                glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
                glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
            glTexCoord2f( 0.5f * cos(i) + 0.5f, 0.5f * sin(i) + 0.5f );
            glVertex3f(radius * cos(i), 0, radius * sin(i));
        }
    glEnd();

    /* middle tube */
    glBegin(GL_QUAD_STRIP);

        for (i = 0; i <= 2 * PI; i += resolution)
        {
                GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
                GLfloat mat_ambient[] = { 0.2*r, 0.2*g, 0.3*b, 1.0 };
                GLfloat mat_diffuse[] = { r, g, b, 1.0 };
                GLfloat mat_specular[] = { 0.7 ,0.7, 0.7, 1.0 };
                GLfloat mat_shininess[] = { 60 };

                glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
                glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
                glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
                glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
            const float tc = ( i / (float)( 2 * PI ) );
            glTexCoord2f( tc, 0.0 );
            glVertex3f(radius * cos(i), 0, radius * sin(i));
            glTexCoord2f( tc, 1.0 );
            glVertex3f(radius * cos(i), height, radius * sin(i));
        }
        /* close the loop back to zero degrees */
        glTexCoord2f( 0.0, 0.0 );
        glVertex3f(radius, 0, 0);
        glTexCoord2f( 0.0, 10.0 );
        glVertex3f(radius, height, 0);
    glEnd();

    glPopMatrix();
}

/*GLuint tex;
void init()
{
    unsigned char data[] =
    {
        128, 128, 128, 255,
        255, 0, 0, 255,
        0, 255, 0, 255,
        0, 0, 255, 255,
    };

    glGenTextures( 1, &tex );
    glBindTexture( GL_TEXTURE_2D, tex );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexImage2D( GL_TEXTURE_2D, 0,GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );
}

float angle = 0;
void timer( int value )
{
    angle += 6;
    glutPostRedisplay();
    glutTimerFunc( 16, timer, 0 );
}
*/
void cyclider(float r, float g, float b)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.2*r, 0.2*g, 0.3*b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 0.7 ,0.7, 0.7, 1.0 };
    GLfloat mat_shininess[] = { 60 };

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

  GLUquadricObj *quadratic;
  quadratic = gluNewQuadric();
      glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,2);
  gluCylinder(quadratic,0.01f,0.01f,0.3f,32,32);
  glDisable(GL_TEXTURE_2D);
}
void dhal(float r, float g, float b)
{
    glBegin(GL_QUADS);
    for (GLint i = 26; i <32; i++)
    {
            GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
           GLfloat mat_ambient[] = { r*0.5, g*0.5, b*0.5, 1.0 };
           GLfloat mat_diffuse[] = { r, g, b, 1.0 };
           GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
           GLfloat mat_shininess[] = { 30 };

           glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
           glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
           glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
           glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

        glVertex3fv(&v_pyramid[quadIndices[i][0]][0]);glTexCoord2f(1,1);
        glVertex3fv(&v_pyramid[quadIndices[i][1]][0]);glTexCoord2f(1,0);
        glVertex3fv(&v_pyramid[quadIndices[i][2]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v_pyramid[quadIndices[i][3]][0]);glTexCoord2f(0,1);
    }
    glEnd();

}

void pillar(float r, float g ,float b, int a,int p,int h)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,1);
    //LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\brick.bmp");
    glPushMatrix();
    glScalef(1,h,1);
    cubes(r,g,b,a,p);
    glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}
void bhavan_vumi()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,2);
    //LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\design_tiles_2.bmp");
    glPushMatrix();
    glTranslatef(10,0,0);
    glScalef(20,3,20);//z-10
    cubes(3,4,2,1,5);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void ticket(){


    glPushMatrix(); //ticket ghor back wall
    glTranslatef(14.5,0,-2);
    glScalef(4,10,0.1);
    cubes(1,1,1,1,1);
    glPopMatrix();

    glPushMatrix(); //ticket ghor left wall
    glTranslatef(14.4,0,-2);
    glScalef(0.1,10,2.5);
    cubes(1,1,1,1,1);
    glPopMatrix();

    glPushMatrix(); //ticket ghor right wall
    glTranslatef(14.9,0,-2);
    glScalef(0.1,10,2.5);
    cubes(1,1,1,1,1);
    glPopMatrix();

    glPushMatrix(); //chad
    glTranslatef(14.5,10,-2);
    glScalef(4,0.1,2.5);
    cubes(1,1,1,1,1);
    glPopMatrix();




    glEnable(GL_TEXTURE_2D); //left
    glBindTexture(GL_TEXTURE_2D,41);
   glPushMatrix(); // ticket
    glTranslatef(14.5,9,0.5);
    glScalef(2,1.5,0.1);
    cubes(1,1,1,1,1);
   glPopMatrix();
    glDisable(GL_TEXTURE_2D); //left one


   glPushMatrix(); // left ticket left line railig
    glTranslatef(14.5,5.5,0.5);
    glScalef(0.1,0.1,6);
    cubes(0,0,0,1,1);
   glPopMatrix();

   glPushMatrix(); // left ticket left lomba
    glTranslatef(14.5,2.1,0.5);
    glScalef(0.1,3.4,0.1);
    cubes(0,0,0,1,1);
for(int i=0;i<8;i++){
    glTranslatef(0,0,7);
    cubes(0,0,0,1,1);
}
   glPopMatrix();

   glPushMatrix(); // left ticket right line raling
    glTranslatef(16.5,5.5,2);
    glScalef(0.1,0.1,4.5);
    cubes(0,0,0,1,1);
   glPopMatrix();

   glPushMatrix(); // left ticket right lomba
    glTranslatef(16.5,2.1,2);
    glScalef(0.1,3.4,0.1);
    cubes(0,0,0,1,1);
for(int i=0;i<6;i++){
    glTranslatef(0,0,7);
    cubes(0,0,0,1,1);
}
   glPopMatrix();



    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,42);
   glPushMatrix(); // ticket
    glTranslatef(14.7,11.5,0.5);
    glScalef(1.5,1.5,0.1);
    cubes(1,1,1,1,1);
   glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    glEnable(GL_TEXTURE_2D); //left
    glBindTexture(GL_TEXTURE_2D,41);
   glPushMatrix(); // ticket
    glTranslatef(24.5,9,0.5);
    glScalef(2,1.5,0.1);
    cubes(1,1,1,1,1);
   glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D); //left two
    glBindTexture(GL_TEXTURE_2D,43);
   glPushMatrix(); // ticket
    glTranslatef(24.7,11.5,0.5);
    glScalef(1.5,1.5,0.1);
    cubes(1,1,1,1,1);
   glPopMatrix();
    glDisable(GL_TEXTURE_2D);



   glPushMatrix(); // right ticket left line railig
    glTranslatef(24.5,5.5,0.5);
    glScalef(0.1,0.1,6);
    cubes(0,0,0,1,1);
   glPopMatrix();

   glPushMatrix(); // right ticket left lomba
    glTranslatef(24.5,2.1,0.5);
    glScalef(0.1,3.4,0.1);
    cubes(0,0,0,1,1);
for(int i=0;i<8;i++){
    glTranslatef(0,0,7);
    cubes(0,0,0,1,1);
}
   glPopMatrix();

   glPushMatrix(); // right ticket right line raling
    glTranslatef(26.5,5.5,2);
    glScalef(0.1,0.1,4.5);
    cubes(0,0,0,1,1);
   glPopMatrix();

   glPushMatrix(); // right ticket right lomba
    glTranslatef(26.5,2.1,2);
    glScalef(0.1,3.4,0.1);
    cubes(0,0,0,1,1);
for(int i=0;i<6;i++){
    glTranslatef(0,0,7);
    cubes(0,0,0,1,1);
}
   glPopMatrix();




}
void bhavan(float r, float g, float b)
{
    /*glEnable(GL_TEXTURE_2D);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\design_tiles_2.bmp");
    glPushMatrix();
    glTranslatef(10,0,0);
    glScalef(20,3,10);
    cubes(3,4,2,1,5);
    glPopMatrix();*/
  // glDisable(GL_TEXTURE_2D);
   glPushMatrix(); // Back piller
    glTranslatef(10,3,0);
    pillar(1,1,1,1,1,10);
   glPopMatrix();
   glPushMatrix();
     glTranslatef(20,3,0);
     pillar(1,1,1,1,1,10);
    glPopMatrix();
    glPushMatrix();
     glTranslatef(29,3,0);
     pillar(1,1,1,1,1,10);
    glPopMatrix();

    glPushMatrix();  //Back wall
     glTranslatef(11,3,0);
     glScalef(4,10,0.4);
    cubes(r,g,b,1,1);
    glPopMatrix();
    glPushMatrix();
     glTranslatef(16,3,0);
     glScalef(4,10,0.4);
    cubes(r,g,b,1,1);
    glPopMatrix();
    glPushMatrix();
     glTranslatef(15,9,0);
     glScalef(1,4,0.4);
    cubes(r,g,b,1,1);
    glPopMatrix();
     glPushMatrix();
     glTranslatef(15,3,0);
     glScalef(1,2.5,0.4);
    cubes(r,g,b,1,1);
    glPopMatrix();
    glPushMatrix();  //Back wall
     glTranslatef(21,3,0);
     glScalef(4,10,0.4);
    cubes(r,g,b,1,1);
    glPopMatrix();
    glPushMatrix();
     glTranslatef(26,3,0);
     glScalef(3,10,0.4);
    cubes(r,g,b,1,1);
    glPopMatrix();
    glPushMatrix();
     glTranslatef(25,9,0);
     glScalef(1,4,0.4);
    cubes(1,1,1,1,1);
    glPopMatrix();
     glPushMatrix();
     glTranslatef(25,3,0);
     glScalef(1,2.5,0.4);
    cubes(r,g,b,1,1);
    glPopMatrix();
   glPushMatrix();// front piller
    glTranslatef(10,3,16); //z-6
    pillar(1,1,1,1,1,10);
    glTranslatef(7,0,0);
    pillar(1,1,1,1,1,10);
   glTranslatef(4,0,0);
    pillar(1,1,1,1,1,10);
   glTranslatef(8,0,0);
    pillar(1,1,1,1,1,10);
   glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
   glPushMatrix(); //front_left_door
     glTranslatef(18,3,16); //z-6
    // glScalef(1,3,0.02);
    glRotatef(-fTheta, 0,1,0);
    glScalef(1.5,10,0.08);
    ///cubes(0.7,0.1,0.8,19,1);
    cubes(1,1,1,1,1);
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,9);
   glPushMatrix(); //front_right_door
     glTranslatef(19.5,3,16); //z-6
    // glScalef(1,3,0.02);
    glTranslatef(1.5,1.5,0);
    glRotatef(fTheta, 0,1,0);
    glTranslatef(-1.5,-1.5,0);
    glScalef(1.5,10,0.08);
     cubes(1,1,1,1,1);
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
   glPushMatrix();  //front wall
     glTranslatef(11,3,16);//z-6
     glScalef(2,10,0.3);
    cubes(r,g,b,1,1);
     glTranslatef(2,0,0);
    cubes(r,g,b,1,1);
    glPopMatrix();
   glPushMatrix();
     glTranslatef(13,3,16); // janalar wall z-6
     glScalef(2,3,0.3);
    cubes(0.7,0,0,1,1);
    glTranslatef(0,2,0);
    cubes(0.7,0,0,1,1);
    glPopMatrix();
    glPushMatrix(); //front_left_janala border
     glTranslatef(13,6,16); //z-6
     glScalef(2,0.3,0.4);
    cubes(0,0,0,1,1);
    glTranslatef(0,10,0);
    cubes(0,0,0,1,1);
   glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,10);
   glPushMatrix(); //left janala
     glTranslatef(13,6.3,16.2); //z-6
    // glScalef(1,3,0.02);
    glRotatef(fTheta, 0,1,0);
    glScalef(1,2.6,0.08);
    cubes(0,0.1,0.8,10,1);
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,10);
   glPushMatrix(); //right janala
     glTranslatef(14,6.3,16.2);//z
    // glScalef(1,3,0.02);
    glTranslatef(1,1.5,0);
    glRotatef(-fTheta, 0,1,0);
    glTranslatef(-1,-1.5,0);
    glScalef(1,2.6,0.08);
    cubes(0,0.1,0.8,10,1);
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
   glPushMatrix();  //front wall
     glTranslatef(22,3,16); //z-6
     glScalef(2.5,10,0.3);
    cubes(r,g,b,1,1);
     glTranslatef(2,0,0);
    cubes(r,g,b,1,1);
    glPopMatrix();
    glPushMatrix();
     glTranslatef(24.5,3,16);//z-6
     glScalef(2.5,3,0.3);
    cubes(0.7,0,0,1,1);
    glTranslatef(0,2,0);
     cubes(0.7,0,0,1,1);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,10);
    glPushMatrix(); //front_right_left janala
     glTranslatef(24.5,6.3,16.2); //z-6
    // glScalef(1,3,0.02);
    glRotatef(fTheta, 0,1,0);
    glScalef(1.25,2.6,0.08);
    cubes(0,0.1,0.8,10,1);
   glPopMatrix();
   glPushMatrix(); //front_right_right janala
     glTranslatef(25.75,6.3,16.2);  //z-6
    // glScalef(1,3,0.02);
    glTranslatef(1.25,1.5,0);
    glRotatef(-fTheta, 0,1,0);
    glTranslatef(-1.25,-1.5,0);
    glScalef(1.25,2.6,0.08);
    cubes(0,0.1,0.8,10,1);
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
     glPushMatrix(); //front_right_janala border
     glTranslatef(24.5,6,16); //z-6
     glScalef(2.5,0.3,0.4);
    cubes(0,0,0,1,1);
    glTranslatef(0,10,0);
    cubes(0,0,0,1,1);
   glPopMatrix();

    glPushMatrix();  //left wall
     glTranslatef(10,3,1);
     glScalef(0.3,10,15);//z-5
    cubes(r,g,b,1,1);
    glPopMatrix();
    glPushMatrix();  //right wall
     glTranslatef(29.6,3,1);
     glScalef(0.3,10,15);  //z-5
    cubes(r,g,b,1,1);
    glPopMatrix();
    glPushMatrix();  //chad
     glTranslatef(9,13,0);
     glScalef(22,1,20); //z-10
     cubes(0.8,1,1,1,1);
    glPopMatrix();



};
void banner()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,3);
    glPushMatrix();
    glTranslatef(17,13.5,21);
    glScalef(5,4,0.02);
    //LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\khulna_station_b.bmp");
    cubes(1,1,1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void time_table()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,16);
    glPushMatrix();
    glTranslatef(22.2,6,16.25);
    glScalef(1.8,4.5,0.1);
    //LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\khulna_station_b.bmp");
    cubes(1,1,1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,17);
    glPushMatrix();
    glTranslatef(15.1,6,16.25);
    glScalef(1.8,2.5,0.1);
    //LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\khulna_station_b.bmp");
    cubes(1,1,1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}



void half_engine(){
     glPushMatrix(); //nicher nil
      glTranslatef(15.2,3.5,28);
      glScalef(6,2,3);
      cubes(0.2,0.2,1,1,1);
      glPopMatrix();

      glPushMatrix();// majher holud
      glTranslatef(15.2,5.5,28);
      glScalef(6,1.5,3);
      cubes(1,1,0.2,1,1);
      glPopMatrix();

      glPushMatrix(); //oporer nil
      glTranslatef(15.2,7,28);
      glScalef(6,2,3);
      cubes(0.2,0.2,1,1,1);
      glPopMatrix();

      glPushMatrix(); //holud platform
      glTranslatef(15,3.5,27.5);
      glScalef(10,0.2,4);
      cubes(1,1,0,1,1);
      glPopMatrix();

     glPushMatrix(); // front nicher porer nil
      glTranslatef(21.2,3.5,31);
      glScalef(3,2,0.05);
      cubes(0.2,0.2,1,1,1);
      glPopMatrix();

     glPushMatrix(); //back nicher porer nil
      glTranslatef(21.2,3.5,28);
      glScalef(3,2,0.05);
      cubes(0.2,0.2,1,1,1);
      glPopMatrix();

     glPushMatrix(); //front majher porer holud
      glTranslatef(21.2,5.5,31);
      glScalef(1.5,2.2,0.05);
      cubes(1,1,0.2,1,1);
      glPopMatrix();

     glPushMatrix(); //back majher porer holud
      glTranslatef(21.2,5.5,28);
      glScalef(1.5,2.2,0.05);
      cubes(1,1,0.2,1,1);
      glPopMatrix();


     glPushMatrix(); //front janala border
      glTranslatef(21.2,7.7,31);
      glScalef(1.5,0.2,0.05);
      cubes(1,1,1,1,1);
      glPopMatrix();

     glPushMatrix(); //back janala border
      glTranslatef(21.2,7.7,28);
      glScalef(1.5,0.2,0.05);
      cubes(1,1,1,1,1);
      glPopMatrix();


     glPushMatrix(); //fornt janala border opor
      glTranslatef(21.2,8.8,31);
      glScalef(1.5,0.2,0.05);
      cubes(1,1,1,1,1);
      glPopMatrix();

     glPushMatrix(); //back janala border opor
      glTranslatef(21.2,8.8,28);
      glScalef(1.5,0.2,0.05);
      cubes(1,1,1,1,1);
      glPopMatrix();

   glPushMatrix(); //front janala border left
      glTranslatef(21.2,7.7,31);
      glScalef(0.2,1.4,0.05);
      cubes(1,1,1,1,1);
      glPopMatrix();

   glPushMatrix(); //back janala border left
      glTranslatef(21.2,7.7,28);
      glScalef(0.2,1.4,0.05);
      cubes(1,1,1,1,1);
      glPopMatrix();


   glPushMatrix(); //front janala border right
      glTranslatef(22.5,7.7,31);
      glScalef(0.2,1.4,0.05);
      cubes(1,1,1,1,1);
      glPopMatrix();

   glPushMatrix(); //back janala border right
      glTranslatef(22.5,7.7,28);
      glScalef(0.2,1.4,0.05);
      cubes(1,1,1,1,1);
      glPopMatrix();

   glPushMatrix(); //front ekdom samner nil
      glTranslatef(22.7,3.5,31);
      glScalef(1,5.5,0.05);
      cubes(0.2,0.2,1,1,1);
      glPopMatrix();

   glPushMatrix(); //back ekdom samner nil
      glTranslatef(22.7,3.5,28);
      glScalef(1,5.5,0.05);
      cubes(0.2,0.2,1,1,1);
      glPopMatrix();
 glEnable(GL_TEXTURE_2D);
 glBindTexture(GL_TEXTURE_2D,40);
   glPushMatrix(); //samner dhakna
      glTranslatef(24,3.5,28);
      glScalef(1,4,3);
      cubes(0.2,0.2,1,1,1);
      glPopMatrix();
 glDisable(GL_TEXTURE_2D);

   glPushMatrix(); //samner dhakna nicher
      glTranslatef(24,8.5,28);
      glScalef(1,0.5,3);
      cubes(1,0.1,0.1,1,1);
      glPopMatrix();

   glPushMatrix(); //chad
      glTranslatef(15,9,28);
      glScalef(9,0.2,3);
      cubes(1,1,1,1,1);
      glPopMatrix();


      glPushMatrix(); //CYLINDRE CAKA
      glTranslatef(1,32.5,28);
      glTranslatef(0,0,-0.5);
      glRotatef(90,1,0,0);
      glTranslatef(0,0,0.5);
      glTranslatef(15.2,2,29.5);
      glScalef(2,3.5,2);
      cylinder(0,0,0);
      glTranslatef(2,0,0);
      cylinder(0,0,0);
      glPopMatrix();

      glPushMatrix(); //chaka_machine
      glTranslatef(17.5,2,30.5);
      glRotatef(90,0,1,0);
          glScalef(35,45,5);
       cyclider(0.99,0.99,0.99);
      glPopMatrix();
      glPushMatrix(); //chaka_machine 2
      glTranslatef(17.5,2.7,30.5);
      glRotatef(90,0,1,0);
          glScalef(30,40,3);
       cyclider(0.99,0.99,0.99);
      glPopMatrix();



      glPushMatrix(); // front side railing
      glTranslatef(15,5.5,31.4);
      glScalef(5,0.1,0.1);
      cubes(1,1,1,1,1);
      glPopMatrix();

      glPushMatrix(); // back side railing
      glTranslatef(15,5.5,27.5);
      glScalef(5,0.1,0.1);
      cubes(1,1,1,1,1);
      glPopMatrix();

      glPushMatrix(); //front lomba
      glTranslatef(15,3.7,31.4);
      glScalef(0.07,1.8,0.1);
      cubes(1,1,1,1,1);
for(int i=0;i<20;i++){
      glTranslatef(3.5,0,0);
      cubes(1,1,1,1,1);
}
      glPopMatrix();

      glPushMatrix(); //back lomba
      glTranslatef(15,3.7,27.5);
      glScalef(0.07,1.8,0.1);
      cubes(1,1,1,1,1);
for(int i=0;i<20;i++){
      glTranslatef(3.5,0,0);
      cubes(1,1,1,1,1);
}
      glPopMatrix();





}
void engine()
{
    glTranslatef(32,0,0);
    half_engine();
}






void pond()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,4);
    glPushMatrix();
    glTranslatef(-30,0,-24);
    glScalef(150,0.3,20);
    //LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\ocean_blue_4.bmp");
    cubes(1,1,1,1,15);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void train_seat()
{
    glPushMatrix();  //back row
    glTranslatef(16,5,17.1); //17.1
    glScalef(1,0.2,1);
    cubes(1,0,0,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15.8,5,17.1);
    glScalef(0.2,2,1);
    cubes(0.1,0.1,1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15.8,5.3,17.1);
    glScalef(1,0.1,0.1);
    cubes(0,0,0,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15.8,5.3,18);
    glScalef(1,0.1,0.1);
    cubes(0,0,0,1,1);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(15.8,3.28,17.5); //seat_paya
    glScalef(0.2,1.7,0.2);
    cubes(0,0,0,1,1);
    glPopMatrix();



    glPushMatrix(); //front row
    glTranslatef(16,5,19); //17.1
    glScalef(1,0.2,1);
    cubes(1,0,0,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15.8,5,19);
    glScalef(0.2,2,1);
    cubes(0.1,0.1,1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15.8,5.3,19);
    glScalef(1,0.1,0.1);
    cubes(0,0,0,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15.8,5.3,19.9);
    glScalef(1,0.1,0.1);
    cubes(0,0,0,1,1);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(15.8,3.28,19.4); //seat_paya
    glScalef(0.2,1.7,0.2);
    cubes(0,0,0,1,1);
    glPopMatrix();

}
void rail_line()
{
   // glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-20,0,28); //Z-17
    glScalef(150,1,3);
     //dhal(1,1,1);
     cubes(1,1,1,1,1);
   // LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\brick.bmp");
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-20,1,28.5); //Z-17
    glScalef(150,0.2,0.2);
    cubes(0,0,0,1,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-20,1,30.5); //Z-19
    glScalef(150,0.2,0.2);
    cubes(0,0,0,1,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-20,1,28); //Z-17
    glScalef(0.2,0.2,3);
    cubes(0,0,0,1,1);
    for(int j=0;j<400;j++)
    {
       glTranslatef(3,0,0);
       cubes(0,0,0,1,1);
    }
    glPopMatrix();


}
void bogi_one_side()
{

    glPushMatrix(); //left dorja start
    glTranslatef(12.5,3,20);
    glScalef(0.5,8,0.1);
    cubes(0.8,0.8,0.1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(13,3,20);
    glScalef(2,0.3,0.1);
    cubes(0.8,0.8,0.1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(13,10.7,20);
    glScalef(2,0.3,0.1);
    cubes(0.8,0.8,0.1,1,1);
    glPopMatrix();  //left dorja finish


    glPushMatrix(); //right dorja start
    glTranslatef(35,3,20);
    glScalef(0.5,8,0.1);
    cubes(0.8,0.8,0.1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(33,3,20);
    glScalef(2,0.3,0.1);
    cubes(0.8,0.8,0.1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(33,10.7,20);
    glScalef(2,0.3,0.1);
    cubes(0.8,0.8,0.1,1,1);
    glPopMatrix();  //right dorja finish


    glPushMatrix();
    glTranslatef(15,3,20);
    glScalef(18,3,0.1);
    //cubes(1,0.8,0.8,1,1);
    cubes(0,0.7,0.9,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15,8,20);
    glScalef(18,3,0.1);
    cubes(0,0.7,0.9,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15,6,20);
    glScalef(2,2,0.1);
    cubes(0.8,0.8,0.1,1,1);
    for(int j=0;j<4;j++)
    {
    glTranslatef(2,0,0);
    cubes(0.8,0.8,0.1,1,1);
    }
    glPopMatrix();


}
void bogi()
{
    glPushMatrix();
    bogi_one_side();
   glTranslatef(0,0,-3);
    bogi_one_side();
    glPopMatrix();

    glPushMatrix(); //left wheel
    glTranslatef(15,2,17);
    glScalef(1,1.2,3);
    cubes(0,0,0,1,1);
    glTranslatef(1.5,0,0);
    cubes(0,0,0,1,1);
    glPopMatrix();
    glPushMatrix(); //right wheel
    glTranslatef(31,2,17);
    glScalef(1,1.2,3);
    cubes(0,0,0,1,1);
    glTranslatef(1.5,0,0);
    cubes(0,0,0,1,1);
    glPopMatrix();

    glPushMatrix(); //floor
     glTranslatef(12.5,3,17);
     glScalef(23,0.3,3);
    cubes(1,1,1,1,1);
    glPopMatrix();
   glPushMatrix(); //ceiling
     glTranslatef(12.5,11,17);
     glScalef(23,0.3,3);
    cubes(0,0.7,0.9,1,1);
    glPopMatrix();

    glPushMatrix(); //left wall
     glTranslatef(12.5,3,17);
     glScalef(0.5,8,3);
    cubes(0,0.7,0.9,1,1);
    glPopMatrix();

    glPushMatrix(); //right wall
     glTranslatef(35,3,17);
     glScalef(0.5,8,3);
    cubes(0,0.7,0.9,1,1);
    glPopMatrix();
    glPushMatrix();
     glTranslatef(35.5,4,17.8);
     glScalef(1.5,1,0.4);
    cubes(0,0,0,1,1);
    glPopMatrix();
    glPushMatrix();
    train_seat();
for(int i=0;i<8;i++){
    glTranslatef(2,0,0);
     train_seat();
     }
    glPopMatrix();
}
void train()
{
    glPushMatrix();
    glTranslatef(-10,0,0);
    bogi();
    glTranslatef(24,0,0);
    bogi();
    glTranslatef(-48,0,0);
    bogi();
for(int i=0;i<10;i++){
    glTranslatef(-24,0,0);
    bogi();
}
    glPopMatrix();
}
void fence()
{
    glPushMatrix();
     glTranslatef(-30,0,-3);
   for(int j=0;j<50;j++){
     pillar(1,1,1,1,1,5);
     glTranslatef(5,0,0);
    }
    glPopMatrix();
    glPushMatrix();
     glTranslatef(-30,4,-2.4);
     glScalef(5,0.5,0.1);
     cubes(1,1,1,1,1);
   for(int j=0;j<48;j++){
     glTranslatef(1,0,0);
     cubes(1,1,1,1,1);
   }
   glPopMatrix();

     glPushMatrix();
     glTranslatef(-30,2.5,-2.4);
     glScalef(5,0.5,0.1);
     cubes(1,1,1,1,1);
   for(int j=0;j<40;j++){
     glTranslatef(1,0,0);
     cubes(1,1,1,1,1);
   }
   glPopMatrix();

     glPushMatrix();
     glTranslatef(-30,1,-2.4);
     glScalef(5,0.5,0.1);
     cubes(1,1,1,1,1);
   for(int j=0;j<40;j++){
     glTranslatef(1,0,0);
     cubes(1,1,1,1,1);
   }
   glPopMatrix();



}
void mati()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,5);
    glPushMatrix();
    glTranslatef(-30,0,-4);
    glScalef(200,0.5,100);
    //LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\grass_texture_03.bmp");
    cubes(1,1,1,1,15);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void platform()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,6);
    //LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\white_tile_1.bmp");
    glPushMatrix();
    glTranslatef(-20,0,20); //z-10
    glScalef(200,2,7);
    cubes(1,1,1,1,20);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    for(int j=0;j<12;j++)
    {
    glPushMatrix();
    glPushMatrix();
    glTranslatef(8,2,22); //z=12
    glScalef(2,1,2);
    cubes(0.5,0.5,1,1,1);
    glPopMatrix();
    glTranslatef(8.5,2,22.5); //Z-12.5
    pillar(1,1,1,1,1,15);
    glPopMatrix();
    glTranslatef(15,0,0);
    }
    glPopMatrix();
    glEnable(GL_TEXTURE_2D); //platform_red_tin
    glBindTexture(GL_TEXTURE_2D,7);
    //LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\red_tin.bmp");
    glPushMatrix();
    glTranslatef(5,17,20);// z-10
    glScalef(200,0.2,6);
    cubes(1,1,1,1,20);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void fan(){
glPushMatrix();   //fan
     glPushMatrix();
     glTranslatef(15,13,23); //pakha-1
     glTranslatef(1.7,0.005,0.2);
     glRotatef(faTheta,0,1,0);
     glTranslatef(-1.7,-0.005,-0.2);
     glScalef(1.5,0.01,0.4);
     cubes(0,0,0,12,1);
     glPopMatrix();
     glPushMatrix();
     glTranslatef(16.9,13,23); //pakha-2
     glTranslatef(-0.2,0.005,0.2);
     glRotatef(faTheta,0,1,0);
     glTranslatef(0.2,-0.005,-0.2);
     glScalef(1.5,0.01,0.4);
     cubes(0,0,0,12,1);
     glPopMatrix();
     glPushMatrix();
     glTranslatef(16.5,13,21.5); //pakha-3
     glTranslatef(0.2,0.005,1.7);
     glRotatef(faTheta,0,1,0);
     glTranslatef(-0.2,-0.005,-1.7);
     glScalef(0.4,0.01,1.5);
     cubes(0,0,0,12,1);
     glPopMatrix();
     glPushMatrix();
     glTranslatef(16.5,13,23.4); //pakha-4
     glTranslatef(0.2,0.005,-0.2);
     glRotatef(faTheta,0,1,0);
     glTranslatef(-0.2,-0.005,0.2);
     glScalef(0.4,0.01,1.5);
     cubes(0,0,0,12,1);
     glPopMatrix();
     glPushMatrix();
     glTranslatef(16.5,13,23); //MIDDLE
     glTranslatef(0.2,0.005,0.2);
     glRotatef(faTheta,0,1,0);
     glTranslatef(-0.2,-0.005,-0.2);
     glScalef(0.4,0.01,0.4);
     cubes(1,1,1,15,1);
     glPopMatrix();
     glPushMatrix();
     glTranslatef(16.7,13,23.2); //fan_stick
     glScalef(0.1,4,0.1);
     cubes(0,0,0,12,1);
     glPopMatrix();
     glPopMatrix();


}
void tower(){
glPushMatrix();
glPushMatrix(); //tower plate
 glTranslatef(60,0,10);
 glScalef(15,5,9);
  cubes(0.6,0.8,1,1,1);
glPopMatrix();
for(int i=0;i<5;i+=2){
glPushMatrix(); //tower nicher back left  white
 glTranslatef(60+(i*10*0.087),4+(10*i),10);
 glTranslatef(0.1,0,0.1);
 glRotatef(-5,0,0,1);
 glTranslatef(-0.1,0,-0.1);
  glScalef(0.2,10,0.2);
  cubes(1,1,1,1,1);
glPopMatrix();
}
for(int i=1;i<6;i+=2){
glPushMatrix(); //tower nicher back left red
 glTranslatef(60+(i*10*0.087),4+(10*i),10);
 glTranslatef(0.1,0,0.1);
 glRotatef(-5,0,0,1);
 glTranslatef(-0.1,0,-0.1);
  glScalef(0.2,10,0.2);
  cubes(1,0.1,0.1,1,1);
glPopMatrix();
}
for(int i=0;i<5;i+=2){
glPushMatrix(); //tower nicher back right white
 glTranslatef(73-(i*10*0.087),4+(10*i),10);
 glTranslatef(0.1,0,0.1);
 glRotatef(5,0,0,1);
 glTranslatef(-0.1,0,-0.1);
  glScalef(0.2,10,0.2);
  cubes(1,1,1,1,1);
glPopMatrix();
}
for(int i=1;i<6;i+=2){
glPushMatrix(); //tower nicher back left red
 glTranslatef(73-(i*10*0.087),4+(10*i),10);
 glTranslatef(0.1,0,0.1);
 glRotatef(5,0,0,1);
 glTranslatef(-0.1,0,-0.1);
  glScalef(0.2,10,0.2);
  cubes(1,0.1,0.1,1,1);
glPopMatrix();
}
for(int i=0;i<5;i+=2){
glPushMatrix(); //tower nicher front left
 glTranslatef(60+(i*10*0.087),4+(10*i),15);
 glTranslatef(0.1,0,0.1);
 glRotatef(-5,0,0,1);
 glTranslatef(-0.1,0,-0.1);
  glScalef(0.2,10,0.2);
  cubes(1,1,1,1,1);

glPopMatrix();
}
for(int i=1;i<6;i+=2){
glPushMatrix(); //tower nicher front left
 glTranslatef(60+(i*10*0.087),4+(10*i),15);
 glTranslatef(0.1,0,0.1);
 glRotatef(-5,0,0,1);
 glTranslatef(-0.1,0,-0.1);
  glScalef(0.2,10,0.2);
  cubes(1,0.1,0.1,1,1);
glPopMatrix();
}
for(int i=0;i<5;i+=2){
glPushMatrix(); //tower nicher front right white
 glTranslatef(73-(i*10*0.087),4+(10*i),15);
 glTranslatef(0.1,0,0.1);
 glRotatef(5,0,0,1);
 glTranslatef(-0.1,0,-0.1);
  glScalef(0.2,10,0.2);
  cubes(1,1,1,1,1);

glPopMatrix();
}
for(int i=1;i<6;i+=2){
glPushMatrix(); //tower nicher front right red
 glTranslatef(73-(i*10*0.087),4+(10*i),15);
 glTranslatef(0.1,0,0.1);
 glRotatef(5,0,0,1);
 glTranslatef(-0.1,0,-0.1);
  glScalef(0.2,10,0.2);
  cubes(1,0.1,0.1,1,1);
glPopMatrix();
}

for(int i=2;i<7;i+=2){
glPushMatrix(); //left stick white
 glTranslatef(60+(i*10*0.087),4+(10*i),10);
  glScalef(0.2,0.2,5);
  cubes(1,1,1,1,1);
glPopMatrix();
}
for(int i=1;i<6;i+=2){
glPushMatrix(); //left stick red
 glTranslatef(60+(i*10*0.087),4+(10*i),10);
  glScalef(0.2,0.2,5);
  cubes(1,.1,.1,1,1);
glPopMatrix();
}
for(int i=2;i<7;i+=2){
glPushMatrix(); //right stick white
 glTranslatef(73-(i*10*0.087),4+(10*i),10);
  glScalef(0.2,0.2,5);
  cubes(1,1,1,1,1);
glPopMatrix();
}
for(int i=1;i<6;i+=2){
glPushMatrix(); //right stick red
 glTranslatef(73-(i*10*0.087),4+(10*i),10);
  glScalef(0.2,0.2,5);
  cubes(1,.1,.1,1,1);
glPopMatrix();
}
for(int i=2;i<7;i+=2){
glPushMatrix(); //tower back  stick  white
 glTranslatef(60+(i*10*0.087),4+(10*i),10);
  glScalef(13-(2*(i*10*0.087)),0.2,0.2);
  cubes(1,1,1,1,1);
glPopMatrix();
}
for(int i=1;i<6;i+=2){
glPushMatrix(); //tower back  stick  red
 glTranslatef(60+(i*10*0.087),4+(10*i),10);
  glScalef(13-(2*(i*10*0.087)),0.2,0.2);
  cubes(1,0.1,0.1,1,1);
glPopMatrix();
}
for(int i=2;i<7;i+=2){
glPushMatrix(); //tower fornt  stick  white
 glTranslatef(60+(i*10*0.087),4+(10*i),15);
  glScalef(13-(2*(i*10*0.087)),0.2,0.2);
  cubes(1,1,1,1,1);
glPopMatrix();
}
for(int i=1;i<6;i+=2){
glPushMatrix(); //tower front  stick  red
 glTranslatef(60+(i*10*0.087),4+(10*i),15);
  glScalef(13-(2*(i*10*0.087)),0.2,0.2);
  cubes(1,0.1,0.1,1,1);
glPopMatrix();
}
for(int i=2;i<6;i+=2){
glPushMatrix(); //left cross stick white
 glTranslatef(60+(i*10*0.087),4+(10*i),10);
 glTranslatef(0.1,0,0.1);
 glRotatef(-5,0,0,1);
 glTranslatef(-0.1,0,-0.1);
 glTranslatef(0.1,0,0.1);
 glRotatef(-63.43,1,0,0);
 glTranslatef(-0.1,0,-0.1);
  glScalef(0.2,0.2,11.18);
  cubes(1,1,1,1,1);
glPopMatrix();
}
for(int i=1;i<6;i+=2){
glPushMatrix(); //left cross stick red
 glTranslatef(60+(i*10*0.087),4+(10*i),10);
 glTranslatef(0.1,0,0.1);
 glRotatef(-5,0,0,1);
 glTranslatef(-0.1,0,-0.1);
 glTranslatef(0.1,0,0.1);
 glRotatef(-63.43,1,0,0);
 glTranslatef(-0.1,0,-0.1);
  glScalef(0.2,0.2,11.18);
  cubes(1,.1,.1,1,1);
glPopMatrix();
}
for(int i=2;i<6;i+=2){
glPushMatrix(); //right cross stick white
 glTranslatef(73-(i*10*0.087),4+(10*i),10);
 glTranslatef(0.1,0,0.1);
 glRotatef(5,0,0,1);
 glTranslatef(-0.1,0,-0.1);
 glTranslatef(0.1,0,0.1);
 glRotatef(-63.43,1,0,0);
 glTranslatef(-0.1,0,-0.1);
  glScalef(0.2,0.2,11.18);
  cubes(1,1,1,1,1);
glPopMatrix();
}
for(int i=1;i<6;i+=2){
glPushMatrix(); //right cross stick red
 glTranslatef(73-(i*10*0.087),4+(10*i),10);
 glTranslatef(0.1,0,0.1);
 glRotatef(5,0,0,1);
 glTranslatef(-0.1,0,-0.1);
 glTranslatef(0.1,0,0.1);
 glRotatef(-63.43,1,0,0);
 glTranslatef(-0.1,0,-0.1);
  glScalef(0.2,0.2,11.18);
  cubes(1,.1,.1,1,1);
glPopMatrix();
}
glPushMatrix(); //gol_machine
glTranslatef(65,63,15);
glScalef(0.3,1,1);
sphere(1,1,1);
glPopMatrix();
glPushMatrix(); //lomba machine
glTranslatef(65,59,11);
glScalef(0.2,8,0.6);
cubes(1,1,1,1,1);
glPopMatrix();
glPushMatrix(); //gol_machine
glTranslatef(67,51,16);
glScalef(1.5,1.5,0.3);
sphere(1,1,1);
glPopMatrix();
glPopMatrix();
}
void atm_machine(){
   glPushMatrix();
   glTranslatef(41.9,2,23);
   glScalef(0.1,7,3);
   cubes(1,1,0,1,1);
   glPopMatrix();
   glPushMatrix();
   glTranslatef(44,2,23);
   glScalef(0.1,7,3);
   cubes(1,1,0,1,1);
   glPopMatrix();
   glEnable(GL_TEXTURE_2D); //atm_machine
   glBindTexture(GL_TEXTURE_2D,15);
   glPushMatrix();
   glTranslatef(42,2,23);
   glScalef(2,7,2);
   cubes(1,1,1,1,1);
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);

}
void booth(){
   glPushMatrix();
   glTranslatef(25,0,0);
   bhavan_vumi();
   glPopMatrix();
   glPushMatrix(); //back_wall
   glTranslatef(36,2,1);
   glScalef(10,10,0.1);
   cubes(1,1,1,1,1);
   glPopMatrix();
   glPushMatrix(); //left_wall
   glTranslatef(36,2,1);
   glScalef(0.1,10,15);
   cubes(1,1,1,1,1);
   glPopMatrix();
   glPushMatrix();
   glTranslatef(46,2,1);//right wall
   glScalef(0.1,10,15);
   cubes(1,1,1,1,1);
   glPopMatrix();//front left wall
   glPushMatrix();
   glTranslatef(36,2,16);
   glScalef(5,10,0.1);
   cubes(1,1,1,1,1);
   glPopMatrix();
   glEnable(GL_TEXTURE_2D); //front left door
   glBindTexture(GL_TEXTURE_2D,12);
   glPushMatrix(); //front left door
   glTranslatef(41,2,16);
   glTranslatef(0,5,0.05);
   glRotatef(fTheta,0,1,0);
   glTranslatef(0,-5,-0.05);
   glScalef(2.5,10,0.1);
   cubes(1,1,1,1,1);
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
   glEnable(GL_TEXTURE_2D); //front  left door
   glBindTexture(GL_TEXTURE_2D,13);
   glPushMatrix();
   glTranslatef(43.5,2,16);
   glTranslatef(2.5,5,0.05);
   glRotatef(-fTheta,0,1,0);
   glTranslatef(-2.5,-5,-0.05);
   glScalef(2.5,10,0.01);
   cubes(1,1,1,1,1);
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
   glPushMatrix(); //chad
   glTranslatef(35,12,1);
   glScalef(12,0.1,17);
   cubes(0.9,0.9,0.9,1,1);
   glPopMatrix();
   glEnable(GL_TEXTURE_2D); //front  right door
   glBindTexture(GL_TEXTURE_2D,14);
   glPushMatrix();
   glTranslatef(36,12,16);
   glScalef(10,4,0.1);
   cubes(1,1,1,1,1);
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
  glPushMatrix();
  glTranslatef(0,0,-20);
  atm_machine();
  glPopMatrix();
}
void tree()
{

      glEnable(GL_TEXTURE_2D); //leaf
      glBindTexture(GL_TEXTURE_2D,18);
      glPushMatrix();
      glTranslatef(20,7,25);
      glScalef(0.25,1,0.25);
      glRotatef(-90,1,0,0);
      leaf(1,1,1,0.1,1,0.1);
      glPopMatrix();
      glDisable(GL_TEXTURE_2D);

}
void tob_tree(){

   glPushMatrix();
   glTranslatef(21.5,2,17.09);
   glScalef(0.5,4,1);
   Basket(0.5,0.2,1,1);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(1.7,0.2,-7);
   glScalef(1,0.7,1);
   tree();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(17,2,17.09);
   glScalef(0.5,4,1);
   Basket(0.5,0.2,1,1);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(-2.7,0.2,-7);
   glScalef(1,0.7,1);
   tree();
   glPopMatrix();

}
void piller_bogi(){

    glPushMatrix();
for(int i=0;i<9;i++){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,19+i);
    glPushMatrix();
    glTranslatef(23.45,12,23.3);
    glScalef(0.01,2,0.7);
    glRotatef(90,0,1,0);
     cubes(1,1,1,1,1);
    glTranslatef(0,0,108);
     cubes(1,1,1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
glTranslatef(15,0,0);
}
glPopMatrix();
}
void sphere2(float r, float g, float b, int a){
                GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
                GLfloat mat_ambient[] = { 0.8*r, 0.8*g, 0.8*b, 1.0 };
                GLfloat mat_diffuse[] = { r, g, b, 1.0 };
                GLfloat mat_specular[] = { 0.7 ,0.7, 0.7, 1.0 };
                GLfloat mat_shininess[] = { 80 };

                glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
                glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
                glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
                glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D,a);

GLUquadric *qobj = gluNewQuadric();
gluQuadricTexture(qobj, GL_TRUE);
gluSphere(qobj, 1, 20, 20);
gluDeleteQuadric(qobj);

glDisable(GL_TEXTURE_2D);



}
void welcome(){

    //glPushMatrix();
glPushMatrix();
int m=0;
int j=0;
for(int i=6-k;i<100;i++){
        if(i<=6){
                glEnable(GL_TEXTURE_2D);
               glBindTexture(GL_TEXTURE_2D,wel[i]);
             // printf("%d ",i);
              glPushMatrix();
              glTranslatef(16,12,21);
              glScalef(1,2,0.04);
              cubes(1,0.1,0.1,1,1);
              glPopMatrix();
              glDisable(GL_TEXTURE_2D);
               glTranslatef(1,0,0);
               j++;
        }
        if(i>=7 && m <(7-j))
        {
                glEnable(GL_TEXTURE_2D);

               glBindTexture(GL_TEXTURE_2D,0);
             // printf("%d ",i);
              glPushMatrix();
              glTranslatef(16,12,21);
              glScalef(1,2,0.04);
              cubes(0,0,0,1,1);
              glPopMatrix();
              glDisable(GL_TEXTURE_2D);
               glTranslatef(1,0,0);
               m++;
        }


}glPopMatrix();
//glPopMatrix();
}
/*void cyclider(int a)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.2, 0.2, 0.3, 1.0 };
    GLfloat mat_diffuse[] = { 1.0, 0.1, 0.1, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 60 };

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

  GLUquadricObj *quadratic;
  quadratic = gluNewQuadric();
  gluCylinder(quadratic,0.2f,0.2f,0.3f,32,32);
}
*/

void siri()
{
    for(int i=0;i<12;i++){ //back left siri
    glPushMatrix();
    glTranslatef(-15+(0.75*i),2+i,22);//-10
    glScalef(0.75,0.25,2);
    cubes(1,.1,.1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-14.25+(0.75*i),2+i,22);//-9.25
    glScalef(0.25,1,2);
     cubes(0.2,0.2,0.2,1,1);
    glPopMatrix();
    }

   for(int i=0;i<13;i++){
    glPushMatrix(); //SIDE LOMBA PICHON
    glTranslatef(-15+(0.75*i),2+i,22);//-10
    glScalef(0.04,2,0.04);
    cubes(1,.1,.1,1,1);
    glPopMatrix();

    glPushMatrix(); //SIDE LOMBA smne
    glTranslatef(-15+(0.75*i),2+i,24);//-10
    glScalef(0.04,2,0.04);
    cubes(1,.1,.1,1,1);
    glPopMatrix();
}
    glPushMatrix(); //lomba railing
     glTranslatef(-15,4,22);
     //glScalef(0.75,0.25,2);
     glTranslatef(0,0,0.02);
       glRotatef(53.13,0,0,1);
     glTranslatef(0,0,0.02);
     glScalef(15,0.1,0.04);
    cubes(1,.1,.1,1,1);
    glPopMatrix();

    glPushMatrix(); //lomba railing
     glTranslatef(-15,4,24);
     //glScalef(0.75,0.25,2);
     glTranslatef(0,0,0.02);
       glRotatef(53.13,0,0,1);
     glTranslatef(0,0,0.02);
     glScalef(15,0.1,0.04);
    cubes(1,.1,.1,1,1);
    glPopMatrix();


for(int i=0;i<12;i++){ //back right siri
    glPushMatrix();
    glTranslatef(-2+(0.75*i),13-i,22); //3
    glScalef(0.75,0.25,2);
    cubes(1,.1,.1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.25+(0.75*i),13-i,22); //2.75
    glScalef(0.25,1,2);
     cubes(0.2,0.2,0.2,1,1);
    glPopMatrix();
    }
for(int i=0;i<13;i++){
    glPushMatrix(); //side lomba
    glTranslatef(-2.04+(0.75*i),14-i,22); //3
    glScalef(0.04,2,0.04);
    cubes(1,.1,.1,1,1);
    glPopMatrix();

    glPushMatrix(); //side lomba
    glTranslatef(-2.04+(0.75*i),14-i,24); //3
    glScalef(0.04,2,0.04);
    cubes(1,.1,.1,1,1);
    glPopMatrix();
}
    glPushMatrix(); //lomba railing
     glTranslatef(-2,16,22);
     //glScalef(0.75,0.25,2);
     glTranslatef(0,0,0.02);
       glRotatef(-53.13,0,0,1);
     glTranslatef(0,0,0.02);
     glScalef(15.64,0.1,0.04);
    cubes(1,.1,.1,1,1);
    glPopMatrix();

    glPushMatrix(); //lomba railing
     glTranslatef(-2,16,24);
     //glScalef(0.75,0.25,2);
     glTranslatef(0,0,0.02);
       glRotatef(-53.13,0,0,1);
     glTranslatef(0,0,0.02);
     glScalef(15.64,0.1,0.04);
    cubes(1,.1,.1,1,1);
    glPopMatrix();
    for(int i=0;i<7;i++){ //majher platform
    glPushMatrix();
    glTranslatef(-6,14,22+(2*i));
    glScalef(4,0.25,1);
    cubes(1,.1,.1,1,1);
    glPopMatrix();

    glPushMatrix(); // mjher lomba
    glTranslatef(-6,14,22+(2*i));
    glScalef(0.04,2,0.04);
    cubes(1,.1,.1,1,1);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-6,14,23+(2*i));
    glScalef(4,0.25,1);
    cubes(0.2,0.2,0.2,1,1);
    glPopMatrix();


    glPushMatrix(); // mjher lomba
    glTranslatef(-6,14,25+(2*i));
    glScalef(0.04,2,0.04);
    cubes(0.2,0.2,0.2,1,1);
    glPopMatrix();

    }
    glPushMatrix(); // middle railing 2 back and front
    glTranslatef(-6,16,22);
    glScalef(4,0.1,0.04);
    cubes(1,.1,.1,1,1);
    glPopMatrix();

    glPushMatrix(); // middle walkway side railing
    glTranslatef(-6,16,24);
    glScalef(0.04,0.1,5);
    cubes(1,.1,.1,1,1);
    glPopMatrix();

    glPushMatrix(); // middle walkway side railing
    glTranslatef(-2,16,24);
    glScalef(0.04,0.1,10);
    cubes(1,.1,.1,1,1);
    glPopMatrix();



    glPushMatrix(); // middle beem
    glTranslatef(-4,2,24);
    glScalef(20,-40.5,20);
    glRotatef(90,1,0,0);
    cyclider(0.5,0.5,0.5);
    glPopMatrix();

}
void overbridge()
{
    glPushMatrix();
    siri();
    glPopMatrix();

    glPushMatrix();
    //glTranslatef(0,0,1);
    glTranslatef(-8,0,63);
    glRotatef(180,0,1,0);
   // glTranslatef(0,0,5);
    siri();

    glPopMatrix();
}

void road()
{
glEnable(GL_TEXTURE_2D);   // road
glBindTexture(GL_TEXTURE_2D,39);
    glPushMatrix();
    glTranslatef(-20,0.4,-52);
    glScalef(200,0.2,7);
     cubes(1,1,1,1,10);
    glPopMatrix();
glDisable(GL_TEXTURE_2D);
}
void bridge(){
glEnable(GL_TEXTURE_2D);   // bridge
glBindTexture(GL_TEXTURE_2D,37);
  glPushMatrix();
  glTranslatef(0,6,-25);
  glScalef(7,0.1,24);
  cubes(0.5,0.5,0.5,1,1);
  glPopMatrix();

  glPushMatrix(); // front dhal bridge
  glTranslatef(0,5,-1.5);
    glTranslatef(3.5,0.5,2.5);
    glRotatef(30,1,0,0);
 glTranslatef(-3.5,-0.5,-2.5);
  glScalef(7,0.1,5);
  cubes(0.5,0.5,0.5,1,1);
  glPopMatrix();

  glPushMatrix(); // front soja bridge
  glTranslatef(0,3.5,2.5);
glTranslatef(3.5,0.5,2.5);
    glRotatef(6,1,0,0);
glTranslatef(-3.5,-0.5,-2.5);
  glScalef(7,0.1,18);
  cubes(0.5,0.5,0.5,1,1);
  glPopMatrix();


  glPushMatrix(); // back dhal bridge
  glTranslatef(0,3.5,-29.5);
    glTranslatef(3.5,0.5,0);
    glRotatef(-30,1,0,0);
 glTranslatef(-3.5,-0.5,0);
  glScalef(7,0.1,5);
  cubes(0.5,0.5,0.5,1,1);
  glPopMatrix();


  glPushMatrix(); // back soja bridge
  glTranslatef(0,0,-47.5);
glTranslatef(3.5,0.5,0);
    glRotatef(-12,1,0,0);
glTranslatef(-3.5,-0.5,0);
  glScalef(7,0.1,20);
  cubes(0.5,0.5,0.5,1,1);
  glPopMatrix();
glDisable(GL_TEXTURE_2D);

  glPushMatrix();  // left side railing
  glTranslatef(0,8,-25);
  glScalef(0.2,0.2,24);
  cubes(1,0.5,0.5,1,1);
  glPopMatrix();


  glPushMatrix();  // right side railing
  glTranslatef(7,8,-25);
  glScalef(0.4,0.4,24);
  cubes(1,0.5,0.5,1,1);
  glPopMatrix();

  glPushMatrix(); // front left dhal railing
  glTranslatef(0,8,-1.5);
    glTranslatef(0.2,0.2,0);
    glRotatef(30,1,0,0);
    glTranslatef(-0.2,-0.2,0);
  glScalef(0.4,0.4,5);
  cubes(1,0.5,0.5,1,1);
  glPopMatrix();

    glPushMatrix(); // front right  dhal railing
  glTranslatef(7,8,-1.5);
    glTranslatef(0.2,0.2,0);
    glRotatef(30,1,0,0);
    glTranslatef(-0.2,-0.2,0);
  glScalef(0.4,0.4,5);
  cubes(1,0.5,0.5,1,1);
  glPopMatrix();


  glPushMatrix(); // front  left soja railing
  glTranslatef(0,5.5,2.5);
    glTranslatef(0.2,0.2,0);
    glRotatef(6,1,0,0);
    glTranslatef(-0.2,-0.2,0);
  glScalef(0.4,0.4,18);
  cubes(1,0.5,0.5,1,1);
  glPopMatrix();

  glPushMatrix(); // front  right soja railing
  glTranslatef(7,5.5,2.5);
    glTranslatef(0.2,0.2,0);
    glRotatef(6,1,0,0);
    glTranslatef(-0.2,-0.2,0);
  glScalef(0.4,0.4,18);
  cubes(1,0.5,0.5,1,1);
  glPopMatrix();

  glPushMatrix(); // back  left dhal railing
  glTranslatef(0,5.5,-29.5);
    glTranslatef(0.2,0.2,0);
    glRotatef(-30,1,0,0);
    glTranslatef(-0.2,-0.2,0);
  glScalef(0.4,0.4,5);
  cubes(1,0.5,0.5,1,1);
  glPopMatrix();


  glPushMatrix(); // back  left dhal railing
  glTranslatef(7,5.5,-29.5);
    glTranslatef(0.2,0.2,0);
    glRotatef(-30,1,0,0);
    glTranslatef(-0.2,-0.2,0);
  glScalef(0.4,0.4,5);
  cubes(1,0.5,0.5,1,1);
  glPopMatrix();


    glPushMatrix(); // middle beem
    glTranslatef(3,3,-6);
    glScalef(2,6,2);
    cylinder(1,1,1);
    glTranslatef(0,0,-7.5);
    cylinder(1,1,1);
    glPopMatrix();

  glPushMatrix(); // back soja railig
  glTranslatef(0,2,-47.5);
    glTranslatef(0.2,0.2,0);
    glRotatef(-12,1,0,0);
    glTranslatef(-0.2,-0.2,0);
  glScalef(0.4,0.4,20);
  cubes(1,0.5,0.5,1,1);
  glPopMatrix();

  glPushMatrix(); // back soja railig
  glTranslatef(7,2,-47.5);
    glTranslatef(0.2,0.2,0);
    glRotatef(-12,1,0,0);
    glTranslatef(-0.2,-0.2,0);
  glScalef(0.4,0.4,20);
  cubes(1,0.5,0.5,1,1);
  glPopMatrix();


  glPushMatrix();  // side beem
  glTranslatef(0,6.1,-25);
  glScalef(0.2,2.2,0.2);
  cubes(1,0.5,0.5,1,1);

for(int j=0;j<24;j++){
   glTranslatef(0,0,5);
   cubes(1,0.5,0.5,1,1);
}
  glPopMatrix();

  glPushMatrix();  // side beem
  glTranslatef(7,6.1,-25);
  glScalef(0.2,2.2,0.2);
  cubes(1,0.5,0.5,1,1);

for(int j=0;j<24;j++){
   glTranslatef(0,0,5);
   cubes(1,0.5,0.5,1,1);
}
  glPopMatrix();


}
void kuli_troly(){

 glPushMatrix(); //hatol
glTranslatef(21.1+(ws*0.8682),4.8,25.2);
glTranslatef(walk2,0,0);
glTranslatef(walk3,0,0);
glScalef(0.1,0.1,1.5);
cubes(0,0,0,1,1);
 glPopMatrix();

 glPushMatrix(); // back dhal rail
glTranslatef(21.1+(ws*0.8682),4.8,25.2);
glTranslatef(walk2,0,0);
glTranslatef(walk3,0,0);
glRotatef(-60,0,0,1);
glScalef(1.5,0.1,0.1);
cubes(0,0,0,1,1);
 glPopMatrix();

 glPushMatrix(); //front dhal rail
glTranslatef(21.1+(ws*0.8682),4.8,26.7);
glTranslatef(walk2,0,0);
glTranslatef(walk3,0,0);
glRotatef(-60,0,0,1);
glScalef(1.5,0.1,0.1);
cubes(0,0,0,1,1);
 glPopMatrix();


 glPushMatrix(); //jinis rakhar jayga
glTranslatef(21.8+(ws*0.8682),3.4,25.2);
glTranslatef(walk2,0,0);
glTranslatef(walk3,0,0);
glScalef(2,0.1,1.8);
cubes(0,0,0,1,1);
 glPopMatrix();
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D,38);
 glPushMatrix(); //jinis 1
glTranslatef(21.8+(ws*0.8682),3.5,25.6);
glTranslatef(walk2,0,0);
glTranslatef(walk3,0,0);
glScalef(1.3,0.4,1);
cubes(1,1,1,1,1);
 glPopMatrix();

glDisable(GL_TEXTURE_2D);
glPushMatrix(); //jinis 1
glTranslatef(21.8+(ws*0.8682),3.9,25.6);
glTranslatef(walk2,0,0);
glTranslatef(walk3,0,0);
glScalef(0.9,0.4,0.8);
cubes(0.1,0.2,1,1,1);
 glPopMatrix();
 glPushMatrix(); //back chaka
glTranslatef(22.5+(ws*0.8682),2.7,25.3);
glTranslatef(walk2,0,0);
glTranslatef(walk3,0,0);
glScalef(0.7,0.7,0.1);
sphere(0.2,0.2,0.2);
 glPopMatrix();

  glPushMatrix(); //front chaka
glTranslatef(22.5+(ws*0.8682),2.7,26.9);
glTranslatef(walk2,0,0);
glTranslatef(walk3,0,0);
glScalef(0.7,0.7,0.1);
sphere(0.2,0.2,0.2);
 glPopMatrix();





}
void khabar_pani(){
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D,0);
glPushMatrix();
glTranslatef(50,7,15);
glScalef(3,4,3);
  cylinder(0.1,0.1,0.1);
glPopMatrix();
glDisable(GL_TEXTURE_2D);
glPushMatrix();
glTranslatef(50,7,16.5);
glScalef(0.1,0.1,0.1);
cubes(1,1,1,1,1);
glPopMatrix();

glPushMatrix(); //tankplatform
glTranslatef(48,4.7,13);
glScalef(4.2,0.3,3.4);
cubes(1,1,1,1,1);
glPopMatrix();

glPushMatrix(); //tankplatform paya1
glTranslatef(48,2,13);
glScalef(0.1,2.7,0.1);
cubes(0,0,0,1,1);
glPopMatrix();

glPushMatrix(); //tankplatform paya2
glTranslatef(52.1,2,13);
glScalef(0.1,2.7,0.1);
cubes(0,0,0,1,1);
glPopMatrix();


glPushMatrix(); //tankplatform paya1
glTranslatef(48.,2,16.3);
glScalef(0.1,2.7,0.1);
cubes(0,0,0,1,1);
glPopMatrix();


glPushMatrix(); //tankplatform paya1
glTranslatef(52.1,2,16.3);
glScalef(0.1,2.7,0.1);
cubes(0,0,0,1,1);
glPopMatrix();



}
void human2(float r, float g, float b,int p){

    glPushMatrix();
glPushMatrix(); //front leg
  glTranslatef(20-(ws*0.8682),2.2,20.5); //27, 26
  glTranslatef(0.1,2.5,0.1);
   glRotatef(-10,0,0,1);
  glTranslatef(-0.1,-2.5,-0.1);
  glTranslatef(0,0.1,0.1);
   glRotatef(walk,0,0,1);
  glTranslatef(0.0,-0.1,-0.1);

  glTranslatef(-walk2,0,0);
  glTranslatef(0.1,2.5,0.1);
   glRotatef(-walk4,0,0,1);
  glTranslatef(-0.1,-2.5,-0.1);
  glScalef(0.2,2.5,0.2);
  cubes(0.8,0.5,0.6,1,1);
glPopMatrix();

glPushMatrix(); //front hand
  glTranslatef(20-(ws*0.8682),4.6,20.7); //27.2
 // glTranslatef(-walk2,0,0);
 // glTranslatef(-walk3,0,0);
/*  glTranslatef(0.1,2,0.1);
   glRotatef(-30,0,0,1);
  glTranslatef(-0.1,-2,-0.1);*/

  glTranslatef(0.1,2.0,0.1);
   glRotatef(10,0,0,1);
  glTranslatef(-0.1,-2.0,-0.1);


glTranslatef(-walk3,0,0);
  glTranslatef(0.1,2,0.1);
   glRotatef(-walk,0,0,1);
  glTranslatef(-0.1,-2,-0.1);

glTranslatef(0,0.1,0.1);
   glRotatef(walk4,0,0,1);
  glTranslatef(0.0,-0.1,-0.1);
  glScalef(0.2,2,0.2);
  cubes(0.8,0.5,0.6,1,1);
glPopMatrix();

glPushMatrix(); //back leg
  glTranslatef(20-(ws*0.8682),2.2,20);


  glTranslatef(0.1,2.5,0.1);
   glRotatef(10,0,0,1);
  glTranslatef(-0.1,-2.5,-0.1);


glTranslatef(-walk3,0,0);
  glTranslatef(0.1,2.5,0.1);
   glRotatef(-walk,0,0,1);
  glTranslatef(-0.1,-2.5,-0.1);

glTranslatef(0,0.1,0.1);
   glRotatef(walk4,0,0,1);
  glTranslatef(0.0,-0.1,-0.1);

  glScalef(0.2,2.5,0.2);
  cubes(0.8,0.5,0.6,1,1);
glPopMatrix();

glPushMatrix(); //back  hand
  glTranslatef(20-(ws*0.8682),4.3,19.8);
  //glTranslatef(-walk2,0,0);
 // glTranslatef(-walk3,0,0);
   glTranslatef(0.1,2,0.1);
   glRotatef(-10,0,0,1);
  glTranslatef(-0.1,-2.,-0.1);
  glTranslatef(0,0.1,0.1);
   glRotatef(walk,0,0,1);
  glTranslatef(0.0,-0.1,-0.1);

  glTranslatef(-walk2,0,0);
  glTranslatef(0.1,2,0.1);
   glRotatef(-walk4,0,0,1);
  glTranslatef(-0.1,-2,-0.1);
  glScalef(0.2,2.5,0.2);
  cubes(0.8,0.5,0.6,1,1);
glPopMatrix();

/*glPushMatrix(); //back  hand
  glTranslatef(19.5-(ws*0.8682),3.3,19.8);
  glTranslatef(-walk2,0,0);
  glTranslatef(-walk3,0,0);
  glScalef(1.2,1.2,0.2);
  cubes(0.9,0.9,0.9,1,1);*/
glPopMatrix();
 glPushMatrix(); //body cube
  glTranslatef(19.9-(ws*0.8682),4.5,20);
  glTranslatef(-walk2,0,0);
  glTranslatef(-walk3,0,0);
  glScalef(0.3,2.5,0.75);
     //sphere2(1,0.6,1,0);
  cubes(r,g,b,1,1);
  //cubes(0.6,0.2,0.6,1,1);
glPopMatrix();

/*  glPushMatrix(); //body sphere
  glTranslatef(20+(ws*0.8682),5.5,26.85);
  glTranslatef(walk2,0,0);
  glTranslatef(walk3,0,0);
  glScalef(0.3,2,0.5);
     sphere2(1,0.6,1,0);
  //cubes(0.6,0.2,0.6,1,1);
glPopMatrix();*/


glPushMatrix(); // mukh
  glTranslatef(20.1-(ws*0.8682),7.5,20.3);
  glTranslatef(-walk2,0,0);
  glTranslatef(-walk3,0,0);
  //glScalef(0.2,2.5,0.7);
  glScalef(0.18,0.5,0.2);
  sphere2(1,1,1,0);
glPopMatrix();

glPopMatrix();
}

void human(float r, float g, float b,int p){

if(p==1){
glPushMatrix();
glPushMatrix(); //front leg
  glTranslatef(20,2.2,20.5); //27, 26
  glTranslatef(0.1,2.5,0.1);
   glRotatef(-10,0,0,1);
  glTranslatef(-0.1,-2.5,-0.1);
  glTranslatef(0,0.1,0.1);
   glRotatef(0,0,0,1);
  glTranslatef(0.0,-0.1,-0.1);

  glTranslatef(0,0,0);
  glTranslatef(0.1,2.5,0.1);
   glRotatef(0,0,0,1);
  glTranslatef(-0.1,-2.5,-0.1);
  glScalef(0.2,2.5,0.2);
  cubes(0.8,0.5,0.6,1,1);
glPopMatrix();

glPushMatrix(); //front hand
  glTranslatef(20,4.6,20.7); //27.2
  glTranslatef(0.1,2.0,0.1);
   glRotatef(10,0,0,1);
  glTranslatef(-0.1,-2.0,-0.1);


glTranslatef(0,0,0);
  glTranslatef(0.1,2,0.1);
   glRotatef(0,0,0,1);
  glTranslatef(-0.1,-2,-0.1);

glTranslatef(0,0.1,0.1);
   glRotatef(0,0,0,1);
  glTranslatef(0.0,-0.1,-0.1);
  glScalef(0.2,2,0.2);
  cubes(0.8,0.5,0.6,1,1);
glPopMatrix();

glPushMatrix(); //back leg
  glTranslatef(20,2.2,20);


  glTranslatef(0.1,2.5,0.1);
   glRotatef(10,0,0,1);
  glTranslatef(-0.1,-2.5,-0.1);


glTranslatef(0,0,0);
  glTranslatef(0.1,2.5,0.1);
   glRotatef(0,0,0,1);
  glTranslatef(-0.1,-2.5,-0.1);

glTranslatef(0,0.1,0.1);
   glRotatef(0,0,0,1);
  glTranslatef(0.0,-0.1,-0.1);

  glScalef(0.2,2.5,0.2);
  cubes(0.8,0.5,0.6,1,1);
glPopMatrix();

glPushMatrix(); //back  hand
  glTranslatef(20,4.3,19.8);
  glTranslatef(0,0,0);
  glTranslatef(0,0,0);
  glScalef(0.2,2.5,0.2);
  cubes(0.8,0.5,0.6,1,1);
glPopMatrix();

glPushMatrix(); //back  hand bag
  glTranslatef(19.5,3.3,19.8);
  glTranslatef(0,0,0);
  glTranslatef(0,0,0);
  glScalef(1.2,1.2,0.2);
  cubes(0.9,0.9,0.9,1,1);
glPopMatrix();
 glPushMatrix(); //body cube
  glTranslatef(19.9,4.5,20);
  glScalef(0.3,2.5,0.75);
     //sphere2(1,0.6,1,0);
  cubes(r,g,b,1,1);
  //cubes(0.6,0.2,0.6,1,1);
glPopMatrix();
glPushMatrix(); // mukh
  glTranslatef(20.1,7.5,20.3);
  glScalef(0.18,0.5,0.2);
  sphere2(1,1,1,0);
glPopMatrix();

glPopMatrix();

}
else{
glPushMatrix();
glPushMatrix(); //front leg
  glTranslatef(20-(ws*0.8682),2.2,20.5); //27, 26
  glTranslatef(0.1,2.5,0.1);
   glRotatef(-10,0,0,1);
  glTranslatef(-0.1,-2.5,-0.1);
  glTranslatef(0,0.1,0.1);
   glRotatef(walk,0,0,1);
  glTranslatef(0.0,-0.1,-0.1);

  glTranslatef(-walk2,0,0);
  glTranslatef(0.1,2.5,0.1);
   glRotatef(-walk4,0,0,1);
  glTranslatef(-0.1,-2.5,-0.1);
  glScalef(0.2,2.5,0.2);
  cubes(0.8,0.5,0.6,1,1);
glPopMatrix();

glPushMatrix(); //front hand
  glTranslatef(20-(ws*0.8682),4.6,20.7); //27.2
 // glTranslatef(-walk2,0,0);
 // glTranslatef(-walk3,0,0);
/*  glTranslatef(0.1,2,0.1);
   glRotatef(-30,0,0,1);
  glTranslatef(-0.1,-2,-0.1);*/

  glTranslatef(0.1,2.0,0.1);
   glRotatef(10,0,0,1);
  glTranslatef(-0.1,-2.0,-0.1);


glTranslatef(-walk3,0,0);
  glTranslatef(0.1,2,0.1);
   glRotatef(-walk,0,0,1);
  glTranslatef(-0.1,-2,-0.1);

glTranslatef(0,0.1,0.1);
   glRotatef(walk4,0,0,1);
  glTranslatef(0.0,-0.1,-0.1);
  glScalef(0.2,2,0.2);
  cubes(0.8,0.5,0.6,1,1);
glPopMatrix();

glPushMatrix(); //back leg
  glTranslatef(20-(ws*0.8682),2.2,20);


  glTranslatef(0.1,2.5,0.1);
   glRotatef(10,0,0,1);
  glTranslatef(-0.1,-2.5,-0.1);


glTranslatef(-walk3,0,0);
  glTranslatef(0.1,2.5,0.1);
   glRotatef(-walk,0,0,1);
  glTranslatef(-0.1,-2.5,-0.1);

glTranslatef(0,0.1,0.1);
   glRotatef(walk4,0,0,1);
  glTranslatef(0.0,-0.1,-0.1);

  glScalef(0.2,2.5,0.2);
  cubes(0.8,0.5,0.6,1,1);
glPopMatrix();

glPushMatrix(); //back  hand
  glTranslatef(20-(ws*0.8682),4.3,19.8);
  glTranslatef(-walk2,0,0);
  glTranslatef(-walk3,0,0);
  glScalef(0.2,2.5,0.2);
  cubes(0.8,0.5,0.6,1,1);
glPopMatrix();

glPushMatrix(); //back  hand bag
  glTranslatef(19.5-(ws*0.8682),3.3,19.8);
  glTranslatef(-walk2,0,0);
  glTranslatef(-walk3,0,0);
  glScalef(1.2,1.2,0.2);
  cubes(0.2,0.2,0.2,1,1);
glPopMatrix();
 glPushMatrix(); //body cube
  glTranslatef(19.9-(ws*0.8682),4.5,20);
  glTranslatef(-walk2,0,0);
  glTranslatef(-walk3,0,0);
  glScalef(0.3,2.5,0.75);
     //sphere2(1,0.6,1,0);
  cubes(r,g,b,1,1);
  //cubes(0.6,0.2,0.6,1,1);
glPopMatrix();

/*  glPushMatrix(); //body sphere
  glTranslatef(20+(ws*0.8682),5.5,26.85);
  glTranslatef(walk2,0,0);
  glTranslatef(walk3,0,0);
  glScalef(0.3,2,0.5);
     sphere2(1,0.6,1,0);
  //cubes(0.6,0.2,0.6,1,1);
glPopMatrix();*/


glPushMatrix(); // mukh
  glTranslatef(20.1-(ws*0.8682),7.5,20.3);
  glTranslatef(-walk2,0,0);
  glTranslatef(-walk3,0,0);
  //glScalef(0.2,2.5,0.7);
  glScalef(0.18,0.5,0.2);
  sphere2(1,1,1,0);
glPopMatrix();

glPopMatrix();
}
}





void kuli(){

glPushMatrix();
glPushMatrix(); //front leg
  glTranslatef(20+(ws*0.8682),2.2,26); //27
  glTranslatef(0.1,2.5,0.1);
   glRotatef(10,0,0,1);
  glTranslatef(-0.1,-2.5,-0.1);
  glTranslatef(0,0.1,0.1);
   glRotatef(-walk,0,0,1);
  glTranslatef(0.0,-0.1,-0.1);

  glTranslatef(walk2,0,0);
  glTranslatef(0.1,2.5,0.1);
   glRotatef(walk4,0,0,1);
  glTranslatef(-0.1,-2.5,-0.1);
  glScalef(0.2,2.5,0.2);
  cubes(0.8,0.5,0.6,1,1);
glPopMatrix();

glPushMatrix(); //front hand
  glTranslatef(20+(ws*0.8682),4.6,26.2); //27.2
  glTranslatef(walk2,0,0);
  glTranslatef(walk3,0,0);
  glTranslatef(0.1,2,0.1);
   glRotatef(30,0,0,1);
  glTranslatef(-0.1,-2,-0.1);
  glScalef(0.2,2,0.2);
  cubes(0.8,0.5,0.6,1,1);
glPopMatrix();

glPushMatrix(); //back leg
  glTranslatef(20+(ws*0.8682),2.2,25.5);


  glTranslatef(0.1,2.5,0.1);
   glRotatef(-10,0,0,1);
  glTranslatef(-0.1,-2.5,-0.1);


glTranslatef(walk3,0,0);
  glTranslatef(0.1,2.5,0.1);
   glRotatef(walk,0,0,1);
  glTranslatef(-0.1,-2.5,-0.1);

glTranslatef(0,0.1,0.1);
   glRotatef(-walk4,0,0,1);
  glTranslatef(0.0,-0.1,-0.1);

  glScalef(0.2,2.5,0.2);
  cubes(0.8,0.5,0.6,1,1);
glPopMatrix();

glPushMatrix(); //back  hand
  glTranslatef(20+(ws*0.8682),4.3,25.3);
  glTranslatef(walk2,0,0);
  glTranslatef(walk3,0,0);
  glTranslatef(0.1,2,0.1);
   glRotatef(30,0,0,1);
  glTranslatef(-0.1,-2,-0.1);
  glScalef(0.2,2.5,0.2);
  cubes(0.8,0.5,0.6,1,1);
glPopMatrix();
 glPushMatrix(); //body cube
  glTranslatef(19.9+(ws*0.8682),4.5,25.5);
  glTranslatef(walk2,0,0);
  glTranslatef(walk3,0,0);
  glScalef(0.3,2.5,0.75);
     //sphere2(1,0.6,1,0);
  cubes(0.6,0.2,0.6,1,1);
glPopMatrix();

/*  glPushMatrix(); //body sphere
  glTranslatef(20+(ws*0.8682),5.5,26.85);
  glTranslatef(walk2,0,0);
  glTranslatef(walk3,0,0);
  glScalef(0.3,2,0.5);
     sphere2(1,0.6,1,0);
  //cubes(0.6,0.2,0.6,1,1);
glPopMatrix();*/


glPushMatrix(); // mukh
  glTranslatef(20.1+(ws*0.8682),7.5,25.8);
  glTranslatef(walk2,0,0);
  glTranslatef(walk3,0,0);
  //glScalef(0.2,2.5,0.7);
  glScalef(0.18,0.5,0.2);
  sphere2(1,1,1,0);
glPopMatrix();

glPopMatrix();

}
void ticket_line(){

glPushMatrix();
glTranslatef(-4.7,0,19.5);
glRotatef(90,0,1,0);
human(1,0.1,0.1,1);
glTranslatef(-2,0,0);
human(0.2,0.1,1,1);
glTranslatef(-2,0,0);
human(0.0,1,0.1,1);
glTranslatef(-2,0,0);
human(1,1,0.1,1);
glPopMatrix();




}

void tree1(int a)
{
     glEnable(GL_TEXTURE_2D);   //tree bakol
     glBindTexture(GL_TEXTURE_2D,35);
      glPushMatrix();
      glTranslatef(15,6,25);
      glScalef(1,15,1);
      cylinder(0.5,0.5,0.5);
      glPopMatrix();
      glPushMatrix();
      glTranslatef(16.5,11,25);
     // glTranslatef(10,25.5);
      glRotatef(-45,0,0,1);
      //glTranslatef(11,10,25.5);
      glScalef(0.5,5,0.2);
      cylinder(1,1,1);
      glPopMatrix();
      glPushMatrix();
      glTranslatef(14,11,25);
     // glTranslatef(10,25.5);
      glRotatef(30,0,0,1);
      //glTranslatef(11,10,25.5);
      glScalef(0.5,5,0.2);
      cylinder(1,1,1);
      glPopMatrix();
     glDisable(GL_TEXTURE_2D);
 glEnable(GL_TEXTURE_2D);   //platform basket
     glBindTexture(GL_TEXTURE_2D,0);
      glPushMatrix();
      glTranslatef(15,16,25);
      glScalef(2,5,3);
      sphere2(0.1,1.0,0.1,a);
      glPopMatrix();
      glPushMatrix(); // right leave
      glTranslatef(17,15,25);
      glScalef(2,4,2);
      sphere2(0.1,1.0,0.1,a);
      glPopMatrix();
      glPushMatrix(); // left leave
      glTranslatef(13.5,15,25);
      glScalef(2,4,2);
      sphere2(0.1,1.0,0.1,a);
      glPopMatrix();
glDisable(GL_TEXTURE_2D);
}
void sky(int a){
    glPushMatrix(); // sky
      glScalef(200,200,200);
      //glTranslatef(2,5,5);
       sphere2(0.8,0.8,1,a);
    glPopMatrix();




}
void bench()
{
    glPushMatrix();
     glTranslatef(17,5,24) ; //bosbar
     glScalef(3,0.1,1);
     cubes(1,0.1,0.1,1,1);
    glPopMatrix();
    glPushMatrix();//bosbar
     glTranslatef(17,5,25) ;
     glScalef(3,0.1,0.9);
     cubes(1,1,0,1,1);
    glPopMatrix();
    glPushMatrix(); //helan
     glTranslatef(17,5,24) ;
     glScalef(3,2,0.1);
     cubes(0.4,0.4,.1,1,1);
    glPopMatrix();

    glPushMatrix();
     glTranslatef(17,6,24) ; //left hatol
     glScalef(0.1,0.1,2);
     cubes(1,1,1,1,1);
    glPopMatrix();

    glPushMatrix();
     glTranslatef(19.9,6,24) ; //right hatol
     glScalef(0.1,0.1,2);
     cubes(1,1,1,1,1);
    glPopMatrix();

    glPushMatrix();
     glTranslatef(17,2,24) ; //left back paya
     glScalef(0.1,3,0.1);
     cubes(1,1,1,1,1);
    glPopMatrix();

    glPushMatrix();
     glTranslatef(17,2,25.9) ; //left front paya
     glScalef(0.1,4,0.1);
     cubes(1,1,1,1,1);
    glPopMatrix();


    glPushMatrix();
     glTranslatef(19.9,2,24) ; //right back paya
     glScalef(0.1,3,0.1);
     cubes(1,1,1,1,1);
    glPopMatrix();

    glPushMatrix();
     glTranslatef(19.9,2,25.9) ; //left front paya
     glScalef(0.1,4,0.1);
     cubes(1,1,1,1,1);
    glPopMatrix();






}
void moon(){
 /*glEnable(GL_TEXTURE_2D);   //moon
glBindTexture(GL_TEXTURE_2D,47);*/
glPushMatrix();
glTranslatef(50,150,-110);
glScalef(5,5,5);
sphere2(1,1,1,47);
glPopMatrix();
 //glDisable(GL_TEXTURE_2D);


}
void Light_One()
{
    glPushMatrix();
    GLfloat light_position[] = { 15, 40.0, 20.0, 1.0 };
    glLightfv( GL_LIGHT0, GL_POSITION, light_position);
    glPopMatrix();
}

void Light_Two()
{
    glPushMatrix();
    GLfloat light_position[] = { 5.0, 7.0, 10.0, 1.0 };
    glLightfv( GL_LIGHT1, GL_POSITION, light_position);
    glPopMatrix();
}

void Light_Three()
{
    glPushMatrix();
   // GLfloat light_position[] = { -16-ftTheta,15,31, 1.0 };  //-23, 2.5, -6.0
    GLfloat light_position[] = { 50,140,-103, 1.0 };  //-23, 2.5, -6.0
    glLightfv( GL_LIGHT2, GL_POSITION, light_position);
    GLfloat spot_direction[] = { 0.0, 1.0, -1.0 };
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
    glLightf( GL_LIGHT2, GL_SPOT_CUTOFF, 30.0);
    glPopMatrix();
}
/*void Light_Four()
{
    glPushMatrix();
    GLfloat light_position[] = { -16-ftTheta,10,31, 1.0 };  //-23, 2.5, -6.0
    glLightfv( GL_LIGHT2, GL_POSITION, light_position);
    GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot_direction);
    glLightf( GL_LIGHT3, GL_SPOT_CUTOFF, 20.0);
    glPopMatrix();
}*/


/*double eye[3]={20,15,45};
double center[3]={20,5,8};*/
 double eye[3]={20,9,47};
double center[3]={20,9,0};
double up[3]={0,1,0};
double zoom[3]={1,1,1};
double wind[2]={3,8};
double nzoom[1]={4};

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum(-wind[0], wind[1], -wind[0], wind[1], nzoom[0], 500);
    //gluPerspective(60,1,5,100);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    //gluLookAt(6,5,13, 4,2,0, 0,1,0);
    gluLookAt(eye[0],eye[1],eye[2],  center[0],center[1],center[2], up[0],up[1],up[2]);
    //gluLookAt(3,13,4, 4,0,5, -1,0,0);

    glViewport(0, 0, windowHeight, windowWidth);

    glEnable(GL_LIGHTING);
    Light_One();
    Light_Two();
    Light_Three();
//    Light_Four();
    // glRotate;f(45, 0, 0, 1 );
    // triangle();
      glRotatef( theta, axis_x, axis_y, 0.0 );

      glScalef(zoom[0],zoom[1],zoom[2]);
      rail_line();
      bhavan_vumi();
        glPushMatrix();
        ticket();
       glPopMatrix();
      bhavan(1,1,1);
      glPushMatrix();
        glTranslatef(0,11,0);
        bhavan(1,1,1);
      glPopMatrix();
      banner();
      mati();
      glPushMatrix();
        glTranslatef(0,0,-119);
            mati();
      glPopMatrix();
      pond();
      fence();
      glPushMatrix();
        glTranslatef(0,0,-22);
        fence();
      glPopMatrix();


      glPushMatrix();
        glTranslatef(65,0,0);
        bhavan_vumi();
        bhavan(0.9,0.9,0.1);
      glPopMatrix();

   /*  glPushMatrix(); // front_train
      glTranslatef(-4,-.5,15);
       glTranslatef(-fTheta,0,0);
       train();
      glPopMatrix();*/


     glPushMatrix(); //back_train
        glTranslatef(-180,-.5,11); //-80
       glTranslatef(-ftTheta,0,0);
       train();
      glPopMatrix();
      glPushMatrix();
       glTranslatef(-177,0,0); //-77
       glTranslatef(-ftTheta,0,0);
      engine();
      glPopMatrix();

      glPushMatrix();
      platform();
      glPopMatrix();


      glPushMatrix();
      glTranslatef(0,0,16);
      platform();
      glPopMatrix();

     glEnable(GL_TEXTURE_2D);   //platform basket
     glBindTexture(GL_TEXTURE_2D,11);
      glPushMatrix();
      glTranslatef(10,2,23);
      glScalef(1,6,1);
      Basket(1,1,1,1);
      for(int j=0;j<10;j++){
      glTranslatef(15,0,0);
      Basket(1,1,1,1);
      }
      glPopMatrix();
      glDisable(GL_TEXTURE_2D);
      glPushMatrix();
      fan();
      for(int j=0;j<15;j++)
      {
          glTranslatef(15,0,0);
          fan();
      }
      glPopMatrix();

      booth();
      tower();
      time_table();
      tob_tree();
      piller_bogi();
      welcome();
      overbridge();

      glPushMatrix(); //opaas gach
      glScalef(1.5,1.5,1.5);
      glTranslatef(-30,0,-45);
       tree1(18);
    for(int i=0;i<50;i++){
      glTranslatef(7,0,0);
       tree1(18);
    }
     glPopMatrix();


      glPushMatrix();
      glScalef(1.5,1.5,1.5);
      glTranslatef(-15,0,-17);
       tree1(45);
      glPopMatrix();

      glPushMatrix(); // bhavan ar atm er middle tree
      glScalef(1.5,2.2,1.5);
      glTranslatef(7,0,-17);
       tree1(45);
      glPopMatrix();

    glPushMatrix(); // atm ar tower er majher tree
      glScalef(1.5,2.2,1.5);
      glTranslatef(23,0,-17);
       tree1(45);
      glPopMatrix();
    glPushMatrix(); // sky
    if(night==false)
    {
        sky(36);
    }
    else{
        sky(46);
            glPopMatrix();
             moon();
            glPushMatrix();
    }
      sky(36);
 //  atm ar tower er majher  choto tree
       //glTranslatef(18,-,-15);
      glScalef(3,5,3);
      glTranslatef(-0.5,-7,-20);
       tree();
    glPopMatrix();

      glPushMatrix(); // bagan
      glScalef(1.5,1.5,1.5);
      glTranslatef(-15,-7,-15);
       tree();
      for(int i=0;i<4;i++)
      {
        glPushMatrix();
          for(int j=0;j<6;j++)
          {
      glTranslatef(-(1.3*j),0,0);
      tree();
          }
          glPopMatrix();
      glTranslatef(0,0,-(2*i));
      }

      glPopMatrix();
      glPushMatrix();
      glScalef(2,2,2);
      sphere2(1,1,1,35);
      glPopMatrix();

      glPushMatrix(); // bridge
      glTranslatef(95,0,0);
       bridge();
      glPopMatrix();

    glPushMatrix();
       road();
    glPopMatrix();


    glPushMatrix(); //kuli_1
       kuli();
    glPopMatrix();
    glPushMatrix();
       kuli_troly();
    glPopMatrix();


    glPushMatrix(); //kuli_2
    glTranslatef(5,0,0);
       kuli();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(5,0,0);
       kuli_troly();
    glPopMatrix();


    glPushMatrix();
       human(0.6,0.1,0.6,0);
    glPopMatrix();

    glPushMatrix();
       glTranslatef(50,0,42);
       glRotatef(180,0,1,0);
       human(0.1,1.0,0.1,0);
       glTranslatef(3,0,0);
       human2(1,0,0,0);
    glPopMatrix();


    glPushMatrix();
       glTranslatef(-4,0,0);
       human2(1.0,0.1,0.6,1);
    glPopMatrix();

    glPushMatrix();
       ticket_line();
    glPopMatrix();


    glPushMatrix();
       khabar_pani();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(30,0,-4);
       bench();
    glTranslatef(15,0,0);
        bench();
    glTranslatef(15,0,0);
        bench();

    glTranslatef(45,0,0);
        bench();
    glTranslatef(15,0,0);
        bench();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(60,0,-21);
        bench();
      glTranslatef(3.2,0,0);
      bench();
      glTranslatef(3.2,0,0);
      bench();
      glTranslatef(3.2,0,0);
      bench();
    glPopMatrix();

 glPushMatrix();
      glScalef(0.5,1,1);
     glTranslatef(-2.5,0,22);
     glRotatef(90,0,1,0);
      bench();
  glPopMatrix();

    glFlush();
    glutSwapBuffers();
}
void Pitch_y1(){
    GLfloat ty, tz;

    ty=center[1]-eye[1];//ty = look_y - eye_y;
    tz=center[2]-eye[2];//tz = look_z - eye_z;

    dy = ty*cs_angle-tz*sn_angle;
    dz = ty*sn_angle+tz*cs_angle;

    center[1]=dy+eye[1];//look_y = dy + eye_y;
    center[2]=dz+eye[2];//look_z = dz + eye_z;

}
void Pitch_y2(){
    GLfloat ty, tz;

   ty=center[1]-eye[1];// ty = look_y - eye_y;
   tz=center[2]-eye[2];// tz = look_z - eye_z;

    dy = ty*cs_angle+tz*sn_angle;// dy = ty*cs_angle+tz*sn_angle;
    dz = ty*sn_angle+tz*cs_angle;// dz = -ty*sn_angle+tz*cs_angle;

       center[1]=dy+eye[1]; //look_y = dy + eye_y;
       center[2]=dz+eye[2];////look_z = dz + eye_z;

}
void Yaw_y1(){
    GLfloat tx, tz;

    tx=center[0]-eye[0];//tx = look_x - eye_x;
    tz=center[2]-eye[2];//tz = look_z - eye_z;

    dx = tx*cs_angle+tz*sn_angle;//dx = tx*cs_angle+tz*sn_angle;
    dz = -tx*sn_angle+tz*cs_angle;//dz = -tx*sn_angle+tz*cs_angle;

    center[0]=dx+eye[0];//look_x = dx + eye_x;
    center[2]=dz+eye[2];//look_z = dz + eye_z;

}

void Yaw_y2(){
    GLfloat tx, tz;

    tx=center[0]-eye[0];//tx = look_x - eye_x;
    tz=center[2]-eye[2];//tz = look_z - eye_z;

    dx = tx*cs_angle-tz*sn_angle;//dx = tx*cs_angle-tz*sn_angle;
    dz = tx*sn_angle+tz*cs_angle;//dz = tx*sn_angle+tz*cs_angle;

    center[0]=dx+eye[0];//look_x = dx + eye_x;
    center[2]=dz+eye[2];//look_z = dz + eye_z;

}


void myKeyboardFunc( unsigned char key, int x, int y )
{
    //printf("%c%d%d",key,x,y);
    float x1, z1, r, theta1, dx, dz, dx_norm, dz_norm, r1=1;
    x1=center[0]-eye[0];
    z1=center[2]-eye[2];
    r=sqrt(x1*x1+z1*z1);

    if(x1==0)
    {
        if(z1>0)
        {
            theta1 = 90;
        }
        else if(z1<0)
        {
            theta1 = -90;
        }
    }
    else
        theta1=atan(z1/x1) * 180 / 3.1416;

    if((z1>0 && theta1<0) || (z1<0 && theta1>0))
        theta1 += 180;
    else if(z1<0 && theta1<0)
    {
        theta1 += 360;
    }

    dx = r1*cos(theta1 * 3.1416 / 180);
    dz = r1*sin(theta1 * 3.1416 / 180);

    dx_norm = r1*cos((theta1-90) * 3.1416 / 180);
    dz_norm = r1*sin((theta1-90) * 3.1416 / 180);

    switch ( key )
    {
    case 'p':
        center[1]+=0.1;
        center[2]=-sqrt(eye[2]*eye[2]-(center[0]-eye[0])*(center[0]-eye[0])-(center[1]-eye[1])*(center[1]-eye[1]))+eye[2];
        gluLookAt(eye[0],eye[1],eye[2],  center[0],center[1],center[2], up[0],up[1],up[2]);
        break;
    case 'P':
        center[1]-=0.1;
        center[2]=-sqrt(eye[2]*eye[2]-(center[0]-eye[0])*(center[0]-eye[0])-(center[1]-eye[1])*(center[1]-eye[1]))+eye[2];
        gluLookAt(eye[0],eye[1],eye[2],  center[0],center[1],center[2], up[0],up[1],up[2]);
        break;
    case 'o':
        center[1]+=0.1;
        center[0]=-sqrt(eye[0]*eye[0]-(center[2]-eye[2])*(center[2]-eye[2])-(center[1]-eye[1])*(center[1]-eye[2]))+eye[0];
        gluLookAt(eye[0],eye[1],eye[2],  center[0],center[1],center[2], up[0],up[1],up[2]);
        break;
    case 'O':
        center[1]-=0.1;
        center[0]=-sqrt(eye[0]*eye[0]-(center[2]-eye[2])*(center[2]-eye[2])-(center[1]-eye[1])*(center[1]-eye[2]))+eye[0];
        gluLookAt(eye[0],eye[1],eye[2],  center[0],center[1],center[2], up[0],up[1],up[2]);
        break;
    case 'w':
        up[0]+=0.01;
        up[1]=sqrt(1-up[0]*up[0]);
        gluLookAt(eye[0],eye[1],eye[2],  center[0],center[1],center[2], up[0],up[1],up[2]);
        break;

    case 'W':
        up[0]-=0.01;
        up[1]=sqrt(1-up[0]*up[0]);
        gluLookAt(eye[0],eye[1],eye[2],  center[0],center[1],center[2], up[0],up[1],up[2]);
        break;

    case 'c':
        center[0]-=0.1;
        center[2]=-sqrt(eye[2]*eye[2]-(center[0]-eye[0])*(center[0]-eye[0])-(center[1]-eye[1])*(center[1]-eye[1]))+eye[2];
        gluLookAt(eye[0],eye[1],eye[2],  center[0],center[1],center[2], up[0],up[1],up[2]);
        break;
    case 'C':
        center[0]+=0.1;
        center[2]=-sqrt(eye[2]*eye[2]-(center[0]-eye[0])*(center[0]-eye[0])-(center[1]-eye[1])*(center[1]-eye[1]))+eye[2];
        gluLookAt(eye[0],eye[1],eye[2], center[0],center[1],center[2], up[0],up[1],up[2]);
        break;
        bRotate = !bRotate;
        uRotate = true;
        axis_x=0.0;
        axis_y=1.0;
        break;
    case 'z':
        zoom[2]+=0.1;
        glScalef(zoom[0],zoom[1],zoom[2]);
        break;
    case 'Z':
        zoom[2]-=0.1;
        glScalef(zoom[0],zoom[1],zoom[2]);
        break;
    case 'n':
        nzoom[0]-=1;
        break;
    case 'N':
        nzoom[0]+=1;
        break;
    case 'j':
        wind[0]-=1;
        wind[1]-=1;
        break;
    case 'J':
        wind[0]+=1;
        wind[1]+=1;
        break;
    case 'f':
        eye[0]-=1;
        gluLookAt(eye[0],eye[1],eye[2], center[0],center[1],center[2], up[0],up[1],up[2]);
        break;
    case 'F':
        eye[0]+=1;
        gluLookAt(eye[0],eye[1],eye[2], center[0],center[1],center[2], up[0],up[1],up[2]);
        break;
    case 'g':
        eye[1]-=1;
        gluLookAt(eye[0],eye[1],eye[2], center[0],center[1],center[2], up[0],up[1],up[2]);
        break;
    case 'G':
        eye[1]+=1;
        gluLookAt(eye[0],eye[1],eye[2], center[0],center[1],center[2], up[0],up[1],up[2]);
        break;
    case 'h':
        eye[2]-=1;
        gluLookAt(eye[0],eye[1],eye[2], center[0],center[1],center[2], up[0],up[1],up[2]);
        break;
    case 'H':
        eye[2]+=1;
        gluLookAt(eye[0],eye[1],eye[2], center[0],center[1],center[2], up[0],up[1],up[2]);
        break;
    case 'b':
        eye[0]=55;
        eye[1]=30;
        eye[2]=29;
        center[0]=55;
        center[1]=4;
        center[2]=8;
      /*  eye[0]=20;
        eye[1]=30;
        eye[2]=29;
        center[0]=20;
        center[1]=3;
        center[2]=27;*/
        /* double eye[3]={40,15,45};
          double center[3]={40,5,8};*/
        gluLookAt(eye[0],eye[1],eye[2], center[0],center[1],center[2], up[0],up[1],up[2]);
        break;
    /*case 'k':
        eye[0]=5;
        eye[1]=4;
        eye[2]=14;
        gluLookAt(eye[0],eye[1],eye[2], center[0],center[1],center[2], up[0],up[1],up[2]);
        break;*/
    case 'i':        ///default
         //double eye[3]={20,9,47};
         //double center[3]={20,9,0};
          eye[0]=20;
          eye[1]=9;
          eye[2]=47;
          center[0]=20;
          center[1]=9;
          center[2]=-50;
          up[0]=0;
          up[1]=1;
          up[2]=0;
          zoom[0]=1;
          zoom[1]=1;
          zoom[2]=1;
          wind[0]=3;
          wind[1]=6;
        break;
    case 'q':
        night=true;
        break;

    case 'Q':
        night=false;
        break;
    case 'y':
    case 'Y':
        bRotate = !bRotate;
        uRotate = false;
        axis_x=0.0;
        axis_y=0.0;
        break;

    case 'r':
    case 'R':
        uRotate = !uRotate;
        bRotate = false;
        axis_x=1.0;
        axis_y=0.0;
        break;
    case '+':
        if(walkrotate1==true)
        {
        walk +=0.5;
        walk3 +=0.021705;
        if(walk>20.0){
             walk4 =0.0;
             walk2 =0.0;
            walkrotate1=false;
            walkrotate2=true;
        }
        }
       // kuli()
        if(walkrotate2==true)
        {
        walk4 +=0.5;
        walk2 +=0.021705;
        if(walk4>20.0)
        {
             walk =0.0;
             walk3 =0.0;
             walk2=0.0;
             walk4=0.0;
            ws+=2;
            walkrotate1=true;
            walkrotate2=false;
        }
        }
        break;
    case '-':
          fTheta -= 2;
        //Tzval-=0.2;
        break;
    case '*':
       //fan on off
        fTheta += 2;
        break;
    case 'u':   //new add
        eye[0] += dx_norm*5;
        eye[2] += dz_norm*5;


        center[0] += dx_norm*5;
         center[2] += dz_norm*5;
        break;
    case 'U':
        eye[0] += dx*5;
        eye[2] += dz*5;
        center[0] += dx*5;
        center[2] += dz*5;
        break;
    case 'K':
        eye[0] -= dx*5;
        eye[2] -= dz*5;

        center[0] -= dx*5;
        center[2] -= dz*5;
        break;
    case 'k':
        eye[0] -= dx_norm*5;
        eye[2]-= dz_norm*5;

        center[0]-= dx_norm*5;
        center[2] -= dz_norm*5;

    case 'l':  //Train
          ftTheta -= 2;
          //printf("%f",ftTheta);
           sound+=1;
           if(ftTheta==-94.0)//sound==11 )
           {
               //continue
          //PlaySound("C:\\Users\\ASUS !\\Downloads\\train_short_3.wav", 0,SND_ASYNC);
           }


        break;
    case 'L': //train
        ftTheta += 2;
        sound-=1;
        break;

    case '1':
        if(Light1 == false)
        {
            Light1 = true; ambL1 = true; diffL1 = true; specL1 = true;
            glEnable( GL_LIGHT0);   //Turn on light 1
        }
        else if(Light1 == true)
        {
            Light1 = false; ambL1 = false; diffL1 = false; specL1 = false;
            glDisable( GL_LIGHT0);   //Turn off light 2
        }
        break;
    case '2':
        if(Light2 == false)
        {
            Light2 = true; ambL2 = true; diffL2 = true; specL2 = true;
            glEnable( GL_LIGHT1);    //Turn on light 2
        }
        else if(Light2 == true)
        {
            Light2 = false; ambL2 = false; diffL2 = false; specL2 = false;
            glDisable( GL_LIGHT1);  //Turn off light 2
        }
        break;
    case '3':
        if(spotLight == false)
        {
            spotLight = true; ambL3 = true; diffL3 = true; specL3 = true;
            glEnable( GL_LIGHT2);   //Turn on spot light
        }
        else if(spotLight == true)
        {
            spotLight = false; ambL3 = false; diffL3 = false; specL3 = false;
            glDisable( GL_LIGHT2);  //Turn off spot light
        }
        break;
    case 'a':
        ambL1 =! ambL1;
        break;
    case 'A':
        ambL2 =! ambL2;
        break;
    case 'M':
        ambL3 =! ambL3;
        break;
    case 'd':
        diffL1 =! diffL1;
        break;
    case 'D':
        diffL2 =! diffL2;
        break;
    case 'E':
        diffL3 =! diffL3;
        break;
    case 's':
        specL1 =! specL1;
        break;
    case 'S':
        specL2 =! specL2;
        break;
    case 'T':
        specL3 =! specL3;
        break;
    case '4':
        Pitch_y1();
        break;
    case '5':
        Pitch_y2();
        break;
    case '6':
        Yaw_y1();
        break;
    case '7':
        Yaw_y2();
        break;

    case 27:	// Escape key
        exit(1);
    }
}



void animate()
{
   /* mTheta -= 1.0/60;
    hTheta -= 1.0/3600;
    if(mTheta < 0)
        mTheta += 360;
    if(hTheta<0)
        hTheta += 360;

    if(fanFlag == true)
    {
        fTheta += speed;
        if(fTheta > 360)
            fTheta -=360;
    }*/

  /*  if (walkrotate1 == true)
    {
        walk[ws] +=0.5;
        walk3[ws] +=0.021705;
        if(walk[ws]>=20.0)
        {
         ws+=1;
       walkrotate1 = false;
       walkrotate2 = true;
        }
        //Sleep(1000);
    }
    if (walkrotate2 == true)
    {
        walk4[ws] +=0.5;
        walk2[ws] +=0.021705;
        if(walk4[ws] >=20.0)
        {
         ws+=1;
       walkrotate1 = true;
       walkrotate2 = false;
        }
        //Sleep(1000);
    }*/
    if (welRotate == true)
    {
        p+=0.02;
        k=p;
        faTheta+=2;
        if(k>=7)
        {
            k=0;
            p=0;
        }
        //Sleep(1000);
    }

    if (bRotate == true)
    {
        fTheta+= 0.2;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }

    if (uRotate == true)
    {
        alpha += 0.2;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }
        //Light1
    if(ambL1 == true)
        {
            glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient1);
        }
    else if(ambL1 == false) {
            glLightfv( GL_LIGHT0, GL_AMBIENT, no_light);
    }
    if(diffL1 == true) {
            glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse1);
    }
    else if(diffL1 == false) {
            glLightfv( GL_LIGHT0, GL_DIFFUSE, no_light);
    }
    if(specL1 == true) {
            glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
    }
    else if(specL1 == false) {
            glLightfv( GL_LIGHT0, GL_SPECULAR, no_light);
    }

    //Light2
    if(ambL2 == true) {
            glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient2);
    }
    else if(ambL2 == false) {
            glLightfv( GL_LIGHT1, GL_AMBIENT, no_light);
    }
    if(diffL2 == true) {
            glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuse2);
    }
    else if(diffL2 == false) {
            glLightfv( GL_LIGHT1, GL_DIFFUSE, no_light);
    }
    if(specL2 == true) {
            glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular);
    }
    else if(specL2 == false) {
            glLightfv( GL_LIGHT1, GL_SPECULAR, no_light);
    }

    //Light3
    if(ambL3 == true) {
            glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient3);
    }
    else if(ambL3 == false) {
            glLightfv( GL_LIGHT2, GL_AMBIENT, no_light);
    }
    if(diffL3 == true) {
            glLightfv( GL_LIGHT2, GL_DIFFUSE, light_diffuse3);
    }
    else if(diffL3 == false) {
            glLightfv( GL_LIGHT2, GL_DIFFUSE, no_light);
    }
    if(specL3 == true) {
            glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular);
    }
    else if(specL3 == false) {
            glLightfv( GL_LIGHT2, GL_SPECULAR, no_light);
    }
    //light4
    if(ambL3 == true) {
            glLightfv( GL_LIGHT3, GL_AMBIENT, light_ambient4);
    }
    else if(ambL3 == false) {
            glLightfv( GL_LIGHT3, GL_AMBIENT, no_light);
    }
    if(diffL3 == true) {
            glLightfv( GL_LIGHT3, GL_DIFFUSE, light_diffuse4);
    }
    else if(diffL3 == false) {
            glLightfv( GL_LIGHT3, GL_DIFFUSE, no_light);
    }
    if(specL3 == true) {
            glLightfv( GL_LIGHT3, GL_SPECULAR, light_specular);
    }
    else if(specL3 == false) {
            glLightfv( GL_LIGHT3, GL_SPECULAR, no_light);
    }
    glutPostRedisplay();

}
static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
//const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */
void LoadTexture(const char*filename,int index)
{

    glGenTextures(1, &ID[index]);
    glBindTexture(GL_TEXTURE_2D, ID[index]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID[index]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

glutInitWindowPosition(100,100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("Texture-Demo");

    //LoadTexture("C:\\field.bmp");

    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    printf("1=enable light 1\n");
    printf("1=click 1 again to disable light 1\n");
    printf("2=enable light 2\n");
    printf("3=enable light on moon\n");
    printf("u= go left \n");
    printf("U= ZOOM in \n");
    printf("K= ZOOM out \n");
    printf("u= go right \n");
    printf("l= click l many times to run the train \n");
    printf("+= click + to run the people\n");
    printf("-= click - to open the door\n");
    printf("i= click i to go initial position\n");
    printf("b= click b for top view\n");
    printf("f/F= to move camera left or right\n");
    printf("g/G= to move camera up or down\n");
    printf("h/H= to move camera near or far\n");
    //glClearColor(0,0,0,1);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\brick.bmp",1); //C:\Users\ASUS !\Documents\glut_project\Arnab\Texture
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\design_tiles_2.bmp",2);
   //C:\Users\ASUS !\Documents\glut_project\Arnab\project1
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\wooden_5.bmp",3);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\grey_wall_4",4);

    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\grass_texture_03.bmp",5);

    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\white_tile_1.bmp",6);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\red_tin.bmp",7);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\door_2.bmp",8);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\door_2_r.bmp",9);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\window_1_l.bmp",10);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\green_dustbin_2.bmp",11);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\bkash_2.bmp",12);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\bkash_4.bmp",13);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\brac_atm.bmp",14);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\atm_machine_2.bmp",15);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\train_time_1.bmp",16);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\train_banner_3.bmp",17);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\leaf_1.bmp",18);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\ka.bmp",19);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\kha.bmp",20);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\ga.bmp",21);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\gha.bmp",22);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\uma.bmp",23);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\ca.bmp",24);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\cha.bmp",25);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\ja.bmp",26);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\jha.bmp",27);

    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\w_3.bmp",28);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\E.bmp",29);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\L.bmp",30);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\C.bmp",31);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\O.bmp",32);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\M.bmp",33);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\E.bmp",34);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\tree_bakol_2.bmp",35);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\sky_2.bmp",36);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\road_3.bmp",37);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\luggage_1.bmp",38);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\road_4.bmp",39);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\BR.bmp",40);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\ticket_2.bmp",41);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\oni.bmp",42);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\twi.bmp",43);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\gazi_tank_1.bmp",44);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\leaf_2.bmp",45);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\night_sky_1.bmp",46);
    LoadTexture("C:\\Users\\user\\Documents\\CGIPL\\railway_station\\tex\\moon_1.bmp",47);


    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    //glEnable(GL_LIGHTING);

//    ligh();
    printf("%f",fTheta);
      if(sound==1){
     //PlaySound("C:\\Users\\ASUS !\\Downloads\\train_short.wav", 0, SND_LOOP|SND_ASYNC);
      }

    glutMainLoop();
    return EXIT_SUCCESS;
}
