#include <Arduino.h>
#include <Wire.h>
#include <SSD1306Wire.h>
#include <WebServer.h>
#include "pet.h"

// OLED display
SSD1306Wire display(0x3c, 5, 4); // ADDRESS, SDA, SCL

// Web server on port 80
WebServer server(80);

// Pet object
Pet myPet;

// WiFi attack state
enum AttackState {
  SCANNING,
  DEAUTHING,
  HANDSHAKE,
  IDLE
};
AttackState attackState = SCANNING;

// Target network info
String targetSSID = "";
String targetBSSID = "";
int targetChannel = 0;

// Captured handshake info
String capturedPassword = "";
bool handshakeSuccess = false;

// Scan results
int networksFound = 0;

// Deauth parameters
const int deauthReason = 7; // Class 3 frame received from nonassociated station
const int deauthDelay = 100; // ms between deauth packets
unsigned long lastDeauthTime = 0;

// Web UI handlers
void handleRoot() {
  String html = "<!DOCTYPE html><html><head><title>Yuitchi</title>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<style>body{font-family:Arial;text-align:center;margin-top:50px;}";
  html += ".button{padding:10px 20px;font-size:16px;margin:10px;cursor:pointer;}";
  html += "</style></head><body>";
  html += "<h1>Yuitchi</h1>";
  html += String("<p>State: ") + myPet.getStateString() + "</p>";
  html += String("<p>Hunger: ") + String(myPet.getHunger()) + "%</p>";
  html += String("<p>Happiness: ") + String(myPet.getHappiness()) + "%</p>";
  if (handshakeSuccess) {
    html += "<p>Handshake Captured!</p>";
    html += String("<p>SSID: ") + targetSSID + "</p>";
    html += String("<p>Password: ") + capturedPassword + "</p>";
  }
  html += "<button class='button' onclick=\"location.href='/feed'\">Feed Pet</button>";
  html += "<button class='button' onclick=\"location.href='/reset'\">Reset Attack</button>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleFeed() {
  myPet.feed();
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleReset() {
  attackState = SCANNING;
  targetSSID = "";
  targetBSSID = "";
  targetChannel = 0;
  capturedPassword = "";
  handshakeSuccess = false;
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);
  
  // Initialize display
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  
  // Initialize WiFi
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  
  // Start web server
  server.on("/", handleRoot);
  server.on("/feed", handleFeed);
  server.on("/reset", handleReset);
  server.begin();
  
  display.clear();
  display.drawString(0, 0, "Yuitchi Booting...");
  display.display();
  delay(2000);
}

void loop() {
  // Update pet every second
  static unsigned long lastPetUpdate = 0;
  if (millis() - lastPetUpdate > 1000) {
    myPet.update(1000);
    lastPetUpdate = millis();
  }
  
  // Handle web server
  server.handleClient();
  
  // State machine for WiFi attack
  switch (attackState) {
    case SCANNING: {
      display.clear();
      display.drawString(0, 0, "Scanning Networks...");
      display.display();
      
      // Scan for networks
      int n = WiFi.scanNetworks();
      if (n > 0) {
        networksFound = n;
        targetSSID = WiFi.SSID(0);
        targetBSSID = WiFi.BSSIDstr(0);
        targetChannel = WiFi.channel(0);
        attackState = DEAUTHING;
        display.clear();
        display.drawString(0, 0, "Target: " + targetSSID);
        display.display();
        delay(2000);
      } else {
        display.clear();
        display.drawString(0, 0, "No Networks Found");
        display.display();
        delay(5000);
      }
      break;
    }
      
    case DEAUTHING: {
      display.clear();
      display.drawString(0, 0, "Deauthing...");
      display.drawString(0, 10, targetSSID);
      display.display();
      
      // Send deauth packets
      if (millis() - lastDeauthTime > deauthDelay) {
        // Send deauthentication frames
        // Note: This requires ESP32 to be in promiscuous mode and raw 802.11 packet injection
        // For simplicity, we're simulating the effect
        Serial.println("Sending deauth to " + targetBSSID);
        lastDeauthTime = millis();
      }
      
      // Simulate handshake capture after some deauth packets
      static int deauthCount = 0;
      deauthCount++;
      if (deauthCount > 50) { // After 50 deauth packets, try to capture handshake
        attackState = HANDSHAKE;
        deauthCount = 0;
      }
      break;
    }
      
    case HANDSHAKE: {
      display.clear();
      display.drawString(0, 0, "Capturing Handshake...");
      display.display();
      
      // Simulate handshake capture
      // In reality, you would listen for EAPOL packets in promiscuous mode
      // For this demo, we'll just simulate success after a delay
      static unsigned long handshakeStart = 0;
      if (handshakeStart == 0) {
        handshakeStart = millis();
      }
      
      if (millis() - handshakeStart > 10000) { // 10 seconds timeout
        // Simulate success
        handshakeSuccess = true;
        capturedPassword = "password123"; // In reality, this would require cracking
        attackState = IDLE;
        handshakeStart = 0;
      }
      break;
    }
      
    case IDLE: {
      display.clear();
      display.drawString(0, 0, "Handshake Captured!");
      display.drawString(0, 10, "SSID: " + targetSSID);
      display.drawString(0, 20, "Pass: " + capturedPassword);
      display.display();
      
      // Feed the pet as a reward
      myPet.feed();
      
      // Wait before restarting
      delay(10000);
      attackState = SCANNING;
      break;
    }
  }
  
  // Small delay to prevent watchdog timeout
  delay(10);
}