#include <iostream>
#include <box2d/box2d.h>
#include <box2cpp/box2cpp.h>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include "entities.h"

int main()
{
	sf::ContextSettings settings;
	settings.antiAliasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(sf::Vector2u(1920, 1080)), "Evil Window", sf::Style::Default, sf::State::Windowed, settings);
	ImGui::SFML::Init(window);



	// Box2d / Box2cpp examples

	// Box2d works best with low-scale sizes, from 0-10.0f (ish) so since our world will be much larger
	// for example 4000x4000, we need to set a fair scale so 1.0f / 50.0f is good enough

	// We will use this to scale up or down to each system as necessary
	constexpr float B2_SCALE = 50.0f;
	// We also do the inverse, since we can multiply this instead of divide. We use either or
	constexpr float B2_SCALE_INVERSE = 1.0f / B2_SCALE;



	// We initialize a world with no gravity
	b2::World w(b2::World::Params{});
	w.SetGravity({ 0.0f, 0.0f });

	// We will make a bouncy ball and give it starting force
	// First we define the body parameters
	b2::Body::Params ball_def{};
	ball_def.type = b2_dynamicBody;
	ball_def.linearDamping = 1.0f;
	ball_def.position = {1920.0f / 2.0f * B2_SCALE_INVERSE, 1080.0f / 2.0f * B2_SCALE_INVERSE};

	// Now the shape
	b2::Shape::Params ball_shape{};
	ball_shape.density = 1.0f;
	ball_shape.material.restitution = 1.0f; // restitution is bounciness, 1.0f means it keeps all the force it had when hitting something
	// if restitution is above 1.0f, it means it will gain force when bouncing. mega bounce

	// We create this body in da world
	b2::Body ball_body = w.CreateBody(b2::OwningHandle, ball_def);
	// gib it shape
	ball_body.CreateShape(b2::DestroyWithParent, ball_shape, b2Circle{ .radius = 5.0f * B2_SCALE_INVERSE});

	// give it a bit of force
	ball_body.ApplyForce({50.0f * B2_SCALE_INVERSE, 50.0f * B2_SCALE_INVERSE}, {0.0f, 0.0f}, true);


	// we make an sfml circle for this
	sf::CircleShape ball_sprite(5.0f);
	ball_sprite.setOrigin({5.0f, 5.0f});
	ball_sprite.setFillColor(sf::Color::Yellow);


	// I think this is not how we should implement this in the future, maybe have dedicated system tied with simulation for it, but this will be our delta time thingimabop

	// sfml has a fairly good implementation for a clock as well
	sf::Clock clock;
	float accumulator = 0.0f;
	float dt = 1.0f / 144.0f;

	sf::Clock delta_clock;
	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			ImGui::SFML::ProcessEvent(window, *event);

			if (event->is<sf::Event::Closed>())
				window.close();

		}
		ImGui::SFML::Update(window, delta_clock.restart());


		float frame = clock.restart().asSeconds();
		accumulator += frame;

		while (accumulator >= dt) {
			// 1 step means it will simulate dt amount of time, 1 / 144.0f is fairly good
			// the substep is important for accuracy, it separates each step into iterations to make sure certain things like
			// collisions are handled well
			w.Step(dt, 8);


			// this should NOT be here but for now its ok
			ball_sprite.setPosition({ball_body.GetPosition().x * B2_SCALE, ball_body.GetPosition().y * B2_SCALE});


			accumulator -= dt;
		}


		window.clear();

		window.draw(ball_sprite);

		if (ImGui::Begin("Ball Touching GUI")) {
			ImGui::Text("Ball Position: %.2f x, %.2f y", ball_body.GetPosition().x * B2_SCALE, ball_body.GetPosition().y * B2_SCALE);

			if (ImGui::Button("press me..."))
				{
				ball_body.ApplyForce({0.00f, 100.0f * B2_SCALE_INVERSE}, {0.00f, 0.00f}, true);
			}

		}ImGui::End();

		ImGui::SFML::Render(window);

		window.display();
	}
}
