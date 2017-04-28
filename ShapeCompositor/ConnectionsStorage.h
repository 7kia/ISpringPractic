#pragma once
#include <vector>
#include "Signal.h"

struct ScopedConnectionsStorage
{
	ScopedConnectionsStorage& operator+=(const signal::Connection & conn)
	{
		m_items.emplace_back(conn);
		return *this;
	}
	ScopedConnectionsStorage& operator+=(signal::Connection && conn)
	{
		m_items.emplace_back(std::move(conn));
		return *this;
	}
	ScopedConnectionsStorage& operator+=(signal::ScopedConnection && conn)
	{
		m_items.emplace_back(std::move(conn));
		return *this;
	}
	ScopedConnectionsStorage& operator += (std::initializer_list<signal::Connection> const & connections)
	{
		for (const auto & con : connections)
		{
			*this += con;
		}
		return *this;
	}
private:
	std::vector<signal::ScopedConnection> m_items;
};