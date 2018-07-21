#include "SoldierType.h"

int getDMG(int T)
{
	switch (T) {
	case 1:
		return 5;
	case 2:
		return 2;
	}
}

int getHP(int T) {
	switch (T) {
	case 1:
		return 100;
	case 2:
		return 50;
	}
}