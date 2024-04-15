#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Vertex {
    float x, y;
};


bool aux = false, aux2 = false;

void drawBezierCurve(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3) {
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= 100; i++) {
        float t = i / 100.0f;
        float x = pow(1 - t, 3) * (x0/2) + 3 * t * pow(1 - t, 2) * (x1/2) + 3 * pow(t, 2) * (1 - t) * (x2/2) + pow(t, 3) * (x3/2);
        float y = pow(1 - t, 3) * (y0/2) + 3 * t * pow(1 - t, 2) * (y1/2) + 3 * pow(t, 2) * (1 - t) * (y2/2) + pow(t, 3) * (y3/2);
        glVertex2d(x, y);
    }
    glEnd();
}

bool loadObj(const char* filename, std::vector<Vertex>& vertices) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo.\n";
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.substr(0, 2) == "v ") {
            Vertex vertex;
            sscanf_s(line.c_str(), "v %f %f", &vertex.x, &vertex.y);
            vertices.push_back(vertex);
        }
    }

    file.close();
    return true;
}


static void teclado(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    if (key == GLFW_KEY_A && action == GLFW_PRESS) {
        aux = !aux;
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main(void)
{
    std::vector<Vertex> vertices;
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280, 720, "Desenho do gatinho", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetWindowPos(window, 50, 100);


    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        /* Render here */
          // Desenhe os eixos X e Y
            glBegin(GL_LINES);
            // Eixo X (verde)
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex2f(-1.0f, 0.0f);
            glVertex2f(1.0f, 0.0f);
            // Eixo Y (azul)
            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex2f(0.0f, -1.0f);
            glVertex2f(0.0f, 1.0f);
            glEnd();
  

    // Define os pontos de controle da curva de Bézier
    float x0 = 0.19f, y0 = -0.47f;
    float x1 = 0.61f, y1 = -0.45f;
    float x2 = 0.75f, y2 = -0.03f;
    float x3 = 0.55f, y3 = 0.3f;

    if (!aux) {
        glBegin(GL_LINE_STRIP);
        glColor3f(1.0f, 0.0f, 1.0f);
        glVertex2f(x0 / 2, y0 / 2);
        glVertex2f(x1 / 2, y1 / 2);
        glVertex2f(x2 / 2, y2 / 2);
        glVertex2f(x3 / 2, y3 / 2);
        glEnd();
    }
    else{
        drawBezierCurve(x0, y0, x1, y1, x2, y2, x3, y3);//Primeira curva
    }

    x0 =x3, x1 =0.44f, x2 =0.60f ,x3 = 0.26f, y0 =y3, y1 = 0.57f, y2 = 0.70f, y3 = 0.46f;
    if (!aux) {
        glBegin(GL_LINE_STRIP);
        glColor3f(1.0f, 0.0f, 1.0f);
        glVertex2f(x0 / 2, y0 / 2);
        glVertex2f(x1 / 2, y1 / 2);
        glVertex2f(x2 / 2, y2 / 2);
        glVertex2f(x3 / 2, y3 / 2);
        glEnd();
    }
    else {
        drawBezierCurve(x0, y0, x1, y1, x2, y2, x3, y3);//Segunda curva
    }

    x0 = 0.19f, y0 = -0.47f , x1 = 0.43f, x2 = -0.08f, x3 = 0.76f, y1 = -0.80f, y2 = -1.30f, y3 = -0.69f;
    if (!aux) {
        glBegin(GL_LINE_STRIP);
        glColor3f(1.0f, 0.0f, 1.0f);
        glVertex2f(x0 / 2, y0 / 2);
        glVertex2f(x1 / 2, y1 / 2);
        glVertex2f(x2 / 2, y2 / 2);
        glVertex2f(x3 / 2, y3 / 2);
        glEnd();
    }
    
    else{
        drawBezierCurve(x0, y0, x1, y1, x2, y2, x3, y3);//Terceira
    }

    x0 = x3, y0 = y3, x1 = 1.16f, y1 = -0.31f, x2 = 1.12f, y2 = 0.94f, x3 = 0.0f, y3 = 0.97f;
    if (!aux) {
        glBegin(GL_LINE_STRIP);
        glColor3f(1.0f, 0.0f, 1.0f);
        glVertex2f(x0 / 2, y0 / 2);
        glVertex2f(x1 / 2, y1 / 2);
        glVertex2f(x2 / 2, y2 / 2);
        glVertex2f(x3 / 2, y3 / 2);
        glEnd();
    }
    
    else {
        drawBezierCurve(x0, y0, x1, y1, x2, y2, x3, y3);//Quarta
    }


    x0 = 0.26f, y0 = 0.46f, x1 = 0.11f, y1 = 0.50f, x2 = -0.07f, y2 = 0.51f, x3 = -0.25f, y3 = 0.46f;
    if (!aux) {
        glBegin(GL_LINE_STRIP);
        glColor3f(1.0f, 0.0f, 1.0f);
        glVertex2f(x0 / 2, y0 / 2);
        glVertex2f(x1 / 2, y1 / 2);
        glVertex2f(x2 / 2, y2 / 2);
        glVertex2f(x3 / 2, y3 / 2);
        glEnd();
    }
    
    else {
        drawBezierCurve(x0, y0, x1, y1, x2, y2, x3, y3);//Quinta
    }

    x0 = x3, y0 = y3, x1 = -0.51f, y1 = 0.63f, x2 = -0.61f, y2 = 0.62f, x3 = -0.54f, y3 = 0.30f;
    if (!aux) {
        glBegin(GL_LINE_STRIP);
        glColor3f(1.0f, 0.0f, 1.0f);
        glVertex2f(x0 / 2, y0 / 2);
        glVertex2f(x1 / 2, y1 / 2);
        glVertex2f(x2 / 2, y2 / 2);
        glVertex2f(x3 / 2, y3 / 2);
        glEnd();
    }
    
    else {
        drawBezierCurve(x0, y0, x1, y1, x2, y2, x3, y3);//Sexta
    }

    x0 = x3, y0 = y3, x1 = -0.73f, y1 = 0.30f, x2 = -0.66f, y2 = -0.45f, x3 = -0.19f, y3 = -0.46f;
    if (!aux) {
        glBegin(GL_LINE_STRIP);
        glColor3f(1.0f, 0.0f, 1.0f);
        glVertex2f(x0 / 2, y0 / 2);
        glVertex2f(x1 / 2, y1 / 2);
        glVertex2f(x2 / 2, y2 / 2);
        glVertex2f(x3 / 2, y3 / 2);
        glEnd();
    }
    
    else {
        drawBezierCurve(x0, y0, x1, y1, x2, y2, x3, y3);//Setima
    }

    x0 = x3, y0 = y3, x1 = -0.30f, y1 = -0.57f, x2 = -0.15f, y2 = -0.63f, x3 = -0.41f, y3 = -0.62f;
    if (!aux) {
        glBegin(GL_LINE_STRIP);
        glColor3f(1.0f, 0.0f, 1.0f);
        glVertex2f(x0 / 2, y0 / 2);
        glVertex2f(x1 / 2, y1 / 2);
        glVertex2f(x2 / 2, y2 / 2);
        glVertex2f(x3 / 2, y3 / 2);
        glEnd();
    }
    
    else {

        drawBezierCurve(x0, y0, x1, y1, x2, y2, x3, y3);//Oitava
    }

    x0 = x3, y0 = y3, x1 = -0.60f, y1 = -0.55f, x2 = -0.50f, y2 = -0.40f, x3 = -0.74f, y3 = -0.42f;
    if (!aux) {
        glBegin(GL_LINE_STRIP);
        glColor3f(1.0f, 0.0f, 1.0f);
        glVertex2f(x0 / 2, y0 / 2);
        glVertex2f(x1 / 2, y1 / 2);
        glVertex2f(x2 / 2, y2 / 2);
        glVertex2f(x3 / 2, y3 / 2);
        glEnd();
    }
    
    else {
        drawBezierCurve(x0, y0, x1, y1, x2, y2, x3, y3);//Nona
    }

    x0 = x3, y0 = y3, x1 = -0.52f, y1 = -0.57f, x2 = -0.64f, y2 = -0.72f, x3 = -0.36f, y3 = -0.76f;
    if (!aux) {
        glBegin(GL_LINE_STRIP);
        glColor3f(1.0f, 0.0f, 1.0f);
        glVertex2f(x0 / 2, y0 / 2);
        glVertex2f(x1 / 2, y1 / 2);
        glVertex2f(x2 / 2, y2 / 2);
        glVertex2f(x3 / 2, y3 / 2);
        glEnd();
    }
    
    else {
        drawBezierCurve(x0, y0, x1, y1, x2, y2, x3, y3);//Decima
    }

    x0 = x3, y0 = y3, x1 = -0.15f, y1 = -0.67f, x2 = -0.22f, y2 = -1.05f, x3 = -0.33f, y3 = -0.96f;
    if (!aux) {
        glBegin(GL_LINE_STRIP);
        glColor3f(1.0f, 0.0f, 1.0f);
        glVertex2f(x0 / 2, y0 / 2);
        glVertex2f(x1 / 2, y1 / 2);
        glVertex2f(x2 / 2, y2 / 2);
        glVertex2f(x3 / 2, y3 / 2);
        glEnd();
    }
    
    else {
        drawBezierCurve(x0, y0, x1, y1, x2, y2, x3, y3);//Decima primeira
    }

    x0 = 0.0f, y0 = 0.96f, x1 = -1.33f, y1 = 0.86f, x2 = -1.20f, y2 = -0.72f;
    if (!aux) {
        glBegin(GL_LINE_STRIP);
        glColor3f(1.0f, 0.0f, 1.0f);
        glVertex2f(x0 / 2, y0 / 2);
        glVertex2f(x1 / 2, y1 / 2);
        glVertex2f(x2 / 2, y2 / 2);
        glVertex2f(x3 / 2, y3 / 2);
        glEnd();
    }
    
    else {
        drawBezierCurve(x0, y0, x1, y1, x2, y2, x3, y3);//Decima segunda
    }

    if (loadObj("caminho_do_arquivo.obj", vertices)) {
        // Processar os dados
        for (const auto& vertex : vertices) {
            std::cout << "Vertex: " << vertex.x << ", " << vertex.y<< std::endl;
        }
    }

        /* Poll for and process events */
        glfwSwapBuffers(window);
        glfwPollEvents();
        glfwSetKeyCallback(window, teclado);

    }

    glfwTerminate();
    return 0;
}