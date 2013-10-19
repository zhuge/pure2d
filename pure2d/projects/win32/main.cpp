#include "EGL\egl.h"
#include "GLES\gl.h"
#include "EGLView.h"

/*
 * This proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2007, 2009, 2011 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

/* file simpApp11.c  Color Cube example using OpenGL ES 1.1 */

#include <stdio.h>
#include <stdlib.h>
#include <EGL/egl.h>
#include <GLES/gl.h>
#include <math.h>
#include <time.h>

static const GLfloat coord [] = {
				  1.f,  1.f,  1.f,      /* 0 */
				 -1.f,  1.f,  1.f,      /* 1 */
				 -1.f, -1.f,  1.f,      /* 2 */
				  1.f, -1.f,  1.f,      /* 3 */
				 -1.f,  1.f, -1.f,      /* 4 */
				  1.f,  1.f, -1.f,      /* 5 */
				  1.f, -1.f, -1.f,      /* 6 */
				 -1.f, -1.f, -1.f };    /* 7 */

static const GLubyte color [] = {
				 255, 255, 255, 255, 
				 255,   0, 255, 255, 
				 0,     0, 255, 255, 
				 0,   255, 255, 255,
				 255,   0,   0, 255,
				 255, 255,   0, 255,
				 0,   255,   0, 255,
				 0,     0,   0, 255};

static const GLushort fanIx [] = {
				 0, 1, 2, 3, 6, 5, 4, 1,   /* One tri.fan  */
				 7, 6, 3, 2, 1, 4, 5, 6};  /*  and another */


static void init(void) {
    glClearColor(0.3f, 0.2f, 0.1f, 1.0f);
    glClearDepthf(1.0f);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, 256, 256);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustumf(-0.6f, 0.6f, -0.6f, 0.6f, 2.0f, 10.f);
    glMatrixMode(GL_MODELVIEW);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, coord);
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(4, GL_UNSIGNED_BYTE, 0, color);
}  /* init */


static float tim(void) {
    return (float)clock()/(float)CLOCKS_PER_SEC;
}


static void draw(void) {
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
    {
		printf("draw() failed (error 0x%x)\n", err);
		exit(1);
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -6.0f);
    glRotatef(tim()*55, 0.3f, 1.f, 1.3f);
    glDrawElements(GL_TRIANGLE_FAN, 8, GL_UNSIGNED_SHORT, fanIx);
    glDrawElements(GL_TRIANGLE_FAN, 8, GL_UNSIGNED_SHORT, &(fanIx[8]));
}  /* draw */

int main(int argc, char** argv) {

	EGLView* eglView = EGLView::sharedInstance();

    /* Begin user code: */

	bool done = false;

    init();

	MSG message;
    for (;!done;)
    {
        /* Do Windows stuff */
        if(PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
        {
            if(message.message == WM_QUIT)
            {
                done = true;
            }
            else 
            {
                TranslateMessage(&message);
                DispatchMessage(&message);
            }
        }
        draw();
		eglView->swapBuffers();
    }		
    
    /* End of user code */

    return 0;
}