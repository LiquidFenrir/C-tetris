#include <conio.h>
#include "keys.h"

int getKeys()
{
	if (!kbhit()) return -1;

    switch (getch()) { // if the first value is \x1b

		case '\r':
			return KEY_ENTER;
			break;
		case 'x':
			return KEY_X;
			break;
		case 'c':
			return KEY_C;
			break;
		case 'v':
			return KEY_V;
			break;

//		case 224:
//			switch(getch()) {
				case 'H':
					return KEY_UP;
					break;
				case 'P':
					return KEY_DOWN;
					break;
				case 'K':
					return KEY_LEFT;
					break;
				case 'M':
					return KEY_RIGHT;
					break;
//			}
//			break;
    }

    return 0;
}
