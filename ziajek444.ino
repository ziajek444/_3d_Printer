// pobrane z pliku pins_RAMPS.h

#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
#define X_CS_PIN           53
#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56
#define Y_CS_PIN           49
#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62
#define Z_CS_PIN           40
#define X_MIN_PIN           3
#define PSA                 3
#define X_MAX_PIN           2
#define Y_MIN_PIN          14
#define Y_MAX_PIN          15
#define Z_MIN_PIN          18
#define Z_MAX_PIN          19

void setup() {

  // put your setup code here, to run once:

  Serial.begin(57600);
  Serial.setTimeout(10);

  // kierunki jazdy, juuuuhuuuuu JAZDA, CZADU
  pinMode(X_MAX_PIN, INPUT); //ustawiam pin "X_MAX_PIN" jako wejscie
  digitalWrite(X_MAX_PIN, HIGH); //ustawia wartosc logicznej jedynki na pin "X_MAX_PIN"
  pinMode(Y_MAX_PIN, INPUT);
  digitalWrite(Y_MAX_PIN, HIGH);
  pinMode(Z_MAX_PIN, INPUT);
  digitalWrite(Z_MAX_PIN, HIGH);
  pinMode(PSA, INPUT);
  digitalWrite(PSA, HIGH);

  //
  pinMode(X_STEP_PIN, OUTPUT);
  pinMode(X_DIR_PIN, OUTPUT);
  pinMode(X_ENABLE_PIN, OUTPUT);

  //
  pinMode(Y_STEP_PIN, OUTPUT);
  pinMode(Y_DIR_PIN, OUTPUT);
  pinMode(Y_ENABLE_PIN, OUTPUT);

  //
  pinMode(Z_STEP_PIN, OUTPUT);
  pinMode(Z_DIR_PIN, OUTPUT);
  pinMode(Z_ENABLE_PIN, OUTPUT);


  digitalWrite(X_ENABLE_PIN, LOW);
  digitalWrite(X_DIR_PIN, LOW);
  digitalWrite(Y_ENABLE_PIN, LOW);
  digitalWrite(Y_DIR_PIN, LOW);
  digitalWrite(Z_ENABLE_PIN, LOW);
  digitalWrite(Z_DIR_PIN, LOW);

}

// zmiana kierunku poprzez wybor na pinie DIR kierunku if krancowka == 1 then zmiana kierunku
int maxz = 0;
int maxx = 0;
int maxy = 0;
String s;
char a1;
bool readed = 0;
int work = 0;
int flaga = 0;
void loop() {

  // put your main code here, to run repeatedly:
  //PSA (odwrotna logika)
  //Serial.print("PSA:");
  //Serial.print(" ");
  //Serial.println(digitalRead(PSA));


  //------------------------------
  //Kalibca manualna
  //PSA jako takie
  //Po puszczeniu powrot do nieruchomej koncowki
  if (digitalRead(PSA) == 0)
  {
    maxx = 0;
    maxy = 0;
    maxz = 0;
    digitalWrite(X_ENABLE_PIN, HIGH);
    digitalWrite(Y_ENABLE_PIN, HIGH);
    digitalWrite(Z_ENABLE_PIN, HIGH);
    if (flaga == 0)
    {
      Serial.println("PSA");
      flaga = 1;
    }
  }
  else
  {
    flaga = 0;
    digitalWrite(X_ENABLE_PIN, LOW);
    digitalWrite(Y_ENABLE_PIN, LOW);
    digitalWrite(Z_ENABLE_PIN, LOW);
  }

  if ((maxx != 0 || maxy != 0 || maxz != 0) && work == 0)
  {
    work = 1;
  }
  if ((maxx == 0 && maxy == 0 && maxz == 0) && work == 1)
  { work = 0;
    Serial.println("OK");
  }
  //------------------------------
  if ( maxx != 0 )
  {
    if (maxx > 0)
    {
      digitalWrite(X_DIR_PIN, LOW);
      maxx--;
    }
    else
    {
      digitalWrite(X_DIR_PIN, HIGH);
      maxx++;
    }
    digitalWrite(X_STEP_PIN, LOW);
  }
  //------------------------------
  if ( maxy != 0 )
  {
    if (maxy > 0)
    {
      digitalWrite(Y_DIR_PIN, LOW);
      maxy--;
    }
    else
    {
      digitalWrite(Y_DIR_PIN, HIGH);
      maxy++;
    }
    digitalWrite(Y_STEP_PIN, LOW);
  }
  //------------------------------
  if ( maxz != 0 )
  {
    if (maxz > 0)
    {
      digitalWrite(Z_DIR_PIN, LOW);
      maxz--;
    }
    else
    {
      digitalWrite(Z_DIR_PIN, HIGH);
      maxz++;
    }
    digitalWrite(Z_STEP_PIN, LOW);
  }

  //------------------------------

  delayMicroseconds(50);

  digitalWrite(X_STEP_PIN, HIGH);
  digitalWrite(Y_STEP_PIN, HIGH);
  digitalWrite(Z_STEP_PIN, HIGH);

  delayMicroseconds(50);
  //------------------------------


  //Praca rownolegla
  //Serial.readString();
  while (Serial.available())
  {
    //s = Serial.readString();
    a1= Serial.read();
    s=s+a1;
    if (a1=='\n')
   {
    sscanf(s.c_str(), "x %d y %d z %d\n", &maxx, &maxy, &maxz);
    s=String("");
   }
    //maxx*=10;
    //maxy*=10;
    //maxz*=10;
    //readed = 1; future
  }
  //Serial.print(maxx);
  //Serial.print(" ");
  //Serial.print(maxy);
  //Serial.print(" ");
  //Serial.println(maxz);
}


