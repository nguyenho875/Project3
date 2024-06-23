//=====[Libraries]=============================================================

#include "arm_book_lib.h"

#include "wifi_aux.h"

#include "non_blocking_delay.h"
#include "serial_com.h"

//=====[Declaration of private defines]========================================

#define DELAY_10_SECONDS        10000
#define DELAY_5_SECONDS         5000
#define DELAY_2_SECONDS         2000

#define IP_MAX_LENGTH (15 + 1)

//=====[Declaration of private data types]=====================================

typedef enum {
   WIFI_STATE_INIT,
   WIFI_STATE_SEND_AT,
   WIFI_STATE_WAIT_AT,
   WIFI_STATE_SEND_CWMODE,
   WIFI_STATE_WAIT_CWMODE,
   WIFI_STATE_SEND_CWJAP_IS_SET,
   WIFI_STATE_WAIT_CWJAP_IS_SET,
   WIFI_STATE_SEND_CWJAP_SET,
   WIFI_STATE_WAIT_CWJAP_SET_1,
   WIFI_STATE_WAIT_CWJAP_SET_2,
   WIFI_STATE_SEND_CIFSR,
   WIFI_STATE_WAIT_CIFSR,
   WIFI_STATE_LOAD_IP,
   WIFI_STATE_SEND_CIPMUX,
   WIFI_STATE_WAIT_CIPMUX,
   WIFI_STATE_SEND_CIPSERVER,
   WIFI_STATE_WAIT_CIPSERVER,
   WIFI_STATE_SEND_CIPSTATUS,
   WIFI_STATE_WAIT_CIPSTATUS_STATUS_3,
   WIFI_STATE_WAIT_CIPSTATUS,
   WIFI_STATE_WAIT_GET_ID,
   WIFI_STATE_WAIT_CIPSTATUS_OK,
   WIFI_STATE_SEND_CIPSEND,
   WIFI_STATE_WAIT_CIPSEND,
   WIFI_STATE_SEND_HTML,
   WIFI_STATE_WAIT_HTML,
   WIFI_STATE_SEND_CIPCLOSE,
   WIFI_STATE_WAIT_CIPCLOSE,
   WIFI_STATE_IDLE,
   WIFI_STATE_ERROR,
   WIFI_STATE_WAIT_RESET
} wifiComState_t;

//=====[Declaration and initialization of public global objects]===============

UnbufferedSerial uartWifi( PC_12, PD_2, 115200 );
nonBlockingDelay wifiComDelay(0);
SerialCom pc_(USBTX, USBRX, 115200);
DigitalOut reset(PG_2, ON);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static const char responseOk[] = "OK";
static const char responseCwjapOk[] = "+CWJAP:";
static const char responseCwjap1[] = "WIFI CONNECTED";
static const char responseCwjap2[] = "WIFI GOT IP";
static const char responseCifsr[] = "+CIFSR:STAIP,\"";
static const char responseStatus3[] = "STATUS:3";
static const char responseCipstatus[] = "+CIPSTATUS:";
static const char responseSendOk[] = "SEND OK";
static const char responseCipclose[] = "CLOSED";

static int currentConnectionId;
static char wifiComApSsid[AP_SSID_MAX_LENGTH] = "Telecentro-5401";
static char wifiComApPassword[AP_PASSWORD_MAX_LENGTH] = "Z2NKJZ3WYJFD";
static char wifiComIpAddress[IP_MAX_LENGTH];

static const char* wifiComExpectedResponse;
static wifiComState_t wifiComState;

static const char htmlCode [] =
   "<!doctype html> <html> <body> Hello! </body> </html>"
   ;

//=====[Declarations (prototypes) of private functions]========================

static bool isExpectedResponse();
bool wifiComCharRead( char* receivedChar );
void wifiComStringWrite( const char* str );

//=====[Implementations of public functions]===================================

void wifiComSetWiFiComApSsid( char * ApSsid )
{
    strncpy(wifiComApSsid, ApSsid, AP_SSID_MAX_LENGTH);
}

void wifiComSetWiFiComApPassword( char * ApPassword )
{
    strncpy(wifiComApPassword, ApPassword, AP_PASSWORD_MAX_LENGTH );
}

char * wifiComGetIpAddress()
{
   return wifiComIpAddress;
}

void wifiComRestart()
{
    wifiComState = WIFI_STATE_INIT;
}

void wifiComInit()
{
    wifiComState = WIFI_STATE_INIT;
}

void wifiComUpdate()
{
   int lengthOfHtmlCode;
   static char receivedCharWifiCom;
   static int IpStringPositionIndex;
   char strToSend[50] = "";

   switch (wifiComState) {

      case WIFI_STATE_INIT:
         wifiComDelay.Start(DELAY_5_SECONDS);
         //nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
         wifiComState = WIFI_STATE_SEND_AT;
      break;

      case WIFI_STATE_SEND_AT:
         if(wifiComDelay.Read()){
         //if (nonBlockingDelayRead(&wifiComDelay)) {
            wifiComStringWrite( "AT\r\n" );
            wifiComExpectedResponse = responseOk;
            wifiComDelay.Start(DELAY_5_SECONDS);
            //nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_WAIT_AT;
         }
      break;

      case WIFI_STATE_WAIT_AT:
         if (isExpectedResponse()) {
            wifiComDelay.Start(DELAY_5_SECONDS);
            //nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_SEND_CWMODE;
            pc_.string_write("AT responded\r\n");
         }
         if(wifiComDelay.Read()){
         //if (nonBlockingDelayRead(&wifiComDelay)) {
            pc_.string_write("AT command not responded ");
            pc_.string_write("correctly\r\n");
            wifiComState = WIFI_STATE_ERROR;
         }
      break;

      case WIFI_STATE_SEND_CWMODE:
         if(wifiComDelay.Read()){
         //if (nonBlockingDelayRead(&wifiComDelay)) {
            wifiComStringWrite( "AT+CWMODE=1\r\n" );
            wifiComExpectedResponse = responseOk;
            wifiComDelay.Start(DELAY_5_SECONDS);
            //nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_WAIT_CWMODE;
         }
      break;

      case WIFI_STATE_WAIT_CWMODE:
         if (isExpectedResponse()) {
            wifiComDelay.Start(DELAY_5_SECONDS);
            //nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_SEND_CWJAP_IS_SET;
            pc_.string_write("AT+CWMODE=1 responded\r\n");
         }
         if(wifiComDelay.Read()){
         //if (nonBlockingDelayRead(&wifiComDelay)) {
            pc_.string_write("AT+CWMODE=1 command not ");
            pc_.string_write("responded correctly\r\n");
            wifiComState = WIFI_STATE_ERROR;
         }
      break;

      case WIFI_STATE_SEND_CWJAP_IS_SET:
         if(wifiComDelay.Read()){
         //if (nonBlockingDelayRead(&wifiComDelay)) {
            wifiComStringWrite( "AT+CWJAP?\r\n" );
            wifiComExpectedResponse = responseCwjapOk;
            wifiComDelay.Start(DELAY_5_SECONDS);
            //nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_WAIT_CWJAP_IS_SET;
         }
      break;

      case WIFI_STATE_WAIT_CWJAP_IS_SET:
         if (isExpectedResponse()) {
            wifiComExpectedResponse = responseOk;
            wifiComState = WIFI_STATE_SEND_CIFSR;
            pc_.string_write( "AT+CWJAP? responded: connected\r\n" );
         }
         if(wifiComDelay.Read()){
         //if (nonBlockingDelayRead(&wifiComDelay)) {
            wifiComDelay.Start(DELAY_5_SECONDS);
            //nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_SEND_CWJAP_SET;
         }
      break;

      case WIFI_STATE_SEND_CWJAP_SET:
         if(wifiComDelay.Read()){
         //if (nonBlockingDelayRead(&wifiComDelay)) {
            wifiComStringWrite( "AT+CWJAP=\"" );
            wifiComStringWrite( wifiComApSsid );
            wifiComStringWrite( "\",\"" );
            wifiComStringWrite( wifiComApPassword );
            wifiComStringWrite( "\"" );
            wifiComStringWrite( "\r\n" );
            wifiComExpectedResponse = responseCwjap1;
            wifiComDelay.Start(DELAY_10_SECONDS);
            //nonBlockingDelayWrite(&wifiComDelay, DELAY_10_SECONDS);
            wifiComState = WIFI_STATE_WAIT_CWJAP_SET_1;
         }
      break;

      case WIFI_STATE_WAIT_CWJAP_SET_1:
         if (isExpectedResponse()) {
            wifiComExpectedResponse = responseCwjap2;
            wifiComState = WIFI_STATE_WAIT_CWJAP_SET_2;
            pc_.string_write( "AT+CWJAP= responded stage 1\r\n" );
         }
         if(wifiComDelay.Read()){
         //if (nonBlockingDelayRead(&wifiComDelay)) {
            pc_.string_write("Error in state: ");
            pc_.string_write("WIFI_STATE_WAIT_CWJAP_SET_1\r\n");
            pc_.string_write("Check Wi-Fi AP credentials ");
            pc_.string_write("and restart\r\n");
            wifiComState = WIFI_STATE_ERROR;
         }
         break;

      case WIFI_STATE_WAIT_CWJAP_SET_2:
         if (isExpectedResponse()) {
            wifiComState = WIFI_STATE_SEND_CIFSR;
            pc_.string_write( "AT+CWJAP= responded stage 2\r\n" );
         }
         if(wifiComDelay.Read()){
         //if (nonBlockingDelayRead(&wifiComDelay)) {
            pc_.string_write("Error in state: ");
            pc_.string_write("WIFI_STATE_WAIT_CWJAP_SET_2\r\n");
            pc_.string_write("Check Wi-Fi AP credentials ");
            pc_.string_write("and restart\r\n");
            wifiComState = WIFI_STATE_ERROR;
         }
      break;

      case WIFI_STATE_SEND_CIFSR:
         if(wifiComDelay.Read()){
         //if (nonBlockingDelayRead(&wifiComDelay)) {
            wifiComStringWrite( "AT+CIFSR\r\n" );
            wifiComExpectedResponse = responseCifsr;
            wifiComDelay.Start(DELAY_5_SECONDS);
            //nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_WAIT_CIFSR;
         }
      break;

      case WIFI_STATE_WAIT_CIFSR:
         if (isExpectedResponse()) {
            wifiComState = WIFI_STATE_LOAD_IP;
            IpStringPositionIndex = 0;
            pc_.string_write( "AT+CIFSR responded\r\n" );
         }
         if(wifiComDelay.Read()){
         //if (nonBlockingDelayRead(&wifiComDelay)) {
            pc_.string_write("AT+CIFSR command not responded ");
            pc_.string_write("correctly\r\n");
            wifiComState = WIFI_STATE_ERROR;
         }
      break;

      case WIFI_STATE_LOAD_IP:
         if (wifiComCharRead(&receivedCharWifiCom)) {
            if ( (receivedCharWifiCom != '"') && 
               (IpStringPositionIndex < IP_MAX_LENGTH) ) {
               wifiComIpAddress[IpStringPositionIndex] = receivedCharWifiCom;
               IpStringPositionIndex++;
            } else {
               wifiComIpAddress[IpStringPositionIndex] = '\0';
               pc_.string_write("IP address assigned correctly\r\n\r\n");
               wifiComState = WIFI_STATE_SEND_CIPMUX;
            }
         }
      break;

      case WIFI_STATE_SEND_CIPMUX:
         if(wifiComDelay.Read()){
         //if (nonBlockingDelayRead(&wifiComDelay)) {
            wifiComStringWrite( "AT+CIPMUX=1\r\n" );
            wifiComExpectedResponse = responseOk;
            wifiComDelay.Start(DELAY_5_SECONDS);
            //nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_WAIT_CIPMUX;
         }
      break;

      case WIFI_STATE_WAIT_CIPMUX:
         if (isExpectedResponse()) {
            wifiComDelay.Start(DELAY_5_SECONDS);
            //nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_SEND_CIPSERVER;
         }
         if(wifiComDelay.Read()){
         //if (nonBlockingDelayRead(&wifiComDelay)) {
            pc_.string_write("AT+CIPMUX=1 command not ");
            pc_.string_write("responded correctly\r\n");
            wifiComState = WIFI_STATE_ERROR;
         }
      break;

      case WIFI_STATE_SEND_CIPSERVER:
         if(wifiComDelay.Read()){
         //if (nonBlockingDelayRead(&wifiComDelay)) {
            wifiComStringWrite( "AT+CIPSERVER=1,80\r\n" );
            wifiComExpectedResponse = responseOk;
            wifiComDelay.Start(DELAY_5_SECONDS);
            //nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_WAIT_CIPSERVER;
         }
      break;

      case WIFI_STATE_WAIT_CIPSERVER:
         if (isExpectedResponse()) {
            wifiComDelay.Start(DELAY_5_SECONDS);
            //nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_SEND_CIPSTATUS;
         }
         if(wifiComDelay.Read()){
         //if (nonBlockingDelayRead(&wifiComDelay)) {
         pc_.string_write("AT+CIPSERVER=1,80 command not ");
         pc_.string_write("responded correctly\r\n");
         wifiComState = WIFI_STATE_ERROR;
         }
      break;

      case WIFI_STATE_SEND_CIPSTATUS:
         if(wifiComDelay.Read()){
         //if (nonBlockingDelayRead(&wifiComDelay)) {
            wifiComStringWrite( "AT+CIPSTATUS\r\n" );
            wifiComExpectedResponse = responseStatus3;
            wifiComDelay.Start(DELAY_5_SECONDS);
            //nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_WAIT_CIPSTATUS_STATUS_3;
         }
      break;

      case WIFI_STATE_WAIT_CIPSTATUS_STATUS_3:
         if (isExpectedResponse()) {
            wifiComDelay.Start(DELAY_5_SECONDS);
            //nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComExpectedResponse = responseCipstatus;
            wifiComState = WIFI_STATE_WAIT_CIPSTATUS;
         }
         if(wifiComDelay.Read()){
         //if (nonBlockingDelayRead(&wifiComDelay)) {
            wifiComDelay.Start(DELAY_5_SECONDS);
            //nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_SEND_CIPSTATUS;
         }
      break;

      case WIFI_STATE_WAIT_CIPSTATUS:
         if (isExpectedResponse()) {
            wifiComState = WIFI_STATE_WAIT_GET_ID;
         }
         if(wifiComDelay.Read()){
         //if (nonBlockingDelayRead(&wifiComDelay)) {
            wifiComDelay.Start(DELAY_5_SECONDS);
            //nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_SEND_CIPSTATUS;
         }
      break;

      case WIFI_STATE_WAIT_GET_ID:
         if( wifiComCharRead(&receivedCharWifiCom) ){
            currentConnectionId = receivedCharWifiCom;
            wifiComExpectedResponse = responseOk;
            wifiComState = WIFI_STATE_WAIT_CIPSTATUS_OK;
         }
      break;

      case WIFI_STATE_WAIT_CIPSTATUS_OK:
         if (isExpectedResponse()) {
            wifiComState = WIFI_STATE_SEND_CIPSEND;
         }
         if(wifiComDelay.Read()){
         //if (nonBlockingDelayRead(&wifiComDelay)) {
            wifiComDelay.Start(DELAY_5_SECONDS);
            //nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_SEND_CIPSTATUS;
         }
      break;

      case WIFI_STATE_SEND_CIPSEND:
         lengthOfHtmlCode = (strlen(htmlCode));
         sprintf( strToSend, "AT+CIPSEND=%c,%d\r\n", 
                  currentConnectionId, lengthOfHtmlCode );
         wifiComStringWrite( strToSend );
         wifiComState = WIFI_STATE_WAIT_CIPSEND;
         wifiComExpectedResponse = responseOk;
      break;

      case WIFI_STATE_WAIT_CIPSEND:
         if (isExpectedResponse()) {
            wifiComDelay.Start(DELAY_5_SECONDS);
            //nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_SEND_HTML;
         }
         if(wifiComDelay.Read()){
         //if (nonBlockingDelayRead(&wifiComDelay)) {
            wifiComDelay.Start(DELAY_5_SECONDS);
            //nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_SEND_CIPSTATUS;
         }
      break;

      case WIFI_STATE_SEND_HTML:
        wifiComStringWrite( htmlCode );
        wifiComState = WIFI_STATE_WAIT_HTML;
        wifiComExpectedResponse = responseSendOk;
      break;

      case WIFI_STATE_WAIT_HTML:
         if (isExpectedResponse()) {
            wifiComDelay.Start(DELAY_5_SECONDS);
            //nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_SEND_CIPCLOSE;
         }
         if(wifiComDelay.Read()){
         //if (nonBlockingDelayRead(&wifiComDelay)) {
            wifiComDelay.Start(DELAY_5_SECONDS);
            //nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_SEND_CIPSEND;
         }
      break;

      case WIFI_STATE_SEND_CIPCLOSE:
         if(wifiComDelay.Read()){
         //if (nonBlockingDelayRead(&wifiComDelay)) {
            sprintf( strToSend, "AT+CIPCLOSE=%c\r\n", currentConnectionId );
            wifiComStringWrite( strToSend );
            wifiComExpectedResponse  = responseCipclose;
            wifiComDelay.Start(DELAY_5_SECONDS);
            //nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_WAIT_CIPCLOSE;
         }
      break;

      case WIFI_STATE_WAIT_CIPCLOSE:
         if (isExpectedResponse()) {
            wifiComDelay.Start(DELAY_5_SECONDS);
            //nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_SEND_CIPSTATUS;
         }
         if(wifiComDelay.Read()){
         //if (nonBlockingDelayRead(&wifiComDelay)) {
            wifiComDelay.Start(DELAY_5_SECONDS);
            //nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_SEND_CIPSTATUS;
         }
      break;

      case WIFI_STATE_IDLE:
      case WIFI_STATE_ERROR:
         reset = OFF;
         wifiComDelay.Start(DELAY_2_SECONDS);
         wifiComState = WIFI_STATE_WAIT_RESET;
      break;

      case WIFI_STATE_WAIT_RESET:
         if(wifiComDelay.Read()){
             reset = ON;
             wifiComState = WIFI_STATE_INIT;
             pc_.string_write("Reset \r\n");
         }
   }
}

//=====[Implementations of private functions]==================================

bool wifiComCharRead( char* receivedChar )
{
    char receivedCharLocal = '\0';
    if( uartWifi.readable() ) {
        uartWifi.read(&receivedCharLocal,1);
        *receivedChar = receivedCharLocal;
        return true;
    }
    return false;
}

void wifiComStringWrite( const char* str )
{
    uartWifi.write( str, strlen(str) );
}

static bool isExpectedResponse()
{
   static int responseStringPositionIndex = 0;
   char charReceived;
   bool moduleResponse = false;

   if( wifiComCharRead(&charReceived) ){
      if (charReceived == wifiComExpectedResponse[responseStringPositionIndex]) {
         responseStringPositionIndex++;
         if (wifiComExpectedResponse[responseStringPositionIndex] == '\0') {
            responseStringPositionIndex = 0;
            moduleResponse = true;
         }
      } else {
         responseStringPositionIndex = 0;
      }
   }
   return moduleResponse;
}