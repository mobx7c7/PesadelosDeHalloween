/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-27
***********************************************************************/
#include "Serial.h"

Serial::Serial(string portname) :
    portname    (portname),
    baudRate    (0),
    byteSize    (0),
    parity      (0),
    stopBits    (0),
    flowControl (0),
    connected   (false)
{

}

Serial::Serial() : Serial("")
{

}

Serial::~Serial()
{

}

string& Serial::getPortName()
{
	return portname;
}

unsigned Serial::getBaudRate()
{
	return baudRate;
}

unsigned Serial::getByteSize()
{
	return byteSize;
}

unsigned Serial::getParity()
{
	return parity;
}

unsigned Serial::getStopBits()
{
	return stopBits;
}

unsigned Serial::getFlowControl()
{
	return flowControl;
}

bool Serial::isConnected()
{
	return connected;
}

void Serial::setPortName(string portname)
{
	if(!connected) this->portname = portname;
}

void Serial::setBaudRate(unsigned baudRate)
{
	if(!connected) this->baudRate = baudRate;
}

void Serial::setByteSize(unsigned byteSize)
{
	if(!connected) this->byteSize = byteSize;
}

void Serial::setParity(unsigned parity)
{
	if(!connected) this->parity = parity;
}

void Serial::setStopBits(unsigned stopBits)
{
	if(!connected) this->stopBits = stopBits;
}

void Serial::setFlowControl(unsigned flowControl)
{
	if(!connected) this->flowControl = flowControl;
}













WinSerial::WinSerial(string portname) : Serial(portname)
{
    baudRate    = CBR_9600;
    byteSize    = 8;
    stopBits    = ONESTOPBIT;
    parity      = NOPARITY;
    flowControl = DTR_CONTROL_ENABLE;
}

WinSerial::WinSerial()
{

}

WinSerial::~WinSerial()
{
    disconnect();
}

int WinSerial::connect()
{
	connected = false;

	hSerial = CreateFile(portname.c_str(),
	                     GENERIC_READ | GENERIC_WRITE,
	                     0,
	                     NULL,
	                     OPEN_EXISTING,
	                     FILE_ATTRIBUTE_NORMAL,
	                     NULL);

	if(hSerial == INVALID_HANDLE_VALUE)
	{
		if(GetLastError() == ERROR_FILE_NOT_FOUND)
		{
			//MessageBox(NULL, "Error: File not found", "Error", MB_OK | MB_ICONSTOP);
			MessageBox(GetActiveWindow(), "Error: Port unavailable.", "Error", MB_OK | MB_ICONSTOP);
			return -1;
		}
		else
		{
			MessageBox(GetActiveWindow(), "Error: Unknown.", "Error", MB_OK | MB_ICONSTOP);
			return -1;
		}
	}
	else
	{
		DCB dcbSerialParams;
		memset(&dcbSerialParams, 0, sizeof(dcbSerialParams));

		if(!GetCommState(hSerial, &dcbSerialParams))
		{
			MessageBox(GetActiveWindow(), "Error: Failed to get current serial parameters!", "Error", MB_OK | MB_ICONSTOP);
			return -1;
		}
		else
		{
			dcbSerialParams.BaudRate    = baudRate;
			dcbSerialParams.ByteSize    = byteSize;
			dcbSerialParams.StopBits    = stopBits;
			dcbSerialParams.Parity      = parity;
			dcbSerialParams.fDtrControl = flowControl;

			if(!SetCommState(hSerial, &dcbSerialParams))
			{
				MessageBox(GetActiveWindow(), "Warning: Couldn't set serial port parameters!", "Warning", MB_OK | MB_ICONSTOP);
				return -1;
			}
			else
			{
				connected = true;
				PurgeComm(hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR);
				Sleep(PURGE_WAIT_TIME);
			}
		}
	}
	return 0;
}

void WinSerial::disconnect()
{
	if(connected)
	{
		connected = false;
		CloseHandle(hSerial);
	}
}

int WinSerial::read(char* buffer, unsigned length)
{
	DWORD bytesRead;

	unsigned bytesLeft;

	ClearCommError(hSerial, &errors, &status);

	if(status.cbInQue > 0)
	{
		if(status.cbInQue > length)
		{
			bytesLeft = length;
		}
		else
		{
			bytesLeft = status.cbInQue;
		}
	}
	if(ReadFile(hSerial, buffer, bytesLeft, &bytesRead, NULL) && bytesRead != 0)
	{
		return bytesRead;
	}
	return -1;
}

int WinSerial::write(char* buffer, unsigned length)
{
	DWORD bytesSend;

	if(!WriteFile(hSerial, (void*)buffer, length, &bytesSend, 0))
	{
		ClearCommError(hSerial, &errors, &status);
		//return false;
	}
	//return true;
	return bytesSend;
}

int WinSerial::peek()
{
    if(connected)
    {
        ClearCommError(hSerial, &errors, &status);
        return (int)status.cbInQue;
    }
    return -1;
}

void WinSerial::flush()
{
    if(connected)
    {
        PurgeComm(hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR);
    }
}










SerialListener* SerialListener::instance = 0;

SerialListener::SerialListener()
{
    cout << "[SerialListener] Iniciando..." << endl;
    memset(analogPins, 0, sizeof(float) * 12);
    memset(digitalPins, 0, sizeof(bool) * 52);
}

SerialListener::~SerialListener()
{
    cout << "[SerialListener] Destruindo..." << endl;
    if(serial) delete serial;
}

void SerialListener::serialCallback(SerialListener* userPtr)
{
	Serial* serial = userPtr->serial;

	if(serial->isConnected())
	{
		int     bytesRead       = 0;
		int     length          = 282; // 61
		char    buffer[length]  = "";
		int     currentPos      = 0;

		memset(buffer, 0, length);
		serial->flush();

		while(serial->isConnected() && userPtr->running)
		{
			serial->write("x", 1);
			bytesRead = serial->read(&buffer[currentPos], length-currentPos);

			if(bytesRead > 0)
			{
				currentPos += bytesRead;
				if(currentPos >= length)
				{
					string line(buffer, length);
					//stringstream ss;
					for(int i=0; i<12; i++)
					{
						userPtr->analogPins[i] = 1.0/4095 * (*(int*)&line[13+(sizeof(int)*i)]);
						//ss << " | " << fixed << userPtr->analogPins[i] << (i%6!=5 ? "" : " | \n");
					}
					for(int i=0; i<52; i++)
					{
						userPtr->digitalPins[i] = (bool)(1.0/1023 * (*(int*)&line[62+(sizeof(int)*i)]));
						//ss << " | " << fixed << (float)userPtr->digitalPins[i] << (i%6!=5 ? "" : " | \n");
					}
					//ss << " | "  << endl;
					//cout << ss.str() << endl;
					currentPos=0;
				}
			}
			else
			{
				currentPos = 0;
			}
		}
		//system("PAUSE");
	}
	//cout << "FIM" << endl;
}

SerialListener* SerialListener::getInstance()
{
    if(!instance) instance = new SerialListener();
    return instance;
}
void SerialListener::destroyInstance()
{
    if(instance) delete instance;
}
void SerialListener::start()
{
	if(!running)
	{
	    if(!serial)
        {
            serial = new WinSerial("COM4");
        }
        serial->setBaudRate(115200);
        serial->connect();

        if(serial->isConnected())
        {
            cout << "[SerialListener] Conectado na porta " << serial->getPortName() << endl;
            running = true;
            t = thread(SerialListener::serialCallback, this);
        }
        else
        {
            cout << "[SerialListener] Impossível conectar na porta " << serial->getPortName() << endl;
        }
	}
}
void SerialListener::stop()
{
	if(running)
	{
	    if(serial->isConnected())
        {
            serial->disconnect();
        }
		running = false;
		t.join();
	}
}
float SerialListener::getAnalogPin(unsigned pin) const
{
	return analogPins[pin];
}
bool SerialListener::getDigitalPin(unsigned pin) const
{
	return digitalPins[pin];
}










