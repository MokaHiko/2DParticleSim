#include "SpriteRenderer.h"
#include <glm/ext/matrix_transform.hpp>

SpriteRenderer::SpriteRenderer(Shader& shader, float screenWidth, float screenHeight)
	:shader(shader), screenWidth(screenWidth), screenHeight(screenHeight)
{
	initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
	glDeleteVertexArrays(1, &quadVAO);
}

void SpriteRenderer::DrawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color)
{
	//prepare transformations	
	shader.Use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));

	model = glm::translate(model, glm::vec3(0.5 * size.x, 0.5 * size.y, 0.0)); //re translate after rotation
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0, 0, 1.0));

	model = glm::translate(model, glm::vec3(-0.5 * size.x, -0.5 * size.y, 0.0)); //rotation occur at 0,0 so we need to center origin
	
	model = glm::scale(model, glm::vec3(size, 1.0f));

	shader.SetMatrix4("model", model);
	shader.SetVector3f("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void SpriteRenderer::initRenderData()
{
	// configure VAO/VBO
	unsigned int VBO;
	float vertices[] = {
		// pos // tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
		GL_STATIC_DRAW);

	glBindVertexArray(quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
		(void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}
