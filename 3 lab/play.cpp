#include<windows.h>
#include<iostream>
#include<cstdlib>
using namespace std;

int main(){
	
	setlocale(0, "");
	
	char PipeName[80];
	wsprintf(PipeName, "\\\\.\\pipe\\NPipe");

	if (!WaitNamedPipe(PipeName, NMPWAIT_WAIT_FOREVER)) {
		std::cerr << "Error000" << GetLastError() << std::endl;
		system("pause");
		return 66;
	}

	HANDLE NPipe = CreateFile(PipeName, GENERIC_WRITE | GENERIC_READ,
		FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (NPipe == INVALID_HANDLE_VALUE) {
		std::cout << "Don't open Pipe: " << GetLastError() << std::endl;
		return 1;
	}

	DWORD writed;
	DWORD proc = GetCurrentProcessId();
	HANDLE dThread = 0, dFile = 0;
	if (!WriteFile(NPipe, &proc, sizeof(proc), &writed, NULL)) {
		cout << "Don't Write File: " << GetLastError() << endl;
		system("pause");
		return 5;
	}

	if (!ReadFile(NPipe, &dThread, sizeof(HANDLE), &writed, NULL)) {
		cout << "Don't Read Server: " << GetLastError() << endl;
		system("pause");
		return 2;
	}
	cout << "dThread получен" << endl;
	if (!ReadFile(NPipe, &dFile, sizeof(HANDLE), &writed, NULL)) {
		cout << "Don't Read Server: " << GetLastError() << endl;
		system("pause");
		return 2;
	}
	cout << "dFile получен" << endl;
	int a;
	char resume[] = "You resume thread\r\n";
	char suspend[] = "You suspend thread\r\n";
	char terminate[] = "You terminate thread\r\n";
	do {
		cout << "Выберите:" << endl;
		cout << "1) Остановить поток" << endl;
		cout << "2) Возобновить работу потока" << endl;
		cout << "3) Выход" << endl;

		cin >> a;

		if (a == 1) {
			SuspendThread(dThread);
			if (!WriteFile(dFile, suspend, sizeof(suspend), &writed, NULL)) {
				cout << "Don't Write dFile: " << GetLastError() << endl;
				system("pause");
				//return 5;
			}
		}
		else if (a == 2) {
			ResumeThread(dThread);
			if (!WriteFile(dFile, resume, sizeof(resume), &writed, NULL)) {
				cout << "Don't Write dFile: " << GetLastError() << endl;
				system("pause");
				//return 5;
			}
		}
	else if (a == 3) {
			void* m = 0;
			TerminateThread(dThread, 0);
			if (!WriteFile(dFile, terminate, sizeof(terminate), &writed, NULL)) {
				cout << "Don't Write File: " << GetLastError() << endl;
				system("pause");
				//return 5;
			}
			if (!WriteFile(NPipe, &m, sizeof(int), &writed, NULL)) {
				cout << "Дескриптро не передан: " << GetLastError() << endl;
				system("pause");
				return 5;
			}
		}

	} while (a != 3);

	CloseHandle(dThread);
	CloseHandle(dFile);
	CloseHandle(NPipe);	
	system("pause");
	return 0;
}
