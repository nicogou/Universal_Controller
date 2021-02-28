#ifndef Droideka_Controller_h
#define Droideka_Controller_h

#include <SoftwareSerial.h>
#include <SoftEasyTransfer.h>

#define NB_MAX_DATA 20
#define BT_HW_HM10 "HM-10"
#define BT_HW_HC05 "HC-05"

struct SEND_DATA_STRUCTURE
{
    // put your variable definitions here for the data you want to receive
    // THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
    int analogNb;
    int digitalNb;
    int analog[NB_MAX_DATA];
    int digital[NB_MAX_DATA];
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
    unsigned long lastMillis = 0;
    unsigned long interval;

    int controllerSerialRx;
    int controllerSerialTx;
    SoftwareSerial *controllerSerial; // RX, TX
    bool btState = false;
    // The HM-10 state pin is at level high when connected, but there are 2 possible behaviour when not connected:
    // 1- state pin oscillates between high and low (500 ms between a change)
    // 2- state pin is low
    // This behaviour can be changed via AT commands : send AT+PIO10 for behaviour 1, and AT+PIO11 for behaviour 2.
    // We will be in behaviour 2 for the purpose of this project.
    String btHardwareConfig; // 2 hardware configs possible for now : HM-10 or HC-05.

    // create two EasyTransfer objects.
    SoftEasyTransfer ETin, ETout;
    // give a name to the group of data
    RECEIVE_DATA_STRUCTURE rxdata;
    SEND_DATA_STRUCTURE txdata;

    int nb_max_data = NB_MAX_DATA;
    int analogNb;
    int analogPin[NB_MAX_DATA];
    int digitalNb;
    int digitalPin[NB_MAX_DATA];
    bool digitalInputPullup[NB_MAX_DATA];
    bool digitalReversedLogic[NB_MAX_DATA];
    // The digital pin at index 0 is always the pin used to check the state of bluetooth. The next digital pins are used for other things.

    Droideka_Controller(int rx, int tx, long inter, int digNb, int anaNb, int digPins[NB_MAX_DATA], int anaPins[NB_MAX_DATA], bool digInputPullup[NB_MAX_DATA], bool digReversedLogic[NB_MAX_DATA], String btHardware);
    bool state(); // Check if bluetooth is connected
    void getDataFromSensors();
    bool sendData(unsigned long inter);
    bool sendData();
};

#endif
