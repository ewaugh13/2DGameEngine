#include "Actor.h"
#include <stdlib.h>
#include <assert.h>

Actor::Actor(const Actor & i_OtherActor) : 
	m_name(_strdup(i_OtherActor.m_name)), m_position(i_OtherActor.m_position), m_Components(i_OtherActor.m_Components)
{
}

Actor::~Actor()
{
	if (this->m_name)
	{
		free(this->m_name);
	}

	for (size_t i = 0; i < m_Components.size(); i++)
	{
		assert(m_Components[i]);
		delete m_Components[i];
	}
}

void Actor::AddComponent(IActorComponent * m_pNewComponent)
{
	this->m_Components.push_back(m_pNewComponent);
}

void Actor::BeginUpdate()
{
	const size_t count = this->m_Components.size();
	for (size_t i = 0; i < count; i++)
	{
		assert(this->m_Components[i]);
		m_Components[i]->BeginUpdate(*this);
	}
}

void Actor::Update()
{
	const size_t count = this->m_Components.size();
	for (size_t i = 0; i < count; i++)
	{
		assert(this->m_Components[i]);
		m_Components[i]->Update(*this);
	}
}

void Actor::EndUpdate()
{
	const size_t count = this->m_Components.size();
	for (size_t i = 0; i < count; i++)
	{
		assert(this->m_Components[i]);
		m_Components[i]->EndUpdate(*this);
	}
}
