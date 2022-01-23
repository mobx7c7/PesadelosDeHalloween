/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de cria��o     : 2015-04-20
***********************************************************************/
#ifndef PREFERENCES_H
#define PREFERENCES_H

/*
    Bin�rio: cada parametro ter� seu enumerador, formato e valor (+ eficiente)
    Texto: cada parametro ter� seu nome e valor (+ leg�vel)
*/

#include <map>
#include <string>
using std::map;
using std::string;

class GlobalOptions
{
    private:

        static GlobalOptions* instance;
        GlobalOptions();
        ~GlobalOptions();
        map<string, string> params;

    public:

        static GlobalOptions*   getInstance();
        static void             destroyInstance();
        bool                    isAvailable(string name);
        string                  getValue(string name);
        void                    setValue(string name, string value);
};

#endif // PREFERENCES_H
