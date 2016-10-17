//Matriz Sensors Adquisition

#include "SPI.h"
#include "SoftwareSerial.h"


//--------------------------------
// EOC	CS3	CS2	CS1	DIN	 DOUT CLOCK
//				    MOSI MISO SCK
// 2 	3	6	7	11 	 12	  13
//--------------------------------

#define	setup_reg		01100100
#define	averaging_reg 	00100000
#define converter_reg	11111000

const int slave1 = 7;
const int slave2 = 6;
const int slave3 = 3;
const int eoc = 2;
const int mosi = 11;
const int miso = 12;
const int clock = 13;

float ready;
int   data0;
int   data1;
int   data2;

void setup() {
	pinMode(eoc, INPUT);
	pinMode(slave1, OUTPUT);
	pinMode(slave2, OUTPUT);
	pinMode(slave3, OUTPUT);
	pinMode(mosi, OUTPUT);
	pinMode(miso, INPUT);
	pinMode(clock, OUTPUT);

	Serial.begin(57600);
	Serial.println("Hello Emanuel");

	digitalWrite(slave1, HIGH);
	digitalWrite(slave2, HIGH);
	digitalWrite(slave3, HIGH);

	//configuracion de la comunicacion por SPI
	SPI.begin();
	SPI.setClockDivider(9000000);	//clk a 9 MHz, max: 10MHz
	SPI.setBitOrder(MSBFIRST);		//los comandos deben ser Most Significant Bit First
	SPI.setDataMode(SPI_MODE0);		//polaridad y fase del clk modo 00

	//activo los slaves para iniciar la solicitud de datos
	digitalWrite(slave1, LOW);
	digitalWrite(slave2, HIGH);
	digitalWrite(slave3, HIGH);

	//configuracion de los registros de los ADCs
	SPI.transfer(setup_reg);
	SPI.transfer(averaging_reg);

	//inicio la conversion
	SPI.transfer(converter_reg);	//Converter Register
	//Serial.write(SPI.transfer(converter_reg));

	digitalWrite(slave1, HIGH);
	digitalWrite(slave2, HIGH);
	digitalWrite(slave3, HIGH);
/*
	//activo los slaves para iniciar la solicitud de datos
	digitalWrite(slave1, HIGH);
	digitalWrite(slave2, LOW);
	digitalWrite(slave3, HIGH);

	//configuracion de los registros de los ADCs
	SPI.transfer(setup_reg);
	SPI.transfer(averaging_reg);

	//inicio la conversion
	SPI.transfer(converter_reg);	//Converter Register
	//Serial.write(SPI.transfer(converter_reg));

	digitalWrite(slave1, HIGH);
	digitalWrite(slave2, HIGH);
	digitalWrite(slave3, HIGH);

	//activo los slaves para iniciar la solicitud de datos
	digitalWrite(slave1, HIGH);
	digitalWrite(slave2, HIGH);
	digitalWrite(slave3, LOW);

	//configuracion de los registros de los ADCs
	SPI.transfer(setup_reg);
	SPI.transfer(averaging_reg);

	//inicio la conversion
	SPI.transfer(converter_reg);	//Converter Register
	//Serial.write(SPI.transfer(converter_reg));

	digitalWrite(slave1, HIGH);
	digitalWrite(slave2, HIGH);
	digitalWrite(slave3, HIGH);

	if(digitalRead(eoc)==LOW)
		Serial.write("LISTO");
*/
	delay(1000);

	digitalWrite(slave1, LOW);
	digitalWrite(slave2, HIGH);
	digitalWrite(slave3, HIGH);


/*
	digitalWrite(slave1, HIGH);
	digitalWrite(slave2, LOW);
	digitalWrite(slave3, HIGH);

	digitalWrite(slave1, HIGH);
	digitalWrite(slave2, HIGH);
	digitalWrite(slave3, LOW);
*/	
}

void loop() {

	//data0 = SPI.transfer(0x00);

	//if (data0!=NULL)
	Serial.write(SPI.transfer(0x00));

	//Serial.write(digitalRead(miso));

	//if(digitalRead(eoc)==LOW)
	//	Serial.write("LISTO");
	
	//Serial.write(SPI.transfer(0));

}

