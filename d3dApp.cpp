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

	case WM_DESTROY:
		PostQuitMessage(0);

		return 0;




		
	}
}