#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Vertex Shader
const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aColor;
    out vec3 ourColor;
    void main()
    {
        gl_Position = vec4(aPos, 1.0);
        ourColor = aColor;
    }
)";

// Fragment Shader
const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    in vec3 ourColor;
    void main()
    {
        FragColor = vec4(ourColor, 1.0f);
    }
)";

int getRefreshRate(GLFWmonitor* monitor)
{
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    return mode->refreshRate;
}
int getScreenWidth(GLFWmonitor* monitor)
{
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    return mode->width;
}
int getScreenHeight(GLFWmonitor* monitor)
{
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    return mode->height;
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    bool isFullscreen = glfwGetWindowMonitor(window) != NULL;
    GLFWmonitor* monitor  = glfwGetPrimaryMonitor();
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && isFullscreen)
        glfwSetWindowMonitor(window, NULL, 0, 50, getScreenWidth(monitor), getScreenHeight(monitor), getRefreshRate(monitor));
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && !isFullscreen)
        glfwSetWindowMonitor(window, monitor, 0, 0, getScreenWidth(monitor), getScreenHeight(monitor), getRefreshRate(monitor));
}
void processInput(GLFWwindow* window, GLFWmonitor* monitor)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // Change clear color to red
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f); // Change clear color to green
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // Change clear color to blue
}

int main()
{
    // Initialize GLFW
    glfwInit();

    // Configure GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(getScreenWidth(monitor), getScreenWidth(monitor), "Holy moly", NULL, NULL);
    glfwSetWindowMonitor(window, monitor, 0, 0, getScreenWidth(monitor), getScreenHeight(monitor), getRefreshRate(monitor));
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Load OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Create vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Create fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Create shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Define vertices of the triangle
    float vertices[] = {
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    // Create vertex buffer object (VBO) and vertex array object (VAO)
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind VAO and VBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glUseProgram(shaderProgram);
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        // Process user input
        processInput(window, monitor);
        glfwSetKeyCallback(window, key_callback);
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use shader program

        
        // Bind VAO
        glBindVertexArray(VAO);

        // Draw the triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Unbind VAO
        glBindVertexArray(0);

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }

    // Delete VAO and VBO
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // Terminate GLFW
    glfwTerminate();

    return 0;
}