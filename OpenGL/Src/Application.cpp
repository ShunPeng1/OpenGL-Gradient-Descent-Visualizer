#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ext/matrix_clip_space.hpp>
#include <vec3.hpp> // glm::vec3
#include <vec4.hpp> // glm::vec4
#include <mat4x4.hpp> // glm::mat4
#include <ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <ext/matrix_clip_space.hpp> // glm::perspective
#include <ext/scalar_constants.hpp> // glm::pi

#include <iostream>
#include "Engine/Render/Shader.h"
#include "Engine/Render/Mesh.h"
#include "Engine/Loader/ModelLoader.h"


enum class RenderMode {
    FACE,
    WIREFRAME,
    POINT
};


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Camera settings
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
float deltaTime = 0.0f;
float lastFrame = 0.0f;
bool spacePressed = false;

int currentModel = 1; // Variable to keep track of the current model
RenderMode currentRenderMode = RenderMode::FACE;


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cout << "ERROR!" << std::endl;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	


    /* Maximize the window */
    glfwMaximizeWindow(window);

    std::cout << glGetString(GL_VERSION) << std::endl;

    Shader defaultShader = Shader(".\\Resources\\Shaders\\default.vert", ".\\Resources\\Shaders\\default.frag");
    defaultShader.Use();

    glm::mat4 world = glm::mat4(1.0f);
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::vec2 texScale = glm::vec2(1.0f, 1.0f);

    defaultShader.SetUniformMat4("mWorld", world);
    defaultShader.SetUniformMat4("mProj", proj);
    defaultShader.SetUniformVec2("mTexScale", texScale);
    defaultShader.SetUniformBool("mUseTexture", false);
    defaultShader.SetUniformBool("mUseColor", true);

    ModelLoader loader = ModelLoader::Builder()
        .SetUseNormalColor(true)
        .Build();
    Mesh teapot = loader.LoadObjFile(".\\Resources\\Models\\teapot.obj");
    Mesh triangle = loader.LoadTriangle();
    // Add other models here
    Mesh quad = loader.LoadQuad();
    Mesh cube = loader.LoadCube();
	Mesh circle = loader.LoadCircle(36);
    Mesh cylinder = loader.LoadCylinder(36);
    Mesh sphere = loader.LoadSphere(40, 40);
    Mesh cone = loader.LoadCone(36);

	ModelLoader::Range xRange(-1.0f, 1.0f, 0.5f);
	ModelLoader::Range yRange(-1.0f, 1.0f, 0.5f);
    
    Mesh plane = loader.LoadPlane(
        [](float x, float y) -> float {
            // Example function: return a constant value
            return x * x + y * y * y;
        }, xRange, yRange);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glEnable(GL_DEPTH_TEST);

        /* Render here */
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        defaultShader.SetUniformMat4("mView", view);

        // Draw the selected model
        switch (currentModel) {
        case 1: teapot.Draw(defaultShader); break;
        case 2: triangle.Draw(defaultShader); break;
        case 3: quad.Draw(defaultShader); break;
        case 4: cube.Draw(defaultShader); break;
		case 5: circle.Draw(defaultShader); break;
        case 6: cylinder.Draw(defaultShader); break;
        case 7: sphere.Draw(defaultShader); break;
        case 8: cone.Draw(defaultShader); break;
        case 9: plane.Draw(defaultShader); break;
            // Add more cases if you have more models
        }

        // Set the polygon mode based on the current rendering mode
        switch (currentRenderMode) {
        case RenderMode::FACE:
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            break;
        case RenderMode::WIREFRAME:
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            break;
        case RenderMode::POINT:
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            break;
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    float cameraSpeed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraUp;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraUp;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Change model based on key press
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        currentModel = 1;
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        currentModel = 2;
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        currentModel = 3;
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
        currentModel = 4;
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
        currentModel = 5;
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
        currentModel = 6;
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
        currentModel = 7;
    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
        currentModel = 8;
	if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
		currentModel = 9;


    // Toggle rendering mode 
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !spacePressed) {
        spacePressed = true;
        switch (currentRenderMode) {
        case RenderMode::FACE:
            currentRenderMode = RenderMode::WIREFRAME;
            break;
        case RenderMode::WIREFRAME:
            currentRenderMode = RenderMode::POINT;
            break;
        case RenderMode::POINT:
            currentRenderMode = RenderMode::FACE;
            break;
        }
    }

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
		spacePressed = false;
	}


}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height * SCR_WIDTH / SCR_HEIGHT);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = static_cast<float>(xpos);
        lastY = static_cast<float>(ypos);
        firstMouse = false;
    }

    float xoffset = static_cast<float>(xpos) - lastX;
    float yoffset = lastY - static_cast<float>(ypos); // reversed since y-coordinates go from bottom to top
    lastX = static_cast<float>(xpos);
    lastY = static_cast<float>(ypos);

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}