//****************************************************************************************
// Init Direct3D.cpp by Frank Luna (C) 2015 All Rights Reserved.
// Copyright Chang-Wan Park 2022
//
// Demonsdtrates the sample framework by initalizing Direct3D, clearing
// the screen, and displaying frame stats.
//
//****************************************************************************************

#include "./d3dApp.h"

#include "crtdbg.h"



class InitDirect3DApp : public D3DApp
{
public:
	InitDirect3DApp(HINSTANCE hInstance);
	~InitDirect3DApp();

	virtual bool Initialize()override;

private:
	// May be exiting OnResize, Update, Draw . 

};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
	PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif


	InitDirect3DApp theApp(hInstance);
	if (!theApp.Initialize())
		return 0;

	return theApp.Run();

}
	
InitDirect3DApp::InitDirect3DApp(HINSTANCE hInstance)
	:D3DApp(hInstance)
{
}

InitDirect3DApp::~InitDirect3DApp()
{
}

bool InitDirect3DApp::Initialize()
{
	if (!D3DApp::Initialize())
		return false;

	return true;
}