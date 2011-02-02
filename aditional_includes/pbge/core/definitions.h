#ifndef definitions_h_
#define definitions_h_ 1

// MISC
#define PBGE_KB 1024

// floatVector
#define PBGE_FLOAT_VECTOR_SIZE 56

// Constantes booleanas
#define PBGE_true 1
#define PBGE_false 0

// Constantes numéricas
#define PBGE_pi 3.1415927
#define PBGE_1_pi 0.3183099f   // 1/PBGE_pi

// Constantes para estabilidade de rotação
#define PBGE_min_rotation 0.18f
#define PBGE_max_rotation 3.125f


#define degToRad(angle) ((PBGE_pi * (angle))/180.0f)

#endif