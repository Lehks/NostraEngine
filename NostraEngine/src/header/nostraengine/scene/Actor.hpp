#ifndef NOE_SCENE_ACTOR_HPP
#define NOE_SCENE_ACTOR_HPP



namespace NOE
{
	class AbstractActor
	{

	public:
		/*
		\brief standard constructor of the class AbstractActor
		*/

		AbstractActor();


		/*
		\brief A function that calls the update function for all actors and their children and safes in a vector
		\return the new position of the actors which are updated by the function {updateImpl()}
		*/

		virtual void updateImpl() = 0;
	};


	class  Actor : public AbstractActor
	{
	private : 

		Actor();
		/*
		\ id number of the Actor
		*/
		long m_id ;

		/*
		\ if static is true the actors children becomes updated and the parent stay not updated but is static false parent and all children will updated
		*/

		bool m_static;

		/*
		\ the main actor will call parent and he can have children 
		*/

		Actor& m_parent; 

		/*
		\ a vector from type actor that safes the children from a parent actor
		*/

		vector<Actor> child;


	public :

		/*
		\ A function 
		*/

		void init();

		/*
		\ A function that shutdowns the scene 
		*/

		void shutdown();

		/*
		\ brief A function that updated an actor that means the actor get a new position on the map 
		\ param transformation from type Transformation { that means new position , rotation and scaling } for the actor
		\return the new data for the actor 
		*/

		void update();

		/*
		\ brief A function that gives you the current transformation {position , rotation and scaling }
		\ return position , rotation and scaling
		*/

		void getTransormation(); 


		/*
		\ brief A function that will give you the parent from an actor 
		\ return parent actor 
		*/

		Actor& getParent(); 


		/*
		\brief A function that allows you to set a new parent 
		\param "parent" from type actor so you give an actor object as paramter
		\ return the new parent 
		*/

		void setParent(Actor& parent); 


		/*
		\brief A function that gives you all children from a parent actor
		\return all children in a vector
		*/

		NOE::NOU_DAT_ALG_VECTOR::Vector<Actor> getChild();

		/*
		\brief A function that allows you to set new children for a parent actor
		\param "child" child is a vector from type actor 
		\ return new children for a parent 
		*/

		void setChild(NOE::NOU_DAT_ALG_VECTOR::Vector<Actor> child);

	};
}

#endif // !NOE_SCENE_ACTOR_HPP
