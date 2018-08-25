#include <MultipleOfModel.hpp>
#include <Models.hpp>
#include <Shaders.hpp>
#include <Camera.hpp>

MultipleOfModel::MultipleOfModel(char * path, const float & scale)
{
    this->_model = new Model(path);
    this->_model->Scale(scale);
}

MultipleOfModel::MultipleOfModel(Model & model)
{
    this->_model = &model;
}

MultipleOfModel::~MultipleOfModel()
{
    delete this->_model;
    this->_points.clear();
}

void MultipleOfModel::AddPoint(Point point)
{
    this->_points.push_back(point);
}

void MultipleOfModel::AddPoint(float x, float y, float z, float degree)
{
    AddPoint(Point{x, y, z, degree});
}

void MultipleOfModel::DeletePoint(Point point)
{
    size_t count = 0;
    for (size_t i = 0; i < this->_points.size(); i++)
    {
        if (this->_points[i]._x == point._x && this->_points[i]._y == point._y
             && this->_points[i]._z == point._z)
            break;
        i++;
        count++;
    }

    if (count != this->_points.size())
        this->_points.erase(this->_points.begin() + count);
}

void MultipleOfModel::DeletePoint(float x, float y, float z)
{
    DeletePoint(Point{x, y, z, 0});
}

void MultipleOfModel::DrawAt(Shaders & shader, glm::mat4 perspective, glm::mat4 view)
{
    shader.use();
    shader.setMat4("projection", perspective);
    shader.setMat4("view", view);
    for (size_t i = 0; i < this->_points.size(); i++)
    {
        Point temp = this->_points[i];
        this->_model->DrawAt(shader, temp._x, temp._z, temp._y, temp._degree);
    }
}

void MultipleOfModel::Draw(Shaders & shader)
{
    for (size_t i = 0; i < this->_points.size(); i++)
    {
        Point temp = this->_points[i];
        this->_model->DrawAt(shader, temp._x, temp._z, temp._y, temp._degree);
    }
}