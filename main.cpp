#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 ) 
#include <iostream>

#include <CGameWindow.h>
#include <CModel.h>
#include <CDirectXManager.h>
#include <CLight.h>
#include <CCamera.h>


using namespace std;

CLight* myLight;
CCamera* myCamera;
CModel* myModel;
CModel* myModel2;
CGameWindow* myWindow;


HRESULT InitAll();



//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID Render()
{
	// Clear the backbuffer and the zbuffer
	myWindow->getDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	// Begin the scene
	myWindow->getDevice()->BeginScene();

	//描画はここに
	myLight->light();
	myModel->draw();
	myModel2->draw();
	myCamera->view();

	// End the scene
	myWindow->getDevice()->EndScene();

	// Present the backbuffer contents to the display
	myWindow->getDevice()->Present(NULL, NULL, NULL, NULL);
}






//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT) {

	//コンソールを使えるように
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);
	cout << "Hello!" << endl;

	myWindow = new CGameWindow();
	myWindow->createWindow(L"HelloWorld", 640, 480);

	InitAll();

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
		while (msg.message != WM_QUIT) {
			if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else {
				Render();
			}
	}

	return 0;
}


HRESULT InitAll() {
	myLight = new CLight();
	myLight->setDir(D3DXVECTOR3(0, -0.5, 1));
	myModel = new CModel(L"tiger.x");
	myModel->setScale(0.2f);
	myModel->setRotate(D3DXVECTOR3(0.5, 0, 0));
	myModel->setPosition(D3DXVECTOR3(-0.3, -0.5, 2));
	myModel2 = new CModel(L"car.x");
	myModel2->setScale(0.2f);
	myModel2->setRotate(D3DXVECTOR3(0.5, 0, 0));
	myModel2->setPosition(D3DXVECTOR3(0.3, 0.0, 2));
	myCamera = new CCamera();
	return S_OK;
}

