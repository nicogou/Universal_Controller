#include "Controller.h"

Controller::Controller(int rx, int tx, long inter, int digNb, int anaNb, int digPins[nb_max_data], int anaPins[nb_max_data])
{
    Serial.begin(9600);
    this->controllerSerialRx = rx;
    this->controllerSerialTx = tx;
    this->controllerSerial = new SoftwareSerial(this->controllerSerialRx), this->controllerSerialTx);
    this->controllerSerial.begin(9600);

    this->interval = inter;
    for (int ii = 0; ii < digNb; ii++)
    {
        this->digitalPins[ii] = digPins[ii];
    }

    /***************    A compléter     ****************/
    /***************    A compléter     ****************/
    /***************    A compléter     ****************/
    /***************    A compléter     ****************/
    /***************    A compléter     ****************/
    /***************    A compléter     ****************/
    /***************    A compléter     ****************/
    for (int ii = 0; ii < 1; ii++)
    {
        pinMode(this->digitalPins[ii], INPUT_PULLUP);
    }
    for (int ii = 0; ii < 1; ii++)
    {
        pinMode(this->digitalPins[ii], INPUT);
    }
    /***************    A compléter     ****************/
    /***************    A compléter     ****************/
    /***************    A compléter     ****************/
    /***************    A compléter     ****************/
    /***************    A compléter     ****************/
    /***************    A compléter     ****************/
    /***************    A compléter     ****************/

    for (int ii = 0; ii < anaNb; ii++)
    {
        this->analogPins[ii] = anaPins[ii];
        pinMode(this->analogPins[ii], INPUT);
    }

    // Start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc.
    this->ETin.begin(details(this->rxdata), this->controllerSerial);
    this->ETout.begin(details(this->txdata), this->controllerSerial);
}

// 2 overloads of function in order to make this->interval a default argument of sendData. See the following for detail : https://stackoverflow.com/questions/9286533/how-to-use-a-member-variable-as-a-default-argument-in-c
bool Controller::sendData()
{
    this->sendData(this->interval);
}

bool Controller::sendData(unsigned long inter)
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

bool Controller::state()
{
    /***************    A compléter     ****************/
    /***************    A compléter     ****************/
    /***************    A compléter     ****************/
    /***************    A compléter     ****************/
    /***************    A compléter     ****************/
    /***************    A compléter     ****************/
    /***************    A compléter     ****************/
    int btPin = 0;
    /***************    A compléter     ****************/
    /***************    A compléter     ****************/
    /***************    A compléter     ****************/
    /***************    A compléter     ****************/
    /***************    A compléter     ****************/
    /***************    A compléter     ****************/
    /***************    A compléter     ****************/
    this->state = digitalRead(digitalPins[btPin]);
    return this->state;
}

void Controller::getDataFromSensors()
{
    for (int ii = 0; ii < this->analogNb; ii++)
    {
        analog[ii] = analogRead(analogPins[ii]);
    }
    for (int ii = 0; ii < this->digitalNb; ii++)
    {
        digital[ii] = analogRead(digitalPins[ii]);
    }

    for (int ii = 0; ii < this->nb_max_data; ii++)
    {
        this.txdata.analog[ii] = this.analog[ii];
        this.txdata.digital[ii] = this.digital[ii];
    }
}