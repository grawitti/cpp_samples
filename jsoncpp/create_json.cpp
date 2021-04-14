#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h> // or something

using namespace std;

void json_add_table(Json::Value &jval, const char *family, const char *tb_name)
{
    if(family == NULL)
        jval["add"]["table"]["family"] = "ip";
    else 
        jval["add"]["table"]["family"] = family;
    
    jval["add"]["table"]["name"] = tb_name;
}

int main(int argc, char const *argv[])
{
    const char *tb_name = "mytable";
    Json::Value nftables;
    json_add_table(nftables, NULL, tb_name);

    Json::Value root;
    root["nftables"].append(nftables);

    Json::StyledWriter st_wr;
    string styled = st_wr.write(root);

    cout << styled;

    return 0;
}

