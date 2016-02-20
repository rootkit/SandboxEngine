#ifndef APPCONFIGURATION_H
#define APPCONFIGURATION_H
#include <jsoncpp/json/json.h>
#include <cstdio>
#include <string>
#include <fstream>

using namespace std;

class AppConfiguration
{
    public:
        AppConfiguration();
        virtual ~AppConfiguration();
    protected:
    private:
        Json::Value _root;
        Json::Reader* _reader;
};

#endif // APPCONFIGURATION_H
