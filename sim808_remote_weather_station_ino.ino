         /////////////////////////////////////////////  
        //    IoT Weather Station Predicting       //
       //    Rainfall Intensity w/ TensorFlow     //
      //         ------------------------        //
     //           Arduino Uno (SIM808)          //           
    //             by Kutluhan Aktar           // 
   //                                         //
  /////////////////////////////////////////////

//
// Collates weather data on Google Sheets and interprets it with a neural network built in TensorFlow to make predictions on the rainfall intensity. 
//
// For more information:
// https://www.theamplituhedron.com/projects/IoT_Weather_Station_Predicting_Rainfall_Intensity_with_TensorFlow
//
// Connections
// Arduino Uno:           
//                                SIM808 GPS/GPRS/GSM Shield For Arduino
// D0  --------------------------- RX
// D1  --------------------------- TX
// D12 --------------------------- POWER          
//                                Weather Station
// 5V  --------------------------- 5V
// D5  --------------------------- RX
// D6  --------------------------- TX
// GND --------------------------- GND


// Include required libraries:
#include <DFRobot_sim808.h>
#include <SoftwareSerial.h>

// Define the sim808.
DFRobot_SIM808 sim808(&Serial);

// Define weather station settings:
char databuffer[35];
double temp;
int transferring = 0;

// Define the serial connection pins - RX and TX.
SoftwareSerial Serial_1(6, 5); // (Rx, Tx)

void setup() {
  // Wait until connected.
  delay(1000);
  // Initiate serial ports:
  Serial.begin(9600);
  Serial_1.begin(9600);

  //******** Initialize sim808 module *************
  while(!sim808.init()) {
     delay(1000);
     Serial.print("Sim808 init error\r\n");
  }
  delay(2000);
  // Continue if the SIM808 Module is working accurately.
  Serial.println("Sim808 init success");
  delay(5000);
}

void loop() {
  // Get data from the remote weather station:
  getBuffer(); 
  // Debug the information and create the link:
  String weather_data_1 = "wd=" + String(WindDirection()) + "&a_ws=" + String(WindSpeedAverage()) + "&m_ws=" + String(WindSpeedMax());
  String weather_data_2 = "&1_rf=" + String(RainfallOneHour()) + "&24_rf=" + String(RainfallOneDay()) + "&tem=" + String(Temperature());
  String weather_data_3 = "&hum=" + String(Humidity()) + "&b_pr=" + String(BarPressure());
  Serial.print("Weather Data => " + weather_data_1);
  Serial.print(weather_data_2);
  Serial.println(weather_data_3);
  Serial.println("Buffer => " + String(databuffer));
  // Send data packets every 5 minutes to the server.
  transferring++; Serial.println("Time => " + String(transferring) + "s / " + String(int(5*60)) + "s\n\n");
  if(transferring == 5*60){
    //*********** Attempt DHCP *******************
    while(!sim808.join(F("cmnet"))) {
      Serial.println("Sim808 join network error!");
      delay(2000);
    }
    //************ Successful DHCP ****************
    delay(5000);
    Serial.println("Successful DHCP");
    //*********** Establish a TCP connection ************
    if(!sim808.connect(TCP,"192.168.1.24", 80)) { // Change it with your server.
      Serial.println("Connection Error");
    }else{
      Serial.println("Connection OK");
    }
    delay(2000);
    //*********** Send a GET request *****************
    String line = "GET /remote_weather_station/?" + weather_data_1 + weather_data_2 + weather_data_3 + " HTTP/1.0\r\n\r\n";
    Serial.println(line);
    char buffer[512];
    // Convert the line from string to char array to make an HTTP Get Request with the SIM808.
    char web_hook[110];
    String_to_Char(line, 110, web_hook);
    sim808.send(web_hook, sizeof(web_hook)-1);
    while (true) {
      int ret = sim808.recv(buffer, sizeof(buffer)-1);
      if (ret <= 0){
          Serial.println("Fetch Over...");
          break; 
      }
      // Uncomment to view the response in the serial monitor.
      /*
      buffer[ret] = '\0';
      Serial.print("Recv: ");
      Serial.print(ret);
      Serial.print(" bytes: ");
      Serial.println(buffer);
      */
      Serial.println("\nData Send");
      break;
    }
    //************* Close TCP or UDP connections **********
    sim808.close();
    //*** Disconnect wireless connection, Close Moving Scene *******
    sim808.disconnect();
    // Exit.
    transferring = 0;  
  }
  // Wait 1 second...
  delay(1000);
}

// WEATHER STATION
void getBuffer(){
  int index;
  for (index = 0;index < 35;index ++){
    if(Serial_1.available()){
      databuffer[index] = Serial_1.read();
      if (databuffer[0] != 'c'){
        index = -1;
      }
    }
    else{
      index --;
    }
  }
}

int transCharToInt(char *_buffer, int _start, int _stop){
  int _index;
  int result = 0;
  int num = _stop - _start + 1;
  int _temp[num];
  for (_index = _start;_index <= _stop;_index ++){
    _temp[_index - _start] = _buffer[_index] - '0';
    result = 10*result + _temp[_index - _start];
  }
  return result;
}

int WindDirection(){ return transCharToInt(databuffer,1,3); } // Wind Direction (deg)

float WindSpeedAverage(){ temp = 0.44704 * transCharToInt(databuffer,5,7); return temp; } // Average Air Speed (1 minute)

float WindSpeedMax(){ temp = 0.44704 * transCharToInt(databuffer,9,11); return temp; } //Max Air Speed (5 minutes)

float Temperature(){ temp = (transCharToInt(databuffer,13,15) - 32.00) * 5.00 / 9.00; return temp; } // Temperature ("C")

float RainfallOneHour(){ temp = transCharToInt(databuffer,17,19) * 25.40 * 0.01; return temp; } // Rainfall (1 hour)

float RainfallOneDay(){ temp = transCharToInt(databuffer,21,23) * 25.40 * 0.01; return temp; } // Rainfall (24 hours)

int Humidity(){ return transCharToInt(databuffer,25,26); } // Humidity (%)

float BarPressure(){ temp = transCharToInt(databuffer,28,32); return temp / 10.00; } // Barometric Pressure (hPA)

void String_to_Char(String _String, int _size, char _convert[]){
  for(int i=0;i<_size;i++){
    _convert[i] = _String[i];
  }
}
