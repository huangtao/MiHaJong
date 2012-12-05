#include "window.h"
#include "../mihajong/version.h"

namespace mihajong_graphic {

const LPTSTR MainWindow::myWindowClassName = _T("mihajong_main");
const LPTSTR MainWindow::WindowCaption = _T("MiHaJong ver. ") _T(MIHAJONG_VER);
unsigned& MainWindow::WindowWidth = Geometry::WindowWidth;
unsigned& MainWindow::WindowHeight = Geometry::WindowHeight;

LRESULT CALLBACK MainWindow::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) { // ウィンドウプロシージャ
	switch (message) {
	case WM_DESTROY: // ウィンドウを閉じた時
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void MainWindow::initWindowClass(HINSTANCE hThisInst, LPCTSTR icon) { // ウィンドウクラスの初期化
	WNDCLASSEX myWindowClass;
	
	myWindowClass.hInstance = hThisInst;
	myWindowClass.lpszClassName = myWindowClassName;
	myWindowClass.lpfnWndProc = WinProc;
	myWindowClass.style = 0;
	myWindowClass.cbSize = sizeof(WNDCLASSEX);
	myWindowClass.hIcon = (HICON)LoadImage(hThisInst, icon, IMAGE_ICON, 0, 0, LR_DEFAULTSIZE);
	myWindowClass.hIconSm = (HICON)LoadImage(hThisInst, icon, IMAGE_ICON, 0, 0, LR_DEFAULTSIZE);
	myWindowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	myWindowClass.lpszMenuName = nullptr;
	myWindowClass.cbClsExtra = 0;
	myWindowClass.cbWndExtra = 0;
	myWindowClass.hbrBackground = nullptr;
	
	if (!RegisterClassEx(&myWindowClass))
		throw _T("ウィンドウクラスの登録に失敗しました");
	else return;
}

void MainWindow::initWindow(HINSTANCE hThisInst, int nWinMode) {
	RECT WindowRect;
	WindowRect.left = 0; WindowRect.right = WindowWidth;
	WindowRect.top = 0; WindowRect.bottom = WindowHeight;
	DWORD ExStyle = 0;
	DWORD Style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	AdjustWindowRectEx(&WindowRect, Style, FALSE, ExStyle);
	hWnd = CreateWindowEx(
		ExStyle, myWindowClassName, WindowCaption, Style,
		CW_USEDEFAULT, CW_USEDEFAULT,
		WindowRect.right - WindowRect.left, WindowRect.bottom - WindowRect.top,
		nullptr, nullptr, hThisInst, nullptr);
	if (!hWnd) throw _T("ウィンドウの生成に失敗しました");
	ShowWindow(hWnd, nWinMode);
	UpdateWindow(hWnd);
	return;
}

MainWindow::MainWindow(HINSTANCE hThisInst, int nWinMode, LPCTSTR icon) {
	initWindowClass(hThisInst, icon);
	initWindow(hThisInst, nWinMode);
	myScreenManipulator = new ScreenManipulator(hWnd);
	myInputManipulator = new input::InputManipulator(hWnd);
}

MainWindow::~MainWindow() {
	delete myScreenManipulator; myScreenManipulator = nullptr;
}

void MainWindow::Render() { // ウィンドウの再描画
	if (myScreenManipulator) {
		myScreenManipulator->Render();
		ValidateRect(hWnd, nullptr);
		if (myInputManipulator)
			myScreenManipulator->inputProc(myInputManipulator);
	}
	return;
}

void MainWindow::transit(sceneID scene) { // シーン切り替え
	if (myScreenManipulator)
		myScreenManipulator->transit(scene);
}

}
