/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-04-20
***********************************************************************/
#ifndef PREFERENCES_H
#define PREFERENCES_H

/*
    Binário: cada parametro terá seu enumerador, formato e valor (+ eficiente)
    Texto: cada parametro terá seu nome e valor (+ legível)
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
