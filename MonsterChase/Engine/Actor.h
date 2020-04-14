#pragma once

#include "SmartPtr.h"
#include "Vector3.h"

#include <string.h>
#include <vector>

namespace MyEngine
{
	class IActorComponent;

	class Actor
	{
	public:

		static SmartPtr<Actor> CreateActor(const char * i_ScriptFilename);

		Actor(const Actor & i_OtherActor);

		~Actor();

#pragma region Getters and Setters
		char * GetName() const { return m_name; }
		void SetName(const char * i_name) { m_name = const_cast<char *>(i_name); }

		Vector3& GetPosition() { return m_position; }
		void SetPosition(const Vector3& i_position) { m_position = i_position; }
#pragma endregion

		// add component
		void AddComponent(IActorComponent * m_pNewComponent);
		// get component
		template<typename ComponentType>
		IActorComponent * GetComponent();

		// update
		void BeginUpdate();
		void Update();
		void EndUpdate();

	private:

		// only can create an actor through a smartptr
		Actor(const char * i_name, const Vector3 & i_initalPosition);

		char * m_name;
		Vector3 m_position;
		std::vector<IActorComponent *> m_Components;
	};

	// interface for components
	class IActorComponent
	{
	public:
		virtual void BeginUpdate(Actor &)
		{}
		virtual void Update(Actor &)
		{}
		virtual void EndUpdate(Actor &)
		{}
	};

}

#include "Actor-inl.h"
