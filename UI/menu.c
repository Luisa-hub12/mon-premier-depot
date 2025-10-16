#include <stdio.h>
#include "menu.h"
#include "../Consignes/utils.h"
#include "creation.h"
#include "changement.h"
#include "Shapes/shapes.h"
#include "../Export/export.h"




/** Tableau global contenant les formes créées */
FormeStockee formes[MAX_FORMES];
int nb_formes = 0;

int main() {
    int choix;
    do {
        printf(CYAN"\n====== Menu Principal ======\n"RESET);
        printf(GREEN"1"RESET" - Créer une forme\n");
        printf(YELLOW"2"RESET" - Modifier une forme\n");
        printf(RED"3"RESET" - Supprimer une forme\n");
        printf(BLUE"4"RESET" - Liste des formes créées\n");
        printf(YELLOW"5"RESET" - Exporter les formes en SVG (export.svg)\n");
        printf(MAGENTA"0 - Quitter\n"RESET);
        printf(BLUE"\n>>> Choisissez une option : "RESET);
        choix = lire_entier();
        switch (choix) {
            case 1: menu_creation(); break;
            case 2: modifier_forme(); break;
            case 3: supprimer_forme(); break;
            case 4: afficher_formes(); break;
            case 5: export_svg(); printf(GREEN "✅ Export SVG réussi ! Ouvre le fichier 'export.svg' dans ton navigateur.\n" RESET); break;
            case 0: printf(YELLOW"\n-------------------------------------\n Vous venez de quitter le programme.\n-------------------------------------\n"RESET); break;
            default: printf(RED"\n----------------\n Choix invalide.\n----------------\n"RESET); break;

        }
    } while (choix != 0);

    /** @brief Libération mémoire avant sortie**/
    for (int i = 0; i < nb_formes; i++) {
        switch (formes[i].type) {
            case 'c': free_circle(formes[i].forme); break;
            case 'a': free_square(formes[i].forme); break;
            case 'r': free_rectangle(formes[i].forme); break;
            case 'l': free_line(formes[i].forme); break;
            case 'e': free_ellipse(formes[i].forme); break;
            case 'g': free_polygon(formes[i].forme); break;
            case 'p': free_polyline(formes[i].forme); break;
            case 'h': free_path(formes[i].forme); break;
        }
    }
    nb_formes = 0;
}