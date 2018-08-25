#ifndef MULTIPLEOFMODEL_HPP
#define MULTIPLEOFMODEL_HPP

#include <iostream>
#include <vector>
#include <Structs.hpp>

class Model;
class Shaders;
class Camera;

class MultipleOfModel
{
    public:
        MultipleOfModel(char * path, const float & scale);
        MultipleOfModel(Model & model);
        ~MultipleOfModel();

        void DrawAt(Shaders & shader, glm::mat4 perspective, glm::mat4 view);
        void Draw(Shaders & shader);
        void AddPoint(float x, float y, float z = 0, float degree = 0);
        void AddPoint(Point point);

        void DeletePoint(float x, float y, float z = 0);
        void DeletePoint(Point point);

    private:
        Model * _model;
        std::vector<Point> _points;
};

#endif