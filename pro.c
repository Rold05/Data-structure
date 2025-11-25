#include <stdio.h>

#define DS_ARRAY_STATIC      1
#define DS_ARRAY_DYNAMIC     2
#define DS_LINKED_LIST       3
#define DS_STACK             4
#define DS_QUEUE             5
#define DS_BST               6
#define DS_HEAP              7
#define DS_GRAPH             8
#define DS_TRIE              9

int askYesNo(const char *question) {
    int answer = -1;
    while (answer != 0 && answer != 1) {
        printf("%s (1 = si, 0 = no): ", question);
        if (scanf("%d", &answer) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            answer = -1;
        }
    }
    return answer;
}


int askOption(const char *question, int min, int max) {
    int option = min - 1;
    while (option < min || option > max) {
        printf("%s (%d-%d): ", question, min, max);
        if (scanf("%d", &option) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            option = min - 1;
        }
    }
    return option;
}

int decideStructure(
    int needRandomAccess,
    int manyMiddleInserts,
    int lifoProcessing,
    int fifoProcessing,
    int needPriority,
    int dynamicSize,
    int graphRelationships,
    int prefixSearch
) {
    if (graphRelationships) {
        return DS_GRAPH;
    }

    if (prefixSearch) {
        return DS_TRIE;
    }

    if (needPriority) {
        return DS_HEAP;
    }

    if (lifoProcessing) {
        return DS_STACK;
    }

    if (fifoProcessing) {
        return DS_QUEUE;
    }

    if (needRandomAccess && dynamicSize && !manyMiddleInserts) {
        return DS_ARRAY_DYNAMIC;
    }

    if (manyMiddleInserts && dynamicSize) {
        return DS_LINKED_LIST;
    }

    if (!dynamicSize && needRandomAccess) {
        return DS_ARRAY_STATIC;
    }

    return DS_BST;
}


void showRecommendation(int dsId) {
    printf("\n==============================\n");
    printf(" RECOMENDACION FINAL\n");
    printf("==============================\n\n");

    switch (dsId) {
    case DS_ARRAY_STATIC:
        printf("Estructura recomendada: ARREGLO ESTATICO\n\n");
        printf("Por que:\n");
        printf("- El tamano de los datos parece fijo o conocido de antemano.\n");
        printf("- Necesitas acceso rapido por indice (arr[i]).\n");
        printf("- No se realizan muchas inserciones/borrados en medio.\n\n");

        printf("Diagrama (vista logica):\n");
        printf("[0] [1] [2] [3] [4]\n");
        printf(" |   |   |   |   |\n");
        printf(" a0  a1  a2  a3  a4\n\n");

        printf("Pseudocodigo de operaciones basicas:\n");
        printf("1) Acceso por indice\n");
        printf("   function get(A, i):\n");
        printf("       pre: 0 <= i < n\n");
        printf("       return A[i]   // O(1)\n\n");
        printf("2) Actualizar valor\n");
        printf("   function set(A, i, x):\n");
        printf("       pre: 0 <= i < n\n");
        printf("       A[i] <- x    // O(1)\n\n");

        printf("Ejemplo (calificaciones de 5 examenes):\n");
        printf("   int grades[5] = {90, 85, 78, 95, 88};\n");
        printf("   // get promedio recorriendo el arreglo\n\n");
        break;

    case DS_ARRAY_DYNAMIC:
        printf("Estructura recomendada: ARREGLO DINAMICO\n\n");
        printf("Por que:\n");
        printf("- Se necesita acceso por indice pero el tamano puede crecer.\n");
        printf("- Se pueden hacer redimensiones usando malloc/realloc.\n\n");

        printf("Diagrama:\n");
        printf("ptr -> [0] [1] [2] ... [cap-1]\n");
        printf("        |   |   |        |\n");
        printf("        a0  a1  a2     a_{n-1}\n\n");

        printf("Pseudocodigo (insertar al final):\n");
        printf("   function pushBack(A, n, cap, x):\n");
        printf("       if n == cap:\n");
        printf("           cap <- 2 * cap\n");
        printf("           reservar nuevo arreglo y copiar\n");
        printf("       A[n] <- x\n");
        printf("       n <- n + 1\n\n");

        printf("Ejemplo (lista de tareas que crece):\n");
        printf("   // agregar nuevas tareas al final segun se necesiten.\n\n");
        break;

    case DS_LINKED_LIST:
        printf("Estructura recomendada: LISTA LIGADA\n\n");
        printf("Por que:\n");
        printf("- Las inserciones y borrados en medio son frecuentes.\n");
        printf("- El tamano puede cambiar mucho y no importa el acceso por indice.\n\n");

        printf("Diagrama:\n");
        printf("head -> [dato|*] -> [dato|*] -> [dato|*] -> NULL\n\n");

        printf("Pseudocodigo insertar despues de un nodo p:\n");
        printf("   function insertAfter(p, x):\n");
        printf("       newNode <- nuevo nodo con dato x\n");
        printf("       newNode.next <- p.next\n");
        printf("       p.next <- newNode\n");
        printf("   // O(1) si ya tienes p\n\n");

        printf("Ejemplo (playlist de canciones):\n");
        printf("   // puedes insertar una nueva cancion entre dos existentes.\n\n");
        break;

    case DS_STACK:
        printf("Estructura recomendada: PILA (STACK)\n\n");
        printf("Por que:\n");
        printf("- La logica es LIFO: el ultimo en entrar es el primero en salir.\n");
        printf("- Se manejan operaciones tipo deshacer/undo o recorrido inverso.\n\n");

        printf("Diagrama:\n");
        printf("   top\n");
        printf("    |\n");
        printf("   [ x3 ]\n");
        printf("   [ x2 ]\n");
        printf("   [ x1 ]\n");
        printf("    ---\n\n");

        printf("Pseudocodigo:\n");
        printf("   push(S, x):\n");
        printf("       S[top+1] <- x\n");
        printf("       top <- top + 1   // O(1)\n\n");
        printf("   pop(S):\n");
        printf("       pre: top >= 0\n");
        printf("       x <- S[top]\n");
        printf("       top <- top - 1   // O(1)\n");
        printf("       return x\n\n");

        printf("Ejemplo (deshacer operaciones de edicion):\n");
        printf("   // cada accion se apila; al deshacer se hace pop.\n\n");
        break;

    case DS_QUEUE:
        printf("Estructura recomendada: COLA (QUEUE)\n\n");
        printf("Por que:\n");
        printf("- Procesas elementos en orden de llegada (FIFO).\n");
        printf("- Tipico en colas de impresion, tareas en un servidor, etc.\n\n");

        printf("Diagrama (array circular):\n");
        printf(" front -> [ a1 ][ a2 ][ a3 ] <- rear\n\n");

        printf("Pseudocodigo:\n");
        printf("   enqueue(Q, x):\n");
        printf("       rear <- (rear + 1) mod cap\n");
        printf("       Q[rear] <- x\n");
        printf("       size <- size + 1\n\n");
        printf("   dequeue(Q):\n");
        printf("       pre: size > 0\n");
        printf("       x <- Q[front]\n");
        printf("       front <- (front + 1) mod cap\n");
        printf("       size <- size + 1\n");
        printf("       return x\n\n");

        printf("Ejemplo (cola de impresion):\n");
        printf("   // cada documento entra al final y sale por el frente.\n\n");
        break;

    case DS_BST:
        printf("Estructura recomendada: ARBOL BINARIO DE BUSQUEDA (BST)\n\n");
        printf("Por que:\n");
        printf("- Necesitas datos ordenados y busquedas rapidas (O(log n)).\n");
        printf("- No hay muchos duplicados.\n\n");

        printf("Diagrama:\n");
        printf("        (root)\n");
        printf("        [ 8 ]\n");
        printf("       /     \\\n");
        printf("    [ 3 ]   [ 10 ]\n");
        printf("    /  \\       \\\n");
        printf(" [1]  [6]     [14]\n\n");

        printf("Pseudocodigo (buscar):\n");
        printf("   search(node, key):\n");
        printf("       if node == NULL: return NOT_FOUND\n");
        printf("       if key == node.key: return node\n");
        printf("       if key < node.key: return search(node.left, key)\n");
        printf("       else: return search(node.right, key)\n\n");

        printf("Ejemplo (busqueda de matricula de estudiante):\n");
        printf("   // cada insercion mantiene el arbol ordenado por matricula.\n\n");
        break;

    case DS_HEAP:
        printf("Estructura recomendada: HEAP / PRIORITY QUEUE\n\n");
        printf("Por que:\n");
        printf("- Importa mas la prioridad que el orden de llegada.\n");
        printf("- Necesitas extraer siempre el maximo o minimo rapido.\n\n");

        printf("Diagrama (max-heap en arreglo):\n");
        printf("   index: 0  1  2  3  4  5\n");
        printf("   valor: 50 30 40 10 20 35\n");
        printf("   // padre(i) = (i-1)/2\n\n");

        printf("Pseudocodigo (insert):\n");
        printf("   insert(heap, x):\n");
        printf("       heap[last] <- x\n");
        printf("       reHeapUp(last)   // intercambiar con padre mientras sea mayor\n");
        printf("       last <- last + 1\n\n");

        printf("Ejemplo (cola de procesos con prioridad):\n");
        printf("   // siempre se atiende primero el proceso con prioridad mas alta.\n\n");
        break;

    case DS_GRAPH:
        printf("Estructura recomendada: GRAFO (lista o matriz de adyacencia)\n\n");
        printf("Por que:\n");
        printf("- Hay relaciones de tipo red (nodos conectados con muchos otros).\n");
        printf("- Necesitas recorridos como BFS/DFS.\n\n");

        printf("Diagrama (lista de adyacencia):\n");
        printf("   A: B -> C\n");
        printf("   B: A -> D\n");
        printf("   C: A\n");
        printf("   D: B\n\n");

        printf("Pseudocodigo (BFS):\n");
        printf("   BFS(G, s):\n");
        printf("       crear cola Q\n");
        printf("       marcar s como visitado y encolar s\n");
        printf("       mientras Q no vacia:\n");
        printf("           u <- desencolar\n");
        printf("           para cada vecino v de u:\n");
        printf("               si v no visitado:\n");
        printf("                   marcar v y encolar v\n\n");

        printf("Ejemplo (red de ciudades y carreteras):\n");
        printf("   // busca ruta minima en numero de aristas.\n\n");
        break;

    case DS_TRIE:
        printf("Estructura recomendada: TRIE (ARBOLES DE PREFIJOS)\n\n");
        printf("Por que:\n");
        printf("- Necesitas buscar por prefijo en cadenas (autocompletar, diccionario).\n");
        printf("- Muchas palabras comparten comienzos iguales.\n\n");

        printf("Diagrama (prefijos):\n");
        printf("   (root)\n");
        printf("     |\n");
        printf("     c\n");
        printf("    / \\\n");
        printf("   a   o\n");
        printf("   |   |\n");
        printf("   t   d\n");
        printf("  (cat) (cod)\n\n");

        printf("Pseudocodigo (insertar palabra):\n");
        printf("   insert(root, word):\n");
        printf("       node <- root\n");
        printf("       para cada caracter c en word:\n");
        printf("           si node.noTieneHijo(c):\n");
        printf("               node.crearHijo(c)\n");
        printf("           node <- node.hijo(c)\n");
        printf("       marcar node como finDePalabra\n\n");

        printf("Ejemplo (autocompletar en un buscador):\n");
        printf("   // el trie permite listar todas las palabras con cierto prefijo.\n\n");
        break;

    default:
        printf("No se pudo determinar una estructura clara.\n");
        printf("Revisa las respuestas o ajusta las reglas.\n");
        break;
    }
}

int main(void) {
    printf("=============================================\n");
    printf(" SISTEMA GUIADO DE DECISION DE ESTRUCTURAS\n");
    printf("=============================================\n\n");

    printf("Responde las siguientes preguntas con 1 (si) o 0 (no).\n\n");

    int needRandomAccess   = askYesNo("1) Necesitas acceso rapido por indice (arr[i]) con frecuencia?");
    int manyMiddleInserts  = askYesNo("2) Haras muchas inserciones/borrados en medio de la coleccion?");
    int lifoProcessing     = askYesNo("3) El procesamiento es tipo LIFO (ultimo en entrar, primero en salir)?");
    int fifoProcessing     = askYesNo("4) El procesamiento es tipo FIFO (primero en entrar, primero en salir)?");
    int needPriority       = askYesNo("5) Importa una prioridad (siempre atender el mas grande/importante primero)?");
    int dynamicSize        = askYesNo("6) El tamano de los datos es dinamico o no conocido al inicio?");
    int graphRelationships = askYesNo("7) Hay relaciones tipo red/ grafo entre los elementos?");
    int prefixSearch       = askYesNo("8) Necesitas buscar por prefijos en cadenas (autocompletar)?");

    int chosen = decideStructure(
        needRandomAccess,
        manyMiddleInserts,
        lifoProcessing,
        fifoProcessing,
        needPriority,
        dynamicSize,
        graphRelationships,
        prefixSearch
    );

    showRecommendation(chosen);

    printf("Fin del programa.\n");
    return 0;
}
