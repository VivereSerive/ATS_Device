// --------------------------------------------------------------
// Air Tracking Device: FreeRTOS Firmware
// --------------------------------------------------------------

// -- Libraries -- //
#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WebSocketsClient.h> // Markus Sattler
#include <PMS.h>
#include <DHT.h>
#include <SensirionI2cScd4x.h>

// -- Parameters -- //
// Pin Assignments
// TODO: Update Assignments
#define I2C_SDA_PIN    
#define I2C_SCL_PIN   

#define PMS_RX_PIN    
#define PMS_TX_PIN    

#define DHT11_PIN     
#define DHT11_TYPE    

#define MQ135_PIN     

#define BUTTON_PIN    
#define LED_RED_PIN   
#define LED_GREEN_PIN 

// Network Config
// TODO: Update Config
const char* SSID = "";
const char* SSID_KEY = "";

const char* SERVER = "";
const uint16_t SERVER_PORT = 5000;

const char* WS_SERVER_ADDR = "";
const char* HTTP_POST_SERVER_ADDR = "";

const char* API_KEY_HEADER = "";
const char* API_KEY_VAL = "";

// Timing Config
#define WS_PUSH_INTERVAL_MS     50      // Live Data
#define HTTP_POST_INTERVAL_MS   60000   // Once a Minute Over Time Data
#define LOGGING_INTERVAL_MS     5000    // How often DataLoggingTask Logs Data
#define BUTTON_POLL_INTERVAL_MS 20      // Debounce polling rate
#define LED_POLL_INTERVAL_MS    300     // Also used in LED blinking

// Data Structures
struct PMData{
  uint16_t pm1_0;
  uint16_t pm2_5;
  uint16_t pm10;
};

// Library Objects
WebSocketsClient WS;

// -- FreeRTOS -- //
// TODO: Queue Handles

// Task Handles
TaskHandle_t RealTimeDataTransferHandle = NULL; // WebSocket
TaskHandle_t OverTimeDataTransferHandle = NULL; // HTTP POST
TaskHandle_t DataLoggingHandle = NULL;
TaskHandle_t ConnectionStatusHandle = NULL; // 2x LEDs
TaskHandle_t DeviceResetHandle = NULL; // Momentary PushSwitch

TaskHandle_t PM25Handle = NULL; // PMS7003
TaskHandle_t CO2Handle = NULL; // SCD41
TaskHandle_t TempHumidHandle = NULL; // DHT11
TaskHandle_t GasHandle = NULL; // MQ135

// Task Function Prototype
void DataLoggingTask(void *parameter);
void RealTimeDataTransferTask(void *parameter);
void OverTImeDataTransferTask(void *parameter);
void ConnectionStatusTask(void *parameter);
void DeviceResetTask(void *paramater);

void PM25Task(void *parameter);
void CO2Task(void *parameter);
void TempHumidTask(void *parameter);
void GasTask(void *parameter);

void connectToWiFi();
void webSocketEventHandler(WStype_t type, uint8_t * payload, size_t length);
String compileDataJson();

// Non-Task Functions
void connectToWiFi(){

}

String compileDataJson(){
  
}

void webSocketEventHandler(WStype_t type, uint8_t * payload, size_t length){
  
}

// Data Processing Task Functions
void DataLoggingTask(void *parameter){
  for (;;) { // Create an Infinite Loop
    // Place here the functionality of the task
  }
}

//  Communication Task Functions
void RealTimeDataTransferTask(void *parameter){
  // WebSocket Feature
  for (;;) { // Create an Infinite Loop
    // Place here the functionality of the task
  }
}

void OverTimeDataTransferTask(void *parameter){
  // HTTP POST Feature
  for (;;) { // Create an Infinite Loop
    // Place here the functionality of the task
  }
}

// Peripheral Task Functions
void ConnectionStatusTask(void *parameter){
  for(;;) { // Create Infinite Loop
    // Place here functionality
  }
}

void DeviceResetTask(void *parameter){
  for (;;) { // Create Infinite Loop
    // Place Here Functionality
  }
}


// Sensor Task Functions
void PM25Task(void *parameter){
  for (;;) { // Create an Infinite Loop
    // Place here the functionality of the task
  }
}

void CO2Task(void *parameter){
  for (;;) { // Create an Infinite Loop
    // Place here the functionality of the task
  }
}

void TempHumidTask(void *parameter){
  for (;;) { // Create an Infinite Loop
    // Place here the functionality of the task
  }
}

void GasTask(void *parameter){
  for (;;) { // Create an Infinite Loop
    // Place here the functionality of the task
  }
}



// -- Setup -- //
void setup(){
    Serial.begin(115200);

    // -- Init Communication Tasks -- //
    xTaskCreatePinnedToCore(
        DataLoggingTask,                    // Task Function
        "Data Logging",                 // Task Name
        10000,                          // Task Size
        NULL,                           // Parameters
        3,                              // Highest Priority
        &DataLoggingHandle,               // Task Handle
        0                               // Core
    );

    xTaskCreatePinnedToCore(
        RealTimeDataTransferTask,           // Task Function
        "Real Time Data Transfer",      // Task Name
        10000,                          // Task Size
        NULL,                           // Parameters
        2,                              // Second Highest Priority
        &RealTimeDataTransferHandle,      // Task Handle
        0                               // Core
    );

    xTaskCreatePinnedToCore(
        OverTimeDataTransferTask,           // Task Function
        "Over Time Data Transfer",      // Task Name
        10000,                          // Task Size
        NULL,                           // Parameters
        1,                              // Lowest Highest Priority
        &OverTimeDataTransferHandle,      // Task Handle
        0                               // Core
    );

    xTaskCreatePinnedToCore(
        ConnectionStatusTask,           // Task Function
        "LED Connection Status",      // Task Name
        10000,                          // Task Size
        NULL,                           // Parameters
        1,                              // Lowest Highest Priority
        &ConnectionStatusHandle,      // Task Handle
        0                               // Core
    );

    xTaskCreatePinnedToCore(
        DeviceResetTask,           // Task Function
        "Button Device Reset",      // Task Name
        10000,                          // Task Size
        NULL,                           // Parameters
        1,                              // Lowest Highest Priority
        &DeviceResetHandle,      // Task Handle
        0                               // Core
    );

    // -- Init Sensor Tasks -- //
    xTaskCreatePinnedToCore(
        PM25Task,           // Task Function
        "PM25",      // Task Name
        10000,                          // Task Size
        NULL,                           // Parameters
        1,                              // Priority
        &PM25Handle,      // Task Handle
        1                               // Core
    );
    xTaskCreatePinnedToCore(
        CO2Task,           // Task Function
        "CO2",      // Task Name
        10000,                          // Task Size
        NULL,                           // Parameters
        1,                              // Priority
        &CO2Handle,      // Task Handle
        1                               // Core
    );
    xTaskCreatePinnedToCore(
        TempHumidTask,           // Task Function
        "Humidity",      // Task Name
        10000,                          // Task Size
        NULL,                           // Parameters
        1,                              // Priority
        &TempHumidHandle,      // Task Handle
        1                               // Core
    );
    xTaskCreatePinnedToCore(
        GasTask,           // Task Function
        "Gas",      // Task Name
        10000,                          // Task Size
        NULL,                           // Parameters
        1,                              // Priority
        &GasHandle,      // Task Handle
        1                               // Core
    );
}

// -- Loop -- //
void loop(){
    // Program is handled by FreeRTOS Task Handler
}