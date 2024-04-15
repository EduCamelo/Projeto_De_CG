#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>


void simetria8(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2d(x, y);
    glVertex2d(y, x);
    glVertex2d(y, -x);
    glVertex2d(x, -y);
    glVertex2d(-x, -y);
    glVertex2d(-y, -x);
    glVertex2d(-y, x);
    glVertex2d(-x, y);
    glEnd();
}


void circunferencia(int raio) {
    int x = 0, y = raio;
    double d = 5.0 / 4 - raio;
    simetria8(x, y);
    while (y > x) {
        if (d < 0) {
            d = d + 2 * x + 3.0;
        }
        else {
            d = d + 2 * (x - y) + 5.0;
            y = y - 1;
        }
        x = x + 1;
        simetria8(x, y);
    }
}


static void teclado(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Reta: algoritmo DDA", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetWindowPos(window, 50, 100);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-320, 320, -240, 240, 0, 1);

        circunferencia(70);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        glfwSetKeyCallback(window, teclado);

    }

    glfwTerminate();
    return 0;
}