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
#include <camera.h>

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

//TEST CODE
static glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

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

void ApplyMVP(const Shader& shader)
{
	// create transformations
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	//set view and projections first

	view = camera.GetViewMatrix();
	projection = glm::perspective(camera.GetFOVInRad(), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

	shader.setMat4("view", view);
	shader.setMat4("projection", projection);

	for (unsigned int i = 0; i < 10; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);

		float angle = glfwGetTime() * glm::radians(20.0f + 5.0f * i);
		model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));

		/************************************************************************/
		/* 
		1. You send the model matrix to the shader before each draw call
		2. glDrawArrays(...) draws the same cube geometry, but the GPU transforms it using the current model matrix
		3. This makes each cube appear in a different location and orientation
		*/
		/************************************************************************/
		shader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

    // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
}

int main() {
    Window window(SCR_WIDTH, SCR_HEIGHT, "Demo 4 - Camera");
    window.init();

	glfwSetCursorPosCallback(window.getWindow(), mouse_callback);
	glfwSetScrollCallback(window.getWindow(), scroll_callback);

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

    Shader quadShader("resources/shaders/transform_3d.vert", "resources/shaders/quad_3d.frag");
    quadShader.use();

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, //x, y, z, u, v
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

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind the Vertex Array Object first, then bind and set vertex buffers, and configure vertex attributes
    glBindVertexArray(VAO);

    //Bind and fill the VBO with vertex data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

#pragma region Vertex Attribute Settings

    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //tex-coord
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

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

	float deltaTime = 0.0f; // Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame

    // Main loop
    while (window.isOpen()) {

		// per-frame time logic
		// --------------------
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

        window.processInput();
		camera.ProcessKeyInput(window.getWindow(), deltaTime);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        quadShader.use();
        SetupTexturesParams(quadShader);
		//RotateQuad(quadShader);

		glBindVertexArray(VAO);
		ApplyMVP(quadShader);

		//glDrawArrays(GL_TRIANGLES, 0, 36);

        window.swapBuffers();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    window.cleanup();
    return 0;
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}