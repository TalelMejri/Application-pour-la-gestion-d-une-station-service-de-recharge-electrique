typedef struct Date{;
  int jour;
  int mois;
  int annee;
  int heure;
  int minute;
}DATE;

typedef struct Reservation{
  int id;
  int id_user;
  int id_borne;
  int id_paiment;
  DATE date_debut;
  DATE date_fin;
}RESERVATION;

typedef struct user{
   int id;
   char nom[30];
   char prenom[30];
   int num_tlf;
   int nb_reserves;
   RESERVATION* reserves;
}USER;

typedef enum Types {Rapide,Normal} TYPE;

typedef enum Status {Disponible,Occupe,Hors_Service } STATUS;

typedef struct BorneDeRecharge{
  int id;
  TYPE type;
  int puissance;
  STATUS status;
  int nb_reserves;
  RESERVATION* reserves;
}BORNE_DE_RECHARGE;

typedef struct station{
   int id;
   char name[30];
   int nb_users;
   USER* users;
   int nb_bornes;
   BORNE_DE_RECHARGE* BorneDeRecharge;
   char location[30];
}STATION;

typedef enum Methode {Sur_Place,En_Ligne} METHODE;

typedef struct Paiment{
  int id;
  double montant;
  METHODE Type;
  char Token[30];
}PAIMENT;




