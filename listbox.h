#ifndef LISTBOX_H
#define LISTBOX_H

#include <vector.h>
#include <vector>

#include "button.h"

namespace vb01{
	class Node;
	class Text;
}

namespace vb01Gui{
	class Listbox{
		public: 
			enum ListboxType{STOCK, CONTROLS};

			class ListboxButton : public Button{
				public:
					ListboxButton(Listbox*, vb01::Vector2, vb01::Vector2, std::string);
					void onClick();
				private:
					Listbox *listbox = nullptr;
			};

			Listbox(vb01::Vector2, vb01::Vector2, std::vector<std::string>&, int, std::string, ListboxType = STOCK);
			~Listbox();
			void update();
			void openUp();
			void close();
			void scrollUp();
			void scrollDown();
			void addLine(std::wstring);
			void changeLine(int, std::wstring);
			inline ListboxType getType(){return type;}
			inline bool isOpen(){return open;}
			void appendLines(std::vector<std::wstring>&);
			inline int getSelectedOption(){return selectedOption;}
			inline int getMaxDisplay(){return maxDisplay;}
			inline int getNumLines(){return lines.size();}
			std::vector<std::wstring> getContents();
			inline vb01::Vector2 getPos(){return pos;} 
			inline vb01::Vector2 getSize(){return size;} 
			inline double* getMousePosX(){return mousePosX;}
			inline double* getMousePosY(){return mousePosY;}
		private: 
			class ScrollingButton : public Button{
				public:
					ScrollingButton(vb01::Vector2, vb01::Vector2, std::string);
					void onClick();
				private:
			};

			std::string convert(std::string);

			double *mousePosX, *mousePosY;
			int maxDisplay, scrollOffset = 0, selectedOption = 0;
			bool open = false;
			std::vector<vb01::Text*> lines;
			std::string fontPath;
			vb01::Vector2 pos, size;
			ListboxButton *listboxButton;
			ScrollingButton *scrollingButton;
			vb01::Node *selRectNode, *guiNode;
			ListboxType type;
		public: 
			inline ListboxButton* getListboxButton(){return listboxButton;}
			inline ScrollingButton* getScrollingButton(){return scrollingButton;}
	};
}

#endif
