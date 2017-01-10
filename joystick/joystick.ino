int iHeight = 10;
int iWidth = 25;

int iPlayerDirection = -1;
int iPlayerLength = 1;
int iPlayerY = 5;
int iPlayerX = 5;

int mapp[10][25];


int iFoodY;
int iFoodX;


boolean bGameOver = false;

void setup(){
  Serial.begin(9600);
  randomSeed(analogRead(0));
  restartGame();
}

void restartGame(){
  iPlayerDirection = -1;
  iPlayerLength = 1;
  iPlayerY = 5;
  iPlayerX = 5;
  bGameOver = false;
  for (int i = 0; i < iHeight; i++){
    for (int j = 0; j < iWidth; j++){
      if (i == 0 || i == iHeight-1|| j == 0 || j == iWidth-1){
        mapp[i][j] = -1;
      }
      else{
        mapp[i][j] = 0;
      }
    }
  }
  
  mapp[iPlayerY][iPlayerX] = iPlayerLength;
  spawnFood();
  printBoard();   
}
 
void loop()
{
  int i, someInt, flag = 0;
    for(i=2; i<9; i++){
      someInt = digitalRead(i);
      if(someInt == 0)
      {  
        flag =1;
        break;
      }
     }
     if(flag == 1){    
       //Serial.println(i); 
       switch(i)
       {
         case 2: iPlayerDirection = 0;
                 break;
         case 3: iPlayerDirection = 1;
                 break;
         case 4: iPlayerDirection = 2;
                 break;
         case 5: iPlayerDirection = 3;
                 break;
         case 6: iPlayerDirection = -2; 
                 break;
         case 7: iPlayerDirection = 5; 
                 break;
         case 8: Serial.println("--------> Button KEY"); break;
         default: break;
         }
         flag=0;
       }
    if(iPlayerDirection == 5){
        restartGame();
      }
    if(bGameOver == false && iPlayerDirection >= 0 ){
      movePlayer(iPlayerDirection);   
      printBoard();   
      delay(1500);
    }
}  
void movePlayer(int i){
  
  if(i == 0){
    iPlayerY = iPlayerY - 1;
  }
  else if(i == 1){
    iPlayerX = iPlayerX + 1;
  }
  else if(i == 2){
    iPlayerY = iPlayerY + 1;
  }
  else if(i == 3){
    iPlayerX = iPlayerX - 1;  
  }
  if(i < 0){
    Serial.println("PAUSED");
  }
  else{
    for (int i = 0; i < iHeight; i++){
      for (int j = 0; j < iWidth; j++){
        if(mapp[i][j] > 0){
          mapp[i][j]--;
        }
      }
    }
    if(iPlayerY == iFoodY && iPlayerX == iFoodX){
    iPlayerLength ++;
    spawnFood();
  }
  else if(mapp[iPlayerY][iPlayerX] != 0){
    bGameOver = true;
  }
  mapp[iPlayerY][iPlayerX] = iPlayerLength;  
  }
}

void printBoard (){
  for (int i = 0; i < iHeight; i++){
      for (int j = 0; j < iWidth; j++){
        //Serial.print("[");
        if(mapp[i][j] == -1){
          Serial.print("XX");
        }
        else if(mapp[i][j] == -2){
          Serial.print("FD");
        }
        else if (mapp[i][j] == 0){
          Serial.print("  ");
        }
        else if(mapp[i][j] < 10){
          Serial.print("0");
          Serial.print(mapp[i][j]);
        }
        else{
          Serial.print(mapp[i][j]);
        }
        //Serial.print("]");
      }
      Serial.println();
    } 
    Serial.println();
    Serial.println();
}

void spawnFood(){

  boolean bFoodSpotFound = false;
  
  while(bFoodSpotFound == false){
    iFoodY = random(iHeight-1)+1;
    iFoodX = random(iWidth-1)+1;
    if(mapp[iFoodY][iFoodX] == 0 ){
      bFoodSpotFound = true;
    }
  }
  mapp[iFoodY][iFoodX] = -2;
  

}
