#include "Droideka_Controller.h"

Droideka_Controller::Droideka_Controller(int rx, int tx, long inter, int digNb, int anaNb, int digPin[NB_MAX_DATA], int anaPin[NB_MAX_DATA], bool digInputPullup[NB_MAX_DATA], bool digReversedLogic[NB_MAX_DATA], String btHardware)
{
    btHardwareConfig = btHardware;

    Serial.begin(9600);
    controllerSerialRx = rx;
    controllerSerialTx = tx;
    controllerSerial = new SoftwareSerial(controllerSerialRx, controllerSerialTx);
    int baudRate;
    if (btHardwareConfig == BT_HW_HM10)
    {
        baudRate = 9600;
    }
    else if (btHardwareConfig == BT_HW_HC05)
    {
        baudRate = 38400;
    }
    controllerSerial->begin(baudRate);

    interval = inter;
    analogNb = anaNb;
    digitalNb = digNb;
    txdata.analogNb = analogNb;
    txdata.digitalNb = digitalNb;
    for (int ii = 0; ii < digitalNb; ii++)
    {
        digitalInputPullup[ii] = digInputPullup[ii];
        digitalReversedLogic[ii] = digReversedLogic[ii];
    }

    for (int ii = 0; ii < digitalNb; ii++)
    {
        digitalPin[ii] = digPin[ii];
    }

    for (int ii = 0; ii < digitalNb; ii++)
    {
        if (digitalInputPullup[ii])
        {
            pinMode(digitalPin[ii], INPUT_PULLUP);
        }
        else
        {
            pinMode(digitalPin[ii], INPUT);
        }
    }

    for (int ii = 0; ii < anaNb; ii++)
    {
        analogPin[ii] = anaPin[ii];
        pinMode(analogPin[ii], INPUT);
    }

    // Start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc.
    ETin.begin(details(rxdata), controllerSerial);
    ETout.begin(details(txdata), controllerSerial);
}

// 2 overloads of function in order to make this->interval a default argument of sendData. See the following for detail : https://stackoverflow.com/questions/9286533/how-to-use-a-member-variable-as-a-default-argument-in-c
bool Droideka_Controller::sendData()
{
    sendData(interval);
}

bool Droideka_Controller::sendData(unsigned long inter)
{
    unsigned long currentMillis = millis();
    if (currentMillis - lastMillis >= inter)
    {
        lastMillis = currentMillis;
        // Send data to receiver.
        ETout.sendData();
        return true;
    }
    return false;
}

bool Droideka_Controller::state()
{
    if (btHardwareConfig == BT_HW_HM10)
    {
        int btPin = 0;
        btState = digitalRead(digitalPin[btPin]);
        return btState;
    }
    else if (btHardwareConfig == BT_HW_HC05)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Droideka_Controller::getDataFromSensors()
{
    for (int ii = 0; ii < analogNb; ii++)
    {
        txdata.analog[ii] = analogRead(analogPin[ii]);
    }
    for (int ii = 0; ii < digitalNb; ii++)
    {
        txdata.digital[ii] = digitalRead(digitalPin[ii]);
        if (digitalReversedLogic[ii])
        {
            txdata.digital[ii] = 1 - txdata.digital[ii];
        }
    }
}