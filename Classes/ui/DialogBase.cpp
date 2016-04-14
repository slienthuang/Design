#include "DialogBase.h"
#include "ReliefButton.h"
#include "my_cocostudio.h"

DialogBase* DialogBase::create(std::string csbFile)
{
	auto dialog = new DialogBase();
	dialog->init(csbFile);
	dialog->autorelease();
	return dialog;
}

bool DialogBase::init(std::string csbFile)
{
	if (!Node::init()) return false;
	m_csbNode = CSLoader::createNode(csbFile);
	this->addChild(m_csbNode);

	m_background = m_csbNode->getChildByName("background");
	m_dialog = m_csbNode->getChildByName("dialog");
	m_buttonPanel = m_dialog->getChildByName("button_panel");

	for (auto button : m_buttonPanel->getChildren())
	{
		auto reliefButton = ReliefButton::create(button);
		m_buttonVector.pushBack(reliefButton);
	}
	showDialog();
	initCommonButtonCallback();
	return true;
}


void DialogBase::showDialog()
{
	onShowDialogBeganCallback();

	float duration = 0.3f;
	m_background->setOpacity(0);
	m_background->runAction(FadeTo::create(duration, 100));

	m_dialog->setScale(0.01f);
	m_dialog->runAction(ScaleTo::create(duration, 1.0f));

	this->runAction(Sequence::create(DelayTime::create(duration), CallFunc::create([this](){
		onShowDialogEndedCallback();
	}), NULL));
}


void DialogBase::onShowDialogBeganCallback()
{
}

void DialogBase::onShowDialogEndedCallback()
{

}


void DialogBase::dismiss()
{
	onDismissDialogBeganCallback();
	float duration = 0.3f;
	//m_background->setOpacity(100);
	m_background->runAction(FadeTo::create(duration, 0));

	//m_csbNode->setScale(0.01f);
	m_dialog->runAction(ScaleTo::create(duration, 0.01f));

	this->runAction(Sequence::create(DelayTime::create(duration), CallFunc::create([this](){
		onDismissDialogEndedCallback();
	}), NULL));
}

void DialogBase::onDismissDialogBeganCallback()
{

}

void DialogBase::onDismissDialogEndedCallback()
{
	this->removeFromParent();
}


void DialogBase::initCommonButtonCallback()
{
	for (auto button : m_buttonVector)
	{
		if (button->getName() == "button_close")
		{
			button->setClickCallback([this](){
				this->dismiss();
			});
		}
	}
}