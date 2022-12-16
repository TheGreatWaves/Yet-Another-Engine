#pragma once

#include <memory>
#include <map>
#include <functional>
#include <cassert>
#include <SFML/Graphics/RenderWindow.hpp>

namespace States
{
	enum class ID
	{

	};

	class StateStack;

	class State
	{
	public:
		using Ptr = std::unique_ptr<State>;
		struct Context
		{
			explicit Context(sf::RenderWindow* window = nullptr);
			sf::RenderWindow* window{};
		};
	public:
		explicit State(StateStack& stack, Context context);
		virtual ~State();

		virtual void draw() = 0;
		virtual bool update(sf::Time dt) = 0;
		virtual bool handleEvent(const sf::Event& event) = 0;

	protected:
		void requestStackPush(ID stateID);
		void requestStackPop();
		void requestStateClear();

		[[nodiscard]] Context getContext() const;

	private:
		Context m_context;
		StateStack* m_stack{};
	};

	class StateStack : private sf::NonCopyable
	{
	public:
		enum Action
		{
			Push,
			Pop,
			Clear,
		};
	public:
		explicit StateStack(State::Context context);
		template <typename T>
		void registerState(ID stateID);
		void update(sf::Time dt);
		void draw();
		void handleEvent(const sf::Event& event);
		void pushState(ID stateID);
		void popState();
		void clearStates();
		bool isEmpty() const;
	private:
		State::Ptr createState(ID stateID);
		void       applyPendingChanges();
	private:
		struct PendingChange
		{
			Action action;
			ID     stateID;
		};
	private:
		std::vector<State::Ptr>                   mStack;
		std::vector<PendingChange>                mPendingList;
		State::Context                            mContext;
		std::map<ID, std::function<State::Ptr()>> mFactories;
	};

}
