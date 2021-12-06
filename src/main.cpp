/**
*   @brief Hello!
* 
* 
* 
*/

// dependencies
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/type_ptr.hpp>

// standard C++ libraries
#include <iostream>
#include <vector>

// project-specific libraries
#include "geometry.hpp"
#include "shaders.cpp"
#include "camera.cpp"

// window size
#define WIDTH 800
#define HEIGHT 600

#define NEAR 0.01f
#define FAR 10.f

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
        GLsizei len;
        glGetShaderInfoLog(id, 512, &len, infoLog);
        std::cerr << (type == GL_VERTEX_SHADER ? "VS " : "FS ") << "FAIL: " << infoLog << std::endl;
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

/**
*  @brief Calculates the view matrix.
* 
* 
* 
*/
glm::mat4 ComputeViewMatrix(CameraData data) {
    
    return glm::rotate(glm::mat4(1.f), data.pitch, glm::vec3(1.f, 0.f, 0.f)) *
        glm::rotate(glm::mat4(1.f), data.yaw, glm::vec3(0.f, 1.f, 0.f)) *
        glm::translate(glm::mat4(1.f), glm::vec3(data.x, data.y, data.z));
}

/**
*  @brief Calculates the projection matrix.
* 
* 
* 
*/
glm::mat4 ComputeProjMatrix(CameraData data) {
    float aspect = (float)WIDTH / (float)HEIGHT;
    return glm::perspective(glm::half_pi<float>(), aspect, NEAR, FAR);
}



int main(void)
{

#ifdef _DEBUG
    // GLM
    glm::mat4 debug_mat = glm::mat4(1.f);

    // geometry.cpp
    VertexNormal* ptr = nullptr;
    Block* debug_block = new Block(5.f, 5.f, 5.f);
    debug_block->PrintSize();
    delete debug_block;
#endif


    GLFWwindow* window;
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WIDTH, HEIGHT, "pgr-game", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);


    auto err = glewInit();

    if (err != GLEW_OK) {
        std::cout << "Failed to initialize GLEW." << std::endl;
        return -1;
    }


#ifdef _DEBUG
    std::cout << glGetString(GL_VERSION) << std::endl;
#endif


    // generate data for displaying image
    Block* block = new Block(1.f, 1.f, 1.f);

    VertexNormal* data = block->GetGeometry();

    std::cerr << data[0].normal[0] << std::endl;
    std::cerr << data[0].normal[1] << std::endl;
    std::cerr << data[0].normal[2] << std::endl;

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 36 * 6 * sizeof(float), data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // create program with shaders
    GLuint program = createProgram({
        createShader(GL_VERTEX_SHADER, basicVS),
        createShader(GL_FRAGMENT_SHADER, basicFS),
        });

    GLuint cel_program = createProgram({
        createShader(GL_VERTEX_SHADER, celVS),
        createShader(GL_FRAGMENT_SHADER, basicFS),
        });

    // create camera instance -- NORMAL SHADER
    Camera* camera = new Camera;

    CameraData cdata = camera->GetData();
    cdata.x = 3.f; cdata.y = 1.f; cdata.z = -3.f;
    camera->SetData(cdata);

    GLuint viewUniform = glGetUniformLocation(program, "u_view");
    GLuint projUniform = glGetUniformLocation(program, "u_proj");

    auto viewM = glm::lookAt(glm::vec3(cdata.x, cdata.y, cdata.z), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));

    glProgramUniformMatrix4fv(program, viewUniform, 1, GL_FALSE, glm::value_ptr(viewM));
    glProgramUniformMatrix4fv(program, projUniform, 1, GL_FALSE, glm::value_ptr(ComputeProjMatrix(camera->GetData())));
    
    // CEL SHADER SETUP
    GLuint cel_viewUniform = glGetUniformLocation(cel_program, "u_view");
    GLuint cel_projUniform = glGetUniformLocation(cel_program, "u_proj");

    glProgramUniformMatrix4fv(cel_program, cel_viewUniform, 1, GL_FALSE, glm::value_ptr(viewM));
    glProgramUniformMatrix4fv(cel_program, cel_projUniform, 1, GL_FALSE, glm::value_ptr(ComputeProjMatrix(camera->GetData())));



    float angle = 0;
    float inc = 0.04f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // update camera position:
        cdata.x = 3 * glm::sin(angle);
        cdata.z = 3 * glm::cos(angle);
        angle += inc;

        auto viewM = glm::lookAt(glm::vec3(cdata.x, cdata.y, cdata.z), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));

        glProgramUniformMatrix4fv(program, viewUniform, 1, GL_FALSE, glm::value_ptr(viewM));
        glProgramUniformMatrix4fv(cel_program, cel_viewUniform, 1, GL_FALSE, glm::value_ptr(viewM));


        /* Render here */
        glClearColor(0.7, 0.7, 0.7, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        glBindVertexArray(vbo);

        // outline render
        glUseProgram(cel_program);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDisable(GL_CULL_FACE);


        // normal render
        glUseProgram(program);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    delete block;
    glfwTerminate();
    return 0;
}