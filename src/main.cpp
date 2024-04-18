#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shader.h>
#include <iostream>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Vertex Shader
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

int main(int argc, char* argv[])
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

    // float vertices[] = {
    //     //pos                //color            //texture
    //      0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
    //      0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
    //     -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
    //     -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f
    // };

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
    // unsigned int indices[] = {
    //     0, 1, 3,
    //     1, 2, 3
    // };
    // Create vertex buffer object (VBO) and vertex array object (VAO)
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // glGenBuffers(1, &EBO);

    // Bind VAO and VBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    Shader shader("D:/Goodies/C++/learning-stuff/shaders/vShader.vs", "D:/Goodies/C++/learning-stuff/shaders/fShader.fs");
    int width, height, nrChannels;
    unsigned int texture1, texture2;
    stbi_set_flip_vertically_on_load(true);  
    unsigned char *data = stbi_load("D:/Goodies/C++/learning-stuff/textures/nah_id_win.jpg", &width, &height, &nrChannels, 0);
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (data == NULL)
    {
        std::cout << "Failed to load texture" << std::endl;
        return -1;
    }
    else
    {
        std::cout << "Loaded texture" << std::endl;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data);


    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);


    data = stbi_load("D:/Goodies/C++/learning-stuff/textures/jkm.jpg", &width, &height, &nrChannels, 0);
    if (data == NULL)
    {
        std::cout << "Failed to load texture" << std::endl;
        return -1;
    }
    else
    {
        std::cout << "Loaded texture" << std::endl;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data);

    shader.use();
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);
    // Render loop
    glEnable(GL_DEPTH_TEST); 
    while (!glfwWindowShouldClose(window))
    {
        processInput(window, monitor);
        glfwSetKeyCallback(window, key_callback);

        double val = (sin(glfwGetTime())/2.0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        shader.use();
        shader.setMat4("transform", model);
        shader.setFloat("mixValue", val);
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Bind VAO
        glBindVertexArray(VBO);

        // Draw the triangle
        glDrawArrays(GL_TRIANGLES, 0, 36);

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