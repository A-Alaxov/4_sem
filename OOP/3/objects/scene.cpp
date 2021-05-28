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
