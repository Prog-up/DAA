#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 256

// Structure for a Huffman tree node
struct MinHeapNode {
    char data; // One of the input characters
    int freq; // Frequency of the character
    struct MinHeapNode *left, *right; // Left and right child
};

// Structure for the priority queue
struct PriorityQueue {
    struct MinHeapNode **nodes;
    int size;
};

// To map each character to its Huffman value
char *codes[256];

// To store the frequency of characters in the input data
int freq[256] = {0};

// Function to create a new MinHeapNode
struct MinHeapNode* createNode(char data, int freq) {
    struct MinHeapNode* newNode = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    newNode->data = data;
    newNode->freq = freq;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to create a priority queue
struct PriorityQueue* createPriorityQueue() {
    struct PriorityQueue* pq = (struct PriorityQueue*)malloc(sizeof(struct PriorityQueue));
    pq->nodes = (struct MinHeapNode**)malloc(MAX_TREE_HT * sizeof(struct MinHeapNode*));
    pq->size = 0;
    return pq;
}

// Function to swap two min heap nodes
void swapNodes(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// Function to heapify the priority queue
void heapify(struct PriorityQueue* pq, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < pq->size && pq->nodes[left]->freq < pq->nodes[smallest]->freq)
        smallest = left;

    if (right < pq->size && pq->nodes[right]->freq < pq->nodes[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapNodes(&pq->nodes[smallest], &pq->nodes[idx]);
        heapify(pq, smallest);
    }
}

// Function to insert a node into the priority queue
void insertNode(struct PriorityQueue* pq, struct MinHeapNode* node) {
    pq->size++;
    int i = pq->size - 1;
    while (i && node->freq < pq->nodes[(i - 1) / 2]->freq) {
        pq->nodes[i] = pq->nodes[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    pq->nodes[i] = node;
}

// Function to remove the minimum node from the priority queue
struct MinHeapNode* removeMin(struct PriorityQueue* pq) {
    struct MinHeapNode* minNode = pq->nodes[0];
    pq->nodes[0] = pq->nodes[pq->size - 1];
    pq->size--;
    heapify(pq, 0);
    return minNode;
}

void buildHuffmanTree(int size, struct PriorityQueue* pq) {
    struct MinHeapNode *left, *right, *top;
    int count = 0; // Track the number of nodes in the priority queue
    
    // Build initial priority queue with nodes for characters with non-zero frequency
    for (int i = 0; i < 256; ++i) {
        if (freq[i] > 0) {
            insertNode(pq, createNode((char)i, freq[i]));
            count++;
        }
    }
    
    // Ensure there are at least two nodes in the priority queue
    if (count < 2) {
        fprintf(stderr, "Error: Insufficient characters with non-zero frequency.\n");
        exit(EXIT_FAILURE);
    }

    // Build Huffman tree until there is only one node in the priority queue
    while (pq->size > 1) {
        left = removeMin(pq);
        right = removeMin(pq);
        top = createNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertNode(pq, top);
    }
}


// Function to print characters along with their Huffman value
void printCodes(struct MinHeapNode* root, char* str, int top) {
    if (root->left) {
        str[top] = '0';
        printCodes(root->left, str, top + 1);
    }
    if (root->right) {
        str[top] = '1';
        printCodes(root->right, str, top + 1);
    }
    if (!root->left && !root->right) {
        str[top] = '\0';
        codes[(unsigned char)root->data] = strdup(str);
    }
}

// Function to decode the Huffman-encoded string
char* decodeFile(struct MinHeapNode* root, char* encodedString) {
    char* decodedString = (char*)malloc(256 * sizeof(char));
    struct MinHeapNode* current = root;
    int index = 0;
    for (int i = 0; encodedString[i]; ++i) {
        if (encodedString[i] == '0') {
            current = current->left;
        } else {
            current = current->right;
        }
        if (current->left == NULL && current->right == NULL) {
            decodedString[index++] = current->data;
            current = root;
        }
    }
    decodedString[index] = '\0';
    return decodedString;
}
// Function to calculate the frequency of each character in the input string
void calcFreq(char* str) {
    while (*str) {
        freq[(unsigned char)*str]++;
        str++;
    }
}

void writeEncodedText(FILE* fout, char* encodedText) {
    fprintf(fout, "%s", encodedText);
}


// Driver code
int main() {
    // Ouverture du fichier d'entrée
    FILE* fin = fopen("input.txt", "r");
    if (!fin) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    // Lecture du contenu du fichier
    char str[1000];
    fgets(str, sizeof(str), fin);

    calcFreq(str);
    printf("%s\n", str);
    int n = strlen(str);
    struct PriorityQueue* pq = createPriorityQueue();
    buildHuffmanTree(n, pq);
    printCodes(pq->nodes[0], (char*)malloc(MAX_TREE_HT * sizeof(char)), 0);

    printf("Character With their Frequencies:\n");
    for (int i = 0; i < 256; ++i) {
        if (codes[i]) {
            printf("%c %s\n", i, codes[i]);
        }
    }
    char *encodedString = (char *)malloc((strlen(str) * 999999 + 1) * sizeof(char));
    encodedString[0] = '\0'; // Assurez-vous que la chaîne est correctement terminée

    // Concaténer les chaînes dans encodedString
    for (int i = 0; i < strlen(str); ++i) {
        strcat(encodedString, codes[(unsigned char)str[i]]);
    }

    FILE* fout_encoded = fopen("encoded_output.txt", "w");
    if (!fout_encoded) {
        perror("Error opening encoded output file");
        free(pq);
        return EXIT_FAILURE;
    }
    writeEncodedText(fout_encoded, encodedString);
    fclose(fout_encoded);
    printf("\nEncoded Huffman data:\n%s\n", encodedString);

    char* decodedString = decodeFile(pq->nodes[0], encodedString);
    FILE* fout_decoded = fopen("decoded_output.txt", "w");
    if (!fout_decoded) {
        perror("Error opening encoded output file");
        free(pq);
        return EXIT_FAILURE;
    }
    writeEncodedText(fout_decoded, decodedString);
    fclose(fout_decoded);
    printf("\nDecoded Huffman Data:\n%s\n", decodedString);

    free(pq);
    free(decodedString);
    free(encodedString);


    return 0;
}
