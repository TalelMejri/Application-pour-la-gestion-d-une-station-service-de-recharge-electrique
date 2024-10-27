#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "maBib.h"
#define prints(x)  for(int i=0; i < x; i++) printf(" ")
#define  endl printf("\n")

int main()
{
     endl;prints(28);printf("***************************************************************************\n");
     prints(28);printf("Application pour la gestion d une station service de recharge electrique\n");
     prints(28);printf("***************************************************************************\n\n");

     int nbr_station;
     STATION **station;
     PAIMENT* paiments;
     int nbr_paiment=0;
     int indice_paiment=0;
     paiments=(PAIMENT *) malloc (nbr_paiment * sizeof(PAIMENT));
     if( !paiments) exit (-1) ;
     prints(50);
     printf("Donner Le Nombre Du Station \n");
     prints(50);
     scanf("%d",&nbr_station);

     station=(STATION**) malloc(nbr_station*sizeof(STATION*));
     if(!station){
        exit(-1);
     }

     for(int i=0;i<nbr_station;i++){
        *(station+i)=(STATION*) malloc(sizeof(STATION));
         if(!(*station+i)){
            exit(-2);
         }

         (*(station+i))->id=rand();
         endl;prints(50);
         printf("Les details de la station Indice :  %d  \n",i+1);
         endl;prints(50);
         printf("Donner Le Name Station \n");
         prints(50);
         scanf("%s",(*(station+i))->name);

         prints(50);printf("Donner Le Nombre des Bornes De Recharge : \n");
         prints(50);scanf("%d",&(*(station+i))->nb_bornes);

        (*(station+i))->BorneDeRecharge=(BORNE_DE_RECHARGE*) malloc ( (*(station+i))->nb_bornes * sizeof(BORNE_DE_RECHARGE));

        for(int compt_borne=0;compt_borne<(*(station+i))->nb_bornes;compt_borne++){
                (*( (*(station + i))->BorneDeRecharge + compt_borne)).id = rand();
                endl;prints(50);printf("Details BORNE DE RECHARGE Avec Indice %d\n",  compt_borne+1);
                prints(50);printf("-----------------------------\n");

                 prints(50);printf("Saisir Type  (0=Rapide, 1=Normal) \n");
                 int type;
                 prints(50);scanf("%d", &type);
                 (*( (*(station + i))->BorneDeRecharge + compt_borne)).type = type == 0 ? Rapide : Normal;
                 prints(50);printf("Saisir Puissance: \n");
                 prints(50);scanf("%d", &(*( (*(station + i))->BorneDeRecharge + compt_borne)).puissance);

                 prints(50); printf("Status (0=Disponible, 1=Occupe, 2=Hors_Service): \n");
                 int status;
                 prints(50);scanf("%d", &status);
                 (*( (*(station + i))->BorneDeRecharge + compt_borne)).status = (STATUS) status;
                 (*( (*(station + i))->BorneDeRecharge + compt_borne)).nb_reserves=0;
                 (*( (*(station + i))->BorneDeRecharge + compt_borne)).reserves=NULL;

                prints(50);printf("-----------------------------\n");
        }

         prints(50);printf("Donner Le Nombre des Utilisateurs : \n");
         prints(50);scanf("%d",&(*(station+i))->nb_users);

         (*(station+i))->users=(USER*) malloc ( (*(station+i))->nb_users * sizeof(USER));

         for(int compt_user=0;compt_user<(*(station+i))->nb_users;compt_user++){
                 (*( (*(station + i))->users + compt_user)).id = rand();
                endl;prints(50);printf("Details USER  Indice %d\n",  compt_user+1);
                prints(50);printf("-----------------------------\n");
                prints(50);
                printf("Donner Le Nom \n");
                prints(50);
                scanf("%s",(*( (*(station + i))->users + compt_user)).nom);
                prints(50);
                printf("Donner Le Prenom \n");
                prints(50);
                scanf("%s",(*( (*(station + i))->users + compt_user)).prenom);
                prints(50);
                printf("Donner Le Numero Telephone \n");
                prints(50);
                scanf("%d",&(*( (*(station + i))->users + compt_user)).num_tlf);
                prints(50);
                printf("Donner Le Nombre Du Reservation \n");
                prints(50);
                scanf("%d",&(*( (*(station + i))->users + compt_user)).nb_reserves);
                (*((*(station+i))->users+compt_user)).reserves=(RESERVATION*) malloc((*( (*(station + i))->users + compt_user)).nb_reserves*sizeof(RESERVATION));
                endl;prints(50);printf("Tableau BorneDeRecharge \n");

                prints(50);
                printf("------------------------------------\n");
                prints(50);
                printf("| ID | Type     | Puissance | Status |\n");
                prints(50);
                printf("------------------------------------\n");

                for (int compt_borne = 0; compt_borne < (*(station + i))->nb_bornes; compt_borne++) {
                        (*( (*(station + i))->BorneDeRecharge + compt_borne)).id = rand();
                        int type = (*( (*(station + i))->BorneDeRecharge + compt_borne)).type;
                        int puissance = (*( (*(station + i))->BorneDeRecharge + compt_borne)).puissance;
                        int status = (*( (*(station + i))->BorneDeRecharge + compt_borne)).status;
                        endl;
                        prints(50); printf("| %d | %s |%d       | %s    |\n",
                        (*( (*(station + i))->BorneDeRecharge + compt_borne)).id,
                        type == 0 ? "Rapide" : "Normal",
                        puissance,
                        status == 0 ? "Disponible" : status == 1 ? "Occupe" : "Hors_Service"
                        );
                        prints(50);
                        printf("------------------------------------\n");
                }

                for (int compt_reserve = 0; compt_reserve < (*( (*(station + i))->users + compt_user)).nb_reserves; compt_reserve++) {
                        prints(50);printf("ID User %d ",  (*( (*(station + i))->users + compt_user)).id);
                        endl;prints(50);
                        printf("Donner ID Du Borne de Recharge \n");
                        prints(50);
                        scanf("%d", &((*((*(station+i))->users+compt_user)).reserves+compt_reserve)->id_borne);

                        nbr_paiment++;
                        paiments= (PAIMENT*) realloc (paiments, nbr_paiment * sizeof(PAIMENT));
                        if( !paiments) exit (-1) ;

                        (paiments+indice_paiment)->id=rand();
                        endl;prints(50);printf("Details Paiment \n");
                        prints(50);printf("-----------------------------\n");
                        prints(50);printf("Saisir montant \n");
                        prints(50);scanf("%lf", &(paiments+indice_paiment)->montant);
                        prints(50); printf("TYPE (0=Sur Place, 1=En Ligne ) \n");
                        int type_paiment;
                        prints(50);scanf("%d", &type_paiment);
                        (paiments+indice_paiment)->Type = (METHODE) type_paiment;
                        if(type_paiment==0){
                            strcpy((paiments + indice_paiment)->Token, "");
                        }else{
                            sprintf((paiments + indice_paiment)->Token, "Pass%d", (paiments + indice_paiment)->id);
                        }
                        ((*((*(station+i))->users+compt_user)).reserves+compt_reserve)->id_paiment= (paiments + indice_paiment)->id;
                        indice_paiment++;
                        endl;
                        prints(50);

                        DATE date_debut;
                        printf("Donner Date Debut  : \n");
                        prints(50);printf("donner jour \n");
                        prints(50);scanf("%d",&date_debut.jour);
                        prints(50);printf("donner mois \n");
                        prints(50);scanf("%d",&date_debut.mois);
                        prints(50);printf("donner annee \n");
                        prints(50);scanf("%d",&date_debut.annee);
                        prints(50);printf("donner heure \n");
                        prints(50);scanf("%d",&date_debut.heure);
                        prints(50);printf("donner minute \n");
                        prints(50);scanf("%d",&date_debut.minute);

                        endl;prints(50);
                        DATE date_fin;
                        printf("Donner Date FIN  : \n");
                        prints(50);printf("donner jour \n");
                        prints(50);scanf("%d",&date_fin.jour);
                        prints(50);printf("donner mois \n");
                        prints(50);scanf("%d",&date_fin.mois);
                        prints(50);printf("donner annee \n");
                        prints(50);scanf("%d",&date_fin.annee);
                        prints(50);printf("donner heure \n");
                        prints(50);scanf("%d",&date_fin.heure);
                        prints(50);printf("donner minute \n");
                        prints(50);scanf("%d",&date_fin.minute);
                        ((*((*(station+i))->users+compt_user)).reserves+compt_reserve)->date_debut=date_debut;
                        ((*((*(station+i))->users+compt_user)).reserves+compt_reserve)->date_fin=date_fin;

                }
                endl;
         }
     }

     prints(50);
     printf("---------------------------------------Affichage--------------------------------------------");

     for(int i=0;i<nbr_station;i++){
         endl;prints(50);printf(".................... Station ID : %d ...................\n",   (*(station+i))->id);
         prints(50); printf("Name %s : \n",(*(station+i))->name);
         prints(50);printf(" Nombre des Bornes De Recharge  : %d: \n",(*(station+i))->nb_bornes);
         endl;prints(50);printf("Tableau Borne De Recharge \n");
                prints(50);
                printf("------------------------------------\n");
                prints(50);
                printf("| ID | Type     | Puissance | Status |\n");
                prints(50);
                printf("------------------------------------\n");

                for (int compt_borne = 0; compt_borne < (*(station + i))->nb_bornes; compt_borne++) {
                        (*( (*(station + i))->BorneDeRecharge + compt_borne)).id = rand();
                        int type = (*( (*(station + i))->BorneDeRecharge + compt_borne)).type;
                        int puissance = (*( (*(station + i))->BorneDeRecharge + compt_borne)).puissance;
                        int status = (*( (*(station + i))->BorneDeRecharge + compt_borne)).status;
                        endl;
                        prints(50); printf("| %d | %s |%d       | %s    |\n",
                        (*( (*(station + i))->BorneDeRecharge + compt_borne)).id,
                        type == 0 ? "Rapide" : "Normal",
                        puissance,
                        status == 0 ? "Disponible" : status == 1 ? "Occupe" : "Hors_Service"
                        );
                        prints(50);
                        printf("------------------------------------\n");
                }

         prints(50);printf(" Nombre des Utilisateurs  : %d \n",(*(station+i))->nb_users);

         for(int compt_user=0;compt_user<(*(station+i))->nb_users;compt_user++){
                endl;prints(50);printf("Details USER  ID :  %d\n",    (*( (*(station + i))->users + compt_user)).id);
                prints(50);printf("-----------------------------\n");
                prints(50);
                printf(" Nom : %s \n",(*( (*(station + i))->users + compt_user)).nom);
                prints(50);
                printf(" Le Prenom : %s \n",(*( (*(station + i))->users + compt_user)).prenom);
                prints(50);
                printf(" Le Numero Telephone: %d \n",(*( (*(station + i))->users + compt_user)).num_tlf);
                prints(50);
                printf("Le Nombre Du Reservation : %d \n",(*( (*(station + i))->users + compt_user)).nb_reserves);
                prints(50);endl;
                for (int compt_reserve = 0; compt_reserve < (*( (*(station + i))->users + compt_user)).nb_reserves; compt_reserve++) {
                        endl;prints(50);
                        printf("ID Du Borne de Recharge  %d \n",((*((*(station+i))->users+compt_user)).reserves+compt_reserve)->id_borne);
                        prints(50);
                         int id_paiment = ((*((*(station+i))->users+compt_user)).reserves+compt_reserve)->id_paiment;
                        PAIMENT* paiment ;
                        for (int i = 0; i <=nbr_paiment; i++) {
                                if ((paiments + i)->id == id_paiment) {
                                        paiment= paiments + i;
                                }
                        }
                         if (paiment) {
                                endl;prints(50); printf("Details du Paiment:\n");
                                prints(50); printf("-----------------------------\n");
                                prints(50); printf("ID : %d\n", paiment->id);
                                prints(50); printf("Montant : %.2lf\n", paiment->montant);
                                prints(50); printf("Type : %s\n", paiment->Type == 0 ? "Sur Place" : "En Ligne");
                                if (paiment->Type == 1) {
                                        prints(50); printf("Token : %s\n", paiment->Token);
                                }
                         } else {
                                        prints(50); printf("Aucun paiment trouve pour l'ID : %d \n", id_paiment);
                         }
                          prints(50); printf("-----------------------------\n");

                        prints(50);printf("Date de debut de la reservation : ");

                        DATE   date_debut= ((*((*(station+i))->users+compt_user)).reserves+compt_reserve)->date_debut;
                        printf("%d/%d/%d %d:%d\n", date_debut.jour, date_debut.mois, date_debut.annee, date_debut.heure, date_debut.minute);

                        prints(50);printf("Date de fin de la reservation : ");
                        DATE   date_fin= ((*((*(station+i))->users+compt_user)).reserves+compt_reserve)->date_fin;

                        printf("%d/%d/%d %d:%d\n", date_fin.jour, date_fin.mois, date_fin.annee, date_fin.heure, date_fin.minute);
                }

                endl;
                prints(50);printf("-----------------------------\n");

         }
     }

    for(int i=0;i<nbr_station;i++){
        free(*(station+i));
     }
     free(paiments);
     station=NULL;
     paiments=NULL;
     free(station);
     return 0;
}
