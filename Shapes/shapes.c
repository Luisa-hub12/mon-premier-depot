#include "shapes.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>


void flip_points(Point* points, int nb_points, bool flipX, bool flipY, int width, int height) {
    if (!points || nb_points <= 0) return;

    for (int i = 0; i < nb_points; i++) {
        if (flipX) points[i].x = width - points[i].x;
        if (flipY) points[i].y = height - points[i].y;
    }
}

/** @brief ici la fonction va servir a créer le carré (square)
 * @param malloc alloue de la mémoire pour le carré. Sizeof = taille en octets de la structure carré.
 * @param strncpy copie une chaîne de caractères (ici les couleurs)
 * @param squ-x = x sert a initialiser la coordonnée x du carré
 * @param strncpy(squ->line_color, line_color, 15); on copie la couleur du trait
 * @param strncpy(squ->background_color, background_color, 15); on copie la couleur de fond
 * @return retourne le pointeur vers le carré
 */
square* create_square(int x, int y, int listed, const char* line_color, const char* background_color, int thickness) {
    square* squ = malloc(sizeof(square)); 
    if (!squ)
        return NULL; 

    squ->x = x; 
    squ->y = y;
    squ->listed = listed; 
    strncpy(squ->line_color, line_color, 15); 
    squ->line_color[15] = '\0';
    strncpy(squ->background_color, background_color, 15); 
    squ->background_color[15] = '\0';
    squ->thickness = thickness; 

    return squ;
}
/** @param move_square permet de déplacer le carré. 
 * @note dx et dy sont les déplacements en x et y.
 * @note si le carré n'existe pas alors on arrête la fonction.
 */
void move_square(square* squ, int dx, int dy) { 
    if (!squ) 
        return;
    squ->x += dx;
    squ->y += dy;
}
/** @brief la fonction change la couleur du trait du caré
 * @param strncpy copie la nouvelle couleur
 * @param squ->line_color[15] = '\0'; on ajoute le caractère de fin de chaîne
 */
void change_color_square_line(square* squ, const char* color) { 
    if (!squ) 
        return;
    strncpy(squ->line_color, color, 15); 
    squ->line_color[15] = '\0'; 
}

void change_background_color_square(square* squ, const char* color) { 
    if (!squ) /** @note si le carré n'existe pas alors on retourne */
        return;
    strncpy(squ->background_color, color, 15);
    squ->background_color[15] = '\0';
}

void free_square(square* squ) { /** @brief la fonction libère la mémoire allouée pour le carré**/
    if (!squ)
        return;
    free(squ); /** @note on libère la mémoire**/
}
/** @brief ici la fonction vérifie si le carré est entièrement visible dans le viewport
 * @param width_viewport largeur du viewport
 * @param if (squ->listed <= 0) si le côté est inférieur ou égal à 0 on retourne false
 * @param if (squ->x < 0 || squ->x + squ->listed > width_viewport) si le carré dépasse les limites du viewport on retourne false
 * @return retourne true si le carré est entièrement visible dans le viewport
 */
bool check_square(const square* squ, int width_viewport, int height_viewport) { 
    if (!squ) 
        return false;
    if (squ->listed <= 0) 
        return false; 
    if (squ->x < 0 || squ->x + squ->listed > width_viewport) 
        return false;
    if (squ->y < 0 || squ->y + squ->listed > height_viewport) 
        return false; 
    return true;
}
void flip_square(square* squ, bool flipX, bool flipY, int width, int height) {
    if (!squ) return;
    if (flipX) squ->x = width - (squ->x + squ->listed);
    if (flipY) squ->y = height - (squ->y + squ->listed);
}


circle* create_circle(int x, int y, int radius, const char* line_color, const char* background_color, int thickness) { 
    circle* cir = malloc(sizeof(circle)); 
    if (!cir) 
        return NULL;

    cir->x = x; 
    cir->y = y;
    cir->radius = radius; /** @note on initialise le rayon**/
    strncpy(cir->line_color, line_color, 15); /** @note on copie la couleur du trait**/
    cir->line_color[15] = '\0'; 
    strncpy(cir->background_color, background_color, 15); /** @note on copie la couleur de fond**/
    cir->background_color[15] = '\0';
    cir->thickness = thickness;

    return cir; /** @note on retourne le pointeur vers le cercle**/
}

void move_circle(circle* cir, int dx, int dy) { 
    if (!cir) 
        return;
    cir->x += dx;
    cir->y += dy;
}

void change_color_line(circle* cir, const char* color) {
    if (!cir) 
        return; 
    strncpy(cir->line_color, color, 15);
    cir->line_color[15] = '\0';
}

void change_background_color(circle* cir, const char* color) { 
    if (!cir)
        return;
    strncpy(cir->background_color, color, 15); 
    cir->background_color[15] = '\0'; 
}

void free_circle(circle* cir) { /** @note la fonction libère la mémoire allouée pour le cercle**/
    free(cir); /** @return on libère la mémoire**/
}
/** @brief la fonction va vérifier si le cercle est entièrement contenu dans le viewport
 * @param if (cir->radius <= 0) si le radius est inférieur ou égal à 0 on retourne false
 * @note sinon on retourne true 
 */
bool check_circle(const circle* cir, int width_viewport, int height_viewport) { 
    if (!cir) 
        return false; 
    if (cir->radius <= 0) 
        return false; 
    if (cir->x < 0 || cir->x + cir->radius > width_viewport) 
        return false; 
    if (cir->y < 0 || cir->y + cir->radius > height_viewport) 
        return false; 
    return true; 
}

void flip_circle(circle* cir, bool flipX, bool flipY, int width, int height) {
    if (!cir) return;
    if (flipX) cir->x = width - cir->x;
    if (flipY) cir->y = height - cir->y;
}

/** @note on libère la mémoire allouée de l'éllipse */
void free_ellipse(ellipse* ell) { 
    if (!ell) return;
    free(ell);
}
ellipse* create_ellipse(int x, int y, int radiusx, int radiusy, const char* line_color, const char* background_color, int thickness) {
    ellipse* ell = malloc(sizeof(ellipse));
    if (!ell) return NULL;


    ell->x = x;
    ell->y = y;
    ell->radiusx = radiusx;
    ell->radiusy = radiusy;
    strncpy(ell->line_color, line_color, 15);
    strncpy(ell->background_color, background_color, 15);
    ell->thickness = thickness;

    return ell;
}
void flip_ellipse(ellipse* ell, bool flipX, bool flipY, int width, int height) {
    if (!ell) return;
    if (flipX) ell->x = width - ell->x;
    if (flipY) ell->y = height - ell->y;
}
void move_ellipse(ellipse* ell, int dx, int dy) {
    if (!ell) return;
    ell->x += dx;
    ell->y += dy;
}

void free_line(line* lin) {
    if (!lin) return;
    free(lin);
}
line* create_line(int x1, int y1, int x2, int y2, const char* line_color, int thickness) {
    line* lin = malloc(sizeof(line)); /** @note ici on fait une allocation dynamique */
    if (!lin) return NULL;

    lin->x1 = x1;
    lin->y1 = y1;
    lin->x2 = x2;
    lin->y2 = y2;

    strncpy(lin->line_color, line_color, 15);
    lin->line_color[14] = '\0';  

    lin->thickness = thickness;

    return lin;
}
void move_line(line* lin, int dx1, int dy1, int dx2, int dy2) {
    if (!lin) return;
    lin->x1 += dx1;
    lin->y1 += dy1;
    lin->x2 += dx2;
    lin->y2 += dy2;
}
void flip_line(line* lin, bool flipX, bool flipY, int width, int height) {
    if (!lin) return;
    if (flipX) {
        lin->x1 = width - lin->x1;
        lin->x2 = width - lin->x2;
    }
    if (flipY) {
        lin->y1 = height - lin->y1;
        lin->y2 = height - lin->y2;
    }
}

void free_polygon(polygon* pgn) {
    if (!pgn) return;
    if (pgn->points) free(pgn->points);
    free(pgn);
}

polygon* create_polygon(Point* points, int nb_points, const char* line_color, const char* background_color, int thickness) {
    if (!points || nb_points < 3) return NULL; 

    polygon* pgn = malloc(sizeof(polygon));
    if (!pgn) return NULL;

    pgn->points = malloc(sizeof(Point) * nb_points);
    if (!pgn->points) {
        free(pgn);
        return NULL;
    }

    /** @note copie de points */
    for (int i = 0; i < nb_points; i++)
        pgn->points[i] = points[i];

    pgn->nb_points = nb_points;

    /** @note copie des couleurs */
    strncpy(pgn->line_color, line_color, MAX_COLOR - 1);
    pgn->line_color[MAX_COLOR - 1] = '\0';

    strncpy(pgn->background_color, background_color, MAX_COLOR - 1);
    pgn->background_color[MAX_COLOR - 1] = '\0';

    pgn->thickness = thickness;

    return pgn;
}
void move_polygon(polygon* pgn, int dx, int dy) {
    if (!pgn) return;
    for (int i = 0; i < pgn->nb_points; i++) {
        pgn->points[i].x += dx;
        pgn->points[i].y += dy;
    }
}

void free_polyline(polyline* pln) {
    if (!pln) return;
    if (pln->points) free(pln->points);
    free(pln);
}
void flip_polygon(polygon* pgn, bool flipX, bool flipY, int width, int height) {
    if (!pgn) return;
    flip_points(pgn->points, pgn->nb_points, flipX, flipY, width, height);
}

polyline* create_polyline(Point* points, int nb_points, const char* line_color, int thickness) {
    if (!points || nb_points < 3) return NULL;

    polyline* pln = malloc(sizeof(polyline));
    if (!pln) return NULL;

    pln->points = malloc(sizeof(Point) * nb_points);
    if (!pln->points) {
        free(pln);
        return NULL;
    }

    for (int i = 0; i < nb_points; i++)
        pln->points[i] = points[i];

    pln->nb_points = nb_points;
    strncpy(pln->line_color, line_color, MAX_COLOR-1);
    pln->thickness = thickness;

    return pln;
}
void move_polyline(polyline* pln, int dx, int dy) {
    if (!pln) return;
    for (int i = 0; i < pln->nb_points; i++) {
        pln->points[i].x += dx;
        pln->points[i].y += dy;
    }
}
void flip_polyline(polyline* pln, bool flipX, bool flipY, int width, int height) {
    if (!pln) return;
    flip_points(pln->points, pln->nb_points, flipX, flipY, width, height);
}


void free_rectangle(rectangle* rec) {
    if (!rec) return;
    free(rec);
}

rectangle* create_rectangle(
    int x, 
    int y, 
    int width, 
    int height, 
    const char* line_color, 
    const char* background_color, 
    int thickness
) {
    
    rectangle* rec = malloc(sizeof(rectangle));
    if (!rec) return NULL;

    
    rec->x = x;
    rec->y = y;
    rec->width = width;
    rec->height = height;

    
    strncpy(rec->line_color, line_color, 15);
    rec->line_color[14] = '\0';

    strncpy(rec->background_color, background_color, 15);
    rec->background_color[14] = '\0';

    rec->thickness = thickness;

    return rec;
}
void move_rectangle(rectangle* rec, int dx, int dy) {
    if (!rec) return;
    rec->x += dx;
    rec->y += dy;
}
void flip_rectangle(rectangle* rec, bool flipX, bool flipY, int width, int height) {
    if (!rec) return;
    if (flipX) rec->x = width - (rec->x + rec->width);
    if (flipY) rec->y = height - (rec->y + rec->height);
}

void free_path(path* pth) {
    if (!pth) return;
    if (pth->points) free(pth->points);
    free(pth);
}


path* create_path(Point* points, int nb_points, const char* line_color, const char* fill_color, int thickness, int closed) {
    if (!points || nb_points < 2) return NULL;

    path* pth = malloc(sizeof(path));
    if (!pth) return NULL;

    pth->points = malloc(sizeof(Point) * nb_points);
    if (!pth->points) {
        free(pth);
        return NULL;
    }

    for (int i = 0; i < nb_points; i++)
        pth->points[i] = points[i];

    pth->nb_points = nb_points;


    strncpy(pth->line_color, line_color, MAX_COLOR - 1);
    pth->line_color[MAX_COLOR - 1] = '\0';

    strncpy(pth->fill_color, fill_color, MAX_COLOR - 1);
    pth->fill_color[MAX_COLOR - 1] = '\0';

    pth->thickness = thickness;
    pth->closed = closed; /** @note 1 si le chemin est fermé, 0 sinon**/

    return pth;
}

/** @note Déplace le path de dx, dy**/
void move_path(path* pth, int dx, int dy) {
    if (!pth) return;
    for (int i = 0; i < pth->nb_points; i++) {
        pth->points[i].x += dx;
        pth->points[i].y += dy;
    }
}
void flip_path(path* pth, bool flipX, bool flipY, int width, int height) {
    if (!pth) return;
    flip_points(pth->points, pth->nb_points, flipX, flipY, width, height);
}
