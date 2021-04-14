#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h> // or something

using namespace std;

int main()
{
    string json_file = "nftables.json";
    ifstream ifs(json_file);
    if (!ifs)
    {
        cerr << "No such JSON file: " << json_file << endl;
    }

    Json::Value obj;
    // Deprecated metod
    // Json::Reader reader;
    // reader.parse(ifs, obj); // reader can also read string

    Json::CharReaderBuilder builder;
    JSONCPP_STRING errs;
    if (!Json::parseFromStream(builder, ifs, &obj, &errs))
    {
        cerr << errs << endl;
    }

    // cout << "PLAIN:\n"
    //      << obj << endl;

    Json::StyledWriter st_obj;
    string styled = st_obj.write(obj);
    cout << "STAYLED:\n"
         << styled;

    // cout << "STYLED STREAM WRITER:\n";
    // Json::StyledStreamWriter styled_stream;
    // styled_stream.write(cout, obj);

    // Print type of JSON object
    switch (obj.type()) {
        case Json::nullValue: cout << "nullValue\n"; break;
        case Json::intValue: cout << "intValue\n"; break;
        case Json::uintValue: cout << "uintValue\n"; break;
        case Json::realValue: cout << "realValue\n"; break;
        case Json::stringValue: cout << "stringValue\n"; break;
        case Json::booleanValue: cout << "booleanValue\n"; break;
        case Json::arrayValue: cout << "arrayValue\n"; break;
        case Json::objectValue: cout << "objectValue\n"; break;
        default: cout << "wrong type\n"; break;
    }

    // Print JSON object or object size
    switch (obj.type()) {
        case Json::nullValue: cout << "null\n"; break;
        case Json::intValue: cout << "int " << obj.asLargestInt() << "\n"; break;
        case Json::uintValue: cout << "uint " << obj.asLargestUInt() << "\n"; break;
        case Json::realValue: cout << "real " << obj.asDouble() << "\n"; break;
        case Json::stringValue: cout << "string " << obj.asString() << "\n"; break;
        case Json::booleanValue: cout << "boolean " << obj.asBool() << "\n"; break;
        case Json::arrayValue: cout << "array of length " << obj.size() << "\n"; break;
        case Json::objectValue: cout << "object of length " << obj.size() << "\n"; break;
        default: cout << "wrong type\n"; break;
    }

    if(obj.isMember("nftables"))
        cout << "nftables\n";

    ifs.close();
    return 0;
}