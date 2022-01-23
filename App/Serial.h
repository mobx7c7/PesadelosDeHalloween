/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-27
***********************************************************************/
#ifndef SERIAL_H
#define SERIAL_H

// Baseado em:
// http://playground.arduino.cc/Interfacing/CPPWindows

#include <windows.h>
#include <string>
#define PURGE_WAIT_TIME 250

using std::string;

class Serial
{
protected:

    string      portname;
    unsigned    baudRate;
    unsigned    byteSize;
    unsigned    parity;
    unsigned    stopBits;
    unsigned    flowControl;
    bool        connected;

    Serial(string portname);
    Serial();

public:

    virtual ~Serial();

    string&         getPortName();
    unsigned        getBaudRate();
    unsigned        getByteSize();
    unsigned        getParity();
    unsigned        getStopBits();
    unsigned        getFlowControl();
    bool            isConnected();

    void            setPortName(string portname);
    void            setBaudRate(unsigned baudRate);
    void            setByteSize(unsigned byteSize);
    void            setParity(unsigned parity);
    void            setStopBits(unsigned stopBits);
    void            setFlowControl(unsigned flowControl);

    virtual int     connect() = 0;
    virtual void    disconnect() = 0;
    virtual int     read(char* data, unsigned length) = 0;
    virtual int     write(char* data, unsigned length) = 0;
    virtual int     peek() = 0;
    virtual void    flush() = 0;
};




class WinSerial : public Serial
{
protected:

    HANDLE  hSerial;
    COMSTAT status;
    DWORD   errors;

public:

    WinSerial(string portname);
    WinSerial();
    ~WinSerial();

    int     connect();
    void    disconnect();
    int     read(char* buffer, unsigned length);
    int     write(char* buffer, unsigned length);
    int     peek();
    void    flush();
};


//class ArduinoSerialController
//{
//protected:
//
//    float* analogPins;
//    bool*  digitalPins;
//
//public:
//
//    ArduinoSerialController()
//    {
//        analogPins  = new float[12];
//        digitalPins = new bool[54];
//    }
//    ~ArduinoSerialController()
//    {
//        delete analogPins;
//        delete digitalPins;
//    }
//    float getAnalogPin(unsigned pin)
//    {
//        return analogPins[pin];
//    }
//    bool getDigitalPin(unsigned pin)
//    {
//        return digitalPins[pin];
//    }
//};


#include <iostream>
#include <sstream>
#include <vector>
#include <thread>

using namespace std;

class SerialListener
{
protected:

    static SerialListener* instance;

    Serial*         serial  = 0;
    bool            running = false;
    thread          t;

    float           analogPins[12];
    bool            digitalPins[52];

    SerialListener();
    ~SerialListener();
    static void serialCallback(SerialListener* userPtr);

public:

    static SerialListener*  getInstance();
    static void             destroyInstance();
    void                    start();
    void                    stop();

    float                   getAnalogPin(unsigned pin) const;
    bool                    getDigitalPin(unsigned pin) const;

    void                    update();
};







#endif // SERIAL_H
