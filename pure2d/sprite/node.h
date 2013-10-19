#pragma once

#include <vector>
#include "../math/point2d.h"

class Node
{
public:
	Node(void);
	virtual ~Node(void);

	virtual void draw();
	virtual void update();

	bool addChild(Node* node);
	bool removeChild(Node* node);
	bool removeChildByName(const std::string& name);
	bool removeChildByIndex(int index);
	//need to review,how to be more effecive
	std::vector<Node*>&& removeAllChildren(bool doCleanup);

	Node* getChildByName(std::string name);
	Node* getChildByIndex(int index);

	inline void setName(const std::string& name);
	inline const std::string& getName();

	inline void setPos(int x,int y);
	inline void setPos(const Point2d& point);
	inline const Point2d& getPos();
	inline void setX(int x);
	inline void setY(int y);
	inline int getX();
	inline int getY();

	inline void setSize(int w,int h);
	inline void setSize(const Point2d&);
	inline const Point2d& getSize();
	inline void setWidth(int width);
	inline void setHeight(int height);
	inline int getWidth();
	inline int getHeight();

private:
	Point2d m_size;
	Point2d m_pos;

	std::vector<Node*> m_children;

	std::string m_name;
};

