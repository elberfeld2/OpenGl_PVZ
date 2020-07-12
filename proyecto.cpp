#include <stdio.h>
#include<malloc.h>
#include <GL/glut.h>

GLfloat puntosControl[4][4][3];
int muestraPuntos = 0,valorr=1;
float tie=0;
float alpha=0,beta=0;
int x0,y0;
GLfloat c01 [4][4][3] = {
{{3.5, -1.5, 1.0}, 
{3.0, -2.0, 1.6}, 
{1.0, -2.0, 1.6}, 
{0.0, -2.0, 1.0}}, 
		
{{4.0, -1.0, 1.5}, 
{3.0, -1.0, 3.5},  
{1.0, -1.0, 3.5}, 
{0, -1.0, 1.75}}, 
		
{{4.0, 0.0, 0.4}, 
{3.0, 0.0,0},  
{1.0, 0.0, 0},
{0, 0.0, 0.26}}, 
		
{{4.0, 1.2, 1.0}, 
{3.0, 2.0, 1.5}, 
{1.0, 2.0,  1.5},
{0.5, 0, 1.0}}
};	//5	
GLUnurbsObj *Nurb;
GLuint texture_id[20];
int  LoadBMP(char *filename, int tex_name)
{
#define SAIR        {fclose(fp_archivo); return -1;}
#define CTOI(C)     (*(int*)&C)
	
	GLubyte     *image;
	GLubyte     Header[0x54]; 
	GLuint      DataPos, imageSize;
	GLsizei     Width,Height;
	
	int nb = 0;
	
	
	// Abre un archivo y efectua la lectura del encabezado del archivo BMP
	FILE * fp_archivo = fopen(filename,"rb");
	if (!fp_archivo) 
		return -1;
	if (fread(Header,1,0x36,fp_archivo)!=0x36) 
		SAIR;
	if (Header[0]!='B' || Header[1]!='M')   
		SAIR;
	if (CTOI(Header[0x1E])!=0)              
		SAIR;
	if (CTOI(Header[0x1C])!=24)             
		SAIR;
	
	// Recupera los atributos de la altura y ancho de la imagen 
	
	Width   = CTOI(Header[0x12]);
	Height  = CTOI(Header[0x16]);
	( CTOI(Header[0x0A]) == 0 ) ? ( DataPos=0x36 ) : ( DataPos = CTOI(Header[0x0A]) );
	
	imageSize=Width*Height*3;
	
	// Llama a la imagen
	image = (GLubyte *) malloc ( imageSize );
	int retorno;
	retorno = fread(image,1,imageSize,fp_archivo);
	
	if (retorno !=imageSize) 
	{
		free (image);
		SAIR;
	}
	
	// Invierte los valores de R y B
	int t, i;
	
	for ( i = 0; i < imageSize; i += 3 )
	{
		t = image[i];
		image[i] = image[i+2];
		image[i+2] = t;
	} 
	
	// Tratamiento de textura para OpenGL
	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_MODULATE);
	
	glTexEnvf ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
	
	// Manipulacion en memoria de la textura
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	
	fclose (fp_archivo);
	free (image);
	return 1;
}
void textu(){
	
	glEnable(GL_TEXTURE_2D);//
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glGenTextures(20,texture_id);
	glBindTexture(GL_TEXTURE_2D,texture_id[0]);
	LoadBMP("data/verde.bmp",0);
	//glGenTextures(2,&texture_id2);
	glBindTexture(GL_TEXTURE_2D,texture_id[1]);
	LoadBMP("data/suelo.bmp",1);
	glBindTexture(GL_TEXTURE_2D,texture_id[2]);
	LoadBMP("data/NEgro.bmp",2);
	glBindTexture(GL_TEXTURE_2D,texture_id[3]);
	LoadBMP("data/amar.bmp",3);
	glBindTexture(GL_TEXTURE_2D,texture_id[4]);
	LoadBMP("data/cafe.bmp",4);
	glBindTexture(GL_TEXTURE_2D,texture_id[5]);
	LoadBMP("data/pap.bmp",5);
	glBindTexture(GL_TEXTURE_2D,texture_id[6]);
	LoadBMP("data/mor.bmp",6);
	glBindTexture(GL_TEXTURE_2D,texture_id[7]);
	LoadBMP("data/bla.bmp",7);
	glBindTexture(GL_TEXTURE_2D,texture_id[8]);
	LoadBMP("data/put.bmp",8);
	glBindTexture(GL_TEXTURE_2D,texture_id[9]);
	LoadBMP("data/ampu.bmp",9);
	glBindTexture(GL_TEXTURE_2D,texture_id[10]);
	LoadBMP("data/kkk.bmp",10);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	
}


void cubo(void)
{
	
	GLfloat vertices1[]={-0.5,-0.5,-0.5,-0.5,0.5,-0.5,-0.5,0.5,0.5,-0.5,-0.5,0.5};
	GLfloat vertices2[]={-0.5,-0.5,0.5,-0.5,0.5,0.5,0.5,0.5,0.5,0.5,-0.5,0.5};
	GLfloat vertices3[]={0.5,-0.5,-0.5,0.5,-0.5,0.5,0.5,0.5,0.5,0.5,0.5,-0.5};
	GLfloat vertices4[]={-0.5,-0.5,-0.5,0.5,-0.5,-0.5,0.5,0.5,-0.5,-0.5,0.5,-0.5};
	GLfloat vertices5[]={-0.5,0.5,-0.5,0.5,0.5,-0.5,0.5,0.5,0.5,-0.5,0.5,0.5};
	GLfloat vertices6[]={-0.5,-0.5,-0.5,-0.5,-0.5,0.5,0.5,-0.5,0.5,0.5,-0.5,-0.5};
	glEnableClientState (GL_VERTEX_ARRAY);
	//glColor3ub(18, 128, 90);
	glVertexPointer(3,GL_FLOAT,0,vertices1);
	glDrawArrays(GL_QUADS,0,4);
	//glColor3ub
	
	(69, 96, 100);
	glVertexPointer(3,GL_FLOAT,0,vertices2);
	glDrawArrays(GL_QUADS,0,4);
	//glColor3ub(128, 85, 136);
	glVertexPointer(3,GL_FLOAT,0,vertices3);
	glDrawArrays(GL_QUADS,0,4);
	//glColor3ub(0, 128, 128);
	glVertexPointer(3,GL_FLOAT,0,vertices4);
	glDrawArrays(GL_QUADS,0,4);
	//glColor3ub(128, 128, 0);
	glVertexPointer(3,GL_FLOAT,0,vertices5);
	glDrawArrays(GL_QUADS,0,4);
	//glColor3ub(128, 0, 128);
	glVertexPointer(3,GL_FLOAT,0,vertices6);
	glDrawArrays(GL_QUADS,0,4);
	glDisableClientState (GL_VERTEX_ARRAY);
}


void init_superficie(void)
{
	int u, v;
	for (u = 0; u < 4; u++) {
		for (v = 0; v < 4; v++) {
			puntosControl[u][v][0] = 2.0*((GLfloat)u - 1.5);
			puntosControl[u][v][1] = 2.0*((GLfloat)v - 1.5);
			
			if ( (u == 1 || u == 2) && (v == 1 || v == 2))
				puntosControl[u][v][2] = 7.0;
			else
				puntosControl[u][v][2] = -3.0;
		}
	}				
}				

void init(void)
{
	GLfloat mat_difusa[] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat mat_especular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_brillo[] = { 100.0 };
	
	glClearColor (0.0, 0.0, 1.0, 1.0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_difusa);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_especular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_brillo);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	
	init_superficie();
	
	Nurb = gluNewNurbsRenderer();
	gluNurbsProperty(Nurb, GLU_SAMPLING_TOLERANCE, 25.0);
	gluNurbsProperty(Nurb, GLU_DISPLAY_MODE, GLU_FILL);
	textu();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef (0.0, 0.0, -5.0);
}

void hoja(){
	GLfloat nudos[8] = {0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0};
	int i, j;
	gluBeginSurface(Nurb);
	gluNurbsSurface(Nurb, 
					8, nudos,
					8, nudos,
					4 * 3,
					3,
					&c01[0][0][0], 
					4, 4,
					GL_MAP2_VERTEX_3);
	gluEndSurface(Nurb);
	
	
}
void super(){
	for(int a=0;a<4;a++){
	glPushMatrix();
	glRotatef(90*a,0,1,0);
	glPushMatrix();
	glTranslatef(0,-0.6,0);
	glScalef (0.07, 0.05, 0.05);
	glRotatef(-90,1,0,0);
	hoja();
	glPopMatrix();
	glPopMatrix();
	
	}
}
void guisante(){
	
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,texture_id[2]);
	glTranslatef(-0.06,0.11,0.1);
	glScalef(0.1,0.2,0.1);
	glutSolidSphere (0.15,30,20);
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,texture_id[2]);
	glTranslatef(-0.06,0.11,-0.1);
	glScalef(0.1,0.2,0.1);
	glutSolidSphere (0.15,30,20);
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,texture_id[2]);
	glTranslatef(-0.2,0.008,0);
	glScalef(0.6,0.6,0.6);
	glutSolidSphere (0.15,30,20);
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,texture_id[1]);
	glScalef(1.2,1,1);
	glutSolidSphere (0.15,30,20);
	glPopMatrix();
	for(int a=0;a<10;a++){
		glPushMatrix();
		glTranslatef(-0.2+a*0.01,0,0);
		glScalef(0.5,0.8-0.02*a,0.8);
		glutSolidSphere (0.15,30,20);
		glPopMatrix();
	}
	glPushMatrix();
	glTranslatef(0,-0.3,0);
	glScalef(0.2,2,0.2);
	glutSolidSphere (0.15,30,20);
	glPopMatrix();
	if(tie==100000)tie=0;
	glPushMatrix();
	float aa=((int)tie%6);
	if(aa>5){tie=0;}
	glTranslatef(-0.4-aa,0.02,0);
	glScalef(0.6,0.6,0.6);
	glutSolidSphere (0.15,30,20);
	glPopMatrix();
	glPushMatrix();
	float aad=(((int)tie+3)%6);
	if(aad>5){tie=0;}
	glTranslatef(-0.4-aad,0.02,0);
	glScalef(0.6,0.6,0.6);
	glutSolidSphere (0.15,30,20);
	glPopMatrix();
	
	super();
	
	
	
}
void esfera1 ( double radio,double longitud,double latitud  )
{   
	GLUquadricObj*  q = gluNewQuadric ( );
	gluQuadricDrawStyle ( q, GLU_FILL   );
	gluQuadricNormals   ( q, GLU_SMOOTH );
	gluQuadricTexture   ( q, GL_TRUE    );
	gluSphere ( q, radio, longitud, latitud );
	gluDeleteQuadric ( q );
}
void cilindro(){ 

	glPushMatrix();
	
	glRotatef(270,1,0,0);
	glScalef(0.1,0.1,0.1);
	GLUquadricObj*  q = gluNewQuadric ( );
	gluQuadricDrawStyle ( q, GLU_FILL   );
	gluQuadricNormals   ( q, GLU_SMOOTH );
	gluQuadricTexture   ( q, GL_TRUE    );
	gluCylinder(q,10,10,15,20,20); 
	gluDeleteQuadric ( q );
	glPopMatrix();
}
void hongomor(){
	
	glBindTexture(GL_TEXTURE_2D,texture_id[6]);
	
	glPushMatrix();	
	glTranslatef(0,0.7,0);
	glScalef(1,0.5,1);    esfera1(0.5,30,20);
	glPopMatrix();
	
	glBindTexture(GL_TEXTURE_2D,texture_id[8]);
	for(int a=0;a<5;a++){
	glPushMatrix();	
	glTranslatef(0,0.8,0.5-(float)a*0.04);
	glScalef(0.15,0.15-(float)a*0.02,0.1);
	esfera1(0.5,30,20);
	glPopMatrix();}
	glBindTexture(GL_TEXTURE_2D,texture_id[7]);
	glPushMatrix();	
	glScalef(0.25,0.4,0.25);
	cilindro();
	glPopMatrix();
	
}

void hongo(){
	
	glBindTexture(GL_TEXTURE_2D,texture_id[9]);
	
	glPushMatrix();	
	glTranslatef(0,0.7,0);
	glScalef(1,0.5,1);
	esfera1(0.5,30,20);
	glPopMatrix();
	
	glBindTexture(GL_TEXTURE_2D,texture_id[7]);
	glPushMatrix();	
	glScalef(0.25,0.4,0.25);
	cilindro();
	glPopMatrix();
	
}


void papa(){
	for(int a=0;a<4;a++){
	glBindTexture(GL_TEXTURE_2D,texture_id[5]);
	glPushMatrix();
	glTranslatef(0,0-a*0.005,0-a*0.018);
	glScalef(1.3,2-a*0.1,1);
	esfera1 (0.15,30,20);
	glPopMatrix();	
}
}
void cubqqo(void)
{
	
	GLfloat vertices1[]={-0.5,-0.5,-0.5,-0.5,0.5,-0.5,-0.5,0.5,0.5,-0.5,-0.5,0.5};
	GLfloat vertices2[]={-0.5,-0.5,0.5,-0.5,0.5,0.5,0.5,0.5,0.5,0.5,-0.5,0.5};
	GLfloat vertices3[]={0.5,-0.5,-0.5,0.5,-0.5,0.5,0.5,0.5,0.5,0.5,0.5,-0.5};
	GLfloat vertices4[]={-0.5,-0.5,-0.5,0.5,-0.5,-0.5,0.5,0.5,-0.5,-0.5,0.5,-0.5};
	GLfloat vertices5[]={-0.5,0.5,-0.5,0.5,0.5,-0.5,0.5,0.5,0.5,-0.5,0.5,0.5};
	GLfloat vertices6[]={-0.5,-0.5,-0.5,-0.5,-0.5,0.5,0.5,-0.5,0.5,0.5,-0.5,-0.5};
	glEnableClientState (GL_VERTEX_ARRAY);
	//glColor3ub(18, 128, 90);
	glVertexPointer(3,GL_FLOAT,0,vertices1);
	glDrawArrays(GL_QUADS,0,4);
	//glColor3ub(69, 96, 100);
	glVertexPointer(3,GL_FLOAT,0,vertices2);
	glDrawArrays(GL_QUADS,0,4);
	//glColor3ub(128, 85, 136);
	glVertexPointer(3,GL_FLOAT,0,vertices3);
	glDrawArrays(GL_QUADS,0,4);
	//glColor3ub(0, 128, 128);
	glVertexPointer(3,GL_FLOAT,0,vertices4);
	glDrawArrays(GL_QUADS,0,4);
	//glColor3ub(128, 128, 0);
	glVertexPointer(3,GL_FLOAT,0,vertices5);
	glDrawArrays(GL_QUADS,0,4);
	//glColor3ub(128, 0, 128);
	glVertexPointer(3,GL_FLOAT,0,vertices6);
	glDrawArrays(GL_QUADS,0,4);
	glDisableClientState (GL_VERTEX_ARRAY);
}

void girasol(){
	glBindTexture(GL_TEXTURE_2D,texture_id[1]);
	
	super();
	glPushMatrix(); 
	glTranslatef(0,-0.3,0);
	glScalef(0.2,2,0.2);
	glutSolidSphere (0.15,30,20);
	glPopMatrix();
	glTranslatef(0,0.15,0);
	glPushMatrix();
	glPushMatrix();	
	glBindTexture(GL_TEXTURE_2D,texture_id[4]);
	glScalef(1.5,1.3,0.2);
	esfera1(0.15,30,20);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D,texture_id[3]);
	for(int a=0;a<24;a++){
	glPushMatrix();
	glRotatef(a*15,0,0,1);
	glScalef(0.4,2,0.1);
	glutSolidSphere (0.15,30,20);
	glPopMatrix();
	}
	glPopMatrix();
}
int rot=0;
void display(void)
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();
	
	
	glBindTexture(GL_TEXTURE_2D,texture_id[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0,1);
	glVertex3f(5.0f, -1.5f,5.0f);
	glTexCoord2f(1,1);
	glVertex3f(5.0f, -1.5f, -15.0f);
	glTexCoord2f(5,0);
	glVertex3f(-5.0f,-1.5f,-15.0f);
	glTexCoord2f(0,0);
	glVertex3f(-5.0f,-1.5f,5.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,texture_id[10]);
	glBegin(GL_QUADS);
	glTexCoord2f(1,1);
	glVertex3f(4.2f, 3.2f,-2.3f);
	glTexCoord2f(1,0);
	glVertex3f(4.2f, -1.8f, -2.3f);
	glTexCoord2f(0,0);
	glVertex3f(-4.2f,-1.8f,-2.3f);
	glTexCoord2f(0,1);
	glVertex3f(-4.2f,3.2f,-2.3f);
	glEnd();
	
	//glRotatef(alpha,1.0f, 0.0f, 0.0f);
	glRotatef(beta, 0.0f, 1.0f, 0.0f);
	glPushMatrix();	
	//glRotatef(rot, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D,texture_id[10]);
	glTranslatef(0,-2,0);
	
	glScalef(3,3,3);
	//cilindro();
	glPopMatrix();	
	glScalef(1.6,1.6,1.6);
	glTranslatef(0,-0.8,0);
	glBindTexture(GL_TEXTURE_2D,texture_id[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0,1);
	glVertex3f(1.0f, 0.0f,1.0f);
	glTexCoord2f(1,1);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glTexCoord2f(1,0);
	glVertex3f(-1.0f,0.0f,-1.0f);
	glTexCoord2f(0,0);
	glVertex3f(-1.0f,0.0f,1.0f);
	glEnd();
	for(int a=0;a<5;a++){
	glPushMatrix();
	glTranslatef(-0.8+a*0.4,0.2,-0.9);
	glScalef(0.3,0.3,0.3);
	girasol();
	glPopMatrix();
	}
	for(int a=0;a<5;a++){
		glPushMatrix();
		glTranslatef(-0.8+a*0.4,0.2,-0.68);
		glScalef(0.3,0.3,0.3);
		glPushMatrix();
		glRotatef(90,0,1,0);
		guisante();
		glPopMatrix();
		glPopMatrix();
	}
	for(int a=0;a<5;a++){
		glPushMatrix();
		glTranslatef(-0.8+a*0.4,0,-0.4);
		glScalef(0.15,0.15,0.15);
		hongo();
		glPopMatrix();
	}
	for(int a=0;a<5;a++){
		glPushMatrix();
		glTranslatef(-0.8+a*0.4,0,0.25);
		glScalef(0.25,0.25,0.25);
		hongomor();
		glPopMatrix();
	}
	for(int a=0;a<5;a++){
		glPushMatrix();
		glTranslatef(-0.8+a*0.4,0.12,0.5);
		glScalef(0.4,0.4,0.4);
		papa();
		glPopMatrix();
	}
    glPopMatrix();
	
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective (45.0, (GLdouble)w/(GLdouble)h, 3.0, 8.0);
	
	glMatrixMode(GL_MODELVIEW);
}

void
menu(int valor)
{
	switch (valor) {
	case 0:
		valorr=1;
		break;
		
	case 1:
		
        
		valorr=2;
	break;
	}
	glutPostRedisplay();
}

int down = 0, lastx;
void onMouse(int button, int state, int x, int y) 
{
	if ( (button == GLUT_LEFT_BUTTON) & (state == GLUT_DOWN) ) 
	{
		x0 = x; y0 = y;
	}
}

void onMotion(int x, int y) 
{
	alpha = (alpha + (y - y0));
	beta = (beta + (x - x0));
	x0 = x; y0 = y;
	glutPostRedisplay();
}


void TimerFunction(int a)
{
	if(valorr==1){tie++;}
	
	glutPostRedisplay();
	glutTimerFunc(630, TimerFunction, 1);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (800, 600);
	glutInitWindowPosition (100, -1500);
	glutCreateWindow("Plantas contra zombies");
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutCreateMenu(menu);
	glutAddMenuEntry("Parar", 1);
	glutAddMenuEntry("Comenzar", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	glutMouseFunc(onMouse);
	glutMotionFunc(onMotion);
	glutTimerFunc(630, TimerFunction, 1);
	glutMainLoop();
	return 0;             
}

