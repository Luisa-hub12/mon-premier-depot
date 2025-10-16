#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Consignes/utils.h"
#include "export.h"
#include "../Shapes/shapes.h" 
/** @note #include "../Shapes/shapes.h" inclu toutes les formes */

/** @brief ici la variable va servir a faire un tableau de formes
 * @note extern indique que la variable est définie ailleurs (dans main.c)
 */
extern FormeStockee formes[MAX_FORMES];
extern int nb_formes;
/** @note ici la fonction va servir a convertir les formes en format svg
 * @param perror affiche un message d'erreur si le fichier ne peut pas être ouvert
 */
void export_svg() {
    FILE* f = fopen("export.svg", "w");
    if (!f) {
        perror("Erreur d’ouverture de export.svg");
        return;
    }

/** @brief ici la commande va servir a créer le viewport et à le définir
 * @note viewBox="0 0 800 600" définit le système de coordonnées internes (origine en haut à gauche, 800x600 unités)
 * @note width et height définissent la taille de l'affichage (800x600 pixels)
 * @note <rect> crée un rectangle de fond blanc couvrant tout le SVG
 */
    fprintf(f, "<svg xmlns='http://www.w3.org/2000/svg' width='800' height='600' viewBox='0 0 800 600'>\n");
    fprintf(f, "<rect width='100%%' height='100%%' fill='white'/>\n"); // fond blanc

/** @note toutes les fonctions qui suivent servent a definir les formes et à donner leurs valeurs pour que lorsque l'utilisateur créer sa forme
 * elle soit bien exportée dans le fichier svg et dans la viewbox
 */
    for (int i = 0; i < nb_formes; i++) {
        char type = formes[i].type;

        switch (type) {
            case 'r': {
                rectangle* rec = (rectangle*)formes[i].forme;
                fprintf(f, "<rect x='%d' y='%d' width='%d' height='%d' stroke='%s' fill='%s' stroke-width='%d'/>\n",
                        rec->x, rec->y, rec->width, rec->height, rec->line_color, rec->background_color, rec->thickness);
                break;
            }
            case 'a': {
                square* sqr = (square*)formes[i].forme;
                fprintf(f, "<rect x='%d' y='%d' width='%d' height='%d' stroke='%s' fill='%s' stroke-width='%d'/>\n",
                        sqr->x, sqr->y, sqr->listed, sqr->listed, sqr->line_color, sqr->background_color, sqr->thickness);
                break;
            }
            case 'c': {
                circle* cir = (circle*)formes[i].forme;
                fprintf(f, "<circle cx='%d' cy='%d' r='%d' stroke='%s' fill='%s' stroke-width='%d'/>\n",
                        cir->x, cir->y, cir->radius, cir->line_color, cir->background_color, cir->thickness);
                break;
            }
            case 'l': {
                line* lin = (line*)formes[i].forme;
                fprintf(f, "<line x1='%d' y1='%d' x2='%d' y2='%d' stroke='%s' stroke-width='%d'/>\n",
                        lin->x1, lin->y1, lin->x2, lin->y2, lin->line_color, lin->thickness);
                break;
            }
            case 'e': {
                ellipse* ell = (ellipse*)formes[i].forme;
                fprintf(f, "<ellipse cx='%d' cy='%d' rx='%d' ry='%d' stroke='%s' fill='%s' stroke-width='%d'/>\n",
                        ell->x, ell->y, ell->radiusx, ell->radiusy, ell->line_color, ell->background_color, ell->thickness);
                break;
            }
            case 'g': {
                polygon* pgn = (polygon*)formes[i].forme;
                fprintf(f, "<polygon points='");
                for (int j = 0; j < pgn->nb_points; j++)
                    fprintf(f, "%d,%d ", pgn->points[j].x, pgn->points[j].y);
                fprintf(f, "' stroke='%s' fill='%s' stroke-width='%d'/>\n",
                        pgn->line_color, pgn->background_color, pgn->thickness);
                break;
            }
            case 'p': {
                polyline* pln = (polyline*)formes[i].forme;
                fprintf(f, "<polyline points='");
                for (int j = 0; j < pln->nb_points; j++)
                    fprintf(f, "%d,%d ", pln->points[j].x, pln->points[j].y);
                fprintf(f, "' stroke='%s' fill='none' stroke-width='%d'/>\n",
                        pln->line_color, pln->thickness);
                break;
            }
            case 'h': { // 'h' = path
                path* pth = (path*)formes[i].forme; // Début du path : M (move to)
                fprintf(f, "<path d='M %d,%d ", pth->points[0].x, pth->points[0].y);// On trace des lignes : L (line to)
                for (int j = 1; j < pth->nb_points; j++) {
                    int cx = (pth->points[j-1].x + pth->points[j].x) / 2; // point de contrôle X
                    int cy = (pth->points[j-1].y + pth->points[j].y) / 2; // point de contrôle Y
                    fprintf(f, "Q %d,%d %d,%d ", cx, cy, pth->points[j].x, pth->points[j].y);
            }
                if (pth->closed) { /** @note ici la fonction va servir a fermer la forme si l'utisateur veut la fermer, sinon elle sera ouverte */
                    fprintf(f, "Z "); 
    }       
                fprintf(f, "' stroke='%s' fill='%s' stroke-width='%d'/>\n",
                    pth->line_color,
                    pth->closed ? pth->fill_color : "none", 
                    pth->thickness);

                break;
            }

        }
    }

    fprintf(f, "</svg>\n");
    fclose(f);

    printf("✅ export.svg créé avec succès. Ouvre-le dans ton navigateur.\n");
}
