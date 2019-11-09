#include "Actor.h"
#include <stdlib.h>
#include <assert.h>

Actor::~Actor()
{
	if (this->m_name)
	{
		free(this->m_name);
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
