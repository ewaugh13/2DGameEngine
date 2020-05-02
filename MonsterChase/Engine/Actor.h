#pragma once

#include "SmartPtr.h"
#include "Vector3.h"

#include <map>
#include <string.h>
#include <vector>

namespace Engine
{
	// interface for components
	class IActorComponent
	{
	public:
		~IActorComponent()
		{}

		virtual void BeginUpdate(float)
		{}
		virtual void Update(float)
		{}
		virtual void EndUpdate(float)
		{}
	};

	class ComponentDestructor
	{
	public:
		static void release(IActorComponent * i_ptr) { delete i_ptr; }
	};

	class Actor
	{
	public:

		static SmartPtr<Actor> CreateActor(const char * i_Name, Vector3 & i_InitPosition);

		Actor(const Actor & i_OtherActor);

		~Actor();

#pragma region Getters and Setters

		char * GetName() const { return m_name; }
		void SetName(const char * i_name) { m_name = const_cast<char *>(i_name); }

		Vector3& GetPosition() { return m_position; }
		void SetPosition(const Vector3& i_position) { m_position = i_position; }

		float GetZRotation() const { return m_ZRotation; }
		void SetZRotation(float i_ZRotation) { m_ZRotation = i_ZRotation; }

#pragma endregion

		Vector3 GetVelocity() const;

		// add component
		void AddComponent(std::string i_ComponentName, IActorComponent * i_NewComponent);
		// get component
		IActorComponent * GetComponent (const std::string & i_ComponentName) const;

		// update
		void BeginUpdate(float i_DeltaTime);
		void Update(float i_DeltaTime);
		void EndUpdate(float i_DeltaTime);

	private:

		// only can create an actor through a smartptr
		Actor(const char * i_name, const Vector3 & i_initalPosition, float i_zRotation = 0.0f);

		char * m_name;
		Vector3 m_position;
		float m_ZRotation;

		std::map<std::string, IActorComponent*> m_Components;
	};
}

#include "Actor-inl.h"
