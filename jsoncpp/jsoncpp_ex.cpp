#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>

using namespace std;

int main(int argc, const char **argv)
{
    string json_file = "alice.json";
    ifstream ifs(json_file);
    if(!ifs){
        cerr << "No such JSON file: " << json_file << endl;
    }

    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifs, obj); // reader can also read strings
    cout << "Book: " << obj["book"].asString() << endl;
    cout << "Year: " << obj["year"].asUInt() << endl;
    const Json::Value& characters = obj["characters"]; // array of characters
    for (int i = 0; i < characters.size(); i++){
        cout << "    name: " << characters[i]["name"].asString();
        cout << " chapter: " << characters[i]["chapter"].asUInt();
        cout << endl;
    }

    return 0;
}