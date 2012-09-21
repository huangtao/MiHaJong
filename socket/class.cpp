#include "class.h"

uint32_t mihajong_socket::Sock::addr2var(const std::string& address) { // �A�h���X���擾
	uint32_t addr = inet_addr(address.c_str()); // �܂��� xxx.xxx.xxx.xxx �`���ł���Ɖ��肷��
	if ((addr == INADDR_NONE) || (addr == INADDR_ANY /* XP�ȑO�ŋ�̏ꍇ */)) { // ���s�����ꍇ
		hostent* host = gethostbyname(address.c_str()); // �z�X�g��������
		if (host == NULL) throw invalid_address(WSAGetLastError()); // ���s�������O�𓊂���
		addr = *(uint32_t *)host->h_addr_list[0]; // ���������炻�̃A�h���X
	}
	return addr;
}

mihajong_socket::Sock::Sock (const std::string& destination, uint16_t port) { // �N���C�A���g�ڑ�
	sock = socket(AF_INET, SOCK_STREAM, 0); // �\�P�b�g��������
	if (sock == INVALID_SOCKET) throw socket_creation_error(WSAGetLastError()); // �\�P�b�g�̍쐬�Ɏ��s�������O

	this->connect(destination, port); // �ڑ�
}

mihajong_socket::Sock::~Sock() { // �ڑ���؂�
	this->disconnect();
}

mihajong_socket::Sock::Sock (uint16_t port) { // �N���C�A���g�ڑ�
	this->listen(port); // �ڑ�
}

void mihajong_socket::Sock::listen (uint16_t port) { // �T�[�o�[�J�n
	lsock = socket(AF_INET, SOCK_STREAM, 0); // �\�P�b�g��������
	if (lsock == INVALID_SOCKET) throw socket_creation_error(WSAGetLastError()); // �\�P�b�g�̍쐬�Ɏ��s�������O
	isServer = true; // �T�[�o�[�ł���
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port); // �|�[�g�ԍ�
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); // �A�h���X
	if (bind(lsock, (sockaddr *)&addr, sizeof(addr)))
		throw socket_bind_error(WSAGetLastError()); // ���s�������O�𓊂���
	this->listen();
}

void mihajong_socket::Sock::listen () { // �T�[�o�[�J�n
	threadPtr.server = new server_thread();
	threadPtr.server->setaddr(addr);
	threadPtr.server->setsock(&sock, &lsock);
	CreateThread(NULL, 0, server_thread::thread, (LPVOID)threadPtr.server, 0, NULL);
}

void mihajong_socket::Sock::connect (const std::string& destination, uint16_t port) { // �N���C�A���g�ڑ�
	isServer = false; // �N���C�A���g�ł���
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port); // �|�[�g�ԍ�
	addr.sin_addr.S_un.S_addr = addr2var(destination.c_str()); // �A�h���X
	this->connect();
}

void mihajong_socket::Sock::connect () { // �N���C�A���g�Đڑ�
	threadPtr.client = new client_thread();
	threadPtr.client->setaddr(addr);
	threadPtr.client->setsock(&sock);
	CreateThread(NULL, 0, client_thread::thread, (LPVOID)threadPtr.client, 0, NULL);
}

bool mihajong_socket::Sock::connected () { // �ڑ�����Ă��邩���m�F
	if (isServer) {
		threadPtr.server->chkError();
		return threadPtr.server->isConnected();
	} else {
		threadPtr.client->chkError();
		return threadPtr.client->isConnected();
	}
};

int mihajong_socket::Sock::getc () { // �ǂݍ���
	try {
		if (isServer) { // ���u��
			return (int)threadPtr.server->read();
			threadPtr.server->chkError();
		} else {
			return (int)threadPtr.client->read();
			threadPtr.client->chkError();
		}
	}
	catch (queue_empty) { // �L���[���󂾂�����
		return -1;
	}
}

void mihajong_socket::Sock::putc (unsigned char byte) { // ��������
	if (isServer) {
		threadPtr.server->write(byte);
		threadPtr.server->chkError();
	} else {
		threadPtr.client->write(byte);
		threadPtr.client->chkError();
	}
}

void mihajong_socket::Sock::disconnect () { // �ڑ���؂�
	if (isServer) {
		threadPtr.server->terminate();
	} else {
		threadPtr.client->terminate();
	}
	closesocket(sock);
	if (isServer) {
		delete threadPtr.server;
		threadPtr.server = NULL;
	} else {
		delete threadPtr.client;
		threadPtr.client = NULL;
	}
}

// -------------------------------------------------------------------------

mihajong_socket::Sock::network_thread::network_thread() {
	errtype = errNone; errcode = 0;
	connected = terminated = finished = false;
	myRecvQueueMutex = CreateMutex(NULL, TRUE, NULL);
	mySendQueueMutex = CreateMutex(NULL, TRUE, NULL);
}

mihajong_socket::Sock::network_thread::~network_thread() {
	CloseHandle(myRecvQueueMutex);
	CloseHandle(mySendQueueMutex);
}

DWORD WINAPI mihajong_socket::Sock::network_thread::thread(LPVOID lp) { // �X���b�h���N�����邽�߂̏���
	return ((client_thread*)lp)->myThreadFunc();
}

void mihajong_socket::Sock::network_thread::chkError () { // �G���[���`�F�b�N���A�����G���[���������O�𓊂���
	switch (errtype) {
	case errNone: // �G���[�Ȃ�
		break;
	case errListen: // listen���s
		throw listen_failure(errcode);
	case errAccept: // accept���s
		throw accept_failure(errcode);
	case errConnection: // �ڑ����s
		throw connection_failure(errcode);
	case errRecv: // ��M���s
		throw recv_error(errcode);
	case errSend: // ���M���s
		throw send_error(errcode);
	default: // �ق��̃G���[
		throw socket_error(errcode);
	}
}

int mihajong_socket::Sock::network_thread::reader() { // ��M����
	unsigned char buf[bufsize] = {0,};
	WSABUF buffer; buffer.buf = reinterpret_cast<CHAR*>(buf); buffer.len = bufsize;
	DWORD recvsz; DWORD flag = 0;
	if (WSARecv(*mySock, &buffer, 1, &recvsz, &flag, NULL, NULL) == 0) { // ��M����
		WaitForSingleObject(myRecvQueueMutex, 0); // ��M�p�~���[�e�b�N�X���擾
		for (unsigned int i = 0; i < recvsz; ++i) myMailBox.push(buf[i]); // �L���[�ɒǉ�
		ReleaseMutex(myRecvQueueMutex); // ��M�p�~���[�e�b�N�X�����
	} else { // ��M�ł��Ȃ���
		switch (int err = WSAGetLastError()) {
		case WSAEWOULDBLOCK:
			break; // �f�[�^���Ȃ��ꍇ
		default: // �G���[����
			errtype = errRecv; errcode = err; terminated = finished = true; connected = false;
			return -((int)errtype);
		}
	}
	return 0;
}

int mihajong_socket::Sock::network_thread::writer() { // ���M����
	unsigned char buf[bufsize] = {0,};
	WSABUF buffer; buffer.buf = reinterpret_cast<CHAR*>(buf); buffer.len = bufsize;
	DWORD sendsz = 0;

	WaitForSingleObject(mySendQueueMutex, 0); // ���M�p�~���[�e�b�N�X���擾
	while (!mySendBox.empty()) {
		buf[sendsz++] = mySendBox.front(); mySendBox.pop(); // �L���[������o��
	}
	ReleaseMutex(mySendQueueMutex); // ���M�p�~���[�e�b�N�X�����
	if (sendsz && (WSASend(*mySock, &buffer, 1, &sendsz, 0, NULL, NULL))) { // ���M
		switch (int err = WSAGetLastError()) {
		case WSAEWOULDBLOCK:
			break; // ���̃G���[�͖�������
		default:
			errtype = errSend; errcode = err; terminated = finished = true; connected = false;
			return -((int)errtype);
		}
	}
	return 0;
}

DWORD WINAPI mihajong_socket::Sock::network_thread::myThreadFunc() { // �X���b�h�̏���
	if (int err = establishConnection()) return err; // �ڑ�
	u_long arg = 1;
	ioctlsocket(*mySock, FIONBIO, &arg); // non-blocking ���[�h�ɐݒ�
	while (!terminated) { // ��~�����܂�
		if (int err = reader()) return err; // �ǂݍ���
		if (int err = writer()) return err; // ��������
	}
	finished = true;
	return S_OK;
}

unsigned char mihajong_socket::Sock::network_thread::read () { // 1�o�C�g�ǂݍ���
	unsigned char byte; bool empty = false;
	WaitForSingleObject(myRecvQueueMutex, 0); // ��M�p�~���[�e�b�N�X���擾
	if (myMailBox.empty()) empty = true; // �L���[����̏ꍇ
	else {byte = myMailBox.front(); myMailBox.pop();} // ��łȂ���Ύ��o��
	ReleaseMutex(myRecvQueueMutex); // ��M�p�~���[�e�b�N�X�����
	if (empty) throw queue_empty(); // �󂾂������O
	else return byte; // �����łȂ���Ύ��o�����l��Ԃ�
}

void mihajong_socket::Sock::network_thread::write (unsigned char byte) { // 1�o�C�g��������
	WaitForSingleObject(mySendQueueMutex, 0); // ���M�p�~���[�e�b�N�X���擾
	mySendBox.push(byte); // �L���[�ɒǉ�
	ReleaseMutex(mySendQueueMutex); // ���M�p�~���[�e�b�N�X�����
}

bool mihajong_socket::Sock::network_thread::isConnected() { // �ڑ��ς���Ԃ��֐�
	return connected;
}

void mihajong_socket::Sock::network_thread::setaddr (const sockaddr_in destination) { // �ڑ����ݒ肷��
	myAddr = destination;
}
void mihajong_socket::Sock::network_thread::setsock (SOCKET* const socket) { // �\�P�b�g��ݒ肷��
	mySock = socket;
}

void mihajong_socket::Sock::network_thread::terminate () { // �ؒf����
	terminated = true; // �t���O�𗧂Ă�
	while (!finished) Sleep(0); // �X���b�h���I������܂ő҂�
	finished = terminated = connected = false; // �t���O�̌�n��
	errtype = errNone; errcode = 0;
}

// -------------------------------------------------------------------------

int mihajong_socket::Sock::client_thread::establishConnection() { // �ڑ����m������
	if (::connect(*mySock, (sockaddr*)&myAddr, sizeof(myAddr)) == SOCKET_ERROR) { // �ڑ�
		errtype = errConnection; errcode = WSAGetLastError(); return -((int)errtype);
	}
	connected = true; // �ڑ��ς݃t���O�𗧂Ă�
	return 0;
}

int mihajong_socket::Sock::server_thread::establishConnection() { // �ڑ����m������
	if (::listen(*listenerSock, SOMAXCONN) == SOCKET_ERROR) { // �ҋ@
		errtype = errListen; errcode = WSAGetLastError(); return -((int)errtype);
	}
	*mySock = accept(*listenerSock, NULL, 0);
	if (*mySock == INVALID_SOCKET) { // �\�P�b�g�̍쐬�Ɏ��s�ꍇ
		errtype = errAccept; errcode = WSAGetLastError();
		closesocket(*listenerSock);
		return -((int)errtype);
	}
	closesocket(*listenerSock);
	connected = true; // �ڑ��ς݃t���O�𗧂Ă�
	return 0;
}

void mihajong_socket::Sock::server_thread::setsock (SOCKET* const socket, SOCKET* const lsocket) { // �\�P�b�g��ݒ肷��
	mySock = socket; listenerSock = lsocket;
}