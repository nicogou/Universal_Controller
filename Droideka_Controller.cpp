#include "Droideka_Controller.h"

Droideka_Controller::Droideka_Controller(int rx, int tx, long inter, int digNb, int anaNb, int digPin[NB_MAX_DATA], int anaPin[NB_MAX_DATA], int ipNb)
{
    Serial.begin(9600);
    controllerSerialRx = rx;
    controllerSerialTx = tx;
    controllerSerial = new SoftwareSerial(controllerSerialRx, controllerSerialTx);
    controllerSerial->begin(9600);

    interval = inter;
    analogNb = anaNb;
    digitalNb = digNb;
    inputPullupNb = ipNb;
    for (int ii = 0; ii < digitalNb; ii++)
    {
        digitalPin[ii] = digPin[ii];
    }

    for (int ii = 0; ii < digitalNb - inputPullupNb; ii++)
    {
        pinMode(digitalPin[ii], INPUT);
    }
    for (int ii = digitalNb - inputPullupNb; ii < digitalNb; ii++)
    {
        pinMode(digitalPin[ii], INPUT_PULLUP);
    }

    for (int ii = 0; ii < anaNb; ii++)
    {
        this->analogPin[ii] = anaPin[ii];
        pinMode(this->analogPin[ii], INPUT);
    }

    // Start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc.
    this->ETin.begin(details(this->rxdata), this->controllerSerial);
    this->ETout.begin(details(this->txdata), this->controllerSerial);
}

// 2 overloads of function in order to make this->interval a default argument of sendData. See the following for detail : https://stackoverflow.com/questions/9286533/how-to-use-a-member-variable-as-a-default-argument-in-c
bool Droideka_Controller::sendData()
{
    this->sendData(this->interval);
}

bool Droideka_Controller::sendData(unsigned long inter)
{
    unsigned long currentMillis = millis();
    if (currentMillis - this->lastMillis >= inter)
    {
        this->lastMillis = currentMillis;
        // Send data to receiver.
        ETout.sendData();
        return true;
    }
    return false;
}

bool Droideka_Controller::state()
{
    int btPin = 0;
    this->btState = digitalRead(digitalPin[btPin]);
    return this->btState;
}

void Droideka_Controller::getDataFromSensors()
{
    for (int ii = 0; ii < this->analogNb; ii++)
    {
        analog[ii] = analogRead(analogPin[ii]);
    }
    for (int ii = 0; ii < this->digitalNb; ii++)
    {
        digital[ii] = digitalRead(digitalPin[ii]);
    }

    for (int ii = 0; ii < this->nb_max_data; ii++)
    {
        this->txdata.analog[ii] = this->analog[ii];
        this->txdata.digital[ii] = this->digital[ii];
    }
}