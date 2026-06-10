#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define HEIGHT 25
#define WIDTH 80
#define MAX_SHAPES 100

typedef enum { LINE = 1, RECTANGLE, CIRCLE, TRIANGLE } ShapeType;

typedef struct {
    ShapeType type;
    int x1, y1;
    int x2, y2;
    int x3, y3; // For triangle
    int radius; // For circle
} Shape;

char canvas[HEIGHT][WIDTH];
Shape shapes[MAX_SHAPES];
int shape_count = 0;

void clear_canvas() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            canvas[i][j] = '_';
        }
    }
}

void put_pixel(int x, int y) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        canvas[y][x] = '*';
    }
}

// Bresenham's Line Algorithm
void draw_line(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
    int dy = -abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
    int err = dx + dy, e2;

    while (1) {
        put_pixel(x1, y1);
        if (x1 == x2 && y1 == y2) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x1 += sx; }
        if (e2 <= dx) { err += dx; y1 += sy; }
    }
}

// Midpoint Circle Algorithm
void draw_circle(int xc, int yc, int r) {
    int x = 0, y = r;
    int d = 3 - 2 * r;
    while (y >= x) {
        put_pixel(xc + x, yc + y);
        put_pixel(xc - x, yc + y);
        put_pixel(xc + x, yc - y);
        put_pixel(xc - x, yc - y);
        put_pixel(xc + y, yc + x);
        put_pixel(xc - y, yc + x);
        put_pixel(xc + y, yc - x);
        put_pixel(xc - y, yc - x);
        x++;
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }
    }
}

void draw_rectangle(int x1, int y1, int x2, int y2) {
    draw_line(x1, y1, x2, y1);
    draw_line(x2, y1, x2, y2);
    draw_line(x2, y2, x1, y2);
    draw_line(x1, y2, x1, y1);
}

void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    draw_line(x1, y1, x2, y2);
    draw_line(x2, y2, x3, y3);
    draw_line(x3, y3, x1, y1);
}

void render_all() {
    clear_canvas();
    for (int i = 0; i < shape_count; i++) {
        switch (shapes[i].type) {
            case LINE:
                draw_line(shapes[i].x1, shapes[i].y1, shapes[i].x2, shapes[i].y2);
                break;
            case RECTANGLE:
                draw_rectangle(shapes[i].x1, shapes[i].y1, shapes[i].x2, shapes[i].y2);
                break;
            case CIRCLE:
                draw_circle(shapes[i].x1, shapes[i].y1, shapes[i].radius);
                break;
            case TRIANGLE:
                draw_triangle(shapes[i].x1, shapes[i].y1, shapes[i].x2, shapes[i].y2, shapes[i].x3, shapes[i].y3);
                break;
        }
    }
}

void display_canvas() {
    printf("\nCanvas (%dx%d):\n", WIDTH, HEIGHT);
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            putchar(canvas[i][j]);
        }
        putchar('\n');
    }
}

void list_objects() {
    if (shape_count == 0) {
        printf("No objects in the picture.\n");
        return;
    }
    printf("\nObjects:\n");
    for (int i = 0; i < shape_count; i++) {
        printf("%d: ", i + 1);
        switch (shapes[i].type) {
            case LINE: printf("Line from (%d,%d) to (%d,%d)\n", shapes[i].x1, shapes[i].y1, shapes[i].x2, shapes[i].y2); break;
            case RECTANGLE: printf("Rectangle from (%d,%d) to (%d,%d)\n", shapes[i].x1, shapes[i].y1, shapes[i].x2, shapes[i].y2); break;
            case CIRCLE: printf("Circle at (%d,%d) with radius %d\n", shapes[i].x1, shapes[i].y1, shapes[i].radius); break;
            case TRIANGLE: printf("Triangle vertices (%d,%d), (%d,%d), (%d,%d)\n", shapes[i].x1, shapes[i].y1, shapes[i].x2, shapes[i].y2, shapes[i].x3, shapes[i].y3); break;
        }
    }
}

void add_object() {
    if (shape_count >= MAX_SHAPES) {
        printf("Maximum shapes reached!\n");
        return;
    }
    int choice;
    printf("\nAdd Object:\n");
    printf("1. Line\n2. Rectangle\n3. Circle\n4. Triangle\nChoice: ");
    scanf("%d", &choice);

    Shape s;
    s.type = (ShapeType)choice;
    switch (choice) {
        case 1:
        case 2:
            printf("Enter x1 y1 x2 y2: ");
            scanf("%d %d %d %d", &s.x1, &s.y1, &s.x2, &s.y2);
            break;
        case 3:
            printf("Enter cx cy radius: ");
            scanf("%d %d %d", &s.x1, &s.y1, &s.radius);
            break;
        case 4:
            printf("Enter x1 y1 x2 y2 x3 y3: ");
            scanf("%d %d %d %d %d %d", &s.x1, &s.y1, &s.x2, &s.y2, &s.x3, &s.y3);
            break;
        default:
            printf("Invalid choice.\n");
            return;
    }
    shapes[shape_count++] = s;
    render_all();
}

void delete_object() {
    list_objects();
    if (shape_count == 0) return;
    int index;
    printf("Enter object index to delete: ");
    scanf("%d", &index);
    if (index < 1 || index > shape_count) {
        printf("Invalid index.\n");
        return;
    }
    for (int i = index - 1; i < shape_count - 1; i++) {
        shapes[i] = shapes[i + 1];
    }
    shape_count--;
    render_all();
}

void modify_object() {
    list_objects();
    if (shape_count == 0) return;
    int index;
    printf("Enter object index to modify: ");
    scanf("%d", &index);
    if (index < 1 || index > shape_count) {
        printf("Invalid index.\n");
        return;
    }
    Shape *s = &shapes[index - 1];
    switch (s->type) {
        case LINE:
        case RECTANGLE:
            printf("Enter new x1 y1 x2 y2: ");
            scanf("%d %d %d %d", &s->x1, &s->y1, &s->x2, &s->y2);
            break;
        case CIRCLE:
            printf("Enter new cx cy radius: ");
            scanf("%d %d %d", &s->x1, &s->y1, &s->radius);
            break;
        case TRIANGLE:
            printf("Enter new x1 y1 x2 y2 x3 y3: ");
            scanf("%d %d %d %d %d %d", &s->x1, &s->y1, &s->x2, &s->y2, &s->x3, &s->y3);
            break;
    }
    render_all();
}

int main() {
    int choice;
    clear_canvas();
    while (1) {
        printf("\n--- 2D Graphics Editor ---\n");
        printf("1. Add Object\n");
        printf("2. Delete Object\n");
        printf("3. Modify Object\n");
        printf("4. Display Picture\n");
        printf("5. Exit\n");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1: add_object(); break;
            case 2: delete_object(); break;
            case 3: modify_object(); break;
            case 4: display_canvas(); break;
            case 5: printf("Exiting...\n"); return 0;
            default: printf("Invalid choice.\n"); break;
        }
    }
    return 0;
}
