#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#define MAX_KEYS 1024
#define MAX_BUTTONS 32 

//! Window Class
/*!
    The Window class controls the window behaviour and events
*/

class Window
{
    public:
        /**
         * @brief Construct a new Window object
         * 
         * @param title 
         * @param w 
         * @param h 
         */
        Window(const char * title, unsigned int w, unsigned int h);
        /**
         * @brief Construct a new Window object
         * 
         * @param src The instance to copy
         */
        Window(const Window & src);
        ~Window();
        /**
         * @brief Assign the data in the right instance to the left
         * 
         * @param src 
         * @return Window& 
         */
        Window & operator=(const Window & src);
        /**
         * @brief Updates the window
         * 
         */
        void update();
        /**
         * @brief Checks to see if the window has closed. Returns true if true
         * 
         * @return true Window has been closed
         * @return false Window is still open
         */
        bool closed();
        /**
         * @brief Closes the window
         * 
         */
        void close();
        /**
         * @brief Clears the window to the color specified
         * 
         * @param r - red on scale of 0 to 255
         * @param g - green on scale of 0 to 255
         * @param b - blue on scale of 0 to 255
         */
        void clear(int8_t r, int8_t g, int8_t b) ;
        /**
         * @brief Clears the window to the color specified
         * 
         * @param r - red on scale of 0 to 1
         * @param g - green on scale of 0 to 1
         * @param b - blue on scale of 0 to 1
         */
        void clear(float r = 0.0f, float g = 0.0f, float b = 0.0f) ;
        /**
         * @brief Resize the window to the parameters specified
         * 
         * @param width
         * @param height
         */
        void resize(unsigned int width, unsigned int height);
        /**
         * @brief Set the window to Fullscreen mode
         * 
         */
        void fullscreen();
        /**
         * @brief Change the window from fullscreen to windowed
         * 
         */
        void windowed();
        /**
         * @brief Return the window width
         * 
         * @return unsigned int 
         */
        unsigned int Width() ;
        /**
         * @brief Return the window height
         * 
         * @return unsigned int 
         */
        unsigned int Height() ;
        /**
         * @brief Is the Key being pressed
         * 
         * @param keycode is the GLFW_KEY enums
         * @return true Key is being pressed
         * @return false Key is not being pressed
         */
        bool isKeyPressed(int keycode) ;
        /**
         * @brief Is the Key being typed
         * 
         * @param keycode is the GLFW_KEY enums
         * @return true Key has been pressed and released
         * @return false Key has not been pressed and released
         */
        bool isKeyTyped(int keycode) ;
        /**
         * @brief Is the Mouse Button being pressed
         * 
         * @param button is the GLFW_BUTTON enums
         * @return true Mouse Button has been pressed
         * @return false Mouse Button has not been pressed
         */
        bool isButtonPressed(int button) ;
        /**
         * @brief Is the Button being clicked
         * 
         * @param button is the GLFW_BUTTON enums
         * @return true Mouse Button has been pressed and released
         * @return false Mouse Button has not been pressed and released
         */
        bool isButtonClicked(int button) ;
        /**
         * @brief The mouse cursor position according to the window
         * 
         * @param x 
         * @param y 
         */
        void CursorPostion(double &x, double & y) ;

        /**
         * @brief Is the window initialised
         * 
         * @return true Window has been initialised
         * @return false Window has not been initialised
         */

        bool isInitialised();

        /**
         * @brief Get the window projection
         * 
         * @return glm::mat4 
         */
        glm::mat4 Projection();

    private:
        const char * _title;
        unsigned int _width;
        unsigned int _height;
        GLFWwindow * _win;
        bool _isInitialised;

        bool _keys[MAX_KEYS];
        bool _keyState[MAX_KEYS];
        bool _keyTyped[MAX_KEYS];
        bool _buttons[MAX_BUTTONS];
        bool _buttonState[MAX_BUTTONS];
        bool _buttonClicked[MAX_BUTTONS];
        double _mouseX;
        double _mouseY;

        friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
        friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
        friend void window_resize(GLFWwindow * window, int width, int height);

        bool Init();
        void centerScreen();
        void setCallback();
        void windowHints();
        void InitKeys();
        void InitButtons();
        void UpdateKeysAndButtons();
        bool InitGlad();
};


#endif