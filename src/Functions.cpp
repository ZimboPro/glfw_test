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
#include <MultipleOfModel.hpp>
#include <ModelGroup.hpp>
#include <Font.hpp>
#include <Log.hpp>
#include <Text.hpp>
#include <Texture2d.hpp>
#include <SpriteRender.hpp>
#include <PreProcessor.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include <stdexcept>

Camera camera(glm::vec3(30.0f, 30.0f, 30.0f));
bool firstMouse = true;
float lastX = 800 / 2.0f;
float lastY = 600 / 2.0f;


float deltaTime = 0.0f;
float lastFrame = 0.0f;

Functions::Functions()
{
    this->_width = 800;
    this->_height = 600;
	this->_win = new Window("Bomberman", this->_width, this->_height);
}

Functions::Functions(Functions const & src)
{
	*this = src;	
}

Functions::~Functions()
{
	glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
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
    Shaders spriteshader(R"(../Resources/VertexShaders/SpriteVert.glsl)", R"(../Resources/FragmentShaders/SpriteFrag.glsl)");

    TextureImages texture("../Resources/Textures/wall.jpg");

    SpriteRender sprites(spriteshader);
    camera.LookAt(glm::vec3(0));
	while (!this->_win->closed())
	{
        this->_win->clear(0.2f, 0.3f, 0.3f);

        if (this->_win->isKeyPressed(GLFW_KEY_ESCAPE))
            this->_win->close();

        glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->_width), 0.0f, static_cast<GLfloat>(this->_height));
        spriteshader.use();
        spriteshader.setMat4Ptr("projection", projection);
        sprites.DrawSprite(texture, glm::vec2(250,200),glm::vec2(50, 50));

		this->_win->update();
	}
}

