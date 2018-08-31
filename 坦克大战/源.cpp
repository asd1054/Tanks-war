#include <graphics.h>
#include<time.h>
#include<conio.h>

class Bullet;//玩家子弹类
class Tank;//玩家类
class Ebullet;//敌人子弹类
class Boss;//敌人类

bool dead = false;//玩家挂了
bool wined = false; //玩家胜利

#define MAX 8//子弹最大数

struct pos//坐标
{
	int x, y;

};

class Ebullet {
public:
	clock_t d;//敌人子弹的时间
	int x, y;
	bool on = false;//是否放置子弹

	pos show()
	{
		setfillcolor(RGB(255, 180, 20));
		fillrectangle(x - 5, y - 5, x + 5, y + 5);
		return pos{ x,y };
	}
	pos del()
	{
		setfillcolor(0);//跟背景一样的颜色	填充色
		setlinecolor(0);//x
		fillrectangle(x - 5, y - 5, x + 5, y + 5);
		return pos{ x,y };
	}

	pos move()//向左移动
	{
		x -= 3;
		return pos{ x,y };
	}
};
class Bullet {
public:
	clock_t d;//子弹的时间
	int x, y;
	bool on = false;//是否放置子弹

	pos show()
	{
		setfillcolor(RGB(255, 180, 20));//或者用YELLOW
		fillrectangle(x - 5, y - 5, x + 5, y + 5);
		return pos{ x,y };
	}
	pos del()
	{
		setfillcolor(0);//跟背景一样的颜色	填充色
		setlinecolor(0);//x
		fillrectangle(x - 5, y - 5, x + 5, y + 5);
		return pos{ x,y };
	}

	pos move()//向👉移动
	{
		x += 3;
		return pos{ x,y };
	}
};
class Boss {
public:
	bool hurting = false;//是否受伤
	bool angle = false;//方向 false 表示向下移动
	clock_t ftime;//开火时间
	clock_t mtime;//移动时间
	clock_t htime;//受伤时间

	COLORREF clr = RGB(150, 180, 210);

	int x, y;
	int hp = 100;//生命值

	COLORREF c = RGB(0, 130, 125);

	Boss(int x, int y)//进行初始化
	{
		this->x = x;
		this->y = y;
	}

	pos show()
	{
		setfillcolor(c);
		fillrectangle(x - 20, y - 20, x + 20, y + 20);
		return pos{ x,y };
	}
	pos del() {
		setfillcolor(0);
		setlinecolor(0);
		rectangle(x - 20, y - 40, x + 20, y + 40);
		fillrectangle(x - 20, y - 40, x + 20, y + 40);
		return pos{ x, y };
	}

	void fire(Ebullet &bullet) {
		bullet.on = true;
		bullet.x = x - 20;//子弹的纵横坐标
		bullet.y = y;
		bullet.d = clock();
	}

	void move() {
		if (angle == true)
			y -= 5;
		if (angle == false)
			y += 5;
		if (y >= 440)
			angle = true;
		if (y <= 40)
			angle = false;
	}

	void hurt() {
		hp -= 4;
		htime = clock();//记录受伤的时间

		//绘制血条
		setfillcolor(0);
		setlinecolor(WHITE);
		fillrectangle(160, 485, 560, 510);
		rectangle(160, 485, 160 + hp * 4, 510);

		setfillcolor(RGB(230, 0, 0));
		setlinecolor(WHITE);
		fillrectangle(160, 485, 160 + hp * 4, 510);

		hurting = true;
		if (hp <= 0) {
			wined = true;//玩家胜利，机器输掉
		}
	}
};
class Tank {
public:
	bool hurting = false;//是否受伤
	bool angle = false;//方向 false 表示向下移动
	clock_t ftime;//开火时间
	clock_t mtime;//移动时间
	clock_t htime;//受伤时间

	COLORREF clr = RGB(150, 180, 210);
	int x, y;
	int hp = 100;//生命值

	COLORREF c = RGB(150, 180, 210);

	Tank(int x, int y)//进行初始化
	{
		this->x = x;
		this->y = y;
	}

	pos show()
	{
		setfillcolor(c);
		fillrectangle(x - 25, y - 25, x + 25, y + 25);
		setfillcolor(RGB(100, 200, 180));
		fillrectangle(x ,y + 5, x + 40,y - 5);//绘制炮筒
		return pos{ x,y };
	}
	pos del() {
		setfillcolor(0);
		setlinecolor(0);
		fillrectangle(x - 25, y - 25, x + 25, y + 25);
		rectangle(x - 25, y - 25, x + 25, y + 25);
		fillrectangle(x, y + 5, x + 40, y - 5);//绘制炮筒
		rectangle(x, y + 5, x + 40, y - 5);//绘制炮筒
		return pos{ x, y };
	}

	void fire(Bullet &bullet) {
		bullet.on = true;//放置子弹
		bullet.x = x +45;//子弹的纵横坐标
		bullet.y = y;
		bullet.d = clock();
		bullet.show();
	}

	//因为手动移动坦克，所有删掉这个函数
	//void move() {
	//	if (angle == true)
	//		y -= 5;
	//	if (angle == false)
	//		y += 5;
	//	if (y >= 440)
	//		angle = true;
	//	if (y <= 40)
	//		angle = false;
	//}

	void hurt() {
		hp -= 20;
		htime = clock();//记录受伤的时间

		//绘制血条
		setfillcolor(0);
		setlinecolor(WHITE);
		fillrectangle(160, 515, 560, 540);
		rectangle(160, 515, 160 + hp * 4, 540);

		setfillcolor(RGB(0,255,1));
		setlinecolor(WHITE);
		fillrectangle(160, 515, 160 + hp * 4, 540);

		hurting = true;
		if (hp <= 0) {
			dead= true;//玩家失败，机器胜利
		}
	}
};


int main() {
	initgraph(640, 550, 4);//初始化屏幕

	//提示
	settextcolor(RGB(0, 255, 0));
	settextstyle(35, 0, L"黑体");
	outtextxy(150, 200, L"W,S移动,K攻击");
	Sleep(3000);

	cleardevice();//刷新提示

	setlinecolor(WHITE);
	setfillcolor(WHITE);
	line(0, 481, 640, 481);//分割画面与血条

	settextstyle(20, 0, L"黑体");
	outtextxy(10, 485, L"BOSS的生命值:");
	setfillcolor(RGB(230, 0, 1));
	fillrectangle(160, 485, 560, 510);//敌人血条

	outtextxy(10, 520, L"玩家的生命值:");
	setfillcolor(RGB(0, 255, 1));
	fillrectangle(160, 515, 560, 540);//玩家血条

	//手动控制 方向
	//GetAsyncKeyState('W');//向上
	/*
	switch(getch()){//getch()不带回显，不需要回车确认
	case 'W':
	case 'w':
	case 72:
	}
	*/

	Tank tk(30, 30);       //玩家坐标初始化
	Bullet bt[MAX];        //玩家的子弹
	Boss bo(580, 240);      //敌人
	Ebullet ebt[MAX];      //敌人的子弹


	//tk.ftime = clock();    //玩家开火时间初始化
	//bo.ftime = clock();    //敌人开火时间初始化
	tk.show();//显示玩家

	while (1)//主循环
	{
		if (wined || dead)//玩家死了或者敌人死了
			break;
		//确定用户当前是否按下了键盘上的一个键的函数
		if (GetAsyncKeyState('W') || GetAsyncKeyState('w'))//玩家移动
		{
			if (tk.y > 28 && (clock() - tk.mtime) >= 40)//间隔40毫秒再按一次，不能连续按，实现延迟
			{
				tk.del(); //删掉原来所在位置
				tk.y -= 3;
				tk.show(); //重新绘制
				tk.mtime = clock();
			}
		}

		if (GetAsyncKeyState('S') || GetAsyncKeyState('s'))//玩家移动
		{
			if (tk.y < 452 && (clock() - tk.mtime) >= 40)
			{
				tk.del();
				tk.y += 3;
				tk.show();
				tk.mtime = clock();
			}
		}

		if (GetAsyncKeyState('K') || GetAsyncKeyState('k'))//玩家开火
		{
			for (int i = 0; i < MAX; i++)//子弹个数最多显示八个
			{
				if (bt[i].on == false && (clock() - tk.ftime) > 800)//没有开火 玩家子弹延时800毫秒
				{
					bt[i].on = true;//开火
					tk.fire(bt[i]);
					tk.ftime = clock();
					break;
				}
			}
		}



		for (int i = 0; i < MAX; i++)//遍历玩家子弹，使子弹刷新
		{
			if (bt[i].on == true && (clock() - bt[i].d) > 20)//放置子弹时间间隔大于20毫秒
			{
				bt[i].del();
				bt[i].move();
				bt[i].show();
				bt[i].d = clock();
				if (bt[i].x >= 635)
					bt[i].on = false, bt[i].del();//到达了屏幕最右端，删除子弹
				if ((bt[i].x + 5 >= bo.x - 20 && bt[i].x - 5 <= bo.x + 20) && (bt[i].y - 5 < bo.y + 40 && bt[i].y + 5 > bo.y - 40))
					//击中敌人
					bt[i].on = false, bo.hurt(), bt[i].del();//血量更新并且删除子弹
			}
		}
		if (clock() - bo.ftime > 700)//敌人自动开火
		{
			for (int i = 0; i < MAX; i++)
			{
				if (ebt[i].on == false)
				{
					bo.fire(ebt[i]); //开火
					break;
				}
			}
			bo.ftime = clock();//敌人子弹时间间隔
		}
		for (int i = 0; i < MAX; i++)//敌人子弹刷新，同上
		{
			if (ebt[i].on == true && (clock() - ebt[i].d > 20))
			{
				ebt[i].del();
				ebt[i].move();
				ebt[i].show();
				ebt[i].d = clock();
				if (ebt[i].x < 5)//到达最左端
					ebt[i].del(), ebt[i].on = false;
				//子弹打到玩家
				if (ebt[i].x - 5 < tk.x + 25 && ebt[i].x + 5 > tk.x - 25 && ebt[i].y - 5 < tk.y + 25 && ebt[i].y + 5 > tk.y - 25)
				{
					ebt[i].on = false, tk.hurt(), ebt[i].del();
				}
			}
		}
		if (tk.hurting == true)//玩家受伤闪烁0.1秒
			if (clock() - tk.htime > 100)
			{

				tk.clr = RGB(150, 180, 210), tk.show(), tk.hurting = false;
			}
			else
				tk.clr = RGB(255, 0, 0), tk.show();
		if (bo.hurting == true)//敌人受伤闪烁0.1秒
			if (clock() - bo.htime > 100)//大于0.1秒显示回玩家本来的颜色
			{

				bo.c = RGB(0, 130, 125), bo.show(), bo.hurting = false;
			}
			else
				bo.c = RGB(0, 255, 0), bo.show();
		if (clock() - bo.mtime > 50)//敌人移动延时;
			bo.del(), bo.move(), bo.show(), bo.mtime = clock();
	}
	if (wined)//胜负已分
	{
		settextcolor(RGB(0, 254, 0));
		settextstyle(35, 0, L"黑体");
		outtextxy(150, 200, L"你打败了boss!你赢了！！");
	}
	else
	{
		settextcolor(RGB(254, 0, 0));
		settextstyle(35, 0, L"黑体");
		outtextxy(140, 200, L"你被boss打败了！");
	}

	Sleep(5000);//等待5秒

	closegraph();//关闭画布

	return 0;
}