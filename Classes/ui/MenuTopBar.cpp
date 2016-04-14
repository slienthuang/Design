#include "MenuTopBar.h"
#include "ReliefButton.h"
#include "EnemyManager.h"
#include "DialogBase.h"

MenuTopBar* MenuTopBar::create()
{
	auto menuTopBar = new MenuTopBar();
	menuTopBar->init();
	menuTopBar->autorelease();
	return menuTopBar;
}

bool MenuTopBar::init()
{
	if (!Node::init())  return false;
	m_rootNode = CSLoader::createNode("MenuTopBar.csb");
	this->addChild(m_rootNode);

	m_groupRecordText = static_cast<ui::Text*>(m_rootNode->getChildByName("menuTopBar")->getChildByName("text_groupCount"));
	//text->setColor(Color3B::RED);
	//text->setTextColor(Color4B::RED);
	///text->setText("1/20");
	m_pauseSprite = static_cast<Sprite*>(m_rootNode->getChildByName("menuTopBar")->getChildByName("pause"));

	m_pauseButton = ReliefButton::create(m_pauseSprite);
	
	auto menuNode = m_rootNode->getChildByName("menuTopBar")->getChildByName("setting");
	m_menuButton = ReliefButton::create(menuNode);
	m_menuButton->setClickCallback([this](){
		auto dialog = DialogBase::create("SettingDialog.csb");
		this->getParent()->addChild(dialog);
		
	});


	return true;
}

void MenuTopBar::updateBarData(int x,int y)
{
	auto str = __String::createWithFormat("%d/%d",x,y);

	m_groupRecordText->setString(str->getCString());

}
void MenuTopBar::setPauseCallback(std::function<void()> callback)
{
	m_pauseButton->setClickCallback(callback);
}


void MenuTopBar::updatePauseButton()
{
	if (UserDefault::getInstance()->getBoolForKey("game_run"))
	{
		m_pauseSprite->initWithFile("start.png");
	}
	else
	{
		m_pauseSprite->initWithFile("pause.png");
	}
}