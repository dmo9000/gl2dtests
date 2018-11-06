#include <stdio.h>
//#include <glut.h>
//#include "chip8.h"
#include <GL/glut.h>
//#include "font8x8.h"
#include "rawfont.h"
#include "ansicanvas.h"

// Display size
#define SCREEN_WIDTH 		640
#define SCREEN_HEIGHT 	384	

//chip8 myChip8;
int modifier = 2;

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
char *p = "HELLO WORLD THIS IS YOUR CAPTAIN SPEAKING, PLEASE STANDBY";
BitmapFont *myfont;

int gfx_opengl_drawglyph(BitmapFont *font, uint16_t px, uint16_t py, uint8_t glyph, uint8_t fg, uint8_t bg, uint8_t attr)
{

    RGBColour *fgc;
    RGBColour *bgc;
    uint8_t rx = 0;
    uint8_t h = 0;

//    printf("gfx_opengl_drawglyph(%u, %u, %u, %u, '%c', fg=%u, bg=%u)\n", px, py, font->header.px, font->header.py, glyph, fg, bg);

    if (attr & ATTRIB_REVERSE) {
        bgc = canvas_displaycolour(fg + ((attr & ATTRIB_BOLD ? 8 : 0)));
        fgc = canvas_displaycolour(bg);
    } else {
        fgc = canvas_displaycolour(fg + ((attr & ATTRIB_BOLD ? 8 : 0)));
        bgc = canvas_displaycolour(bg);
    }

    for (uint8_t ii = 0; ii < font->header.py; ii++) {
        h = 0;
        for (uint8_t jj = 128; jj >0; jj = jj >> 1) {
            //printf("%u -> %u, ", r, jj);
            rx = font->fontdata[(glyph*font->header.py) + ii];

            if (rx & jj) {
//										setTexturePixel((px*8) + h, (py*16)+(ii*2), fgc->r, fgc->g, fgc->b);
//										setTexturePixel((px*8) + h, (py*16)+(ii*2)+1, fgc->r, fgc->g, fgc->b);
                setTexturePixel((px*8) + h, (py*16)+(ii*2), 255, 255, 255);
                setTexturePixel((px*8) + h, (py*16)+(ii*2)+1, 255, 255, 255);
//                    printf("X");
            } else {
//										setTexturePixel((px*8) + h, (py*16)+(ii*2), bgc->r, bgc->g, bgc->b);
//										setTexturePixel((px*8) + h, (py*16)+(ii*2)+1, bgc->r, bgc->g, bgc->b);
                setTexturePixel((px*8) + h, (py*16)+(ii*2), 0, 0, 0);
                setTexturePixel((px*8) + h, (py*16)+(ii*2)+1, 0, 0, 0);
//										printf(" ");
            }
            h++;
        }
        //  printf("\n");
    }
    return 0;
}

void process_Normal_Keys(int key, int x, int y) 
{
		printf("process_Normal_Keys()\r\n");
     switch (key) 
    {    
       case 27 :      break;
       case 100 : printf("GLUT_KEY_LEFT %d\n",key);   break;
       case 102: printf("GLUT_KEY_RIGHT %d\n",key);  ;  break;
       case 101   : printf("GLUT_KEY_UP %d\n",key);  ;  break;
       case 103 : printf("GLUT_KEY_DOWN %d\n",key);  ;  break;
    }

}


int main(int argc, char **argv)
{
    char *filename = NULL;
    filename = "bmf/8x8.bmf";

    myfont = bmf_load(filename);

    if (!myfont) {
        perror("bmf_load");
        exit(1);
    }


    display_width = SCREEN_WIDTH * modifier;
    display_height = SCREEN_HEIGHT * modifier;


//    if(!myChip8.loadApplication(argv[1]))
//        return 1;

    // Setup OpenGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

		glutSpecialFunc( process_Normal_Keys );

    glutInitWindowSize(display_width, display_height);
    glutInitWindowPosition(320, 320);
    glutCreateWindow("68K");

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape_window);
		//glutSpecialFunc( process_Normal_Keys );

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

    gfx_opengl_drawglyph(myfont, cx, cy, c, 7, 0, 0);
    cx++;
    if (cx == 80)	{
        cx = 0;
        cy ++;
    }
}

void updateTexture()
{
    while (p[0] != 0) {
        output_character(p[0]);
        p++;
    }
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
    glClear(GL_COLOR_BUFFER_BIT);

    updateTexture();
    glutSwapBuffers();
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
    display_width = w;
    display_height = h;
}


