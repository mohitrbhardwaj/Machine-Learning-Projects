#include <Keypad.h>
const int rpin=11;
const int gpin=12;
const int bpin=13;
const int rclk=14;
const int gclk=15;
const int bclk=16;
const int ledpin=20;
const byte ROWS = 4; //four ROWS-1
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
        {'1','2','3'},
        {'4','5','6'},
        {'7','8','9'},
        {'*','0','#'}
        };
        
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6}; //connect to the column pinouts of the keypad
int lim[ROWS-1][COLS] = {
  {1,2,1},
  {2,3,2},
  {1,2,1}
  };
int val[ROWS-1][COLS],colr[ROWS-1][COLS];
  
int color=0;
char row,col;
Keypad keyp = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); 
bool firsttime= true;
int var=0;

void setup()
{
  pinMode(ledpin, OUTPUT);
  pinMode(rpin, OUTPUT);
  pinMode(gpin, OUTPUT);
  pinMode(bpin, OUTPUT);
  pinMode(rclk, OUTPUT);
  pinMode(gclk, OUTPUT);
  pinMode(bclk, OUTPUT);
  Serial.begin(9600);
  Serial.println("RED's turn, Please start the game:");
}

void bunc()
{
  row=NO_KEY;
  while(!row)
  {
    row = keyp.getKey();
  }
  if(row=='*')
  {
     bunc();
  }
  col=NO_KEY;
  while(!col)
  {
    col = keyp.getKey();
  }
  if(col=='*')
  {
    bunc();
  }
  if(row>'0'&&col>'0'&&row<'4'&&col<'4'&&(colr[row-'1'][col-'1']==color||colr[row-'1'][col-'1']==0))
  {
    
  }
  else
  {
    bunc();
  }
}

void func(int i, int j, int colt)
{
  if(i>=ROWS-1||i<0)
  {
    return;
  }
  if(j>=COLS||j<0)
   {
    return;
   }
  if(val[i][j]<lim[i][j])
  {
    val[i][j]++;
    colr[i][j]=colt;
  }
  else
  {
    val[i][j]=0;
    colr[i][j]=0;
    func(i,j-1,colt);
    func(i-1,j,colt);
    func(i+1,j,colt);
    func(i,j+1,colt);
   } 
}

void upd(String s,int color)
{
  Serial.print(s);
  Serial.print(" ");
  Serial.println(color);
  while(s.length()<15)
  {
    s+='0';
  }
  for(int i=0;i<s.length();i++)
  {
    if(s[i]=='0')
    {
      digitalWrite(rpin+color-1,HIGH);
    }
    else
    {
      digitalWrite(rpin+color-1,LOW);
    }
    //yaha clock wala part
  }
}

void update_hardware()
{
  for( int kk=1;kk<=3;kk++)
  {
    String s="";
    for(int i=0;i<3;i++)
    {
      for(int j=0;j<3;j++)
      {
        int xx=val[i][j];
        for(int k=0;k<lim[i][j];k++)
        {
          if(xx>0&&colr[i][j]==kk)
          {
             s+='1';
             xx--;
          }
          else
          {
             s+='0';
          }
        }
      }
     }
     upd(s,kk);
  }
}

void dunc()
{
  Serial.println("This is current state: \n");
  for(int i=0;i<ROWS-1;i++)
  {
    for(int j=0;j<COLS;j++)
    {
      Serial.print(val[i][j]);
      Serial.print(",");
      if(colr[i][j]==0)
      {
        Serial.print("N ");
      }
      if(colr[i][j]==1)
      {
        Serial.print("R ");
      }
      if(colr[i][j]==2)
      {
        Serial.print("G ");
      }
      if(colr[i][j]==3)
      {
        Serial.print("B ");
      }
    }
    Serial.println();
  }
}

bool check()
{
  int pat[4]={0,0,0,0};
  
  for(int i=0;i<4;i++)
  {
    for(int j=0;j<4;j++)
    {
      pat[colr[i][j]]++;
    }
  }
  int coun=0;
  int ind=0;
  for(int i=1;i<4;i++)
  {
    if(pat[i]>0)
    {
      ind=i;
      coun++;
    }
  }
  if(coun==1)
  {
    if(ind==1)
    {
      Serial.println("Winner is RED/1");
    }
    else if(ind==2)
    {
      Serial.println("Winner is GREEN/2");
    }
    else if(ind==3)
    {
      Serial.println("Winner is BLUE/3");
    }
    return true;
  }
  else
  {
    return false;
  }
}
void loop()
{
  var++;
  color++;
  if(color==4)
  {
    color=1;
  }
  bunc();                           // take inputs
  if(row!=NO_KEY&&col!=NO_KEY) 
  {
    func(row-'1',col-'1',color);    //makes changes as according to the inputs
  }
  update_hardware();
    
  dunc();                           // print current state
  if(firsttime==false)
  {
    if(check())
    {
      Serial.println("Game is Finished");
      return;
    }
  }
  else
  {
    firsttime=false;
  }
}
