#include <stdio.h>
#include <stdlib.h>
#include<GL/glut.h>
#include<time.h>
#include<string.h>
#define SIZE 19

int adj[SIZE][SIZE];
float cod[SIZE][2];//stores co-ordinates of the points
int src,dst;//Source node and destination node
int p[SIZE];
//static int flag=0;

int id;

void screen3();
void myMenu(int val)
{
    if(val==1) exit(0);
    if(val==2) id=2;
    if(val==3) id=3;
    screen3();
}
//The following function is used to give a delay
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

//The following function is used to display TEXT on the screen
//Arguments are "STRING",R,G,B,X,Y,ScaleX,ScaleY,Width
void typeText(char *string,float x,float y,float z,float w,float h,float sx,float sy,float width){
    int i;
	glColor3f(x, y, z);
	//glLoadIdentity();
	glPushMatrix();
    glTranslatef(w,h,0);
	glScalef(sx,sy,1);
	glLineWidth(width);
    for (i = 0; string[i]; i++)
	{
             glutStrokeCharacter(GLUT_STROKE_ROMAN,string[i]);
	}
	//glutSwapBuffers();
	glPopMatrix();
	glFlush();
	//glLoadIdentity();//
}

void typeText2(char *string,float x,float y,float z,float w,float h,float sx,float sy,float width){
    int i;
	glColor3f(x, y, z);
	//glLoadIdentity();
	glPushMatrix();
    glTranslatef(w,h,0);
	glScalef(sx,sy,1);
	glLineWidth(width);
    for (i = 0; string[i]; i++)
	{
             glutStrokeCharacter(GLUT_STROKE_ROMAN,string[i]);
	}
	//glutSwapBuffers();
	glPopMatrix();
	glFlush();
	//glLoadIdentity();//
}

//The following function is used to display a point on the screen
//Arguments X,Y,SIZE
void plotPoint(float x,float y,int s){
    //glPushMatrix();
    glPointSize(s);
    glBegin(GL_POINTS);
    glColor3f(1,0,1);
    glPointSize(s);
    glVertex3f(x,y,0);
    glEnd();
    glPointSize(1);

}

void rec(int x1,int y,int x2,int y2){
    glColor3f(1,0,0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(x1,y,0);
    glVertex3f(x2,y,0);
    glVertex3f(x2,y2,0);
    glVertex3f(x1,y2,0);
    glEnd();

}

//The following function stores the co-ordinates of each node in 'cod' 2D matrix
void mark_points()
{
    int i;
 cod[0][0]=0.050;
    cod[0][1]=0.050;
    cod[1][0]=0.050;
    cod[1][1]=0.650;
    cod[2][0]=0.650;
    cod[2][1]=0.650;
    cod[3][0]=0.650;
    cod[3][1]=0.050;
    cod[4][0]=0.650;
    cod[4][1]=0.550;
    cod[5][0]=0.350;
    cod[5][1]=0.550;
    cod[6][0]=0.200;
    cod[6][1]=0.650;
    cod[7][0]=0.300;
    cod[7][1]=0.500;
    cod[8][0]=0.300;
    cod[8][1]=0.250;
    cod[9][0]=0.650;
    cod[9][1]=0.250;
    cod[10][0]=0.350;
    cod[10][1]=0.250;
    cod[11][0]=0.350;
    cod[11][1]=0.050;
    cod[12][0]=0.550;
    cod[12][1]=0.150;
    cod[13][0]=0.350;
    cod[13][1]=0.150;
    cod[14][0]=0.100;
    cod[14][1]=0.250;
    cod[15][0]=0.150;
    cod[15][1]=0.500;
    cod[16][0]=0.350;
    cod[16][1]=0.500;
    cod[17][0]=0.375;
    cod[17][1]=0.575;
    cod[18][0]=0.9;
    cod[18][1]=0.9;
    for(i=0;i<SIZE;i++)
    {
        plotPoint(cod[i][0],cod[i][1],6);
        char str[12];
        sprintf(str, "%d",i);//convert integer to string
        typeText2(str,1,0,0,cod[i][0],cod[i][1],0.0002,0.0002,0.003);//to show the number along with the point
    }



}

//The following function is use to draw the initial roads
void drawRoad(int adj[SIZE][SIZE])
{
    int i,j;
    glColor3f(0.96,0.96,0.8);
    glLineWidth(5);
    for(i=0;i<SIZE;i++)
        for(j=0;j<SIZE;j++)
        {
            if((adj[i][j]!=999)&&(adj[i][j]!=0))
            {
                printf("%d %d %d \n ",i,j,adj[i][j]);
                glBegin(GL_LINE_STRIP);
                glVertex3f(cod[i][0],cod[i][1],0);
                glVertex3f(cod[j][0],cod[j][1],0);
                glFlush();
                glEnd();
            }
        }

    /*glColor3f(1,0,0);
    glBegin(GL_POLYGON);
    glVertex3f(70,70,0);
    glVertex3f(580,70,0);
    glVertex3f(300,50,0);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(70,70,300);
    glVertex3f(580,70,300);
    glVertex3f(300,50,300);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(70,70,0);
    glVertex3f(70,70,300);
    glVertex3f(580,70,0);
    glVertex3f(580,70,300);
    glVertex3f(300,50,0);
    glVertex3f(300,50,300);
    glEnd();*/

    glFlush();
    return;
}

//The following function is used to find the path from source to destination and also draw the path
void path(int k) {
	if(p[k] == -1 ) {
		return;
	}
	path(p[k]);

	printf("%d ",k);
    glVertex2f(cod[k][0],cod[k][1]);
    glEnd();
    glFinish();
    glBegin(GL_LINES);
    delay(1000000);
    glVertex2f(cod[k][0],cod[k][1]);
    glFlush();
}

//Dijkstra implementation
void dijkstra(int adj[SIZE][SIZE],int n,int src) {
	int visit[SIZE];
	int d[SIZE];
	int i,j,k;
	int min=0,w=0;
	for(i=0;i<n;i++) {
		visit[i]=0;
		d[i]= 999;
		p[i]= -1;
	}
	visit[src]=1;
	d[src]=0;
	p[src]=-1;
	for(i=0;i<n;i++) {
		if(adj[src][i] != 999 && adj[src][i] != 0) {
			d[i]=adj[src][i];
			p[i]=src;
		}

	}
	for(i=1;i<n;i++) {
		min = 999;
		for(j=0;j<n;j++) {
			if(visit[j]==0 && d[j] < min) {
				min =d[j];
				w=j;
			}
		}
		visit[w]=1;
		for(k=0;k<n;k++) {
			if(visit[k]==0 && adj[w][k] != 999 && adj[w][k] != 0) {
				if(d[k] > (d[w] + adj[w][k])) {
					d[k]= d[w] + adj[w][k];
					p[k]=w;
				}
			}
		}
	}
        delay(1000000);
		printf("path taken is");
		printf("%d ",src);
		//draw triangle
		/*glColor3f(1, 1, 1);
		glPointSize(50);
        glBegin(GL_POINT);
        glVertex3f(cod[src][0],cod[src][1],0);
        glEnd();*/
        //
		glPushMatrix();
        glLineWidth(20);
        glColor3f(0,0,1);
		glBegin(GL_LINES);
		glVertex2f(cod[src][0],cod[src][1]);
		glFlush();
		delay(1000000);
        path(dst);
		glEnd();
		glPopMatrix();
        printf("\n");
        //screen3();////////////////
}



void drawbuild(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4)
{
    //glColor3f(1,1,1);
    glColor3f(0.88,0.93,0.93);
    glBegin(GL_POLYGON);
    glVertex3f(x1,y1,0);
    glVertex3f(x2,y2,0);
    glVertex3f(x3,y3,0);
    glVertex3f(x4,y4,0);
    glEnd();
}
//The following function makes the adjacency matrix and calls draw road and dijkstra
void callDijkstra(){


    //int i,j;
	/*int adj[SIZE][SIZE]={
				{0,6,999,4,999,999,999,999,999,999},
				{6,0,3,999,999,999,999,999,999,999},
				{999,3,0,6,999,999,999,999,999,999},
				{4,999,6,0,999,6,7,999,999,999},
                {999,999,999,999,0,8,999,999,999,999,999},
                {999,999,999,6,8,0,10,11,999,999},
                {999,999,999,7,999,10,0,999,999,9},
                {999,999,999,999,999,11,999,0,12,999},
                {999,999,999,999,999,999,999,12,0,999},
                {999,999,999,999,999,999,9,999,999,0},
                };*/
    //int adj[SIZE][SIZE];

    int i,j;
    for(i=0;i<SIZE;i++)
    {
        for(j=0;j<SIZE;j++)
        {
            if(i==j)
                adj[i][j]=0;
            else
                adj[i][j]=999;
        }
    }
    adj[0][1]=adj[1][0]=20;
    adj[0][11]=adj[11][0]=10;
    adj[1][2]=adj[2][1]=20;
    adj[1][6]=adj[6][1]=6;
    adj[2][3]=adj[3][2]=20;
    adj[2][4]=adj[4][2]=3;
    adj[2][6]=adj[6][2]=14;
    adj[3][4]=adj[4][3]=17;
    adj[3][9]=adj[9][3]=8;
    adj[3][11]=adj[11][3]=10;
    adj[4][5]=adj[5][4]=10;
    adj[4][9]=adj[9][4]=9;
    adj[5][6]=adj[6][5]=5;
    adj[5][7]=adj[7][5]=2;
    adj[7][8]=adj[8][7]=8;
    adj[8][9]=adj[9][8]=12;
    adj[8][10]=adj[10][8]=1;
    adj[9][10]=adj[10][9]=11;
    adj[10][11]=adj[11][10]=8;
    adj[10][13]=adj[13][10]=4;
    adj[11][13]=adj[13][11]=4;
    adj[12][13]=adj[13][12]=7;
    adj[8][14]=adj[14][8]=8;
    adj[7][15]=adj[15][7]=6;
    adj[5][16]=adj[16][5]=1;
    adj[5][17]=adj[17][5]=1;
    adj[2][18]=adj[18][2]=5;
    drawRoad(adj);

drawbuild(0.350,0.300,0.600,0.300,0.600,0.500,0.350,0.500);
    drawbuild(0.100,0.300,0.250,0.300,0.250,0.450,0.100,0.450);
    drawbuild(0.100,0.350,0.150,0.350,0.150,0.550,0.100,0.550);
    drawbuild(0.100,0.550,0.250,0.550,0.250,0.600,0.100,0.600);
    drawbuild(0.060,0.100,0.300,0.100,0.300,0.200,0.060,0.200);
    drawbuild(0.060,0.200,0.100,0.200,0.100,0.250,0.060,0.250);
    drawbuild(0.375,0.575,0.550,0.575,0.550,0.625,0.275,0.625);
    drawbuild(0.100,0.550,0.250,0.550,0.250,0.600,0.100,0.600);
    drawbuild(0.575,0.575,0.600,0.575,0.600,0.625,0.575,0.625);
    drawbuild(0.600,0.600,0.625,0.600,0.625,0.625,0.600,0.625);
    drawbuild(0.550,0.100,0.600,0.100,0.600,0.200,0.550,0.200);
    drawbuild(0.925,0.8,0.990,0.8,0.990,0.990,0.925,0.990);
    drawbuild(0.925,0.910,0.925,0.990,0.810,0.990,0.810,0.910);
    //draw sea and island

    glColor3f(0.6, 0.6, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(0.050,0.660);
    glVertex2f(0.645,0.660);
    glVertex2f(0.8,0.820);
    glVertex2f(0.8,1);
    glVertex2f(0.050,1);
    glEnd();
    glColor3f(0.6, 0.6, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(0.660,0.050);
    glVertex2f(1,0.050);
    glVertex2f(1,0.790);
    glVertex2f(0.8,0.790);
    glVertex2f(0.660,0.640);
    glEnd();

    glFlush();

  /* printf("Enter source\n");
    scanf("%d",&src);
    printf("Enter the destination\n");
    scanf("%d",&dst);

    dijkstra(adj,SIZE,src);*/
}

void entersrc()
{
 printf("Enter source\n");
    scanf("%d",&src);
    printf("Enter the destination\n");
    scanf("%d",&dst);

    dijkstra(adj,SIZE,src);
}

//The following function calls mark_points() to make the initial map and then calls Dijkstra
void screen3(){

   /* glLoadIdentity();
    glClearColor(0.65,0.93,0.31,1);
    glOrtho(0,1,0,1,0,1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);*/
    if(id==2){
        mark_points();
        glFlush();
            callDijkstra();
        glFlush();
    }
    else if(id==3)
    {
        mark_points();
        glFlush();
            callDijkstra();
        glFlush();
        entersrc();
        glFlush();
    }

    printf("bye");
}

void prescreen3()
{
    glLoadIdentity();
    //glClearColor(0.65,0.93,0.31,1);
    glClearColor(0.94,1,1,1);
    glOrtho(0,1,0,1,0,1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    int submenu= glutCreateMenu(myMenu);
    glutAddMenuEntry("Draw map",2);
    glutAddMenuEntry("src and dst",3);
    glutCreateMenu(myMenu);
    glutAddMenuEntry("QUIT",1);
    glutAddSubMenu("options",submenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

//The following function is used to display the WELCOME text
void welcomepg()
{
    glClearColor(0.1,1,1,1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    delay(100000);
    typeText("WELCOME",1,1,0,200,345,0.5,0.5,3);
    delay(3000000);
    glFlush();
    prescreen3();
}

void setpoly(int a)
{
    glColor3f(0,0,1);
    glBegin(GL_POLYGON);
    glVertex3f(300,345,0);
    glVertex3f(a,345,0);
    glVertex3f(a,355,0);
    glVertex3f(300,355,0);
    glEnd();

}

//The following function displays the loading page
void loading()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    typeText("Loading",1, 0, 0,300,355,0.2,0.2,2);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLineWidth(2);
    int i;
    float j=1;
    int a=310;
    for(i=0;i<10;i++)
    {
        glClearColor(j,1,1,1.0);
        j=j-0.1;
        glColor3f(0,0,0);
        glBegin(GL_LINE_LOOP);
        glVertex3f(300,345,0);
        glVertex3f(390,345,0);
        glVertex3f(390,355,0);
        glVertex3f(300,355,0);
        glEnd();
        setpoly(a);
        delay(100000);
        a=a+10;
        glFlush();
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    }
    welcomepg();
}

void keys(unsigned char key,int x,int y){
    if(key ==(char)13){
        loading();
    }

}

//The following function shows the initial page
void screen1()
{
    int len;
    char string[]="NAVIGATION";
    //    rec(1,1,100,100);
        glPushMatrix();
        //glLoadIdentity();
        glTranslatef(270,300,0);
        glScalef(2,2,1);

        glColor3f(0.93, 0.27, 0.21);
        glBegin(GL_POLYGON);
        glVertex3f(30,23,0);
        glVertex3f(40,25,0);
        glVertex3f(45,35,0);
        glEnd();
        glColor3f(0.75, 0.22, 0.17);
        glBegin(GL_POLYGON);
        glVertex3f(45,17,0);
        glVertex3f(40,25,0);
        glVertex3f(45,35,0);
        glEnd();
        //glutSwapBuffers();
        glPopMatrix();
        glFlush();

        //glLoadIdentity();
        len=(int) strlen(string);
        typeText(string,0.99, 0.75, 0.06,175,600,0.5,0.5,5);
        typeText("ENTER TO START",0.97, 0.22, 0.22,175,400,0.3,0.3,3);
        typeText("RAHUL.J 1PE15CS115",0.75, 0.93, 0.96,10,130,0.2,0.2,3);
        typeText("RAKSHIT 1PE15CS119",0.75, 0.93, 0.96,10,80,0.2,0.2,3);
}

void display(){
    //    gluLookAt(0,0,0,0,0,-1,0,0,1);
    gluLookAt(0,0,0,0,0,-1,0,1,0);
    //gluLookAt(2.3,1.3,2.0,350,350,350,0.0,1.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    screen1();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(1024,1000);
	glutCreateWindow("Navigation");
    glutKeyboardFunc(keys);
    glEnable(GL_POINT_SMOOTH);
	glClearColor(0,0.4,0.52,1);
	glOrtho(0,700,0,700,0,700);
	glutDisplayFunc(display);

	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}
