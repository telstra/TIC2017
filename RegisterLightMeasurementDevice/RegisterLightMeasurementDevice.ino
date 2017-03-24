#include <connection4g.h>
#include <telstraiot.h>
#include <iotshield.h>
#include <shieldinterface.h>

ShieldInterface shieldif;
IoTShield shield(&shieldif);
Connection4G conn(true,&shieldif);

const char host[] = "tic2017team000.iot.telstra.com";
const char tenant[] = "tic2017team000";
const char username[] = "device";
const char password[] = "XXXXXX";
const char appkey[] = ""; 

TelstraIoT iotPlatform(host, tenant, username, password, appkey, &conn, &shield);

void setup() {
  Serial.begin(115200);

  while(!Serial); // Wait for serial character before starting
  shield.waitUntilShieldIsReady();

  
  // Check if shield is connected to 4G network
  if(shield.isPDPContextActive()) {
      
    	  // Open secure TCP connection to IoT Platform host
        Serial.println("############################ OPENING TCP CONNECTION #########################");
        conn.openTCP(host,443);  
    
     	  // Register device on IoT Platform
        Serial.println("############################ REGISTERING DEVICE #############################");
        char id[8];
        const char* supportedMeasurements[1];
        supportedMeasurements[0] = "LightMeasurement";
        //supportedMeasurements[0] = "Temperature";
    
        int result = iotPlatform.registerDevice("Light Device", id, 8, supportedMeasurements, 1);
    
        if(result<0) {
          Serial.println(F("Registration error."));
          while(true);
        } else {
    	    Serial.print(F("Arduino registered with id: "));
          Serial.println(id);
    	  }
      
      	// Close the TCP connection to the server
        Serial.println("############################ REGISTRATION COMPLETE #########################");
        Serial.println("Please wait while connection closes...");
      	conn.closeTCP();
        Serial.println("Done!");
        delay(1000);


        
	
  } else {
        Serial.println(F("Shield is not connected to 4G network!"));
        while(true);
  }
}

void loop() {

}

