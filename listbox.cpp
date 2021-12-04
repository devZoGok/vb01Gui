#include <node.h>
#include <text.h>
#include <quad.h>
#include <root.h>
#include <glfw3.h>
#include <material.h>

#include "listbox.h"
#include "util.h"

using namespace vb01;
using namespace std;

namespace vb01Gui{
	Listbox::ListboxButton::ListboxButton(Listbox *l, Vector2 pos, Vector2 size, string name) : Button(pos, size, name, "", -1, false){listbox = l;}

	void Listbox::ListboxButton::onClick(){
		ListboxType type = listbox->getType();

		if(type != CONTROLS && !listbox->isOpen())
			listbox->openUp();
		else{
			double x = *listbox->getMousePosX(), y = *listbox->getMousePosY();
			Vector2 pos = listbox->getPos(), size = listbox->getSize();

			if(x > pos.x + size.x - 20 && x < pos.x + size.x){
				int scrollOffset = (listbox->getNumLines() - listbox->getMaxDisplay()) * (abs(y - pos.y) / (size.y * listbox->getMaxDisplay()));
				Vector2 scrollButtonPos = listbox->getScrollingButton()->getPos();

				for(int i = 0; i < scrollOffset; i++)
					if(y > scrollButtonPos.y)
						listbox->scrollDown();
					else
						listbox->scrollUp();

				listbox->getScrollingButton()->setPos(Vector2(pos.x + size.x - 20, y));
			}
			else if(type == STOCK&&listbox->isOpen())
				listbox->close();
		}
	}

	Listbox::ScrollingButton::ScrollingButton(Vector2 pos, Vector2 size, string name) : Button(pos, size, name, "", -1, false){}

	void Listbox::ScrollingButton::onClick(){}

	Listbox::Listbox(Vector2 pos, Vector2 size, std::vector<string> &lines, int maxDisplay, string fontPath, ListboxType type){
		this->pos = pos;
		this->size = size; 
		this->maxDisplay = maxDisplay;
		this->type = type;
		this->fontPath = fontPath;

		mousePosX = new double, mousePosY = new double;
		Root *root = Root::getSingleton();
		glfwGetCursorPos(root->getWindow(), mousePosX, mousePosY);
		guiNode = Root::getSingleton()->getGuiNode();
		string texUni = "texturingEnabled", diffColUni = "diffuseColor";

		for(int i = 0; i < lines.size(); i++){
			Text *text = new Text(fontPath, stringToWstring(lines[i]));
			text->setScale(.2);

			Material *textMat = new Material(root->getLibPath() + "text");
			textMat->addBoolUniform(texUni, false);
			textMat->addVec4Uniform(diffColUni, Vector4::VEC_IJKL);
			text->setMaterial(textMat);

			Node *node = new Node(Vector3(pos.x, pos.y + size.y * (i + 1), -.1));
			node->addText(text);
			guiNode->attachChild(node);
			node->setVisible(false);

			this->lines.push_back(text);
		}

		this->lines[0]->getNode()->setVisible(true);
		listboxButton = new ListboxButton(this, pos, size, "ListboxButton");
		scrollingButton = new ScrollingButton(Vector2(pos.x + size.x - 20, pos.y + 20), Vector2(20, 20.0 * (maxDisplay - 2) / (lines.size() - maxDisplay)), "scrollingButton");
		scrollingButton->setColor(Vector4(.2, .2, .2, 1));
		scrollingButton->setZOrder(-.05);

		Quad *selRect = new Quad(Vector3(size.x, size.y, 0), false);
		selRectNode = new Node(Vector3(size.x, size.y, -.05));
		Material *mat = new Material(root->getLibPath() + "gui");
		mat->addBoolUniform(texUni, false);
		mat->addVec4Uniform(diffColUni, Vector4(.6, .35, .05, 1));
		selRect->setMaterial(mat);
		selRectNode->attachMesh(selRect);
		selRectNode->setVisible(false);
		guiNode->attachChild(selRectNode);

		if(type == CONTROLS)
			openUp();
	}

	Listbox::~Listbox(){
		while(!lines.empty()){
			int id = lines.size() - 1;
			Node *textNode = lines[id]->getNode();
			guiNode->dettachChild(textNode);
			delete textNode;
			lines.pop_back();
		}

		guiNode->dettachChild(selRectNode);
		delete selRectNode;
		delete mousePosX, mousePosY;
	}

	void Listbox::update(){
		if(open){
			glfwGetCursorPos(Root::getSingleton()->getWindow(), mousePosX, mousePosY);
			Vector2 p = pos;

			if(*mousePosY > pos.y && *mousePosY < pos.y + size.y * maxDisplay){
				selectedOption = scrollOffset + ((int)(*mousePosY - pos.y) / ((int)size.y));
				p.y = pos.y + size.y * ((int)(*mousePosY - pos.y) / ((int)size.y));
			}
			else if(*mousePosY < pos.y){
				selectedOption = 0;
				p.y = pos.y;
			}
			else{
				selectedOption = lines.size() - 1;
				p.y = pos.y + size.y * (maxDisplay - 1);
			}

			selRectNode->setPosition(Vector3(p.x, p.y, -.05));

			for(int i = 0; i < maxDisplay; i++) {
			}
			/*
			if(scrollOffset>0){
				Vector2 scrollingButtonPos = scrollingButton->getPos();
				scrollingButtonPos.y = pos.y + 20 + scrollingButton->getSize().y * (scrollOffset - 1);
				scrollingButton->setPos(scrollingButtonPos);
				Vector2 p = scrollingButtonPos-scrollingButton->getPos();
				scrollingButton->setPos(Vector2(p.x, p.y));
			}
			*/
		} 
	}

	void Listbox::openUp(){
		open = true;
		lines[selectedOption]->getNode()->setPosition(Vector3(pos.x, pos.y + size.y * (selectedOption-scrollOffset + 1), -.1));
		lines[selectedOption]->getNode()->setVisible(false);
		Vector2 size = listboxButton->getSize();
		size.y *= maxDisplay;
		listboxButton->setSize(size);
		selRectNode->setVisible(true);

		for(int i = scrollOffset; i < scrollOffset + maxDisplay; i++)
			lines[i]->getNode()->setVisible(true);
	}

	void Listbox::close(){
		open = false;
		Vector2 size = listboxButton->getSize();
		size.y /= maxDisplay;
		listboxButton->setSize(size);
		selRectNode->setVisible(false);

		for(int i = scrollOffset; i < scrollOffset + maxDisplay; i++)
			lines[i]->getNode()->setVisible(false);

		lines[selectedOption]->getNode()->setPosition(Vector3(pos.x, pos.y + size.y, -.1));
		lines[selectedOption]->getNode()->setVisible(true);
	}

	void Listbox::scrollUp(){
		if(scrollOffset > 0){
			scrollOffset--;

			for(Text *l : lines){
				Node *node = l->getNode();
				Vector3 p = node->getPosition();
				node->setPosition(Vector3(p.x, p.y + size.y, p.z));

				if(node->getPosition().y > pos.y + size.y * maxDisplay)
					node->setVisible(false);
				else if(node->getPosition().y > pos.y)
					node->setVisible(true);
			}
		}
	}

	void Listbox::scrollDown(){
		if (scrollOffset < lines.size() - maxDisplay){
			scrollOffset++;

			for(Text *l : lines){
				Node *node = l->getNode();
				Vector3 p = node->getPosition();
				node->setPosition(Vector3(p.x, p.y - size.y, p.z));

				if(node->getPosition().y - size.y < pos.y)
					node->setVisible(false);
				else if(node->getPosition().y < pos.y + size.y * (maxDisplay + 1))
					node->setVisible(true);
			}
		}
	}

	void Listbox::changeLine(int id, wstring change){
		lines[id]->setText(change);	
	}

	std::vector<wstring> Listbox::getContents(){
		std::vector<wstring> lines;

		for(Text *t : this->lines)
			lines.push_back(t->getText());

		return lines;
	}

	void Listbox::addLine(wstring line){
		Text *t = new Text(fontPath, line);
		Node *node = new Node(Vector3(pos.x, pos.y - size.y * lines.size(), 1));
		node->addText(t);
		guiNode->attachChild(node);
		lines.push_back(t);
	}

	string Listbox::convert(string str){
		return str;
	}
}
