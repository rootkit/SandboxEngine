#define _GLIBCXX_USE_CXX11_ABI 0
#include "AppConfiguration.h"

AppConfiguration::AppConfiguration()
{
   /* std::fstream appJsonTxt;
    appJsonTxt.open ("Config/app.json", std::fstream::in | std::fstream::out | std::fstream::app);

    _root = new Json::Value;

    _reader = new Json::Reader();

    std::string jsonString;

    while(appJsonTxt.eof()){

        jsonString += appJsonTxt.getline()

        jsonString.begin();

    }

    _reader->parse(appJsonTxt,_root);


    appJsonTxt.close();*/
}

AppConfiguration::~AppConfiguration()
{
    //dtor
}
