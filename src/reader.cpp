#include "../include/rapidjson/document.h"
#include "../include/rapidjson/istreamwrapper.h"
#include "../include/rapidjson/writer.h"
#include "../include/rapidjson/stringbuffer.h"
#include <fstream>
#include <iostream>

using namespace rapidjson;
using namespace std;

int main()
{
    ifstream ifs("json/in/teachers.json");
    if (!ifs.is_open())
    {
        std::cerr << "Could not open file for reading!\n";
        return EXIT_FAILURE;
    }

    IStreamWrapper isw(ifs);

    Document doc{};
    doc.ParseStream(isw);

    for (SizeType i = 0; i < doc["teachers"].Size(); i++)
    {
        if (doc["teachers"][i]["subject"] == "Mathematics")
            cout << doc["teachers"][i]["id"].GetInt() << endl;
    }
    return 0;
}