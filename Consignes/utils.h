#ifndef UTILS_H
#define UTILS_H

/**
 * @file utils.h
 * @brief Fonctions utilitaires et définitions communes pour le projet.
 */

#include "../Shapes/shapes.h"  // Inclut la définition unique de Point
#include <stdbool.h>
#include <stdio.h>

/** 
 * @brief Couleurs ANSI pour affichage coloré dans le terminal.
 */
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define BLUE    "\033[1;34m"
#define YELLOW  "\033[1;33m"
#define ORANGE  "\033[38;2;255;165;0m"
#define PURPLE  "\033[38;2;128;0;128m"
#define PINK    "\033[38;2;255;192;203m"
#define BROWN   "\033[38;2;165;42;42m"
#define GRAY    "\033[1;30m"
#define CYAN    "\033[1;36m"
#define MAGENTA "\033[1;35m"
#define RESET   "\033[0m"

/** @brief Taille maximale d'une chaîne de couleur (hex + '\0' ou nom standard) */
#define MAX_COLOR 16

/** @brief Nombre maximum de formes pouvant être stockées simultanément. */
#define MAX_FORMES 10

/**
 * @struct FormeStockee
 * @brief Structure générique pour stocker une forme quelconque.
 *
 * Chaque forme est stockée via un pointeur générique, accompagné d’un
 * identifiant de type pour distinguer les différentes figures géométriques.
 */
typedef struct {
    void* forme; /**< Pointeur vers la structure de la forme */
    char type;   /**< Type de forme ('c'=cercle, 'a'=carré, 'r'=rectangle, 'l'=ligne, 'g'=polygone, 'p'=polyline, 'e'=ellipse, 'h' =path) */
} FormeStockee;

/** @brief Tableau global contenant les formes créées */
extern FormeStockee formes[MAX_FORMES];

/** @brief Nombre actuel de formes stockées dans le tableau */
extern int nb_formes;

/** 
 * @brief Tableau des couleurs SVG standards acceptées par le programme.
 *
 * Il est utilisé pour valider les saisies de l'utilisateur dans `saisir_couleur`.
 */
extern const char* couleurs_standard[];

/** @brief Nombre de couleurs standard dans le tableau `couleurs_standard`. */
extern const int nb_couleurs_standard;

/**
 * @brief Vide le buffer d'entrée standard.
 *
 * Supprime les caractères résiduels dans `stdin`, notamment après une saisie incorrecte.
 */
void vider_buffer();

/**
 * @brief Lit un entier saisi par l’utilisateur.
 *
 * La fonction répète la saisie tant qu’un entier valide n’est pas entré.
 * @return L’entier saisi par l’utilisateur.
 */
int lire_entier();

/**
 * @brief Vérifie si une chaîne représente un code hexadécimal de couleur valide (#RRGGBB).
 *
 * @param s Chaîne à vérifier
 * @return `true` si la chaîne est un hexadécimal valide, `false` sinon
 */
bool est_hex(const char* s);

/**
 * @brief Vérifie si une chaîne correspond à une couleur standard SVG acceptée.
 *
 * @param s Chaîne à vérifier
 * @return `true` si la chaîne est une couleur standard, `false` sinon
 */
bool est_couleur_standard(const char* s);

/**
 * @brief Vérifie si une couleur est valide pour SVG.
 *
 * Une couleur est valide si c’est soit un code hexadécimal `#RRGGBB`,
 * soit une couleur standard listée dans `couleurs_standard`.
 *
 * @param s Chaîne représentant la couleur
 * @return `true` si la couleur est valide, `false` sinon
 */
bool couleur_valide_svg(const char* s);

/**
 * @brief Lit un entier depuis l’entrée standard. Permet d’annuler si entrée vide.
 *
 * @param[out] val Pointeur vers l’entier à remplir.
 * @return true si un entier a été saisi, false si entrée seule (annuler).
 */
bool lire_entier_ou_retour(int* val);

/**
 * @brief Demande à l’utilisateur de saisir une couleur et la valide.
 *
 * Affiche un message et attend la saisie. Si la couleur n’est pas valide,
 * elle indique l’erreur et affiche la liste des couleurs standard disponibles.
 *
 * @param buffer Chaîne de caractères où sera stockée la couleur saisie
 * @param message Message à afficher pour demander la couleur
 */
void saisir_couleur(char* buffer, const char* message);

#endif // UTILS_H
