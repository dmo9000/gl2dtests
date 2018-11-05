#include <stdio.h>
//#include <glut.h>
//#include "chip8.h"
#include <GL/glut.h>

// Display size
#define SCREEN_WIDTH 		640	
#define SCREEN_HEIGHT 	480	

//chip8 myChip8;
int modifier = 1;

// Window size
//int display_width = SCREEN_WIDTH * modifier;
//int display_height = SCREEN_HEIGHT * modifier;
int display_width = 0;
int display_height = 0;

void display();
void reshape_window(GLsizei w, GLsizei h);

int vxoffset = 0;

// Use new drawing method
//typedef unsigned __int8 u8;
typedef unsigned char u8;
u8 screenData[SCREEN_HEIGHT][SCREEN_WIDTH][3];
void setupTexture();
char *p = "HELLO WORLD\0";

int main(int argc, char **argv)
{
    /*
    if(argc < 2)
    {
        printf("Usage: myChip8.exe chip8application\n\n");
        return 1;
    }
    */
    display_width = SCREEN_WIDTH * modifier;
    display_height = SCREEN_HEIGHT * modifier;


    // Load game
//    if(!myChip8.loadApplication(argv[1]))
//        return 1;

    // Setup OpenGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowSize(display_width, display_height);
    glutInitWindowPosition(320, 320);
    glutCreateWindow("myChip8 by Laurence Muller");

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape_window);

    setupTexture();

    glutMainLoop();

    return 0;
}

void setTexturePixel(int x, int y, u8 r, u8 g, u8 b)
{

		screenData[y][x][0] = r;
		screenData[y][x][1] = g;
		screenData[y][x][2] = b;

}

// Setup Texture
void setupTexture()
{


    // Clear screen
    for(int y = 0; y < SCREEN_HEIGHT; ++y)	{
        for(int x = 0; x < SCREEN_WIDTH; ++x) {
            if (y % 2) {
                screenData[y][x][0] = 255;
                screenData[y][x][1] = 0;
                screenData[y][x][2] = 0;
            } else {
                screenData[y][x][0] = 0;
                screenData[y][x][1] = 255;
                screenData[y][x][2] = 0;
            }
        }
    }

    // Create a texture
    glTexImage2D(GL_TEXTURE_2D, 0, 3, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)screenData);

    // Set up the texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    // Enable textures
    glEnable(GL_TEXTURE_2D);
}

//void updateTexture(const chip8& c8)
//
void output_character(char c)
{
	int i = 0, j = 0;
	static int cx=0, cy=0;
	

	for (j = (cy * 16); j < (cy*16) + 16; j++) {
		for (i = (cx * 8); i < (cx*8) + 8; i++) {
				setTexturePixel(i, j, 0, 0, 0);
				}
			}

	cx++;
	if (cx == 80)	{
		cx = 0;
		cy ++;
		}
	

	printf("OUTPUT=[%c][%u], cx=%d, cy=%d\r\n", p[0], p[0], cx, cy);

}

void updateTexture()
{

		while (p[0] != 0) {
			//	printf("OUTPUT=[%c][%u]\r\n", p[0], p[0]);
				output_character(p[0]);	
				p++;
				}

    // Update pixels
//    for(int y = 0; y < 32; ++y)
//        for(int x = 0; x < 64; ++x)
//           if(c8.gfx[(y * 64) + x] == 0)
    //              screenData[y][x][0] = screenData[y][x][1] = screenData[y][x][2] = 0;	// Disabled
    //         else
    //            screenData[y][x][0] = screenData[y][x][1] = screenData[y][x][2] = 255;  // Enabled

    // Update Texture
    glTexSubImage2D(GL_TEXTURE_2D, 0,0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)screenData);

    glBegin( GL_QUADS );
    glTexCoord2d(0.0, 0.0);
    glVertex2d(0.0,			  0.0);
    glTexCoord2d(1.0, 0.0);
    glVertex2d(display_width, 0.0);
    glTexCoord2d(1.0, 1.0);
    glVertex2d(display_width, display_height);
    glTexCoord2d(0.0, 1.0);
    glVertex2d(0.0,			  display_height);
    glEnd();
}

void display()
{
//		printf("display()\n");
//   myChip8.emulateCycle();

//    if(myChip8.drawFlag)
//    {
    // Clear framebuffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw pixels to texture
    //updateTexture(myChip8);
    updateTexture();
    // Swap buffers!
    glutSwapBuffers();

    // Processed frame
//        myChip8.drawFlag = false;
// 	}
}

void reshape_window(GLsizei w, GLsizei h)
{
		printf("reshape_window()\n");
    glClearColor(0.0f, 0.0f, 0.5f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, h, 0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, w, h);

    // Resize quad
    display_width = w;
    display_height = h;
}
