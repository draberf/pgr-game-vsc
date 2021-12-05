/**
*   @brief Hello!
* 
* 
* 
*/

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>

#include <iostream>
#include <vector>


/**
*   @brief Function to compile a shader and validate it. 
* 
* 
* 
*/
GLuint createShader(GLenum type, std::string const& src) {
    auto id = glCreateShader(type);
    char const* srcs[] = { src.data() };
    glShaderSource(id, 1, srcs, nullptr);
    glCompileShader(id);

    // validate shader
    int success;
    char infoLog[512];
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        std::cerr << "FAIL: " << infoLog << std::endl;
    }

    return id;
}

/**
* 
* 
* 
* 
* 
*/
GLuint createProgram(std::vector<GLuint>const& shaders) {
    auto id = glCreateProgram();
    for (auto const& shader : shaders) {
        glAttachShader(id, shader);
    }
    glLinkProgram(id);

    int success;
    char infoLog[512];
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        GLsizei len = 0;
        glGetProgramInfoLog(id, 512, &len, infoLog);
        std::cerr << "FAIL: " << infoLog << std::endl;
    }
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

    #ifdef _DEBUG
    std::cout << glGetString(GL_VERSION) << std::endl;
    #endif

    float quads[12] = {
        -1.f, -1.f,
         1.f, -1.f,
         1.f,  1.f,

        -1.f, -1.f,
         1.f,  1.f,
        -1.f,  1.f
    };

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quads), quads, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    auto vs_source = R".(
    #version 460

    layout(location=0)in vec2 position;

    out vec2 fPos;

    void main(){
        gl_Position = vec4(position.xy,0,1);
        fPos = vec2((gl_Position.xy+1)/2);
    }
    ).";

    auto fs_source = R".(
    #version 460
    in vec2 fPos;
    layout(location=0)out vec4 fColor;
    void main(){
        fColor = vec4(fPos.xy,0,1);
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

        glBindVertexArray(vbo);

        glUseProgram(program);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glBindVertexArray(0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}