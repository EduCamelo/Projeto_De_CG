#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

/*
    Alunos:
        - Matheus aroeira
        - Eduardo Camelo
        - Pedro queiroga
        - Loren gabriela
        - Evellyn Alane
        - Antonio Henrique
*/

//Estruturas para a plotagem de pontos e transformações
struct Vertex {
    float x, y;
};

struct Transforme {
    float x, y;
};



//Vars de controle global
bool aux = true, aux2 = false, aux3 = true;
int pimp = 0;

//Desenho de Bezier
void drawBezierCurve(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3) {
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= 100; i++) {
        float t = i / 100.0f;
        float x = pow(1 - t, 3) * (x0)+3 * t * pow(1 - t, 2) * (x1)+3 * pow(t, 2) * (1 - t) * (x2)+pow(t, 3) * (x3);
        float y = pow(1 - t, 3) * (y0)+3 * t * pow(1 - t, 2) * (y1)+3 * pow(t, 2) * (1 - t) * (y2)+pow(t, 3) * (y3);
        glVertex2d(x, y);
    }
    glEnd();
}

//Leitura do arquivo.obj
bool loadObj(std::string filename, std::vector<Vertex>& vertices, std::vector<int>& transformacao, std::vector<Transforme>& transforme) {
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
        else if (line.substr(0, 2) == "t ") {
            Transforme trans;
            sscanf_s(line.c_str(), "t %f %f", &trans.x, &trans.y);
            transformacao.push_back(1);
            transforme.push_back(trans);
        }
        else if (line.substr(0, 2) == "r ") {
            Transforme rot;
            sscanf_s(line.c_str(), "r %f", &rot.x);
            rot.y = 0;
            transformacao.push_back(2);
            transforme.push_back(rot);
        }
        else if (line.substr(0, 2) == "s ") {
            Transforme esc;
            sscanf_s(line.c_str(), "s %f %f", &esc.x, &esc.y);
            transformacao.push_back(3);
            transforme.push_back(esc);
        }
        else if (line.substr(0, 2) == "c ") {
            Transforme c;
            sscanf_s(line.c_str(), "c %f %f", &c.x, &c.y);
            transformacao.push_back(4);
            transforme.push_back(c);
        }
    }

    file.close();
    return true;
}

//Teclado e funções do teclado
static void teclado(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    if (key == GLFW_KEY_P && action == GLFW_PRESS) {
        aux = !aux;
    }

    if (key == GLFW_KEY_A && action == GLFW_PRESS) {
        aux3 = !aux3;
    }

    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        aux2 = !aux2;
    }

}

//Atualizando pontos
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

}


//Logica do desenho
void desenho(std::vector<Vertex> vertices) {
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
    for (int i = 1; i < vertices.size(); i += 3) {
        glColor3f(1.0f, 0.0f, 0.0f);
        drawBezierCurve(vertices[i - 1].x, vertices[i - 1].y, vertices[i].x, vertices[i].y, vertices[i + 1].x, vertices[i + 1].y, vertices[i + 2].x, vertices[i + 2].y);
    }
    glFlush();
}

void desenho2(std::vector<Vertex> vertices) {
    for (int i = 1; i < vertices.size(); i += 3) {
        glColor3f(0.0f, 1.0f, 1.0f);
        drawBezierCurve(vertices[i - 1].x, vertices[i - 1].y, vertices[i].x, vertices[i].y, vertices[i + 1].x, vertices[i + 1].y, vertices[i + 2].x, vertices[i + 2].y);
    }
    glFlush();
}

void translacaoAux(std::vector<Vertex>& transforme, float x, float y) {
    std::vector<Vertex> auxTransforme(transforme);
    transforme.clear();
    for (size_t i = 0; i < transforme.size(); i++)
    {
        Vertex pontosAux;
        pontosAux.x = auxTransforme[i].x + x;
        pontosAux.x = auxTransforme[i].y + y;
        transforme.push_back(pontosAux);
    }
}

//Logica do escala, 2d
void translacaoT(std::vector<Vertex>& transforme,float x, float y) {

    for (int i = 0; i < transforme.size(); ++i) {
        transforme[i].x = transforme[i].x + x;
        transforme[i].y = transforme[i].y + y;
    }

};
void escala(std::vector<Vertex>& transforme,float x, float y, Vertex& fixo) {
    float x1 = fixo.x;
    float y1 = fixo.y;
    // Translada para a origem
    translacaoT(transforme,-x1, -y1);

    for (int i = 0; i < transforme.size(); ++i) {
        transforme[i].x = transforme[i].x * x;
        transforme[i].y = transforme[i].y * y;
    }
    translacaoT(transforme,x1, y1);

    // Translada para de volta origem
};

//Logica do translacao, 2d
void translacao(std::vector<Vertex>& transforme, float transX, float transY) {
    std::vector<Vertex>auxTransforme(transforme);
    transforme.clear();
    for (const auto& point : auxTransforme)
    {
        Vertex pontoTransformado;
        pontoTransformado.x = point.x + transX;
        pontoTransformado.y = point.y + transY;
        transforme.push_back(pontoTransformado);
    }
}

//Logica do rotação, 2d
void rotacaoPontos(std::vector<Vertex>& transforme, float angle, Vertex centro) {
    float x1 = centro.x;
    float y1 = centro.y;
    translacaoT(transforme, -x1, -y1);
    std::vector<Vertex> auxTransforme(transforme);
    transforme.clear();

    // Tive que transformar graus em radianos (obs: proximei PI)
    angle = angle * 3.14 / 180;
    float cos = std::cos(angle);
    float seno = std::sin(angle);

    for (const auto& point : auxTransforme) {
        Vertex pontoTransformado;

        pontoTransformado.x = centro.x + point.x * cos - point.y * seno;
        pontoTransformado.y = centro.y + point.x* seno + point.y  * cos;
        transforme.push_back(pontoTransformado);
    }
    translacaoT(transforme, x1, y1);
}

//Logica do cisalhamento, 2d
void cisa(std::vector<Vertex>& transforme, float shearX, float shearY, Vertex centro) {
    float x1 = centro.x;
    float y1 = centro.y;
    translacaoT(transforme, -x1, -y1);
    std::vector<Vertex> auxTransforme(transforme);
    transforme.clear();
    // Aplicar cisalhamento aos pontos originais
    for (const auto& point : auxTransforme) {
        Vertex pontoTransformado;

        pontoTransformado.x = point.x + shearX * (point.y - centro.y);
        pontoTransformado.y = point.y + shearY * (point.x - centro.x);

        transforme.push_back(pontoTransformado);
    }
    translacaoT(transforme, x1, y1);

}

int main(void)
{
    //Vetores
    std::vector<Vertex> vertices;
    std::vector<int> transformacao;
    std::vector<Transforme> transforme;
    std::string caminho;
    std::cout << "Digite o caminho do arquivo (exemplo: C:/pasta/arquivo.obj): ";
    std::getline(std::cin, caminho);
    const char* Pointer = caminho.c_str();

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Desenho do gatinho", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetWindowPos(window, 50, 100);
    glLineWidth(2);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    /* Loop until the user closes the window */
    if (loadObj(Pointer, vertices, transformacao, transforme)) {
        std::vector<Vertex> transformado(vertices);
        std::vector<Vertex> anterior;
        while (!glfwWindowShouldClose(window))
        {
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-320, 320, -240, 240, 0, 1);
            glMatrixMode(GL_MODELVIEW);
            glClear(GL_COLOR_BUFFER_BIT);
            /* Render here */

            // Desenha os eixos X e Y
            glBegin(GL_LINES);
            // Eixo X (verde)
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex2f(-320, 0.0f);
            glVertex2f(320, 0.0f);
            // Eixo Y (azul)
            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex2f(0.0f, -240);
            glVertex2f(0.0f, 240);
            glEnd();

            glLineWidth(2.0f);
            //Pinta o desenho
            if (aux3) {
                desenho2(anterior);
            }
            desenho(transformado);

            if (aux2) {
                anterior.clear();
                for (size_t i = 0; i < transformado.size(); i++)
                {
                    anterior.push_back(transformado[i]);
                }
                if (pimp != transformacao.size()) {
                    switch (transformacao[pimp])
                    {
                    case 1:
                        //translação
                        translacao(transformado, transforme[pimp].x, transforme[pimp].y);
                        break;

                    case 2:
                        //rotação
                        Vertex centro_rotacao;
                        std::cout << "Digite as coordenadas do ponto central de rotação (x y): ";
                        std::cin >> centro_rotacao.x >> centro_rotacao.y;
                        rotacaoPontos(transformado, transforme[pimp].x, centro_rotacao);
                        break;
                    case 3:
                        //Escala
                        Vertex centro_escala;
                        std::cout << "Digite as coordenadas do ponto central de escala (x y): ";
                        std::cin >> centro_escala.x >> centro_escala.y;
                        escala(transformado, transforme[pimp].x, transforme[pimp].y, centro_escala);
                        break;

                    case 4:
                        //Cisalhamento
                        Vertex centro_cisa;
                        std::cout << "Digite as coordenadas do ponto central do cisalhamento (x y): ";
                        std::cin >> centro_cisa.x >> centro_cisa.y;
                        cisa(transformado, transforme[pimp].x, transforme[pimp].y, centro_cisa);
                        break;
                    }
                    pimp++;
                }
                else {
                    pimp = 0;
                    transformado.clear();
                    for (size_t i = 0; i < vertices.size(); i++)
                    {
                        transformado.push_back(vertices[i]);
                        anterior.clear();
                    }
                }
                aux2 = false;

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
