#pragma once

#include "Common.hpp"
#include <unordered_map>
#include <memory>

namespace resources
{

	enum class TextureID
	{
	};

	enum class FontID
	{
	};

	template <typename IDType, typename ResourceType>
	class ResourceHolder
	{
	public:
		// Loads a resource from the specified file and associates it with the given ID
		void Load(IDType id, const std::string& filename);

		// Returns a reference to the resource with the given ID
		ResourceType& Get(IDType id);

		// Returns a const reference to the resource with the given ID
		const ResourceType& Get(IDType id) const;

		template <typename ParameterType>
		void Load(IDType id, const std::string& filename,
			const ParameterType& second_param);

	private:
		// Map of resource IDs to resource pointers
		std::unordered_map<IDType, std::unique_ptr<ResourceType>> resource_map;
	};

	// Loads a resource from the specified file and associates it with the given ID
	template <typename IDType, typename ResourceType>
	void ResourceHolder<IDType, ResourceType>::Load(IDType id,
		const std::string& filename)
	{
		// Create a new resource object
		auto resource = std::make_unique<ResourceType>();

		// Load the resource from the file
		if (!resource->loadFromFile(filename)) {
			// If the resource could not be loaded, throw an exception
			throw std::runtime_error("ResourceHolder::Load - Failed to load " + filename);
		}

		// Insert the resource into the map, using the ID as the key
		// The std::move function is used to transfer ownership of the resource to the map
		auto [iterator, success] = resource_map.insert({ id, std::move(resource) });

		// Assert that the insertion was successful
		assert(success);
	}

	// Returns a reference to the resource with the given ID
	template <typename IDType, typename ResourceType>
	ResourceType& ResourceHolder<IDType, ResourceType>::Get(IDType id)
	{
		// Use find to search for the resource in the map
		auto found = resource_map.find(id);

		// Assert that the resource was found
		assert(found != resource_map.end());

		// Return a reference to the resource
		return *found->second;
	}

	// Returns a const reference to the resource with the given ID
	template <typename IDType, typename ResourceType>
	const ResourceType& ResourceHolder<IDType, ResourceType>::Get(IDType id) const
	{
		// Use find to search for the resource in the map
		auto found = resource_map.find(id);

		// Assert that the resource was found
		assert(found != resource_map.end());

		// Return a const reference to the resource
		return *found->second;
	}

	template <typename IDType, typename ResourceType>
	template <typename ParameterType>
	void ResourceHolder<IDType, ResourceType>::Load(IDType id,
		const std::string& filename,
		const ParameterType& second_param)
	{
		// Create a new resource object
		auto resource = std::make_unique<ResourceType>();

		if (!resource->loadFromFile(filename, second_param)) {
			throw std::runtime_error("ResourceHolder::Load - Failed to load " + filename);
		}
		// Insert the resource into the map, using the ID as the key
		// The std::move function is used to transfer ownership of the resource to the map
		auto [iterator, success] = resource_map.insert({ id, std::move(resource) });

		// Assert that the insertion was successful
		assert(success);
	}

	// Aliases for resource holders specialized for textures and fonts
	using TextureHolder = ResourceHolder<TextureID, sf::Texture>;
	using FontHolder = ResourceHolder<FontID, sf::Font>;

}
