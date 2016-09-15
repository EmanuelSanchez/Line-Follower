//Matrix_SPI_Test.ino
// Bus Spi = 4Mhz
// Spi mode = 0 or 3
// MSB first


#include <SPI.h>  // include the new SPI library:


// using two incompatible SPI devices, A and B
const int ADC_chip_1 = 10;
const int ADC_chip_2 = 21;
const int ADC_chip_3 = 20;
const int EOC = 2;


// set up the speed, mode and endianness of each device (Bus at 4Mhz)
SPISettings settings(4000000, MSBFIRST, SPI_MODE0);

  // Configuration Registers
uint8_t  Averaging_REG = 0b00100000; //No Averaging and no scanning
uint8_t  Setup_REG     = 0b01100100; //Internally timed, Ain15 as Ain15, External Reference,
uint8_t  Conversion_REG= 0b11111000; //Select 15 channels, convert all from 0 to 15.
uint8_t  Reset_REG     = 0b00011000; // Clear FIFO

uint8_t  Output_ADC1[] ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint8_t  Output_ADC2[] ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint8_t  Output_ADC3[] ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint8_t  ADC1_Results[] ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint8_t  ADC2_Results[] ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint8_t  ADC3_Results[] ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

uint8_t Matrix_Result[][7] = {{0,0,0,0,0,0,0}, {0,0,0,0,0,0,0}, {0,0,0,0,0,0,0}, {0,0,0,0,0,0,0}, {0,0,0,0,0,0,0}, {0,0,0,0,0,0,0}, {0,0,0,0,0,0,0}};



void setup() {
  // set the Slave Select Pins as outputs:
  pinMode (ADC_chip_1, OUTPUT);
  pinMode (ADC_chip_2, OUTPUT);
  pinMode (ADC_chip_3, OUTPUT);
  // initialize SPI:
  Serial.begin(115200);
  SPI.begin();

}

uint8_t ignored;

void loop() {

  // Start Conversion on ADC 1
  //SPI.beginTransaction(settings);
  SPI.setClockDivider(4000000);	//clk a 9 MHz, max: 4MHz
  SPI.setBitOrder(MSBFIRST);		//los comandos deben ser Most Significant Bit First
  SPI.setDataMode(SPI_MODE0);		//polaridad y fase del clk modo 00 
  digitalWrite (ADC_chip_1, LOW);
  // Configure and start conversion
  SPI.transfer(Averaging_REG);
  SPI.transfer(Setup_REG);
  SPI.transfer(Conversion_REG);
  digitalWrite (ADC_chip_1, HIGH);
  SPI.endTransaction();

  // Start Conversion on ADC 2
  SPI.beginTransaction(settings);
  digitalWrite (ADC_chip_2, LOW);
  // Configure and start conversion
  SPI.transfer(Averaging_REG);
  SPI.transfer(Setup_REG);
  SPI.transfer(Conversion_REG);
  digitalWrite (ADC_chip_2, HIGH);
  SPI.endTransaction();

  // Start Conversion on ADC 3
  SPI.beginTransaction(settings);
  digitalWrite (ADC_chip_3, LOW);
  // Configure and start conversion
  SPI.transfer(Averaging_REG);
  SPI.transfer(Setup_REG);
  SPI.transfer(Conversion_REG);
  digitalWrite (ADC_chip_3, HIGH);
  SPI.endTransaction();

  // Wait for the conversion to finish
  while(digitalRead(EOC));


  //Read Results ADC1
  SPI.beginTransaction(settings);
  digitalWrite (ADC_chip_1, LOW);
  // Read FIFO
  for(int i=0; i<32; i++){
    Output_ADC1[i] = SPI.transfer(0);
  }
  digitalWrite (ADC_chip_1, HIGH);
  SPI.endTransaction();


  //Read Results ADC2
  SPI.beginTransaction(settings);
  digitalWrite (ADC_chip_2, LOW);
  // Read FIFO
  for(int i=0; i<32; i++){
    Output_ADC2[i] = SPI.transfer(0);
  }
  digitalWrite (ADC_chip_2, HIGH);
  SPI.endTransaction();


  //Read Results ADC3
  SPI.beginTransaction(settings);
  digitalWrite (ADC_chip_3, LOW);
  // Read FIFO
  for(int i=0; i<32; i++){
    Output_ADC3[i] = SPI.transfer(0);
  }
  digitalWrite (ADC_chip_3, HIGH);
  SPI.endTransaction();


// Order Results of each ADC
for(int i=0; i<16; i++){

    ADC1_Results[i] = ((Output_ADC1[2*i] & 0x0F) << 4) | ((Output_ADC1[2*i + 1] & 0xF0) >> 4); // Join bytes of FIFO to form answer
    ADC2_Results[i] = ((Output_ADC2[2*i] & 0x0F) << 4) | ((Output_ADC2[2*i + 1] & 0xF0) >> 4); // Join bytes of FIFO to form answer
    ADC3_Results[i] = ((Output_ADC3[2*i] & 0x0F) << 4) | ((Output_ADC3[2*i + 1] & 0xF0) >> 4); // Join bytes of FIFO to form answer
}


// Order the results in a matrix format
    Matrix_Result[0][0] = ADC1_Results[15];
    Matrix_Result[0][1] = ADC1_Results[8];
    Matrix_Result[0][2] = ADC1_Results[1];
    Matrix_Result[0][3] = ADC2_Results[10];
    Matrix_Result[0][4] = ADC2_Results[3];
    Matrix_Result[0][5] = ADC3_Results[12];
    Matrix_Result[0][6] = ADC3_Results[5];

    Matrix_Result[1][0] = ADC1_Results[14];
    Matrix_Result[1][1] = ADC1_Results[7];
    Matrix_Result[1][2] = ADC1_Results[0];
    Matrix_Result[1][3] = ADC2_Results[9];
    Matrix_Result[1][4] = ADC2_Results[2];
    Matrix_Result[1][5] = ADC3_Results[11];
    Matrix_Result[1][6] = ADC3_Results[4];

    Matrix_Result[2][0] = ADC1_Results[13];
    Matrix_Result[2][1] = ADC1_Results[6];
    Matrix_Result[2][2] = ADC2_Results[15];
    Matrix_Result[2][3] = ADC2_Results[8];
    Matrix_Result[2][4] = ADC2_Results[1];
    Matrix_Result[2][5] = ADC3_Results[10];
    Matrix_Result[2][6] = ADC3_Results[3];

    Matrix_Result[3][0] = ADC1_Results[12];
    Matrix_Result[3][1] = ADC1_Results[5];
    Matrix_Result[3][2] = ADC2_Results[14];
    Matrix_Result[3][3] = ADC2_Results[7];
    Matrix_Result[3][4] = ADC2_Results[0];
    Matrix_Result[3][5] = ADC3_Results[9];
    Matrix_Result[3][6] = ADC3_Results[2];

    Matrix_Result[4][0] = ADC1_Results[11];
    Matrix_Result[4][1] = ADC1_Results[4];
    Matrix_Result[4][2] = ADC2_Results[13];
    Matrix_Result[4][3] = ADC2_Results[6];
    Matrix_Result[4][4] = ADC3_Results[15];
    Matrix_Result[4][5] = ADC3_Results[8];
    Matrix_Result[4][6] = ADC3_Results[1];

    Matrix_Result[5][0] = ADC1_Results[10];
    Matrix_Result[5][1] = ADC1_Results[3];
    Matrix_Result[5][2] = ADC2_Results[12];
    Matrix_Result[5][3] = ADC2_Results[5];
    Matrix_Result[5][4] = ADC3_Results[14];
    Matrix_Result[5][5] = ADC3_Results[7];
    Matrix_Result[5][6] = ADC3_Results[0];

    Matrix_Result[6][0] = ADC1_Results[9];
    Matrix_Result[6][1] = ADC1_Results[2];
    Matrix_Result[6][2] = ADC2_Results[11];
    Matrix_Result[6][3] = ADC2_Results[4];
    Matrix_Result[6][4] = ADC3_Results[13];
    Matrix_Result[6][5] = ADC3_Results[6];
    Matrix_Result[6][6] = 0;




  // Print Result
 
 Serial.print("begin\n");
  for(int i=0; i<7; i++){
    for(int j=0; j<7; j++){
        
        Serial.print(Matrix_Result[i][j]);
        Serial.print(" ");

    }
    //Serial.print("\n");
  }

}

