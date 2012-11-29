#include "input.h"
#include "init.h"
#include "../mjcore/strcode.h"

namespace mihajong_graphic {
namespace input {

// -------------------------------------------------------------------------

InputManipulator::InputManipulator(HWND hwnd) {
	if (FAILED(DirectInput8Create(
		GraphicDLL, 0x0800, IID_IDirectInput8, reinterpret_cast<void**>(&myInterface), nullptr)))
		throw CodeConv::tstring(_T("DirectInput8Create失敗！！"));
	myKeyboard = new Keyboard(myInterface, hwnd);
}

InputManipulator::~InputManipulator() {
	if (myKeyboard) delete myKeyboard;
	myInterface->Release();
}

// -------------------------------------------------------------------------

InputDevice::~InputDevice() {}

// -------------------------------------------------------------------------

Keyboard::Keyboard(LPDIRECTINPUT8 inputInterface, HWND hwnd) {
	if (FAILED(inputInterface->CreateDevice(GUID_SysKeyboard, &myInputDevice, nullptr)))
		throw CodeConv::tstring(_T("CreateDevice失敗！！"));
	if (FAILED(myInputDevice->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
		throw CodeConv::tstring(_T("SetCooperativeLevel失敗！！"));
}

Keyboard::~Keyboard() {
	if (myInputDevice) {
		myInputDevice->Unacquire();
		myInputDevice->Release();
	}
}

// -------------------------------------------------------------------------

}
}
