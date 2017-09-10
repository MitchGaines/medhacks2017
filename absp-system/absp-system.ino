#define inf_ul 22 //inflate upper left
#define inf_ll 23 //inflate lower left
#define inf_ur 24 //inflate upper right
#define inf_lr 25 //inflate lower right

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

void setup() {
  Serial.begin(9600);
  
  // set inflatables to output pins
  pinMode(inf_ul, OUTPUT);  
  pinMode(inf_ll, OUTPUT);  
  pinMode(inf_ur, OUTPUT);  
  pinMode(inf_lr, OUTPUT);  

}

void loop() {
  Serial.println("test");
  delay(1000); //loops once every second
}

/*
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
*/



