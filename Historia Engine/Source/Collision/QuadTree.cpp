#include <Collision\QuadTree.hpp>


namespace zkt {

	QuadTree::QuadTree(float _x, float _y, float _width, float _height, int _level, int _maxLevel) :
		m_x(_x),
		m_y(_y),
		m_width(_width),
		m_height(_height),
		m_level(_level),
		m_maxLevel(_maxLevel)
	{
		

		if (m_level == m_maxLevel) {
			return;
		}

		m_NW = new QuadTree(m_x, m_y, m_width / 2.0f, m_height / 2.0f, m_level + 1, m_maxLevel);
		m_NE = new QuadTree(m_x + m_width / 2.0f, m_y, m_width / 2.0f, m_height / 2.0f, m_level + 1, m_maxLevel);
		m_SW = new QuadTree(m_x, m_y + m_height / 2.0f, m_width / 2.0f, m_height / 2.0f, m_level + 1, m_maxLevel);
		m_SE = new QuadTree(m_x + m_width / 2.0f, m_y + m_height / 2.0f, m_width / 2.0f, m_height / 2.0f, m_level + 1, m_maxLevel);
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

	void QuadTree::AddObject(Object *object) {
		if (level == maxLevel) {
			objects.push_back(object);
			return;
		}
		if (contains(NW, object)) {
			NW->AddObject(object); return;
		}
		else if (contains(NE, object)) {
			NE->AddObject(object); return;
		}
		else if (contains(SW, object)) {
			SW->AddObject(object); return;
		}
		else if (contains(m_SE, object)) {
			SE->AddObject(object); return;
		}
		if (contains(this, object)) {
			objects.push_back(object);
		}
	}

	std::vector<Object*> QuadTree::GetObjectsAt(float _x, float _y) {
		if (m_level == m_maxLevel) {
			return m_objects;
		}

		std::vector<Object*> returnObjects, childReturnObjects;
		if (!objects.empty()) {
			returnObjects = objects;
		}
		if (_x > m_x + m_width / 2.0f && _x < m_x + m_width) {
			if (_y > m_y + m_height / 2.0f && _y < m_y + m_height) {
				childReturnObjects = m_SE->GetObjectsAt(_x, _y);
				returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
				return returnObjects;
			}
			else if (_y > y && _y <= y + height / 2.0f) {
				childReturnObjects = NE->GetObjectsAt(_x, _y);
				returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
				return returnObjects;
			}
		}
		else if (_x > m_x && _x <= m_x + m_width / 2.0f) {
			if (_y > m_y + m_height / 2.0f && _y < m_y + m_height) {
				childReturnObjects = m_SW->GetObjectsAt(_x, _y);
				returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
				return returnObjects;
			}
			else if (_y > y && _y <= y + m_height / 2.0f) {
				childReturnObjects = m_NW->GetObjectsAt(_x, _y);
				returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
				return returnObjects;
			}
		}
		return returnObjects;
	}

	void QuadTree::Clear() {
		if (m_level == m_maxLevel) {
			objects.clear();
			return;
		}
		else {
			m_NW->Clear();
			m_NE->Clear();
			m_SW->Clear();
			m_SE->Clear();
		}
		if (!objects.empty()) {
			objects.clear();
		}
	}

	


	bool QuadTree::contains(QuadTree *child, Object *object) {
		return	 !(object->x < child->m_x ||
			object->y < child->m_y ||
			object->x > child->m_x + child->m_width ||
			object->y > child->m_y + child->m_height ||
			object->x + object->m_width < child->m_x ||
			object->y + object->height < child->m_y ||
			object->x + object->width > child->m_x + child->m_width ||
			object->y + object->height > child->m_y + child->m_height);
	}


}























Quadtree::Quadtree() :
left(0),
right(0),
top(0),
down(0),
numObjectsToGrow(4),
nodes(0),
isLeaf(true)
{
}

Quadtree::Quadtree(double _left, double _right, double _top, double _down, unsigned int _numObjectsToGrow) :
left(_left),
right(_right),
top(_top),
down(_down),
numObjectsToGrow(_numObjectsToGrow),
nodes(0),
isLeaf(true)
{
}

Quadtree::~Quadtree()
{
	if (!isLeaf)
		delete[] nodes;
}

void Quadtree::AddObject(Object *object)
{
	if (isLeaf) {
		objects.push_back(object);
		bool reachedMaxObjects = (objects.size() == numObjectsToGrow);
		if (reachedMaxObjects) {
			createLeaves();
			moveObjectsToLeaves();
			isLeaf = false;
		}
		return;
	}

	for (int n = 0; n < NodeCount; ++n) {
		if (nodes[n].contains(object)) {
			nodes[n].AddObject(object);
			return;
		}
	}

	objects.push_back(object);
}

void Quadtree::Clear()
{
	objects.clear();

	if (!isLeaf) {
		for (int n = 0; n < NodeCount; ++n) {
			nodes[n].Clear();
		}
	}
}

vector<Object*> Quadtree::GetObjectsAt(double x, double y)
{
	if (isLeaf) {
		return objects;
	}

	vector<Object*> returnedObjects;
	vector<Object*> childObjects;

	if (!objects.empty())
		returnedObjects.insert(returnedObjects.end(), objects.begin(), objects.end());

	for (int n = 0; n < NodeCount; ++n) {
		if (nodes[n].contains(x, y)) {
			childObjects = nodes[n].GetObjectsAt(x, y);
			returnedObjects.insert(returnedObjects.end(), childObjects.begin(), childObjects.end());
			break;
		}
	}

	return returnedObjects;
}

void Quadtree::Display(SDL_Renderer *renderer)
{
	SDL_Rect rect;
	rect.x = left;
	rect.y = top;
	rect.w = right - left;
	rect.h = down - top;
	SDL_RenderDrawRect(renderer, &rect);

	if (!isLeaf) {
		for (int n = 0; n < NodeCount; ++n) {
			nodes[n].Display(renderer);
		}
	}
}

bool Quadtree::contains(Object *object)
{
	return 	object->left > left &&
		object->right < right &&
		object->top > top &&
		object->down < down;
}

bool Quadtree::contains(double x, double y)
{
	return 	(x >= left && x <= right) &&
		(y >= top && y <= down);
}

void Quadtree::createLeaves()
{
	nodes = new Quadtree[4];
	nodes[NW] = Quadtree(left, (left + right) / 2, top, (top + down) / 2, numObjectsToGrow);
	nodes[NE] = Quadtree((left + right) / 2, right, top, (top + down) / 2, numObjectsToGrow);
	nodes[SW] = Quadtree(left, (left + right) / 2, (top + down) / 2, down, numObjectsToGrow);
	nodes[SE] = Quadtree((left + right) / 2, right, (top + down) / 2, down, numObjectsToGrow);
}

void Quadtree::moveObjectsToLeaves()
{
	for (int n = 0; n < NodeCount; ++n) {
		for (unsigned int m = 0; m < objects.size(); ++m) {
			if (nodes[n].contains(objects[m])) {
				nodes[n].AddObject(objects[m]);
				objects.erase(objects.begin() + m);
				--m;
			}
		}
	}
}