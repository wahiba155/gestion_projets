#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include <windows.h>
#include <mysql.h>
#include "person.h"
#include <iostream>
using namespace std;


class client : public person
{
    public:
        client();
        virtual ~client();
        virtual void ajouterPerson()override
{
    // person::ajouterPerson();
    MYSQL *sock;
    MYSQL_ROW row = NULL;
    MYSQL_RES *res = NULL;

    sock = mysql_init(0);

    char choix;
    string str;

    if (sock)
        cout << "mysql initialise !" << endl;
    else
        cout << "impossible d'initialiser mysql!" << endl;

    char *host = "localhost";
    char *user = "root";
    char *pass = "";
    char *db = "projet";

    if (mysql_real_connect(sock, host, user, pass, db, 0, NULL, 0)){

        cout << "";

        }
    else
        cout << "connexion impossible à la base de données" << endl;
        for(int i=0;i<5;i++)
    cout << "\t";
    cout << "\033[32m";
    cout<< "*****Saisir les informations du client*****"<<endl<<endl<<endl;
    cout << "\033[0m";
    cout << "                    -ID_client         : " ;
    cin >> idcl;
    cout << "                    -Nom               : " ;
    cin >> nom;
    cout << "                    -Prenom            : " ;
    cin >> prenom;
    cout << "                    -CIN               : " ;
    cin >> c_nationalle;
    cout << "                    -Adresse           : " ;
    cin >> addresse;
     cout << "                   -Telephone         : " ;
    cin >> tele;

    str = "SELECT cin FROM client WHERE cin = '" + c_nationalle + "'";
    mysql_query(sock, str.c_str());

    res = mysql_use_result(sock);
    row = mysql_fetch_row(res);

    if (mysql_num_rows(res) > 0)
    {
        cout <<endl<< "                    ce client existe deja.." << endl;
    }
    else
    {
        str = "INSERT INTO client (idcl, nom, prenom, cin, adresse,tele) VALUES ('" +std::to_string(idcl)+ "' , '" + nom + "', '" + prenom + "', '" + c_nationalle+"','"+ addresse+ "', '" +tele+"')";
        mysql_query(sock,str.c_str());
       cout << "\033[31m";
        cout <<endl<< "                                       Client ajoutee avec succès !" << endl;
         cout << "\033[0m";
    }

    mysql_free_result(res);
    mysql_close(sock);
}
   virtual void modifierPerson()override
        {
           int choix;


        cout << "Entrez l'ID de client à modifier : ";
        cin>>idcl;
        cin.ignore();
        do {
        cout<< "\t\t\tQUELLE COLONE VOUS VOULEZ MDIFIER ?!"<<endl<<endl;
        cout << "\033[34m";
         cout << "   Entrer votre choix :" << endl<<endl;
        cout << "0. Quitter" << endl;
        cout << "1. Modifier le nom de client" << endl;
        cout << "2. Modifier le prenom de client" << endl;
        cout << "3. Modifier le numero de telephone de client " << endl;
        cout << "4. Modifier le cin" << endl;
        cout << "5. Modifier l'adresse" << endl<<endl;
         cout << "\033[0m";
        cout << "Choix : ";
        cin >> choix;
        cin.ignore();

        switch (choix) {
            case 1: {
                cout << "Entrez le nouveau nom de client : ";
                getline(cin, nom);
                modifierAttribut("nom", nom);
                break;
            }
            case 2: {
                cout << "Entrez le nouveau prenom de client : ";
                getline(cin, prenom);
                modifierAttribut("prenom", prenom);
                break;
            }
            case 3: {
                cout << "Entrez le nouveau cin : ";
                getline(cin,tele);
                modifierAttribut("tele",tele);
                break;
            }
            case 4: {
                cout << "Entrez le nouveau cin : ";
                getline(cin, c_nationalle);
                modifierAttribut("cin", c_nationalle);
                break;
            }
             case 5: {
                cout << "Entrez le nouveau adresse : ";
                getline(cin,addresse);
                modifierAttribut("adresse",addresse);
                break;
            }

            case 0: {
               cout << "\033[31m";
                cout << "Sortie du menu de modification." << endl;
                cout << "\033[0m";
                break;
            }
            default: {
                cout << "Choix invalide. Veuillez réessayer." << endl;
                break;
            }
        }

    } while (choix != 0);

}

    virtual void modifierAttribut(const std::string& attribut, const std::string& valeur)override
{

    MYSQL* conn = mysql_init(0);
    if (conn) {
        const char* host = "localhost";
        const char* user = "root";
        const char* pass = "";
        const char* db = "projet";

        if (mysql_real_connect(conn, host, user, pass, db, 0, NULL, 0)) {
            std::string query = "UPDATE client SET " + attribut + " = '" + valeur + "' WHERE idcl = " + to_string(idcl);

            if (mysql_query(conn, query.c_str()) == 0){
                cout << "\033[31m";
                cout << " modifié avec succès !" << endl;
                cout << "\033[0m";
            }
            else
                cout << "Échec de la modification du projet." << endl;
        }
        else {
            cout << "Connexion impossible à la base de données" << endl;
        }

        mysql_close(conn);
    }
    else {
        cout << "Impossible d'initialiser MySQL !" << endl;
    }
}

int getIdcl();

    private:
    int idcl;
    std::string addresse;
    std::string tele;
};

#endif // CLIENT_H
