#include "State.hpp"

States::State::State(StateStack& stack, Context context): m_context()
{
}

States::State::~State()
{
}

void States::State::requestStackPush(States::ID stateID)
{
}

void States::State::requestStackPop()
{
}

void States::State::requestStateClear()
{
}

States::State::Context States::State::getContext() const
{
	return m_context;
}

States::StateStack::StateStack(States::State::Context context): mContext()
{
}

template <typename T>
void States::StateStack::registerState(States::ID stateID)
{
}

void States::StateStack::update(sf::Time dt)
{
}

void States::StateStack::draw()
{
}

void States::StateStack::handleEvent(const sf::Event& event)
{
}

void States::StateStack::pushState(States::ID stateID)
{
}

void States::StateStack::popState()
{
}

void States::StateStack::clearStates()
{
}

bool States::StateStack::isEmpty() const
{
	return false;
}

States::State::Ptr States::StateStack::createState(States::ID stateID)
{
	auto found = mFactories.find(stateID);
	assert(found != mFactories.end());
	return found->second();
}

void States::StateStack::applyPendingChanges()
{
}

States::State::Context::Context(sf::RenderWindow* window)
	: window{ window }
{
}
