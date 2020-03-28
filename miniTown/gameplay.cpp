#include"miniTown.h"
using namespace std;

//�ж�����object�Ƿ�Ӵ�
bool IsCloseTo(Object* A, Object* B)
{
	if (A->x + A->pic->Width > B->x)
	{
		if (A->x < B->x + B->pic->Width)
		{
			if (A->y + A->pic->Height > B->y)
			{
				if (A->y < B->y + B->pic->Height)
				{
					return true;
				}
			}
		}
	}
	return false;
}

//�жϸ���Ʒ�ǲ���rice
bool ObjectIsRice(Object* object)
{
	if (object == NULL)
	{
		return false;
	}
	for (int i = 0; i <= NowRiceSum; i++)
	{
		if (object == &objRice[i])
			return true;
	}

	return false;

}

bool ObjectIsWood(Object* object)
{
	if (object == NULL)
	{
		return false;
	}
	for (int i = 0; i < NowWoodSum; i++)
	{
		if (object == &objWood[i])
		{
			return true;
		}
	}
	return false;
}


//��������Object�����ľ���
float DistanceAToB(Object* A, Object* B)
{
	float distance;
	distance = sqrt((A->x+A->pic->Width/2 - (B->x+B->pic->Width/2)) * (A->x + A->pic->Width / 2 - (B->x + B->pic->Width / 2)) +
		(A->y+A->pic->Height/2 - (B->y+B->pic->Height/2)) * (A->y + A->pic->Height / 2 - (B->y + B->pic->Height / 2)));
	return distance;
}


//Ѱ����DrawObject�����һ�����ӣ��ҵ��˰�������
//type=0ʱ����ͨ���ӣ�1�Ǵ峤����
House* GetANearEmptyHouse(Object *man,int type)
{
	House* NearEmptyHouse = NULL;
	float MinDistance = 999999;
	for (int i = 0; i < NowHouseSum; i++)
	{
		if (house[i].isUsed == false)
		{
			if ((type == 0 && house[i].isKingHouse == false) || (type == 1 && house[i].isKingHouse == true))
			{
				int nowDistance = DistanceAToB(man, house[i].DrawObject);
				if (nowDistance < MinDistance)
				{
					MinDistance = nowDistance;
					NearEmptyHouse = &house[i];
				}
			}
		}
	}
	if (NearEmptyHouse != NULL)
	{
		NearEmptyHouse->isUsed = true;
	}
	return NearEmptyHouse;
}

//�ҵ�һ����DrawObject�������ҵ��˰�������
Field* GetANearUnUsedField(Object* man)
{
	Field* NearUnUsedField = NULL;
	float MinDistance = 999999;
	for (int i = 0; i < NowFieldSum; i++)
	{
		if (field[i].isUsed == false)
		{
			int nowDistance = DistanceAToB(man, field[i].DrawObject);
			if (nowDistance < MinDistance)
			{
				MinDistance = nowDistance;
				NearUnUsedField = &field[i];
			}
		}
	}
	if (NearUnUsedField != NULL)
	{
		NearUnUsedField->isUsed = true;
	}
	return NearUnUsedField;
}

void AddUnFinishHouse(int x, int y)
{
	house[NowHouseSum].buildTime = 0;
	house[NowHouseSum].DrawObject = &objHouse[NowHouseSum];
	house[NowHouseSum].DrawObject->pic = &picHouse1;
	house[NowHouseSum].id = NowHouseSum - 1;
	house[NowHouseSum].DrawObject->x = x *  picHouse.Width;
	house[NowHouseSum].DrawObject->y = y * picHouse.Height;
	AddDrawObject(house[NowHouseSum].DrawObject);
	NowHouseSum++;
	
}


void AddFinishHouse(int x, int y,int type)
{
	house[NowHouseSum].buildTime = house[NowHouseSum].RequireBuildTime;
	house[NowHouseSum].DrawObject = &objHouse[NowHouseSum];
	house[NowHouseSum].DrawObject->pic = &picHouse;
	house[NowHouseSum].id = NowHouseSum;
	house[NowHouseSum].DrawObject->x = x * picHouse.Width;
	house[NowHouseSum].DrawObject->y = y * picHouse.Height;
	if (type == 1)
	{
		house[NowHouseSum].isKingHouse = true;
		house[NowHouseSum].DrawObject->pic = &picKingHouse;
	}
	
	AddDrawObject(house[NowHouseSum].DrawObject);
	NowHouseSum++;
}

void AddFarmer(int x,int y)
{
	objFarmer[NowFarmerSum].pic = &picFarmer;
	objFarmer[NowFarmerSum].x = x * objFarmer[NowFarmerSum].pic->Width;
	objFarmer[NowFarmerSum].y = y * objFarmer[NowFarmerSum].pic->Height;

	farmer[NowFarmerSum].DrawObject = &objFarmer[NowFarmerSum];
	farmer[NowFarmerSum].belongField = GetANearUnUsedField(farmer[NowFarmerSum].DrawObject);
	farmer[NowFarmerSum].belongHouse = GetANearEmptyHouse(farmer[NowFarmerSum].DrawObject);
	farmer[NowFarmerSum].age = 18;
	farmer[NowFarmerSum].monney = 10;
	farmer[NowFarmerSum].wantFoodLevel = 1;
	farmer[NowFarmerSum].wantSexLevel = 1;
	farmer[NowFarmerSum].id = NowFarmerSum;
	

	AddDrawObject(farmer[NowFarmerSum].DrawObject);
	NowFarmerSum++;
}

void AddBuilder(int x, int y)
{
	objBuilder[NowBuilderSum].pic = &picBuilder;
	objBuilder[NowBuilderSum].x = x*objBuilder[NowBuilderSum].pic->Width;
	objBuilder[NowBuilderSum].y = y*objBuilder[NowBuilderSum].pic->Height;

	builder[NowBuilderSum].DrawObject = &objBuilder[NowBuilderSum];
	builder[NowBuilderSum].belongHouse = GetANearEmptyHouse(builder[NowBuilderSum].DrawObject);
	builder[NowBuilderSum].age = 18;
	builder[NowBuilderSum].money = 10;
	builder[NowBuilderSum].wantFoodLevel = 1;
	builder[NowBuilderSum].wantSexLevel = 1;
	builder[NowBuilderSum].id = NowBuilderSum;

	AddDrawObject(builder[NowBuilderSum].DrawObject);
	NowBuilderSum++;
}

void AddKing(int x, int y)
{
	objKing.pic = &picKing;
	objKing.x = x * objKing.pic->Width;
	objKing.y = y * objKing.pic->Height;

	king.DrawObject = &objKing;
	king.belongHouse = GetANearEmptyHouse(king.DrawObject,1);
	king.belongHouse->isUsed = true;
	king.id = 0;
	king.age = 18;
	king.monney = 0;
	king.wantFoodLevel = 1;
	king.wantSexLevel = 1;
	AddDrawObject(king.DrawObject);
}

void AddTree(int x, int y)
{
	objTree[NowTreeSum].pic = &picTree;
	objTree[NowTreeSum].x = x * picTree.Width;
	objTree[NowTreeSum].y = y * picTree.Height;
	tree[NowTreeSum].cutTime = 0;
	tree[NowTreeSum].DrawObject = &objTree[NowTreeSum];
	tree[NowTreeSum].id = NowTreeSum ;
	

	AddDrawObject(&objTree[NowTreeSum]);
	NowTreeSum++;

}

void AddField(int x, int y)
{
	objField[NowFieldSum].pic = &picField;
	objField[NowFieldSum].x = x * picField.Width;
	objField[NowFieldSum].y = y * picField.Height;

	field[NowFieldSum].DrawObject = &objField[NowFieldSum];
	field[NowFieldSum].id = NowFieldSum ;
	field[NowFieldSum].growingTime = 0;
	field[NowFieldSum].isUsed = false;

	AddDrawObject(&objField[NowFieldSum]);
	NowFieldSum++;

}


void ResourceCount()//�Դ���ӵ�е���Դ����ͳ��
{
	int moneyCount = 0;
	int riceCount = 0;
	int woodCount = 0;

	for (int i = 0; i < NowHouseSum; i++)
	{
		if (house[i].isUsed == true)
		{
			riceCount += house[i].StoneRiceSum;
			woodCount += house[i].StoneWoodSum;
		}
	}

	for (int i = 0; i < NowFarmerSum; i++)
	{
		moneyCount += farmer[i].monney;
	}
	for (int i = 0; i < NowBuilderSum; i++)
	{
		moneyCount += builder[i].money;
	}

	cout << "==================" << endl;
	cout << "ResourceCount" << endl;
	cout << "money:" << moneyCount << endl;
	cout << "rice:" << riceCount << endl;
	cout << "wood:" << woodCount << endl;
	cout << "==================" << endl;
	
}


void ShowSky()
{
	//������ʾ̫����background
	objSun.x = ((int)runtime % DayTime) * SCREEN_WIDTH / DayTime*2-objSun.pic->Width;
	objMoon.x = (((int)runtime) % DayTime) * SCREEN_WIDTH / DayTime * 2 - SCREEN_WIDTH-objMoon.pic->Width;
	if(((int)runtime/(DayTime/2))%2==1)
	{
		objBackground.pic = &picBackground1;
	}
	else
	{
		objBackground.pic = &picBackground;
	}
}