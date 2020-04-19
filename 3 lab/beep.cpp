#include<windows.h>
#include<iostream>
#include<cstdlib>
using namespace std;

void Beeper() {
	/*double B = 493.88,
		D = 587.32,
		A = 440.00,
		G = 392.00;*/
		/*Beep(B, 300);
		Beep(D, 300);
		Beep(B, 300);
		Beep(D, 600);

		Beep(B, 300);
		Beep(A, 300);
		Beep(B, 600);

		Beep(A, 300);
		Beep(G, 300);
		Beep(A, 600);
		Beep(G, 600);
	*/
	DWORD d = 190,
		r = 240,
		m = 290,
		f = 340,
		s = 390,
		l = 440,
		c = 490;
	/*Beep(190, 500);
	Beep(240, 500);
	Beep(290, 500);
	Beep(340, 500);
	Beep(390, 500);
	Beep(440, 500);
	Beep(490, 500);
	Beep(540, 500);
*/
/*Beep(90, 300);
Beep(d, 300);
Beep(r, 400);
Beep(r, 400);
Beep(r, 300);
Beep(m, 300);
Beep(f, 400);
Beep(f, 400);
Beep(f, 300);
Beep(s, 300);
Beep(m, 400);
Beep(m, 400);
Beep(r, 300);
Beep(d, 300);
Beep(d, 250);
Beep(r, 400);*/

	Beep(490, 400);
	Beep(640, 500);
	Beep(740, 250);
	Beep(715, 400);
	Beep(640, 800);
	Beep(840, 400);
	Beep(790, 950);
	Beep(715, 950);

	Beep(640, 500);
	Beep(740, 250);
	Beep(715, 400);
	Beep(615, 800);
	Beep(690, 400);
	Beep(490, 1350);
	Beep(490, 400);

	Beep(640, 500);
	Beep(740, 250);
	Beep(715, 400);
	Beep(640, 800);
	Beep(840, 400);
	Beep(940, 800);
	Beep(915, 400);
	Beep(890, 800);

	Beep(765, 400);
	Beep(890, 500);
	Beep(840, 250);
	Beep(815, 400);
	Beep(465, 800);
	Beep(740, 400);
	Beep(640, 1350);
}

DWORD WINAPI WorkerThread(PVOID param) {
	while (true) {
		Beeper();
	}
}

int main() {
	setlocale(LC_ALL, "rus");
	DWORD lpdwFlags = 0;
	DWORD ThreadID;

	if (GetProcessHandleCount(GetCurrentProcess(), &lpdwFlags)) {
		cout << (int)lpdwFlags << endl;
	}

	HANDLE NPipe = CreateNamedPipe("\\\\.\\pipe\\NPipe", PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE | PIPE_WAIT, 1, 0, 0, INFINITE, NULL);

	if (NPipe == INVALID_HANDLE_VALUE) {
		std::cout << "Don't create pipe: " << GetLastError() << std::endl;
		system("pause");
		return 1;
	}

	GetHandleInformation(NPipe, &lpdwFlags);
	if ((int)lpdwFlags == HANDLE_FLAG_INHERIT) {
		cout << "NPipe наследуется" << endl;
	}
	else cout << "NPipe НЕ наследуется" << endl;
	if ((int)lpdwFlags == HANDLE_FLAG_PROTECT_FROM_CLOSE) {
		cout << "При вызове CloseHandle дескриптор НЕ будет закрыт" << endl;
	}
	else cout << "При вызове CloseHandle дескриптор будет закрыт" << endl;

	SetHandleInformation(NPipe, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);

	GetHandleInformation(NPipe, &lpdwFlags);
	if ((int)lpdwFlags == HANDLE_FLAG_INHERIT) {
		cout << "NPipe наследуется" << endl;
	}
	else cout << "NPipe НЕ наследуется" << endl;
	if ((int)lpdwFlags == HANDLE_FLAG_PROTECT_FROM_CLOSE) {
		cout << "При вызове CloseHandle дескриптор НЕ будет закрыт" << endl;
	}
	else cout << "При вызове CloseHandle дескриптор будет закрыт" << endl;

	SetHandleInformation(NPipe, HANDLE_FLAG_INHERIT, 0);

	GetHandleInformation(NPipe, &lpdwFlags);
	if ((int)lpdwFlags == HANDLE_FLAG_INHERIT) {
		cout << "NPipe наследуется" << endl;
	}
	else cout << "NPipe НЕ наследуется" << endl;
	if ((int)lpdwFlags == HANDLE_FLAG_PROTECT_FROM_CLOSE) {
		cout << "При вызове CloseHandle дескриптор НЕ будет закрыт" << endl;
	}
	else cout << "При вызове CloseHandle дескриптор будет закрыт" << endl;

	if (GetProcessHandleCount(GetCurrentProcess(), &lpdwFlags)) {
		cout << (int)lpdwFlags << endl;
	}

	if (!ConnectNamedPipe(NPipe, NULL)) {
		std::cout << "Don't connect with client: " << GetLastError() << std::endl;
		system("pause");
		return 2;
	}
	
	HANDLE hThread = CreateThread(NULL, 0, WorkerThread, NULL, 0, &ThreadID);
	
	HANDLE file = CreateFile("beep_play.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE
		| FILE_SHARE_DELETE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	
	DWORD writed;
	const int buf = sizeof(HANDLE);
	DWORD message = 0;

	if (!ReadFile(NPipe, (LPVOID)&message, sizeof(message), &writed, NULL)) {
		cout << "Don't Read Server: " << GetLastError() << endl;
		system("pause");
		return 2;
	}

	HANDLE cProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, message);
	if (cProc == NULL) {
		std::cerr << "Bad PID" << GetLastError() << std::endl;
		system("pause");
		return 5;
	}
	
	HANDLE dThread, dFile = 0;
	if (DuplicateHandle(GetCurrentProcess(), hThread, cProc, &dThread, 0, FALSE, DUPLICATE_SAME_ACCESS)) {
		cout << "dThread создан" << endl;
		if (DuplicateHandle(GetCurrentProcess(), file, cProc, &dFile, 0, FALSE, DUPLICATE_SAME_ACCESS)) {
			cout << "dFile создан" << endl;

			if (!WriteFile(NPipe, &dThread, sizeof(HANDLE), &writed, NULL)) {
				cout << "dThread не передан: " << GetLastError() << endl;
				system("pause");
				return 5;
			}

			if (!WriteFile(NPipe, &dFile, sizeof(HANDLE), &writed, NULL)) {
				cout << "dFile не передан: " << GetLastError() << endl;
				system("pause");
				return 5;
			}

			while (true) {
				if (!ReadFile(NPipe, &message, sizeof(DWORD), &writed, NULL)) {
					cout << "Don't Read Server: " << GetLastError() << endl;
					system("pause");
					return 2;
				}
				if ((int)message == 0) break;
			}
		}
		else {
			cout << "dFile НЕ создан: " << GetLastError() << endl;
		}
	}
	else {
		cout << "dThread НЕ создан: " << GetLastError() << endl;
	}

	CloseHandle(cProc);
	CloseHandle(NPipe);
	system("pause");
	return 0;
}