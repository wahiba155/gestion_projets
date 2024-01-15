#ifndef CHEF_H
#define CHEF_H
#include <string>
#include <windows.h>
#include <mysql.h>
#include <iostream>
#include "person.h"

using namespace std;

class chef : public person
{
    public:
        chef();
        virtual ~chef();
        virtual void modifierPerson()override
        {
           int choix;


        cout << "Entrez l'ID d'expert à modifier : ";
        cin>>idc;
        cin.ignore();
        do {
        cout << " \t\t\t\tQUEL COLONNE VOUS SOUHAITEZ MODIFIER ??" << endl;
        cout << "\033[34m";
        cout << "   Entrer votre choix :" << endl<<endl;
        cout << "0. Quitter" << endl;
        cout << "1. Modifier le nom d'expert" << endl;
        cout << "2. Modifier le prenom d'expert" << endl;
        cout << "3. Modifier le cin d'expert" << endl;
        cout << "4. Modifier le niveau d'expert" << endl<<endl;
        cout << "\033[34m";
        cout << "Choix : ";
        cin >> choix;
        cin.ignore();

        switch (choix) {
            case 1: {
                cout << "Entrez le nouveau nom d'expert : ";
                getline(cin, nom);
                modifierAttribut("nom", nom);
                break;
            }
            case 2: {
                cout << "Entrez le nouveau prenom d'expert : ";
                getline(cin, prenom);
                modifierAttribut("prenom", prenom);
                break;
            }
            case 3: {
                cout << "Entrez le nouveau cin : ";
                getline(cin, c_nationalle);
                modifierAttribut("cin", c_nationalle);
                break;
            }
            case 4: {
                cout << "Entrez le nouveau niveau d'expert : ";

                cin >> niv;
                cin.ignore();
                modifierAttribut("niv_exp",niv);
                break;
            }

            case 0: {
                cout << "Sortie du menu de modification." << endl;
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
            std::string query = "UPDATE chef SET " + attribut + " = '" + valeur + "' WHERE idc = " + to_string(idc);

            if (mysql_query(conn, query.c_str()) == 0)
                cout << " modifié avec succès !" << endl;
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
        virtual void ajouterPerson()override
{
         // person::ajouterPerson();
    MYSQL *sock;
    MYSQL_ROW row = NULL;
    MYSQL_RES *res = NULL;

    sock = mysql_init(0);

    char choix;
    string str;
    string niveau;

    if (sock)
        cout << "" << endl;
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
    cout<< "**Saisir les informations du chef**"<<endl<<endl<<endl;
    cout << "                    -ID_chef              : " ;
    cin >> idc;
    cout << "                    -Nom               : " ;
    cin >> nom;
    cout << "                    -Prenom            : " ;
    cin >> prenom;
    cout << "                    -CIN      : " ;
    cin >> c_nationalle;
    cout << "                -Niveau d'experience      : "<<endl;
    cout << "      1.Ingenieur_en_developement_web" << endl;
     cout << "      2.Ingenieur_administration_reseau" << endl;
     cout << "      3.Ingenieur_developpement_de_system_informatique" << endl;
     cout << "      4.Expert_en_developement_des_systemes_embarques" << endl;
     cout << "      5.Technicien_superieur_en_developpement " << endl;
     cout << "   Choisissez un niveau en saisissant le numéro correspondant : ";

    int niveauChoice;
    cin >> niveauChoice;

switch (niveauChoice) {
    case 1:
        niveau = "Ingenieur_en_developement_web";
        break;
    case 2:
        niveau = "Ingenieur_administration_reseau";
        break;
    case 3:
        niveau = "Ingenieur_developpement_de_system_informatique";
        break;
    case 4:
        niveau = "Expert_en_developement_des_systemes_embarques";
        break;
    case 5:
        niveau = "Technicien_superieur_en_developpement";
        break;
    default:
        cout << "Choix  invalide." << endl;
        break;}

    str = "SELECT idc FROM chef WHERE idc = " + std::to_string(idc);
    mysql_query(sock, str.c_str());

    res = mysql_use_result(sock);
    row = mysql_fetch_row(res);

    if (mysql_num_rows(res) > 0)
    {
        cout <<endl<< "                    ce chef existe deja.." << endl;
    }
    else
    {
        str = "INSERT INTO chef (idc, nom, prenom, cin, niv_exp) VALUES ('" +std::to_string(idc)+ "' , '" + nom + "', '" + prenom + "', '" + c_nationalle+"','"+ niveau+"')";
        mysql_query(sock,str.c_str());
       cout << "\033[31m";
        cout <<endl<< "                                       chef ajoutee avec succès !" << endl;
         cout << "\033[0m";
    }

    mysql_free_result(res);
    mysql_close(sock);
}


    private:
        int idc;
        std::string niv;
};

#endif // CHEF_H
