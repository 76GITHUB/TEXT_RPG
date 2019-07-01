#include <iostream>
#include <time.h>
using namespace std;

enum MAIN_MENU //���θ޴� ������
{
	MM_NONE, 
	MM_MAP,  //�㼱��
	MM_STORE,//����
	MM_INVENTORY,//����
	MM_EXIT//������
};

enum MAP_TYPE //�ʼ��� ������
{
	MT_NONE,
	MT_EASY,//����
	MT_NORMAL,//����
	MT_HARD,//�����
	MT_BACK//������
};

enum JOB //�÷��̾� ���������� ���� ������
{
	JOB_NONE,
	JOB_KNIGHT,//���
	JOB_ARCHER,//�ü�
	JOB_WIZARD,//������
	JOB_END
};

enum EQUIP //������ ������ ������
{
	EQ_WEAPON, //����
	EQ_ARMOR, //��
	EQ_MAX
};

enum ITEM_TYPE //������Ÿ�� ������
{
	IT_NONE,
	IT_WEAPON, //����
	IT_ARMOR,//��
	IT_BACK
};

enum BATTLE
{
	BATTLE_NONE,
	BATTLE_ATTACK, //����
	BATTLE_BACK //����
};

//��ũ�� ���� ������ ��������� �����ش�.
#define	NAME_SIZE	32 //�̸�����
#define	ITEM_DESC_LENGTH	512 //�����ۼ������
#define	INVENTORY_MAX		20 //�κ��丮�ִ�ũ��
#define	STORE_WEAPON_MAX	3 //���������ִ�ũ��
#define	STORE_ARMOR_MAX		3//�������ִ�ũ��
#define	LEVEL_MAX			10//�ƽ�����ũ��

const int	iLevelUpExp[LEVEL_MAX] = { 4000, 10000, 20000, 35000, 50000, 70000, 100000, 150000, 200000, 400000 };
//����ġ ���̺� ��������

struct _tagItem //������ ����ü
{
	char	strName[NAME_SIZE]; //�������̸�
	char	strTypeName[NAME_SIZE];//�����ۼӼ��̸�
	ITEM_TYPE	eType;//������ Ÿ�� ������ ������ ����
	int		iMin;
	int		iMax;
	int		iPrice;
	int		iSell;
	char	strDesc[ITEM_DESC_LENGTH];
};

struct _tagInventory //�κ��丮 ����ü
{
	_tagItem	tItem[INVENTORY_MAX]; 
	int			iItemCount;
	int			iGold;
};

struct _tagPlayer //�÷��̾� ����ü
{
	char	strName[NAME_SIZE]; //�÷��̾� �̸�
	char	strJobName[NAME_SIZE];//�÷��̾� �����̸�
	JOB		eJob; //���� ������ ����
	int		iAttackMin;
	int		iAttackMax;
	int		iArmorMin;
	int		iArmorMax;
	int		iHP;
	int		iHPMax;
	int		iMP;
	int		iMPMax;
	int		iExp;
	int		iLevel;
	_tagItem	tEquip[EQ_MAX];
	bool		bEquip[EQ_MAX];
	_tagInventory	tInventory;
};

struct _tagMonster // ���� ����ü
{
	char	strName[NAME_SIZE];
	int		iAttackMin;
	int		iAttackMax;
	int		iArmorMin;
	int		iArmorMax;
	int		iHP;
	int		iHPMax;
	int		iMP;
	int		iMPMax;
	int		iLevel;
	int		iExp;
	int		iGoldMin;
	int		iGoldMax;
};

int Input() { //�޴��� ������� �Է��� �ޱ����� �Լ�
	int iInput; 
	cin >> iInput;//�Է�

	if (cin.fail()) //������ �ƴ� ���� �Է¹����� ����ó��
	{
		cin.clear(); //���� ���� Ŭ����
		cin.ignore(1024, '\n'); // \n�Է��������� ���۸� ����
		return INT_MAX;  //INT_MAX�� ���ϵǸ� �߸��Ȱ��� �Է��ߴٴ� �ǹ�
	}
	return iInput;
}

int OPMainMenu() { //���θ޴��� �������Լ�, �׸��� �Է¹��� �޴��� ��ȯ�Ѵ�
	system("cls"); //�߸��� �޴��� �Է��Ѱ�쿡�� MM_NONE��ȯ
	cout << "*************************** �κ� ***************************" << endl;
	cout << "1. ��" << endl;
	cout << "2. ����" << endl;
	cout << "3. ����" << endl;
	cout << "4. ����" << endl;
	cout << "�޴��� �����ϼ��� : ";
	int imenu = Input(); //Input�Լ��� ȣ���Ͽ� ��ȯ�������� imenu�� ������ �ʱ�ȭ

	if (imenu == INT_MAX || imenu <= MM_NONE || imenu > MM_EXIT) //imenu�� INT_MAX���̰ų� MM_NONE=0 �����̰ų�
		MM_NONE; //MM_EXIT=4���� Ŭ��쿡�� MM_NONE�̴�.

	return imenu;
}

int OPMapMenu() {
	system("cls");
	cout << "*************************** �� ***************************" << endl;
	cout << "1. ����" << endl;
	cout << "2. ����" << endl;
	cout << "3. �����" << endl;
	cout << "4. �ڷΰ���" << endl;
	cout << "���� �����ϼ��� : ";

	int imenu = Input(); //Input�Լ��� ȣ���Ͽ� ��ȯ�������� imenu�� ������ �ʱ�ȭ

	if (imenu == INT_MAX || imenu <= MT_NONE || imenu > MT_BACK) //imenu�� INT_MAX���̰ų� MT_NONE=0 �����̰ų�
		MT_NONE; //MT_EXIT=4���� Ŭ��쿡�� MT_NONE�̴�.

	return imenu;

}

int SJob() { //������ �����ϱ����� �Լ�
	int	iJob = JOB_NONE; //�⺻����
	while (iJob == JOB_NONE) // ���ѷ����� ����������
	{
		system("cls");
		cout << "1. ���" << endl;
		cout << "2. �ü�" << endl;
		cout << "3. ������" << endl;
		cout << "������ �����ϼ��� : ";
		iJob = Input();//Input�Լ��� ȣ���Ͽ� ���� �޾ƿ´�


		if (iJob == INT_MAX || iJob <= JOB_NONE || iJob >= JOB_END)
			iJob = JOB_NONE;
	}
	return iJob; //�ùٸ� ���� �Է��ߴٸ� �Է��� �������� ������ ��ȯ�Ѵ�.
}

void SetPlayer(_tagPlayer * pPlayer) { //call-by-address

	cout << "�̸� : ";   // �÷��̾� �̸��� �Է¹޴´�.
	cin.getline(pPlayer->strName, NAME_SIZE - 1);

	pPlayer->eJob = (JOB)SJob(); //SJob�Լ��� int�� ��ȯ������eJob�� JOBŸ�� �����̹Ƿ� ����ȯ�� �����ش�.
	pPlayer->iLevel = 1;
	pPlayer->iExp = 0;
	pPlayer->tInventory.iGold = 10000;

	switch (pPlayer->eJob)
	{
	case JOB_KNIGHT:
		strcpy_s(pPlayer->strJobName, "���");
		pPlayer->iAttackMin = 5;
		pPlayer->iAttackMax = 10;
		pPlayer->iArmorMin = 15;
		pPlayer->iArmorMax = 20;
		pPlayer->iHPMax = 500;
		pPlayer->iHP = 500;
		pPlayer->iMP = 100;
		pPlayer->iMPMax = 100;
		break;
	case JOB_ARCHER:
		strcpy_s(pPlayer->strJobName, "�ü�");
		pPlayer->iAttackMin = 10;
		pPlayer->iAttackMax = 15;
		pPlayer->iArmorMin = 10;
		pPlayer->iArmorMax = 15;
		pPlayer->iHPMax = 400;
		pPlayer->iHP = 400;
		pPlayer->iMP = 200;
		pPlayer->iMPMax = 200;
		break;
	case JOB_WIZARD:
		strcpy_s(pPlayer->strJobName, "������");
		pPlayer->iAttackMin = 15;
		pPlayer->iAttackMax = 20;
		pPlayer->iArmorMin = 5;
		pPlayer->iArmorMax = 10;
		pPlayer->iHPMax = 300;
		pPlayer->iHP = 300;
		pPlayer->iMP = 300;
		pPlayer->iMPMax = 300;
		break;

	}

}

void BattleMode(int imenu) { //��Ʋ���̵��� ������ִ� �Լ�
	switch (imenu)
	{
	case MT_EASY:
		cout << "*************************** ���� ***************************" << endl;
		break;
	case MT_NORMAL:
		cout << "*************************** ���� ***************************" << endl;
		break;
	case MT_HARD:
		cout << "************************** ����� ***************************" << endl;
		break;
	}
}

void OPplayer(_tagPlayer *pPlayer) {
	// �÷��̾� ������ ����Ѵ�.
	cout << "================== Player ==================" << endl;
	cout << "�̸� : " << pPlayer->strName << "\t���� : " <<
		pPlayer->strJobName << endl;
	cout << "���� : " << pPlayer->iLevel << "\t����ġ : " <<
		pPlayer->iExp << " / " << iLevelUpExp[pPlayer->iLevel - 1] << endl;

	// ���⸦ �����ϰ� ���� ��� ���ݷ¿� ������ݷ��� �߰��Ͽ� ����Ѵ�.
	if (pPlayer->bEquip[EQ_WEAPON] == true)
	{
		cout << "���ݷ� : " << pPlayer->iAttackMin << " + " <<
			pPlayer->tEquip[EQ_WEAPON].iMin << " - " <<
			pPlayer->iAttackMax << " + " << pPlayer->tEquip[EQ_WEAPON].iMax;
	}

	else
	{
		cout << "���ݷ� : " << pPlayer->iAttackMin << " - " <<
			pPlayer->iAttackMax;
	}

	// ���� �����ϰ� ���� ��� ���¿� �� ������ �߰��Ͽ� ����Ѵ�.
	if (pPlayer->bEquip[EQ_ARMOR] == true)
	{
		cout << "\t���� : " << pPlayer->iArmorMin << " + " <<
			pPlayer->tEquip[EQ_ARMOR].iMin << " - " <<
			pPlayer->iArmorMax << " + " << pPlayer->tEquip[EQ_ARMOR].iMax << endl;
	}

	else
	{
		cout << "\t���� : " << pPlayer->iArmorMin << " - " <<
			pPlayer->iArmorMax << endl;
	}

	cout << "ü�� : " << pPlayer->iHP << " / " << pPlayer->iHPMax <<
		"\t���� : " << pPlayer->iMP << " / " << pPlayer->iMPMax << endl;

	if (pPlayer->bEquip[EQ_WEAPON])
		cout << "�������� : " << pPlayer->tEquip[EQ_WEAPON].strName;

	else
		cout << "�������� : ����";

	if (pPlayer->bEquip[EQ_ARMOR])
		cout << "\t������ : " << pPlayer->tEquip[EQ_ARMOR].strName << endl;

	else
		cout << "\t������ : ����" << endl;

	cout << "������� : " << pPlayer->tInventory.iGold << " Gold" << endl << endl;

}

void OPmonster(_tagMonster *pMonster) {
	// ���� ���� ���
	cout << "================== Monster ==================" << endl;
	cout << "�̸� : " << pMonster->strName << "\t���� : " <<
		pMonster->iLevel << endl;
	cout << "���ݷ� : " << pMonster->iAttackMin << " - " <<
		pMonster->iAttackMax << "\t���� : " << pMonster->iArmorMin <<
		" - " << pMonster->iArmorMax << endl;
	cout << "ü�� : " << pMonster->iHP << " / " << pMonster->iHPMax <<
		"\t���� : " << pMonster->iMP << " / " << pMonster->iMPMax << endl;
	cout << "ȹ�����ġ : " << pMonster->iExp << "\tȹ���� : " <<
		pMonster->iGoldMin << " - " << pMonster->iGoldMax << endl << endl;
}

int BattleMenu() {
	cout << "1. ����" << endl;
	cout << "2. ��������" << endl;
	cout << "�޴��� �����ϼ��� : ";
	int imenu = Input();

	if (imenu == INT_MAX || imenu <= BATTLE_NONE || imenu > BATTLE_BACK)
		return BATTLE_NONE;

	return imenu;
}


//������ �⺻ �����͸� �ۼ��ϱ����� �Լ�
_tagMonster CreateMonster(char* pName, int iAttackMin, int iAttackMax, int iArmorMin, int iArmorMax,
	int iHP, int iMP, int iLevel,int iExp, int iGoldMin, int iGoldMax) {
	_tagMonster monster = {};

	strcpy_s(monster.strName, pName);
	monster.iAttackMin = iAttackMin;
	monster.iAttackMax = iAttackMax;
	monster.iArmorMin = iArmorMin;
	monster.iArmorMax = iArmorMax;
	monster.iHP = iHP;
	monster.iHPMax = iHP;
	monster.iMP = iMP;
	monster.iMPMax = iMP;
	monster.iLevel = iLevel;
	monster.iExp = iExp;
	monster.iGoldMin = iGoldMin;
	monster.iGoldMax = iGoldMax;

	return monster;
}

void setMonster(_tagMonster *pMonsterArr) { //���� �����Լ�
	pMonsterArr[0] = CreateMonster("�־�ü", 20, 30, 2, 5, 100, 10, 1, 1000, 500, 1500);
	pMonsterArr[1] = CreateMonster("���ڱ� �ú�Ŵ� ���", 80, 130, 60, 90, 2000, 100, 5, 7000, 6000, 8000);
	pMonsterArr[2] = CreateMonster("�巡��", 250, 500, 200, 400, 30000, 20000, 10, 30000, 20000, 50000);
	
}

void Battle(_tagPlayer *pPlayer, _tagMonster *pMonsterArr, int imenu) { //��Ʋ�� ���� �Լ�

	_tagMonster monster = pMonsterArr[MT_BACK - 1];
	while (true) {
		system("cls");
		BattleMode(imenu);

		//�÷��̾ ���
		OPplayer(pPlayer);

		OPmonster(&monster);

		switch (BattleMenu())
		{
		case BATTLE_ATTACK:
			break;
		case BATTLE_BACK:
			return;
		}
	}
}

//�ʿ� ���õ� ������ ó���ϴ� �Լ�
void runMap(_tagPlayer *pPlayer, _tagMonster *pMonsterArr) {
	bool Loop = true;// While���� ���ѷ��� ó���� ���� boolŸ�� ����
	while (Loop) {//true�� ���·� ���� ������ �����Ѵ�

		int imenu = OPMapMenu();

		if (MT_BACK == imenu)
			return;

		//������ �����Ѵ�

		Battle(pPlayer, pMonsterArr, imenu);
	}
}

int main() {
	srand((unsigned int)time(0));
	bool Loop = true; // While���� ���ѷ��� ó���� ���� boolŸ�� ����

	_tagPlayer player = {};//���� ���۽� �÷��̾� ������ ����

	SetPlayer(&player);//�÷��̾� ����

	_tagMonster tMonsterArr[MT_BACK - 1] = {}; //���� ����

	setMonster(tMonsterArr);


	while (Loop) { //true�� ���·� ���� ������ �����Ѵ�
		switch (OPMainMenu())
		{
		case MM_MAP:
			runMap(&player, tMonsterArr); //�ʰ��� ���������� ���� �Լ�ȣ��
			break;
		case MM_STORE:
			break;
		case MM_INVENTORY:
			break;
		case MM_EXIT:
			Loop = false; //MM_EXIT=������ �� �����Ѱ�� Loop=false�Ǿ� while�� ���ѷ����� �����Եȴ�.
			break;
		}
	}
}