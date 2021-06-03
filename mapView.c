#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void viewOnMap(long double lat, long double lng) {
	char script[150] = "python webmap.py ";
	char latStr[100], lngStr[100];
	snprintf(latStr, 50, "%f", lat); // converting doubles to str
	snprintf(lngStr, 50, "%f", lng);
	strcat(script, strcat(strcat(latStr, ","), lngStr)); // cancatenating all together!
	system(script);
}

////testing code
//int main() {
//	viewOnMap(30.062611479156878, 31.277055382673012);
//}