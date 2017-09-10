#include <QueueArray.h>

#define leg_lll 2 //leg left lower left
#define leg_llm 3 //leg left lower middle
#define leg_llr 4 //leg left lower right
#define leg_lml 5 //leg left middle left
#define leg_lmm 6 //leg left middle middle
#define leg_lmr 7 //leg left middle right
#define leg_lul 8 //leg left upper left
#define leg_lum 9 //leg left upper middle
#define leg_lur 10 //leg left upper right

#define leg_rll 11 //leg right lower left
#define leg_rlm 12 //leg right lower middle
#define leg_rlr 13 //leg right lower right
#define leg_rml 14 //leg right middle left
#define leg_rmm 15 //leg right middle middle
#define leg_rmr 16 //leg right middle right
#define leg_rul 17 //leg right upper left
#define leg_rum 18 //leg right upper middle
#define leg_rur 19 //leg right upper right

#define inf_ul 20 //inflate upper left
#define inf_ll 21 //inflate lower left
#define inf_ur 22 //inflate upper right
#define inf_lr 23 //inflate lower right

const int pm_columns = 6;
const int pm_rows = 3;
int pressure_matrix[pm_rows][pm_columns];
int reaction_time = 10; // 10 seconds of high pressure before alleviation action is taken
QueueArray <int> pressure_queue;

// 32 mfg is max pressure that can be experienced before pressure ulcers begin to form
/*
 * pressure matrix following this diagram with 
 * LUL->[0][0] and RLR->[2][5]
 * 
 *   LUL|LUM|LUR     RUL|RUM|RUR
 *      |   |           |   |
 *      |UL |           |UR |
 *      |   |           |   |
 *   LML|LMM|LMR     RML|RMM|RMR
 *      |   |           |   | 
 *      |LL |           |LR |
 *      |   |           |   |
 *   LLL|LLM|LLR     RLL|RLM|RLR
 *  __ /    |           |    \___
 * |________|           |________|
 */

void printPM(){
  Serial.write("LUL: " + pressure_matrix[0][0]);
  delay(50);
  Serial.write("LUM: " + pressure_matrix[0][1]);  
  delay(50);
  Serial.write("LUR: " + pressure_matrix[0][2]);
  delay(50);
  Serial.write("RUL: " + pressure_matrix[0][3]);
  delay(50);
  Serial.write("RUM: " + pressure_matrix[0][4]); 
  delay(50); 
  Serial.write("RUR: " + pressure_matrix[0][5]);
  delay(50);

  Serial.write("LML: " + pressure_matrix[1][0]);
  delay(50);
  Serial.write("LMM: " + pressure_matrix[1][1]);
  delay(50);  
  Serial.write("LMR: " + pressure_matrix[1][2]);
  delay(50);
  Serial.write("RML: " + pressure_matrix[1][3]);
  delay(50);
  Serial.write("RMM: " + pressure_matrix[1][4]);
  delay(50);  
  Serial.write("RMR: " + pressure_matrix[1][5]);
  delay(50);

  Serial.write("LLL: " + pressure_matrix[2][0]);
  delay(50);
  Serial.write("LLM: " + pressure_matrix[2][1]);
  delay(50);  
  Serial.write("LLR: " + pressure_matrix[2][2]);
  delay(50);
  Serial.write("RLL: " + pressure_matrix[2][3]);
  delay(50);
  Serial.write("RLM: " + pressure_matrix[2][4]);  
  delay(50);
  Serial.write("RLR: " + pressure_matrix[2][5]);
}

void setup() {
  Serial.begin(9600);
  
  // set sensors as input pins
  pinMode(leg_lll, INPUT);
  pinMode(leg_llm, INPUT);
  pinMode(leg_llr, INPUT);
  pinMode(leg_lml, INPUT);
  pinMode(leg_lmm, INPUT);
  pinMode(leg_lmr, INPUT);
  pinMode(leg_lul, INPUT);
  pinMode(leg_lum, INPUT);
  pinMode(leg_lur, INPUT);
  
  pinMode(leg_rll, INPUT);
  pinMode(leg_rlm, INPUT);
  pinMode(leg_rlr, INPUT);
  pinMode(leg_rml, INPUT);
  pinMode(leg_rmm, INPUT);
  pinMode(leg_rmr, INPUT);
  pinMode(leg_rul, INPUT);
  pinMode(leg_rum, INPUT);
  pinMode(leg_rur, INPUT);
  
  // set inflatables to output pins
  pinMode(inf_ul, OUTPUT);  
  pinMode(inf_ll, OUTPUT);  
  pinMode(inf_ur, OUTPUT);  
  pinMode(inf_lr, OUTPUT);  

  // initializing pressure matrix values
  for (int i =0; i < pm_rows; i++) {
    for (int j =0; j < pm_columns; j++) {
      pressure_matrix[i][j] = 0;
    }
  }
}

void loop() {
  readPressurePins();
  setPressureMatrix();
  printPM();
  delay(1000); //loops once every second
}


void setPressureMatrix(){
  for(int i = 0; i < pressure_queue.count(); i++){

      //first row
      if(pressure_queue.peek() == leg_lul) {
        pressure_queue.pop();
        if(pressure_matrix[0][0]++ >= reaction_time){
            inflate(inf_ul);
        }
      }
      if(pressure_queue.peek() == leg_lum) {
        pressure_queue.pop();
        if(pressure_matrix[0][1]++ >= reaction_time){
            inflate(inf_ul);
        } 
      }
      if(pressure_queue.peek() == leg_lur) {
        pressure_queue.pop();
        if(pressure_matrix[0][2]++ >= reaction_time){
            inflate(inf_ul);
        }  
      }
      if(pressure_queue.peek() == leg_rul) {
        pressure_queue.pop();
        if(pressure_matrix[0][3]++ >= reaction_time){
            inflate(inf_ur);
        }  
      }
      if(pressure_queue.peek() == leg_rum) {
        pressure_queue.pop();
        if(pressure_matrix[0][4]++ >= reaction_time){
            inflate(inf_ur);
        }    
      }
      if(pressure_queue.peek() == leg_rur) {
        pressure_queue.pop();
        if(pressure_matrix[0][5]++ >= reaction_time){
            inflate(inf_ur);
        }  
      }


      //second row
      if(pressure_queue.peek() == leg_lml) {
        pressure_queue.pop();
        if(pressure_matrix[1][0]++ >= reaction_time){
           inflate(inf_ll);
        }   
      }
      if(pressure_queue.peek() == leg_lmm) {
        pressure_queue.pop();
        if(pressure_matrix[1][1]++ >= reaction_time){
           inflate(inf_ll);
        }   
      }
      if(pressure_queue.peek() == leg_lmr) {
        pressure_queue.pop();
        if(pressure_matrix[1][2]++ >= reaction_time){
           inflate(inf_ll);
        }   
      }
      if(pressure_queue.peek() == leg_rml) {
        pressure_queue.pop();
        if(pressure_matrix[1][3]++ >= reaction_time){
           inflate(inf_lr);
        }    
      }
      if(pressure_queue.peek() == leg_rmm) {
        pressure_queue.pop();
        if(pressure_matrix[1][4]++ >= reaction_time){
           inflate(inf_lr);
        }     
      }
      if(pressure_queue.peek() == leg_rmr) {
        pressure_queue.pop();
        if(pressure_matrix[1][5]++ >= reaction_time){
           inflate(inf_lr);
        }     
      }

      //third row
      if(pressure_queue.peek() == leg_lll) {
        pressure_queue.pop();
        if(pressure_matrix[2][0]++ >= reaction_time){
           inflate(inf_ll);
        }
      }
      if(pressure_queue.peek() == leg_llm) {
        pressure_queue.pop();
        if(pressure_matrix[2][1]++ >= reaction_time){
           inflate(inf_ll);
        }  
      }
      if(pressure_queue.peek() == leg_llr) {
        pressure_queue.pop();
        if(pressure_matrix[2][2]++ >= reaction_time){
           inflate(inf_ll);
        }  
      }
      if(pressure_queue.peek() == leg_rll) {
        pressure_queue.pop();
        if(pressure_matrix[2][3]++ >= reaction_time){
           inflate(inf_lr);
        }    
      }
      if(pressure_queue.peek() == leg_rlm) {
        pressure_queue.pop();
        if(pressure_matrix[2][4]++ >= reaction_time){
           inflate(inf_lr);
        }   
      }
      if(pressure_queue.peek() == leg_rlr) {
        pressure_queue.pop();
        if(pressure_matrix[2][5]++ >= reaction_time){
           inflate(inf_lr);
        }     
      }
  }  
}

void readPressurePins(){
  if(digitalRead(leg_lll)) pressure_queue.enqueue(leg_lll); 
  if(digitalRead(leg_llm)) pressure_queue.enqueue(leg_llm);
  if(digitalRead(leg_llr)) pressure_queue.enqueue(leg_llr);
  if(digitalRead(leg_lml)) pressure_queue.enqueue(leg_lml); 
  if(digitalRead(leg_lmm)) pressure_queue.enqueue(leg_lmm);
  if(digitalRead(leg_lmr)) pressure_queue.enqueue(leg_lmr);
  if(digitalRead(leg_lul)) pressure_queue.enqueue(leg_lul); 
  if(digitalRead(leg_lum)) pressure_queue.enqueue(leg_lum);
  if(digitalRead(leg_lur)) pressure_queue.enqueue(leg_lur);

  if(digitalRead(leg_rll)) pressure_queue.enqueue(leg_rll);
  if(digitalRead(leg_rlm)) pressure_queue.enqueue(leg_rlm); 
  if(digitalRead(leg_rlr)) pressure_queue.enqueue(leg_rlr);
  if(digitalRead(leg_rml)) pressure_queue.enqueue(leg_rml); 
  if(digitalRead(leg_rmm)) pressure_queue.enqueue(leg_rmm);
  if(digitalRead(leg_rmr)) pressure_queue.enqueue(leg_rmr);
  if(digitalRead(leg_rul)) pressure_queue.enqueue(leg_rul); 
  if(digitalRead(leg_rum)) pressure_queue.enqueue(leg_rum);
  if(digitalRead(leg_rur)) pressure_queue.enqueue(leg_rur);
}

void inflate(int port){
   if(port == inf_ll){
     // inflating lower left
     
    digitalWrite(inf_ll, HIGH);
    pressure_matrix[1][0] = 0;
    pressure_matrix[1][1] = 0;
    pressure_matrix[1][2] = 0;
    pressure_matrix[2][0] = 0;
    pressure_matrix[2][1] = 0;
    pressure_matrix[2][2] = 0;
   } else if(port == inf_lr){
    // inflating lower right
    
    digitalWrite(inf_lr, HIGH);
    pressure_matrix[1][3] = 0;
    pressure_matrix[1][4] = 0;
    pressure_matrix[1][5] = 0;
    pressure_matrix[2][3] = 0;
    pressure_matrix[2][4] = 0;
    pressure_matrix[2][5] = 0;
   } else if(port == inf_ul){
    // inflating upper left
    
    digitalWrite(inf_ul, HIGH);
    pressure_matrix[0][0] = 0;
    pressure_matrix[0][1] = 0;
    pressure_matrix[0][2] = 0;
   } else if(port == inf_ur){
     // inflating upper right
     
    digitalWrite(inf_ur, HIGH);
    pressure_matrix[0][3] = 0;
    pressure_matrix[0][4] = 0;
    pressure_matrix[0][5] = 0;
   }
}






