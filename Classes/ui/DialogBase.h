#pragma once 

#include "cocos2d.h"
USING_NS_CC;

class ReliefButton;

class DialogBase:public Node
{
public:
	static DialogBase* create(std::string csbFile);
	bool init(std::string csbNode);

	void showDialog();
	void onShowDialogBeganCallback();
	void onShowDialogEndedCallback();


	void dismiss();
	void onDismissDialogBeganCallback();
	void onDismissDialogEndedCallback();

	void initCommonButtonCallback();

private:
	Node* m_csbNode;
	Node* m_background;
	Node* m_dialog;
	Node* m_buttonPanel;
	Vector<ReliefButton*> m_buttonVector;
};