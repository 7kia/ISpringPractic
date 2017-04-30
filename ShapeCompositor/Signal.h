#pragma once
#include <boost/signals2.hpp>

namespace signal
{
	template <typename Handler>
	using Signal = boost::signals2::signal<Handler>;

	using Connection = boost::signals2::connection;

	using ScopedConnection = boost::signals2::scoped_connection;

	using EmptySignal = Signal<void()>;

}