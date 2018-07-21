#pragma once


int getDMG(int T) {
	switch (T) {
	case 1:
		return 10;
	case 2:
		return 5;
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