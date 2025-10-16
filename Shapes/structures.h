#ifndef STRUCTURES_H
#define STRUCTURES_H
#include "../Consignes/utils.h"
#include "shapes.h"

#define MAX_SHAPES 10   /**< Nombre maximal de formes stockables */


/**
 * @struct Square
 * @brief Représente un carré.
 */
typedef struct {
    int x;                              /**< Coordonnée X du coin supérieur gauche */
    int y;                              /**< Coordonnée Y du coin supérieur gauche */
    int side;                           /**< Longueur du côté */
    char line_color[MAX_COLOR];         /**< Couleur du trait */
    char background_color[MAX_COLOR];   /**< Couleur du fond */
    int thickness;                      /**< Épaisseur du trait */
} square;

/**
 * @struct Circle
 * @brief Représente un cercle.
 */
typedef struct {
    int x;                              /**< Coordonnée X du centre */
    int y;                              /**< Coordonnée Y du centre */
    int radius;                         /**< Rayon du cercle */
    char line_color[MAX_COLOR];         /**< Couleur du trait */
    char background_color[MAX_COLOR];   /**< Couleur du fond */
    int thickness;                      /**< Épaisseur du trait */
} circle;

/**
 * @struct Ellipse
 * @brief Représente une ellipse.
 */
typedef struct {
    int x;                              /**< Coordonnée X du centre */
    int y;                              /**< Coordonnée Y du centre */
    int radiusx;                        /**< Rayon horizontal */
    int radiusy;                        /**< Rayon vertical */
    char line_color[MAX_COLOR];         /**< Couleur du trait */
    char background_color[MAX_COLOR];   /**< Couleur du fond */
    int thickness;                      /**< Épaisseur du trait */
} ellipse;

/**
 * @struct Line
 * @brief Représente un segment de droite.
 */
typedef struct {
    int x1;                             /**< Coordonnée X du premier point */
    int y1;                             /**< Coordonnée Y du premier point */
    int x2;                             /**< Coordonnée X du second point */
    int y2;                             /**< Coordonnée Y du second point */
    char line_color[MAX_COLOR];         /**< Couleur du trait */
    int thickness;                      /**< Épaisseur du trait */
} line;

/**
 * @struct Rectangle
 * @brief Représente un rectangle.
 */
typedef struct {
    int x;                              /**< Coordonnée X du coin supérieur gauche */
    int y;                              /**< Coordonnée Y du coin supérieur gauche */
    int width;                          /**< Largeur du rectangle */
    int height;                         /**< Hauteur du rectangle */
    char line_color[MAX_COLOR];         /**< Couleur du trait */
    char background_color[MAX_COLOR];   /**< Couleur du fond */
    int thickness;                      /**< Épaisseur du trait */
} rectangle;

/**
 * @struct Point
 * @brief Représente un point dans le plan.
 */
typedef struct {
    int x;  /**< Coordonnée X du point */
    int y;  /**< Coordonnée Y du point */
} Point;

/**
 * @struct Polygone
 * @brief Représente un polygone fermé.
 */
typedef struct {
    Point* points;                      /**< Tableau de points formant le polygone */
    int nb_points;                      /**< Nombre de points du polygone */
    char line_color[MAX_COLOR];         /**< Couleur du trait */
    char background_color[MAX_COLOR];   /**< Couleur du fond */
    int thickness;                      /**< Épaisseur du trait */
} polygon;

/**
 * @struct Path
 * @brief Représente un chemin (path) — une suite de segments pouvant être ouverts ou fermés.
 */
typedef struct {
    Point* points;                      /**< Tableau de points formant le chemin */
    int nb_points;                      /**< Nombre total de points du chemin */
    char line_color[MAX_COLOR];         /**< Couleur du contour */
    char fill_color[MAX_COLOR];         /**< Couleur de remplissage (si fermé) */
    int thickness;                      /**< Épaisseur du contour */
    int closed;                         /**< 1 si le chemin est fermé (Z), 0 sinon */
} path;


/**
 * @struct Polyline
 * @brief Représente une polyligne (suite de segments non fermée).
 */
typedef struct {
    Point* points;                      /**< Tableau de points formant la polyligne */
    int nb_points;                      /**< Nombre de points de la polyligne */
    char line_color[MAX_COLOR];         /**< Couleur du trait */
    int thickness;                      /**< Épaisseur du trait */
} polyline;

/**
 * @enum ShapeType
 * @brief Identifie le type d'une forme.
 */
typedef enum {
    CIRCLE,     /**< Cercle */
    SQUARE,     /**< Carré */
    RECTANGLE,  /**< Rectangle */
    LINE,       /**< Ligne */
    ELLIPSE,    /**< Ellipse */
    POLYGONE,   /**< Polygone */
    POLYLINE,   /**< Polyligne */
    PATH,       /**< Chemin */
    UNKNOWN     /**< Type inconnu */
} ShapeType;

/**
 * @union ShapeData
 * @brief Contient un pointeur vers une structure de forme spécifique.
 */
typedef union {
    circle* Circle;         /**< Pointeur vers un cercle */
    square* Square;         /**< Pointeur vers un carré */
    rectangle* Rectangle;   /**< Pointeur vers un rectangle */
    line* Line;             /**< Pointeur vers une ligne */
    ellipse* Ellipse;       /**< Pointeur vers une ellipse */
    polygon* Polygon;     /**< Pointeur vers un polygone */
    polyline* Polyline;     /**< Pointeur vers une polyligne */
    path* Path;             /**< Pointeur vers un chemin */
    void* ptr;              /**< Pointeur générique */
} ShapeData;

/**
 * @struct StoredForm
 * @brief Structure générique stockant une forme et son type.
 */
typedef struct {
    ShapeType type; /**< Type de la forme */
    ShapeData data; /**< Données associées à la forme */
} StoredForm;

/** Tableau global contenant toutes les formes dessinées */
extern StoredForm shapes[MAX_SHAPES];

/** Nombre actuel de formes stockées */
extern int nb_shapes;

#endif
