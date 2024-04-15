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


bool aux = false, aux2 = false, aux3 = true;

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
            vertex.x = (vertex.x*2) / 100;
            vertex.y = (vertex.y* 2) / 100;
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

    if (key == GLFW_KEY_P && action == GLFW_PRESS) {
        aux = !aux;
    }

    if(key == GLFW_KEY_A && action == GLFW_PRESS) {
        aux3 = !aux3;
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
            if (aux3) {
                float x0 = 0.19f, y0 = -0.47f;
                float x1 = 0.66f, y1 = -0.45f;
                float x2 = 0.73f, y2 = -0.07f;
                float x3 = 0.54f, y3 = 0.3f;

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
                    drawBezierCurve(x0, y0, x1, y1, x2, y2, x3, y3);//Primeira curva
                }

                x0 = x3, y0 = y3,
                    x1 = 0.60f, y1 = 0.64f,
                    x2 = 0.50f, y2 = 0.60f,
                    x3 = 0.25f, y3 = 0.46f;
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

                x0 = x3, y0 = y3,
                    x1 = 0.13f, y1 = 0.48f,
                    x2 = 0.01f, y2 = 0.52f,
                    x3 = -0.25f, y3 = 0.46f;
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
                    drawBezierCurve(x0, y0, x1, y1, x2, y2, x3, y3);//Terceira
                }

                x0 = x3, y0 = y3,
                    x1 = -0.50f, y1 = 0.60f,
                    x2 = -0.60f, y2 = 0.64f,
                    x3 = -0.54f, y3 = 0.30f;
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


                x0 = x3, y0 = y3,
                    x1 = -0.73f, y1 = 0.07f,
                    x2 = -0.66f, y2 = -0.45f,
                    x3 = -0.19f, y3 = -0.47f;
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

                x0 = x3, y0 = y3,
                    x1 = -0.28f, y1 = -0.56f,
                    x2 = -0.16f, y2 = -0.64f,
                    x3 = -0.42f, y3 = -0.62f;
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

                x0 = x3, y0 = y3,
                    x1 = -0.54f, y1 = -0.58f,
                    x2 = -0.53f, y2 = -0.39f,
                    x3 = -0.73f, y3 = -0.42f;
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

                x0 = x3, y0 = y3,
                    x1 = -0.77f, y1 = -0.45f,
                    x2 = -0.65f, y2 = -0.45f,
                    x3 = -0.56f, y3 = -0.67f;
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

                x0 = x3, y0 = y3,
                    x1 = -0.48f, y1 = -0.78f,
                    x2 = -0.32f, y2 = -0.75f,
                    x3 = -0.25f, y3 = -0.74f;
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

                x0 = x3, y0 = y3,
                    x1 = -0.26f, y1 = -0.90f,
                    x2 = -0.22f, y2 = -0.96f,
                    x3 = -0.30f, y3 = -0.98f;
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

                x0 = x3, y0 = y3,
                    x1 = -1.57f, y1 = -0.45f,
                    x2 = -0.91f, y2 = 1.02f,
                    x3 = 0.00f, y3 = 0.97f;
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

                x0 = x3, y0 = y3,
                    x1 = 0.91f, y1 = 1.02f,
                    x2 = 1.57f, y2 = -0.45f,
                    x3 = 0.30f, y3 = -0.98f;
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

                x0 = x3, y0 = y3,
                    x1 = 0.18f, y1 = -0.96f,
                    x2 = 0.32f, y2 = -0.67f,
                    x3 = 0.19f, y3 = -0.47f;
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
                    drawBezierCurve(x0, y0, x1, y1, x2, y2, x3, y3);//Decima terceira
                }

                

            }else {
                if (loadObj("C:/Users/vanpe/Downloads/exem.obj", vertices)) {
                    // Processar os dados
                    if (!aux) {
                        glBegin(GL_LINE_STRIP);
                        glColor3f(1.0f, 0.0f, 1.0f);
                        for (int i = 0; i < vertices.size(); i++) {
                            glVertex2f(((vertices[i].x/2)), ((vertices[i].y/2)));
                        }
                        glEnd();
                    }
                    else {
                        drawBezierCurve(vertices[0].x, vertices[0].y, vertices[1].x, vertices[1].y, vertices[2].x, vertices[2].y, vertices[3].x, vertices[3].y);
                    }
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