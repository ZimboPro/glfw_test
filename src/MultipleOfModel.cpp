#include <MultipleOfModel.hpp>
#include <Models.hpp>
#include <Shaders.hpp>
#include <Camera.hpp>

MultipleOfModel::MultipleOfModel(const std::string & path, const float & scale)
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
    AddPoint(Point point{x, y, z, degree});
}

void MultipleOfModel::DeletePoint(Point point)
{
    size_t count = 0;
    for (size_t i = 0; i < this->_points.Size(); i++)
    {
        if (this->_points[i].x == point.x && this->_points[i].y == point.y && this->_points[i].z == point.z)
            break;
        i++;
        count++;
    }

    if (count != this->_points.Size())
        this->_points.erase(this->_points.begin() + count);
}

void MultipleOfModel::DeletePoint(float x, float y, float z)
{
    DeletePoint(Point point{x, y, z});
}

void MultipleOfModel::Draw(Shaders & shader, glm::mat4 perspective, glm::mat4 view)
{
    shader.use();
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);
    for (size_t i = 0; i < this->_points.Size(); i++)
    {
        Point temp = this->_points[i];
        this->_model->DrawAt(shader, temp._x, temp._z, temp._y, temp._degree);
    }
}