//Prueba de Motores: Line Follower


// PIN ASIGNATIONS

// motor right:
//    enable - 0
//    phase  - 1
// motor left:
//    enable - 8
//    phase  - 9

const int motor_r_en = 0;
const int motor_r_ph = 1;
const int motor_l_en = 8;
const int motor_l_ph = 9;

void setup()
{
  pinMode(motor_l_en, OUTPUT);
  pinMode(motor_l_ph, OUTPUT);
  pinMode(motor_r_en, OUTPUT);
  pinMode(motor_r_ph, OUTPUT);

  digitalWrite(motor_r_en, HIGH);
  digitalWrite(motor_l_en, HIGH);
}

void loop()
{
  
}
