#include "Node.h"
#include <cstring>


Node::Node(void)
{
}


Node::~Node(void)
{
}

void Node::draw(void)
{
	
}

void Node::update()
{

}

bool Node::addChild(Node* node)
{
	m_children.push_back(node);
	return true;
}

bool Node::removeChild(Node* node)
{
	for (auto itor = m_children.begin();itor != m_children.end(); ++itor) {
		if(*itor == node) {
			*itor = *(--m_children.end());
			m_children.pop_back();
			return true;
		}
	}

	return false;

}

bool Node::removeChildByName(const std::string& name)
{
	Node* child = getChildByName(name);
	if(!child) {
		return false;
	}

	*(--m_children.end()) = child;
	m_children.pop_back();
	return true;
}

bool Node::removeChildByIndex(int index)
{
	int size = m_children.size();
	if(size <= index){
		return false;
	}

	m_children[index] = m_children[size-1];
	m_children.pop_back();
	return true;
}

std::vector<Node*>&& Node::removeAllChildren(bool doCleanup)
{
	if(!doCleanup) {
		std::vector<Node*> children(m_children);
		m_children.clear();
		m_children.shrink_to_fit();
		return std::move(children);
	}

	for(auto child:m_children) {
		delete(child);
	}
	m_children.clear();
	return std::vector<Node*>();
}

Node* Node::getChildByName(std::string name)
{
	for (auto itor = m_children.begin();itor != m_children.end(); ++itor) {
		if(!std::strcmp( (*itor)->getName().c_str(),name.c_str())) {
			return *itor;
		}
	}

	return nullptr;
}

Node* Node::getChildByIndex(int index)
{
	int size = m_children.size();
	if(size <= index){
		return nullptr;
	}

	return m_children[index];
}

void  Node::setName(const std::string& name)
{
	m_name = name;
}

const std::string&  Node::getName()
{
	return m_name;
}

void Node::setPos(int x,int y)
{
	m_pos.x = x;
	m_pos.y = y;
}

void Node::setPos(const Point2d& point)
{
	m_pos = point;
}

const Point2d& Node::getPos()
{
	return m_pos;
}

void Node::setX(int x)
{
	m_pos.x = x;
}

void Node::setY(int y)
{
	m_pos.y = y;
}

int Node::getX()
{
	return m_pos.x;
}

int Node::getY()
{
	return m_pos.y;
}

void Node::setSize(int w,int h)
{
	m_size.x = w;
	m_size.y = h;
}

void Node::setSize(const Point2d& point)
{
	m_size = point;
}

const Point2d& Node::getSize()
{
	return m_size;
}

void Node::setWidth(int width)
{
	m_size.x = width;
}

void Node::setHeight(int height)
{
	m_size.y = height;
}

int Node::getWidth()
{
	return m_size.x;
}

int Node::getHeight()
{
	return m_size.y;
}
