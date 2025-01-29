#include <stdio.h>
#include <stdlib.h>

struct NOD {
    int value;
    struct NOD *left, *right;
};

struct NOD* creeaza_nod(int valoare, struct NOD* stanga, struct NOD* dreapta) {
    struct NOD* nou = (struct NOD*)malloc(sizeof(struct NOD));
    nou->value = valoare;
    nou->left = stanga;
    nou->right = dreapta;
    return nou;
}


void sortare(int *v, int dim) {
    for (int i = 0; i < dim - 1; i++) {
        for (int j = i + 1; j < dim; j++) {
            if (v[i] > v[j]) {
                int temp = v[i];
                v[i] = v[j];
                v[j] = temp;
            }
        }
    }
}


struct NOD* construieste_heap(int *v, int n) {
    struct NOD **heap = (struct NOD**)malloc(n * sizeof(struct NOD*));

    //fiecare element devine un nod de frunza
    for (int i = 0; i < n; i++) {
        heap[i] = creeaza_nod(v[i], NULL, NULL);
    }

    int dim = n;
    while (dim > 1) {
        struct NOD *stanga = heap[0];
        struct NOD *dreapta = heap[1];
        int suma = stanga->value + dreapta->value;

        struct NOD *parinte = creeaza_nod(suma, stanga, dreapta);


        heap[1] = parinte;

        //shiftare la stanga
        for (int i = 0; i < dim - 1; i++) {
            heap[i] = heap[i + 1];
        }

        dim--; 
        ///sortarea nodurilor
        for (int i = 0; i < dim ; i++) {
            for (int j = i + 1; j < dim; j++) {
                if (heap[i]->value > heap[j]->value) {
                    struct NOD *temp = heap[i];
                    heap[i] = heap[j];
                    heap[j] = temp;
                }
            }
        }
    }

    struct NOD* root = heap[0];
    free(heap);
    return root;
}

void preordine(struct NOD* root) {
    if (root == NULL) return;
    printf("%d\n", root->value);
    preordine(root->left);
    preordine(root->right);
}

int main() {
    int n;

    scanf("%d", &n);
    int *v = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }
    sortare(v, n);
    struct NOD* root = construieste_heap(v, n);
    preordine(root);
    free(v);
    return 0;
}
