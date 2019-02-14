#include <stdio.h>
#include <stdlib.h>

struct Vertex *createVertices(int n_v);
void makeNeighbours(struct Vertex *vertices, int u, int v);

enum Colour {
    UNCOLOURED,
    BLACK,
    WHITE
};

struct Vertex {
    struct Vertex **neighbours;
    int n_n; // number of neighbours
    enum Colour colour;
    int id;
};

void quickTest(void);
void quickTest2(void);

int main(void) {
	printf("Hello, world!\n");
    quickTest();
    printf("\n");
    quickTest2();

    /*
    // number of vertices
    int n_v;

    scanf("%d", &n_v);

    struct Vertex * vertices = createVertices(n_v);


    for(int i = 0; i < n_v - 1; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        makeNeighbours(vertices, u, v);
    }
    */




	return 0;
}

struct Vertex *createVertices(int n_v) {

    // list of vertices
    struct Vertex * vertices = malloc(n_v * sizeof(struct Vertex));

    // setup each vertex
    for(int i = 0; i < n_v; i++){
        vertices[i].neighbours = calloc(n_v - 1, sizeof(struct Vertex *));
        vertices[i].n_n = 0;
        vertices[i].id = i+1;
        vertices[i].colour = UNCOLOURED;
    }

    return vertices;

}

void makeNeighbours(struct Vertex *vertices, int u, int v){

    struct Vertex *a = &vertices[u-1];
    struct Vertex *b = &vertices[v-1];
    a->neighbours[a->n_n++] = b;
    b->neighbours[b->n_n++] = a;
}

void showVertex(struct Vertex *v) {
    for(int i = 0; i < v->n_n; i++){
        printf("%d ", v->neighbours[i]->id);
    }

}

void showVertices(struct Vertex *v, int n_v) {

    int i = 0;
    for(struct Vertex *c = v; i < n_v; i++, c++) {
        printf("%d : ", i+1);
        showVertex(c);
        printf("\n");
    }

}

void quickTest(void) {

    struct Vertex * v = createVertices(4);
    makeNeighbours(v, 1, 2);
    makeNeighbours(v, 1, 3);
    makeNeighbours(v, 1, 4);

    showVertices(v, 4);

}

void quickTest2(void) {

    int n = 5;
    struct Vertex * v = createVertices(n);
    makeNeighbours(v, 1, 2);
    makeNeighbours(v, 2, 3);
    makeNeighbours(v, 3, 4);
    makeNeighbours(v, 4, 5);

    showVertices(v, n);

}
