#include "EGL\egl.h"
#include "GLES\gl.h"

class EGLView
{
public:
	static EGLView* sharedInstance();

public:
	void swapBuffers();

private:
	EGLView();
	~EGLView();

	void createWindow();
	void releaseWindow();
	void initEgl();
	void releaseEgl();

	static LRESULT CALLBACK windowProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);

private:
	HWND m_hwnd;
	HDC m_hdc;

	EGLDisplay m_eglDisplay;
    EGLContext m_eglContext;
    EGLSurface m_eglSurface;
};