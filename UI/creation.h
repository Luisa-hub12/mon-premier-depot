#ifndef CREATION_H
#define CREATION_H

/**
 * @brief Affiche le menu permettant de choisir la forme à créer.
 */
void menu_creation();

/**
 * @brief Demande à l’utilisateur les paramètres pour créer un cercle.
 */
void ask_circle();

/**
 * @brief Demande à l’utilisateur les paramètres pour créer un carré.
 */
void ask_square();

/**
 * @brief Demande à l’utilisateur les paramètres pour créer un rectangle.
 */
void ask_rectangle();

/**
 * @brief Demande à l’utilisateur les paramètres pour créer une ligne.
 */
void ask_line();

/**
 * @brief Demande à l’utilisateur les paramètres pour créer une ellipse.
 */
void ask_ellipse();

/**
 * @brief Demande à l’utilisateur les paramètres pour créer un polygone.
 */
void ask_polygon();

/**
 * @brief Demande à l’utilisateur les paramètres pour créer une polyligne.
 */
void ask_polyline();

void ask_path();

void export_svg();

#endif