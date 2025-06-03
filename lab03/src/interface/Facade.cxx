#include "objects/Model.hpp"
#include "visitor/TransformVisitor.hpp"
#include <QGraphicsScene>
#include <interface/Facade.hpp>

Facade::Facade(std::shared_ptr<QGraphicsScene> graphicsScene)
{
    sceneManager = std::make_shared<SceneManager>();
    drawManager = std::make_shared<DrawManager>(graphicsScene);

    drawManager->setSceneManager(sceneManager);

    std::vector<Point> verts = {{0, 0, 0}, {100, 100, 100}, {100, 0, 0}, {50, 0, 50}};
    std::vector<Edge> edges = {{0, 3}, {0, 2}, {2, 3}, {0, 1}, {2, 1}, {3, 1}};

    std::shared_ptr<Wireframe> wireframe = std::make_shared<Wireframe>(verts, edges);

    std::shared_ptr<Scene> scene = std::make_shared<Scene>();
    std::shared_ptr<Model> model = std::make_shared<Model>(wireframe);

	Matrix<double> mx = {
		{1, 0, 0},
		{0, 1, 0},
		{0, 0, 1}
	};

	mx *= 5;
	Matrix<double> rotMx = {
		{1, 0, 0},
		{0, 0.7, -0.7},
		{0, 0.7, 0.7}
	};
	mx *= rotMx;

	std::shared_ptr<TransformVisitor> vis = std::make_shared<TransformVisitor>(mx);
	model->accept(vis);

    scene->add(model);
    sceneManager->setScene(scene);
}

void Facade::execute(std::shared_ptr<Command> command)
{
    command->setManagers(sceneManager, drawManager);
    command->execute();
}
