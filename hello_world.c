#include <stdio.h>
#include <stdlib.h>

enum Colour {
    UNCOLOURED,
    WHITE,
    BLACK
};

enum MatchState {
    IN_PROGRESS,
    WHITE_WIN,
    BLACK_WIN,
    DRAW
};

struct Vertex {
    struct Vertex **neighbours;
    int n_n; // number of neighbours
    enum Colour colour;
    int id;
};

struct Vertex *createVertices(int n_v);
void freeVertices(struct Vertex *vertices, int n_v);

void makeNeighbours(struct Vertex *vertices, int u, int v);
void colourVertex(struct Vertex *vertices, int i, enum Colour colour);
void showVertices(struct Vertex *v, int n_v);

void playGame(struct Vertex *vertices, int n_v);
int getMove(struct Vertex *vertices, int n_v, enum Colour colour);
void makeMove(struct Vertex *vertices, int position, enum Colour colour);
enum MatchState checkWin(struct Vertex *vertices, int n_v);
void printGameResult(enum MatchState state);


void quickTest(void);
void quickTest2(void);

int main(int argc, char *argv[]) {
    /*
	printf("Hello, world!\n");
    quickTest();
    printf("\n");
    quickTest2();
    printf("\n");
    */

    FILE *fp = stdin;

    if(argc > 1) {
        fp = fopen(argv[1], "r");
        if(!fp) {
            printf("Could not open file\n");
            exit(1);
        }
    }

    // number of vertices
    int n_v;

    fscanf(fp, "%d", &n_v);

    struct Vertex * vertices = createVertices(n_v);


    for(int i = 0; i < n_v - 1; i++){
        int u, v;
        fscanf(fp, "%d %d\n", &u, &v);
        makeNeighbours(vertices, u, v);
    }

    char *chars = malloc((n_v + 1) * sizeof(char));

    fgets(chars, n_v + 1, fp);
    printf("%s\n", chars);

    for(int i = 0; i < n_v; i++) {
        switch (chars[i]) {
            case 'W' :
                colourVertex(vertices, i, WHITE);
                break;
        }
    } 
    free(chars);

    showVertices(vertices, n_v);

    playGame(vertices, n_v);

    freeVertices(vertices, n_v);

    if(fp != stdin) {
        fclose(fp);
    }

	return 0;
}

void playGame(struct Vertex *vertices, int n_v) {

    int position;

    enum Colour colour = WHITE;

    enum MatchState state;

    while((state = checkWin(vertices, n_v)) == IN_PROGRESS) {

        position = getMove(vertices, n_v, colour);
        makeMove(vertices, position, colour);

        showVertices(vertices, n_v);

        colour = (colour == WHITE) ? BLACK : WHITE;
    }

    printGameResult(state);
    
}

void printGameResult(enum MatchState state){
    switch (state) {
        case WHITE_WIN :
            printf("Player White wins!\n");
            break;
        case BLACK_WIN :
            printf("Player Black wins!\n");
            break;
        case DRAW :
            printf("Game has ended in a draw!\n");
            break;
        default : break;
    }
}

enum MatchState checkWin(struct Vertex *vertices, int n_v) {

    enum MatchState state = DRAW;

    for(int i = 0; i < n_v; i++) {

        struct Vertex *curr = &vertices[i];

        enum Colour check = curr->colour;
        if(check == UNCOLOURED) {
            state = IN_PROGRESS;
            continue;
        }

        int count = 0;
        for(int i = 0; i < curr->n_n; i++) {
            if(curr->neighbours[i]->colour == check) {
                count++;
            }
        }

        if(count >= 2){
            switch (check) {
                case WHITE :
                    return WHITE_WIN;
                case BLACK :
                    return BLACK_WIN;
                default :
                    printf("Shouldnt be here\n");
                    exit(1);
            }
        }
    }

    return state;
}

int getMove(struct Vertex *vertices, int n_v, enum Colour colour){

    int r;

    while(1) {
        scanf("%d", &r);

        if (vertices[r - 1].colour == UNCOLOURED) {
            break;
        }

        printf("coloured in already, choose another\n");
    } 

    return r;
}

void makeMove(struct Vertex *vertices, int position, enum Colour colour) {

    vertices[position - 1].colour = colour;

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

void colourVertex(struct Vertex *vertices, int i, enum Colour colour) {
    vertices[i].colour = colour;
}

void showVertex(struct Vertex *v) {
    printf("c-%d, ", v->colour);
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

void freeVertices(struct Vertex *vertices, int n_v){

    for(int i = 0; i < n_v; i++){
        free(vertices[i].neighbours);
    }
    free(vertices);

}

void quickTest(void) {

    struct Vertex * v = createVertices(4);
    makeNeighbours(v, 1, 2);
    makeNeighbours(v, 1, 3);
    makeNeighbours(v, 1, 4);

    colourVertex(v, 0, UNCOLOURED);
    colourVertex(v, 1, UNCOLOURED);
    colourVertex(v, 2, UNCOLOURED);
    colourVertex(v, 3, WHITE);

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

    int position = getMove(v, n, WHITE);
    makeMove(v, position, WHITE);

    showVertices(v, n);

}
