/*code Telegraphe de Chappe
 * creation 10/08/2019 
 * But de ce code Recevoir via une liaison terminal 
 * 
 * pin D8 servo du regulateur
 * Pin D6 servo indicateur Droit
 * Pin D7 Servo indcateur Gauche
 * 
 * Via Terminal ou liaison serie reception d'un code de 1 a 92 qui correspond a une position definie
 *   
 * 
 */




#include <Servo.h>
#include <stdlib.h>  /* pour utiliser strtol */

String inputString = " ";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

const byte positions[]={0,6,1,8,48,5,2,16,40,4,3,24,32,14,49,22,41,30,33,54,9,46,17,38,25,12,51,20,43,28,35,52,11,44,19,36,27,13,50,21,42,29,34,53,10,37,26,112,72,65,70,104,80,66,69,96,88,67,68,113,78,114,77,115,76,118,73,117,74,116,75,97,94,98,93,99,92,102,89,101,90,100,91,105,86,106,85,107,84,110,81,108,83};
const int angle[]={0,45,90,135,180,225,270,315};
const int angle_Reg[]={0,45,90};
int reg_pos;
int indic_G_pos;
int indic_D_pos;


Servo serv_reg; //creation objetc pour le servo indicator
Servo serv_indic_G; //Crea object pour le servo inducateur gauche
Servo serv_indic_D; //crea obj servo indicator Droite
  
// twelve servo objects can be created on most boards

String pos =" ";    // variable to store the servo position

void setup() {
  // attaches les pin des servo 
  
  serv_reg.attach(8); 
  serv_indic_G.attach(7);
  serv_indic_D.attach(6);

  // init du serial 
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() {

/* desactiver tmp
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
*/
 // print the string when a newline arrives:
  if (stringComplete) {
    Serial.println(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true; // print the string when a newline arrives:
  if (stringComplete) {

    // on recupere l'index via terminal et on sort du tableau la position 
   
    //byte val=107; //test


    // convertion des Strings en Byte
    
    String maValeur =inputString;
    long maValeurNumerique = strtol(maValeur.c_str(), NULL, 8);
    Serial.print("valeur convertie:");
    Serial.println(maValeurNumerique);
    
    byte val=positions [maValeurNumerique];

    // de la position on determine pour chaque element 

    reg_pos=(val>>6)&1;     // position du regulateur
    indic_G_pos=(val>>3)&7; // pos de l'indicateur G
    indic_D_pos=val&7;      // pos de l'indicateur D


    Serial.print("input :");
    Serial.println(inputString);
   
    Serial.print("Reception code/index :");
    Serial.println(val);

    Serial.println("-------");
    
    Serial.print("regulateur :");
    Serial.println(reg_pos);
 
    Serial.print("indicateur G :");
    Serial.println(indic_G_pos);

    Serial.print("indicateur D :");
    Serial.println(indic_D_pos);
    
    Serial.println("--------");

    Serial.print("Angle Regulateur :");
    Serial.println(angle_Reg[reg_pos]);
    
    Serial.print("Angle Indic G :");
    Serial.println(angle[indic_G_pos]);

    Serial.print("Angle Indic D :");
    Serial.println(angle[indic_D_pos]);


    // clear the string:
    inputString = "";
    stringComplete = false;

    // ben maintenent on bouge les servo :)
    // myservo.write(pos); 
     serv_reg.write(angle_Reg[reg_pos]); 
     serv_indic_G.write(angle[indic_G_pos]);
     serv_indic_D.write(angle[indic_D_pos]);
    
  }
    }
  }
}
