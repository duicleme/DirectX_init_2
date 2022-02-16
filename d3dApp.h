//****************************************************************************************
// d3dApp.h by Frank Luna (C) 2015 All Rights Reserved.
// Copyright Chang-Wan Park 2022
//****************************************************************************************

#pragma once

#if defined(DEBUG) || defined (_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include <Windows.h>
#include <string>


class D3DApp
{
protected:
	D3DApp(HINSTANCE hInstance);
	D3DApp(const D3DApp& rhs) = delete;
	D3DApp& operator=(const D3DApp& rhs) = delete;
	virtual ~D3DApp();

public:

	static D3DApp* GetApp();

	HINSTANCE AppInst()const;
	HWND      MainWnd()const;
	
	int Run();

	virtual bool Initialize();
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	bool InitMainWindow();

protected:
	static D3DApp* mApp;
	
	HINSTANCE	mhAppInst = nullptr;	// application instance handle
	HWND		mhMainWnd = nullptr;	// main window handle
	bool		mAppPaused = false;		// is the application paused?

	std::wstring mMainWndCaption = L"d3d App";
	int mClientWidth = 800;
	int mClientHeight = 600;

};