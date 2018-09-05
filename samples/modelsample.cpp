#include <Shaders.hpp>
#include <ModelTexture.hpp>
#include <ModelSprite.hpp>

unsigned int WIDTH = 800;
unsigned int HEIGHT = 800;

// this example rewuires that camera be a global exapmle due to the collback functions
Camera camera(glm::vec3(30.0f, 30.0f, 30.0f));
bool firstMouse = true;
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;

GLFWwindow * win;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void InitialiseWindow()
{
    glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    win = glfwCreateWindow(this->_width, this->_height, "Learn OpenGL", NULL, NULL);
	if (win == NULL)
	{
		std::cout << "fail init" << std::endl;
		glfwTerminate();
		throw std::logic_error("INIT Failed");
	}

	glfwMakeContextCurrent(win);

    glfwSetFramebufferSizeCallback(win, framebuffer_size_callback);
    glfwSetCursorPosCallback(win, mouse_callback);
    glfwSetScrollCallback(win, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //doesn't cap fps
    glfwSwapInterval(0.0);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		throw std::logic_error("glad Failed");
	}

	glViewport(0, 0, this->_width, this->_height);
    glEnable(GL_DEPTH_TEST);
}

void ProcessInput()
{
	if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(win, true);
    
    if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

int main(void)
{
    // Initialise window and input according to GLFW
    InitialiseWindow();

    // coloring and how to interpret shader data
    Shaders modelshader(R"(../Resources/VertexShaders/ShadedModelsVert.glsl)", R"(../Resources/FragmentShaders/DarkShadedModelsFrag.glsl)");
    // loads model, can also set postion and scale 
    
    ModelTexture modelTexture(R"(../Resources/Assets/iron_block.obj)");
    ModelTexture modelTexture2(R"(../Resources/Assets/mario_walking_1.obj)");

    ModelSprite sprite1(modelTexture);
    ModelSprite sprite2(modelTexture);
    
    ModelSprite sprite3;
    sprite.LoadModelTexture(modelTexture2);

    //point camera needs to look at
    camera.LookAt(glm::vec3(0));

    // for timing purposes
    float elapsed = glfwGetTime();
    float currentFrame;
    int fps = 0;

    //if only one position of model
    //NOTE, in this case the Y component is actually the hieght in 3d space, would used in jumping
    sprite.Position(0,0);
    sprite.Scale(0.2);

    sprite.Position(10,10);
    sprite.Scale(0.2);

    sprite3.Position(-5,-5);
    sprite3.Scale(0.2);
    

    while (glfwWindowShouldClose(win))
    {
        currentFrame = glfwGetTime();
        ProcessInput();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //set view
        //NOTE:: all drawings can only be done after setting the camera
        camera.SetShaderView(modelshader, WIDTH, HEIGHT);

        // set position of the light for shading
        modelshader.setVec3("light", glm::vec3(-30, 30, 30));

        //draw models
        sprite1.Draw(modelshader);
        sprite2.Draw(modelshader);
        sprite3.Draw(modelshader);

        if (currentFrame - elapsed >= 0.25f)
        {
            // move model sprite and/or rotate
            sprite3.Move(-0.01, -0.01);
        }

        fps++;
        if (currentFrame - elapsed >= 1.0f)
        {
            std::cout << fps << std::endl;
            elapsed = glfwGetTime();
            fps = 0;
        }

        GLenum error = glGetError();

        if (error != GL_NO_ERROR)
            std::cout << "OpenGL error: " << error << std::endl;

		glfwSwapBuffers(this->_win);
		glfwPollEvents();
    }

    return (1);
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