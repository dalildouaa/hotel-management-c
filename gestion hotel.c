/*
 * HOTEL MANAGEMENT SYSTEM
 *
 * This project was developed as part of the C Programming Language course.
 * It was developed collaboratively as a team project.
 *
 * The system is designed to manage:
 * - Hotel rooms
 * - Clients
 * - Reservations
 * - Invoices
 *
 * C programming concepts used in this project include:
 * - Structures
 * - Pointers
 * - Dynamic memory allocation
 * - Doubly linked lists
 * - Searching and sorting
 * - Input validation
 *
 * The program allows users to add, display, modify, delete,
 * search and sort rooms and clients, as well as manage reservations
 * and calculate invoices.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct chambre
{
    int numero;
    char type[20];
    float prix;
    int reserve;
    struct chambre *suiv;
    struct chambre *prec;
} chambre;
typedef struct client
{
    int id;
    char nom[30];
    int tel;
    struct client *suiv;
    struct client *prec;
} client;
typedef struct reservation
{
    int id;
    int idClient;
    int numeroChambre;
    int dateReservation;
    int debut;
    int fin;
    struct reservation *suiv;
    struct reservation *prec;
} reservation;
int numeroChambreUnique(int num,chambre *teteChambre)
{
    chambre *tmp=teteChambre;
    while(tmp!=NULL)
    {
        if(tmp->numero==num)
        {
            return 0;
        }
        tmp=tmp->suiv;
    }
    return 1;
}
int idClientUnique(int id,client *teteClient)
{
    client *tmp=teteClient;
    while(tmp!=NULL)
    {
        if(tmp->id==id)
        {
            return 0;
        }
        tmp=tmp->suiv;
    }
    return 1;
}
int idReservationUnique(int id,reservation *teteReservation)
{
    reservation *tmp=teteReservation;
    while(tmp!=NULL)
    {
        if(tmp->id==id)
        {
            return 0;
        }
        tmp=tmp->suiv;
    }
    return 1;
}
int dateValide(int date)
{
    int annee = date / 10000;
    int mois = (date / 100) % 100;
    int jour = date % 100;
    if(annee < 2026 || annee > 2100)
    {
        return 0;
    }
    if(mois < 1 || mois > 12)
    {
        return 0;
    }
    if(jour < 1 || jour > 31)
    {
        return 0;
    }
    return 1;
}
chambre *ajouterChambre(chambre *teteChambre)
{
    chambre *nv=malloc(sizeof(chambre));
    do
    {
        printf("numero chambre : ");
        scanf("%d",&nv->numero);
        if(numeroChambreUnique(nv->numero,teteChambre) == 0)
        {
            printf("numero deja existe\n");
        }
    }
    while(numeroChambreUnique(nv->numero,teteChambre) == 0);
    printf("type : ");
    scanf("%s",nv->type);
    printf("prix : ");
    scanf("%f",&nv->prix);
    nv->reserve=0;
    if(teteChambre==NULL)
    {
        teteChambre = nv;
        printf("chambre ajoutee\n");
        return teteChambre;
    }
    nv->suiv = teteChambre;
    nv->prec = NULL;
    teteChambre = nv;
    printf("chambre ajoutee\n");
    return teteChambre;
}
void afficherChambres(chambre *teteChambre)
{
    chambre *tmp=teteChambre;
    if(teteChambre == NULL)
    {
        printf("erreur, liste des chambres est vide");
    }
    else
    {
        while(tmp!=NULL)
        {
            printf("\nnumero : %d\n",tmp->numero);
            printf("type : %s\n",tmp->type);
            printf("prix : %.2f\n",tmp->prix);
            if(tmp->reserve == 1)
            {
                printf("statut : reservee\n");
            }
            else
            {
                printf("statut : libre\n");
            }
            tmp=tmp->suiv;
        }
    }
}
chambre *modifierChambre(chambre *teteChambre)
{
    int num;
    chambre *tmp = teteChambre;
    printf("Numero chambre a modifier : ");
    scanf("%d",&num);
    while(tmp!=NULL)
    {
        if(tmp->numero==num)
        {
            printf("Nouveau type : ");
            scanf("%s",tmp->type);

            printf("Nouveau prix : ");
            scanf("%f",&tmp->prix);

            printf("Chambre modifiee\n");
            return teteChambre;
        }
        tmp=tmp->suiv;
    }
    printf("Chambre non trouvee\n");
}
chambre *supprimerChambre(chambre *teteChambre)
{
    int num;
    printf("numero chambre : ");
    scanf("%d",&num);
    chambre *tmp=teteChambre;
    while(tmp!=NULL)
    {
        if(tmp->numero==num)
        {
            if(tmp->reserve)
            {
                printf("impossible de supprimer chambre reserver\n");
                return teteChambre;
            }
            if(tmp->prec!=NULL)
            {
                tmp->prec->suiv=tmp->suiv;
            }
            else
            {
                teteChambre=tmp->suiv;
            }

            if(tmp->suiv!=NULL)
            {
                tmp->suiv->prec=tmp->prec;
            }

            free(tmp);
            printf("chambre supprimee\n");
            return teteChambre;
        }
        tmp=tmp->suiv;
    }
    printf("chambre non trouver\n");
    return teteChambre;
}
client *ajouterClient(client *teteClient)
{
    client *nv = malloc(sizeof(client));
    do
    {
        printf("id client : ");
        scanf("%d",&nv->id);
        if(idClientUnique(nv->id, teteClient) == 0)
        {
            printf("id deja utilise\n");
        }
    }
    while(idClientUnique(nv->id, teteClient) == 0);
    printf("nom : ");
    fflush(stdin);
    fgets(nv->nom,30,stdin);
    nv->nom[strcspn(nv->nom,"\n")] = 0;
    printf("telephone : ");
    scanf("%d",&nv->tel);
    if(teteClient==NULL)
    {
        teteClient = nv;
        return teteClient;
    }
    nv->suiv = teteClient;
    nv->prec = NULL;
    teteClient = nv;
    printf("client ajoute\n");
    return teteClient;
}
void afficherClients(client *teteClient)
{
    client *tmp=teteClient;
    if(teteClient == NULL)
    {
        printf("erreur, liste des clients est vide");
    }
    else
    {
        while(tmp!=NULL)
        {

            printf("\nid : %d\n",tmp->id);
            printf("nom : %s\n",tmp->nom);
            printf("telephone : %d\n",tmp->tel);
            tmp=tmp->suiv;
        }
    }
}
client *modifierClient(client *teteClient)
{
    int id;
    client *tmp = teteClient;

    printf("ID client a modifier : ");
    scanf("%d",&id);

    while(tmp!=NULL)
    {
        if(tmp->id==id)
        {
            printf("Nouveau nom : ");
            scanf(" %[^\n]", tmp->nom);

            printf("Nouveau telephone : ");
            scanf("%d",&tmp->tel);

            printf("Client modifie\n");
            return teteClient;
        }

        tmp=tmp->suiv;
    }

    printf("Client non trouve\n");
    return teteClient;
}
client *supprimerClient(client *teteClient, reservation *teteReservation)
{
    int id;
    client *tmp = teteClient;

    printf("ID client a supprimer : ");
    scanf("%d",&id);

    reservation *r = teteReservation;
    while(r != NULL)
    {
        if(r->idClient == id)
        {
            printf("Impossible supprimer client avec reservation\n");
            return teteClient;
        }
        r = r->suiv;
    }

    while(tmp != NULL)
    {
        if(tmp->id == id)
        {
            if(tmp->prec != NULL)
            {
                tmp->prec->suiv = tmp->suiv;
            }
            else
            {
                teteClient = tmp->suiv;
            }
            if(tmp->suiv != NULL)
            {
                tmp->suiv->prec = tmp->prec;
            }
            free(tmp);

            printf("Client supprime\n");
            return teteClient;
        }
        tmp = tmp->suiv;
    }
    printf("Client non trouve\n");
    return teteClient;
}
chambre *chercherChambreLibre(char type[],chambre *teteChambre)
{
    chambre *tmp=teteChambre;

    while(tmp!=NULL)
    {
        if(strcmp(tmp->type,type)==0 && tmp->reserve==0)
        {
            return tmp;
        }
        tmp=tmp->suiv;
    }
    return NULL;
}
reservation *ajouterReservation(reservation *teteReservation, chambre *teteChambre)
{
    reservation *nv=malloc(sizeof(reservation));

    do
    {
        printf("id reservation : ");
        scanf("%d",&nv->id);
        if(idReservationUnique(nv->id, teteReservation) == 0)
        {
            printf("id deja utilise\n");
        }
    }
    while(idReservationUnique(nv->id, teteReservation) == 0);

    printf("id client : ");
    scanf("%d",&nv->idClient);

    char type[20];

    printf("type chambre demande : ");
    scanf("%s",type);

    chambre *ch=chercherChambreLibre(type,teteChambre);

    if(ch==NULL)
    {
        printf("aucune chambre libre\n");
        free(nv);
        return teteReservation;
    }

    nv->numeroChambre=ch->numero;

    printf("date debut (YYYYMMDD) : ");
    scanf("%d",&nv->debut);

    if(dateValide(nv->debut) == 0)
    {
        printf("date debut invalide\n");
        free(nv);
        return teteReservation;
    }
    printf("date fin (YYYYMMDD) : ");
    scanf("%d",&nv->fin);
    if(dateValide(nv->fin) == 0)
    {
        printf("date fin invalide\n");
        free(nv);
        return teteReservation;
    }
    if(nv->fin <= nv->debut)
    {
        printf("date fin doit etre apres date debut\n");
        free(nv);
        return teteReservation;
    }
    printf("date reservation (YYYYMMDD) : ");
    scanf("%d",&nv->dateReservation);
    if(dateValide(nv->dateReservation) == 0)
    {
        printf("date reservation invalide\n");
        free(nv);
        return teteReservation;
    }
    ch->reserve=1;
    nv->suiv=teteReservation;
    nv->prec=NULL;
    if(teteReservation!=NULL)
    {
        teteReservation->prec=nv;
    }
    teteReservation=nv;

    printf("reservation creer chambre %d\n",nv->numeroChambre);
    return teteReservation;
}
void afficherReservations(reservation *teteReservation)
{
    reservation *tmp=teteReservation;
    if(teteReservation == NULL)
    {
        printf("erreur, liste des reservations est vide");
    }
    else
    {

        while(tmp!=NULL)
        {
            printf("\nreservation : %d\n",tmp->id);
            printf("client : %d\n",tmp->idClient);
            printf("chambre : %d\n",tmp->numeroChambre);
            printf("debut : %d\n",tmp->debut);
            printf("fin : %d\n",tmp->fin);

            tmp=tmp->suiv;
        }
    }
}
reservation *modifierReservation(reservation *teteReservation)
{
    int id;
    reservation *tmp = teteReservation;

    printf("ID reservation a modifier : ");
    scanf("%d",&id);

    while(tmp!=NULL)
    {
        if(tmp->id==id)
        {
            printf("Nouvelle date debut (YYYYMMDD) : ");
            scanf("%d",&tmp->debut);

            if(dateValide(tmp->debut)==0)
            {
                printf("Date invalide\n");
                return teteReservation;
            }

            printf("Nouvelle date fin (YYYYMMDD) : ");
            scanf("%d",&tmp->fin);

            if(dateValide(tmp->fin)==0 || tmp->fin <= tmp->debut)
            {
                printf("Date fin invalide\n");
                return teteReservation;
            }

            printf("Reservation modifiee\n");
            return teteReservation;
        }
        tmp=tmp->suiv;
    }

    printf("Reservation non trouvee\n");
    return teteReservation;
}
reservation *supprimerReservation(reservation *teteReservation, chambre *teteChambre)
{
    int id;
    reservation *tmp = teteReservation;

    printf("ID reservation a supprimer : ");
    scanf("%d",&id);

    while(tmp != NULL)
    {
        if(tmp->id == id)
        {
            chambre *ch = teteChambre;
            while(ch != NULL)
            {
                if(ch->numero == tmp->numeroChambre)
                {
                    ch->reserve = 0;
                    break;
                }
                ch = ch->suiv;
            }

            if(tmp->prec != NULL)
            {
                tmp->prec->suiv = tmp->suiv;
            }
            else
            {
                teteReservation = tmp->suiv;
            }
            if(tmp->suiv != NULL)
                tmp->suiv->prec = tmp->prec;

            free(tmp);

            printf("Reservation supprimee\n");
            return teteReservation;
        }

        tmp = tmp->suiv;
    }

    printf("Reservation non trouvee\n");
    return teteReservation;
}
void rechercherChambre(chambre *teteChambre)
{
    int num;
    chambre *tmp = teteChambre;

    printf("Numero chambre a rechercher : ");
    scanf("%d",&num);

    while(tmp != NULL)
    {
        if(tmp->numero == num)
        {
            printf("\nChambre trouvee\n");
            printf("Numero : %d\n",tmp->numero);
            printf("Type : %s\n",tmp->type);
            printf("Prix : %.2f\n",tmp->prix);
            if(tmp->reserve == 1)
            {
                printf("Statut : reservee\n");
            }
            else
            {
                printf("Statut : libre\n");
            }
            return;
        }
        tmp = tmp->suiv;
    }
    printf("Chambre non trouvee\n");
}
chambre *trierChambresType(chambre *teteChambre)
{
    if(teteChambre == NULL)
    {
        printf("liste vide");
        return teteChambre;
    }
    int permut;
    chambre *ptr;
    chambre *tmp;
    do
    {
        permut = 0;
        ptr = teteChambre;

        while(ptr->suiv != NULL)
        {
            if(strcmp(ptr->type, ptr->suiv->type) > 0)
            {
                tmp = ptr;
                ptr = ptr->suiv;
                ptr->suiv = tmp;
                permut = 1;
            }

            ptr = ptr->suiv;
        }
    }
    while(permut == 1);

    printf("Liste des chambres triee par type\n");
    return teteChambre;
}
void rechercherClient(client *teteClient)
{
    int id;
    client *tmp = teteClient;
    printf("ID client a rechercher : ");
    scanf("%d",&id);
    while(tmp != NULL)
    {
        if(tmp->id == id)
        {
            printf("\nClient trouve\n");
            printf("ID : %d\n",tmp->id);
            printf("Nom : %s\n",tmp->nom);
            printf("Telephone : %d\n",tmp->tel);
            return;
        }
        tmp = tmp->suiv;
    }

    printf("Client non trouve\n");
}
client *trierClientsNom(client *teteClient)
{
    if(teteClient == NULL)
    {
        printf("liste vide");
        return teteClient;
    }
    int permut;
    client *ptr;
    client *tmp;
    do
    {
        permut = 0;
        ptr = teteClient;
        while(ptr->suiv != NULL)
        {
            if(strcmp(ptr->nom, ptr->suiv->nom) > 0)
            {
                tmp = ptr;
                ptr = ptr->suiv;
                ptr->suiv = tmp;
                permut = 1;
            }
            ptr = ptr->suiv;
        }
    }
    while(permut);
    printf("Liste des clients triee par nom\n");
    return teteClient;
}
void rechercherReservation(reservation *teteReservation)
{
    int id;
    reservation *tmp = teteReservation;
    printf("ID reservation a rechercher : ");
    scanf("%d",&id);
    while(tmp != NULL)
    {
        if(tmp->id == id)
        {
            printf("\nReservation trouvee\n");
            printf("ID : %d\n",tmp->id);
            printf("Client : %d\n",tmp->idClient);
            printf("Chambre : %d\n",tmp->numeroChambre);
            printf("Debut : %d\n",tmp->debut);
            printf("Fin : %d\n",tmp->fin);
            return;
        }
        tmp = tmp->suiv;
    }
    printf("Reservation non trouvee\n");
}
float calculerFacture(reservation *teteReservation, chambre *teteChambre)
{
    int id;
    printf("Entrer ID reservation : ");
    scanf("%d", &id);

    reservation *res = teteReservation;

    while(res != NULL)
    {
        if(res->id == id)
        {
            chambre *ch = teteChambre;

            while(ch != NULL)
            {
                if(ch->numero == res->numeroChambre)
                {
                    int nbJours = res->fin - res->debut;

                    float facture = nbJours * ch->prix;

                    printf("\n===== FACTURE =====\n");
                    printf("Reservation ID : %d\n", res->id);
                    printf("Chambre : %d\n", ch->numero);
                    printf("Prix par jour : %.2f\n", ch->prix);
                    printf("Nombre de jours : %d\n", nbJours);
                    printf("Total a payer : %.2f\n", facture);

                    return facture;
                }
                ch = ch->suiv;
            }
        }
        res = res->suiv;
    }

    printf("Reservation non trouvee\n");
    return 0;
}
chambre *menuChambre(chambre *teteChambre)
{
    int choix;
    do
    {
        printf("\n---Gestion Chambres---\n");
        printf("ajouter---->taper--->1\n");
        printf("afficher--->taper--->2\n");
        printf("supprimer-->taper--->3\n");
        printf("modifier--->taper--->4\n");
        printf("rechercher->taper--->5\n");
        printf("trier------>taper--->6\n");
        printf("retour----->taper--->0\n");
        printf("choix : ");
        scanf("%d",&choix);

        switch(choix)
        {
        case 1:
            teteChambre = ajouterChambre(teteChambre);
            break;
        case 2:
            afficherChambres(teteChambre);
            break;
        case 3:
            teteChambre = supprimerChambre(teteChambre);
            break;
        case 4:
            teteChambre = modifierChambre(teteChambre);
            break;
        case 5:
            rechercherChambre(teteChambre);
            break;
        case 6:
            teteChambre = trierChambresType(teteChambre);
            break;
        }
    }
    while(choix != 0);
    return teteChambre;
}
client *menuClient(client *teteClient,reservation *teteReservation)
{
    int choix;
    do
    {
        printf("\n----Gestion Clients---\n");
        printf("ajouter---->taper--->1\n");
        printf("afficher--->taper--->2\n");
        printf("supprimer-->taper--->3\n");
        printf("modifier--->taper--->4\n");
        printf("rechercher->taper--->5\n");
        printf("trier------>taper--->6\n");
        printf("retour----->taper--->0\n");
        printf("choix : ");
        scanf("%d",&choix);

        switch(choix)
        {
        case 1:
            teteClient = ajouterClient(teteClient);
            break;
        case 2:
            afficherClients(teteClient);
            break;
        case 3:
            teteClient = supprimerClient(teteClient,teteReservation);
            break;
        case 4:
            teteClient = modifierClient(teteClient);
            break;
        case 5:
            rechercherClient(teteClient);
            break;
        case 6:
            teteClient = trierClientsNom(teteClient);
            break;
        }
    }
    while(choix != 0);
    return teteClient;
}
reservation *menuReservation(reservation *teteReservation, chambre *teteChambre)
{
    int choix;
    do
    {
        printf("\n--- Gestion Reservations ---\n");
        printf("ajouter---------->taper--->1\n");
        printf("afficher--------->taper--->2\n");
        printf("supprimer-------->taper--->3\n");
        printf("modifier--------->taper--->4\n");
        printf("rechercher------->taper--->5\n");
        printf("calculer facture->taper--->6\n");
        printf("retour----------->taper--->0\n");
        printf("choix : ");
        scanf("%d",&choix);

        switch(choix)
        {
        case 1:
            teteReservation = ajouterReservation(teteReservation, teteChambre);
            break;
        case 2:
            afficherReservations(teteReservation);
            break;
        case 3:
            teteReservation = supprimerReservation(teteReservation, teteChambre);
            break;
        case 4:
            teteReservation = modifierReservation(teteReservation);
            break;
        case 5:
            rechercherReservation(teteReservation);
            break;
        case 6:
            calculerFacture(teteReservation, teteChambre);
            break;
        }
    }
    while(choix != 0);
    return teteReservation;
}
int main()
{
    chambre *teteChambre = NULL;
    client *teteClient = NULL;
    reservation *teteReservation = NULL;

    int choix;

    do
    {
        printf("\n--------------HOTEL--------------\n");
        printf("gestion chambres------>taper--->1\n");
        printf("gestion clients------->taper--->2\n");
        printf("gestion reservations-->taper--->3\n");
        printf("quitter--------------->taper--->0\n");
        printf("choix : ");
        scanf("%d",&choix);

        switch(choix)
        {
        case 1:
            teteChambre = menuChambre(teteChambre);
            break;
        case 2:
            teteClient = menuClient(teteClient,teteReservation);
            break;
        case 3:
            teteReservation = menuReservation(teteReservation,teteChambre);
            break;
        }
    }
    while(choix != 0);

    return 0;
}
