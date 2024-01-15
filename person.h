#ifndef PERSON_H
#define PERSON_H
#include <string>
#include <windows.h>
#include <mysql.h>

class person
{
    public:
        person();
        virtual ~person();
        virtual void ajouterPerson()=0;

        virtual  void modifierPerson()=0;
         virtual void modifierAttribut(const std::string& attribut, const std::string& valeur)=0;


    protected:
    std::string nom;
    std::string prenom;
    std::string c_nationalle;
};

#endif // PERSON_H
