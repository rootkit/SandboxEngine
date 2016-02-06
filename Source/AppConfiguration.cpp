#define _GLIBCXX_USE_CXX11_ABI 0
#include "AppConfiguration.h"

AppConfiguration::AppConfiguration()
{
    /*ifstream appJsonTxt;
    appJsonTxt.open ("example.txt");

    Json::Reader reader;
    Json::Value root;

    string json = "";
    string tmpLine = "";

    while(!appJsonTxt.eof()) // To get you all the lines.
    {
        getline(appJsonTxt,tmpLine); // Saves the line in STRING.
        json = json + tmpLine;
    }


    if (appJsonTxt != NULL && reader.parse(json,root)) {
        const Json::Value arrayDest = root["dest"];
        for (unsigned int i = 0; i < arrayDest.size(); i++) {
            if (!arrayDest[i].isMember("name"))
                continue;
            std::string out;
            out = arrayDest[i]["name"].asString();
            std::cout << out << "\n";
        }
    }
    appJsonTxt.close();*/
}

AppConfiguration::~AppConfiguration()
{
    //dtor
}
