#include "EGLView.h"

EGLView* EGLView::sharedInstance()
{
	static EGLView eglView;
	return &eglView;
}


LRESULT CALLBACK EGLView::windowProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam) {
    switch(uiMsg) {
        case WM_CLOSE:
            PostQuitMessage(0);
            return 0;

        case WM_ACTIVATE:
        case WM_KEYDOWN:
        case WM_KEYUP:
        case WM_SIZE:
            return 0;
    }

    return DefWindowProc(hWnd, uiMsg, wParam, lParam);
}

void EGLView::createWindow()
{
	WNDCLASS wc;
	RECT wRect;
	//HWND hwnd;
	HINSTANCE hInstance;

	wRect.left = 0L;
	wRect.right = (long)960;
	wRect.top = 0L;
	wRect.bottom = (long)640;

	hInstance = GetModuleHandle(NULL);

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)EGLView::windowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "OGLES";

	RegisterClass(&wc);

	AdjustWindowRectEx(&wRect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);

	m_hwnd = CreateWindowEx(
		WS_EX_APPWINDOW | WS_EX_WINDOWEDGE, 
		"OGLES", "Pure2D",
		WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 
		0, 0, 
		wRect.right-wRect.left, wRect.bottom-wRect.top, 
		NULL, NULL, 
		hInstance, 
		NULL
		);

	ShowWindow(m_hwnd, SW_SHOW);
    SetForegroundWindow(m_hwnd);
    SetFocus(m_hwnd);

	m_hdc = GetDC(m_hwnd);
}

void EGLView::releaseWindow()
{
	ReleaseDC(m_hwnd,m_hdc);
	DestroyWindow(m_hwnd);
}

void EGLView::initEgl()
{
    EGLint attributeList[] = { EGL_RED_SIZE, 1, EGL_DEPTH_SIZE, 1, EGL_NONE };
    
    EGLint		aEGLAttributes[] = {
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_DEPTH_SIZE, 16,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES_BIT,
        EGL_NONE
    };
    EGLint		aEGLContextAttributes[] = {
        EGL_CONTEXT_CLIENT_VERSION, 1,
        EGL_NONE
    };
    EGLConfig m_eglConfig[1];
    EGLint nConfigs;

	m_eglDisplay = eglGetDisplay(m_hdc);

    eglInitialize(m_eglDisplay, NULL, NULL);
    eglChooseConfig(m_eglDisplay, aEGLAttributes, m_eglConfig, 1, &nConfigs);

	m_eglSurface = eglCreateWindowSurface(m_eglDisplay, m_eglConfig[0], (NativeWindowType)m_hwnd, 0);
    m_eglContext = eglCreateContext(m_eglDisplay, m_eglConfig[0], EGL_NO_CONTEXT, aEGLContextAttributes);

    eglMakeCurrent(m_eglDisplay, m_eglSurface, m_eglSurface, m_eglContext);
}

void EGLView::releaseEgl()
{
	eglMakeCurrent(m_eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglDestroyContext(m_eglDisplay, m_eglContext);
    eglDestroySurface(m_eglDisplay, m_eglSurface);
    eglTerminate(m_eglDisplay);
}

EGLView::EGLView()
{
	createWindow();
	initEgl();
}

EGLView::~EGLView()
{
	releaseEgl();
	releaseWindow();
}

void EGLView::swapBuffers()
{
	 eglSwapBuffers(m_eglDisplay, m_eglSurface);
}