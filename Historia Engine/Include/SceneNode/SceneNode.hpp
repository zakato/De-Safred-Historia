#include <SFML\System\NonCopyable.hpp>
#include <SFML\System\Time.hpp>
#include <SFML\Graphics\Transformable.hpp>
#include <SFML\Graphics\Drawable.hpp>

#include <vector>
#include <memory>


namespace zkt
{

	class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
	{

		typedef std::unique_ptr<SceneNode> Ptr;

	public:

		SceneNode();

		void	attachChild(Ptr child);
		Ptr		detachChild(const SceneNode& node);

		sf::Vector2f	getWorldPosition() const;
		sf::Transform	getWorldTransform() const;


	private:
		std::vector<Ptr>	m_children;
		SceneNode*			m_parent;

	};
}