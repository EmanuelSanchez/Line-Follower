// Control Robot Velocista

#define kp 10 
#define ki 10
#define kd 1

#define enc1 2    //encoder izquierdo
#define enc2 3    //encoder derecho

#define pi 3,1416

//motor izquierdo
float e1_last = 0;
float e1_suma  = 0;     //suma de error
float vel1;        //velocidad deseada
float vel1_in;     //velocidad real
float vel1_out;    //salida del control

//motor derecho
float e2_last = 0;
float e2_suma = 0;     //suma de error
float vel2;        //velocidad deseada
float vel2_in;     //velocidad real
float vel2_out;    //salida del control

float read_encoders (float *vel1_in, float *vel2_in){
  //lee los encoders para determinar la velocidad actual de los motores 

}

void pid_calc_motor1 () {
  // Calculo del PID
  float e_now;      //error actual
  float e_dif;      //derivada del error

  e_now = vel1 - vel1_in;
  e_dif = e_now - e1_last;
  e1_suma += e_now;

  vel1_out = (kp * e_now) + (ki * e1_suma) + (kd * e_dif);
  
  e1_last = e_now;
}

void pid_calc_motor2 () {
  // Calculo del PID
  float e_now;      //error actual
  float e_dif;      //derivada del error

  e_now = vel2 - vel1_in;
  e_dif = e_now - e2_last;
  e2_suma += e_now;

  vel2_out = (kp * e_now) + (ki * e2_suma) + (kd * e_dif);
  
  e2_last = e_now;
}

void setup() {
  pinMode (enc1, INPUT);
  pinMode (enc2, INPUT);
}

void loop() {
  read_encoders(&vel1_in, &vel2_in);
  pid_calc_motor1();
  pid_calc_motor2();
}