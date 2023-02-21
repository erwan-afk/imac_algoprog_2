#include <iostream>
#include <cmath>
using namespace std;

typedef struct Noeud{
    int donnee;
    Noeud* suivant;
}Noeud;

typedef struct Liste{
    Noeud* premier;
}Liste;

void initialise(Liste* liste)
{
    liste->premier = nullptr;
}

bool est_vide(Liste* liste)
{
    return (liste->premier == nullptr);
}

void ajoute(Liste* liste, int valeur)
{
    Noeud* nouvel_element = new Noeud;
    nouvel_element->donnee = valeur;
    nouvel_element->suivant = liste->premier;
    liste->premier = nouvel_element;
}   

int recupere(Liste* liste, int index)
{
    Noeud* element = liste->premier;
    for (int i = 0; i < index; i++) {
        element = element->suivant;
    }
    return element->donnee;
}

int cherche(Liste* liste, int valeur)
{
    int index = 0;
    for (Noeud* element = liste->premier; element != nullptr; element = element->suivant) {
        if (element->donnee == valeur) {
            return index;
        }
        index++;
    }
    return -1;
}

void stocke(Liste* liste, int index, int valeur)
{
    Noeud* element = liste->premier;
    for (int i = 0; i < index; i++) {
        element = element->suivant;
    }
    element->donnee = valeur;
}

void affiche(Liste* liste)
{
    for (Noeud* element = liste->premier; element != nullptr; element = element->suivant) {
        std::cout << element->donnee << " ";
    }
    std::cout << std::endl;
}

struct DynaTableau {
    int* donnees;
    int capacite;
    int taille;
};



void initialise(DynaTableau* tableau, int capacite)
{
    tableau->donnees = new int[capacite];
    tableau->capacite = capacite;
    tableau->taille = 0;
}

bool est_vide(DynaTableau* tableau)
{
    return (tableau->taille == 0);
}

void ajoute(DynaTableau* tableau, int valeur)
{
    if (tableau->taille < tableau->capacite) {
        tableau->donnees[tableau->taille] = valeur;
        tableau->taille++;
    }
    if (tableau->capacite < tableau->taille + 1) {
        tableau->capacite += 1;
        int *newTab = new int[tableau->capacite];
        for (int i = 0; i < tableau->taille; i++) {
            newTab[i] = tableau->donnees[i];
        }
        tableau->donnees = newTab;
    }
}

int recupere(DynaTableau* tableau, int index)
{
    return tableau->donnees[index];
}

int cherche(DynaTableau* tableau, int valeur)
{
    for (int i = 0; i < tableau->taille; i++) {
        if (tableau->donnees[i] == valeur) {
            return i;
        }
    }
    return -1;
}

void stocke(DynaTableau* tableau, int index, int valeur)
{
    tableau->donnees[index] = valeur;
}

void affiche(DynaTableau* tableau)
{
    for (int i = 0; i < tableau->taille; i++) {
        std::cout << tableau->donnees[i] << " ";
    }
    std::cout << std::endl;
}

void pousse_pile(Liste* pile, int valeur)
{
    ajoute(pile, valeur);
}

//void pousse_file(DynaTableau* liste, int valeur)
void pousse_file(Liste* liste, int valeur)
{
    Noeud* nouvel_element = new Noeud;
    nouvel_element->donnee = valeur;
    nouvel_element->suivant = nullptr;

    if (liste->premier == nullptr) {
        // Si la liste est vide, le nouvel élément devient le premier élément de la liste
        liste->premier = nouvel_element;
    } else {
        // Sinon, on ajoute le nouvel élément à la fin de la liste
        Noeud* element = liste->premier;
        while (element->suivant != nullptr) {
            element = element->suivant;
        }
        element->suivant = nouvel_element;
    }
    std::cout << "Elément ajouté à la file : " << valeur << std::endl;
}

// Fonction pour retirer la première valeur d'une file
int retire_file(Liste* liste)
{
    if (liste->premier == nullptr) {
        // Si la liste est vide, on retourne une valeur spéciale (par exemple -1)
        return -1;
    }
    int valeur = liste->premier->donnee;
    Noeud* suivant = liste->premier->suivant;
    delete liste->premier;
    liste->premier = suivant;
    return valeur;
}

// Fonction pour retirer la valeur au sommet d'une pile
int retire_pile(Liste* liste)
{
    if (liste->premier == nullptr) {
        // Si la liste est vide, on retourne une valeur spéciale (par exemple -1)
        return -1;
    }
    int valeur = liste->premier->donnee;
    Noeud* suivant = liste->premier->suivant;
    delete liste->premier;
    liste->premier = suivant;
    return valeur;
}



int main()
{
    
     
    Liste liste;
    initialise(&liste);
    
    
    DynaTableau tableau;
    initialise(&tableau, 5);

    
    

    if (!est_vide(&liste))
    {
        std::cout << "Oups y a une anguille dans ma liste" << std::endl;
    }

    if (!est_vide(&tableau))
    {
        std::cout << "Oups y a une anguille dans mon tableau" << std::endl;
    }

    for (int i=1; i<=7; i++) {
        ajoute(&liste, i*7);
        ajoute(&tableau, i*5);

        std::cout <<"ajout :" << i*7 << std::endl;
    }

    if (est_vide(&liste))
    {
        std::cout << "Oups y a une anguille dans ma liste" << std::endl;
    }

    if (est_vide(&tableau))
    {
        std::cout << "Oups y a une anguille dans mon tableau" << std::endl;
    }

    
    std::cout << "Elements initiaux:" << std::endl;
    affiche(&liste);
    affiche(&tableau);
    std::cout << std::endl;

    std::cout << "5e valeur de la liste " << recupere(&liste, 4) << std::endl;
    std::cout << "5e valeur du tableau " << recupere(&tableau, 4) << std::endl;

    std::cout << "21 se trouve dans la liste a " << cherche(&liste, 21) << std::endl;
    std::cout << "15 se trouve dans la liste a " << cherche(&tableau, 15) << std::endl;

    stocke(&liste, 4, 7);
    stocke(&tableau, 4, 7);

    std::cout << "Elements apres stockage de 7:" << std::endl;
    affiche(&liste);
    affiche(&tableau);
    std::cout << std::endl;

 
    Liste pile; // DynaTableau pile;
    Liste file; // DynaTableau file;

    initialise(&pile);
    initialise(&file);

    

    for (int i=1; i<=7; i++) {
        pousse_file(&file, i);
        pousse_pile(&pile, i);
    }

    
    affiche(&pile);
    affiche(&file);

    int compteur = 10;
    while(!est_vide(&file) && compteur > 0)
    {
        std::cout << retire_file(&file) << std::endl;
        compteur--;
    }

    if (compteur == 0)
    {
        std::cout << "Ah y a un soucis là1..." << std::endl;
    }

    compteur = 10;
    while(!est_vide(&pile) && compteur > 0)
    {
        std::cout << retire_pile(&pile) << std::endl;
        compteur--;
    }

    if (compteur == 0)
    {
        std::cout << "Ah y a un soucis là..." << std::endl;
    }
  
    
    return 0;
}
