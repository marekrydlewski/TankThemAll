#pragma once
#include<vector>
#include <iostream>
#include "Bullet.h"
#include "Model.h"


using namespace std;
namespace BasicEngine
{
	namespace Rendering
	{
		namespace Models
		{
			class Bullets :
				public Model
			{
			public:
				Bullets();
				virtual ~Bullets();
				virtual void Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override;
				virtual void Update()           override;
				void Create();
				virtual void AddBullet(const glm::mat4& bullet_model_matrix, GLfloat angle);
				vector<Bullet*> listOfBullets;
			};
		}

	}
}