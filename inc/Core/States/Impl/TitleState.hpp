#pragma once

#include "../Core/State.hpp"
#include "../../../Utils.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

class TitleState : public States::State
{
public:
					TitleState(States::StateStack& stack, States::State::Context context);

					void draw() override;
					bool update(const sf::Time& dt) override;
					bool handleEvent(const sf::Event& event) override;

private:

	sf::RectangleShape	background_sprite_;
	sf::Text			text_;

	// TEMPORARY: TODO: REMOVE THIS
	sf::Font			font_;

	sf::Time			time_elapsed_{ sf::Time::Zero };
};

inline TitleState::TitleState(States::StateStack& stack, States::State::Context context)
	: State(stack, context)
{
	const auto*      window = context.window;
	const auto size = window->getSize();

	// Set up....
	this->background_sprite_.setSize({static_cast<float>(size.x), static_cast<float>(size.y)});
	this->background_sprite_.setFillColor(sf::Color(20, 20, 20));

	this->font_.loadFromFile("../../../Resources/Fonts/Sansation.ttf");
	this->text_.setFont(this->font_);
	this->text_.setString("0.00");
	this->text_.setCharacterSize(30);
	Utils::Text::CenterOrigin(this->text_);
	this->text_.setPosition(context.window->getView().getSize() / 2.f);
	
}

inline bool TitleState::update(const sf::Time& dt)
{
	time_elapsed_ += dt;

	const auto string = std::to_string(time_elapsed_.asSeconds());
	this->text_.setString(string);
	
	return true;
}

inline void TitleState::draw()
{
	auto* window = getContext().window;

	window->draw( this->background_sprite_ );
	window->draw(this->text_);
}

inline bool TitleState::handleEvent(const sf::Event& event)
{
	// If any key is pressed, trigger the next screen
	if (event.type == sf::Event::KeyPressed)
	{
		requestStackPop();
	}

	return true;
}