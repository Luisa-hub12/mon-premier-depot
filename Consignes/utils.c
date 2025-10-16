#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include "../Consignes/utils.h"

/** @brief on utilise strings.h pour pouvoir utiliser strcasecmp */

/** @brief ici on va donner la liste des couleurs SVG que l'utilisateur va devoir choisir
 * @note par exemple, l'utilisateur va choisir la forme qu'il veut, ensuite il va devoir choisir la couleur de la forme, si il ne choisit 
 * pas une couleur valide, on lui donne la liste des couleurs valides jusqu'a ce qu'il choisisse une couleur valide
 */

const char* couleurs_standard[] = { 
    "black", "white", "red", "green", "blue",
    "yellow", "orange", "purple", "pink", "brown",
    "gray", "cyan", "magenta"
};
const int nb_couleurs_standard = sizeof(couleurs_standard) / sizeof(couleurs_standard[0]);

/** @brief ici un buffer va servir a une zone de mémoire temporaire utilisée pour stocker des données en attente de traitement. 
 * @param int c est un caractère temporaire pour vider le buffer
 * @note on vide le buffer pour éviter que des entrées invalides restent dans le buffer
 * @note on utilise getchar() pour lire les caractères un par un jusqu'à ce qu'on trouve un saut de ligne ou la fin du fichier (EOF)
 * @note cette fonction est utile après une saisie utilisateur pour s'assurer que le buffer d'entrée est propre avant la prochaine saisie
 */
void vider_buffer() {  
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}
/** @brief int lire_entier: ici on créer une fonction pour lire un entier qui va avoir un gestion des erreurs
 * @note on utilise scanf pour lire l'entrée utilisateur et on vérifie si la lecture a réussi en vérifiant le retour de scanf
 * @note si l'entrée n'est pas un entier valide, on affiche un message d'erreur et on vide le buffer pour enlever l'entrée invalide
 * @note on continue à demander une entrée jusqu'à ce qu'un entier valide soit saisi
 * @param vider_buffer() est appelé après une lecture réussie pour s'assurer que le buffer est propre pour les futures lectures
 * @note on vide le buffer après que l'entrée de l'utilisateur soit valide pour éviter des problèmes lors de futures lectures
*/
int lire_entier() { 
    int valeur;
    while (scanf("%d", &valeur) != 1) {
        printf(RED"\n>>> Entrée invalide. Veuillez entrer un entier : "RESET);
        vider_buffer();
    }
    vider_buffer();
    return valeur;
}
/** @brief ici bool est_hex va servir a vérifier si une chaîne est un code hexadécimal de couleur valide (#RRGGBB)
 * @param s est la chaîne à vérifier
 * @note on vérifie que la chaîne commence par '#' et qu'elle a une longueur de 7 caractères
 * @note on vérifie que les 6 caractères suivants sont des chiffres hexadécimaux (0-9, A-F, a-f)
 * @return true si la chaîne est un code hexadécimal valide, false sinon
 */
bool est_hex(const char* s) { 
    if (!s || strlen(s) != 7 || s[0] != '#') return false;
    for (int i = 1; i < 7; i++) {
    char c = s[i];
    if (!((c >= '0' && c <= '9') ||
          (c >= 'A' && c <= 'F') ||
          (c >= 'a' && c <= 'f')))
        return false;
}

    return true;
}
/** @brief ici avec bool est_couleur standars, on va vérifier si la chaîne s est dans la liste des couleurs standars
 * @param s est la chaîne à vérifier
 * @note on utilise strcasecmp pour comparer les chaînes de manière insensible à la casse
 * @return true si la chaîne est une couleur standard, false sinon
 */
bool est_couleur_standard(const char* s) {
    for (int i = 0; i < nb_couleurs_standard; i++) {
        if (strcasecmp(s, couleurs_standard[i]) == 0) return true;
    }
    return false;
}
/** @brief une couleur est valide si c'est soit un code hexadécimal #RRGGBB, soit une couleur standard listée dans couleurs_standard
 * @param s est la chaîne représentant la couleur
 * @return true si la couleur est valide, false sinon
 * @note on utilise les fonctions est_hex et est_couleur_standard pour vérifier la validité de la couleur
 * @note si l'une des deux conditions est vraie, la couleur est considérée comme valide
 */
bool couleur_valide_svg(const char* s) {
    return est_hex(s) || est_couleur_standard(s);
}
/** @brief ici la fonction va permettre d'annuler la commande de l'utilisateur si l'entier est vide
 * @param valeur est un pointeur vers l'entier à remplir
 * @note on utilise fgets pour lire une ligne d'entrée et on vérifie si la ligne est vide
 * @note si la ligne est vide, on retourne false pour indiquer l'annulation
 * @note si la ligne n'est pas vide, on utilise strtol pour convertir la chaîne en entier
 * @note on vérifie si la conversion a réussi en vérifiant si endptr pointe à la fin de la chaîne
 * @return true si un entier a été saisi, false si entrée seule (annuler) (strlen(buffer) == 0)
 */
bool lire_entier_ou_retour(int* valeur) { 
    char buffer[64];
    if (!fgets(buffer, sizeof(buffer), stdin)) return false;
    buffer[strcspn(buffer, "\n")] = '\0'; // enlever le \n

    if (strlen(buffer) == 0) return false; 

    char* endptr;
    long val = strtol(buffer, &endptr, 10);
    if (*endptr != '\0') return false;
    *valeur = (int)val;
    return true;
}
/** @brief ici on va demander a l'utilisateur de saisir une couleur
 * @param buffer est la chaîne où la couleur saisie sera stockée
 * @param message est le message à afficher pour demander la couleur
 * @note on utilise une boucle infinie pour continuer à demander la couleur jusqu'à ce qu'une couleur valide soit saisie
 * @note on utilise scanf pour lire la couleur saisie par l'utilisateur
 * @note si la couleur est valide (vérifiée par couleur_valide_svg), on retourne de la fonction
 * @note si la couleur n'est pas valide, on affiche un message d'erreur et la liste des couleurs standard disponibles
 */
void saisir_couleur(char* buffer, const char* message) {
    while (1) {
        printf("%s", message);
        scanf("%15s", buffer);
        vider_buffer();
        if (couleur_valide_svg(buffer)) return;
        printf(RED"\nCouleur invalide ! Utilisez un hexadécimal (#RRGGBB) ou une couleur standard :\n\n"RESET);
        printf(RED"red  "GREEN"green  "BLUE"blue  "YELLOW"yellow  "ORANGE"orange  "PURPLE"purple  "PINK"pink  "BROWN"brown  "GRAY"gray  "CYAN"cyan  "MAGENTA"magenta\n\n"RESET);
    }
}