#include "scene.hpp"

scene::scene()
    :models(new composite), cameras(new composite)
{
}

void scene::add_model(std::shared_ptr<object> _model)
{
    models->add(_model);
}

void scene::remove_model(long index)
{
    models->remove(index);
}

void scene::add_camera(std::shared_ptr<object> _camera)
{
    cameras->add(_camera);
}

void scene::remove_camera(long index)
{
    cameras->remove(index);
}

void scene::reform(std::shared_ptr<Matrix<double>> reform_mtr)
{
    for (auto _model : *models)
        _model->reform(reform_mtr);
}
/*
std::shared_ptr<model> scene::get_model()
{
    auto iter = models->begin();
    auto iter_end = models->end();
    bool flag = true;

    while (iter != iter_end && flag)
    {
        auto t = iter.get();
        if (iter.get()->GetName() == object)
        {
            flag = false;
        }
        if (flag)
        {
            ++iter;
        }
    }

    if (flag)
    {
        time_t t_time = time(NULL);
        throw ObjectError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    }

    return iter.get();
}
*/
