/* Melda Kiziltan | Sem. 1 | TEJ 4MI-01 | October 2018 
 To play: 
 When started up: 
  - LED's will flash, pick one of the following:
    - Red for easy
    - Yellow for hard
    - Green for extreme
    - Blue for multiplayer (2 or 4 players)
  - When pressed, games will start
    - Follow the patterns
      - If you lose: lights will all light up and you will be taken back to the start selection
      - If you win: you get RICKROLLED and you will be taken back to the start selection
 Good luck!
 ;)
 
*/

//Establishing and creating global variables

//LED's and their corresponding pins
const int RL = 8;
const int YL = 7;
const int GL = 3;
const int BL = 2;

//Buttons and their corresponding pins
const int RB = 10;
const int YB = 9;
const int GB = 5;
const int BB = 4;

//Button store. This is used to stare the colour number into a variable that we can use globally to check if the button press is the same as the pattern
int ButtonStore;
bool PRESSED = false;

//Speaker and it's corresponding pin
const int SPK = 6;

//colour sounds
const int RSPK = 1046; // (C6 = 1046 Hz)
const int YSPK = 523; // (C5 = 523 Hz)
const int GSPK = 261; // (C4 = 261 Hz)
const int BSPK = 130; // (C3 = 130 Hz)

//Assigning number values to the colours helps us create an array or pattern for the games
const int Red = 0;
const int Yellow = 1;
const int Green = 2;
const int Blue = 3;

//time
unsigned long time;

const int delay1 = 300;
const int delay2 = 500;

//game stuffs
int GAMESIZE = 0;  //GAMESIZE is the size of the game that is being played
byte GAME [25];    //creates an array that can store 25 integers
bool xTREME;       //sets xTREME mode to false
int check = 0;     //for the post array processing
bool multiPLAY;    //sets multiplayer mode to false
int players = 4;   //number of players in the game
bool RED = true;   //Colour bools for use in multiplayer
bool YELLOW = true;//Colour bools for use in multiplayer
bool GREEN = true; //Colour bools for use in multiplayer
bool BLUE = true;  //Colour bools for use in multiplayer

/*-----------------------------*/

void setup(){
  //Starts the serial monitor - used mostly for troubleshooting
  Serial.begin(250000);
  //LED's + speaker
  pinMode(RL, OUTPUT);
  pinMode(YL, OUTPUT);
  pinMode(GL, OUTPUT);
  pinMode(BL, OUTPUT);
  pinMode(SPK, OUTPUT);
  //Buttons
  pinMode(RB, INPUT);
  pinMode(YB, INPUT);
  pinMode(GB, INPUT);
  pinMode(BB, INPUT);
  
  wait();   //waits until the red button is pressed to start the game
            //this also allows the timer to stop at a certain time to create the game array

  delay(500); //this delay is for if the first colour in the array is the same as the button you pressed so you don't confuse it with the light just pulsing normally

//generates game pattern. If good, breaks, if not, tries again
  while (true){
   setGame();
   bool goodGAME = checkGame();
    if (goodGAME == true){
      break;
    }
  }
  
  printList(); //prints the pattern to the serial monitor
  playGame(); //plays the game! (go figure)
  
}

/*-----------------------------*/
void(* reset) (void) = 0; //resets the Arduino without having to connect to the reset pin or physically push the reset button (great for cases)
/*-----------------------------*/
//Shuts all the LED's and the speaker off
void kill(){
  digitalWrite(RL, LOW);
  digitalWrite(YL, LOW);
  digitalWrite(GL, LOW);
  digitalWrite(BL, LOW);
  noTone(SPK);
}
/*-----------------------------*/
void wait(){
//all buttons will flash and play a tone as if to say, "Press me!"
  //Waits until a button is pressed to start a game
  while (true) {
      digitalWrite(RL, HIGH);
      digitalWrite(YL, HIGH);
      digitalWrite(GL, HIGH);
      digitalWrite(BL, HIGH);
      tone(SPK, 231);
    
      for(int x = 0;x<100;x++){
        //checks red button
        if (digitalRead(RB) == LOW){
        delay(5);
        if (digitalRead(RB) == LOW){
              kill();
              GAMESIZE = 8; //sets GAMESIZE to 8 for an easy level
              check = 3; //This is for post-array processing saying that there can not be more than 3 of each colour
              return;
          }
        }
        //checks the yellow button
        if (digitalRead(YB) == LOW){
        delay(5);
        if (digitalRead(YB) == LOW){
              kill();
              GAMESIZE = 17; //sets GAMESIZE to 17 for a hard level
              check = 5; //This is for post-array processing saying that there can not be more than 5 of each colour
              return;
          }
        }
        //check the green button
        if (digitalRead(GB) == LOW){
        delay(5);
        if (digitalRead(GB) == LOW){
              kill();
              GAMESIZE = 12; //Sets game array to 10 for xTREME mode
              xTREME = true; //tells the Arduino that the player has selected xTREME mode
              Serial.print("xTREME mode ON");
              check = 4; //This is for post-array processing saying that there can not be more than 3 of each colour
              return;
          }
        }
        //checks the blue button
        if (digitalRead(BB) == LOW){
          delay(5);
          if (digitalRead(BB) == LOW){
              kill();
              GAMESIZE = 25; //sets the game array to 25 for multiplayer mode
              multiPLAY = true; //tells the Arduino that the player has selected multiplayer mode
              Serial.print("Multiplayers go!");
              check = 7; //This is for post-array processing saying that there can not be more than 7 of each colour
              return;
          }
        }
      delay (5);
      }
      kill(); 
      for(int x = 0;x<100;x++){
        //checks red button
        if (digitalRead(RB) == LOW){
        delay(5);
        if (digitalRead(RB) == LOW){
              kill();
              GAMESIZE = 8; //sets GAMESIZE to 8 for an easy level
              check = 3; //This is for post-array processing saying that there can not be more than 3 of each colour
              return;
          }
        }
        //checks the yellow button
        if (digitalRead(YB) == LOW){
        delay(5);
        if (digitalRead(YB) == LOW){
              kill();
              GAMESIZE = 17; //sets GAMESIZE to 17 for a hard level
              check = 5; //This is for post-array processing saying that there can not be more than 5 of each colour
              return;
          }
        }
        //check the green button
        if (digitalRead(GB) == LOW){
        delay(5);
        if (digitalRead(GB) == LOW){
              kill();
              GAMESIZE = 10; //Sets game array to 10 for xTREME mode
              xTREME = true; //tells the Arduino that the player has selected xTREME mode
              Serial.print("xTREME mode ON");
              check = 3; //This is for post-array processing saying that there can not be more than 3 of each colour
              return;
          }
        }
        //checks the blue button
        if (digitalRead(BB) == LOW){
          delay(5);
          if (digitalRead(BB) == LOW){
              kill();
              GAMESIZE = 25; //sets the game array to 25 for multiplayer mode
              multiPLAY = true; //tells the Arduino that the player has selected multiplayer mode
              Serial.print("Muiltiplayers go!");
              check = 7; //This is for post-array processing saying that there can not be more than 7 of each colour
              return;
          }
        }
      delay (5);
      } 
   }
}
/*-----------------------------*/
//This is to play a tone and light up the correct LED when the button is pressed
void Bpress(){
    while (PRESSED == false){
  Bcheck(RB, RL, RSPK);
  Bcheck(YB, YL, YSPK);
  Bcheck(GB, GL, GSPK);
  Bcheck(BB, BL, BSPK);
    }
  PRESSED = false;
}
/*-----------------------------*/
//Checks which button is checked and stores it in the variable ButtonStore for future use
void Bcheck(int button, int led, int sound){
  if (digitalRead(button) == LOW){
    delay(5); //contact bounce
    while (digitalRead(button) == LOW){
      digitalWrite(led, HIGH);
      tone(SPK, sound);
    }
    kill();
    if (button == RB){
      ButtonStore = Red;
        PRESSED = true;
    }
    else if (button == YB){
      ButtonStore = Yellow;
        PRESSED = true;
    }
    else if (button == GB){
      ButtonStore = Green;
      PRESSED = true;
    }
    else {
      ButtonStore = Blue;
      PRESSED = true;
    }
          Serial.print(ButtonStore);
  }
}
/*-----------------------------*/
//Generates a "random" pattern for the games
void setGame(){
  randomSeed(micros());
  for(int x = 0; x<GAMESIZE; x++){
    GAME[x]= random(4);
  }
}
/*-----------------------------*/
//checks the game sequence to see if the pattern matches the criteria. If so, it plays. If not, it re-rolls
bool checkGame(){
while (true){
  //POST ARRAY PROCESSING
    int r = 0;
    int y = 0;
    int g = 0;
    int b = 0;
 
  for (int x = 0; x<GAMESIZE; x++){
    //checks the game array at x and adds one to the variable 
    if (Red == GAME[x]){
      r++; //adds one to the r variable to represent the colour red
    }
    if (Yellow == GAME[x]){
      y++; //adds one to the y variable to represent the colour yellow
    }
    if (Green == GAME[x]){
      g++; //adds one to the g variable to represent the colour green
    }
    if (Blue == GAME[x]){
      b++; //adds one to the b variable to represent the colour blue
    }
  }
 
  //re-rolls if number of each colour in the pattern is more than a certain number (as determined by the initial button selection) or less than 2 (A.K.A. 1). This ensures that there is at least 1 of each colour in the sequence
    if(r>check || r<2){
    return false;
    }
    else if(y>check || y<2){
    return false;
    }
    else if(g>check || g<2){
    return false;
    }
    else if(b>check || b<2){
    return false;
    }
  return true;
  }
}
/*-----------------------------*/
//Prints the pattern to the serial monitor
void printList(){
  for(int x = 0; x<GAMESIZE; x++){
    Serial.print(GAME[x]);
  }
  Serial.println();
}
/*-----------------------------*/
//defines what he games should do when playing the game pattern
void play(int led,int sound,int duration){
  delay(duration);
  digitalWrite(led,HIGH);
  tone(SPK,sound);
  delay(duration);
  digitalWrite(led,LOW);
  noTone(SPK);
}
/*-----------------------------*/
//This sets the new game for the multiplayer
void setGameMP(){
  int x = 0;
  while (x <= 26){
    GAME[x]= random(4); 
    if (GAME[x] == Red && RED == true){ //What this is doing is it is going through the array and placing each number one at a time instead of creating whole patterns at a time
      x++;
    }
    else if (GAME[x] == Yellow && YELLOW == true){
      x++;
    }
    else if (GAME[x] == Green && GREEN == true){
      x++;
    }
    else if (GAME[x] == Blue && BLUE == true){
      x++;
    }
    //printList();
  }
}
/*-----------------------------*/
//for winners only!
void win(){
  if (multiPLAY == true && players == 1){ //confirms if multiplayer mode is on
   if (RED == true){ //if winner is red or 0, it will only light up the red LED
      digitalWrite(RL, HIGH);
    }
    else if (YELLOW == true){ //if the winner is yellow, or 1, it will only light up the yellow LED
      digitalWrite(YL, HIGH);
    }
    else if (GREEN == true){ //if the winner is green, or 2, it will only light up the green LED
      digitalWrite(GL, HIGH);
    }
    else if (BLUE == true){ //if the winner is blue, or 3, it will only light up the blue LED
      digitalWrite(BL, HIGH);
    }

  }
  else if (multiPLAY == false || players > 1){
  //all LED's will be on
  digitalWrite(RL, HIGH);
  digitalWrite(YL, HIGH);
  digitalWrite(GL, HIGH);
  digitalWrite(BL, HIGH);
  }
  //GET RICKROLLED (plays never gonna give you up)
  tone(SPK, 466);
  delay(100);
  tone(SPK, 466);
  delay(100);
  tone(SPK, 415);
  delay(100);
  tone(SPK, 415);
  delay(100);
  tone(SPK, 698);
  delay(200);
  tone(SPK, 698);
  delay(200);
  tone(SPK, 622);
  delay(300);
  tone(SPK, 466);
  delay(100);
  tone(SPK, 466);
  delay(100);
  tone(SPK, 415);
  delay(100);
  tone(SPK, 415);
  delay(100);
  tone(SPK, 622);
  delay(200);
  tone(SPK, 544);
  delay(200);
  tone(SPK, 543);
  delay(200);
  tone(SPK, 466);
  delay(200);
  tone(SPK, 554);
  delay(100);
  tone(SPK, 554);
  delay(100);
  tone(SPK, 554);
  delay(100);
  tone(SPK, 554);
  delay(100);
  tone(SPK, 554);
  delay(200);
  tone(SPK, 622);
  delay(100);
  tone(SPK, 523);
  delay(100);
  tone(SPK, 466);
  delay(100);
  tone(SPK, 415);
  delay(100);
  tone(SPK, 415);
  delay(100);
  tone(SPK, 415);
  delay(100);
  tone(SPK, 622);
  delay(200);
  tone(SPK, 554);
  delay(200);

  kill(); //stops everything
  delay(750);
  reset(); //resets Arduino to beginning start
}

/*-----------------------------*/
//you lost :(
void gameOver(){
  if (multiPLAY == false){
  //flashes all lights, plays a high tone
     digitalWrite(RL, HIGH);
     digitalWrite(YL, HIGH);
     digitalWrite(GL, HIGH);
     digitalWrite(BL, HIGH);
     tone(SPK, 2000);
     delay(500);
        
     kill(); //stops everything
     delay(750);
     reset(); //resets Arduino to beginning start
    }
  if (multiPLAY == true){
    if (ButtonStore == Red){ //If the last button pressed is red...
      RED = false;       //It will set the red colour bool to false meaning that the colour/player red is now out
      Serial.print("Red is out");
      players = players-1;   //Takes one away from the number of current players
      }
    else if (ButtonStore == Yellow){ //If the last button pressed is yellow...
      YELLOW = false;        //It will set the yellow colour bool to false, meaning that the colour/player yellow is now out
      Serial.print("Yellow is out");
      players = players-1;       //Takes one away from the number of current players
      }
    else if (ButtonStore == Green){ //If the last button pressed is green...
      GREEN = false;        //It will set the green colour bool to false meaning that the colour/player yellow is now out
      Serial.print("Green is out");
      players = players-1;      //Takes one away from the number of current players
      }
    else if (ButtonStore == Blue){ //If the last button pressed is blue...
      BLUE = false;          //It will set the blue colour bool to false, meaning that the colour/player blue is now out
      Serial.print("Blue is out");
      players = players-1;       //Takes one away from the number of current players
      }
    if (players == 1){ //If there is only one player left, they win!
      win();
      }
    setGameMP(); //When the player has gotten out, the bool is set to false and the number of players has gone down, the Arduino sets a new multiplayer game
    playGame(); //After the game is set, it starts playing!
    }
  }

/*-----------------------------*/
//plays the game. Has Simon's turn and the player's turn.
void playGame(){
  for(int y=0;y<GAMESIZE;y++){
    if (xTREME == true){ //If the player selects extreme mode, the game pattern will change each set of turns
      setGame(); //sets the new game
      checkGame(); //checks the new game
    }
    // Simon's turn
    for (int x=0;x<=y;x++){
      if (GAME[x] == Red){
        play(RL,RSPK,delay1); //if the number in the pattern is red, shine the light, play the sound and have a small delay
      }
      else if (GAME[x] == Blue){
        play(BL,BSPK,delay1); //if the number in the pattern is blue, shine the light, play the sound and have a small delay
      }
      else if (GAME[x] == Green){
        play(GL,GSPK,delay1); //if the number in the pattern is green, shine the light, play the sound and have a small delay
      }
      else if (GAME[x] == Yellow){
        play(YL,YSPK,delay1); //if the number in the pattern is yellow, shine the light, play the sound and have a small delay
        }
      delay(10);
      }
    
    // Player's turn
    for(int x=0;x<=y;x++){
      Bpress(); //checks which button was pressed
        if (GAME[x] != ButtonStore){ //if the button pressed does not match the pattern, it sets y to 27 and calls game over
          y=27;
          gameOver();
      }
    }
  delay(50);
  }
  win(); //if the entire pattern is completed successfully, the player wins!
}

//not using loop
void loop()
{
}
