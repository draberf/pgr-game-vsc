#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

GLuint createShader(GLenum type, std::string const& src) {
    auto id = glCreateShader(type);
    char const* srcs[] = { src.data() };
    glShaderSource(id, 1, srcs, nullptr);
    glCompileShader(id);
    return id;
}

GLuint createProgram(std::vector<GLuint>const& shaders) {
    auto id = glCreateProgram();
    for (auto const& shader : shaders) {
        glAttachShader(id, shader);
    }
    glLinkProgram(id);
    return id;
}

int main(void)
{
    GLFWwindow* window;
    /* Initialize the library */
    if (!glfwInit())
        return -1;



    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
 
    auto err = glewInit();

    if (err != GLEW_OK) {
        std::cout << "Failed to initialize GLEW." << std::endl;
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
    
    GLuint vao;
    glCreateVertexArrays(1, &vao);

    auto vs_source = R".(
    #version 460
    void main(){
        gl_Position = vec4(gl_VertexID&1, gl_VertexID>>1,0,1);
    }
    ).";

    auto fs_source = R".(
    #version 460
    layout(location=0)out vec4 fColor;
    void main(){
        fColor = vec4(1,0,0,1);
    }
    ).";

    GLuint program = createProgram({
        createShader(GL_VERTEX_SHADER,vs_source),
        createShader(GL_FRAGMENT_SHADER, fs_source),
        });



    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.0, 0.1, 0.1, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vao);

        glUseProgram(program);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}