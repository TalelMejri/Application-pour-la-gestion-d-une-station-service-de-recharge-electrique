#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maBib.h"
#define prints(x)  for(int i=0; i < x; i++) printf(" ")
#define  endl printf("\n")

int main()
{
     printf("***************************************************************************\n");
     printf("Application pour la Gestion d une station service de recharge electrique\n");
     printf("***************************************************************************\n\n");

     int nbr_station;
     int nbr_paiment=0;
     int indice_paiment=0;

     STATION** station;
     PAIMENT* paiments;

     //Allocation Paiment
     paiments=(PAIMENT *) malloc (nbr_paiment * sizeof(PAIMENT));
     if( !paiments) exit (-1) ;

     printf("Donner Le Nombre Du Station \n");
     scanf("%d",&nbr_station);

     //Allocation Station
     station=(STATION**) malloc(nbr_station*sizeof(STATION*));
     if(!station) exit(-1);

     for(int i=0;i<nbr_station;i++){
         //Allocation Station tableau
        *(station+i)=(STATION*) malloc(sizeof(STATION));
         if(!(*station+i)) exit(-2);

         (*(station+i))->id=rand();
         printf("Les details de la station Indice :  %d  \n",i+1);

         printf("Donner Le Name Station \n");
         scanf("%s",(*(station+i))->name);

         printf("Donner Le Nombre des Bornes De Recharge : \n");
         scanf("%d",&(*(station+i))->nb_bornes);

         // Allocation Bornde De Charge :
        (*(station+i))->BorneDeRecharge=(BORNE_DE_RECHARGE*) malloc ( (*(station+i))->nb_bornes * sizeof(BORNE_DE_RECHARGE));

        // Remplir Borne De Charge
         RemplirBorneDeCharge((*(station + i))->nb_bornes, *(station + i));

         printf("Donner Le Nombre des Utilisateurs : \n");
         scanf("%d",&(*(station+i))->nb_users);

        // Allocation users
         (*(station+i))->users=(USER*) malloc ( (*(station+i))->nb_users * sizeof(USER));

         for(int compt_user=0;compt_user<(*(station+i))->nb_users;compt_user++){

                 //Ajouter User
                 init_user(((*(station+i))->users+compt_user));

                //Allocation User
                (*((*(station+i))->users+compt_user)).reserves=(RESERVATION*) malloc((*( (*(station + i))->users + compt_user)).nb_reserves*sizeof(RESERVATION));

                //Afficher Borne De Recharge
                TableauBorneDeRecharge((*(station + i))->nb_bornes, *(station + i));

             for (int compt_reserve = 0; compt_reserve < (*( (*(station + i))->users + compt_user)).nb_reserves; compt_reserve++) {

                        printf("ID User %d \n",  (*( (*(station + i))->users + compt_user)).id);

                        printf("Donner ID Du Borne de Recharge \n");
                        scanf("%d", &((*((*(station+i))->users+compt_user)).reserves+compt_reserve)->id_borne);

                        nbr_paiment++;
                        //Realloc Paiments
                        paiments= (PAIMENT*) realloc (paiments, nbr_paiment * sizeof(PAIMENT));
                        if( !paiments) exit (-1) ;

                        //Ajouter Paiment
                        init_paiment(paiments+indice_paiment);

                        ((*((*(station+i))->users+compt_user)).reserves+compt_reserve)->id_paiment= (paiments + indice_paiment)->id;
                        ((*((*(station+i))->users+compt_user)).reserves+compt_reserve)->id_user= (*( (*(station + i))->users + compt_user)).id;

                        indice_paiment++;

                        printf("Donner Date Debut  : \n");
                        entrer_date(&((*((*(station+i))->users+compt_user)).reserves+compt_reserve)->date_debut);
                        printf("Donner Date FIN  : \n");
                        entrer_date(&((*((*(station+i))->users+compt_user)).reserves+compt_reserve)->date_fin);
                }
         }
     }


     printf("---------------------------------------Affichage--------------------------------------------");

     for(int i=0;i<nbr_station;i++){
          printf(".................... Station ID : %d ...................\n",   (*(station+i))->id);
          printf("Name %s : \n",(*(station+i))->name);
          printf(" Nombre des Bornes De Recharge  : %d: \n",(*(station+i))->nb_bornes);

         TableauBorneDeRecharge((*(station + i))->nb_bornes, *(station + i));
         printf(" Nombre des Utilisateurs  : %d \n",(*(station+i))->nb_users);

         for(int compt_user=0;compt_user<(*(station+i))->nb_users;compt_user++){
                //afficher details User
                afficher_details_user(*( (*(station + i))->users + compt_user));

                for (int compt_reserve = 0; compt_reserve < (*( (*(station + i))->users + compt_user)).nb_reserves; compt_reserve++) {
                        printf("ID Du Borne de Recharge  %d \n",((*((*(station+i))->users+compt_user)).reserves+compt_reserve)->id_borne);
                        int id_paiment = ((*((*(station+i))->users+compt_user)).reserves+compt_reserve)->id_paiment;

                        //afficher details paiment
                        afficher_details_paiment(paiments, nbr_paiment, id_paiment);

                        //Affiche Date Debut et Date Fin
                        printf("Date de debut de la reservation : ");
                        DATE   date_debut= ((*((*(station+i))->users+compt_user)).reserves+compt_reserve)->date_debut;
                        afficher_date(date_debut);

                        printf("Date de fin de la reservation : ");
                        DATE   date_fin= ((*((*(station+i))->users+compt_user)).reserves+compt_reserve)->date_fin;
                        afficher_date(date_fin);
                }
         }
     }

    afficherBornesDisponibles(station, nbr_station);

    DATE date_debut, date_fin;

    printf("Entrer la date de debut de la reservation :\n");
    entrer_date(&date_debut);

    printf("Entrer la date de fin de la reservation :\n");
    entrer_date(&date_fin);
    USER* user;

    user=utilisateur_max_reservations(station,nbr_station,date_debut,date_fin);
    if (user != NULL) {
        printf("Utilisateur avec Nom %s  le plus de reservations \n", user->nom);
    } else {
        printf("Aucun utilisateur trouve .\n");
    }

   RESERVATION* reserve = reservation_durable(station, nbr_station, paiments, nbr_paiment);
    if (reserve != NULL) {
        printf("Id User %d", reserve->id_user);
    } else {
        printf("Aucune reservation trouvee.\n");
    }


     RESULTAT** resultat;
     resultat=(RESULTAT**) malloc(3*sizeof(RESULTAT*));
     if(!resultat){
        exit(-1);
     }

     trierStationsParBornes(station, nbr_station);

     for(int i=0; i<3; i++)
    {
        *(resultat+i)=(RESULTAT*) malloc (sizeof(RESULTAT));
        if(! *(resultat+i) ) exit(-2);
        (*(resultat+i))->nbr_bornes = (*(station+i))->nb_bornes;
        strcpy((*(resultat+i))->name ,(*(station+i))->name);
    }

    printf("\n Les 3 stations avec le plus de bornes :\n");
    for (int i = 0; i < 3; i++) {
         printf("Station %d | Nom: %s, Nombre de bornes: %d\n", i + 1,    (*(resultat+i))->name,  (*(resultat+i))->nbr_bornes);
    }
    free(resultat);


    for(int i=0;i<nbr_station;i++){
        free(*(station+i));
    }

     free(paiments);
     station=NULL;
     paiments=NULL;
     free(station);
     return 0;
}
