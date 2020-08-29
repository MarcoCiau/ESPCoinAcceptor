#ifndef ESP_COIN_ACCEPTOR_H
#define ESP_COIN_ACCEPTOR_H
#include <Arduino.h>
#define DEFAULT_COIN_PIN 14//ESP8266 GPIO 14 (D5)
#define PULSE_TIMEOUT_MS 200 // In fast mode, each pulse is 20ms, with an interval of 100ms

class ESPCoinAcceptor
{
private:
    /* data */
    bool coinInserted;
    int coinPin;
    void process();
public:
    ESPCoinAcceptor(int pin);
    void begin();
    void loop();
    bool isCoinInserted();
};



#endif //ESP_COIN_ACCEPTOR_H