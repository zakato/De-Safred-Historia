#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <Collision\cCollider.hpp>

#include <SFML\Graphics\Rect.hpp>

#include <vector>

namespace zkt {

	class QuadTree {
	public:
		QuadTree(float x, float y, float width, float height, int level, int maxLevel);

		~QuadTree();

		void					AddObject(cCollider *object);
		std::vector<cCollider*>			GetObjectsAt(float x, float y);
		void					Clear();

		

	private:
		std::vector<cCollider*>		m_objects;
		sf::FloatRect				m_shape;
		float						m_x;
		float						m_y;
		float						m_width;
		float						m_height;
		int							m_level;
		int							m_maxLevel;

		QuadTree *					m_parent;
		QuadTree *					m_NW;
		QuadTree *					m_NE;
		QuadTree *					m_SW;
		QuadTree *					m_SE;

		

		bool					contains(QuadTree *child, cCollider *object);



	};
}


#endif
//
//
//
//class Quadtree {
//
//	enum Node {
//		NW = 0,
//		NE,
//		SW,
//		SE,
//		NodeCount
//	};
//
//public:
//	Quadtree();
//
//	Quadtree(double left, double right, double top, double down, unsigned int numObjectsToGrow = 3);
//
//	~Quadtree();
//
//	void				AddObject(Object *object);
//
//	void				Clear();
//
//	vector<Object*>			GetObjectsAt(double x, double y);
//
//	void				Display(SDL_Renderer *renderer);
//
//private:
//	double				left;
//
//	double				right;
//
//	double				top;
//
//	double				down;
//
//	unsigned int			numObjectsToGrow;
//
//	vector<Object*>			objects;
//
//	Quadtree * 			nodes;
//
//	bool				isLeaf;
//
//	bool				contains(Object *object);
//
//	bool				contains(double x, double y);
//
//	void				createLeaves();
//
//	void				moveObjectsToLeaves();
//
//};