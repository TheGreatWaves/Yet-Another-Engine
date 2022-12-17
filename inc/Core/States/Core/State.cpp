#include "State.hpp"

States::State::State(StateStack& stack, Context context)
	: m_context( context )
	, m_stack( &stack )
{
}

States::State::~State()
{
}

void States::State::requestStackPush(States::ID stateID)
{
	m_stack->pushState(stateID);
}

void States::State::requestStackPop()
{
	m_stack->popState();
}

void States::State::requestStateClear()
{
	m_stack->clearStates();
}

States::State::Context States::State::getContext() const
{
	return m_context;
}

States::StateStack::StateStack(States::State::Context context)
	: mContext{ context }
{
}

void States::StateStack::update(const sf::Time& dt)
{
	// Iterate from top to bottom, stop as soon as update() returns false
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->update(dt))
		{
			break;
		}
	}

	applyPendingChanges();
}

void States::StateStack::draw()
{
	for (const auto& state : mStack)
	{
		state->draw();
	}
}

void States::StateStack::handleEvent(const sf::Event& event)
{
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->handleEvent(event))
			return;
	}
	applyPendingChanges();
}

void States::StateStack::pushState(States::ID stateID)
{
	mPendingList.emplace_back(Push, stateID);
}

void States::StateStack::popState()
{
	mPendingList.emplace_back(Pop);
}

void States::StateStack::clearStates()
{
	mPendingList.emplace_back(Clear);
}

bool States::StateStack::isEmpty() const
{
	return mStack.empty();
}

States::State::Ptr States::StateStack::createState(States::ID stateID)
{
	const auto found = mFactories.find(stateID);
	assert(found != mFactories.end());
	return found->second();
}

void States::StateStack::applyPendingChanges()
{
	for (const auto& change : mPendingList)
	{
		switch (change.action)
		{
			case Push:
			{
				mStack.push_back(createState(change.stateID));
				break;
			}
			case Pop:
			{
				mStack.pop_back();
				break;
			}
			case Clear:
			{
				mStack.clear();
				break;
			}
		}
	}

	mPendingList.clear();
}

States::State::Context::Context(sf::RenderWindow* window)
	: window{ window }
{
}

States::StateStack::PendingChange::PendingChange(Action _action, ID _stateID)
	: action( _action )
	, stateID( _stateID )
{
}
