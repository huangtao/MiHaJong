#ifndef SOCKET_H
#define SOCKET_H

#include <WinSock2.h>
#include "class.h"

#define NUM_OF_SOCKETS 32

#ifdef SOCKET_EXPORTS
#include "except.h"
#define DLL __declspec(dllexport)
#else
#define DLL __declspec(dllimport)
#endif

namespace mihajong_socket {
#ifdef SOCKET_EXPORTS
class Sock;
extern WSADATA SocketInfo;
extern HINSTANCE dllInst;
#else
#define DLL __declspec(dllimport)
#endif

void errordlg (socket_error& err); // �G���[�_�C�A���O
DLL int socket_init (); // �\�P�b�g������������
DLL int socket_bye (); // �\�P�b�g�̃N�����i�b�v

}
#endif