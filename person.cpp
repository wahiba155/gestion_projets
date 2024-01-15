#include "person.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <mysql.h>

using namespace std;
person::person()
{
   nom = "";
   prenom = "";
   c_nationalle = "";
}

person::~person()
{
    //dtor
}
