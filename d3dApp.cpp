//*****************************************************************************************
// d3dApp.cpp by Frank Luna (C) 2015 All Rights Reserved.
// Copyright Chang-Wan Park 2022
//*****************************************************************************************

#include "d3dApp.h"


#include "windowsx.h"
#include <cassert>

using namespace std;

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// Forward hwnd on because we can get message ( e.g., WM_CREATE)
	// before CreateWindow returns, and thus before mhMainWnd is valid.

	return D3DApp::GetApp()->MsgProc(hwnd, msg, wParam, lParam);
}

D3DApp* D3DApp::mApp = nullptr;

D3DApp* D3DApp::GetApp()
{
	return mApp;
}

D3DApp::D3DApp(HINSTANCE hInstance)
	: mhAppInst(hInstance)
{
	// Only one D3DApp can be constructed.
	assert(mApp == nullptr);
	mApp = this;
}

D3DApp::~D3DApp()
{
}

HINSTANCE D3DApp::AppInst()const
{
	return mhAppInst;
}

HWND D3DApp::MainWnd()const
{
	return mhMainWnd;
}

int D3DApp::Run()
{
	MSG msg = { 0 };

	while (msg.message != WM_QUIT)
	{
		// If there are Window messages then process them.
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// Otherwise, do animation/game stuff.
		else
		{
			if (!mAppPaused)
			{
				// May be Calulate & Update & Draw
			}
			else
			{
				Sleep(100);
			}
			
		}

	}

	return (int)msg.wParam;
}


bool D3DApp::Initialize()
{
	if (!InitMainWindow()) return false;

	return true;

}


LRESULT D3DApp::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		// WM_ACTIVATE is sent when the window is activated or deactivated.
		// We pause the game when the window is deactivated and unpause it
		// when it becomes active.
	case WM_ACTIVATE:
		if (LOWORD(wParam) == WA_INACTIVE)
		{
			mAppPaused = true;
		}
		else
		{
			mAppPaused = false;
		}

		return 0;

	// WM_SIZE is sent when the user resizes the window.
	case WM_SIZE:
		mClientWidth	= LOWORD(lParam);
		mClientHeight	= HIWORD(lParam);
		
		return 0;


	// WM_ENTERSIZEMOVE is sent when the user grabs the resize bars.
	case WM_ENTERSIZEMOVE:
		mAppPaused = true;

		return 0;

	// WM_EXITSIZEMOVE is sent when the user releases the resize bars.
	// Here we reset everything based on the new windodw dimensions.
	case WM_EXITSIZEMOVE:
		mAppPaused = false;

		return 0;

	// WM_DESTROY is sent when the window is being destroyed.
	case WM_DESTROY:
		PostQuitMessage(0);

		return 0;

	// The WM_MENUCHAR message is sent when a menu is active and the user presses
	// a key that does not correspond to any mnemonic or accelerator key.
	case WM_MENUCHAR:
		// Don't beep when we alt-enter.
		return MAKELRESULT(0, MNC_CLOSE);

	// Catch this message so th prevent the window from becoming to small.
	// If you want to FullScreen but historical none.
	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200;
		return 0;

	case WM_KEYUP:
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
		}
		
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}


bool D3DApp::InitMainWindow()
{
	WNDCLASS wc;
	wc.style		= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc	= MainWndProc;
	wc.cbClsExtra	= 0;
	wc.cbWndExtra	= 0;
	wc.hInstance	= mhAppInst;
	wc.hIcon		= LoadIcon(0, IDI_APPLICATION);
	wc.hCursor		= LoadCursor(0, IDC_ARROW);
	wc.hbrBackground	= (HBRUSH)GetStockObject(NULL_BRUSH);
	wc.lpszMenuName		= 0;
	wc.lpszClassName	= L"MainWnd";

	if (!RegisterClass(&wc))
	{
		MessageBox(0, L"RegisterClass Failed.", 0, 0);
		return false;
	}

	// Compute window rectangle dimensions based on requested client area dimensions.
	RECT R = { 0, 0, mClientWidth, mClientHeight };
	AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
	int width = R.right - R.left;
	int height = R.bottom - R.top;

	mhMainWnd = CreateWindow(L"MainWnd", mMainWndCaption.c_str(),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, mhAppInst, 0);

	if (!mhMainWnd)
	{
		MessageBox(0, L"CreateWindow Failed", 0, 0);
		return false;
	}

	ShowWindow(mhMainWnd, SW_SHOW);
	UpdateWindow(mhMainWnd);

	return true;

}