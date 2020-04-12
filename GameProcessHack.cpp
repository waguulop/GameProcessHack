// GameProcessHack.cpp : Hacking a game process using memory heap.
// Author: Guillermo Santamaría Quesada
//

#include <iostream>
#include <Windows.h>
#include <string.h>
#include <TlHelp32.h>
using namespace std;

void menu();

int readMemory(HANDLE handle) {

	int readtest = 0;

	//You need to change the direction memory for every game using game test programs like cheat engine.
	ReadProcessMemory(handle, (PBYTE*)0x00ABEA6C, &readtest, sizeof(readtest), 0);

	//Return the integer of the value that we want to change on the game.
	return readtest;
}


void WriteNewValueMemory(HANDLE handle, int new_value){

	WriteProcessMemory(handle, (LPVOID)0x00ABEA6C, &new_value, sizeof(new_value), 0);
}

HANDLE findProcess(LPCSTR name_process){
	
	//Assign the windows process founded to hwnd.
	HWND hwnd = FindWindowA(NULL, name_process);
	//If hwnd hasn't been founded.
	if (hwnd == NULL)
	{
		cout << "\n\tCannot find the window process, try it again." << endl;
		menu();
	}
	else
	{
		//To assign the process ID (DWORD It's 32 bits).
		DWORD processID;
		GetWindowThreadProcessId(hwnd, &processID);

		//Acces to the memory ID.
		HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);

		//If processID hasn't been founded.
		if (processID == NULL)
		{
			cout << "\n\tCannot find the process, try it again." << endl;
			menu();
		}
		else //Writing memory.
		{
			return handle;
		}
	}
}

void menu(){

	int option = 0, new_value = 0;
	char name_process[50];

	cout << "\n\tGame process hack (only for local games, not multiplayer)" << endl;
	cout << "\t1. Find the process if it exists" << endl;
	cout << "\t2. Execute the hack" << endl;
	cout << "\t3. Exit" << endl;
	cout << "\n\tPlease, type an option: "; cin >> option;

	if (option == 1)
	{
		cout << "\n\tPlease, type the name process exactly (recommend to copy and past from task list): ";
		cin.ignore(256, '\n');
		cin.getline(name_process, 30);
		menu();
	}
	else if (option == 2)
	{
		cout << "\n\tActual value that you want to change on the game: " << readMemory(findProcess(name_process)) << endl;
		cout << "\n\tType the new value: "; cin >> new_value;
		WriteNewValueMemory(findProcess(name_process), new_value);
		menu();
	}
	else if (option == 3)
	{
		exit(-1);
	}
	
}


int main()
{
	menu();
}


