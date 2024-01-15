#ifndef PROJET_H
#define PROJET_H
#include "client.h"
#include <string>
#include <windows.h>
#include <mysql.h>
#include <vector>
#include <iostream>
using namespace std;

class Projet
{
    public:
        Projet();
        ~Projet();
        void chercherProjet();
        void ajouterProjet();
        void modifierProjet(){
         int choix;


        cout << "Entrez l'ID du projet � modifier : ";
        cin>>idp;
        cin.ignore();
        do {
        cout<< "\t\t\tQUELLE COLONE VOUS VOULEZ MDIFIER ?!"<<endl<<endl;
        cout << "\033[34m";
        cout << "\t\t\t1. Modifier le nom du projet" << endl;
        cout << "\t\t\t2. Modifier la date de d�but du projet" << endl;
        cout << "\t\t\t3. Modifier la date de fin du projet" << endl;
        cout << "\t\t\t4. Modifier le budget du projet" << endl;
        cout << "\t\t\t5. Modifier le statut du projet" << endl;
        cout << "\t\t\t6. Modifier l'ID du client associ� au projet" << endl;
        cout << "\t\t\t7. Modifier l'ID du chef associ� au projet" << endl;
        cout << "\t\t\t0. Quitter" << endl<<endl;
         cout << "\033[0m";
        cout << "Choix : ";
        cin >> choix;
        cin.ignore();

        switch (choix) {
            case 1: {
                cout << "Entrez le nouveau nom du projet : ";
                getline(cin, nom);
                modifierAttribut("nom", nom);
                break;
            }
            case 2: {
                cout << "Entrez la nouvelle date de d�but du projet : ";
                getline(cin, date_debut);
                modifierAttribut("date_debut", date_debut);
                break;
            }
            case 3: {
                cout << "Entrez la nouvelle date de fin du projet : ";
                getline(cin, date_fin);
                modifierAttribut("date_fin", date_fin);
                break;
            }
            case 4: {
                cout << "Entrez le nouveau budget du projet : ";
                cin >> budget;
                cin.ignore();
                modifierAttribut("budget", to_string(budget));
                break;
            }
            case 5: {
                cout << "Entrez le nouveau statut du projet :" << endl;
                cout << "\033[34m";
                cout << "   1. En d�but" << endl;
                cout << "   2. En progr�s" << endl;
                cout << "   3. Termin�" << endl;
                cout << "\033[0m";
                cout << "Choisissez un statut en saisissant le num�ro correspondant : ";
                int statuChoice;
                cin >> statuChoice;
                cin.ignore();
                string statu;

                switch (statuChoice) {
                    case 1: {
                        statu = "En d�but";
                        break;
                    }
                    case 2: {
                        statu = "En progr�s";
                        break;
                    }
                    case 3: {
                        statu = "Termin�";
                        break;
                    }
                    default: {
                        cout << "Choix de statut invalide. Statut par d�faut : En d�but." << endl;
                        statu = "En d�but";
                        break;
                    }
                }

                modifierAttribut("statu", statu);
                break;
            }
            case 6: {
                cout << "Entrez le nouvel ID du client associ� au projet : ";
                cin >> idcl;
                cin.ignore();
                modifierAttribut("idcl", to_string(idcl));
                break;
            }
            case 7: {
                cout << "Entrez le nouvel ID du chef associ� au projet : ";
                cin >> idc;
                cin.ignore();
                modifierAttribut("idc", to_string(idc));
                break;
            }
            case 0: {
                cout << "Sortie du menu de modification." << endl;
                break;
            }
            default: {
                cout << "Choix invalide. Veuillez r�essayer." << endl;
                break;
            }
        }

    } while (choix != 0);
}

void modifierAttribut(const string& attribut, const string& valeur)
{

    MYSQL* conn = mysql_init(0);
    if (conn) {
        const char* host = "localhost";
        const char* user = "root";
        const char* pass = "";
        const char* db = "projet";

        if (mysql_real_connect(conn, host, user, pass, db, 0, NULL, 0)) {
            string query = "UPDATE projet SET " + attribut + " = '" + valeur + "' WHERE idp = " + to_string(idp);

            if (mysql_query(conn, query.c_str()) == 0)
                {cout <<"\033[31m";
                cout << "Le projet a �t� modifi� avec succ�s !" << endl;
                cout << "\033[0m";}
            else
                cout << "�chec de la modification du projet." << endl;
        }
        else {
            cout << "Connexion impossible � la base de donn�es" << endl;
        }

        mysql_close(conn);
    }
    else {
        cout << "Impossible d'initialiser MySQL !" << endl;
    }
}
       void supprimerProjet() {
    cout << "Entrez l'ID du projet � supprimer : ";
    cin >> idp;
    cin.ignore();

    // Connexion � la base de donn�es et ex�cution de la requ�te DELETE
    MYSQL* conn = mysql_init(0);
    MYSQL_RES* res;
    MYSQL_ROW row;
    if (conn) {
        const char* host = "localhost";
        const char* user = "root";
        const char* pass = "";
        const char* db = "projet";

           if (mysql_real_connect(conn, host, user, pass, db, 0, NULL, 0)) {
            string query = "SELECT idp FROM projet WHERE idp = " + to_string(idp);
            if (mysql_query(conn, query.c_str()) == 0) {
                res = mysql_use_result(conn);
                row = mysql_fetch_row(res);

                if (!row) {
                    cout << "Projet introuvable" << endl;
                } else {
                    mysql_free_result(res);

                    query = "DELETE FROM projet WHERE idp = " + to_string(idp);
                    if (mysql_query(conn, query.c_str()) == 0) {
                        mysql_commit(conn);
                         cout << "\033[31m";
                        cout << "Le projet a �t� supprim� avec succ�s !" << endl;
                        cout << "\033[0m";
                    } else {
                        cout << "�chec de la suppression du projet." << endl;
                    }
                }
            } else {
                cout << "�chec de la requ�te SELECT." << endl;
            }
        } else {
            cout << "Connexion impossible � la base de donn�es" << endl;
        }

        mysql_close(conn);
    } else {
        cout << "Impossible d'initialiser MySQL !" << endl;
    }
}

        private:
    int idp;
    std::string nom;
    std::string date_fin;
    std::string date_debut;
    double budget;
    std::string statu;
    int idcl;
    int idc;
};

#endif // PROJET_H
