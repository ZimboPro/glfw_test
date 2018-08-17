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

#include <stdexcept>

Functions::Functions()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
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
	this->_win = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);
	if (this->_win == NULL)
	{
		std::cout << "fail init" << std::endl;
		glfwTerminate();
		throw std::logic_error("INIT Failed");
	}

	glfwMakeContextCurrent(this->_win);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		throw std::logic_error("glad Failed");
	}

	glViewport(0, 0, 800, 600);


    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};  

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered this->VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind

	

    // You can unbind the this->VAO afterwards so other this->VAO calls won't accidentally modify this this->VAO, but this rarely happens. Modifying other
    // this->VAOs requires a call to glBindVertexArray anyways so we generally don't unbind this->VAOs (nor this->VBOs) when it's not directly necessary.



    glBindVertexArray(VAO);
    
    Shaders basic("/Volumes/LESLIE_DJ/2nd_Year/temp/glfw_test/Resoures/VertexShaders/Basic.vshader", "/Volumes/LESLIE_DJ/2nd_Year/temp/glfw_test/Resoures/FragmentShaders/Basic.fshader");
    basic.use();

	while (!glfwWindowShouldClose(this->_win))
	{
		ProcessInput();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(this->_win);
		glfwPollEvents();
	}
}

void Functions::ProcessInput()
{
	if (glfwGetKey(this->_win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(this->_win, true);
}

void Functions::DrawBlock(int x, int y, int r, int g, int b)
{
    float xf = static_cast<float>(x - 400) / 400;
    float yf = static_cast<float>(y - 300) / 300;
    float x1 = static_cast<float>(x - 400 + 20) / 400;
    float y1 = static_cast<float>(y - 300 + 20) / 300;
    float rf = static_cast<float>(r) / 255;
    float gf = static_cast<float>(g) / 255;
    float bf = static_cast<float>(b) / 255;
    float arr [] = {
        xf, yf, 0, rf, gf, bf,
        x1, yf, 0, rf, gf, bf,
        xf, y1, 0, rf, gf, bf
    };
    unsigned int va;
    unsigned int vb;
}
