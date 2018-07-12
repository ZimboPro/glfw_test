/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Functions.hpp                                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage   <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 12/47/59 by lde-jage          #+#    #+#             */
/*   Updated: 2018/07/11 12/47/59 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		FUNCTIONS_HPP
# define	FUNCTIONS_HPP

#include "../libglad/include/glad/glad.h"
#include "../libogd/include/GLFW/glfw3.h"
#include <iostream>

class Functions {
	public:
		Functions();
		Functions(Functions const & src);
		~Functions();
		Functions & operator=(Functions const & src);

		void Loop();

	private:
		GLFWwindow * _win;
		void ProcessInput();
		void DrawBlock(int r, int c, int cr, int cg, int cb);
		unsigned int VAO;
		unsigned int VBO;
		int shaderProgram;

		const char * vertex = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aCol;\n"
	"out vec4 ourColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "   ourColor = aColor;\n"
    "}\0";

		const char * fragment = "#version 330 core\n"
    "out vec4 FragColor;\n"
	"in vec4 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(ourColor, 1.0f);\n"
    "}\n\0";

};

#endif
