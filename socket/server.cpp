#include "server.h"

namespace mihajong_socket {
namespace server {
	starter* starterThread = nullptr;
	unsigned int NumberOfPlayers = 4;
	std::string getString(unsigned int socketID) { // 文字列を取得(同期)
		std::string tmpString; unsigned int l = 0u;
		while (true) { // 文字列開始シグネチャを受け取る
			if (sockets[socketID]->syncgetc() == protocol::StartString_Signature)
				break;
		}
		l = sockets[socketID]->syncgetc(); // 文字列の長さを受け取る
		unsigned char tmpchr[sizeof(int)] = {0};
		for (unsigned int sp = 0; sp < l; ++sp) { // 文字列を受信する
			tmpchr[0] = sockets[socketID]->syncgetc();
			tmpString += std::string(reinterpret_cast<char*>(tmpchr));
		}
		return tmpString;
	}
	void putString(unsigned int socketID, const std::string& sendingStr) { // 文字列を送信
		sockets[socketID]->putc(protocol::StartString_Signature);
		unsigned strsz = sendingStr.length();
		if (strsz > UCHAR_MAX) {
			sockets[socketID]->putc(UCHAR_MAX);
			sockets[socketID]->puts(sendingStr.substr(0, UCHAR_MAX));
		} else {
			sockets[socketID]->putc(strsz);
			sockets[socketID]->puts(sendingStr);
		}
	}

	// ---------------------------------------------------------------------

	starter::starter (const std::string& InputPlayerName, unsigned short port, const char* const * const rule) { // コンストラクタ
		terminated = finished = false;
		playerName[0] = std::string("[A]") + InputPlayerName;
		playerName[1] = std::string("[b]COM");
		playerName[2] = std::string("[c]COM");
		playerName[3] = std::string("[d]COM");
		portnum = port;
		std::memset(ruleConf, 0, sizeof(ruleConf));
		for (unsigned i = 0; i < (RULESIZE/RULE_IN_LINE); ++i)
			std::memcpy(ruleConf[i], rule[i], RULE_IN_LINE);
	}

	// ---------------------------------------------------------------------

	DWORD WINAPI starter::preparationThread () { // 接続を待ち、接続処理をする
		sockets[0] = new Sock(portnum);
		CurrentConnection = 1;
		while (!terminated) {
			if (sockets[0]->connected()) {
				sockets[0]->putc(CurrentConnection + 1);
				delete sockets[0]; sockets[0] = nullptr;
				sockets[CurrentConnection] = new Sock(portnum + CurrentConnection);
				sockets[CurrentConnection]->wait_until_connected(); // 接続を待つ
				char tmpsignature[] = "[A]"; tmpsignature[1] += CurrentConnection; // 英字
				playerName[CurrentConnection] = std::string(tmpsignature) + getString(CurrentConnection);
				sockets[0] = new Sock(portnum); // 再度listen開始
				++CurrentConnection;
			}
			if (CurrentConnection >= NumberOfPlayers) break;
			Sleep(50); // Yield
		}
		delete sockets[0]; sockets[0] = nullptr; // 待機用のソケットを閉じる
		send(protocol::Server_StartGame_Signature);
		for (unsigned int i = 0; i < NumberOfPlayers; ++i)
			sendstr(playerName[i]); // 名前を送信
		for (unsigned i = 0; i < (RULESIZE/RULE_IN_LINE); ++i)
			sendstr(ruleConf[i]); // ルールを送信
		finished = true;
		return S_OK;
	}

	// ---------------------------------------------------------------------

	DWORD WINAPI starter::initiate (LPVOID param) { // CreateThread()に渡す引数用
		return ((starter*)param)->preparationThread();
	}

	void starter::terminate () { // すぐに開始
		terminated = true;
	}
	bool starter::isFinished () { // 待機用スレッドが終わったかどうか
		return finished;
	}
	unsigned int starter::chkCurrentConnection () { // 現在の接続数
		return CurrentConnection;
	}
	std::string starter::getPlayerName (unsigned id) { // プレイヤー名
		return playerName[id];
	}

	DLL void start (const char* const name, int port, int players, const char* const * const rule) { // サーバーを開始させる(DLL)
		NumberOfPlayers = (unsigned int)players;
		starterThread = new starter(name, (unsigned short)port, rule);
		CreateThread(nullptr, 0, starter::initiate, (LPVOID)starterThread, 0, nullptr);
	}
	DLL void doStart() { // 接続待機をやめ、直ちに開始する
		starterThread->terminate();
	}
	DLL int isStartingFinished () { // 待機用スレッドが終わったかどうか
		return starterThread->isFinished() ? 1 : 0;
	}
	DLL int chkCurrentConnection () { // 現在の接続数
		return (int)starterThread->chkCurrentConnection();
	}
	DLL void getPlayerNames (char* playerName1, char* playerName2, char* playerName3, char* playerName4, unsigned bufsz) {
		strcpy_s(playerName1, bufsz, starterThread->getPlayerName(0).c_str());
		strcpy_s(playerName2, bufsz, starterThread->getPlayerName(1).c_str());
		strcpy_s(playerName3, bufsz, starterThread->getPlayerName(2).c_str());
		strcpy_s(playerName4, bufsz, starterThread->getPlayerName(3).c_str());
	}
	DLL void releaseobj () { // デストラクタを呼ぶだけ
		delete starterThread; starterThread = nullptr;
	}

	// ---------------------------------------------------------------------

	DLL void send (unsigned char SendingMsg) { // サーバーからの送信
		for (unsigned int i = 1; i < NumberOfPlayers; ++i)
			if (sockets[i]&&(sockets[i]->connected())) sockets[i]->putc(SendingMsg);
	}
	void sendstr (const std::string& sendingStr) { // サーバーからの文字列送信
		for (unsigned int i = 1; i < NumberOfPlayers; ++i)
			if (sockets[i]&&(sockets[i]->connected())) putString(i, sendingStr);
	}
	DLL void send (int SendingMsg, void*) { // サーバーからの送信
		send((unsigned char)SendingMsg);
	}

	// ---------------------------------------------------------------------

	std::array<unsigned, 3> ServerCheckRotation; // クライアントの読み出し優先順位

	DLL void rotation_reset () { // 取得優先順位のリセット
		for (unsigned i = 0; i < 3; ++i) ServerCheckRotation[i] = i + 1;
	}
	DLL void receive (int* const ServerReceived, int* const ReceivedMsg) { // 取得する
		*ServerReceived = 0; *ReceivedMsg = 1023; bool finished = false;
		for (unsigned i = 0; i < (NumberOfPlayers - 1); ++i) {
			if (sockets[ServerCheckRotation[i]] != nullptr) {
				try {
					*ServerReceived = ServerCheckRotation[i];
					*ReceivedMsg = sockets[ServerCheckRotation[i]]->getc();
					finished = true;
				}
				catch (queue_empty) { // Falling back if empty...
					*ServerReceived = 0;
					*ReceivedMsg = 1023;
					finished = false;
				}
				// かつてはここでログを送っていた
			}
			if (finished) break;
		}
		{ // 取得優先順位をシフト
			unsigned tmp = ServerCheckRotation[0];
			ServerCheckRotation[0] = ServerCheckRotation[1];
			ServerCheckRotation[1] = ServerCheckRotation[2];
			ServerCheckRotation[2] = tmp;
		}
	}

}
}
