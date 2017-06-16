#pragma once

#include <map>

namespace Library
{
	class ServiceContainer final
	{
	public:
		ServiceContainer() = default;
		ServiceContainer(const ServiceContainer&) = delete;
		ServiceContainer& operator=(const ServiceContainer&) = delete;
		ServiceContainer(ServiceContainer&&) = delete;
		ServiceContainer& operator=(ServiceContainer&&) = delete;
		~ServiceContainer() = default;

		void AddService(std::uint64_t typeID, void* service);
		void RemoveService(std::uint64_t typeID);
		void* GetService(std::uint64_t typeID) const;

		std::map<std::uint64_t, void*> mServices;
	};
}