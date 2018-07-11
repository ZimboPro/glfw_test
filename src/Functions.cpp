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

#include "../include/Functions.hpp"
#include <stdexcept>

Functions::Functions()
{
	glfwInit();
	this->_win = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);
	if (this->_win == NULL)
	{
		std::cout << "fail init" << std::endl;
		glfwTerminate();
		throw std::logic_error("INIT Failed");
	}
	glfwMakeContextCurrent(this->_win);
	glViewport(0, 0, 800, 600);
}

Functions::Functions(Functions const & src)
{
	*this = src;	
}

Functions::~Functions()
{
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
	float vet[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};
	
	//vertex input
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vet), vet, GL_STATIC_DRAW);

	//vertex shader
	unsigned int vertShader;
	vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, this->vertex, NULL);
	glCompileShader(vertShader);

	int success;
	char info[512];
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(vertShader, 512, NULL, info);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info << std::endl;
		throw std::logic_error("compile error");
	}

	//fragment shader
	unsigned int fragShader;
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, this->fragment, NULL);
	glCompileShader(fragShader);

	//shader program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertShader);
	glAttachShader(shaderProgram, fragShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, info);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << info << std::endl;
		throw std::logic_error("link error");
	}

	glUseProgram(shaderProgram);
	glDeleteShader(vertShader);
	glDeleteShader(fragShader); 

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(this->_win))
	{
		ProcessInput();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(this->_win);
		glfwPollEvents();
	}
}

void Functions::ProcessInput()
{
	if (glfwGetKey(this->_win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(this->_win, true);
}
