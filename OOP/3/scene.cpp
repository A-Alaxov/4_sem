#include "scene.hpp"

scene::scene()
    :models(new composite)
{
}

void scene::add_model(std::shared_ptr<model> _model)
{
    models->add(_model);
}
