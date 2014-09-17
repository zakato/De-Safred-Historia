#include <Collision\QuadTree.hpp>


namespace zkt {

	QuadTree::QuadTree(float _x, float _y, float _width, float _height, int _level, int _maxLevel) :
		m_shape(_x, _y, _width, _height),
		m_level(_level),
		m_maxLevel(_maxLevel)
	{


		if (m_level == m_maxLevel) {
			return;
		}

		m_NW = new QuadTree(m_shape.left, m_shape.top, m_shape.width / 2.0f, m_shape.height / 2.0f, m_level + 1, m_maxLevel);
		m_NE = new QuadTree(m_shape.left + m_shape.width / 2.0f, m_shape.top, m_shape.width / 2.0f, m_shape.height / 2.0f, m_level + 1, m_maxLevel);
		m_SW = new QuadTree(m_shape.left, m_shape.top + m_shape.height / 2.0f, m_shape.width / 2.0f, m_shape.height / 2.0f, m_level + 1, m_maxLevel);
		m_SE = new QuadTree(m_shape.left + m_shape.width / 2.0f, m_shape.top + m_shape.height / 2.0f, m_shape.width / 2.0f, m_shape.height / 2.0f, m_level + 1, m_maxLevel);
	}

	QuadTree::~QuadTree()
	{
		if (m_level == m_maxLevel)
			return;

		delete m_NW;
		delete m_NE;
		delete m_SW;
		delete m_SE;
	}

	void QuadTree::AddObject(artemis::Entity* object) {
		
		if (m_level == m_maxLevel) {
			m_objects.push_back(object);
			return;
		}
		if (contains(m_NW, object)) {
			m_NW->AddObject(object); 
		}
		if (contains(m_NE, object)) {
			m_NE->AddObject(object); 
		}
		if (contains(m_SW, object)) {
			m_SW->AddObject(object); 
		}
		if (contains(m_SE, object)) {
			m_SE->AddObject(object); 
		}
		if (contains(this, object)) {
			m_objects.push_back(object);
		}
	}

	std::vector<artemis::Entity*> QuadTree::GetObjectsAt(float _x, float _y) {
		if (m_level == m_maxLevel) {
			return m_objects;
		}

		std::vector<artemis::Entity*> returnObjects, childReturnObjects;
		if (!m_objects.empty()) {
			returnObjects = m_objects;
		}
		if (_x > m_shape.left + m_shape.width / 2.0f && _x < m_shape.left + m_shape.width) {
			if (_y > m_shape.top + m_shape.height / 2.0f && _y < m_shape.top + m_shape.height) {
				childReturnObjects = m_SE->GetObjectsAt(_x, _y);
				returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
				return returnObjects;
			}
			else if (_y > m_shape.top && _y <= m_shape.top + m_shape.height / 2.0f) {
				childReturnObjects = m_NE->GetObjectsAt(_x, _y);
				returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
				return returnObjects;
			}
		}
		else if (_x > m_shape.left && _x <= m_shape.top + m_shape.width / 2.0f) {
			if (_y > m_shape.top + m_shape.height / 2.0f && _y < m_shape.top + m_shape.height) {
				childReturnObjects = m_SW->GetObjectsAt(_x, _y);
				returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
				return returnObjects;
			}
			else if (_y > m_shape.top && _y <= m_shape.top + m_shape.height / 2.0f) {
				childReturnObjects = m_NW->GetObjectsAt(_x, _y);
				returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
				return returnObjects;
			}
		}
		return returnObjects;
	}


	void QuadTree::Clear() {
		if (m_level == m_maxLevel) {
			m_objects.clear();
			return;
		}
		else {
			m_NW->Clear();
			m_NE->Clear();
			m_SW->Clear();
			m_SE->Clear();
		}
		if (!m_objects.empty()) {
			m_objects.clear();
		}
	}


	/*void QuadTree::checkCollision( QuadTree* node) 
	{
		if ()
		for (artemis::Entity* e1 : node->m_objects)
		{
			for (artemis::Entity* e2 : node->m_objects)
			{
				if (e1->getId() != e2->getId())
				{
					cCollider* collider1 = (cCollider*)e1->getComponent<cCollider>();
					cCollider* collider2 = (cCollider*)e2->getComponent<cCollider>();

					if (collider1->getCollider().getBoxCollider().intersects(collider2->getCollider().getBoxCollider()))
					{
						collider1->setCollision(true);
						collider2->setCollision(true);
					}

				}
			}
		}
	}*/

	void QuadTree::checkCollisions()
	{ 

		if (m_level == m_maxLevel) {
			checkCollision();
			return;
		}
		else
		{
			m_NW->checkCollisions();
			m_NE->checkCollisions();
			m_SW->checkCollisions();
			m_SE->checkCollisions();
		}

		checkCollision();
			
	}


	void QuadTree::checkCollision()
	{

		if (m_objects.empty())
		{
			return;
		}

		for (artemis::Entity* e1 : m_objects)
		{
			for (artemis::Entity* e2 : m_objects)
			{
				if (e1->getId() != e2->getId())
				{
					cCollider* collider1 = (cCollider*)e1->getComponent<cCollider>();
					cCollider* collider2 = (cCollider*)e2->getComponent<cCollider>();

					if (collider1->getCollider().getBoxCollider().intersects(collider2->getCollider().getBoxCollider()))
					{
						collider1->setCollision(true);
						collider2->setCollision(true);
					}

				}
			}
		}

	}



	bool QuadTree::contains(QuadTree *child, artemis::Entity *object) {
		cCollider* collider = (cCollider*) object->getComponent<cCollider>();
		sf::FloatRect boxCollider = collider->getCollider().getBoxCollider();
		
		return		!(boxCollider.left < child->m_shape.left
					|| boxCollider.top < child->m_shape.top 
					|| boxCollider.left > child->m_shape.left + child->m_shape.width
					|| boxCollider.top > child->m_shape.top + child->m_shape.height
					|| boxCollider.left + boxCollider.width < child->m_shape.left
					|| boxCollider.top + boxCollider.height < child->m_shape.top
					|| boxCollider.left + boxCollider.width > child->m_shape.left + child->m_shape.width
					|| boxCollider.top + boxCollider.height > child->m_shape.top + child->m_shape.height);
	}
}




















//
//
//Quadtree::Quadtree() :
//left(0),
//right(0),
//top(0),
//down(0),
//numObjectsToGrow(4),
//nodes(0),
//isLeaf(true)
//{
//}
//
//Quadtree::Quadtree(double _left, double _right, double _top, double _down, unsigned int _numObjectsToGrow) :
//left(_left),
//right(_right),
//top(_top),
//down(_down),
//numObjectsToGrow(_numObjectsToGrow),
//nodes(0),
//isLeaf(true)
//{
//}
//
//Quadtree::~Quadtree()
//{
//	if (!isLeaf)
//		delete[] nodes;
//}
//
//void Quadtree::AddObject(Object *object)
//{
//	if (isLeaf) {
//		objects.push_back(object);
//		bool reachedMaxObjects = (objects.size() == numObjectsToGrow);
//		if (reachedMaxObjects) {
//			createLeaves();
//			moveObjectsToLeaves();
//			isLeaf = false;
//		}
//		return;
//	}
//
//	for (int n = 0; n < NodeCount; ++n) {
//		if (nodes[n].contains(object)) {
//			nodes[n].AddObject(object);
//			return;
//		}
//	}
//
//	objects.push_back(object);
//}
//
//void Quadtree::Clear()
//{
//	objects.clear();
//
//	if (!isLeaf) {
//		for (int n = 0; n < NodeCount; ++n) {
//			nodes[n].Clear();
//		}
//	}
//}
//
//vector<Object*> Quadtree::GetObjectsAt(double x, double y)
//{
//	if (isLeaf) {
//		return objects;
//	}
//
//	vector<Object*> returnedObjects;
//	vector<Object*> childObjects;
//
//	if (!objects.empty())
//		returnedObjects.insert(returnedObjects.end(), objects.begin(), objects.end());
//
//	for (int n = 0; n < NodeCount; ++n) {
//		if (nodes[n].contains(x, y)) {
//			childObjects = nodes[n].GetObjectsAt(x, y);
//			returnedObjects.insert(returnedObjects.end(), childObjects.begin(), childObjects.end());
//			break;
//		}
//	}
//
//	return returnedObjects;
//}
//
//void Quadtree::Display(SDL_Renderer *renderer)
//{
//	SDL_Rect rect;
//	rect.x = left;
//	rect.y = top;
//	rect.w = right - left;
//	rect.h = down - top;
//	SDL_RenderDrawRect(renderer, &rect);
//
//	if (!isLeaf) {
//		for (int n = 0; n < NodeCount; ++n) {
//			nodes[n].Display(renderer);
//		}
//	}
//}
//
//bool Quadtree::contains(Object *object)
//{
//	return 	object->left > left &&
//		object->right < right &&
//		object->top > top &&
//		object->down < down;
//}
//
//bool Quadtree::contains(double x, double y)
//{
//	return 	(x >= left && x <= right) &&
//		(y >= top && y <= down);
//}
//
//void Quadtree::createLeaves()
//{
//	nodes = new Quadtree[4];
//	nodes[NW] = Quadtree(left, (left + right) / 2, top, (top + down) / 2, numObjectsToGrow);
//	nodes[NE] = Quadtree((left + right) / 2, right, top, (top + down) / 2, numObjectsToGrow);
//	nodes[SW] = Quadtree(left, (left + right) / 2, (top + down) / 2, down, numObjectsToGrow);
//	nodes[SE] = Quadtree((left + right) / 2, right, (top + down) / 2, down, numObjectsToGrow);
//}
//
//void Quadtree::moveObjectsToLeaves()
//{
//	for (int n = 0; n < NodeCount; ++n) {
//		for (unsigned int m = 0; m < objects.size(); ++m) {
//			if (nodes[n].contains(objects[m])) {
//				nodes[n].AddObject(objects[m]);
//				objects.erase(objects.begin() + m);
//				--m;
//			}
//		}
//	}
//}