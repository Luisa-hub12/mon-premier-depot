#ifndef EXPORT_H
#define EXPORT_H

#include "../Consignes/utils.h"          // Pour accéder à FormeStockee, MAX_FORMES, etc.
#include "../Shapes/shapes.h"

/**
 * @brief Exporte toutes les formes créées dans un fichier SVG.
 *
 * La fonction parcourt la liste globale des formes (formes[])
 * et écrit un fichier nommé "export.svg" contenant la représentation
 * graphique de toutes les formes en respectant leur position, couleur,
 * et épaisseur de ligne.
 *
 * Le fichier exporté peut être visualisé dans n’importe quel navigateur web.
 *
 * Exemple :
 * @code
 * export_svg();
 * @endcode
 */
void export_svg(void);

#endif