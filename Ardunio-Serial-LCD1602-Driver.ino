// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
int incomingByte = 0; // for incoming serial data
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


const int Array_Size = 32;
const int Display_Size = 16;

char firstline[Array_Size];
char secline[Array_Size];

bool newData = true;
bool swap = true;

short unsigned int ndx = 0;

void setup() {
	// set up the LCD's number of columns and rows:
	Serial.begin(115200);
	lcd.begin(16, 2);


}


void loop() { 
//Make sure that the line that is newest is first
	if (swap){ 
		recvWithEndMarker(firstline);
		showNewData(secline,firstline);
	}
	else{ 
		recvWithEndMarker(secline);
		showNewData(firstline,secline);
	}

}

void recvWithEndMarker(char *ar) {
	char rc;
	while (Serial.available() > 0 && newData == false) {
	rc = Serial.read();
	if (rc != '\n') {
		 ar[ndx] = rc;
		 ndx++;
		 if (ndx >= Array_Size) {
		ndx = Array_Size - 1;
		 }
	}
	else {
	ar[ndx] = '\0'; // terminate the string
	ndx = 0;
	newData = true;
	swap = !swap;
	}
	}
}




void showNewData(char *fr,char *sc){
	if (newData == true) {
	lcd.clear();
		 
	char frstorage[Display_Size] = "                ";
	char scstorage[Display_Size] = "                ";
		 
	char *storpoint = frstorage;
	char *arrpoint = fr;
	char *increment = sc;
		 
	while (*storpoint){
		*storpoint = *arrpoint;
		storpoint++;
		arrpoint++;
		 }
	


	storpoint = scstorage;
	arrpoint = sc;
		 

	while (*increment){
		while(*storpoint) {
			*storpoint = *arrpoint;
			arrpoint++;
			storpoint++;
		}
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print(frstorage);
	lcd.setCursor(0,1);
	lcd.print(scstorage);
	storpoint = scstorage;
	arrpoint = increment;
	increment++;
	delay(500);
	} 
	
	newData = false;

	}
}
