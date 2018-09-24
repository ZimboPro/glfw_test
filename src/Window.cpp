#include <Window.hpp>
#include <iostream>
#include <cstring>
#include <glm/gtc/matrix_transform.hpp>
#include <Coplien.hpp>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (mods < 0) {}
    if (scancode < 0) {}
    Window *win = static_cast<Window *>(glfwGetWindowUserPointer(window));
    win->_keys[key] = action != GLFW_RELEASE; 
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    Window *win = static_cast<Window *>(glfwGetWindowUserPointer(window));
    win->_mouseX = xpos;
    win->_mouseY = ypos;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (mods < 0) {}
    Window *win = static_cast<Window *>(glfwGetWindowUserPointer(window));
    win->_buttons[button] = action != GLFW_RELEASE;
}

void window_resize(GLFWwindow * window, int width, int height)
{
    glViewport(0, 0, width, height);
    Window *win = static_cast<Window *>(glfwGetWindowUserPointer(window));
    win->_height = height;
    win->_width = width;
}

Window::Window(const char *title, unsigned int w, unsigned int h) : _title(title)
{
    this->_height = h;
    this->_width = w;

    this->_isInitialised = Init();
    if (!this->_isInitialised)
        glfwTerminate();
    
    InitKeys();
    InitButtons();
}

Window::Window(const Window & src) : _title(src._title)
{
    *this = src;
}

Window::~Window()
{
    glfwTerminate();
}

Window & Window::operator=(const Window & src)
{
    if (this != &src)
    {
        copy(this->_width, src._width);
        copy(this->_height, src._height);
        copy(this->_win, src._win);
        copy(this->_isInitialised, src._isInitialised);
        copyArr(this->_keys, src._keys);
        copyArr(this->_keyState, src._keyState);
        copyArr(this->_keyTyped, src._keyTyped);
        copyArr(this->_buttons, src._buttons);
        copyArr(this->_buttonState, src._buttonState);
        copyArr(this->_buttonClicked, src._buttonClicked);
        copy(this->_mouseX, src._mouseX);
        copy(this->_mouseY, src._mouseY);
    }
    return *this;
}

void Window::InitKeys()
{
    for (int i = 0; i < MAX_KEYS; i++)
    {
        this->_keys[i] = false;
        this->_keyState[i] = false;
        this->_keyTyped[i] = false;
    }
}

void Window::InitButtons()
{
    for (int i = 0; i < MAX_BUTTONS; i++)
    {
        this->_buttons[i] = false;
        this->_buttonState[i] = false;
        this->_buttonClicked[i] = false;
    }
}

void Window::close()
{
    glfwSetWindowShouldClose(this->_win, true);
}

void Window::UpdateKeysAndButtons()
{
    for (int i = 0; i < MAX_KEYS; i++)
        this->_keyTyped[i] = this->_keys[i] && !this->_keyState[i];
    memcpy(this->_keyState, this->_keys, MAX_KEYS);

    for (int i = 0; i < MAX_BUTTONS; i++)
        this->_buttonClicked[i] = this->_buttons[i] && !this->_buttonState[i];
    memcpy(this->_buttonState, this->_buttons, MAX_BUTTONS);
}

void Window::update()
{
    UpdateKeysAndButtons();

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
        std::cout << "OpenGL error: " << error << std::endl;

    glfwSwapBuffers(this->_win);
    glfwPollEvents();
}

bool failed(std::string str)
{
    std::cout << str << std::endl;
    return false;
}

bool Window::isKeyPressed(int keycode) 
{
    if (keycode >= MAX_KEYS)
        return false;
    return _keys[keycode];
}

bool Window::isKeyTyped(int keycode) 
{
    if (keycode >= MAX_KEYS)
        return false;
    return _keyTyped[keycode];
}

bool Window::isButtonPressed(int button) 
{
    if (button >= MAX_BUTTONS)
        return false;
    return _buttons[button];
}

bool Window::isButtonClicked(int button) 
{
    if (button >= MAX_BUTTONS)
        return false;
    return this->_buttonClicked [button];
}

void Window::CursorPostion(double &x, double & y) 
{
    x = _mouseX;
    y = _mouseY;
}

void Window::setCallback()
{
    glfwMakeContextCurrent(this->_win);

    glfwSetKeyCallback(this->_win, key_callback);
    glfwSetCursorPosCallback(this->_win, cursor_position_callback);
    glfwSetMouseButtonCallback(this->_win, mouse_button_callback);
    glfwSetFramebufferSizeCallback(this->_win, window_resize);

    glfwSwapInterval(0.0);
    glfwSetWindowUserPointer(this->_win, this);
}

void Window::windowHints()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

bool Window::Init()
{
    if (!glfwInit())
        return failed(R"(GameEngine failed to initialise)");
    windowHints();

    this->_win = glfwCreateWindow(this->_width, this->_height,this->_title, NULL, NULL);
    if (!this->_win)
        return failed(R"(Failed to create window)");
    
    setCallback();
    return InitGlad();
}

bool Window::InitGlad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        return failed(R"(Failed to initialize GLAD)");
    glEnable(GL_DEPTH_TEST);
    return true;
}

bool Window::closed() 
{
    return glfwWindowShouldClose(this->_win) == 1;
}

void Window::clear(int8_t r, int8_t g, int8_t b) 
{
    float red = static_cast<float>(r) / 255.0f;
    float green = static_cast<float>(g) / 255.0f;
    float blue = static_cast<float>(b) / 255.0f;
    glClearColor(red, green, blue, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::clear(float r, float g, float b) 
{
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

unsigned int Window::Width() 
{
    return this->_width;
}

unsigned int Window::Height() 
{
    return this->_height;
}

void Window::resize(unsigned int w, unsigned int h)
{
    this->_width = w;
    this->_height = h;
    glfwSetWindowSize(this->_win, this->_width, this->_height);
    centerScreen();
}

void Window::fullscreen()
{
    glfwSetWindowMonitor(this->_win, glfwGetPrimaryMonitor(), 0, 0, this->_width, this->_height, GL_DONT_CARE);
}

void Window::windowed()
{
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    glfwSetWindowMonitor(this->_win, NULL, (mode->width - this->_width) / 2, (mode->height - this->_height) / 2, this->_width, this->_height, GL_DONT_CARE);
}

void Window::centerScreen()
{
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    glfwSetWindowPos(this->_win, (mode->width - this->_width) / 2, (mode->height - this->_height) / 2);
}

bool Window::isInitialised()
{
    return this->_isInitialised;
}

glm::mat4 Window::Projection()
{
    return glm::ortho(0.0f, static_cast<GLfloat>(this->_width), 0.0f, static_cast<GLfloat>(this->_height), 0.0f, 100.0f);
}