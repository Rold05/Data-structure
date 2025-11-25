const readline = require("readline");

const DS_ARRAY_STATIC  = 1;
const DS_ARRAY_DYNAMIC = 2;
const DS_LINKED_LIST   = 3;
const DS_STACK         = 4;
const DS_QUEUE         = 5;
const DS_BST           = 6;
const DS_HEAP          = 7;
const DS_GRAPH         = 8;
const DS_TRIE          = 9;

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

function askYesNo(question) {
  return new Promise((resolve) => {
    const ask = () => {
      rl.question(`${question} (1 = si, 0 = no): `, (answer) => {
        if (answer === "1") return resolve(1);
        if (answer === "0") return resolve(0);
        console.log("Ingresa 1 o 0.");
        ask();
      });
    };
    ask();
  });
}

function decideStructure(
  needRandomAccess,
  manyMiddleInserts,
  lifoProcessing,
  fifoProcessing,
  needPriority,
  dynamicSize,
  graphRelationships,
  prefixSearch
) {
  if (graphRelationships) return DS_GRAPH;
  if (prefixSearch) return DS_TRIE;
  if (needPriority) return DS_HEAP;
  if (lifoProcessing) return DS_STACK;
  if (fifoProcessing) return DS_QUEUE;
  if (needRandomAccess && dynamicSize && !manyMiddleInserts) return DS_ARRAY_DYNAMIC;
  if (manyMiddleInserts && dynamicSize) return DS_LINKED_LIST;
  if (!dynamicSize && needRandomAccess) return DS_ARRAY_STATIC;
  return DS_BST;
}

function showRecommendation(dsId) {
  console.log("\n==============================");
  console.log(" RECOMENDACION FINAL");
  console.log("==============================\n");

  switch (dsId) {
    case DS_ARRAY_STATIC:
      console.log("Estructura recomendada: ARREGLO ESTATICO\n");
      console.log("Acceso rapido por indice y tamano fijo.\n");
      console.log("[0] [1] [2] [3] [4]\n");
      console.log("function get(A,i) -> A[i]");
      console.log("function set(A,i,x) -> A[i] = x\n");
      break;

    case DS_ARRAY_DYNAMIC:
      console.log("Estructura recomendada: ARREGLO DINAMICO\n");
      console.log("Crece segun necesidad y permite acceso directo.\n");
      console.log("ptr -> [0] [1] [2] ... [cap-1]\n");
      console.log("pushBack(x) si cap==n -> redimensionar\n");
      break;

    case DS_LINKED_LIST:
      console.log("Estructura recomendada: LISTA LIGADA\n");
      console.log("Inserciones y eliminaciones frecuentes en medio.\n");
      console.log("head -> [dato|*] -> [dato|*] -> NULL\n");
      console.log("insertAfter(p,x) en O(1)\n");
      break;

    case DS_STACK:
      console.log("Estructura recomendada: PILA (STACK)\n");
      console.log("LIFO.\n");
      console.log("top");
      console.log("[ x3 ]");
      console.log("[ x2 ]");
      console.log("[ x1 ]\n");
      break;

    case DS_QUEUE:
      console.log("Estructura recomendada: COLA (QUEUE)\n");
      console.log("FIFO.\n");
      console.log("front -> [ a1 ][ a2 ] <- rear\n");
      break;

    case DS_BST:
      console.log("Estructura recomendada: ARBOL BINARIO DE BUSQUEDA (BST)\n");
      console.log("Datos ordenados y busqueda eficiente.\n");
      console.log("        (8)");
      console.log("       /   \\");
      console.log("    (3)    (10)\n");
      break;

    case DS_HEAP:
      console.log("Estructura recomendada: HEAP / PRIORITY QUEUE\n");
      console.log("Extraer siempre el max/min rapidamente.\n");
      console.log("index: 0 1 2 3");
      console.log("valor:50 30 40 10\n");
      break;

    case DS_GRAPH:
      console.log("Estructura recomendada: GRAFO\n");
      console.log("Relaciones tipo red.\n");
      console.log("A: B, C");
      console.log("B: A, D\n");
      break;

    case DS_TRIE:
      console.log("Estructura recomendada: TRIE\n");
      console.log("Busqueda por prefijo.\n");
      console.log("(root) - t - o - p\n");
      break;

    default:
      console.log("No hay coincidencias claras.\n");
  }

  console.log("Fin del programa.");
}

async function main() {
  console.log("=============================================");
  console.log(" SISTEMA GUIADO DE DECISION DE ESTRUCTURAS");
  console.log("=============================================\n");

  const needRandomAccess = await askYesNo("Acceso rápido por indice?");
  const manyMiddleInserts = await askYesNo("Muchas inserciones en medio?");
  const lifoProcessing = await askYesNo("LIFO?");
  const fifoProcessing = await askYesNo("FIFO?");
  const needPriority = await askYesNo("Importa prioridad?");
  const dynamicSize = await askYesNo("Tamaño dinamico?");
  const graphRelationships = await askYesNo("Relaciones tipo grafo?");
  const prefixSearch = await askYesNo("Busqueda por prefijo?");

  const chosen = decideStructure(
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
  rl.close();
}

main();
