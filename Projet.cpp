#include "Projet.h"
#include <iostream>
#include <windows.h>
#include <mysql.h>
#include <memory>

using namespace std;

Projet::Projet()
{
   idp=0;
   nom = "";
   date_fin = "";
   date_debut = "";
   budget = 0.0;
   statu = "Au_début";
   idcl = 0;
   idc  = 0;
}

Projet::~Projet()
{

}

void Projet::ajouterProjet()
{
    MYSQL *sock;
    MYSQL_ROW row = NULL;
    MYSQL_RES *res = NULL;

    sock = mysql_init(0);

    char choix;
    string str;

    if (sock)
        cout << "" << endl;
    else
        cout << "impossible d'initialiser mysql!" << endl;

    char *host = "localhost";
    char *user = "root";
    char *pass = "";
    char *db = "projet";
    string niveau;
    if (mysql_real_connect(sock, host, user, pass, db, 0, NULL, 0))
    {
        // Connexion réussie à la base de données
        cout << "" << endl;
    }
    else
    {
        cout << "Connexion impossible à la base de données" << endl;
        return;
    }

    // Saisie des informations du projet
    for(int i=0;i<7;i++)
    cout << "\t";
    cout << "\033[32m";
    cout<< "*****Saisir les informations du projet*****"<<endl<<endl<<endl;
    cout << "\033[0m";
    cout << "                     - id du projet      : ";
    cin >> idp;
    cout << "                     - nom               : ";
    cin >> nom;
    cout << "                     - date de début     : ";
    cin >> date_debut;
    cout << "                     - date de fin       : ";
    cin >> date_fin;
    cout << "                     - budget            : ";
    cin >> budget;
    cout << "    - statut : " << endl;

cout << "\033[34m";
cout << "                              1. En début" << endl;
cout << "                              2. En progrès" << endl;
cout << "                              3. Terminé" << endl<<endl;
cout << "\033[0m";
cout << "   Choisissez un statut en saisissant le numéro correspondant : ";

int statuChoice;
cin >> statuChoice;

switch (statuChoice) {
    case 1:
        statu = "En début";
        break;
    case 2:
        statu = "En progrès";
        break;
    case 3:
        statu = "Terminé";
        break;
    default:
        cout << "Choix de statut invalide. Statut par défaut : En début." << endl;
        statu = "En début";
        break;}

    cout << "    - id du client      : ";
    cin >> idcl;
    cout << "\033[34m"; cout << "    - quel niveau pour le chef de projet : "<<endl<<endl;cout << "\033[0m";

     cout << "           1.Ingenieur_en_developement_web" << endl;
     cout << "           2.Ingenieur_administration_reseau" << endl;
     cout << "           3.Ingenieur_developpement_de_system_informatique" << endl;
     cout << "           4.Expert_en_developement_des_systemes_embarques" << endl;
     cout << "           5.Technicien_superieur_en_developpement " << endl;
     cout << "           Choisissez un niveau en saisissant le numéro correspondant : ";

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


    str = "SELECT * FROM chef WHERE niv_exp = '" + niveau + "'";
    mysql_query(sock, str.c_str());
    res = mysql_use_result(sock);
    row = mysql_fetch_row(res);

    if (!row)
    {
        cout << "Il n'y a aucun chef pour ce niveau" << endl;
    }
    else
    {
        // Affichage des informations du chef
        cout << "\n\t\t\t\t\t Le chef" << endl;
        cout << "\n";
        cout << "\t\t\t\t\t ------------------------------------" << endl;
        cout << "\t\t\t\t\t id du chef           |\t" << row[0] << endl;
        cout << "\t\t\t\t\t ------------------------------------" << endl;
        cout << "\t\t\t\t\t niveau               |\t" << row[1] << endl;
        cout << "\t\t\t\t\t ------------------------------------" << endl;
        cout << "\t\t\t\t\t nom                  |\t" << row[2] << endl;
        cout << "\t\t\t\t\t ------------------------------------" << endl;
        cout << "\t\t\t\t\t prenom               |\t" << row[3] << endl;
        cout << "\t\t\t\t\t ------------------------------------" << endl;
        cout << "\t\t\t\t\t cin                  |\t" << row[4] << endl;
        cout << "\t\t\t\t\t ------------------------------------" << endl;
        }

        // Assigner l'idc (id du chef) pour le projet
       idc = std::stoi(row[0]);

        mysql_free_result(res);

        /*cout << "    - idc               : ";
        cin >> idc;*/

        str = "SELECT nom FROM projet WHERE nom = '" + nom +"'";
        mysql_query(sock, str.c_str());

        res = mysql_use_result(sock);
        row = mysql_fetch_row(res);

        if (mysql_num_rows(res) > 0)
        {
            cout << "Ce projet existe déjà." << endl;
        }
        else
        {

            str = "INSERT INTO projet (idp, nom, date_debut, date_fin, budget, statu, idcl, idc) VALUES ('" +
      std::to_string(idp) + "', '" + nom + "', '" + date_debut + "', '" + date_fin + "', '" +
      std::to_string(budget) + "', '" + statu + "', '" +
      std::to_string(idcl) + "', '" + std::to_string(idc) + "')";

            mysql_query(sock, str.c_str());
            cout << "\033[31m";
        cout << "projet ajoute avec succès !" << endl;
        cout << "\033[0m";
        }


    mysql_free_result(res);
    mysql_close(sock);
}

void Projet::chercherProjet()
{
    MYSQL *sock;
    MYSQL_ROW row = NULL;
    MYSQL_RES *res = NULL;

    sock = mysql_init(0);

    if (sock)
        cout << "" << endl;
    else
    {
        cout << "Impossible d'initialiser MySQL !" << endl;
        return;
    }

    const char *host = "localhost";
    const char *user = "root";
    const char *pass = "";
    const char *db = "projet";

    if(mysql_real_connect(sock, host, user, pass, db, 0, NULL, 0))
        cout << "" << endl;
    else
    {
        cout << "Connexion impossible à la base de données" << endl;
        return;
    }


    cout << "Entrez l'ID du projet à rechercher : ";
    cin >> idp;

    string str = "SELECT * FROM projet WHERE idp = " +std::to_string(idp);
    mysql_query(sock, str.c_str());

    res = mysql_use_result(sock);
    row = mysql_fetch_row(res);

    if (!row)
    {
        cout << "Projet introuvable" << endl;
    }
    else
    {
        // Afficher les détails du projet

         cout<< "\t \t \t \t \t le projet correspond à l'id "<<idp<<" : "<<endl;
                 cout<<"\n";
        cout<<"\t \t \t \t \t";cout <<"------------------------------------"<< endl;
        cout<<"\t \t \t \t \t";cout <<"ID du projet      |\t" << row[0]       << endl;
        cout<<"\t \t \t \t \t";cout <<"------------------------------------"<< endl;
        cout<<"\t \t \t \t \t";cout <<"Nom               |\t" << row[1]       << endl;
        cout<<"\t \t \t \t \t";cout <<"------------------------------------"<< endl;
        cout<<"\t \t \t \t \t";cout <<"Date de début     |\t" << row[2]       << endl;
        cout<<"\t \t \t \t \t";cout <<"------------------------------------"<< endl;
        cout<<"\t \t \t \t \t";cout <<"Date de fin       |\t" << row[3]       << endl;
        cout<<"\t \t \t \t \t";cout <<"------------------------------------"<< endl;
        cout<<"\t \t \t \t \t";cout <<"Budget            |\t" << row[4]       << endl;
        cout<<"\t \t \t \t \t";cout <<"------------------------------------"<< endl;
        cout<<"\t \t \t \t \t";cout <<"Statut            |\t" << row[5]       << endl;
        cout<<"\t \t \t \t \t";cout <<"------------------------------------"<< endl;
        cout<<"\t \t \t \t \t";cout <<"ID du client      |\t" << row[6]       << endl;
        cout<<"\t \t \t \t \t";cout <<"------------------------------------"<< endl;
        cout<<"\t \t \t \t \t";cout <<"ID du chef        |\t" << row[7]       << endl;
        cout<<"\t \t \t \t \t";cout <<"------------------------------------"<< endl;
    }

    mysql_free_result(res);
    mysql_close(sock);
}
