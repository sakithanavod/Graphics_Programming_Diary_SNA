// src/demos/Demo1/Demo1.cpp
#include "Window.h"
#include "Shader.h"
#include <glad/glad.h>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <texture.h>
#include <GLFW/glfw3.h>

void SetupTexturesParams(const Shader& shader)
{
    float timeValue = glfwGetTime();
    float alphaValue = (sin(timeValue) / 2.0f) + 0.5f; // Oscillates between 0 and 1
    float blendFactor = (cos(timeValue) / 2.0f) + 0.5f;     // For blending between textures

    shader.setFloat("alpha", alphaValue);
    shader.setFloat("blendFactor", blendFactor);
}

void RotateQuad(const Shader& shader)
{
    float timeValue = (float)glfwGetTime();
    glm::mat4 trans = glm::mat4(1.0f);

    trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
    trans = glm::rotate(trans, timeValue, glm::vec3(0.0f, 0.0f, 1.0f));

	unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
}

int main() {
    Window window(800, 600, "Demo 2 - Textures");
    window.init();

    Shader quadShader("resources/shaders/transform.vert", "resources/shaders/quad_3.frag");
    quadShader.use();

    float vertices[] = {
        // Positions      // Colors		 //TexCoords	
         0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // Top Right
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Bottom Right
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom Left
        -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // Top Left
    };

    unsigned int indices[] = {
    0, 1, 3,  // First triangle (Top Right, Bottom Right, Top Left)
    1, 2, 3   // Second triangle (Bottom Right, Bottom Left, Top Left)
    };

    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind the Vertex Array Object first, then bind and set vertex buffers, and configure vertex attributes
    glBindVertexArray(VAO);

    //Bind and fill the VBO with vertex data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind and fill the EBO with index data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

#pragma region Vertex Attribute Settings

    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //tex-coord
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

#pragma endregion

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0); 

#pragma region LoadTextures
    // load and create a texture 
    // -------------------------

    Texture texture1("resources/textures/container.jpg", 0, false);
    Texture texture2("resources/textures/awesomeface.png", 1, true);

#pragma endregion

    // Setup texture units for each texture
    quadShader.setInt("ourTexture1", 0);
    quadShader.setInt("ourTexture2", 1);

	// Set the transformation matrix
	/*glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

	unsigned int transformLoc = glGetUniformLocation(quadShader.ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));*/

    // Main loop
    while (window.isOpen()) {
        window.processInput();

        glClear(GL_COLOR_BUFFER_BIT);

        quadShader.use();
        SetupTexturesParams(quadShader);
		RotateQuad(quadShader);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        window.swapBuffers();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    window.cleanup();
    return 0;
}
