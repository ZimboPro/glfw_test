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

#include <glad/glad.h>
#include <GLFW/glfw3.h>
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
		unsigned int shaderProgram;
};

#endif
