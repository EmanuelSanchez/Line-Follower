/**
* @Author: emanuel
* @Date:   2016-10-12T22:19:16-04:00
@Last modified by:   emanuel
@Last modified time: 2016-10-16T03:22:39-04:00
*
* @Description: Proof the Software
*   Run in forward line and read the sensor matriz
*
*/

#include <SPI.h>  // include the new SPI library:


/************************  Important Variables: ************************/

const int pwm_velocity = 30;  // 0-255 velocity

/************************  Pins Configurations: ************************/
// Motors:
const int motorL_en = 3;      // violet wire
const int motorL_phase = 2;   // blue wire
const int motorR_en = 4;      // violet wire
const int motorR_phase = 5;   // blue wire

// Encoders
const int encoderL_A = 23;  //orange wire
const int encoderL_B = 22;  //yellow wire
const int encoderR_A = 15;  //oran ge wire
const int encoderR_B = 16;  //yellow wire

// using two incompatible SPI devices, A and B
const int ADC_chip_1 = 10;
const int ADC_chip_2 = 21;
const int ADC_chip_3 = 20;
const int EOC = 1;

/************************  SPI configurations: ************************/
// Bus Spi = 4Mhz
// Spi mode = 0 or 3
// MSB first

// set up the speed, mode and endianness of each device (Bus at 4Mhz)
SPISettings settings(4000000, MSBFIRST, SPI_MODE0);

// Configuration Registers
uint8_t  Averaging_REG = 0b00100000; //No Averaging and no scanning
uint8_t  Setup_REG     = 0b01100100; //Internally timed, Ain15 as Ain15, External Reference,
uint8_t  Conversion_REG= 0b11111000; //Select 15 channels, convert all from 0 to 15.
uint8_t  Reset_REG     = 0b00011000; // Clear FIFO

/************************  Auxiliar Variables: ************************/
// Endoders ticks
uint8_t tick_L = 0;
uint8_t tick_R = 0;

// SPI:
uint8_t  Output_ADC1[] ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint8_t  Output_ADC2[] ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint8_t  Output_ADC3[] ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint8_t  ADC1_Results[] ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint8_t  ADC2_Results[] ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint8_t  ADC3_Results[] ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

uint8_t Matrix_Result[][7] = {{0,0,0,0,0,0,0}, {0,0,0,0,0,0,0}, {0,0,0,0,0,0,0}, {0,0,0,0,0,0,0}, {0,0,0,0,0,0,0}, {0,0,0,0,0,0,0}, {0,0,0,0,0,0,0}};

/************************  Interrupts Routines for Encoders  ************************/

// Left Encoder
void count_L(){
  tick_L++;
  //Serial.println();
  //Serial.print("Left: ");
  //Serial.println(tick_L);
}

// Right Encoder
void count_R(){
  tick_R++;
  //Serial.println();
  //Serial.print("Right: ");
  //Serial.println(tick_R);
}

/************************  Conversion from ADC  ************************/

void conversion(const int chip){
  // Start Conversion on ADC
  SPI.beginTransaction(settings);
  digitalWriteFast (chip, LOW);
  // Configure and start conversion
  SPI.transfer(Averaging_REG);
  SPI.transfer(Setup_REG);
  SPI.transfer(Conversion_REG);
  digitalWriteFast (chip, HIGH);
  SPI.endTransaction();
}

/************************  Read results from ADC  ************************/
// one function by ADC


void read_results1(const int chip){

  //Read Results ADC
  SPI.beginTransaction(settings);
  digitalWriteFast (chip, LOW);
  // Read FIFO
  for(int i=0; i<32; i++){
    Output_ADC1[i] = SPI.transfer(0);
  }
  digitalWriteFast (chip, HIGH);
  SPI.endTransaction();
}

void read_results2(const int chip){

  //Read Results ADC
  SPI.beginTransaction(settings);
  digitalWriteFast (chip, LOW);
  // Read FIFO
  for(int i=0; i<32; i++){
    Output_ADC2[i] = SPI.transfer(0);
  }
  digitalWriteFast (chip, HIGH);
  SPI.endTransaction();
}

void read_results3(const int chip){

  //Read Results ADC
  SPI.beginTransaction(settings);
  digitalWriteFast (chip, LOW);
  // Read FIFO
  for(int i=0; i<32; i++){
    Output_ADC3[i] = SPI.transfer(0);
  }
  digitalWriteFast (chip, HIGH);
  SPI.endTransaction();
}

void order_results(){

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
}

/************************  Print by serial functions  ************************/


void print_first_line(){

  // Print Result of the first line by serial
  Serial.println("\nMatrix:");
  for(int i=0; i<7; i++){
      Serial.print(Matrix_Result[0][i]);
      Serial.print("\t");
  }
  Serial.print("\n");
}

void print_matrix(){

  // Print Result of all matrix
  Serial.println("Matrix");
  for(int i=0; i<7; i++){
    for(int j=0; j<7; j++){

        Serial.print(Matrix_Result[i][j]);
        Serial.print("\t");

    }
    Serial.print("\n");
  }

}

//
/************************  SETUP FUNCTION  ************************/
//

void setup() {

  // set the Slave Select Pins as outputs:
  pinMode (ADC_chip_1, OUTPUT);
  pinMode (ADC_chip_2, OUTPUT);
  pinMode (ADC_chip_3, OUTPUT);

  //motors: pinout configuration
  pinMode(motorL_en, OUTPUT);
  pinMode(motorL_phase, OUTPUT);
  pinMode(motorR_en, OUTPUT);
  pinMode(motorR_phase, OUTPUT);

  //encoders: pinout configuration
  pinMode(encoderL_A, INPUT);
  pinMode(encoderL_B, INPUT);
  pinMode(encoderR_A, INPUT);
  pinMode(encoderR_B, INPUT);

  // motors: direction
  digitalWriteFast(motorL_phase, HIGH);
  digitalWriteFast(motorR_phase, HIGH);

  // Interrupt configuration for encoders
  attachInterrupt(digitalPinToInterrupt(encoderR_A), count_R, RISING);
  attachInterrupt(digitalPinToInterrupt(encoderL_A), count_L, RISING);

  // initialize SPI and Serial:
  Serial.begin(115200);
  SPI.begin();

  // wait 2 seconds to initiate movement
  delay(2000);

  // motors: set velocity/initiate movement
  analogWrite(motorL_en, pwm_velocity);
  analogWrite(motorR_en, pwm_velocity);

}

//
/************************  LOOP FUNCTION  ************************/
//

void loop() {

  // Start the conversion on each ADC
  conversion(ADC_chip_1);
  conversion(ADC_chip_2);
  conversion(ADC_chip_3);

  // Wait for the conversion to finish
  while(digitalReadFast(EOC));

  // Read result from each ADC
  read_results1(ADC_chip_1);
  read_results2(ADC_chip_2);
  read_results3(ADC_chip_3);

  // Order Results of each ADC
  for(int i=0; i<16; i++){
      ADC1_Results[i] = ((Output_ADC1[2*i] & 0x0F) << 4) | ((Output_ADC1[2*i + 1] & 0xF0) >> 4); // Join bytes of FIFO to form answer
      ADC2_Results[i] = ((Output_ADC2[2*i] & 0x0F) << 4) | ((Output_ADC2[2*i + 1] & 0xF0) >> 4); // Join bytes of FIFO to form answer
      ADC3_Results[i] = ((Output_ADC3[2*i] & 0x0F) << 4) | ((Output_ADC3[2*i + 1] & 0xF0) >> 4); // Join bytes of FIFO to form answer
  }

  // Order all results in a matrix
  order_results();

  print_matrix();

}
