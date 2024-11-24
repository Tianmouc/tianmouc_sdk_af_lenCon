#include"LensCtrl.h"
#include"LensConnect.h"
#include<unistd.h>
#include<termios.h>
#include<stdbool.h>

void MoveLens(int addrData) {
	/*
	printf("\n iris(0 - 656)");
	printf("\n zoom(901 - 6353)");
	printf("\n focus(3608 - 6050)");
	*/
	int mode = -1;
	if (0 <= addrData && 656 >= addrData){
		mode = 0;
	}
	if (901 <= addrData && 6353 >= addrData){
		mode = 1;		
	}
	if (3608 <= addrData && 6050 >= addrData){
		mode = 2;		
	}

	switch (mode) {
	case 0:
		printf("\najusting iris(0 - 656)");
		IrisMove((uint16_t)addrData);
		break;
	case 1:
		printf("\najusting zoom(901 - 6353)");
		ZoomMove((uint16_t)addrData);
		break;
	case 2 :
		printf("\najusting focus(3608 - 6050)");
		FocusMove((uint16_t)addrData);
		break;
	default:
		break;
	}
	printf("\n");
}

void UserIDRead() {
	char userName[33];
	UserAreaRead(userName);
	printf("%s\n", userName);

}
void UserIDWrite() {
	char userName[33];
	char dummy;
	printf("\nPlease fill in the user area(32byte full)\n");
	printf("12345678901234567890123456789012\n");
	scanf("%[\n]",&dummy);
	scanf("%[^\n]", userName);
	UserAreaWrite(userName);
	printf("\n");
}

void FineFocusMove(){
#define QUIT_CHAR 0x0d	// Enter key
struct termios CookedTermIos;
struct termios RawTermIos;
	tcgetattr(STDIN_FILENO, &CookedTermIos);
	RawTermIos = CookedTermIos;
	cfmakeraw(&RawTermIos);
	tcsetattr(STDIN_FILENO, 0, &RawTermIos);
	int c;
	uint16_t addrData;
	while ((c = getchar()) != QUIT_CHAR) {
		switch(c) {
		case 'z':
			addrData = focusCurrentAddr + fineNum;
			LimFocusMove(addrData);
			break;
		case 'x':
			addrData = focusCurrentAddr - fineNum;
			LimFocusMove(addrData);
			break;
		default :
			break;
		}
	}
	printf("\r\nEnd fine move focus mode\n");
	tcsetattr(STDIN_FILENO, 0, &CookedTermIos);
	putchar('\n');
}

void LimFocusMove(uint16_t addrData) {
	if ((focusMaxAddr >= addrData) & (addrData >= focusMinAddr)){
		int retval = FocusMove(addrData);
		if (retval == SUCCESS)
			printf("\rAddr= %d", focusCurrentAddr);
	} else {
		printf("\rLimit      ");
	}
}	

