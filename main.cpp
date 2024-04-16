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

struct translate {
    float x, y;
};

struct rotate {
    float x, y;
};

struct scale {
    float x, y;
};

struct cisa {
    float x,y;
};


bool aux = false, aux2 = false, aux3 = true;



void drawBezierCurve(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3) {
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= 100; i++) {
        float t = i / 100.0f;
        float x = pow(1 - t, 3) * (x0) + 3 * t * pow(1 - t, 2) * (x1) + 3 * pow(t, 2) * (1 - t) * (x2) + pow(t, 3) * (x3);
        float y = pow(1 - t, 3) * (y0) + 3 * t * pow(1 - t, 2) * (y1) + 3 * pow(t, 2) * (1 - t) * (y2) + pow(t, 3) * (y3);
        glVertex2d(x, y);
    }
    glEnd();
}

bool loadObj(const char* filename, std::vector<Vertex>& vertices, std::vector<int>& transformacao,std::vector<translate>& translacao,std::vector<rotate>& rotacao, std::vector<scale>& escala,std::vector<cisa>& cisalhamento) {
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
            vertex.x = vertex.x / 2;
            vertex.y = vertex.y / 2;
            vertices.push_back(vertex);
        }
        else if (line.substr(0, 2) == "t ") {
            translate trans;
            sscanf_s(line.c_str(), "t %f %f", &trans.x, &trans.y);
            transformacao.push_back(1);
            translacao.push_back(trans);
        }
        else if (line.substr(0, 2) == "r ") {
            rotate rot;
            sscanf_s(line.c_str(), "r %f", &rot.x);
            transformacao.push_back(2);
            rotacao.push_back(rot);
        }
        else if (line.substr(0, 2) == "s ") {
            scale esc;
            sscanf_s(line.c_str(), "s %f %f", &esc.x, &esc.y);
            transformacao.push_back(3);
            escala.push_back(esc);
        }
        else if (line.substr(0, 2) == "c ") {
            cisa c;
            sscanf_s(line.c_str(), "c %f %f", &c.x, &c.y);
            transformacao.push_back(4);
            cisalhamento.push_back(c);
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
    std::vector<int> transformacao;
    std::vector<translate> translacao;
    std::vector<rotate> rotacao;
    std::vector<scale> escala;
    std::vector<cisa> cisalhamento;

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

    if (loadObj("C:/Users/vanpe/source/repos/teste1/gato.obj", vertices, transformacao, translacao, rotacao, escala, cisalhamento)) {
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

                        // Processar os dados
            if (!aux) {
                glBegin(GL_LINE_STRIP);
                glColor3f(1.0f, 0.0f, 1.0f);
                for (int i = 1; i < vertices.size(); i += 3) {
                    glVertex2f(vertices[i - 1].x, vertices[i - 1].y);
                    glVertex2f(vertices[i].x, vertices[i].y);
                    glVertex2f(vertices[i + 1].x, vertices[i + 1].y);
                    glVertex2f(vertices[i + 2].x, vertices[i + 2].y);
                }
                glEnd();
            }
            else {
                for (int i = 1; i < vertices.size(); i += 3) {
                    drawBezierCurve(vertices[i - 1].x, vertices[i - 1].y, vertices[i].x, vertices[i].y, vertices[i + 1].x, vertices[i + 1].y, vertices[i + 2].x, vertices[i + 2].y);
                }
            }


            /* Poll for and process events */
            glfwSwapBuffers(window);
            glfwPollEvents();
            glfwSetKeyCallback(window, teclado);
        }

        glfwTerminate();
    }
    return 0;
}