 #include <SPI.h>  
 #include <Adb.h>  
 #define FW_PIN 3  
 #define BW_PIN 4  
 #define LF_PIN 5  
 #define RT_PIN 6  
 // Adb connection.  
 Connection * connection;  
 // Elapsed time for ADC sampling  
 long lastTime;  
 void actuate(int pin);  
 void turnLeft();  
 void turnRight();  
 // Event handler for the shell connection.   
 void adbEventHandler(Connection * connection, adb_eventType event, uint16_t length, uint8_t * data)  
 {  
  int i;  
  // Data packets contain two bytes, one for each servo, in the range of [0..180]  
  if (event == ADB_CONNECTION_RECEIVE)  
  {  
   Serial.println(data[0], DEC);  
   if(data[0] == 0x01) {  
     actuate(FW_PIN);  
   } else if(data[0] == 0x02) {  
     actuate(BW_PIN);   
   } else if(data[0] == 0x03) {  
     turnLeft();   
   } else if(data[0] == 0x04) {  
     turnRight();   
   }  
  }  
 }  
 void setup()  
 {  
  Serial.begin(9600);  
  // Note start time  
  lastTime = millis();  
  pinMode(FW_PIN, OUTPUT);  
  pinMode(BW_PIN, OUTPUT);  
  pinMode(LF_PIN, OUTPUT);  
  pinMode(RT_PIN, OUTPUT);  
  // Initialise the ADB subsystem.   
  ADB::init();  
  // Open an ADB stream to the phone's shell. Auto-reconnect  
  connection = ADB::addConnection("tcp:4567", true, adbEventHandler);   
 }  
 void loop()  
 {  
  lastTime = millis();  
  // Poll the ADB subsystem.  
  ADB::poll();  
  delay(50);  
 }  
 void actuate(int pin) {  
  digitalWrite(pin, HIGH);  
  delay(50);  
  digitalWrite(pin, LOW);   
 }  
 void turnLeft() {  
  digitalWrite(LF_PIN, HIGH);  
  actuate(FW_PIN);  
  digitalWrite(LF_PIN, LOW);  
 }  
 void turnRight() {  
  digitalWrite(RT_PIN, HIGH);  
  actuate(FW_PIN);  
  digitalWrite(RT_PIN, LOW);  
 }  
