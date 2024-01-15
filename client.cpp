#include "client.h"
#include "person.h"
#include <string>
#include <windows.h>
#include <mysql.h>
#include <iostream>
using namespace std;

client::client()
{
    idcl=0;
     addresse = "";
   tele = "";
}

int client::getIdcl()
{
    return idcl;
}

client::~client()
{
    //dtor
}
