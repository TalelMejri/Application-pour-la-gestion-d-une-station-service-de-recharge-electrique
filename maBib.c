#include "maBib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int EstDisponible(BORNE_DE_RECHARGE* borne) {
    if (borne->status == 0) {
        return 1;
    }
    return 0;
}

void afficherBornesDisponibles(STATION** stations, int nbr_stations) {
    for (int i = 0; i < nbr_stations; i++) {
        printf("Station %s - Bornes disponibles :\n", stations[i]->name);

        for (int j = 0; j < (*(stations+i))->nb_bornes; j++) {
            if (EstDisponible(((*(stations + i))->BorneDeRecharge + j))) {
                printf("Borne ID: %d | Type: %s | Puissance: %d kW\n",
                       (*( (*(stations + i))->BorneDeRecharge + j)).id,
                       (*( (*(stations + i))->BorneDeRecharge + j)).type== Rapide ? "Rapide" : "Normal",
                       (*( (*(stations + i))->BorneDeRecharge + j)).puissance);
            }
        }
    }
}

void entrer_date(DATE *date) {
    printf("Jour: ");
    scanf("%d", &date->jour);
    printf("Mois: ");
    scanf("%d", &date->mois);
    printf("Annee: ");
    scanf("%d", &date->annee);
    printf("Heure: ");
    scanf("%d", &date->heure);
    printf("Minute: ");
    scanf("%d", &date->minute);
}

void trierStationsParBornes(STATION** station, int nbr_station) {
    for (int i = 0; i < nbr_station - 1; i++) {
        for (int j = 0; j < nbr_station - i - 1; j++) {
            if  ( (*(station+j))->nb_bornes <   (*(station+j+1))->nb_bornes) {
                STATION* temp =(*(station+j));
               (*(station+j)) = (*(station+j+1));
               (*(station+j+1)) = temp;
            }
        }
    }
}

void RemplirBorneDeCharge(int nb, STATION* station) {

    for (int compt_borne = 0; compt_borne < nb; compt_borne++) {
        (station->BorneDeRecharge + compt_borne)->id = rand();

        printf("--------------------------------------------------\n");
        printf("Details BORNE DE RECHARGE Avec Indice %d\n", compt_borne + 1);
        printf("--------------------------------------------------\n");

        printf("Saisir Type (0=Rapide, 1=Normal): ");
        int type;
        scanf("%d", &type);
        (station->BorneDeRecharge + compt_borne)->type = (type == 0) ? Rapide : Normal;

        printf("Saisir Puissance: ");
        scanf("%d", &(station->BorneDeRecharge + compt_borne)->puissance);

        printf("Status (0=Disponible, 1=Occupe, 2=Hors_Service): ");
        int status;
        scanf("%d", &status);
        (station->BorneDeRecharge + compt_borne)->status = (STATUS) status;

        (station->BorneDeRecharge + compt_borne)->nb_reserves = 0;
        (station->BorneDeRecharge + compt_borne)->reserves = NULL;

        printf("--------------------------------------------------\n");
    }
}

void TableauBorneDeRecharge(int nb, STATION* station) {
                printf("Tableau BorneDeRecharge \n");
                printf("------------------------------------\n");
                printf("| ID | Type     | Puissance | Status |\n");
                printf("------------------------------------\n");

               for (int compt_borne = 0; compt_borne < nb; compt_borne++) {
                        int type = (station->BorneDeRecharge + compt_borne)->type;
                        int puissance =  (station->BorneDeRecharge + compt_borne)->puissance;
                        int status = (station->BorneDeRecharge + compt_borne)->status;
                         printf("| %d | %s |%d       | %s    |\n",
                        (station->BorneDeRecharge + compt_borne)->id,
                        type == 0 ? "Rapide" : "Normal",
                        puissance,
                        status == 0 ? "Disponible" : status == 1 ? "Occupe" : "Hors_Service"
                        );
                        printf("------------------------------------\n");
                }
}


void init_paiment(PAIMENT* paiment) {
    paiment->id = rand();
    printf("Details Paiment\n");
    printf("-----------------------------\n");
    printf("Saisir montant:\n");
    scanf("%lf", &paiment->montant);

    printf("TYPE (0=Sur Place, 1=En Ligne):\n");
    int type_paiment;
    scanf("%d", &type_paiment);
    paiment->Type = (METHODE) type_paiment;

    if (type_paiment == 0) {
        strcpy(paiment->Token, "");
    } else {
        sprintf(paiment->Token, "Pass%d", paiment->id);
    }
}

void init_user(USER* user) {
    user->id = rand();
    printf("Details USER\n");
    printf("-----------------------------\n");

    printf("Donner Le Nom:\n");
    scanf("%s", user->nom);

    printf("Donner Le Prenom:\n");
    scanf("%s", user->prenom);

    printf("Donner Le Numero Telephone:\n");
    scanf("%d", &user->num_tlf);

    printf("Donner Le Nombre Du Reservation:\n");
    scanf("%d", &user->nb_reserves);
}


void afficher_date(DATE date) {
    printf("%d/%d/%d %d:%d\n", date.jour, date.mois, date.annee, date.heure, date.minute);
}

void afficher_details_user(USER user) {
    printf("Details USER  ID :  %d\n", user.id);
    printf("-----------------------------\n");
    printf("Nom : %s \n", user.nom);
    printf("Le Prenom : %s \n", user.prenom);
    printf("Le Numero Telephone: %d \n", user.num_tlf);
    printf("Le Nombre Du Reservation : %d \n", user.nb_reserves);
}

void afficher_details_paiment(PAIMENT* paiments, int nbr_paiment, int id_paiment) {
    PAIMENT* paiment = NULL;

    for (int i = 0; i < nbr_paiment; i++) {
        if ((paiments + i)->id == id_paiment) {
            paiment = paiments + i;
            break;
        }
    }

    if (paiment) {
        printf("Details du Paiment:\n");
        printf("-----------------------------\n");
        printf("ID : %d\n", paiment->id);
        printf("Montant : %.2lf\n", paiment->montant);
        printf("Type : %s\n", paiment->Type == 0 ? "Sur Place" : "En Ligne");
        if (paiment->Type == 1) {
            printf("Token : %s\n", paiment->Token);
        }
    } else {
        printf("Aucun paiement trouve pour l'ID : %d \n", id_paiment);
    }
}

int compare_dates(DATE d1, DATE d2) {
    if (d1.annee < d2.annee) {
        return -1;
    } else if (d1.annee > d2.annee) {
        return 1;
    }

    if (d1.mois < d2.mois) {
        return -1;
    } else if (d1.mois > d2.mois) {
        return 1;
    }

    if (d1.jour < d2.jour) {
        return -1;
    } else if (d1.jour > d2.jour) {
        return 1;
    }

    if (d1.heure < d2.heure) {
        return -1;
    } else if (d1.heure > d2.heure) {
        return 1;
    }
    if (d1.minute < d2.minute) {
        return -1;
    } else if (d1.minute > d2.minute) {
        return 1;
    }

    return 0;
}

USER* utilisateur_max_reservations(STATION** stations, int nbr_station, DATE date_debut, DATE date_fin) {
    int max_reservations = 0;
    USER* max_user = NULL;
    for (int i = 0; i < nbr_station; i++) {
        STATION* station = *(stations + i);

        for (int j = 0; j < station->nb_users; j++) {
            USER* user = station->users + j;
            int reservations_count = 0;

            for (int k = 0; k < user->nb_reserves; k++) {
                RESERVATION* reservation = user->reserves + k;

                if (compare_dates(reservation->date_debut, date_debut) < 0 && compare_dates(reservation->date_fin, date_fin) > 0) {
                    reservations_count++;
                }
            }

            if (reservations_count >= max_reservations) {
                max_reservations = reservations_count;
                max_user = user;
            }
        }
    }

    return max_user;
}

double RecherchePaiementAvecId(int id, PAIMENT* paiment, int nbr) {
    double montant = 0.0;
    for (int i = 0; i < nbr; i++) {
        if ((paiment + i)->id == id) {
            montant = (paiment + i)->montant;
            break;
        }
    }
    return montant;
}
RESERVATION* reservation_durable(STATION** stations, int nbr_station, PAIMENT* paiments, int nbr_paiment) {
    double max_montant = 0.0;
    RESERVATION* max_reserve = NULL;
    for (int i = 0; i < nbr_station; i++) {
        STATION* station = stations[i];
        if (station == NULL) continue;

        for (int j = 0; j < station->nb_users; j++) {
            USER* user = station->users + j;
            if (user == NULL) continue;

            for (int k = 0; k < user->nb_reserves; k++) {
                RESERVATION* reservation = user->reserves + k;
                if (reservation == NULL) continue;

                double montant = RecherchePaiementAvecId(reservation->id_paiment, paiments, nbr_paiment);
                if (montant > max_montant) {
                    max_montant = montant;
                    max_reserve = reservation;
                }
            }
        }
    }
    return max_reserve;
}
