#include "SettingDialog.h"
#include "my_cocostudio.h"

SettingDialog* SettingDialog::create()
{
	auto settingDialog = new SettingDialog();
	settingDialog->init();
	settingDialog->autorelease();
	return settingDialog;

}

bool SettingDialog::init()
{
	if (!Node::init()) return true;

	auto dialog = CSLoader::createNode("SettingDialog.csb");
	addChild(dialog);


	return true;
}