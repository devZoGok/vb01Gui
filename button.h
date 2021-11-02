#ifndef BUTTON_H
#define BUTTON_H

#include <vector.h>
#include <vector>
#include <string>

class GLFWwindow;

namespace vb01{
	class Quad;
	class Node;
	class Text;
	class Texture;
}

namespace vb01Gui{
	class Button{
		public:
			Button(vb01::Vector2, vb01::Vector2, std::string, std::string = "", int = -1, bool = true, std::string = "");
			virtual ~Button();
			void update();
			virtual void onMouseOver();
			virtual void onMouseOff();
			virtual void onClick(){}
			inline vb01::Vector2 getPos(){return pos;}
			void setPos(vb01::Vector2);
			inline vb01::Vector2 getSize(){return size;}
			void setSize(vb01::Vector2);
			inline std::string getName(){return name;}
			inline void setActive(bool active){this->active = active;}
			inline bool isSeparate(){return separate;}
			inline bool isActive(){return active;}
			inline vb01::Vector4 getColor(){return color;}
			inline int getTrigger(){return trigger;}
			void setColor(vb01::Vector4);
			void setZOrder(float);
			void setImage(std::string);
		protected:
			int trigger, initWindowSize[2];
			bool separate, active = true, mouseOver = false;
			vb01::Quad *rect;
			vb01::Node *rectNode, *textNode = nullptr, *guiNode;
			vb01::Vector2 pos, size;
			vb01::Text *text = nullptr;
			std::string name, imagePath;
			std::vector<vb01::Texture*> textures;
			vb01::Vector4 color = vb01::Vector4(.6, .6, .6, 1);
	};
}

#endif
