#include<ESP8266WiFi.h>
#include<LwipDhcpServer-NonOS.h>
#include<Servo.h>
const int MQ135_PIN = A0;     // Analog pin where MQ135 is connected
const int led = D0;
const int ENA = D5;
const int ENB = D6;
const int IN_1 = D8;
const int IN_2 = D7;
const int IN_3 = D4;
const int IN_4 = D3;

const int THRESHOLD = 124;    // Threshold for MQ-135 sensor value
Servo servo;  // servo at D2
WiFiClient Client;
WiFiServer server(80); 
 void setup(){
    Serial.begin(9600);
    WiFi.begin("MEGH","abcdefgh1234");
    while(WiFi.status() !=WL_CONNECTED)
    {
      Serial.print("..");
      delay(200);
    }
    Serial.println();
    Serial.println("NODE IS CONNECTED");
    Serial.println(WiFi.localIP());
    server.begin();
    pinMode(led, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);  
    pinMode(IN_1, OUTPUT);
    pinMode(IN_2, OUTPUT);
    pinMode(IN_3, OUTPUT);
    pinMode(IN_4, OUTPUT);
    servo.attach(D2); //D2
    servo.write(0);
  }
  void loop(){
    Client = server.available();
    int sensorValue = analogRead(MQ135_PIN); // Read the analog value from MQ135
    Serial.print("MQ135 Sensor Value: ");
    Serial.println(sensorValue);             // Print the sensor value to the Serial Monitor
    if(Client==1){
      String request =  Client.readStringUntil('\n');
      Serial.println(request);
      request.trim();
      if(request=="GET /led1off HTTP/1.1")
        {
        digitalWrite(led,LOW);///for home led
        }
      if(request=="GET /led1on HTTP/1.1")
        {
        digitalWrite(led,HIGH);
        }  
      if (sensorValue > THRESHOLD || request=="GET /fanon HTTP/1.1") {
        digitalWrite(IN_1, LOW);
        digitalWrite(IN_2, HIGH);
        analogWrite(ENA, 80);
      }
      else{
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);
      }
    // pump controls
      if(request=="GET /pumpon HTTP/1.1")
      {
        digitalWrite(IN_3, HIGH);
        digitalWrite(IN_4, LOW);
        analogWrite(ENB, 80);
      }
      if(request=="GET /pumpoff HTTP/1.1")
      {
        digitalWrite(IN_3, LOW);
        digitalWrite(IN_4, LOW);
        analogWrite(ENB, 300);
      }
      // servo controls
      if(sensorValue > 50 ||request=="GET /regulatoroff HTTP/1.1" ){
        servo.write(180); // Turn servo to 90 degrees
      } 
      else if(request=="GET /regulatoron HTTP/1.1"){
        int pos=0;
        servo.write(pos);
      }
      else {
        servo.write(0);  // Return servo to 0 degrees
      }
      delay(1000); // Delay for 1 second between readings
    }
Client.println("HTTP/1.1 200 OK");
Client.println("Content-Type: text/html");
Client.println("");
Client.println("<!DOCTYPE html>");
Client.println("<html lang=\"en\">");
Client.println("<head>");
Client.println("    <meta charset=\"UTF-8\">");
Client.println("    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
Client.println("    <title>Document</title>");
Client.println("    <style>");
Client.println("        .pages{");
Client.println("            height:100vh;");
Client.println("            width:98vw;");
Client.println("            background-color:#e0f4ff;");
Client.println("            display: flex;");
Client.println("            flex-direction: column;");
Client.println("            justify-content: space-around;");
Client.println("            align-content: center;");
Client.println("        }");
Client.println("        .heading{");
Client.println("            display: inline-block;");
Client.println("            align-items: start;");
Client.println("            font-size: 150px;");
Client.println("            text-align:center;");
Client.println("            vertical-align:top;");
Client.println("            color:#e89907;");
Client.println("            font-family: 'Courier New', Courier, monospace;");
Client.println("        }");
Client.println("        .buttons{");
Client.println("            background-color: #e0f4ff;");
Client.println("            display: flex;");
Client.println("            justify-content: space-evenly;");
Client.println("            align-items: center;");
Client.println("        }");
Client.println("        .rooms {");
Client.println("            height: 200px;");
Client.println("            width: 500px;");
Client.println("            display: flex;");
Client.println("            justify-content: space-evenly;");
Client.println("            align-items: center;");
Client.println("        }");
Client.println("        .accesories {");
Client.println("            background-color: rgb(154, 242, 161);");
Client.println("            height: 50px;");
Client.println("            width: 150px;");
Client.println("            border-radius: 25px;");
Client.println("            font-size: 25px;");
Client.println("            animation: back;");
Client.println("        }");
Client.println("        .reg {");
Client.println("            width: 200px;");
Client.println("            font-size: 22px;");
Client.println("        }");
Client.println("        .accesories:hover {");
Client.println("            background-color: rgb(21, 157, 21);");
Client.println("        }");
Client.println("        .accesories:active {");
Client.println("            background-color: rgb(157, 66, 21);");
Client.println("        }");
Client.println("        .text{");
Client.println("            display: flex;");
Client.println("            flex-direction: column-reverse;");
Client.println("            align-items: center;");
Client.println("            font-size: 45px;");
Client.println("            text-align: center;");
Client.println("            font-weight: 600;");
Client.println("            color:#b00b32;");
Client.println("            font-family: 'Courier New', Courier, monospace;");
Client.println("        }");
Client.println("    </style>");
Client.println("</head>");
Client.println("<body>");
// First page
Client.println("    <!--first page -->");
Client.println("    <div class=\"pages first-page\">");
Client.println("        <div class=\"heading\">");
Client.println("            BIT-AUTOMATION");
Client.println("        </div>");
Client.println("    </div>");
Client.println("    <hr>");
// Second page
Client.println("    <!-- second page -->");
Client.println("    <div class=\"pages\">");
Client.println("        <div class=\"heading\">");
Client.println("            HOME");
Client.println("        </div>");
Client.println("        <div class=\"buttons\">");
Client.println("            <div class=\"livingroom \">");
Client.println("                <div class=\"text\">LIGHT</div>");
Client.println("                <div class=\"rooms\">");
Client.println("                    <a href=\"/led1off\"><button class=\"led accesories\">OFF</button></a>");
Client.println("                    <a href=\"/led1on\"><button class=\"led accesories\">ON</button></a>");
Client.println("                </div>");
Client.println("            </div>");
Client.println("            <div class=\"hall\">");
Client.println("                <div class=\"text\">FAN</div>");
Client.println("                <div class=\"rooms\">");
Client.println("                    <a href=\"/fanoff\"><button class=\"fan accesories\">OFF</button></a>");
Client.println("                    <a href=\"/fanon\"><button class=\"fan accesories\">ON</button></a>");
Client.println("                </div>");
Client.println("            </div>");
Client.println("            <div class=\"kitchen \">");
Client.println("                <div class=\"text\">GAS REGULATOR</div>");
Client.println("                <div class=\"rooms\">");
Client.println("                    <a href=\"/regulatoron\"><button class=\"reg accesories\">ON</button></a>");
Client.println("                    <a href=\"/regulatoroff\"><button class=\"reg accesories\">OFF</button></a>");
Client.println("                </div>");
Client.println("            </div>");
Client.println("        </div>");
Client.println("    </div>");
Client.println("    <hr>");
// Third page
Client.println("    <!-- third page -->");
Client.println("    <div class=\"pages\">");
Client.println("        <div class=\"heading\">");
Client.println("            FARM");
Client.println("        </div>");
Client.println("        <div class=\" buttons\">");
Client.println("            <div class=\"farm\">");
Client.println("                <div class=\"text\">PUMP</div>");
Client.println("                <DIV class=\"rooms\">");
Client.println("                    <a href=\"/pumpoff\"><button class=\"led accesories\">OFF</button></a>");
Client.println("                    <a href=\"/pumpon\"><button class=\"led accesories\">ON</button></a>");
Client.println("                </DIV>");
Client.println("            </div>");
Client.println("        </div>");
Client.println("    </div>");
Client.println("</body>");
Client.println("</html>");

  }