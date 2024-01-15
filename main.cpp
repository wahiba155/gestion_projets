#include <iostream>
#include "Projet.h"
#include "person.h"
#include "client.h"
#include "chef.h"
#include <windows.h>
#include <mysql.h>
#include <memory>
#include <cstdlib>

using namespace std;
void afficherTableauDeBord()
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

    if (mysql_real_connect(sock, host, user, pass, db, 0, NULL, 0))
        cout << "" << endl;
    else
    {
        cout << "Connexion impossible à la base de données" << endl<<endl;
        return;
    }

    string statut = "En progrès";
    string str = "SELECT * FROM projet WHERE statu ='" + statut + "'";
    mysql_query(sock, str.c_str());

    res = mysql_use_result(sock);

   cout << "\033[31m";cout << "                                         ***********************PROJET EN PROGRES***********************: " << endl<<endl; cout<< "\033[0m";
   cout<<"\t\t";cout<<"                        _______________________________________________________________         "<<endl;
        cout<<"\t\t";cout << "\033[31m"; cout << "                        NOM                                    |\t  STATUS" <<endl; cout << "\033[0m";
        cout<<"\t\t";cout<<"                        _______________________________________________________________         "<<endl;

    while ((row = mysql_fetch_row(res)) != NULL)
    {


       cout<<"\t\t";                     cout<<"                        ";    cout <<row[1]<<"                                  "<<row[5]<<endl;

    }
      cout<<"\t\t";cout<<"                        _______________________________________________________________         "<<endl;


    mysql_free_result(res);
    mysql_close(sock);
}

void decore()
{
    for(int i = 0; i < 9; i++)
        cout << "\t";
    cout << "\033[32m";  // Code d'échappement ANSI pour la couleur verte
    cout << "*                         *" << endl;
    cout << "\033[0m";  // Code d'échappement ANSI pour réinitialiser la couleur

    for(int i = 0; i < 9; i++)
        cout << "\t";
}

int main()
{
    Projet p;
    client c;
    chef ch;
    int choix;
       afficherTableauDeBord();
    while (true) {
          system("pause");
        cout << endl
             << endl;
        for (int i = 0; i < 10; i++)
            cout << "\t*";
        cout << "\033[32m";  //  la couleur verte
        cout << " Menu ";
        cout << "\033[0m";
        for (int i = 0; i < 10; i++)
            cout << "*\t";

        for (int i = 0; i < 4; i++)
            cout << endl;
        for (int i = 0; i < 10; i++)
            cout << "\t";
        cout << "\033[32m";  //  la couleur verte
        cout << "********";
        cout << "\033[0m";  //
        cout << endl
             << endl;
        for (int i = 0; i < 9; i++)
            cout << "\t";
        cout << "*  1. Ajouter un projet   *" << endl;
        decore();
        cout << "*  2. Supprimer un projet *" << endl;
        decore();
        cout << "*  3. Chercher un projet  *" << endl;
        decore();
        cout << "*  4. Modifier un projet  *" << endl;
        decore();
        cout << "*  5. Ajouter client      *" << endl;
        decore();
        cout << "*  6. Ajouter expert      *" << endl;
        decore();
        cout << "*  7. Modifier client     *" << endl;
        decore();
        cout << "*  8. Modifier expert     *" << endl;
        decore();
        cout << "*  0. Quitter             *" << endl
             << endl;
        for (int i = 0; i < 10; i++)
            cout << "\t";
        cout << "\033[32m";  // Code d'échappement ANSI pour la couleur verte
        cout << "********";
        cout << "\033[0m";  // Code d'échappement ANSI pour réinitialiser la couleur
        cout << endl
             << endl
             << endl;
        for (int i = 0; i < 9; i++)
            cout << "\t";
        cout << "\033[32m";  // Code d'échappement ANSI pour la couleur verte
        cout << "Veuillez choisir une option : ";
        cout << "\033[0m";  // Code d'échappement ANSI pour réinitialiser la couleur
       cout<<endl;
        for (int i = 0; i < 7; i++)
            cout << "\t";
        cin>>choix;
        // Traitement des choix
        switch (choix) {
            case 0:
                cout << "Au revoir !" <<endl;
                 return 0;
            case 1:
                p.ajouterProjet();
                break;
            case 2:
                p.supprimerProjet();
                break;
            case 3:
                p.chercherProjet();
                break;
            case 4:
                p.modifierProjet();
                break;
            case 5:
                c.ajouterPerson();
                break;
            case 6:
                ch.ajouterPerson();
                break;
            case 7:
                c.modifierPerson();
                break;
            case 8:
                ch.modifierPerson();
                break;
            default:
                cout << "Choix invalide. Veuillez entrer une option valide." <<endl;

        }
        system("pause"); // Fait une pause jusqu'à ce qu'une touche soit pressée
        system("cls");   // Efface l'affichage précédent

    }

    return 0;
}
