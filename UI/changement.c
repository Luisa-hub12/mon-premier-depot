#include <stdio.h>
#include <stdlib.h>
#include "changement.h"
#include <string.h>
#include "../Consignes/utils.h"
#include "../Shapes/shapes.h"


void modifier_forme() {
    if (nb_formes == 0) {
        printf(YELLOW"\n--------------------------\n Aucune forme à modifier.\n--------------------------\n"RESET);
        return;
    }

    afficher_formes();
    printf(MAGENTA"\nTouche Entrer -> Annuler\n"RESET);
    printf(BLUE"\n>>> Index de la forme à modifier (0-%d) : "RESET, nb_formes-1);

    char buffer[16];
    if (!fgets(buffer, sizeof(buffer), stdin)) return; /** @note annule si erreur**/
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) == 0) return; /** @note Entrée seule = annuler**/

    int idx = atoi(buffer);
    if (idx < 0 || idx >= nb_formes) {
        printf(RED"\n-----------------\n Index invalide.\n-----------------\n"RESET);
        return;
    }

    FormeStockee* f = &formes[idx];

    switch(f->type) {
        case 'c': { 
            circle* cir = f->forme;
            printf(MAGENTA"\n--- Modifier Cercle ---\n"RESET);
            printf(BLUE"1"RESET" - Déplacer le centre\n");
            printf(BLUE"2"RESET" - Rayon\n");
            printf(BLUE"3"RESET" - Couleur du trait\n");
            printf(BLUE"4"RESET" - Couleur du fond\n");
            printf(BLUE"5"RESET" - Inverser selon un axe\n");
            printf(MAGENTA"\nTouche Entrer pour Annuler à tout moment\n"RESET);
            printf(BLUE"\n>>> Choisissez une option : "RESET);
            int choix = lire_entier();
            switch(choix) {
                case 1: {
                    int dx, dy;
                    printf("Déplacer X de : ");
                    if (!lire_entier_ou_retour(&dx)) break;
                    printf("Déplacer Y de : ");
                    if (!lire_entier_ou_retour(&dy)) break;
                    cir->x += dx; cir->y += dy;
                } break;
                case 2: {
                    int nouveau;
                    printf("Nouveau rayon : ");
                    if (!lire_entier_ou_retour(&nouveau)) break;
                    cir->radius = nouveau;
                } break;
                case 3: {
                    printf("Nouvelle couleur du trait : "); scanf("%15s", cir->line_color); vider_buffer();
                } break;
                case 4: {
                    printf("Nouvelle couleur du fond : "); scanf("%15s", cir->background_color); vider_buffer();
                } break;
                case 5: { // 🔹 FLIP SELON AXE
                        printf(BLUE"\nInverser le cercle :\n"RESET);
                        printf("1 - Selon X (horizontal)\n");
                        printf("2 - Selon Y (vertical)\n");
                        printf(">>> Votre choix : ");
                        int axe = lire_entier();
                        if (axe == 1)
                            flip_circle(cir, true, false, 800, 800);  // inverser horizontalement
                          else if (axe == 2)
                            flip_circle(cir, false, true, 800, 800);  // inverser verticalement
                        else
                            printf(YELLOW"\nAnnulé.\n"RESET);
                } break;
            }
        } break;

        case 'a': { 
            square* squ = f->forme;
            printf(MAGENTA"\n--- Modifier Carré ---\n"RESET);
            printf(BLUE"1"RESET" - Déplacer le coin inférieur gauche\n");
            printf(BLUE"2"RESET" - Longueur des côtés\n");
            printf(BLUE"3"RESET" - Couleur du trait\n");
            printf(BLUE"4"RESET" - Couleur du fond\n");
            printf(BLUE"5"RESET" - Inverser selon un axe\n");
            printf(MAGENTA"\nTouche Entrer pour Annuler à tout moment\n"RESET);
            printf(BLUE"\n>>> Choisissez une option : "RESET);
            int choix = lire_entier();
            switch(choix) {
                case 1: {
                    int dx, dy;
                    printf("Déplacer X : ");
                    if (!lire_entier_ou_retour(&dx)) break;
                    printf("Déplacer Y : ");
                    if (!lire_entier_ou_retour(&dy)) break;
                    squ->x += dx; squ->y += dy;
                } break;
                case 2: {
                    int listed;
                    printf("Nouvelle longueur des côtés  : ");
                    if (!lire_entier_ou_retour(&listed)) break;
                    squ->listed = listed;
                } break;
                case 3: printf("Nouvelle couleur du trait : "); scanf("%15s", squ->line_color); vider_buffer(); break;
                case 4: printf("Nouvelle couleur du fond : "); scanf("%15s", squ->background_color); vider_buffer(); break;
                case 5: { // 🔹 FLIP SELON AXE
                        printf(BLUE"\nInverser le carré :\n"RESET);
                        printf("1 - Selon X (horizontal)\n");
                        printf("2 - Selon Y (vertical)\n");
                        printf(">>> Votre choix : ");
                        int axe = lire_entier();
                        if (axe == 1)
                            flip_square(squ, true, false, 800, 800);  // inverser horizontalement
                          else if (axe == 2)
                            flip_square(squ, false, true, 800, 800);  // inverser verticalement
                        else
                            printf(YELLOW"\nAnnulé.\n"RESET);
                } break;
            }
        } break;

        case 'r': { 
            rectangle* rec = f->forme;
            printf(MAGENTA"\n--- Modifier Rectangle ---\n"RESET);
            printf(BLUE"1"RESET" - Déplacer le coin inférieur gauche\n");
            printf(BLUE"2"RESET" - Largeur\n");
            printf(BLUE"3"RESET" - Hauteur\n");
            printf(BLUE"4"RESET" - Couleur du trait\n");
            printf(BLUE"5"RESET" - Couleur du fond\n");
            printf(BLUE"6"RESET" - Inverser selon un axe\n");
            printf(MAGENTA"\nTouche Entrer pour Annuler à tout moment\n"RESET);
            printf(BLUE"\n>>> Choisissez une option : "RESET);
            int choix = lire_entier();
            switch(choix) {
                case 1: {
                    int dx, dy;
                    printf("Déplacer X  : "); if (!lire_entier_ou_retour(&dx)) break;
                    printf("Déplacer Y  : "); if (!lire_entier_ou_retour(&dy)) break;
                    rec->x += dx; rec->y += dy;
                } break;
                case 2: {
                    int larg; printf("Nouvelle largeur : "); if (!lire_entier_ou_retour(&larg)) break;
                    rec->width = larg;
                } break;
                case 3: {
                    int haut; printf("Nouvelle hauteur : "); if (!lire_entier_ou_retour(&haut)) break;
                    rec->height = haut;
                } break;
                case 4: printf("Nouvelle couleur : "); scanf("%15s", rec->line_color); vider_buffer(); break;
                case 5: printf("Nouvelle couleur du fond : "); scanf("%15s", rec->background_color); vider_buffer(); break;
                case 6: { // 🔹 FLIP SELON AXE
                        printf(BLUE"\nInverser le rectangle :\n"RESET);
                        printf("1 - Selon X (horizontal)\n");
                        printf("2 - Selon Y (vertical)\n");
                        printf(">>> Votre choix : ");
                        int axe = lire_entier();
                        if (axe == 1)
                            flip_rectangle(rec, true, false, 800, 800);  // inverser horizontalement
                          else if (axe == 2)
                            flip_rectangle(rec, false, true, 800, 800);  // inverser verticalement
                        else
                            printf(YELLOW"\nAnnulé.\n"RESET);
                } break;
            }
        } break;

        case 'l': { 
            line* lin = f->forme;
            printf(MAGENTA"\n--- Modifier Ligne ---\n"RESET);
            printf(BLUE"1"RESET" - Déplacer le premier point\n");
            printf(BLUE"2"RESET" - Déplacer le second point\n");
            printf(BLUE"3"RESET" - Couleur du trait\n");
            printf(BLUE"4"RESET" - Épaisseur du trait\n");
            printf(BLUE"5"RESET" - Inverser selon un axe\n");
            printf(MAGENTA"\nTouche Entrer pour Annuler à tout moment\n"RESET);
            printf(BLUE"\n>>> Choisissez une option : "RESET);
            int choix = lire_entier();
            switch(choix) {
                case 1: {
                    int dx1, dy1;
                    printf("Déplacer X1 : "); if (!lire_entier_ou_retour(&dx1)) break;
                    printf("Déplacer Y1 : "); if (!lire_entier_ou_retour(&dy1)) break;
                    lin->x1 += dx1; lin->y1 += dy1;
                } break;
                case 2: {
                    int dx2, dy2;
                    printf("Déplacer X2 : "); if (!lire_entier_ou_retour(&dx2)) break;
                    printf("Déplacer Y2 : "); if (!lire_entier_ou_retour(&dy2)) break;
                    lin->x2 += dx2; lin->y2 += dy2;
                } break;
                case 3: printf("Nouvelle couleur du trait : "); scanf("%15s", lin->line_color); vider_buffer(); break;
                case 4: {
                    int epaisseur;
                    printf("Nouvelle épaisseur du trait : "); if (!lire_entier_ou_retour(&epaisseur)) break;
                    lin->thickness = epaisseur;
                } break;
                case 5: { // 🔹 FLIP SELON AXE
                        printf(BLUE"\nInverser la ligne :\n"RESET);
                        printf("1 - Selon X (horizontal)\n");
                        printf("2 - Selon Y (vertical)\n");
                        printf(">>> Votre choix : ");
                        int axe = lire_entier();
                        if (axe == 1)
                            flip_line(lin, true, false, 800, 800);  // inverser horizontalement
                          else if (axe == 2)
                            flip_line(lin, false, true, 800, 800);  // inverser verticalement
                        else
                            printf(YELLOW"\nAnnulé.\n"RESET);
                } break;
            }
        } break;

        case 'e': {
            ellipse* ell = f->forme;
            printf(MAGENTA"\n--- Modifier Ellipse ---\n"RESET);
            printf(BLUE"1"RESET" - Déplacer le centre\n");
            printf(BLUE"2"RESET" - Rayons\n");
            printf(BLUE"3"RESET" - Couleur du trait\n");
            printf(BLUE"4"RESET" - Couleur du fond\n");
            printf(BLUE"5"RESET" - Inverser selon un axe\n");
            printf(MAGENTA"\nTouche Entrer pour Annuler à tout moment\n"RESET);
            printf(BLUE"\n>>> Choisissez une option : "RESET);
            int choix = lire_entier();
            switch(choix) {
                case 1: {
                    int dx, dy;
                    printf("Déplacer X : "); if (!lire_entier_ou_retour(&dx)) break;
                    printf("Déplacer Y : "); if (!lire_entier_ou_retour(&dy)) break;
                    ell->x += dx; ell->y += dy;
                } break;
                case 2: {
                    int r1, r2;
                    printf("Nouveau rayon 1 : "); if (!lire_entier_ou_retour(&r1)) break;
                    printf("Nouveau rayon 2 : "); if (!lire_entier_ou_retour(&r2)) break;
                    ell->radiusx= r1; ell->radiusy = r2;
                } break;
                case 3: printf("Nouvelle couleur du trait : "); scanf("%15s", ell->line_color); vider_buffer(); break;
                case 4: printf("Nouvelle couleur du fond : "); scanf("%15s", ell->background_color); vider_buffer(); break;
                case 5: { // 🔹 FLIP SELON AXE
                        printf(BLUE"\nInverser l'ellipse :\n"RESET);
                        printf("1 - Selon X (horizontal)\n");
                        printf("2 - Selon Y (vertical)\n");
                        printf(">>> Votre choix : ");
                        int axe = lire_entier();
                        if (axe == 1)
                            flip_ellipse(ell, true, false, 800, 800);  // inverser horizontalement
                          else if (axe == 2)
                            flip_ellipse(ell, false, true, 800, 800);  // inverser verticalement
                        else
                            printf(YELLOW"\nAnnulé.\n"RESET);
                } break;
            }
        } break;

        case 'g': {
            polygon* pgn = f->forme;
            printf(MAGENTA"\n--- Modifier Polygone ---\n"RESET);
            printf(BLUE"1"RESET" - Déplacer le polygone\n");
            printf(BLUE"2"RESET" - Couleur du trait\n");
            printf(BLUE"3"RESET" - Couleur du fond\n");
            printf(BLUE"4"RESET" - Inverser selon un axe\n");
            printf(MAGENTA"\nTouche Entrer pour Annuler à tout moment\n"RESET);
            printf(BLUE"\n>>> Choisissez une option : "RESET);
            int choix = lire_entier();
            switch(choix) {
                case 1: {
                    int dx, dy;
                    printf("Déplacer X : "); if (!lire_entier_ou_retour(&dx)) break;
                    printf("Déplacer Y : "); if (!lire_entier_ou_retour(&dy)) break;
                    for (int i = 0; i < pgn->nb_points; i++) {
                        pgn->points[i].x += dx;
                        pgn->points[i].y += dy;
                    }
                } break;
                case 2: printf("Nouvelle couleur du trait : "); scanf("%15s", pgn->line_color); vider_buffer(); break;
                case 3: printf("Nouvelle couleur du fond : "); scanf("%15s", pgn->background_color); vider_buffer(); break;
                case 4: { // 🔹 FLIP SELON AXE
                        printf(BLUE"\nInverser le polygone :\n"RESET);
                        printf("1 - Selon X (horizontal)\n");
                        printf("2 - Selon Y (vertical)\n");
                        printf(">>> Votre choix : ");
                        int axe = lire_entier();
                        if (axe == 1)
                            flip_polygon(pgn, true, false, 800, 800);  // inverser horizontalement
                          else if (axe == 2)
                            flip_polygon(pgn, false, true, 800, 800);  // inverser verticalement
                        else
                            printf(YELLOW"\nAnnulé.\n"RESET);
                } break;
            }
        } break;

        case 'p': { 
            polyline* pln = f->forme;
            printf(MAGENTA"\n--- Modifier Polyligne ---\n"RESET);
            printf(BLUE"1"RESET" - Déplacer la polyligne\n");
            printf(BLUE"2"RESET" - Couleur du trait\n");
            printf(BLUE"3"RESET" - Inverser selon un axe\n");
            printf(MAGENTA"\nTouche Entrer pour Annuler à tout moment\n"RESET);
            printf(BLUE"\n>>> Choisissez une option : "RESET);
            int choix = lire_entier();
            switch(choix) {
                case 1: {
                    int dx, dy;
                    printf("Déplacer X : "); if (!lire_entier_ou_retour(&dx)) break;
                    printf("Déplacer Y : "); if (!lire_entier_ou_retour(&dy)) break;
                    for (int i = 0; i < pln->nb_points; i++) {
                        pln->points[i].x += dx;
                        pln->points[i].y += dy;
                    }
                } break;
                case 2: printf("Nouvelle couleur du trait : "); scanf("%15s", pln->line_color); vider_buffer(); break;
                case 3: { // 🔹 FLIP SELON AXE
                        printf(BLUE"\nInverser la polyligne :\n"RESET);
                        printf("1 - Selon X (horizontal)\n");
                        printf("2 - Selon Y (vertical)\n");
                        printf(">>> Votre choix : ");
                        int axe = lire_entier();
                        if (axe == 1)
                            flip_polyline(pln, true, false, 800, 800);  // inverser horizontalement
                          else if (axe == 2)
                            flip_polyline(pln, false, true, 800, 800);  // inverser verticalement
                        else
                            printf(YELLOW"\nAnnulé.\n"RESET);
                } break;
            } 
        } break; 
        
        case 'h': {
            path* pth = f->forme;
            printf(MAGENTA"\n--- Modifier Path ---\n"RESET);
            printf(BLUE"1"RESET" - Déplacer le path\n");
            printf(BLUE"2"RESET" - Couleur du trait\n");
            printf(BLUE"3"RESET" - Couleur de remplissage\n");
            printf(BLUE"4"RESET" - Fermer/Ouvrir le path\n");
            printf(BLUE"5"RESET" - Inverser selon un axe\n");
            printf(MAGENTA"\nTouche Entrer pour Annuler à tout moment\n"RESET);
            printf(BLUE"\n>>> Choisissez une option : "RESET);
            int choix = lire_entier();
            switch(choix) {
                case 1: {
                    int dx, dy;
                    printf("Déplacer X : "); if (!lire_entier_ou_retour(&dx)) break;
                    printf("Déplacer Y : "); if (!lire_entier_ou_retour(&dy)) break;
                    move_path(pth, dx, dy);
                } break;
                case 2: printf("Nouvelle couleur du trait : "); scanf("%15s", pth->line_color); vider_buffer(); break;
                case 3: printf("Nouvelle couleur de remplissage : "); scanf("%15s", pth->fill_color); vider_buffer(); break;
                case 4: pth->closed = !pth->closed; 
                        printf(GREEN"\n------------------------\n Le path est maintenant %s.\n------------------------\n"RESET, pth->closed ? "fermé" : "ouvert");
                } break;
                case 5: { // 🔹 FLIP SELON AXE
                        printf(BLUE"\nInverser le path :\n"RESET);
                        printf("1 - Selon X (horizontal)\n");
                        printf("2 - Selon Y (vertical)\n");
                        printf(">>> Votre choix : ");
                        int axe = lire_entier();
                        if (axe == 1)
                            flip_path(pth, true, false, 800, 800);  // inverser horizontalement
                          else if (axe == 2)
                            flip_path(pth, false, true, 800, 800);  // inverser verticalement
                        else
                            printf(YELLOW"\nAnnulé.\n"RESET);
                } break;
            }
        default: {
            printf(RED"\n-----------------\n Forme inconnue.\n-----------------\n"RESET);
        } break;
    }
}




void supprimer_forme() {
    if (nb_formes == 0) {
        printf(YELLOW"\n----------------------------\n Aucune forme à supprimer.\n----------------------------\n"RESET);
        return;
    }

    afficher_formes();
    printf(MAGENTA"\nTouche Entrer -> Annuler\n"RESET);
    printf(BLUE"\n>>> Index de la forme à supprimer (0-%d) : "RESET, nb_formes-1);

    char buffer[16];
    if (!fgets(buffer, sizeof(buffer), stdin)) return;
    buffer[strcspn(buffer, "\n")] = '\0';

    if (strlen(buffer) == 0) return; 

    int idx = atoi(buffer);
    if (idx < 0 || idx >= nb_formes) {
        printf(RED"\n-----------------\n Index invalide.\n-----------------\n"RESET);
        return;
    }

    switch(formes[idx].type) {
        case 'c': free_circle(formes[idx].forme); break;
        case 'a': free_square(formes[idx].forme); break;
        case 'r': free_rectangle(formes[idx].forme); break;
        case 'l': free_line(formes[idx].forme); break;
        case 'e': free_ellipse(formes[idx].forme); break;
        case 'g': free_polygon(formes[idx].forme); break;
        case 'p': free_polyline(formes[idx].forme); break;
        case 'h': free_path(formes[idx].forme); break;
    }

    for (int i = idx; i < nb_formes-1; i++) formes[i] = formes[i+1];
    nb_formes--;
    printf(GREEN"\n-------------------\n Forme supprimée !\n-------------------\n"RESET);
}



/** @brief Affiche la liste des formes stockées**/
void afficher_formes() {
    if (nb_formes == 0) {
        printf(YELLOW"\n------------------------------------\n Aucune forme n'a encore été créée.\n------------------------------------\n"RESET); // jaune
        return;
    }
    printf(CYAN"\n=== Liste des formes créées ===\n"RESET);
    for (int i = 0; i < nb_formes; i++) {
        printf("[%d] ", i);
        switch (formes[i].type) {
            case 'c': {
                circle* cir = formes[i].forme;
                printf("circle - position=(%d,%d), radius=%d, trait=%s, fond=%s, thickness=%d\n",
                       cir->x, cir->y, cir->radius, cir->line_color, cir->background_color, cir->thickness);
                break;
            }
            case 'a': {
                square* squ = formes[i].forme;
                printf("square - position=(%d,%d), côté=%d, trait=%s, fond=%s, thickness=%d\n",
                       squ->x, squ->y, squ->listed, squ->line_color, squ->background_color, squ->thickness);
                break;
            }
            case 'r': {
                rectangle* rec = formes[i].forme;
                printf("rectangle - position=(%d,%d), largeur=%d, hauteur=%d, trait=%s, fond=%s, thickness=%d\n",
                       rec->x, rec->y, rec->width, rec->height, rec->line_color, rec->background_color, rec->thickness);
                break;
            }
            case 'l': {
                line* lin = formes[i].forme;
                printf("line - de=(%d,%d) à=(%d,%d), couleur=%s, thickness=%d\n",
                       lin->x1, lin->y1, lin->x2, lin->y2, lin->line_color, lin->thickness);
                break;
            }
            case 'e': {
                ellipse* ell = formes[i].forme;
                printf("ellipse - position=(%d,%d), radius-x=%d, radius-y==%d, trait=%s, fond=%s, thickness=%d\n",
                       ell->x, ell->y, ell->radiusx, ell->radiusy, ell->line_color, ell->background_color, ell->thickness);
                break;
            }
            case 'g': {
                polygon* pgn = formes[i].forme;
                printf("polygon - %d points, trait=%s, fond=%s, thickness=%d\n",
                       pgn->nb_points, pgn->line_color, pgn->background_color, pgn->thickness);
                break;
            }
            case 'p': {
                polyline* pln = formes[i].forme;
                printf("polyline - %d points, trait=%s, thickness=%d\n",
                       pln->nb_points, pln->line_color, pln->thickness);
                break;
            }
            case 'h': { 
                path* pth = formes[i].forme;
                printf("path - %d points, trait=%s, remplissage=%s, thickness=%d, %s\n",
                    pth->nb_points,
                    pth->line_color,
                    pth->fill_color,
                    pth->thickness,
                    pth->closed ? "fermé" : "ouvert");
                break;
            }

default:
                printf(RED"\n-----------------\n Forme inconnue.\n-----------------\n"RESET);
                break;
        }
    }
}
