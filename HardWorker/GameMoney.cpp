#include"GameMoney.h"

#include<math.h>

int money = 10000;
int amount = 0;
bool changed = false;

extern bool win;
extern int chuk;

extern int m_count1;
extern int m_count2;
extern int m_count3;

bool first = false;
int fcnt = 0;
extern int day;

int clear_score = 0;
int hire_score = 0;
int ret_score = 0;
int earn_score = 0;

extern int amount;

void GameMoney::Initialize()
{
	numbers = ResourceManager::GetTexture("numbers");
	symbol = ResourceManager::GetTexture("$");
	clear_score = 0;
	if (win) {
		clear_score = 1000 * pow(10, (chuk / 10));
		money += clear_score;
		win = false;
		cleared = true;
		day += 1;
	}
	tDia = ResourceManager::GetTexture("dialog");
	fcnt++;
	//ret_score = m_count1 * 50 + m_count2 * 250;
	
	if (fcnt % 2 == 1){
		show_on = true;	
		ret_score = m_count1 * 50 + m_count2 * 250 + m_count3 * 1000;
		money += m_count1 * 50 + m_count2 * 250 + m_count3 * 1000;
	}
	if (first == false){
		show_on = false;
		first = true;
	}
	
	//show_on = true;
	_x = _sceneWIDTH / 2;
	_y = _sceneHEIGHT / 2;

	clear = ResourceManager::GetTexture("clear");
	hire = ResourceManager::GetTexture("hire");
	ret = ResourceManager::GetTexture("return");
	earn = ResourceManager::GetTexture("earn");
	total = ResourceManager::GetTexture("total");

	rect = ResourceManager::GetTexture("rect");
}

void GameMoney::Step()
{
	if (show_on) {
		if (show_dialog <= 1.0f) show_dialog += 0.02f;
		if (show_dialog >= 1.0f){
			if (Input::MouseDown(MOUSE_LEFT)){
				show_off = true;
			}
		}
		if (show_off){
			if (show_dialog >= 0.0f) show_dialog -= 0.04f;
			if (show_dialog <= 0.0f) {
				show_off = false;
				show_on = false;
				show_dialog = 0.0f;
				hire_score = 0;
				clear_score = 0;
				ret_score = 0;
				earn_score = 0;
			}
		}
	}
}

void GameMoney::Draw()
{
	DrawTexture(symbol, 12,  20, 0.4, 2,2,0, 1);
	DrawNumber(numbers, money, 8, 30, 20 , 0.4, 2, 2,1,0);
	DrawTexture(tDia, _sceneWIDTH / 2, _sceneHEIGHT / 2 , 0.5, 2, 2, 0, show_dialog);

	DrawTexture(clear, _sceneWIDTH / 2, _sceneHEIGHT / 2- 70-20 , 0.5, 2, 2, 0, show_dialog);
	DrawNumber(numbers, clear_score, 8, _sceneWIDTH / 2, _sceneHEIGHT / 2 - 45 - 20, 0.5,2,2, show_dialog, 1);
	DrawTexture(rect, _sceneWIDTH / 2 - DrawNumber(numbers, hire_score, 0, -10, -10, 0, 0, 0, 0, 0) * 13 / 2 - 10, _sceneHEIGHT / 2 + 5 - 20, 0.9, 10, 3, 0, show_dialog);
	DrawTexture(hire, _sceneWIDTH /2, _sceneHEIGHT / 2 - 20 - 20, 0.5, 2, 2, 0, show_dialog);
	DrawNumber(numbers, hire_score, 8, _sceneWIDTH / 2, _sceneHEIGHT / 2 + 5 - 20, 0.5, 2, 2, show_dialog, 1);
	DrawTexture(ret, _sceneWIDTH / 2, _sceneHEIGHT / 2 + 30 - 20, 0.5, 2, 2, 0, show_dialog);
	DrawNumber(numbers, ret_score, 8, _sceneWIDTH / 2, _sceneHEIGHT / 2 + 55 - 20, 0.5, 2, 2, show_dialog, 1);
	DrawTexture(earn, _sceneWIDTH / 2, _sceneHEIGHT / 2 + 80 - 20, 0.5, 2, 2, 0, show_dialog);
	DrawNumber(numbers, amount, 8, _sceneWIDTH / 2, _sceneHEIGHT / 2 + 105 - 20, 0.5, 2, 2, show_dialog, 1);
	DrawTexture(total, _sceneWIDTH / 2, _sceneHEIGHT / 2 + 130 - 20, 0.5, 2, 2, 0, show_dialog);
	int tot = clear_score - hire_score + ret_score + amount;
	if (tot < 0) 
		DrawTexture(rect, _sceneWIDTH / 2 - DrawNumber(numbers, abs(tot), 2, -10, -10, 0, 0, 0, 0, 0)*13/2 - 10, _sceneHEIGHT / 2 + 155 - 20, 0.9,10, 3, 0, show_dialog);
	DrawNumber(numbers, abs(tot), 8, _sceneWIDTH / 2, _sceneHEIGHT / 2 + 155 - 20, 0.5, 2, 2, show_dialog, 1);
	//DrawNumber(numbers, -(m_count1 * 100 + m_count2 * 500), 8, _x, _y+50, 0.6, 2, 2, show_dialog, 0);
	SetSamplerStateNone();
}

void GameMoney::Destroy()
{

}