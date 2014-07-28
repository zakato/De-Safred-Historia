#include <SceneNode\SceneNode.hpp>

#include <algorithm>
#include <assert.h>


namespace zkt
{
	SceneNode::SceneNode()
		: m_children()
		, m_parent(nullptr)
	{
	}

	void SceneNode::attachChild(Ptr Child)
	{
		Child->m_parent = this;
		m_children.push_back(std::move(Child));
	}


	//SceneNode::Ptr	SceneNode::detachChild(const SceneNode& node)
	//{
	//	auto found = std::find_if(m_children.begin(), m_children.end(), [&](Ptr& p) { return p.get() == &node; } );
	//	assert(found != m_children.end());
	//	return found;
	//}



}