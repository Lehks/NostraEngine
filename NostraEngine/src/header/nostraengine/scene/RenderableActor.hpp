#ifndef NOE_SCENE_RENDERABLE_ACTOR_HPP
#define NOE_SCENE_RENDERABLE_ACTOR_HPP

#include "nostrautils/NostraUtils.hpp"

#include "nostraengine/NostraEngine.hpp"

#include "nostraengine/core/StdIncludes.hpp"

#include "nostraengine/renderer/RenderableImpl.hpp"
#include "nostraengine/renderer/RenderableImplFactory.hpp"

/**
\file scene/RenderableActor.hpp

\author	 Lukas Gross
\version 0.0.1
\since   0.0.1

\brief A file that contains the RenderableActor.
*/
namespace NOE::NOE_SCENE
{
	/**
	\brief					A class that stores all information for a renderable.
	*/
	class RenderableActor
	{
	private:

		/**
		\brief				Defines if the renderable is enabled for rendering.
		*/
		NOU::boolean m_renderingEnabled;

		/**
		\brief				Points to an instance of a RenderableImpl.

		\details			Is a null pointer if no factory was found.
		*/
		NOE::NOE_RENDERER::RenderableImpl* m_ptr;

		/**
		\brief				The factories that can be used for creating a new renderable.
		*/
		static NOU::NOU_DAT_ALG::Vector<NOE::NOE_RENDERER::RenderableImplFactory*> m_factories;

	public:

		/**
		\param identifier	The identifier of the factory, that is used for creating the renderable.

		\brief				Constructs a new RenderableActor.

		\details			When a new renderable is created, an identifier will be passed to identify the
							correct factory. Dependent on this identifier the corresponding factory will be 
							used to create a new instance of a RenderableImpl.
		*/
		NOE_FUNC RenderableActor(NOU::sizeType identifier);

		/**
		\brief				Destructor of the RenderableActor.
		*/
		NOE_FUNC ~RenderableActor();

		/**
		\return				True if the renderable will be rendered in the next frame, false if not.

		\brief				Returns the status of the renderable.
		*/
		NOE_FUNC NOU::boolean getEnabled() const;

		/**
		\param enable		Defines if the renderable will be enabled.

		\brief				Sets the renderable to true, if it should be rendered and false if not.
		*/
		NOE_FUNC void setEnabled(NOU::boolean enable);
		
		/**
		\param renderable	The renderable of the previous frame.

		\brief				Binds the meshes and textures to an renderable. If no change was made,
							it uses the previous bind.
		*/
		NOE_FUNC void bind(const RenderableActor renderable) const;

		/**
		\param factory		The factory that is passed.
		\param identifier	The identifier of the factory.

		\return				Returns true if a factory was added and false if the operation failed.

		\brief				Adds a factory to the m_factories vector. 
		
		\details			The identifier is use to:
							-Check if a factory with the same identifier is already in the vector.
							-And for creating an renderable with this identifier (For further details take a 
							look in the constructor documentation of this class). 
		*/
		NOE_FUNC static NOU::boolean addFactory(NOE::NOE_RENDERER::RenderableImplFactory* factory,
			NOU::sizeType identifier);

		/**
		\param other		The RenderableActor that will be compared.

		\return				True if the RenderableActors are equal, false if not.

		\brief				Checks if the underlying RenderableImpl is the same.
		*/
		NOU::boolean operator == (const RenderableActor& other) const;

		/**
		\param other		The RenderableActor that will be compared.

		\return				True if the RenderableActors are smaller, false if not.

		\brief				Checks if the underlying RenderableImpl is smaller.
		*/
		NOU::boolean operator < (const RenderableActor& other) const;

		/**
		\param other		The RenderableActor that will be compared.

		\return				True if the RenderableActors are bigger, false if not.

		\brief				Checks if the underlying RenderableImpl is bigger.
		*/
		NOU::boolean operator > (const RenderableActor& other) const;
	};
}

#endif