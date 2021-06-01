#include <SPI.h>
#include <WiFi101.h>
#include <LiquidCrystal.h>
char ssid[] = "MEO-COSTA";      //  your network SSID (name)
char pass[] = "t1ze965p";   // your network password
int keyIndex = 0;                // your network key Index number (needed only for WEP)
int status = WL_IDLE_STATUS;
WiFiServer server(80);
//----------------------------fim defenições wifi--------------------------------------------------------
//---------------------------inicialização de algumas variáveis-----------------------------------------
unsigned long myTime;
int array_tempos[100];
int array_register[100];
int array_tipo[100];
int online=1;
int counter=0;

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0



volatile int beatlength = 100; // determines tempo
float beatseparationconstant = 0.3;

int threshold;

int tempo = 114;



int buzzerPin = 11;

int melody[] = { //musica russia
  NOTE_G4, NOTE_C5, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_E4, NOTE_E4, 
  NOTE_A4, NOTE_G4, NOTE_F4, NOTE_G4, NOTE_C4, NOTE_C4, 
  NOTE_D4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_D5, 
  NOTE_E5, NOTE_D5, NOTE_C5, NOTE_D5, NOTE_B4, NOTE_G4, 
  NOTE_C5, NOTE_B4, NOTE_A4, NOTE_B4, NOTE_E4, NOTE_E4, 
  NOTE_A4, NOTE_G4, NOTE_F4, NOTE_G4, NOTE_C4, NOTE_C4, 
  NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_B4, NOTE_C5, NOTE_D5, 
  NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_G4, NOTE_G4, NOTE_B4, NOTE_C5, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_E4, NOTE_E4, NOTE_G4, NOTE_A4, NOTE_B4,
  NOTE_C5, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_A4, NOTE_C5, NOTE_F5,
  NOTE_F5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_C5,
  NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_A4, NOTE_A4,
  NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_C4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5
};

int noteDurations[] = {
  8, 4, 6, 16, 4, 8, 8, 
  4, 6, 16, 4, 8, 8, 
  4, 8, 8, 4, 8, 8, 4, 8, 8, 2,
  4, 6, 16, 4, 8, 8, 
  4, 6, 16, 4, 8, 8, 
  4, 6, 16, 4, 6, 16, 
  4, 6, 16, 8, 8, 8, 8, 
  2, 8, 8, 8, 8, 3, 8, 8, 8, 8, 8,
  2, 8, 8, 8, 8, 3, 8, 8, 8, 8, 8,
  4, 6, 16, 4, 6, 16, 4, 8, 8, 2,
  2, 8, 8, 8, 8, 3, 8, 2,
  2, 8, 8, 8, 8, 3, 8, 2,
  4, 6, 16, 4, 4, 2, 4, 4, 1
};


int melody_rick[] = {

  // Never Gonna Give You Up - Rick Astley
  // Score available at https://musescore.com/chlorondria_5/never-gonna-give-you-up_alto-sax
  // Arranged by Chlorondria

  NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,4, //1
  NOTE_E5,-4, NOTE_FS5,-4, NOTE_A5,16, NOTE_G5,16, NOTE_FS5,8,
  NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,2,
  NOTE_A4,16, NOTE_A4,16, NOTE_B4,16, NOTE_D5,8, NOTE_D5,16,
  NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,4, //repeat from 1
  NOTE_E5,-4, NOTE_FS5,-4, NOTE_A5,16, NOTE_G5,16, NOTE_FS5,8,
  NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,2,
  NOTE_A4,16, NOTE_A4,16, NOTE_B4,16, NOTE_D5,8, NOTE_D5,16,
  REST,4, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_D5,8, NOTE_E5,8, NOTE_CS5,-8,
  NOTE_B4,16, NOTE_A4,2, REST,4, 

  REST,8, NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,4, NOTE_A4,8, //7
  NOTE_A5,8, REST,8, NOTE_A5,8, NOTE_E5,-4, REST,4, 
  NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, NOTE_D5,8, NOTE_E5,8, REST,8,
  REST,8, NOTE_CS5,8, NOTE_B4,8, NOTE_A4,-4, REST,4,
  REST,8, NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, NOTE_A4,4,
  NOTE_E5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,4, REST,4,
   
  NOTE_D5,2, NOTE_E5,8, NOTE_FS5,8, NOTE_D5,8, //13
  NOTE_E5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,4, NOTE_A4,4,
  REST,2, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8,
  REST,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,

  NOTE_E5,-8, NOTE_E5,-8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,-8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16, //18
  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,8, NOTE_A4,8, NOTE_A4,8, 
  NOTE_E5,4, NOTE_D5,2, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_A5,4, NOTE_CS5,8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,

  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,4, NOTE_A4,8,  //23
  NOTE_E5,4, NOTE_D5,2, REST,4,
  REST,8, NOTE_B4,8, NOTE_D5,8, NOTE_B4,8, NOTE_D5,8, NOTE_E5,4, REST,8,
  REST,8, NOTE_CS5,8, NOTE_B4,8, NOTE_A4,-4, REST,4,
  REST,8, NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, NOTE_A4,4,
  REST,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8, NOTE_D5,8,
  
  REST,8, NOTE_A4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, //29
  REST,8, NOTE_CS5,8, NOTE_B4,8, NOTE_A4,-4, REST,4,
  NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, NOTE_A4,4, REST,8,
  REST,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,4, NOTE_E5,-4, 
  NOTE_D5,2, NOTE_D5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,4, 
  NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8, NOTE_A4,8, NOTE_A4,4,

  REST,-4, NOTE_A4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, //35
  REST,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_E5,-8, NOTE_E5,-8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,4, NOTE_A4,8, 

   NOTE_E5,4, NOTE_D5,2, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16, //40
  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_A5,4, NOTE_CS5,8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,4, NOTE_A4,8,  
  NOTE_E5,4, NOTE_D5,2, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
   
  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16, //45
  NOTE_A5,4, NOTE_CS5,8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,4, NOTE_A4,8,  
  NOTE_E5,4, NOTE_D5,2, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16, //45
  
  NOTE_A5,4, NOTE_CS5,8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,4, NOTE_A4,8, 

  NOTE_E5,4, NOTE_D5,2, REST,4
};

int notes = sizeof(melody) / sizeof(melody[0]) / 2;
int wholenote = (60000 * 4) / tempo;
int divider = 0, noteDuration = 0;



const int rs=12, en=11,d4 = 5, d5 = 4, d6 = 3, d7 = 2;
int sensorPin = A1;    // select the input pin for the potentiometer
int statusPin = A5;
int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;
int statusvalue = 0;
int buzzer = 8 ;// variable to store the value coming from the sensor
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


//------------------------------------------fim das defenições--------------------------------------------

void setup() {
  
  Serial.begin(9600);      // initialize serial communication
  pinMode(13, OUTPUT);      // set the LED pin mode
// check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);       // don't continue
  }
// attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);
// Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }
  server.begin();                           // start the web server on port 80
  printWifiStatus();                        // you're connected now, so print out the status

  delay(5000);

//---------------------fim do setup wifi-------------------------------------------------------
  lcd.begin(16, 2);
  pinMode(ledPin, OUTPUT);
  pinMode (buzzer, OUTPUT);
  lcd.setCursor(0,0);
  lcd.print("Sensor Movimento");
}
//---------------------------------fim do setup---------------------------------------------------
void loop() {

 //código interface
  WiFiClient client = server.available();   // listen for incoming clients
if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character
// if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {

            myTime=millis();
            int j=0;
            while(array_register[j]!=0){
              array_tempos[j]=myTime-array_register[j];
              j=j+1;
            }
            
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            //código HTML com funções java script
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Refresh: 15");
            client.println();

            client.println("<!DOCTYPE html>");
            client.println("<html>");
            client.println("<head>");
            client.println(  "<title>Browser Interface</title>");
            client.println( "<meta charset='UTF-8'>");
            
            client.println("</head>");
            client.println("<body>");
            client.println("<h1>Estado do sensor:");
            if(online==1){
              client.print("Online");
            }
            else{
              client.print("Offline");
            }
            client.print("</h1>");
            
            
            client.println("<ul id='lista'>");
            client.println("</ul>");
            
            
            
            client.println("<script type='text/javascript'>");
                
            client.println("var tempos=[");
            int i=0;
            
            while(array_tempos[i]!=0){
              client.print(array_tempos[i]);
              client.print(",");
              i=i+1;
            }
                      
            client.print(0);
            client.print("]");
            client.println();
            
            client.println("var tipo_mensagem=[");

            i=0;
            while(array_tipo[i]!=0){
              client.print(array_tipo[i]);
              client.print(",");
              i=i+1;
            }
                      
            client.print(0);
            client.print("]");

            client.println();
             
            client.println(   "var i=tempos.length-1;");

            //client.println("console.log(i)");
            
            client.println(   "function construir_lista(i,l){");
            
            client.println(     "i=Math.floor(i/1000);");
            
            client.println(     "var today = new Date();");
            
            client.println(     "hora=today.getHours();");
            client.println(     "min=today.getMinutes();");
            client.println(     "segundos=today.getSeconds();");
            
            
            client.println("      if(i<=60){");
            
            client.println("        if(segundos>=i){");
            client.println("          segundos=segundos-i");
            client.println("        }");
            client.println("        else{");
            client.println("          min=min-1");
            client.println("          var segundos_sub=segundos-i");
            client.println("          segundos=60+segundos_sub");
            client.println("        }");
            
            client.println("      }");
            
            client.println("      else if (i<=3600) {");
            
            client.println("        var min_passados = Math.floor(i/60);");
            //client.println("        console.log(min_passados)");
            //client.println("        console.log(min)");
            
            
            client.println("      if (min>=min_passados) {");
            
            client.println("          min=min-min_passados");
            
            client.println("        var segundos_pass=i-min_passados*60");
            
            client.println("          if(segundos>=segundos_pass){");
            client.println("            segundos=segundos-segundos_pass");
            client.println("          }");
            client.println( "       else{");
            client.println( "         min=min-1");
            client.println( "         var segundos_sub=segundos-segundos_pass");
            client.println( "         segundos=60+segundos_sub");
            client.println( "       }");
            client.println( "     }");
            client.println( "     else{");
            
            client.println( "       hora=hora-1");
            
            client.println( "       var minutos_sub=min-min_passados");
            
            client.println( "       min=60+minutos_sub");
            
            client.println( "       console.log(min)");
            
            client.println( "       var segundos_pass=i-min_passados*60");
            
            client.println( "       if(segundos>=segundos_pass){");
            client.println( "         segundos=segundos-segundos_pass");
            client.println( "       }");
            client.println( "       else{");
            client.println( "         min=min-1");
            client.println( "         var segundos_sub=segundos-segundos_pass");
            client.println( "         segundos=60+segundos_sub");
            client.println( "       }");
            client.println( "     }");
                    
            client.println( "   }");
            
                    
            client.println(  "          var date = today.getFullYear()+'-'+(today.getMonth()+1)+'-'+today.getDate();");
            
            client.println(   "         var time = hora + ':' + min + ':' + segundos;");
            
            client.println(    "        var dateTime = date+' '+time+'⇨';");
            
            client.println(     "       var list = document.getElementById('lista');");
            client.println(      "      var entry = document.createElement('li');");
            client.println(       "     entry.appendChild(document.createTextNode(dateTime));");
            client.println("if(l==1){");
            client.println("   entry.appendChild(document.createTextNode('Obstrução Identificada!! '))");
            client.println("}");
            client.println("else if (l==2) {");
            client.println(" entry.appendChild(document.createTextNode('Ativou '))");
            client.println("}");
            client.println(" else {");
            client.println("entry.appendChild(document.createTextNode('Desligou '))");
            client.println("}");

            //client.println(         "   entry.appendChild(document.createTextNode(i));");
            client.println(          "  list.appendChild(entry);");
            client.println("    }");
            
            client.println("    for (var j = 0; j < i; j++) {");
            
            client.println( "   construir_lista(tempos[j],tipo_mensagem[j]);");
            client.println( " }");
                
            
            client.println("  </script>");
            
            client.println("</body>");
            
            client.println("</html>");
            // break out of the while loop:
            break;
          }
          else {      // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        }
        else if (c != '\r') {    // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }

//------------------------------inicio código do sensor--------------------------------

    unsigned char i, j ;
    // read the value from the sensor:
    sensorValue = analogRead(sensorPin);
    statusvalue = analogRead(statusPin);
    Serial.println("");
    Serial.print("status value: ");
    Serial.println(statusvalue);
    if (statusvalue > 1000)
    {
        while(online==0){
            myTime = millis();
            array_register[counter]=myTime;
            array_tipo[counter]=2;
            counter=counter+1;
            online=1;
        }
          
    Serial.println(""); 
    Serial.print("Sensor value: ");
    Serial.println(sensorValue);
    
    if (sensorValue > 210)
    {
      digitalWrite (ledPin,LOW);
      lcd.setCursor(0,1);
      lcd.print(" ");
      lcd.setCursor(0,1);
      lcd.print("Sem Obstrucao");
    }
    if (sensorValue < 200)
    {
      digitalWrite(ledPin,HIGH);
      lcd.setCursor(0,1);
      lcd.print(" ");
      lcd.setCursor(0,1);
      lcd.print("Tapado              ");
      
      myTime = millis();
      array_register[counter]=myTime;
      array_tipo[counter]=1;
      counter=counter+1;
      
      int thisNote=0;
 
       /* while (thisNote < (sizeof(melody) / 2)) { // Russian anthem
        Serial.println(sensorValue);
        int noteDuration = 2000 / noteDurations[thisNote];
        tone(buzzer, melody[thisNote], noteDuration);
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        noTone(buzzer);
        thisNote++;
        sensorValue = analogRead(sensorPin);
        if (sensorValue > 50) {
          Serial.println("entrou");
          break;
          }
      }*/
  
      for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) { //rick roll musica
      Serial.println("");
      Serial.print("Sensor value: ");
      Serial.println(sensorValue);
      // calculates the duration of each note
      divider = melody_rick[thisNote + 1];
      if (divider > 0) {
        // regular note, just proceed
        noteDuration = (wholenote) / divider;
      } else if (divider < 0) {
        // dotted notes are represented with negative durations!!
        noteDuration = (wholenote) / abs(divider);
        noteDuration *= 1.5; // increases the duration in half for dotted notes
      }
  
      // we only play the note for 90% of the duration, leaving 10% as a pause
      tone(buzzer, melody_rick[thisNote], noteDuration * 0.9);
  
      // Wait for the specief duration before playing the next note.
      delay(noteDuration);
  
      // stop the waveform generation before the next note.
      noTone(buzzer);
      sensorValue = analogRead(sensorPin);
      statusvalue = analogRead(statusPin);
        if (sensorValue > 200 ) {
          Serial.println("");
          Serial.println("entrou");
          Serial.print("Sensor value: ");
          Serial.println(sensorValue);
          digitalWrite(buzzer,LOW);
          break;
          }
          else if (statusvalue < 1000)
          {
            Serial.println("");
            Serial.println("entrou status");
            Serial.print("Status value: ");
            Serial.println(statusvalue);
            digitalWrite(buzzer,LOW);
            break;
            }
      }
          
     // for (i = 0; i <80; i++) // Wen a frequency sound
     // {
     //   digitalWrite (buzzer, HIGH) ;// send voice
     //   delay (1) ;// Delay 1ms
     //   digitalWrite (buzzer, LOW) ;// do not send voice
     //   delay (1) ;// delay ms
     // }
     // for (i = 0; i <100; i++) // Wen Qie out another frequency sound
     // {
     //   digitalWrite (buzzer, HIGH) ;// send voice
     //   delay (3) ;// delay 2ms
     //   digitalWrite (buzzer, LOW) ;// do not send voice
     //   delay (3) ;// delay 2ms
     //}
    }
     delay(20);}
     else {
  
        lcd.setCursor(0,1);
        lcd.print("offline          ");
        digitalWrite (ledPin,LOW);
        digitalWrite (buzzer, LOW);
        Serial.print("");
        Serial.print("Sensor Value: ");
        Serial.println(sensorValue );
        delay(20);
        
        while(online==1){
            myTime = millis();
            array_register[counter]=myTime;
            array_tipo[counter]=3;
            counter=counter+1;
            online=0;
        }
     }

}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
// print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
// print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}
