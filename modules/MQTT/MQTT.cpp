//=====[Libraries]=============================================================

#include "MQTT.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

//=====[Implementations of private functions]==================================

//=====[Implementations of public methods]=====================================

MQTT::MQTT(PinName Tx, PinName Rx, int baudrate, PinName pin_status, PinName pin_led_connected, PinName pin_led_disconnected, PinName pin_led_message): 
        esp32(Tx, Rx, baudrate), status_in(pin_status, PullDown), led_connected(pin_led_connected), led_message(pin_led_message, OFF),
        led_disconnected(pin_led_disconnected), int_MQTT_status(pin_status, PullDown), int_MQTT_mensaje(PIN_MQTT_MENSAJE, PullDown), message_led_delay(MQTT_MESSAGE_RECEIVED_LED_DELAY_TIME_MS, callback(this, &MQTT::delay_callback))
{
    if(status_in == HIGH){
        MQTT::update_status(CONECTADO);
    }
    else{
        MQTT::update_status(DESCONECTADO);
    }

    this->int_MQTT_status.rise(callback(this, &MQTT::int_MQTT_status_callback_on));
    this->int_MQTT_status.fall(callback(this, &MQTT::int_MQTT_status_callback_off));
    this->int_MQTT_mensaje.fall(callback(this, &MQTT::int_MQTT_mensaje_callback));
}

void MQTT::subscribe(const char * topic)
{
    if (!isSubscribed(topic)) {
        pendingSubscriptions.push_back(topic);
    }
}

void MQTT::unsubscribe(const char * topic)
{
    pendingUnsubscriptions.push_back(topic);
}

void MQTT::publish(const char * topic, const char * message)
{
    if(MQTT_status == CONECTADO){
        PendingMessage_t pendingMessage = {topic, message};
        pendingMessages.push_back(pendingMessage);
    }
}

bool MQTT::receive(char* topic, char* message) {
    if (!this->esp32.readable()) {
        return false;
    }
    
    char buffer[256];
    int index = 0;
    char ch = '\0';

    while (ch != '\n' && index < sizeof(buffer) - 1) {
        if (this->esp32.readable()) {
            this->esp32.read(&ch, 1);
            if (ch != '\n') {
                buffer[index++] = ch;
            }
        }
    }
    buffer[index] = '\0';

    char* separator = strchr(buffer, ':');
    if (separator != NULL) {
        *separator = '\0';
        strcpy(topic, buffer);
        strcpy(message, separator + 1);
    } else {
        topic[0] = '\0';
        message[0] = '\0';
    }
    return true;
}

MQTT_status_t MQTT::status()
{
    return this->MQTT_status;
}

bool MQTT::isSubscribed(const char* topic) {
    std::string strTopic(topic);
    return std::find(subscribedTopics.begin(), subscribedTopics.end(), strTopic) != subscribedTopics.end();
}

std::vector<std::string> MQTT::getSubscribedTopics() {
    return subscribedTopics;
}

void MQTT::processPendings() {
    // Enviar mensajes de suscripción pendientes
    for (const std::string& topic : pendingSubscriptions) {
        MQTT::write(subscribe_str, topic.c_str());
    }
    // Enviar mensajes de desuscripción pendientes
    for (const std::string& topic : pendingUnsubscriptions) {
        MQTT::write(unsubscribe_str, topic.c_str());
    }

    /*
    // Enviar mensajes pendientes
    for (const PendingMessage_t& msg : pendingMessages) {
        if(MQTT_status == CONECTADO){
            MQTT::write(msg.topic.c_str(), msg.message.c_str());
        }
    }
    pendingMessages.clear();
    */

    // Enviar el mensaje pendiente más antiguo
    if (!pendingMessages.empty()) {
        const PendingMessage_t& msg = pendingMessages.front();
        if(MQTT_status == CONECTADO){
            MQTT::write(msg.topic.c_str(), msg.message.c_str());
            pendingMessages.erase(pendingMessages.begin()); // Eliminar el mensaje más antiguo
        }
    }
}

void MQTT::confirmSubscription(const char* topic) {
    std::string confirmedTopic(topic);
    auto it = std::find(pendingSubscriptions.begin(), pendingSubscriptions.end(), confirmedTopic);
    if (it != pendingSubscriptions.end()) {
        pendingSubscriptions.erase(it);
        subscribedTopics.push_back(confirmedTopic);
    }
}

void MQTT::confirmUnsubscription(const char* topic) {
    std::string confirmedTopic(topic);
    auto it = std::find(pendingUnsubscriptions.begin(), pendingUnsubscriptions.end(), confirmedTopic);
    if (it != pendingUnsubscriptions.end()) {
        pendingUnsubscriptions.erase(it);
        subscribedTopics.erase(std::remove(subscribedTopics.begin(), subscribedTopics.end(), confirmedTopic), subscribedTopics.end());
    }
}

//=====[Implementations of private methods]====================================

void MQTT::update_status(MQTT_status_t new_status)
{
    this->MQTT_status = new_status;
    switch (MQTT_status){
        case CONECTADO:
            this->led_connected = ON;
            this->led_disconnected = OFF;
            break;
        case DESCONECTADO:
            this->led_connected = OFF;
            this->led_disconnected = ON;
            break;
        default:
            break;
    }
}

void MQTT::int_MQTT_status_callback_on()
{
    MQTT::update_status(CONECTADO);
}

void MQTT::int_MQTT_status_callback_off()
{
    MQTT::update_status(DESCONECTADO);

    // Move all subscribed topics to pending subscriptions
    for (const std::string& topic : subscribedTopics) {
        pendingSubscriptions.push_back(topic);
    }
    subscribedTopics.clear();
}

void MQTT::int_MQTT_mensaje_callback()
{
    this->led_message = ON;
    this->message_led_delay.Start();
}

void MQTT::delay_callback()
{
    this->led_message = OFF;
}

void MQTT::write(const char * topic, const char * message)
{
    this->esp32.write(topic, strlen(topic));
    this->esp32.write(":", 1);
    this->esp32.write(message, strlen(message));
    this->esp32.write("\n", 1);
}
