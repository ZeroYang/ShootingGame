/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __UIRICHTEXT_H__
#define __UIRICHTEXT_H__

#include "ui/UIWidget.h"

NS_CC_BEGIN

namespace ui {
    
typedef enum {
    RICH_TEXT,
    RICH_IMAGE,
    RICH_CUSTOM
}RichElementType;
    
class RichElement : public Ref
{
public:
    RichElement(){};
    virtual ~RichElement(){};
    bool init(int tag, const Color3B& color, GLubyte opacity);
protected:
    RichElementType _type;
    int _tag;
    Color3B _color;
    GLubyte _opacity;
    friend class RichText;
};
    
class RichElementText : public RichElement
{
public:
    RichElementText(){_type = RICH_TEXT;};
    virtual ~RichElementText(){};
    bool init(int tag, const Color3B& color, GLubyte opacity, const char* text, const char* fontName, float fontSize);
    static RichElementText* create(int tag, const Color3B& color, GLubyte opacity, const char* text, const char* fontName, float fontSize);
protected:
    std::string _text;
    std::string _fontName;
    float _fontSize;
    friend class RichText;
    
};
    
class RichElementImage : public RichElement
{
public:
    RichElementImage(){_type = RICH_IMAGE;};
    virtual ~RichElementImage(){};
    bool init(int tag, const Color3B& color, GLubyte opacity, const char* filePath);
    static RichElementImage* create(int tag, const Color3B& color, GLubyte opacity, const char* filePath);
protected:
    std::string _filePath;
    Rect _textureRect;
    int _textureType;
    friend class RichText;
};
    
class RichElementCustomNode : public RichElement
{
public:
    RichElementCustomNode(){_type = RICH_CUSTOM;};
    virtual ~RichElementCustomNode(){CC_SAFE_RELEASE(_customNode);};
    bool init(int tag, const Color3B& color, GLubyte opacity, Node* customNode);
    static RichElementCustomNode* create(int tag, const Color3B& color, GLubyte opacity, Node* customNode);
protected:
    Node* _customNode;
    friend class RichText;
};
    
class RichText : public Widget
{
public:
    RichText();
    virtual ~RichText();
    static RichText* create();
    void insertElement(RichElement* element, int index);
    void pushBackElement(RichElement* element);
    void removeElement(int index);
    void removeElement(RichElement* element);
    virtual void visit(cocos2d::Renderer *renderer, const kmMat4 &parentTransform, bool parentTransformUpdated) override;
    void setVerticalSpace(float space);
    virtual void setAnchorPoint(const Point &pt);
    virtual const Size& getVirtualRendererSize() const override;
    void formatText();
    virtual void ignoreContentAdaptWithSize(bool ignore);
    virtual std::string getDescription() const override;
	
CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;
    
protected:
    virtual void initRenderer();
    void pushToContainer(Node* renderer);
    void handleTextRenderer(const char* text, const char* fontName, float fontSize, const Color3B& color, GLubyte opacity);
    void handleImageRenderer(const char* fileParh, const Color3B& color, GLubyte opacity);
    void handleCustomRenderer(Node* renderer);
    void formarRenderers();
    void addNewLine();
protected:
    bool _formatTextDirty;
    Vector<RichElement*> _richElements;
    std::vector<Vector<Node*>*> _elementRenders;
    float _leftSpaceWidth;
    float _verticalSpace;
    Node* _elementRenderersContainer;
};
    
}

NS_CC_END

#endif /* defined(__UIRichText__) */
