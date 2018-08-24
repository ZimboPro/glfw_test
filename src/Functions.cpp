/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Functions.cpp                                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage   <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 12/47/59 by lde-jage          #+#    #+#             */
/*   Updated: 2018/07/11 12/47/59 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Functions.hpp>
#include <Shaders.hpp>
#include <TextureImages.hpp>
#include <Camera.hpp>
#include <Models.hpp>
#include <Image.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include <stdexcept>

Camera camera(glm::vec3(30.0f, 30.0f, 30.0f));
bool firstMouse = true;
float lastX = 800 / 2.0f;
float lastY = 600 / 2.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

float deltaTime = 0.0f;
float lastFrame = 0.0f;

Functions::Functions()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    this->_height = 600;
    this->_width = 800;

    this->_win = glfwCreateWindow(this->_width, this->_height, "Learn OpenGL", NULL, NULL);
	if (this->_win == NULL)
	{
		std::cout << "fail init" << std::endl;
		glfwTerminate();
		throw std::logic_error("INIT Failed");
	}

	glfwMakeContextCurrent(this->_win);

    glfwSetFramebufferSizeCallback(this->_win, framebuffer_size_callback);
    glfwSetCursorPosCallback(this->_win, mouse_callback);
    glfwSetScrollCallback(this->_win, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(this->_win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		throw std::logic_error("glad Failed");
	}

	glViewport(0, 0, this->_width, this->_height);
    glEnable(GL_DEPTH_TEST);
}

Functions::Functions(Functions const & src)
{
	*this = src;	
}

Functions::~Functions()
{
	glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
	glfwTerminate();
}

Functions & Functions::operator=(Functions const & src)
{
	if (this != &src)
    {
		*this = src;
    }
	return (*this);
}

void Functions::Loop()
{
    // Shaders basic(R"(../Resources/VertexShaders/Basic.vshader)", R"(../Resources/FragmentShaders/Basic.fshader)");
    
    // Shaders cam(R"(../Resources/VertexShaders/CameraVert.glsl)", R"(../Resources/FragmentShaders/CameraFrag.glsl)");
    // Shaders shader(R"(../Resources/VertexShaders/ImageVert.glsl)", R"(../Resources/FragmentShaders/ImageFrag.glsl)");
    Shaders modelshader(R"(../Resources/VertexShaders/MeshVert.glsl)", R"(../Resources/FragmentShaders/MeshFrag.glsl)");
    Shaders darkshader(R"(../Resources/VertexShaders/DarkerMeshVert.glsl)", R"(../Resources/FragmentShaders/DarkerMeshFrag.glsl)");

    Model model(R"(../Resources/Assets/iron_block.obj)");
    Model model2(R"(../Resources/Assets/mario_walking_1.obj)");
    camera.LookAt(glm::vec3(0));

    // TextureImages texture("awesomeface.png");

    // Image image(200, 150, 400, 300, &texture, this->_width, this->_height);
    
    
    model2.NewPostionAndScale(glm::vec3(5.0f, 0.0f, -10.0f), 0.2f, 45);
	while (!glfwWindowShouldClose(this->_win))
	{
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

		ProcessInput();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)this->_width / (float)this->_height, 0.1f, 100.0f);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        modelshader.use();
        modelshader.setMat4("projection", projection);
        modelshader.setMat4("view", view);

        model.NewPostionAndScale(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.2f, 0.2f, 0.2f));
        model.DrawAndSet(modelshader, "model");

        //need to reset the matrix
        model2.DrawAndSet(modelshader, "model");

        darkshader.use();
        darkshader.setMat4("projection", projection);
        darkshader.setMat4("view", view);

        model.NewPostionAndScale(glm::vec3(-7.0f, 0.0f, -10.0f), glm::vec3(0.2f, 0.2f, 0.2f));
        model.DrawAndSet(darkshader, "model");

        // image.Draw(shader, camera);

		glfwSwapBuffers(this->_win);
		glfwPollEvents();
	}
}

void Functions::ProcessInput()
{
	if (glfwGetKey(this->_win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(this->_win, true);
    
    if (glfwGetKey(this->_win, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(this->_win, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(this->_win, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(this->_win, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
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
    camera.ProcessMouseScroll(yoffset);
}
