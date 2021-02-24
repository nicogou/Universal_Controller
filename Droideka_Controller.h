#ifndef Droideka_Controller_h
#define Droideka_Controller_h

#include <SoftwareSerial.h>
#include <SoftEasyTransfer.h>

const int nb_max_data = 50;

struct SEND_DATA_STRUCTURE
{
    // put your variable definitions here for the data you want to receive
    // THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
    int analog[nb_max_data];
    int digital[nb_max_data];
};

struct RECEIVE_DATA_STRUCTURE
{
    // put your variable definitions here for the data you want to receive
    // THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO

    // Nothing to be sent back to Controller yet.
};

class Droideka_Controller
{
public:
    unsigned long lastMillis;
    unsigned long interval = 400;

    int controllerSerialRx;
    int controllerSerialTx;
    SoftwareSerial *controllerSerial; // RX, TX
    int bluetoothStatePin;
    bool state = false;
    // The HM-10 state pin is at level high when connected, but there are 2 possible behaviour when not connected:
    // 1- state pin oscillates between high and low (500 ms between a change)
    // 2- state pin is low
    // This behaviour can be changed via AT commands : send AT+PIO10 for behaviour 1, and AT+PIO11 for behaviour 2.
    // We will be in behaviour 2 for the purpose of this project.

    // create two EasyTransfer objects.
    SoftEasyTransfer ETin, ETout;
    // give a name to the group of data
    RECEIVE_DATA_STRUCTURE rxdata;
    SEND_DATA_STRUCTURE txdata;

    int nb_max_data = nb_max_data;
    int analogNb;
    int analogPin[nb_max_data];
    int analog[nb_max_data];
    int digitalNb;
    int digitalPin[nb_max_data];
    int digital[nb_max_data];

    Droideka_Controller(int rx, int tx, long inter, int digNb, int anaNb, int digPins[nb_max_data], int anaPins[nb_max_data]);
    bool state(); // Check if bluetooth is connected
    void getDataFromSensors();
    bool sendData(unsigned long inter);
    bool sendData();
};

#endif
