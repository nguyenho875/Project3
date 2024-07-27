//=====[#include guards - begin]===============================================

#ifndef _MQTT_H_
#define _MQTT_H_

//==================[Libraries]===============================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "global_defines.h"
#include "led.h"
#include "non_blocking_delay.h"
#include <vector>
#include <string>

//=====[Declaration of public defines]=========================================

#ifndef MQTT_MESSAGE_RECEIVED_LED_DELAY_TIME_MS
#define MQTT_MESSAGE_RECEIVED_LED_DELAY_TIME_MS 1000
#endif

//=====[Declaration of public data types]======================================

typedef enum{
    CONECTADO,
    DESCONECTADO
} MQTT_status_t;

typedef struct {
    std::string topic;
    std::string message;
} PendingMessage_t;

//=====[Declaration of public classes]=========================================

class MQTT
{
    public:
        // Crea el objeto
        MQTT(PinName Tx, PinName Rx, int baudrate, PinName pin_status, PinName pin_led_connected, PinName pin_led_disconnected, PinName pin_led_message);

        // Se suscribe a un tópico
        void subscribe(const char * topic);

        // Se desuscribe a un tópico
        void unsubscribe(const char * topic);

        // Envía un mensaje a un tópico
        void publish(const char * topic, const char * message);

        //
        bool receive(char* topic, char* message);

        // Devuelve el estado de la conexión MQTT
        MQTT_status_t status();

        bool isSubscribed(const char* topic);

        std::vector<std::string> getSubscribedTopics();

        void processPendings();

        void confirmSubscription(const char* topic);
        void confirmUnsubscription(const char* topic);

    private:
        // Conexión con el módulo esp32 que maneja MQTT
        BufferedSerial esp32;

        // Pin que indica el estado de la conexión MQTT
        DigitalIn status_in;

        // Led indicativo de que la conexión MQTT está activa
        Led led_connected;

        // Led indicativo de que la conexión MQTT está inactiva
        Led led_disconnected;

        // Led indicativo de que se recibió un mensaje
        Led led_message;

        MQTT_status_t MQTT_status;

        const char * subscribe_str = "subscribe";
        const char * unsubscribe_str = "unsubscribe";

        InterruptIn int_MQTT_status;
        InterruptIn int_MQTT_mensaje;

        nonBlockingDelay message_led_delay;

        std::vector<std::string> subscribedTopics;
        std::vector<std::string> pendingSubscriptions;
        std::vector<std::string> pendingUnsubscriptions;
        std::vector<PendingMessage_t> pendingMessages;

        bool reset_subscriptions = false;

        // Actualiza el status de la conexión
        void update_status(MQTT_status_t new_status);

        void int_MQTT_status_callback_on();
        void int_MQTT_status_callback_off();
        void int_MQTT_mensaje_callback();

        void delay_callback();

        void write(const char * topic, const char * message);
};

//=====[Declarations (prototypes) of public functions]=========================

//=====[#include guards - end]=================================================

#endif // _MQTT_H_
