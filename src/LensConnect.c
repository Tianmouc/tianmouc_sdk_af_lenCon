#include"LensCtrl.h"
#include"LensConnect.h"
#include<stdbool.h>


int ItemNum;
int detailSelect;
int fineNum;
BOOL USBOpen_flag = FALSE;
BOOL withZoom = FALSE;
BOOL withFocus = FALSE;
BOOL withIris = FALSE;
BOOL withOptFil = FALSE;


const char* OnOff(uint16_t flag) {
	if (flag == 1)
		return "ON";
	else
		return "OFF";
}

void ScanUSBLensInfo() {
	DWORD numDevices = 0;
	char snString[260];	// SnString is 260bytes according to the instructions of the USB IC
	char model[25];
	UsbGetNumDevices(&numDevices);
	if (numDevices >= 1) {
		printf("No.: S/N\n");
		for (uint16_t i = 0; i < numDevices; i++) {
			int retval = UsbGetSnDevice(i, snString);
			if (retval == SUCCESS){
				printf(" %d : %s, ", i, snString);
				UsbOpen(i);
				ModelName(model);
				printf("%s, ", model);
				UserIDRead();
				UsbClose();
			} else {
				printf(" %d : %s\n", i, snString);
			}
		}
	}
	else
	{
		printf("No LensConnect is connected.\r\n");
	}
	printf("\n");
}	

void UsbConnect(int deviceNumber) {
	uint16_t capabilities;
	int retval = UsbOpen(deviceNumber);
	if (retval != SUCCESS) {
		printf("%s\n", ErrorTxt(retval));
		return;
	}
	retval = UsbSetConfig();
	if (retval != SUCCESS) {
		printf("%s\n", ErrorTxt(retval));
		return;
	}
	printf("opened\r\n");
	CapabilitiesRead(&capabilities);
	Status2ReadSet();

	if (capabilities & ZOOM_MASK) {
		ZoomParameterReadSet();
		if ((status2 & ZOOM_MASK) == INIT_COMPLETED)
			ZoomCurrentAddrReadSet();
		withZoom = TRUE;
	}
	if (capabilities & FOCUS_MASK) {
		FocusParameterReadSet();
		if ((status2 & FOCUS_MASK) == INIT_COMPLETED)
			FocusCurrentAddrReadSet();
		withFocus = TRUE;
	}
	if (capabilities & IRIS_MASK) {
		IrisParameterReadSet();
		if ((status2 & IRIS_MASK) == INIT_COMPLETED)
			IrisCurrentAddrReadSet();
		withIris = TRUE;
	}
	if (capabilities & OPT_FILTER_MASK) {
		OptFilterParameterReadSet();
		if ((status2 & OPT_FILTER_MASK) == INIT_COMPLETED)
			OptFilterCurrentAddrReadSet();
		withOptFil = TRUE;
	}
	USBOpen_flag = TRUE;
}

void UsbDisconnect(){
	UsbClose();
	USBOpen_flag = FALSE;
	withZoom = FALSE;
	withFocus = FALSE;
	withIris = FALSE;
	withOptFil = FALSE;
}



int init_lens(){
	int number = 0;
	ItemNum = MAIN;
	fineNum = 2;
	bool INIT = true;
	printf("LensConnect Control %s\n", PROGRAM_VERSION);
	while (TRUE)
	{
		if (USBOpen_flag == false) {			
			ScanUSBLensInfo();
			UsbConnect(number);
		}
		else {		
			if(INIT){
				printf("Initializing zoom\n");
				ZoomInit();	
				printf("Initializing fouces\n");
				FocusInit();			
				printf("Initializing iris\n");
				IrisInit();				
				printf("\n iris(0 - 656),DEFAULT_IRIS = 10");
				printf("\n zoom(901 - 6353),DEFAULT_ZOOM = 1000");
				printf("\n focus(3608 - 6050),DEFAULT_FOCUS = 4200");
				INIT = false;
			}
			else{
				break;
			}
		}
	}
	return 0;
}